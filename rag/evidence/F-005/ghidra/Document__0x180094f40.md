---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x180094f40
nome: mapeamento de criptografia/permissoes para GADocEncryptionParams (usado por Document::Save)
endereco: 0x180094f40
confianca: alta
xrefs: [0x18009aaf4, 0x18009ad2a, 0x18009b0bd]
strings: ["Document: Unknown encryption value ", "document.document"]
---

# Mapeamento de criptografia para GADocEncryptionParams

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`).
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs2.txt` (secao `## FN 180094f40`).

## Assinatura observada
`GADocEncryptionParams* __thiscall FUN_180094f40(GADocEncryptionParams *out,
ArtDoc::Security *security)`

## O que faz (observado)
1. `ArtDoc::Security::GetPermissions` e traduz a mascara de permissoes para os enums
   `ChangePermissions` e `PrintPermissions` usados por `GADocEncryptionParams`.
2. `ArtDoc::Security::GetEncryption` -> mapeia para `EncryptionType` (valores 1, 2, 3;
   padrao 2; 0 = sem criptografia).
3. Para valor desconhecido: log em `clog` com guard `"document.document"` e a mensagem
   `"Document: Unknown encryption value "` seguida do valor.
4. Constroi `PDFACCESSLAYER.DLL::GADocEncryptionParams(out, type, change, print, ...)`.

## Escopo correto (importante)
- **Nao** faz parte do caminho de abertura. Todos os call sites estao em
  `ArtDoc::Document::Save` (`0x18009aaf4`, `0x18009ad2a`, `0x18009b0bd`).
- Foi incluido nesta evidencia porque a spec trata senha/criptografia na abertura; o
  teste do codigo mostra que a leitura da criptografia na abertura esta no construtor
  `Document::Document` (@`0x18008f590`, via `GADoc::GetEncryptionType`), enquanto este
  endereco prepara os parametros para **gravar** um PDF criptografado.

## Chamadas de saida confirmadas
- `0x180173880` ArtDoc::Security::GetPermissions
- `0x180173810` ArtDoc::Security::GetEncryption
- `EXTERNAL:00000696` PDFACCESSLAYER.DLL::GADocEncryptionParams::GADocEncryptionParams
- `LOGGING.DLL::Logging::HasLevel`, `Logging::Guard::Guard`

## Confianca
`alta` - corpo completo lido; a atribuicao ao fluxo de Save vem dos tres xrefs de
chamada observados, nao de suposicao.
