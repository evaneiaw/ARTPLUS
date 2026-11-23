---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x180093d60
nome: ArtDoc::Document::Cache
endereco: 0x180093d60
confianca: alta
xrefs: [0x18009023b, 0x180090af8, 0x180095a80, 0x1800996cc, 0x18009b18b, 0x18009b66a, 0x18009c299]
strings: ["Document: File has no pages"]
---

# ArtDoc::Document::Cache (contagem de paginas e criacao de Page)

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`).
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs2.txt` (secao `## FN 180093d60`,
  corpo com 2050 bytes).
- Simbolo demangled: `?Cache@Document@ArtDoc@@AEAAXXZ`.

## Assinatura observada
`void __thiscall Cache(Document *this)`

## O que faz (observado)
1. `SwitchToWorkingFile(this)` e verificacoes de flags de informacao do documento.
2. `GetPDFDocument(this)` -> o objeto `PDFDocument`; a partir dele obtem o `GODocument`
   (chamada virtual no offset +0x80) e o `GADoc` (`GADoc::GetCatalog`).
3. **Contagem de paginas**: o laco de paginas usa o campo `*(int*)(godo + 0x1a0)`.
   Quando esse valor e -1, chama `PDFOBJECTLAYER.DLL::GODocument::UpdateNumPagesCache`
   e le novamente o campo:
   ```
   if (*(int *)(this_02 + 0x1a0) == -1) GODocument::UpdateNumPagesCache(this_02);
   if (*(int *)(this_02 + 0x1a0) <= iVar17) break;
   ```
4. **Criacao de paginas**: para cada indice, aloca 0x248 bytes, constroi
   `ArtDoc::Page::Page` (@`0x1800f9770`) e registra no documento com
   `ArtDoc::ContentTracker::AddPageToDocument(@0x180083f80)`; incrementa o indice.
5. **Documento sem paginas**: quando o vetor interno de paginas continua vazio
   (`*(longlong*)(this+0x1b0) == *(longlong*)(this+0x1b8)`), loga
   `"Document: File has no pages"` e lanca `ArtDoc::DocumentOpenException(path, 2)`
   via `_CxxThrowException` (codigo 2 = ERROR_FILE_INVALID, ver
   `GHIDRA-Document-0x1800A0EC0`).
6. Tambem le o catalogo PDF (`GADoc::GetCatalog`, `GADictIterator`), o catalogo de
   separacoes/OutputIntent e a DPart tree (`GODocument::GetDPartTree`) apos o laco de
   paginas.

## Chamadas de saida confirmadas
- `0x180083f80` ArtDoc::ContentTracker::AddPageToDocument
- `0x1800f9770` ArtDoc::Page::Page, `0x1800f9960` ArtDoc::Page::~Page
- `0x1800a0aa0` ArtDoc::DocumentOpenException::DocumentOpenException
- `EXTERNAL:000003a0` PDFOBJECTLAYER.DLL::GODocument::UpdateNumPagesCache
- `EXTERNAL:00000464` GODocument::GetDPartTree
- `EXTERNAL:00000688` PDFACCESSLAYER.DLL::GADoc::GetCatalog

## Xrefs de entrada (chamadores)
- `0x18009023b` em `0x18008f590` Document::Document (construtor de abertura)
- `0x180090af8` em `0x180090600` Document::Document (construtor por PDFDocument)
- `0x180095a80` Document::Flush, `0x1800996cc` Document::RevertToSaved,
  `0x18009b18b` e `0x18009b66a` Document::Save, `0x18009c299` Document::Swap

## Confianca
`alta` - laco de paginas, fonte do numero de paginas (campo do GODocument atualizado por
`UpdateNumPagesCache`), criacao de `Page` e a excecao de "sem paginas" foram lidos
diretamente no pseudocodigo.
