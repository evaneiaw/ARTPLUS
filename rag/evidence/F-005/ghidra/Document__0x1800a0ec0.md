---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x1800a0ec0
nome: mapeamento de codigo de erro de abertura para nome simbolico (ERROR_FILE_*)
endereco: 0x1800a0ec0
confianca: alta
xrefs: [0x1800a0bb7]
strings: ["ERROR_FILE_NOT_FOUND", "ERROR_FILE_ACCESS_DENIED", "ERROR_FILE_INVALID", "ERROR_WRONG_PASSWORD", "ERROR_FILE_UNKNOWN"]
---

# Codigo de erro de abertura -> nome simbolico

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`).
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs2.txt` (secao `## FN 1800a0ec0`).

## Assinatura observada
`std::basic_string<char>* __cdecl FUN_1800a0ec0(std::string *out, int code)`

## O que faz (observado)
Retorna um `std::string` com o nome simbolico do erro de abertura:
```
code 0 -> "ERROR_FILE_NOT_FOUND"
code 1 -> "ERROR_FILE_ACCESS_DENIED"
code 2 -> "ERROR_FILE_INVALID"
code 3 -> "ERROR_WRONG_PASSWORD"
outro  -> "ERROR_FILE_UNKNOWN"
```
(cada ramo aloca o buffer e copia o literal; os literais estao em
`0x1802ea7d8`, `0x1802ea7f0`, `0x1802ea810`, `0x1802ea828`, `0x1802ea840`)

## Chamador
- `0x1800a0bb7`, dentro de `ArtDoc::DocumentOpenException::GetDescription`
  (@`0x1800a0b80`): a descricao textual da excecao de abertura e este nome simbolico.

## Relacao com os codigos usados na abertura
- `DocumentOpenException(path, 0)` -> arquivo nao encontrado
  (`Document::Document` @`0x18008f590`: status < 2).
- `DocumentOpenException(path, 2)` -> arquivo sem paginas
  (`Document::Cache` @`0x180093d60`), reportado como ERROR_FILE_INVALID.
- `DocumentOpenException(path, 7)` -> nenhum handler registrado para o MIME
  (`FileDispatcher::OpenFile` @`0x1802160b0`); cai no ramo padrao
  ERROR_FILE_UNKNOWN (observado: nao ha ramo especifico para 4..7).

## Confianca
`alta` - os cinco literais e o encadeamento if/else foram lidos no pseudocodigo; a
associacao codigo->nome e direta.
