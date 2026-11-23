---
modulo: DocumentMarks.dll
funcao: FUN_1801652B0 (fabricante do PDFPlusBearerBar)
endereco: 0x1801652B0
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x18016F250
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x1801652B0

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x18016F250`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x1801652B0`
- simbolo: `FUN_1801652b0`
- assinatura: `undefined FUN_1801652b0()`
- corpo: `0x1801652B0`..`0x18016531D` (110 bytes), convencao `unknown`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x18016F250`

## O que faz

Fabrica do PDFPlusBearerBar: operator new(0x858), transfere o shared_ptr<FormPaint const> do chamador (zerando o par de ponteiros do chamador) e chama o ctor 0x18012C640. Devolve o objeto pelo primeiro parametro. Nao referencia strings.

## Chamadores (xrefs de chamada)

- `1801683e0 FUN_1801683e0`

Chamadas diretas (2):

- `18012c640 DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar`
- `1802cbe68 FUN_1802cbe68`

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
undefined8 * FUN_1801652b0(undefined8 *param_1,undefined8 *param_2)

{
  PDFPlusBearerBar *pPVar1;
  undefined8 uVar2;
  undefined8 local_20;
  undefined8 local_18;
  
  uVar2 = 0;
  pPVar1 = (PDFPlusBearerBar *)FUN_1802cbe68(0x858);
  if (pPVar1 != (PDFPlusBearerBar *)0x0) {
    local_20 = *param_2;
    local_18 = param_2[1];
    *param_2 = 0;
/* ... 6 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_1801652B0.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
