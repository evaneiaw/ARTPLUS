#pragma once

#include <QByteArray>
#include <QString>
#include <QColor>
#include <QMap>
#include <memory>

namespace ArtPlus {

class ColorProfile {
public:
    enum class Type {
        Unknown = 0,
        Input = 1,
        Display = 2,
        Output = 3,
        Link = 4,
        Abstract = 5,
        ColorSpace = 6
    };
    
    enum class ColorSpace {
        Unknown = 0,
        Gray = 1,
        RGB = 2,
        CMYK = 3,
        Lab = 4,
        XYZ = 5,
        NamedColor = 6,
        HiFiColor = 7,
        Multichannel = 8
    };
    
    enum class RenderingIntent {
        Perceptual = 0,
        RelativeColorimetric = 1,
        Saturation = 2,
        AbsoluteColorimetric = 3
    };
    
    struct Header {
        uint32_t size;
        uint32_t cmmType;
        uint32_t version;
        Type deviceClass;
        ColorSpace colorSpace;
        ColorSpace pcs;
        uint64_t dateTime;
        uint32_t signature; // 'acsp'
        uint32_t platform;
        uint32_t flags;
        uint32_t manufacturer;
        uint32_t model;
        uint64_t attributes;
        uint32_t renderingIntent;
        float illuminant[3]; // XYZ
        uint32_t creator;
        uint32_t reserved[44];
    };
    
    struct Tag {
        uint32_t signature;
        uint32_t offset;
        uint32_t size;
    };
    
    ColorProfile();
    explicit ColorProfile(const QByteArray& data);
    ~ColorProfile();
    
    bool isValid() const { return !m_data.isEmpty(); }
    bool loadFromData(const QByteArray& data);
    bool loadFromFile(const QString& path);
    QByteArray saveToData() const;
    bool saveToFile(const QString& path) const;
    
    const Header& header() const { return m_header; }
    Type type() const { return m_header.deviceClass; }
    ColorSpace colorSpace() const { return m_header.colorSpace; }
    ColorSpace pcs() const { return m_header.pcs; }
    QString name() const;
    QString description() const;
    QString manufacturer() const;
    QString model() const;
    QString copyright() const;
    
    // Tags
    bool hasTag(uint32_t signature) const;
    QByteArray tagData(uint32_t signature) const;
    QStringList tagNames() const;
    
    // Color conversion (requires external transform engine)
    bool canConvertFrom(ColorSpace space) const;
    bool canConvertTo(ColorSpace space) const;
    
    // Viewing conditions
    float illuminantX() const { return m_header.illuminant[0]; }
    float illuminantY() const { return m_header.illuminant[1]; }
    float illuminantZ() const { return m_header.illuminant[2]; }
    
private:
    bool parseHeader();
    bool parseTags();
    void readHeader(const QByteArray& data);
    void readTags(const QByteArray& data);
    
    QByteArray m_data;
    Header m_header;
    QMap<uint32_t, Tag> m_tags;
};

} // namespace ArtPlus