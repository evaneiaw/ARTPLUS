import struct
import pefile

TARGET = r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\PDFObjectActions.dll"
pe = pefile.PE(TARGET, fast_load=True)
base = pe.OPTIONAL_HEADER.ImageBase
data = open(TARGET, "rb").read()


def read_qword(va, n=1):
    rva = va - base
    off = pe.get_offset_from_rva(rva)
    out = []
    for i in range(n):
        out.append(struct.unpack("<d", data[off + i * 8: off + i * 8 + 8])[0])
    return out


def read_bytes(va, n):
    off = pe.get_offset_from_rva(va - base)
    return data[off:off + n]


for name, va in [("DAT_18044ef28", 0x18044EF28), ("DAT_1804141a0", 0x1804141A0),
                 ("DAT_18040a028", 0x18040A028), ("DAT_180418898", 0x180418898),
                 ("DAT_18040d700", 0x18040D700)]:
    try:
        vals = read_qword(va)
        raw = read_bytes(va, 8)
        print("%s = %r -> %r" % (name, vals[0], raw.hex()))
    except Exception as e:
        print("%s erro: %s" % (name, e))
