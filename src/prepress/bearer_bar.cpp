#include "bearer_bar.h"

#include <QJsonArray>
#include <QJsonValue>

#include <algorithm>
#include <cmath>

namespace ArtPlus {

namespace {

constexpr double kPointsPerMm = 72.0 / 25.4;

double mmToPoints(double mm) { return mm * kPointsPerMm; }

QString boxTypeName(PageBoxType t) {
    switch (t) {
        case PageBoxType::MediaBox: return QStringLiteral("MediaBox");
        case PageBoxType::CropBox:  return QStringLiteral("CropBox");
        case PageBoxType::BleedBox: return QStringLiteral("BleedBox");
        case PageBoxType::TrimBox:  return QStringLiteral("TrimBox");
        case PageBoxType::ArtBox:   return QStringLiteral("ArtBox");
    }
    return QStringLiteral("TrimBox");
}

bool boxTypeFromName(const QString& name, PageBoxType& out) {
    if (name == QStringLiteral("MediaBox")) { out = PageBoxType::MediaBox; return true; }
    if (name == QStringLiteral("CropBox"))  { out = PageBoxType::CropBox;  return true; }
    if (name == QStringLiteral("BleedBox")) { out = PageBoxType::BleedBox; return true; }
    if (name == QStringLiteral("TrimBox"))  { out = PageBoxType::TrimBox;  return true; }
    if (name == QStringLiteral("ArtBox"))   { out = PageBoxType::ArtBox;   return true; }
    return false;
}

QRectF pageBoxRect(const PageBoxes& boxes, PageBoxType type) {
    switch (type) {
        case PageBoxType::MediaBox: return boxes.mediaBox;
        case PageBoxType::CropBox:  return boxes.cropBox;
        case PageBoxType::BleedBox: return boxes.bleedBox;
        case PageBoxType::TrimBox:  return boxes.trimBox;
        case PageBoxType::ArtBox:   return boxes.artBox;
    }
    return boxes.trimBox;
}

std::shared_ptr<PathObject> makeBar(const QRectF& r, const BearerBarParams& params, LayerId layerId) {
    auto path = std::make_shared<PathObject>();
    path->setLayerId(layerId);
    path->addMove(r.topLeft());
    path->addLine(r.topRight());
    path->addLine(r.bottomRight());
    path->addLine(r.bottomLeft());
    path->closePath();       // D3: fechado e preenchido
    path->setClosed(true);  // D3: rectangle closed and filled

    FillStroke fs;
    fs.fill = params.color;
    fs.stroke = Color(); // None
    fs.strokeWidth = 0.0f;
    path->fillStroke() = fs;
    return path;
}

std::shared_ptr<GroupObject> makeGroup(const QString& name, LayerId layerId) {
    auto group = std::make_shared<GroupObject>();
    group->setName(name);
    group->setLayerId(layerId);
    return group;
}

void detachSide(Document& doc, ObjectId groupId,
                const std::shared_ptr<DocumentObject>& root,
                const std::vector<std::shared_ptr<DocumentObject>>& content) {
    auto group = root ? root : doc.object(groupId);
    for (const auto& obj : content) {
        if (!obj) continue;
        if (group) group->removeChild(obj->id());
        if (auto layer = doc.layer(obj->layerId())) layer->removeObject(obj->id());
        doc.removeObject(obj->id());
    }
    if (root) {
        if (auto layer = doc.layer(root->layerId())) layer->removeObject(root->id());
        doc.removeObject(root->id());
    }
}

void attachSide(Document& doc, ObjectId groupId,
                const std::shared_ptr<DocumentObject>& root,
                const std::vector<std::shared_ptr<DocumentObject>>& content) {
    if (root) {
        doc.addObject(root);
        if (auto layer = doc.layer(root->layerId())) layer->addObject(root->id());
    }
    auto group = root ? root : doc.object(groupId);
    for (const auto& obj : content) {
        if (!obj) continue;
        doc.addObject(obj);
        if (auto layer = doc.layer(obj->layerId())) layer->addObject(obj->id());
        if (group) group->addChild(obj->id());
    }
}

} // namespace

// ================================================================= BearerBarParams

bool BearerBarParams::sizeReferenceCoherent(int sizeReference, int direction) {
    if (sizeReference < 0 || sizeReference > 8) return false;
    if (sizeReference == 0) return true;
    if (sizeReference >= 1 && sizeReference <= 4) {
        return direction == 0;
    }
    if (sizeReference >= 5 && sizeReference <= 8) {
        return direction == 1;
    }
    return false;
}

bool BearerBarParams::operator==(const BearerBarParams& o) const {
    return referenceBox == o.referenceBox &&
           qFuzzyCompare(widthMm + 1.0, o.widthMm + 1.0) &&
           qFuzzyCompare(extendMm + 1.0, o.extendMm + 1.0) &&
           qFuzzyCompare(offsetMm + 1.0, o.offsetMm + 1.0) &&
           locationMask == o.locationMask &&
           sizeReference == o.sizeReference &&
           direction == o.direction &&
           color == o.color;
}

bool BearerBarParams::operator!=(const BearerBarParams& o) const {
    return !(*this == o);
}

// ====================================================== BearerBarEditCommand

// Helper implementations visible from BearerBarEditCommand and BearerBarManager.
void BearerBarManager::detachGroup(Document& doc, ObjectId groupId) {
    if (groupId == 0) return;
    auto group = doc.object(groupId);
    if (!group) return;
    const std::vector<ObjectId> children = group->children();
    for (ObjectId childId : children) {
        if (auto child = doc.object(childId)) {
            if (auto layer = doc.layer(child->layerId())) layer->removeObject(childId);
            doc.removeObject(childId);
        }
    }
    for (ObjectId childId : children) group->removeChild(childId);
    if (auto layer = doc.layer(group->layerId())) layer->removeObject(groupId);
    doc.removeObject(groupId);
}

void BearerBarManager::attachGroup(Document& doc, ObjectId groupId, LayerId layerId) {
    Q_UNUSED(doc);
    Q_UNUSED(groupId);
    Q_UNUSED(layerId);
    // Intentionally empty: creation redo uses applyTo() to recreate the group.
}

BearerBarEditCommand::BearerBarEditCommand(BearerBarManager* manager, ObjectId groupId, int displayIndex)
    : m_manager(manager), m_groupId(groupId), m_displayIndex(displayIndex) {}

void BearerBarEditCommand::capture(Document& doc, bool includeRoot, const BearerBarParams& params) {
    m_beforeParams = params;
    m_hasBefore = true;
    m_beforeRoot = includeRoot ? doc.object(m_groupId) : nullptr;
    m_beforeContent.clear();
    if (auto group = doc.object(m_groupId)) {
        for (ObjectId childId : group->children()) {
            if (auto child = doc.object(childId)) m_beforeContent.push_back(child);
        }
    }
}

void BearerBarEditCommand::captureAfter(Document& doc, bool includeRoot, const BearerBarParams& params) {
    m_afterParams = params;
    m_hasAfter = true;
    m_afterRoot = includeRoot ? doc.object(m_groupId) : nullptr;
    m_afterContent.clear();
    if (auto group = doc.object(m_groupId)) {
        for (ObjectId childId : group->children()) {
            if (auto child = doc.object(childId)) m_afterContent.push_back(child);
        }
    }
}

void BearerBarEditCommand::undo(Document& doc) const {
    if (m_hasAfter) detachSide(doc, m_groupId, m_afterRoot, m_afterContent);
    if (m_hasBefore) attachSide(doc, m_groupId, m_beforeRoot, m_beforeContent);
    if (m_manager) {
        const bool present = m_hasBefore && doc.object(m_groupId) != nullptr;
        m_manager->onMarkRestored(m_groupId, m_beforeParams, m_displayIndex, present);
    }
}

void BearerBarEditCommand::redo(Document& doc) const {
    if (m_hasBefore) detachSide(doc, m_groupId, m_beforeRoot, m_beforeContent);
    if (m_hasAfter) attachSide(doc, m_groupId, m_afterRoot, m_afterContent);
    if (m_manager) {
        const bool present = doc.object(m_groupId) != nullptr;
        m_manager->onMarkRestored(m_groupId, m_afterParams, m_displayIndex, present);
    }
}

// ================================================================= BearerBar

BearerBar::BearerBar() = default;

BearerBar::BearerBar(const BearerBarParams& params) : m_params(params) {}

const BearerBarParams& BearerBar::params() const { return m_params; }

void BearerBar::setParams(const BearerBarParams& params) { m_params = params; }

ObjectId BearerBar::objectId() const { return m_groupId; }

QString BearerBar::displayName() const {
    return QStringLiteral("Bearer Bar Mark %1").arg(m_displayIndex);
}

int BearerBar::displayIndex() const { return m_displayIndex; }

QRectF BearerBar::resolveReferenceBox(const Document& doc, PageId page) const {
    auto pg = doc.page(page);
    if (!pg) return QRectF();
    return pageBoxRect(pg->boxes(), m_params.referenceBox);
}

QVector<QRectF> BearerBar::buildGeometry(const QRectF& referenceBoxPt) const {
    // TODO(F-003): v1 aproxima a geometria PDF+ (transformacao do FormPaint,
    //              anchors, escala e guarda 0,01 mm) com faixas retangulares
    //              derivadas dos parametros; formula fechada fica para F-003a.
    // TODO(F-003): limites de extendMm/offsetMm nao testados (A7) — somente o
    //              limite widthMm <= 0 e guarda declarada; negativos passam direto.
    QVector<QRectF> rects;
    if (referenceBoxPt.isEmpty()) return rects;
    if (m_params.widthMm <= 0.0) return rects;

    const double w = mmToPoints(m_params.widthMm);
    const double e = mmToPoints(m_params.extendMm);
    const double o = mmToPoints(m_params.offsetMm);

    const double L = referenceBoxPt.left();
    const double T = referenceBoxPt.top();
    const double R = referenceBoxPt.right();
    const double B = referenceBoxPt.bottom();

    if (m_params.locationMask & 0x1) { // side 0 - left
        rects.append(QRectF(L - o - w, T - e, w, (B - T) + 2.0 * e));
    }
    if (m_params.locationMask & 0x2) { // side 1 - right
        rects.append(QRectF(R + o, T - e, w, (B - T) + 2.0 * e));
    }
    if (m_params.locationMask & 0x4) { // side 2 - top
        rects.append(QRectF(L - e, T - o - w, (R - L) + 2.0 * e, w));
    }
    if (m_params.locationMask & 0x8) { // side 3 - bottom
        rects.append(QRectF(L - e, B + o, (R - L) + 2.0 * e, w));
    }
    return rects;
}

ObjectId BearerBar::applyTo(Document& doc, PageId page, int displayIndex) {
    m_displayIndex = displayIndex;
    auto pg = doc.page(page);
    if (!pg || pg->layers().empty()) return 0;

    const QRectF box = resolveReferenceBox(doc, page);
    if (box.isEmpty()) return 0;

    const QVector<QRectF> rects = buildGeometry(box);
    if (rects.isEmpty() && (m_params.locationMask != 0)) return 0; // widthMm<=0 caught here

    const LayerId layerId = pg->layers().back(); // InsertNewObjectOnTop
    auto layer = doc.layer(layerId);
    if (!layer) return 0;

    auto group = std::make_shared<GroupObject>();
    group->setName(displayName());
    group->setLayerId(layerId);

    doc.addObject(group);
    layer->addObject(group->id());
    for (const QRectF& r : rects) {
        auto path = makeBar(r, m_params, layerId);
        doc.addObject(path);
        group->addChild(path->id());
        layer->addObject(path->id());
    }

    m_groupId = group->id();
    return m_groupId;
}

bool BearerBar::regenerate(Document& doc, PageId page) {
    if (m_groupId == 0) return false;
    auto group = doc.object(m_groupId);
    if (!group || group->type() != ObjectType::Group) return false;

    const QRectF box = resolveReferenceBox(doc, page);
    if (box.isEmpty()) return false; // preserve previous geometry

    // R7: apaga o conteudo anterior e recria (substitui, nao acumula).
    const std::vector<ObjectId> previous = group->children();
    for (ObjectId childId : previous) {
        if (auto child = doc.object(childId)) {
            if (auto layer = doc.layer(child->layerId())) layer->removeObject(childId);
            doc.removeObject(childId);
        }
        group->removeChild(childId);
    }

    const LayerId layerId = group->layerId();
    auto layer = doc.layer(layerId);
    const QVector<QRectF> rects = buildGeometry(box);
    for (const QRectF& r : rects) {
        auto path = makeBar(r, m_params, layerId);
        doc.addObject(path);
        group->addChild(path->id());
        if (layer) layer->addObject(path->id());
    }
    return true;
}

QJsonObject BearerBar::toMetadata() const {
    QJsonObject o;
    o["groupId"] = (int)m_groupId;
    o["name"] = displayName();
    o["displayIndex"] = m_displayIndex;
    o["kind"] = QStringLiteral("DynamicObject_PDFPlusBearerBar");

    QJsonObject ref;
    ref["kind"] = QStringLiteral("PageBox");
    ref["box"] = boxTypeName(m_params.referenceBox);
    o["reference"] = ref;

    o["widthMm"] = m_params.widthMm;
    o["extendMm"] = m_params.extendMm;
    o["offsetMm"] = m_params.offsetMm;
    o["locationMask"] = m_params.locationMask;
    o["sizeReference"] = m_params.sizeReference;
    o["direction"] = m_params.direction;
    return o;
}

std::optional<BearerBar> BearerBar::fromMetadata(const QJsonObject& json, const Document& doc) {
    const ObjectId groupId = (ObjectId)json.value("groupId").toInt(0);
    if (groupId == 0) return std::nullopt;

    auto obj = doc.object(groupId);
    if (!obj || obj->type() != ObjectType::Group) return std::nullopt;

    const QString kind = json.value("kind").toString();
    if (!kind.isEmpty() && kind != QStringLiteral("DynamicObject_PDFPlusBearerBar")) {
        return std::nullopt;
    }

    BearerBarParams p;
    const QJsonObject ref = json.value("reference").toObject();
    PageBoxType t = PageBoxType::TrimBox;
    if (boxTypeFromName(ref.value("box").toString(), t)) p.referenceBox = t;

    if (json.contains("widthMm")) p.widthMm = json.value("widthMm").toDouble(5.0);
    if (json.contains("extendMm")) p.extendMm = json.value("extendMm").toDouble(0.0);
    if (json.contains("offsetMm")) p.offsetMm = json.value("offsetMm").toDouble(0.0);
    if (json.contains("locationMask")) p.locationMask = json.value("locationMask").toInt(0x3);
    if (json.contains("sizeReference")) p.sizeReference = json.value("sizeReference").toInt(0);
    if (json.contains("direction")) p.direction = json.value("direction").toInt(1);

    BearerBar bar(p);
    bar.m_groupId = groupId;
    bar.m_displayIndex = json.value("displayIndex").toInt(0);
    return bar;
}

// ========================================================== BearerBarManager

BearerBarManager::BearerBarManager(Document& document) : m_document(&document) {}

void BearerBarManager::setUndoStack(UndoStack* stack) { m_undoStack = stack; }

BearerBar* BearerBarManager::addBearerBar(PageId pageId) {
    if (!m_document) return nullptr;
    pruneDetached();

    const int nextIndex = nextDisplayIndex();

    BearerBar mark; // R2: defaults of factory (TrimBox, widthMm 5)
    const ObjectId groupId = mark.applyTo(*m_document, pageId, nextIndex);
    if (groupId == 0) return nullptr; // E5/E6/E9: nothing created

    if (m_undoStack) {
        // Creation: nothing before, the whole subtree (group + paths) after.
        auto cmd = std::make_unique<BearerBarEditCommand>(this, groupId, nextIndex);
        cmd->captureAfter(*m_document, true, mark.params());
        m_undoStack->push(std::move(cmd));
    }

    m_bars.append(mark);
    return &m_bars.last();
}

BearerBar* BearerBarManager::find(ObjectId groupId) {
    for (auto& bar : m_bars) {
        if (bar.objectId() == groupId) return &bar;
    }
    return nullptr;
}

const QVector<BearerBar>& BearerBarManager::bearerBars() const { return m_bars; }

bool BearerBarManager::setParams(ObjectId groupId, const BearerBarParams& params) {
    if (!m_document) return false;
    BearerBar* mark = find(groupId);
    if (!mark) return false;
    if (mark->params() == params) return true; // nothing to do, no undo action

    const PageId page = pageOf(*mark);
    if (page == 0) return false;

    const BearerBarParams before = mark->params();
    auto cmd = std::make_unique<BearerBarEditCommand>(this, groupId, mark->displayIndex());
    cmd->capture(*m_document, false, before);

    mark->setParams(params);
    if (!mark->regenerate(*m_document, page)) {
        mark->setParams(before); // empty box: keep previous state
        return false;
    }

    cmd->captureAfter(*m_document, false, params);
    if (m_undoStack) m_undoStack->push(std::move(cmd)); // R5: uma única ação
    saveToMetadata();
    return true;
}

bool BearerBarManager::loadFromMetadata() {
    m_bars.clear();
    if (!m_document) return false;

    const QJsonObject meta = m_document->metadata();
    if (!meta.contains(QStringLiteral("DocumentMarks"))) {
        return true; // documento sem a chave carrega com zero marcas
    }
    const QJsonValue value = meta.value(QStringLiteral("DocumentMarks"));
    if (!value.isObject()) return false;

    const QJsonObject dm = value.toObject();
    const QJsonArray bars = dm.value(QStringLiteral("bearerBars")).toArray();
    for (const auto& entry : bars) {
        auto mark = BearerBar::fromMetadata(entry.toObject(), *m_document);
        if (mark) m_bars.append(*mark);
    }
    return true;
}

bool BearerBarManager::saveToMetadata() const {
    if (!m_document) return false;
    QJsonObject meta = m_document->metadata();
    QJsonObject dm = meta.value("DocumentMarks").toObject();
    dm["bearerBars"] = toMetadata().value("bearerBars");
    dm["version"] = dm.value("version").toInt(1);
    meta["DocumentMarks"] = dm;
    m_document->setMetadata(meta);
    return true;
}

QJsonObject BearerBarManager::toMetadata() const {
    QJsonObject dm;
    dm["version"] = 1;
    QJsonArray bars;
    for (const auto& bar : m_bars) bars.append(bar.toMetadata());
    dm["bearerBars"] = bars;
    return dm;
}

void BearerBarManager::onMarkRestored(ObjectId groupId, const BearerBarParams& params, int displayIndex, bool present) {
    if (!present) {
        for (int i = m_bars.size() - 1; i >= 0; --i) {
            if (m_bars[i].objectId() == groupId) m_bars.remove(i);
        }
        return;
    }
    for (auto& bar : m_bars) {
        if (bar.objectId() == groupId) {
            bar.setParams(params);
            return;
        }
    }
    // Redo da criacao: o undo removeu a entrada e agora o grupo voltou ao
    // documento. Reinsere a marca com os parametros originais.
    BearerBar restored(params);
    restored.m_groupId = groupId;
    restored.m_displayIndex = displayIndex > 0 ? displayIndex : nextDisplayIndex();
    m_bars.append(restored);
}

int BearerBarManager::nextDisplayIndex() const {
    int next = 0;
    for (const auto& bar : m_bars) next = std::max(next, bar.displayIndex());
    return next + 1;
}

PageId BearerBarManager::pageOf(const BearerBar& mark) const {
    if (!m_document) return 0;
    auto group = m_document->object(mark.objectId());
    if (!group) return 0;
    const LayerId layerId = group->layerId();
    for (PageId pid : m_document->pageOrder()) {
        auto page = m_document->page(pid);
        if (!page) continue;
        for (LayerId lid : page->layers()) {
            if (lid == layerId) return pid;
        }
    }
    return 0;
}

void BearerBarManager::pruneDetached() {
    if (!m_document) {
        m_bars.clear();
        return;
    }
    QVector<BearerBar> kept;
    kept.reserve(m_bars.size());
    for (const auto& bar : m_bars) {
        auto group = m_document->object(bar.objectId());
        if (group && group->type() == ObjectType::Group) kept.append(bar);
    }
    m_bars = kept;
}

} // namespace ArtPlus
