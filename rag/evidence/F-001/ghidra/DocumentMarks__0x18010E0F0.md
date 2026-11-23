---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x18010E0F0
endereco: 0x18010E0F0
nome: "FUN_18010E0F0 (createDynamicObject legado)"
confianca: alta
xrefs: ["0x1803130E8", "0x180485328"]
strings: ["AIDynamicMarks-CutMark", "AIDynamicMarks-BearerBar", "AIDynamicMarks-CustomMark"]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# createDynamicObject legado (FUN_18010E0F0) — v24.03.10017

## Identificacao

- Endereco: `0x18010E0F0` (corpo `0x18010E0F0`–`0x18010FD37`, 7239 bytes)
- Nome atual: `FUN_18010E0F0` (sem simbolo)
- Assinatura observada: `MarkReader` -> cria objeto dinamico a partir do
  dicionario de propriedades do mark set.

## O que a funcao faz (para Cut Mark)

1. Le o dicionario de propriedades (`MarkReader::GetPropertiesAsDictionary`).
2. Compara o nome do objeto com os tipos `AIDynamicMarks-*` via `memcmp`.
3. No ramo do Cut Mark:
   - `memcmp(PTR_s_AIDynamicMarks_CutMark_1802FDC48, name, 0x16)` em
     `0x18010F0DD` (22 bytes = `AIDynamicMarks-CutMark`);
   - aloca o objeto e chama **`DocumentMarks::CutMark::CutMark(this, true)`** em
     `0x18010F130`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R12.1 na v240: o caminho legado identifica
  `AIDynamicMarks-CutMark` por comparacao de 22 bytes e instancia
  `CutMark(true)`.
- Confirma que o nome do tipo legado e exatamente `AIDynamicMarks-CutMark`
  (literal em `0x1802FDC58`).

## Confianca

Alta: comparacao, tamanho e chamada do construtor sao explicitos no decompilado.
