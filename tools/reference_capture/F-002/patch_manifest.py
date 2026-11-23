import json, io
p = r"rag/evidence/F-002/manifest.json"
with io.open(p, encoding="utf-8") as f:
    m = json.load(f)
m["comportamental"] = ["CAP-20261121-03"]
m["capturas"] = [
    "shot-06-file-probe.png", "shot-07-document-open.png", "menu-1842.png",
    "menu-1899.png", "shot-08-save-delete-markset.png"
]
bl = [b for b in m.get("bloqueios", []) if not b.startswith("CAP-BLOCKED-20261121-01")]
bl.append("CAP-BLOCKED-20261121-01 (Mark Set nao localizada) esta SUPERADO por CAP-20261121-03: Mark Set existe na v24.03.10017 em painel Document > Marks > engrenagem (Load Mark Set... / Save/Delete Mark Set...). O arquivo CAP-BLOCKED fica preservado como historico da tentativa.")
m["bloqueios"] = bl
with io.open(p, "w", encoding="utf-8") as f:
    json.dump(m, f, ensure_ascii=False, indent=2)
print("manifest ok", m["comportamental"], len(m["capturas"]))
