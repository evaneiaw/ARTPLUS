---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x1802160b0
nome: DocumentIO::FileDispatcher::OpenFile
endereco: 0x1802160b0
confianca: alta
xrefs: [0x1802161d5, 0x180378e40, 0x18042b274]
strings: []
---

# DocumentIO::FileDispatcher::OpenFile

## Identidade e prova
- Binario alvo: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\Document.dll`
  (size 4421040, mtime 2024-03-12 18:41:10).
- Projeto Ghidra `ArtProPlus_Document`, programa `Document.dll`,
  `executableSHA256=da91e28574c877d392d3e6bef9ccbb7c4dcf3117ebd03655de89834fc8fa9e21`.
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs1.txt` (secao `## FN 1802160b0`).

## Assinatura observada
`unique_ptr<ArtDoc::Document> __thiscall DocumentIO::FileDispatcher::OpenFile(
FileDispatcher *this, boost::filesystem::path const& path, ArtDoc::ReadOptions const& options)`

## O que faz (observado no pseudocodigo)
1. `boost::filesystem::detail::status(path, ec)`: se o resultado for menor que 2, constroi
   `ArtDoc::DocumentOpenException(path, 0)` e lanca via `_CxxThrowException`
   (codigo 0 = ERROR_FILE_NOT_FOUND, ver `GHIDRA-Document-0x1800A0EC0`).
2. `ExtraBoostFilesystem::MimeType::GetMimeType(path)`: obtem o MIME do arquivo.
3. Procura o MIME num `std::map` (busca binaria com `memcmp` sobre a chave `string_view`)
   cujo valor e um `unique_ptr<DocumentIO::OpenFileHandler>`.
4. Se a chave nao existe: `DocumentOpenException(path, 7)` e lanca. Este e o ponto em que
   o formato do arquivo e decidido: nao ha sniffing de bytes no Document.dll, a decisao e
   MIME (derivado do conteudo/extensao pela camada ExtraBoostFilesystem) -> handler registrado.
5. `AddToOpeningFiles(path)`; chama o metodo virtual do handler no slot 1
   (`(**(code**)(*(longlong*)handler + 8))(handler, path, options, out)`);
   `RemoveFromOpeningFiles(path)`; devolve o `unique_ptr<Document>` de saida.

## Chamadas de saida confirmadas
- `0x180215d50` DocumentIO::FileDispatcher::AddToOpeningFiles
- `0x180216380` DocumentIO::FileDispatcher::RemoveFromOpeningFiles
- `0x1800a0aa0` ArtDoc::DocumentOpenException::DocumentOpenException
- `EXTERNAL:0000011f` ExtraBoostFilesystem::MimeType::GetMimeType
- `EXTERNAL:00000141` boost::filesystem::detail::status
- `VCRUNTIME140.DLL::_CxxThrowException`, `memcmp`

## Xrefs
- Referencias de dados (tabela/vtable de exportacao): `0x180378e40`, `0x18042b274`.
- Nenhum chamador direto por `CALL` dentro do modulo (API publica consumida por outro
  modulo/entry point).

## Confianca
`alta` - assinatura demangled conferida no simbolo exportado
(`?OpenFile@FileDispatcher@DocumentIO@@QEAA...`) e pseudocodigo completo obtido.
