---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::TaskMarkSets::PrepareMarksCache"
endereco: 0x180246C70
versao: 24.03.10017
confianca: media
xrefs: []
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x180246C70

## Identificacao lida no programa v240

- endereco: `0x180246c70`
- simbolo: `DocumentMarks::TaskMarkSets::PrepareMarksCache`
- assinatura: `bool __thiscall PrepareMarksCache(Document * param_1, bool param_2, path * param_3)`
- corpo: `180246c70..1802475d2` (2400 bytes), convencao `__thiscall`, thunk=false, external=false
- parametros: 4
- referencias apontando para a entrada: 3 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Prepara o **documento de cache** de marcas a partir de um documento
(`PrepareMarksCache(Document&, bool, path const&)`), sobrecarga com `Document&`
(a outra sobrecarga, 0x1802475E0, recebe `SheetIteratorProxy&`).

Callees que caracterizam: `ClonePage`, `CloneStrategy`, `InsertPage`, `Create`,
`SetFilePathForDocument`, `SetInfoFlag`, `SetOutputIntent`/`GetOutputIntent`,
`OutputIntent`, `GetUsedSeparationsFromDocument`, `SetSeparationInfo`/`GetSeparationInfo`,
`RemoveStaticContent`, `StoreCurrentPageBoxes`, `MakeFormsFromCachedMarks`,
`CanCacheMarks`, `PrepareMarksCachePage` (0x180248720), `GetNumberOfPages`,
`SetInfoFlag`, `~Document`, `~CloneStrategy`.

Leitura: cria um documento novo, clona paginas com a estrategia, propaga separacoes usadas e
output intent, aplica as formas geradas (`MakeFormsFromCachedMarks`), e para cada pagina chama
`PrepareMarksCachePage(...)` para copiar as marcas e consolidar separacoes. `CanCacheMarks`
decide se o cache e valido.

## Chamadores (xrefs de chamada)

- nenhum chamador interno registrado (funcao de entrada/exportada; ver `refTo` do bruto)

## Chamadas diretas (34)

- `EXTERNAL:0000022a ~CloneStrategy`
- `EXTERNAL:000000ec InsertPage`
- `EXTERNAL:00000211 OutputIntent`
- `EXTERNAL:0000020e ~Entry`
- `180248720 PrepareMarksCachePage`
- `EXTERNAL:000000e9 Create`
- `EXTERNAL:00000200 GetSeparationInfo`
- `18003a010 FUN_18003a010`
- `EXTERNAL:00000216 SetOutputIntent`
- `EXTERNAL:00000229 CloneStrategy`
- `EXTERNAL:0000020c GetPageBox`
- `1802493f0 RemoveStaticContent`
- `1800eab80 GetUsedSeparationsFromDocument`
- `EXTERNAL:00000163 SetInfoFlag`
- `EXTERNAL:00000162 SetFilePathForDocument`
- `1802495b0 StoreCurrentPageBoxes`
- `EXTERNAL:0000016f GetInfoFlag`
- `1800ea320 CreateObjectWithAllColorsOnPage`
- `EXTERNAL:00000170 GetPagesBegin`
- `1802cbea4 free`
- `EXTERNAL:00000213 SetSeparationInfo`
- `EXTERNAL:00000171 GetPagesEnd`
- `EXTERNAL:0000016d ~Document`
- `EXTERNAL:000005ad _invalid_parameter_noinfo_noreturn`
- `EXTERNAL:00000341 GetNumberOfPages`
- `EXTERNAL:00000215 GetOutputIntent`
- `EXTERNAL:00000208 GetProperties`
- `180246ab0 MakeFormsFromCachedMarks`
- `180242f20 FUN_180242f20`
- `180035ab0 FUN_180035ab0`
- `1802ccf92 memcmp`
- `1802ccf68 __std_type_info_compare`
- `EXTERNAL:00000234 ClonePage`
- `180114b00 CanCacheMarks`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- Sem simbolo nos helpers internos; ordem exata ClonePage/InsertPage por pagina nao foi seguida linha a linha.

## Confianca

`media` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
