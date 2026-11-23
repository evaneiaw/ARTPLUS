---
modulo: DocumentMarks.dll
funcao: FUN_18010E0F0 (createDynamicObject legado)
endereco: 0x18010E0F0
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x180111410
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18010E0F0

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x180111410`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18010E0F0`
- simbolo: `FUN_18010e0f0`
- assinatura: `undefined FUN_18010e0f0()`
- corpo: `0x18010E0F0`..`0x18010FD42` (7239 bytes), convencao `unknown`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x180111410`

## O que faz

Criador 'createDynamicObject' da biblioteca legada (corpo de 7239 bytes). Despacha pelo literal de tipo lido do dicionario: compara 24 bytes com AIDynamicMarks-BearerBar (0x1802FA140) e, no caso Bearer Bar, faz operator new(0x788) e chama o ctor 0x18001C270 em 0x18010E4CE, seguido de setPdfPropertiesDict. Trata tambem BarcodeMark, CornerMark, CustomMark, CutMark, GradationStrip, GridMark e UniPointText/UniAreaText.

String-chave de Bearer Bar: AIDynamicMarks-BearerBar (0x1802FA140), referenciada em 0x18010E474; dezenas de outros AIDynamicMarks-*

## Chamadores (xrefs de chamada)

- nenhum chamador direto no programa (a funcao e virtual, exportada por vtable, ou so tem xref de dados)

Chamadas diretas (47):

- `1802ccf92 VCRUNTIME140.DLL::memcmp`
- `18027d890 DocumentMarks::VDPBarcode::VDPBarcode`
- `1800d4560 DocumentMarks::ImageMark::ImageMark`
- `18024ec10 DocumentMarks::TextMark::TextMark`
- `180063a30 FUN_180063a30`
- `EXTERNAL:00000267 DOCUMENT.DLL::ArtDoc::FindModule`
- `180115f40 DocumentMarks::MarksModule::GetFeatures`
- `180019ae0 DocumentMarks::BarcodeMark::BarcodeMark`
- `180051f90 DocumentMarks::CutMark::CutMark`
- `EXTERNAL:0000036b DOCUMENT.DLL::ArtDoc::MarkReader::GetPropertiesAsDictionary`
- ... mais 37 no bruto

## Strings referenciadas no corpo

- `1802f9c60 "AIDynamicMarks-BarcodeMark"`
- `1802fa140 "AIDynamicMarks-BearerBar"`
- `1802fd108 "AIDynamicMarks-CornerMark"`
- `1802fd400 "AIDynamicMarks-CustomMark"`
- `1802fdc58 "AIDynamicMarks-CutMark"`
- `1802ff518 "UniPointText"`
- `1802ff538 "UniAreaText"`
- `1803029a4 "markid"`
- `1803068c8 "Barcode"`
- `18030da10 "AIDynamicMarks-GradationStrip"`
- `18030e000 "AIDynamicMarks-GridMark"`
- `18030ec68 "AIDynamicMarks-ImageMark"`
- `180313050 "ImageMono"`
- `180313060 "ImageColor"`
- `180313070 "ImagePDF"`
- `180313bb0 "createDynamicObject "`
- `180313bc8 "createDynamicObject params: "`
- `18032fd98 "DM-TextParams"`
- `180330648 "DM-TextParams-Version"`
- `180330698 "DM-TextParams-Area-Width"`
- `1803306b8 "DM-TextParams-Area-Height"`

## Pseudocodigo (inicio; integral no bruto)

```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * FUN_18010e0f0(MarkReader *param_1,undefined8 *param_2)

{
  longlong *plVar1;
  int *piVar2;
  void *pvVar3;
  longlong *plVar4;
  bool bVar5;
  uint uVar6;
  int iVar7;
  Dictionary *this;
/* ... 1165 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18010E0F0.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
