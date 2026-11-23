---
modulo: DocumentMarks.dll
funcao: DocumentMarks::BearerBar::updatePdfPropertiesDictImp
endereco: 0x18001E9A0
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x180020950
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18001E9A0

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x180020950`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18001E9A0`
- simbolo: `DocumentMarks::BearerBar::updatePdfPropertiesDictImp`
- assinatura: `void updatePdfPropertiesDictImp(BearerBar * this, Dictionary * param_1)`
- corpo: `0x18001E9A0`..`0x18001ED7E` (985 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x180020950`

## O que faz

Escritor virtual do dicionario DM-BearerBarParams: grava sempre Version = 2, Width/Extend/Offset convertidos mp -> mm e Location; nao grava IsVertical. O container 0x1800208D0 nao e este escritor; o escritor e o membro virtual que entra na vtable de BearerBar.

String-chave de Bearer Bar: DM-BearerBarParams, DM-BearerBarParams-Width/Extend/Offset/Location/Version

## Chamadores (xrefs de chamada)

- nenhum chamador direto no programa (a funcao e virtual, exportada por vtable, ou so tem xref de dados)

Chamadas diretas (10):

- `EXTERNAL:000005ad API-MS-WIN-CRT-RUNTIME-L1-1-0.DLL::_invalid_parameter_noinfo_noreturn`
- `1802cbea4 API-MS-WIN-CRT-HEAP-L1-1-0.DLL::free`
- `EXTERNAL:000001aa DOCUMENT.DLL::ArtDoc::Dictionary::AddDictionary`
- `EXTERNAL:000001e1 DOCUMENT.DLL::ArtDoc::Dictionary::AddFloat`
- `1802cbfd0 __security_check_cookie`
- `180097af0 DocumentMarks::DynamicObject::updatePdfPropertiesDictImp`
- `EXTERNAL:000001a8 DOCUMENT.DLL::ArtDoc::Dictionary::AddInteger`
- `18000d740 FUN_18000d740`
- `EXTERNAL:000001a7 DOCUMENT.DLL::ArtDoc::Dictionary::~Dictionary`
- `EXTERNAL:000001af DOCUMENT.DLL::ArtDoc::Dictionary::Dictionary`

## Strings referenciadas no corpo

- `18032fda8 "DM-BearerBarParams"`
- `180330128 "DM-BearerBarParams-Width"`
- `180330148 "DM-BearerBarParams-Extend"`
- `180330168 "DM-BearerBarParams-Offset"`
- `1803301a8 "DM-BearerBarParams-Location"`
- `1803301c8 "DM-BearerBarParams-Version"`

## Pseudocodigo (inicio; integral no bruto)

```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: virtual void __cdecl DocumentMarks::BearerBar::updatePdfPropertiesDictImp(class
   ArtDoc::Dictionary & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::BearerBar::updatePdfPropertiesDictImp(BearerBar *this,Dictionary *param_1)

{
  int iVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  Dictionary *pDVar5;
/* ... 163 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001E9A0.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
