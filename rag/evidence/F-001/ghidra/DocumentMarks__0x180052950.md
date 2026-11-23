---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180052950
endereco: 0x180052950
nome: "DocumentMarks::CutMark::regenerateMarkImp (legado)"
confianca: alta
xrefs: ["0x1802FDB48", "0x1803AC1CC"]
strings: [" Cut Mark update at \n", "gridParams:\n", "GridBbox mm:", "] -> ["]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# CutMark::regenerateMarkImp (caminho legado) — v24.03.10017

## Identificacao

- Endereco: `0x180052950` (corpo `0x180052950`–`0x18005307C`, 1827 bytes)
- Assinatura: `void __thiscall regenerateMarkImp(CutMark *this)`
- Referencia de dados `0x1802FDB48` (slot de vtable da classe legada).

## O que a funcao faz (decompilado)

1. Obtem a caixa/objeto de referencia com
   `DynamicObject::getPositionRefBBox`/`getPositionRefObject` e
   `GetBoundingBoxForPositioning` (`0x18012A130`).
2. Gera as posicoes (`dm::CutMarkPositionGenerator`/vetor de posicoes) — as
   posicoes nao foram contadas nesta extracao.
3. Para cada posicao:
   - `ArtDoc::CloneStrategy::CloneStrategy(strategy, document, 1)`;
   - `DocumentEdit::ExtractObjectFromParent` + `DocumentEdit::InsertNewObjectAfter`;
   - `CutMark::PlaceCutMarkSymbol(this, newObj, CPoint*, CPoint*)` em
     `0x180052D22`.
4. Com nivel de debug (`GetMarksDebugLevel`) imprime, entre outros,
   `" Cut Mark update at 
"` (literal em `0x1802FDC78`).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R12.3/R12.4: o caminho legado **clona o simbolo** e o posiciona apos
  a marca, com `CPoint` de origem e destino — diferenca estrutural em relacao ao
  caminho PDF+.
- O literal de debug ` Cut Mark update at 
` confirma a identidade do fluxo.

## Confianca

Alta para a sequencia de clonagem/insercao; media para a quantidade de copias
(o vetor de posicoes de `dm::CutMarkPositionGenerator` nao foi contado).
