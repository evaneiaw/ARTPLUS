// src/color_management/color_manipulation.h
#pragma once
#include "icc_profile.h"
#include "color_lib_info.h"
#include <QtGlobal>
#include <memory>
#include <vector>

namespace artplus::color {

class ColorManipulation {
public:
    static ColorManipulation& instance();

    void setLevelICCProfile(ColorType ct,
                            std::shared_ptr<ICCProfile> profile,
                            bool replace,
                            CategoryType cat);

    std::shared_ptr<ICCProfile> getActiveICCProfile(ColorType ct,
                                                    bool useCache,
                                                    CategoryType cat) const;

    RenderingIntent activeRenderingIntent(CategoryType cat) const;
    bool activeBlackPointCompensation() const;
    bool isActiveCMMEngine(CategoryType cat) const;

private:
    ColorManipulation() = default;
    ~ColorManipulation() = default;

    std::vector<std::shared_ptr<ICCProfile>> mDefaultProfiles;
    std::vector<std::shared_ptr<ICCProfile>> mOverrideProfiles;
    int mCurrentLevel = 0;

    std::shared_ptr<ICCProfile> mActiveProfileCache;

    std::vector<ColorLibInfo> mColorLibInfos;

    void setLevelProfileInternal(std::shared_ptr<ICCProfile>& slot,
                                 ColorType ct,
                                 std::shared_ptr<ICCProfile> profile,
                                 bool replace);
};

} // namespace artplus::color