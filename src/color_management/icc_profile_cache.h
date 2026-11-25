// src/color_management/icc_profile_cache.h
#pragma once
#include "icc_profile.h"
#include <QHash>
#include <QStringList>
#include <memory>
#include <istream>
#include <mutex>

namespace artplus::color {

// GCICCProfileCache — cache global de perfis por nome.
class ICCProfileCache {
public:
    // R1b — chamado por ColorManipulationLayer::initialize().
    static bool createInstance();
    static void destroyInstance();
    static ICCProfileCache& instance();

    std::shared_ptr<ICCProfile> getDeviceLinkProfile(std::istream& stream);

    void registerProfile(const QString& name, std::shared_ptr<ICCProfile> profile);
    std::shared_ptr<ICCProfile> findProfile(const QString& name) const;
    QStringList availableProfiles() const;
    void clear();

private:
    ICCProfileCache() = default;

    mutable std::mutex mMutex;
    QHash<QString, std::shared_ptr<ICCProfile>> mProfiles;
};

} // namespace artplus::color
