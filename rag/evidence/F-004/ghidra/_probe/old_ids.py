import struct
import pefile

TARGET = r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\PDFObjectActions.dll"
pe = pefile.PE(TARGET, fast_load=True)
base = pe.OPTIONAL_HEADER.ImageBase
data = open(TARGET, "rb").read()
secs = [(s.Name.rstrip(b"\x00").decode(), s.VirtualAddress, s.Misc_VirtualSize,
         s.PointerToRawData, s.SizeOfRawData) for s in pe.sections]
print("sections:", secs)

for va in [0x1806DC21E, 0x1806DC254, 0x1806DC287, 0x1806DC2C4, 0x18068447E, 0x1806844B4,
           0x180688437, 0x1806AC7C5, 0x1806E8F62, 0x1807015ED, 0x1802A7060, 0x1802A79E0,
           0x18028BEE0, 0x18028CC70, 0x18028C310, 0x18028DF80]:
    rva = va - base
    sec = None
    for n, sva, vs, praw, rsz in secs:
        if sva <= rva < sva + max(vs, rsz):
            sec = n
            break
    if sec is None:
        print("%x -> fora de secao" % va)
        continue
    off = pe.get_offset_from_rva(rva)
    chunk = data[off:off + 48]
    printable = sum(1 for b in chunk if 32 <= b < 127) / max(1, len(chunk))
    print("%x sec=%-7s printable=%.2f %r" % (va, sec, printable, chunk[:40]))
