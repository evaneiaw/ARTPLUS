#pragma once

#include <memory>
#include <QString>
#include <QVector>
#include <functional>
#include <stdexcept>
#include <QByteArray>

namespace ArtPlus::Prepress {

// Forward declarations for color subsystem classes
class LCMSSubsystem {
public:
    static bool initialize();
};

class PantoneSubsystem {
public:
    static bool initialize();
};

// ===== Enums (mapeados de GCColorManipulationEnums) =====
enum class ColorType {
    CMYK = 0,
    RGB  = 1,
    Lab  = 2,
    Gray = 3,
    Spot = 4,
    DeviceN = 5,
    MultiChannel = 6
};

enum class CategoryType {
    Default = 0,
    Override = 1,
    DeviceLink = 2,
    Proof = 3
};

enum class RenderingIntent {
    Perceptual = 0,
    RelativeColorimetric = 1,
    Saturation = 2,
    AbsoluteColorimetric = 3
};

// ===== Exception =====
class ColorManagementException : public std::exception {
public:
    enum class Code {
        NotInitialized = 1,
        NoProfileMatch = 2,
        ReadFailed = 3,
        InvalidProfile = 4,
        CMMEngineUnavailable = 5,
        ChannelMismatch = 6,
        InvalidArgument = 7
    };
    ColorManagementException(Code code, const QString& message = {});
    Code code() const noexcept;
    const char* what() const noexcept override;
private:
    Code m_code;
    QString m_message;
};

// ===== ICC Profile (wrapper de GCICCProfile) =====
class ICCProfile {
public:
    using Ptr = std::shared_ptr<ICCProfile>;
    ICCProfile() = default;
    explicit ICCProfile(const QByteArray& iccData);
    explicit ICCProfile(const QString& filePath);
    ~ICCProfile();

    bool isValid() const;
    bool loadFromData(const QByteArray& data);
    bool loadFromFile(const QString& path);
    QByteArray saveToData() const;
    bool saveToFile(const QString& path) const;

    // Header info
    enum class ColorSpace { Unknown, Gray, RGB, CMYK, Lab, XYZ, NamedColor, HiFiColor, Multichannel };
    ColorSpace colorSpace() const;
    ColorSpace pcs() const; // Profile Connection Space
    QString name() const;
    QString description() const;
    bool hasTag(uint32_t signature) const;
    QByteArray tagData(uint32_t signature) const;

private:
    struct Private;
    std::unique_ptr<Private> d;
};

// ===== ColorLibInfo (entrada do stack de perfis) =====
class ColorLibInfo {
public:
    ColorLibInfo() = default;
    ColorLibInfo(ColorType type, CategoryType cat, ICCProfile::Ptr profile);

    ColorType colorType() const;
    CategoryType categoryType() const;
    ICCProfile::Ptr profile() const; // AddRef interno

    // Match usado em GetActiveICCProfile
    bool matches(ColorType ct, CategoryType cat) const;

private:
    ColorType m_colorType;
    CategoryType m_categoryType;
    ICCProfile::Ptr m_profile;
};

// ===== ICCProfileCache (GCICCProfileCache) =====
class ICCProfileCache {
public:
    static bool createInstance();  // 0x180020d90
    static void destroyInstance();
    static ICCProfileCache& instance();

    ICCProfile::Ptr findProfile(const QString& name) const;
    void registerProfile(const QString& name, ICCProfile::Ptr profile);
    void unregisterProfile(const QString& name);
    QStringList availableProfiles() const;

public:
    ICCProfileCache() = default;
private:
    struct Private;
    std::unique_ptr<Private> d;
};

// ===== CallbackConverter (GCCallbackConverter) =====
using ColorTable = QVector<double>;  // normalizado 0.0-1.0 ou 0-255
using CallbackFn = std::function<ColorTable(const ColorTable&)>;
using CallbackTable = QVector<CallbackFn>;

class CallbackConverter {
public:
    virtual ~CallbackConverter() = default;

    // 0x18000a2f0 - pipeline principal
    virtual void convertColor(
        const ColorTable& input,
        const CallbackTable& callbacks,
        CallbackFn fn,
        int param,
        ColorTable& output
    ) = 0;

    // Factory cria instância baseada em lcms2
    static std::unique_ptr<CallbackConverter> create();
};

// ===== ColorManipulation (GCColorManipulation) =====
class ColorManipulation {
public:
    // 0x1800132f0 - único ponto de entrada público
    static ColorManipulation& instance();

    // 0x180014980 - define perfil por nível (stack)
    void setLevelICCProfile(
        ColorType colorType,
        ICCProfile::Ptr profile,
        bool replace,           // true = substitui no nível atual; false = empilha (push)
        CategoryType category = CategoryType::Default
    );

    // 0x180012bf0 - resolve perfil ativo
    ICCProfile::Ptr getActiveICCProfile(
        ColorType colorType,
        bool useCache = false,
        CategoryType category = CategoryType::Default
    ) const;

    // Sobrecarga conveniente (0x180012d20)
    ICCProfile::Ptr getActiveICCProfile(
        ColorType colorType,
        CategoryType category = CategoryType::Default
    ) const { return getActiveICCProfile(colorType, false, category); }

    // Acesso ao cache de perfis
    ICCProfileCache& profileCache() const;

    // Conversão direta via callback
    void convertColor(
        const ColorTable& input,
        const CallbackTable& callbacks,
        CallbackFn fn,
        int param,
        ColorTable& output
    );

private:
    friend class ColorManipulationLayer;
    ColorManipulation() = default;
public:
    ~ColorManipulation() = default;

    struct Private;
    std::unique_ptr<Private> d;
};

// ===== ColorManipulationLayer (GCColorManipulationLayer) =====
class ColorManipulationLayer {
public:
    // 0x180014b80 - inicialização singleton com reentrância
    static bool initialize();   // retorna false se lcms/Pantone falhar
    static void shutdown();     // decrementa contador; destrói se 0
    static bool isInitialized();

    // Perfis padrão embutidos (registrados no initialize)
    static void registerBuiltinProfiles();
    static ICCProfile::Ptr builtinXYZProfile();      // Enfocus XYZ Profile.icc (D50)
    static ICCProfile::Ptr builtinRGBProfile();      // AdobeRGB1998.icc
    static ICCProfile::Ptr builtinCMYKProfile();     // WAN-IFRA/ISOcoated_v2_eci.icc (FOGRA53)

private:
    ColorManipulationLayer() = delete;
    static int s_initialized;
    static std::unique_ptr<ColorManipulation> s_instance;
    static std::unique_ptr<ICCProfileCache> s_profileCache;
};

} // namespace ArtPlus::Prepress