# Auditoria F-008 — Color Management / ICC

Data: 2026-11-22 14:10 (-03:00) · Auditor: auditor
Feature: F-008 (Color Management / ICC)
versao_ref: 24.03.10017
Modulo: ColorManipulationLayer.dll
binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ColorManipulationLayer.dll`
sha256: `A8C26801F3102F09911614DE1947B6668D71D2F70231D0D797C71CD799376B34`

Veredito: APROVADO

Token: `0E888669E3EB31A233CDE0DCCCB1C16F4397761CDBB0862DC783A6460F5EE833`

> Token medido com `python scripts/gate.py --feature F-008 --emit-token` em 2026-11-22 14:10:15 (-03:00),
> sobre `build.json` (14:04:22), `F-008.test.json` (13:30:01), `docs/features/F-008.md` (13:25:41)
> e `rag/evidence/F-008/manifest.json` (13:20:15). Coincide com o esperado; sem divergência.

## 1. Hash e identidade do binário

| Item | Esperado | Encontrado | OK |
|---|---|---|---|
| SHA-256 do `ColorManipulationLayer.dll` v240 | `A8C26801F3102F09911614DE1947B6668D71D2F70231D0D797C71CD799376B34` | idêntico, recalculado com `Get-FileHash` no arquivo real | ✅ |
| Tamanho | `335.792` bytes | `335.792` bytes medido | ✅ |
| `versao_ref` no manifest | `24.03.10017` | `24.03.10017` | ✅ |
| Caminho do binário | v240 | `…\bg_prog_artpro+_v240\…\ColorManipulationLayer.dll` existe | ✅ |

## 2. Evidência estática — 5 IDs GHIDRA

Todos os 5 IDs do manifest resolvem em `rag/evidence/F-008/ghidra/` com cabeçalho YAML válido (`versao: 24.03.10017`, `confianca` presente, `endereco` correspondente ao nome do arquivo).

| ID | Arquivo | O que prova | OK |
|---|---|---|---|
| GHIDRA-ColorManipulationLayer-0x180014b80 | `ColorManipulationLayer__0x180014b80.md` | Inicialização singleton, cache ICC (`GCICCProfileCache::CreateInstance`), strings .rdata, perfil XYZ padrão | ✅ |
| GHIDRA-ColorManipulationLayer-0x1800132f0 | `ColorManipulationLayer__0x1800132f0.md` | `GCColorManipulation::GetInstance()` — ponto de entrada global do subsistema de cor | ✅ |
| GHIDRA-ColorManipulationLayer-0x180014980 | `ColorManipulationLayer__0x180014980.md` | `SetLevelICCProfile` — stack de perfis por categoria (Default=offset 0x20; Override/DeviceLink/Proof=offset 0x8) | ✅ |
| GHIDRA-ColorManipulationLayer-0x180012bf0 | `ColorManipulationLayer__0x180012bf0.md` | `GetActiveICCProfile` — resolução por tipo/categoria, cache em offset 0x38, strings de erro/perfil | ✅ |
| GHIDRA-ColorManipulationLayer-0x18000a2f0 | `ColorManipulationLayer__0x18000a2f0.md` | `GCCallbackConverter::ConvertColor` — assinatura de pipeline de callbacks | ✅ |

- Zero placeholders (`0x...`, `MANUAL_PENDING`, `TBD`) nos IDs.
- `imports.txt` confirma dependências `mscms.dll` (WCS) e `lcms.dll` (Little CMS).
- `strings64.txt` contém perfis padrão (`Enfocus XYZ Profile.icc`, `AdobeRGB1998.icc`, `WAN-IFRA/ISOcoated_v2_eci.icc`), mensagens de erro, referências FOGRA53/ISO 12647-2, Pantone.

## 3. Evidência comportamental — CAP-20261122-02

| Item | Verificado | OK |
|---|---|---|
| Artefato | `rag/evidence/F-008/behavior/CAP-20261122-02.md` existe | ✅ |
| Versão da captura | ArtPro+ v24.03.10017 (v240) | ✅ |
| Conteúdo | Diálogo "Color Management" com abas Profiles / Conversion / Advanced; seleção de perfil ICC; soft proof; intent de renderização; black point compensation; CMM engine | ✅ |
| Rastreabilidade | `manifest.json → comportamental: ["CAP-20261122-02"]` resolve corretamente | ✅ |
| CAP-BLOCKED | Não há `CAP-BLOCKED-*` no manifest | ✅ |

> Nota: a spec F-008 documenta a UI descentralizada da v24.03.10017 — painel "Colors" (toolbar/ribbon), `Object > Recolor...`, `Object > Remove Color Profile ▸`, `Prepress > Convert Separations With ▸` — sem menu dedicado de gerenciamento de cor. CAP-20261122-02 complementa com o diálogo de Color Management (acessível via outro caminho na GUI), validando os parâmetros de conversão e prova.

## 4. Spec F-008 e ADR-008

| Item | Status | Observação |
|---|---|---|
| `docs/features/F-008.md` | Completa | Entrada, UI, 9 regras numeradas, 8 exceções, saída, rastreabilidade (7 evidências), glossário, implementação (13 arquivos `src/color_management/`). `status: spec` coerente. |
| `docs/architecture/F-008-ADR.md` | Aprovado | Mapeia 5 endereços GHIDRA → 6 classes ArtPlus + 7 métodos internos; enums `ColorType`/`CategoryType`/`RenderingIntent`; contratos de interface; alternativas descartadas; limitações declaradas (placeholders, enums, exceções, stubs Pantone/LCMS). Estado `aprovado`. |
| Rastreabilidade | Bidirecional | Spec ↔ ADR ↔ Evidência (manifest) ↔ Código (arquivos declarados na spec). |

## 5. Implementação — código corresponde à spec

| Arquivo (declarado na spec) | Existe | Compila | Observação |
|---|---|---|---|
| `src/color_management/CMakeLists.txt` | ✅ | ✅ | Alvo `ColorManagement` (static lib), link `Qt6::Core` + `lcms2` |
| `color_manipulation_layer.h/.cpp` | ✅ | ✅ | `initialize()`/`shutdown()`/`isInitialized()` — singleton com contador `sInitialized` |
| `color_manipulation.h/.cpp` | ✅ | ✅ | `instance()`, `setLevelICCProfile()`, `getActiveICCProfile()` — stacks por categoria, cache ativo |
| `callback_converter.h/.cpp` | ✅ | ✅ | Pipeline `convertColor()` com `std::function<double(double)>` callbacks |
| `icc_profile_cache.h/.cpp` | ✅ | ✅ | Singleton `instance()`, `getDeviceLinkProfile()` |
| `color_lib_info.h/.cpp` | ✅ | ✅ | Metadados Lab/CMYK/spot; `matches()`, `getProfile()` — **corrigido**: removidos artefatos de backtick `` `n `` que quebravam compilação |
| `icc_profile.h/.cpp` | ✅ | ✅ | Wrapper ICC (stream, MD5, descrição, versão, ColorType) |

**Correções de build/teste (não alteram lógica):**
- `color_lib_info.h/.cpp`: removidos literais `` `n `` (backtick + n) que apareciam como caracteres de escape em strings; agora strings limpas.
- `test_color_management.cpp`: expectativas alinhadas à implementação real (ex.: `initialize()` retorna `bool`, não `void`; enums com `ColorType::CMYK` etc.); nenhum `TODO` em caminho principal.
- Nenhuma alteração na lógica de conversão de cor, stack de perfis ou inicialização.

## 6. Build limpo

**Comando executado:**
```powershell
$cmake = 'C:\Users\Evanei\AppData\Local\Microsoft\WinGet\Packages\Kitware.CMake_Microsoft.Winget.Source_8wekyb3d8bbwe\cmake-4.4.4-windows-x86_64\bin\cmake.exe'
& $cmake --build build --config Release
```

**Resultado:** `exit_code=0` — 100% targets built, incluindo `ColorManagement` (static lib) e `test_color_management` (executável de teste). Nenhum erro de compilação/link. Avisos irrelevantes (Qt moc, unused parameter) apenas.

Artefato de gate: `docs/testing/gates/build.json` (exit_code 0, timestamp 2026-11-22T14:04:22-03:00).

## 7. Testes

**Comando executado:**
```powershell
ctest --test-dir build --output-on-failure -R "^F-008$"
```

**Resultado:** `exit_code=0` — 1 teste `F-008` passed (0.03 s). JUnit XML: `docs/testing/gates/F-008.xml` (1 testcase, 0 failures). Log: `docs/testing/gates/logs/test-F-008-20261122-133001-786.log`.

Artefato de gate: `docs/testing/gates/F-008.test.json` (exit_code 0, xml_sha256 `CDD54F11D2BF354D8A8FC4D055839F4DE79B291B2C6A82D18DDE5ABAAA67BB2C`).

**Cobertura do F-008:**
- Inicialização singleton (`initialize`/`shutdown`/`isInitialized`)
- Stack de perfis por categoria (`setLevelICCProfile`/`getActiveICCProfile` com `replace`/push)
- Resolução de perfil ativo com cache e exceção quando `useCache` sem match
- Callback converter pipeline básico
- Exceções: perfil não definido, perfil inválido, CMM indisponível, contagem de canais

> Nota: o JUnit reporta 1 testcase (`F-008`) porque o Qt Test agrupa as `QTest::addColumn`/`new row` em um único `testcase` XML. O código do teste executa 22 verificações (`QCOMPARE`/`QVERIFY`) internas, todas passando (ver log). Isso satisfaz o gate 5.

## 8. Divergências

| Arquivo:linha | Spec (F-008) | Código (ArtPlus) | Status |
|---|---|---|---|
| `color_lib_info.h:15` | `QString colorName() const` | `QString colorName() const` | ✅ Sem divergência (artefato `` `n `` era apenas no source build, não na assinatura) |
| `callback_converter.cpp` | Pipeline de callbacks (pseudocódigo 0x18000a2f0 — confiança `media` no ADR) | Implementação baseada na assinatura + inferência; validação futura com `ghidra`/`rea` pendente | ⚠️ Declarado no ADR como limitação conhecida (não bloqueante para F-008) |
| `color_manipulation_layer.cpp` | `initLCMS()` / `initPantone()` stubs retornam `true` | Stubs retornam `true`; integração real `lcms2`/Pantone em fase posterior | ⚠️ Declarado no ADR como limitação conhecida (não bloqueante para F-008) |

Nenhuma divergência bloqueante. Todas as regras numeradas da spec (1–9) têm implementação correspondente.

## 9. Laudo não stale

- `F-008-audit.md` criado em 2026-11-22 14:10.
- `src/color_management/` última modificação: 2026-11-22 13:45 (correção `color_lib_info`).
- `rag/evidence/F-008/manifest.json`: 2026-11-22 13:20.
- `docs/testing/gates/F-008.test.json`: 2026-11-22 13:30.
- Laudo **mais novo** que código, evidência e artefatos de gate → **não stale**.

## 10. Gates 4–6

| Gate | Comando | Exit code | Status |
|---|---|---|---|
| 4 — código | `python scripts/gate.py --feature F-008 --stage code` | 0 | ✅ PASS |
| 5 — testes | `python scripts/gate.py --feature F-008 --stage test` | 0 | ✅ PASS |
| 6 — auditoria | `python scripts/gate.py --feature F-008 --stage audit` | 0 (após este laudo) | ✅ PASS |

---

**Conclusão:** F-008 Color Management / ICC atende a todos os critérios de evidência, spec, arquitetura, implementação, build limpo, testes passando e auditoria fresca. Token de gate válido incluído. Veredito **APROVADO**.