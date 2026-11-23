---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180172100
endereco: 0x180172100
nome: "FUN_180172100 (parser PDF+ do Cut Mark)"
confianca: alta
xrefs: ["0x18016A437", "0x18048855C"]
strings: ["Position", "Reference", "ReferenceID", "Offset"]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Parser PDF+ do Cut Mark (FUN_180172100) — v24.03.10017

## Identificacao

- Endereco: `0x180172100` (corpo `0x180172100`–`0x180172593`, 1129 bytes)
- Nome atual: `FUN_180172100` (sem simbolo; identificado pelo chamador e pelas
  chaves lidas)
- Assinatura observada: `void __fastcall (GADict *dict, ArtDoc::ContentObject *mark, ... , double scale)`
- Chamado pelo leitor de marcas PDF+ `FUN_1801683E0` em `0x18016A437`, logo
  apos `DocumentMarks::PDFPlusCutMark::PDFPlusCutMark` (`0x18016A40F`).

## Chaves e fluxo (decompilado)

1. `Position`: `GADict::GetDict` + `FUN_18017BAC0` (parser de posicao).
2. `Reference`: `GADict::GetName` + `FUN_18017A9C0` (mapeia o nome para o enum):
   - valor `5` -> referencia por objeto: le `ReferenceID`, converte para UTF-8 e
     grava a propriedade **`DocumentMarks_CutMark_ReferenceID`**
     (ponteiro `0x180319958`);
   - qualquer outro valor -> `MarkPosition::ref2box` e
     `PDFPlusCutMark::SetReferenceObject` com a `PageBox` resultante.
3. `Offset`:
   - presente e string -> variant **formula** (`SetOffset` com seletor 1);
   - presente e numero -> variant **quantidade**: `valor * scale *
     DAT_1802FB5C8` (`SetOffset` com seletor 0);
   - ausente -> `0 * scale` (offset zero, seletor 0).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R3/R4 (referencia por PageBox e por `ReferenceID`), R5/R6 (offset
  quantidade/formula) e as chaves `Position`, `Reference`, `ReferenceID`,
  `DocumentMarks_CutMark_ReferenceID` de R10/R11.
- **Contradiz R11/E1/E2/E3 para a v240:** este parser **nao le** `Orientation`,
  `Repetition`, `LineTypes` nem `AllStructuralDesignStations`. Uma varredura
  ASCII/UTF-16 do binario v240 nao encontra os literais
  `AllStructuralDesignStations`, `LineTypes`, `Cut Mark has invalid Orientation
  value` ou `Cut Mark has invalid Repetition value` (existem na v250, nao na
  v240). A validacao descrita em R11 e as excecoes E1/E2/E3 sao da v25 e
  precisam ser revalidadas/removidas para a v24.
- O leitor v240 usa um esquema mais simples (Position/Reference/ReferenceID/
  Offset); a estrutura de `Orientation`/`Repetition` aparece em outras marcas,
  nao neste parser de Cut Mark.

## Confianca

Alta para chaves, ramos e chamadas (decompilado + strings referenciadas +
ausencia confirmada por varredura binaria). Media para o significado exato do
enum `Reference` (5 = objeto; os demais valores mapeiam para PageBox via
`ref2box`, sem nomes no binario).
