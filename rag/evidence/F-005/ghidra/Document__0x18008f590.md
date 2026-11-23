---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x18008f590
nome: ArtDoc::Document::Document(path const&, ReadOptions const&, PrivateKey)
endereco: 0x18008f590
confianca: alta
xrefs: [0x180094e50]
strings: ["Document: File ", " could not be found", "Document: Open read/write but file is write-protected: ", "Document: Open read/write: ", "Document: Open read-only: "]
---

# ArtDoc::Document::Document (construtor de abertura)

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`).
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs2.txt` (secao `## FN 18008f590`,
  corpo com 4198 bytes).
- Simbolo demangled:
  `??0Document@ArtDoc@@QEAA@AEBVpath@filesystem@boost@@AEBVReadOptions@1@VPrivateKey@01@@Z`.

## Assinatura observada
`__thiscall Document(Document *this, path const& path, ReadOptions const& options,
PrivateKey key)`

## O que faz (observado no pseudocodigo)
1. Inicializa os membros (ActionList, Errors, ChangeCollector, ContentTracker, Layers,
   Halftones, Properties, Security, DynamicObjectController, ErrorAggregator).
2. `boost::filesystem::detail::status(path, ec)`; quando o status e menor que 2:
   - log `"Document: File "` + path + `" could not be found"` (clog, nivel de log 1);
   - `ArtDoc::DocumentOpenException(path, 0)` e `_CxxThrowException`.
   Isto corresponde a excecao de I/O "arquivo nao encontrado" da spec.
3. Copia o path para o objeto (`FUN_18009cee0`) e entra num laco de ate 5 tentativas
   (`FUN_180098560`), escolhendo o modo de abertura. Os logs observados no caminho:
   - `"Document: Open read/write but file is write-protected: "`
   - `"Document: Open read/write: "`
   - `"Document: Open read-only: "`
   (cada um precedido do guard de log `"document.document"`).
4. Inicializa `ArtDoc::Security`; le `GADoc::GetEncryptionType` (via
   `GODocument::GetGADoc` @import de PDFOBJECTLAYER, chamada virtual no offset +0x80) e
   mapeia para `Security::SetEncryption` com valores 1, 2, 3 (0 = sem criptografia).
   Tambem consulta `GODocument::IsEncrypted` e `GODocument::GetPermissions`.
5. Chama `ArtDoc::Document::Cache(this)` (@`0x180093d60`), que conta as paginas do
   GODocument e cria as `ArtDoc::Page` do documento (ver
   `GHIDRA-Document-0x180093D60`).
6. `GetPDFDocument(this)` e usado depois para acessar o documento PDF subjacente.

## Onde o parse acontece
- O objeto PDF e construido pelo construtor `PDFOBJECTLAYER.DLL::GODocument::GODocument`
  (import `EXTERNAL:00000471`), ou seja, o parse do PDF **nao** esta neste modulo: e
  delegado ao PDFObjectLayer. Inferencia: o argumento passado e o path do arquivo, porque
  o construtor deste modulo ja validou `status(path)` e em seguida consulta
  `GODocument`/`GADoc` para criptografia e paginas.

## Chamadas de saida relevantes
- `0x180093d60` Document::Cache (contagem de paginas / criacao de Page)
- `0x1800971e0` Document::GetPDFDocument
- `0x1800a0aa0` DocumentOpenException::DocumentOpenException
- `EXTERNAL:00000471` PDFOBJECTLAYER.DLL::GODocument::GODocument
- `EXTERNAL:00000469` GODocument::IsEncrypted, `EXTERNAL:00000468` GetPermissions
- `EXTERNAL:00000682` PDFACCESSLAYER.DLL::GADoc::GetEncryptionType

## Xrefs de entrada
- `0x180094e50` dentro de `ArtDoc::Document::Create(path, ReadOptions)` (@`0x180094e10`).

## Confianca
`alta` para os passos 1-5 (strings, chamadas e ordem observadas no pseudocodigo);
`media` para a afirmacao de que o parse ocorre dentro do construtor de GODocument
(delegacao a outro modulo, marcada como inferencia).
