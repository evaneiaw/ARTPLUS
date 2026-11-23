---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x1800a2e40
nome: OpenDocumentHandler::Open (slot 1 da vtable 0x1802eab68)
endereco: 0x1800a2e40
confianca: media
xrefs: [0x1802eab70, 0x18041d048]
strings: []
---

# OpenDocumentHandler - metodo virtual do slot 1 (handler de abertura)

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`).
- Vtable `OpenDocumentHandler` @`0x1802eab68` (simbolo `vftable`, namespace
  `_anon_D86631B5::OpenDocumentHandler`); dump em
  `tools/ghidra_analysis/f005_vtables2.txt`:
  - slot 0 = `0x1800a2a70` (destrutor: chama `OpenFileHandler::~OpenFileHandler` e `free`)
  - slot 1 = `0x1800a2e40` (metodo sobrescrito; na vtable base `OpenFileHandler`
    @`0x1802ea970` o slot 1 e `_purecall`)
  - slot 2 = `0x180017220` (`DocumentIO::OpenFileHandler::Cancel`)
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs4.txt` (secao `## FN 1800a2e40`).

## Por que este e o handler de abertura
`DocumentIO::FileDispatcher::OpenFile` (@`0x1802160b0`) invoca o handler pelo slot 1
(`*(vtable + 8)`). Como o slot 1 desta vtable sobrescreve o `_purecall` da base, este
endereco e a implementacao de `Open` para documentos. Inferencia sustentada por tres
fatos observados: vtable derivada com slot 1 concreto, chamada de `OpenFile` pelo mesmo
slot, e o corpo abaixo criar o `ArtDoc::Document`.

## Assinatura observada
`path* __thiscall FUN_1800a2e40(OpenDocumentHandler*, path* out, ArtDoc::ReadOptions const&)`

## O que faz (observado)
1. `ArtDoc::Document::Create(path, options)` (@`0x180094e10`) - cria o documento.
2. `boost::filesystem::detail::path_algorithms::filename_v3` +
   `ExtraBoostFilesystem::ToUTF8String` - extrai o nome do arquivo.
3. `ArtDoc::Document::SetTitle(document, filename)` (@`0x18009c080`) - titulo inicial do
   documento = nome do arquivo.
4. Devolve o `unique_ptr<Document>` em `out`.

## Chamadas de saida confirmadas
- `0x180094e10` ArtDoc::Document::Create(path, ReadOptions)
- `0x18009c080` ArtDoc::Document::SetTitle
- `EXTERNAL:0000012b` ExtraBoostFilesystem::ToUTF8String
- `EXTERNAL:0000012d` boost::filesystem::path_algorithms::filename_v3

## Confianca
`media` - o corpo e o papel do slot foram observados; o **nome** `Open` e inferido da
posicao na vtable e do ponto de chamada em `OpenFile`, nao de um simbolo com nome
`OpenDocumentHandler::Open` (o binario so tem o RTTI/vtable da classe anonima).
