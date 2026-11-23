---
modulo: DocumentMarks.dll
funcao: DocumentMarks::BearerBar::Clone
endereco: 0x18001CC10
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x18001EDA0
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18001CC10

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x18001EDA0`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18001CC10`
- simbolo: `DocumentMarks::BearerBar::Clone`
- assinatura: `BearerBar * Clone(BearerBar * this, CloneStrategy * param_1)`
- corpo: `0x18001CC10`..`0x18001CC5A` (75 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x18001EDA0`

## O que faz

Clone virtual. Aloca 0x788 bytes (FUN_1802CBE68, operator new do runtime do binario), chama o construtor de clone 0x18001C200 e devolve o ponteiro; devolve nullptr se a alocacao falhar. E o unico chamador do ctor de clone.

## Chamadores (xrefs de chamada)

- nenhum chamador direto no programa (a funcao e virtual, exportada por vtable, ou so tem xref de dados)

Chamadas diretas (2):

- `18001c200 DocumentMarks::BearerBar::BearerBar`
- `1802cbe68 FUN_1802cbe68`

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* public: virtual class DocumentMarks::BearerBar * __ptr64 __cdecl
   DocumentMarks::BearerBar::Clone(class ArtDoc::CloneStrategy & __ptr64)const __ptr64 */

BearerBar * __thiscall DocumentMarks::BearerBar::Clone(BearerBar *this,CloneStrategy *param_1)

{
  BearerBar *pBVar1;
  
                    /* 0x1cc10  851
                       ?Clone@BearerBar@DocumentMarks@@UEBAPEAV12@AEAVCloneStrategy@ArtDoc@@@Z */
  pBVar1 = (BearerBar *)FUN_1802cbe68(0x788);
  if (pBVar1 == (BearerBar *)0x0) {
    return (BearerBar *)0x0;
  }
/* ... 3 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001CC10.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
