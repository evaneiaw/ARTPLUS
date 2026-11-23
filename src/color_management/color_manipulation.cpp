// src/color_management/color_manipulation.cpp
#include "color_manipulation.h"
#include <QtGlobal>

namespace artplus::color {

ColorManipulation& ColorManipulation::instance() {
    static ColorManipulation sInstance;
    return sInstance;
}

void ColorManipulation::setLevelICCProfile(ColorType ct,
                                           std::shared_ptr<ICCProfile> profile,
                                           bool replace,
                                           CategoryType cat) {
    if (cat == CategoryType::Default) {
        if (mDefaultProfiles.empty()) {
            mDefaultProfiles.resize(7);
        }
        setLevelProfileInternal(mDefaultProfiles[static_cast<int>(ct)], ct, profile, replace);
    } else {
        if (mOverrideProfiles.empty()) {
            mOverrideProfiles.resize(7);
        }
        setLevelProfileInternal(mOverrideProfiles[static_cast<int>(ct)], ct, profile, replace);
    }
    mCurrentLevel++;
}

std::shared_ptr<ICCProfile> ColorManipulation::getActiveICCProfile(ColorType ct,
                                                                   bool useCache,
                                                                   CategoryType cat) const {
    if (useCache) {
        if (mActiveProfileCache) {
            return mActiveProfileCache;
        }
        qWarning("ColorManagement: active ICC profile cache is empty");
        return nullptr;
    }

    for (const ColorLibInfo& info : mColorLibInfos) {
        if (info.matches(ct, cat)) {
            auto profile = info.getProfile();
            if (profile) {
                return profile;
            }
        }
    }

    qWarning("ColorManagement: no active ICC profile found for type %d, category %d",
             static_cast<int>(ct), static_cast<int>(cat));
    return nullptr;
}

RenderingIntent ColorManipulation::activeRenderingIntent(CategoryType cat) const {
    Q_UNUSED(cat)
    return RenderingIntent::RelativeColorimetric;
}

bool ColorManipulation::activeBlackPointCompensation() const {
    return true;
}

bool ColorManipulation::isActiveCMMEngine(CategoryType cat) const {
    Q_UNUSED(cat)
    return true;
}

void ColorManipulation::setLevelProfileInternal(std::shared_ptr<ICCProfile>& slot,
                                                ColorType ct,
                                                std::shared_ptr<ICCProfile> profile,
                                                bool replace) {
    Q_UNUSED(ct)
    if (replace || !slot) {
        slot = profile;
    }
    mActiveProfileCache = profile;
}

} // namespace artplus::color