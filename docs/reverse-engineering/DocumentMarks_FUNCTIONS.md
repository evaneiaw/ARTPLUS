# DocumentMarks.dll — índice de funções (F-001, Trim Marks)

Módulo: `C:\Esko\bg_prog_artpro+_v250\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
versão 25.0 · SHA-256 `ffa8809d294a7aa08bd2794e0b0c1e64608d898b5f7ba698a4e58a8e575bee10`
PE32+ x64 · MSVC 19.41 · image base `0x180000000` · **2.268 exports nomeados**

Programa Ghidra: projeto `ArtProPlus`, programa `DocumentMarks.dll` (análise padrão, import
único). Reprocessar sempre com `-process`, nunca `-import`.

Export bruto: `rag/ghidra/exports/DocumentMarks.dll/`
(`functions.csv` 10.672 · `symbols.csv` 111.739 · `xrefs.csv` 28.768 · `strings.csv` 6.612 ·
`marks_focus.txt` · `marks_decompiled.c` · `decompiled/`). Evidência: `rag/evidence/F-001/ghidra/`.

## Nomenclatura: "Trim Marks" × "Cut Mark"

Não existe literal `Trim Marks`/`TrimMark` no binário. A funcionalidade é implementada pela
família **Cut Mark**:

| Chave / símbolo | Onde |
|---|---|
| `AIDynamicMarks-CutMark` | formato legado (AI Dynamic Marks) |
| `DynamicObject_PDFPlusCutMark` | retorno de `getMarkType()` no formato PDF+ |
| `DM-CutMarkParams*` | persistência legada (offset, símbolo, versão) |

**Mapeamento F-001 → `PDFPlusCutMark` (inferência, confiança alta)** — justificado por:
única classe de marca de corte do módulo, referência a `PageBox` (que contém TrimBox) e
strings de erro "Cut Mark". Ver `rag/evidence/F-001/ghidra/DocumentMarks__identity.md`.

## Classes

| Classe | Papel | Vtable (ListItem / Visitable) |
|---|---|---|
| `DocumentMarks::PDFPlusCutMark` | marca de corte do formato PDF+ (caminho atual) | `0x1803231B0` / `0x180323330` |
| `DocumentMarks::CutMark` | marca de corte legada (AI Dynamic Marks) | `0x180308BD8` / `0x180308D58` |
| `dm::CutMarkPositionGenerator` | gerador de posições (RTTI presente, sem export) | — |
| `TaskMarkSets` | aplicação de mark sets em páginas | `0x180337D60` |

Herança observada nas vtables: `ContentObject` → `Group` → `DynamicObject` → `DynamicMark` →
`PDFPlusCutMark`; interfaces `Visitable` e `ArtDoc::Detail::ListItem<ContentObject>`.

## Funções-chave

| Endereço | Função | Papel | Confiança | Evidência |
|---|---|---|---|---|
| `0x18013A8B0` | `PDFPlusCutMark::PDFPlusCutMark(shared_ptr<FormPaint const>)` | ctor; defaults (PageBox 3, Orientation 1, Repetition 2, LineTypes [0], Offset 0) | alta | [0x18013A8B0](../../rag/evidence/F-001/ghidra/DocumentMarks__0x18013A8B0.md) |
| `0x18013E3B0` | `PDFPlusCutMark::getMarkType` | devolve `"DynamicObject_PDFPlusCutMark"` | alta | [strings](../../rag/evidence/F-001/ghidra/DocumentMarks__strings.md) |
| `0x18013CB50` | `PDFPlusCutMark::GetReferenceBox` | resolve a caixa via `ArtDoc::Page::GetPageBox` | alta | [0x18013CB50](../../rag/evidence/F-001/ghidra/DocumentMarks__0x18013CB50.md) |
| `0x18013D160` | `PDFPlusCutMark::SetOffset` | offset = quantidade **ou** fórmula (variant) | alta | [0x18013D160](../../rag/evidence/F-001/ghidra/DocumentMarks__0x18013D160.md) |
| `0x1800ADB10` | `SetCutMarkOffset(PDFPlusCutMark&, variant const&)` | setter transacional (undo) | alta | [0x1800ADB10](../../rag/evidence/F-001/ghidra/DocumentMarks__0x1800ADB10.md) |
| `0x18013EE90` | `PDFPlusCutMark::regenerateMarkImp` | gera a geometria (slot 29) | alta | [0x18013EE90](../../rag/evidence/F-001/ghidra/DocumentMarks__0x18013EE90.md) |
| `0x18017C5D0` | parser de dicionário PDF+ (nome sintético) | lê Position/Reference/Orientation/Repetition; valida | alta | [0x18017C5D0](../../rag/evidence/F-001/ghidra/DocumentMarks__0x18017C5D0.md) |
| `0x180172550` | leitor de marca PDF+ (nome sintético) | cria `PDFPlusCutMark` em `0x1801747BA` e chama o parser | alta | [0x180172550](../../rag/evidence/F-001/ghidra/DocumentMarks__0x180172550.md) |
| `0x180111410` | `createDynamicObject` legado | `memcmp "AIDynamicMarks-CutMark"` → `new CutMark(true)` em `0x18011235D` | alta | [0x180111410](../../rag/evidence/F-001/ghidra/DocumentMarks__0x180111410.md) |
| `0x180052CA0` | `CutMark::regenerateMarkImp` | clona símbolo por canto via `PlaceCutMarkSymbol` | alta | [0x180052CA0](../../rag/evidence/F-001/ghidra/DocumentMarks__0x180052CA0.md) |
| `0x18024D3E0` | `TaskMarkSets::ApplyMarksFromSet` | copia a 1ª página de cada doc de mark set para a página alvo | alta | [0x18024D3E0](../../rag/evidence/F-001/ghidra/DocumentMarks__0x18024D3E0.md) |

### Funções auxiliares confirmadas

| Endereço | Função | Nota |
|---|---|---|
| `0x180052340` | `CutMark::CutMark(bool)` | ctor legado; chamado pela fábrica em `0x18011235D` |
| `0x180052820` | `CutMark::PlaceCutMarkSymbol(ContentObject&, CPoint, CPoint)` | posiciona cópia do símbolo |
| `0x180052A50` | `CutMark::parsePdfPropertiesDict` | lê `DM-CutMarkParams-{Version,Offset,SymbolDefinition}` |
| `0x1800AD910` | `SetCutMarkOffset(Content&, function<bool(const PDFPlusCutMark&)>, variant const&)` | variante em lote |
| `0x1800ADCA0` / `0x1800ADE00` | `SetCutMarkOrientation` | lote / objeto |
| `0x1800AE100` / `0x1800AE260` | `SetCutMarkRepetition` | lote / objeto |
| `0x1800AD540` / `0x1800AD730` | `SetCutMarkLineTypes` | lote / objeto |
| `0x1800ADF00` | `SetCutMarkReferenceToAllStructuralDesignStations` | referência especial |
| `0x18013D750` | `PDFPlusCutMark::UpdateMarkErrors` | registra erros de marca (tags 0x7D/0x7E) |
| `0x18013CEF0` | `PDFPlusCutMark::RemoveInvalidCustomFormulasImp` | remove fórmula inválida via `SetCutMarkOffset` |
| `0x18024D460` | `TaskMarkSets::ApplyRelevantMarkSets` | separações + `MakeFormsFromMarks` |
| `0x18024E9B0` | `TaskMarkSets::CopyMarksToPageWithLog` | cópia página→página |
| `0x180251790` | `TaskMarkSets::PrepareMarksCachePage` | prepara cache de marcas |
| `0x1800C4100` | `GetMarkTypeFromPDFPlusKey` | mapeia chave PDF+ → tipo de marca |

## Pipeline reconstruído

```
mark set (.markset / template)
  ├─ PDF+ : FUN_180172550 → new PDFPlusCutMark (0x18013A8B0)
  │           └─ FUN_18017C5D0 (Position/Reference/Orientation/Repetition/LineTypes)
  └─ legado: createDynamicObject 0x180111410 → new CutMark(true) (0x180052340)
              └─ CutMark::parsePdfPropertiesDict 0x180052A50 (DM-CutMarkParams*)

aplicação na página
  TaskMarkSets::ApplyMarksFromSet 0x18024D3E0
    └─ CopyMarksToPageWithLog 0x18024E9B0 → conteúdo do mark set é copiado
  TaskMarkSets::ApplyRelevantMarkSets 0x18024D460 (separações, forms)

geometria
  PDFPlusCutMark::regenerateMarkImp 0x18013EE90
    ├─ GetReferenceBox 0x18013CB50 → Page::GetPageBox(page, PageBox)
    ├─ offset (variant quantidade/fórmula)
    └─ cos/sin/atan2 + InsertNewObjectOnTop (dentro de ActionGroupCreator/Expander)
  CutMark::regenerateMarkImp 0x180052CA0
    └─ PlaceCutMarkSymbol 0x180052820 (cópia do símbolo por canto)
```

## Vtables, COL e RTTI

Ver detalhe em [`DocumentMarks__vtables_rtti.md`](../../rag/evidence/F-001/ghidra/DocumentMarks__vtables_rtti.md).

- `PDFPlusCutMark` ListItem `0x1803231B0` (COL `0x18035F0F8`), Visitable `0x180323330` (COL `0x18035F1C0`)
- `CutMark` ListItem `0x180308BD8` (COL `0x1803463C8`), Visitable `0x180308D58` (COL `0x180346490`)
- Slots: `regenerateMarkImp` = **[29]**, `getRefBoxes` = [25], `getRefObjects` = [26],
  `getMarkType` = [12], `Clone` = [1]
- **Limitação:** Ghidra não gerou símbolos `??_R*`; e ICF faz um endereço ter vários nomes
  (ex.: `0x18001C700` = `CutMark::getRefBoxes` nos exports e `BarcodeMark::getRefBoxes` na
  vtable). Nome válido = nome do export PE.

## Strings de UI e persistência

Tabela completa em [`DocumentMarks__strings.md`](../../rag/evidence/F-001/ghidra/DocumentMarks__strings.md). Destaques:

| Endereço | Literal | Uso |
|---|---|---|
| `0x180308DD0` | `AIDynamicMarks-CutMark` | dispatch legado (`0x1801122FE`) |
| `0x180312B40` | `DynamicObject_PDFPlusCutMark` | `getMarkType` |
| `0x180327538` | `Cut Mark has invalid Orientation value` | exceção no parser `0x18017C5D0` |
| `0x180327560` | `Cut Mark has invalid Repetition value` | exceção no parser `0x18017C5D0` |
| `0x180308DF0` | ` Cut Mark update at \n` | log de debug em `CutMark::regenerateMarkImp` |
| `0x18033D550` | `DM-CutMarkParams-Offset` | persistência legada |
| `0x18033D568` | `DM-CutMarkParams-SymbolDefinition` | persistência legada |
| `0x18033D590` | `DM-CutMarkParams-Version` | persistência legada |
| `0x180323368` | `PDFPlusCutMark_Offset` | nome-base na fórmula de offset |
| `0x180326A08` | `DocumentMarks_CutMark_ReferenceID` | referência por ID |
| `0x180323180` | `PDFPlusCutMark_OriginalReferenceName` | referência original |

Box names (contexto): `Media Box` `0x180307620`, `Crop Box` `0x180307630`,
`Bleed Box` `0x180307640`, `Trim Box` `0x180307650`, `Art Box` (imediatamente após).

## Ponto aberto: `PageBox = 3` é TrimBox?

Analisado em [`Document__GetPageBox.md`](../../rag/evidence/F-001/ghidra/Document__GetPageBox.md).

- **Observado:** `ArtDoc::Page::GetPageBox` (`0x1800FAE70`) indexa o array por `PageBox`
  cru (stride `0x58`), com tabela de fallback `DAT_1802EF6D8`; o ctor grava **3**.
- **Observado:** ordem canônica do produto = Media, Crop, Bleed, **Trim**, Art
  (`FUN_1800453F0`, `page.boxes.*`).
- **Inferido (média):** `3 = TrimBox`, logo o default referencia a Trim Box.
- **Falta:** confirmação por captura de UI (inspetor de Cut Mark aberto no v250). Até lá,
  spec não deve elevar isso a fato.

## Cobertura e lacunas

- 10.672 funções identificadas; 87 funções de interesse exportadas em detalhe; 70
  descompiladas; 8 vtables lidas.
- **Não extraído:** geometria exata (comprimento/espessura das linhas por canto), semântica
  nominal de `Repetition = 2` e `Orientation = 1`, e o critério de seleção de ramo em
  `FUN_180172550` (função de ~105 KB).
- **Diff v240×v250:** apenas por strings/RTTI (mesmas chaves e mesmas lambdas de
  `regenerateMarkImp`). Não houve diff de função; nenhuma afirmação de comportamento
  idêntico entre versões deve ser feita além disso.

## Reprodução

```powershell
$env:JAVA_HOME = 'C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot'
$headless = 'H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat'
& $headless 'H:\Desktop\ArtPlus\tools\ghidra_projects' ArtProPlus `
  -process DocumentMarks.dll -noanalysis `
  -scriptPath 'H:\Desktop\ArtPlus\tools\ghidra_analysis\ghidra_scripts' `
  -postScript ExportMarksFocus.java -postScript ExportDecompile.java
```

`Document.dll` (para `GetPageBox`) está no projeto `ArtProPlus_PDFDocument`; usar
`DecompileAddr.java 0x1800FAE70`.
