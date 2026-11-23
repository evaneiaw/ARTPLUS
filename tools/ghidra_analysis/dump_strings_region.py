import re
p=r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll"
data=open(p,'rb').read()
for m in re.finditer(rb"[ -~]{5,}",data):
    off=m.start()
    if 0x319000 <= off <= 0x323500:
        print(hex(off), m.group().decode('ascii','ignore'))
