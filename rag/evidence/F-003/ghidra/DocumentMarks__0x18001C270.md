---
modulo: DocumentMarks.dll
funcao: DocumentMarks::BearerBar::BearerBar
endereco: 0x18001C270
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x18001E3C0
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18001C270

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x18001E3C0`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18001C270`
- simbolo: `DocumentMarks::BearerBar::BearerBar`
- assinatura: `undefined BearerBar(BearerBar * this, bool param_1)`
- corpo: `0x18001C270`..`0x18001C2CC` (93 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x18001E3C0`

## O que faz

Construtor legado publico BearerBar(bool). Chama DynamicMark(this, param_1, 0xFD), instala as vftables e aplica os defaults: +0x758 = 0x40CBAE9D3A74E9D4 (double 14173.228346456694 mp = 5.000 mm), +0x768 = 0, +0x778 = 0 e +0x780 = 3. E o caminho de criacao usado por createDynamicObject (0x18010E0F0) ao reconhecer AIDynamicMarks-BearerBar; a chamada esta em 0x18010E4CE.

## Chamadores (xrefs de chamada)

- `18010e0f0 FUN_18010e0f0`

Chamadas diretas (1):

- `18006bd80 DocumentMarks::DynamicMark::DynamicMark`

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* public: __cdecl DocumentMarks::BearerBar::BearerBar(bool) __ptr64 */

BearerBar * __thiscall DocumentMarks::BearerBar::BearerBar(BearerBar *this,bool param_1)

{
                    /* 0x1c270  168  ??0BearerBar@DocumentMarks@@QEAA@_N@Z */
  DynamicMark::DynamicMark((DynamicMark *)this,param_1,0xfd);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this + 0x758) = 0x40cbae9d3a74e9d4;
  *(undefined8 *)(this + 0x768) = 0;
  *(undefined8 *)(this + 0x778) = 0;
  *(undefined4 *)(this + 0x780) = 3;
  return this;
/* ... 1 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001C270.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
