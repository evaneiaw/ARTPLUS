#ifndef MARKSET_PDF_LOADER_H
#define MARKSET_PDF_LOADER_H

#include "../prepress/markset_processor.h"
#include "../document/document_model.h"
#include "pdf_document.h"
#include <memory>
#include <string>
#include <vector>

namespace ArtPlus::PDF {

class MarkSetPdfLoader {
public:
    struct Result {
        bool success = false;
        std::unique_ptr<Document> document;
        Prepress::MarkSetError error = Prepress::MarkSetError::None;
        std::string errorDetail;
        Prepress::MarkSetInfo info;
    };

    // Carrega PDF de mark set, extrai metadata.DocumentMarks se presente
    static Result load(const std::string& filePath);

    // Verifica se PDF contém metadata.DocumentMarks (marca de mark set válido)
    static bool isMarkSetPdf(const std::string& filePath);

private:
    static bool extractMarkSetMetadata(const PdfDocument& pdf, Prepress::MarkSetInfo& info);
    static std::unique_ptr<Document> importFirstPage(const PdfDocument& pdf);
    static bool hasInputFileMark(const PdfDocument& pdf);
};

} // namespace ArtPlus::Pdf

#endif // MARKSET_PDF_LOADER_H