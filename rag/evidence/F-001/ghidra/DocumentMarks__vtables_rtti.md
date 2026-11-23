---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180316AB0
endereco: 0x180316AB0
nome: "vtables e slots de PDFPlusCutMark na v24.03.10017"
confianca: alta
xrefs: []
strings: ["PDFPlusCutMark"]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Vtables e slots — DocumentMarks::PDFPlusCutMark (v24.03.10017)

## Vtables instaladas pelo construtor (`0x1801344E0`)

- `this+0x000` -> `0x180316AB0` (`vftable` para
  `ArtDoc::Detail::ListItem<ArtDoc::ContentObject>`)
- `this+0x020` -> `0x180316C30` (`vftable` para `ArtDoc::Visitable`)

## Slots confirmados por xref de dados (vftable `0x180316AB0`)

| Slot | Endereco do slot | Funcao |
|---|---|---|
| [1] | `0x180316AB8` | `PDFPlusCutMark::Clone` (`0x180134830`) |
| [7] | `0x180316AE8` | `PDFPlusCutMark::ContentChangedSelf` (`0x180134880`) |
| [12] | `0x180316B10` | `PDFPlusCutMark::getMarkType` (`0x180135660`) |
| [16] | `0x180316B30` | `PDFPlusCutMark::postProcessClonedMark` (`0x180135CB0`) |
| [25] | `0x180316B78` | `PDFPlusCutMark::getRefBoxes` (`0x180135930`) |
| [29] | `0x180316B98` | `PDFPlusCutMark::regenerateMarkImp` (`0x180136190`) |
| [32] | `0x180316BB0` | `PDFPlusCutMark::getPositionRefBBox` (`0x180135670`) |
| [39] | `0x180316BE8` | `PDFPlusCutMark::RemoveInvalidCustomFormulasImp` (`0x180134F60`) |

A aritmetica `slot = (endereco_do_slot - 0x180316AB0) / 8` confere para todos
os itens acima. Em particular, **`regenerateMarkImp` e o slot [29]**, igual ao
observado na v25.

## RTTI / hierarquia

Os nomes qualificados (vindos do RTTI e dos simbolos) confirmam a cadeia
`ContentObject` -> `Group` -> `DynamicObject` -> `DynamicMark` ->
`PDFPlusCutMark`, com as interfaces `Visitable` e
`ArtDoc::Detail::ListItem<ArtDoc::ContentObject>`. Os type descriptors
`PDFPlusCutMark` aparecem em `0x1803B...` (RTTI), conforme o import log.

## Confianca

Alta: cada slot foi derivado de uma referencia de dados real do binario v240.
