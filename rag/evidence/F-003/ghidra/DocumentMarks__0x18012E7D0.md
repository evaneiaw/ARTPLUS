---
modulo: DocumentMarks.dll
funcao: DocumentMarks::PDFPlusBearerBar::UpdateDirection
endereco: 0x18012E7D0
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x180131C40
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18012E7D0

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x180131C40`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18012E7D0`
- simbolo: `DocumentMarks::PDFPlusBearerBar::UpdateDirection`
- assinatura: `void UpdateDirection(PDFPlusBearerBar * this)`
- corpo: `0x18012E7D0`..`0x18012E830` (97 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x180131C40`

## O que faz

Deriva a Direction a partir dos dois anchors em +0x418/+0x41C: aplica YAGL::ToVertical aos dois e grava 0 em +0x770 quando nenhum muda; caso contrario grava 1. Nao referencia strings.

## Chamadores (xrefs de chamada)

- `18012f6e0 DocumentMarks::PDFPlusBearerBar::regenerateMarkImp`

Chamadas diretas (1):

- `EXTERNAL:000004ae YAGL.DLL::YAGL::ToVertical`

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* private: void __cdecl DocumentMarks::PDFPlusBearerBar::UpdateDirection(void) __ptr64 */

void __thiscall DocumentMarks::PDFPlusBearerBar::UpdateDirection(PDFPlusBearerBar *this)

{
  Anchor AVar1;
  Anchor AVar2;
  
                    /* 0x12e7d0  1688  ?UpdateDirection@PDFPlusBearerBar@DocumentMarks@@AEAAXXZ */
  AVar1 = YAGL::ToVertical(*(Anchor *)(this + 0x418));
  AVar2 = YAGL::ToVertical(*(Anchor *)(this + 0x41c));
  if ((*(Anchor *)(this + 0x418) == AVar1) && (*(Anchor *)(this + 0x41c) == AVar2)) {
    *(undefined4 *)(this + 0x770) = 0;
    return;
/* ... 4 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012E7D0.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
