---
modulo: DocumentMarks.dll
funcao: DocumentMarks::BearerBar::BearerBar
endereco: 0x18001C200
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x18001E350
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18001C200

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x18001E350`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18001C200`
- simbolo: `DocumentMarks::BearerBar::BearerBar`
- assinatura: `undefined BearerBar(BearerBar * this, BearerBar * param_1, CloneStrategy * param_2)`
- corpo: `0x18001C200`..`0x18001C26D` (110 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x18001E350`

## O que faz

Construtor de clone (protected). Delega a copia base a DynamicMark::DynamicMark(this, const&, CloneStrategy&), reinstala as duas vftables (ArtDoc::Detail::ListItem<ArtDoc::ContentObject> em +0x0 e ArtDoc::Visitable em +0x20) e copia os campos proprios da classe: +0x750, +0x758, +0x760, +0x768, +0x770, +0x778 e o int em +0x780. Nao referencia string alguma.

## Chamadores (xrefs de chamada)

- `18001cc10 DocumentMarks::BearerBar::Clone`

Chamadas diretas (1):

- `18006b5c0 DocumentMarks::DynamicMark::DynamicMark`

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* protected: __cdecl DocumentMarks::BearerBar::BearerBar(class DocumentMarks::BearerBar const &
   __ptr64,class ArtDoc::CloneStrategy & __ptr64) __ptr64 */

BearerBar * __thiscall
DocumentMarks::BearerBar::BearerBar(BearerBar *this,BearerBar *param_1,CloneStrategy *param_2)

{
  undefined8 uVar1;
  
                    /* 0x1c200  167
                       ??0BearerBar@DocumentMarks@@IEAA@AEBV01@AEAVCloneStrategy@ArtDoc@@@Z */
  DynamicMark::DynamicMark((DynamicMark *)this,(DynamicMark *)param_1,param_2);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
/* ... 12 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001C200.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
