#ifndef MARKSET_COMMANDS_H
#define MARKSET_COMMANDS_H

#include "../document/document_model.h"
#include "../document/undo.h"
#include <string>
#include <vector>
#include <QCoreApplication>

namespace ArtPlus::Prepress {

class ApplyMarkSetCommand : public Command {
public:
    struct RemovedObject {
        ArtPlus::ObjectId id = 0;
        ArtPlus::LayerId layerId = 0;
        int layerIndex = -1;
        std::shared_ptr<ArtPlus::DocumentObject> snapshot;
    };

    ApplyMarkSetCommand(ArtPlus::Document& doc,
                        ArtPlus::PageId pageId,
                        std::string markSetPath,
                        bool deleteExisting,
                        std::vector<ArtPlus::ObjectId> copiedObjectIds,
                        std::vector<RemovedObject> removedObjects,
                        std::vector<Separation::Entry> previousSeparations,
                        std::vector<Separation::Entry> newSeparations);
    ~ApplyMarkSetCommand() override = default;

    void undo(ArtPlus::Document& doc) const override;
    void redo(ArtPlus::Document& doc) const override;
    QString description() const override { return QCoreApplication::translate("ApplyMarkSetCommand", "Apply Mark Set"); }

private:
    ArtPlus::PageId m_pageId = 0;
    std::string m_markSetPath;
    bool m_deleteExisting = false;
    std::vector<ArtPlus::ObjectId> m_copiedObjectIds;
    std::vector<RemovedObject> m_removedObjects;
    std::vector<Separation::Entry> m_previousSeparations;
    std::vector<Separation::Entry> m_newSeparations;
    // Snapshots dos objetos copiados (estado pós-aplicação) para redo.
    std::vector<std::shared_ptr<ArtPlus::DocumentObject>> m_copiedSnapshots;
};

} // namespace ArtPlus::Prepress

#endif // MARKSET_COMMANDS_H
