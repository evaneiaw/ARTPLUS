#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QTimer>
#include "../color_management/color_manipulation_layer.h"
#include "../ui/main_window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addOption(QCommandLineOption("open", "Open document on startup", "path"));
    parser.addOption(QCommandLineOption("page", "Switch to page N (1-based) after opening", "n"));
    parser.addOption(QCommandLineOption("quit-after", "Quit after N seconds (for smoke testing)", "sec"));
    parser.process(app);

    // F-008 R1: inicialização do subsistema de cor antes da primeira janela.
    if (!artplus::color::ColorManipulationLayer::initialize()) {
        qCritical("Color Management indisponível: %s",
                  "No Color Management support available");
    }

    ArtPlus::ArtPlusMainWindow window;
    window.show();

    if (parser.isSet("open")) {
        QString path = parser.value("open");
        if (!window.openDocumentPath(path)) {
            qCritical("openDocumentPath failed for: %s", qPrintable(path));
            return 2;
        }
        if (parser.isSet("page")) {
            bool ok = false;
            int page = parser.value("page").toInt(&ok);
            if (ok && page >= 1) window.viewPage(page - 1);
        }
    }
    if (parser.isSet("quit-after")) {
        int sec = parser.value("quit-after").toInt();
        QTimer::singleShot(sec * 1000, &app, &QApplication::quit);
    }
    return app.exec();
}
