# DocumentMarks.dll — Registro de funções não mapeadas: Registration Mark e Color Bar

**Versão:** v250 (SHA-256 `ffa8809d294a7aa08bd2794e0b0c1e64608d898b5f7ba698a4e58a8e575bee10`)
**Módulo:** `C:\Esko\bg_prog_artpro+_v250\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
**Data da triagem:** 2026-11-19
**Relatório de triagem:** `rag/evidence/DocumentMarks/rea/DOCUMENTMARKS_ADDITIONAL_FUNCTIONS.md`

---

## Identificação do binário

| Campo | Valor |
|---|---|
| PE | PE64 (x86-64 DLL) |
| Image base | `0x180000000` |
| Compilador | Microsoft VC++ 19.41.34435 (VS 2022 17.11) |
| Linker | Microsoft Linker 14.41.34435 |
| Runtime | Microsoft C/C++ Runtime (dinâmico) |
| Assinatura | Windows Authenticode (PKCS #7) |
| Secões | `.text`, `.textidx`, `.rdata`, `.data`, `.pdata`, `.fnp_dir`, `.fnp_mar`, `.rsrc`, `.reloc` |
| Ghidra procedures | 12.192 |
| Ghidra strings | 9.004 |
| GHS Ghidra | `H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC`, projeto `ArtProPlus`, `DocumentMarks.dll` |

---

## Registration Mark

### Contexto

A funcionalidade de **registration ink** não é uma marca própria com classe dedicada (`RegistrationMark`). É uma **política de cor/região** aplicável a objetos existentes através de um tipo variant no sistema de edição do documento.

### Strings identificadas

```text
NDLTaskMessages.DocumentMarks.kMarkContentUsesRegistrationInk
NDLTaskMessages.DocumentMarks.kTextMarkUsesRegistrationInk
NDLTaskMessages.DocumentMarks.kContentOfRfSMUsesRegistrationInk
Registration
[Registration]
registration
```

### Assinaturas de função (strings, não endereços)

| Assinatura | Papel |
|---|---|
| `?ChangeFillPaint@DocumentEdit@@YAXAEAVFillable@ArtDoc@@AEBV?$variant@USetPaint@DocumentEdit@@USetOverprint@2@USetRegistration@2@@std@@@Z` | Altera fill paint com opção `SetRegistration` (variant `Paint | Overprint | Registration`) |
| `?ChangeStrokePaint@DocumentEdit@@YAXAEAVStrokable@ArtDoc@@AEBV?$variant@USetPaint@DocumentEdit@@USetOverprint@2@USetRegistration@2@@std@@@Z` | Altera stroke paint com opção `SetRegistration` |
| `?ChangeStrokePaint@DocumentEdit@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVStrokable@ArtDoc@@@Z@std@@AEBV?$variant@USetPaint@DocumentEdit@@USetOverprint@2@USetRegistration@2@@5@@Z` | Overload para Content-based stroke |
| `?UnregisterPDFPlusMarks@DocumentMarks@@YAXAEAVPage@ArtDoc@@@Z` | Desativa marcas PDF+ em uma página (registration aware) |

### Internos observados (via lambda names e vtable)

| Símbolo | Contexto |
|---|---|
| `?applyRegistrationStroke@?A0xcea0966c@@YAXAEAVContentObject@ArtDoc@@PEAV34@@Z` | Aplica registration stroke em ContentObject |
| `?applyRegistrationFill@?A0xcea0966c@@YAXAEAVContentObject@ArtDoc@@PEAV34@@Z` | Aplica registration fill em ContentObject |

**Interpretação:** Registration Mark está implementado como um **tipo de paint dentro do variant `SetPaint/SetOverprint/SetRegistration`** da camada `DocumentEdit`, não como um mark com vtable própria. Toda operação de activation/desativaçao passa pelos wrappers `ChangeFillPaint`/`ChangeStrokePaint` em `DocumentEdit.dll` (count de imports: 66 símbolos).

---

## Color Bar / Gradation Mark

### Contexto

A funcionalidade de color bar (correspondente a gradação/faixa de cor de controle) está implementada pela classe **`GradationMark`**, com vtable e RTTI dedicados no binário.

### Strings de interesse

| String | Uso |
|---|---|
| `GradationMark` | Nome do tipo mark |
| `GradationMarkFillTint` | Chave/constante de cor de preenchimento |
| `GradationMarkStrokeTint` | Chave/constante de cor de contorno |
| `WARNING: Gradation Mark is set to horizontal but is vertical` | Validação de orientação |
| `WARNING: Gradation Mark is set to vertical but is horizontal` | Validação de orientação |
| `Error: cannot obtain horizontal info for Gradation Mark` | Erro de leitura de geometria horizontal |
| `Error: cannot obtain flip info for Gradation Mark` | Erro de leitura de espelhamento/flip |

### RTTI (vtable addresses)

| Símbolo | Significado |
|---|---|
| `??_7GradationMark@DocumentMarks@@6B` | RTTI da classe GradationMark |
| `??0?$ConstVisitor@VGradationMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z` | ConstVisitor constructor |
| `??0?$Visitor@VGradationMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z` | Visitor constructor |

### Funções identificadas

| Nome (demangled) | Papel | Status |
|---|---|---|
| `?CreateSingleGradationStrip@GradationMark@DocumentMarks@@CA_NPEAPEAVBlendable@ArtDoc@@...@Z` | Cria strip de graduação/gradiente a partir de um blendable | Identificado via strings |
| `?PlaceGradationSymbol@GradationMark@DocumentMarks@@CANAEAVContentObject@ArtDoc@@...@Z` | Posiciona símbolo de graduação no export tree | Identificado via strings |
| `?TrimSymbol@GradationMark@DocumentMarks@@CAXAEAVContentObject@ArtDoc@@_NN@Z` | Trimsímbolo (corte/segmentação do gradiente) | Identificado via strings |
| `?getFormulas@GradationMark@DocumentMarks@@MEBA...` | Retorna fórmulas de parâmetros | Padrão de DynamicMark |
| `?getMarkType@GradationMark@DocumentMarks@@UEBA...` | Retorna string de tipo | Padrão de DynamicMark |
| `?parsePdfPropertiesDict@GradationMark@DocumentMarks@@UEAA...` | Parse do dicionário PDF+ | Padrão de DynamicMark |
| `?regenerateMarkImp@GradationMark@DocumentMarks@@MEAAX...` | Regenera conteúdo da marca | Padrão de DynamicMark |

**Interpretação:** `GradationMark` segue o mesmo padrão arquitetônico de `DynamicMark` já documentado para Bearer Bar (F-003). Não há endereços numéricos disponíveis sem importação Ghidra dedicada.

---

## Comparação com Bearer Bar (F-003)

| Item | Bearer Bar (já mapeado) | Gradation Mark | Registration Mark |
|---|---|---|---|
| Classe | `DocumentMarks::BearerBar` + `PDFPlusBearerBar` | `DocumentMarks::GradationMark` | Não existe classe dedicada |
| Vtable | Endereços conhecidos | RTTI presente | Não aplicável |
| Persistence keys | `DM-BearerBarParams-*` | (inferido: `DM-GradationMarkParams-*`) | `SetRegistration` variant |
| UI strings | Encontradas em debug log | Não encontradas (warnings logados) | Não encontradas (multi-language module) |
| Funções de undo/serialização | `setColorTypeImp`, `updatePdfPropertiesDictImp` | (padrão similar esperado) | `ChangeFillPaint`/`ChangeStrokePaint` |

---

## Dependências

| DLL | Import count | Papel |
|---|---|---|
| Document.dll | 732 | Modelo de documento central |
| DocumentEdit.dll | 66 | Edit operations (registration ink variant) |
| YAGL.dll | 45+ | Geometria/anchors |
| Localization.dll | 47 | Mensagens de UI (registration ink) |
| CMS.dll | 8 | Color management (gradation tint) |
| DocumentBarCode.dll | 33 | Barcode marks (cross-include) |
| DocumentTypesetting.dll | 48+ | Text marks |
| UniversalText.dll | 48+ | Text composition |
| DocumentEditSeparations.dll | 3 | Separação/validação de tintas |

---

## Evidência

| Artefato | Caminho |
|---|---|
| Triage completo (markdown) | `rag/evidence/DocumentMarks/rea/DOCUMENTMARKS_ADDITIONAL_FUNCTIONS.md` |
| DIE JSON | `rag/sources/DocumentMarks_die.json` |
| Informações PE | `rag/sources/DocumentMarks_pofit.txt` (via `inspect_pe.py`) |
| Strings | `rag/sources/DocumentMarks.strings.txt` |
| Pe-file exports/imports | via `pefile` scan (não salvo separadamente) |
| Ghidra | Projeto `ArtProPlus`, `DocumentMarks.dll` (não importado novo; usa projeto existente) |

---

## Status e lacunas

1. **Registration Mark:** Tipo `SetRegistration` existe como variant dentro do sistema de paint. Implementação completa requer descompilação de `DocumentEdit::ChangeFillPaint` / `ChangeStrokePaint` e validação do comportamento da separação de tintas.
2. **Gradation Mark:** Classe RTTI e funções de geração/posicionamento/trimming identificadas por strings. Endereços e comportamento internos (geom do gradiente, tinta de preenchimento vs. contorno, exportação por separação) requerem importação Ghidra dedicada ou analise por `procedure_pseudo_code`.
3. **UI strings:** Não foram encontradas strings de menu/painel com "Registration Mark" ou "Color Bar" em `DocumentMarks.dll`. O UI pode residir em outro módulo (Localization, Preferences, ou studio UI).
4. **Diff v240×v250:** Não executado. Não fazer afirmações de comportamento idêntico entre versões sem diff.