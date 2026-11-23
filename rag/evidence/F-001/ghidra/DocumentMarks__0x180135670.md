---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180135670
endereco: 0x180135670
nome: "DocumentMarks::PDFPlusCutMark::getPositionRefBBox"
confianca: media
xrefs: ["0x180316BB0", "0x1803ABF04"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::getPositionRefBBox — v24.03.10017

## Identificacao

- Endereco: `0x180135670` (corpo `0x180135670`–`0x1801358E1`, 625 bytes)
- Assinatura: `YAGL::RectangleBase<YAGL::MilliPointCoordinateSystem> __thiscall getPositionRefBBox(PDFPlusCutMark *this) const`
- Slot de vtable: `0x180316BB0` = `0x180316AB0 + 32*8` -> slot [32].

## O que a funcao faz (decompilado)

- Resolve a caixa de referencia de posicionamento a partir de
  `this+0x7C0`/`this+0x838`:
  - seletor 0 -> `PageContent::GetPage` + `Page::GetPageBox`;
  - seletor 1 -> `Content::GetObjectWithID` + `GetBoundingBoxForPositioning`
    (`0x18012A130`);
  - estados invalidos/nao ligados -> caminho vazio.
- Consulta `DynamicObject::isNotLinkedYet` e `GetTopLevelTargetContent` antes de
  resolver o objeto.

## Por que sustenta F-001 (Cut Mark)

- Fornece o bounding box usado na resolucao de formulas/posicionamento (R6):
  `GetBoundingBoxForPositioning` e quem referencia a chave
  `PDFPlusCutMark_Offset` (dados em `0x18012A2CF`/`0x18012A2D6`).
- Confirma que a mesma dupla `PageBox`/objeto de `GetReferenceBox` alimenta o
  posicionamento da marca.

## Confianca

Media: fluxo principal confirmado; a ligacao com a avaliacao da formula e
indireta (via `GetBoundingBoxForPositioning`) e nao foi seguida ate o avaliador.
