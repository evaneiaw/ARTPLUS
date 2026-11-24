#pragma once

#include "../document/file_dispatcher.h"

namespace ArtPlus {

// F-005 R5/R6: usa PdfDocument + PdfImporter existentes e devolve OpenResult
// tipado; falha de leitura/página é FileInvalid (ou WrongPassword se /Encrypt).
class PdfOpenHandler final : public OpenFileHandler {
public:
    OpenResult open(const QString& filePath) const override;
};

} // namespace ArtPlus
