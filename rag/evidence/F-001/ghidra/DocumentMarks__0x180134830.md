---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180134830
endereco: 0x180134830
nome: "DocumentMarks::PDFPlusCutMark::Clone"
confianca: alta
xrefs: ["0x180316AB8", "0x1803AADD0"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::Clone — v24.03.10017

## Identificacao

- Endereco: `0x180134830` (corpo `0x180134830`–`0x18013487B`, 75 bytes)
- Assinatura: `PDFPlusCutMark * __thiscall Clone(PDFPlusCutMark *this, ArtDoc::CloneStrategy *strategy)`
- Slot de vtable: `0x180316AB8` = `0x180316AB0 + 1*8` -> slot [1].

## O que a funcao faz

1. Aloca `0x850` bytes (`FUN_1802CBE68`).
2. Chama o construtor de copia `PDFPlusCutMark::PDFPlusCutMark(this, other, strategy)`
   (`0x1801343D0`).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R4/R8 no aspecto de duplicacao: a marca clonada preserva o tipo
  `PDFPlusCutMark` e passa pelo pos-processamento (`0x180135CB0`) que reescreve
  referencias.
- E o slot [1] da vtable, usado por copiar/colar e mark sets.

## Confianca

Alta.
