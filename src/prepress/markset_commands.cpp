#include "prepress/markset_commands.h"
#include "../document/undo.h"
#include <algorithm>
#include <utility>

namespace ArtPlus::Prepress {

ApplyMarkSetCommand::ApplyMarkSetCommand(
    Document& doc,
    PageId pageId,
    std::string markSetPath,
    bool deleteExisting,
    std::vector<ObjectId> copiedObjectIds,
    std::vector<RemovedObject> removedObjects,
    std::vector<Separation::Entry> previousSeparations,
    std::vector<Separation::Entry> newSeparations)
    : m_pageId(pageId),
      m_markSetPath(std::move(markSetPath)),
      m_deleteExisting(deleteExisting),
      m_copiedObjectIds(std::move(copiedObjectIds)),
      m_removedObjects(std::move(removedObjects)),
      m_previousSeparations(std::move(previousSeparations)),
      m_newSeparations(std::move(newSeparations)) {
    // Snapshot dos objetos copiados após a aplicação — usado para reconstruí-los no redo.
    m_copiedSnapshots.reserve(m_copiedObjectIds.size());
    for (ObjectId id : m_copiedObjectIds) {
        if (auto obj = doc.object(id)) m_copiedSnapshots.push_back(obj->clone());
    }
}

void ApplyMarkSetCommand::undo(Document& doc) const {
    // Remove os objetos criados pela aplicação e suas referências nas camadas.
    for (ObjectId id : m_copiedObjectIds) {
        doc.removeObject(id);
        for (LayerId layerId : doc.layerOrder()) {
            if (auto layer = doc.layer(layerId)) layer->removeObject(id);
        }
    }

    // Restaura objetos removidos pela flag deleteExisting (com id original e posição na camada).
    for (const RemovedObject& removed : m_removedObjects) {
        auto snapshot = removed.snapshot ? removed.snapshot : doc.object(removed.id);
        if (!snapshot) continue;
        const ObjectId id = removed.id ? removed.id : snapshot->id();
        snapshot->setId(id);
        doc.addObject(snapshot);
        if (auto layer = doc.layer(removed.layerId)) {
            if (removed.layerIndex >= 0 && static_cast<size_t>(removed.layerIndex) <= layer->objects().size()) {
                layer->insertObjectAt(static_cast<size_t>(removed.layerIndex), id);
            } else {
                layer->addObject(id);
            }
        }
    }

    doc.setSeparationInfo(m_previousSeparations);
}

void ApplyMarkSetCommand::redo(Document& doc) const {
    // Remove novamente os objetos anteriores se deleteExisting estava ativo.
    if (m_deleteExisting) {
        for (const RemovedObject& removed : m_removedObjects) {
            const ObjectId id = removed.id;
            doc.removeObject(id);
            for (LayerId layerId : doc.layerOrder()) {
                if (auto layer = doc.layer(layerId)) layer->removeObject(id);
            }
        }
    }

    // Recria os objetos copiados a partir dos snapshots pós-aplicação.
    for (size_t i = 0; i < m_copiedObjectIds.size() && i < m_copiedSnapshots.size(); ++i) {
        const ObjectId id = m_copiedObjectIds[i];
        auto copy = m_copiedSnapshots[i] ? m_copiedSnapshots[i]->clone() : nullptr;
        if (!copy) continue;
        copy->setId(id);
        doc.addObject(copy);
        if (auto layer = doc.layer(copy->layerId())) layer->addObject(id);
    }

    doc.setSeparationInfo(m_newSeparations);
}

} // namespace ArtPlus::Prepress
