import os,re,codecs
d=r"H:\Desktop\ArtPlus\rag\evidence\F-001\ghidra"
bad=[]
for f in sorted(os.listdir(d)):
    if not f.endswith(".md"): continue
    p=os.path.join(d,f)
    raw=open(p,"rb").read()
    if raw.startswith(codecs.BOM_UTF8): bad.append((f,"BOM"))
    try:
        t=raw.decode("utf-8")
    except Exception as e:
        bad.append((f,"utf8:"+str(e))); continue
    if not t.lstrip().startswith("---"): bad.append((f,"sem ---"))
    m=re.search(r"^versao:\s*(\S+)",t,re.M)
    if not m or m.group(1)!="24.03.10017": bad.append((f,"versao="+(m.group(1) if m else "?")))
    for k in ("modulo:","funcao:","endereco:","confianca:"):
        if not re.search(r"^"+k,t,re.M): bad.append((f,"sem "+k))
    for mk in ("Ã","â€","Â"):
        if mk in t: bad.append((f,"mojibake "+mk))
print("arquivos:",len([f for f in os.listdir(d) if f.endswith('.md')]))
print("problemas:",bad if bad else "nenhum")
