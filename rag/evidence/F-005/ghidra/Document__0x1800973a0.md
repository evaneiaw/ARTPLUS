---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x1800973a0
nome: ArtDoc::Document::GetPagesBegin
endereco: 0x1800973a0
confianca: alta
xrefs: [0x1800a0532, 0x1800c47c5, 0x1800fef06, 0x1801a5ff8]
strings: []
---

# ArtDoc::Document::GetPagesBegin

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`).
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs1.txt` (secao `## FN 1800973a0`).
- Dois simbolos demangled compartilham o endereco (versao nao-const e const):
  `?GetPagesBegin@Document@ArtDoc@@QEAA?AV?$indirect_iterator@...XZ` e
  `?GetPagesBegin@Document@ArtDoc@@QEBA?AV?$indirect_iterator@...XZ`.

## Assinatura observada
`indirect_iterator __thiscall GetPagesBegin(Document *this)`

## O que faz (observado)
```
SwitchToWorkingFile(this);
*out = *(undefined8 *)(this + 0x1b0);
```
Devolve um `boost::iterators::indirect_iterator` sobre o inicio do vetor de
`std::unique_ptr<ArtDoc::Page>` interno do documento (ponteiro em `this+0x1b0`).

## Relacao com a abertura
- O mesmo offset `this+0x1b0` e o inicio do vetor usado por
  `ArtDoc::Document::Cache` (@`0x180093d60`) para decidir "Document: File has no pages"
  (comparacao `this+0x1b0` com `this+0x1b8`), e por `InsertPage` (@`0x180097960`,
  `0x180097ab0`) para inserir paginas.
- Portanto `GetPagesBegin`/`GetPagesEnd` e a leitura publica da lista de paginas criada
  na abertura.

## Chamadores (amostra dos 30+ xrefs de codigo)
`0x1800a0532` (GetAssociatedContent), `0x1800c47c5`/`0x1800c4806`/`0x1800c497e`
(GetLayerPositionForInsertingAfter), `0x1800fef06`/`0x1800fef26`/`0x1800fefd4`/`0x1800feff4`
(Part::ExtractPart), `0x1801a5ff8` (PDFAction), entre outros.

## Confianca
`alta` - corpo de 45 bytes lido (offset `+0x1b0` explicito no pseudocodigo).
