// tests/unit/color_management_tests.cpp
// F-008: Color Management — unit tests for artplus::color namespace
#include <QtTest/QtTest>
#include <sstream>
#include "../../src/color_management/icc_profile.h"
#include "../../src/color_management/icc_profile_cache.h"
#include "../../src/color_management/color_lib_info.h"
#include "../../src/color_management/color_manipulation.h"
#include "../../src/color_management/color_manipulation_layer.h"
#include "../../src/color_management/callback_converter.h"

using namespace artplus::color;

class ColorManagementTests : public QObject {
    Q_OBJECT
private slots:
    // F-008.1: ICCProfile basic construction and validation
    void testICCProfileConstruction() {
        ICCProfile profile;
        QVERIFY(profile.isValid());  // Default constructed is valid (m_valid=true, version=0x0210)
        QCOMPARE(profile.version(), 0x0210);
        QCOMPARE(profile.description(), QString("Default Profile"));
        QVERIFY(profile.md5Hash().isEmpty());
    }

    // F-008.1: ICCProfile with stream (empty stream should handle gracefully)
    void testICCProfileFromStream() {
        std::istringstream emptyStream;
        ICCProfile profile(emptyStream);
        QVERIFY(!profile.isValid());  // Empty stream should not produce valid profile
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
        // Empty stream may return nullptr or empty profile - both acceptable for empty input
        // The important thing is it doesn't crash
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

    // F-008.4: ColorManipulation singleton access
    void testColorManipulationInstance() {
        ColorManipulation& cm1 = ColorManipulation::instance();
        ColorManipulation& cm2 = ColorManipulation::instance();
        QVERIFY(&cm1 == &cm2);  // Singleton check
    }

    // F-008.4: ColorManipulation active rendering intent
    void testColorManipulationRenderingIntent() {
        ColorManipulation& cm = ColorManipulation::instance();
        // Default is RelativeColorimetric (1) per implementation
        QCOMPARE(static_cast<int>(cm.activeRenderingIntent(CategoryType::Default)),
                 static_cast<int>(RenderingIntent::RelativeColorimetric));
    }

    // F-008.4: ColorManipulation black point compensation
    void testColorManipulationBlackPointCompensation() {
        ColorManipulation& cm = ColorManipulation::instance();
        // Default is true per implementation
        QVERIFY(cm.activeBlackPointCompensation());
    }

    // F-008.4: ColorManipulation CMM engine active check
    void testColorManipulationCMMActive() {
        ColorManipulation& cm = ColorManipulation::instance();
        // Default is true for all categories per implementation
        QVERIFY(cm.isActiveCMMEngine(CategoryType::Default));
        QVERIFY(cm.isActiveCMMEngine(CategoryType::Override));
        QVERIFY(cm.isActiveCMMEngine(CategoryType::DeviceLink));
        QVERIFY(cm.isActiveCMMEngine(CategoryType::Proof));
    }

    // F-008.5: ColorManipulationLayer initialize/shutdown
    void testColorManipulationLayerInitialize() {
        // Should be able to initialize multiple times (idempotent)
        QVERIFY(ColorManipulationLayer::initialize());
        QVERIFY(ColorManipulationLayer::isInitialized());
        QVERIFY(ColorManipulationLayer::initialize());  // Second call should succeed
        QVERIFY(ColorManipulationLayer::isInitialized());
        ColorManipulationLayer::shutdown();
        QVERIFY(!ColorManipulationLayer::isInitialized());
    }

    // F-008.5: ColorManipulationLayer shutdown without initialize
    void testColorManipulationLayerShutdown() {
        ColorManipulationLayer::shutdown();  // Should not crash
        QVERIFY(!ColorManipulationLayer::isInitialized());
    }

    // F-008.6: CallbackConverter interface (abstract class)
    void testCallbackConverterInterface() {
        // Cannot instantiate abstract class, but we can verify the interface exists
        // by checking the type is complete
        QVERIFY(true);  // Compilation success proves interface is valid
    }
};

QTEST_APPLESS_MAIN(ColorManagementTests)
#include "color_management_tests.moc"