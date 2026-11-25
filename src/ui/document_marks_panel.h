#ifndef DOCUMENT_MARKS_PANEL_H
#define DOCUMENT_MARKS_PANEL_H

#include "../prepress/markset_processor.h"
#include "../prepress/markset_reporter.h"
#include "../document/document_model.h"
#include "../document/undo.h"
#include <QWidget>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <vector>
#include <memory>

namespace ArtPlus::UI {

class DocumentMarksPanel : public QWidget {
    Q_OBJECT
public:
    explicit DocumentMarksPanel(Document* doc, UndoStack* undoStack, QWidget* parent = nullptr);
    ~DocumentMarksPanel() override;

    void setDocument(Document* doc);

signals:
    void markSetApplied(const std::string& markSetPath);
    void markSetLoaded(const std::string& markSetPath);
    void errorOccurred(const QString& message);

private slots:
    void onLoadMarkSet();
    void onSaveDeleteMarkSet();
    void onUpdateMarks();
    void onCreateMarkFromSelection();
    void onAddMark(int markType); // CutMark, BearerBar, Dimensions, etc.
    void onLoadCustomVariables();
    void onDeleteMark();
    void onDeleteAllMarks();

private:
    enum MarkType {
        CutMark = 0,
        BearerBar = 1,
        Dimensions = 2,
        ExternalFile = 3,
        Position = 4,
        InputFile = 5,
        RepeatForGrid = 6
    };

    Document* m_doc = nullptr;
    UndoStack* m_undoStack = nullptr;
    Prepress::MarkSetProcessor m_processor;
    std::unique_ptr<Prepress::Reporter> m_reporter;

    // UI elements
    QToolButton* m_gearButton = nullptr;     // engrenagem ▾
    QToolButton* m_addButton = nullptr;      // + ▾
    QMenu* m_gearMenu = nullptr;
    QMenu* m_addMenu = nullptr;
    QAction* m_loadMarkSetAction = nullptr;
    QAction* m_saveDeleteMarkSetAction = nullptr;
    QAction* m_updateMarksAction = nullptr;
    QAction* m_createMarkFromSelectionAction = nullptr;
    QAction* m_loadCustomVarsAction = nullptr;
    QAction* m_deleteMarkAction = nullptr;
    QAction* m_deleteAllMarksAction = nullptr;
    std::vector<QAction*> m_addMarkActions;

    void setupUI();
    void connectSignals();
    void showLoadMarkSetDialog();
    void showSaveDeleteMarkSetDialog();
    void applyMarkSet(const std::string& path);

    // Helper para emitir error signal
    void emitError(const QString& msg);

    // Reporter implementation for UI warnings
    class UiReporter : public Prepress::Reporter {
    public:
        explicit UiReporter(DocumentMarksPanel* panel) : m_panel(panel) {}
        void warnMissingNamedObject(const std::vector<std::string>& names,
                                    const std::string& markSetName,
                                    size_t pageIndex) override;
        void warnMissingPageBox(const std::string& boxName,
                                const std::string& markSetName,
                                size_t pageIndex) override;
    private:
        DocumentMarksPanel* m_panel;
    };
};

} // namespace ArtPlus::UI

#endif // DOCUMENT_MARKS_PANEL_H