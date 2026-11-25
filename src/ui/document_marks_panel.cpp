#include "document_marks_panel.h"
#include "../prepress/markset_processor.h"
#include "../pdf/markset_pdf_loader.h"
#include "../document/document_model.h"
#include "../document/undo.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QTableWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QDir>
#include <QCoreApplication>

namespace ArtPlus::UI {

DocumentMarksPanel::DocumentMarksPanel(Document* doc, UndoStack* undoStack, QWidget* parent)
    : QWidget(parent), m_doc(doc), m_undoStack(undoStack) {
    setupUI();
    connectSignals();

    // Configura reporter para avisos na UI
    m_reporter = std::make_unique<UiReporter>(this);
    m_processor.setReporter(std::move(m_reporter));
}

DocumentMarksPanel::~DocumentMarksPanel() = default;

void DocumentMarksPanel::setDocument(Document* doc) {
    m_doc = doc;
    m_processor.setTargetDocument(*doc);
}

void DocumentMarksPanel::setupUI() {
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(4);

    // Botão engrenagem ▾
    m_gearButton = new QToolButton(this);
    m_gearButton->setText(QCoreApplication::translate("DocumentMarksPanel", "\u2699\ufe0f"));
    m_gearButton->setToolTip(tr("Mark Set Options"));
    m_gearButton->setPopupMode(QToolButton::InstantPopup);
    m_gearMenu = new QMenu(this);

    m_loadMarkSetAction = m_gearMenu->addAction(tr("Load Mark Set..."));
    m_saveDeleteMarkSetAction = m_gearMenu->addAction(tr("Save/Delete Mark Set..."));
    m_gearMenu->addSeparator();
    m_updateMarksAction = m_gearMenu->addAction(tr("Update Marks"));
    m_gearMenu->addSeparator();
    m_createMarkFromSelectionAction = m_gearMenu->addAction(tr("Create Mark from Selection"));
    m_gearMenu->addSeparator();
    m_loadCustomVarsAction = m_gearMenu->addAction(tr("Load Custom Variables Database..."));
    m_gearMenu->addSeparator();
    m_deleteMarkAction = m_gearMenu->addAction(tr("Delete Mark"));
    m_deleteAllMarksAction = m_gearMenu->addAction(tr("Delete All Marks"));

    m_gearButton->setMenu(m_gearMenu);
    layout->addWidget(m_gearButton);

    // Botão + ▾
    m_addButton = new QToolButton(this);
    m_addButton->setText(QCoreApplication::translate("DocumentMarksPanel", "+\u25be"));
    m_addButton->setToolTip(tr("Add Mark"));
    m_addButton->setPopupMode(QToolButton::InstantPopup);
    m_addMenu = new QMenu(this);

    const char* markTypeNames[] = {
        "Cut Mark",
        "Bearer Bar",
        "Dimensions",
        "External File",
        "Position",
        "Input File",
        "Repeat for Grid"
    };

    for (int i = 0; i < 7; ++i) {
        QAction* act = m_addMenu->addAction(tr(markTypeNames[i]));
        act->setData(i);
        m_addMarkActions.push_back(act);
    }

    m_addButton->setMenu(m_addMenu);
    layout->addWidget(m_addButton);

    layout->addStretch();
}

void DocumentMarksPanel::connectSignals() {
    connect(m_loadMarkSetAction, &QAction::triggered, this, &DocumentMarksPanel::onLoadMarkSet);
    connect(m_saveDeleteMarkSetAction, &QAction::triggered, this, &DocumentMarksPanel::onSaveDeleteMarkSet);
    connect(m_updateMarksAction, &QAction::triggered, this, &DocumentMarksPanel::onUpdateMarks);
    connect(m_createMarkFromSelectionAction, &QAction::triggered, this, &DocumentMarksPanel::onCreateMarkFromSelection);
    connect(m_loadCustomVarsAction, &QAction::triggered, this, &DocumentMarksPanel::onLoadCustomVariables);
    connect(m_deleteMarkAction, &QAction::triggered, this, &DocumentMarksPanel::onDeleteMark);
    connect(m_deleteAllMarksAction, &QAction::triggered, this, &DocumentMarksPanel::onDeleteAllMarks);

    for (QAction* act : m_addMarkActions) {
        connect(act, &QAction::triggered, this, [this, act]() {
            onAddMark(act->data().toInt());
        });
    }
}

void DocumentMarksPanel::onLoadMarkSet() {
    if (!m_doc) {
        emit errorOccurred(tr("No document open"));
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Load Mark Set"), QDir::homePath(),
        tr("Mark Set Files (*.pdf *.artplus);;All Files (*)"));
    if (filePath.isEmpty()) return;

    // Prepara página atual
    auto currentPage = m_doc->currentPage();
    if (!currentPage) {
        emit errorOccurred(tr("No current page"));
        return;
    }

    if (!m_processor.prepareMarksCachePage(*currentPage)) {
        emit errorOccurred(QString::fromStdString(m_processor.lastError()));
        return;
    }

    if (m_processor.applyMarksFromSet(filePath.toStdString())) {
        emit markSetLoaded(filePath.toStdString());
        emit markSetApplied(filePath.toStdString());
    } else {
        emit errorOccurred(QString::fromStdString(m_processor.lastError()));
    }
}

void DocumentMarksPanel::onSaveDeleteMarkSet() {
    // Diálogo Save/Delete Mark Set com tabela de mark sets locais
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Save/Delete Mark Set"));
    dialog.resize(500, 400);

    auto layout = new QVBoxLayout(&dialog);

    // Tabela de mark sets
    QTableWidget* table = new QTableWidget(0, 2, &dialog);
    table->setHorizontalHeaderLabels({tr("Name"), tr("Path")});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(table);

    // Campo Name
    auto nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel(tr("Name:"), &dialog));
    QLineEdit* nameEdit = new QLineEdit(&dialog);
    nameLayout->addWidget(nameEdit);
    layout->addLayout(nameLayout);

    // Botões
    auto buttonLayout = new QHBoxLayout();
    QPushButton* saveBtn = new QPushButton(tr("Save"), &dialog);
    QPushButton* cancelBtn = new QPushButton(tr("Cancel"), &dialog);
    QPushButton* deleteBtn = new QPushButton(tr("Delete"), &dialog);
    buttonLayout->addWidget(saveBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelBtn);
    layout->addLayout(buttonLayout);

    // TODO: Popular tabela com mark sets salvos localmente
    // Por enquanto, diálogo vazio

    connect(saveBtn, &QPushButton::clicked, &dialog, [&dialog]() { dialog.accept(); });
    connect(cancelBtn, &QPushButton::clicked, &dialog, [&dialog]() { dialog.reject(); });
    connect(deleteBtn, &QPushButton::clicked, &dialog, []() {
        // TODO: Deletar mark set selecionado
    });

    dialog.exec();
}

void DocumentMarksPanel::onUpdateMarks() {
    // Atualiza marcas na página atual (reaplica mark set)
    if (!m_doc) return;
    auto currentPage = m_doc->currentPage();
    if (!currentPage) return;

    // TODO: Implementar update de marcas existentes
    emit errorOccurred(tr("Update Marks not yet implemented"));
}

void DocumentMarksPanel::onCreateMarkFromSelection() {
    // Cria marca a partir da seleção atual
    if (!m_doc) return;
    auto selected = m_doc->selectedObjects();
    if (selected.empty()) {
        emit errorOccurred(tr("No objects selected"));
        return;
    }

    // TODO: Implementar criação de mark set a partir da seleção
    emit errorOccurred(tr("Create Mark from Selection not yet implemented"));
}

void DocumentMarksPanel::onAddMark(int markType) {
    if (!m_doc) return;
    auto currentPage = m_doc->currentPage();
    if (!currentPage) return;

    // TODO: Implementar adição de cada tipo de marca
    const char* typeNames[] = {
        "Cut Mark", "Bearer Bar", "Dimensions", "External File",
        "Position", "Input File", "Repeat for Grid"
    };
    emit errorOccurred(QString(tr("Add %1 not yet implemented")).arg(typeNames[markType]));
}

void DocumentMarksPanel::onLoadCustomVariables() {
    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Load Custom Variables Database"), QDir::homePath(),
        tr("Database Files (*.db *.sqlite);;All Files (*)"));
    if (filePath.isEmpty()) return;

    // TODO: Implementar carregamento de variáveis customizadas
    emit errorOccurred(tr("Load Custom Variables not yet implemented"));
}

void DocumentMarksPanel::onDeleteMark() {
    if (!m_doc) return;
    auto selected = m_doc->selectedObjects();
    if (selected.empty()) {
        emit errorOccurred(tr("No mark selected"));
        return;
    }

    // TODO: Deletar marca selecionada
    emit errorOccurred(tr("Delete Mark not yet implemented"));
}

void DocumentMarksPanel::onDeleteAllMarks() {
    if (!m_doc) return;
    auto currentPage = m_doc->currentPage();
    if (!currentPage) return;

    // TODO: Deletar todas as marcas da página
    emit errorOccurred(tr("Delete All Marks not yet implemented"));
}

void DocumentMarksPanel::applyMarkSet(const std::string& path) {
    // Método auxiliar para aplicação programática
    if (!m_doc) return;
    auto currentPage = m_doc->currentPage();
    if (!currentPage) return;

    if (!m_processor.prepareMarksCachePage(*currentPage)) {
        emit errorOccurred(QString::fromStdString(m_processor.lastError()));
        return;
    }

    if (m_processor.applyMarksFromSet(path)) {
        emit markSetApplied(path);
    } else {
        emit errorOccurred(QString::fromStdString(m_processor.lastError()));
    }
}

// UiReporter implementation
void DocumentMarksPanel::UiReporter::warnMissingNamedObject(const std::vector<std::string>& names,
                                                            const std::string& markSetName,
                                                            size_t pageIndex) {
    QString msg = tr("Missing named objects in mark set '%1' (page %2): %3")
        .arg(QString::fromStdString(markSetName))
        .arg(pageIndex + 1)
        .arg(QString::fromStdString(names.empty() ? "" : names[0]));
    if (names.size() > 1) {
        msg += tr(" and %1 more").arg(names.size() - 1);
    }
    m_panel->emitError(msg);
}

void DocumentMarksPanel::UiReporter::warnMissingPageBox(const std::string& boxName,
                                                        const std::string& markSetName,
                                                        size_t pageIndex) {
    QString msg = tr("Missing page box '%1' in mark set '%2' (page %3)")
        .arg(QString::fromStdString(boxName))
        .arg(QString::fromStdString(markSetName))
        .arg(pageIndex + 1);
    m_panel->emitError(msg);
}

// Helper para emitir error signal (precisa ser friend ou método público)
void DocumentMarksPanel::emitError(const QString& msg) {
    emit errorOccurred(msg);
}

} // namespace ArtPlus::UI