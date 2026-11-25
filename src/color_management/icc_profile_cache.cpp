// src/color_management/icc_profile_cache.cpp
#include "icc_profile_cache.h"

namespace artplus::color {

bool ICCProfileCache::createInstance() {
    // A instância é o singleton estático de instance(); a chamada garante a
    // construção antes de qualquer registro (R1b) e é idempotente.
    (void)instance();
    return true;
}

void ICCProfileCache::destroyInstance() {
    // O singleton tem duração estática; limpar o conteúdo é o equivalente ao
    // destroyInstance() do binário.
    instance().clear();
}

ICCProfileCache& ICCProfileCache::instance() {
    static ICCProfileCache sInstance;
    return sInstance;
}

std::shared_ptr<ICCProfile> ICCProfileCache::getDeviceLinkProfile(std::istream& stream) {
    auto profile = std::make_shared<ICCProfile>(stream);
    if (!profile->isValid()) {
        return nullptr;
    }
    return profile;
}

void ICCProfileCache::registerProfile(const QString& name, std::shared_ptr<ICCProfile> profile) {
    if (name.isEmpty() || !profile) {
        return;
    }
    std::lock_guard<std::mutex> lock(mMutex);
    mProfiles.insert(name, std::move(profile));
}

std::shared_ptr<ICCProfile> ICCProfileCache::findProfile(const QString& name) const {
    std::lock_guard<std::mutex> lock(mMutex);
    return mProfiles.value(name, nullptr);
}

QStringList ICCProfileCache::availableProfiles() const {
    std::lock_guard<std::mutex> lock(mMutex);
    return mProfiles.keys();
}

void ICCProfileCache::clear() {
    std::lock_guard<std::mutex> lock(mMutex);
    mProfiles.clear();
}

} // namespace artplus::color
