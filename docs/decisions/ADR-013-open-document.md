# ADR-013 — Abertura de documento PDF (F-005)

## Contexto

Spec `F-005` (Open Document), alvo **v24.03.10017**. Evidência estática de `Document.dll`
(SHA-256 `DA91E28574C877D392D3E6BEF9CCBB7C4DCF3117EBD03655DE89834FC8FA9E21`, 4.421.040 bytes):
`GHIDRA-Document-0x1802160B0`, `0x180216270`, `0x1800A2E40`, `0x180094E10`, `0x18008F590`,
`0x180093D60`, `0x1800A0EC0`. Evidência comportamental: `CAP-20261121-01`. Laudo vigente:
`docs/audit/F-005-audit-20261121b.md` (ressalva **e**).

O ArtPro+ real despacha a abertura por **MIME** (`DocumentIO::FileDispatcher::OpenFile`,
`0x1802160B0`), invoca o handler registrado (`0x1800A2E40`), constrói `ArtDoc::Document`
(`0x180094E10` / `0x18008F590`) e conta páginas em `ArtDoc::Document::Cache` (`0x180093D60`).
O parse do PDF **não** está nesse módulo: é delegado a `PDFOBJECTLAYER.DLL::GODocument`
(import externo; ponto marcado como inferência `media` na evidência e declarado em F-005 §8.4).

O código do ArtPlus **não** reproduz essa arquitetura de DLLs: existe parser PDF próprio em
`src/pdf/` e o importador é chamado diretamente pela UI. A redação anterior desta ADR
("nenhum serviço de parsing de PDF será implementado do zero", `Estado: proposto`) negava o
código real; esta versão a substitui pelo desenho que existe.

## Decisão

1. **Parser PDF próprio em `src/pdf/`.** `ArtPlus::PDF::PdfDocument`
   (`src/pdf/pdf_document.h/.cpp`) lê o arquivo, rejeita conteúdo menor que 16 bytes ou sem
   cabeçalho `%PDF-`, localiza `startxref`, varre os objetos `N G obj … endobj`
   (`parseAll`), resolve `/Root` e as páginas; qualquer falha devolve `false`, sem posição de
   falha. Completam o módulo o lexer/parser (`src/pdf/pdf_lexer.*`, `src/pdf/pdf_parser.h`),
   os tipos (`src/pdf/pdf_types.*`) e o content stream (`src/pdf/pdf_content.*`).
   (`src/pdf/pdf_exporter.*` pertence ao caminho de exportação, não à abertura.)
2. **Importação para o modelo de domínio por `ArtPlus::PdfImporter`**
   (`src/pdf/pdf_importer.h/.cpp`). `PdfImporter::import(const PDF::PdfDocument&, Document&)`
   devolve `PdfImportResult` (`ok`, `error`, `warnings`, contagens). O importador limpa o
   destino (`out.clear()`), cria uma `Page` e uma `Layer` `Page N` por página, converte o
   content stream em `Path`/`Text`/`Image` e acumula recursos não suportados em `warnings`.
   As cinco caixas são **gravadas com a mesma área** `0,0,largura,altura` derivada do
   `cropBox`; a geometria por caixa que `PDF::PdfDocument::pageGeometry` lê (MediaBox
   explícita; CropBox/BleedBox/TrimBox/ArtBox herdadas do MediaBox quando ausentes) não é
   preservada no modelo. Documento sem páginas → `ok = false` e
   `error = "PDF has no pages"`.
3. **A UI orquestra a abertura de PDF.** `ArtPlusMainWindow::openPdfPath(const QString&)`
   (`src/ui/main_window.cpp`) é o ponto único: `PdfDocument::open` →
   `PdfImporter::import` sobre `m_document` → `setFilePath`/`setModified(false)` →
   `m_history.clear()` → recarga de `m_cutMarkManager`/`m_bearerBarManager`/
   `m_selectionMarkManager` → `rebuildScene()` → `updateDocumentInfo()` →
   `updateModifiedIndicator()`; devolve `bool`. `openPdf()` é o slot do menu `Open PDF...`
   (`QFileDialog` com filtro `PDF Files (*.pdf)`). `src/app/main.cpp` (opção `--open`) usa o
   mesmo `openPdfPath`.
4. **`.artplus` é aberto por `ArtPlus::DocumentSerializer`** (`src/document/`).
   `openArtPlus()` chama `DocumentSerializer::load(path, Document&)` sobre o JSON `.artplus`
   e mostra `QMessageBox::critical` em falha. Esse formato é do clone; não existe no ArtPro+.
5. **Sem vínculo em runtime com as DLLs Esko.** `PDFAccessLayer.dll` e `PDFObjectLayer.dll`
   são referência de comportamento (evidência de F-005), não dependência carregada: o clone
   não exporta `ArtDoc`, não chama `GODocument` e não usa as interfaces proprietárias.

## Mapeamento binário → ArtPlus

| Função (Ghidra) | Classe/método ArtPlus | Observação |
|---|---|---|
| `GHIDRA-Document-0x1802160B0` `FileDispatcher::OpenFile` | `ArtPlusMainWindow::openPdf()` / `openArtPlus()` | divergência: o clone escolhe a ação de menu; não há despacho por MIME (R2) |
| `GHIDRA-Document-0x1800A2E40` handler de abertura (slot 1 da vtable) | `ArtPlusMainWindow::openPdfPath()` | cria/substitui o `Document` e devolve `bool` |
| `GHIDRA-Document-0x180094E10` `Document::Create` + `GHIDRA-Document-0x18008F590` construtor | `PDF::PdfDocument::open()` + `PdfImporter::import()` | parser próprio substitui o `GODocument` |
| `GHIDRA-Document-0x180093D60` `Document::Cache` (contagem de páginas) | `PDF::PdfDocument::pageCount()` + laço de `PdfImporter::import()` | contagem pelo parser; sem `UpdateNumPagesCache` |
| `GHIDRA-Document-0x1800A0EC0` mapa código → `ERROR_FILE_*` | `PdfImportResult::error` (texto) | sem enum de erro tipado (§5) |
| `GHIDRA-Document-0x180216270` `RegisterFileHandler` + `0x1800A1230` inicialização | — | **não implementado**: não há registro de handler (R3) |
| `PDFOBJECTLAYER.DLL::GODocument` (import externo) | `PDF::PdfDocument` | parse próprio; a DLL Esko não é carregada |
| — (sem função equivalente: formato do clone) | `DocumentSerializer::load()` | `.artplus` JSON |

## Contrato de interface

Assinaturas reais do código (não proposta):

```cpp
// src/pdf/pdf_document.h
namespace ArtPlus { namespace PDF {
class PdfDocument {
public:
    bool open(const QString& filePath);
    bool isOpen() const;
    int pageCount() const;                                  // m_pageRefs.size()
    const DocumentInfo& info() const;
    PageGeometry pageGeometry(int pageIndex) const;          // unidades PDF (1/72 in)
    PdfValue pageResources(int pageIndex) const;
    QByteArray pageContents(int pageIndex) const;            // stream decodificado
    const PdfObject* findObject(int obj, int gen) const;
};
} }  // namespace ArtPlus::PDF

// src/pdf/pdf_importer.h
struct PdfImportResult {
    int pagesImported = 0;
    int objectsImported = 0;
    int pathsImported = 0;
    int textsImported = 0;
    int imagesImported = 0;
    std::vector<QString> warnings;
    bool ok = false;
    QString error;
};

class PdfImporter {
public:
    static PdfImportResult import(const PDF::PdfDocument& doc, Document& out);
};

// src/document/document_serializer.h
class DocumentSerializer {
public:
    static bool save(const Document& doc, const QString& filePath);
    static bool load(const QString& filePath, Document& out);
};

// src/ui/main_window.h
class ArtPlusMainWindow {
    bool openPdfPath(const QString& path);   // ponto único da abertura de PDF
    void openPdf();                          // slot do menu "Open PDF..."
    void openArtPlus();                      // slot do menu "Open .artplus..."
};
```

## Alternativas descartadas

1. **Delegar a `PDFAccessLayer.dll`/`PDFObjectLayer.dll`** (redação anterior desta ADR) —
   descartada: não corresponde ao código. O clone não carrega as DLLs Esko nem expõe
   `ArtDoc`; o parser em `src/pdf/` já existe e é o que a UI chama. A referência binária
   permanece apenas como comportamento do original (F-005 §7.3).
2. **Biblioteca externa de PDF (ex.: Poppler)** — descartada: dependência nova exigiria
   auditoria de licença própria, e o parser existente já sustenta a leitura/importação
   coberta por `PdfRoundTrip`.
3. **Implementar agora o despacho por MIME e o registro de handler** — **não decidido nesta
   ADR**: exigiria `FileDispatcher`/`RegisterFileHandler`, ausentes em `src/`. Fica como
   pendência declarada de F-005 (R2/R3), não como decisão tomada.

## Consequências

**Arquivos abrangidos:** `src/pdf/pdf_document.h/.cpp`, `src/pdf/pdf_importer.h/.cpp`
(e dependências `pdf_lexer.*`, `pdf_parser.h`, `pdf_types.*`, `pdf_content.*`),
`src/ui/main_window.h/.cpp`, `src/app/main.cpp`, `src/document/document_serializer.h/.cpp`,
`src/document/document_model.*`, `CMakeLists.txt`.

**O que está implementado** (conferido no código em 2026-11-21): parser próprio, importador
para o modelo, dois comandos de abertura na UI, `--open` na linha de comando e carregamento
`.artplus` por `DocumentSerializer`.

**Divergências em relação ao ArtPro+ v24 — declaradas, não resolvidas aqui** (F-005 §7.3,
§8 e laudo §7):

- **R1** — o clone tem dois comandos (`Open PDF...`, `Open .artplus...`) e filtros sem
  `*.pdpdla`/`*.ap`/`*.art`; o original tem um comando e um filtro único.
- **R2/R3** — sem despacho por MIME e sem registro de handler.
- **§5** — sem os códigos `ERROR_FILE_*`; `PdfDocument::open()` devolve `false` sem detalhar
  a falha, e o caminho "sem páginas" é `PdfImportResult::error`, não exceção tipada.
- **Caixas de página** — `PdfImporter` achata `mediaBox`/`cropBox`/`bleedBox`/`trimBox`/
  `artBox` numa única área derivada do `cropBox`; a distinção lida pelo parser não chega ao
  modelo.
- **R8/R9** — sem equivalente de título derivado do arquivo, zoom inicial e relayout.
- **Defeito conhecido (laudo, ressalva d)** — `openPdf()` ignora o retorno de
  `openPdfPath()` e anuncia `Imported <arquivo>` mesmo em falha; `openArtPlus()` faz o
  correto. Correção posterior, fora do escopo documental desta ADR.

**Risco:** a cobertura do parser (xref corrompido, streams, fontes) não tem evidência
própria; `PdfRoundTrip` prova o modelo (fixture `test_vector.pdf`, 1 página, 6 objetos), não
a UI, o despacho nem os códigos de erro (laudo, ressalvas b e f).

**Migração de dados:** nenhuma; `.artplus` é JSON e o formato de documento não muda.

## Estado

aceito (2026-11-21) — confere com `src/pdf/`, `src/ui/main_window.cpp`,
`src/app/main.cpp` e `src/document/document_serializer.*`.
