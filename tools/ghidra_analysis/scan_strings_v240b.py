import re
p=r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll"
data=open(p,'rb').read()
for s in [b"structural",b"Structural",b"LineType",b"linetypes",b"Orientation",b"Repetition",b"Reference"]:
    idx=[m.start() for m in re.finditer(re.escape(s),data)]
    print(s, len(idx), [hex(i) for i in idx[:8]])
# utf16
for s in ["AllStructuralDesignStations","LineTypes","Cut Mark has invalid Orientation value"]:
    u=s.encode('utf-16le')
    idx=[m.start() for m in re.finditer(re.escape(u),data)]
    print("UTF16",s,len(idx),[hex(i) for i in idx[:4]])
# all ascii strings containing 'ut Mark' with printable context
import sys
for m in re.finditer(rb"[ -~]{6,}",data):
    t=m.group().decode('ascii','ignore')
    if 'ut Mark' in t or 'utMark' in t:
        print(hex(m.start()), repr(t[:100]))
