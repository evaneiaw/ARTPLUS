---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x180094e10
nome: ArtDoc::Document::Create(path const&, ReadOptions const&)
endereco: 0x180094e10
confianca: alta
xrefs: [0x1800a2e76, 0x18016e7ac, 0x180377d60, 0x18041c580]
strings: []
---

# ArtDoc::Document::Create(path, ReadOptions)

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`), projeto
  `ArtProPlus_Document`.
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs5.txt` (secao `## FN 180094e10`).

## Assinatura observada
`unique_ptr<ArtDoc::Document> __cdecl ArtDoc::Document::Create(
boost::filesystem::path const& path, ArtDoc::ReadOptions const& options)`

## O que faz (observado)
1. Aloca 0x330 bytes (`operator new` via `FUN_1802ae920`).
2. Chama o construtor `ArtDoc::Document::Document(this, path, options, PrivateKey)`
   (@`0x18008f590`) - e o construtor que faz o trabalho de abertura/parse delegado.
3. `FUN_180159c90` e `FUN_180098b30` no objeto criado (inicializacao pos-construcao;
   nomes nao recuperados).

## Xrefs de entrada
- `0x1800a2e76` em `0x1800a2e40` (handler de abertura, ver `GHIDRA-Document-0x1800A2E40`)
- `0x18016e7ac` em `0x18016e5e0` (segundo caminho de abertura, nao detalhado)
- Dados: `0x180377d60`, `0x18041c580`.

## Chamadas de saida confirmadas
- `0x18008f590` ArtDoc::Document::Document (construtor de abertura)
- `0x180159c90`, `0x180098b30`

## Confianca
`alta` - simbolo demangled presente na tabela e pseudocodigo completo coerente com a
assinatura.
