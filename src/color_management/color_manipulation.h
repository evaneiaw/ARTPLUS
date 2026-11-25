// src/color_management/color_manipulation.h
#pragma once
#include "icc_profile.h"
#include "color_lib_info.h"
#include <array>
#include <memory>
#include <vector>

namespace artplus::color {

// GCColorManipulation — API de runtime do subsistema de cor.
class ColorManipulation {
public:
    static constexpr int kColorTypeCount = 7;
    static constexpr int kCategoryCount = 4;

    // Um nível do stack contém um slot por ColorType (R3b).
    using ProfileLevel = std::array<std::shared_ptr<ICCProfile>, kColorTypeCount>;

    static ColorManipulation& instance();

    // R3 — 0x180014980. cat == Default usa o stack de +0x20, as demais
    // categorias o stack de +0x8. O índice do nível vem de mCurrentLevel
    // (+0xc). replace == true substitui o slot no nível corrente; false
    // empilha um novo nível (push) herdando o nível anterior.
    void setLevelICCProfile(ColorType ct,
                            std::shared_ptr<ICCProfile> profile,
                            bool replace,
                            CategoryType cat);

    // R4 — 0x180012bf0. useCache == true devolve o cache (+0x38) ou lança
    // ColorManagementException(kErrorCodeNoProfile). useCache == false varre
    // os níveis do stack correspondente (topo para base) e depois as entradas
    // ColorLibInfo; sem match lança a mesma exceção.
    std::shared_ptr<ICCProfile> getActiveICCProfile(ColorType ct,
                                                    bool useCache,
                                                    CategoryType cat) const;

    // Estado real; default Perceptual conforme spec §3.2 (Recolor).
    RenderingIntent activeRenderingIntent(CategoryType cat) const;
    void setRenderingIntent(CategoryType cat, RenderingIntent intent);

    // Estado real; false enquanto a conversão BPC não foi configurada.
    bool activeBlackPointCompensation() const;
    void setBlackPointCompensation(bool enabled);

    // Estado real do backend CMM integrado (bridge lcms — ADR-008 Limitação 5).
    bool isActiveCMMEngine(CategoryType cat) const;

    // Sincroniza o cache de perfil ativo (+0x38).
    void setActiveProfileCache(std::shared_ptr<ICCProfile> profile);

    // Entradas ColorLibInfo usadas na resolução da R4.
    void addColorLibInfo(const ColorLibInfo& info);
    void clearColorLibInfos();

    // Nível corrente do stack (índice em [0, profundidade-1]).
    int currentLevel() const { return mCurrentLevel; }

private:
    ColorManipulation();

    std::vector<ProfileLevel>& stackFor(CategoryType cat);
    const std::vector<ProfileLevel>& stackFor(CategoryType cat) const;

    void setLevelProfileInternal(ProfileLevel& level,
                                ColorType ct,
                                std::shared_ptr<ICCProfile> profile,
                                bool replace);

    // cat == Default → array de +0x20; Override/DeviceLink/Proof → +0x8.
    std::vector<ProfileLevel> mDefaultLevels;
    std::vector<ProfileLevel> mOverrideLevels;
    int mCurrentLevel = 0;

    std::shared_ptr<ICCProfile> mActiveProfileCache; // +0x38

    std::vector<ColorLibInfo> mColorLibInfos;

    std::array<RenderingIntent, kCategoryCount> mRenderingIntents;
    bool mBlackPointCompensation = false;
};

} // namespace artplus::color
