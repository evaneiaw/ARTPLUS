// src/color_management/color_manipulation_layer.cpp
#include "color_manipulation_layer.h"
#include <QDebug>
#include <QtGlobal>

namespace artplus::color {

std::atomic<int> ColorManipulationLayer::sInitialized{0};

bool ColorManipulationLayer::initialize() {
    if (sInitialized.load() > 0) {
        qWarning("ColorManagement: already initialized");
        return true;
    }

    // Stub initializations
    if (!initLCMS()) {
        qWarning("ColorManagement: initLCMS failed");
        return false;
    }
    if (!initPantone()) {
        qWarning("ColorManagement: initPantone failed");
        return false;
    }
    initializeStrings();
    initializeXYZProfile();

    sInitialized.store(1);
    return true;
}

void ColorManipulationLayer::shutdown() {
    if (sInitialized.load() > 0) {
        sInitialized.store(0);
        qWarning("ColorManagement: shutdown");
    }
}

bool ColorManipulationLayer::isInitialized() {
    return sInitialized.load() > 0;
}

bool ColorManipulationLayer::initLCMS() {
    // Stub: returns true; real LCMS initialization later
    return true;
}

bool ColorManipulationLayer::initPantone() {
    // Stub: returns true; real Pantone initialization later
    return true;
}

void ColorManipulationLayer::initializeStrings() {
    // Stub: load error strings, etc.
}

void ColorManipulationLayer::initializeXYZProfile() {
    // Stub: registers default XYZ profile.
}

} // namespace artplus::color