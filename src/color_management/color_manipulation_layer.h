// src/color_management/color_manipulation_layer.h
#pragma once
#include <QtGlobal>
#include <atomic>

namespace artplus::color {

class ColorManipulationLayer {
public:
    static bool initialize();
    static void shutdown();
    static bool isInitialized();

private:
    static std::atomic<int> sInitialized;
    static bool initLCMS();
    static bool initPantone();
    static void initializeStrings();
    static void initializeXYZProfile();
};

} // namespace artplus::color