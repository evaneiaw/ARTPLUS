#include "file_dispatcher.h"

#include "artplus_open_handler.h"
#include "../pdf/pdf_open_handler.h"

#include <QFile>
#include <QFileInfo>

#include <utility>

namespace ArtPlus {
namespace {

constexpr const char* kMimePdf = "application/pdf";
constexpr const char* kMimeArtPlus = "application/vnd.artplus.document";
// Extensões enumeradas no filtro de F-005 cujos MIMEs reais não foram medidos
// (F-005 §8.3). São constantes internas do clone, não uma afirmação sobre o Esko.
constexpr const char* kMimePdpdla = "application/vnd.artplus.pdpdla";
constexpr const char* kMimeAp = "application/vnd.artplus.ap";
constexpr const char* kMimeArt = "application/vnd.artplus.art";

// GHIDRA-Document-0x180215D50 / 0x180216380: guarda de abertura.Além de marcar
// o caminho em abertura, detecta reentrância para o mesmo arquivo.
class OpeningFilesGuard {
public:
    OpeningFilesGuard(std::set<QString>& opening, const QString& path)
        : m_opening(opening), m_path(path), m_inserted(opening.insert(path).second) {}

    ~OpeningFilesGuard() {
        if (m_inserted) m_opening.erase(m_path);
    }

    bool inserted() const { return m_inserted; }

    OpeningFilesGuard(const OpeningFilesGuard&) = delete;
    OpeningFilesGuard& operator=(const OpeningFilesGuard&) = delete;

private:
    std::set<QString>& m_opening;
    QString m_path;
    bool m_inserted;
};

} // namespace

QString FileDispatcher::mimeTypeForPath(const QString& filePath) {
    const QString suffix = QFileInfo(filePath).suffix().toLower();
    if (suffix == QStringLiteral("pdf")) return QString::fromLatin1(kMimePdf);
    if (suffix == QStringLiteral("artplus")) return QString::fromLatin1(kMimeArtPlus);
    if (suffix == QStringLiteral("pdpdla")) return QString::fromLatin1(kMimePdpdla);
    if (suffix == QStringLiteral("ap")) return QString::fromLatin1(kMimeAp);
    if (suffix == QStringLiteral("art")) return QString::fromLatin1(kMimeArt);
    return QStringLiteral("application/octet-stream");
}

bool FileDispatcher::registerHandler(const QString& mimeType,
                                     std::unique_ptr<OpenFileHandler> handler) {
    if (m_handlers.find(mimeType) != m_handlers.end()) {
        return false; // handler recebido é destruído (R3)
    }
    m_handlers.emplace(mimeType, std::move(handler));
    return true;
}

bool FileDispatcher::hasHandler(const QString& mimeType) const {
    return m_handlers.find(mimeType) != m_handlers.end();
}

void FileDispatcher::registerBuiltinHandlers(FileDispatcher& dispatcher) {
    dispatcher.registerHandler(QString::fromLatin1(kMimePdf),
                               std::make_unique<PdfOpenHandler>());
    dispatcher.registerHandler(QString::fromLatin1(kMimeArtPlus),
                               std::make_unique<ArtPlusDocumentHandler>());
}

OpenResult FileDispatcher::open(const QString& filePath) const {
    // F-005 §2 pré-condição 1 / R2 passo 1: status(path) < 2 → código 0.
    const QFileInfo info(filePath);
    if (!info.exists()) {
        return OpenResult::failure(OpenError::FileNotFound, filePath);
    }
    QFile probe(filePath);
    if (!probe.open(QIODevice::ReadOnly)) {
        return OpenResult::failure(OpenError::FileAccessDenied, filePath);
    }
    probe.close();

    // R2 passos 2–4: MIME → mapa; sem entrada, código 7 (refinado para
    // NoHandlerForMime no clone, conforme ADR-014).
    const QString mime = mimeTypeForPath(filePath);
    const auto it = m_handlers.find(mime);
    if (it == m_handlers.end()) {
        return OpenResult::failure(OpenError::NoHandlerForMime,
                                   mime + QStringLiteral(" | ") + filePath);
    }

    const OpeningFilesGuard guard(m_openingFiles, filePath);
    if (!guard.inserted()) {
        return OpenResult::failure(OpenError::Unknown,
                                   QStringLiteral("Reentrant open | ") + filePath);
    }
    return it->second->open(filePath);
}

} // namespace ArtPlus
