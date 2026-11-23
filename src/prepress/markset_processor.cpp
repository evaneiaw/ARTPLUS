#include "prepress/markset_processor.h"

#include "../document/document_serializer.h"
#include "../pdf/pdf_document.h"
#include "../pdf/pdf_importer.h"

#include <QFileInfo>
#include <QString>

#include <deque>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace ArtPlus;

namespace {

// Objetos que compõem a página: primeiro a ordem das camadas (ordem de desenho), depois
// qualquer objeto alcançável apenas por referência — máscara de clipping, soft mask e
// filhos de grupo. Garante que nenhuma cópia fique apontando para um id do mark set.
std::vector<ObjectId> pageObjectIds(const Document& doc, const Page& page) {
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

// Camada de destino: a de topo da página, porque a marca entra por cima do conteúdo
// (v240 CopyMarksToPage insere sobre o conteúdo da página). O importador sempre cria uma
// camada por página; o ramo que cria a camada existe para páginas montadas à mão.
std::shared_ptr<Layer> targetLayerFor(Document& doc, Page& page) {
    for (auto it = page.layers().rbegin(); it != page.layers().rend(); ++it) {
        if (auto layer = doc.layer(*it)) return layer;
    }
    auto layer = std::make_shared<Layer>("Mark Set");
    doc.addLayer(layer);
    page.addLayer(layer->id());
    return layer;
}

// Copia `sourceIds` do mark set para a página alvo com ids novos.
// Ordem das operações: clona e remapeia tudo primeiro (nenhuma escrita no destino) e só
// depois cria camada/objetos, de modo que uma falha não deixa o destino meio alterado.
bool copyPageObjects(const Document& sourceDoc,
                     const std::vector<ObjectId>& sourceIds,
                     Document& targetDoc,
                     Page& targetPage,
                     int& copiedCount,
                     std::string& error) {
    struct Clone {
        std::shared_ptr<DocumentObject> source;
        std::shared_ptr<DocumentObject> copy;
    };

    std::vector<Clone> clones;
    clones.reserve(sourceIds.size());
    std::unordered_map<ObjectId, ObjectId> remap;

    for (ObjectId sourceId : sourceIds) {
        auto source = sourceDoc.object(sourceId);
        if (!source) continue;
        auto copy = source->clone(); // DocumentObject::clone() atribui um ObjectId novo
        if (!copy) {
            error = "MarkSetFileError: could not clone object " + std::to_string(sourceId);
            return false;
        }
        remap[sourceId] = copy->id();
        clones.push_back(Clone{std::move(source), std::move(copy)});
    }
    if (clones.empty()) {
        error = "WrongMarkSet: mark set page has no objects to copy";
        return false;
    }

    // Referência que sai do conjunto copiado não existe no documento de destino:
    // é descartada em vez de virar id órfão. TODO(F-002): a v240 religa marcas
    // dinâmicas a objetos ausentes (RelinkDynamicObjects, 0x1800426F0) e emite os
    // avisos "Missing Named Object"/"Missing Page Box" (0x180245380); o modelo do
    // clone ainda não representa marcas dinâmicas, então o relink não é feito.
    auto mappedId = [&remap](ObjectId oldId) -> ObjectId {
        if (oldId == 0) return 0;
        auto it = remap.find(oldId);
        return it != remap.end() ? it->second : 0;
    };

    auto targetLayer = targetLayerFor(targetDoc, targetPage);

    for (auto& clone : clones) {
        auto& copy = *clone.copy;
        copy.clearClipMaskIds();
        for (ObjectId oldClip : clone.source->clipMaskIds()) {
            if (ObjectId newClip = mappedId(oldClip)) copy.addClipMaskId(newClip);
        }
        copy.setSoftMaskId(mappedId(clone.source->softMaskId()));
        // clone() não leva parentId e copia os filhos com os ids do mark set.
        copy.setParentId(mappedId(clone.source->parentId()));
        copy.setLayerId(targetLayer->id());
        const std::vector<ObjectId> copiedChildren(copy.children().begin(), copy.children().end());
        for (ObjectId oldChild : copiedChildren) copy.removeChild(oldChild);
        for (ObjectId oldChild : clone.source->children()) {
            if (ObjectId newChild = mappedId(oldChild)) copy.addChild(newChild);
        }
    }

    for (auto& clone : clones) {
        targetDoc.addObject(clone.copy);
        targetLayer->addObject(clone.copy->id());
    }

    copiedCount = static_cast<int>(clones.size());
    return true;
}

} // namespace

MarkSetProcessor::MarkSetProcessor() = default;

void MarkSetProcessor::setTargetDocument(Document& targetDocument) {
    m_targetDocument = &targetDocument;
}

std::vector<std::string> MarkSetProcessor::identifyRelevantSets() const {
    // TODO(F-002): a v240 (ApplyRelevantMarkSets, 0x18024D460) identifica o mark set
    // "relevante" por nome/tipo, mas o critério não foi derivado da evidência
    // (F-002 §Em aberto, item 2). Devolver ids fixos seria simulação; vazio significa
    // "nenhum conjunto identificado automaticamente".
    return {};
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

    m_targetPageId = page.id();
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
        PDF::PdfDocument pdf;
        if (!pdf.open(path)) {
            m_lastError = "CannotOpenMarkSetFile: Markset file '" + filePath + "' error!";
            return false;
        }
        PdfImportResult imported = PdfImporter::import(pdf, markSetDocument);
        if (!imported.ok) {
            m_lastError = "MarkSetFileError: Markset file '" + filePath + "' error! ("
                          + imported.error.toStdString() + ")";
            return false;
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

bool MarkSetProcessor::applyMarksFromSet(const std::string& markSetPath) {
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

    // R1: o mark set entra num documento local. O destino só é escrito na cópia, depois
    // de o arquivo carregar e a primeira página existir.
    Document markSet;
    if (!loadMarkSetFile(markSetPath, markSet)) return false;
    if (markSet.pageOrder().empty()) {
        m_lastError = "MarkSetFileError: Markset file '" + markSetPath + "' error! (no pages)";
        return false;
    }

    return copyMarksToPage(markSet, *targetPage);
}

bool MarkSetProcessor::copyMarksToPage(const Document& sourceDoc, const Page& targetPage) {
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
    // (0x180243EC0: *GetPagesBegin(doc)), não a página corrente da origem.
    auto sourcePage = sourceDoc.page(sourceDoc.pageOrder().front());
    if (!sourcePage) {
        m_lastError = "MarkSetFileError: first page of the source document cannot be read";
        return false;
    }

    const std::vector<ObjectId> sourceIds = pageObjectIds(sourceDoc, *sourcePage);
    if (sourceIds.empty()) {
        m_lastError = "WrongMarkSet: first page of the source document has no objects";
        return false;
    }

    int copied = 0;
    if (!copyPageObjects(sourceDoc, sourceIds, *m_targetDocument, *target, copied, m_lastError)) {
        return false;
    }

    m_targetDocument->setModified(true);
    m_lastCopiedObjectCount = copied;
    return true;
}
