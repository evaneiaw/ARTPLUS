#pragma once

#include "../document/document_model.h"
#include "../document/file_dispatcher.h"
#include "../document/undo.h"
#include "../prepress/cut_mark.h"
#include "../prepress/bearer_bar.h"
#include "../ui/document_marks_panel.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QToolBar>
#include <QStatusBar>
#include <QListWidget>
#include <QDockWidget>
#include <QTreeWidget>
#include <QMenuBar>
#include <QComboBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QInputDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QFormLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QColorDialog>
#include <memory>
#include <vector>
#include <unordered_map>

namespace ArtPlus {

// ---------------------------------------------------------------- scene
class ArtPlusScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit ArtPlusScene(QObject* parent = nullptr) : QGraphicsScene(parent) {}
    void setDocument(Document* doc);
    Document* document() const { return m_doc; }
    void setUndoStack(UndoStack* stack) { m_undoStack = stack; }
    void refresh();
    bool hasItems() const { return !QGraphicsScene::items().isEmpty(); }
    void setCurrentPage(PageId id);
    PageId currentPage() const { return m_currentPage; }
    // F-005 R8: overlay "Media Box W x H mm" (conversão pt → mm na borda da UI).
    void setPageBoxOverlay(const QString& text);

    // Selection helpers
    std::vector<ObjectId> selectedObjectIds() const;
    void setSelectionIds(const std::vector<ObjectId>& ids);
    void deleteSelected();

signals:
    void selectionChangedObjects(const std::vector<ObjectId>& ids);
    void documentModified();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    Document* m_doc = nullptr;
    PageId m_currentPage = 0;
    QString m_pageBoxOverlay;
    UndoStack* m_undoStack = nullptr;
    bool m_dragging = false;
    QPointF m_dragStart;
    bool m_rubberBand = false;
    QRectF m_rubberBandRect;
    bool m_additive = false;
    std::unordered_map<ObjectId, QTransform> m_dragStartTransforms;

    std::vector<ObjectId> hitTest(const QPointF& scenePos) const;
    void selectIds(const std::vector<ObjectId>& ids, bool additive);
};

// ---------------------------------------------------------------- view
class ArtPlusView : public QGraphicsView {
    Q_OBJECT
public:
    explicit ArtPlusView(QGraphicsScene* scene, QWidget* parent = nullptr);
    void setTool(int tool); // 0 = select, 1 = hand, 2 = zoom
    int tool() const { return m_tool; }

signals:
    void zoomChanged(double factor);
    void deleteRequested();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    int m_tool = 0;
    bool m_panning = false;
    QPoint m_panStart;
    QPoint m_panStartScroll;
    void zoomAt(const QPoint& pos, double factor);
};

// ------------------------------------------------------------ main window

// Action structures for Module 17/18
struct Action {
    enum class Type {
        StepRepeat,
        Imposition,
        Marks,
        CutCreaseLines,
        Unknown
    } type;

    // Step & Repeat parameters
    int copiesX = 1;
    int copiesY = 1;
    qreal spacingX = 0.0;
    qreal spacingY = 0.0;
    qreal angle = 0.0;

    // Imposition parameters
    int impositionType = 0; // 0=None, 1=Half, 2=Quarter

    // Marks parameters
    int marksType = 0; // 0=None, 1=Crop, 2=Registration, 3=Crease

    // Cut/Crease Lines parameters
    int cutType = 0; // 0=None, 1=Cut, 2=Crease, 3=Art/Knife Separation

    // Data for serialization
    QString description;

    QJsonDocument toJson() const;
    static Action fromJson(const QJsonDocument& doc);
};

struct ActionList {
    QString name;
    QDateTime timestamp;
    QVector<Action> actions;

    QJsonDocument toJson() const;
    static ActionList fromJson(const QJsonDocument& doc);
};

class ArtPlusMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit ArtPlusMainWindow(QWidget* parent = nullptr);
    ~ArtPlusMainWindow() override = default;
    // F-005 R1/R2: ponto único de abertura — o --open de main.cpp deixa de presumir PDF.
    // On failure returns false, fills `errorOut` with the symbolic message and leaves
    // the previous document intact.
    bool openDocumentPath(const QString& filePath, QString* errorOut = nullptr);
    void viewPage(int index); // 0-based; triggers onPageChanged via the combo

private slots:
    // File operations
    void openDocument();
    void saveArtPlus();
    void saveArtPlusAs();
    void exportPdf();

    // View operations
    void zoomIn();
    void zoomOut();
    void zoomFit();
    // F-005 R9: recalcula a viewport quando docks são exibidos/ocultados/flutuam.
    void relayoutViewport();

    // Tool selection
    void selectTool();
    void handTool();
    void zoomTool();

    // Selection operations
    void selectAll();
    void deselectAll();
    void deleteSelected();

    // Undo/Redo
    void undoAction();
    void redoAction();

    // Production operations (Module 14-16)
    void stepRepeat();
    void imposition();
    void marks();
    void cutLines();
    // F-001: `Marks > Add Cut Mark` — cria a marca dinâmica sem diálogo modal.
    void addCutMark();
    // F-003: `Marks > Add Bearer Bar Mark` — cria a marca dinâmica sem diálogo modal.
    void addBearerBar();
    // Action Lists (Module 17)
    void actionLists();
    void executeAction(const Action& action);
    void batchProcessing();

    // Scripts & Extensibility (Module 18)
    void presets();
    void scripting();

    // Reports, Performance, Recovery (Module 19/20)
    void reports();
    void performance();
    void recovery();

    // Document state
    void onSelectionChanged(const std::vector<ObjectId>& ids);
    void updateModifiedIndicator();
    void onPageChanged(int index);

private:
    // ── UI Skeleton helpers ──────────────────────────────────────────────
    void setupMarksMenuAndToolbar();   // submenu Marks + toolbar placeholders
    void refreshDynamicMarksDock();    // repopula lista de marcas dinâmicas
    void refreshInspector();           // sincroniza Inspector com documento

private:
    ArtPlusScene* m_scene = nullptr;
    ArtPlusView* m_view = nullptr;
    Document m_document;
    // F-005 R3: o dispatcher pertence à janela; handlers registrados uma única vez.
    FileDispatcher m_dispatcher;
    QString m_originalPdfPath;
    QDockWidget* m_layersDock = nullptr;
    QListWidget* m_layersList = nullptr;
    QDockWidget* m_objectsDock = nullptr;
    QTreeWidget* m_objectTree = nullptr;
    QStatusBar* m_statusBar = nullptr;
    UndoStack m_history;
    // F-001 / ADR-001 D6: dono das Cut Marks dinâmicas do documento aberto.
    CutMarkManager m_cutMarkManager{m_document};
    // F-003 / ADR-002 D5: dono das Bearer Bars dinâmicas do documento aberto.
    BearerBarManager m_bearerBarManager{m_document};

    // ── UI Skeleton members ──────────────────────────────────────────────
    // Dock: Dynamic Marks — lista de marcas dinâmicas no documento
    QDockWidget* m_dynamicMarksDock = nullptr;
    QListWidget* m_dynamicMarksList = nullptr;
    // Dock: Inspector / Context Bar — placeholder com parâmetros visuais de marcas
    QDockWidget* m_inspectorDock = nullptr;
    QWidget*     m_inspectorPanel = nullptr;
    QFormLayout* m_inspectorLayout = nullptr;

    // Toolbar placeholders (futuras marcas visuais)
    QAction* m_openAct      = nullptr; // F-005 R1: único comando de abertura
    QAction* m_regMarkAct   = nullptr;
    QAction* m_colorBarAct  = nullptr;
    QAction* m_gradStripAct = nullptr;
    QComboBox* m_pageCombo = nullptr;
    std::vector<PageId> m_pageIds;

    // F-002: Document > Marks panel (dock widget)
    QDockWidget* m_documentMarksDock = nullptr;
    UI::DocumentMarksPanel* m_documentMarksPanel = nullptr;

    // Action Lists recording state
    QVector<Action> m_recordedActions;

    // F-005 R8: título `<arquivo> @ <zoom> – ArtPlus` e overlay em milímetros.
    void updateWindowTitle() const;
    void updatePageBoxOverlay(const QRectF& mediaBoxPt);

    void setupUi();
    void setupMenusAndToolbars();
    void updatePageCombo();
    void rebuildScene();
    void updateDocumentInfo();
};

} // namespace ArtPlus
