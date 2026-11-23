#!/usr/bin/env python3
"""Deterministic overnight extraction for ArtPlus modules.

No LLM in the loop. For each queued module:
  1. SHA-256 + PE sections/entropy
  2. DIE JSON + strings sample
  3. triage markdown
  4. dossier.py
  5. optional Ghidra import/export (--ghidra), then dossier again

Examples:
  python scripts/auto_extract.py --limit 8 --ghidra --hours 8
  python scripts/auto_extract.py --limit 3 --no-ghidra
"""
from __future__ import annotations

import argparse
import hashlib
import json
import math
import os
import re
import shutil
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path

try:
    out = getattr(sys.stdout, "reconfigure", None)
    if callable(out):
        out(encoding="utf-8", errors="replace")
except Exception:
    pass

TARGET = Path(r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows")
GHIDRA = Path(r"H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat")
PROJECTS = Path(r"H:\Desktop\ArtPlus\tools\ghidra_projects")
SCRIPTS = Path(r"H:\Desktop\ArtPlus\scripts\ghidra_scripts")
JAVA_HOME = r"C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot"
INTEREST = ("http", ".dll", ".pdf", "error", "fail", "menu", "marks", "layer",
            "color", "trap", "pdf+", "xmp", "esko", "document", "separ")


def entropy(data: bytes) -> float:
    if not data:
        return 0.0
    counts = [0] * 256
    for byte in data:
        counts[byte] += 1
    total = len(data)
    return -sum((count / total) * math.log2(count / total) for count in counts if count)


def pe_info(path: Path):
    data = path.read_bytes()
    info = {"machine": "", "sections": []}
    if data[:2] != b"MZ":
        return info
    pe = int.from_bytes(data[0x3C:0x40], "little")
    if data[pe:pe + 4] != b"PE\0\0":
        return info
    machine, sections, _, _, _, opt_size, _ = __import__("struct").unpack_from("<HHIIIHH", data, pe + 4)
    info["machine"] = {0x14c: "x86", 0x8664: "x64", 0xAA64: "arm64"}.get(machine, hex(machine))
    offset = pe + 24 + opt_size
    for index in range(sections):
        base = offset + index * 40
        name = data[base:base + 8].rstrip(b"\0").decode("latin1", "replace")
        vsize, va, rawsize, rawptr = __import__("struct").unpack_from("<IIII", data, base + 8)
        raw = data[rawptr:rawptr + rawsize]
        info["sections"].append({
            "name": name,
            "va": f"0x{va:X}",
            "vsize": vsize,
            "rawsize": rawsize,
            "entropy": round(entropy(raw), 3),
        })
    return info


def run_capture(command, timeout=300):
    try:
        result = subprocess.run(command, capture_output=True, timeout=timeout,
                                stdin=subprocess.DEVNULL)
        return result.returncode, result.stdout, result.stderr
    except (OSError, subprocess.TimeoutExpired) as exc:
        return 1, b"", str(exc).encode()


def die_summary(raw: bytes):
    """Flatten diec -j output into short labels.

    diec emits detects[] entries carrying `filetype` (PE64, ELF, ...) plus
    values[] entries whose human-readable text lives in `string`. Older
    payloads used `name`/`type` only, so keep those as fallbacks.
    """
    try:
        data = json.loads(raw.decode("utf-8", "replace"))
    except json.JSONDecodeError:
        return []
    if isinstance(data, list):
        data = {"detects": data}
    names = []
    for item in data.get("detects", []):
        if not isinstance(item, dict):
            continue
        label = (item.get("name") or item.get("filetype")
                 or item.get("type") or "detect")
        parts = []
        for value in item.get("values", []) or []:
            if isinstance(value, dict):
                text = value.get("string") or value.get("name") or ""
            else:
                text = str(value)
            text = " ".join(str(text).split())
            if text:
                parts.append(text[:120])
        names.append(f"{label}: {'; '.join(parts[:4])}" if parts else str(label))
    return names[:8]


def triage(root: Path, module: str, kind: str) -> dict:
    path = TARGET / module
    row = {"module": module, "ok": False, "sha256": "", "size": 0, "note": ""}
    if not path.is_file():
        row["note"] = "arquivo ausente no alvo v24"
        return row
    data = path.read_bytes()
    row.update({
        "sha256": hashlib.sha256(data).hexdigest(),
        "size": len(data),
        "ok": True,
    })
    info = pe_info(path)
    sources = root / "rag" / "sources"
    sources.mkdir(parents=True, exist_ok=True)
    stem = Path(module).stem

    code, out, err = run_capture(["diec", "-j", str(path)])
    die_names = []
    if out:
        (sources / f"{stem}.die.json").write_bytes(out)
        die_names = die_summary(out)

    code, out, err = run_capture(["strings64", "-n", "8", str(path)], timeout=600)
    text = out.decode("utf-8", "replace") if out else ""
    lines = text.splitlines()
    interesting = [line.strip() for line in lines if any(key in line.lower() for key in INTEREST)]
    (sources / f"{stem}.strings.txt").write_text("\n".join(lines[:200000]), encoding="utf-8")

    report_dir = root / "docs" / "reverse-engineering"
    report_dir.mkdir(parents=True, exist_ok=True)
    report = report_dir / f"{stem}_AUTO_TRIAGE.md"
    body = [
        f"# {module} — triagem automatica",
        "",
        f"- Gerado: {datetime.now().strftime('%Y-%m-%d %H:%M')}",
        f"- Caminho: `{path}`",
        f"- Tamanho: {len(data)} bytes",
        f"- SHA-256: `{row['sha256']}`",
        f"- Arquitetura: {info['machine'] or 'desconhecida'}",
        f"- DIE: {'; '.join(die_names) if die_names else 'sem deteccao'}",
        f"- Strings: {len(lines)} capturadas; amostra em `rag/sources/{stem}.strings.txt`",
        "",
        "## Secoes",
        "",
        "| Secao | VA | VSize | RawSize | Entropia |",
        "|---|---|---|---|---|",
    ]
    for section in info["sections"]:
        body.append(f"| {section['name']} | {section['va']} | {section['vsize']} | "
                    f"{section['rawsize']} | {section['entropy']} |")
    body += ["", "## Strings de interesse (amostra)", ""]
    for line in interesting[:120]:
        body.append(f"- `{line[:220]}`")
    body += ["", "## Lacunas", "",
             "- funcoes/xrefs: aguardando export do Ghidra", ""]
    report.write_text("\n".join(body), encoding="utf-8")

    subprocess.run([sys.executable, str(root / "scripts" / "dossier.py"),
                    "--module", module], cwd=root, check=False,
                   stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL)
    row["note"] = f"triage={report.relative_to(root).as_posix()}"
    return row


def run_process(command, log_path: Path, timeout_seconds: int, env=None):
    log_path.parent.mkdir(parents=True, exist_ok=True)
    with log_path.open("wb") as log:
        process = subprocess.Popen(command, stdin=subprocess.DEVNULL, stdout=log,
                                   stderr=subprocess.STDOUT, env=env,
                                   creationflags=getattr(subprocess, "CREATE_NO_WINDOW", 0))
        try:
            return process.wait(timeout=timeout_seconds), False
        except subprocess.TimeoutExpired:
            subprocess.run(["taskkill", "/PID", str(process.pid), "/T", "/F"],
                           capture_output=True, check=False)
            return -1, True


def project_for(module: str) -> str:
    """Nome de projeto Ghidra isolado por modulo."""
    stem = re.sub(r'[<>:"/\\|?*]', "_", Path(module).stem)
    stem = re.sub(r"\s+", "_", stem).strip("._")
    return f"ArtProPlus_{stem}"[:80]


def remove_project(project: str) -> None:
    for suffix in (".rep", ".gpr", ".lock", ".lock~"):
        target = PROJECTS / f"{project}{suffix}"
        try:
            if target.is_dir():
                shutil.rmtree(target, ignore_errors=True)
            elif target.exists():
                target.unlink()
        except OSError:
            pass


def refresh_dossier(root: Path, module: str) -> None:
    try:
        subprocess.run([sys.executable, str(root / "scripts" / "dossier.py"),
                        "--module", module], cwd=root, check=False, timeout=300,
                       stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL,
                       stderr=subprocess.DEVNULL)
    except (OSError, subprocess.TimeoutExpired):
        pass


def refresh_status(root: Path) -> None:
    """Mantem logs/auto/status.json e docs/status/dashboard.html atualizados."""
    try:
        subprocess.run([sys.executable, str(root / "scripts" / "status.py"),
                        "--json", "--html"], cwd=root, check=False, timeout=180,
                       stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL,
                       stderr=subprocess.DEVNULL)
    except (OSError, subprocess.TimeoutExpired):
        pass


def ghidra_phase(root: Path, module: str, minutes: int) -> str:
    """Importa/exporta um modulo no Ghidra usando um projeto proprio.

    Cada modulo vive em `ArtProPlus_<stem>`; um timeout, lock orfao ou .rep
    corrompido afeta apenas aquele modulo.
    """
    base = root / "rag" / "ghidra" / "exports"
    stem = Path(module).stem
    if base.is_dir() and any(path.is_dir() and path.name.lower() == module.lower() for path in base.iterdir()):
        return "export existente"
    path = TARGET / module
    if not path.is_file():
        return "arquivo ausente"
    if path.stat().st_size > 12 * 1024 * 1024:
        return "maior que 12 MB; Ghidra adiado"

    env = os.environ.copy()
    env["JAVA_HOME"] = JAVA_HOME
    project = project_for(module)

    if (PROJECTS / f"{project}.rep").exists():
        note = run_export(root, module, project, env)
        if note == "ok":
            refresh_dossier(root, module)
            return "ghidra ok (retomado)"
        remove_project(project)
        log_note = root / "logs" / "auto" / f"ghidra-{stem}.log"
        with log_note.open("a", encoding="utf-8") as handle:
            handle.write(f"\n[auto_extract] retomada falhou ({note}); reimportando\n")

    note = run_import(root, module, project, env, minutes)
    if note != "ok":
        return note
    note = run_export(root, module, project, env)
    if note != "ok":
        return note
    refresh_dossier(root, module)
    return "ghidra ok"


def run_import(root: Path, module: str, project: str, env, minutes: int) -> str:
    log = root / "logs" / "auto" / f"ghidra-{Path(module).stem}.log"
    command = ["cmd", "/c", str(GHIDRA), str(PROJECTS), project,
               "-import", str(TARGET / module), "-overwrite"]
    code, timed_out = run_process(command, log, minutes * 60, env)
    if timed_out:
        remove_project(project)
        return f"timeout no import ({minutes} min)"
    if code != 0:
        remove_project(project)
        return f"import falhou (exit {code})"
    return "ok"


def run_export(root: Path, module: str, project: str, env) -> str:
    log = root / "logs" / "auto" / f"ghidra-{Path(module).stem}-export.log"
    command = ["cmd", "/c", str(GHIDRA), str(PROJECTS), project,
               "-process", module, "-noanalysis",
               "-scriptPath", str(SCRIPTS), "-postScript", "ExportFunctions.java"]
    code, timed_out = run_process(command, log, 20 * 60, env)
    if timed_out:
        return "timeout no export"
    if code != 0:
        return f"export falhou (exit {code})"
    return "ok"


def main() -> int:
    parser = argparse.ArgumentParser(description="Deterministic overnight extraction")
    parser.add_argument("--root", default=str(Path(__file__).resolve().parents[1]))
    parser.add_argument("--limit", type=int, default=8)
    parser.add_argument("--hours", type=float, default=8)
    parser.add_argument("--ghidra", action="store_true")
    parser.add_argument("--no-ghidra", action="store_true")
    parser.add_argument("--ghidra-minutes", type=int, default=45)
    parser.add_argument("--include-done", action="store_true")
    parser.add_argument("--only", default="", metavar="MODULE",
                        help="triage/analyse just this module instead of the queue")
    args = parser.parse_args()
    root = Path(args.root).resolve()
    report = root / "docs" / "phases" / f"OVERNIGHT-{datetime.now().strftime('%Y%m%d')}.md"
    report.parent.mkdir(parents=True, exist_ok=True)
    log_dir = root / "logs" / "auto"
    log_dir.mkdir(parents=True, exist_ok=True)

    if args.only:
        modules = [args.only.strip()]
    else:
        queue_cmd = [sys.executable, str(root / "scripts" / "auto_queue.py"),
                     "--limit", str(args.limit)]
        if args.include_done:
            queue_cmd.append("--include-done")
        queue = subprocess.run(queue_cmd, capture_output=True, text=True,
                               stdin=subprocess.DEVNULL)
        modules = [line.strip() for line in queue.stdout.splitlines() if line.strip()]
    if not modules:
        print("fila vazia")
        return 1

    deadline = None if args.hours <= 0 else time.time() + args.hours * 3600
    report.write_text("\n".join([
        f"# Extracao continua - {datetime.now().strftime('%Y-%m-%d')}",
        "",
        f"- Inicio: {datetime.now().strftime('%H:%M')}",
        f"- Modulos: {', '.join(modules)}",
        f"- Total na fila: {len(modules)}",
        f"- Ghidra: {'sim' if args.ghidra and not args.no_ghidra else 'nao'}",
        f"- Projeto Ghidra: ArtProPlus_<modulo> (um por modulo)",
        f"- Orcamento: {'sem limite' if deadline is None else f'{args.hours:g} h'}",
        "",
        "| Modulo | SHA-256 | Ghidra | Dossie |",
        "|---|---|---|---|",
    ]) + "\n", encoding="utf-8")

    for index, module in enumerate(modules, start=1):
        if deadline is not None and time.time() >= deadline:
            print("orcamento de tempo atingido", flush=True)
            break
        print(f"[{index}/{len(modules)}] {module}", flush=True)
        ghidra_note = "-"
        row = {"sha256": "", "ok": False, "note": ""}
        try:
            row = triage(root, module, "dll")
            if args.ghidra and not args.no_ghidra and row["ok"]:
                ghidra_note = ghidra_phase(root, module, args.ghidra_minutes)
        except Exception as exc:  # um modulo quebrado nao derruba a fila
            ghidra_note = f"erro: {type(exc).__name__}"
            print(f"  erro em {module}: {exc}", flush=True)
            with (log_dir / "extract-errors.log").open("a", encoding="utf-8") as handle:
                handle.write(f"{datetime.now().isoformat(timespec='seconds')} "
                             f"{module}: {type(exc).__name__}: {exc}\n")
        dossier = root / "dossiers" / Path(module).stem / "DOSSIER.md"
        dossier_cell = f"[{dossier.relative_to(root).as_posix()}]({(dossier.relative_to(root)).as_posix()})" if dossier.is_file() else "-"
        line = f"| {module} | `{row['sha256'][:16] or '-'}` | {ghidra_note} | {dossier_cell} |"
        with report.open("a", encoding="utf-8") as handle:
            handle.write(line + "\n")
        print(f"  {line}", flush=True)
        refresh_status(root)

    with report.open("a", encoding="utf-8") as handle:
        handle.write(f"\nFim: {datetime.now().strftime('%Y-%m-%d %H:%M')}\n")
    print(f"relatorio: {report}", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
