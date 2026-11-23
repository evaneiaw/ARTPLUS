---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x1802FDC58
endereco: 0x1802FDC58
nome: "literais de Cut Mark na v24.03.10017"
confianca: alta
xrefs: []
strings: ["AIDynamicMarks-CutMark", "DynamicObject_PDFPlusCutMark", "PDFPlusCutMark_Offset", "DocumentMarks_CutMark_ReferenceID", "PDFPlusCutMark_OriginalReferenceName", "DM-CutMarkParams"]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Strings de Cut Mark — v24.03.10017

Enderecos lidos da tabela de dados definidos do programa v240
(`Listing.getDefinedData`), nao de offsets de arquivo.

| Endereco | Valor | Papel |
|---|---|---|
| `0x1802FDC58` | `AIDynamicMarks-CutMark` | tipo do mark set legado (R12) |
| `0x1802FDC70` | `CutMark` | identificador curto legado |
| `0x1802FDC78` | ` Cut Mark update at \n` | log de debug do regenerador legado |
| `0x180305DC8` | `DynamicObject_PDFPlusCutMark` | tipo persistido (R9/R10) |
| `0x180316A80` | `PDFPlusCutMark_OriginalReferenceName` | chave de referencia clonada |
| `0x180316C68` | `PDFPlusCutMark_Offset` | nome do offset (R6/R10) |
| `0x180319368` | `DocumentMarks_CutMark_ReferenceID` | ID da referencia por objeto (R4) |
| `0x18032FDD8` | `DM-CutMarkParams` | dicionario legado (R12.2) |
| `0x1803302A0` | `DM-CutMarkParams-Offset` | offset legado |
| `0x1803302B8` | `DM-CutMarkParams-SymbolDefinition` | simbolo legado (chave existe; uso nao localizado) |
| `0x1803302E0` | `DM-CutMarkParams-Version` | versao legada |
| `0x18031AA50` | `Invalid Repetition Direction value` | mensagem de outra marca/contexto (nao e a de Cut Mark) |

## Literais que NAO existem na v240

Varredura binaria ASCII e UTF-16 (script
`tools/ghidra_analysis/scan_strings_v240.py`) retorna **zero ocorrencias** de:

- `AllStructuralDesignStations`
- `LineTypes`
- `Cut Mark has invalid Orientation value`
- `Cut Mark has invalid Repetition value`

Esses literais existem na v25 e sustentam R11/E1/E2/E3 **apenas na v25**.
Na v240 o parser e outro (`0x180172100`) e nao le essas chaves.

## Confianca

Alta para presenca/endereco dos literais listados; alta para a ausencia dos
literais v25 (duas buscas independentes: tabela do Ghidra e varredura de bytes).
