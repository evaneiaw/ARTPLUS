---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180135CB0
endereco: 0x180135CB0
nome: "DocumentMarks::PDFPlusCutMark::postProcessClonedMark"
confianca: media
xrefs: ["0x180316B30", "0x1803AC15C"]
strings: ["PDFPlusCutMark_OriginalReferenceName", "PDFPlusCutMark_Offset"]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::postProcessClonedMark — v24.03.10017

## Identificacao

- Endereco: `0x180135CB0` (corpo `0x180135CB0`–`0x1801360DF`, 1231 bytes)
- Assinatura: `void __thiscall postProcessClonedMark(PDFPlusCutMark *this, ArtDoc::CloneStrategy *strategy)`
- Slot de vtable: `0x180316B30` = `0x180316AB0 + 16*8` -> slot [16].

## O que a funcao faz

1. Chama `DynamicMark::postProcessClonedMark`.
2. Ajusta referencias do clone: `CloneStrategy::GetOriginalObject`,
   `Content::GetObjectWithID`, `GetProperties`.
3. Referencia as chaves **`PDFPlusCutMark_OriginalReferenceName`**
   (`0x180316A80`) e **`PDFPlusCutMark_Offset`** (`0x180316C68`).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R10 (chaves de persistencia) e R4: ao clonar/duplicar a marca, a
  referencia por objeto e o nome original sao reescritos a partir do original.
- Explica a existencia de `PDFPlusCutMark_OriginalReferenceName` no dicionario.

## Confianca

Media: chaves e operacoes confirmadas; a regra exata de reescrita nao foi
detalhada.
