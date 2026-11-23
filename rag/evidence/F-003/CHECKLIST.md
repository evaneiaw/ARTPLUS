# F-003 Evidence Checklist

## Static Evidence (Ghidra) — 19 entries

| # | GHIDRA ID | File | Status |
|---|-----------|------|--------|
| 1 | GHIDRA-DocumentMarks-0x18001E3C0 | ghidra/DocumentMarks__0x18001E3C0.md | ✅ Created |
| 2 | GHIDRA-DocumentMarks-0x18001E350 | ghidra/DocumentMarks__0x18001E350.md | ✅ Created |
| 3 | GHIDRA-DocumentMarks-0x18001EDA0 | ghidra/DocumentMarks__0x18001EDA0.md | ✅ Created |
| 4 | GHIDRA-DocumentMarks-0x18001F870 | ghidra/DocumentMarks__0x18001F870.md | ✅ Created |
| 5 | GHIDRA-DocumentMarks-0x180020950 | ghidra/DocumentMarks__0x180020950.md | ✅ Created |
| 6 | GHIDRA-DocumentMarks-0x18001FDB0 | ghidra/DocumentMarks__0x18001FDB0.md | ✅ Created |
| 7 | GHIDRA-DocumentMarks-0x18012FAA0 | ghidra/DocumentMarks__0x18012FAA0.md | ✅ Created |
| 8 | GHIDRA-DocumentMarks-0x180132A70 | ghidra/DocumentMarks__0x180132A70.md | ✅ Created |
| 9 | GHIDRA-DocumentMarks-0x180131C40 | ghidra/DocumentMarks__0x180131C40.md | ✅ Created |
| 10 | GHIDRA-DocumentMarks-0x180131DC0 | ghidra/DocumentMarks__0x180131DC0.md | ✅ Created |
| 11 | GHIDRA-DocumentMarks-0x180131E30 | ghidra/DocumentMarks__0x180131E30.md | ✅ Created |
| 12 | GHIDRA-DocumentMarks-0x180131FE0 | ghidra/DocumentMarks__0x180131FE0.md | ✅ Created |
| 13 | GHIDRA-DocumentMarks-0x180179DA0 | ghidra/DocumentMarks__0x180179DA0.md | ✅ Created |
| 14 | GHIDRA-DocumentMarks-0x180170C20 | ghidra/DocumentMarks__0x180170C20.md | ✅ Created |
| 15 | GHIDRA-DocumentMarks-0x18016F250 | ghidra/DocumentMarks__0x18016F250.md | ✅ Created |
| 16 | GHIDRA-DocumentMarks-0x1800AA260 | ghidra/DocumentMarks__0x1800AA260.md | ✅ Created |
| 17 | GHIDRA-DocumentMarks-0x1800AA3C0 | ghidra/DocumentMarks__0x1800AA3C0.md | ✅ Created |
| 18 | GHIDRA-DocumentMarks-0x1800AA520 | ghidra/DocumentMarks__0x1800AA520.md | ✅ Created |
| 19 | GHIDRA-DocumentMarks-0x180111410 | ghidra/DocumentMarks__0x180111410.md | ✅ Created |

## Behavioral Evidence — 1 entry

| # | Capture ID | File | Status |
|---|------------|------|--------|
| 1 | CAP-20261119-02 | behavior/CAP-20261119-02/ | ⏳ Pending |

## REA Evidence — Already present

- rea/strings64.txt ✅
- rea/scan_binary.txt ✅
- rea/manifest.json ✅
- rea/inspect_pe.txt ✅
- rea/imports.txt ✅
- rea/exports.txt ✅
- rea/die.json ✅
- rea/_inspect_dm.py ✅

## Next Steps

1. Populate each Ghidra .md file with actual analysis data (xrefs, strings, vtables, etc.)
2. Create behavior capture folder and add CAP-20261119-02 evidence
3. Update manifest.json with `documentos` array listing all expected paths