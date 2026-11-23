---
modulo: DocumentMarks.dll
funcao: DocumentMarks::PDFPlusBearerBar::UpdateSizeReference
endereco: 0x18012E950
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x180131DC0
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18012E950

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x180131DC0`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18012E950`
- simbolo: `DocumentMarks::PDFPlusBearerBar::UpdateSizeReference`
- assinatura: `void UpdateSizeReference(PDFPlusBearerBar * this)`
- corpo: `0x18012E950`..`0x18012E98C` (61 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x180131DC0`

## O que faz

Correcao silenciosa de SizeReference: switch sobre +0x7F8; valores 1..4 sao zerados quando Direction == 0 e valores 5..8 quando Direction == 1. Esta e a regra que a R5 da spec descreve ao contrario (ver o bloqueio correspondente no manifest). Nao referencia strings.

## Chamadores (xrefs de chamada)

- `1800b0210 FUN_1800b0210`
- `18012f6e0 DocumentMarks::PDFPlusBearerBar::regenerateMarkImp`

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* public: void __cdecl DocumentMarks::PDFPlusBearerBar::UpdateSizeReference(void) __ptr64 */

void __thiscall DocumentMarks::PDFPlusBearerBar::UpdateSizeReference(PDFPlusBearerBar *this)

{
  bool bVar1;
  
                    /* 0x12e950  1713  ?UpdateSizeReference@PDFPlusBearerBar@DocumentMarks@@QEAAXXZ
                        */
  switch(*(undefined4 *)(this + 0x7f8)) {
  default:
    goto switchD_18012e96e_caseD_0;
  case 1:
  case 2:
/* ... 16 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012E950.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
