// src/color_management/color_lib_info.cpp
#include "color_lib_info.h"

namespace artplus::color {

ColorLibInfo::ColorLibInfo() = default;

double ColorLibInfo::L() const { return m_L; }
double ColorLibInfo::a() const { return m_a; }
double ColorLibInfo::b() const { return m_b; }
double ColorLibInfo::cyan() const { return m_cyan; }
double ColorLibInfo::magenta() const { return m_magenta; }
double ColorLibInfo::yellow() const { return m_yellow; }
double ColorLibInfo::black() const { return m_black; }
bool ColorLibInfo::labIsDefined() const { return m_labDefined; }
bool ColorLibInfo::cmykIsDefined() const { return m_cmykDefined; }
QString ColorLibInfo::colorName() const { return m_colorName; }
ColorType ColorLibInfo::colorSpaceType() const { return m_colorSpaceType; }

void ColorLibInfo::setL(double l) { m_L = l; }
void ColorLibInfo::setA(double a) { m_a = a; }
void ColorLibInfo::setB(double b) { m_b = b; }
void ColorLibInfo::setCyan(double c) { m_cyan = c; }
void ColorLibInfo::setMagenta(double m) { m_magenta = m; }
void ColorLibInfo::setYellow(double y) { m_yellow = y; }
void ColorLibInfo::setBlack(double bl) { m_black = bl; }
void ColorLibInfo::setLabDefined(bool v) { m_labDefined = v; }
void ColorLibInfo::setCmykDefined(bool v) { m_cmykDefined = v; }
void ColorLibInfo::setColorName(const QString& name) { m_colorName = name; }
void ColorLibInfo::setColorSpaceType(ColorType ct) { m_colorSpaceType = ct; }

bool ColorLibInfo::matches(ColorType ct, CategoryType cat) const {
    // Match if the requested type matches our color space type (if defined) and category matches
    bool typeMatch = (m_colorSpaceType == ColorType::MultiChannel || ct == ColorType::MultiChannel || m_colorSpaceType == ct);
    bool catMatch = true;
    if (cat == CategoryType::Default) {
        catMatch = !m_labDefined || !m_cmykDefined; // simplified: if nothing specific defined, match
    } else {
        // Override/DeviceLink/Proof match based on category bits if needed
        catMatch = true;
    }
    return typeMatch && catMatch;
}

std::shared_ptr<ICCProfile> ColorLibInfo::getProfile() const {
    // Stub: return default ICC profile
    return std::make_shared<ICCProfile>();
}

} // namespace artplus::color
