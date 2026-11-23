---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x180083f80
nome: ArtDoc::ContentTracker::AddPageToDocument
endereco: 0x180083f80
confianca: alta
xrefs: [0x18008f4fb, 0x18009438f, 0x180097a41, 0x180097b9a, 0x180097cae, 0x180097d73, 0x180097eda, 0x180097f9f]
strings: []
---

# ArtDoc::ContentTracker::AddPageToDocument

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`).
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs1.txt` (secao `## FN 180083f80`).
- Simbolo demangled: `?AddPageToDocument@ContentTracker@ArtDoc@@QEAAXAEAVPage@2@@Z`.

## Assinatura observada
`void __thiscall AddPageToDocument(ContentTracker *this, ArtDoc::Page& page)`

## O que faz (observado)
```
_Var1 = ArtImg::PictureBuffer::GetBitsPerSample((PictureBuffer *)param_1);
FUN_18007ff10(this + 8, _Var1, local_res8, 0);
```
Registra a pagina no `ContentTracker` do documento (estrutura interna em `this+8`).
E o ponto unico por onde passa toda pagina criada no documento: as paginas vindas da
abertura de PDF e as paginas inseridas manualmente.

## Xrefs de entrada (todos os caminhos de criacao de pagina)
- `0x18009438f` em `ArtDoc::Document::Cache` (@`0x180093d60`) - paginas lidas do PDF
- `0x180097a41` em `InsertPage` (@`0x180097960`)
- `0x180097b9a` em `InsertPage` (@`0x180097ab0`)
- `0x180097cae` e `0x180097d73` em `InsertPage` (@`0x180097c00`)
- `0x180097eda` e `0x180097f9f` em `InsertPage` (@`0x180097e20`)
- `0x18008f4fb` em `Document::Document` (@`0x18008ee30`, construtor alternativo)

## Confianca
`alta` - corpo de 42 bytes e todos os xrefs de codigo enumerados pelo export do Ghidra.
