# Auditoria F-003 — Bearer Bar Mark
Data: 2026-11-21 · Auditor: auditor
Veredito: **REPROVADO**

---

## Evidência verificada

| Item | Esperado | Encontrado | OK |
|---|---|---|---|
| `rag/evidence/F-003/manifest.json` | Manifesto com id, versao_ref, binário, sha256, estatico, comportamental, bloqueios | **Pasta `rag/evidence/F-003/` não existe** | ❌ |
| `rag/evidence/F-003/ghidra/DocumentMarks__0x18001E3C0.md` | Evidência estática ctor legado (R2) | Arquivo não encontrado (pasta ausente) | ❌ |
| `CAP-20261119-02` | Captura comportamental criação, UI, geometria | `docs/behavior/BearerBar.md` existe, mas **não há `rag/evidence/F-003/behavior/`** | ❌ |
| `docs/reverse-engineering/DocumentMarks_BEARERBAR_FUNCTIONS.md` | Índice consolidado de funções | Arquivo existe | ✅ |
| Build limpo (`cmake --preset mingw-msvcrt` + `release-mingw`) | Compilação sem erros | **Não executado** (ambiente de auditoria sem toolchain completo) | ⚠️ |
| `ctest --preset unit-tests` | Testes F-003 rodam e passam | **Testes não registrados no CMake/CTest** (`add_test` ausente) | ❌ |
| Spec `docs/features/F-003.md` status `spec` | Requisitos R1–R13, exceções E1–E10, rastreabilidade | Completa, confiança `media` | ✅ |
| ADR `docs/decisions/ADR-002-bearer-bar.md` | Decisões D1–D8, ambiguidades A1–A13 | Aprovado (orquestrador, 2026-11-19) | ✅ |

---

## Build
- **Comando esperado**: 
  ```powershell
  $cmake = 'C:\Users\Evanei\AppData\Local\Microsoft\WinGet\Packages\Kitware.CMake_Microsoft.Winget.Source_8wekyb3d8bbwe\cmake-4.4.4-windows-x86_64\bin\cmake.exe'
  & $cmake --preset mingw-msvcrt
  & $cmake --build --preset release-mingw
  & $cmake --build build --target ArtPlus
  ```
- **Resultado**: **Não executado** durante a auditoria (ambiente Linux/busca limitado). O `CMakeLists.txt` inclui `bearer_bar.cpp/.h` em `PREPRESS_SOURCES` → compila no alvo `ArtPlus`. Preset `mingw-msvcrt` configurado em `CMakePresets.json`. Toolchain WinLibs POSIX.MSVCRT (compatível Qt 6.8.3 mingw_64) declarado.
- **Avisos**: `CMakeLists.txt` força `CMAKE_CXX_COMPILER`/`CMAKE_C_COMPILER` para BrechtSanders.WinLibs se vazio; risco de conflito se preset já os definir.

---

## Testes
- **Arquivo**: `tests/unit/test_bearer_bar.cpp` — 8 casos cobrindo D8 (R2, R4, R5, R6, R7, A1, D4, D4-7b).
- **Registro CTest**: **AUSENTE** — não há `add_executable(bearer_bar_test ...)` nem `add_test(NAME BearerBarTests ...)` no `CMakeLists.txt`.
- **Cobertura do F-003**: 
  - `testDefaults_R2` (R2)
  - `testGeometryTopology_R4_R6` (R4, R6)
  - `testBitmask_R4` (R4 + E6)
  - `testExtend_R6` (R6)
  - `testRegeneration_R7` (R7)
  - `testReferenceBox_A1` (A1)
  - `testPersistence_D4` (D4)
  - `testSingleWriterRegression_D4` (D4 7b — regressão escritor único `cut_mark.cpp`)
  - `testSizeReferenceCoherence_R5` (R5)
- **Passaram**: **N/A** — não executáveis via `ctest --preset unit-tests`.

---

## Divergências

| Arquivo:linha | Spec / ADR | Código | Status |
|---|---|---|---|
| `bearer_bar.h:27-34` | A1–A5 declaradas como ambiguidades com `TODO(F-003)` | `TODO(F-003)` presentes nos campos `referenceBox`, `widthMm`, `extendMm`, `sizeReference`, `direction`, `color` | ✅ Declarado |
| `bearer_bar.cpp:232-236` | R7 geometria PDF+ não derivada → F-003a | `TODO(F-003): v1 aproxima… fórmula fechada fica para F-003a` | ✅ Declarado |
| `bearer_bar.cpp:139-160` | `detachGroup`/`attachGroup` declarados no header | Definidos mas **nunca chamados** (código morto; fluxo usa `attachSide`/`detachSide`) | ⚠️ Limpeza |
| `bearer_bar.cpp:459-468` | `saveToMetadata` mescla chave `bearerBars` preservando outras | Implementado corretamente (mesma estratégia de ADR-002 D4) | ✅ |
| `cut_mark.cpp:466-468` | `CutMarkManager::saveToMetadata` deve mesclar (não sobrescrever) | **Não verificado** — edição autorizada em D6 depende disso | ⚠️ Risco |
| `main_window.cpp:621` | `BearerBarManager::setUndoStack` | Chamado no `ArtPlusMainWindow` ctor | ✅ |
| `main_window.cpp:946-948, 974-976` | `loadFromMetadata` nas duas passadas de carga | Chamado para `bearerBarManager` | ✅ |
| `main_window.cpp:987-989, 1003-1005` | `saveToMetadata` nos dois pontos de save | Chamado para `bearerBarManager` | ✅ |

---

## O que falta para aprovar

- [ ] **Criar `rag/evidence/F-003/`** com `manifest.json` (id, versao_ref, binário, sha256, estatico, comportamental, bloqueios) e arquivos `ghidra/` citados na spec (§7).
- [ ] **Registrar testes no CTest**: adicionar ao `CMakeLists.txt`:
  ```cmake
  add_executable(bearer_bar_test
      tests/unit/test_bearer_bar.cpp
      ${DOCUMENT_SOURCES}
      ${PDF_SOURCES}
      ${PREPRESS_SOURCES}
  )
  target_link_libraries(bearer_bar_test PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::ZlibPrivate)
  add_test(NAME BearerBarTests COMMAND bearer_bar_test)
  set_tests_properties(BearerBarTests PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")
  ```
- [ ] **Executar build limpo + ctest** com saída anexada:
  ```powershell
  & $cmake --preset mingw-msvcrt
  & $cmake --build --preset release-mingw
  ctest --preset unit-tests
  ```
- [ ] **Rodar `scripts/check_version.py`** (regra §0 AGENTS.md — valida referência única v24.03.10017).
- [ ] Remover métodos mortos `attachGroup`/`detachGroup` de `bearer_bar.h/.cpp` (ou usá-los se houver intenção).
- [ ] Confirmar que `CutMarkManager::saveToMetadata` mescla `cutMarks` sem apagar `bearerBars` (teste 7b cobre, mas o código de `cut_mark.cpp` precisa da edição autorizada em D6).

---

## Resumo técnico

**Implementação v1 (ADR-002 D1–D8) está funcional para o escopo declarado:**
- Criação sem modal (`R1`) — `main_window.cpp:1276-1289`.
- Defaults `widthMm=5`, `extendMm=0`, `offsetMm=0`, `locationMask=3`, `direction=1`, `TrimBox` (`R2`).
- Bitmask `Location` 4 bits → 1 faixa por bit (`R4`, `buildGeometry`).
- Geometria de faixas retangulares fora da caixa de referência (`R6`).
- Regeneração substitui conteúdo (`R7`, `regenerate`).
- Coerência `SizeReference`/`Direction` como predicado puro (`R5`, `sizeReferenceCoherent`).
- Undo único via `BearerBarEditCommand` + `ActionList` (`R12`).
- Persistência `.artplus` com `metadata.DocumentMarks.bearerBars` (`D4`).
- UI: ação no menu `Marks`, toolbar, listagem no painel, Inspector mostra parâmetros (`D5`).

**Escopo fora de v1 (declarado em ADR D4, D5, D8):**
- R8–R11 (PDF+ roundtrip, legado `DM-BearerBarParams`, parser `Position`, exceção offset vertical) → F-003b.
- Fórmula fechada retângulo PDF+ (transformação/anchors/escala/guarda 0,01mm) → F-003a.
- Painel `Marks`, dropdown ancoragem, Inspector edível, menu radial, reordenação painel → dono da UI.
- Mark Sets (cópia de página) → F-002.

**Veredito final: REPROVADO** por falha automática de evidência ausente (critério 2) e testes não registrados/executáveis (critério 6). A implementação de código cobre o escopo v1; a reprovação é infraestrutural.