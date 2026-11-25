#include "dynamic_marks_controller.h"
#include "document_model.h"
#include <unordered_map>

namespace ArtPlus {

// Flag global por documento para controlar updates de marcas dinâmicas
// Em implementação real, seria armazenado no Document ou em mapa estático
namespace {
    std::unordered_map<const Document*, bool> g_dynamicMarksUpdatesEnabled;
}

void DynamicMarksController::EnableUpdates(Document& doc, bool enable) {
    g_dynamicMarksUpdatesEnabled[&doc] = enable;
}

bool DynamicMarksController::RelinkDynamicObjects(Document& doc,
                                                   const std::vector<ObjectId>& sourceIds,
                                                   const std::unordered_map<ObjectId, ObjectId>& idRemap) {
    bool allSuccess = true;
    for (ObjectId id : sourceIds) {
        if (!relinkMark(doc, id, idRemap)) {
            allSuccess = false;
        }
    }
    return allSuccess;
}

bool DynamicMarksController::HasDynamicMarks(const Document& doc) {
    for (const auto& [id, obj] : doc.objects()) {
        // Verifica se é marca dinâmica (CutMark, BearerBar, etc.)
        // Por enquanto, verifica pelo nome ou metadados
        if (obj->name().contains("DynamicMark", Qt::CaseInsensitive) ||
            obj->name().contains("CutMark", Qt::CaseInsensitive) ||
            obj->name().contains("BearerBar", Qt::CaseInsensitive)) {
            return true;
        }
    }
    return false;
}

std::vector<ObjectId> DynamicMarksController::GetDynamicMarkIds(const Document& doc) {
    std::vector<ObjectId> ids;
    for (const auto& [id, obj] : doc.objects()) {
        if (obj->name().contains("DynamicMark", Qt::CaseInsensitive) ||
            obj->name().contains("CutMark", Qt::CaseInsensitive) ||
            obj->name().contains("BearerBar", Qt::CaseInsensitive)) {
            ids.push_back(id);
        }
    }
    return ids;
}

bool DynamicMarksController::relinkMark(Document& doc, ObjectId markId,
                                        const std::unordered_map<ObjectId, ObjectId>& idRemap) {
    auto mark = doc.object(markId);
    if (!mark) return false;

    // Se a marca tem referências que não estão no remap, tenta encontrar por nome
    // ou por page box
    // Implementação simplificada
    return true;
}

ObjectId DynamicMarksController::findTargetByName(const Document& doc, const QString& name) {
    for (const auto& [id, obj] : doc.objects()) {
        if (obj->name() == name) return id;
    }
    return 0;
}

ObjectId DynamicMarksController::findTargetByPageBox(const Document& doc, PageBoxType boxType) {
    // Procura objeto que representa a page box (ex: crop marks referenciam CropBox)
    // Implementação simplificada
    return 0;
}

} // namespace ArtPlus