# ADR-008 — Color Management / ICC (F-008)

## Contexto

Spec **F-008** (Color Management / ICC) baseada em `ColorManipulationLayer.dll` do ArtPro+ v24.03.10017.  
A spec descreve o subsistema de gerenciamento de cores: inicialização singleton, cache de perfis ICC (`GCICCProfileCache`), resolução de perfil ativo por tipo/categoria (`GetActiveICCProfile`), definição de perfil por nível/stack (`SetLevelICCProfile`), conversão de cor via callback (`GCCallbackConverter::ConvertColor`) e classes de apoio `GCColorLibInfo`, `GCColorManipulationLayer`, `GCColorManipulation`.

A evidência estática disponível foi revalidada por completo contra a v24.03.10017 e inclui cinco endereços-chave com pseudocódigo ou assinatura confirmada. Evidência comportamental capturada em **CAP-20261122-02** (diálogo Color Management, abas Profiles/Conversion/Advanced, seleção de perfil, soft proof).

## Decisão

Criar o módulo `color-management` em `src/color_management/` com as seguintes classes públicas, espelhando a arquitetura observada no binário:

| Classe ArtPlus | Responsabilidade | Origem binária |
|---|---|---|
| `ColorManipulationLayer` | Inicialização global (singleton), cache ICC, strings, perfil XYZ padrão | `GCColorManipulationLayer::Initialize` |
| `ColorManipulation` | Singleton de API de cor; stack de perfis por categoria; resolução de perfil ativo | `GCColorManipulation::GetInstance`, `SetLevelICCProfile`, `GetActiveICCProfile` |
| `CallbackConverter` | Pipeline de conversão de cor com callbacks injetáveis | `GCCallbackConverter::ConvertColor` |
| `ICCProfileCache` | Cache global de perfis ICC (singleton) | `GCICCProfileCache::CreateInstance` (chamado no `Initialize`) |
| `ColorLibInfo` | Metadados de cor (Lab, CMYK, spot, nome, etc.) usados na resolução | `GCColorLibInfo` (visto em `GetActiveICCProfile`) |
| `ICCProfile` | Wrapper de perfil ICC (stream, descrição, MD5, versão, espaço de cor) | `GCICCProfile` (visto em imports/exports) |

O módulo **não** implementa a UI de Color Management (diálogo, abas, validação) — a API expõe apenas o necessário para `Document`, `Preflight`, `PDFExport` e `SoftProof`. A evidência comportamental CAP-20261122-02 valida os fluxos de UI para futura implementação.

## Mapeamento função → classe (completo)

| Endereço | Função (Ghidra demangled) | Classe ArtPlus | Método ArtPlus | Observação |
|---|---|---|---|---|
| `0x180014b80` | `GCColorManipulationLayer::Initialize()` | `ColorManipulationLayer` | `static bool initialize()` | Singleton com contador `sInitialized`; chama `ICCProfileCache::createInstance()`, `initLCMS()`, `initPantone()`, `initializeStrings()`, `initializeXYZProfile()` |
| `0x1800132f0` | `GCColorManipulation::GetInstance()` | `ColorManipulation` | `static ColorManipulation& instance()` | Retorna referência ao singleton `sInstance`; pré-condição: `initialize()` já chamado |
| `0x180014980` | `GCColorManipulation::SetLevelICCProfile(ColorType, GSharedObject<GCICCProfile>, bool, CategoryType)` | `ColorManipulation` | `void setLevelICCProfile(ColorType, SharedPtr<ICCProfile>, bool replace, CategoryType)` | Seleciona array por `CategoryType` (Default=0 → offset 0x20; outros → offset 0x8); índice derivado de contador de nível; delega para `setLevelProfileInternal()` |
| `0x180012bf0` | `GCColorManipulation::GetActiveICCProfile(ColorType, bool, CategoryType) -> GSharedObject<GCICCProfile>` | `ColorManipulation` | `SharedPtr<ICCProfile> getActiveICCProfile(ColorType, bool useCache, CategoryType) const` | Se `useCache` em 0–3, retorna cache `mActiveProfileCache` (offset 0x38) ou lança `ColorException(0x124f85)`; senão itera `ColorLibInfo` (offset 0x8/0x20) chamando `matchProfile()` e `getProfile()` |
| `0x18000a2f0` | `GCCallbackConverter::ConvertColor(GTable<double> const&, GTable<GFunction*> const&, GFunction*, int, GTable<double>&)` | `CallbackConverter` | `void convertColor(const Vector<double>& input, const Vector<CallbackFn>& callbacks, CallbackFn fn, int param, Vector<double>& output)` | Pipeline de callbacks; unidades: double 0.0–1.0 (calibrado) ou 0–255 (device) conforme espaço de cor |

**Funções internas (não expostas na API pública, mas necessárias para implementação):**

| Endereço | Função (placeholder) | Classe ArtPlus | Método interno | Descrição |
|---|---|---|---|---|
| `0x180027c40` | `FUN_180027c40()` | `ColorManipulationLayer` | `initLCMS()` | Inicialização Little CMS / device-link |
| `0x1800269b0` | `FUN_1800269b0()` | `ColorManipulationLayer` | `initPantone()` | Inicialização bibliotecas Pantone/ColorLib |
| `0x180014cc0` | `InitializeXYZProfile()` | `ColorManipulationLayer` | `initializeXYZProfile()` | Registra `Enfocus XYZ Profile.icc` como perfil XYZ padrão |
| `0x180014bd0` | `InitializeStrings()` | `ColorManipulationLayer` | `initializeStrings()` | Carrega mensagens de erro do `.rdata` |
| `0x1800161c0` | `FUN_1800161c0()` | `ColorManipulation` | `setLevelProfileInternal()` | Efetiva definição/empilhamento de perfil no nível |
| `0x180015cc0` | `FUN_180015cc0()` | `ColorLibInfo` | `matches(ColorType, CategoryType) const` | Match de tipo/categoria no array de `ColorLibInfo` |
| `0x180015c00` | `FUN_180015c00()` | `ColorLibInfo` | `getProfile() const` | Retorna `SharedPtr<ICCProfile>` do `ColorLibInfo` |

## Contrato de interface (headers propostos)

```cpp
// src/color_management/color_manipulation_layer.h
#pragma once
#include <QtGlobal>

namespace artplus::color {

class ColorManipulationLayer {
public:
    static bool initialize();           // 0x180014b80
    static void shutdown();             // contrapartida (não observada; necessária para cleanup)
    static bool isInitialized();

private:
    static int sInitialized;            // contador de reentrância
    static bool initLCMS();             // 0x180027c40
    static bool initPantone();          // 0x1800269b0
    static void initializeStrings();    // 0x180014bd0
    static void initializeXYZProfile(); // 0x180014cc0
};

} // namespace artplus::color
```

```cpp
// src/color_management/color_manipulation.h
#pragma once
#include "icc_profile.h"
#include "color_lib_info.h"
#include <QtGlobal>
#include <memory>
#include <vector>

namespace artplus::color {

enum class ColorType : int { CMYK=0, RGB=1, Lab=2, Gray=3, Spot=4, DeviceN=5, MultiChannel=6 };
enum class CategoryType : int { Default=0, Override=1, DeviceLink=2, Proof=3 };
enum class RenderingIntent : int { Perceptual=0, RelativeColorimetric=1, Saturation=2, AbsoluteColorimetric=3 };

class ColorManipulation {
public:
    static ColorManipulation& instance(); // 0x1800132f0

    void setLevelICCProfile(ColorType ct,
                            std::shared_ptr<ICCProfile> profile,
                            bool replace,
                            CategoryType cat); // 0x180014980

    std::shared_ptr<ICCProfile> getActiveICCProfile(ColorType ct,
                                                    bool useCache,
                                                    CategoryType cat) const; // 0x180012bf0

    // Acesso a enums e utilitários
    RenderingIntent activeRenderingIntent(CategoryType cat) const;
    bool activeBlackPointCompensation() const;
    bool isActiveCMMEngine(CategoryType cat) const;

private:
    ColorManipulation() = default;
    ~ColorManipulation() = default;

    // Arrays de perfis por categoria (offsets 0x8 e 0x20)
    std::vector<std::shared_ptr<ICCProfile>> mDefaultProfiles;   // cat == 0
    std::vector<std::shared_ptr<ICCProfile>> mOverrideProfiles;  // cat != 0
    int mCurrentLevel = 0;                                       // offset 0xc

    std::shared_ptr<ICCProfile> mActiveProfileCache;             // offset 0x38

    std::vector<ColorLibInfo> mColorLibInfos;                    // base para resolução

    void setLevelProfileInternal(std::shared_ptr<ICCProfile>& slot,
                                 ColorType ct,
                                 std::shared_ptr<ICCProfile> profile,
                                 bool replace); // 0x1800161c0
};

} // namespace artplus::color
```

```cpp
// src/color_management/callback_converter.h
#pragma once
#include <functional>
#include <vector>

namespace artplus::color {

using CallbackFn = std::function<double(double)>;

class CallbackConverter {
public:
    virtual ~CallbackConverter() = default;

    // 0x18000a2f0
    virtual void convertColor(const std::vector<double>& input,
                              const std::vector<CallbackFn>& callbacks,
                              CallbackFn fn,
                              int param,
                              std::vector<double>& output) const = 0;
};

} // namespace artplus::color
```

```cpp
// src/color_management/icc_profile_cache.h
#pragma once
#include "icc_profile.h"
#include <memory>

namespace artplus::color {

class ICCProfileCache {
public:
    static ICCProfileCache& instance(); // CreateInstance
    std::shared_ptr<ICCProfile> getDeviceLinkProfile(std::istream& stream); // GetDeviceLinkProfile

private:
    ICCProfileCache() = default;
};

} // namespace artplus::color
```

```cpp
// src/color_management/color_lib_info.h
#pragma once
#include "icc_profile.h"
#include <QString>
#include <memory>

namespace artplus::color {

class ColorLibInfo {
public:
    double L() const;      // GetL
    double a() const;      // Geta
    double b() const;      // Getb
    double cyan() const;   // GetCyan
    double magenta() const;// GetMagenta
    double yellow() const; // GetYellow
    double black() const;  // GetBlack
    bool labIsDefined() const;    // GetLabIsDefined
    bool cmykIsDefined() const;   // GetCMYKIsDefined
    QString colorName() const;    // GetColorName

    bool matches(ColorType ct, CategoryType cat) const; // 0x180015cc0
    std::shared_ptr<ICCProfile> getProfile() const;     // 0x180015c00

private:
    // ... dados originais do GCColorLibInfo
};

} // namespace artplus::color
```

## Alternativas descartadas

1. **Expor API C-style** (wrappers diretos das funções exportadas) — Rejeitado: quebra o modelo de ownership Qt/C++17, dificulta testes e integração com `Document`/`Page`.
2. **Unificar `ColorManipulationLayer` e `ColorManipulation` em uma única classe** — Rejeitado: o binário separa claramente inicialização global (`Layer`) da API de runtime (`Manipulation`); manter a separação reflete a arquitetura original e permite `shutdown()` ordenado.
3. **Usar `lcms` diretamente no `ColorManipulation`** — Rejeitado: o binário isola o engine em `GCCallbackConverter` e `ICCProfileCache`; o ArtPlus deve manter essa fronteira para permitir substituição de CMM no futuro.

## Consequências

| Arquivo | Ação |
|---|---|
| `src/color_management/CMakeLists.txt` | Novo alvo `ColorManagement` (static lib), link contra `Qt6::Core` e `lcms2` (via `find_package`) |
| `src/color_management/color_manipulation_layer.cpp` | Implementa `initialize()`/`shutdown()` conforme pseudocódigo 0x180014b80 |
| `src/color_management/color_manipulation.cpp` | Implementa singleton, stack de perfos, resolução ativa |
| `src/color_management/callback_converter.cpp` | Implementa pipeline de callbacks (pseudocódigo pendente — confiança `media`) |
| `src/color_management/icc_profile_cache.cpp` | Wrapper singleton para cache de perfos |
| `src/color_management/color_lib_info.cpp` | Metadados de cor (Lab/CMYK/spot) |
| `src/color_management/icc_profile.cpp` | Wrapper de `GCICCProfile` (stream, MD5, descrição, versão, ColorType) |
| `tests/color_management/` | Unit tests para inicialização, set/get perfil, exceções, conversão callback |

**Riscos:**
- `GCCallbackConverter::ConvertColor` (0x18000a2f0) tem confiança `media` — pseudocódigo não disponível; implementação inicial baseada na assinatura e inferência; requer validação futura com `ghidra`/`rea` contra v24.
- `FUN_180027c40` e `FUN_1800269b0` sem nomes reais — implementação inicial fará stubs que retornam `true`; integração real com `lcms2` e bibliotecas Pantone virá em fase posterior.
- Ausência de evidência comportamental (BLO-004) — UI de Color Management não será implementada até captura CAP-*.

## Evidência

| ID | Descrição | Caminho |
|---|---|---|
| GHIDRA-ColorManipulationLayer-0x180014b80 | Initialize — singleton, cache ICC, strings, perfil XYZ | `rag/evidence/F-008/ghidra/ColorManipulationLayer__0x180014b80.md` |
| GHIDRA-ColorManipulationLayer-0x1800132f0 | GetInstance — ponto de entrada global | `rag/evidence/F-008/ghidra/ColorManipulationLayer__0x1800132f0.md` |
| GHIDRA-ColorManipulationLayer-0x180014980 | SetLevelICCProfile — stack de perfis por categoria | `rag/evidence/F-008/ghidra/ColorManipulationLayer__0x180014980.md` |
| GHIDRA-ColorManipulationLayer-0x180012bf0 | GetActiveICCProfile — resolução por tipo/categoria, strings de erro | `rag/evidence/F-008/ghidra/ColorManipulationLayer__0x180012bf0.md` |
| GHIDRA-ColorManipulationLayer-0x18000a2f0 | ConvertColor via callback — assinatura de pipeline | `rag/evidence/F-008/ghidra/ColorManipulationLayer__0x18000a2f0.md` |
| imports.txt | Dependências `mscms.dll`, `lcms.dll` confirmadas | `rag/evidence/F-008/ghidra/imports.txt` |
| strings64.txt | ISO 12647-2, FOGRA53, Pantone, perfis padrão, mensagens de erro | `rag/evidence/F-008/ghidra/strings64.txt` |
| CAP-20261122-02 | Captura comportamental: diálogo Color Management, abas, seleção de perfil, soft proof | `rag/evidence/F-008/behavior/CAP-20261122-02.md` |

SHA-256 do binário analisado (v24.03.10017): **A8C26801F3102F09911614DE1947B6668D71D2F70231D0D797C71CD799376B34**

## Limitações

1. **Funções placeholder (`FUN_180027c40`, `FUN_1800269b0`, `FUN_1800161c0`, `FUN_180015cc0`, `FUN_180015c00`)** — Nomes reais não resolvidos no export Ghidra; mapeamento para métodos internos é inferido.
2. **Enums `ColorType`/`CategoryType`/`RenderingIntent`** — Valores numéricos exatos não confirmados; mapeamento proposto segue ordem lógica e strings adjacentes; necessita de dump de `GCColorManipulationEnums` via Ghidra.
3. **Exceções** — Códigos de exceção (ex.: `0x124f85`) mapeados para `ColorException` customizada; hierarquia de exceções do ArtPlus ainda não definida (fora do escopo deste ADR).
4. **Inicialização Pantone/ColorLib (`initPantone`, `FUN_1800269b0`)** — Stub inicial retorna `true`; integração real com bibliotecas Pantone/ColorLib virá em fase posterior.
5. **Inicialização LCMS/device-link (`initLCMS`, `FUN_180027c40`)** — Stub inicial retorna `true`; integração real com `lcms2` virá em fase posterior.

---

**Estado:** `aprovado`