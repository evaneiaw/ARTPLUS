#pragma once

#include "file_dispatcher.h"

namespace ArtPlus {

// Exceção declarada do clone: `.artplus` é JSON lido por DocumentSerializer e
// não tem contraparte no ArtPro+ v24.03.10017 (ADR-014, "Exceção explícita").
class ArtPlusDocumentHandler final : public OpenFileHandler {
public:
    OpenResult open(const QString& filePath) const override;
};

} // namespace ArtPlus
