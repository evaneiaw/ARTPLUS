// src/color_management/icc_profile_cache.cpp
#include "icc_profile_cache.h"
#include <memory>

namespace artplus::color {

ICCProfileCache& ICCProfileCache::instance() {
    static ICCProfileCache sInstance;
    return sInstance;
}

std::shared_ptr<ICCProfile> ICCProfileCache::getDeviceLinkProfile(std::istream& stream) {
    if (stream) {
        return std::make_shared<ICCProfile>(stream);
    }
    return nullptr;
}

} // namespace artplus::color