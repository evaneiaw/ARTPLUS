#pragma once
#include <QString>
#include <QByteArray>
#include <istream>

namespace artplus::color {

enum class ColorType : int { CMYK=0, RGB=1, Lab=2, Gray=3, Spot=4, DeviceN=5, MultiChannel=6 };
enum class CategoryType : int { Default=0, Override=1, DeviceLink=2, Proof=3 };
enum class RenderingIntent : int { Perceptual=0, RelativeColorimetric=1, Saturation=2, AbsoluteColorimetric=3 };

class ICCProfile {
public:
    ICCProfile();
    explicit ICCProfile(std::istream& stream);
    ~ICCProfile() = default;

    QString description() const;
    void setDescription(const QString& desc);

    QString md5Hash() const;
    void setMd5Hash(const QString& hash);

    int version() const;
    void setVersion(int ver);

    ColorType colorSpaceType() const;
    void setColorSpaceType(ColorType ct);

    bool isValid() const;

private:
    QString m_description;
    QString m_md5Hash;
    int m_version = 0x0210; // Default ICC v2.1
    ColorType m_colorSpaceType;
    bool m_valid = false;
};

} // namespace artplus::color
