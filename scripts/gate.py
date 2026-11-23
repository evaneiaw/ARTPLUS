#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
gate.py — trava mecânica do pipeline ArtPlus.

Nenhuma etapa é considerada concluída por declaração de agente. Este script
verifica fatos no repositório e nos binários da versão de referência
(v24.03.10017) e deriva o estado máximo permitido de cada F-###.

Uso:
    python scripts/gate.py --halt
    python scripts/gate.py --all
    python scripts/gate.py --feature F-003 --stage evidence
    python scripts/gate.py --feature F-003 --stage spec
    python scripts/gate.py --feature F-001 --stage code
    python scripts/gate.py --feature F-001 --stage test
    python scripts/gate.py --feature F-001 --stage audit
    python scripts/gate.py --build                 # build real em build_audit
    python scripts/gate.py --feature F-001 --run-test
    python scripts/gate.py --feature F-001 --emit-token
    python scripts/gate.py --selftest
    python scripts/gate.py --inventory          # confronta INVENTORY x realidade
    python scripts/gate.py --json

Artefatos de execução (verificáveis, ficam versionados):
    docs/testing/gates/build.json
    docs/testing/gates/logs/build-<timestamp>.log
    docs/testing/gates/F-###.xml            (JUnit gerado pelo CTest)
    docs/testing/gates/F-###.test.json
    docs/testing/gates/logs/test-F-###-<timestamp>.log

Token de auditoria (liga o laudo aos artefatos realmente executados):
    token = SHA-256( sha256(build.json) + sha256(F-###.test.json)
                     + sha256(spec) + sha256(manifest) )
    onde sha256(x) é o hexadecimal maiúsculo do SHA-256 de x.

Códigos de saída:
    0  APROVADO
    1  REPROVADO (fato ausente/inconsistente)
    2  BLOQUEADO (bloqueio registrado ou HALT)
    3  ERRO DE USO/AMBIENTE
"""

import argparse
import datetime
import glob
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET

# Permite que o --selftest rode o próprio gate contra um repositório temporário
# sem jamais tocar o repositório real.
_DEFAULT_REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REPO = os.path.abspath(os.environ.get("ARTPLUS_GATE_REPO") or _DEFAULT_REPO)

EVID = os.path.join(REPO, "rag", "evidence")
V240 = r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows"
CANON = "24.03.10017"
HALT_FILE = os.path.join(REPO, "docs", "agents", "HALT.md")
INVENTORY = os.path.join(REPO, "docs", "reverse-engineering", "INVENTORY.md")
BLOQUEIOS = os.path.join(REPO, "docs", "agents", "BLOQUEIOS.md")
AUDIT_DIR = os.path.join(REPO, "docs", "audit")
SPEC_DIR = os.path.join(REPO, "docs", "features")
ADR_DIR = os.path.join(REPO, "docs", "decisions")
SRC_DIR = os.path.join(REPO, "src")
TESTS_DIR = os.path.join(REPO, "tests")
CMAKELISTS = os.path.join(REPO, "CMakeLists.txt")

GATES_DIR = os.path.join(REPO, "docs", "testing", "gates")
LOGS_DIR = os.path.join(GATES_DIR, "logs")
BUILD_DIR_NAME = "build"
BUILD_DIR = os.path.join(REPO, BUILD_DIR_NAME)
BUILD_JSON = os.path.join(GATES_DIR, "build.json")

# Mapa feature -> suíte CTest. A existência do add_test(NAME ...) é conferida
# no CMakeLists.txt real (não basta confiar nesta tabela).
NO_TEST_FEATURES = {"F-007", "F-004"}
FEATURE_TEST_MAP = {
    "F-001": "CutMarkTests",
    "F-002": "MarkSetProcessor",
    "F-003": "BearerBarTests",
    # "F-004" is now in NO_TEST_FEATURES
    "F-005": "PdfRoundTrip",
    "F-006": "SaveDocumentTests",
    "F-008": "F-008",
}

STAGES = ["triado", "analisado", "comportamento", "spec", "arquitetado",
          "implementado", "testado", "auditado", "fora-do-escopo-v24"]
STATE_ALIASES = {
    "triado": "triado", "analisado": "analisado", "comportamento": "comportamento",
    "spec": "spec", "arquitetado": "arquitetado", "implementado": "implementado",
    "testado": "testado", "auditado": "auditado", "fora-do-escopo-v24": "fora-do-escopo-v24",
}


def fail(msg):
    raise RuntimeError(msg)


def read_text(path):
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        return f.read()


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest().upper()


def sha256_text(text):
    return hashlib.sha256(text.encode("utf-8")).hexdigest().upper()


def _now():
    return datetime.datetime.now().astimezone()


def _iso():
    return _now().isoformat(timespec="seconds")


def _stamp():
    return _now().strftime("%Y%m%d-%H%M%S-%f")[:-3]


def _rel(path):
    try:
        return os.path.relpath(path, REPO).replace("\\", "/")
    except ValueError:
        return path


def write_json(path, obj):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        json.dump(obj, f, ensure_ascii=False, indent=2)
        f.write("\n")


def load_json(path):
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)


def norm_addr(a):
    return a.lower().replace("0x", "")


def newest_file(roots):
    """Retorna (mtime, caminho) do arquivo mais recente sob as raízes dadas."""
    newest, which = 0.0, None
    for p in roots:
        if os.path.isfile(p):
            m = os.path.getmtime(p)
            if m > newest:
                newest, which = m, p
            continue
        if not os.path.isdir(p):
            continue
        for root, _, files in os.walk(p):
            for f in files:
                fp = os.path.join(root, f)
                try:
                    m = os.path.getmtime(fp)
                except OSError:
                    continue
                if m > newest:
                    newest, which = m, fp
    return newest, which


# ---------------------------------------------------------------------------
# Ferramentas de build (descoberta dinâmica; nunca depender do PATH)
# ---------------------------------------------------------------------------

def cmake_exe():
    env = os.environ.get("ARTPLUS_CMAKE")
    if env and os.path.exists(env):
        return env
    local = os.environ.get("LOCALAPPDATA", "")
    if local:
        hits = glob.glob(os.path.join(local, "Microsoft", "WinGet", "Packages",
                                     "Kitware.CMake*", "cmake-*", "bin", "cmake.exe"))
        if hits:
            return sorted(hits)[-1]
    found = shutil.which("cmake")
    return found or "cmake"


def ctest_exe():
    cand = os.path.join(os.path.dirname(cmake_exe()), "ctest.exe")
    if os.path.exists(cand):
        return cand
    return shutil.which("ctest") or "ctest"


def mingw_gxx():
    env = os.environ.get("ARTPLUS_GXX")
    if env and os.path.exists(env):
        return env
    local = os.environ.get("LOCALAPPDATA", "")
    if local:
        hits = glob.glob(os.path.join(local, "Microsoft", "WinGet", "Packages",
                                      "BrechtSanders.WinLibs.POSIX.MSVCRT_*",
                                      "mingw64", "bin", "g++.exe"))
        if hits:
            return sorted(hits)[-1]
    found = shutil.which("g++")
    return found or "g++"


def _run_capture(cmd, timeout=3600):
    """Executa cmd capturando stdout+stderr como bytes. Retorna (code, bytes)."""
    try:
        p = subprocess.run(cmd, cwd=REPO, stdout=subprocess.PIPE,
                           stderr=subprocess.STDOUT, timeout=timeout)
        return p.returncode, p.stdout or b""
    except FileNotFoundError as e:
        return 127, f"comando não encontrado: {e}\n".encode("utf-8", "replace")
    except subprocess.TimeoutExpired as e:
        out = e.stdout or b""
        return 124, out + b"\n[gate] timeout\n"


# ---------------------------------------------------------------------------
# Evidência estática/comportamental
# ---------------------------------------------------------------------------

def find_evidence_file(fid, fid_dir):
    m = re.match(r"GHIDRA-(.+?)-(0x)?([0-9A-Fa-f]+)$", fid)
    if not m:
        return None
    addr = norm_addr(m.group(3))
    gdir = os.path.join(fid_dir, "ghidra")
    if not os.path.isdir(gdir):
        return None
    for root, _, files in os.walk(gdir):
        for f in files:
            if not f.lower().endswith((".md", ".json")):
                continue
            m2 = re.search(r"__0?x?([0-9a-f]+)\.(md|json)$", f.lower())
            if m2 and m2.group(1) == addr:
                return os.path.join(root, f)
    return None


def find_cap(cap, fid_dir):
    roots = [os.path.join(fid_dir, "behavior"), os.path.join(REPO, "docs", "behavior")]
    for root in roots:
        if not os.path.isdir(root):
            continue
        for dirpath, _, files in os.walk(root):
            for f in files:
                p = os.path.join(dirpath, f)
                if cap.lower() in f.lower():
                    return p
    for root in roots:
        if not os.path.isdir(root):
            continue
        for dirpath, _, files in os.walk(root):
            for f in files:
                p = os.path.join(dirpath, f)
                if p.lower().endswith((".md", ".txt")):
                    try:
                        if cap.lower() in read_text(p).lower():
                            return p
                    except OSError:
                        pass
    return None


def check_halt():
    return os.path.exists(HALT_FILE)


def check_version():
    """Executa o verificador de versão; retorna (ok, detalhes)."""
    script = os.path.join(REPO, "scripts", "check_version.py")
    if not os.path.exists(script):
        return False, ["scripts/check_version.py ausente"]
    try:
        env = dict(os.environ, PYTHONIOENCODING="utf-8")
        p = subprocess.run([sys.executable, script], capture_output=True,
                           text=True, encoding="utf-8", errors="replace", env=env,
                           cwd=REPO, timeout=180)
        out = (p.stdout or "") + (p.stderr or "")
        if p.returncode == 0:
            return True, []
        bad = [ln.strip() for ln in out.splitlines()
               if ln.strip().startswith(("docs", "rag", "AGENTS", "scripts", "src"))]
        return False, bad[:20] or [out.strip().splitlines()[-1] if out.strip() else "falhou"]
    except Exception as e:  # noqa: BLE001
        return False, [f"erro ao executar check_version: {e}"]


def evidence_file_errors(path):
    """Valida o conteúdo mínimo de um arquivo de evidência Ghidra."""
    errs = []
    txt = read_text(path)
    name = os.path.basename(path)
    if not txt.lstrip().startswith("---"):
        errs.append(f"{name}: sem cabeçalho YAML '---'")
    m = re.search(r"^versao:\s*(\S+)", txt, re.M)
    if not m:
        errs.append(f"{name}: sem campo 'versao:'")
    elif m.group(1) != CANON:
        errs.append(f"{name}: versao='{m.group(1)}' (exige {CANON})")
    if path.lower().endswith(".md"):
        if not re.search(r"^funcao:\s*\S+", txt, re.M):
            errs.append(f"{name}: sem campo 'funcao:'")
        if not re.search(r"^confianca:\s*\S+", txt, re.M):
            errs.append(f"{name}: sem campo 'confianca:'")
    return errs


def manifest_errors(fid):
    errs = []
    info = {"ids_static": 0, "ids_cap": 0}
    fid_dir = os.path.join(EVID, fid)
    mp = os.path.join(fid_dir, "manifest.json")
    if not os.path.exists(mp):
        return ["manifest.json ausente"], info
    try:
        d = json.loads(read_text(mp))
    except Exception as e:  # noqa: BLE001
        return [f"manifest.json inválido: {e}"], info
    ver = str(d.get("versao_ref", ""))
    if ver != CANON:
        errs.append(f"versao_ref='{ver}' (exige {CANON})")
    binp = d.get("binario", "")
    if not binp or not os.path.exists(binp):
        errs.append(f"binario inexistente: {binp!r}")
    elif os.path.isdir(binp):
        errs.append("binario aponta para diretório, não DLL")
    else:
        real = sha256(binp)
        if real != str(d.get("sha256", "")).upper():
            errs.append("sha256 do manifest não confere com o binário")
    est = d.get("estatico", []) or []
    comp = d.get("comportamental", []) or []
    for i in est:
        if not isinstance(i, str) or not i.startswith("GHIDRA-"):
            errs.append(f"id estático inválido: {i!r}")
            continue
        if "0x..." in i or "MANUAL_PENDING" in i:
            errs.append(f"placeholder em id estático: {i}")
            continue
        p = find_evidence_file(i, fid_dir)
        if p is None:
            errs.append(f"evidência estática não resolve: {i}")
        else:
            info["ids_static"] += 1
            errs.extend(evidence_file_errors(p))
    for c in comp:
        if not isinstance(c, str) or "BLOCKED" in c.upper():
            errs.append(f"CAP bloqueado/ inválido: {c!r}")
            continue
        if find_cap(c, fid_dir) is None:
            errs.append(f"CAP não resolve: {c}")
        else:
            info["ids_cap"] += 1
    if info["ids_static"] < 1:
        errs.append("nenhuma evidência estática válida")
    if info["ids_cap"] < 1:
        errs.append("nenhuma evidência comportamental válida")
    return errs, info


def spec_path(fid):
    return os.path.join(SPEC_DIR, f"{fid}.md")


def spec_errors(fid):
    errs = []
    p = spec_path(fid)
    if not os.path.exists(p):
        return ["spec ausente"]
    txt = read_text(p)
    m = re.match(r"^---\r?\n(.*?)\r?\n---\r?\n", txt, re.S)
    if not m:
        return ["frontmatter ausente"]
    fm = m.group(1)
    for key in ("id", "modulo", "versao_ref", "status", "confianca", "evidencia"):
        if not re.search(rf"^{key}:", fm, re.M):
            errs.append(f"frontmatter sem '{key}'")
    vm = re.search(r"^versao_ref:\s*[\"']?([^\"'\r\n]+)", fm, re.M)
    if vm and vm.group(1).strip() != CANON:
        errs.append(f"spec versao_ref='{vm.group(1).strip()}'")
    sm = re.search(r"^status:\s*[\"']?([^\"'\r\n]+)", fm, re.M)
    if sm and sm.group(1).strip() not in ("spec", "architecture", "implemented",
                                          "tested", "audited"):
        errs.append(f"status inválido: {sm.group(1).strip()}")
    body = txt[m.end():]
    required = ["resumo", "entrada", "ui", "regras", "exce", "sa", "rastreab"]
    low = body.lower()
    missing = [k for k in required if k not in low]
    if missing:
        errs.append("seções ausentes: " + ", ".join(missing))
    if "em aberto" not in low:
        errs.append("seção 'Em aberto' ausente")
    ev = re.search(r"^evidencia:\s*\[(.*?)\]", fm, re.M | re.S)
    if ev:
        for item in [x.strip() for x in ev.group(1).split(",") if x.strip()]:
            item = item.strip("\"'")
            if item.startswith("GHIDRA-"):
                if find_evidence_file(item, os.path.join(EVID, fid)) is None:
                    errs.append(f"evidência do frontmatter não resolve: {item}")
    return errs


def adr_errors(fid):
    errs = []
    files = glob.glob(os.path.join(ADR_DIR, "ADR-*.md"))
    files += glob.glob(os.path.join(REPO, "docs", "architecture", "*ADR*.md"))
    hits = []
    for p in files:
        txt = read_text(p)
        if re.search(rf"\b{fid}\b", txt):
            hits.append((p, txt))
    if not hits:
        return [f"nenhuma ADR menciona {fid}"]
    ok = False
    for p, txt in hits:
        low = txt.lower()
        if "estado" in low and ("aprovado" in low or "implementado" in low):
            ok = True
    if not ok:
        errs.append("ADR existente não está 'aprovado'/'implementado'")
    return errs


# ---------------------------------------------------------------------------
# Artefatos de execução: build.json / F-###.test.json
# ---------------------------------------------------------------------------

def test_json_path(fid):
    return os.path.join(GATES_DIR, f"{fid}.test.json")


def test_xml_path(fid):
    return os.path.abspath(os.path.join(GATES_DIR, f"{fid}.xml"))


def _artifact_stale(path, roots, label):
    t = os.path.getmtime(path)
    newest, which = newest_file(roots)
    if newest > t:
        return [f"{label} ({_rel(path)}) é mais antigo que {_rel(which)} "
                f"(artefato precisa ser gerado depois do código)"]
    return []


def build_artifact_errors():
    """Verifica docs/testing/gates/build.json e o log correspondente."""
    errs = []
    if not os.path.exists(BUILD_JSON):
        return ["build.json ausente — rode: python scripts/gate.py --build"]
    try:
        d = load_json(BUILD_JSON)
    except Exception as e:  # noqa: BLE001
        return [f"build.json inválido: {e}"]
    for key in ("timestamp", "command", "exit_code", "log_path", "log_sha256", "build_dir"):
        if key not in d:
            errs.append(f"build.json sem campo '{key}'")
    if not errs:
        if d["exit_code"] != 0:
            errs.append(f"build.json registra exit_code={d['exit_code']} (build falhou)")
        bdir = os.path.join(REPO, str(d["build_dir"]).replace("/", os.sep))
        if not os.path.isdir(bdir):
            errs.append(f"build_dir inexistente: {d['build_dir']}")
        logp = os.path.join(REPO, str(d["log_path"]).replace("/", os.sep))
        if not os.path.exists(logp):
            errs.append(f"log de build ausente: {d['log_path']}")
        elif sha256(logp) != str(d["log_sha256"]).upper():
            errs.append("log_sha256 do build.json não confere com o log real")
        errs.extend(_artifact_stale(BUILD_JSON, [SRC_DIR], "build.json"))
    return errs


def test_artifact_errors(fid):
    """Verifica F-###.test.json, o XML JUnit e o frescor contra src/tests."""
    errs = []
    jp = test_json_path(fid)
    if not os.path.exists(jp):
        return [f"{fid}.test.json ausente — rode: python scripts/gate.py "
                f"--feature {fid} --run-test"]
    try:
        d = load_json(jp)
    except Exception as e:  # noqa: BLE001
        return [f"{fid}.test.json inválido: {e}"]
    for key in ("timestamp", "command", "exit_code", "xml_path", "xml_sha256",
                "tests", "failures"):
        if key not in d:
            errs.append(f"{fid}.test.json sem campo '{key}'")
    if errs:
        return errs
    if d.get("feature") and d["feature"] != fid:
        errs.append(f"{fid}.test.json pertence a {d['feature']}")
    if d["exit_code"] != 0:
        errs.append(f"{fid}.test.json registra exit_code={d['exit_code']} (CTest falhou)")
    tests = d.get("tests") or []
    if not isinstance(tests, list) or len(tests) < 1:
        errs.append(f"{fid}.test.json não registra nenhum teste executado")
    failures = d.get("failures")
    if isinstance(failures, list):
        failures = len(failures)
    if not isinstance(failures, int):
        errs.append(f"{fid}.test.json campo 'failures' inválido: {failures!r}")
    elif failures != 0:
        names = [t.get("name") for t in tests if t.get("status") != "passed"]
        errs.append(f"{fid}.test.json registra {failures} falha(s): {names}")
    xmlp = d.get("xml_path") or ""
    if not xmlp or not os.path.isabs(xmlp):
        errs.append(f"{fid}.test.json xml_path não é absoluto: {xmlp!r}")
    elif not os.path.exists(xmlp):
        errs.append(f"XML JUnit ausente: {xmlp}")
    elif sha256(xmlp) != str(d["xml_sha256"]).upper():
        errs.append(f"xml_sha256 do {fid}.test.json não confere com o XML real")
    errs.extend(_artifact_stale(jp, [SRC_DIR, TESTS_DIR], f"{fid}.test.json"))
    return errs


def resolve_test(fid):
    """Mapeia F-### -> suíte CTest e confere o add_test no CMakeLists.txt."""
    name = FEATURE_TEST_MAP.get(fid)
    if not name:
        if fid in NO_TEST_FEATURES:
            return None, f"{fid} não possui teste mapeado (sem suíte em CMakeLists.txt)"
        return None, f"{fid}: mapeamento feature->teste desconhecido"
    if not os.path.exists(CMAKELISTS):
        return None, "CMakeLists.txt ausente"
    txt = read_text(CMAKELISTS)
    if not re.search(rf"add_test\s*\(\s*NAME\s+{re.escape(name)}\b", txt, re.I):
        return None, f"add_test(NAME {name}) não encontrado em CMakeLists.txt"
    return name, None


def compute_token_files(build_p, test_p, spec_p, manifest_p):
    """token = sha256(sha256(build)+sha256(test)+sha256(spec)+sha256(manifest))."""
    paths = [build_p, test_p, spec_p, manifest_p]
    missing = [p for p in paths if not os.path.exists(p)]
    if missing:
        return None, [], [f"token impossível: artefato ausente {_rel(p)}" for p in missing]
    parts = [sha256(p) for p in paths]
    return sha256_text("".join(parts)), parts, []


def compute_token(fid):
    return compute_token_files(
        BUILD_JSON,
        test_json_path(fid),
        spec_path(fid),
        os.path.join(EVID, fid, "manifest.json"),
    )


# ---------------------------------------------------------------------------
# Gates de etapa
# ---------------------------------------------------------------------------

def code_errors(fid):
    """Spec declara os arquivos, eles existem, e há build real e fresco."""
    errs = []
    p = spec_path(fid)
    if not os.path.exists(p):
        return ["spec ausente (não é possível mapear código)"]
    txt = read_text(p)
    paths = set(re.findall(r"`(src/[A-Za-z0-9_./-]+\.(?:cpp|h|hpp))`", txt))
    paths |= set(re.findall(r"(src/[A-Za-z0-9_./-]+\.(?:cpp|h|hpp))", txt))
    if not paths:
        return ["spec não declara arquivos de implementação em src/"]
    for rel in sorted(paths):
        ap = os.path.join(REPO, rel.replace("/", os.sep))
        if not os.path.exists(ap):
            errs.append(f"arquivo da spec ausente: {rel}")
    errs.extend(build_artifact_errors())
    return errs


def test_errors(fid):
    errs = []
    files = glob.glob(os.path.join(TESTS_DIR, "**", "*.cpp"), recursive=True)
    hit = [f for f in files if re.search(rf"\b{fid}\b", read_text(f))]
    if not hit:
        return [f"nenhum teste cita {fid}"]
    for f in hit:
        if not re.search(r"QVERIFY|QCOMPARE|QEXPECT_FAIL|REQUIRE|CHECK", read_text(f)):
            errs.append(f"teste sem asserção: {os.path.relpath(f, REPO)}")
    errs.extend(test_artifact_errors(fid))
    return errs


def audit_errors(fid):
    errs = []
    files = sorted(glob.glob(os.path.join(AUDIT_DIR, f"{fid}-audit*.md")))
    if not files:
        return [f"laudo de auditoria ausente ({fid}-audit*.md)"]
    latest = max(files, key=os.path.getmtime)
    txt = read_text(latest)
    vm = re.search(r"veredito[^\n]*", txt, re.I)
    if not vm:
        errs.append(f"{os.path.basename(latest)} sem 'Veredito'")
    else:
        verdict = vm.group(0).upper()
        if "REPROVADO" in verdict and "APROVADO" not in verdict:
            errs.append(f"{os.path.basename(latest)} está REPROVADO")
    if not re.search(r"(cmake|ctest|build)", txt, re.I):
        errs.append("laudo não registra comando de build/teste")

    # code + test precisam estar verdes para o laudo valer
    ce = code_errors(fid)
    te = test_errors(fid)
    if ce:
        errs.append("GATE code não está verde: " + "; ".join(ce[:3]))
    if te:
        errs.append("GATE test não está verde: " + "; ".join(te[:3]))

    # token vincula o laudo aos artefatos executados
    token, _, terr = compute_token(fid)
    if terr:
        errs.extend(terr)
    else:
        found = {h.upper() for h in re.findall(r"[0-9A-Fa-f]{64}", txt)}
        if token not in found:
            errs.append(f"laudo sem token de gate válido (esperado {token})")

    # frescor: laudo anterior ao código/evidência = inválido
    t_audit = os.path.getmtime(latest)
    newest, which = newest_file([SRC_DIR])
    mp = os.path.join(EVID, fid, "manifest.json")
    if os.path.exists(mp):
        m = os.path.getmtime(mp)
        if m > newest:
            newest, which = m, mp
    if t_audit < newest:
        errs.append(f"laudo é mais antigo que {_rel(which)} (stale)")
    return errs


def blocked_features():
    if not os.path.exists(BLOQUEIOS):
        return set()
    txt = read_text(BLOQUEIOS)
    return set(re.findall(r"\bF-\d{3}\b", txt))


def derived_state(fid, results):
    """Estado máximo comprovável a partir dos gates."""
    if fid in blocked_features():
        return "bloqueado"
    if results["evidence"]:
        return "triado"
    if results["spec"]:
        return "analisado"
    if results["adr"]:
        return "spec"
    if results["code"]:
        return "arquitetado"
    if results["test"]:
        return "implementado"
    if results["audit"]:
        return "testado"
    return "auditado"


def parse_inventory():
    """Retorna {F-###: estado_declarado}."""
    out = {}
    if not os.path.exists(INVENTORY):
        return out
    for ln in read_text(INVENTORY).splitlines():
        if not ln.strip().startswith("|"):
            continue
        cells = [c.strip() for c in ln.strip().strip("|").split("|")]
        if len(cells) < 4:
            continue
        m = re.search(r"F-\d{3}", " ".join(cells))
        if not m:
            continue
        state = cells[3].lower()
        state = re.sub(r"\(.*?\)", "", state).strip()
        state = state.replace("**", "").strip()
        out[m.group(0)] = state
    return out


def run_feature(fid):
    res = {}
    res["halt"] = check_halt()
    ev_err, ev_info = manifest_errors(fid)
    res["evidence"] = ev_err
    res["evidence_info"] = ev_info
    res["spec"] = spec_errors(fid)
    res["adr"] = adr_errors(fid)
    res["code"] = code_errors(fid)
    res["test"] = test_errors(fid)
    res["audit"] = audit_errors(fid)
    return res


def inventory_verdict(fid, derived, claimed, res):
    """Retorna (ok, mensagem) da coerência INVENTORY x estado comprovado."""
    if not claimed:
        return True, None
    c = STATE_ALIASES.get(claimed, claimed)
    if c == "bloqueado":
        if fid not in blocked_features():
            return False, "declara 'bloqueado' sem registro em BLOQUEIOS.md"
        return True, None
    if c == "fora-do-escopo-v24":
        if fid in blocked_features():
            return False, "declara 'fora-do-escopo-v24' mas a feature está bloqueada"
        # For 'fora-do-escopo-v24', evidence, spec, and adr gates must pass.
        # Code and test gates must indicate absence of artifacts.
        if res["evidence"] or res["spec"] or res["adr"]:
            return False, "declara 'fora-do-escopo-v24' mas as etapas de evidência/spec/ADR não estão verdes"

        # Check that the code_errors implies no code declared/present
        code_errs = res["code"]
        code_ok = False
        if len(code_errs) == 1 and ("não declara arquivos de implementação em src/" in code_errs[0] or "arquivo da spec ausente" in code_errs[0]):
            code_ok = True
        elif len(code_errs) == 2 and any("arquivo da spec ausente" in e for e in code_errs):
            code_ok = True
        elif not code_errs and not os.path.exists(spec_path(fid)): # No spec, so no code to declare
             code_ok = True
        # If code_errors finds other issues, it's not a clean "no code" state.
        if not code_ok:
            return False, f"declara 'fora-do-escopo-v24' mas a etapa de código não indica ausência de implementação: {code_errs}"

        # Check that test_errors implies no tests
        test_errs = res["test"]
        test_ok = False
        if len(test_errs) == 1 and "nenhum teste cita" in test_errs[0]:
            test_ok = True
        elif fid in NO_TEST_FEATURES: # If no test is expected, this is also okay
            test_ok = True
        # If test_errors finds other issues, it's not a clean "no test" state.
        if not test_ok:
             return False, "declara 'fora-do-escopo-v24' mas a etapa de testes não indica ausência de testes"

        # Also check for actual test artifacts, should not exist
        if os.path.exists(test_json_path(fid)):
            return False, "declara 'fora-do-escopo-v24' mas artefatos de teste ainda existem"

        # Since code_errors checks build_artifact_errors, we don't need to recheck it directly.
        # The key is that it *must not* fail due to code artifacts existing.

        return True, None
    if c in STAGES:
        if STAGES.index(c) > STAGES.index(derived):
            return False, f"declara '{claimed}' mas só prova '{derived}'"
        return True, None
    return False, f"estado declarado não reconhecido: '{claimed}'"



def print_feature(fid, res, claimed=None):
    derived = derived_state(fid, res)
    print(f"\n=== {fid} ===")
    print(f"  estado comprovado: {derived}" + (f"  | declarado: {claimed}" if claimed else ""))
    for stage in ("evidence", "spec", "adr", "code", "test", "audit"):
        errs = res[stage]
        label = {"evidence": "GATE 3 evidência", "spec": "GATE 2 spec",
                 "adr": "GATE 2 arquitetura", "code": "GATE 4 código",
                 "test": "GATE 5 testes", "audit": "GATE 6 auditoria"}[stage]
        if errs:
            print(f"  [{label}] REPROVADO")
            for e in errs:
                print(f"      - {e}")
        else:
            print(f"  [{label}] ok")
    inv_ok, inv_msg = inventory_verdict(fid, derived, claimed, res)
    if not inv_ok:
        print(f"  [GATE 7 inventário] REPROVADO: {inv_msg}")
    return derived, inv_ok


# ---------------------------------------------------------------------------
# Execução real: build e CTest
# ---------------------------------------------------------------------------

def cmd_build():
    os.makedirs(LOGS_DIR, exist_ok=True)
    cmake = cmake_exe()
    log_path = os.path.join(LOGS_DIR, f"build-{_stamp()}.log")
    chunks = []
    configure_code = None

    if not os.path.exists(os.path.join(BUILD_DIR, "CMakeCache.txt")):
        cfg = [cmake, "--preset", "mingw-msvcrt"]
        print("[build] configure:", " ".join(cfg))
        configure_code, cfg_out = _run_capture(cfg, timeout=900)
        chunks.append(("CONFIGURE", cfg, configure_code, cfg_out))
        if configure_code != 0:
            _write_build_log(log_path, chunks)
            _write_build_json(log_path, " ".join(cfg), configure_code, configure_code, True)
            print(f"[build] configure FALHOU (exit {configure_code}); log: {_rel(log_path)}")
            return 1
    else:
        print(f"[build] configure ignorado (cache existente em {BUILD_DIR_NAME}/CMakeCache.txt)")

    cmd = [cmake, "--build", "--preset", "release-mingw"]
    print("[build] executando:", " ".join(cmd))
    code, out = _run_capture(cmd, timeout=3600)
    chunks.append(("BUILD", cmd, code, out))
    _write_build_log(log_path, chunks)
    _write_build_json(log_path, " ".join(cmd), code, configure_code, False)

    print(f"[build] exit_code={code}")
    print(f"[build] log: {_rel(log_path)}")
    print(f"[build] artefato: {_rel(BUILD_JSON)}")
    if code == 0:
        print("[build] APROVADO")
        return 0
    print("[build] REPROVADO — veja o log")
    return 1


def _write_build_log(log_path, chunks):
    with open(log_path, "wb") as f:
        for label, cmd, code, out in chunks:
            f.write(f"===== {label} @ {_iso()} =====\n".encode("utf-8"))
            f.write(("$ " + " ".join(cmd) + "\n").encode("utf-8"))
            f.write(out or b"")
            if not (out or b"").endswith(b"\n"):
                f.write(b"\n")
            f.write(f"===== {label} exit_code={code} =====\n\n".encode("utf-8"))


def _write_build_json(log_path, command, exit_code, configure_code, configure_only):
    write_json(BUILD_JSON, {
        "timestamp": _iso(),
        "command": command,
        "exit_code": exit_code,
        "log_path": _rel(log_path),
        "log_sha256": sha256(log_path),
        "build_dir": BUILD_DIR_NAME,
        "configured": configure_code is not None,
        "configure_exit_code": configure_code,
    })


def cmd_run_test(fid):
    if not fid:
        print("[test] erro de uso: --run-test exige --feature F-###")
        return 3
    test_name, err = resolve_test(fid)
    if err:
        print(f"[test] {err}")
        return 3
    if not os.path.exists(os.path.join(BUILD_DIR, "CTestTestfile.cmake")):
        print(f"[test] {BUILD_DIR_NAME} não está configurado; rode --build primeiro")
        return 1

    os.makedirs(LOGS_DIR, exist_ok=True)
    xml_path = test_xml_path(fid)
    os.makedirs(os.path.dirname(xml_path), exist_ok=True)
    if os.path.exists(xml_path):
        os.remove(xml_path)  # garante que só validamos XML gerado nesta execução

    log_path = os.path.join(LOGS_DIR, f"test-{fid}-{_stamp()}.log")
    cmd = [ctest_exe(), "--test-dir", BUILD_DIR_NAME,
           "--output-junit", xml_path, "--output-on-failure",
           "-R", f"^{re.escape(test_name)}$"]
    print("[test] executando:", " ".join(cmd))
    code, out = _run_capture(cmd, timeout=1800)
    with open(log_path, "wb") as f:
        f.write(f"===== CTEST @ {_iso()} =====\n".encode("utf-8"))
        f.write(("$ " + " ".join(cmd) + "\n").encode("utf-8"))
        f.write(out or b"")
        if not (out or b"").endswith(b"\n"):
            f.write(b"\n")
        f.write(f"===== CTEST exit_code={code} =====\n".encode("utf-8"))

    print(f"[test] exit_code={code}; log: {_rel(log_path)}")

    # O CTest reancora caminhos relativos em --test-dir; exigimos o XML absoluto.
    if not os.path.exists(xml_path):
        print(f"[test] REPROVADO: XML JUnit não foi gerado em {xml_path}")
        return 1

    try:
        tests, failures, details = parse_junit(xml_path)
    except Exception as e:  # noqa: BLE001
        print(f"[test] REPROVADO: XML JUnit inválido: {e}")
        return 1

    passed = sum(1 for t in tests if t["status"] == "passed")
    print(f"[test] testes={len(tests)} passaram={passed} falhas={failures}")
    for t in tests:
        print(f"    - {t['name']}: {t['status']} ({t['time']:.3f}s)")

    write_json(test_json_path(fid), {
        "timestamp": _iso(),
        "feature": fid,
        "test_name": test_name,
        "command": " ".join(cmd),
        "exit_code": code,
        "xml_path": xml_path,
        "xml_sha256": sha256(xml_path),
        "log_path": _rel(log_path),
        "tests": tests,
        "failures": failures,
        "failure_details": details,
    })
    print(f"[test] artefato: {_rel(test_json_path(fid))}")
    print(f"[test] xml_sha256: {sha256(xml_path)}")

    ok = code == 0 and failures == 0 and len(tests) >= 1
    print("[test] APROVADO" if ok else "[test] REPROVADO")
    return 0 if ok else 1


def parse_junit(xml_path):
    root = ET.parse(xml_path).getroot()
    tests = []
    details = []
    for tc in root.iter("testcase"):
        name = tc.get("name") or "?"
        try:
            t = float(tc.get("time") or 0.0)
        except ValueError:
            t = 0.0
        status = "passed"
        node = tc.find("failure")
        if node is None:
            node = tc.find("error")
            if node is not None:
                status = "error"
        else:
            status = "failed"
        if node is None:
            sk = tc.find("skipped")
            if sk is not None:
                status = "skipped"
        if status == "failed" or status == "error":
            msg = (node.get("message") or node.text or "").strip()
            details.append({"name": name, "status": status, "message": msg[:800]})
        elif status == "skipped":
            details.append({"name": name, "status": status, "message": "teste pulado"})
        tests.append({"name": name, "status": status, "time": round(t, 3)})
    failures = sum(1 for t in tests if t["status"] != "passed")
    return tests, failures, details


def cmd_emit_token(fid):
    if not fid:
        print("[token] erro de uso: --emit-token exige --feature F-###")
        return 3
    token, parts, errs = compute_token(fid)
    if errs:
        for e in errs:
            print(f"[token] {e}")
        return 1
    print(token)
    return 0


# ---------------------------------------------------------------------------
# --selftest: 17 cenários em repositórios temporários (não toca o repo real)
# ---------------------------------------------------------------------------

FIXTURE_SPEC = """---
id: F-001
modulo: Fixture
versao_ref: 24.03.10017
status: spec
confianca: alta
evidencia: [GHIDRA-Fixture-0x1000]
---

# F-001 — fixture

## Resumo
Fixture de teste do gate.

## Entrada
Arquivo de fixture.

## UI
Nenhuma.

## Regras
R1. Regra sintética.

## Exceções
E1. Nenhuma.

## Saída
Resultado sintético.

## Rastreabilidade
GHIDRA-Fixture-0x1000.

## Em aberto
Nada.

Implementação: `src/feature/feature.cpp`.
"""


def _fixture_write(root, rel, text):
    p = os.path.join(root, rel.replace("/", os.sep))
    os.makedirs(os.path.dirname(p), exist_ok=True)
    with open(p, "w", encoding="utf-8", newline="\n") as f:
        f.write(text)


def _fixture_write_bytes(root, rel, data):
    p = os.path.join(root, rel.replace("/", os.sep))
    os.makedirs(os.path.dirname(p), exist_ok=True)
    with open(p, "wb") as f:
        f.write(data)


def _fixture_paths(root):
    return {
        "build": os.path.join(root, "docs", "testing", "gates", "build.json"),
        "test": os.path.join(root, "docs", "testing", "gates", "F-001.test.json"),
        "spec": os.path.join(root, "docs", "features", "F-001.md"),
        "manifest": os.path.join(root, "rag", "evidence", "F-001", "manifest.json"),
        "xml": os.path.join(root, "docs", "testing", "gates", "F-001.xml"),
        "audit": os.path.join(root, "docs", "audit", "F-001-audit.md"),
        "inventory": os.path.join(root, "docs", "reverse-engineering", "INVENTORY.md"),
    }


def _fixture_build(root):
    """Cria um repositório sintético completo e coerente (todos os gates verdes)."""
    _fixture_write(root, "scripts/check_version.py", "import sys\nsys.exit(0)\n")
    _fixture_write(root, "CMakeLists.txt", """cmake_minimum_required(VERSION 3.22)
project(Fixture CXX)
add_executable(test_cut_mark tests/unit/test_cut_mark.cpp)
add_test(NAME CutMarkTests COMMAND test_cut_mark)
""")
    _fixture_write(root, "tests/unit/test_cut_mark.cpp",
                   "// F-001 fixture\nvoid t() { QVERIFY(true); }\n")
    _fixture_write(root, "src/feature/feature.cpp", "int fixture_fn() { return 1; }\n")
    _fixture_write(root, "docs/features/F-001.md", FIXTURE_SPEC)
    _fixture_write(root, "docs/decisions/ADR-001-fixture.md",
                   "# ADR-001 fixture\n\nFeature: F-001\nEstado: aprovado\n")
    _fixture_write(root, "docs/reverse-engineering/INVENTORY.md", """# INVENTORY fixture

| # | Feature | Módulo | Estado |
|---|---|---|---|
| 1 | Cut Mark (F-001) | Fixture | **auditado** |
""")

    binp = os.path.join(root, "rag", "evidence", "F-001", "bin.dll")
    os.makedirs(os.path.dirname(binp), exist_ok=True)
    with open(binp, "wb") as f:
        f.write(b"MZ fixture binary")
    _fixture_write(root, "rag/evidence/F-001/ghidra/Fixture__0x1000.md",
                   "---\nversao: 24.03.10017\nfuncao: fixture_fn\nconfianca: alta\n---\n")
    _fixture_write(root, "rag/evidence/F-001/behavior/CAP-20261118-01.md",
                   "# CAP-20261118-01\nFixture comportamental.\n")
    write_json(os.path.join(root, "rag", "evidence", "F-001", "manifest.json"), {
        "id": "F-001",
        "versao_ref": CANON,
        "binario": binp,
        "sha256": _sha_file(binp),
        "estatico": ["GHIDRA-Fixture-0x1000"],
        "comportamental": ["CAP-20261118-01"],
        "bloqueios": [],
    })

    paths = _fixture_paths(root)
    os.makedirs(os.path.join(root, "build_audit"), exist_ok=True)
    logp = os.path.join(root, "docs", "testing", "gates", "logs", "build-fixture.log")
    _fixture_write_bytes(root, "docs/testing/gates/logs/build-fixture.log",
                         b"$ cmake --build build_audit -j 6\nfixture build ok\n")
    write_json(paths["build"], {
        "timestamp": _iso(),
        "command": "cmake --build build_audit -j 6",
        "exit_code": 0,
        "log_path": "docs/testing/gates/logs/build-fixture.log",
        "log_sha256": _sha_file(logp),
        "build_dir": "build_audit",
    })
    _fixture_write(root, "docs/testing/gates/F-001.xml",
                   '<?xml version="1.0" encoding="UTF-8"?>\n'
                   '<testsuites><testsuite name="CutMarkTests" tests="1" failures="0">'
                   '<testcase name="CutMarkTests" time="0.010"/></testsuite></testsuites>\n')
    _write_fixture_test_json(root, failures=0, exit_code=0)
    token, _, errs = compute_token_files(paths["build"], paths["test"],
                                         paths["spec"], paths["manifest"])
    assert not errs, errs
    _fixture_write(root, "docs/audit/F-001-audit.md",
                   "# F-001 fixture — laudo\n\n"
                   "Veredito: APROVADO\n\n"
                   "Comandos: ctest --test-dir build_audit --output-on-failure\n\n"
                   f"Gate-Token: {token}\n")


def _sha_file(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        h.update(f.read())
    return h.hexdigest().upper()


def _write_fixture_test_json(root, failures, exit_code):
    paths = _fixture_paths(root)
    tests = [{"name": "CutMarkTests", "status": "passed" if failures == 0 else "failed",
              "time": 0.01}]
    write_json(paths["test"], {
        "timestamp": _iso(),
        "feature": "F-001",
        "test_name": "CutMarkTests",
        "command": f"ctest --test-dir build_audit --output-junit {paths['xml']} "
                   f"--output-on-failure -R ^CutMarkTests$",
        "exit_code": exit_code,
        "xml_path": paths["xml"],
        "xml_sha256": _sha_file(paths["xml"]),
        "log_path": "docs/testing/gates/logs/test-F-001-fixture.log",
        "tests": tests,
        "failures": failures,
        "failure_details": [] if failures == 0 else [
            {"name": "CutMarkTests", "status": "failed", "message": "falha sintética"}],
    })


def _mut_failed_test(root):
    p = _fixture_paths(root)["xml"]
    with open(p, "w", encoding="utf-8", newline="\n") as f:
        f.write('<?xml version="1.0" encoding="UTF-8"?>\n'
                '<testsuites><testsuite name="CutMarkTests" tests="1" failures="1">'
                '<testcase name="CutMarkTests" time="0.010">'
                '<failure message="falha sintética"/></testcase>'
                '</testsuite></testsuites>\n')
    _write_fixture_test_json(root, failures=1, exit_code=8)


def _mut_audit_rejected(root):
    p = _fixture_paths(root)["audit"]
    txt = read_text(p).replace("Veredito: APROVADO", "Veredito: REPROVADO")
    _fixture_write(root, "docs/audit/F-001-audit.md", txt)


def _mut_halt(root):
    _fixture_write(root, "docs/agents/HALT.md", "# HALT\nAtivo.\n")


def _mut_cap_blocked(root):
    p = _fixture_paths(root)["manifest"]
    d = load_json(p)
    d["comportamental"] = ["CAP-BLOCKED-01"]
    write_json(p, d)


def _mut_spec_incomplete(root):
    p = _fixture_paths(root)["spec"]
    txt = read_text(p).replace("## Em aberto\nNada.\n", "")
    _fixture_write(root, "docs/features/F-001.md", txt)


def _mut_inventory_ahead(root):
    os.remove(_fixture_paths(root)["manifest"])


def _mut_inventory_coherent_red_stage(root):
    """Inventário coerente com etapa vermelha: declarado == comprovado ('triado').

    Corrompe o sha256 do manifest (evidência vermelha → comprovado 'triado') e
    declara 'triado' no INVENTORY. --inventory deve aprovar (0) mesmo com a
    etapa vermelha, enquanto --all reprova (1).
    """
    _fixture_write(root, "docs/reverse-engineering/INVENTORY.md", """# INVENTORY fixture

| # | Feature | Módulo | Estado |
|---|---|---|---|
| 1 | Cut Mark (F-001) | Fixture | **triado** |
""")
    p = _fixture_paths(root)["manifest"]
    d = load_json(p)
    d["sha256"] = "0" * 64
    write_json(p, d)


def _mut_conclusion_without_evidence(root):
    os.remove(_fixture_paths(root)["manifest"])


def _mut_hash_divergent(root):
    p = _fixture_paths(root)["manifest"]
    d = load_json(p)
    d["sha256"] = "0" * 64
    write_json(p, d)


def _mut_build_absent(root):
    os.remove(_fixture_paths(root)["build"])


def _mut_test_absent(root):
    os.remove(_fixture_paths(root)["test"])


def _mut_token_mismatch(root):
    p = _fixture_paths(root)["audit"]
    txt = read_text(p)
    token, _, _ = compute_token_files(*[ _fixture_paths(root)[k]
                                         for k in ("build", "test", "spec", "manifest")])
    txt = txt.replace(token, "F" * 64)
    _fixture_write(root, "docs/audit/F-001-audit.md", txt)


def _mut_build_stale(root):
    p = _fixture_paths(root)["build"]
    src_newest, _ = newest_file([os.path.join(root, "src")])
    os.utime(p, (src_newest - 120, src_newest - 120))


def _mut_build_failed(root):
    p = _fixture_paths(root)["build"]
    d = load_json(p)
    d["exit_code"] = 1
    write_json(p, d)


def _mut_test_stale(root):
    p = _fixture_paths(root)["test"]
    newest, _ = newest_file([os.path.join(root, "src"), os.path.join(root, "tests")])
    os.utime(p, (newest - 120, newest - 120))


def run_selftest():
    script = os.path.abspath(__file__)
    tmp = tempfile.mkdtemp(prefix="artplus_gate_selftest_")
    base = os.path.join(tmp, "base")
    os.makedirs(base)
    _fixture_build(base)

    scenarios = [
        ("tudo ok (code/test/audit)", None,
         [(["--all"], 0),
          (["--feature", "F-001", "--stage", "code"], 0),
          (["--feature", "F-001", "--stage", "test"], 0),
          (["--feature", "F-001", "--stage", "audit"], 0)]),
        ("teste falho", _mut_failed_test,
         [(["--feature", "F-001", "--stage", "test"], 1)]),
        ("auditoria reprovada", _mut_audit_rejected,
         [(["--feature", "F-001", "--stage", "audit"], 1)]),
        ("HALT ativo", _mut_halt,
         [(["--halt"], 2), (["--all"], 2)]),
        ("CAP-BLOCKED", _mut_cap_blocked,
         [(["--feature", "F-001", "--stage", "evidence"], 1)]),
        ("doc incompleta", _mut_spec_incomplete,
         [(["--feature", "F-001", "--stage", "spec"], 1)]),
        ("inventário adiantado", _mut_inventory_ahead,
         [(["--inventory"], 1)]),
        ("conclusão sem evidência", _mut_conclusion_without_evidence,
         [(["--stage", "audit", "--feature", "F-001"], 1), (["--all"], 1)]),
        ("hash divergente", _mut_hash_divergent,
         [(["--feature", "F-001", "--stage", "evidence"], 1)]),
        ("build não executado", _mut_build_absent,
         [(["--feature", "F-001", "--stage", "code"], 1)]),
        ("teste não executado", _mut_test_absent,
         [(["--feature", "F-001", "--stage", "test"], 1)]),
        ("token divergente", _mut_token_mismatch,
         [(["--feature", "F-001", "--stage", "audit"], 1)]),
        ("build stale", _mut_build_stale,
         [(["--feature", "F-001", "--stage", "code"], 1)]),
        ("build falho (exit!=0)", _mut_build_failed,
         [(["--feature", "F-001", "--stage", "code"], 1)]),
        ("test stale", _mut_test_stale,
         [(["--feature", "F-001", "--stage", "test"], 1)]),
        ("feature sem teste (F-007)", None,
         [(["--feature", "F-007", "--run-test"], 3)]),
        # Regressão do contrato AGENTS §10.2: inventário coerente (declarado ==
        # comprovado) com etapa vermelha ⇒ --inventory = 0 e --all = 1.
        ("inventário coerente c/ etapa vermelha", _mut_inventory_coherent_red_stage,
         [(["--inventory"], 0), (["--all"], 1)]),
    ]

    rows = []
    ok_all = True
    for idx, (title, mutate, checks) in enumerate(scenarios):
        dst = os.path.join(tmp, f"case{idx:02d}")
        shutil.copytree(base, dst)
        if mutate:
            mutate(dst)
        env = dict(os.environ)
        env["ARTPLUS_GATE_REPO"] = dst
        env["PYTHONIOENCODING"] = "utf-8"
        results = []
        for args, expected in checks:
            try:
                p = subprocess.run([sys.executable, script] + args, cwd=dst, env=env,
                                   stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                   timeout=180)
                got = p.returncode
                out = (p.stdout or b"").decode("utf-8", "replace")
            except subprocess.TimeoutExpired:
                got, out = 124, "timeout"
            results.append((args, expected, got, out))
        ok = all(r[1] == r[2] for r in results)
        ok_all = ok_all and ok
        detail = "; ".join(f"{' '.join(r[0])} => {r[2]} (esperado {r[1]})"
                           for r in results)
        rows.append((title, "PASS" if ok else "FAIL", detail, results))

    print("=" * 100)
    print("gate.py --selftest — cenários em repositórios temporários")
    print("=" * 100)
    print(f"{'#':>2}  {'CENÁRIO':<34} {'RESULTADO':<9} DETALHE")
    print("-" * 100)
    for i, (title, verdict, detail, _) in enumerate(rows, 1):
        print(f"{i:>2}  {title:<34} {verdict:<9} {detail}")
    print("-" * 100)
    passed = sum(1 for r in rows if r[1] == "PASS")
    print(f"TOTAL: {passed}/{len(rows)} PASS")
    if not ok_all:
        print("\n--- saída dos cenários que falharam ---")
        for title, verdict, _, results in rows:
            if verdict == "PASS":
                continue
            for args, expected, got, out in results:
                if expected == got:
                    continue
                print(f"\n### {title} :: {' '.join(args)} (esperado {expected}, obtido {got})")
                print(out[-2500:])
    if os.environ.get("ARTPLUS_KEEP_SELFTEST"):
        print(f"\nfixtures preservadas em: {tmp}")
    else:
        shutil.rmtree(tmp, ignore_errors=True)
    return 0 if ok_all else 1


# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--halt", action="store_true")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--feature")
    ap.add_argument("--stage", choices=["evidence", "spec", "adr", "code", "test", "audit"])
    ap.add_argument("--inventory", action="store_true")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--build", action="store_true", help="executa build real em build_audit")
    ap.add_argument("--run-test", action="store_true", help="executa a suíte CTest da feature")
    ap.add_argument("--emit-token", action="store_true", help="imprime o token de auditoria")
    ap.add_argument("--selftest", action="store_true", help="testa o próprio gate")
    args = ap.parse_args()

    # Infraestrutura de gate não é avanço de funcionalidade: roda mesmo sob HALT.
    if args.selftest:
        return run_selftest()
    if args.build:
        return cmd_build()
    if args.run_test:
        return cmd_run_test(args.feature)
    if args.emit_token:
        return cmd_emit_token(args.feature)

    if args.halt:
        if check_halt():
            print("HALT ATIVO — nenhuma funcionalidade pode avançar.")
            return 2
        print("HALT inativo.")
        return 0

    halt = check_halt()
    if halt and not args.inventory:
        print("HALT ATIVO — gate bloqueia avanço de funcionalidade (docs/agents/HALT.md).")
        if args.stage:
            print("(verificação de etapa permitida; o avanço continua bloqueado)")

    version_ok, version_details = check_version()
    if not args.json:
        print("=" * 72)
        print("gate.py — verificação factual do pipeline ArtPlus")
        print(f"versão canônica: {CANON}")
        print("=" * 72)
        print(f"[GATE 0 versão] {'ok' if version_ok else 'REPROVADO'}")
        for d in version_details:
            print(f"    - {d}")

    inv = parse_inventory() if (args.all or args.inventory) else {}
    features = ([args.feature] if args.feature else
                (sorted(inv) if (args.all or args.inventory) else []))

    results = {}
    status = 0 if version_ok else 1
    # --inventory mede apenas coerência INVENTORY x estado comprovado. Etapa
    # vermelha (build/teste/evidência) reprova --all, mas não pode reprovar o
    # inventário quando o estado declarado não supera o comprovado.
    inv_status = 0 if version_ok else 1
    for fid in features:
        res = run_feature(fid)
        derived, inv_ok = print_feature(fid, res, inv.get(fid))
        results[fid] = {"derived": derived,
                        "claimed": inv.get(fid),
                        "gates": {k: res[k] for k in ("evidence", "spec", "adr", "code", "test", "audit")}}
        if any(res[k] for k in ("evidence", "spec", "adr", "code", "test", "audit")):
            status = max(status, 1)
        if not inv_ok:
            status = max(status, 1)
            inv_status = max(inv_status, 1)

    if args.json:
        print(json.dumps({"version_ok": version_ok, "version_details": version_details,
                          "features": results}, ensure_ascii=False, indent=2))

    if args.stage:
        if not args.feature:
            print("erro de uso: --stage exige --feature F-###")
            return 3
        stage_ok = not results.get(args.feature, {}).get("gates", {}).get(args.stage, ["x"])
        if halt:
            print("\nHALT ATIVO: verificação registrada; avanço de funcionalidade bloqueado.")
        return 0 if (stage_ok and version_ok) else 1

    if halt and not args.inventory:
        print("\nHALT ATIVO: avanço de funcionalidade bloqueado.")
        return 2
    if halt:
        print("\nHALT ATIVO: inspeção de inventário permitida; avanço bloqueado.")
    return inv_status if args.inventory else status


if __name__ == "__main__":
    try:
        sys.exit(main())
    except RuntimeError as e:
        print(f"erro: {e}")
        sys.exit(3)
