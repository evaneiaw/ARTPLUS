#include "cut_mark.h"

#include <QJsonArray>
#include <QJsonValue>

#include <algorithm>

namespace ArtPlus {

namespace {

// Conversão mm <-> pontos de documento (72 dpi), o mesmo fator de
// MarksUtils::mmToPoints. Repetido aqui como helper local para não obrigar
// quem linka cut_mark.cpp a arrastar marks.cpp (MarksEngine) junto.
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
    if (name == "MediaBox") { out = PageBoxType::MediaBox; return true; }
    if (name == "CropBox")  { out = PageBoxType::CropBox;  return true; }
    if (name == "BleedBox") { out = PageBoxType::BleedBox; return true; }
    if (name == "TrimBox")  { out = PageBoxType::TrimBox;  return true; }
    if (name == "ArtBox")   { out = PageBoxType::ArtBox;   return true; }
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

std::shared_ptr<PathObject> makeSegment(const QLineF& line, const CutMarkParams& params, LayerId layerId) {
    auto path = std::make_shared<PathObject>();
    path->setLayerId(layerId);
    path->addMove(line.p1());
    path->addLine(line.p2());
    FillStroke fs;
    fs.stroke = params.color;
    fs.strokeWidth = (float)params.strokeWidthPt;
    fs.capStyle = Qt::FlatCap;
    fs.joinStyle = Qt::MiterJoin;
    path->fillStroke() = fs;
    return path;
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

// ================================================================= CutMark
CutMark::CutMark() = default;

CutMark::CutMark(const CutMarkParams& params) : m_params(params) {}

QString CutMark::displayName() const {
    return QStringLiteral("Cut Mark %1").arg(m_displayIndex);
}

QRectF CutMark::resolveReferenceBox(const Document& doc, PageId page) const {
    return resolveReferenceBoxWith(doc, page, m_manager, 0);
}

QRectF CutMark::resolveReferenceBoxWith(const Document& doc, PageId page,
                                        const CutMarkManager* manager, int depth) const {
    if (depth > 8) return QRectF(); // guarda de ciclo (A → B → A)

    switch (m_params.referenceKind) {
        case CutMarkParams::ReferenceKind::PageBox: {
            auto pg = doc.page(page);
            if (!pg) return QRectF(); // E6-like: sem página não há caixa
            return pageBoxRect(pg->boxes(), m_params.referenceBox);
        }
        case CutMarkParams::ReferenceKind::Mark: {
            if (m_params.referenceMarkId == 0) return QRectF(); // nenhuma referência
            if (!manager) return QRectF(); // sem catálogo não há Cut Mark a resolver
            const CutMark* ref = manager->find(m_params.referenceMarkId);
            if (!ref) return QRectF();       // E5: referência inexistente no manager
            if (m_groupId != 0 && ref->objectId() == m_groupId) return QRectF(); // auto-referência
            const PageId refPage = manager->pageOf(*ref);
            if (refPage == 0) return QRectF(); // E5: grupo órfão, fora do documento
            // R4: retângulo da Cut Mark referenciada, calculado a partir da própria
            // geometria dela — não usa GroupObject::boundingBox() (vazio no core).
            return ref->markBoundsImpl(doc, refPage, depth + 1);
        }
    }
    return QRectF();
}

QRectF CutMark::markBounds(const Document& doc, PageId page) const {
    return markBoundsImpl(doc, page, 0);
}

QRectF CutMark::markBoundsImpl(const Document& doc, PageId page, int depth) const {
    const QRectF ref = resolveReferenceBoxWith(doc, page, m_manager, depth);
    if (ref.isEmpty()) return QRectF();

    const QVector<QLineF> segments = buildGeometry(ref);
    if (segments.isEmpty()) return QRectF();

    bool first = true;
    QRectF bounds;
    for (const QLineF& line : segments) {
        const QRectF r = QRectF(line.p1(), line.p2()).normalized();
        bounds = first ? r : bounds.united(r);
        first = false;
    }
    return bounds;
}

QVector<QLineF> CutMark::buildGeometry(const QRectF& referenceBoxPt) const {
    QVector<QLineF> segments;
    if (referenceBoxPt.isEmpty()) return segments;

    const double off = mmToPoints(m_params.offsetMm);
    const double len = mmToPoints(m_params.lengthMm);

    const double left = referenceBoxPt.left();
    const double right = referenceBoxPt.right();
    const double top = referenceBoxPt.top();
    const double bottom = referenceBoxPt.bottom();

    // (vértice, sinal externo em x, sinal externo em y) — D3
    struct Corner { double cx, cy, sx, sy; };
    const Corner corners[4] = {
        { left,  top,    -1.0, -1.0 },
        { right, top,     1.0, -1.0 },
        { left,  bottom, -1.0,  1.0 },
        { right, bottom,  1.0,  1.0 },
    };

    for (const Corner& c : corners) {
        // Segmento horizontal, prolongado para fora no eixo x.
        segments.append(QLineF(c.cx + c.sx * off, c.cy,
                               c.cx + c.sx * (off + len), c.cy));
        // Segmento vertical, prolongado para fora no eixo y.
        segments.append(QLineF(c.cx, c.cy + c.sy * off,
                               c.cx, c.cy + c.sy * (off + len)));
    }
    return segments;
}

ObjectId CutMark::applyTo(Document& doc, PageId page, int displayIndex) {
    m_displayIndex = displayIndex;
    auto pg = doc.page(page);
    if (!pg || pg->layers().empty()) return 0; // E9: sem página/camada
    const QRectF box = resolveReferenceBox(doc, page);
    if (box.isEmpty()) return 0; // E5/E6

    const QVector<QLineF> segments = buildGeometry(box);
    if (segments.size() != 8) return 0; // D3: 4 vértices × 2 segmentos

    const LayerId layerId = pg->layers().back(); // InsertNewObjectOnTop
    auto layer = doc.layer(layerId);
    if (!layer) return 0;

    auto group = std::make_shared<GroupObject>();
    group->setName(displayName());
    group->setLayerId(layerId);

    doc.addObject(group);
    layer->addObject(group->id());
    for (const QLineF& seg : segments) {
        auto path = makeSegment(seg, m_params, layerId);
        doc.addObject(path);
        group->addChild(path->id());
        layer->addObject(path->id());
    }

    m_groupId = group->id();
    return m_groupId;
}

bool CutMark::regenerate(Document& doc, PageId page) {
    if (m_groupId == 0) return false;
    auto group = doc.object(m_groupId);
    if (!group || group->type() != ObjectType::Group) return false;

    const QRectF box = resolveReferenceBox(doc, page);
    if (box.isEmpty()) return false; // E5/E6: preserva a geometria anterior
    const QVector<QLineF> segments = buildGeometry(box);
    if (segments.size() != 8) return false;

    // R8: apaga o conteúdo anterior e recria (substitui, não acumula).
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
    for (const QLineF& seg : segments) {
        auto path = makeSegment(seg, m_params, layerId);
        doc.addObject(path);
        group->addChild(path->id());
        if (layer) layer->addObject(path->id());
    }
    return true;
}

QJsonObject CutMark::toMetadata() const {
    QJsonObject o;
    o["groupId"] = (int)m_groupId;
    o["name"] = displayName();
    o["displayIndex"] = m_displayIndex;
    o["kind"] = QStringLiteral("DynamicObject_PDFPlusCutMark"); // R9 / 0x18013E3B0

    QJsonObject ref;
    if (m_params.referenceKind == CutMarkParams::ReferenceKind::PageBox) {
        ref["kind"] = QStringLiteral("PageBox");
        ref["box"] = boxTypeName(m_params.referenceBox);
    } else {
        ref["kind"] = QStringLiteral("Mark");
        ref["markId"] = (int)m_params.referenceMarkId;
    }
    o["reference"] = ref;

    o["offsetMm"] = m_params.offsetMm;
    o["offsetFormula"] = m_params.offsetFormula;
    o["orientation"] = m_params.orientation;
    o["repetition"] = m_params.repetition;
    QJsonArray lineTypes;
    for (int lt : m_params.lineTypes) lineTypes.append(lt);
    o["lineTypes"] = lineTypes;
    o["lengthMm"] = m_params.lengthMm;
    o["strokeWidthPt"] = m_params.strokeWidthPt;
    return o;
}

std::optional<CutMark> CutMark::fromMetadata(const QJsonObject& json, const Document& doc) {
    const ObjectId groupId = (ObjectId)json.value("groupId").toInt(0);
    if (groupId == 0) return std::nullopt;

    auto obj = doc.object(groupId);
    if (!obj || obj->type() != ObjectType::Group) return std::nullopt; // órfão descartado

    const QString kind = json.value("kind").toString();
    if (!kind.isEmpty() && kind != QStringLiteral("DynamicObject_PDFPlusCutMark")) {
        return std::nullopt;
    }

    CutMarkParams p;
    const QJsonObject ref = json.value("reference").toObject();
    if (ref.value("kind").toString() == QStringLiteral("Mark")) {
        p.referenceKind = CutMarkParams::ReferenceKind::Mark;
        p.referenceMarkId = (ObjectId)ref.value("markId").toInt(0);
    } else {
        p.referenceKind = CutMarkParams::ReferenceKind::PageBox;
        PageBoxType t = PageBoxType::TrimBox;
        if (boxTypeFromName(ref.value("box").toString(), t)) p.referenceBox = t;
    }

    p.offsetMm = json.value("offsetMm").toDouble(0.0);
    p.offsetFormula = json.value("offsetFormula").toString();
    p.orientation = json.value("orientation").toInt(1);
    p.repetition = json.value("repetition").toInt(2);
    if (json.value("lineTypes").isArray()) {
        p.lineTypes.clear();
        for (const auto& v : json.value("lineTypes").toArray()) p.lineTypes.append(v.toInt(0));
        if (p.lineTypes.isEmpty()) p.lineTypes.append(0);
    }
    p.lengthMm = json.value("lengthMm").toDouble(5.0);
    p.strokeWidthPt = json.value("strokeWidthPt").toDouble(0.25);

    CutMark mark(p);
    mark.m_groupId = groupId;
    mark.m_displayIndex = json.value("displayIndex").toInt(0);
    return mark;
}

// ========================================================== CutMarkManager
CutMark* CutMarkManager::find(ObjectId groupId) {
    for (auto& mark : m_marks) {
        if (mark.objectId() == groupId) return &mark;
    }
    return nullptr;
}

const CutMark* CutMarkManager::find(ObjectId groupId) const {
    for (const auto& mark : m_marks) {
        if (mark.objectId() == groupId) return &mark;
    }
    return nullptr;
}

CutMark* CutMarkManager::addCutMark(PageId page) {
    if (!m_document) return nullptr;
    pruneDetached();

    const int nextIndex = nextDisplayIndex();

    CutMark mark; // R2: defaults de fábrica (TrimBox, offsetMm 0)
    mark.setManagerContext(this); // R4: resolve `Attach to: Cut Mark N` durante applyTo
    const ObjectId groupId = mark.applyTo(*m_document, page, nextIndex);
    if (groupId == 0) return nullptr; // E5/E6/E9: nada criado

    if (m_undoStack) {
        // Criação: nada antes, a subárvore toda (grupo + 8 paths) depois.
        // O displayIndex viaja no comando para o redo reinserir "Cut Mark N".
        auto cmd = std::make_unique<CutMarkEditCommand>(this, groupId, nextIndex);
        cmd->captureAfter(*m_document, true, mark.params());
        m_undoStack->push(std::move(cmd));
    }

    m_marks.append(mark);
    return &m_marks.last();
}

bool CutMarkManager::setParams(ObjectId groupId, const CutMarkParams& params) {
    if (!m_document) return false;
    CutMark* mark = find(groupId);
    if (!mark) return false;
    if (mark->params() == params) return true; // nada a fazer, nenhuma ação de undo

    const PageId page = pageOf(*mark);
    if (page == 0) return false;

    const CutMarkParams before = mark->params();
    auto cmd = std::make_unique<CutMarkEditCommand>(this, groupId, mark->displayIndex());
    cmd->capture(*m_document, false, before);

    mark->setParams(params);
    if (!mark->regenerate(*m_document, page)) {
        mark->setParams(before); // caixa vazia: mantém estado anterior
        return false;
    }

    cmd->captureAfter(*m_document, false, params);
    if (m_undoStack) m_undoStack->push(std::move(cmd)); // R5: uma única ação
    return true;
}

void CutMarkManager::onMarkRestored(ObjectId groupId, const CutMarkParams& params, int displayIndex, bool present) {
    if (!present) {
        for (int i = m_marks.size() - 1; i >= 0; --i) {
            if (m_marks[i].objectId() == groupId) m_marks.remove(i);
        }
        return;
    }
    for (auto& mark : m_marks) {
        if (mark.objectId() == groupId) {
            mark.setParams(params);
            return;
        }
    }
    // Redo da criação: o undo removeu a entrada e agora o grupo voltou ao
    // documento. Reinsere a marca com os parâmetros originais (nunca defaults).
    CutMark restored(params);
    restored.m_groupId = groupId;
    restored.m_displayIndex = displayIndex > 0 ? displayIndex : nextDisplayIndex();
    restored.setManagerContext(this);
    m_marks.append(restored);
}

int CutMarkManager::nextDisplayIndex() const {
    int next = 0;
    for (const auto& mark : m_marks) next = std::max(next, mark.displayIndex());
    return next + 1;
}

PageId CutMarkManager::pageOf(const CutMark& mark) const {
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

void CutMarkManager::pruneDetached() {
    if (!m_document) {
        m_marks.clear();
        return;
    }
    QVector<CutMark> kept;
    kept.reserve(m_marks.size());
    for (const auto& mark : m_marks) {
        auto group = m_document->object(mark.objectId());
        if (group && group->type() == ObjectType::Group) kept.append(mark);
    }
    m_marks = kept;
}

bool CutMarkManager::loadFromMetadata() {
    m_marks.clear();
    if (!m_document) return false;

    const QJsonObject meta = m_document->metadata();
    if (!meta.contains(QStringLiteral("DocumentMarks"))) {
        return true; // documento sem a chave carrega com zero marcas
    }
    const QJsonValue value = meta.value(QStringLiteral("DocumentMarks"));
    if (!value.isObject()) return false;

    const QJsonObject dm = value.toObject();
    const QJsonArray marks = dm.value(QStringLiteral("cutMarks")).toArray();
    for (const auto& entry : marks) {
        auto mark = CutMark::fromMetadata(entry.toObject(), *m_document);
        if (mark) {
            m_marks.append(*mark);
            m_marks.last().setManagerContext(this); // R4 após reload
        }
    }
    return true;
}

bool CutMarkManager::saveToMetadata() const {
    if (!m_document) return false;
    QJsonObject meta = m_document->metadata();
    QJsonObject dm = meta.value("DocumentMarks").toObject();
    dm["cutMarks"] = toMetadata().value("cutMarks");
    dm["version"] = dm.value("version").toInt(1);
    meta["DocumentMarks"] = dm;
    m_document->setMetadata(meta);
    return true;
}

QJsonObject CutMarkManager::toMetadata() const {
    QJsonObject dm;
    dm["version"] = 1;
    QJsonArray marks;
    for (const auto& mark : m_marks) marks.append(mark.toMetadata());
    dm["cutMarks"] = marks;
    return dm;
}

// ===================================================== CutMarkEditCommand
CutMarkEditCommand::CutMarkEditCommand(CutMarkManager* manager, ObjectId groupId, int displayIndex)
    : m_manager(manager), m_groupId(groupId), m_displayIndex(displayIndex) {}

void CutMarkEditCommand::capture(Document& doc, bool includeRoot, const CutMarkParams& params) {
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

void CutMarkEditCommand::captureAfter(Document& doc, bool includeRoot, const CutMarkParams& params) {
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

void CutMarkEditCommand::undo(Document& doc) const {
    if (m_hasAfter) detachSide(doc, m_groupId, m_afterRoot, m_afterContent);
    if (m_hasBefore) attachSide(doc, m_groupId, m_beforeRoot, m_beforeContent);
    if (m_manager) {
        const bool present = m_hasBefore && doc.object(m_groupId) != nullptr;
        m_manager->onMarkRestored(m_groupId, m_beforeParams, m_displayIndex, present);
    }
}

void CutMarkEditCommand::redo(Document& doc) const {
    if (m_hasBefore) detachSide(doc, m_groupId, m_beforeRoot, m_beforeContent);
    if (m_hasAfter) attachSide(doc, m_groupId, m_afterRoot, m_afterContent);
    if (m_manager) {
        const bool present = doc.object(m_groupId) != nullptr;
        m_manager->onMarkRestored(m_groupId, m_afterParams, m_displayIndex, present);
    }
}

} // namespace ArtPlus
