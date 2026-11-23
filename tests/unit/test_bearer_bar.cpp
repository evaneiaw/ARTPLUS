// F-003 — Bearer Bar Mark (v1). Unit tests for ADR-002 D8.
// 
// Evidence backing each case:
//   R2    GHIDRA-DocumentMarks-0x18012FAA0 (PDF+ ctor defaults)
//   R4    GHIDRA-DocumentMarks-0x18001FDB0 (regenerateMarkImp: 1 Path per Location bit)
//   R6    GHIDRA-DocumentMarks-0x180132A70 (regenerateMarkImp geometry)
//   R5    GHIDRA-DocumentMarks-0x180131DC0 (UpdateSizeReference coherence)
//   D4    ADR-002 D4 (metadata.DocumentMarks.bearerBars in .artplus)
//   A1    ADR-001 A1 (PageBox=3 → TrimBox inference)
//
// Coordinate tolerance is the one declared in ADR-002 D3: ±0.03 pt (≈ 0.01 mm).
// Topology (number of bars, which sides) is compared exactly.

#include <QtTest/QtTest>
#include <QTemporaryDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QRectF>
#include <QVector>
#include <cmath>

#include "../../src/prepress/bearer_bar.h"
#include "../../src/prepress/cut_mark.h"
#include "../../src/document/document_model.h"
#include "../../src/document/document_serializer.h"
#include "../../src/document/undo.h"

using namespace ArtPlus;

namespace {

constexpr double kBearerBarTolPt = 0.03;
constexpr double kPtsPerMm = 72.0 / 25.4;

// A4 in points (210.00 × 297.00 mm), the page of CAP-20261119-02.
const QRectF kA4Pt(0.0, 0.0, 595.276, 841.89);

bool nearRect(const QRectF& a, const QRectF& b, double tol = kBearerBarTolPt) {
    return qAbs(a.left() - b.left()) <= tol &&
           qAbs(a.top() - b.top()) <= tol &&
           qAbs(a.right() - b.right()) <= tol &&
           qAbs(a.bottom() - b.bottom()) <= tol;
}

QString rectText(const QRectF& r) {
    return QStringLiteral("[%1,%2 - %3,%4]")
        .arg(r.left(), 0, 'f', 4).arg(r.top(), 0, 'f', 4)
        .arg(r.right(), 0, 'f', 4).arg(r.bottom(), 0, 'f', 4);
}

// Expected geometry for buildGeometry, written from ADR-002 D3 (independent of
// BearerBar::buildGeometry): one filled rectangle per enabled side bit.
QVector<QRectF> expectedGeometry(const QRectF& box, double widthMm,
                                 double extendMm, double offsetMm, int locationMask) {
    const double w = widthMm * kPtsPerMm;
    const double e = extendMm * kPtsPerMm;
    const double o = offsetMm * kPtsPerMm;

    const double L = box.left();
    const double T = box.top();
    const double R = box.right();
    const double B = box.bottom();

    QVector<QRectF> out;
    // Side 0: Left (bit 0x1)
    if (locationMask & 0x1) {
        out.append(QRectF(L - o - w, T - e, w, (B - T) + 2.0 * e));
    }
    // Side 1: Right (bit 0x2)
    if (locationMask & 0x2) {
        out.append(QRectF(R + o, T - e, w, (B - T) + 2.0 * e));
    }
    // Side 2: Top (bit 0x4)
    if (locationMask & 0x4) {
        out.append(QRectF(L - e, T - o - w, (R - L) + 2.0 * e, w));
    }
    // Side 3: Base / Bottom (bit 0x8)
    if (locationMask & 0x8) {
        out.append(QRectF(L - e, B + o, (R - L) + 2.0 * e, w));
    }

    return out;
}

// Geometry actually stored in the document: the rectangles under the mark group.
// Each rectangle is a PathObject with 4 elements (Move + 3 Line).
QVector<QRectF> documentGeometry(const Document& doc, ObjectId groupId) {
    QVector<QRectF> rects;
    auto group = doc.object(groupId);
    if (!group) return rects;
    for (ObjectId childId : group->children()) {
        auto path = std::dynamic_pointer_cast<PathObject>(doc.object(childId));
        if (!path) continue;
        // Path must have Move + 3 Line for a rectangle
        if (path->elements().size() < 4) continue;
        if (path->elements()[0].type != PathObject::PathElement::Type::Move) continue;
        if (path->elements()[1].type != PathObject::PathElement::Type::Line) continue;
        if (path->elements()[2].type != PathObject::PathElement::Type::Line) continue;
        if (path->elements()[3].type != PathObject::PathElement::Type::Line) continue;
        
        // Reconstruct rectangle from 4 corners
        QPointF p0 = path->elements()[0].p1;
        QPointF p1 = path->elements()[1].p1;
        QPointF p2 = path->elements()[2].p1;
        QPointF p3 = path->elements()[3].p1;
        
        // Rectangle: p0=top-left, p1=top-right, p2=bottom-right, p3=bottom-left
        rects.append(QRectF(QPointF(p0.x(), p0.y()), QPointF(p2.x(), p2.y())));
    }
    return rects;
}

// Page + layer fixture: the mark needs a page with at least one layer.
PageId setupPage(Document& doc, const QRectF& media, const QRectF& trim) {
    auto layer = std::make_shared<Layer>(QStringLiteral("Page 1"));
    doc.addLayer(layer);

    auto page = std::make_shared<Page>();
    page->boxes().mediaBox = media;
    page->boxes().cropBox = media;
    page->boxes().bleedBox = media;
    page->boxes().trimBox = trim;
    page->boxes().artBox = trim;
    page->addLayer(layer->id());
    doc.addPage(page);
    return page->id();
}

} // namespace

class TestBearerBar : public QObject {
    Q_OBJECT

private slots:
    // D8 case 1 — R2: factory defaults.
    void testDefaults_R2() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        UndoStack history;
        BearerBarManager mgr(doc);
        mgr.setUndoStack(&history);

        BearerBar* mark = mgr.addBearerBar(pageId);
        QVERIFY2(mark != nullptr, "addBearerBar must create a mark on a valid page");

        const BearerBarParams& p = mark->params();
        QCOMPARE(p.referenceBox, PageBoxType::TrimBox);   // A1: PageBox=3 → TrimBox
        QCOMPARE(p.widthMm, 5.0);                          // R2: 5 mm from legacy ctor
        QCOMPARE(p.extendMm, 0.0);
        QCOMPARE(p.offsetMm, 0.0);
        QCOMPARE(p.locationMask, 0x3);                     // R4: left+right
        QCOMPARE(p.sizeReference, 0);
        QCOMPARE(p.direction, 1);

        QCOMPARE(mark->displayName(), QStringLiteral("Bearer Bar Mark 1"));
        QCOMPARE(mark->displayIndex(), 1);

        // One content object (group) whose name is the display name.
        auto group = doc.object(mark->objectId());
        QVERIFY(group != nullptr);
        QCOMPARE(group->type(), ObjectType::Group);
        QCOMPARE(group->name(), QStringLiteral("Bearer Bar Mark 1"));
        QVERIFY(mark->objectId() != 0);

        // Creation is a single undoable action.
        QVERIFY(history.canUndo());
    }

    // D8 case 2 — R4/R6: page 210×297 mm, locationMask=3, extend=offset=0.
    // Expected: exactly 2 bars: [-5,0]×[0,H] mm and [W,W+5]×[0,H] mm (±0.03 pt).
    void testGeometryTopology_R4_R6() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        BearerBarManager mgr(doc);
        BearerBar* mark = mgr.addBearerBar(pageId);
        QVERIFY(mark != nullptr);

        auto group = doc.object(mark->objectId());
        QVERIFY(group != nullptr);
        QCOMPARE(group->children().size(), (size_t)2); // 2 bars for locationMask=0x3

        // Every child is a PathObject with 5 elements (Move + 3 Line + Close).
        // F-003 R6 passo 4 (FillPaint => path fechado): retângulo preenchido exige contorno fechado.
        for (ObjectId childId : group->children()) {
            auto path = std::dynamic_pointer_cast<PathObject>(doc.object(childId));
            QVERIFY2(path != nullptr, "each bearer bar child must be a PathObject");
            QCOMPARE(path->elements().size(), 5);
            QCOMPARE(path->elements()[0].type, PathObject::PathElement::Type::Move);
            QCOMPARE(path->elements()[1].type, PathObject::PathElement::Type::Line);
            QCOMPARE(path->elements()[2].type, PathObject::PathElement::Type::Line);
            QCOMPARE(path->elements()[3].type, PathObject::PathElement::Type::Line);
            QCOMPARE(path->elements()[4].type, PathObject::PathElement::Type::Close);
        }

        const QVector<QRectF> actual = documentGeometry(doc, mark->objectId());
        QCOMPARE(actual.size(), 2);

        // Expected geometry: left bar and right bar.
        const QVector<QRectF> expected = expectedGeometry(kA4Pt, 5.0, 0.0, 0.0, 0x3);
        QCOMPARE(expected.size(), 2);

        for (int i = 0; i < expected.size(); ++i) {
            QVERIFY2(nearRect(actual[i], expected[i]),
                     qPrintable(QStringLiteral("bar %1: got %2, expected %3")
                                .arg(i).arg(rectText(actual[i]), rectText(expected[i]))));
        }

        // Verify no point is strictly inside the reference box (offset=0 keeps all bars outside).
        for (const QRectF& r : actual) {
            QVERIFY2(r.right() <= kA4Pt.left() + kBearerBarTolPt || r.left() >= kA4Pt.right() - kBearerBarTolPt ||
                     r.bottom() <= kA4Pt.top() + kBearerBarTolPt || r.top() >= kA4Pt.bottom() - kBearerBarTolPt,
                     "bar must be outside the reference box");
        }
    }

    // D8 case 3 — R4: bitmask. 0xC ⇒ 2 horizontal (top/bottom); 0x5 ⇒ 2 (left/top);
    // 0x1 ⇒ 1 (left); 0x0 ⇒ 0 bars and no object created, no error (E6).
    void testBitmask_R4() {
        // 0xC: top and bottom
        {
            Document doc;
            const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
            BearerBarManager mgr(doc);
            BearerBar* mark = mgr.addBearerBar(pageId);
            QVERIFY(mark != nullptr);

            BearerBarParams p = mark->params();
            p.locationMask = 0xC;
            QVERIFY(mgr.setParams(mark->objectId(), p));

            const QVector<QRectF> actual = documentGeometry(doc, mark->objectId());
            QCOMPARE(actual.size(), 2);

            const QVector<QRectF> expected = expectedGeometry(kA4Pt, 5.0, 0.0, 0.0, 0xC);
            QCOMPARE(expected.size(), 2);
            for (int i = 0; i < expected.size(); ++i) {
                QVERIFY2(nearRect(actual[i], expected[i]),
                         qPrintable(QStringLiteral("0xC bar %1: got %2, expected %3")
                                    .arg(i).arg(rectText(actual[i]), rectText(expected[i]))));
            }
        }

        // 0x5: left and top
        {
            Document doc;
            const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
            BearerBarManager mgr(doc);
            BearerBar* mark = mgr.addBearerBar(pageId);
            QVERIFY(mark != nullptr);

            BearerBarParams p = mark->params();
            p.locationMask = 0x5;
            QVERIFY(mgr.setParams(mark->objectId(), p));

            const QVector<QRectF> actual = documentGeometry(doc, mark->objectId());
            QCOMPARE(actual.size(), 2);

            const QVector<QRectF> expected = expectedGeometry(kA4Pt, 5.0, 0.0, 0.0, 0x5);
            QCOMPARE(expected.size(), 2);
            for (int i = 0; i < expected.size(); ++i) {
                QVERIFY2(nearRect(actual[i], expected[i]),
                         qPrintable(QStringLiteral("0x5 bar %1: got %2, expected %3")
                                    .arg(i).arg(rectText(actual[i]), rectText(expected[i]))));
            }
        }

        // 0x1: left only
        {
            Document doc;
            const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
            BearerBarManager mgr(doc);
            BearerBar* mark = mgr.addBearerBar(pageId);
            QVERIFY(mark != nullptr);

            BearerBarParams p = mark->params();
            p.locationMask = 0x1;
            QVERIFY(mgr.setParams(mark->objectId(), p));

            const QVector<QRectF> actual = documentGeometry(doc, mark->objectId());
            QCOMPARE(actual.size(), 1);

            const QVector<QRectF> expected = expectedGeometry(kA4Pt, 5.0, 0.0, 0.0, 0x1);
            QCOMPARE(expected.size(), 1);
            QVERIFY2(nearRect(actual[0], expected[0]),
                     qPrintable(QStringLiteral("0x1 bar: got %2, expected %3")
                                .arg(rectText(actual[0]), rectText(expected[0]))));
        }

        // 0x0: no bars, no object created, no error (E6)
        {
            Document doc;
            const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
            BearerBarManager mgr(doc);

            BearerBar* mark = mgr.addBearerBar(pageId);
            QVERIFY(mark != nullptr); // creation succeeds with defaults

            BearerBarParams p = mark->params();
            p.locationMask = 0x0;
            QVERIFY(mgr.setParams(mark->objectId(), p));

            const QVector<QRectF> actual = documentGeometry(doc, mark->objectId());
            QCOMPARE(actual.size(), 0);
        }
    }

    // D8 case 4 — R6: extend. extendMm=2 ⇒ each bar grows 2 mm on each end in the
    // side axis (±0.03 pt); perpendicular dimension unchanged.
    void testExtend_R6() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        BearerBarManager mgr(doc);
        BearerBar* mark = mgr.addBearerBar(pageId);
        QVERIFY(mark != nullptr);

        const QVector<QRectF> before = documentGeometry(doc, mark->objectId());
        QCOMPARE(before.size(), 2);

        BearerBarParams p = mark->params();
        p.extendMm = 2.0;
        QVERIFY(mgr.setParams(mark->objectId(), p));

        const QVector<QRectF> after = documentGeometry(doc, mark->objectId());
        QCOMPARE(after.size(), 2);

        const QVector<QRectF> expected = expectedGeometry(kA4Pt, 5.0, 2.0, 0.0, 0x3);
        QCOMPARE(expected.size(), 2);

        for (int i = 0; i < expected.size(); ++i) {
            QVERIFY2(nearRect(after[i], expected[i]),
                     qPrintable(QStringLiteral("extend 2mm, bar %1: got %2, expected %3")
                                .arg(i).arg(rectText(after[i]), rectText(expected[i]))));
        }

        // Verify perpendicular dimension unchanged (width still 5 mm).
        const double tol = kBearerBarTolPt;
        QVERIFY2(qAbs((after[0].right() - after[0].left()) - (before[0].right() - before[0].left())) <= tol,
                 "perpendicular dimension (width) must not change with extend");
    }

    // D8 case 5 — R7: regeneration replaces, never accumulates.
    void testRegeneration_R7() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        BearerBarManager mgr(doc);
        BearerBar* mark = mgr.addBearerBar(pageId);
        QVERIFY(mark != nullptr);
        const ObjectId gid = mark->objectId();

        auto group = doc.object(gid);
        QVERIFY(group != nullptr);
        const size_t objectsAfterCreate = doc.objectIds().size();
        const size_t childrenAfterCreate = group->children().size();
        const std::vector<ObjectId> firstIds = group->children();

        // Change offset to trigger regeneration.
        BearerBarParams params = mark->params();
        params.offsetMm = 1.0;
        QVERIFY(mgr.setParams(gid, params));

        group = doc.object(gid);
        QVERIFY(group != nullptr);
        QCOMPARE(doc.objectIds().size(), objectsAfterCreate);   // no accumulation
        QCOMPARE(group->children().size(), childrenAfterCreate);
        QVERIFY(group->children() != firstIds);               // content replaced

        const std::vector<ObjectId> secondIds = group->children();
        const QVector<QRectF> expected1 = expectedGeometry(kA4Pt, 5.0, 0.0, 1.0, 0x3);
        const QVector<QRectF> actual1 = documentGeometry(doc, gid);
        QCOMPARE(actual1.size(), 2);
        for (int i = 0; i < expected1.size(); ++i) {
            QVERIFY2(nearRect(actual1[i], expected1[i]),
                     qPrintable(QStringLiteral("offset 1 mm, bar %1: got %2, expected %3")
                                .arg(i).arg(rectText(actual1[i]), rectText(expected1[i]))));
        }

        // Change offset again.
        params.offsetMm = 2.0;
        QVERIFY(mgr.setParams(gid, params));

        group = doc.object(gid);
        QVERIFY(group != nullptr);
        QCOMPARE(doc.objectIds().size(), objectsAfterCreate);
        QCOMPARE(group->children().size(), childrenAfterCreate);
        QVERIFY(group->children() != secondIds);

        const QVector<QRectF> expected2 = expectedGeometry(kA4Pt, 5.0, 0.0, 2.0, 0x3);
        const QVector<QRectF> actual2 = documentGeometry(doc, gid);
        QCOMPARE(actual2.size(), 2);
        for (int i = 0; i < expected2.size(); ++i) {
            QVERIFY2(nearRect(actual2[i], expected2[i]),
                     qPrintable(QStringLiteral("offset 2 mm, bar %1: got %2, expected %3")
                                .arg(i).arg(rectText(actual2[i]), rectText(expected2[i]))));
        }
    }

    // D8 case 6 — A1: reference box. Trim ≠ Media ⇒ bars use Trim; switch to
    // MediaBox ⇒ bars move to Media Box edges.
    void testReferenceBox_A1() {
        // Media A4; Trim inset by 10 mm on every side.
        const double inset = 10.0 * kPtsPerMm;
        const QRectF media = kA4Pt;
        const QRectF trim(media.left() + inset, media.top() + inset,
                          media.width() - 2.0 * inset, media.height() - 2.0 * inset);

        Document doc;
        const PageId pageId = setupPage(doc, media, trim);
        BearerBarManager mgr(doc);
        BearerBar* mark = mgr.addBearerBar(pageId);
        QVERIFY(mark != nullptr);
        const ObjectId gid = mark->objectId();

        // Default attach: TrimBox.
        QCOMPARE(mark->resolveReferenceBox(doc, pageId), trim);
        const QVector<QRectF> trimActual = documentGeometry(doc, gid);
        QCOMPARE(trimActual.size(), 2);

        const QVector<QRectF> trimExpected = expectedGeometry(trim, 5.0, 0.0, 0.0, 0x3);
        for (int i = 0; i < trimExpected.size(); ++i) {
            QVERIFY2(nearRect(trimActual[i], trimExpected[i]),
                     qPrintable(QStringLiteral("TrimBox, bar %1: got %2, expected %3")
                                .arg(i).arg(rectText(trimActual[i]), rectText(trimExpected[i]))));
        }

        // Switch to MediaBox: bars move to the Media Box corners.
        BearerBarParams p = mark->params();
        p.referenceBox = PageBoxType::MediaBox;
        QVERIFY(mgr.setParams(gid, p));
        QCOMPARE(mark->resolveReferenceBox(doc, pageId), media);

        const QVector<QRectF> mediaExpected = expectedGeometry(media, 5.0, 0.0, 0.0, 0x3);
        const QVector<QRectF> mediaActual = documentGeometry(doc, gid);
        QCOMPARE(mediaActual.size(), 2);
        for (int i = 0; i < mediaExpected.size(); ++i) {
            QVERIFY2(nearRect(mediaActual[i], mediaExpected[i]),
                     qPrintable(QStringLiteral("MediaBox, bar %1: got %2, expected %3")
                                .arg(i).arg(rectText(mediaActual[i]), rectText(mediaExpected[i]))));
        }

        // And it is not the Trim geometry any more.
        QVERIFY2(!nearRect(mediaActual[0], trimActual[0]),
                 "switching to MediaBox must move the geometry away from the TrimBox");
    }

    // D8 case 7 — D4: persistence. Save .artplus and reload ⇒ same params and
    // same bars; metadata.DocumentMarks.bearerBars present; document without
    // the key loads with zero bearer bars.
    void testPersistence_D4() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        BearerBarManager mgr(doc);

        BearerBar* mark = mgr.addBearerBar(pageId);
        QVERIFY(mark != nullptr);
        const ObjectId gid = mark->objectId();

        BearerBarParams p = mark->params();
        p.widthMm = 6.0;
        p.extendMm = 1.0;
        p.offsetMm = 2.0;
        p.locationMask = 0x5;
        QVERIFY(mgr.setParams(gid, p));
        QVERIFY(mgr.saveToMetadata());

        // JSON: metadata.DocumentMarks.bearerBars exists and carries the entry.
        const QJsonObject json = DocumentSerializer::toJson(doc);
        QVERIFY2(json.contains(QStringLiteral("metadata")), "root must contain metadata");
        const QJsonObject meta = json.value(QStringLiteral("metadata")).toObject();
        QVERIFY2(meta.contains(QStringLiteral("DocumentMarks")),
                 "metadata.DocumentMarks must be present");
        const QJsonObject dm = meta.value(QStringLiteral("DocumentMarks")).toObject();
        QVERIFY2(dm.contains(QStringLiteral("bearerBars")),
                 "metadata.DocumentMarks.bearerBars must be present");
        const QJsonArray bearerBars = dm.value(QStringLiteral("bearerBars")).toArray();
        QCOMPARE(bearerBars.size(), 1);
        const QJsonObject entry = bearerBars.at(0).toObject();
        QCOMPARE(entry.value(QStringLiteral("kind")).toString(),
                 QStringLiteral("DynamicObject_PDFPlusBearerBar"));
        QCOMPARE(entry.value(QStringLiteral("name")).toString(),
                 QStringLiteral("Bearer Bar Mark 1"));
        QVERIFY(qAbs(entry.value(QStringLiteral("widthMm")).toDouble() - 6.0) <= 1e-9);
        QVERIFY(qAbs(entry.value(QStringLiteral("extendMm")).toDouble() - 1.0) <= 1e-9);
        QVERIFY(qAbs(entry.value(QStringLiteral("offsetMm")).toDouble() - 2.0) <= 1e-9);
        QCOMPARE(entry.value(QStringLiteral("locationMask")).toInt(), 0x5);

        // Save + load the .artplus document.
        QTemporaryDir tmp;
        QVERIFY2(tmp.isValid(), "QTemporaryDir must be valid");
        const QString path = tmp.path() + QStringLiteral("/f003_bearer_bar.artplus");
        QVERIFY2(DocumentSerializer::save(doc, path), "saving the .artplus must succeed");

        Document loaded;
        QVERIFY2(DocumentSerializer::load(path, loaded), "loading the .artplus must succeed");

        BearerBarManager loadedMgr(loaded);
        QVERIFY(loadedMgr.loadFromMetadata());
        QCOMPARE(loadedMgr.bearerBars().size(), 1);

        const BearerBar& reloaded = loadedMgr.bearerBars().front();
        QCOMPARE(reloaded.params().referenceBox, PageBoxType::TrimBox);
        QCOMPARE(reloaded.params().widthMm, 6.0);
        QCOMPARE(reloaded.params().extendMm, 1.0);
        QCOMPARE(reloaded.params().offsetMm, 2.0);
        QCOMPARE(reloaded.params().locationMask, 0x5);
        QCOMPARE(reloaded.displayName(), QStringLiteral("Bearer Bar Mark 1"));

        // The group id still resolves and the geometry survived with 2 bars.
        auto group = loaded.object(reloaded.objectId());
        QVERIFY2(group != nullptr, "reloaded groupId must resolve in the document");
        QCOMPARE(group->children().size(), (size_t)2);

        const QVector<QRectF> expected = expectedGeometry(kA4Pt, 6.0, 1.0, 2.0, 0x5);
        const QVector<QRectF> actual = documentGeometry(loaded, reloaded.objectId());
        QCOMPARE(actual.size(), 2);
        for (int i = 0; i < expected.size(); ++i) {
            QVERIFY2(nearRect(actual[i], expected[i]),
                     qPrintable(QStringLiteral("reloaded, bar %1: got %2, expected %3")
                                .arg(i).arg(rectText(actual[i]), rectText(expected[i]))));
        }

        // A document without the key loads with zero bearer bars.
        Document plain;
        BearerBarManager plainMgr(plain);
        QVERIFY(plainMgr.loadFromMetadata());
        QCOMPARE(plainMgr.bearerBars().size(), 0);
    }

    // D8 case 7b — Single-writer regression. With 1 Cut Mark + 1 Bearer Bar:
    // save, reload and save again ⇒ both lists preserved (fails if saveToMetadata
    // of one manager erases the key of the other).
    void testSingleWriterRegression_D4() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);

        // Create a Cut Mark.
        CutMarkManager cutMgr(doc);
        CutMark* cutMark = cutMgr.addCutMark(pageId);
        QVERIFY(cutMark != nullptr);
        const ObjectId cutGid = cutMark->objectId();

        CutMarkParams cp = cutMark->params();
        cp.offsetMm = 1.5;
        QVERIFY(cutMgr.setParams(cutGid, cp));
        QVERIFY(cutMgr.saveToMetadata());

        // Create a Bearer Bar.
        BearerBarManager bearerMgr(doc);
        BearerBar* bearerBar = bearerMgr.addBearerBar(pageId);
        QVERIFY(bearerBar != nullptr);
        const ObjectId bearerGid = bearerBar->objectId();

        BearerBarParams bp = bearerBar->params();
        bp.widthMm = 4.0;
        QVERIFY(bearerMgr.setParams(bearerGid, bp));
        QVERIFY(bearerMgr.saveToMetadata());

        // Verify both are in the metadata.
        {
            const QJsonObject json = DocumentSerializer::toJson(doc);
            const QJsonObject dm = json.value(QStringLiteral("metadata"))
                                       .toObject()
                                       .value(QStringLiteral("DocumentMarks"))
                                       .toObject();
            QVERIFY2(dm.contains(QStringLiteral("cutMarks")), "cutMarks must be present");
            QVERIFY2(dm.contains(QStringLiteral("bearerBars")), "bearerBars must be present");
            QCOMPARE(dm.value(QStringLiteral("cutMarks")).toArray().size(), 1);
            QCOMPARE(dm.value(QStringLiteral("bearerBars")).toArray().size(), 1);
        }

        // Save, reload, and save again.
        QTemporaryDir tmp;
        QVERIFY(tmp.isValid());
        const QString path1 = tmp.path() + QStringLiteral("/f003_single_writer.artplus");
        QVERIFY(DocumentSerializer::save(doc, path1));

        Document loaded;
        QVERIFY(DocumentSerializer::load(path1, loaded));

        CutMarkManager loadedCutMgr(loaded);
        QVERIFY(loadedCutMgr.loadFromMetadata());
        QCOMPARE(loadedCutMgr.cutMarks().size(), 1);

        BearerBarManager loadedBearerMgr(loaded);
        QVERIFY(loadedBearerMgr.loadFromMetadata());
        QCOMPARE(loadedBearerMgr.bearerBars().size(), 1);

        // Save again.
        QVERIFY(loadedCutMgr.saveToMetadata());
        QVERIFY(loadedBearerMgr.saveToMetadata());

        const QString path2 = tmp.path() + QStringLiteral("/f003_single_writer2.artplus");
        QVERIFY(DocumentSerializer::save(loaded, path2));

        // Verify both lists are still present.
        {
            const QJsonObject json = DocumentSerializer::toJson(loaded);
            const QJsonObject dm = json.value(QStringLiteral("metadata"))
                                       .toObject()
                                       .value(QStringLiteral("DocumentMarks"))
                                       .toObject();
            QVERIFY2(dm.contains(QStringLiteral("cutMarks")), "cutMarks must still be present");
            QVERIFY2(dm.contains(QStringLiteral("bearerBars")), "bearerBars must still be present");
            QCOMPARE(dm.value(QStringLiteral("cutMarks")).toArray().size(), 1);
            QCOMPARE(dm.value(QStringLiteral("bearerBars")).toArray().size(), 1);
        }
    }

    // D8 case 8 — R5: SizeReference coherence.
    void testSizeReferenceCoherence_R5() {
        // (1..4, 0) == true
        for (int sr = 1; sr <= 4; ++sr) {
            QVERIFY2(BearerBarParams::sizeReferenceCoherent(sr, 0),
                     qPrintable(QStringLiteral("sizeReference %1, direction 0 must be coherent")
                                .arg(sr)));
        }

        // (1..4, 1) == false
        for (int sr = 1; sr <= 4; ++sr) {
            QVERIFY2(!BearerBarParams::sizeReferenceCoherent(sr, 1),
                     qPrintable(QStringLiteral("sizeReference %1, direction 1 must NOT be coherent")
                                .arg(sr)));
        }

        // (5..8, 1) == true
        for (int sr = 5; sr <= 8; ++sr) {
            QVERIFY2(BearerBarParams::sizeReferenceCoherent(sr, 1),
                     qPrintable(QStringLiteral("sizeReference %1, direction 1 must be coherent")
                                .arg(sr)));
        }

        // (5..8, 0) == false
        for (int sr = 5; sr <= 8; ++sr) {
            QVERIFY2(!BearerBarParams::sizeReferenceCoherent(sr, 0),
                     qPrintable(QStringLiteral("sizeReference %1, direction 0 must NOT be coherent")
                                .arg(sr)));
        }

        // (0, 0) == true
        QVERIFY2(BearerBarParams::sizeReferenceCoherent(0, 0),
                 "sizeReference 0, direction 0 must be coherent");

        // (0, 1) == true
        QVERIFY2(BearerBarParams::sizeReferenceCoherent(0, 1),
                 "sizeReference 0, direction 1 must be coherent");

        // (9, 1) == false (out of range)
        QVERIFY2(!BearerBarParams::sizeReferenceCoherent(9, 1),
                 "sizeReference 9, direction 1 must NOT be coherent (out of range)");
    }
};

QTEST_APPLESS_MAIN(TestBearerBar)
#include "test_bearer_bar.moc"