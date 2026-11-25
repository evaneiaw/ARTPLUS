// src/color_management/color_manipulation_layer.cpp
// F-008 R1/R6 — inicialização do subsistema de cor e perfis padrão.
#include "color_manipulation_layer.h"
#include "color_manipulation.h"
#include "color_lib_info.h"
#include "icc_profile_cache.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QStringList>

namespace artplus::color {
namespace {

// Nomes declarados nas strings do .rdata (spec F-008 §4 R6).
constexpr auto kXyzProfileName = "Enfocus XYZ Profile.icc";
constexpr auto kAdobeRgbProfileName = "AdobeRGB1998.icc";
constexpr auto kIsoCoatedProfileName = "ISOcoated_v2_eci.icc";
constexpr auto kIsoCoatedRelativePath = "WAN-IFRA/ISOcoated_v2_eci.icc";

std::atomic<bool> sCmmEngineAvailable{false};
std::shared_ptr<ICCProfile> sXyzProfile;
std::shared_ptr<ICCProfile> sRgbProfile;
std::shared_ptr<ICCProfile> sCmykProfile;

// R7 — caminhos de busca de perfis. As variáveis de ambiente não têm valor
// documentado: quando não existem, o diretório simplesmente não é pesquisado.
QStringList colorSearchPaths() {
    QStringList paths;

    const QStringList envVars = {
        QStringLiteral("SystemColorFolder"),  QStringLiteral("LocalColorFolder"),
        QStringLiteral("NetworkColorFolder"), QStringLiteral("UserColorFolder"),
        QStringLiteral("EnfocusResourceFolder"),
    };
    for (const QString& var : envVars) {
        const QString value = qEnvironmentVariable(var.toUtf8().constData());
        if (!value.isEmpty() && !paths.contains(value)) {
            paths.append(value);
        }
    }

    const QString systemRoot = qEnvironmentVariable("SystemRoot");
    if (!systemRoot.isEmpty()) {
        const QString colorDir = QDir::toNativeSeparators(
            systemRoot + QStringLiteral("/System32/spool/drivers/color"));
        if (!paths.contains(colorDir)) {
            paths.append(colorDir);
        }
    }

    return paths;
}

std::shared_ptr<ICCProfile> loadBuiltinProfile(const QStringList& relativeNames,
                                               ColorType expectedSpace,
                                               const QString& declaredName) {
    const QStringList roots = colorSearchPaths();
    const QStringList extensions = {QString(), QStringLiteral(".icc"), QStringLiteral(".icm")};

    for (const QString& relativeName : relativeNames) {
        for (const QString& root : roots) {
            for (const QString& extension : extensions) {
                const QString candidate = QDir(root).filePath(relativeName + extension);
                if (!QFileInfo::exists(candidate)) {
                    continue;
                }
                auto profile = std::make_shared<ICCProfile>();
                if (!profile->loadFromFile(candidate)) {
                    qWarning("ColorManagement: perfil inválido em %s", qPrintable(candidate));
                    continue;
                }
                if (profile->colorSpaceType() != expectedSpace) {
                    qWarning("ColorManagement: perfil %s não é do espaço esperado",
                             qPrintable(candidate));
                    continue;
                }
                qInfo("ColorManagement: perfil padrão registrado: %s (%s)", qPrintable(declaredName),
                      qPrintable(candidate));
                return profile;
            }
        }
    }

    // Ausência não é erro fatal: o perfil só existe se estiver instalado.
    qWarning("ColorManagement: perfil padrão não encontrado: %s", qPrintable(declaredName));
    return nullptr;
}

void registerResolvedProfile(const QString& name,
                             const std::shared_ptr<ICCProfile>& profile,
                             ColorType colorType) {
    if (!profile) {
        return;
    }
    ICCProfileCache::instance().registerProfile(name, profile);

    ColorLibInfo info;
    info.setColorName(name);
    info.setColorSpaceType(colorType);
    info.setProfile(profile);
    ColorManipulation::instance().addColorLibInfo(info);
}

} // namespace

std::atomic<int> ColorManipulationLayer::sInitialized{0};

bool ColorManipulationLayer::initialize() {
    // R1a: reingresso incrementa o contador e retorna true.
    if (sInitialized.load() > 0) {
        sInitialized.fetch_add(1);
        return true;
    }

    // R1b: cache global de perfis.
    ICCProfileCache::createInstance();

    // R1c/R1d: qualquer falha aborta com false.
    if (!initLCMS()) {
        qCritical("ColorManagement: %s", "initLCMS failed");
        return false;
    }
    if (!initPantone()) {
        qCritical("ColorManagement: %s", "initPantone failed");
        return false;
    }

    // R1e (mensagens de erro) é atendida pelas constantes de
    // color_management_exception.h; R1f (perfil XYZ padrão) e R6 (demais
    // perfis padrão) por registerBuiltinProfiles().
    registerBuiltinProfiles();

    // R1g
    sInitialized.fetch_add(1);
    return true;
}

void ColorManipulationLayer::shutdown() {
    if (sInitialized.load() <= 0) {
        return;
    }
    if (sInitialized.fetch_sub(1) > 1) {
        return;
    }

    sXyzProfile.reset();
    sRgbProfile.reset();
    sCmykProfile.reset();
    ICCProfileCache::destroyInstance();
}

bool ColorManipulationLayer::isInitialized() {
    return sInitialized.load() > 0;
}

bool ColorManipulationLayer::isCmmEngineAvailable() {
    return sCmmEngineAvailable.load();
}

bool ColorManipulationLayer::initLCMS() {
    // Stub declarado (ADR-008 Limitação 5): a bridge lcms2 não está integrada.
    // O pipeline interno (CallbackConverter, R5) não depende de lcms, então a
    // etapa de inicialização não falha; a ausência da engine é reportada de
    // forma honesta por isCmmEngineAvailable() == false.
    // TODO(F-008): integrar lcms2 e marcar sCmmEngineAvailable = true.
    sCmmEngineAvailable.store(false);
    return true;
}

bool ColorManipulationLayer::initPantone() {
    // Stub declarado (ADR-008 Limitação 4): bibliotecas Pantone/ColorLib não
    // integradas; nada a inicializar, nenhuma capacidade é anunciada.
    // TODO(F-008): carregar bibliotecas Pantone/ColorLib.
    return true;
}

void ColorManipulationLayer::initializeXYZProfile() {
    // R1f: perfil XYZ de referência (D50).
    sXyzProfile = loadBuiltinProfile({QString::fromLatin1(kXyzProfileName)},
                                     ColorType::Lab,
                                     QString::fromLatin1(kXyzProfileName));
    registerResolvedProfile(QString::fromLatin1(kXyzProfileName), sXyzProfile, ColorType::Lab);
}

void ColorManipulationLayer::registerBuiltinProfiles() {
    initializeXYZProfile();

    sRgbProfile = loadBuiltinProfile({QString::fromLatin1(kAdobeRgbProfileName)},
                                     ColorType::RGB,
                                     QString::fromLatin1(kAdobeRgbProfileName));
    registerResolvedProfile(QString::fromLatin1(kAdobeRgbProfileName), sRgbProfile,
                            ColorType::RGB);

    sCmykProfile = loadBuiltinProfile(
        {QString::fromLatin1(kIsoCoatedRelativePath), QString::fromLatin1(kIsoCoatedProfileName)},
        ColorType::CMYK,
        QString::fromLatin1(kIsoCoatedProfileName));
    registerResolvedProfile(QString::fromLatin1(kIsoCoatedProfileName), sCmykProfile,
                            ColorType::CMYK);
}

std::shared_ptr<ICCProfile> ColorManipulationLayer::builtinXYZProfile() {
    return sXyzProfile;
}

std::shared_ptr<ICCProfile> ColorManipulationLayer::builtinRGBProfile() {
    return sRgbProfile;
}

std::shared_ptr<ICCProfile> ColorManipulationLayer::builtinCMYKProfile() {
    return sCmykProfile;
}

} // namespace artplus::color
