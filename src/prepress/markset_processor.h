#ifndef MARKSET_PROCESSOR_H
#define MARKSET_PROCESSOR_H

#include "../document/document_model.h"
#include "../prepress/markset_commands.h"
#include "../prepress/markset_reporter.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace ArtPlus { class UndoStack; }

namespace ArtPlus::Prepress {

enum class MarkSetError {
    None,
    MarkSetFileDoesNotExist,      // E1: arquivo inexistente ou não regular
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
    std::string displayName;                    // stem do arquivo
    std::vector<PageId> pageOrder;
    std::vector<ArtPlus::Separation::Entry> separations; // consolidadas da primeira página
    std::vector<ArtPlus::PageBox> pageBoxes;    // caixas de página da primeira página
    bool hasInputFileMark = false;
};

class MarkSetProcessor {
public:
    MarkSetProcessor() = default;
    ~MarkSetProcessor() = default;

    // Contexto da operação: documento de destino (não possuído, precisa sobreviver ao processor)
    void setTargetDocument(ArtPlus::Document& targetDocument);

    // R2: valida e registra a página alvo para applyMarksFromSet()
    // Consolida separações da página (Separation::Entry) e grava Document::SetSeparationInfo
    // Devolve false se página sem geometria utilizável ou que não pertence ao documento de destino
    bool prepareMarksCachePage(const ArtPlus::Page& page);

    // R1: carrega filePath (.pdf ou .artplus) para markSetDocument
    // O documento de destino NÃO é tocado; em falha retorna false e lastError() explica
    bool loadMarkSetFile(const std::string& filePath, ArtPlus::Document& markSetDocument);

    // R3: carrega o mark set e copia a primeira página dele para a página preparada
    // no documento definido por setTargetDocument()
    bool applyMarksFromSet(const std::string& markSetPath, bool deleteExisting = false);

    // R3 (CopyMarksToPage): copia a primeira página de sourceDoc para targetPage
    // (targetPage precisa pertencer ao documento de destino). Ids novos; sourceDoc intacto.
    // Preserva estrutura de camadas do mark set; religa marcas dinâmicas; empilha undo
    // (deleteExisting=true removes marks previously added by applyMarksFromSet on the target).
    bool copyMarksToPage(const ArtPlus::Document& sourceDoc, const ArtPlus::Page& targetPage,
                         const std::string& markSetPath, bool deleteExisting = false);

    // R4 (ApplyRelevantMarkSets): retorna mark sets relevantes para a página alvo.
    // Critério: mark sets cujo displayName/pageBoxes/separations coincidem com a página alvo.
    // Requer prepareMarksCachePage() chamado antes.
    std::vector<MarkSetInfo> identifyRelevantSets() const;

    // Aplica mark set adicional (vetor) à página já preparada.
    bool applyExtraMarkSet(const std::vector<std::string>& markSetPaths);

    // Aplica a todas as páginas do documento alvo.
    bool applyMarkSetToDocument(const std::string& markSetPath, bool deleteExisting);

    // Aplica a uma página específica.
    bool applyMarkSetToPage(const std::string& markSetPath, const ArtPlus::Page& targetPage, bool deleteExisting);

    // Último erro: identificador da spec + detalhe. Vazio quando não há erro.
    const std::string& lastError() const;

    // Objetos copiados na última operação bem-sucedida (0 em falha).
    int lastCopiedObjectCount() const;

    // Reporter de avisos (MissingNamedObject, MissingPageBox) — ids estáveis DocumentMarks.Warning.*
    void setReporter(std::unique_ptr<Reporter>);

    // Stack de undo para os comandos de aplicação de mark set (ex.: ApplyMarkSetCommand).
    void setUndoStack(ArtPlus::UndoStack* stack) { m_undoStack = stack; }

private:
    ArtPlus::Document* m_targetDocument = nullptr;
    ArtPlus::PageId m_targetPageId = 0;
    ArtPlus::UndoStack* m_undoStack = nullptr;
    std::string m_lastError;
    int m_lastCopiedObjectCount = 0;
    std::unique_ptr<Reporter> m_reporter;
    std::vector<MarkSetInfo> m_loadedMarkSets; // cache para identifyRelevantSets
    std::unordered_map<ArtPlus::PageId, std::vector<ArtPlus::ObjectId>> m_marksByPage; // marcas aplicadas por página (deleteExisting)

    // Internals
    std::vector<ArtPlus::ObjectId> pageObjectIds(const ArtPlus::Document& doc, const ArtPlus::Page& page) const;
    ArtPlus::Layer* targetLayerFor(const ArtPlus::Page& page, const ArtPlus::Document& markSetDoc, const ArtPlus::Page& markSetPage, const std::unordered_map<LayerId, LayerId>& layerRemap);
    bool copyPageObjects(const ArtPlus::Document& sourceDoc, const std::vector<ArtPlus::ObjectId>& sourceIds,
                         ArtPlus::Document& targetDoc, ArtPlus::Page& targetPage, bool deleteExisting,
                         std::vector<ArtPlus::ObjectId>& copiedObjectIds,
                         std::vector<ArtPlus::ObjectId>& removedObjectIds,
                         Reporter* reporter,
                         const std::string& markSetName,
                         size_t pageIndex);
    bool consolidateSeparations(const ArtPlus::Page& page);
    bool relinkDynamicObjects(const ArtPlus::Document& sourceDoc, const std::vector<ArtPlus::ObjectId>& sourceIds,
                              ArtPlus::Document& targetDoc, const std::unordered_map<ArtPlus::ObjectId, ArtPlus::ObjectId>& remap,
                              Reporter* reporter,
                              const std::string& markSetName,
                              size_t pageIndex);
};

} // namespace ArtPlus::Prepress

#endif // MARKSET_PROCESSOR_H