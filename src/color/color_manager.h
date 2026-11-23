#pragma once

#include "../document/document_model.h"
#include <QColor>
#include <QMap>
#include <QString>
#include <memory>

namespace ArtPlus {

class ColorProfile;
class ColorTransform;

class ColorManager {
public:
    static ColorManager& instance();
    
    // ICC Profile management
    bool loadProfile(const QString& name, const QString& path);
    bool loadProfileFromData(const QString& name, const QByteArray& data);
    std::shared_ptr<ColorProfile> getProfile(const QString& name) const;
    QStringList availableProfiles() const;
    
    // Color conversion
    Color convertColor(const Color& color, const QString& srcProfile, const QString& dstProfile, RenderingIntent intent = RenderingIntent::Perceptual);
    
    // Color spaces
    Color cmykToRgb(const Color& cmyk);
    Color rgbToCmyk(const Color& rgb);
    Color cmykToLab(const Color& cmyk);
    Color labToCmyk(const Color& lab);
    Color rgbToLab(const Color& rgb);
    Color labToRgb(const Color& lab);
    
    // Spot colors
    Color createSpotColor(const QString& name, float tint, const Color& alternate);
    bool isSpotColor(const Color& color) const;
    QString spotColorName(const Color& color) const;
    float spotColorTint(const Color& color) const;
    
    // DeviceN
    Color createDeviceNColor(const QStringList& colorants, const QVector<float>& values);
    
    // Simulation
    void setSimulationProfile(const QString& profileName);
    void setSimulationIntent(RenderingIntent intent);
    bool isSimulating() const;
    
    // Color comparison
    float colorDifference(const Color& c1, const Color& c2, DifferenceFormula formula = DifferenceFormula::DeltaE2000) const;
    bool colorsMatch(const Color& c1, const Color& c2, float tolerance = 1.0) const;
    
    // Named colors
    Color namedColor(const QString& name) const;
    void addNamedColor(const QString& name, const Color& color);
    void removeNamedColor(const QString& name);
    
private:
    ColorManager();
    ~ColorManager();
    
    struct Private;
    std::unique_ptr<Private> d;
};

enum class RenderingIntent {
    Perceptual = 0,
    RelativeColorimetric = 1,
    Saturation = 2,
    AbsoluteColorimetric = 3
};

enum class DifferenceFormula {
    DeltaE76 = 0,
    DeltaE94 = 1,
    DeltaE2000 = 2,
    CMC = 3
};

} // namespace ArtPlus