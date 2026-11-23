---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180134F60
endereco: 0x180134F60
nome: "DocumentMarks::PDFPlusCutMark::RemoveInvalidCustomFormulasImp"
confianca: alta
xrefs: ["0x180316BE8", "0x1803AB6CC"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::RemoveInvalidCustomFormulasImp — v24.03.10017

## Identificacao

- Endereco: `0x180134F60` (corpo `0x180134F60`–`0x180135154`, 500 bytes)
- Assinatura: `bool __thiscall RemoveInvalidCustomFormulasImp(PDFPlusCutMark *this)`
- Slot de vtable: `0x180316BE8` = `0x180316AB0 + 39*8` -> slot [39].

## O que a funcao faz (decompilado)

1. Só age se o offset for formula (`this+0x770 == 1`).
2. Valida a formula com `FUN_180147EE0` e `FUN_180148050`; se **ambas** falham:
   - reporta `MarkActionError` (codigo `4`) com o nome do objeto via
     `ArtDoc::Document::GetErrorReporter`;
   - chama `DocumentMarks::SetCutMarkOffset(this, variant vazio)` em `0x1801350D2`;
   - devolve `true`.
3. Se o offset nao e formula ou a formula e valida, devolve `false`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta E4/R6 na v240: formula invalida e **removida** por
  `SetCutMarkOffset`, e o estado final do offset e o variant vazio (`0xFF`),
  nao "ultimo valor valido". O erro e reportado ao `ErrorReporter` do documento.
- O slot [39] confirma que e um hook de pos-leitura da classe.

## Confianca

Alta para o fluxo e para o estado final vazio; media para a semantica exata dos
dois validadores (nao decompilados nesta passagem).
