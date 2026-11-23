---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::TaskMarkSets::ApplyRelevantMarkSets"
endereco: 0x180243F40
versao: 24.03.10017
confianca: alta
xrefs: []
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x180243F40

## Identificacao lida no programa v240

- endereco: `0x180243f40`
- simbolo: `DocumentMarks::TaskMarkSets::ApplyRelevantMarkSets`
- assinatura: `void __thiscall ApplyRelevantMarkSets(Page * param_1, int param_2, bool param_3, bool param_4, bool param_5, bool param_6)`
- corpo: `180243f40..180244a4d` (2824 bytes), convencao `__thiscall`, thunk=false, external=false
- parametros: 7
- referencias apontando para a entrada: 3 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Funcao central do fluxo de Mark Set -- **equivalente v240** do ID historico
`GHIDRA-DocumentMarks-0x18024D460` (v250 historico). Assinatura:
`void ApplyRelevantMarkSets(Page& page, int flags, bool b1, bool b2, bool b3, bool b4)`.

Sequencia observada no corpo (2824 bytes):

1. `DynamicMarksController::EnableUpdates(doc, false)` -- suspende atualizacao das marcas.
2. Para cada `Separation::Entry` em `this+0x10..0x18`, se `GetInkType` for 2 ou 3, chama
   `AddNormalizedInkHint(name, inkType)` (normalizacao de tintas especiais).
3. **Grupos de documentos**: `this+0x28` e sempre aplicado; `this+0x40` quando
   `(flags & 1) == 0`; `this+0x58` quando `(flags & 1) != 0`; `this+0x70` quando
   `flags == 1`; `this+0x88` quando `b1` (param_3) e verdadeiro. Para cada documento de cada
   grupo, `CopyMarksToPageWithLog(this, *GetPagesBegin(doc), page, !b4)`.
4. `DetectNormalizedInkTypes(pageContent, true, true)`; cria `InkCollector`, aplica visitor
   (`PageContent::Accept`), copia `Document::GetSeparationInfo` para um vetor local e repete a
   normalizacao de tintas sobre as entradas; para cada grupo efetivamente usado, faz
   `InkCollector::MergeUsedSeparations` e acumula `AddNormalizedInkHints`.
5. `Separation::FindOrAdd` de cada entrada de `this+0x10` no vetor acumulado;
   `Document::SetSeparationInfo(doc, ...)`; registra lambda no change tracker.
6. `UpdateMarksOnPage(page)`; compara a contagem de separacoes antes/depois via
   `FUN_180243bc0` e, se mudou, `MergeSeparationInfo` + `SetSeparationInfo` +
   `DynamicObjectController::SetAllNeedUpdate` + novo `UpdateMarksOnPage`.
7. Final: se `b3` (param_5) -> `GetDynamicMarksBox` + `AdjustPageBoxes(page, box)`;
   se `b4` (param_6) -> `MakeFormsFromMarks(page,false)`; sempre
   `MoveExpandedMarks(page, !b4)`.

Strings: nenhuma literal; mensagens vem de `CopyMarksToPageWithLog`.

## Chamadores (xrefs de chamada)

- nenhum chamador interno registrado (funcao de entrada/exportada; ver `refTo` do bruto)

## Chamadas diretas (42)

- `EXTERNAL:0000017c GetDocument`
- `18001be10 FUN_18001be10`
- `1800f3430 AddNormalizedInkHints`
- `EXTERNAL:000001fc GetInkType`
- `EXTERNAL:00000200 GetSeparationInfo`
- `18003a010 FUN_18003a010`
- `180016510 FUN_180016510`
- `18003f2b0 FUN_18003f2b0`
- `180046550 MoveExpandedMarks`
- `EXTERNAL:00000170 GetPagesBegin`
- `180023a60 FUN_180023a60`
- `EXTERNAL:0000023b GetDynamicObjects`
- `1800f4d00 DetectNormalizedInkTypes`
- `1800316e0 GetChangeTracker`
- `18001c310 FUN_18001c310`
- `EXTERNAL:000001a4 ~ConstVisitorBase`
- `EXTERNAL:00000235 GetList`
- `1800db8a0 InkCollector`
- `180082d70 EnableUpdates`
- `1800f3400 AddNormalizedInkHint`
- `EXTERNAL:0000016f GetInfoFlag`
- `180243bc0 FUN_180243bc0`
- `EXTERNAL:00000213 SetSeparationInfo`
- `EXTERNAL:00000261 Accept`
- `1800c83f0 GetDynamicMarksBox`
- `180084680 GetDynamicMarksController`
- `1800ec5f0 MergeSeparationInfo`
- `1802cbea4 free`
- `EXTERNAL:00000236 GetName`
- `EXTERNAL:00000168 GetContent`
- `1800c82e0 AdjustPageBoxes`
- `EXTERNAL:00000273 GetSeparations`
- `180035ab0 FUN_180035ab0`
- `180045c70 MakeFormsFromMarks`
- `180245380 CopyMarksToPageWithLog`
- `EXTERNAL:00000239 FindOrAdd`
- `180117f20 UpdateMarksOnPage`
- `1800138d0 FUN_1800138d0`
- `EXTERNAL:00000397 SetAllNeedUpdate`
- `EXTERNAL:000005ad _invalid_parameter_noinfo_noreturn`
- `1800dc190 MergeUsedSeparations`
- `1802cbfd0 __security_check_cookie`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- O mapeamento exato de cada offset de grupo (+0x28/+0x40/+0x58/+0x70/+0x88) para um tipo de mark set (DMK, extra, plate, cache) nao e nomeado no binario: e inferencia pelo uso e pelos setters do mesmo objeto.

## Confianca

`alta` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
