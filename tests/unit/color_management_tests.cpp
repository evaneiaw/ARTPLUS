// tests/unit/color_management_tests.cpp
// F-008: Color Management — unit tests for artplus::color namespace.
//
// Alinhado à implementação corrigida (auditoria F-008 de 2026-11-24):
//  - ICCProfile default é INVÁLIDO (sem "Default Profile" fabricado).
//  - RenderingIntent default = Perceptual (spec §3.2).
//  - BlackPointCompensation default = false (estado real, não constante fixa).
//  - isActiveCMMEngine espelha a disponibilidade real da engine (lcms ausente).
//  - initialize() conta reentrância (R1a): 2×init + 1×shutdown => resto 1.
//  - Cobertura real de R3 (stack replace/push), R4 (cache/scan/0x124f85),
//    R5 (pipeline de callbacks) e R6 (perfis embutidos sem fabricação).
#include <QtTest/QtTest>
#include <QDir>
#include <QFileInfo>

#include <cmath>
#include <cstring>
#include <istream>
#include <memory>
#include <sstream>
#include <vector>

#include "../../src/color_management/icc_profile.h"
#include "../../src/color_management/icc_profile_cache.h"
#include "../../src/color_management/color_lib_info.h"
#include "../../src/color_management/color_manipulation.h"
#include "../../src/color_management/color_manipulation_layer.h"
#include "../../src/color_management/callback_converter.h"
#include "../../src/color_management/color_management_exception.h"

using namespace artplus::color;

namespace {

// Constrói um perfil ICC mínimo válido (cabeçalho ICC.1:2010 §7.2) com a
// assinatura 'acsp' em 0x24 e o espaço de cor em 0x10. Usado para exercitar
// R3/R4 sem depender de arquivos .icc instalados.
std::shared_ptr<ICCProfile> makeValidProfile(const char* space4) {
    QByteArray data(128, '\0');
    data[3] = static_cast<char>(0x80); // tamanho declarado = 128 (big-endian)
    data[8] = 0x02;                    // versão 2.1
    data[9] = 0x10;
    std::memcpy(data.data() + 16, space4, 4);
    std::memcpy(data.data() + 36, "acsp", 4);

    auto profile = std::make_shared<ICCProfile>();
    profile->loadFromData(data);
    return profile;
}

// Mesmo caminho de busca do sistema usado por registerBuiltinProfiles().
bool installedInSystemColorFolder(const char* fileName) {
    const QString systemRoot = qEnvironmentVariable("SystemRoot");
    if (systemRoot.isEmpty()) {
        return false;
    }
    const QString dir = systemRoot + QStringLiteral("/System32/spool/drivers/color");
    return QFileInfo::exists(QDir(dir).filePath(QString::fromLatin1(fileName)));
}

} // namespace

class ColorManagementTests : public QObject {
    Q_OBJECT
private slots:
    // F-008 R? — ICCProfile default NÃO é um perfil válido: não existe
    // "Default Profile" sem fonte (auditoria §7). O cabeçalho só valida com 'acsp'.
    void testICCProfileConstruction() {
        ICCProfile profile;
        QVERIFY(!profile.isValid());
        QCOMPARE(profile.version(), 0x0210);
        QVERIFY(profile.description().isEmpty());
        QVERIFY(profile.md5Hash().isEmpty());
        QVERIFY(profile.data().isEmpty());
        QCOMPARE(profile.colorSpaceType(), ColorType::CMYK);
    }

    // F-008.1: ICCProfile with stream (empty stream should handle gracefully)
    void testICCProfileFromStream() {
        std::istringstream emptyStream;
        ICCProfile profile(emptyStream);
        QVERIFY(!profile.isValid());  // Empty stream should not produce valid profile
        QVERIFY(profile.data().isEmpty());
    }

    // F-008.1: ICCProfile setters and getters
    void testICCProfileSetters() {
        ICCProfile profile;
        profile.setDescription("Test CMYK Profile");
        profile.setMd5Hash("abcdef1234567890");
        profile.setVersion(0x0220);
        profile.setColorSpaceType(ColorType::CMYK);

        QCOMPARE(profile.description(), QString("Test CMYK Profile"));
        QCOMPARE(profile.md5Hash(), QString("abcdef1234567890"));
        QCOMPARE(profile.version(), 0x0220);
        QCOMPARE(profile.colorSpaceType(), ColorType::CMYK);
        // Setters de metadados não tornam o perfil válido (sem bytes ICC).
        QVERIFY(!profile.isValid());
    }

    // F-008.1: ICCProfile ColorType enum values
    void testColorTypeEnum() {
        QCOMPARE(static_cast<int>(ColorType::CMYK), 0);
        QCOMPARE(static_cast<int>(ColorType::RGB), 1);
        QCOMPARE(static_cast<int>(ColorType::Lab), 2);
        QCOMPARE(static_cast<int>(ColorType::Gray), 3);
        QCOMPARE(static_cast<int>(ColorType::Spot), 4);
        QCOMPARE(static_cast<int>(ColorType::DeviceN), 5);
        QCOMPARE(static_cast<int>(ColorType::MultiChannel), 6);
    }

    // F-008.1: ICCProfile CategoryType enum values
    void testCategoryTypeEnum() {
        QCOMPARE(static_cast<int>(CategoryType::Default), 0);
        QCOMPARE(static_cast<int>(CategoryType::Override), 1);
        QCOMPARE(static_cast<int>(CategoryType::DeviceLink), 2);
        QCOMPARE(static_cast<int>(CategoryType::Proof), 3);
    }

    // F-008.1: ICCProfile RenderingIntent enum values
    void testRenderingIntentEnum() {
        QCOMPARE(static_cast<int>(RenderingIntent::Perceptual), 0);
        QCOMPARE(static_cast<int>(RenderingIntent::RelativeColorimetric), 1);
        QCOMPARE(static_cast<int>(RenderingIntent::Saturation), 2);
        QCOMPARE(static_cast<int>(RenderingIntent::AbsoluteColorimetric), 3);
    }

    // F-008.2: ICCProfileCache singleton access
    void testICCProfileCacheInstance() {
        ICCProfileCache& cache1 = ICCProfileCache::instance();
        ICCProfileCache& cache2 = ICCProfileCache::instance();
        QVERIFY(&cache1 == &cache2);  // Singleton check
    }

    // F-008.2: ICCProfileCache getDeviceLinkProfile with empty stream
    void testICCProfileCacheGetDeviceLink() {
        ICCProfileCache& cache = ICCProfileCache::instance();
        std::istringstream emptyStream;
        auto profile = cache.getDeviceLinkProfile(emptyStream);
        // Empty stream cannot produce a valid ICC profile; cache must not
        // fabricate one (auditoria F-008 §7).
        QVERIFY(!profile);
    }

    // F-008.3: ColorLibInfo construction and default values
    void testColorLibInfoConstruction() {
        ColorLibInfo info;
        QCOMPARE(info.L(), 0.0);
        QCOMPARE(info.a(), 0.0);
        QCOMPARE(info.b(), 0.0);
        QCOMPARE(info.cyan(), 0.0);
        QCOMPARE(info.magenta(), 0.0);
        QCOMPARE(info.yellow(), 0.0);
        QCOMPARE(info.black(), 0.0);
        QVERIFY(!info.labIsDefined());
        QVERIFY(!info.cmykIsDefined());
        QVERIFY(info.colorName().isEmpty());
    }

    // F-008.3: ColorLibInfo Lab setters/getters
    void testColorLibInfoLab() {
        ColorLibInfo info;
        info.setL(50.0);
        info.setA(20.0);
        info.setB(-15.0);
        info.setLabDefined(true);

        QCOMPARE(info.L(), 50.0);
        QCOMPARE(info.a(), 20.0);
        QCOMPARE(info.b(), -15.0);
        QVERIFY(info.labIsDefined());
    }

    // F-008.3: ColorLibInfo CMYK setters/getters
    void testColorLibInfoCmyk() {
        ColorLibInfo info;
        info.setCyan(1.0);
        info.setMagenta(0.5);
        info.setYellow(0.0);
        info.setBlack(0.2);
        info.setCmykDefined(true);

        QCOMPARE(info.cyan(), 1.0);
        QCOMPARE(info.magenta(), 0.5);
        QCOMPARE(info.yellow(), 0.0);
        QCOMPARE(info.black(), 0.2);
        QVERIFY(info.cmykIsDefined());
    }

    // F-008.3: ColorLibInfo color name
    void testColorLibInfoColorName() {
        ColorLibInfo info;
        info.setColorName("PANTONE 185 C");
        QCOMPARE(info.colorName(), QString("PANTONE 185 C"));
    }

    // F-008.3: ColorLibInfo matches with ColorType
    void testColorLibInfoMatches() {
        ColorLibInfo info;
        // Verify default color space type is CMYK as per header initialization
        QCOMPARE(info.colorSpaceType(), ColorType::CMYK);

        // Initially, with default values (CMYK color space, neither Lab nor CMYK defined)
        // Should not match RGB with default category
        QVERIFY(!info.matches(ColorType::RGB, CategoryType::Default));
        // Should match CMYK with default category (due to default color space type)
        QVERIFY(info.matches(ColorType::CMYK, CategoryType::Default));

        // Now, set CMYK as defined
        info.setCmykDefined(true);
        // Still should match CMYK with default category
        QVERIFY(info.matches(ColorType::CMYK, CategoryType::Default));
        // Still should not match RGB when only CMYK is defined (and matches logic still considers the color space type)
        QVERIFY(!info.matches(ColorType::RGB, CategoryType::Default));

        // Test with different color space type explicitly set
        info.setColorSpaceType(ColorType::RGB);
        QCOMPARE(info.colorSpaceType(), ColorType::RGB); // Verify setter worked
        QVERIFY(info.matches(ColorType::RGB, CategoryType::Default));
        QVERIFY(!info.matches(ColorType::CMYK, CategoryType::Default));
    }

    // F-008 R4/R6: ColorLibInfo não fabrica um perfil válido sem fonte
    // (auditoria F-008 §7 — getProfile devolvia "Default Profile" válido).
    void testColorLibInfoDoesNotFabricateProfile() {
        ColorLibInfo info;
        QVERIFY(!info.getProfile());

        auto real = makeValidProfile("CMYK");
        info.setProfile(real);
        QVERIFY(info.getProfile() == real);
        QVERIFY(info.getProfile()->isValid());
    }

    // F-008 R3 — setLevelICCProfile: replace substitui no nível corrente,
    // push==false cria um novo nível. O índice é o contador de nível, e as
    // categorias usam stacks separados (Default vs Override/DeviceLink/Proof).
    void testSetLevelICCProfileReplaceAndPush() {
        ColorManipulation& cm = ColorManipulation::instance();

        auto profileA = makeValidProfile("GRAY");
        profileA->setDescription("Gray A");
        auto profileB = makeValidProfile("GRAY");
        profileB->setDescription("Gray B");

        // push (replace=false): novo nível com A.
        cm.setLevelICCProfile(ColorType::Gray, profileA, false, CategoryType::Proof);
        const int levelAfterPush = cm.currentLevel();
        QVERIFY(cm.getActiveICCProfile(ColorType::Gray, false, CategoryType::Proof) == profileA);

        // Segundo push: nível mais profundo com B (o topo resolve B).
        cm.setLevelICCProfile(ColorType::Gray, profileB, false, CategoryType::Proof);
        QCOMPARE(cm.currentLevel(), levelAfterPush + 1);
        QVERIFY(cm.getActiveICCProfile(ColorType::Gray, false, CategoryType::Proof) == profileB);

        // replace=true no nível corrente: substitui B por A sem empilhar.
        cm.setLevelICCProfile(ColorType::Gray, profileA, true, CategoryType::Proof);
        QCOMPARE(cm.currentLevel(), levelAfterPush + 1); // profundidade inalterada
        QVERIFY(cm.getActiveICCProfile(ColorType::Gray, false, CategoryType::Proof) == profileA);

        // Categoria distinta (Default) não é afetada pelo stack de Proof via
        // perfil definido aqui; o slot Gray de Default permanece ausente, então
        // a busca sem cache lança a exceção (R4c).
        cm.setActiveProfileCache(nullptr);
        cm.clearColorLibInfos();
        bool threw = false;
        try {
            cm.getActiveICCProfile(ColorType::Gray, false, CategoryType::Default);
        } catch (const ColorManagementException& e) {
            threw = true;
            QCOMPARE(e.code(), ColorManagementException::kErrorCodeNoProfile);
        }
        QVERIFY(threw);
    }

    // F-008 R4a — useCache=true devolve o cache (+0x38) e lança
    // ColorManagementException(0x124f85) quando ele está vazio.
    void testGetActiveICCProfileCache() {
        ColorManipulation& cm = ColorManipulation::instance();
        auto profile = makeValidProfile("CMYK");

        cm.setActiveProfileCache(profile);
        QVERIFY(cm.getActiveICCProfile(ColorType::CMYK, true, CategoryType::Default) == profile);

        // Cache vazio => exceção, nunca nullptr silencioso.
        cm.setActiveProfileCache(nullptr);
        bool threw = false;
        try {
            cm.getActiveICCProfile(ColorType::CMYK, true, CategoryType::Default);
        } catch (const ColorManagementException& e) {
            threw = true;
            QCOMPARE(e.code(), ColorManagementException::kErrorCodeNoProfile);
            QCOMPARE(e.code(), 0x124f85);
        }
        QVERIFY(threw);
    }

    // F-008 R4c — sem cache e sem match (nível e ColorLibInfo) => exceção
    // 0x124f85, jamais perfil fabricado.
    void testGetActiveICCProfileThrowsWithoutProfile() {
        ColorManipulation& cm = ColorManipulation::instance();
        cm.setActiveProfileCache(nullptr);
        cm.clearColorLibInfos(); // remove eventuais perfis padrão registrados

        // useCache=false e useCache=true devem lançar o mesmo código.
        for (bool useCache : {false, true}) {
            bool threw = false;
            try {
                cm.getActiveICCProfile(ColorType::Spot, useCache, CategoryType::Default);
            } catch (const ColorManagementException& e) {
                threw = true;
                QCOMPARE(e.code(), 0x124f85);
                QCOMPARE(e.message(), QString::fromLatin1(messages::kNoProfileDefined));
            }
            QVERIFY(threw);
        }
    }

    // F-008 R4b — useCache=false varre os níveis do stack da categoria e
    // devolve o primeiro perfil válido (topo para base).
    void testGetActiveICCProfileScansLevels() {
        ColorManipulation& cm = ColorManipulation::instance();
        auto profile = makeValidProfile("CMYK");
        profile->setDescription("DeviceLink CMYK");

        cm.setActiveProfileCache(nullptr);
        cm.setLevelICCProfile(ColorType::CMYK, profile, true, CategoryType::DeviceLink);
        QVERIFY(cm.getActiveICCProfile(ColorType::CMYK, false, CategoryType::DeviceLink) ==
                profile);
    }

    // F-008 R5 — convertColor aplica fn(input[i]) e depois os callbacks em
    // sequência, gravando output[canal]; não ignora a entrada.
    void testConvertColorPipeline() {
        auto converter = CallbackConverter::create();
        QVERIFY(converter);

        const std::vector<double> input = {0.1, 0.2, 0.3, 0.4};
        const std::vector<CallbackFn> callbacks = {
            [](double v) { return v * 2.0; },
            [](double v) { return v + 1.0; },
        };
        CallbackFn fn = [](double v) { return v * 10.0; };

        std::vector<double> output;
        converter->convertColor(input, callbacks, fn, static_cast<int>(input.size()), output);
        QCOMPARE(static_cast<int>(output.size()), static_cast<int>(input.size()));
        for (std::size_t i = 0; i < input.size(); ++i) {
            const double expected = (input[i] * 10.0) * 2.0 + 1.0;
            QVERIFY(std::abs(output[i] - expected) < 1e-12);
        }

        // Sem fn: a entrada é a base do pipeline; callbacks ainda se aplicam.
        std::vector<double> withoutFn;
        converter->convertColor(input, {[](double v) { return v * 2.0; }}, CallbackFn{}, 0,
                                withoutFn);
        QCOMPARE(static_cast<int>(withoutFn.size()), static_cast<int>(input.size()));
        for (std::size_t i = 0; i < input.size(); ++i) {
            QVERIFY(std::abs(withoutFn[i] - input[i] * 2.0) < 1e-12);
        }
    }

    // F-008 R5/§5 — contagem de canais divergente não escreve em output.
    void testConvertColorChannelMismatch() {
        auto converter = CallbackConverter::create();
        QVERIFY(converter);

        const std::vector<double> input = {0.1, 0.2, 0.3};
        std::vector<double> output = {9.0}; // sentinela: não pode ser alterada

        bool threw = false;
        try {
            converter->convertColor(input, {}, CallbackFn{}, 4, output);
        } catch (const ColorManagementException& e) {
            threw = true;
            QCOMPARE(e.code(), 0x124f86);
            QCOMPARE(e.message(), QString::fromLatin1(messages::kChannelMismatch));
        }
        QVERIFY(threw);
        QCOMPARE(static_cast<int>(output.size()), 1);
        QCOMPARE(output[0], 9.0);
    }

    // F-008.4: ColorManipulation singleton access
    void testColorManipulationInstance() {
        ColorManipulation& cm1 = ColorManipulation::instance();
        ColorManipulation& cm2 = ColorManipulation::instance();
        QVERIFY(&cm1 == &cm2);  // Singleton check
    }

    // F-008 spec §3.2 — RenderingIntent default é Perceptual para todas as
    // categorias; setter altera apenas a categoria alvo.
    void testColorManipulationRenderingIntent() {
        ColorManipulation& cm = ColorManipulation::instance();

        auto intentOf = [&cm](CategoryType cat) {
            return static_cast<int>(cm.activeRenderingIntent(cat));
        };
        const int perceptual = static_cast<int>(RenderingIntent::Perceptual);

        QCOMPARE(intentOf(CategoryType::Default), perceptual);
        QCOMPARE(intentOf(CategoryType::Override), perceptual);
        QCOMPARE(intentOf(CategoryType::DeviceLink), perceptual);
        QCOMPARE(intentOf(CategoryType::Proof), perceptual);

        cm.setRenderingIntent(CategoryType::Proof, RenderingIntent::AbsoluteColorimetric);
        QCOMPARE(intentOf(CategoryType::Proof),
                 static_cast<int>(RenderingIntent::AbsoluteColorimetric));
        QCOMPARE(intentOf(CategoryType::Default), perceptual);

        // Restaura o default para não contaminar outras verificações.
        cm.setRenderingIntent(CategoryType::Proof, RenderingIntent::Perceptual);
        QCOMPARE(intentOf(CategoryType::Proof), perceptual);
    }

    // F-008 — BlackPointCompensation default false (estado real, não constante
    // fixa) e setter funcional.
    void testColorManipulationBlackPointCompensation() {
        ColorManipulation& cm = ColorManipulation::instance();

        QVERIFY(!cm.activeBlackPointCompensation());
        cm.setBlackPointCompensation(true);
        QVERIFY(cm.activeBlackPointCompensation());
        cm.setBlackPointCompensation(false);
        QVERIFY(!cm.activeBlackPointCompensation());
    }

    // F-008 — isActiveCMMEngine espelha a disponibilidade real da engine.
    // Sem bridge lcms2 (ADR-008 Limitação 5) o valor honesto é false.
    void testColorManipulationCMMActive() {
        ColorManipulation& cm = ColorManipulation::instance();

        QVERIFY(!ColorManipulationLayer::isCmmEngineAvailable());
        for (CategoryType cat : {CategoryType::Default, CategoryType::Override,
                                 CategoryType::DeviceLink, CategoryType::Proof}) {
            QCOMPARE(cm.isActiveCMMEngine(cat), ColorManipulationLayer::isCmmEngineAvailable());
            QVERIFY(!cm.isActiveCMMEngine(cat));
        }
    }

    // F-008 R1a — reentrância conta: 2×initialize + 1×shutdown deixa resto 1,
    // ou seja, o subsistema continua inicializado.
    void testColorManipulationLayerInitialize() {
        ColorManipulationLayer::shutdown(); // garante contador zerado
        QVERIFY(!ColorManipulationLayer::isInitialized());

        QVERIFY(ColorManipulationLayer::initialize());
        QVERIFY(ColorManipulationLayer::isInitialized());
        QVERIFY(ColorManipulationLayer::initialize()); // reingresso incrementa o contador
        QVERIFY(ColorManipulationLayer::isInitialized());

        ColorManipulationLayer::shutdown(); // 2 -> 1: ainda inicializado
        QVERIFY(ColorManipulationLayer::isInitialized());

        ColorManipulationLayer::shutdown(); // 1 -> 0
        QVERIFY(!ColorManipulationLayer::isInitialized());
    }

    // F-008.5: ColorManipulationLayer shutdown without initialize
    void testColorManipulationLayerShutdown() {
        ColorManipulationLayer::shutdown();  // Should not crash
        QVERIFY(!ColorManipulationLayer::isInitialized());
    }

    // F-008 R6 — perfis padrão embutidos: quando o .icc está instalado o
    // perfil resultante é válido e tem bytes reais; quando não está, o
    // resultado é nulo (ausência honesta), nunca um perfil fabricado.
    void testBuiltinProfilesHonestAbsence() {
        ColorManipulationLayer::registerBuiltinProfiles();

        auto xyz = ColorManipulationLayer::builtinXYZProfile();
        auto rgb = ColorManipulationLayer::builtinRGBProfile();
        auto cmyk = ColorManipulationLayer::builtinCMYKProfile();

        // Invariante de não-fabricação: qualquer perfil devolvido veio de
        // bytes reais e é válido; nulo significa "não instalado".
        for (const auto& profile : {xyz, rgb, cmyk}) {
            if (profile) {
                QVERIFY(profile->isValid());
                QVERIFY(!profile->data().isEmpty());
                QVERIFY(!profile->md5Hash().isEmpty());
            }
        }

        if (installedInSystemColorFolder("Enfocus XYZ Profile.icc")) {
            QVERIFY(xyz && xyz->isValid());
        } else {
            QVERIFY(!xyz);
        }

        if (installedInSystemColorFolder("AdobeRGB1998.icc")) {
            QVERIFY(rgb && rgb->isValid());
            QCOMPARE(rgb->colorSpaceType(), ColorType::RGB);
        } else {
            QVERIFY(!rgb);
        }

        if (installedInSystemColorFolder("ISOcoated_v2_eci.icc")) {
            QVERIFY(cmyk && cmyk->isValid());
        } else {
            QVERIFY(!cmyk);
        }
    }

    // F-008 R5 — a interface abstrata só é utilizável via create(); a fábrica
    // devolve um conversor concreto (compilação + instanciação reais).
    void testCallbackConverterFactory() {
        std::unique_ptr<CallbackConverter> converter = CallbackConverter::create();
        QVERIFY(converter);
        QVERIFY(dynamic_cast<CmmCallbackConverter*>(converter.get()) != nullptr);
    }
};

QTEST_APPLESS_MAIN(ColorManagementTests)
#include "color_management_tests.moc"
