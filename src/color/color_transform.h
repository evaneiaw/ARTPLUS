#pragma once

#include "color_profile.h"
#include <QVector>
#include <QColor>
#include <memory>

namespace ArtPlus {

class ColorTransform {
public:
    enum class Intent {
        Perceptual = 0,
        RelativeColorimetric = 1,
        Saturation = 2,
        AbsoluteColorimetric = 3
    };
    
    enum class Direction {
        Forward = 0,  // Source -> Destination
        Backward = 1  // Destination -> Source
    };
    
    enum class Quality {
        Fast = 0,      // Low precision, fast
        Normal = 1,    // Balanced
        Best = 2       // High precision, slow
    };
    
    struct Result {
        bool success = false;
        QString error;
        QVector<float> output;
    };
    
    static std::unique_ptr<ColorTransform> create(
        const ColorProfile& srcProfile,
        const ColorProfile& dstProfile,
        ColorProfile::RenderingIntent intent = ColorProfile::RenderingIntent::Perceptual
    );
    
    virtual ~ColorTransform() = default;
    
    // Transform single pixel
    virtual Result transformPixel(const float* input) = 0;
    
    // Transform multiple pixels
    virtual bool transformPixels(
        const float* input,
        float* output,
        size_t count,
        size_t stride = 0
    ) = 0;
    
    // Transform QColor
    virtual QColor transformColor(const QColor& color) = 0;
    
    // Batch transform QVector<QColor>
    virtual QVector<QColor> transformColors(const QVector<QColor>& colors) = 0;
    
    // Get transform info
    virtual QString sourceProfileName() const = 0;
    virtual QString destProfileName() const = 0;
    virtual ColorProfile::RenderingIntent intent() const = 0;
    
    // Inverse transform
    virtual std::unique_ptr<ColorTransform> inverse() = 0;
    
protected:
    ColorTransform() = default;
};

// High-level color conversion utilities
namespace ColorConvert {
    
    // Simple conversions without profiles
    inline QColor cmykToRgb(float c, float m, float y, float k) {
        float r = (1.0f - c) * (1.0f - k);
        float g = (1.0f - m) * (1.0f - k);
        float b = (1.0f - y) * (1.0f - k);
        return QColor::fromRgbF(r, g, b);
    }
    
    inline void rgbToCmyk(float r, float g, float b, float& c, float& m, float& y, float& k) {
        k = 1.0f - qMax(r, qMax(g, b));
        if (k >= 1.0f) {
            c = m = y = 0.0f;
        } else {
            c = (1.0f - r - k) / (1.0f - k);
            m = (1.0f - g - k) / (1.0f - k);
            y = (1.0f - b - k) / (1.0f - k);
        }
    }
    
    inline QColor cmykToRgb(const QVector<float>& cmyk) {
        if (cmyk.size() >= 4) {
            return cmykToRgb(cmyk[0], cmyk[1], cmyk[2], cmyk[3]);
        }
        return QColor();
    }
    
    inline QVector<float> rgbToCmyk(const QColor& color) {
        float c, m, y, k;
        rgbToCmyk(color.redF(), color.greenF(), color.blueF(), c, m, y, k);
        return QVector<float>{c, m, y, k};
    }
    
    // Lab conversions (D50 white point)
    struct LabColor { float L, a, b; };
    
    static LabColor rgbToLab(float r, float g, float b);
    static QColor labToRgb(float L, float a, float b);
    
    static LabColor cmykToLab(float c, float m, float y, float k);
    static QVector<float> labToCmyk(float L, float a, float b);
    
    // Spot color handling
    struct SpotColor {
        QString name;
        float tint = 1.0f;
        QColor alternate; // RGB/CMYK fallback
    };
    
    static QColor spotToRgb(const SpotColor& spot);
    static QVector<float> spotToCmyk(const SpotColor& spot);
    
    // DeviceN
    static QColor deviceNToRgb(const QVector<float>& colorants, const QVector<QColor>& componentColors);
    static QVector<float> rgbToDeviceN(const QColor& color, const QVector<QColor>& componentColors);
    
    // Overprint simulation
    QColor overprint(const QColor& top, const QColor& bottom, bool overprintFill, bool overprintStroke);
    
    // Transparency blending
    QColor blend(const QColor& top, const QColor& bottom, float opacity, Qt::CompositionMode mode = Qt::CompositionMode_SourceOver);
}

} // namespace ArtPlus