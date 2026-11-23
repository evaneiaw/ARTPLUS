---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x1800AA1B0
endereco: 0x1800AA1B0
nome: "DocumentMarks::SetCutMarkOffset(PDFPlusCutMark&, variant)"
confianca: alta
xrefs: ["0x1801350D2", "0x1803AB78C", "0x180481DD0"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# SetCutMarkOffset(PDFPlusCutMark&, const variant&) — v24.03.10017

## Identificacao

- Endereco: `0x1800AA1B0` (corpo `0x1800AA1B0`–`0x1800AA339`, 393 bytes)
- Assinatura: `void __cdecl DocumentMarks::SetCutMarkOffset(DocumentMarks::PDFPlusCutMark &mark, const std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem>, std::string> &value)`
- Chamador unico: `PDFPlusCutMark::RemoveInvalidCustomFormulasImp` (`0x1801350D2`).

## O que a funcao faz (decompilado)

1. Monta um `std::function` getter do offset e um `std::function` setter que
   aponta para `PDFPlusCutMark::SetOffset` (`0x180135160`).
2. Normaliza o variant recebido (`0xFF` vazio, `0` quantidade, `1` string).
3. Cria a acao com `FUN_1800A9420` e executa
   `ArtDoc::Action::GetActionList` -> **`ArtDoc::ActionList::DoAction`**.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R5/R8 na v240: **toda alteracao de offset passa por
  `ActionList::DoAction`**, ou seja, e uma acao undoable unica.
- E o caminho usado por `RemoveInvalidCustomFormulasImp` (E4) para remover a
  formula invalida.

## Confianca

Alta: presenca de `ActionList::DoAction` e do setter `SetOffset` e explicita no
decompilado.
