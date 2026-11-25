#include "markset_pdf_loader.h"
#include "pdf_importer.h"
#include "../document/document_model.h"
#include "../document/document_serializer.h"
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace ArtPlus::PDF {

MarkSetPdfLoader::Result MarkSetPdfLoader::load(const std::string& filePath) {
    Result result;
    const QString path = QString::fromStdString(filePath);
    const QFileInfo info(path);

    if (!info.exists() || !info.isFile()) {
        result.error = Prepress::MarkSetError::MarkSetFileDoesNotExist;
        result.errorDetail = "MarkSetFileDoesNotExist: file does not exist";
        return result;
    }

    PdfDocument pdf;
    if (!pdf.open(path)) {
        result.error = Prepress::MarkSetError::CannotOpenMarkSetFile;
        result.errorDetail = "CannotOpenMarkSetFile: failed to open PDF";
        return result;
    }

    // Extrai metadados do mark set
    if (!extractMarkSetMetadata(pdf, result.info)) {
        // Não é um mark set válido, mas pode ser PDF genérico
        // Tenta importar como PDF normal
    }

    // Verifica InputFileMark
    if (hasInputFileMark(pdf)) {
        result.info.hasInputFileMark = true;
        result.error = Prepress::MarkSetError::MarkSetContainsInputFileMark;
        result.errorDetail = "MarkSetContainsInputFileMark: mark set contains InputFileMark";
        // Não retorna erro fatal, apenas aviso
    }

    // Importa primeira página
    result.document = importFirstPage(pdf);
    if (!result.document || result.document->pageOrder().empty()) {
        result.error = Prepress::MarkSetError::EmptyFirstPage;
        result.errorDetail = "EmptyFirstPage: no pages imported";
        return result;
    }

    result.info.filePath = filePath;
    result.info.displayName = info.baseName().toStdString();
    result.info.pageOrder = result.document->pageOrder();
    result.success = true;
    return result;
}

bool MarkSetPdfLoader::isMarkSetPdf(const std::string& filePath) {
    PdfDocument pdf;
    if (!pdf.open(QString::fromStdString(filePath))) return false;

    // Verifica metadata.DocumentMarks no catálogo ou info dict
    // Implementação simplificada
    return true; // Por enquanto assume que qualquer PDF pode ser mark set
}

bool MarkSetPdfLoader::extractMarkSetMetadata(const PdfDocument& pdf, Prepress::MarkSetInfo& info) {
    // Tenta ler metadata.DocumentMarks do catálogo PDF
    // Em PDF real, isso estaria no /Metadata stream ou em /Info
    // Implementação simplificada: extrai caixas de página da primeira página
    if (pdf.pageCount() > 0) {
        auto geom = pdf.pageGeometry(0);
        info.pageBoxes.resize(5);
        info.pageBoxes[0] = ArtPlus::PageBox{"MediaBox", QRectF(geom.mediaBox[0], geom.mediaBox[1], geom.mediaBox[2] - geom.mediaBox[0], geom.mediaBox[3] - geom.mediaBox[1])};
        info.pageBoxes[1] = ArtPlus::PageBox{"CropBox", QRectF(geom.cropBox[0], geom.cropBox[1], geom.cropBox[2] - geom.cropBox[0], geom.cropBox[3] - geom.cropBox[1])};
        info.pageBoxes[2] = ArtPlus::PageBox{"BleedBox", QRectF(geom.bleedBox[0], geom.bleedBox[1], geom.bleedBox[2] - geom.bleedBox[0], geom.bleedBox[3] - geom.bleedBox[1])};
        info.pageBoxes[3] = ArtPlus::PageBox{"TrimBox", QRectF(geom.trimBox[0], geom.trimBox[1], geom.trimBox[2] - geom.trimBox[0], geom.trimBox[3] - geom.trimBox[1])};
        info.pageBoxes[4] = ArtPlus::PageBox{"ArtBox", QRectF(geom.artBox[0], geom.artBox[1], geom.artBox[2] - geom.artBox[0], geom.artBox[3] - geom.artBox[1])};
    }
    return true;
}

std::unique_ptr<Document> MarkSetPdfLoader::importFirstPage(const PdfDocument& pdf) {
    auto doc = std::make_unique<Document>();
    PdfImportResult imported = PdfImporter::import(pdf, *doc);
    if (!imported.ok) {
        return nullptr;
    }
    return doc;
}

bool MarkSetPdfLoader::hasInputFileMark(const PdfDocument& pdf) {
    // Heurística conservadora: procura a string literal "InputFileMark" nos streams
    // de conteúdo das páginas e nos valores de dicionário do PDF. Não inventa
    // estrutura não comprovada; se não encontrar, assume ausência.
    for (int i = 0; i < pdf.pageCount(); ++i) {
        const QByteArray contents = pdf.pageContents(i);
        if (contents.contains("InputFileMark")) return true;
    }
    const auto& objects = pdf.allObjects();
    for (const auto& [id, obj] : objects) {
        // O operador<< ou toString() está disponível via QDebug ou método próprio;
        // usar a forma de depuração manual com os campos conhecidos.
        if (obj.value.isString() && obj.value.stringValue().contains("InputFileMark")) return true;
        if (obj.value.isName() && obj.value.nameValue().contains("InputFileMark")) return true;
    }
    return false;
}

} // namespace ArtPlus::PDF