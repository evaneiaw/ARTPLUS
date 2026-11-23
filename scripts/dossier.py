#!/usr/bin/env python3
"""Build one consolidated dossier per ArtPro+ module.

A dossier is a single readable DOSSIER.md plus a manifest.json, copies of the
raw evidence and the specs/ADRs/audits that belong to the module. It also
maintains dossiers/INDEX.md and dossiers/knowledge.jsonl.

No external dependencies.

Examples:
  python scripts/dossier.py --module Document.dll
  python scripts/dossier.py --all
  python scripts/dossier.py --list
  python scripts/dossier.py --all --zip
"""
from __future__ import annotations

import argparse
import csv
import json
import re
import shutil
import sys
import zipfile
from datetime import datetime, timezone
from pathlib import Path

try:
    reconfigure = getattr(sys.stdout, "reconfigure", None)
    if callable(reconfigure):
        reconfigure(encoding="utf-8", errors="replace")
except Exception:
    pass

MODULE_RE = re.compile(r"([A-Za-z0-9_+.\-]+\.(?:dll|exe))", re.IGNORECASE)
FEATURE_RE = re.compile(r"F-\d{3}[a-z]?")
ARTIFACT_REVERSE = re.compile(r"(?i)(document|pdf|marks|color|trapping|step|impose|packaging)")


def read_text(path: Path) -> str:
    try:
        return path.read_text(encoding="utf-8-sig", errors="replace")
    except OSError:
        return ""


def split_frontmatter(text: str):
    if not text.startswith("---"):
        return "", text
    end = text.find("\n---", 3)
    if end < 0:
        return "", text
    return text[3:end], text[end + 4:]


def fm_value(frontmatter: str, key: str) -> str:
    match = re.search(rf"^{re.escape(key)}:\s*(.+?)\s*$", frontmatter, re.MULTILINE)
    return match.group(1).strip().strip('"').strip("'") if match else ""


def module_name(value: str) -> str:
    return Path(value.strip().strip('"').strip("'")).name


def module_stem(name: str) -> str:
    return Path(name).stem


def matches(text: str, stem: str) -> bool:
    if not stem:
        return False
    pattern = rf"(?i)(?<![a-z0-9]){re.escape(stem)}(?=$|[^a-z0-9])"
    return re.search(pattern, text) is not None


def rel(root: Path, path: Path) -> str:
    try:
        return path.resolve().relative_to(root.resolve()).as_posix()
    except ValueError:
        return str(path)


def _clean_state(value: str) -> str:
    """'**auditado**' -> 'auditado'; '**bloqueado** (BLO-005)' -> 'bloqueado'."""
    state = value.replace("**", "").replace("`", "").strip()
    state = re.sub(r"\s*\(.*?\)\s*", " ", state).strip()
    return state


def load_inventory(root: Path):
    """Estado comprovado por módulo, lido da fonte única
    `docs/reverse-engineering/INVENTORY.md` (tabela
    `| # | Feature | Módulo/Binário | Estado comprovado | ... |`).

    Retorna {modulo.lower(): {"name", "status", "features": {F-###: estado}}}.
    `status` é o estado das features do módulo; quando divergem, vem discriminado
    por feature (ex.: "auditado (F-001, F-003); triado (F-002)"). Módulo ausente do
    inventário não entra no dicionário — o chamador mostra `—`.
    """
    path = root / "docs" / "reverse-engineering" / "INVENTORY.md"
    rows = {}
    if not path.is_file():
        return rows
    for line in read_text(path).splitlines():
        stripped = line.strip()
        if not stripped.startswith("|"):
            continue
        cells = [cell.strip() for cell in stripped.strip("|").split("|")]
        if len(cells) < 4:
            continue
        feature = FEATURE_RE.search(cells[1])
        if not feature:
            continue
        module_cell = cells[2].replace("`", "").replace("**", "").strip()
        module_match = MODULE_RE.search(module_cell)
        module = module_match.group(1) if module_match else module_cell
        if not module:
            continue
        row = rows.setdefault(module.lower(), {
            "name": module, "kind": "", "sha256": "", "status": "", "features": {},
        })
        row["features"][feature.group(0)] = _clean_state(cells[3])
    for row in rows.values():
        grouped = {}
        for feature_id, state in sorted(row["features"].items()):
            grouped.setdefault(state, []).append(feature_id)
        if len(grouped) == 1:
            row["status"] = next(iter(grouped))
        else:
            row["status"] = "; ".join(
                f"{state} ({', '.join(ids)})" for state, ids in grouped.items())
    return rows


def load_manifests(root: Path):
    manifests = []
    base = root / "rag" / "evidence"
    if not base.is_dir():
        return manifests
    for path in base.rglob("manifest.json"):
        try:
            data = json.loads(read_text(path))
        except (json.JSONDecodeError, OSError):
            continue
        data["_path"] = rel(root, path)
        data["_dir"] = path.parent
        manifests.append(data)
    return manifests


def find_features(root: Path, module: str, stem: str, manifests):
    features = {}
    for path in sorted((root / "docs" / "features").glob("*.md")):
        text = read_text(path)
        frontmatter, body = split_frontmatter(text)
        feature_id = fm_value(frontmatter, "id") or (FEATURE_RE.search(path.name) or [""])[0]
        modulo = fm_value(frontmatter, "modulo")
        if not feature_id:
            continue
        if matches(modulo, stem) or matches(body[:4000], stem):
            features[feature_id] = {
                "id": feature_id,
                "ui": fm_value(frontmatter, "ui"),
                "status": fm_value(frontmatter, "status"),
                "confidence": fm_value(frontmatter, "confianca"),
                "path": rel(root, path),
            }
    for manifest in manifests:
        binary = module_name(str(manifest.get("binario", "")))
        if binary.lower() != module.lower() and not matches(binary, stem):
            continue
        feature_id = str(manifest.get("id", "")).strip()
        if not feature_id:
            continue
        entry = features.setdefault(feature_id, {
            "id": feature_id, "ui": "", "status": "", "confidence": "", "path": "",
        })
        entry.setdefault("manifest", manifest.get("_path", ""))
    for path in sorted((root / "docs" / "audit").glob("*.md")):
        found = FEATURE_RE.findall(path.name)
        for feature_id in found:
            features.setdefault(feature_id, {
                "id": feature_id, "ui": "", "status": "audited",
                "confidence": "", "path": "",
            })
    return features


def find_documents(root: Path, stem: str, feature_ids: set[str]):
    documents = []

    def add(path: Path):
        if path.is_file() and path not in [item[0] for item in documents]:
            documents.append((path, rel(root, path)))

    for path in sorted((root / "docs" / "reverse-engineering").rglob("*.md")):
        if matches(path.name, stem) or matches(read_text(path)[:5000], stem):
            add(path)
    for path in sorted((root / "docs" / "behavior").glob("*.md")):
        text = read_text(path)
        if matches(text[:4000], stem) or any(fid in text for fid in feature_ids):
            add(path)
    for path in sorted((root / "docs" / "decisions").glob("*.md")):
        text = read_text(path)
        if matches(text[:4000], stem) or any(fid in text for fid in feature_ids):
            add(path)
    for path in sorted((root / "docs" / "audit").glob("*.md")):
        if any(fid in path.name for fid in feature_ids):
            add(path)
    for path in sorted((root / "docs" / "features").glob("*.md")):
        if any(fid in path.name for fid in feature_ids):
            add(path)
    return documents


AUDIT_DATE_RE = re.compile(r"(\d{8})([a-z])?")


def find_current_audits(root: Path):
    """Laudo vigente por feature, lido de `docs/audit/`.

    Regra: o laudo de maior data no nome (`AAAAMMDD`); sem data no nome vale menos
    que qualquer laudo datado. Desempate: sufixo alfabético (`…20261121b` vence
    `…20261121`) e, por último, o mtime. Assim laudos superados
    (`F-003-audit.md`, `F-005-audit-20261121.md`, `F-006-audit.md` quando houver
    versão datada posterior) não definem o veredito.

    Retorna {feature_id: {"path", "verdict", "rank"}}.
    """
    best = {}
    audit_dir = root / "docs" / "audit"
    if not audit_dir.is_dir():
        return best
    for path in sorted(audit_dir.glob("*.md")):
        feature_ids = set(FEATURE_RE.findall(path.name))
        if len(feature_ids) != 1:
            continue  # laudo agregado ou ambíguo não define veredito de feature
        feature_id = feature_ids.pop()
        match = AUDIT_DATE_RE.search(path.stem)
        rank = (
            match.group(1) if match else "",          # data: "" perde para qualquer AAAAMMDD
            (match.group(2) or "") if match else "",  # sufixo: "b" vence ""
        )
        try:
            mtime = path.stat().st_mtime
        except OSError:
            mtime = 0.0
        rank = rank + (mtime,)
        current = best.get(feature_id)
        if current is not None and rank <= current["rank"]:
            continue
        verdict_match = re.search(r"(?im)^Veredito:\s*(.+)$", read_text(path))
        best[feature_id] = {
            "path": rel(root, path),
            "verdict": (verdict_match.group(1).strip().replace("**", "").strip()
                        if verdict_match else ""),
            "rank": rank,
        }
    return best


def summarize_verdicts(verdicts: dict):
    """Agrega {feature: {verdict, ...}} num texto único, agrupado por veredito."""
    if not verdicts:
        return ""
    grouped = {}
    for feature_id in sorted(verdicts):
        grouped.setdefault(verdicts[feature_id]["verdict"] or "—", []).append(feature_id)
    if len(grouped) == 1:
        return next(iter(grouped))
    return "; ".join(f"{verdict} ({', '.join(ids)})" for verdict, ids in grouped.items())


def find_exports(root: Path, module: str, stem: str):
    found = []
    base = root / "rag" / "ghidra" / "exports"
    if base.is_dir():
        for path in sorted(base.iterdir()):
            if path.is_dir() and (path.name.lower() == module.lower()
                                  or matches(path.name, stem)):
                found.append(path)
    return found


def find_ghidra_notes(root: Path, stem: str):
    base = root / "rag" / "ghidra"
    if not base.is_dir():
        return []
    return [path for path in sorted(base.iterdir())
            if path.is_dir() and path.name not in {"exports"} and matches(path.name, stem)]


def find_sources(root: Path, stem: str):
    base = root / "rag" / "sources"
    if not base.is_dir():
        return []
    return [path for path in sorted(base.rglob("*"))
            if path.is_file() and matches(path.name, stem)]


def copy_tree(source: Path, destination: Path):
    for path in sorted(source.rglob("*")):
        if path.is_file():
            target = destination / path.relative_to(source)
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(path, target)


def scan_code(root: Path, feature_ids: set[str]):
    code, tests = [], []
    if not feature_ids:
        return code, tests
    for base, bucket in ((root / "src", code), (root / "tests", tests)):
        if not base.is_dir():
            continue
        for path in sorted(base.rglob("*")):
            if path.suffix.lower() not in {".h", ".hpp", ".hxx", ".cpp", ".cc", ".cxx"}:
                continue
            if path.stat().st_size > 2 * 1024 * 1024:
                continue
            text = read_text(path)
            if any(fid in text for fid in feature_ids):
                bucket.append(rel(root, path))
    return code, tests


def csv_info(path: Path):
    if not path.is_file():
        return {"exists": False, "rows": 0, "header": [], "sample": []}
    lines = read_text(path).splitlines()
    if not lines:
        return {"exists": True, "rows": 0, "header": [], "sample": []}
    header = next(csv.reader([lines[0]]))
    rows = []
    for line in lines[1:41]:
        try:
            rows.append(next(csv.reader([line])))
        except (csv.Error, StopIteration):
            continue
    return {"exists": True, "rows": max(0, len(lines) - 1), "header": header, "sample": rows}


def build_dossier(root: Path, out_root: Path, module: str, manifests, inventory) -> dict:
    stem = module_stem(module)
    manifests = [item for item in manifests
                 if module_name(str(item.get("binario", ""))).lower() == module.lower()
                 or matches(module_name(str(item.get("binario", ""))), stem)]
    features = find_features(root, module, stem, manifests)
    feature_ids = set(features)
    documents = find_documents(root, stem, feature_ids)
    exports = find_exports(root, module, stem)
    notes = find_ghidra_notes(root, stem)
    sources = find_sources(root, stem)
    code, tests = scan_code(root, feature_ids)

    identity = inventory.get(module.lower(), {})
    feature_states = identity.get("features", {})
    binary = next((item.get("binario") for item in manifests if item.get("binario")), "")
    if not binary:
        candidate = Path(r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows") / module
        if candidate.is_file():
            binary = str(candidate)
    sha256 = next((item.get("sha256") for item in manifests if item.get("sha256")), "") or identity.get("sha256", "")

    target = out_root / stem
    if target.exists():
        shutil.rmtree(target)
    target.mkdir(parents=True, exist_ok=True)

    copied = []

    def copy_doc(path: Path):
        destination = target / "artifacts" / rel(root, path)
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(path, destination)
        copied.append(rel(root, destination))

    for path, _ in documents:
        copy_doc(path)

    for feature_id, entry in features.items():
        evidence_dir = root / "rag" / "evidence" / feature_id
        if evidence_dir.is_dir():
            copy_tree(evidence_dir, target / "evidence" / feature_id)
            for path in evidence_dir.rglob("*"):
                if path.is_file():
                    copied.append(rel(root, target / "evidence" / feature_id / path.relative_to(evidence_dir)))
        manifest = entry.get("manifest")
        if manifest:
            path = root / manifest
            if path.is_file():
                destination = target / "evidence" / feature_id / "manifest.json"
                destination.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(path, destination)
                copied.append(rel(root, destination))

    for export_dir in exports:
        copy_tree(export_dir, target / "evidence" / "ghidra_exports" / export_dir.name)
    for note_dir in notes:
        copy_tree(note_dir, target / "evidence" / "ghidra_notes" / note_dir.name)
    for source in sources:
        destination = target / "evidence" / "sources" / source.name
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, destination)

    functions_jsonl = root / "rag" / "index" / "functions.jsonl"
    function_rows = []
    if functions_jsonl.is_file():
        for line in read_text(functions_jsonl).splitlines():
            line = line.strip()
            if not line:
                continue
            try:
                record = json.loads(line)
            except json.JSONDecodeError:
                continue
            if matches(record.get("modulo", ""), stem):
                function_rows.append(record)

    export_csv = {}
    if exports:
        base = exports[0]
        export_csv = {
            "functions": csv_info(base / "functions.csv"),
            "symbols": csv_info(base / "symbols.csv"),
            "strings": csv_info(base / "strings.csv"),
            "xrefs": csv_info(base / "xrefs.csv"),
        }

    gaps = []
    if not feature_ids:
        gaps.append("sem spec F-### associada")
    if not any(item.get("estatico") for item in manifests):
        gaps.append("sem evidência estática em manifest")
    if not any(item.get("comportamental") for item in manifests):
        gaps.append("sem captura comportamental em manifest")
    if not function_rows and not export_csv.get("functions", {}).get("exists"):
        gaps.append("sem funções exportadas")
    if not code:
        gaps.append("sem código mapeado para F-###")

    audit_docs = [(path, relative) for path, relative in documents
                  if "docs/audit/" in relative.replace("\\", "/")]
    current_audits = find_current_audits(root)
    verdicts = {feature_id: current_audits[feature_id]
                for feature_id in sorted(feature_ids) if feature_id in current_audits}
    # O veredito do módulo considera as features que o INVENTORY atribui a ele;
    # sem inventário para o módulo, cai para todas as features com laudo.
    owned = set(feature_states)
    verdict_scope = ({fid: item for fid, item in verdicts.items() if fid in owned}
                     if owned else verdicts)
    verdict = summarize_verdicts(verdict_scope)

    lines = [
        f"# Dossiê — {module}",
        "",
        f"Gerado em {datetime.now(timezone.utc).strftime('%Y-%m-%d %H:%M UTC')}.",
        "",
        "## 1. Identidade",
        "",
        "| Campo | Valor |",
        "|---|---|",
        f"| Módulo | `{module}` |",
        f"| Tipo | {identity.get('kind', '') or '—'} |",
        f"| Tamanho | {identity.get('size_bytes', '') or '—'} bytes |",
        f"| SHA-256 | `{sha256 or '—'}` |",
        f"| Estado no inventário | {identity.get('status', '') or '—'} |",
        f"| Binário | `{binary or '—'}` |",
        "",
        "## 2. Funcionalidades (F-###)",
        "",
    ]
    if features:
        lines += ["| ID | UI | Estado (INVENTORY) | Confiança | Laudo vigente | Veredito |",
                  "|---|---|---|---|---|---|"]
        for entry in sorted(features.values(), key=lambda item: item["id"]):
            feature_id = entry["id"]
            audit = verdicts.get(feature_id) or {}
            lines.append(
                f"| {feature_id} | {entry.get('ui') or '—'} | "
                f"{feature_states.get(feature_id) or entry.get('status') or '—'} | "
                f"{entry.get('confidence') or '—'} | "
                f"{audit.get('path') or '—'} | {audit.get('verdict') or '—'} |")
    else:
        lines.append("_Nenhuma spec F-### associada ainda._")

    lines += ["", "## 3. Evidência", ""]
    if manifests:
        for manifest in manifests:
            lines.append(f"- **{manifest.get('id', '?')}** — `{manifest.get('_path', '')}`")
            if manifest.get("estatico"):
                lines.append(f"  - estático: {', '.join(manifest['estatico'])}")
            if manifest.get("comportamental"):
                lines.append(f"  - comportamental: {', '.join(manifest['comportamental'])}")
            if manifest.get("bloqueios"):
                lines.append(f"  - bloqueios: {', '.join(manifest['bloqueios'])}")
    else:
        lines.append("_Nenhum `manifest.json` encontrado._")

    lines += ["", "## 4. Funções e estruturas", ""]
    if function_rows:
        lines.append(f"- `rag/index/functions.jsonl`: **{len(function_rows)}** registros")
        lines += ["", "| Endereço | Nome | Spec | Confiança |", "|---|---|---|---|"]
        for record in function_rows[:80]:
            lines.append(f"| `{record.get('endereco', '')}` | {record.get('nome', '')} | "
                         f"{record.get('spec', '')} | {record.get('confianca', '')} |")
    if export_csv.get("functions", {}).get("exists"):
        functions = export_csv["functions"]
        lines += ["", f"- Export Ghidra: **{functions['rows']}** funções; "
                      f"{export_csv.get('symbols', {}).get('rows', 0)} símbolos; "
                      f"{export_csv.get('strings', {}).get('rows', 0)} strings; "
                      f"{export_csv.get('xrefs', {}).get('rows', 0)} xrefs."]
        if functions["header"]:
            lines += ["", "| " + " | ".join(functions["header"]) + " |",
                      "|" + "---|" * len(functions["header"])]
            for row in functions["sample"][:40]:
                padded = row + [""] * (len(functions["header"]) - len(row))
                lines.append("| " + " | ".join(padded) + " |")
    if not function_rows and not export_csv.get("functions", {}).get("exists"):
        lines.append("_Nenhuma função exportada._")

    def embed(title: str, selector):
        lines.extend(["", f"## {title}", ""])
        selected = [(path, relative) for path, relative in documents if selector(relative)]
        if not selected:
            lines.append("_Não encontrado._")
            return
        for path, relative in selected:
            _, body = split_frontmatter(read_text(path))
            lines.extend([f"### `{relative}`", "", body.strip(), ""])

    embed("5. Comportamento observado", lambda value: "/behavior/" in value.replace("\\", "/"))
    embed("6. Especificações", lambda value: "/features/" in value.replace("\\", "/"))
    embed("7. Decisões de arquitetura", lambda value: "/decisions/" in value.replace("\\", "/"))

    lines += ["", "## 8. Código e testes", ""]
    if code:
        lines.append("**Código:**")
        lines += [f"- `{item}`" for item in code]
    else:
        lines.append("_Nenhum arquivo de `src/` cita as features deste módulo._")
    if tests:
        lines += ["", "**Testes:**"]
        lines += [f"- `{item}`" for item in tests]
    else:
        lines.append("_Nenhum teste cita as features deste módulo._")

    lines += ["", "## 9. Auditoria", ""]
    if audit_docs or verdict:
        if verdict:
            lines.append(f"**Veredito:** {verdict}")
        if verdicts:
            lines += ["", "Laudo vigente por feature (maior data no nome; desempate por sufixo/mtime):",
                      "", "| Feature | Laudo | Veredito |", "|---|---|---|"]
            for feature_id in sorted(verdicts):
                audit = verdicts[feature_id]
                lines.append(f"| {feature_id} | `{audit['path']}` | {audit['verdict'] or '—'} |")
        lines += ["", "Laudos embutidos abaixo incluem versões históricas (mantidas para "
                      "rastreabilidade; não definem o veredito acima).", ""]
        for path, relative in audit_docs:
            _, body = split_frontmatter(read_text(path))
            lines.extend([f"### `{relative}`", "", body.strip(), ""])
    else:
        lines.append("_Sem laudo de auditoria._")

    lines += ["", "## 10. Em aberto e bloqueios", ""]
    blockers = []
    for manifest in manifests:
        for blocker in manifest.get("bloqueios", []) or []:
            blockers.append(f"{manifest.get('id', '?')}: {blocker}")
    if gaps:
        lines += [f"- Lacuna: {gap}" for gap in gaps]
    if blockers:
        lines += [f"- Bloqueio: {blocker}" for blocker in blockers]
    if not gaps and not blockers:
        lines.append("_Nada registrado._")

    lines += ["", "## 11. Arquivos deste dossiê", ""]
    for item in sorted(set(copied)):
        lines.append(f"- `{item}`")
    lines += ["", f"Manifesto: `{rel(root, target)}/manifest.json`", ""]

    (target / "DOSSIER.md").write_text("\n".join(lines), encoding="utf-8")

    manifest_out = {
        "module": module,
        "stem": stem,
        "generated": datetime.now(timezone.utc).isoformat(),
        "identity": {
            "kind": identity.get("kind", ""),
            "size_bytes": identity.get("size_bytes", ""),
            "sha256": sha256,
            "status": identity.get("status", ""),
            "binary": binary,
        },
        "features": [
            dict(entry,
                 inventory_status=feature_states.get(entry["id"], ""),
                 audit_path=(verdicts.get(entry["id"]) or {}).get("path", ""),
                 audit_verdict=(verdicts.get(entry["id"]) or {}).get("verdict", ""))
            for entry in sorted(features.values(), key=lambda item: item["id"])
        ],
        "evidence": {
            "static": sorted({item for entry in manifests for item in entry.get("estatico", [])}),
            "behavioral": sorted({item for entry in manifests for item in entry.get("comportamental", [])}),
        },
        "documents": [relative for _, relative in documents],
        "exports": [rel(root, path) for path in exports],
        "function_count": (len(function_rows) if function_rows
                           else export_csv.get("functions", {}).get("rows", 0)),
        "code_files": code,
        "test_files": tests,
        "verdict": verdict,
        "verdicts": [
            {"feature": feature_id,
             "path": verdicts[feature_id]["path"],
             "verdict": verdicts[feature_id]["verdict"]}
            for feature_id in sorted(verdicts)
        ],
        "gaps": gaps,
        "blockers": blockers,
        "copied_files": sorted(set(copied)),
    }
    (target / "manifest.json").write_text(
        json.dumps(manifest_out, ensure_ascii=False, indent=2), encoding="utf-8")
    return manifest_out


def discover_modules(root: Path, manifests):
    names = set()
    exports = root / "rag" / "ghidra" / "exports"
    if exports.is_dir():
        names.update(path.name for path in exports.iterdir() if path.is_dir())
    for manifest in manifests:
        name = module_name(str(manifest.get("binario", "")))
        if name:
            names.add(name)
    reverse = root / "docs" / "reverse-engineering"
    if reverse.is_dir():
        for path in reverse.rglob("*.md"):
            names.update(MODULE_RE.findall(read_text(path)[:8000]))
    return sorted(names, key=str.lower)


def has_artifacts(root: Path, module: str, manifests, inventory) -> bool:
    stem = module_stem(module)
    exports = root / "rag" / "ghidra" / "exports"
    if exports.is_dir():
        for path in exports.iterdir():
            if path.is_dir() and (path.name.lower() == module.lower()
                                  or matches(path.name, stem)):
                return True
    for item in manifests:
        binary = module_name(str(item.get("binario", "")))
        if binary.lower() == module.lower() or matches(binary, stem):
            return True
    reverse = root / "docs" / "reverse-engineering"
    if reverse.is_dir():
        for path in reverse.rglob("*.md"):
            if matches(path.name, stem):
                return True
    row = inventory.get(module.lower())
    return bool(row and row.get("status") not in {"", "nao-tratado"})


def write_index(root: Path, out_root: Path):
    manifests = []
    for path in sorted(out_root.glob("*/manifest.json")):
        try:
            manifests.append(json.loads(read_text(path)))
        except json.JSONDecodeError:
            continue
    inventory = load_inventory(root)
    counts = {}
    for row in inventory.values():
        status = row.get("status", "nao-tratado")
        counts[status] = counts.get(status, 0) + 1
    lines = [
        "# Índice de dossiês",
        "",
        f"Gerado em {datetime.now(timezone.utc).strftime('%Y-%m-%d %H:%M UTC')}.",
        "",
        "## Fila do inventário",
        "",
        "| Estado | Módulos |",
        "|---|---|",
    ]
    for status, count in sorted(counts.items()):
        lines.append(f"| {status} | {count} |")
    lines += ["", f"Total: **{sum(counts.values())}** módulos.", "",
              "## Dossiês gerados", "",
              "| Módulo | Features | Funções | Estado | Veredito | Dossiê |",
              "|---|---|---|---|---|---|"]
    for item in sorted(manifests, key=lambda entry: entry.get("module", "").lower()):
        lines.append(f"| {item.get('module', '')} | {len(item.get('features', []))} | "
                     f"{item.get('function_count', 0)} | "
                     f"{item.get('identity', {}).get('status', '') or '—'} | "
                     f"{item.get('verdict', '') or '—'} | "
                     f"[{item.get('stem', '')}]({item.get('stem', '')}/DOSSIER.md) |")
    blockers = [(item.get("module", ""), blocker) for item in manifests for blocker in item.get("blockers", [])]
    lines += ["", "## Bloqueios", ""]
    if blockers:
        lines += [f"- **{module}**: {blocker}" for module, blocker in blockers]
    else:
        lines.append("_Nenhum bloqueio registrado._")
    lines.append("")
    (out_root / "INDEX.md").write_text("\n".join(lines), encoding="utf-8")


def write_knowledge(root: Path, out_root: Path):
    records = []
    for path in sorted(out_root.glob("*/manifest.json")):
        try:
            data = json.loads(read_text(path))
        except json.JSONDecodeError:
            continue
        records.append({"type": "dossier", "module": data.get("module", ""),
                        "path": f"{data.get('stem', '')}/DOSSIER.md",
                        "status": data.get("identity", {}).get("status", ""),
                        "verdict": data.get("verdict", "")})
        for feature in data.get("features", []):
            records.append({"type": "feature", "id": feature.get("id", ""),
                            "module": data.get("module", ""), "ui": feature.get("ui", ""),
                            "status": feature.get("status", ""),
                            "confidence": feature.get("confidence", ""),
                            "path": feature.get("path", "")})
        for evidence_id in data.get("evidence", {}).get("static", []):
            records.append({"type": "evidence", "kind": "static", "id": evidence_id,
                            "module": data.get("module", "")})
        for evidence_id in data.get("evidence", {}).get("behavioral", []):
            records.append({"type": "evidence", "kind": "behavioral", "id": evidence_id,
                            "module": data.get("module", "")})
    functions = root / "rag" / "index" / "functions.jsonl"
    if functions.is_file():
        for line in read_text(functions).splitlines():
            line = line.strip()
            if not line:
                continue
            try:
                record = json.loads(line)
            except json.JSONDecodeError:
                continue
            record["type"] = "function"
            records.append(record)
    with (out_root / "knowledge.jsonl").open("w", encoding="utf-8") as handle:
        for record in records:
            handle.write(json.dumps(record, ensure_ascii=False) + "\n")
    return len(records)


def main() -> int:
    parser = argparse.ArgumentParser(description="Build ArtPlus module dossiers")
    parser.add_argument("--module", help="module name, e.g. Document.dll")
    parser.add_argument("--all", action="store_true", help="build every module with artifacts")
    parser.add_argument("--list", action="store_true", help="list discovered modules")
    parser.add_argument("--max", type=int, default=0, help="limit modules with --all")
    parser.add_argument("--out", default="dossiers")
    parser.add_argument("--root", default=str(Path(__file__).resolve().parents[1]))
    parser.add_argument("--zip", action="store_true")
    args = parser.parse_args()

    root = Path(args.root).resolve()
    out_root = (root / args.out).resolve()
    out_root.mkdir(parents=True, exist_ok=True)
    inventory = load_inventory(root)
    manifests = load_manifests(root)

    if args.list:
        modules = discover_modules(root, manifests)
        for module in modules:
            marker = "dossier" if has_artifacts(root, module, manifests, inventory) else "vazio"
            print(f"{module:40} {marker}")
        return 0

    if not args.module and not args.all:
        parser.error("informe --module, --all ou --list")

    built = []
    if args.module:
        built.append(build_dossier(root, out_root, module_name(args.module), manifests, inventory))
    else:
        modules = [module for module in discover_modules(root, manifests)
                   if has_artifacts(root, module, manifests, inventory)]
        if args.max > 0:
            modules = modules[:args.max]
        for module in modules:
            print(f"gerando {module}")
            built.append(build_dossier(root, out_root, module, manifests, inventory))

    write_index(root, out_root)
    count = write_knowledge(root, out_root)

    if args.zip:
        stamp = datetime.now(timezone.utc).strftime("%Y%m%d")
        archive = out_root / f"artplus-dossiers-{stamp}.zip"
        with zipfile.ZipFile(archive, "w", zipfile.ZIP_DEFLATED) as zf:
            for path in out_root.rglob("*"):
                if path.is_file() and path != archive:
                    zf.write(path, path.relative_to(out_root))
        print(f"zip: {rel(root, archive)}")

    for item in built:
        print(f"{item['module']}: {len(item['features'])} features, "
              f"{item['function_count']} funcoes, dossie {item['stem']}/DOSSIER.md")
    print(f"indice: {rel(root, out_root / 'INDEX.md')}")
    print(f"knowledge: {count} registros")
    return 0


if __name__ == "__main__":
    sys.exit(main())
