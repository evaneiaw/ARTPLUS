---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x1800A9FB0
endereco: 0x1800A9FB0
nome: "DocumentMarks::SetCutMarkOffset(Content&, predicate, variant)"
confianca: alta
xrefs: ["0x1803AB788", "0x180481DC4"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# SetCutMarkOffset(Content&, predicate, const variant&) — v24.03.10017

## Identificacao

- Endereco: `0x1800A9FB0` (corpo `0x1800A9FB0`–`0x1800AA1B1`, 505 bytes)
- Assinatura: `void __cdecl DocumentMarks::SetCutMarkOffset(ArtDoc::Content &content, const std::function<bool(const PDFPlusCutMark&)> &predicate, const std::variant<...> &value)`
- Sem chamadores diretos no binario (variante usada por callbacks/acoes da UI).

## O que a funcao faz (decompilado)

1. Empacota getter/setter (`PDFPlusCutMark::SetOffset` em `0x180135160`).
2. Aloca uma acao (`0x120` bytes) e valida o predicado recebido.
3. Obtem `ArtDoc::Action::GetActionList` e executa
   **`ArtDoc::ActionList::DoAction`**.

## Por que sustenta F-001 (Cut Mark)

- Complementa R5/R8: a edicao de offset na v240 e uma acao undoable, com
  predicado de aplicabilidade (permite so aplicar a marcas que satisfacam a
  condicao, tipico de edicao em lote/selecao).
- O predicado explica por que existem duas sobrecargas: uma dirigida a uma marca
  (usada por E4) e uma dirigida a `Content` com filtro.

## Confianca

Alta para o uso de `ActionList::DoAction`; media para o papel do predicado na UI
(nao rastreado ate o chamador).
