#include "artplus_open_handler.h"

#include "document_serializer.h"

#include <memory>

namespace ArtPlus {

OpenResult ArtPlusDocumentHandler::open(const QString& filePath) const {
    auto document = std::make_unique<Document>();
    if (!DocumentSerializer::load(filePath, *document)) {
        return OpenResult::failure(OpenError::FileInvalid, filePath);
    }
    return OpenResult::success(std::move(document), filePath);
}

} // namespace ArtPlus
