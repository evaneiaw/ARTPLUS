#pragma once

#include "open_error.h"

#include <QString>
#include <map>
#include <memory>
#include <set>

namespace ArtPlus {

// F-005 R2: slot 1 da vtable de OpenFileHandler no binário. Um handler por MIME;
// nenhum handler fictício para formatos não exercitados (ADR-014, alternativa 3).
class OpenFileHandler {
public:
    virtual ~OpenFileHandler() = default;
    virtual OpenResult open(const QString& filePath) const = 0;
};

// F-005 R2/R3 / GHIDRA-Document-0x1802160B0: o despacho é feito por MIME, nunca
// pela ação de menu escolhida. A instância pertence à janela principal (R3).
class FileDispatcher {
public:
    static QString mimeTypeForPath(const QString& filePath);
    static void registerBuiltinHandlers(FileDispatcher& dispatcher);

    // Chave duplicada é ignorada e o handler recebido é descartado (R3).
    bool registerHandler(const QString& mimeType, std::unique_ptr<OpenFileHandler> handler);
    bool hasHandler(const QString& mimeType) const;
    OpenResult open(const QString& filePath) const;

private:
    std::map<QString, std::unique_ptr<OpenFileHandler>> m_handlers;
    // Equivalente às listas AddToOpeningFiles/RemoveFromOpeningFiles do binário.
    mutable std::set<QString> m_openingFiles;
};

} // namespace ArtPlus
