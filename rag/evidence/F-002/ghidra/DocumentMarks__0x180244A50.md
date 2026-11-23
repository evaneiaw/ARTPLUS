---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::TaskMarkSets::ApplyRelevantMarkSetsWithReuse"
endereco: 0x180244A50
versao: 24.03.10017
confianca: media
xrefs: []
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x180244A50

## Identificacao lida no programa v240

- endereco: `0x180244a50`
- simbolo: `DocumentMarks::TaskMarkSets::ApplyRelevantMarkSetsWithReuse`
- assinatura: `void __thiscall ApplyRelevantMarkSetsWithReuse(Page * param_1, CloneStrategy * param_2, int param_3, bool param_4, bool param_5, RectangleBase<YAGL::MilliPointCoordinateSystem> * param_6)`
- corpo: `180244a50..180244d28` (729 bytes), convencao `__thiscall`, thunk=false, external=false
- parametros: 7
- referencias apontando para a entrada: 3 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Variante com reuso de clones -- **equivalente** de `ApplyRelevantMarkSets` quando ha
`CloneStrategy` disponivel. Assinatura:
`void ApplyRelevantMarkSetsWithReuse(Page&, CloneStrategy&, int flags, bool, bool, RectangleBase<MilliPoint>*)`.

Callees que caracterizam: `CloneStrategy::Clone`, `CopyMarksAsFormsToPage` (0x180042670),
`MakeFormsFromMarks`, `UpdateMarksOnPage`, `AdjustPageBoxes`, `GetDynamicMarksBox`,
`MoveExpandedMarks`, `GetPagesBegin`, `GetChangeTracker`, `~CloneStrategy`.

Leitura: clona os documentos de mark set com a estrategia fornecida, copia o resultado para a
pagina alvo como formas (`CopyMarksAsFormsToPage`), atualiza as marcas, ajusta caixas de
pagina com a bounding box recebida e move marcas expandidas. O retangulo `param_6` e a caixa
de referencia usada no ajuste.

## Chamadores (xrefs de chamada)

- nenhum chamador interno registrado (funcao de entrada/exportada; ver `refTo` do bruto)

## Chamadas diretas (17)

- `EXTERNAL:00000170 GetPagesBegin`
- `180016510 FUN_180016510`
- `EXTERNAL:00000219 AddOnTop`
- `180044500 FUN_180044500`
- `1800c82e0 AdjustPageBoxes`
- `180046550 MoveExpandedMarks`
- `EXTERNAL:00000168 GetContent`
- `180045c70 MakeFormsFromMarks`
- `1800316e0 GetChangeTracker`
- `EXTERNAL:0000010a Clone`
- `1800138d0 FUN_1800138d0`
- `180117f20 UpdateMarksOnPage`
- `EXTERNAL:0000017c GetDocument`
- `180044570 FUN_180044570`
- `180042670 CopyMarksAsFormsToPage`
- `1800c83f0 GetDynamicMarksBox`
- `1802cbfd0 __security_check_cookie`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- O corpo nao foi decompilado linha a linha para decidir a ordem exata Clone/Copy; a descricao vem da assinatura e do conjunto de callees.

## Confianca

`media` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
