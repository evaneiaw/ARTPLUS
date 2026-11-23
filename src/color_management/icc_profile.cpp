// src/color_management/icc_profile.cpp
#include "icc_profile.h"
#include <QCryptographicHash>

namespace artplus::color {

ICCProfile::ICCProfile()
    : m_description("Default Profile"),
      m_md5Hash(""),
      m_version(0x0210),
      m_valid(true) {}

ICCProfile::ICCProfile(std::istream& stream) {
    // Read stream bytes to generate basic profile info
    if (stream) {
        stream.seekg(0, std::ios::end);
        std::streamsize size = stream.tellg();
        stream.seekg(0, std::ios::beg);

        if (size > 0) {
            QByteArray data;
            data.resize(static_cast<int>(size));
            stream.read(data.data(), size);

            m_md5Hash = QString(QCryptographicHash::hash(data, QCryptographicHash::Md5).toHex());
            m_description = "Stream ICC Profile";
            m_valid = true;
        } else {
            m_valid = false;
        }
    } else {
        m_valid = false;
    }
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
