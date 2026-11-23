#ifndef MARKSET_PROCESSOR_H
#define MARKSET_PROCESSOR_H

#include "../document/document_model.h"

#include <string>
#include <vector>

// F-002 — Mark set (DocumentMarks.dll, v24.03.10017).
//
// Contrato implementado a partir da evidência v240 em rag/evidence/F-002/ghidra/:
//   R1 ReadMarkSetFile (GHIDRA-DocumentMarks-0x180248D30): carrega o documento de mark
//      set. Arquivo inexistente -> "MarkSetFileDoesNotExist"; erro de leitura/parse ->
//      "MarkSetFileError"/"CannotOpenMarkSetFile". A v240 NÃO verifica versão dentro
//      dessa função (as strings kVersionTooOld/kVersionTooNew existem no binário mas não
//      são referenciadas ali), então nenhuma checagem de versão é inventada aqui.
//   R2 PrepareMarksCachePage (GHIDRA-DocumentMarks-0x180248720): seleciona e valida a
//      página alvo (geometria) antes de qualquer escrita.
//   R3 ApplyMarksFromSet (GHIDRA-DocumentMarks-0x180243EC0) + CopyMarksToPageWithLog
//      (GHIDRA-DocumentMarks-0x180245380) + CopyMarksToPage (0x1800426F0): copia a
//      PRIMEIRA página de cada documento de mark set para a página alvo, com ids de
//      objeto novos, sem alterar o documento de origem.
//
// O mark set é um documento do clone: .pdf (PdfImporter) ou .artplus
// (DocumentSerializer::load). A cópia usa o modelo real (Document/Page/Layer/
// DocumentObject::clone), não há conteúdo simulado.
class MarkSetProcessor {
public:
    MarkSetProcessor();
    ~MarkSetProcessor() = default;

    // Equivalente ao TaskMarkSets da v240 (`__thiscall`): o documento de destino é o
    // contexto da operação. Não é possuído por este objeto e precisa sobreviver a ele.
    void setTargetDocument(ArtPlus::Document& targetDocument);

    // R2: valida a página alvo e a registra como destino de applyMarksFromSet().
    // false = página sem geometria utilizável; quando há documento de destino definido,
    // também exige que a página pertença a ele.
    bool prepareMarksCachePage(const ArtPlus::Page& page);

    // R1: carrega `filePath` (.pdf ou .artplus) para `markSetDocument`.
    // O documento de destino não é tocado; em falha retorna false e lastError() explica.
    bool loadMarkSetFile(const std::string& filePath, ArtPlus::Document& markSetDocument);

    // R3: carrega o mark set e copia a primeira página dele para a página preparada em
    // prepareMarksCachePage(), no documento definido por setTargetDocument().
    // Nada é escrito no destino antes de o mark set carregar e validar.
    bool applyMarksFromSet(const std::string& markSetPath);

    // R3 (CopyMarksToPage): copia a primeira página de `sourceDoc` para `targetPage`,
    // que precisa pertencer ao documento de destino. Ids novos; `sourceDoc` intacto.
    bool copyMarksToPage(const ArtPlus::Document& sourceDoc, const ArtPlus::Page& targetPage);

    // R4 (ApplyRelevantMarkSets, GHIDRA-DocumentMarks-0x18024D460): os critérios de
    // "mark set relevante" não foram derivados da evidência (F-002 §Em aberto, item 2).
    // TODO(F-002): devolve vazio até haver critério comprovado; a seleção de documentos
    // de mark set é explícita, via loadMarkSetFile()/copyMarksToPage()/applyMarksFromSet().
    std::vector<std::string> identifyRelevantSets() const;

    // Último erro: identificador da spec (MarkSetFileDoesNotExist / MarkSetFileError /
    // CannotOpenMarkSetFile / WrongMarkSet) + detalhe. Vazio quando não há erro.
    const std::string& lastError() const { return m_lastError; }

    // Objetos copiados na última operação bem-sucedida (0 em falha).
    int lastCopiedObjectCount() const { return m_lastCopiedObjectCount; }

private:
    ArtPlus::Document* m_targetDocument = nullptr;
    ArtPlus::PageId m_targetPageId = 0;
    std::string m_lastError;
    int m_lastCopiedObjectCount = 0;
};

#endif // MARKSET_PROCESSOR_H
