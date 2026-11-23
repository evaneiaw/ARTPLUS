import hashlib, json, sys
import pefile

TARGET = r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\PDFObjectActions.dll"
OUT = r"H:\Desktop\ArtPlus\rag\evidence\F-004"

h256 = hashlib.sha256(open(TARGET, 'rb').read()).hexdigest().upper()
h1 = hashlib.md5(open(TARGET, 'rb').read()).hexdigest().upper()

pe = pefile.PE(TARGET, fast_load=False)
info = {
    "arquivo": TARGET,
    "tamanho_bytes": len(open(TARGET, 'rb').read()),
    "sha256": h256,
    "md5": h1,
    "machine": hex(pe.FILE_HEADER.Machine),
    "image_base": hex(pe.OPTIONAL_HEADER.ImageBase),
    "timestamp": pe.FILE_HEADER.TimeDateStamp,
    "dll": bool(pe.FILE_HEADER.Characteristics & 0x2000),
    "secoes": [{"nome": s.Name.rstrip(b"\x00").decode("latin-1"),
                "va": hex(s.VirtualAddress), "vsize": s.Misc_VirtualSize,
                "rawsize": s.SizeOfRawData,
                "entropia": round(s.get_entropy(), 3)} for s in pe.sections],
    "imports": sorted({e.dll.decode("latin-1").lower() for e in getattr(pe, "DIRECTORY_ENTRY_IMPORT", [])}),
    "exports_count": len(pe.DIRECTORY_ENTRY_EXPORT.symbols) if hasattr(pe, "DIRECTORY_ENTRY_EXPORT") else 0,
}
with open(OUT + r"\identity.json", "w", encoding="utf-8", newline="\n") as f:
    json.dump(info, f, indent=2, ensure_ascii=False)
    f.write("\n")

with open(OUT + r"\imports.txt", "w", encoding="utf-8", newline="\n") as f:
    for d in info["imports"]:
        f.write(d + "\n")

with open(OUT + r"\exports.txt", "w", encoding="utf-8", newline="\n") as f:
    for s in getattr(getattr(pe, "DIRECTORY_ENTRY_EXPORT", None), "symbols", []):
        f.write((s.name.decode("latin-1") if s.name else "%d" % s.ordinal) + "\n")

print(json.dumps({k: info[k] for k in ("tamanho_bytes", "sha256", "md5", "image_base", "exports_count")}, indent=2))
print("imports:", info["imports"])
