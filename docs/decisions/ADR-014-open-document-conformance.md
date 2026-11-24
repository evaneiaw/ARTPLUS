---
id: ADR-014
feature: F-005
titulo: Conformidade da abertura de documento — lacunas R1/R2/R3/R4/R6/R8/R9/§5
Estado: aceito
data: 2026-11-23
versao_ref: 24.03.10017
autor: arquitetura
---

# ADR-014 — Conformidade da abertura de documento (F-005)

**Estado: aceito** — aprovado para implementação em 2026-11-23, no despacho que reabre as
lacunas de conformidade de `F-005`. Esta ADR **não altera** `ADR-013-open-document.md`; ela
substitui apenas o item 3 de "Alternativas descartadas" daquela ADR
("não decidido nesta ADR") e a lista de divergências "não resolvidas aqui" **nos itens
nominalmente autorizados abaixo** (R1, R2, R3, R4, R6, R8, R9 e §5). R5, R7, caixas de página
e painéis prepress não são reabertos por esta decisão.

## Contexto

A spec `F-005` (versão de referência `24.03.10017`) define, com evidência rastreável:

- `GHIDRA-Document-0x1802160B0` — `DocumentIO::FileDispatcher::OpenFile`: `status(path) < 2`
  → exceção `0`; MIME sem entrada no mapa → exceção `7`; chamada do handler pelo slot 1;
  guarda `AddToOpeningFiles`/`RemoveFromOpeningFiles` (`0x180215D50`/`0x180216380`).
- `GHIDRA-Document-0x180216270` — `RegisterFileHandler`; `0x1800A1230` — registro na
  inicialização do DocumentLayer (`File handlers registered (6/7)`).
- `GHIDRA-Document-0x1800A2E40` — handler de abertura: `Document::Create` → `SetTitle(filename)`
  → retorno; `0x18009C080` é `SetTitle`.
- `GHIDRA-Document-0x180093D60` — `Document::Cache`: contagem de páginas e exceção `2`
  (`Document: File has no pages`) quando o vetor fica vazio.
- `GHIDRA-Document-0x1800A0EC0` — mapa código → nome simbólico (`0`..`3`, demais →
  `ERROR_FILE_UNKNOWN`), reproduzido em F-005 §5.
- `CAP-20261121-01` — único comando `File > Open...`, diálogo nativo `Open File` com filtro
  literal `All supported documents (*.pdf; *.pdpdla; *.ap; *.art)`, nenhum diálogo de
  importação, título `test_vector.pdf @ 96,45% – ArtPro+`, overlay
  `Media Box  210,00 x 297,00 mm` (vírgula decimal) e queda de zoom `96,45% → 64,00%` ao
  abrir `Object Browser` (passo 12). É a única fonte de UI permitida (AGENTS.md §6.12,
  EXISTENCE-FIRST); nenhum menu, botão ou atalho é inventado aqui.

`ADR-013` está `aceito`, mas registrou R1/R2/R3/R4/R6/R8/R9/§5 como divergências não
resolvidas. O laudo `docs/audit/F-005-audit-20261123.md` (**REPROVADO**) exige exatamente
essas lacunas para aprovar a feature. Esta ADR é a decisão de arquitetura que as autoriza,
preservando o parser próprio em `src/pdf/`, o modelo em `src/document/` e a orquestração em
`src/ui/`, sem dependência nova.

## Decisão — autorização nominal (sem ambiguidade)

A presente ADR **autoriza a implementação imediata** das sete regras e da seção abaixo, nos
termos precisos desta tabela. Não há "não decidido" remanescente para os itens listados.

| Item | DECISÃO | Desenho autorizado (F-005 / evidência) |
|---|---|---|
| **R1** | **AUTORIZADO** | Um único `QAction` de abertura, com texto exibido literal `Open...`, no menu `File`; sem acelerador (F-005 §3 e §8.1 não medem `Ctrl+O`). Um único `QFileDialog` nativo (sem `DontUseNativeDialog`) com filtro default literal `All supported documents (*.pdf; *.pdpdla; *.ap; *.art)` (CAP-20261121-01 passos 4–8; F-005 §3). Os atuais `Open PDF...` e `Open .artplus...` deixam de existir como comandos de menu/barra. |
| **R2** | **AUTORIZADO** | `ArtPlus::FileDispatcher` com `std::map<QString, std::unique_ptr<OpenFileHandler>>` MIME → handler; `mimeTypeForPath()` determinístico por extensão; MIME sem handler → `OpenError::NoHandlerForMime`; handler chamado sob guarda de abertura equivalente a `AddToOpeningFiles`/`RemoveFromOpeningFiles` (`0x1802160B0`, F-005 §2/R2). |
| **R3** | **AUTORIZADO** | `registerBuiltinHandlers()` chamado **uma vez na inicialização** (construtor de `ArtPlusMainWindow`, raiz de composição usada por `src/app/main.cpp`), nunca dentro de `openDocumentPath()`. Chave duplicada é ignorada e o handler recebido é descartado, conforme a semântica inferida em F-005 R3. |
| **R4** | **AUTORIZADO** | `OpenResult::title` = `QFileInfo(filePath).fileName()` e `Document::setTitle()` / `Document::title()` no modelo; o título do documento passa a existir como contrato explícito (`0x1800A2E40` + `0x18009C080`, F-005 R4). |
| **R6** | **AUTORIZADO** | `PdfOpenHandler` rejeita `PdfDocument::pageCount() == 0` **ou** `PdfImportResult::pagesImported == 0` com `OpenError::FileInvalid` e mensagem `ERROR_FILE_INVALID` (`0x180093D60`, F-005 R6/§5). ArtPlus usa **retorno tipado** `OpenResult`, não `throw` através de slots Qt. |
| **R8** | **AUTORIZADO** | Título da janela `<arquivo> @ <zoom> – ArtPlus` (U+2013), com zoom em `%` e vírgula decimal; overlay `Media Box W x H mm`, `W`/`H` em milímetros (`mm = pt × 25,4 / 72`), também com vírgula decimal (CAP-20261121-01 passos 8 e 12; F-005 R8). Escopo desta ADR para R8 é título + overlay; painéis prepress do laudo não são criados aqui. |
| **R9** | **AUTORIZADO** | `relayoutViewport()` ligado a `visibilityChanged`/`topLevelChanged` dos `QDockWidget` existentes: recalcula `zoomFit()` da viewport e atualiza o título da janela (CAP-20261121-01 passo 12; F-005 R9). |
| **§5** | **AUTORIZADO** | Enum `OpenError { None, FileNotFound, FileAccessDenied, FileInvalid, WrongPassword, NoHandlerForMime, Unknown }` em `src/document/open_error.h`, com `openErrorMessage()` e as mensagens simbólicas da tabela abaixo (F-005 §5, `0x1800A0EC0`). |

### Exceção explícita — formato próprio `.artplus`

O clone **continua** abrindo `.artplus` (JSON, `DocumentSerializer`), que não tem
contraparte no ArtPro+ `24.03.10017`. Para não confundir com a UI do original:

- o filtro literal exigido por R1 permanece o **primeiro e default**;
- um **segundo** filtro, `ArtPlus documents (*.artplus)`, é uma exceção declarada do clone,
  acrescentada via separador `;;` do `QFileDialog`; não é atribuído à v24 e não altera R1;
- o handler `ArtPlusDocumentHandler` é registrado sob o MIME interno
  `application/vnd.artplus.document`;
- um arquivo `.pdpdla`, `.ap` ou `.art` aparece no filtro R1, mas **não** recebe handler
  falso: sem handler registrado, o resultado é `OpenError::NoHandlerForMime` (R2). Isso
  evita stub silencioso (AGENTS.md §6.6). Os MIMEs reais usados pelo original para essas
  extensões permanecem em aberto em F-005 §8.3 e **não** são inferidos aqui; os identificadores
  `application/vnd.artplus.*` são constantes internas do clone, não uma reclamação sobre o
  binário Esko.

### Tabela de mensagens simbólicas (§5)

| `OpenError` | Código original (F-005 §5) | Mensagem devolvida por `openErrorMessage()` |
|---|---|---|
| `None` | — (sucesso) | `QString()` |
| `FileNotFound` | `0` | `ERROR_FILE_NOT_FOUND` |
| `FileAccessDenied` | `1` | `ERROR_FILE_ACCESS_DENIED` |
| `FileInvalid` | `2` (inclui "sem páginas", R6) | `ERROR_FILE_INVALID` |
| `WrongPassword` | `3` | `ERROR_WRONG_PASSWORD` |
| `NoHandlerForMime` | `7` (refinamento do clone) | `ERROR_FILE_NO_HANDLER_FOR_MIME` |
| `Unknown` | outro | `ERROR_FILE_UNKNOWN` |

> No original, o código `7` cai no ramo padrão e produz `ERROR_FILE_UNKNOWN` (F-005 §5).
> O clone mantém o nome distinto `NoHandlerForMime`/`ERROR_FILE_NO_HANDLER_FOR_MIME` para
> cumprir o contrato tipado exigido pelo laudo; esta é uma decisão do clone, não uma
> reatribuição do comportamento do binário.

## Mapeamento função-do-binário → classe/método do ArtPlus

| Função / evidência (Ghidra/CAP) | Classe/método ArtPlus | Observação |
|---|---|---|
| `GHIDRA-Document-0x1802160B0` `FileDispatcher::OpenFile` | `ArtPlus::FileDispatcher::open(const QString&)` | MIME → handler; erro tipado para MIME sem handler (R2) |
| `0x180215D50` / `0x180216380` `AddToOpeningFiles` / `RemoveFromOpeningFiles` | guarda RAII interna em `FileDispatcher::open()` | não é API pública; evita reentrância |
| `GHIDRA-Document-0x180216270` `RegisterFileHandler` | `ArtPlus::FileDispatcher::registerHandler()` | `std::map`; chave duplicada ignorada (R3) |
| `GHIDRA-Document-0x1800A1230` inicialização do DocumentLayer | `ArtPlusMainWindow::ArtPlusMainWindow()` → `FileDispatcher::registerBuiltinHandlers()` | registro único na inicialização (R3) |
| `GHIDRA-Document-0x1800A2E40` handler slot 1 | `PdfOpenHandler::open()` e `ArtPlusDocumentHandler::open()` | um handler por formato; nenhum handler fictício (R2/R3) |
| `GHIDRA-Document-0x180094E10` / `0x18008F590` `Document::Create` + construtor | `PDF::PdfDocument::open()` chamado por `PdfOpenHandler::open()` | parser próprio permanece (ADR-013, decisão 1) |
| `GHIDRA-Document-0x180093D60` `Document::Cache` | `PdfOpenHandler::open()` (checa `pageCount()`/`pagesImported`) | sem páginas → `FileInvalid` (R6) |
| `GHIDRA-Document-0x180083F80` `AddPageToDocument` | `Document::addPage()` via `PdfImporter::import()` | ponto único de registro de página |
| `GHIDRA-Document-0x18009C080` `SetTitle` | `Document::setTitle()` + `OpenResult::title` | título derivado do nome do arquivo (R4) |
| `GHIDRA-Document-0x1800A0EC0` mapa código → nome | `ArtPlus::openErrorMessage(OpenError)` | mensagens simbólicas (§5) |
| `CAP-20261121-01` `File > Open...`, diálogo e filtro | `ArtPlusMainWindow::openDocument()` + `m_openAct` | comando único, filtro literal (R1) |
| `CAP-20261121-01` título `<arquivo> @ <zoom> – ...` | `ArtPlusMainWindow::updateWindowTitle()` | marca do clone: `ArtPlus` (R8) |
| `CAP-20261121-01` overlay `Media Box ... mm` | `ArtPlusScene::setPageBoxOverlay()` | conversão pt → mm na borda de UI (R8) |
| `CAP-20261121-01` passo 12 (zoom ao abrir painel) | `ArtPlusMainWindow::relayoutViewport()` | `zoomFit()` + `updateWindowTitle()` (R9) |
| — (sem equivalente: formato do clone) | `ArtPlusDocumentHandler::open()` → `DocumentSerializer::load()` | exceção `.artplus`, não reivindicada na v24 |

## Contrato de interface

Assinaturas que atravessam módulos (C++17, Qt 6.8.3). Tipos de domínio usam apenas QtCore;
`QDockWidget`/`QFileDialog` ficam exclusivamente em `src/ui/`.

```cpp
// src/document/open_error.h  (novo)
namespace ArtPlus {

enum class OpenError {
    None,
    FileNotFound,
    FileAccessDenied,
    FileInvalid,
    WrongPassword,
    NoHandlerForMime,
    Unknown
};

QString openErrorMessage(OpenError error);   // ERROR_FILE_* / ERROR_WRONG_PASSWORD

struct OpenResult {
    std::unique_ptr<Document> document;
    OpenError error = OpenError::Unknown;
    QString detail;                          // caminho/diagnóstico, sem localização
    QString title;                           // = QFileInfo(path).fileName() (R4)

    static OpenResult success(std::unique_ptr<Document> doc, const QString& filePath);
    static OpenResult failure(OpenError error, const QString& detail);
};

} // namespace ArtPlus

// src/document/file_dispatcher.h  (novo)
namespace ArtPlus {

class OpenFileHandler {
public:
    virtual ~OpenFileHandler() = default;
    virtual OpenResult open(const QString& filePath) const = 0;
};

class FileDispatcher {
public:
    static QString mimeTypeForPath(const QString& filePath);          // extensão → MIME interno
    static void registerBuiltinHandlers(FileDispatcher& dispatcher); // chamado uma vez (R3)

    bool registerHandler(const QString& mimeType,
                         std::unique_ptr<OpenFileHandler> handler);   // duplicata → false
    bool hasHandler(const QString& mimeType) const;
    OpenResult open(const QString& filePath) const;                   // R2

private:
    std::map<QString, std::unique_ptr<OpenFileHandler>> m_handlers;
};

} // namespace ArtPlus

// src/pdf/pdf_open_handler.h  (novo) e acréscimo em src/pdf/pdf_document.h
namespace ArtPlus {

class PdfOpenHandler final : public OpenFileHandler {
public:
    OpenResult open(const QString& filePath) const override;          // R5/R6 + §5
};

namespace PDF {
// acrescentar a PdfDocument: fonte local para OpenError::WrongPassword (F-005 §5)
bool isEncrypted() const;   // presença de /Encrypt no catálogo; sem UI própria

} // namespace PDF
} // namespace ArtPlus

// src/document/artplus_open_handler.h  (novo)
namespace ArtPlus {

class ArtPlusDocumentHandler final : public OpenFileHandler {
public:
    OpenResult open(const QString& filePath) const override;          // exceção .artplus
};

} // namespace ArtPlus

// src/document/document_model.h  (acréscitos)
namespace ArtPlus {
class Document {
public:
    void setTitle(const QString& title);                              // R4
    const QString& title() const;
    // ... demais membros existentes inalterados
};
} // namespace ArtPlus

// src/ui/main_window.h  (alterações)
namespace ArtPlus {

class ArtPlusScene : public QGraphicsScene {
public:
    void setPageBoxOverlay(const QString& text);                      // R8
};

class ArtPlusMainWindow : public QMainWindow {
public:
    bool openDocumentPath(const QString& filePath,
                          QString* errorOut = nullptr);               // chamado por --open

private slots:
    void openDocument();                                              // R1: único comando
    void relayoutViewport();                                          // R9

private:
    void updateWindowTitle() const;                                   // R8
    void updatePageBoxOverlay(const QRectF& mediaBoxPt);              // pt → mm, R8
    FileDispatcher m_dispatcher;                                      // R3
    QAction* m_openAct = nullptr;                                     // R1
};
} // namespace ArtPlus
```

`openDocumentPath()` preserva a garantia atual de `openPdfPath()`: em falha devolve `false`,
preenche `errorOut` e não destrói o documento corrente. A substituição de `m_document` só
ocorre depois que `FileDispatcher::open()` devolve `OpenResult` com `error == None`.
`src/app/main.cpp` passa a chamar `openDocumentPath()` (o `--open` deixa de presumir PDF).

## Alternativas descartadas

1. **Manter `Open PDF...` + `Open .artplus...`** — reprovada: contradiz R1 e
   `CAP-20261121-01` (um único `Open...`).
2. **Singleton global de dispatcher** — reprovada: piora testabilidade e cria estado implícito;
   a instância pertence a `ArtPlusMainWindow`, que já é a raiz de composição.
3. **Registrar handlers fictícios para `*.pdpdla`, `*.ap`, `*.art`** — reprovada: F-005 só
   exercitou PDF e §8.3 deixa os MIMEs em aberto; handler que finge funcionar viola
   AGENTS.md §6.6. O caminho correto é `NoHandlerForMime`.
4. **Adicionar Poppler ou outra biblioteca de PDF** — reprovada: dependência nova exigiria
   ADR e auditoria de licença; o parser em `src/pdf/` já existe (ADR-013, decisão 2).
5. **Lançar exceções C++ através dos slots de menu** — reprovada: o contrato tipado
   `OpenResult` carrega a mesma informação sem cruzar o ciclo de eventos Qt.
6. **Atribuir `Ctrl+O` a `Open...`** — reprovada por EXISTENCE-FIRST: F-005 §3/§8.1 registra
   o atalho como **não medido**; nenhuma aceleração é inventada.
7. **Guardar o título apenas em `Document::metadata()`** — reprovada: chave genérica não é
   contrato; R4 exige campo explícito equivalente a `SetTitle`.

## Consequências

### Arquivos abrangidos

| Caminho em `src/` | Natureza | Regras atendidas |
|---|---|---|
| `src/document/open_error.h` | novo: enum, mensagens simbólicas e `OpenResult` | §5, R6 |
| `src/document/file_dispatcher.h` / `src/document/file_dispatcher.cpp` | novos: mapa MIME→handler, resolução por extensão, guarda de abertura, registro embutido | R2, R3 |
| `src/document/artplus_open_handler.h` / `src/document/artplus_open_handler.cpp` | novos: handler do formato próprio | exceção `.artplus`, R2/R3 |
| `src/document/document_model.h` / `src/document/document_model.cpp` | acréscito de `setTitle()`/`title()` | R4 |
| `src/pdf/pdf_open_handler.h` / `src/pdf/pdf_open_handler.cpp` | novos: handler PDF, checagem de páginas, classificação de erro | R2/R3, R5/R6, §5 |
| `src/pdf/pdf_document.h` / `src/pdf/pdf_document.cpp` | acréscito de `isEncrypted()`; `open()` continua com a assinatura atual | §5 (`WrongPassword`) |
| `src/pdf/pdf_importer.h` / `src/pdf/pdf_importer.cpp` | sem mudança de assinatura; `pagesImported` passa a ser insumo de R6 | R6 |
| `src/ui/main_window.h` / `src/ui/main_window.cpp` | ação única `Open...`, filtro literal, `openDocumentPath()`, título, overlay, relayout | R1, R4, R8, R9 |
| `src/app/main.cpp` | `--open` passa a usar `openDocumentPath()` | R1/R2 |

`CMakeLists.txt` **não** precisa de alvo, `find_package` ou biblioteca nova: Qt6 Core/Gui/Widgets
já são linkados em `ArtPlus` (`find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test
ZlibPrivate)`).

**Reutilização antes de criar classe nova.** `PDF::PdfDocument` e `PdfImporter` já fazem a
leitura/importação e permanecem; `DocumentSerializer` já carrega `.artplus`; nenhum desses
tipos possui mapa de handlers, classificação de erro nem título de documento, o que justifica
`FileDispatcher`, `OpenError`/`OpenResult` e `setTitle()`. Os handlers são finos e apenas
adaptam esses componentes existentes ao contrato `OpenFileHandler`.

**Risco.** A classificação `FileNotFound`/`FileAccessDenied` depende de `QFileInfo`/`QFile`
no handler PDF (o parser devolve `bool` sem detalhe, ADR-013); `WrongPassword` depende do
sinal local `/Encrypt`, sem captura GUI de erro (F-005 §5/§8.5). O teste de UI exigido pelo
laudo continua sendo responsabilidade do agente `testes`; esta ADR não altera testes.

**Migração de dados.** Nenhuma. `.artplus` permanece JSON lido por `DocumentSerializer`; o
campo `title` é novo no modelo em memória e não muda o formato serializado obrigatório.

**Estado do pipeline após esta ADR.** O gate de código (`python scripts/gate.py --feature F-005
--stage code`) só ficará verde depois que `implementacao` materializar os arquivos acima e o
build real for registrado; o laudo REPROVADO atual não é alterado por esta decisão.

## Estado

Estado: aceito (aprovado em 2026-11-23) — decisão de arquitetura, sem código implementado por
esta ADR. Substitui, apenas para R1/R2/R3/R4/R6/R8/R9/§5, o registro "não decidido nesta ADR"
de `ADR-013`.
