---
modulo: DocumentMarks.dll
funcao: FUN_18016FA10 (parser Position do PDF+)
endereco: 0x18016FA10
versao: 24.03.10017
confianca: media
id_historico: GHIDRA-DocumentMarks-0x180179DA0
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18016FA10

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x180179DA0`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18016FA10`
- simbolo: `FUN_18016fa10`
- assinatura: `undefined FUN_18016fa10()`
- corpo: `0x18016FA10`..`0x18016FF8C` (1403 bytes), convencao `unknown`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x180179DA0`

## O que faz

Parser de Position do PDF+: recebe GADict, ContentObject, um terceiro argumento e um double; le as chaves Position, Offset, SourceAnchor, ReferenceAnchor, Reference, ReferenceID e ObjectID, aplica o resultado no ContentObject e lanca a excecao literal 'Vertical offset in bearer bar not supported.' quando o offset vertical e usado num Bearer Bar.

String-chave de Bearer Bar: Position, Offset, SourceAnchor, ReferenceAnchor, Reference, ReferenceID, ObjectID e 'Vertical offset in bearer bar not supported.'

## Chamadores (xrefs de chamada)

- `1801683e0 FUN_1801683e0`

Chamadas diretas (33):

- `EXTERNAL:00000472 BASICFRAMEWORKCORELAYER.DLL::GName::GName`
- `180011420 FUN_180011420`
- `EXTERNAL:00000429 PDFACCESSLAYER.DLL::GADict::GetName`
- `EXTERNAL:00000434 PDFACCESSLAYER.DLL::GAName::operator==`
- `EXTERNAL:000003a6 DOCUMENT.DLL::ArtDocGlue::PDFConverters::UTF8String`
- `18017aac0 FUN_18017aac0`
- `18001e750 DocumentMarks::PDFPlusBearerBar::SetOffset`
- `EXTERNAL:000003f9 PDFACCESSLAYER.DLL::GAObject::~GAObject`
- `18012e790 DocumentMarks::PDFPlusBearerBar::SetReferenceObject`
- `EXTERNAL:0000041f PDFACCESSLAYER.DLL::GADict::GADict`
- ... mais 23 no bruto

## Strings referenciadas no corpo

- `1803126d0 "SourceAnchor"`
- `180312740 "Reference"`
- `180312788 "ObjectID"`
- `180312798 "ReferenceID"`
- `1803127a8 "ReferenceAnchor"`
- `1803127b8 "Offset"`
- `18031a378 "Position"`
- `18031ad78 "Vertical offset in bearer bar not supported."`

## Pseudocodigo (inicio; integral no bruto)

```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_18016fa10(GADict *param_1,ContentObject *param_2,undefined8 param_3,double param_4)

{
  void *pvVar1;
  bool bVar2;
  Anchor AVar3;
  Anchor AVar4;
  undefined8 uVar5;
  GAObject *this;
  Properties *pPVar6;
  variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer> *pvVar7;
  GAArray *pGVar8;
/* ... 155 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`media` - equivalencia estrutural: o parser de Position foi dividido na v240 (Position/Offset aqui, Extends/Reference de tamanho em 0x180166B70) e o simbolo nao foi recuperado; a identificacao vem das chaves lidas e do literal de erro.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18016FA10.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
