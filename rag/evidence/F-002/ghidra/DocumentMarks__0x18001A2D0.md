---
modulo: DocumentMarks.dll
funcao: "ID historico sem funcao na v240: endereco interno de DocumentMarks::BarcodeMark::Accept (0x18001A240); nao e entrada de funcao"
endereco: 0x18001A2D0
versao: 24.03.10017
confianca: alta
xrefs: []
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Registro de ID - `0x18001A2D0` (citado pelo manifest de F-002)

## Resultado neste binario (v24.03.10017)

- `isFunctionEntry=false` em `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
  (sha256 `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`).
- O endereco cai **dentro** do corpo de `DocumentMarks::BarcodeMark::Accept`,
  `0x18001A240`..`0x18001A33B` (252 bytes).
- Instrucao que contem o endereco: `0x18001a2cd` `CALL 0x1802ccf7a`; o endereco esta 3 byte(s)
  apos o inicio da instrucao, ou seja, **no meio de uma instrucao**.
- Nenhum simbolo e nenhuma referencia apontam para `0x18001A2D0`.
- O endereco **tambem nao e export da instalacao historica**: a tabela de exports
  de `DocumentMarks.dll` dessa instalacao (2268 exports) nao contem nenhum VA na
  faixa `0x18001A2xx`.

## Por que este arquivo existe

O ID `GHIDRA-DocumentMarks-0x18001A2D0` estava listado como evidencia estatica de F-002 sem
arquivo correspondente. Os 10 IDs `0x18001A2C0`..`0x18001A350` formam uma sequencia
regular de passo 0x10 dentro de `BarcodeMark::Accept` -- padrao de offsets de codigo,
nao de entradas de funcao. Este registro preserva a rastreabilidade e documenta a
prova de que o ID nao identifica funcao na versao de referencia.

## Equivalente v240

Nenhum. O ID nao tem funcao correspondente: e um deslocamento interno de
`DocumentMarks::BarcodeMark::Accept` (0x18001A240), funcao sem relacao com Mark Set.

## Confianca

`alta` - `isFunctionEntry`, funcao conteiner, instrucao conteiner e ausencia de
simbolos lidos diretamente no programa v240; ausencia na tabela de exports da
instalacao historica (rastreabilidade)
conferida no dump de exports da instalacao historica.

## Fonte

- bruto: `rag/evidence/F-002/ghidra/raw_v240/_interior.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
- tabela de exports historica: `rag/evidence/F-006/exports.txt` (DocumentMarks.dll)
