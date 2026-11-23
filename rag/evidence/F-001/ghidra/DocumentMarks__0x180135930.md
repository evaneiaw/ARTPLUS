---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180135930
endereco: 0x180135930
nome: "DocumentMarks::PDFPlusCutMark::getRefBoxes"
confianca: alta
xrefs: ["0x180316B78", "0x1803ABF54"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::getRefBoxes — v24.03.10017

## Identificacao

- Endereco: `0x180135930` (corpo `0x180135930`–`0x1801359A1`, 113 bytes)
- Assinatura: `std::vector<ArtDoc::PageBox> __thiscall getRefBoxes(PDFPlusCutMark *this) const`
- Slot de vtable: `0x180316B78` = `0x180316AB0 + 25*8` -> slot [25].

## O que a funcao faz

- Se o seletor de referencia (`this+0x838`) nao e `0`, devolve vetor vazio.
- Se e `0`, devolve um vetor com **um** elemento: `*(uint32*)(this+0x7C0)`
  (a PageBox de referencia).

## Por que sustenta F-001 (Cut Mark)

- Sustenta o dropdown `Attach to:` de R3: a marca oferece exatamente a caixa
  configurada quando referencia por PageBox; a lista das cinco caixas e
  construida pelos menus/UI, nao por esta funcao.
- Confirma que referencia por objeto nao produz page boxes.

## Confianca

Alta.
