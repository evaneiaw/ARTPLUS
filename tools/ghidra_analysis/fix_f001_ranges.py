# -*- coding: utf-8 -*-
p = r"H:\Desktop\ArtPlus\tools\ghidra_analysis\gen_f001_evidence.py"
s = open(p, encoding="utf-8").read()
repl = {
    "`0x180136190`\u2013`0x180136DE2`": "`0x180136190`\u2013`0x180136DD6`",
    "`0x180172100`\u2013`0x180172593`": "`0x180172100`\u2013`0x180172568`",
    "`0x1800A9FB0`\u2013`0x1800AA1B1`": "`0x1800A9FB0`\u2013`0x1800AA1B0`",
    "`0x180134F60`\u2013`0x180135154`": "`0x180134F60`\u2013`0x180135153`",
    "`0x180135660`\u2013`0x18013566E`": "`0x180135660`\u2013`0x18013566D`",
    "`0x18010E0F0`\u2013`0x18010FD37`": "`0x18010E0F0`\u2013`0x18010FD36`",
    "`0x180051F90`\u2013`0x180051FCD`": "`0x180051F90`\u2013`0x180051FCC`",
    "`0x180052950`\u2013`0x18005307C`": "`0x180052950`\u2013`0x180053072`",
    "`0x180052470`\u2013`0x1800526EE`": "`0x180052470`\u2013`0x1800526ED`",
    "`0x180052700`\u2013`0x180052940`": "`0x180052700`\u2013`0x18005293F`",
    "`0x180243EC0`\u2013`0x180243F2D`": "`0x180243EC0`\u2013`0x180243F2C`",
    "`0x180245380`\u2013`0x180245B79`": "`0x180245380`\u2013`0x180245B78`",
    "`0x180134880`\u2013`0x180134B03`": "`0x180134880`\u2013`0x180134AFB`",
    "`0x180135930`\u2013`0x1801359A1`": "`0x180135930`\u2013`0x1801359A0`",
    "`0x180135CB0`\u2013`0x1801360DF`": "`0x180135CB0`\u2013`0x18013617E`",
    "`0x180134830`\u2013`0x18013487B`": "`0x180134830`\u2013`0x18013487A`",
    "`0x18012A130`\u2013`0x18012A3C5`": "`0x18012A130`\u2013`0x18012A3C4`",
    "`0x1801683E0`\u2013`0x18016D5BF`": "`0x1801683E0`\u2013`0x18016D5B7`",
    "`0x180135670`\u2013`0x1801358E1`": "`0x180135670`\u2013`0x1801358E0`",
    "Os type descriptors\n`PDFPlusCutMark` aparecem em `0x1803B...` (RTTI), conforme o import log.":
        "Os type descriptors de `PDFPlusCutMark` aparecem no bloco `.rdata`\n(por exemplo, `0x1803AF992`), conforme o import log e a varredura de strings.",
}
missing = []
for a, b in repl.items():
    if a not in s:
        missing.append(a)
    s = s.replace(a, b)
open(p, "w", encoding="utf-8", newline="\n").write(s)
print("missing:", missing)
