# DocumentMarks.dll — Additional Functions (Registration Mark + Color Bar)

**Date:** 2026-11-19
**Module:** `C:\Esko\bg_prog_artpro+_v250\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
**SHA-256:** `ffa8809d294a7aa08bd2794e0b0c1e64608d898b5f7ba698a4e58a8e575bee10`
**Triagem:** REA `analyze` + DIE + pefile + strings64

---

## Identification

| Aspect | Value |
|---|---|
| **Compiler** | Microsoft VC++ 19.41.34435 (VS 2022 17.11) |
| **Linker** | Microsoft Linker 14.41.34435 |
| **Architecture** | PE64 x64 |
| **Image Base** | 0x180000000 |
| **Sections** | .text, .textidx, .rdata, .data, .pdata, .fnp_dir, .fnp_mar, .rsrc, .reloc |
| **Strings Found** | ~9000 defined strings (Ghidra inventory) |
| **Available Mark Types** | ~35 mark classes documented in strings |

---

## Registration Mark Support

Evidence for **registration ink** functionality (color control register mark):

### Strings

```text
NDLTaskMessages.DocumentMarks.kMarkContentUsesRegistrationInk
NDLTaskMessages.DocumentMarks.kTextMarkUsesRegistrationInk
NDLTaskMessages.DocumentMarks.kContentOfRfSMUsesRegistrationInk
```

### Type Flag Operations (from strings)

```cpp
// ChangedFillPaint (variant with SetRegistration)
?ChangeFillPaint@DocumentEdit@@YAXAEAVFillable@ArtDoc@@AEBV?$variant@USetPaint@DocumentEdit@@USetOverprint@2@USetRegistration@2@@std@@@Z

// ChangedStrokePaint (variant with SetRegistration)
?ChangeStrokePaint@DocumentEdit@@YAXAEAVContent@ArtDoc@@AEBV?$variant@USetPaint@DocumentEdit@@USetOverprint@2@USetRegistration@2@@5@@Z
```

### Registration Application Functions (from RTTI in lambda names)

```
?UnregisterPDFPlusMarks@DocumentMarks@@YAXAEAVPage@ArtDoc@@@Z
?applyRegistrationStroke@?A0xcea0966c@@YAXAEAVContentObject@ArtDoc@@PEAV34@@Z
?applyRegistrationFill@?A0xcea0966c@@YAXAEAVContentObject@ArtDoc@@PEAV34@@Z
```

**Interpretation:** Registration marks are a **global ink type** (not an individual mark class) that can be applied to any fillable object. The implementation uses:

1. A **variant type** (`SetPaint` union: `SetPaint` | `SetOverprint` | `SetRegistration`) in `DocumentEdit`
2. Lambda functions apply registration stroke/fill during regeneration
3. Message IDs for validation (`kMarkContentUsesRegistrationInk`, etc.)

**Status:** Architecture and type manifest are identified. Function implementation requires Ghidra decompilation to map to concrete functions.

---

## Color Bar / Gradation Mark Support

Evidence for **gradational color strip** functionality (often called "Color Bar" or "Control Strip"):

### Class RTTI

```cpp
??0?$ConstVisitor@VGradationMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z           // ConstVisitor<GradationMark>
??0?$ConstVisitor@VGradationMark@DocumentMarks@@@ArtDoc@@QEAA@XZ                // ConstVisitor constructor
??0?$Visitor@VGradationMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z              // Visitor<GradationMark>
??0?$Visitor@VGradationMark@DocumentMarks@@@ArtDoc@@QEAA@XZ                     // Visitor constructor
??_7?$ConstVisitor@VGradationMark@DocumentMarks@@@ArtDoc@@6B@
??_7?$Visitor@VGradationMark@DocumentMarks@@@ArtDoc@@6B@
??_7GradationMark@DocumentMarks@@6B?$ListItem@VContentObject@ArtDoc@@@Detail@ArtDoc@@@
??_7GradationMark@DocumentMarks@@6BVisitable@ArtDoc@@@
```

### Key Property Strings

```text
GradationMarkFillTint
GradationMarkStrokeTint
GradationMark
WARNING: Gradation Mark is set to horizontal but is vertical
WARNING: Gradation Mark is set to vertical but is horizontal
Error: cannot obtain horizontal info for Gradation Mark
Error: cannot obtain flip info for Gradation Mark
```

### Generation Functions

```cpp
// Legacy creation function (static)
?CreateSingleGradationStrip@GradationMark@DocumentMarks@@CA_NPEAPEAVBlendable@ArtDoc@@_NAEBV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@N@Z

// Placement functions (from RTTI lambda names)
?PlaceGradationSymbol@GradationMark@DocumentMarks@@CANAEAVContentObject@ArtDoc@@_NAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
.?AV<lambda_2>@?1??PlaceGradationSymbol@GradationMark@DocumentMarks@@CANAEAVContentObject@ArtDoc@@_NAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z@
```

```cpp
// Trimming function
?TrimSymbol@GradationMark@DocumentMarks@@CAXAEAVContentObject@ArtDoc@@_NN@Z
```

### Generic Mark Functions (see note)
Observing the string pattern across ~35 documented mark classes, each has the same wrapper functions:

```cpp
getFormulas@GradationMark@DocumentMarks@@MEBA...
getMarkType@GradationMark@DocumentMarks@@UEBA...
parsePdfPropertiesDict@GradationMark@DocumentMarks@@UEAA...
regenerateMarkImp@GradationMark@DocumentMarks@@MEAAX...
getRefBoxes@GradationMark@DocumentMarks@@MEBA...
getRefObjects@GradationMark@DocumentMarks@@MEBA...
```

**Interpretation:** `GradationMark` implements the standard `DynamicMark` pattern (see F-003 BearerBar):

1. **Composition:** Uses `Blendable` objects for color/stroke control (from `CreateSingleGradationStrip`)
2. **Placement:** `PlaceGradationSymbol` determines where the gradation appears in the export tree
3. **Trimmability:** `TrimSymbol` supports variable-length gradation strips (裁剪/分段)
4. **Orientation:** Warnings indicate horizontal/vertical flexibility with flip support
5. **Tint properties:** Fill (`GradationMarkFillTint`) and stroke (`GradationMarkStrokeTint`) can be tuned separately

**Status:** Class structure and function signatures are identified. Behavior for gradation color model and export mapping needs Ghidra decompilation.

---

## Other Mark Types Identified

### Visitor Patterns (RTTI)

**CustomMark:**
```cpp
??0?$ConstVisitor@VCustomMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z
??0?$ConstVisitor@VCustomMark@DocumentMarks@@@ArtDoc@@QEAA@XZ
??0?$Visitor@VCustomMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z
??0?$Visitor@VCustomMark@DocumentMarks@@@ArtDoc@@QEAA@XZ
```

**TextMark:**
```cpp
??0?$ConstVisitor@VTextMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z
??0?$ConstVisitor@VTextMark@DocumentMarks@@@ArtDoc@@QEAA@XZ
??0?$Visitor@VTextMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z
??0?$Visitor@VTextMark@DocumentMarks@@@ArtDoc@@QEAA@XZ
```

**ImageMark:**
```cpp
??0?$ConstVisitor@VImageMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z
??0?$ConstVisitor@VImageMark@DocumentMarks@@@ArtDoc@@QEAA@XZ
??0?$Visitor@VImageMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z
??0?$Visitor@VImageMark@DocumentMarks@@@ArtDoc@@QEAA@XZ
```

### Mark Registration Entrypoints (from strings)

```cpp
?registerMarkGenerator@CustomMark@DocumentMarks@@SAXXZ
?registerMarkGenerator@ImageMark@DocumentMarks@@SAXXZ
?registerMarkGenerator@TextMark@DocumentMarks@@SAXXZ
?registerGenerator@DynamicObject@DocumentMarks@@SAX...
```

**Interpretation:** These functions register factory callbacks: when a file loads (PDF+), the reader calls `registerMarkGenerator` for each known type to instantiate the mark object.

---

## Dependencies

### Imported DLLs (from pefile scan)

| DLL | Count | Purpose |
|---|---|---|
| `Document.dll` | 732 | Core document model |
| `DocumentEdit.dll` | 66+ | Edit operations |
| `YAGL.dll` | 45+ | Geometry / Anchor system |
| ` localization.dll` | 47 | UI strings (registration ink messages) |
| `DocumentBarCode.dll` | 33 | Barcode mark support (families cross-include) |
| `DocumentEditSeparations.dll` | 3 | Separation/ink validation |
| `DocumentDimensions.dll` | 5 | Dimensions marks |
| `DocumentTypesetting.dll` | 48+ | Text/flow marks |
| `UniversalText.dll` | 48+ | Advanced text composition |
| `CMS.dll` | 8 | Color management (gradation tints) |
| `boost_filesystem.dll` | 12 | Path handling |
| `boost_iostreams.dll` | 11+ | Data streaming |

**Observation:** Registration mark is **not** a standalone mark type—it's implemented via existing ink/region infrastructure (`DocumentEdit`, `CMS`, `Localization`).

---

## Gap Analysis vs. F-003 (Bearer Bar) Approach

| Aspect | BearerBar (F-003) | Registration Mark | GradationMark |
|---|---|---|---|
| **Explicit class** | ✅ `DocumentMarks::BearerBar` + `PDFPlusBearerBar` | ⚠️ No dedicated `RegistrationMark` class | ✅ `DocumentMarks::GradationMark` |
| **Vtable entry** | Listed (families documented) | Not listed | Listed (see RTTI above) |
| **Dominant string prefix** | `BearerBar` | `Registration` (ink type only) | `GradationMark` |
| **UI string** | Found (logged in debug) | Not found (likely multi-language UI module) | Not found (edge case warnings logged) |
| **Persistence/format** | `DM-BearerBarParams` (custom) | `SetRegistration` variant (colorant policy) | `DM-GradationMarkParams` (inferred, pattern similar to BearerBar) |

**Conclusion:**
- **Registration Mark** is a **global ink policy**, not a visible mark class on artwork. Controls whether selected objects use registration ink in separations.
- **GradationMark** follows the **same architectural pattern** as BearerBar (F-003) and will likely have the same GitOps support (PDF+ writer, undo/undo/serialize). Manual import is needed.

---

## Evidence Links

- **DIE JSON:** `rag/sources/DocumentMarks_die.json`
- **PE Headers:** `rag/sources/DocumentMarks_pofit.py`
- **Strings CSV:** `rag/sources/DocumentMarks.strings.txt`
- **Dependents Table:** `C:\Users\Evanei\AppData\Local\Microsoft\WinGet\Packages\horsicq.DIE-engine_Microsoft.Winget.Source_8wekyb3d8bbwe\die\diec.exe -j` (merged into this file)
- **Ghidra Analysis:** Project `ArtProPlus` / binary `DocumentMarks.dll` (CE available)
- **Ghidra Summary:** `ev_12dee37cf3a373a21c4656157e427bd3ecdf1d30f61991ab9081d1ba7e54165a` (from `rea analyze`)

---

## Recommendations

1. **For Registration Mark (F-007?):** allocate `DocumentEdit::SetRegistrationContent` / `ClearRegistrationInk` functions and implement the variant update flow seen in `ChangeFillPaint` / `ChangeStrokePaint` signatures.
2. **For GradationMark (F-008?):** use F-003 as a blueprint (Variant↔object syntax from `parsePdfPropertiesDict`, undo functions naming pattern).
3. **For Ghidra deep-dive:** verify whether `GradationMark` has:
   - Separate `GradationMarkParams` keys (`DM-GradationMarkParams-Version` pattern)
   - UIManager integration (non-logged UI steps, not only warnings)
   - Export bundle integration (`RenderSeparations::GradationMark`)

---

## Saved Output References

- Raw DIE: `rag/sources/DocumentMarks_die.json`
- Debug script output: `tools/ghidra_analysis/DocumentMarks_strings.log`