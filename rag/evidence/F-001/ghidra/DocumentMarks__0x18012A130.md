---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x18012A130
endereco: 0x18012A130
nome: "DocumentMarks::GetBoundingBoxForPositioning"
confianca: media
xrefs: ["0x18009560F", "0x180052559", "0x180052A55", "0x1803AB17C"]
strings: ["PDFPlusCutMark_Offset"]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# GetBoundingBoxForPositioning — v24.03.10017

## Identificacao

- Endereco: `0x18012A130` (corpo `0x18012A130`–`0x18012A3C5`, 661 bytes)
- Assinatura: `std::optional<YAGL::RectangleBase<YAGL::MilliPointCoordinateSystem>> __cdecl GetBoundingBoxForPositioning(const ArtDoc::ContentObject &obj)`

## O que a funcao faz

1. Se nao ha `Content`, devolve `optional` vazio.
2. Tenta obter o objeto como `GridInterface` (RTTI); se nao for grid, percorre o
   conteudo/dynamic objects (`isMarkNormalized`, `GetPDFPlusBoundingBox`,
   `GetBoundingBox`).
3. Referencia a chave de propriedade **`PDFPlusCutMark_Offset`**
   (dados em `0x18012A2CF`/`0x18012A2D6`) ao montar a caixa para posicionamento.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R6: e o ponto onde o nome `PDFPlusCutMark_Offset` e lido para o
  posicionamento, usado por `getPositionRefBBox` e pelo regenerador legado.
- Complementa R3/R4 para o caso de referencia por objeto.

## Confianca

Media: chamadas e string confirmadas; a composicao exata da caixa nao foi
traduzida linha a linha.
