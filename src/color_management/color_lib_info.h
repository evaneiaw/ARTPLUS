// src/color_management/color_lib_info.h
#pragma once
#include "icc_profile.h"
#include <QString>
#include <memory>

namespace artplus::color {

class ColorLibInfo {
public:
    ColorLibInfo();
    ~ColorLibInfo() = default;

    double L() const;
    double a() const;
    double b() const;
    double cyan() const;
    double magenta() const;
    double yellow() const;
    double black() const;
    bool labIsDefined() const;
    bool cmykIsDefined() const;
    QString colorName() const;
    ColorType colorSpaceType() const;

    bool matches(ColorType ct, CategoryType cat) const;
    std::shared_ptr<ICCProfile> getProfile() const;

    void setL(double l);
    void setA(double a);
    void setB(double b);
    void setCyan(double c);
    void setMagenta(double m);
    void setYellow(double y);
    void setBlack(double bl);
    void setLabDefined(bool v);
    void setCmykDefined(bool v);
    void setColorName(const QString& name);
    void setColorSpaceType(ColorType ct);

private:
    double m_L = 0.0;
    double m_a = 0.0;
    double m_b = 0.0;
    double m_cyan = 0.0;
    double m_magenta = 0.0;
    double m_yellow = 0.0;
    double m_black = 0.0;
    bool m_labDefined = false;
    bool m_cmykDefined = false;
    QString m_colorName;
    ColorType m_colorSpaceType = ColorType::CMYK;
};

} // namespace artplus::color
