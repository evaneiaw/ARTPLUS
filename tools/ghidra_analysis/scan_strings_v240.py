import re,sys
p=r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll"
data=open(p,'rb').read()
pats=[b"Cut Mark has invalid Orientation value",b"Cut Mark has invalid Repetition value",b"AllStructuralDesignStations",b"Horizontal",b"Vertical",b"LineTypes",b"Creasing",b"Cutting",b"ReferenceID",b"PDFPlusCutMark_Offset"]
for s in pats:
    idx=[m.start() for m in re.finditer(re.escape(s),data)]
    print(s.decode(), len(idx), [hex(i) for i in idx[:6]])
