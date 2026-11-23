---
modulo: DocumentMarks.dll
funcao: DocumentMarks::PDFPlusBearerBar::ValidateAnchors
endereco: 0x18012E9C0
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x180131E30
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18012E9C0

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x180131E30`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18012E9C0`
- simbolo: `DocumentMarks::PDFPlusBearerBar::ValidateAnchors`
- assinatura: `void ValidateAnchors(PDFPlusBearerBar * this)`
- corpo: `0x18012E9C0`..`0x18012EA3D` (126 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x180131E30`

## O que faz

Normaliza o par de anchors antes da geracao: com Direction == 0 aplica YAGL::ToVertical e com Direction == 1 aplica YAGL::ToHorizontal; so chama MarkPosition::setAnchors (base +0x390) quando algum anchor realmente mudou. Nao referencia strings.

## Chamadores (xrefs de chamada)

- `18012f6e0 DocumentMarks::PDFPlusBearerBar::regenerateMarkImp`

Chamadas diretas (3):

- `180108450 DocumentMarks::MarkPosition::setAnchors`
- `EXTERNAL:000004ae YAGL.DLL::YAGL::ToVertical`
- `EXTERNAL:000004af YAGL.DLL::YAGL::ToHorizontal`

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* protected: void __cdecl DocumentMarks::PDFPlusBearerBar::ValidateAnchors(void) __ptr64 */

void __thiscall DocumentMarks::PDFPlusBearerBar::ValidateAnchors(PDFPlusBearerBar *this)

{
  Anchor AVar1;
  Anchor AVar2;
  
                    /* 0x12e9c0  1714  ?ValidateAnchors@PDFPlusBearerBar@DocumentMarks@@IEAAXXZ */
  if (*(int *)(this + 0x770) == 0) {
    AVar1 = YAGL::ToVertical(*(Anchor *)(this + 0x418));
    AVar2 = YAGL::ToVertical(*(Anchor *)(this + 0x41c));
  }
  else {
/* ... 11 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012E9C0.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
