// src/color_management/icc_profile_cache.h
#pragma once
#include "icc_profile.h"
#include <memory>
#include <istream>

namespace artplus::color {

class ICCProfileCache {
public:
    static ICCProfileCache& instance();
    std::shared_ptr<ICCProfile> getDeviceLinkProfile(std::istream& stream);

private:
    ICCProfileCache() = default;
};

} // namespace artplus::color