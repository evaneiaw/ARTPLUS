---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180134880
endereco: 0x180134880
nome: "DocumentMarks::PDFPlusCutMark::ContentChangedSelf"
confianca: media
xrefs: ["0x180316AE8", "0x1803AAE78"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::ContentChangedSelf — v24.03.10017

## Identificacao

- Endereco: `0x180134880` (corpo `0x180134880`–`0x180134B03`, 636 bytes)
- Assinatura: `void __thiscall ContentChangedSelf(PDFPlusCutMark *this, ArtDoc::Content *changed, ArtDoc::Content *owner)`
- Slot de vtable: `0x180316AE8` = `0x180316AB0 + 7*8` -> slot [7].

## O que a funcao faz

1. Chama `DynamicMark::ContentChangedSelf` (base).
2. Se o objeto mudou (`changed != nullptr`), invalida o estado em `this+0x840`
   (`FUN_18002AB30`).
3. Para o documento dono, consulta o `ChangeCollector`
   (`ArtDoc::Document::GetChangeCollector`) e atualiza o `shared_ptr` interno
   (`this+0x840`/`this+0x848`).

## Por que sustenta F-001 (Cut Mark)

- Fornece o mecanismo de propagacao de mudanca que sustenta R4/R8: quando a
  referencia/conteudo muda, o estado derivado da marca e invalidado para a
  proxima regeneracao.
- Nao foi capturado em execucao; a evidencia e estatica.

## Confianca

Media: fluxo de invalidacao identificado; a semantica exata do estado em
`+0x840` nao foi decodificada.
