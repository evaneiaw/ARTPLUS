---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180135660
endereco: 0x180135660
nome: "DocumentMarks::PDFPlusCutMark::getMarkType"
confianca: alta
xrefs: ["0x180316B10", "0x1803ABE6C"]
strings: ["DynamicObject_PDFPlusCutMark"]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::getMarkType — v24.03.10017

## Identificacao

- Endereco: `0x180135660` (corpo `0x180135660`–`0x18013566E`, 14 bytes)
- Assinatura: `std::string_view __thiscall getMarkType(PDFPlusCutMark *this) const`
- Slot de vtable: `0x180316B10` = `0x180316AB0 + 12*8` -> slot [12].

## O que a funcao faz

Devolve um `std::string_view` apontando para o literal
`DynamicObject_PDFPlusCutMark`:
`*out = *(void**)0x180316C58; out[1] = *(uint64*)0x180316C60`.
O literal foi localizado em `0x180305DC8` na varredura de strings do binario.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R9/R10: o tipo persistido da marca na v240 e exatamente
  `DynamicObject_PDFPlusCutMark`, o que permite ao parser PDF+ reconhecer o
  objeto e ao painel `Marks` lista-lo como Cut Mark.

## Confianca

Alta: 14 bytes, retorno constante e literal conferido na varredura.
