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
| `0x180014bd0` | `InitializeStrings()` | `ColorManipulationLayer` | — (tabela de constantes de `color_management_exception.h`, namespace `artplus::color::messages`) | Carrega mensagens de erro do `.rdata`; no ArtPlus não há chamada de inicialização em runtime |
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
    // R1e — sem chamada de inicialização em runtime no ArtPlus: o equivalente é a
    // tabela de constantes de src/color_management/color_management_exception.h
    // (namespace artplus::color::messages). No binário, as mensagens do .rdata são
    // carregadas por InitializeStrings() (0x180014bd0).
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
| `src/color_management/CMakeLists.txt` | Novo alvo `ColorManagement` (static lib) com link **apenas** em `Qt6::Core` — sem `find_package(lcms2)`; integração lcms2/Pantone adiada (Limitação 5). Investigação sistemática (2026-11) confirmou que lcms2 dev headers/libs e Pantone SDK não estão disponíveis para o toolchain MinGW/MSVCRT + Qt 6.8.3 — see findings below. |
| `src/color_management/color_manipulation_layer.cpp` | Implementa `initialize()`/`shutdown()` conforme pseudocódigo 0x180014b80 |
| `src/color_management/color_manipulation.cpp` | Implementa singleton, stack de perfos, resolução ativa |
| `src/color_management/callback_converter.cpp` | Implementa pipeline de callbacks (pseudocódigo pendente — confiança `media`) |
| `src/color_management/icc_profile_cache.cpp` | Wrapper singleton para cache de perfos |
| `src/color_management/color_lib_info.cpp` | Metadados de cor (Lab/CMYK/spot) |
| `src/color_management/icc_profile.cpp` | Wrapper de `GCICCProfile` (stream, MD5, descrição, versão, ColorType) |
| `tests/color_management/` | Unit tests para inicialização, set/get perfil, exceções, conversão callback |

**Riscos:**
- `GCCallbackConverter::ConvertColor` (0x18000a2f0) tem confiança `media` — pseudocódigo não disponível; implementação inicial baseada na assinatura e inferência; requer validação futura com `ghidra`/`rea` contra v24.
- `FUN_180027c40` e `FUN_1800269b0` sem nomes reais — `initLCMS()` e `initPantone()` são stubs declarados (`TODO(F-008)`) guardados pelas Limitações 4–5. `initLCMS()` grava `sCmmEngineAvailable = false` e `isCmmEngineAvailable()` retorna `false` (nenhuma engine é anunciada); a integração real com `lcms2` e bibliotecas Pantone virá em fase posterior.
- Ausência de evidência comportamental (BLO-004) — UI de Color Management não será implementada até captura CAP-*.

## Investigação de disponibilidade — lcms2 e Pantone (F-008, 2026-11-24)

Esta seção registra a investigação sistemática de disponibilidade/viabilidade das dependências externas
que sustentam as Limitações 4–5, conforme solicitado pelo orquestrador. Toda a investigação é leitura
do ambiente e do repositório; **nenhum** arquivo de `src/`, `tests/` ou evidência foi alterado.

### Evidência da necessidade (binário v24.03.10017)

| Achado | Fonte | Interpretação |
|---|---|---|
| Import `lcms.dll` | `rag/sources/ColorManipulationLayer_strings.txt:1027`; `rag/evidence/F-003/rea/scan_binary.txt:95` | O backend v24 usa Little CMS **v1** (`lcms.dll`), não `lcms2.dll`. |
| RTTI `BCMLittleCMS`, `BCMLittleCMSProfile`, `BCMLittleCMSDLProfile`, `BCMLittleCMSLink` | `rag/sources/ColorManipulationLayer_strings.txt:1336-1342` | Abstração interna de CMM/device-link confirma engine Little CMS no original. |
| Import `mscms.dll` | spec F-008 §7, `imports.txt` | Windows Color System é usado para perfis do sistema. |
| Strings ISO 12647-2, FOGRA53, Pantone | spec F-008 §6; `strings64.txt` | Dados de referência de perfis/spots presentes no binário. |

> Observação de versão: a spec F-008 §7 escreve "lcms.dll (Little CMS)" e o ADR original (limitação 5)
> fala em "lcms2". O binário de referência importa `lcms.dll` (API v1). A decisão abaixo cobre
> **ambas** as variantes: nenhuma está disponível no toolchain atual. Isto é uma correção de
> diagnóstico, **não** uma autorização para implementar engine substituta.

### Resultado da busca no ambiente (comandos e caminhos)

| Alvo de busca | Método | Resultado |
|---|---|---|
| `lcms2.h` / `lcms.h` em todo `C:\` | glob recursivo `**/lcms2.h` | **nenhum arquivo** |
| `liblcms*` / `lcms*.lib` / `lcms*.dll` em WinGet packages | glob `**/*lcms*`, `**/liblcms*` | **nenhum arquivo** |
| lcms em `C:\Qt` (Qt 6.8.3 mingw_64) | glob `**/*lcms*` | **nenhum arquivo** (Qt não distribui lcms2 dev) |
| vcpkg instalado | glob `vcpkg*` em `C:\` | **ausente** (sem porta `lcms2` disponível) |
| Conan instalado | glob `**/*conan*` em WinGet | **ausente** |
| MSYS2 (`C:\msys64`) | glob `**/lcms*` | **diretório inexistente** (sem `mingw-w64-lcms2`) |
| Pantone SDK / libraries | glob `**/*Pantone*` em `C:\` | **nenhum SDK**; apenas paletas de cores XML do CorelDRAW (`PantonePlusSolidCoated.xml` etc.) — dados de paleta, **não** biblioteca de conversão Pantone/ColorLib |
| `find_package(lcms2)` no projeto | grep em `src/`, `CMakeLists.txt` | **nenhum** (decisão prévia já vigente) |

O toolchain canônico (`CMakePresets.json`) é WinLibs POSIX.MSVCRT + Qt 6.8.3 `mingw_64`,
com `Qt6::Core/Gui/Widgets/Test/ZlibPrivate`. Não há pacote lcms2 compatível com esse par
ABI (MSVCRT, não UCRT) pré-instalado, nem gerenciador de pacotes C++ operacional no ambiente.

### Análise de viabilidade das rotas de integração

| Rota | Viabilidade | Razão |
|---|---|---|
| `find_package(lcms2)` com pacote sistema | **Inválida** | Nenhum lcms2 dev instalado; CMake falharia em find_package e quebraria o gate de build. |
| vcpkg `lcms2` | **Inválida no estado atual** | vcpkg não instalado; exigiria bootstrap + port build + política de licença (dependency-license-audit), fora do escopo desta feature. |
| Conan `lcms2` | **Inválida no estado atual** | Conan não instalado; mesmo custo de bootstrap e auditoria de dependência. |
| MSYS2 `mingw-w64-lcms2` | **Inválida no estado atual** | MSYS2 não instalado; além disso, pacotes MSYS2 são UCRT — mistura de heap com o Qt MSVCRT (risco documentado em `AGENTS.md` §5 e `CMakePresets.json`). |
| Build de lcms2 a partir do fonte com o próprio MinGW/MSVCRT | **Tecnicamente possível, mas bloqueada por política** | Exige importar código de terceiros para `src/` ou `tools/`, registrar licença (Little CMS é MIT — compatível), validar ABI MSVCRT, escrever bridge C++ e testes de conversão calibrada com tolerância ΔE. Nenhuma spec F-### cobre a bridge; fazer isso agora seria decisão por inferência e violaria "evidência primeiro" (AGENTS.md §6, regra 1). |
| Usar `mscms.dll` (Windows Color System / WCS) como engine | **Rejeitada** | O binário de referência usa lcms como engine de conversão; WCS é usado apenas para acesso a perfis do sistema. Substituir por WCS mudaria o comportamento (intent, BPC, device-link) sem evidência de equivalência — clone funcional exige o mesmo CMM. |
| Pantone SDK / ColorLib | **Indisponível** | SDK proprietário não encontrado; as paletas XML do CorelDRAW são dados, não API de conversão. Não há caminho de integração sem licença/SDK. |

### Decisão formal (adiamento com registro de bloqueio recomendado)

**Decisão: INTEGRAR DEPOIS (`integrate later`) — não integrar agora, não remover os stubs honestos.**

Justificativa (cada item cita F-008 e sua evidência):

1. F-008 spec §7 e RTTI/imports provam que o original depende de `lcms.dll`/Little CMS e de
   bibliotecas Pantone; porém a engine não é substituível por outra sem mudar comportamento
   (intents, BPC, device-link) — integração *now* exigiria a engine real, que não existe no ambiente.
2. Nenhuma das rotas de integração (pacote, vcpkg, conan, MSYS2) está operacional; a única rota
   tecnicamente viável (build do fonte lcms2 com MSVCRT) é uma mudança arquitetural de dependência
   não coberta por spec/ADR aprovada e exigiria auditoria de licença — decisão fora da autonomia
   desta feature (AGENTS.md §6, regra 1: "evidência primeiro"; regra 8: conflito de contrato vai
   para `docs/agents/CONFLITOS.md`).
3. Os stubs `initLCMS()`/`initPantone()` são **honestos**: retornam `true` para não abortar o
   `initialize()` (que no original só falha se a lib não carregar — aqui não há lib para carregar),
   mas `isCmmEngineAvailable()` reporta `false` e nenhuma capacidade de conversão calibrada é
   anunciada. O auditor confirmou (laudo `F-008-audit-20261124c.md` §6) que não há stub silencioso.
   Remover os stubs sem substituto funcional quebraria o contrato de inicialização (R1) e os
   testes; portanto permanecem até que a bridge real exista.
4. As regras 7 e 9 da spec ficam **parcialmente** implementadas por decisão registrada, não por
   omissão — o laudo de auditoria registra essa parcialidade como ressalva não bloqueante.

**Recomendação ao orquestrador (fora do escopo deste agente):** registrar bloqueio formal em
`docs/agents/BLOQUEIOS.md` — sugestão de ID `BLO-009` — com o texto: "F-008: integração da engine
lcms/lcms2 e de Pantone/ColorLib bloqueada — nenhuma dependência dev disponível para toolchain
MinGW/MSVCRT + Qt 6.8.3; rotas vcpkg/conan/MSYS2 ausentes; build do fonte exige spec+ADR de
dependência e auditoria de licença. Stubs honestos mantidos (isCmmEngineAvailable()==false)."
Este agente **não** edita `docs/agents/` (fora do seu escopo de escrita). A recomendação não altera
o estado comprovado atual da feature, que permanece `auditado` com ressalvas declaradas.

**Critério de desbloqueio (para o orquestrador):** abrir nova spec/ADR de dependência
(dependency-license-audit) cobrindo: (a) escolha lcms v1 vs v2 com evidence do binário v24,
(b) build com toolchain MSVCRT e hash do artefato, (c) bridge C++ isolada atrás de
`CallbackConverter`/`ICCProfileCache`, (d) testes de conversão com tolerância ΔE medida no original.
Somente após esses artefatos os stubs devem ser substituídos e as regras 7/9 marcadas como completas.

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
4. **Inicialização Pantone/ColorLib (`initPantone`, `FUN_1800269b0`)** — Stub honesto mantido; integração real não possível no ambiente (Pantone SDK não encontrado — ver *Investigação de disponibilidade* acima e `docs/decisions/ADR-008-lcms2-pantone-dependency.md`).
5. **Inicialização LCMS/device-link (`initLCMS`, `FUN_180027c40`)** — Stub honesto mantido; integração real não possível no ambiente (lcms2 dev headers/libs não encontrados para MinGW/MSVCRT + Qt 6.8.3 — ver *Investigação de disponibilidade* acima e `docs/decisions/ADR-008-lcms2-pantone-dependency.md`).

---

**Estado:** `aprovado`