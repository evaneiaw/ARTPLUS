---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x1800973d0
nome: ArtDoc::Document::GetPagesEnd
endereco: 0x1800973d0
confianca: alta
xrefs: [0x1800c47b5, 0x1800ffb90, 0x1801a6005, 0x1803787cc]
strings: []
---

# ArtDoc::Document::GetPagesEnd

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`).
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs1.txt` (secao `## FN 1800973d0`).
- Simbolos demangled: `?GetPagesEnd@Document@ArtDoc@@QEAA?AV?$indirect_iterator@...XZ`
  e a variante const no mesmo endereco.

## Assinatura observada
`indirect_iterator __thiscall GetPagesEnd(Document *this)`

## O que faz (observado)
```
SwitchToWorkingFile(this);
*out = *(undefined8 *)(this + 0x1b8);
```
Devolve o iterator de fim do vetor de paginas do documento (ponteiro em `this+0x1b8`).

## Relacao com a abertura
- `this+0x1b8` e exatamente o limite usado por `ArtDoc::Document::Cache`
  (@`0x180093d60`) no teste de documento vazio:
  `if (*(longlong*)(this+0x1b0) == *(longlong*)(this+0x1b8))` -> loga
  "Document: File has no pages" e lanca `DocumentOpenException(path, 2)`.
- Confirma que o numero de paginas abertas e o tamanho do vetor
  `[this+0x1b0, this+0x1b8)`.

## Chamadores (amostra)
`0x1800c47b5`/`0x1800c4997`/`0x1800c4ab4` (GetLayerPositionForInsertingAfter),
`0x1800ffb90`/`0x1800ffbe8` (IsPartsValid), `0x1801a6005` (PDFAction),
`0x180144d3a`, `0x18017955a`, `0x18019d7bb`, `0x18019d821`.

## Confianca
`alta` - corpo lido; offset `+0x1b8` explicito.
