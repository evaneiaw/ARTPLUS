---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::TaskMarkSets::PrepareMarksCachePage"
endereco: 0x180248720
versao: 24.03.10017
confianca: alta
xrefs: ["0x1802475E0", "0x180246C70"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x180248720

## Identificacao lida no programa v240

- endereco: `0x180248720`
- simbolo: `DocumentMarks::TaskMarkSets::PrepareMarksCachePage`
- assinatura: `vector<ArtDoc::Separation::Entry,std::allocator<ArtDoc::Separation::Entry>_> __thiscall PrepareMarksCachePage(Page * param_1, vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_> * param_2, vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_> * param_3, vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_> * param_4, bool param_5, bool param_6)`
- corpo: `180248720..180248d2b` (1547 bytes), convencao `__thiscall`, thunk=false, external=false
- parametros: 7
- referencias apontando para a entrada: 12 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Prepara o cache de marcas de **uma pagina** -- **equivalente v240** do ID historico
`GHIDRA-DocumentMarks-0x180251790` (v250 historico). Retorna
`std::vector<ArtDoc::Separation::Entry>` (as separacoes usadas na pagina).

Assinatura v240: `PrepareMarksCachePage(Page&, vector<unique_ptr<Document>> const& a,
vector<unique_ptr<Document>> const& b, vector<unique_ptr<Document>> const& c, bool, bool)`.

Fluxo observado:
1. Se `param_6` (ultimo bool): `DeleteMarks(page)`, `DeleteExpandedMarks(page)` e
   `RemoveUnusedSeparationsFromPage(page)`.
2. Se o bool em `in_stack_00000040`: `MoveExpandedMarks(page,false)`.
3. `DynamicMarksController::EnableUpdates(doc,false)` e montagem da informacao de separacoes:
   parte de `Document::GetSeparationInfo(doc)` e acumula por tres vezes
   `FUN_180246b40(vec, ac, docVector)` (um para cada vetor de documentos recebido), depois
   `Separation::FindOrAdd` para cada entrada de `this+0x10..0x18` e
   `Document::SetSeparationInfo`.
4. Para cada documento dos vetores `a` e `c` (e do terceiro), copia a primeira pagina para a
   pagina alvo com `CopyMarksToPageWithLog(this, *GetPagesBegin(doc), page, false)`.
5. Consolida separacoes em `this+0x10` e retorna o vetor.

Chamada por `PrepareMarksCache(Document&)` (0x180246C70) e por
`PrepareMarksCache(SheetIteratorProxy&)` (0x1802475E0).

## Chamadores (xrefs de chamada)

- `1802475e0 PrepareMarksCache`
- `180246c70 PrepareMarksCache`

## Chamadas diretas (31)

- `18001be10 FUN_18001be10`
- `EXTERNAL:00000235 GetList`
- `EXTERNAL:00000200 GetSeparationInfo`
- `180246b40 FUN_180246b40`
- `18003a010 FUN_18003a010`
- `180043340 DeleteMarks`
- `180046550 MoveExpandedMarks`
- `EXTERNAL:0000023b GetDynamicObjects`
- `EXTERNAL:00000239 FindOrAdd`
- `180043140 DeleteExpandedMarks`
- `1800ecd80 RemoveUnusedSeparationsFromPage`
- `180243bc0 FUN_180243bc0`
- `180082d70 EnableUpdates`
- `EXTERNAL:00000397 SetAllNeedUpdate`
- `EXTERNAL:00000170 GetPagesBegin`
- `EXTERNAL:00000213 SetSeparationInfo`
- `1802cbea4 free`
- `EXTERNAL:00000228 Clear`
- `EXTERNAL:000005ad _invalid_parameter_noinfo_noreturn`
- `EXTERNAL:00000273 GetSeparations`
- `EXTERNAL:00000168 GetContent`
- `180084680 GetDynamicMarksController`
- `18003f2b0 FUN_18003f2b0`
- `EXTERNAL:00000207 GetActionList`
- `180035ab0 FUN_180035ab0`
- `180245380 CopyMarksToPageWithLog`
- `1800ec5f0 MergeSeparationInfo`
- `180117f20 UpdateMarksOnPage`
- `EXTERNAL:0000017c GetDocument`
- `1800e6940 FUN_1800e6940`
- `1802cbfd0 __security_check_cookie`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- Os tres vetores de documentos recebem nomes neutros (a/b/c) porque o binario nao identifica o papel de cada um (mark set normal, extra, cache).

## Confianca

`alta` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
