#pragma once

#include "document_model.h"

#include <QFileInfo>
#include <QString>
#include <memory>
#include <utility>

namespace ArtPlus {

// F-005 §5 / GHIDRA-Document-0x1800A0EC0: códigos de abertura mapeados para nomes
// simbólicos. `NoHandlerForMime` é o refinamento do clone para o código 7 do binário
// (ADR-014, "Tabela de mensagens simbólicas").
enum class OpenError {
    None,
    FileNotFound,
    FileAccessDenied,
    FileInvalid,
    WrongPassword,
    NoHandlerForMime,
    Unknown
};

inline QString openErrorMessage(OpenError error) {
    switch (error) {
        case OpenError::None:             return QString();
        case OpenError::FileNotFound:     return QStringLiteral("ERROR_FILE_NOT_FOUND");
        case OpenError::FileAccessDenied: return QStringLiteral("ERROR_FILE_ACCESS_DENIED");
        case OpenError::FileInvalid:      return QStringLiteral("ERROR_FILE_INVALID");
        case OpenError::WrongPassword:    return QStringLiteral("ERROR_WRONG_PASSWORD");
        case OpenError::NoHandlerForMime: return QStringLiteral("ERROR_FILE_NO_HANDLER_FOR_MIME");
        case OpenError::Unknown:          return QStringLiteral("ERROR_FILE_UNKNOWN");
    }
    return QStringLiteral("ERROR_FILE_UNKNOWN");
}

// Retorno tipado da abertura (ADR-014): nenhuma exceção C++ atravessa slots Qt.
struct OpenResult {
    std::unique_ptr<Document> document;
    OpenError error = OpenError::Unknown;
    QString detail;   // caminho/diagnóstico, sem localização
    QString title;    // = QFileInfo(filePath).fileName() (R4)

    static OpenResult success(std::unique_ptr<Document> doc, const QString& filePath) {
        OpenResult result;
        result.error = OpenError::None;
        result.detail = filePath;
        result.title = QFileInfo(filePath).fileName();
        result.document = std::move(doc);
        if (result.document) {
            // R4 / GHIDRA-Document-0x18009C080 (SetTitle): título inicial = nome do arquivo.
            result.document->setTitle(result.title);
        }
        return result;
    }

    static OpenResult failure(OpenError error, const QString& detail) {
        OpenResult result;
        result.error = error;
        result.detail = detail;
        return result;
    }
};

} // namespace ArtPlus
