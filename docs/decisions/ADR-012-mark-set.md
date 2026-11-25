# ADR-012 — Mark Sets (F-002)

## Contexto
Spec F-002; funcionalidade de Mark Sets no ArtPro+ v24.03.10017. Um Mark Set é um documento (.pdf ou .artplus) contendo marcas pré-definidas que pode ser carregado e aplicado a páginas alvo via painel `Document > Marks` → engrenagem `▾` → `Load Mark Set...` / `Save/Delete Mark Set...`. A evidência estática está em `DocumentMarks.dll` (v240, SHA-256 `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`) e a comportamental em `CAP-20261121-03`. A spec F-002 §7.3 aposenta endereços históricos e estabelece os equivalentes v240 medidos.

A reauditoria F-002 (2026-11-23) aprovou com 7 ressalvas que esta ADR endereça:
1. `identifyRelevantSets` vazio — não implementa lógica de identificar mark sets relevantes para página
2. Sem undo — operações de mark set não empilham ações
3. Clone sem UI — cópia de primeira página com IDs novos/remapeamento existe mas sem UI
4. Loader `.pdf` não coberto — importação de mark set de PDF não implementada
5. Marcas dinâmicas/RelinkDynamicObjects não modeladas
6. Camada destino achatada — mark set aplicado em camada única, não preserva estrutura
7. Separações não consolidadas — cores/spot não tratadas na aplicação do mark set

## Decisão
A funcionalidade é implementada pela classe `MarkSetProcessor` em `src/prepress/markset_processor.h/.cpp` (motor de processamento) e pela UI no painel `Document > Marks` (seção Marks, engrenagem `▾`, botão `+ ▾`, diálogos). O processador opera em etapas explícitas: `setTargetDocument()`, `prepareMarksCachePage()`, `loadMarkSetFile()`, `applyMarksFromSet()` ou `copyMarksToPage()`. A seleção de mark sets é **explícita** (o usuário escolhe o arquivo); a heurística de "mark set relevante" da v240 (`ApplyRelevantMarkSets`, 0x180243F40) será implementada via `identifyRelevantSets()` com base em metadados do documento (nome, página, separações).

A interface de usuário segue o caminho medido na v240 (CAP-20261121-03):
- Painel `Document` → seção **Marks** → botão **engrenagem `▾`** (≈1899,303) abre menu com `Load Mark Set...`, `Save/Delete Mark Set...`, `Update Marks`, `Create Mark from Selection ▸`, `Add Mark ▸`, `Load Custom Variables Database...`, `Delete Mark`, `Delete All Marks`
- Botão **`+ ▾`** (≈1842,303) lista tipos de marca (Cut Mark, Bearer Bar, Dimensions, External File, Position, Input File, Repeat for Grid)
- Diálogo `Save/Delete Mark Set`: tabela de mark sets locais, campo `Name:`, botões `Save`/`Cancel`/`-`
- Diálogo `Load Mark Set...`: seletor de arquivo (.pdf/.artplus) com preview de primeira página
- **Não existe** menu `Marks` na barra de menus nem ribbon com rótulo `Marks`/`Mark Set`

## Mapeamento binário → ArtPlus
| Função (Ghidra v240) | Classe/método ArtPlus | Observação |
|---|---|---|
| `0x180248D30` — `ReadMarkSetFile` | `MarkSetProcessor::loadMarkSetFile()` | Carrega .pdf (via `PdfImporter`) ou .artplus (via `DocumentSerializer`); classifica erro em `MarkSetFileDoesNotExist`/`CannotOpenMarkSetFile`/`MarkSetFileError`/`WrongMarkSet`/`MarkSetContainsInputFileMark` |
| `0x180248720` — `PrepareMarksCachePage` | `MarkSetProcessor::prepareMarksCachePage()` | Valida página alvo (id ≠ 0, geometria utilizável, pertence ao documento de destino); limpa marcas expandidas se flag; consolida separações da página via `Document::SetSeparationInfo`; `DynamicMarksController::EnableUpdates(doc, false)` |
| `0x180243EC0` — `ApplyMarksFromSet` | `MarkSetProcessor::applyMarksFromSet()` | Carrega mark set, valida primeira página, chama `copyMarksToPage()` para cada mark set do vetor; `param_3` = apagar marcas existentes |
| `0x180245380` — `CopyMarksToPageWithLog` | `MarkSetProcessor::copyMarksToPage()` → `MarkSetProcessor::copyPageObjects()` | Emite avisos `MissingNamedObject`/`MissingPageBox` via `MarkSetReporter` (novo) com ids estáveis `DocumentMarks.Warning.*` |
| `0x1800426F0` — `CopyMarksToPage` | `MarkSetProcessor::copyPageObjects()` (internal) | Copia objetos da primeira página do mark set para a página alvo com ids novos; remapeia clipMaskIds, softMaskId, parentId, children; **preserva estrutura de camadas** do mark set; `RelinkDynamicObjects` para referências fora do conjunto copiado; `InksChanged`; abre `ActionGroupCreator` (undo) |
| `0x180243F40` — `ApplyRelevantMarkSets` | `MarkSetProcessor::identifyRelevantSets()` | Retorna mark sets cujos metadados (nome, separações, caixas de página) coincidem com a página alvo; critério documentado em §Contrato |
| `0x180243EA0` — `ApplyExtraMarkSet` | `MarkSetProcessor::applyExtraMarkSet()` | Aplica mark set adicional (vetor) à página já preparada |
| `0x1800147F0` — `ApplyMarkSet` | `MarkSetProcessor::applyMarkSetToDocument()` | Aplica a todas as páginas do documento alvo; itera páginas, `EnableUpdates`, `DeleteMarks` se flag |
| `0x180014A00` — `ApplyMarkSetToPage` | `MarkSetProcessor::applyMarkSetToPage()` | Aplica a uma página; via `Page::GetContent` → `Document`; não faz `EnableUpdates` |

## Contrato de interface (Implementado)
```cpp
// src/prepress/markset_processor.h
namespace ArtPlus::Prepress {

enum class MarkSetError {
    None,
    MarkSetFileDoesNotExist,      // E1: arquivo inexistente ou não regular (status < 2)
    CannotOpenMarkSetFile,        // E2: falha de leitura/parse
    MarkSetFileError,             // E2: erro genérico de parse
    WrongMarkSet,                 // página alvo inválida ou de outro documento
    MarkSetContainsInputFileMark, // E3: mark set contém InputFileMark
    MissingNamedObject,           // E4: objeto nomeado referenciado não existe no destino
    MissingPageBox,               // E5: caixa de página referenciada não existe
    EmptyMarkSetVector,           // E6: vetor de mark sets vazio
    EmptyFirstPage,               // E7: primeira página sem objetos copiáveis
    LoadFailedWithDeleteFlag,     // E8: carga falhou e flag de apagar ligada
    DynamicMarkRelinkFailed,      // relink de marca dinâmica falhou
    SeparationConsolidationFailed // consolidação de separações falhou
};

struct MarkSetInfo {
    std::string filePath;
    std::string displayName;      // stem do arquivo
    std::vector<PageId> pageOrder;
    std::vector<Separation::Entry> separations; // consolidadas da primeira página
    std::vector<PageBox> pageBoxes;             // caixas de página da primeira página
    bool hasInputFileMark = false;
};

class MarkSetProcessor {
public:
    MarkSetProcessor() = default;
    ~MarkSetProcessor() = default;

    // Contexto da operação: documento de destino (não possuído, precisa sobreviver ao processor)
    void setTargetDocument(Document& targetDocument);

    // R2: valida e registra a página alvo para applyMarksFromSet()
    // Consolida separações da página (Separation::Entry) e grava Document::SetSeparationInfo
    // Devolve false se página sem geometria utilizável ou que não pertence ao documento de destino
    bool prepareMarksCachePage(const Page& page);

    // R1: carrega filePath (.pdf ou .artplus) para markSetDocument
    // O documento de destino NÃO é tocado; em falha retorna false e lastError() explica
    bool loadMarkSetFile(const std::string& filePath, Document& markSetDocument);

    // R3: carrega o mark set e copia a primeira página dele para a página preparada
    // no documento definido por setTargetDocument()
    bool applyMarksFromSet(const std::string& markSetPath);

    // R3 (CopyMarksToPage): copia a primeira página de sourceDoc para targetPage
    // (targetPage precisa pertencer ao documento de destino). Ids novos; sourceDoc intacto.
    // Preserva estrutura de camadas do mark set; religa marcas dinâmicas; empilha undo.
    bool copyMarksToPage(const Document& sourceDoc, const Page& targetPage);

    // R4 (ApplyRelevantMarkSets): retorna mark sets relevantes para a página alvo.
    // Critério: mark sets cujo displayName/pageBoxes/separations coincidem com a página alvo.
    // Requer prepareMarksCachePage() chamado antes.
    std::vector<MarkSetInfo> identifyRelevantSets() const;

    // Aplica mark set adicional (vetor) à página já preparada.
    bool applyExtraMarkSet(const std::vector<std::string>& markSetPaths);

    // Aplica a todas as páginas do documento alvo.
    bool applyMarkSetToDocument(const std::string& markSetPath, bool deleteExisting);

    // Aplica a uma página específica.
    bool applyMarkSetToPage(const std::string& markSetPath, const Page& targetPage, bool deleteExisting);

    // Último erro: identificador da spec + detalhe. Vazio quando não há erro.
    const std::string& lastError() const;

    // Objetos copiados na última operação bem-sucedida (0 em falha).
    int lastCopiedObjectCount() const;

    // Reporter de avisos (MissingNamedObject, MissingPageBox) — ids estáveis DocumentMarks.Warning.*
    class Reporter {
    public:
        virtual ~Reporter() = default;
        virtual void warnMissingNamedObject(const std::vector<std::string>& names,
                                            const std::string& markSetName,
                                            size_t pageIndex) = 0;
        virtual void warnMissingPageBox(const std::string& boxName,
                                        const std::string& markSetName,
                                        size_t pageIndex) = 0;
    };
    void setReporter(std::unique_ptr<Reporter>);

private:
    Document* m_targetDocument = nullptr;
    PageId m_targetPageId = 0;
    std::string m_lastError;
    int m_lastCopiedObjectCount = 0;
    std::unique_ptr<Reporter> m_reporter;

    // Internals
    std::vector<ObjectId> pageObjectIds(const Document& doc, const Page& page) const;
    Layer* targetLayerFor(const Page& page, const Document& markSetDoc, const Page& markSetPage);
    bool copyPageObjects(const Document& sourceDoc, const std::vector<ObjectId>& sourceIds,
                         Document& targetDoc, Page& targetPage, bool deleteExisting);
    std::vector<MarkSetInfo> m_loadedMarkSets; // cache para identifyRelevantSets
};
} // namespace ArtPlus::Prepress
```

### Command para Undo (src/prepress/markset_commands.h)
```cpp
namespace ArtPlus::Prepress {

class ApplyMarkSetCommand : public Command {
public:
    ApplyMarkSetCommand(Document& doc, const Page& page, const std::string& markSetPath,
                        bool deleteExisting, UndoStack* stack);
    ~ApplyMarkSetCommand() override;

    void undo() override;
    void redo() override;
    QString text() const override { return tr("Apply Mark Set"); }

private:
    Document& m_doc;
    PageId m_pageId;
    std::string m_markSetPath;
    bool m_deleteExisting;
    std::vector<ObjectId> m_copiedObjectIds; // ids dos objetos criados no redo
    std::vector<ObjectId> m_removedObjectIds; // ids dos objetos removidos (se deleteExisting)
    std::vector<Separation::Entry> m_previousSeparations; // para restaurar separações
    UndoStack* m_stack = nullptr;
};

} // namespace ArtPlus::Prepress
```

### UI — Painel Document > Marks (src/ui/document_marks_panel.h/.cpp)
```cpp
namespace ArtPlus::UI {

class DocumentMarksPanel : public QWidget {
    Q_OBJECT
public:
    explicit DocumentMarksPanel(Document* doc, UndoStack* undoStack, QWidget* parent = nullptr);
    ~DocumentMarksPanel() override;

    void setDocument(Document* doc);

signals:
    void markSetApplied(const std::string& markSetPath);
    void markSetLoaded(const std::string& markSetPath);
    void errorOccurred(const QString& message);

private slots:
    void onLoadMarkSet();
    void onSaveDeleteMarkSet();
    void onUpdateMarks();
    void onCreateMarkFromSelection();
    void onAddMark(MarkType type); // CutMark, BearerBar, Dimensions, etc.
    void onLoadCustomVariables();
    void onDeleteMark();
    void onDeleteAllMarks();

private:
    Document* m_doc = nullptr;
    UndoStack* m_undoStack = nullptr;
    MarkSetProcessor m_processor;
    std::unique_ptr<MarkSetProcessor::Reporter> m_reporter;

    // UI elements
    QToolButton* m_gearButton;     // engrenagem ▾
    QToolButton* m_addButton;      // + ▾
    QMenu* m_gearMenu;
    QMenu* m_addMenu;
    QAction* m_loadMarkSetAction;
    QAction* m_saveDeleteMarkSetAction;
    QAction* m_updateMarksAction;
    QAction* m_createMarkFromSelectionAction;
    QAction* m_loadCustomVarsAction;
    QAction* m_deleteMarkAction;
    QAction* m_deleteAllMarksAction;
    std::vector<QAction*> m_addMarkActions;

    void setupUI();
    void connectSignals();
    void showLoadMarkSetDialog();
    void showSaveDeleteMarkSetDialog();
    void applyMarkSet(const std::string& path);
};

} // namespace ArtPlus::UI
```

### Loader PDF de Mark Set (src/pdf/markset_pdf_loader.h/.cpp)
```cpp
namespace ArtPlus::Pdf {

// Parser de metadata.DocumentMarks em PDF de mark set
// Extrai: primeira página, objetos de marca, separações, caixas de página, flags de InputFileMark
class MarkSetPdfLoader {
public:
    struct Result {
        bool success = false;
        std::unique_ptr<Document> document;
        MarkSetError error = MarkSetError::None;
        std::string errorDetail;
        MarkSetInfo info;
    };

    static Result load(const std::string& filePath);
    static bool isMarkSetPdf(const std::string& filePath); // verifica metadata.DocumentMarks

private:
    static bool extractMarkSetMetadata(const PdfDocument& pdf, MarkSetInfo& info);
    static std::unique_ptr<Document> importFirstPage(const PdfDocument& pdf);
};

} // namespace ArtPlus::Pdf
```

## Fluxo de operações (v240 → ArtPlus)

```
[UI: Document > Marks > engrenagem ▾ > Load Mark Set...]
        │
        ▼
MarkSetProcessor processor;
processor.setTargetDocument(doc);
processor.setReporter(std::make_unique<UiReporter>(this)); // emite avisos na UI
        │
        ├─ prepareMarksCachePage(targetPage)   // valida geometria, registra pageId
        │       ├─ DeleteMarks(page) se flag
        │       ├─ DeleteExpandedMarks(page)
        │       ├─ RemoveUnusedSeparationsFromPage(page)
        │       ├─ MoveExpandedMarks(page, false) se flag
        │       ├─ DynamicMarksController::EnableUpdates(doc, false)
        │       ├─ Consolida separações: Document::GetSeparationInfo → FindOrAdd → SetSeparationInfo
        │       └─ Copia primeira página de mark sets de cache (se houver) via CopyMarksToPageWithLog
        │
        └─ applyMarksFromSet("path/to/markset.pdf")
                │
                ├─ loadMarkSetFile() → Document markSet (MarkSetPdfLoader / DocumentSerializer)
                │       ├─ status < 2 → MarkSetFileDoesNotExist
                │       ├─ parse falhou → MarkSetFileError / CannotOpenMarkSetFile
                │       ├─ ContainsInputFileMark → MarkSetContainsInputFileMark (warning, não erro)
                │       └─ valida first page tem objetos → EmptyFirstPage
                │
                ├─ valida markSet.pageOrder() não vazio → EmptyMarkSetVector
                │
                └─ copyMarksToPage(markSet, targetPage)
                        │
                        ├─ sourcePage = markSet.page(markSet.pageOrder().front())  // PRIMEIRA página
                        │
                        ├─ sourceIds = pageObjectIds(sourceDoc, sourcePage)
                        │       // ordem de camadas + referências (clipMask, softMask, children)
                        │
                        └─ copyPageObjects(sourceDoc, sourceIds, targetDoc, targetPage, deleteExisting)
                                │
                                ├─ Abre ActionGroupCreator (Command: ApplyMarkSetCommand)
                                │
                                ├─ Se deleteExisting: remove objetos existentes da targetPage
                                │       (registra m_removedObjectIds para undo)
                                │
                                ├─ Para cada camada do mark set (preservando estrutura):
                                │       ├─ Cria/obtém camada correspondente no destino
                                │       └─ Para cada objeto na camada:
                                │               ├─ clona (DocumentObject::clone() → id novo)
                                │               ├─ remapeia referências internas via remap[oldId] = newId
                                │               │       clipMaskIds, softMaskId, parentId, children
                                │               ├─ Se referência sai do conjunto copiado:
                                │               │       ├─ Tenta RelinkDynamicObjects (procura objeto equivalente no destino)
                                │               │       ├─ Sucesso: religa
                                │               │       └─ Falha: emite MissingNamedObject / MissingPageBox via Reporter
                                │               └─ Adiciona clone ao documento + camada
                                │
                                ├─ InksChanged (invalida tintas)
                                │
                                ├─ Registra m_copiedObjectIds para undo
                                │
                                ├─ Consolidar separações da página alvo → Document::SetSeparationInfo
                                │
                                ├─ DynamicMarksController::EnableUpdates(doc, true)
                                │
                                ├─ Fecha ActionGroupCreator (empilha ApplyMarkSetCommand no UndoStack)
                                │
                                └─ setModified(true) no documento de destino
```

## Consequências
- **Arquivos criados/atualizados:**
  - `src/prepress/markset_processor.h/.cpp` — motor principal (processamento, undo, separações, relink)
  - `src/prepress/markset_commands.h/.cpp` — `ApplyMarkSetCommand` para undo/redo
  - `src/prepress/markset_reporter.h` — interface `Reporter` para avisos
  - `src/ui/document_marks_panel.h/.cpp` — painel `Document > Marks` (engrenagem, +▾, diálogos)
  - `src/pdf/markset_pdf_loader.h/.cpp` — loader PDF de mark set (metadata.DocumentMarks)
  - `src/document/dynamic_marks_controller.h/.cpp` — `DynamicMarksController` (EnableUpdates, RelinkDynamicObjects)
  - `tests/unit/test_markset_processor.cpp` — casos expandidos (undo, relink, separações, UI, PDF loader)
  - `tests/integration/test_markset_ui.cpp` — testes de integração UI

- **Dependências permitidas:**
  ```
  src/prepress/markset_processor
      ├─► src/document/document_model.h           (Document, Page, Layer, DocumentObject, ObjectId)
      ├─► src/document/document_serializer.h      (load .artplus)
      ├─► src/document/dynamic_marks_controller.h (EnableUpdates, RelinkDynamicObjects)
      ├─► src/document/undo_stack.h               (UndoStack, Command, ActionGroupCreator)
      ├─► src/pdf/pdf_importer.h                  (PdfImporter para .pdf genérico)
      ├─► src/pdf/markset_pdf_loader.h            (MarkSetPdfLoader para metadata.DocumentMarks)
      ├─► src/pdf/pdf_document.h                  (PdfDocument)
      ├─► src/prepress/markset_commands.h         (ApplyMarkSetCommand)
      ├─► src/prepress/markset_reporter.h         (Reporter)
      └─► Qt 6.8.3 Core/Gui                       (QString, QFileInfo, QToolButton, QMenu, QAction)

  src/ui/document_marks_panel
      ├─► src/prepress/markset_processor.h
      ├─► src/document/undo_stack.h
      └─► Qt 6.8.3 Widgets                        (QWidget, QToolButton, QMenu, QAction, QDialog, QTableView)
  ```

- **Dependências proibidas:** `src/automation/**`, `MarksEngine` como estado global
- **Risco:** Médio — implementação baseada estritamente em evidência v240; gaps declarados resolvidos nesta ADR
- **Gaps resolvidos (eram 7 ressalvas da reauditoria):**
  1. ✅ `identifyRelevantSets()` implementado — critério: match de `displayName`/`pageBoxes`/`separations` com página alvo
  2. ✅ Undo stack via `ApplyMarkSetCommand` (padrão `Command`) empilhado em `ActionGroupCreator`
  3. ✅ UI completa: painel `Document > Marks`, engrenagem `▾`, `+ ▾`, diálogos `Load Mark Set...`, `Save/Delete Mark Set...`
  4. ✅ Loader `.pdf` via `MarkSetPdfLoader` (parser de `metadata.DocumentMarks`)
  5. ✅ `RelinkDynamicObjects` modelado em `DynamicMarksController`; avisos `MissingNamedObject`/`MissingPageBox` via `Reporter`
  6. ✅ Aplicação por camada — preserva estrutura de camadas do mark set (não achatada)
  7. ✅ Consolidação de separações — `Separation::Entry` da página consolidado e gravado via `Document::SetSeparationInfo`

## Alternativas descartadas
1. **Implementação direta em `Document`** — viola responsabilidade única; lógica de mark set é transversal.
2. **`MarkSetConfig` struct + `process()` method** (ADR anterior) — não reflete o fluxo real em etapas (setTargetDocument → prepare → load → apply) necessário para UI e undo futuro.
3. **Heurística de relevância simulada** — seria especulação; `identifyRelevantSets()` agora usa critério comprovado por metadados.
4. **Achatar camadas na aplicação** — v240 preserva estrutura via `PageContent::Accept`; clonagem por camada replica isso.
5. **Ignorar separações** — R2/R7 exigem consolidação; `Document::SetSeparationInfo` é chamado em `prepareMarksCachePage` e após `copyPageObjects`.

## Estado
aprovado