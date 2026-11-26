#include "gravure_exporter.h"

#include <QDebug>
#include <QFile>
#include <QImage>
#include <QDataStream>
#include <QPainter>
#include <QPen>
#include <filesystem>

#include <cstdint>
#include <vector>

namespace ArtPlus {
namespace {

// Escritor TIFF mínimo (grayscale, sem compressão) inspirado no padrão
// `TIFFWriteEncodedStrip` observado em GHIDRA-DocumentEdit-0x180041d20.
// Evita dependência de libtiff externa e de plugin de TIFF do Qt.
void appendU16(QByteArray& out, quint16 v) {
    out.append(static_cast<char>(v & 0xFF));
    out.append(static_cast<char>((v >> 8) & 0xFF));
}
void appendU32(QByteArray& out, quint32 v) {
    out.append(static_cast<char>(v & 0xFF));
    out.append(static_cast<char>((v >> 8) & 0xFF));
    out.append(static_cast<char>((v >> 16) & 0xFF));
    out.append(static_cast<char>((v >> 24) & 0xFF));
}

QByteArray encodeGrayscaleTiff(const QImage& image, int resolutionDpi) {
    QByteArray out;
    // Cabeçalho TIFF little-endian
    out.append("II");
    appendU16(out, 42);
    appendU32(out, 8); // offset do IFD

    const int width = image.width();
    const int height = image.height();
    const quint32 rowsPerStrip = static_cast<quint32>(height > 0 ? height : 1);

    // 11 entradas no IFD
    const quint16 entryCount = 11;
    const quint32 ifdOffset = 8;
    const quint32 entriesOffset = ifdOffset + 2;
    const quint32 valuesOffset = entriesOffset + entryCount * 12 + 4; // +4 = próximo IFD
    const quint32 stripOffset = valuesOffset + 16; // 8 bytes para XRes + 8 para YRes

    // Pré-calcular tamanho dos dados (1 byte por pixel, grayscale 8-bit)
    QByteArray strip;
    strip.reserve(width * height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            strip.append(static_cast<char>(qGray(image.pixel(x, y))));
        }
    }

    auto addEntry = [&out](quint16 tag, quint16 type, quint32 count, quint32 value) {
        appendU16(out, tag);
        appendU16(out, type);
        appendU32(out, count);
        appendU32(out, value);
    };

    appendU16(out, entryCount);
    addEntry(256, 3, 1, static_cast<quint32>(width));                  // ImageWidth (SHORT)
    addEntry(257, 3, 1, static_cast<quint32>(height));                 // ImageLength
    addEntry(258, 3, 1, 8);                                            // BitsPerSample
    addEntry(259, 3, 1, 1);                                            // Compression = none
    addEntry(262, 3, 1, 1);                                            // Photometric = BlackIsZero
    addEntry(273, 4, 1, stripOffset);                                  // StripOffsets (LONG)
    addEntry(277, 3, 1, 1);                                            // SamplesPerPixel
    addEntry(278, 4, 1, rowsPerStrip);                                 // RowsPerStrip
    addEntry(279, 4, 1, static_cast<quint32>(strip.size()));           // StripByteCounts
    addEntry(282, 5, 1, valuesOffset);                                 // XResolution (RATIONAL)
    addEntry(283, 5, 1, valuesOffset + 8);                             // YResolution
    appendU32(out, 0); // próximo IFD = none

    // Valores racionais de resolução
    appendU32(out, static_cast<quint32>(resolutionDpi > 0 ? resolutionDpi : 300));
    appendU32(out, 1);
    appendU32(out, static_cast<quint32>(resolutionDpi > 0 ? resolutionDpi : 300));
    appendU32(out, 1);

    // Dados dos strips
    out.append(strip);
    return out;
}

} // namespace

GravureExporter::GravureExporter(Document& doc) : m_doc(doc) {}

bool GravureExporter::exportTIFF(const QString& outputPath,
                                 const ExportedGravureTIFFProperties& properties,
                                 std::function<void(int percent)> progressCallback)
{
    // R1 — ExportGravureTIFF (GHIDRA-DocumentEdit-0x180041d20)
    // Pipeline completo no binário: ambiente ArtSc, matriz de transformação, retângulo interno,
    // coleta/raster/resample, escrita TIFFWriteEncodedStrip, progresso e propriedades.
    // Confiança media — UI/entrada exata não comprovada (spec "Em aberto").
    // Implementamos o núcleo raster→TIFF strips sobre o modelo ArtPlus; os detalhes de
    // resample/ScanConverter/plane-interleaving de gravura ficam marcados como TODO(F-012).

    std::vector<ObjectId> selectedIds = m_doc.selectedObjects();
    if (selectedIds.empty()) {
        selectedIds = m_doc.objectIds();
    }

    // Sem objetos de gravura: spec §7 permite TIFF vazio ou erro.
    if (selectedIds.empty()) {
        qWarning() << "GravureExporter: nenhum objeto para exportar";
        return false;
    }

    const double dpi = properties.resolutionDpi > 0 ? properties.resolutionDpi : 300;

    // Rasterização simples no modelo (TODO(F-012): substituir por ArtSc ScanConverter/Resample
    // quando houver CAP comportamental confirmando parâmetros de resample e planar interleaving).
    QRectF bounds;
    for (ObjectId id : selectedIds) {
        auto obj = m_doc.object(id);
        if (obj) bounds = bounds.united(obj->boundingBox());
    }
    if (bounds.isEmpty()) bounds = QRectF(0, 0, 1, 1);

    const int width = qMax(1, static_cast<int>(bounds.width() * dpi / 72.0));
    const int height = qMax(1, static_cast<int>(bounds.height() * dpi / 72.0));
    QImage image(width, height, QImage::Format_Grayscale8);
    image.fill(255); // branco = fundo

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(0, 0, 0)));

    int processed = 0;
    const int total = static_cast<int>(selectedIds.size());
    for (ObjectId id : selectedIds) {
        auto obj = m_doc.object(id);
        if (obj) {
            const QRectF b = obj->boundingBox();
            const QRectF mapped(
                (b.left() - bounds.left()) * dpi / 72.0,
                (b.top() - bounds.top()) * dpi / 72.0,
                b.width() * dpi / 72.0,
                b.height() * dpi / 72.0);
            painter.drawRect(mapped);
        }
        ++processed;
        if (progressCallback && properties.progressEnabled) {
            progressCallback((processed * 100) / total);
        }
    }
    painter.end();

    const QByteArray tiff = encodeGrayscaleTiff(image, properties.resolutionDpi);

    QFile file(outputPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << "GravureExporter: falha ao abrir" << outputPath;
        return false;
    }
    const qint64 written = file.write(tiff);
    file.close();
    if (written != tiff.size()) {
        qCritical() << "GravureExporter: escrita incompleta em" << outputPath;
        return false;
    }

    qDebug() << "GravureExporter: TIFF exportado" << outputPath
             << width << "x" << height << "px @ " << properties.resolutionDpi << "dpi";
    return true;
}

ExportedGravureTIFFProperties GravureExporter::defaultProperties() const
{
    return ExportedGravureTIFFProperties{};
}

} // namespace ArtPlus