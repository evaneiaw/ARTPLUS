// src/color_management/icc_profile.cpp
// F-008 — leitura do cabeçalho ICC (ICC.1:2010 §7.2) e descrição do perfil.
#include "icc_profile.h"

#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>

#include <cstring>
#include <vector>

namespace artplus::color {
namespace {

quint32 readU32BE(const QByteArray& d, int offset) {
    if (offset < 0 || offset + 4 > d.size()) {
        return 0;
    }
    const auto* p = reinterpret_cast<const unsigned char*>(d.constData() + offset);
    return (static_cast<quint32>(p[0]) << 24) | (static_cast<quint32>(p[1]) << 16) |
           (static_cast<quint32>(p[2]) << 8) | static_cast<quint32>(p[3]);
}

QByteArray tagSignature(const QByteArray& d, int offset) {
    if (offset < 0 || offset + 4 > d.size()) {
        return {};
    }
    return d.mid(offset, 4);
}

// 'desc' (ICC v2) e 'mluc' (ICC v4) — os dois tipos de descrição observados.
QString descriptionFromTag(const QByteArray& d, int tagOffset, int tagSize) {
    if (tagOffset <= 0 || tagSize <= 8 || tagOffset + tagSize > d.size()) {
        return {};
    }
    const QByteArray type = tagSignature(d, tagOffset);

    if (type == "desc") {
        // type(4) reserved(4) asciiCount(4) ascii...
        const quint32 count = readU32BE(d, tagOffset + 8);
        const int available = tagSize - 12;
        const int len = qMin<int>(static_cast<int>(count), available);
        if (len <= 1) {
            return {};
        }
        QByteArray text = d.mid(tagOffset + 12, len - 1); // sem o NUL final
        return QString::fromLatin1(text).trimmed();
    }

    if (type == "mluc") {
        // type(4) reserved(4) recordCount(4) recordSize(4) records...
        const quint32 recordCount = readU32BE(d, tagOffset + 8);
        const quint32 recordSize = readU32BE(d, tagOffset + 12);
        if (recordCount == 0 || recordSize < 12) {
            return {};
        }
        QString fallback;
        for (quint32 i = 0; i < recordCount; ++i) {
            const int rec = tagOffset + 16 + static_cast<int>(i) * static_cast<int>(recordSize);
            if (rec + 12 > tagOffset + tagSize) {
                break;
            }
            const QByteArray language = tagSignature(d, rec);
            const quint32 length = readU32BE(d, rec + 4);
            const quint32 offset = readU32BE(d, rec + 8);
            const int begin = tagOffset + static_cast<int>(offset);
            if (length < 2 || begin < 0 || begin + static_cast<int>(length) > tagOffset + tagSize) {
                continue;
            }
            QByteArray utf16 = d.mid(begin, static_cast<int>(length));
            if (utf16.size() % 2 != 0) {
                utf16.chop(1);
            }
            // UTF-16 big-endian
            QString text;
            text.reserve(utf16.size() / 2);
            for (int k = 0; k + 1 < utf16.size(); k += 2) {
                const auto hi = static_cast<ushort>(static_cast<unsigned char>(utf16[k]));
                const auto lo = static_cast<ushort>(static_cast<unsigned char>(utf16[k + 1]));
                text.append(QChar(static_cast<ushort>((hi << 8) | lo)));
            }
            text = text.trimmed();
            if (text.isEmpty()) {
                continue;
            }
            if (fallback.isEmpty()) {
                fallback = text;
            }
            if (language == "en") {
                return text;
            }
        }
        return fallback;
    }

    return {};
}

} // namespace

ICCProfile::ICCProfile() = default;

ICCProfile::ICCProfile(std::istream& stream) {
    QByteArray buffer;
    if (stream) {
        char chunk[4096];
        while (stream.read(chunk, sizeof(chunk)) || stream.gcount() > 0) {
            buffer.append(chunk, static_cast<int>(stream.gcount()));
            if (!stream) {
                break;
            }
        }
    }
    loadFromData(buffer);
}

bool ICCProfile::loadFromData(const QByteArray& data) {
    m_data = data;
    m_description.clear();
    m_md5Hash.clear();
    m_version = 0x0210;
    m_colorSpaceType = ColorType::CMYK;
    m_valid = false;

    if (m_data.size() < kHeaderSize) {
        return false;
    }

    parseHeader();
    if (!m_valid) {
        m_data.clear();
        return false;
    }

    m_md5Hash = QString::fromLatin1(
        QCryptographicHash::hash(m_data, QCryptographicHash::Md5).toHex());
    return true;
}

bool ICCProfile::loadFromFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    const QByteArray data = file.readAll();
    if (!loadFromData(data)) {
        return false;
    }
    if (m_description.isEmpty()) {
        m_description = QFileInfo(path).completeBaseName();
    }
    return true;
}

void ICCProfile::parseHeader() {
    // Assinatura 'acsp' no offset 36 identifica um perfil ICC (ICC.1:2010 §7.2.10).
    if (tagSignature(m_data, 36) != "acsp") {
        return;
    }

    const quint32 declaredSize = readU32BE(m_data, 0);
    if (declaredSize != 0 && static_cast<int>(declaredSize) > m_data.size()) {
        return;
    }

    const quint32 rawVersion = readU32BE(m_data, 8);
    m_version = static_cast<int>(((rawVersion >> 24) & 0xFF) << 8 | ((rawVersion >> 20) & 0x0F));

    const QByteArray space = tagSignature(m_data, 16);
    if (space == "CMYK") {
        m_colorSpaceType = ColorType::CMYK;
    } else if (space == "RGB ") {
        m_colorSpaceType = ColorType::RGB;
    } else if (space == "GRAY") {
        m_colorSpaceType = ColorType::Gray;
    } else if (space == "Lab ") {
        m_colorSpaceType = ColorType::Lab;
    } else if (space == "XYZ ") {
        m_colorSpaceType = ColorType::Lab; // XYZ não tem ColorType próprio na spec §4 R8
    } else if (space == "nmcl") {
        m_colorSpaceType = ColorType::DeviceN;
    } else if (space.size() == 4 && space.endsWith("CLR")) {
        m_colorSpaceType = ColorType::MultiChannel;
    } else {
        return; // espaço de cor não suportado pela spec
    }

    m_valid = true;

    // Tabela de tags: count(4) em 128, entradas de 12 bytes.
    if (m_data.size() < 132) {
        return;
    }
    const quint32 tagCount = readU32BE(m_data, kHeaderSize);
    const int tableEnd = kHeaderSize + 4 + static_cast<int>(tagCount) * 12;
    if (tagCount == 0 || tableEnd > m_data.size()) {
        return;
    }
    for (quint32 i = 0; i < tagCount; ++i) {
        const int entry = kHeaderSize + 4 + static_cast<int>(i) * 12;
        const QByteArray sig = tagSignature(m_data, entry);
        if (sig != "desc" && sig != "mluc") {
            continue;
        }
        const int offset = static_cast<int>(readU32BE(m_data, entry + 4));
        const int size = static_cast<int>(readU32BE(m_data, entry + 8));
        const QString text = descriptionFromTag(m_data, offset, size);
        if (!text.isEmpty()) {
            m_description = text;
            return;
        }
    }
}

QByteArray ICCProfile::data() const {
    return m_data;
}

QString ICCProfile::description() const {
    return m_description;
}

void ICCProfile::setDescription(const QString& desc) {
    m_description = desc;
}

QString ICCProfile::md5Hash() const {
    return m_md5Hash;
}

void ICCProfile::setMd5Hash(const QString& hash) {
    m_md5Hash = hash;
}

int ICCProfile::version() const {
    return m_version;
}

void ICCProfile::setVersion(int ver) {
    m_version = ver;
}

ColorType ICCProfile::colorSpaceType() const {
    return m_colorSpaceType;
}

void ICCProfile::setColorSpaceType(ColorType ct) {
    m_colorSpaceType = ct;
}

bool ICCProfile::isValid() const {
    return m_valid;
}

} // namespace artplus::color
