# ADR-008 — Integração de engine CMM (lcms/lcms2) e Pantone em F-008

## Contexto

Spec **F-008** (Color Management / ICC, `docs/features/F-008.md`), módulo `ColorManipulationLayer.dll`
da referência única **v24.03.10017** (`versao_ref: 24.03.10017`). O despacho do orquestrador pediu
uma decisão formal sobre a disponibilidade/viabilidade de LittleCMS 2 e Pantone SDK para o
toolchain canônico do ArtPlus.

Evidência que sustenta a necessidade da dependência (toda ela de `v24.03.10017`):

| Achado | Evidência (F-008 / v24) | O que prova |
|---|---|---|
| Import `lcms.dll` | `rag/sources/ColorManipulationLayer_strings.txt:1027`; `rag/evidence/F-003/rea/scan_binary.txt:95`; spec F-008 §7 | backend v24 depende de Little CMS (API v1 — `lcms.dll`, **não** `lcms2.dll`) |
| RTTI `BCMLittleCMS`, `BCMLittleCMSProfile`, `BCMLittleCMSDLProfile`, `BCMLittleCMSLink` | `rag/sources/ColorManipulationLayer_strings.txt:1336-1342` | abstração interna de CMM/device-link confirma engine Little CMS |
| Import `mscms.dll` | spec F-008 §7, `rag/evidence/F-008/ghidra/imports.txt` | Windows Color System para perfis do sistema (não substitui a engine de conversão) |
| `FUN_180027c40` / `FUN_1800269b0` | GHIDRA-ColorManipulationLayer-0x180014b80; spec F-008 R1c/R1d | `Initialize()` aborta com `false` se a init de lcms (`0x180027c40`) ou Pantone (`0x1800269b0`) falhar |
| SHA-256 do binário | `rag/evidence/F-008/manifest.json` = `A8C26801F3102F09911614DE1947B6668D71D2F70231D0D797C71CD799376B34` | integridade da referência |

Estado atual do código (implementação auditada, laudo `docs/audit/F-008-audit-20261124c.md`):
`initLCMS()` e `initPantone()` são **stubs honestos** (`TODO(F-008)`) que retornam `true` mas não
anunciam capacidade — `isCmmEngineAvailable()` retorna `false`. O módulo `ColorManagement` linka
apenas `Qt6::Core`; não existe `find_package(lcms2)`. A auditoria confirmou que não há stub
silencioso (laudo §6).

## Decisão

**INTEGRAR DEPOIS (`integrate later`) — não integrar agora; manter os stubs honestos até existir
substituto funcional.** Não se trata de "não agora" indefinido: há critério de desbloqueio explícito
(§ Critério abaixo) e recomendação de bloqueio formal ao orquestrador.

Justificativa (cada item cita F-008 e a evidência que o sustenta):

1. F-008 R7/R9 e os imports/RTTI acima provam que o original usa Little CMS como engine de
   conversão. Integrar *agora* exigiria a engine real: substituí-la por outra (ex.: `mscms.dll`/WCS)
   mudaria intents, black-point-compensation e device-link sem evidência de equivalência —
   incompatível com o objetivo de clone funcional da v24 (`AGENTS.md` §1–2).
2. A investigação de ambiente (detalhada em `docs/architecture/F-008-ADR.md`, seção
   *Investigação de disponibilidade*) não encontrou: `lcms2.h`/`lcms.h` em `C:\`, `liblcms*`/`lcms*.lib`
   nos pacotes WinGet, lcms em `C:\Qt` (6.8.3 `mingw_64`), vcpkg, Conan ou MSYS2. Também não
   encontrou Pantone SDK — apenas paletas XML do CorelDRAW (dados, não API de conversão).
3. Rotas de integração disponíveis na teoria são todas inválidas no estado atual: `find_package`
   quebra o build; vcpkg/conan/MSYS2 não estão instalados; MSYS2 além disso produziria bins UCRT
   que misturam heap com o Qt MSVCRT (risco já documentado em `AGENTS.md` §5 e
   `CMakePresets.json`). O build do fonte lcms2 com o próprio MinGW/MSVCRT é tecnicamente possível
   (licença MIT, compatível), mas exigiria importar código de terceiros, auditoria de licença
   (`dependency-license-audit`) e uma bridge C++ coberta por spec — nada disso existe hoje. Decidir
   por conta própria violaria `AGENTS.md` §6 regra 1 ("evidência primeiro") e regra 8 (conflito de
   contrato vai para `docs/agents/CONFLITOS.md`).
4. Os stubs permanecem porque `Initialize()` deve continuar retornando `true` (R1) — no original
   ela só falha se a lib não carregar, e aqui não há lib para carregar — e porque removê-los sem
   substituto quebraria R1 e os 28 testes auditados. A honestidade é preservada: nenhuma capacidade
   de conversão calibrada é anunciada (`isCmmEngineAvailable() == false`).
5. Consequência declarada: regras 7 e 9 da spec F-008 ficam **parcialmente** implementadas por
   decisão registrada (não por omissão), exatamente como o laudo de auditoria registra em §7/§8.

### Mapeamento binário → artefato de decisão

| Função (Ghidra, v24) | Classe/método ArtPlus | Situação da decisão |
|---|---|---|
| `0x180027c40` (`FUN_180027c40`, init CMM/lcms) | `ColorManipulationLayer::initLCMS()` | stub honesto mantido; integração adiada por esta ADR (Limitação 5 da ADR de arquitetura) |
| `0x1800269b0` (`FUN_1800269b0`, init Pantone/ColorLib) | `ColorManipulationLayer::initPantone()` | stub honesto mantido; integração adiada por esta ADR (Limitação 4) |
| `0x180014b80` (`GCColorManipulationLayer::Initialize`) | `ColorManipulationLayer::initialize()` | inalterado — continua chamando os dois stubs e reportando `isCmmEngineAvailable()==false` |
| `0x18000a2f0` (`GCCallbackConverter::ConvertColor`) | `CallbackConverter::convertColor()` | permanece como pipeline puro de callbacks, sem engine externa |
| — (build) | `src/color_management/CMakeLists.txt` | permanece com link só em `Qt6::Core`; **sem** `find_package(lcms2)` nesta decisão |

### Contrato de interface (inalterado por esta decisão)

```cpp
// src/color_management/color_manipulation_layer.h — contrato vigente
class ColorManipulationLayer {
public:
    static bool initialize();            // R1; chama initLCMS()/initPantone()
    static bool isCmmEngineAvailable();  // hoje: false (honesto)
private:
    static bool initLCMS();              // TODO(F-008) — stub até nova ADR de dependência
    static bool initPantone();           // TODO(F-008) — stub até nova ADR de dependência
};
```

Esta ADR **não** altera contrato entre módulos; portanto não exige revisão adicional de contrato
além da já registrada em `docs/architecture/F-008-ADR.md`.

## Alternativas descartadas

1. **Integrar lcms2 agora via `find_package(lcms2)` / vcpkg / conan / MSYS2** — Rejeitado: nenhuma
   dessas dependências existe no ambiente e as rotas que existiriam (MSYS2/UCRT) quebram a ABI
   MSVCRT do Qt 6.8.3. Gate de build falharia. (Evidência: busca em `C:\`, `C:\Qt`, WinGet, `C:\msys64`.)
2. **Substituir a engine por `mscms.dll` (WCS do Windows)** — Rejeitado: o backend v24 usa `lcms.dll`
   como engine; WCS é apenas origem de perfis do sistema. Trocar a engine alteraria intents/BPC/
   device-link sem evidência de equivalência (spec F-008 R9 e exceção de CMM indisponível).
3. **Remover os stubs e fingir capacidade (`isCmmEngineAvailable() == true`)** — Rejeitado: seria stub
   silencioso, proibido por `AGENTS.md` §6 regra 6 e detectado pelo auditor (laudo §6).
4. **Tratar como "não agora / fora do escopo v24"** — Rejeitado: a dependência **existe** na v24
   (imports + RTTI + `Initialize()` falha se CMM não carregar); declarar fora de escopo seria falso.

## Consequências

| Arquivo afetado | Ação |
|---|---|
| `docs/architecture/F-008-ADR.md` | Adicionada seção de investigação de disponibilidade e decisão formal (este ADR a referencia) |
| `src/color_management/**` | **Nenhuma alteração** — stubs honestos e contrato permanecem |
| `CMakeLists.txt` / `src/color_management/CMakeLists.txt` | **Nenhuma alteração** — sem `find_package(lcms2)` |
| `docs/agents/BLOQUEIOS.md` | **Recomendação** de registro de bloqueio `BLO-009` (fora do escopo de escrita deste agente) |

Risco residual: regras 7 e 9 da spec F-008 permanecem parciais (conversão calibrada e mapeamento de
intents para engine não exercitados); nenhuma capacidade falsa é anunciada. Migração de dados: nenhuma.

### Recomendação de bloqueio ao orquestrador

Registrar em `docs/agents/BLOQUEIOS.md` (sugestão `BLO-009`):

> F-008: integração da engine lcms/lcms2 e de Pantone/ColorLib bloqueada — nenhuma dependência dev
> disponível para o toolchain MinGW/MSVCRT + Qt 6.8.3; rotas vcpkg/conan/MSYS2 ausentes; build do
> fonte exige spec+ADR de dependência e auditoria de licença. Stubs honestos mantidos
> (`isCmmEngineAvailable()==false`). Não redistribuir a feature até o desbloqueio.

Este agente **não** edita `docs/agents/`; a recomendação não muda o estado comprovado atual da
feature (`auditado`, laudo `F-008-audit-20261124c.md`, gates 0–6 verdes), que permanece válido — a
decisão é de adiar uma dependência, não de desfazer trabalho auditado.

### Critério de desbloqueio

Abrir nova spec + ADR de dependência (com `dependency-license-audit`) cobrindo:
(a) escolha lcms v1 (`lcms.dll`) vs v2 com base na evidência do binário v24;
(b) build com o toolchain MSVCRT e hash do artefato resultante;
(c) bridge C++ isolada atrás de `CallbackConverter`/`ICCProfileCache`;
(d) testes de conversão com tolerância ΔE medida no original.
Somente após esses artefatos os stubs devem ser substituídos e as regras 7/9 marcadas como completas.

## Estado

`aprovado`

> Referência: spec F-008 (`docs/features/F-008.md`); evidência `rag/evidence/F-008/manifest.json`
> (SHA-256 `A8C26801F3102F09911614DE1947B6668D71D2F70231D0D797C71CD799376B34`); decisão
> detalhada em `docs/architecture/F-008-ADR.md`; auditoria `docs/audit/F-008-audit-20261124c.md`.
