#pragma once

// F-001 — Cut Mark (Trim Marks).
// ADR-001-cut-mark.md (D1–D6). The dynamic cut mark created by
// `Marks > + > Add Cut Mark` (no modal dialog) is a new entity here, not a
// MarkSettings preset of MarksEngine.
//
// Evidence (v24.03.10017): GHIDRA-DocumentMarks-0x1801344E0 (ctor defaults),
// 0x180134B00 (GetReferenceBox), 0x180135160 (offset variant, SetOffset),
// 0x180136190 (regenerateMarkImp), 0x1800AA1B0 (SetCutMarkOffset is undoable),
// 0x180135660 (getMarkType = DynamicObject_PDFPlusCutMark),
// CAP-20261119-01 (observação histórica: Add Cut Mark sem modal, Attach to: Trim Box,
// offset 0,00 mm).

#include "../document/document_model.h"
#include "../document/undo.h"

#include <QJsonObject>
#include <QLineF>
#include <QRectF>
#include <QString>
#include <QVector>
#include <QtGlobal>
#include <memory>
#include <optional>
#include <vector>

namespace ArtPlus {

// D2 — parameter model. UI units are in the field name (offsetMm, lengthMm);
// stroke thickness is in points (strokeWidthPt). Geometry is expressed in
// document points, the same unit as PageBoxes (see pdf_importer.cpp).
struct CutMarkParams {
    enum class ReferenceKind { PageBox, Mark };

    ReferenceKind referenceKind = ReferenceKind::PageBox;
    PageBoxType   referenceBox  = PageBoxType::TrimBox; // PDF+ PageBox=3 (inferência, spec R2)
    ObjectId      referenceMarkId = 0;                  // ReferenceKind::Mark (spec R4)

    double  offsetMm = 0.0;        // unidade de UI; convertido para pt na geometria
    QString offsetFormula;         // fx; v1 não avalia (TODO(F-001), spec R6/E4)

    int orientation = 1;           // opaco; ctor 0x1801344E0. TODO(F-001)
    int repetition  = 2;           // opaco; ctor 0x1801344E0. TODO(F-001)
    QVector<int> lineTypes{0};     // ctor: vetor com 1 elemento, valor 0
    // TODO(F-001): `orientation`/`repetition`/`lineTypes` são persistidos aqui, mas a v240 não escreve esses campos (spec §8).

    // Parâmetros de forma v1 — inferência declarada, não medidos (spec §8 item 1)
    double lengthMm      = 5.0;    // TODO(F-001)
    double strokeWidthPt = 0.25;   // TODO(F-001)
    Color  color = Color::cmyk(0.0f, 1.0f, 0.0f, 0.0f); // provisório; spec §8 item 9

    bool operator==(const CutMarkParams& o) const {
        return referenceKind == o.referenceKind &&
               referenceBox == o.referenceBox &&
               referenceMarkId == o.referenceMarkId &&
               qFuzzyCompare(offsetMm + 1.0, o.offsetMm + 1.0) &&
               offsetFormula == o.offsetFormula &&
               orientation == o.orientation &&
               repetition == o.repetition &&
               lineTypes == o.lineTypes &&
               qFuzzyCompare(lengthMm + 1.0, o.lengthMm + 1.0) &&
               qFuzzyCompare((double)strokeWidthPt + 1.0, (double)o.strokeWidthPt + 1.0) &&
               color == o.color;
    }
    bool operator!=(const CutMarkParams& o) const { return !(*this == o); }
};

class CutMarkManager;

// Undo command for one cut mark edit (R5: every offset edit is a single undo
// action; R8: regeneration replaces the content atomically).
//
// The command snapshots the mark's content (the GroupObject children, and the
// group itself for creation) and restores it verbatim — object ids are
// preserved, so the manager keeps a stable group id across undo/redo.
// A non-owning CutMarkManager* lets the manager resynchronise the in-memory
// parameters after undo/redo; the manager must outlive the commands in the
// stack (true for the UI owner: both are members of ArtPlusMainWindow).
class CutMarkEditCommand : public Command {
public:
    // displayIndex preserva "Cut Mark N" quando o comando é o da criação e o
    // manager precisa reinserir a entrada no redo (auditoria F-001 D1).
    CutMarkEditCommand(CutMarkManager* manager, ObjectId groupId, int displayIndex = 0);

    // Snapshot of the current content. includeRoot applies to creation, where
    // the group itself is created/removed by the command.
    void capture(Document& doc, bool includeRoot, const CutMarkParams& params);
    // Snapshot taken after the mutation (same id sets as the live document).
    void captureAfter(Document& doc, bool includeRoot, const CutMarkParams& params);

    QString description() const override { return QStringLiteral("Edit Cut Mark"); }
    void undo(Document& doc) const override;
    void redo(Document& doc) const override;

private:
    CutMarkManager* m_manager = nullptr;
    ObjectId m_groupId = 0;
    int m_displayIndex = 0;

    CutMarkParams m_beforeParams;
    CutMarkParams m_afterParams;
    bool m_hasBefore = false;
    bool m_hasAfter = false;

    std::shared_ptr<DocumentObject> m_beforeRoot;
    std::shared_ptr<DocumentObject> m_afterRoot;
    std::vector<std::shared_ptr<DocumentObject>> m_beforeContent;
    std::vector<std::shared_ptr<DocumentObject>> m_afterContent;
};

class CutMark {
public:
    CutMark();
    explicit CutMark(const CutMarkParams& params);

    const CutMarkParams& params() const { return m_params; }
    void setParams(const CutMarkParams& params) { m_params = params; } // só grava; não regenera

    ObjectId objectId() const { return m_groupId; } // grupo no documento; 0 = nunca aplicada
    QString  displayName() const;                   // "Cut Mark N"
    int      displayIndex() const { return m_displayIndex; }

    QRectF resolveReferenceBox(const Document& doc, PageId page) const;
    // Retângulo delimitador da própria marca, calculado a partir dos 8 segmentos
    // (não depende de GroupObject::boundingBox(), que é vazio no core atual).
    // Para `referenceKind == Mark` resolve a Cut Mark referenciada pela lista do
    // manager e usa o retângulo dela (R4).
    QRectF markBounds(const Document& doc, PageId page) const;
    // 4 vértices × 2 segmentos (D3); offset positivo = para fora da caixa.
    // TODO(F-001): geometria sintetizada (8 QLineF num único Group); R7 da spec descreve cópia do FormPaint com um Group por posição de dm::MarkPositionVector.
    QVector<QLineF> buildGeometry(const QRectF& referenceBoxPt) const;

    // Cria a subárvore; devolve o id do grupo, 0 em caixa vazia/página inválida (E5/E6/E9).
    ObjectId applyTo(Document& doc, PageId page, int displayIndex);
    // Apaga a subárvore atual e recria com os parâmetros correntes (R8).
    bool regenerate(Document& doc, PageId page);

    QJsonObject toMetadata() const;
    static std::optional<CutMark> fromMetadata(const QJsonObject& json, const Document& doc);

private:
    friend class CutMarkManager;

    QRectF resolveReferenceBoxWith(const Document& doc, PageId page,
                                   const CutMarkManager* manager, int depth) const;
    QRectF markBoundsImpl(const Document& doc, PageId page, int depth) const;
    void setManagerContext(const CutMarkManager* manager) { m_manager = manager; }

    CutMarkParams m_params;
    ObjectId m_groupId = 0;
    int m_displayIndex = 0;
    const CutMarkManager* m_manager = nullptr; // catálogo para resolver R4; não possui
};

class CutMarkManager {
public:
    explicit CutMarkManager(Document& document) : m_document(&document) {}

    void setUndoStack(UndoStack* stack) { m_undoStack = stack; } // padrão StepRepeatEngine

    CutMark* addCutMark(PageId page); // R1: defaults TrimBox / 0,00 mm
    CutMark* find(ObjectId groupId);
    const CutMark* find(ObjectId groupId) const;
    const QVector<CutMark>& cutMarks() const { return m_marks; }

    // Regenera e empilha UMA ação de undo. false = id desconhecido ou caixa vazia.
    bool setParams(ObjectId groupId, const CutMarkParams& params);

    // Chave `metadata.DocumentMarks` (D4). Documento sem a chave ⇒ zero marcas.
    bool loadFromMetadata();
    bool saveToMetadata() const;
    QJsonObject toMetadata() const;

private:
    friend class CutMarkEditCommand;
    friend class CutMark; // R4: resolve a Cut Mark referenciada pela lista

    // Chamado pelo CutMarkEditCommand após undo/redo. `present` = o grupo está
    // no documento; `displayIndex` mantém a numeração no redo da criação.
    void onMarkRestored(ObjectId groupId, const CutMarkParams& params, int displayIndex, bool present);
    int nextDisplayIndex() const;

    PageId pageOf(const CutMark& mark) const;
    void pruneDetached();

    Document* m_document = nullptr;
    UndoStack* m_undoStack = nullptr;
    QVector<CutMark> m_marks;
};

} // namespace ArtPlus
