---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::MakeFormsFromMarks"
endereco: 0x180045C70
versao: 24.03.10017
confianca: media
xrefs: ["0x180243F40", "0x180246AB0", "0x1802475E0", "0x180244A50"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x180045C70

## Identificacao lida no programa v240

- endereco: `0x180045c70`
- simbolo: `DocumentMarks::MakeFormsFromMarks`
- assinatura: `bool __cdecl MakeFormsFromMarks(Page * param_1, bool param_2)`
- corpo: `180045c70..18004615e` (1261 bytes), convencao `__cdecl`, thunk=false, external=false
- parametros: 2
- referencias apontando para a entrada: 13 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Converte as marcas dinamicas de uma pagina em **formas estaticas** ("make forms from
marks"). E chamada por `ApplyRelevantMarkSets` (0x180243F40),
`ApplyRelevantMarkSetsWithReuse` (0x180244A50), `MakeFormsFromCachedMarks` (0x180246AB0) e
`PrepareMarksCache` (0x1802475E0).

Callees que caracterizam a operacao (34 no total): `DocumentEdit::MakeForm`,
`ArtDoc::Group`, `SetTransformation`/`GetTransformation`, `GetBoundingBox`, `InsertBefore`,
`AddOnTop`, `ExtractFromParent`, `ObjectWillBeDeleted`, `GetActionList`, `GetProperties`,
`SetTransparency`/`GetTransparency`, `makeStatic` (0x1800961b0) e
`~VisitorBase`/`VisitorBase` (visitor sobre o conteudo da pagina).

Leitura: percorre o conteudo da pagina via visitor, para cada objeto dinamico gera uma forma
(`MakeForm`), agrupa/posiciona pela transformacao e pela bounding box, marca o objeto original
como removivel, e aplica transparencia herdada. Retorna bool (sucesso).

## Chamadores (xrefs de chamada)

- `180243f40 ApplyRelevantMarkSets`
- `180246ab0 MakeFormsFromCachedMarks`
- `1802475e0 PrepareMarksCache`
- `180244a50 ApplyRelevantMarkSetsWithReuse`

## Chamadas diretas (33)

- `EXTERNAL:0000017c GetDocument`
- `EXTERNAL:00000248 SetTransparency`
- `EXTERNAL:00000210 GetBoundingBox`
- `180048840 FUN_180048840`
- `180016510 FUN_180016510`
- `EXTERNAL:0000024a Group`
- `EXTERNAL:00000244 ObjectWillBeDeleted`
- `EXTERNAL:00000246 SetTransformation`
- `EXTERNAL:0000023b GetDynamicObjects`
- `EXTERNAL:00000240 InsertBefore`
- `EXTERNAL:000000c9 MakeForm`
- `EXTERNAL:0000024c AddOnTop`
- `18003b9e0 FUN_18003b9e0`
- `EXTERNAL:00000242 GetProperties`
- `EXTERNAL:00000247 GetTransformation`
- `1800961b0 makeStatic`
- `EXTERNAL:000001a6 GetContent`
- `18003ae20 FUN_18003ae20`
- `1802cbea4 free`
- `EXTERNAL:00000166 ~VisitorBase`
- `1802cbe68 FUN_1802cbe68`
- `EXTERNAL:00000168 GetContent`
- `EXTERNAL:00000241 ExtractFromParent`
- `18010ffa0 FUN_18010ffa0`
- `1802b3a02 SetName`
- `180016520 FUN_180016520`
- `EXTERNAL:00000232 Accept`
- `EXTERNAL:00000207 GetActionList`
- `EXTERNAL:00000249 GetTransparency`
- `EXTERNAL:00000228 Clear`
- `EXTERNAL:00000167 VisitorBase`
- `EXTERNAL:000005ad _invalid_parameter_noinfo_noreturn`
- `1802cbfd0 __security_check_cookie`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- Sem simbolo nos helpers internos; a ordem exata de MakeForm/Group por objeto nao foi seguida linha a linha -- descricao por conjunto de callees e assinatura.

## Confianca

`media` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
