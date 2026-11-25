#ifndef DYNAMIC_MARKS_CONTROLLER_H
#define DYNAMIC_MARKS_CONTROLLER_H

#include "document_model.h"
#include <vector>

namespace ArtPlus {

class DynamicMarksController {
public:
    // Habilita/desabilita atualizações automáticas de marcas dinâmicas
    // Quando desabilitado (false), marcas dinâmicas não são recalculadas durante edição
    // Deve ser chamado com false antes de operações em lote (apply mark set) e true depois
    static void EnableUpdates(Document& doc, bool enable);

    // Religa marcas dinâmicas a objetos de destino após cópia/importação
    // Procura objetos com nomes/correspondência no documento de destino
    // Retorna true se todas as religações tiveram sucesso
    static bool RelinkDynamicObjects(Document& doc,
                                     const std::vector<ObjectId>& sourceIds,
                                     const std::unordered_map<ObjectId, ObjectId>& idRemap);

    // Verifica se há marcas dinâmicas no documento
    static bool HasDynamicMarks(const Document& doc);

    // Lista IDs de marcas dinâmicas
    static std::vector<ObjectId> GetDynamicMarkIds(const Document& doc);

private:
    static bool relinkMark(Document& doc, ObjectId markId,
                           const std::unordered_map<ObjectId, ObjectId>& idRemap);
    static ObjectId findTargetByName(const Document& doc, const QString& name);
    static ObjectId findTargetByPageBox(const Document& doc, PageBoxType boxType);
};

} // namespace ArtPlus

#endif // DYNAMIC_MARKS_CONTROLLER_H