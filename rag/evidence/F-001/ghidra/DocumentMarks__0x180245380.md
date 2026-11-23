---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180245380
endereco: 0x180245380
nome: "DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog"
confianca: alta
xrefs: ["0x180243F0E", "0x18024405E", "0x1802440BE", "0x1802440FE", "0x18024415E"]
strings: ["WARNING: Missing Named Objects", "WARNING: Missing Page Box"]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# TaskMarkSets::CopyMarksToPageWithLog — v24.03.10017

## Identificacao

- Endereco: `0x180245380` (corpo `0x180245380`–`0x180245B79`, 2041 bytes)
- Assinatura: `void __thiscall CopyMarksToPageWithLog(TaskMarkSets *this, ArtDoc::Page &source, ArtDoc::Page &target, bool flag)`

## O que a funcao faz

1. Monta conjuntos de nomes/IDs ausentes e de page boxes ausentes.
2. Chama `DocumentMarks::CopyMarksToPage` (`0x1800426F0`) com esses conjuntos.
3. Emite avisos localizados quando ha objetos nomeados ausentes
   (`"WARNING: Missing Named Objects: %s.
Referenced from Mark Set: %s.
Dynamic Marks linked to a missing object were removed from page %lu.
"`,
   `0x18032AC70`) ou page boxes ausentes (`0x18032AD30`), usando as chaves
   `DocumentMarks.Warning.MissingNamedObject` / `...MissingPageBox`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta E5/E7 no contexto de mark set (F-002): referencias ausentes sao
  removidas/religadas com aviso, nao geram marca silenciosamente quebrada.
- Complementa R13 com o comportamento de log do caminho de aplicacao.

## Confianca

Alta para as chamadas e mensagens; media para o detalhe fino das religacoes.
