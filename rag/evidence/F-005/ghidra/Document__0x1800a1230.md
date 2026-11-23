---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x1800a1230
nome: DocumentLayer init - registro de file handlers (FUN_1800a1230)
endereco: 0x1800a1230
confianca: alta
xrefs: [0x1800a2c39, 0x18041cf64]
strings: ["Start DocumentLayer (0/7)", "Font caching done (1/7)", "Enfocus PDFLib initialized (2/7)", "Mark/PieceInfo readers and writers installed (4/7)", "Reuse Form queries installed (5/7)", "File handlers registered (6/7)", "Install default content post readers (7/7)", "application/illustrator"]
---

# Inicializacao do DocumentLayer: registro dos handlers de abertura

## Identidade e prova
- Programa `Document.dll` v240 (`executableSHA256=da91e285...fa9e21`).
- Pseudocodigo bruto: `tools/ghidra_analysis/f005_refs2.txt` (secao `## FN 1800a1230`).
- Chamado por `FUN_1800a2c10` (@`0x1800a2c10`, chamada em `0x1800a2c39`), que por sua vez
  e referenciado por `ArtDoc::Initialize` (@`0x1800a2e00`): ou seja, roda na inicializacao
  do modulo, antes de qualquer abertura.

## O que faz (observado)
Sequencia de inicializacao com log de progresso "n/7":
1. `document.documentlayer`, "Start DocumentLayer (0/7)"; font caching, "Font caching
   done (1/7)"; "Enfocus PDFLib initialized (2/7)"; CMS ("BGCMS ... initialized (3/7)").
2. Instala readers/writers de marcas e PieceInfo: `ArtDoc::RegisterMarkReader`,
   `ArtDoc::RegisterPieceInfoReader`, `ArtDoc::RegisterPieceInfoWriter`,
   `ArtDoc::RegisterTypeMarkWriter`, `ArtDoc::RegisterPropertyMarkWriter`,
   `ArtDoc::RegisterFormDefinitionPieceInfoReader` -> log
   "Mark/PieceInfo readers and writers installed (4/7)".
3. `ArtDoc::RegisterReuseFormQuery` -> "Reuse Form queries installed (5/7)".
4. **Registro de handlers de arquivo**:
   `DocumentIO::FileDispatcher::GetInstance` (@`0x180215f60`) e duas chamadas a
   `DocumentIO::FileDispatcher::RegisterFileHandler` (@`0x180216270`, call sites
   `0x1800a1db6` e `0x1800a1e20`), ambas com a chave `"application/illustrator"`
   (string @`0x1802eac60`, refs `0x1800a1e01` e `0x1800a1e08`) -> log
   "File handlers registered (6/7)".
5. `ArtDoc::RegisterContentPostReader` -> "Install default content post readers (7/7)".
6. Tambem inicializa camadas externas: `COLORMANIPULATIONLAYER` (`Initialize`,
   `PushLevel`), `CMS.DLL::TCMS_Init`, `PDFOBJECTLAYER::GOPDFObjectLayer::Initialize`,
   `GODocument`/`GOErrorReporter` e `BASICFRAMEWORKCORELAYER::GBasicFrameworkCoreLayer::Initialize`.

## Sobre o handler de PDF (lacuna declarada)
- A string `"application/pdf"` existe no binario em `0x1802eaae8`, mas o unico xref e de
  dados (`0x1802eaad8`), nao de codigo. Nenhuma chamada a `RegisterFileHandler` com
  `"application/pdf"` foi observada neste modulo (`f005_refs3.txt`).
- Conclusao observada: o registro do handler de PDF **nao ocorre no Document.dll**; o
  dispatcher aceita MIME que tenha handler registrado, e o parse do PDF e delegado ao
  `PDFOBJECTLAYER.DLL::GODocument` (ver `GHIDRA-Document-0x18008F590`).

## Confianca
`alta` - ordem das chamadas, strings de log e os dois call sites de
`RegisterFileHandler` foram lidos no pseudocodigo. A conclusao sobre "application/pdf"
e observacao negativa registrada com o dump de xrefs correspondente.
