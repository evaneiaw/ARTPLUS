#include "color_manipulation_layer.h"
#include "color_manipulation_layer.h" // self-include guard (redundant but ok)
#include <QtGlobal>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QMutex>

namespace ArtPlus::Prepress {

// ===== Standalone helper functions (forward declarations) =====
void initializeErrorStrings();
void initializeXYZProfile();

// ===== PIMPL Private struct definitions =====

struct ICCProfile::Private {
    QByteArray iccData;
    bool valid = false;
    // TODO(F-008): Add lcms2 profile handle (cmsHPROFILE) and parsed header fields
};

struct ICCProfileCache::Private {
    QHash<QString, ICCProfile::Ptr> profiles;
    QMutex mutex; // thread-safe access if needed
};

struct ColorManipulation::Private {
    // Stack-based profile storage per color type and category
    // m_defaultStack for CategoryType::Default, m_overrideStack for others
    QVector<QVector<ColorLibInfo>> defaultStack;
    QVector<QVector<ColorLibInfo>> overrideStack;
    int currentLevel = 0;
    ICCProfile::Ptr cachedProfile;
    // TODO(F-008): Add lcms2 transform cache
};

// ===== Standalone helper functions (forward declarations) =====
void initializeErrorStrings();
void initializeXYZProfile();

// ===== ICCProfile implementation =====

ICCProfile::ICCProfile(const QByteArray& iccData)
{
    Q_UNUSED(iccData);
    // TODO(F-008): Parse ICC profile from data using lcms2 or custom parser
    // For now, default construction with invalid state
}

ICCProfile::ICCProfile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        // Will be invalid
        return;
    }
    QByteArray data = file.readAll();
    // TODO(F-008): Parse ICC profile from file using lcms2
}

ICCProfile::~ICCProfile()
{
}

bool ICCProfile::isValid() const
{
    // TODO(F-008): Check profile validity
    return false;
}

bool ICCProfile::loadFromData(const QByteArray& data)
{
    Q_UNUSED(data);
    // TODO(F-008): Parse ICC profile from data
    return false;
}

bool ICCProfile::loadFromFile(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QByteArray data = file.readAll();
    return loadFromData(data);
}

QByteArray ICCProfile::saveToData() const
{
    QByteArray result;
    // TODO(F-008): Serialize profile data
    return result;
}

bool ICCProfile::saveToFile(const QString& path) const
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    QByteArray data = saveToData();
    return file.write(data) >= 0;
}

ICCProfile::ColorSpace ICCProfile::colorSpace() const
{
    // TODO(F-008): Parse and return color space
    return ColorSpace::Unknown;
}

ICCProfile::ColorSpace ICCProfile::pcs() const
{
    // TODO(F-008): Return Profile Connection Space (typically XYZ/D50)
    return ColorSpace::XYZ;
}

QString ICCProfile::name() const
{
    // TODO(F-008): Return ICC profile name from header
    return QString{};
}

QString ICCProfile::description() const
{
    // TODO(F-008): Return ICC profile description
    return QString{};
}

bool ICCProfile::hasTag(uint32_t signature) const
{
    Q_UNUSED(signature);
    // TODO(F-008): Check if ICC tag exists
    return false;
}

QByteArray ICCProfile::tagData(uint32_t signature) const
{
    Q_UNUSED(signature);
    // TODO(F-008): Return ICC tag data
    return QByteArray{};
}

// ===== ColorLibInfo implementation =====

ColorLibInfo::ColorLibInfo(ColorType type, CategoryType cat, ICCProfile::Ptr profile)
    : m_colorType(type), m_categoryType(cat), m_profile(profile)
{
}

ColorType ColorLibInfo::colorType() const
{
    return m_colorType;
}

CategoryType ColorLibInfo::categoryType() const
{
    return m_categoryType;
}

ICCProfile::Ptr ColorLibInfo::profile() const
{
    // AddRef interno (shared_ptr copy)
    return m_profile;
}

bool ColorLibInfo::matches(ColorType ct, CategoryType cat) const
{
    return m_colorType == ct && m_categoryType == cat;
}

// ===== ICCProfileCache implementation =====

bool ICCProfileCache::createInstance()
{
    // Stub: Ensure only one instance exists
    static ICCProfileCache cache;
    (void)cache;
    return true;
}

void ICCProfileCache::destroyInstance()
{
    // No-op for static local instance
}

ICCProfileCache& ICCProfileCache::instance()
{
    static ICCProfileCache cache;
    return cache;
}

ICCProfile::Ptr ICCProfileCache::findProfile(const QString& name) const
{
    Q_UNUSED(name);
    // TODO(F-008): Search by name
    return nullptr;
}

void ICCProfileCache::registerProfile(const QString& name, ICCProfile::Ptr profile)
{
    Q_UNUSED(name);
    Q_UNUSED(profile);
    // TODO(F-008): Register profile by name
}

void ICCProfileCache::unregisterProfile(const QString& name)
{
    Q_UNUSED(name);
    // TODO(F-008): Unregister profile by name
}

QStringList ICCProfileCache::availableProfiles() const
{
    QStringList list;
    // TODO(F-008): Return available profiles
    return list;
}

// ===== CallbackConverter implementation =====

void CallbackConverter::convertColor(
    const ColorTable& input,
    const CallbackTable& callbacks,
    CallbackFn fn,
    int param,
    ColorTable& output
)
{
    // Stub: Initialize output with same size as input
    Q_UNUSED(input);
    Q_UNUSED(callbacks);
    Q_UNUSED(fn);
    Q_UNUSED(param);
    output = ColorTable(input.size(), 0.0);
    // TODO(F-008): Full pipeline using lcms2 with callbacks
    //  - Create lcms transform
    //  - Apply callbacks if any
    //  - Do transform
}

std::unique_ptr<CallbackConverter> CallbackConverter::create()
{
    // TODO(F-008): Return lcms2-based implementation
    return nullptr;
}

// ===== ColorManipulation implementation =====

ColorManipulation& ColorManipulation::instance()
{
    // Singleton pattern - thread-unsafe (matches original ArtPro+ behavior)
    static ColorManipulation sInstance;
    return sInstance;
}

void ColorManipulation::setLevelICCProfile(
    ColorType colorType,
    ICCProfile::Ptr profile,
    bool replace,
    CategoryType category
)
{
    Q_UNUSED(colorType);
    Q_UNUSED(profile);
    Q_UNUSED(replace);
    Q_UNUSED(category);
    // TODO(F-008): Stack-based profile definition (see ADR-008 R3-R4)
    // - Two arrays: m_defaultStack (+0x20) for CategoryType::Default
    //   and m_overrideStack (+0x8) for other categories
    // - Index from m_currentLevel (+0xC)
    // - Calls internal setProfileAtLevel (0x1800161c0)
}

ICCProfile::Ptr ColorManipulation::getActiveICCProfile(
    ColorType colorType,
    bool useCache,
    CategoryType category
) const
{
    Q_UNUSED(colorType);
    Q_UNUSED(useCache);
    Q_UNUSED(category);
    // TODO(F-008): Two paths:
    // 1. Cache rápido (useCache ∈ {0,1,2,3}): retorna m_cachedProfile (+0x38)
    //    Se NULL → ColorManagementException(0x124F85) "No XYZ ICC profile has been defined"
    // 2. Busca lenta: itera GCColorLibInfo no stack correspondente
    //    Para cada entrada: GetGreen255 + match function (FUN_180015cc0)
    //    Se achado: FUN_180015c00 para GSharedObject<GCICCProfile>, AddRef e retorna
    //    Sem match → exception com mensagem específica
    return nullptr;
}

void ColorManipulation::convertColor(
    const ColorTable& input,
    const CallbackTable& callbacks,
    CallbackFn fn,
    int param,
    ColorTable& output
)
{
    Q_UNUSED(input);
    Q_UNUSED(callbacks);
    Q_UNUSED(fn);
    Q_UNUSED(param);
    output = ColorTable(input.size(), 0.0);
    // TODO(F-008): Pipeline via callback usando lcms2
    // Pipeline: para cada callback, aplica fn(input[i]) acumulando em output
    // Unidades: double 0.0-1.0 (calibrado) ou 0-255 (device)
}

ICCProfileCache& ColorManipulation::profileCache() const
{
    // TODO(F-008): Retornar referência ao cache global
    static ICCProfileCache dummyCache;
    return dummyCache;
}

// ===== ColorManipulationLayer implementation =====

int ColorManipulationLayer::s_initialized = 0;
std::unique_ptr<ColorManipulation> ColorManipulationLayer::s_instance;
std::unique_ptr<ICCProfileCache> ColorManipulationLayer::s_profileCache;

bool ColorManipulationLayer::initialize()
{
    // R1 - Inicialização single-shot com reentrância (0x180014b80)
    if (s_initialized > 0) {
        s_initialized++;
        return true;
    }

    // b. Cria ICCProfileCache
    s_profileCache = std::make_unique<ICCProfileCache>();
    ICCProfileCache::createInstance();

    // c. Inicializa subsistema lcms/device-link (FUN_180027c40)
    // TODO(F-008): FUN_180027c40 inicializa lcms.dll
    bool lcmsOk = LCMSSubsystem::initialize();
    if (!lcmsOk) {
        qCritical() << "Color Management: LCMS subsystem initialization failed";
        return false;
    }

    // d. Inicializa bibliotecas Pantone/color libraries (FUN_1800269b0)
    // TODO(F-008): FUN_1800269b0 inicializa bibliotecas Pantone
    bool pantoneOk = PantoneSubsystem::initialize();
    if (!pantoneOk) {
        qCritical() << "Color Management: Pantone subsystem initialization failed";
        return false;
    }

    // e. Carrega strings de erro do .rdata (InitializeStrings)
    initializeErrorStrings();

    // f. Registra perfil XYZ padrão Enfocus XYZ Profile.icc (0x180014bd0 / initializeXYZProfile)
    initializeXYZProfile();

    // g. Define sInitialized = 1 e retorna true
    s_initialized = 1;
    return true;
}

void ColorManipulationLayer::shutdown()
{
    // Decrementa contador; se 0, destrói ICCProfileCache, limpa lcms/Pantone
    if (s_initialized > 0) {
        s_initialized--;
    }
    if (s_initialized == 0) {
        s_profileCache.reset();
        s_instance.reset();
        // TODO(F-008): Cleanup lcms/Pantone subsystems
    }
}

bool ColorManipulationLayer::isInitialized()
{
    return s_initialized > 0;
}

void ColorManipulationLayer::registerBuiltinProfiles()
{
    // Registra perfis padrão embutidos (hardcoded strings .rdata)
    // - Enfocus XYZ Profile.icc (D50) - perfil XYZ de referência
    // - AdobeRGB1998.icc - RGB calibrado
    // - WAN-IFRA/ISOcoated_v2_eci.icc - CMYK ISO 12647-2 (FOGRA39/53)
}

ICCProfile::Ptr ColorManipulationLayer::builtinXYZProfile()
{
    // TODO(F-008): Carregar perfil "Enfocus XYZ Profile.icc" de recursos Qt
    // Caminho esperado :/icc/Enfocus_XYZ_Profile.icc
    return nullptr;
}

ICCProfile::Ptr ColorManipulationLayer::builtinRGBProfile()
{
    // TODO(F-008): Carregar perfil "AdobeRGB1998.icc" de recursos Qt
    // Caminho esperado :/icc/AdobeRGB1998.icc
    return nullptr;
}

ICCProfile::Ptr ColorManipulationLayer::builtinCMYKProfile()
{
    // TODO(F-008): Carregar perfil "WAN-IFRA/ISOcoated_v2_eci.icc" de recursos Qt
    // Caminho esperado :/icc/WAN-IFRA_ISOcoated_v2_eci.icc
    return nullptr;
}

// ===== LCMSSubsystem implementation =====
bool LCMSSubsystem::initialize()
{
    // TODO(F-008): FUN_180027c40 - inicializa lcms.dll
    // Retorna true se lcms.dll estiver disponível
    return true;
}

// ===== PantoneSubsystem implementation =====
bool PantoneSubsystem::initialize()
{
    // TODO(F-008): FUN_1800269b0 - inicializa bibliotecas Pantone/color libraries
    // Retorna true se estiver disponível
    return true;
}

// ===== Standalone helper functions =====
void initializeErrorStrings()
{
    // TODO(F-008): Carrega mensagens de erro do .rdata para ColorManagementException
    // Ex.: "No XYZ ICC profile has been defined", "An ICC profile could not be read",
    //      "Invalid ICC profile", "Color conversion was not possible..."
}

void initializeXYZProfile()
{
    // TODO(F-008): Registra perfil XYZ padrão Enfocus XYZ Profile.icc
    // - Carrega perfil da resource :/icc/Enfocus_XYZ_Profile.icc
    // - Registra no ICCProfileCache
}

} // namespace ArtPlus::Prepress