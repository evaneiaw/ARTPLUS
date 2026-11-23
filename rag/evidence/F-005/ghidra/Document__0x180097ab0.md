---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x180097ab0
nome: ArtDoc::Document::InsertPage(RectangleBase const&, indirect_iterator)
endereco: 0x180097ab0
confianca: alta
xrefs: [0x180378be4, 0x18041c7b4]
strings: []
---

# ArtDoc::Document::InsertPage (overload por iterator)

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`).
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs6.txt` (secao `## FN 180097ab0`).
- Simbolo demangled:
  `?InsertPage@Document@ArtDoc@@QEAA?AV?$indirect_iterator@...@iterators@boost@@
  AEBV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@V?$indirect_iterator@...@@@Z`

## Assinatura observada
`indirect_iterator __thiscall InsertPage(Document *this,
YAGL::RectangleBase<YAGL::MilliPointCoordinateSystem> const& box,
boost::iterators::indirect_iterator position)`

## O que faz (observado)
Mesmo contrato do overload `0x180097960`, mas a posicao de insercao vem de um iterator
(insercao antes da pagina apontada):
1. `SwitchToWorkingFile(this)`.
2. Calcula o indice pelo iterator recebido e valida a posicao (`FUN_180095880`).
3. Aloca 0x248 bytes e constroi `ArtDoc::Page::Page` (@`0x1800f95a0`).
4. Insere o `unique_ptr<Page>` no vetor de paginas (`FUN_18009dce0`) e devolve o iterator.
5. `ArtDoc::ContentTracker::AddPageToDocument` (@`0x180083f80`, chamada em `0x180097b9a`),
   `ArtDoc::Page::SetPart`, `ArtDoc::Parts::InsertPageIndex`.

## Chamadas de saida confirmadas
- `0x1800f95a0` ArtDoc::Page::Page
- `0x180083f80` ArtDoc::ContentTracker::AddPageToDocument
- `0x1800fb770` ArtDoc::Page::SetPart
- `0x1800ff460` ArtDoc::Parts::InsertPageIndex
- `0x180095880` FUN (validacao da posicao de insercao)

## Xrefs
- Referencias de dados: `0x180378be4`, `0x18041c7b4` (tabela de exportacao).

## Confianca
`alta` - corpo e chamadas lidos no pseudocodigo; a diferenca em relacao ao overload
`0x180097960` e a origem da posicao (iterator em vez de `Part`).
