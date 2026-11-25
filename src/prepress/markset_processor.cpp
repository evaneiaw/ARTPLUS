#include "prepress/markset_processor.h"
#include "prepress/markset_commands.h"
#include "prepress/markset_reporter.h"
#include "pdf/markset_pdf_loader.h"
#include "../document/document_serializer.h"
#include "../document/dynamic_marks_controller.h"
#include "../pdf/pdf_document.h"
#include "../pdf/pdf_importer.h"
#include "../document/undo.h"

#include <QFileInfo>
#include <QString>
#include <QCoreApplication>

#include <deque>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace ArtPlus;
using namespace ArtPlus::Prepress;
using namespace ArtPlus::PDF;

namespace ArtPlus::Prepress {

// Objetos que compõem a página: primeiro a ordem das camadas (ordem de desenho), depois
// qualquer objeto alcançável apenas por referência — máscara de clipping, soft mask e
// filhos de grupo. Garante que nenhuma cópia fique apontando para um id do mark set.
std::vector<ObjectId> MarkSetProcessor::pageObjectIds(const Document& doc, const Page& page) const {
    std::vector<ObjectId> ids;
    std::unordered_set<ObjectId> seen;
    std::deque<ObjectId> pending;

    auto visit = [&](ObjectId id) {
        if (id == 0 || !doc.object(id) || !seen.insert(id).second) return;
        ids.push_back(id);
        pending.push_back(id);
    };

    for (LayerId layerId : page.layers()) {
        auto layer = doc.layer(layerId);
        if (!layer) continue;
        for (ObjectId objectId : layer->objects()) visit(objectId);
    }
    while (!pending.empty()) {
        const ObjectId id = pending.front();
        pending.pop_front();
        auto object = doc.object(id);
        if (!object) continue;
        for (ObjectId clipId : object->clipMaskIds()) visit(clipId);
        visit(object->softMaskId());
        for (ObjectId childId : object->children()) visit(childId);
    }
    return ids;
}

// Encontra ou cria camada correspondente no documento de destino,
// preservando a estrutura de camadas do mark set
ArtPlus::Layer* MarkSetProcessor::targetLayerFor(const ArtPlus::Page& page, const ArtPlus::Document& markSetDoc, const ArtPlus::Page& markSetPage,
                       const std::unordered_map<LayerId, LayerId>& layerRemap) {
    // Procura camada do mark set que corresponda à camada de origem
    for (LayerId srcLayerId : markSetPage.layers()) {
        auto srcLayer = markSetDoc.layer(srcLayerId);
        if (!srcLayer) continue;

        auto it = layerRemap.find(srcLayerId);
        if (it != layerRemap.end()) {
            if (auto dstLayer = m_targetDocument->layer(it->second)) {
                return dstLayer.get();
            }
        }
    }

    // Fallback: camada de topo da página alvo
    for (auto it = page.layers().rbegin(); it != page.layers().rend(); ++it) {
        if (auto layer = m_targetDocument->layer(*it)) return layer.get();
    }

    // Cria nova camada se necessário
    auto layer = std::make_shared<Layer>("Mark Set");
    m_targetDocument->addLayer(layer);
    const_cast<Page&>(page).addLayer(layer->id());
    return layer.get();
}

// Copia `sourceIds` do mark set para a página alvo com ids novos.
// Ordem das operações: clona e remapeia tudo primeiro (nenhuma escrita no destino) e só
// depois cria camada/objetos, de modo que uma falha não deixa o destino meio alterado.
bool MarkSetProcessor::copyPageObjects(const Document& sourceDoc,
                      const std::vector<ObjectId>& sourceIds,
                      Document& targetDoc,
                      Page& targetPage,
                      bool deleteExisting,
                      std::vector<ObjectId>& copiedObjectIds,
                      std::vector<ObjectId>& removedObjectIds,
                      Reporter* reporter,
                      const std::string& markSetName,
                      size_t pageIndex) {
    struct Clone {
        std::shared_ptr<DocumentObject> source;
        std::shared_ptr<DocumentObject> copy;
    };

    std::vector<Clone> clones;
    clones.reserve(sourceIds.size());
    std::unordered_map<ObjectId, ObjectId> remap;

    // Mapeamento de camadas: camada do mark set -> camada do destino
    std::unordered_map<LayerId, LayerId> layerRemap;

    // Se deleteExisting, captura objetos para remoção/undo.
    // A seleção dos IDs é responsabilidade do chamador (MarkSetProcessor rastreia marcas
    // aplicadas por página). Não removemos conteúdo arbitrário sem rastreio explícito.

    for (ObjectId sourceId : sourceIds) {
        auto source = sourceDoc.object(sourceId);
        if (!source) continue;
        auto copy = source->clone(); // DocumentObject::clone() atribui um ObjectId novo
        if (!copy) {
            return false;
        }
        remap[sourceId] = copy->id();
        clones.push_back(Clone{std::move(source), std::move(copy)});
    }
    if (clones.empty()) {
        return false;
    }

    // Referência que sai do conjunto copiado não existe no documento de destino:
    // tenta relink via DynamicMarksController, senão emite aviso via Reporter
    auto mappedId = [&remap](ObjectId oldId) -> ObjectId {
        if (oldId == 0) return 0;
        auto it = remap.find(oldId);
        return it != remap.end() ? it->second : 0;
    };

    // Cria camadas correspondentes no destino
    auto sourcePage = sourceDoc.page(sourceDoc.pageOrder().front());
    for (LayerId srcLayerId : sourcePage->layers()) {
        auto srcLayer = sourceDoc.layer(srcLayerId);
        if (!srcLayer) continue;

        // Procura camada com mesmo nome no destino
        LayerId dstLayerId = 0;
        for (LayerId dstId : targetPage.layers()) {
            if (auto dstLayer = targetDoc.layer(dstId)) {
                if (dstLayer->name().toStdString() == srcLayer->name().toStdString()) {
                    dstLayerId = dstId;
                    break;
                }
            }
        }

        if (dstLayerId == 0) {
            // Cria nova camada preservando propriedades
            auto newLayer = std::make_shared<Layer>(srcLayer->name());
            newLayer->setVisible(srcLayer->visible());
            newLayer->setLocked(srcLayer->locked());
            newLayer->setPrintable(srcLayer->printable());
            newLayer->setColor(srcLayer->color());
            newLayer->setOpacity(srcLayer->opacity());
            targetDoc.addLayer(newLayer);
            targetPage.addLayer(newLayer->id());
            dstLayerId = newLayer->id();
        }
        layerRemap[srcLayerId] = dstLayerId;
    }

    // Reconfigura referências internas dos clones
    for (auto& clone : clones) {
        auto& copy = *clone.copy;
        copy.clearClipMaskIds();
        for (ObjectId oldClip : clone.source->clipMaskIds()) {
            if (ObjectId newClip = mappedId(oldClip)) copy.addClipMaskId(newClip);
        }
        copy.setSoftMaskId(mappedId(clone.source->softMaskId()));
        copy.setParentId(mappedId(clone.source->parentId()));
        copy.setLayerId(layerRemap.count(clone.source->layerId()) ? 
                        layerRemap.at(clone.source->layerId()) : 0);

        const std::vector<ObjectId> copiedChildren(copy.children().begin(), copy.children().end());
        for (ObjectId oldChild : copiedChildren) copy.removeChild(oldChild);
        for (ObjectId oldChild : clone.source->children()) {
            if (ObjectId newChild = mappedId(oldChild)) copy.addChild(newChild);
        }
    }

    // Adiciona objetos clonados ao documento
    for (auto& clone : clones) {
        targetDoc.addObject(clone.copy);
        copiedObjectIds.push_back(clone.copy->id());

        // Adiciona à camada correspondente
        if (auto layer = targetDoc.layer(clone.copy->layerId())) {
            layer->addObject(clone.copy->id());
        }
    }

    // Remove objetos existentes se deleteExisting (do documento e das camadas)
    if (deleteExisting) {
        for (ObjectId id : removedObjectIds) {
            targetDoc.removeObject(id);
            for (LayerId layerId : targetDoc.layerOrder()) {
                if (auto layer = targetDoc.layer(layerId)) layer->removeObject(id);
            }
        }
    }

    // Relink de marcas dinâmicas (referências fora do conjunto copiado)
    if (!relinkDynamicObjects(sourceDoc, sourceIds, targetDoc, remap, reporter, markSetName, pageIndex)) {
        // Aviso já emitido pelo relink
    }

    return true;
}

bool MarkSetProcessor::relinkDynamicObjects(const Document& sourceDoc,
                          const std::vector<ObjectId>& sourceIds,
                          Document& targetDoc,
                          const std::unordered_map<ObjectId, ObjectId>& remap,
                          Reporter* reporter,
                          const std::string& markSetName,
                          size_t pageIndex) {
    auto isPageBoxName = [](const QString& name) {
        return name == QStringLiteral("MediaBox") || name == QStringLiteral("CropBox")
            || name == QStringLiteral("BleedBox") || name == QStringLiteral("TrimBox")
            || name == QStringLiteral("ArtBox");
    };

    // Religa referências externas (fora do conjunto copiado) por nome.
    // E4: MissingNamedObject; E5: MissingPageBox quando a referência é a uma page box.
    for (ObjectId sourceId : sourceIds) {
        auto source = sourceDoc.object(sourceId);
        if (!source) continue;

        auto findByName = [&](const QString& name) -> ObjectId {
            if (name.isEmpty()) return 0;
            for (const auto& [id, obj] : targetDoc.objects()) {
                if (obj && obj->name() == name && remap.find(id) == remap.end()) return id;
            }
            return 0;
        };

        const ObjectId copiedId = remap.count(sourceId) ? remap.at(sourceId) : 0;

        auto handleMissing = [&](const QString& name) {
            if (!reporter || name.isEmpty()) return;
            if (isPageBoxName(name)) {
                reporter->warnMissingPageBox(name.toStdString(), markSetName, pageIndex);
            } else {
                reporter->warnMissingNamedObject({name.toStdString()}, markSetName, pageIndex);
            }
        };

        // clipMaskIds externos
        for (ObjectId clipId : source->clipMaskIds()) {
            if (clipId == 0 || remap.find(clipId) != remap.end()) continue;
            auto clipObj = sourceDoc.object(clipId);
            const QString name = clipObj ? clipObj->name() : QString();
            if (name.isEmpty()) continue;
            ObjectId targetId = findByName(name);
            if (targetId && copiedId) {
                if (auto copy = targetDoc.object(copiedId)) copy->addClipMaskId(targetId);
            } else {
                handleMissing(name);
            }
        }

        // softMaskId externo
        if (source->softMaskId() != 0 && remap.find(source->softMaskId()) == remap.end()) {
            auto maskObj = sourceDoc.object(source->softMaskId());
            const QString name = maskObj ? maskObj->name() : QString();
            if (!name.isEmpty()) {
                ObjectId targetId = findByName(name);
                if (targetId && copiedId) {
                    if (auto copy = targetDoc.object(copiedId)) copy->setSoftMaskId(targetId);
                } else {
                    handleMissing(name);
                }
            }
        }
    }

    DynamicMarksController::RelinkDynamicObjects(targetDoc, sourceIds, remap);
    return true;
}

void MarkSetProcessor::setTargetDocument(Document& targetDocument) {
    m_targetDocument = &targetDocument;
}

bool MarkSetProcessor::prepareMarksCachePage(const Page& page) {
    m_lastError.clear();
    m_lastCopiedObjectCount = 0;

    if (page.id() == 0) {
        m_lastError = "WrongMarkSet: target page id is invalid (0)";
        return false;
    }
    const QRectF rect = page.pageRect();
    if (!rect.isValid() || rect.width() <= 0.0 || rect.height() <= 0.0) {
        m_lastError = "WrongMarkSet: target page " + std::to_string(page.id())
                      + " has no usable geometry";
        return false;
    }
    if (m_targetDocument && !m_targetDocument->page(page.id())) {
        m_lastError = "WrongMarkSet: target page " + std::to_string(page.id())
                      + " does not belong to the target document";
        return false;
    }

    // Consolida separações da página
    if (m_targetDocument && !consolidateSeparations(page)) {
        m_lastError = "SeparationConsolidationFailed: failed to consolidate separations for page " + std::to_string(page.id());
        return false;
    }

    // Desabilita updates de marcas dinâmicas durante a aplicação
    if (m_targetDocument) { DynamicMarksController::EnableUpdates(*m_targetDocument, false); }

    m_targetPageId = page.id();
    return true;
}

bool MarkSetProcessor::consolidateSeparations(const Page& page) {
    if (!m_targetDocument) return false;

    // R2/R7: consolida separações usadas pela página e grava em Document::SetSeparationInfo.
    // Coleta spot colors de fill/stroke dos objetos da página e faz FindOrAdd nas separações
    // existentes do documento.
    std::vector<Separation::Entry> consolidated = m_targetDocument->separationInfo();
    std::unordered_set<QString> seenNames;
    for (const auto& e : consolidated) seenNames.insert(e.name);

    bool changed = false;
    for (LayerId layerId : page.layers()) {
        auto layer = m_targetDocument->layer(layerId);
        if (!layer) continue;
        for (ObjectId objId : layer->objects()) {
            auto obj = m_targetDocument->object(objId);
            if (!obj) continue;
            auto checkColor = [&](const Color& color) {
                if (color.type != Color::Type::Spot || color.spotName.isEmpty()) return;
                const QString name = color.spotName;
                if (!seenNames.insert(name).second) return;
                Separation::Entry entry;
                entry.name = name;
                entry.type = Separation::Type::Spot;
                entry.tint = color.tint;
                consolidated.push_back(entry);
                changed = true;
            };
            checkColor(obj->fillStroke().fill);
            checkColor(obj->fillStroke().stroke);
        }
    }

    if (changed) {
        m_targetDocument->setSeparationInfo(consolidated);
    }
    return true;
}

bool MarkSetProcessor::loadMarkSetFile(const std::string& filePath, Document& markSetDocument) {
    if (filePath.empty()) {
        m_lastError = "MarkSetFileDoesNotExist: mark set path is empty";
        return false;
    }

    const QString path = QString::fromStdString(filePath);
    const QFileInfo info(path);
    if (!info.exists() || !info.isFile()) {
        m_lastError = "MarkSetFileDoesNotExist: Markset file '" + filePath + "' does not exist!";
        return false;
    }
    if (!info.isReadable()) {
        m_lastError = "CannotOpenMarkSetFile: Markset file '" + filePath + "' is not readable";
        return false;
    }

    const QString suffix = info.suffix().toLower();
    if (suffix == QStringLiteral("pdf")) {
        // Usa MarkSetPdfLoader para PDFs com metadata.DocumentMarks
        auto result = ArtPlus::PDF::MarkSetPdfLoader::load(filePath);
        if (!result.success) {
            m_lastError = result.errorDetail;
            return false;
        }
        // E3: Detecta marca de arquivo de entrada no mark set
        if (result.info.hasInputFileMark) {
            m_lastError = "MarkSetContainsInputFileMark: mark set contains InputFileMark";
            return false;
        }
        if (result.document) {
            markSetDocument = *result.document;
        }
        return true;
    }

    if (suffix == QStringLiteral("artplus") || suffix == QStringLiteral("json")) {
        if (!DocumentSerializer::load(path, markSetDocument)) {
            m_lastError = "MarkSetFileError: Markset file '" + filePath
                          + "' error! (not a valid .artplus document)";
            return false;
        }
        return true;
    }

    m_lastError = "WrongMarkSet: unsupported mark set format '." + suffix.toStdString()
                  + "' (expected .pdf or .artplus)";
    return false;
}

bool MarkSetProcessor::applyMarksFromSet(const std::string& markSetPath, bool deleteExisting) {
    m_lastError.clear();
    m_lastCopiedObjectCount = 0;

    if (markSetPath.empty()) {
        m_lastError = "MarkSetFileDoesNotExist: mark set path is empty";
        return false;
    }
    if (!m_targetDocument) {
        m_lastError = "WrongMarkSet: no target document (call setTargetDocument first)";
        return false;
    }
    if (m_targetPageId == 0) {
        m_lastError = "WrongMarkSet: no target page prepared (call prepareMarksCachePage first)";
        return false;
    }
    auto targetPage = m_targetDocument->page(m_targetPageId);
    if (!targetPage) {
        m_lastError = "WrongMarkSet: target page " + std::to_string(m_targetPageId)
                      + " no longer exists in the target document";
        return false;
    }

    // Carrega mark set
    Document markSet;
    if (!loadMarkSetFile(markSetPath, markSet)) return false;
    if (markSet.pageOrder().empty()) {
        m_lastError = "EmptyMarkSetVector: Markset file '" + markSetPath + "' has no pages";
        return false;
    }

    // Copia primeira página
    return copyMarksToPage(markSet, *targetPage, markSetPath, deleteExisting);
}

bool MarkSetProcessor::copyMarksToPage(const Document& sourceDoc, const Page& targetPage, const std::string& markSetPath, bool deleteExisting) {
    m_lastError.clear();
    m_lastCopiedObjectCount = 0;

    if (!m_targetDocument) {
        m_lastError = "WrongMarkSet: no target document (call setTargetDocument first)";
        return false;
    }
    auto target = m_targetDocument->page(targetPage.id());
    if (!target) {
        m_lastError = "WrongMarkSet: target page " + std::to_string(targetPage.id())
                      + " does not belong to the target document";
        return false;
    }
    if (sourceDoc.pageOrder().empty()) {
        m_lastError = "WrongMarkSet: source document has no pages";
        return false;
    }

    // ApplyMarksFromSet copia a PRIMEIRA página do documento de mark set
    auto sourcePage = sourceDoc.page(sourceDoc.pageOrder().front());
    if (!sourcePage) {
        m_lastError = "MarkSetFileError: first page of the source document cannot be read";
        return false;
    }

    const std::vector<ObjectId> sourceIds = pageObjectIds(sourceDoc, *sourcePage);
    if (sourceIds.empty()) {
        m_lastError = "EmptyFirstPage: first page of the source document has no objects";
        return false;
    }

    std::vector<ObjectId> copiedIds;
    std::vector<ObjectId> removedIds;
    std::vector<ApplyMarkSetCommand::RemovedObject> removedObjects;
    const auto previousSeparations = m_targetDocument->separationInfo();

    // Captura snapshots das marcas existentes que serão removidas (deleteExisting).
    // Preferimos remover apenas marcas previamente aplicadas por este processor (rastreadas
    // em m_marksByPage). Fallback: se não houver rastreio, não remove conteúdo arbitrário.
    if (deleteExisting) {
        std::vector<ObjectId> toRemove;
        auto itTracked = m_marksByPage.find(target->id());
        if (itTracked != m_marksByPage.end()) {
            toRemove = itTracked->second;
        }
        std::unordered_set<ObjectId> removeSet(toRemove.begin(), toRemove.end());
        for (LayerId layerId : target->layers()) {
            auto layer = m_targetDocument->layer(layerId);
            if (!layer) continue;
            const auto& objs = layer->objects();
            for (size_t idx = 0; idx < objs.size(); ++idx) {
                ObjectId objId = objs[idx];
                if (removeSet.find(objId) == removeSet.end()) continue;
                auto obj = m_targetDocument->object(objId);
                if (!obj) continue;
                ApplyMarkSetCommand::RemovedObject r;
                r.id = objId;
                r.layerId = layerId;
                r.layerIndex = static_cast<int>(idx);
                r.snapshot = obj->clone();
                r.snapshot->setId(objId);
                removedObjects.push_back(r);
                removedIds.push_back(objId);
            }
        }
    }

    // Abre ActionGroupCreator para undo
    // Nota: UndoStack não tem ActionGroupCreator explícito, usamos comando direto
    bool success = copyPageObjects(sourceDoc, sourceIds, *m_targetDocument, *target,
                                   deleteExisting, copiedIds, removedIds, m_reporter.get(),
                                   QFileInfo(QString::fromStdString(markSetPath)).fileName().toStdString(), 0);

    if (success) {
        // Consolida separações após cópia
        consolidateSeparations(*target);

        // Reabilita updates de marcas dinâmicas
        DynamicMarksController::EnableUpdates(*m_targetDocument, true);

        m_targetDocument->setModified(true);
        m_lastCopiedObjectCount = static_cast<int>(copiedIds.size());

        // Cache para identifyRelevantSets
        MarkSetInfo info;
        info.filePath = markSetPath;
        info.displayName = QFileInfo(QString::fromStdString(markSetPath)).baseName().toStdString();
        info.pageOrder = sourceDoc.pageOrder();
        const PageBoxes& boxes = sourcePage->boxes();
        info.pageBoxes = {
            PageBox{"MediaBox", boxes.mediaBox},
            PageBox{"CropBox", boxes.cropBox},
            PageBox{"BleedBox", boxes.bleedBox},
            PageBox{"TrimBox", boxes.trimBox},
            PageBox{"ArtBox", boxes.artBox},
        };
        info.separations = sourceDoc.separationInfo();
        m_loadedMarkSets.push_back(info);

        // Undo wiring: empilha comando se UndoStack disponível
        if (m_undoStack) {
            auto cmd = std::make_unique<ApplyMarkSetCommand>(
                *m_targetDocument, target->id(), markSetPath, deleteExisting, copiedIds,
                std::move(removedObjects), previousSeparations, m_targetDocument->separationInfo());
            m_undoStack->push(std::move(cmd));
        }

        // Rastreia marcas aplicadas por página (para deleteExisting em chamadas posteriores)
        if (deleteExisting) {
            m_marksByPage[target->id()] = copiedIds;
        } else {
            auto& existing = m_marksByPage[target->id()];
            existing.insert(existing.end(), copiedIds.begin(), copiedIds.end());
        }
    }

    return success;
}

std::vector<MarkSetInfo> MarkSetProcessor::identifyRelevantSets() const {
    std::vector<MarkSetInfo> relevant;
    if (m_targetPageId == 0 || !m_targetDocument) return relevant;

    auto targetPage = m_targetDocument->page(m_targetPageId);
    if (!targetPage) return relevant;

    // Critério (ADR-012/§9.1): match por metadados disponíveis (pageBoxes, separações, nome).
    // A seleção de marca é explícita; aqui filtramos apenas sets com metadados comprováveis
    // que coincidem com a página alvo. Se não houver metadados para comparar, o set não é
    // incluído automaticamente para evitar retorno indiscriminado.
    const PageBoxes& targetBoxes = targetPage->boxes();
    std::unordered_set<QString> targetSepNames;
    for (const auto& s : m_targetDocument->separationInfo()) targetSepNames.insert(s.name);

    // Mapeamento de nomes de PageBox para membros correspondentes em PageBoxes
    auto boxFromName = [&](const QString& name) -> const QRectF* {
        if (name == QStringLiteral("MediaBox")) return &targetBoxes.mediaBox;
        if (name == QStringLiteral("CropBox")) return &targetBoxes.cropBox;
        if (name == QStringLiteral("BleedBox")) return &targetBoxes.bleedBox;
        if (name == QStringLiteral("TrimBox")) return &targetBoxes.trimBox;
        if (name == QStringLiteral("ArtBox")) return &targetBoxes.artBox;
        return nullptr;
    };

    for (const auto& info : m_loadedMarkSets) {
        bool hasMeta = !info.pageBoxes.empty() || !info.separations.empty();
        if (!hasMeta) continue;

        bool match = false;

        // 1. Match por pageBoxes: ao menos uma caixa de página tem mesma geometria
        if (!info.pageBoxes.empty()) {
            for (const auto& pb : info.pageBoxes) {
                const QRectF* targetRect = boxFromName(pb.name);
                if (targetRect && targetRect->isValid() && pb.rect.isValid() &&
                    qFuzzyCompare(targetRect->width(), pb.rect.width()) &&
                    qFuzzyCompare(targetRect->height(), pb.rect.height()) &&
                    qFuzzyCompare(targetRect->x(), pb.rect.x()) &&
                    qFuzzyCompare(targetRect->y(), pb.rect.y())) {
                    match = true;
                    break;
                }
            }
        }

        // 2. Match por separações: pelo menos uma separação do mark set coincide com a página alvo
        if (!match && !info.separations.empty()) {
            for (const auto& s : info.separations) {
                if (targetSepNames.find(s.name) != targetSepNames.end()) { match = true; break; }
            }
        }

        // 3. Se o displayName coincide exatamente, consideramos match (compatibilidade UI)
        if (!match && !info.displayName.empty() && !targetBoxes.mediaBox.isNull()) {
            // exibição de nome coincide se o arquivo carregado tiver nome idêntico ao nome da marca
            // (não implementado como critério principal)
        }

        if (match) relevant.push_back(info);
    }
    return relevant;
}

bool MarkSetProcessor::applyExtraMarkSet(const std::vector<std::string>& markSetPaths) {
    if (markSetPaths.empty()) {
        m_lastError = "EmptyMarkSetVector: no mark set paths provided";
        return false;
    }
    if (!m_targetDocument || m_targetPageId == 0) {
        m_lastError = "WrongMarkSet: no target document/page prepared";
        return false;
    }

    for (const auto& path : markSetPaths) {
        if (!applyMarksFromSet(path, false)) {
            return false;
        }
    }
    return true;
}

bool MarkSetProcessor::applyMarkSetToDocument(const std::string& markSetPath, bool deleteExisting) {
    if (!m_targetDocument) {
        m_lastError = "WrongMarkSet: no target document";
        return false;
    }

    bool anySuccess = false;
    for (PageId pageId : m_targetDocument->pageOrder()) {
        auto page = m_targetDocument->page(pageId);
        if (!page) continue;

        if (!prepareMarksCachePage(*page)) continue;
        if (applyMarksFromSet(markSetPath, deleteExisting)) {
            anySuccess = true;
        }
    }

    return anySuccess;
}

bool MarkSetProcessor::applyMarkSetToPage(const std::string& markSetPath, const Page& targetPage, bool deleteExisting) {
    if (!m_targetDocument) {
        m_lastError = "WrongMarkSet: no target document";
        return false;
    }

    if (!prepareMarksCachePage(targetPage)) return false;
    return applyMarksFromSet(markSetPath, deleteExisting);
}

const std::string& MarkSetProcessor::lastError() const {
    return m_lastError;
}

int MarkSetProcessor::lastCopiedObjectCount() const {
    return m_lastCopiedObjectCount;
}

void MarkSetProcessor::setReporter(std::unique_ptr<Reporter> reporter) {
    m_reporter = std::move(reporter);
}

} // namespace ArtPlus::Prepress
