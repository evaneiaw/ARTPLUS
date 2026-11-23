# F-005 — Arquitetura da abertura de documento PDF

> **Estado deste documento.** Descreve o que **existe** no ArtPlus em 2026-11-21, conferido
> por leitura de `src/pdf/pdf_document.h/.cpp`, `src/pdf/pdf_importer.h/.cpp`,
> `src/ui/main_window.h/.cpp`, `src/app/main.cpp` e `src/document/document_serializer.h/.cpp`.
> A decisão registrada está em **`ADR-013`** (fonte de verdade); este documento é a visão de
> módulo. Versão de referência do original: **v24.03.10017**; evidência em
> `rag/evidence/F-005/`, laudo em `docs/audit/F-005-audit-20261121b.md`.
>
> A redação anterior deste arquivo — `PDFAccessLayer::readPageBoxes()`,
> `PDFObjectLayer::parseObjectStream()`, `ArtDoc::loadFromPdf()` — **não corresponde a
> código nenhum** do ArtPlus e foi substituída.

## 1. Visão geral

A funcionalidade é a mesma nos dois lados: abrir um documento e entregá-lo ao viewport, sem
diálogo intermediário de importação. O **caminho interno** difere em um ponto estrutural:

| | ArtPro+ v24.03.10017 (original) | ArtPlus (clone) |
|---|---|---|
| Entrada | um comando `File > Open...`, filtro único `All supported documents (*.pdf; *.pdpdla; *.ap; *.art)` | dois comandos: `Open PDF...` e `Open .artplus...` |
| Seleção de handler | despacho por **MIME** (`FileDispatcher::OpenFile`) para handler registrado | escolha pela **ação de menu**; sem MIME, sem registro |
| Leitura do PDF | delegada a `PDFOBJECTLAYER.DLL::GODocument` (import externo) | **parser próprio** em `src/pdf/` |
| Modelo | `ArtDoc::Document` (`Document.dll`) | `ArtPlus::Document` (modelo do clone) |
| Contagem de páginas | campo `godo+0x1A0` + `UpdateNumPagesCache` | `PDF::PdfDocument::pageCount()` |
| Erros | `ArtDoc::DocumentOpenException(path, 0/1/2/3/7)` → `ERROR_FILE_*` | `bool` e `PdfImportResult::error` (texto) |
| Documento nativo | formatos `*.pdpdla`, `*.ap`, `*.art` no mesmo filtro (não exercitados em `CAP-20261121-01`) | `.artplus` JSON (`DocumentSerializer`), formato do clone |

Nenhuma DLL Esko é carregada, linkada ou chamada pelo clone: `PDFAccessLayer.dll`,
`PDFObjectLayer.dll` e `Document.dll` são **referência de comportamento** (evidência), não
dependência de runtime.

## 2. Responsabilidades por módulo (clone)

| Módulo / arquivos | Responsabilidade | Não faz |
|---|---|---|
| `src/pdf/pdf_document.*` (+ `pdf_lexer.*`, `pdf_parser.h`, `pdf_types.*`) | ler bytes, validar `%PDF-`, `startxref`, objetos `N G obj … endobj`, catálogo `/Root`, páginas, streams decodificados | não conhece UI, modelo de documento nem erro tipado |
| `src/pdf/pdf_content.*` | interpretar content stream em operações de path/texto/imagem | não cria objetos de documento |
| `src/pdf/pdf_importer.*` | converter `PdfDocument` → `Document`: `Page`, `Layer`, `Path`/`Text`/`Image`, `PdfImportResult` | não abre arquivo, não mexe em UI nem em histórico |
| `src/document/document_model.*` | modelo de documento (`Document`, `Page`, `Layer`, objetos, `clear()`) | não lê PDF |
| `src/document/document_serializer.*` | `.artplus` JSON (`save`/`load`/`compare`) | não lê PDF |
| `src/ui/main_window.*` | orquestrar abertura, substituir o documento corrente, recarregar managers de marcas, reconstruir a cena | não parseia PDF nem serializa |
| `src/app/main.cpp` | abrir por linha de comando (`--open`) reusando `openPdfPath` | — |

## 3. Dependências permitidas e proibidas

**Permitidas**

- `src/pdf/pdf_document.*`, `pdf_lexer.*`, `pdf_parser.h`, `pdf_types.*` → QtCore (`QFile`,
  `QByteArray`, `QString`) e QtZlib (`<QtZlib/zlib.h>`, para `FlateDecode`). Nada de
  `src/document/`, `src/ui/` ou `src/prepress/`.
- `src/pdf/pdf_importer.*` → `pdf_document.h`, `pdf_content.h` e
  `../document/document_model.h` (é a fronteira de conversão).
- `src/document/document_serializer.*` → `document_model.h` e QtCore (`QJsonObject`,
  `QJsonDocument`).
- `src/ui/main_window.*` e `src/app/main.cpp` → `src/pdf/`, `src/document/`, managers de
  marcas e `src/prepress/` (são o *composition root*).

**Proibidas**

- `src/pdf/` ou `src/document/` dependerem de `src/ui/` (regra de negócio não sobe para a
  UI) ou de tipos de `QGraphicsScene`.
- `src/document/` depender de `src/pdf/` (o modelo não conhece formato de arquivo).
- Qualquer `#include`, `LoadLibrary` ou `QLibrary` das DLLs Esko (`Document.dll`,
  `PDFAccessLayer.dll`, `PDFObjectLayer.dll`) em código do clone.
- Parse de arquivo dentro de `src/ui/` (a UI só chama `openPdfPath`/`openArtPlus`).

## 4. O que o binário faz (original v24.03.10017)

Somente funções com evidência estática em `rag/evidence/F-005/ghidra/`; a última linha é a
captura comportamental (`CAP-20261121-01`). O parse do PDF **não** está nesta lista porque
não pertence a `Document.dll`: é delegado a `PDFOBJECTLAYER.DLL::GODocument` (import externo,
ponto marcado como inferência `media` na evidência e declarado em F-005 §8.4).

| Evidência | Função | O que prova |
|---|---|---|
| `GHIDRA-Document-0x1802160B0` | `DocumentIO::FileDispatcher::OpenFile(path, ReadOptions)` | `status(path) < 2` → exceção 0; obtém MIME, busca no `std::map`; chave ausente → exceção 7; `AddToOpeningFiles`; handler pelo slot 1 da vtable |
| `GHIDRA-Document-0x180216270` | `FileDispatcher::RegisterFileHandler(mime, handler)` | registro no mapa; chave duplicada ignorada (inferência declarada) |
| `GHIDRA-Document-0x1800A1230` | inicialização do DocumentLayer | `File handlers registered (6/7)`; dois call sites; chave `"application/illustrator"`; ausência de registro de `"application/pdf"` neste módulo (observação negativa) |
| `GHIDRA-Document-0x1800A2E40` | handler de abertura (slot 1) | `Document::Create` → `SetTitle(filename)` → devolve `unique_ptr<Document>` |
| `GHIDRA-Document-0x180094E10` | `ArtDoc::Document::Create(path, ReadOptions)` | aloca `0x330` e chama o construtor |
| `GHIDRA-Document-0x18008F590` | construtor de abertura | `status`, até 5 tentativas read/write, `Security` (`GetEncryptionType`/`IsEncrypted`/`GetPermissions`), `Cache`, construção do `GODocument` |
| `GHIDRA-Document-0x180093D60` | `ArtDoc::Document::Cache` | conta `godo+0x1A0` (ou `UpdateNumPagesCache`); cria `ArtDoc::Page`; sem páginas → log `"Document: File has no pages"` + exceção 2 |
| `GHIDRA-Document-0x180083F80` | `ContentTracker::AddPageToDocument` | ponto único de registro de página |
| `GHIDRA-Document-0x1800973A0` / `0x1800973D0` | `GetPagesBegin` / `GetPagesEnd` | iteradores sobre `[this+0x1B0, this+0x1B8)` |
| `GHIDRA-Document-0x180097960` / `0x180097AB0` | `InsertPage(box, Part)` / `InsertPage(box, iterator)` | **inserção**, não abertura (mesmo vetor e `AddPageToDocument`) |
| `GHIDRA-Document-0x1800A0EC0` | mapa de código → nome | `0→ERROR_FILE_NOT_FOUND`, `1→…ACCESS_DENIED`, `2→…INVALID`, `3→…WRONG_PASSWORD`, outro→`…UNKNOWN` |
| `GHIDRA-Document-0x180094F40` | mapeamento de criptografia | pertence a `Document::Save` (F-006), **não** à abertura |
| `Document__identity.md` | identidade | SHA-256 `DA91E285…FA9E21`, 4.421.040 bytes, 12.793 funções |
| `CAP-20261121-01` | comportamento na GUI real | filtro literal único, sem diálogo de importação, título `test_vector.pdf @ 96,45% – ArtPro+`, input inalterado |

Contrato de erro observado: `ArtDoc::DocumentOpenException(path, codigo)`, com a descrição
simbólica vinda de `0x1800A0EC0` (F-005 §5).

## 5. O que o clone faz

Espelho fiel de `ADR-013` (decisões 1–5):

1. **Parser PDF próprio em `src/pdf/`.** `ArtPlus::PDF::PdfDocument` lê o arquivo, rejeita
   conteúdo menor que 16 bytes ou sem cabeçalho `%PDF-`, localiza `startxref`, varre os
   objetos (`parseAll`), resolve `/Root` e as páginas. Qualquer falha devolve `false`, sem
   posição de falha. `pdf_exporter.*` atende exportação (F-006), não a abertura.
2. **Importação por `ArtPlus::PdfImporter`.** `PdfImporter::import(const PDF::PdfDocument&,
   Document&)` devolve `PdfImportResult` (`ok`, `error`, `warnings`, contagens). Limpa o
   destino (`out.clear()`), cria uma `Page` e uma `Layer` `Page N` por página, converte o
   content stream em `Path`/`Text`/`Image`, acumula não suportados em `warnings`. Sem páginas
   → `ok = false`, `error = "PDF has no pages"`.
3. **UI orquestra.** `ArtPlusMainWindow::openPdfPath(const QString&)` é o ponto único;
   `openPdf()` é o slot do menu `Open PDF...` (`QFileDialog`, filtro `PDF Files (*.pdf)`);
   `src/app/main.cpp` (`--open`) usa o mesmo caminho.
4. **`.artplus` por `ArtPlus::DocumentSerializer`.** `openArtPlus()` chama
   `DocumentSerializer::load(path, Document&)` (JSON) e mostra `QMessageBox::critical` em
   falha.
5. **Sem vínculo em runtime com as DLLs Esko.** `ArtDoc`, `GODocument` e as interfaces
   proprietárias não são usados; o clone tem modelo próprio (`ArtPlus::Document`).

## 6. Fluxo de dados (clone)

```
PDF:
  menu "Open PDF..."  ──► openPdf()                      [main_window.cpp]
      QFileDialog filtro "PDF Files (*.pdf)"
        └─► openPdfPath(path)
              ├─ PDF::PdfDocument::open(path)            [pdf_document.cpp]
              │     %PDF-, startxref, parseAll, /Root, páginas
              ├─ m_document = Document()                 (substitui o corrente)
              ├─ PdfImporter::import(pdf, m_document)    [pdf_importer.cpp]
              │     out.clear(); Page + Layer "Page N"; content stream
              │     → Path/Text/Image; warnings
              ├─ setFilePath / setModified(false)
              ├─ m_history.clear()
              ├─ managers de marcas .loadFromMetadata()
              └─ rebuildScene() → updateDocumentInfo() → updateModifiedIndicator()

.artplus:
  menu "Open .artplus..." ──► openArtPlus()              [main_window.cpp]
      QFileDialog filtro "ArtPlus Files (*.artplus *.json)"
        └─► DocumentSerializer::load(path, doc)          [document_serializer.cpp]
              falha → QMessageBox::critical; sucesso → m_document = doc

linha de comando:
  main --open <pdf> ──► openPdfPath(path)                [app/main.cpp]
```

Detalhes que o desenho precisa preservar:

- `openPdfPath` devolve `bool` e **não** mostra mensagem: quem decide o feedback é o chamador.
- A substituição de `m_document` acontece **depois** de `PdfDocument::open` ter sucesso e
  **antes** de `PdfImporter::import`; se a importação falhar, o documento anterior já foi
  descartado (não há restauração).
- `PdfImporter::import` devolve `ok = true` mesmo com `warnings` (recursos não suportados e
  anotações).
- Cada página recebe uma `Layer` própria (`Page N`) e as cinco caixas recebem a **mesma
  área** (ver §8, caixas de página).

## 7. Mapeamento binário → clone

| Função (original, Ghidra) | Classe/método do clone | Observação |
|---|---|---|
| `GHIDRA-Document-0x1802160B0` `FileDispatcher::OpenFile` | `ArtPlusMainWindow::openPdf()` / `openArtPlus()` | despacho pela ação de menu; sem MIME (R2) |
| `GHIDRA-Document-0x1800A2E40` handler (slot 1) | `ArtPlusMainWindow::openPdfPath()` | cria/substitui o `Document`; devolve `bool` |
| `GHIDRA-Document-0x180094E10` + `0x18008F590` | `PDF::PdfDocument::open()` + `PdfImporter::import()` | parser próprio no lugar do `GODocument` |
| `GHIDRA-Document-0x180093D60` `Cache` | `PDF::PdfDocument::pageCount()` + laço de import | sem `UpdateNumPagesCache` |
| `GHIDRA-Document-0x180083F80` `AddPageToDocument` | `Document::addPage()` (via importador) | registro de página |
| `GHIDRA-Document-0x1800A0EC0` mapa de erro | `PdfImportResult::error` (texto) | sem enum `ERROR_FILE_*` (§5) |
| `GHIDRA-Document-0x180216270` / `0x1800A1230` | — | **não implementado**: sem registro de handler (R3) |
| `PDFOBJECTLAYER.DLL::GODocument` (externo) | `PDF::PdfDocument` | substituto; DLL Esko não é carregada |
| — (sem equivalente: formato do clone) | `DocumentSerializer::load()` | `.artplus` JSON |

## 8. Divergências declaradas (não maquiadas)

| # | Regra / item | Original (v24.03.10017) | Clone | Situação |
|---|---|---|---|---|
| R1 | comando e filtro | um `Open...`; filtro `*.pdf; *.pdpdla; *.ap; *.art` | `Open PDF...` + `Open .artplus...`; filtros `*.pdf` e `*.artplus *.json` | parcial — formatos Esko não reconhecidos |
| R2 | despacho por MIME | `FileDispatcher::OpenFile` (`0x1802160B0`), exceções 0/7 | escolha pela ação de menu; não há MIME | ausente |
| R3 | registro de handler | `RegisterFileHandler` (`0x180216270`) na inicialização (`0x1800A1230`) | não existe | ausente |
| §5 | códigos de erro | `DocumentOpenException` 0/1/2/3/7 → `ERROR_FILE_*` | `false` + texto em `PdfImportResult::error` | ausente |
| R6 | sem páginas | log + exceção 2 (`ERROR_FILE_INVALID`) | `ok = false`, `error = "PDF has no pages"` | parcial — sem exceção tipada |
| R8 | título e zoom | título inicial = nome do arquivo (`SetTitle`, `0x18009C080`); janela mostra `arquivo @ zoom – ArtPro+` | título fixo `ArtPlus` (+ ` *` se modificado) | sem equivalente |
| R9 | relayout ao abrir painel | zoom `96,45%` → `64,00%` (`CAP-20261121-01`) | não medido / não implementado | sem equivalente |
| — | caixas de página | caixas expostas separadamente (overlay `Media Box 210,00 x 297,00 mm` e painel `Page Boxes` em `CAP-20261121-01`) | `PdfImporter` grava as cinco caixas com a **mesma área** derivada do `cropBox`; a geometria que `PDF::PdfDocument::pageGeometry` lê (com herança do MediaBox) é descartada na importação | divergência declarada |
| D-01 | feedback de falha na UI | exceção propagada ao chamador | `openPdf()` ignora o retorno de `openPdfPath()` e anuncia `Imported <arquivo>` **mesmo em falha** (`main_window.cpp:955-959`); `openArtPlus()` faz o certo (`QMessageBox::critical`) | defeito conhecido — laudo F-005, ressalva d; correção posterior |

Cobertura de teste (ressalva f do laudo): `PdfRoundTrip` prova o modelo — `PdfDocument::open`
no fixture `test_vector.pdf` (`pageCount() == 1`), import de 5 paths/1 texto/6 objetos/1
página, round-trip `.artplus`, imagens, multipágina, clipping mask e Form XObject. **Não**
prova UI, diálogo, filtro, MIME, códigos de erro nem `*.pdpdla/*.ap/*.art`.

Risco (ressalva b): o parser não tem evidência própria para xref corrompido, streams
comprimidos e fontes; o original delega esse trecho a `PDFObjectLayer.dll`, fora do manifest
de F-005.

## 9. Pontos de extensão

1. **Despacho por MIME (R2/R3).** Ponto natural é uma camada de despacho entre a UI e o
   parser, com mapa MIME → handler; hoje `openPdfPath` é o único ponto de entrada, então a
   troca não afeta os chamadores. Implementar exige ADR própria (contrato novo atravessa
   módulos).
2. **Erros tipados (§5).** `PdfImportResult` já carrega `error`; um enum de erro pode ser
   acrescentado sem mudar a assinatura de `import`.
3. **Caixas de página.** `PDF::PdfDocument::pageGeometry` já entrega as cinco caixas com
   herança; preservá-las no modelo é mudança local em `PdfImporter` (mais o modelo, se
   necessário).
4. **Novos recursos de PDF** (xref stream robusto, fontes, transparência): `pdf_document.*` e
   `pdf_content.*`; o importador só precisa mapear o resultado.
5. **Outros formatos Esko** (`*.pdpdla`, `*.ap`, `*.art`): mesmo padrão do item 1 — um
   importador por formato atrás de um despacho, sem tocar no modelo.

## 10. O que NÃO entra neste módulo

- **Renderização e interação**: `QGraphicsScene`, itens, zoom, relayout de painéis (R8/R9).
  `rebuildScene()` apenas consume o modelo já carregado.
- **Salvamento e exportação** (F-006): `DocumentSaveManager`, `DocumentSerializer::save` e
  `src/pdf/pdf_exporter.*` são caminhos de escrita, não de abertura.
- **Marcas** (F-001…F-004): a abertura apenas recarrega `m_cutMarkManager`,
  `m_bearerBarManager` e `m_selectionMarkManager` a partir dos metadados do documento.
- **Prepress** (trapping, separações, screening): consome o documento depois de aberto.
- **Cópia de código Esko**: nenhuma DLL proprietária é carregada, e nenhuma interface
  `ArtDoc`/`GODocument` é reproduzida.

## 11. Rastreabilidade

- Spec: `docs/features/F-005.md` (inclui §7.3 e §8).
- Decisão: `docs/decisions/ADR-013-open-document.md` (aceita).
- Laudo: `docs/audit/F-005-audit-20261121b.md` (ressalvas b, d, e, f).
- Evidência estática: `rag/evidence/F-005/ghidra/` (14 IDs + `Document__identity.md`).
- Evidência comportamental: `CAP-20261121-01` → `docs/behavior/F-005-open-document.md`,
  capturas em `rag/evidence/F-005/behavior/shot-01…shot-07-*.png`.
- Código: `src/pdf/`, `src/ui/main_window.*`, `src/app/main.cpp`, `src/document/`.
