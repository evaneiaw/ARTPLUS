// src/color_management/icc_profile.h
// F-008 — wrapper de GCICCProfile.
//
// O perfil é considerado válido somente quando o cabeçalho ICC foi lido e
// contém a assinatura 'acsp' (ICC.1:2010 §7.2). Um ICCProfile recém-construído
// é inválido: não existe "perfil default" sem fonte (ver auditoria F-008 §7).
#pragma once
#include <QByteArray>
#include <QString>
#include <istream>

namespace artplus::color {

enum class ColorType : int { CMYK=0, RGB=1, Lab=2, Gray=3, Spot=4, DeviceN=5, MultiChannel=6 };
enum class CategoryType : int { Default=0, Override=1, DeviceLink=2, Proof=3 };
enum class RenderingIntent : int { Perceptual=0, RelativeColorimetric=1, Saturation=2, AbsoluteColorimetric=3 };

class ICCProfile {
public:
    // Tamanho mínimo de um perfil ICC (cabeçalho de 128 bytes, ICC.1:2010 §7.2).
    static constexpr int kHeaderSize = 128;

    ICCProfile();
    // Lê o stream inteiro e valida o cabeçalho ICC.
    explicit ICCProfile(std::istream& stream);
    ~ICCProfile() = default;

    // Lê e valida os bytes de um perfil ICC.
    bool loadFromData(const QByteArray& data);
    bool loadFromFile(const QString& path);

    // Bytes originais do perfil (vazio quando inválido).
    QByteArray data() const;

    QString description() const;
    void setDescription(const QString& desc);

    QString md5Hash() const;
    void setMd5Hash(const QString& hash);

    int version() const;
    void setVersion(int ver);

    ColorType colorSpaceType() const;
    void setColorSpaceType(ColorType ct);

    // true somente se o cabeçalho ICC ('acsp') foi validado.
    bool isValid() const;

private:
    void parseHeader();

    QByteArray m_data;
    QString m_description;
    QString m_md5Hash;
    int m_version = 0x0210; // default ICC v2.1 quando o cabeçalho não informa
    ColorType m_colorSpaceType = ColorType::CMYK;
    bool m_valid = false;
};

} // namespace artplus::color
