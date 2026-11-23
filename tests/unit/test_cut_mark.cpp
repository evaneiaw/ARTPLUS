// F-001 — Cut Mark (Trim Marks). Unit tests for the D7 matrix of
// docs/decisions/ADR-001-cut-mark.md, against src/prepress/cut_mark.h/.cpp.
//
// Evidence backing each case (endereços da referência v24.03.10017 / v240;
// os endereços de origem mapeados para a v24.03.10017:
// 0x1801344E0 (ctor defaults), 0x180134B00 (GetReferenceBox), 0x180136190 (regenerateMarkImp)):
//   R2/R9  GHIDRA-DocumentMarks-0x1801344E0 (ctor defaults), 0x18013E3B0 (mark type)
//   R3     GHIDRA-DocumentMarks-0x180134B00 (GetReferenceBox), GHIDRA-Document-0x1800FAE70
//   R4/E5  GHIDRA-DocumentMarks-0x180134B00 (reference-by-object branch / empty rect)
//   R5     GHIDRA-DocumentMarks-0x1800ADB10 (offset edit is one undo action)
//   R7     GHIDRA-DocumentMarks-0x180136190 (regenerateMarkImp inserts on top)
//   R8     GHIDRA-DocumentMarks-0x180136190, 0x1800ADCA0/0x1800AE100/0x1800AD540 (setters)
//   R10v1  ADR-001 D4 (`metadata.DocumentMarks` in `.artplus`, PDF+ keys deferred to F-001a)
//
// Regression cases for defect D1 of docs/audit/F-001-audit.md: undoing the
// creation removed the mark from CutMarkManager, but redoing it reattached the
// group to the document without reinserting the manager entry (so saveToMetadata
// wrote `cutMarks: []` and the next addCutMark duplicated "Cut Mark 1").
// Fix under test: CutMarkManager::onMarkRestored reinserts the mark on redo
// (src/prepress/cut_mark.cpp:384-404), preserving displayIndex and parameters.
//
// Coordinate tolerance is the one declared in ADR-001 D3: ±0,03 pt (≈ 0,01 mm).
// Segment counts are compared exactly.

#include <QtTest/QtTest>
#include <QTemporaryDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QLineF>
#include <QRectF>
#include <memory>

#include "../../src/prepress/cut_mark.h"
#include "../../src/document/document_model.h"
#include "../../src/document/document_serializer.h"
#include "../../src/document/undo.h"

using namespace ArtPlus;

namespace {

// ADR-001 D3: declared tolerance, and the mm -> pt factor of the document model.
constexpr double kCutMarkTolPt = 0.03;
constexpr double kPtsPerMm = 72.0 / 25.4;

// A4 in points (210,00 × 297,00 mm), the page of CAP-20261119-01.
const QRectF kA4Pt(0.0, 0.0, 595.276, 841.89);

bool nearPoint(const QPointF& a, const QPointF& b, double tol = kCutMarkTolPt) {
    return qAbs(a.x() - b.x()) <= tol && qAbs(a.y() - b.y()) <= tol;
}

bool nearLine(const QLineF& a, const QLineF& b, double tol = kCutMarkTolPt) {
    return nearPoint(a.p1(), b.p1(), tol) && nearPoint(a.p2(), b.p2(), tol);
}

QString lineText(const QLineF& l) {
    return QStringLiteral("(%1, %2) -> (%3, %4)")
        .arg(l.x1(), 0, 'f', 4).arg(l.y1(), 0, 'f', 4)
        .arg(l.x2(), 0, 'f', 4).arg(l.y2(), 0, 'f', 4);
}

QString linesText(const QVector<QLineF>& lines) {
    QStringList parts;
    for (const QLineF& l : lines) parts << lineText(l);
    return parts.join(QStringLiteral(" | "));
}

// Expected geometry written from ADR-001 D3 (independent of CutMark::buildGeometry):
// 4 corners × 2 segments; h: (cx+sx*off, cy) -> (cx+sx*(off+len), cy);
// v: (cx, cy+sy*off) -> (cx, cy+sy*(off+len)).
QVector<QLineF> expectedGeometry(const QRectF& box, double offsetMm, double lengthMm = 5.0) {
    const double off = offsetMm * kPtsPerMm;
    const double len = lengthMm * kPtsPerMm;

    struct Corner { double cx, cy, sx, sy; };
    const Corner corners[4] = {
        { box.left(),  box.top(),    -1.0, -1.0 },
        { box.right(), box.top(),     1.0, -1.0 },
        { box.left(),  box.bottom(), -1.0,  1.0 },
        { box.right(), box.bottom(),  1.0,  1.0 },
    };

    QVector<QLineF> out;
    for (const Corner& c : corners) {
        out.append(QLineF(c.cx + c.sx * off, c.cy,
                          c.cx + c.sx * (off + len), c.cy));
        out.append(QLineF(c.cx, c.cy + c.sy * off,
                          c.cx, c.cy + c.sy * (off + len)));
    }
    return out;
}

// Geometry actually stored in the document: the 8 PathObjects under the mark group.
QVector<QLineF> documentGeometry(const Document& doc, ObjectId groupId) {
    QVector<QLineF> lines;
    auto group = doc.object(groupId);
    if (!group) return lines;
    for (ObjectId childId : group->children()) {
        auto path = std::dynamic_pointer_cast<PathObject>(doc.object(childId));
        if (!path) continue;
        if (path->elements().size() != 2) continue;
        if (path->elements()[0].type != PathObject::PathElement::Type::Move) continue;
        if (path->elements()[1].type != PathObject::PathElement::Type::Line) continue;
        lines.append(QLineF(path->elements()[0].p1, path->elements()[1].p1));
    }
    return lines;
}

// Page + layer fixture: the mark needs a page with at least one layer (E9).
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

class TestCutMark : public QObject {
    Q_OBJECT

private slots:
    // D7 case 1 — R2/R9: factory defaults and display name.
    void testDefaults_R2_R9() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        UndoStack history;
        CutMarkManager mgr(doc);
        mgr.setUndoStack(&history);

        CutMark* mark = mgr.addCutMark(pageId);
        QVERIFY2(mark != nullptr, "addCutMark must create a mark on a valid page");

        const CutMarkParams& p = mark->params();
        QCOMPARE(p.referenceKind, CutMarkParams::ReferenceKind::PageBox);
        QCOMPARE(p.referenceBox, PageBoxType::TrimBox);   // PDF+ PageBox = 3
        QCOMPARE(p.referenceMarkId, (ObjectId)0);
        QCOMPARE(p.offsetMm, 0.0);                        // "0,00 mm"
        QCOMPARE(p.orientation, 1);
        QCOMPARE(p.repetition, 2);
        QCOMPARE(p.lineTypes, QVector<int>{0});

        QCOMPARE(mark->displayName(), QStringLiteral("Cut Mark 1"));
        QCOMPARE(mark->displayIndex(), 1);

        // R9: one content object (group) whose name is the display name.
        auto group = doc.object(mark->objectId());
        QVERIFY(group != nullptr);
        QCOMPARE(group->type(), ObjectType::Group);
        QCOMPARE(group->name(), QStringLiteral("Cut Mark 1"));
        QVERIFY(mark->objectId() != 0);

        // Creation is a single undoable action (R1/R5 model side).
        QVERIFY(history.canUndo());
    }

    // D7 case 2 — R7: 4 corners × 2 segments, Move+Line, outward, nothing inside.
    void testGeometryTopology_R7() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt); // Trim = Media
        CutMarkManager mgr(doc);
        CutMark* mark = mgr.addCutMark(pageId);
        QVERIFY(mark != nullptr);

        auto group = doc.object(mark->objectId());
        QVERIFY(group != nullptr);
        QCOMPARE(group->children().size(), (size_t)8);

        // Every child is a PathObject with exactly Move + Line.
        for (ObjectId childId : group->children()) {
            auto path = std::dynamic_pointer_cast<PathObject>(doc.object(childId));
            QVERIFY2(path != nullptr, "each cut mark child must be a PathObject");
            QCOMPARE(path->elements().size(), 2);
            QCOMPARE(path->elements()[0].type, PathObject::PathElement::Type::Move);
            QCOMPARE(path->elements()[1].type, PathObject::PathElement::Type::Line);
        }

        const QVector<QLineF> lines = documentGeometry(doc, mark->objectId());
        QCOMPARE(lines.size(), 8);

        // Exact contract geometry with offset 0 and length 5 mm (±0,03 pt).
        const QVector<QLineF> expected = expectedGeometry(kA4Pt, 0.0);
        for (int i = 0; i < expected.size(); ++i) {
            QVERIFY2(nearLine(lines[i], expected[i]),
                     qPrintable(QStringLiteral("segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(lines[i]), lineText(expected[i]))));
        }

        // Two segments per vertex: each corner is the start point of exactly 2 segments.
        const QPointF corners[4] = { kA4Pt.topLeft(), kA4Pt.topRight(),
                                     kA4Pt.bottomLeft(), kA4Pt.bottomRight() };
        for (const QPointF& corner : corners) {
            int starts = 0;
            for (const QLineF& l : lines) if (nearPoint(l.p1(), corner)) ++starts;
            QVERIFY2(starts == 2,
                     qPrintable(QStringLiteral("corner (%1, %2) should start 2 segments, got %3")
                                    .arg(corner.x(), 0, 'f', 3).arg(corner.y(), 0, 'f', 3)
                                    .arg(starts)));
        }

        // No point strictly inside the reference box (offset 0 keeps all lines outside).
        for (const QLineF& l : lines) {
            const QPointF pts[2] = { l.p1(), l.p2() };
            for (const QPointF& pt : pts) {
                const bool inside = pt.x() > kA4Pt.left() + kCutMarkTolPt &&
                                    pt.x() < kA4Pt.right() - kCutMarkTolPt &&
                                    pt.y() > kA4Pt.top() + kCutMarkTolPt &&
                                    pt.y() < kA4Pt.bottom() - kCutMarkTolPt;
                QVERIFY2(!inside,
                         qPrintable(QStringLiteral("endpoint (%1, %2) of %3 is inside the box")
                                        .arg(pt.x(), 0, 'f', 4).arg(pt.y(), 0, 'f', 4)
                                        .arg(lineText(l))));
            }
        }
    }

    // D7 case 3 — R5: offset 3,00 mm moves outward; one edit == one undo, then redo, then undo.
    void testOffsetAndSingleUndo_R5() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        UndoStack history;
        CutMarkManager mgr(doc);
        mgr.setUndoStack(&history);

        CutMark* mark = mgr.addCutMark(pageId);
        QVERIFY(mark != nullptr);
        const ObjectId gid = mark->objectId();
        const QVector<QLineF> original = documentGeometry(doc, gid);
        QCOMPARE(original.size(), 8);

        CutMarkParams p = mark->params();
        p.offsetMm = 3.0;
        QVERIFY2(mgr.setParams(gid, p), "setParams(offset 3,00 mm) must regenerate");

        const QVector<QLineF> expected3 = expectedGeometry(kA4Pt, 3.0);
        const QVector<QLineF> after3 = documentGeometry(doc, gid);
        QCOMPARE(after3.size(), 8);
        for (int i = 0; i < expected3.size(); ++i) {
            QVERIFY2(nearLine(after3[i], expected3[i]),
                     qPrintable(QStringLiteral("offset 3 mm, segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(after3[i]), lineText(expected3[i]))));
        }

        // Direction check independent of the expectation table: the horizontal
        // segment of the top-left corner moved 3 mm to the left (outward, x < 0).
        QVERIFY2(after3[0].x1() < -1.0 &&
                 qAbs(after3[0].x1() - (-3.0 * kPtsPerMm)) <= kCutMarkTolPt,
                 qPrintable(QStringLiteral("TL horizontal start must be 3 mm outward: %1")
                                .arg(lineText(after3[0]))));

        // ONE undo reverts the whole edit: parameters and geometry, mark still present.
        QVERIFY(history.canUndo());
        history.undo(doc);
        QVERIFY(mgr.find(gid) != nullptr); // the creation action was not undone
        QCOMPARE(mgr.find(gid)->params().offsetMm, 0.0);
        const QVector<QLineF> afterUndo = documentGeometry(doc, gid);
        QCOMPARE(afterUndo.size(), 8);
        for (int i = 0; i < original.size(); ++i) {
            QVERIFY2(nearLine(afterUndo[i], original[i]),
                     qPrintable(QStringLiteral("undo, segment %1: got %2, original %3")
                                    .arg(i).arg(lineText(afterUndo[i]), lineText(original[i]))));
        }

        // Redo re-applies the 3 mm edit.
        QVERIFY(history.canRedo());
        history.redo(doc);
        QCOMPARE(mgr.find(gid)->params().offsetMm, 3.0);
        const QVector<QLineF> afterRedo = documentGeometry(doc, gid);
        for (int i = 0; i < expected3.size(); ++i) {
            QVERIFY2(nearLine(afterRedo[i], expected3[i]),
                     qPrintable(QStringLiteral("redo, segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(afterRedo[i]), lineText(expected3[i]))));
        }

        // Undo again returns to the original geometry.
        history.undo(doc);
        QCOMPARE(mgr.find(gid)->params().offsetMm, 0.0);
        const QVector<QLineF> afterUndo2 = documentGeometry(doc, gid);
        for (int i = 0; i < original.size(); ++i) {
            QVERIFY2(nearLine(afterUndo2[i], original[i]),
                     qPrintable(QStringLiteral("second undo, segment %1: got %2, original %3")
                                    .arg(i).arg(lineText(afterUndo2[i]), lineText(original[i]))));
        }
    }

    // D7 case 4 — R3: Trim != Media uses Trim; switching to MediaBox follows Media.
    void testReferenceBoxResolution_R3() {
        // Media A4; Trim inset by 10 mm on every side.
        const double inset = 10.0 * kPtsPerMm;
        const QRectF media = kA4Pt;
        const QRectF trim(media.left() + inset, media.top() + inset,
                          media.width() - 2.0 * inset, media.height() - 2.0 * inset);

        Document doc;
        const PageId pageId = setupPage(doc, media, trim);
        CutMarkManager mgr(doc);
        CutMark* mark = mgr.addCutMark(pageId);
        QVERIFY(mark != nullptr);
        const ObjectId gid = mark->objectId();

        // Default attach: TrimBox.
        QCOMPARE(mark->resolveReferenceBox(doc, pageId), trim);
        const QVector<QLineF> trimExpected = expectedGeometry(trim, 0.0);
        const QVector<QLineF> trimActual = documentGeometry(doc, gid);
        QCOMPARE(trimActual.size(), 8);
        for (int i = 0; i < trimExpected.size(); ++i) {
            QVERIFY2(nearLine(trimActual[i], trimExpected[i]),
                     qPrintable(QStringLiteral("TrimBox, segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(trimActual[i]), lineText(trimExpected[i]))));
        }

        // Switch to MediaBox: vertices move to the Media Box corners.
        CutMarkParams p = mark->params();
        p.referenceBox = PageBoxType::MediaBox;
        QVERIFY(mgr.setParams(gid, p));
        QCOMPARE(mark->resolveReferenceBox(doc, pageId), media);

        const QVector<QLineF> mediaExpected = expectedGeometry(media, 0.0);
        const QVector<QLineF> mediaActual = documentGeometry(doc, gid);
        QCOMPARE(mediaActual.size(), 8);
        for (int i = 0; i < mediaExpected.size(); ++i) {
            QVERIFY2(nearLine(mediaActual[i], mediaExpected[i]),
                     qPrintable(QStringLiteral("MediaBox, segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(mediaActual[i]), lineText(mediaExpected[i]))));
        }

        // And it is not the Trim geometry any more.
        QVERIFY2(!nearLine(mediaActual[0], trimActual[0]),
                 "switching to MediaBox must move the geometry away from the TrimBox");
    }

    // D7 case 5 — R8: regeneration replaces, never accumulates.
    void testRegenerationReplaces_R8() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        CutMarkManager mgr(doc);
        CutMark* mark = mgr.addCutMark(pageId);
        QVERIFY(mark != nullptr);
        const ObjectId gid = mark->objectId();

        auto group = doc.object(gid);
        QVERIFY(group != nullptr);
        const size_t objectsAfterCreate = doc.objectIds().size();
        const size_t childrenAfterCreate = group->children().size();
        const std::vector<ObjectId> firstIds = group->children();

        CutMarkParams p = mark->params();
        p.offsetMm = 1.0;
        QVERIFY(mgr.setParams(gid, p));
        group = doc.object(gid);
        QVERIFY(group != nullptr);
        QCOMPARE(doc.objectIds().size(), objectsAfterCreate);   // no accumulation
        QCOMPARE(group->children().size(), childrenAfterCreate);
        QCOMPARE(group->children().size(), (size_t)8);
        QVERIFY(group->children() != firstIds);               // content replaced

        const std::vector<ObjectId> secondIds = group->children();
        const QVector<QLineF> expected1 = expectedGeometry(kA4Pt, 1.0);
        const QVector<QLineF> actual1 = documentGeometry(doc, gid);
        QCOMPARE(actual1.size(), 8);
        for (int i = 0; i < expected1.size(); ++i) {
            QVERIFY2(nearLine(actual1[i], expected1[i]),
                     qPrintable(QStringLiteral("offset 1 mm, segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(actual1[i]), lineText(expected1[i]))));
        }

        p.offsetMm = 2.0;
        QVERIFY(mgr.setParams(gid, p));
        group = doc.object(gid);
        QVERIFY(group != nullptr);
        QCOMPARE(doc.objectIds().size(), objectsAfterCreate);
        QCOMPARE(group->children().size(), childrenAfterCreate);
        QVERIFY(group->children() != secondIds);

        const QVector<QLineF> expected2 = expectedGeometry(kA4Pt, 2.0);
        const QVector<QLineF> actual2 = documentGeometry(doc, gid);
        QCOMPARE(actual2.size(), 8);
        for (int i = 0; i < expected2.size(); ++i) {
            QVERIFY2(nearLine(actual2[i], expected2[i]),
                     qPrintable(QStringLiteral("offset 2 mm, segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(actual2[i]), lineText(expected2[i]))));
        }
    }

    // D7 case 6 — R4/E5: reference by object.
    // R4 resolution lives in CutMark::resolveReferenceBox -> resolveReferenceBoxWith,
    // which needs the manager catalogue (`Attach to: Cut Mark N` lists marks of the
    // document). The reference is resolved from the referenced mark's own geometry
    // (CutMark::markBounds), not from GroupObject::boundingBox(), which is still a
    // stub in the document core.
    void testReferenceByMark_R4_E5() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        CutMarkManager mgr(doc);

        QVERIFY(mgr.addCutMark(pageId) != nullptr);                    // Cut Mark 1
        const ObjectId firstId = mgr.cutMarks().front().objectId();
        QVERIFY(mgr.addCutMark(pageId) != nullptr);                    // Cut Mark 2
        const ObjectId secondId = mgr.cutMarks().back().objectId();
        QVERIFY(firstId != 0);
        QVERIFY(secondId != 0);
        QCOMPARE(mgr.cutMarks().size(), 2);

        // E5: a reference id with no mark in the catalogue cannot resolve a box,
        // so the edit is refused and the parameters are not changed.
        CutMarkParams refParams = mgr.find(secondId)->params();
        refParams.referenceKind = CutMarkParams::ReferenceKind::Mark;
        refParams.referenceMarkId = 0x7FFFFFFF; // never allocated
        QVERIFY2(!mgr.setParams(secondId, refParams),
                 "E5: unknown reference mark must make the edit fail");
        QCOMPARE(mgr.find(secondId)->params().referenceKind,
                 CutMarkParams::ReferenceKind::PageBox);
        QVERIFY2(!mgr.find(secondId)->resolveReferenceBox(doc, pageId).isEmpty(),
                 "refused edit must keep the TrimBox geometry");

        // A standalone CutMark has no catalogue: Mark reference resolves empty (E5).
        CutMarkParams zeroRef = refParams;
        zeroRef.referenceMarkId = 0;
        CutMark noRef(zeroRef);
        QVERIFY2(noRef.resolveReferenceBox(doc, pageId).isEmpty(),
                 "E5: referenceMarkId 0 must resolve an empty box");
        QCOMPARE(noRef.applyTo(doc, pageId, 99), (ObjectId)0);

        // Self reference is an invalid cycle: refused, previous geometry kept.
        CutMarkParams selfRef = mgr.find(secondId)->params();
        selfRef.referenceKind = CutMarkParams::ReferenceKind::Mark;
        selfRef.referenceMarkId = secondId;
        QVERIFY2(!mgr.setParams(secondId, selfRef), "self reference must be refused");

        // R4: `Attach to: Cut Mark 1` — reference to the existing first mark.
        refParams.referenceMarkId = firstId;
        QVERIFY2(mgr.setParams(secondId, refParams), "R4: reference to Cut Mark 1 must resolve");

        // The reference box of mark 2 is the geometry bounds of mark 1.
        const QRectF firstBounds = mgr.find(firstId)->markBounds(doc, pageId);
        QVERIFY2(!firstBounds.isEmpty(), "markBounds of Cut Mark 1 must not be empty");

        // With offset 0 and length 5 mm, the bounds are the TrimBox expanded by
        // 5 mm on each side (the eight segments grow outward from the corners).
        const double len = 5.0 * kPtsPerMm;
        const QRectF expectedBounds(QPointF(kA4Pt.left() - len, kA4Pt.top() - len),
                                    QPointF(kA4Pt.right() + len, kA4Pt.bottom() + len));
        QVERIFY2(nearPoint(firstBounds.topLeft(), expectedBounds.topLeft()) &&
                 nearPoint(firstBounds.bottomRight(), expectedBounds.bottomRight()),
                 qPrintable(QStringLiteral("markBounds %1,%2-%3,%4, expected %5,%6-%7,%8")
                                .arg(firstBounds.left(), 0, 'f', 4).arg(firstBounds.top(), 0, 'f', 4)
                                .arg(firstBounds.right(), 0, 'f', 4).arg(firstBounds.bottom(), 0, 'f', 4)
                                .arg(expectedBounds.left(), 0, 'f', 4).arg(expectedBounds.top(), 0, 'f', 4)
                                .arg(expectedBounds.right(), 0, 'f', 4).arg(expectedBounds.bottom(), 0, 'f', 4)));

        const QRectF resolved = mgr.find(secondId)->resolveReferenceBox(doc, pageId);
        QVERIFY2(nearPoint(resolved.topLeft(), firstBounds.topLeft()) &&
                 nearPoint(resolved.bottomRight(), firstBounds.bottomRight()),
                 "R4: resolved box must be the referenced mark bounds");

        // Mark 2 geometry is drawn on the corners of that box.
        const QVector<QLineF> expected2 = expectedGeometry(firstBounds, 0.0);
        const QVector<QLineF> actual2 = documentGeometry(doc, secondId);
        QCOMPARE(actual2.size(), 8);
        for (int i = 0; i < expected2.size(); ++i) {
            QVERIFY2(nearLine(actual2[i], expected2[i]),
                     qPrintable(QStringLiteral("R4, segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(actual2[i]), lineText(expected2[i]))));
        }

        // Moving Cut Mark 1 changes its bounds; the next regeneration of mark 2 follows.
        CutMarkParams firstParams = mgr.find(firstId)->params();
        firstParams.offsetMm = 1.0;
        QVERIFY(mgr.setParams(firstId, firstParams));

        const QRectF movedBounds = mgr.find(firstId)->markBounds(doc, pageId);
        QVERIFY2(!nearPoint(movedBounds.topLeft(), firstBounds.topLeft()),
                 "moving Cut Mark 1 must change its bounds");

        QVERIFY2(mgr.find(secondId)->regenerate(doc, pageId),
                 "regenerating the dependent mark must succeed");
        const QVector<QLineF> expectedMoved = expectedGeometry(movedBounds, 0.0);
        const QVector<QLineF> actualMoved = documentGeometry(doc, secondId);
        QCOMPARE(actualMoved.size(), 8);
        for (int i = 0; i < expectedMoved.size(); ++i) {
            QVERIFY2(nearLine(actualMoved[i], expectedMoved[i]),
                     qPrintable(QStringLiteral("R4 after move, segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(actualMoved[i]), lineText(expectedMoved[i]))));
        }
    }

    // D7 case 7 — R10 v1: metadata.DocumentMarks + .artplus round trip.
    void testPersistence_R10v1() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        CutMarkManager mgr(doc);

        CutMark* mark = mgr.addCutMark(pageId);
        QVERIFY(mark != nullptr);
        const ObjectId gid = mark->objectId();

        CutMarkParams p = mark->params();
        p.offsetMm = 1.5; // "1,5 mm"
        QVERIFY(mgr.setParams(gid, p));
        QVERIFY(mgr.saveToMetadata());

        // JSON: metadata.DocumentMarks exists and carries the cut mark entry.
        const QJsonObject json = DocumentSerializer::toJson(doc);
        QVERIFY2(json.contains(QStringLiteral("metadata")), "root must contain metadata");
        const QJsonObject meta = json.value(QStringLiteral("metadata")).toObject();
        QVERIFY2(meta.contains(QStringLiteral("DocumentMarks")),
                 "metadata.DocumentMarks must be present (ADR-001 D4)");
        const QJsonObject dm = meta.value(QStringLiteral("DocumentMarks")).toObject();
        const QJsonArray cutMarks = dm.value(QStringLiteral("cutMarks")).toArray();
        QCOMPARE(cutMarks.size(), 1);
        const QJsonObject entry = cutMarks.at(0).toObject();
        QCOMPARE(entry.value(QStringLiteral("kind")).toString(),
                 QStringLiteral("DynamicObject_PDFPlusCutMark")); // R9 / 0x18013E3B0
        QCOMPARE(entry.value(QStringLiteral("name")).toString(), QStringLiteral("Cut Mark 1"));
        QCOMPARE(entry.value(QStringLiteral("reference")).toObject()
                     .value(QStringLiteral("box")).toString(),
                 QStringLiteral("TrimBox"));
        QVERIFY(qAbs(entry.value(QStringLiteral("offsetMm")).toDouble() - 1.5) <= 1e-9);

        // Save + load the .artplus document.
        QTemporaryDir tmp;
        QVERIFY2(tmp.isValid(), "QTemporaryDir must be valid");
        const QString path = tmp.path() + QStringLiteral("/f001_cut_mark.artplus");
        QVERIFY2(DocumentSerializer::save(doc, path), "saving the .artplus must succeed");

        Document loaded;
        QVERIFY2(DocumentSerializer::load(path, loaded), "loading the .artplus must succeed");

        CutMarkManager loadedMgr(loaded);
        QVERIFY(loadedMgr.loadFromMetadata());
        QCOMPARE(loadedMgr.cutMarks().size(), 1);

        const CutMark& reloaded = loadedMgr.cutMarks().front();
        QCOMPARE(reloaded.params().referenceKind, CutMarkParams::ReferenceKind::PageBox);
        QCOMPARE(reloaded.params().referenceBox, PageBoxType::TrimBox);
        QCOMPARE(reloaded.params().offsetMm, 1.5);
        QCOMPARE(reloaded.params().orientation, 1);
        QCOMPARE(reloaded.params().repetition, 2);
        QCOMPARE(reloaded.params().lineTypes, QVector<int>{0});
        QCOMPARE(reloaded.displayName(), QStringLiteral("Cut Mark 1"));

        // The group id still resolves and the geometry survived with 8 segments.
        auto group = loaded.object(reloaded.objectId());
        QVERIFY2(group != nullptr, "reloaded groupId must resolve in the document");
        QCOMPARE(group->children().size(), (size_t)8);

        const QVector<QLineF> expected = expectedGeometry(kA4Pt, 1.5);
        const QVector<QLineF> actual = documentGeometry(loaded, reloaded.objectId());
        QCOMPARE(actual.size(), 8);
        for (int i = 0; i < expected.size(); ++i) {
            QVERIFY2(nearLine(actual[i], expected[i]),
                     qPrintable(QStringLiteral("reloaded, segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(actual[i]), lineText(expected[i]))));
        }

        // A document without the key loads with zero marks (D4 compatibility).
        Document plain;
        CutMarkManager plainMgr(plain);
        QVERIFY(plainMgr.loadFromMetadata());
        QCOMPARE(plainMgr.cutMarks().size(), 0);
    }

    // Regression for D1 (docs/audit/F-001-audit.md §6): the redo of the creation
    // must reinsert the mark in the manager, otherwise toMetadata() loses it.
    void testUndoRedoCreation_D1() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        UndoStack history;
        CutMarkManager mgr(doc);
        mgr.setUndoStack(&history);

        QVERIFY(mgr.addCutMark(pageId) != nullptr);
        const ObjectId gid = mgr.cutMarks().front().objectId();
        const CutMarkParams created = mgr.find(gid)->params();
        QCOMPARE(mgr.find(gid)->displayName(), QStringLiteral("Cut Mark 1"));

        // Non-default edit on top of the creation, so the redo chain also has to
        // preserve real parameters (1,5 mm) and not just defaults.
        CutMarkParams p = created;
        p.offsetMm = 1.5;
        QVERIFY(mgr.setParams(gid, p));
        QCOMPARE(mgr.find(gid)->params().offsetMm, 1.5);

        // Back to the initial state: undo the edit, then undo the creation.
        history.undo(doc);
        history.undo(doc);
        QCOMPARE(mgr.cutMarks().size(), 0);
        QVERIFY2(doc.object(gid) == nullptr, "undo of creation must remove the group");
        QCOMPARE(mgr.toMetadata().value(QStringLiteral("cutMarks")).toArray().size(), 0);

        // D1: redo of the creation reattaches the group AND reinserts the mark.
        history.redo(doc);
        QCOMPARE(mgr.cutMarks().size(), 1);
        QVERIFY2(doc.object(gid) != nullptr, "redo of creation must restore the group");
        QVERIFY2(mgr.find(gid) != nullptr, "D1: redo of creation must reinsert the mark in the manager");
        QCOMPARE(mgr.find(gid)->displayName(), QStringLiteral("Cut Mark 1"));
        QCOMPARE(mgr.find(gid)->displayIndex(), 1);
        QVERIFY2(mgr.find(gid)->params() == created,
                 "D1: redo of creation must restore the creation parameters");
        QCOMPARE(doc.object(gid)->children().size(), (size_t)8);

        // The metadata written at this point must carry exactly one mark (the D1
        // symptom was `cutMarks: []`).
        const QJsonArray afterCreationRedo =
            mgr.toMetadata().value(QStringLiteral("cutMarks")).toArray();
        QCOMPARE(afterCreationRedo.size(), 1);
        QCOMPARE(afterCreationRedo.at(0).toObject().value(QStringLiteral("name")).toString(),
                 QStringLiteral("Cut Mark 1"));
        QVERIFY(mgr.saveToMetadata());
        const QJsonObject root = DocumentSerializer::toJson(doc);
        QCOMPARE(root.value(QStringLiteral("metadata")).toObject()
                     .value(QStringLiteral("DocumentMarks")).toObject()
                     .value(QStringLiteral("cutMarks")).toArray().size(),
                 1);

        // Redo of the edit restores 1,5 mm with a single mark in the manager.
        history.redo(doc);
        QCOMPARE(mgr.cutMarks().size(), 1);
        QCOMPARE(mgr.find(gid)->params().offsetMm, 1.5);
        QCOMPARE(mgr.toMetadata().value(QStringLiteral("cutMarks")).toArray().size(), 1);

        const QVector<QLineF> expected = expectedGeometry(kA4Pt, 1.5);
        const QVector<QLineF> actual = documentGeometry(doc, gid);
        QCOMPARE(actual.size(), 8);
        for (int i = 0; i < expected.size(); ++i) {
            QVERIFY2(nearLine(actual[i], expected[i]),
                     qPrintable(QStringLiteral("D1 redo, segment %1: got %2, expected %3")
                                    .arg(i).arg(lineText(actual[i]), lineText(expected[i]))));
        }
    }

    // Regression for D1 side effect: after undo+redo of the creation, a new mark
    // must be numbered "Cut Mark 2", never a duplicate "Cut Mark 1".
    void testNoDuplicateNumberingAfterRedo_D1() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        UndoStack history;
        CutMarkManager mgr(doc);
        mgr.setUndoStack(&history);

        QVERIFY(mgr.addCutMark(pageId) != nullptr);
        const ObjectId firstId = mgr.cutMarks().front().objectId();
        QCOMPARE(mgr.cutMarks().front().displayName(), QStringLiteral("Cut Mark 1"));

        history.undo(doc);
        QCOMPARE(mgr.cutMarks().size(), 0);
        history.redo(doc);
        QCOMPARE(mgr.cutMarks().size(), 1);
        QVERIFY(mgr.find(firstId) != nullptr);

        // Second creation after the redo: sequential numbering must continue.
        QVERIFY(mgr.addCutMark(pageId) != nullptr);
        QCOMPARE(mgr.cutMarks().size(), 2);
        const ObjectId secondId = mgr.cutMarks().back().objectId();
        QVERIFY2(secondId != firstId, "the second mark must be a new object");
        QCOMPARE(mgr.find(secondId)->displayName(), QStringLiteral("Cut Mark 2"));
        QCOMPARE(mgr.find(secondId)->displayIndex(), 2);
        QCOMPARE(mgr.find(firstId)->displayName(), QStringLiteral("Cut Mark 1"));

        // Both marks are distinct in the manager and in the metadata.
        const QJsonArray marks = mgr.toMetadata().value(QStringLiteral("cutMarks")).toArray();
        QCOMPARE(marks.size(), 2);
        QCOMPARE(marks.at(0).toObject().value(QStringLiteral("name")).toString(),
                 QStringLiteral("Cut Mark 1"));
        QCOMPARE(marks.at(1).toObject().value(QStringLiteral("name")).toString(),
                 QStringLiteral("Cut Mark 2"));
        QVERIFY(doc.object(firstId) != nullptr);
        QVERIFY(doc.object(secondId) != nullptr);

        // A third creation still yields "Cut Mark 3".
        QVERIFY(mgr.addCutMark(pageId) != nullptr);
        QCOMPARE(mgr.cutMarks().size(), 3);
        QCOMPARE(mgr.cutMarks().back().displayName(), QStringLiteral("Cut Mark 3"));
    }

    // Regression for D1 across persistence: save/reload after undo->redo must show
    // one mark, and the reloaded document must resolve its group.
    void testUndoRedoCreationSurvivesReload_D1() {
        Document doc;
        const PageId pageId = setupPage(doc, kA4Pt, kA4Pt);
        UndoStack history;
        CutMarkManager mgr(doc);
        mgr.setUndoStack(&history);

        QVERIFY(mgr.addCutMark(pageId) != nullptr);
        const ObjectId gid = mgr.cutMarks().front().objectId();

        history.undo(doc);
        history.redo(doc);
        QCOMPARE(mgr.cutMarks().size(), 1);
        QVERIFY(doc.object(gid) != nullptr);

        QVERIFY(mgr.saveToMetadata());
        QTemporaryDir tmp;
        QVERIFY(tmp.isValid());
        const QString path = tmp.path() + QStringLiteral("/f001_d1.artplus");
        QVERIFY(DocumentSerializer::save(doc, path));

        Document loaded;
        QVERIFY(DocumentSerializer::load(path, loaded));
        CutMarkManager loadedMgr(loaded);
        QVERIFY(loadedMgr.loadFromMetadata());
        QCOMPARE(loadedMgr.cutMarks().size(), 1);
        QCOMPARE(loadedMgr.cutMarks().front().displayName(), QStringLiteral("Cut Mark 1"));

        auto group = loaded.object(loadedMgr.cutMarks().front().objectId());
        QVERIFY2(group != nullptr, "D1: reloaded groupId must resolve");
        QCOMPARE(group->children().size(), (size_t)8);

        const QJsonObject meta = DocumentSerializer::toJson(loaded)
                                     .value(QStringLiteral("metadata")).toObject();
        QCOMPARE(meta.value(QStringLiteral("DocumentMarks")).toObject()
                     .value(QStringLiteral("cutMarks")).toArray().size(),
                 1);
    }
};

QTEST_APPLESS_MAIN(TestCutMark)
#include "test_cut_mark.moc"
