#pragma once

// F-003 — Bearer Bar Mark.
// ADR-002-bearer-bar.md (D1–D8). Dynamic mark created by
// `Marks > Add Bearer Bar Mark` (no modal dialog). One filled rectangle per
// enabled side bit of `locationMask`, outside the reference box.
//
// Evidence: GHIDRA-DocumentMarks-0x18001E3C0 (legacy ctor defaults),
// 0x18001FDB0 (regenerateMarkImp: 1 Path per Location bit),
// 0x18012FAA0 (PDF+ ctor defaults), 0x18012E950 (SizeReference coherence, R5).

#include "../document/document_model.h"
#include "../document/undo.h"

#include <QJsonObject>
#include <QRectF>
#include <QVector>
#include <QtGlobal>
#include <optional>
#include <memory>
#include <vector>
#include <QString>

namespace ArtPlus {

struct BearerBarParams {
    PageBoxType referenceBox = PageBoxType::TrimBox; // PDF+ PageBox=3 (A1). TODO(F-003): PageBox=3 = TrimBox por inferência A1
    double widthMm       = 5.0;   // ctor legado 0x18001E3C0 (A2). TODO(F-003): PDF+ não expõe espessura numérica
    double extendMm      = 0.0;   // PDF+ +0x6A0 / legado +0x6A0. TODO(F-003): modelo do retângulo — confiança média
    double offsetMm      = 0.0;   // PDF+ +0x698 / legado +0x6A8
    int    locationMask  = 0x3;   // 1=l 2=r 4=t 8=b (R4)
    int    sizeReference = 0;     // 0..8 (R5), opaco (A3). TODO(F-003)
    int    direction     = 1;     // 0=vertical 1=horizontal (A3). TODO(F-003)
    Color  color = Color::rgb(168.0f / 255.0f, 164.0f / 255.0f, 164.0f / 255.0f); // A5. TODO(F-003): cinza provisório; Registration ainda não decidido

    static bool sizeReferenceCoherent(int sizeReference, int direction);

    bool operator==(const BearerBarParams& o) const;
    bool operator!=(const BearerBarParams& o) const;
};

class BearerBarManager;

class BearerBarEditCommand : public Command {
public:
    BearerBarEditCommand(BearerBarManager* manager, ObjectId groupId, int displayIndex = 0);
    void capture(Document& doc, bool includeRoot, const BearerBarParams& params);
    void captureAfter(Document& doc, bool includeRoot, const BearerBarParams& params);

    QString description() const override { return QStringLiteral("Edit Bearer Bar Mark"); }
    void undo(Document& doc) const override;
    void redo(Document& doc) const override;
private:
    BearerBarManager* m_manager = nullptr;
    ObjectId m_groupId = 0;
    int m_displayIndex = 0;

    BearerBarParams m_beforeParams;
    BearerBarParams m_afterParams;
    bool m_hasBefore = false;
    bool m_hasAfter = false;

    std::shared_ptr<DocumentObject> m_beforeRoot;
    std::shared_ptr<DocumentObject> m_afterRoot;
    std::vector<std::shared_ptr<DocumentObject>> m_beforeContent;
    std::vector<std::shared_ptr<DocumentObject>> m_afterContent;
};

class BearerBar {
public:
    BearerBar();
    explicit BearerBar(const BearerBarParams& params);

    const BearerBarParams& params() const;
    void setParams(const BearerBarParams& params); // só grava; não regenera

    ObjectId objectId() const;
    QString  displayName() const;                    // "Bearer Bar Mark N"
    int      displayIndex() const;

    QRectF resolveReferenceBox(const Document& doc, PageId page) const;
    QVector<QRectF> buildGeometry(const QRectF& referenceBoxPt) const;

    ObjectId applyTo(Document& doc, PageId page, int displayIndex); // 0 = nada criado
    bool regenerate(Document& doc, PageId page);                    // substitui, não acumula

    QJsonObject toMetadata() const;
    static std::optional<BearerBar> fromMetadata(const QJsonObject& json, const Document& doc);

private:
    friend class BearerBarManager;
    BearerBarParams m_params;
    ObjectId m_groupId = 0;
    int m_displayIndex = 0;
};

class BearerBarManager {
public:
    explicit BearerBarManager(Document& document);
    void setUndoStack(UndoStack* stack);

    BearerBar* addBearerBar(PageId page);
    BearerBar* find(ObjectId groupId);
    const QVector<BearerBar>& bearerBars() const;

    bool setParams(ObjectId groupId, const BearerBarParams& params); // UMA ação de undo
    bool loadFromMetadata();
    bool saveToMetadata() const;
    QJsonObject toMetadata() const;

private:
    friend class BearerBarEditCommand;
    void onMarkRestored(ObjectId groupId, const BearerBarParams& params, int displayIndex, bool present);
    int  nextDisplayIndex() const;
    PageId pageOf(const BearerBar& mark) const;
    void pruneDetached();

    // Helpers for undo/redo of group creation/removal.
    static void detachGroup(Document& doc, ObjectId groupId);
    static void attachGroup(Document& doc, ObjectId groupId, LayerId layerId);

    Document* m_document = nullptr;
    UndoStack* m_undoStack = nullptr;
    QVector<BearerBar> m_bars;
};

} // namespace ArtPlus