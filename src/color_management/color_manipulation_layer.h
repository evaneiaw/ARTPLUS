// src/color_management/color_manipulation_layer.h
#pragma once
#include "icc_profile.h"

#include <QtGlobal>

#include <atomic>
#include <memory>

namespace artplus::color {

// GCColorManipulationLayer — inicialização global do subsistema de cor.
class ColorManipulationLayer {
public:
    // R1 — 0x180014b80.
    static bool initialize();
    static void shutdown();
    static bool isInitialized();

    // Estado real da engine CMM integrada (bridge lcms2 — ADR-008 Limitação 5).
    static bool isCmmEngineAvailable();

    // R6 — registra os perfis padrão declarados na spec quando instalados.
    static void registerBuiltinProfiles();
    static std::shared_ptr<ICCProfile> builtinXYZProfile();  // Enfocus XYZ Profile.icc
    static std::shared_ptr<ICCProfile> builtinRGBProfile();  // AdobeRGB1998.icc
    static std::shared_ptr<ICCProfile> builtinCMYKProfile(); // ISOcoated_v2_eci.icc

private:
    ColorManipulationLayer() = delete;

    static std::atomic<int> sInitialized;
    static bool initLCMS();
    static bool initPantone();
    static void initializeXYZProfile();
};

} // namespace artplus::color
