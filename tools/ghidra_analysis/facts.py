import re,glob,os
base=r"H:\Desktop\ArtPlus\rag\evidence\F-001\ghidra\raw_v240"
addrs=["1801344e0","180136190","180134b00","180172100","180135160","1800aa1b0","1800a9fb0","180134f60","180135670","180135660","18010e0f0","180051f90","180052950","180052470","180052700","180243ec0","180245380","180134880","180135930","180135cb0","180134830","18012a130","1801683e0"]
for a in addrs:
    p=os.path.join(base,"addr_%s.txt"%a)
    if not os.path.exists(p): continue
    t=open(p,encoding='utf-8').read().splitlines()
    def get(k):
        for l in t:
            if l.startswith(k+"="): return l.split("=",1)[1]
        return ""
    print("###",a,get("qualifiedName"),"|",get("bodySize"),"bytes","|",get("signature")[:110])
    sec=None; xr=[]; cal=[]; st=[]
    for l in t:
        if l.startswith("["): sec=l; continue
        if sec=="[XREFS_TO]" and "refType=" in l: xr.append(l.strip())
        if sec=="[CALLEES]" and l.strip(): cal.append(l.strip())
        if sec=="[STRINGS_REFERENCED]" and l.strip(): st.append(l.strip())
    print("  xrefs_to:", "; ".join(xr[:8]))
    print("  callees:", "; ".join(cal[:14]))
    print("  strings:", "; ".join(st[:6]))
