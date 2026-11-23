---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180134B00
endereco: 0x180134B00
nome: "DocumentMarks::PDFPlusCutMark::GetReferenceBox"
confianca: alta
xrefs: ["0x1801365B3", "0x1803AB3D0", "0x1804867D4"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::GetReferenceBox — v24.03.10017

## Identificacao

- Endereco: `0x180134B00` (corpo `0x180134B00`–`0x180134D91`, 658 bytes)
- Nome qualificado: `DocumentMarks::PDFPlusCutMark::GetReferenceBox`
- Assinatura: `YAGL::RectangleBase<YAGL::MilliPointCoordinateSystem> __thiscall GetReferenceBox(PDFPlusCutMark *this) const`
- Chamador unico: `regenerateMarkImp` (`0x1801365B3`).

## O que a funcao faz (decompilado)

1. `ContentObject::GetContent(this)`; se `nullptr`, devolve retangulo vazio
   (quatro doubles `0` + flag `1`).
2. Se `this+0x838 != 0`:
   - `+0x838 == 1` -> referencia por objeto: `Content::GetObjectWithID(content,
     *(uint64*)(this+0x7C0))`; objeto inexistente -> retangulo vazio; existente ->
     `DocumentMarks::GetPDFPlusBoundingBox` (com `RTTI` de `Visitable`).
   - qualquer outro valor -> `FUN_180023A30()` (caminho de erro sem retorno).
3. Se `this+0x838 == 0` -> referencia por caixa de pagina:
   `ContentObject::GetContent` -> `__RTDynamicCast` para `ArtDoc::PageContent`;
   se o cast falhar, retangulo vazio; senao `PageContent::GetPage` e
   `ArtDoc::Page::GetPageBox(page, *(PageBox*)(this+0x7C0))`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R3 e as excecoes E5/E6/E8 na v240, com os offsets desta versao:
  seletor em `+0x838`, `PageBox` em `+0x7C0`.
- Confirma que o caminho por caixa chama `Page::GetPageBox` (import de
  `DOCUMENT.DLL`), que indexa o array de caixas pelo inteiro cru.
- Confirma que referencia por objeto usa `GetObjectWithID` + bounding box e que
  objeto inexistente produz retangulo vazio (E5).
- **Diferenca v240 x v250:** a v25 usa `+0x780/+0x788/+0x708`; a v240 usa
  `+0x838/+0x7C0`. O comportamento e equivalente, os offsets nao.

## Confianca

Alta: leitura direta do decompilado e dos xrefs.
