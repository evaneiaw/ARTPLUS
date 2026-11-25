// src/color_management/color_manipulation.cpp
#include "color_manipulation.h"
#include "color_management_exception.h"
#include "color_manipulation_layer.h"

#include <QtGlobal>

#include <utility>

namespace artplus::color {

ColorManipulation::ColorManipulation() {
    // Default observado no fluxo de recolor (spec §3.2): Perceptual.
    mRenderingIntents.fill(RenderingIntent::Perceptual);
}

ColorManipulation& ColorManipulation::instance() {
    static ColorManipulation sInstance;
    return sInstance;
}

std::vector<ColorManipulation::ProfileLevel>& ColorManipulation::stackFor(CategoryType cat) {
    return cat == CategoryType::Default ? mDefaultLevels : mOverrideLevels;
}

const std::vector<ColorManipulation::ProfileLevel>&
ColorManipulation::stackFor(CategoryType cat) const {
    return cat == CategoryType::Default ? mDefaultLevels : mOverrideLevels;
}

void ColorManipulation::setLevelICCProfile(ColorType ct,
                                           std::shared_ptr<ICCProfile> profile,
                                           bool replace,
                                           CategoryType cat) {
    std::vector<ProfileLevel>& stack = stackFor(cat);
    if (stack.empty()) {
        stack.emplace_back();
    }

    // R3b: o índice do nível é o contador corrente, não o ColorType.
    const int level = static_cast<int>(stack.size()) - 1;
    if (replace) {
        // R3d: substitui o perfil do nível corrente.
        setLevelProfileInternal(stack[level], ct, std::move(profile), true);
    } else {
        // R3d: push — novo nível herda o anterior e recebe o perfil.
        ProfileLevel pushed = stack[level];
        setLevelProfileInternal(pushed, ct, std::move(profile), false);
        stack.push_back(std::move(pushed));
    }
    mCurrentLevel = static_cast<int>(stack.size()) - 1;
}

std::shared_ptr<ICCProfile> ColorManipulation::getActiveICCProfile(ColorType ct,
                                                                   bool useCache,
                                                                   CategoryType cat) const {
    // R4a: caminho de cache (+0x38). Cache vazio = erro, não nullptr silencioso.
    if (useCache) {
        if (!mActiveProfileCache) {
            throw ColorManagementException(
                ColorManagementException::kErrorCodeNoProfile,
                QString::fromLatin1(messages::kNoProfileDefined));
        }
        return mActiveProfileCache;
    }

    // R4b: varredura dos níveis de categoria, do topo para a base.
    const std::vector<ProfileLevel>& stack = stackFor(cat);
    for (int level = static_cast<int>(stack.size()) - 1; level >= 0; --level) {
        const std::shared_ptr<ICCProfile>& candidate = stack[level][static_cast<int>(ct)];
        if (candidate && candidate->isValid()) {
            return candidate;
        }
    }

    // R4b: fallback pelas entradas GCColorLibInfo (sem perfil fabricado).
    for (const ColorLibInfo& info : mColorLibInfos) {
        if (!info.matches(ct, cat)) {
            continue;
        }
        std::shared_ptr<ICCProfile> candidate = info.getProfile();
        if (candidate && candidate->isValid()) {
            return candidate;
        }
    }

    // R4c: nenhum match → exceção (0x124f85), nunca nullptr.
    throw ColorManagementException(ColorManagementException::kErrorCodeNoProfile,
                                   QString::fromLatin1(messages::kNoProfileDefined));
}

RenderingIntent ColorManipulation::activeRenderingIntent(CategoryType cat) const {
    const int index = static_cast<int>(cat);
    if (index < 0 || index >= kCategoryCount) {
        return RenderingIntent::Perceptual;
    }
    return mRenderingIntents[static_cast<std::size_t>(index)];
}

void ColorManipulation::setRenderingIntent(CategoryType cat, RenderingIntent intent) {
    const int index = static_cast<int>(cat);
    if (index < 0 || index >= kCategoryCount) {
        return;
    }
    mRenderingIntents[static_cast<std::size_t>(index)] = intent;
}

bool ColorManipulation::activeBlackPointCompensation() const {
    return mBlackPointCompensation;
}

void ColorManipulation::setBlackPointCompensation(bool enabled) {
    mBlackPointCompensation = enabled;
}

bool ColorManipulation::isActiveCMMEngine(CategoryType cat) const {
    Q_UNUSED(cat)
    // Estado real do backend CMM: a bridge lcms2 não está integrada
    // (ADR-008 Limitação 5), então não há engine ativo a reportar.
    return ColorManipulationLayer::isCmmEngineAvailable();
}

void ColorManipulation::setActiveProfileCache(std::shared_ptr<ICCProfile> profile) {
    mActiveProfileCache = std::move(profile);
}

void ColorManipulation::addColorLibInfo(const ColorLibInfo& info) {
    mColorLibInfos.push_back(info);
}

void ColorManipulation::clearColorLibInfos() {
    mColorLibInfos.clear();
}

void ColorManipulation::setLevelProfileInternal(ProfileLevel& level,
                                                ColorType ct,
                                                std::shared_ptr<ICCProfile> profile,
                                                bool replace) {
    // 0x1800161c0 — efetiva a definição no nível.
    // Spec §5: perfil NULL no SetLevelICCProfile assume substituição por
    // perfil vazio (slot nulo, sem perfil fabricado).
    Q_UNUSED(replace)
    level[static_cast<int>(ct)] = std::move(profile);
    mActiveProfileCache = level[static_cast<int>(ct)];
}

} // namespace artplus::color
