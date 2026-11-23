---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180136190
endereco: 0x180136190
nome: "DocumentMarks::PDFPlusCutMark::regenerateMarkImp"
confianca: alta
xrefs: ["0x180316B98", "0x1803AC1EC", "0x1804868D0"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::regenerateMarkImp — v24.03.10017

## Identificacao

- Endereco: `0x180136190` (corpo `0x180136190`–`0x180136DE2`, 3143 bytes)
- Nome qualificado: `DocumentMarks::PDFPlusCutMark::regenerateMarkImp`
- Assinatura: `void __thiscall regenerateMarkImp(PDFPlusCutMark *this)`
- Slot de vtable: `0x180316B98` = vftable `0x180316AB0` + 29 * 8 -> **slot [29]**.

## Xrefs

- Referencia de dados `0x180316B98` (slot [29] da vftable principal).
- Referencias de dados `0x1803AC1EC` e `0x1804868D0` (tabelas do modulo).
- Nao ha chamador direto: e invocado por vtable/regeneracao de marca.

## O que a funcao faz (decompilado)

1. **Apaga o conteudo anterior**: `DocumentEdit::Delete` em `0x180136223`.
2. **Zera estado derivado** e resolve o offset:
   - se `this+0x770 == 1` (formula), avalia a string com
     `Localization::Evaluate` e o functor `EvaluateFunction` (aprox. `0x180136314`);
   - se `this+0x770 == 0` (quantidade), converte `*(double*)(this+0x758)`
     pela unidade (`Localization::PointUnit`, `CanConvert`, `GetValueForUnit`).
3. **Obtem a caixa de referencia** com `GetReferenceBox` em `0x1801365B3`.
4. **Gera as posicoes**: instala um `dm::MarkPositionVector` (vftable em
   `local_9D8`) e chama `FUN_180298840(rect, vector)` para o caso PageBox; no
   caso referencia por objeto (`this+0x838 == 1`), obtem o objeto por
   `GetObjectWithID(this+0x7C0)`, valida `GridInterface` por RTTI e chama
   `FUN_1802988F0` para gerar as posicoes a partir do grid.
5. **Por posicao**, cria um `ArtDoc::Group` (`Group::Group(group, 0x1FF)`), abre
   um `DocumentEdit::Expander` com o conteudo do `FormPaint` de origem
   (`DynamicMark::GetSourceContent` -> `ArtPaint::FormPaint::GetContent`),
   calcula a rotacao com `atan2`/`cos`/`sin`, aplica `SetTransformation`, obtem
   o bounding box (`GetPDFPlusBoundingBox`) e, dentro de
   `ArtDoc::ActionGroupCreator`, insere com `DocumentEdit::InsertNewObjectOnTop`
   e aplica a cor com `DynamicMark::ApplyPDFPlusColor` (`0x180136CFx`).
6. Termina com `FUN_18004A3B0`/`FUN_180297130` liberando o vetor de posicoes.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R7 na v240 no essencial: apaga o conteudo anterior, resolve o offset
  (quantidade ou formula), resolve a caixa por `GetReferenceBox`, aplica cor e
  insere no topo do conteudo dentro de `ActionGroupCreator` (transacao de undo).
- Sustenta a regeneracao de R8: o conteudo e substituido, nao acumulado
  (`DocumentEdit::Delete` antes de inserir).
- **Diferenca v240 x v250:** na v240 a geometria e obtida **copiando o conteudo
  do `FormPaint` de origem** (via `Expander`) para um `Group` por posicao; a v25
  gera a geometria diretamente (8 `PathObject`). A contagem de posicoes vem de
  `dm::MarkPositionVector` e **nao foi contada** nesta extracao. Portanto o teste
  de R7 ("1 GroupObject com 8 PathObject") e uma expectativa da v25 e precisa ser
  revalidado/ajustado para a v240.

## Confianca

Alta para o fluxo de chamadas e para as operacoes de undo/insercao; media para
a forma geometrica final (depende de `dm::MarkPositionVector` e do conteudo do
`FormPaint`, nao decodificados nesta passagem).
