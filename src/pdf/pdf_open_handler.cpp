#include "pdf_open_handler.h"

#include "pdf_document.h"
#include "pdf_importer.h"

#include <QFile>
#include <QFileInfo>

#include <memory>

namespace ArtPlus {

OpenResult PdfOpenHandler::open(const QString& filePath) const {
    // O dispatcher já classifica ausência/acesso; a checagem também vale quando o
    // handler é chamado diretamente (ADR-014, risco de classificação).
    const QFileInfo info(filePath);
    if (!info.exists()) {
        return OpenResult::failure(OpenError::FileNotFound, filePath);
    }
    QFile probe(filePath);
    if (!probe.open(QIODevice::ReadOnly)) {
        return OpenResult::failure(OpenError::FileAccessDenied, filePath);
    }
    probe.close();

    PDF::PdfDocument pdf;
    if (!pdf.open(filePath)) {
        // F-005 §5: /Encrypt é o sinal local disponível; não há captura GUI do erro.
        const OpenError error = pdf.isEncrypted() ? OpenError::WrongPassword
                                                  : OpenError::FileInvalid;
        return OpenResult::failure(error, filePath);
    }

    // R6 / GHIDRA-Document-0x180093D60: documento sem páginas → código 2.
    if (pdf.pageCount() <= 0) {
        return OpenResult::failure(OpenError::FileInvalid, filePath);
    }

    auto document = std::make_unique<Document>();
    const PdfImportResult imported = PdfImporter::import(pdf, *document);
    if (!imported.ok || imported.pagesImported <= 0) {
        return OpenResult::failure(OpenError::FileInvalid,
                                   filePath + QStringLiteral(" | ") + imported.error);
    }
    return OpenResult::success(std::move(document), filePath);
}

} // namespace ArtPlus
