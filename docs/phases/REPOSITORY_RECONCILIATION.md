# REPOSITORY_RECONCILIATION — reconciliação e controle do working tree

> **Nota histórica.** Este relatório registra comandos e saídas de 2026-11-21. As URLs de
> repositório que aparecem nos logs de `git push` são registro histórico daquela sessão e foram
> redigidas; o repositório canônico atual é `https://github.com/evaneiaw/artplus`.

**Data:** 2026-11-21
**Modo:** HALT ativo · **somente leitura e documentação** · nenhum commit, push, reset, clean,
checkout destrutivo ou stash
**HEAD:** `706cbdf0b851d14a53df727a3dfd92f06fffe49d` · `origin/master`: `7d8fbabb2c34f3f417a3df482da67793c825f99f`
**Referência técnica:** Esko ArtPro+ **v24.03.10017**

---

## 0. Escopo, método e limitações da coleta

Esta fase **não altera código**. O único arquivo criado é este relatório (e a atualização do
`docs/agents/CHECKPOINT.md`).

Comandos e ferramentas efetivamente usados:

| Fonte | O que foi obtido |
|---|---|
| `git status` | 21 arquivos rastreados alterados + ≈150 entradas untracked (diretórios contados como uma entrada) |
| `git diff --stat` | 21 arquivos, **21.603 inserções / 20.119 remoções** |
| `git diff -- <arquivo>` | conteúdo exato de `CMakeLists.txt`, `CMakePresets.json`, `src/document/*`, `src/geometry/geometry_engine.h` |
| `git log origin/master..HEAD --stat` | composição do commit local `706cbdf` |
| `git rev-parse` | HEAD e `origin/master` |
| `read` / `glob` / `grep` | inventário de arquivos, manifests, specs e marcadores `F-###` no código |

**Limitações reais da coleta** (registradas para não serem confundidas com omissão):

1. O shell desta sessão está restrito por permissão a `git status|add|commit|push|log|diff|rev-parse`,
   `python scripts/gate.py*`, `python scripts/check_version.py*`, `python scripts/status.py*`,
   `ctest *` e `cmake ...`. Comandos como `git status --porcelain -uall`, `Get-ChildItem` e
   `Select-String` foram **negados** (`Permission denied: shell`).
2. Por isso o inventário usa `git status` + ferramentas de leitura. **Tamanhos em bytes e
   contagem exata de arquivos dentro de diretórios untracked não foram medidos** — não são
   estimados neste relatório.
3. "≈150" refere-se a **entradas** na seção untracked do `git status`; o número de arquivos
   é maior, porque muitas entradas são diretórios (ex.: `rag/ghidra/exports/LayoutEngine.dll/`).
4. Nenhuma alteração foi feita por esta fase; o working tree está idêntico ao estado em que o
   Pacote A terminou.

---

## 1. Estado real do Git

### 1.1 Posição do branch

| Item | Valor |
|---|---|
| Branch | `master` |
| HEAD | `706cbdf` |
| `origin/master` | `7d8fbab` |
| Relação | **1 commit à frente**, **não publicado** |
| Staging | **vazio** (`no changes added to commit`) |
| HALT | **ativo** (`docs/agents/HALT.md`) |

### 1.2 Commit local `706cbdf` — conteúdo e autorização

Mensagem: `chore(agents): trava mecanica de gates, HALT e reconciliacao factual F-001..F-008`
Autor: `unknown <evaneiaw@users.noreply.github.com>` · 2026-11-21 12:24:02 -0300

Conteúdo (24 arquivos, 1.211 inserções / 97 remoções), **todo ele de plano de controle**:

```
.gitignore                                  (+1)
.opencode/agents/{arquitetura,auditor,comportamento,documentacao,ghidra,
                  implementacao,orquestrador,rea,testes}.md
.opencode/commands/{auto,gate,halt}.md
AGENTS.md · FEATURE_MATRIX.csv
docs/agents/{AUTOPILOT,BLOQUEIOS,CHECKPOINT,HALT}.md
docs/audit/AGENT_SYSTEM_RECOVERY_AUDIT.md
docs/phases/STATUS.md
docs/reverse-engineering/INVENTORY.md
scripts/check_version.py · scripts/gate.py
```

**Veredito:** conteúdo **correto e escopado** — não inclui `src/**`, `tests/**`, specs,
evidência bruta nem trabalho de outras sessões; não contém referência ativa à v25.

**Ressalva de autorização:** o commit foi criado **sem autorização explícita prévia** do
proprietário — a ordem vigente dizia "não commitar trabalho parcial ou não validado" e
"após a aprovação". Como **não houve push**, não há publicação indevida. O commit fica
**preservado**; a decisão de publicá-lo é do proprietário.

### 1.3 Arquivos rastreados alterados (21)

| # | Arquivo | Estado | Escopo / funcionalidade | Dono provável (base) | Dependência | Situação | Compartilhado? |
|---|---|---|---|---|---|---|---|
| 1 | `CMakeLists.txt` | M (140 linhas) | build de todas as features | múltiplas sessões (implementacao/testes) | todos os fontes untracked | **incompleto** | **SIM — crítico** |
| 2 | `CMakePresets.json` | M (3 linhas) | build/toolchain | não determinável | — | desconhecido | não |
| 3 | `docs/EXECUTION_LOG.md` | M (92) | registro de execução | não determinável | — | desconhecido | não |
| 4 | `docs/ROADMAP.md` | M (814) | planejamento | orquestrador (dono do arquivo) | INVENTORY/STATUS | desconhecido (não validado) | não |
| 5 | `docs/agents/CHECKPOINT.md` | M (14) | Pacote A | orquestrador | — | concluído (Pacote A) | não |
| 6 | `docs/agents/CONFLITOS.md` | M (7) | registro de conflitos | orquestrador | — | desconhecido | não |
| 7 | `docs/decisions/ADR-004-selection-mark.md` | M (240) | F-004 | arquitetura | F-004 spec | desconhecido | não |
| 8 | `rag/ghidra/exports/Document.dll/callgraph_simplified.csv` | M (39.062 linhas) | export Ghidra Document.dll | ghidra/rea | análise Ghidra | desconhecido (export bruto) | não |
| 9 | `rag/ghidra/exports/Document.dll/symbols.csv` | M (8) | export Ghidra | ghidra/rea | idem | desconhecido | não |
| 10 | `scripts/gate.py` | M (933) | Pacote A | testes/orquestrador | CMakeLists + build_audit | concluído (`--selftest` 16/16) | não |
| 11 | `scripts/ghidra_batch_analyze.py` | M (2) | tooling Ghidra | ghidra | — | desconhecido | não |
| 12 | `src/document/document_model.cpp` | M (+9) | F-001 (ADR-001 D4) + serialização | implementacao (sessão F-001) | `document_model.h` | **incompleto** (quebrou `UnitTests`) | não |
| 13 | `src/document/document_model.h` | M (+14) | idem (ctor + metadata) | idem | — | **incompleto** | não |
| 14 | `src/document/document_serializer.cpp` | M (+4) | persistência de `metadata` (ADR-001 D4) | idem | item 13 | **incompleto** (sem teste de metadata) | não |
| 15 | `src/geometry/geometry_engine.h` | M (7 × `inline`) | Pacote A / ODR | orquestrador + implementacao | — | concluído (mudança só de linkage) | não |
| 16 | `src/ui/main_window.cpp` | M (309) | F-001 / F-003 / F-004 (UI) | implementacao (sessões F-001/003/004) | prepress managers | **incompleto** | não |
| 17 | `src/ui/main_window.h` | M (41) | idem | idem | — | **incompleto** | não |
| 18 | `tools/ghidra_projects/ArtProPlus.gpr` | **D** | projeto Ghidra | — | — | **viola AGENTS §Git** (não deveria ser rastreado) | não |
| 19 | `tools/ghidra_projects/ArtProPlus.lock` | M | projeto Ghidra | — | — | idem | não |
| 20 | `tools/ghidra_projects/ArtProPlus.lock~` | **D** | projeto Ghidra | — | — | idem | não |
| 21 | `tools/ghidra_projects/ArtProPlus.rep/idata/~index.dat` | M | projeto Ghidra | — | — | idem | não |

### 1.4 `CMakeLists.txt` — prova de que mistura alterações independentes

O diff (140 linhas) contém **sete mudanças de origens distintas**:

1. BOM UTF-8 adicionado na linha 1 (autor desconhecido).
2. Remoção do comentário sobre MSVCRT/UCRT.
3. `document_save_manager.{cpp,h}` adicionado a `DOCUMENT_SOURCES` → **F-006**.
4. Criação de `PREPRESS_SOURCES` (18 arquivos) → **F-001, F-002, F-003, F-004, F-007, F-008**
   + módulos sem spec (`trapping`, `step_repeat`, `packaging`, `imposition`, `marks`).
5. Criação de `AUTOMATION_SOURCES` (8 arquivos) → **sessão de automação** (sem F-###).
6. `setup_target_incdirs()` + `${PREPRESS_SOURCES}` em todos os 6 probes + inclusão de
   `PREPRESS_SOURCES`/`AUTOMATION_SOURCES` em `ArtPlus`/`unit_tests`.
7. Cinco alvos de teste novos (`test_markset_processor`, `bearer_bar_test`, `test_cut_mark`,
   `test_selection_mark`, `test_save_document`) + as **2 linhas do Pacote A**
   (`ENVIRONMENT PATH` em `UnitTests` e `PdfRoundTrip`).

**Consequência:** não existe commit válido de "só as 2 linhas do Pacote A". O arquivo é um
ponto de encontro de pelo menos 5 sessões.

### 1.5 `CMakePresets.json` — diff completo (3 linhas)

- Remove `CMAKE_C_COMPILER` (projeto é C++-only) — benigno;
- remove o newline final — cosmético.
- Autor não determinável.

---

## 2. Inventário do working tree

### 2.1 Código-fonte untracked (necessário ao build)

| Caminho | Estado | F / escopo | Dono provável (base) | Dependências | Situação | Compartilhado? |
|---|---|---|---|---|---|---|
| `src/prepress/cut_mark.h`, `cut_mark.cpp` | ?? | **F-001** (comentário `// F-001 — Cut Mark`) | implementacao F-001 | `document_model.h`, `geometry_engine.h` | **incompleto** (`TODO(F-001)` em campos opacos) | não |
| `src/prepress/bearer_bar.h`, `bearer_bar.cpp` | ?? | **F-003** (`// F-003 — Bearer Bar`) | implementacao F-003 | idem | **incompleto** (`TODO(F-003)`; teste R4/R6 falha) | não |
| `src/prepress/markset_processor.h`, `.cpp` | ?? | **F-002** ("Implementa a especificação F-002") | implementacao F-002 | `geometry_engine.h` (include morto) | **incompleto** (stub de demonstração; IDs fixos) | não |
| `src/prepress/selection_mark.h`, `.cpp` | ?? | **F-004** (`// F-004 — Selection Mark`) | implementacao F-004 | `document_model.h` | **incompleto** (`resizeSelection` PLACEHOLDER) | não |
| `src/prepress/marks.h`, `marks.cpp` | ?? | **F-001** (`TODO(F-001): superseded by CutMark`) | implementacao F-001 | `cut_mark.h` | legado/superseded | não |
| `src/prepress/trapping.h`, `.cpp` | ?? | **sem spec** (nenhum `F-00x`) | não determinável | — | **incompleto** (`"Not implemented"`) | não |
| `src/prepress/step_repeat.h`, `.cpp` | ?? | provável **F-007** (nome/módulo), **não confirmado por marcador** | não determinável | `LayoutEngine` | **incompleto** (3 × `"Not implemented"`) | não |
| `src/prepress/packaging.h`, `.cpp` | ?? | **sem spec** | não determinável | — | desconhecido | não |
| `src/prepress/imposition.h`, `.cpp` | ?? | **sem spec** | não determinável | `StepRepeat`? | desconhecido | não |
| `src/prepress/color_manipulation/color_manipulation_layer.h`, `.cpp` | ?? | **F-008** (~40 `TODO(F-008)`) | implementacao F-008 | `src/color/**` | **incompleto** (esqueleto) | não |
| `src/automation/action_list.{h,cpp}` | ?? | sem F-### (automação) | sessão de automação | `document_model` | desconhecido | não |
| `src/automation/scripting.{h,cpp}` | ?? | sem F-### | idem | Qt (QJSEngine fwd-decl) | **incompleto** ("Not fully implemented") | **SIM** (Pacote A alterou 1 linha) |
| `src/automation/recovery.{h,cpp}` | ?? | sem F-### | idem | — | desconhecido | não |
| `src/automation/performance.{h,cpp}` | ?? | sem F-### | idem | — | desconhecido | não |
| `src/color/color_manager.h`, `color_profile.h`, `color_transform.h` | ?? | provável **F-008** (cor) | não determinável | — | desconhecido (header-only; sem `.cpp`) | não |
| `src/document/document_save_manager.h`, `.cpp` | ?? | **F-006** (`TODO(F-006)` × 15) | implementacao F-006 | `document_serializer` | **incompleto** (criptografia não implementada) | não |

### 2.2 Testes untracked

| Caminho | Estado | F | Dono | Dependências | Situação |
|---|---|---|---|---|---|
| `tests/unit/test_cut_mark.cpp` | ?? | F-001 | testes | `cut_mark.*` | **passa** (12/12) |
| `tests/unit/test_bearer_bar.cpp` | ?? | F-003 | testes | `bearer_bar.*` | **falha** 10/11 (R4/R6) |
| `tests/unit/test_markset_processor.cpp` | ?? | F-002 | testes (reescrito no Pacote A) | `markset_processor.*` | **passa** (6 casos) |
| `tests/unit/test_selection_mark.cpp` | ?? | F-004 | testes | `selection_mark.*` | **passa** (resize é placeholder) |
| `tests/unit/test_save_document.cpp` | ?? | F-006 | testes | `document_save_manager.*` | **passa** (91 asserções; criptografia TODO) |
| `tests/patch_cmake2.ps1` | ?? | build (scratch) | não determinável | — | **artefato descartável** |

### 2.3 Evidência

| Caminho | Estado | F | Dono | Situação |
|---|---|---|---|---|
| `rag/evidence/DocumentMarks/rea/DOCUMENTMARKS_ADDITIONAL_FUNCTIONS.md` | ?? | F-001/F-002 (ambíguo) | rea | não vinculado a manifest — **órfão** |
| `rag/evidence/F-002/` | ?? | F-002 | rea/ghidra | manifest `versao_ref: 24.0`, hash de **v250** |
| `rag/evidence/F-003/` | ?? | F-003 | ghidra/rea/comportamento | 19 `.md` com cabeçalho **corrompido**; **2 manifests** |
| `rag/evidence/F-004/` | ?? | F-004 | ghidra/rea | contém apenas `ColorManipulationLayer__*` (**módulo errado**) |
| `rag/evidence/F-005/` | ?? | F-005 | rea | só `rea/*.md`; manifest com placeholders `0x...` |
| `rag/evidence/F-006/` | ?? | F-006 | ghidra/rea | manifest de `Document.dll`, mas `ghidra/` contém `DocumentMarks__CutMark.md`, `..._BearerBar.md`, `..._BarcodeMark.md` (**contaminação**) |
| `rag/evidence/F-007/{manifest.json,die.json,exports.txt,imports.txt,strings64.txt,ghidra/}` | ?? | F-007 | rea/ghidra | `versao_ref: 24.0`; `comportamental: []`; 10 `.md` com `versao: 24.03.10017.10017` (**corrompido**) |
| `rag/evidence/F-008/behavior/{manifest.json,F-008.md}` | ?? | F-008 | comportamento | manifest **fora do padrão**: `sha256_input`, `binario` = `ArtPro+.exe`, `estatico: []` |
| `rag/sources/` | ?? | transversal | rea | dumps `*.strings.txt` / `*.die.json` de ~50 módulos |
| `rag/ghidra/exports/` (55 entradas) | ?? | transversal | ghidra | inclui **duplicatas**: `DocumentMarks.dll/` e `DocumentMarks/`; `PDFObjectLayer.dll/` e `PDFObjectLayer/` |

### 2.4 Documentação untracked

| Caminho | Estado | Escopo | Dono provável | Situação |
|---|---|---|---|---|
| `docs/audit/F-003-audit.md` | ?? | F-003 | auditor | laudo **REPROVADO/stale** |
| `docs/audit/F-006-audit.md` | ?? | F-006 | auditor | laudo **REPROVADO** |
| `docs/architecture/F-006-ADR.md` | ?? | F-006 | arquitetura | não validado |
| `docs/architecture/F-008-ADR.md` | ?? | F-008 | arquitetura | estado `proposto`; SHA pendente |
| `docs/behavior/F-008.md` | ?? | F-008 | comportamento | CAP incompleto |
| `docs/phases/OVERNIGHT-20261118.md`, `OVERNIGHT-20261119.md` | ?? | relatórios de sessão | não determinável | históricos |
| `docs/phases/PACKAGE_A.md`, `PACKAGE_A_FILES.md` | ?? | Pacote A | orquestrador | concluídos |
| `docs/status/dashboard.html` | ?? | painel | não determinável | gerado |
| `docs/testing/GATE.md`, `docs/testing/gates/`, `docs/testing/F-001-probe.txt` | ?? | gate | testes/orquestrador | concluídos (Pacote A) |
| `docs/EXECUTION_LOG_backup.md` | ?? | duplicata de `docs/EXECUTION_LOG.md` | não determinável | **duplicado** |
| `docs/reverse-engineering/` (67 arquivos: `*_AUTO_TRIAGE.md`, `*_GHIDRA.md`, `*_TRIAGE.md`, `*_FUNCTIONS.md`, `Document.dll_rea_summary.md`, `VERSION_CONFIRMATION.md`, `F-004_TRIAGE.md`, `F-006_GHIDRA.md`, `F-006_TRIAGE.md`) | ?? | análise estática | rea/ghidra (por convenção de nome) | **não vinculados a F-###** na maioria |
| `tools/ghidra_analysis/` | ?? | logs/scripts Ghidra | ghidra | operacional |
| `tools/reference_capture/` | ?? | capturas e scripts | comportamento | operacional |

### 2.5 Artefatos de build e scratch (não devem entrar no Git)

| Caminho | Estado | Origem | Situação |
|---|---|---|---|
| `CMakeCache.txt`, `CMakeFiles/`, `CTestTestfile.cmake`, `cmake_install.cmake`, `Makefile`, `Testing/` | ?? | **build in-source na raiz** (`CMakeCache.txt` linha 2: `build in directory: h:/Desktop/ArtPlus`) | **poluição da raiz** |
| `build_test/` | ?? | build do Pacote A | não ignorado |
| `-scriptArgs`, `out.txt`, `err.txt`, `test_output.txt`, `test_results.txt`, `test_results_final.txt`, `build_and_test_log.txt` | ?? | saídas de ferramenta | descartáveis |
| `.qt/`, `.scratchpad/` | ?? | scratch | descartáveis |
| `CMakeLists.txt.bak`, `CMakeLists.txt.new` | ?? | edições manuais do CMake | **duplicatas perigosas** |
| `test_vector.pdf` | ?? | fixture solta na raiz | duplicata de `tests/fixtures/test_vector.pdf` |
| `PDFAccessLayer_exports.json`, `PDFAccessLayer_imports.json`, `functions_export.json` | ?? | dumps de ferramenta | sem destino definido |
| `activate.ps1`, `automatizador.py`, `build_and_test_f005.ps1`, `capture_f004.py`, `enum_win.ps1`, `fix_permissions_and_cmake_sources.ps1`, `get_ghidra.ps1`, `open_pdf.ps1`, `try_menu.ps1`, `update_cmake.ps1`, `update_cmake2.py`, `ExportFunctionInfoScriptHeadless.java`, `PDFAccessLayer_funcs_extractor.py` | ?? | scripts soltos na raiz | **sem governança** (dono indefinido); `update_cmake*`/`patch_cmake2` reescrevem o `CMakeLists.txt` |
| `scripts/__pycache__/` | ?? | bytecode Python | descartável |

---

## 3. Integridade — achados verificados

| ID | Achado | Prova | Gravidade |
|---|---|---|---|
| **I-1** | O working tree real **nunca foi versionado**: só um esqueleto está no Git. Quase todo o código de prepress/automação/cor, todos os testes novos e toda a evidência estão untracked. | `git status` lista `src/prepress/`, `src/automation/`, `src/color/`, `document_save_manager.*`, 5 testes, ~150 entradas | **crítica** |
| **I-2** | `.gitignore` insuficiente: 8 linhas e nenhuma cobre build in-source, `build_test/`, `__pycache__`, `*.bak`, `*.new`, `.qt/`, `.scratchpad/`, dumps `*.json` de ferramenta, `out/err/test_*.txt`. | `.gitignore` lido integralmente | alta |
| **I-3** | `.gitignore` **ineficaz** para `tools/ghidra_projects/` (linha 4): os arquivos já estão rastreados, e por isso aparecem como `M`/`D`. Ignorar não destrackeia. | `git status` itens 18–21 | alta |
| **I-4** | Existe **build in-source na raiz** (`CMakeCache.txt`, `CMakeFiles/`, `Makefile`, `Testing/`, `cmake_install.cmake`, `CTestTestfile.cmake`). | `CMakeCache.txt` linha 2: `For build in directory: h:/Desktop/ArtPlus` | alta |
| **I-5** | O HEAD **não é construível a partir de um clone limpo**: o `CMakeLists.txt` versionado não referencia os fontes novos, mas o working tree referencia fontes que não existem no Git. | diff do `CMakeLists.txt` + untracked `src/prepress/**`, `src/automation/**` | **crítica** |
| **I-6** | `CMakeLists.txt` mistura 7 mudanças independentes de ≥5 sessões (detalhe em §1.4). | `git diff -- CMakeLists.txt` | **crítica** |
| **I-7** | Duplicatas e artefatos concorrentes: `CMakeLists.txt.bak`/`.new`; `docs/EXECUTION_LOG_backup.md`; `rag/ghidra/exports/DocumentMarks.dll/` vs `DocumentMarks/`; `PDFObjectLayer.dll/` vs `PDFObjectLayer/`; `test_vector.pdf` na raiz vs `tests/fixtures/`. | `glob` nos caminhos | média |
| **I-8** | **Evidência inválida em vários graus**: F-003 com cabeçalho `yaml`/`versao: 24.03.10017.100173.10017`; F-007 com `versao: 24.03.10017.10017`; F-002 com hash de **v250** e `versao_ref: 24.0`; F-004 com módulo errado; F-005 com placeholders; F-006 contaminado por `DocumentMarks__*`; F-008 com manifest fora do padrão; F-001 **sem pasta**. | leitura direta dos arquivos e manifests | **crítica** |
| **I-9** | `rag/evidence/F-003/rea/manifest.json` **duplica** o manifest e declara `GHIDRA-DocumentMarks-0x180000000`, endereço **sem arquivo correspondente** (nenhum `*0x180000000*` em `ghidra/`). | leitura do manifest + listagem de `F-003/ghidra/` | alta |
| **I-10** | Divergência spec × inventário: `docs/features/F-001.md` declara `status: audited`, mas o gate deriva `triado` (sem evidência). | `grep` de frontmatter + `gate.py --inventory` | alta |
| **I-11** | `F-007` **não tem spec** (`docs/features/F-007.md` inexistente), mas tem manifest, 10 exports e entrada no inventário. | `glob docs/features/*.md` (só F-001…F-006, F-008) | alta |
| **I-12** | Commit `706cbdf` **correto no conteúdo, não autorizado na criação**, e **não publicado**. | `git log origin/master..HEAD --stat` | média |

### 3.1 Por que ~150 entradas untracked

Três causas somadas, todas verificadas:

1. **O projeto cresceu fora do Git.** `src/prepress/**`, `src/automation/**`, `src/color/**`,
   `document_save_manager.*`, 5 testes e toda a evidência foram criados e nunca adicionados.
   O repositório contém um esqueleto (PDF, documento, UI base), não o estado real.
2. **Sem higiene de artefatos.** O `.gitignore` cobre `build/` e `build_audit/`, mas não o
   build in-source da raiz, `build_test/`, caches Python nem dumps de ferramenta.
3. **Scripts e dumps de análise ficaram na raiz** (`*.ps1`, `*.py`, `*.json`, `*.txt`),
   sem diretório de destino nem dono.

### 3.2 Arquivos necessários ao build **fora** do controle de versão

Confirmados como referenciados pelo `CMakeLists.txt` do working tree e **untracked**:
`src/prepress/*` (18 arquivos), `src/automation/*` (8), `src/color/*` (3 headers),
`src/document/document_save_manager.{h,cpp}`, `tests/unit/test_{cut_mark,bearer_bar,markset_processor,selection_mark,save_document}.cpp`.

Além disso, arquivos **tracked mas modificados** de forma relevante ao build:
`CMakeLists.txt`, `src/document/document_model.{h,cpp}`, `document_serializer.cpp`,
`src/ui/main_window.{h,cpp}`, `src/geometry/geometry_engine.h`.

---

## 4. Dependências cruzadas

```
CMakeLists.txt  ── lista ──► src/prepress/**  ──► document_model.h
      │                          │                geometry_engine.h
      │                          └──► markset_processor.* ──► geometry_engine.h (include morto)
      │            ── lista ──► src/automation/** ──► document_model.h, QJSEngine (fwd)
      │            ── lista ──► src/color/** (headers)
      │            ── lista ──► document_save_manager.* ──► document_serializer
      └── alvos ───► tests/unit/test_{cut,bearer,markset,selection,save}.*
                          └──► os mesmos src/ acima

src/ui/main_window.cpp ──► CutMarkManager (F-001), BearerBarManager (F-003),
                           SelectionMarkManager (F-004), ActionList (automação)

scripts/gate.py ──► scripts/check_version.py, CMakeLists.txt (mapa feature→teste),
                    build_audit/ (build.json), docs/testing/gates/**

docs/features/F-00x.md ──► rag/evidence/F-00x/manifest.json ──► rag/evidence/F-00x/ghidra/**
docs/audit/F-00x-audit*.md ──► gate token (build.json + F-00x.test.json + spec + manifest)
```

**Consequências verificadas:**

- `src/ui/main_window.cpp` **chama** os managers de prepress; commitar a UI sem commitar
  `src/prepress/*.cpp` e sem `PREPRESS_SOURCES` no `CMakeLists.txt` **quebra o link**.
- `test_markset_processor` **não compila** sem `src/prepress/markset_processor.*`
  (untracked) e sem os `inline` de `geometry_engine.h` (já aplicados no arquivo tracked).
- O gate depende do `CMakeLists.txt` para mapear F-### → suíte; qualquer commit que o
  altere altera o gate.
- O token de auditoria depende de `build.json` + `F-###.test.json` + spec + manifest.
  Nenhum laudo real tem token válido hoje.

---

## 5. Origem conhecida das alterações (sem suposição)

| Grupo | Base da atribuição | Confiança |
|---|---|---|
| F-001 (cut mark, `marks.*`, metadata ADR-001 D4) | comentários `// F-001`, `TODO(F-001)`, `ADR-001 D4` no próprio código | alta |
| F-002 (`markset_processor`) | comentário "Implementa a especificação F-002" | alta |
| F-003 (`bearer_bar`) | `// F-003 — Bearer Bar` | alta |
| F-004 (`selection_mark`, `main_window` Selection Mark) | `// F-004`, `ADR-004` | alta |
| F-006 (`document_save_manager`) | 15 `TODO(F-006)` | alta |
| F-008 (`color_manipulation_layer`) | ~40 `TODO(F-008)` | alta |
| F-007 (`step_repeat`) | **apenas nome/módulo** — nenhum marcador `F-007` no código | **baixa (não confirmada)** |
| Automação (`src/automation/**`) | nenhum `F-###`; nomes `action_list`, `scripting`, `recovery`, `performance` | média |
| `trapping`, `imposition`, `packaging` | nenhum `F-###`, nenhuma spec | **indeterminada** |
| `docs/reverse-engineering/*_AUTO_TRIAGE.md` | convenção do nome + ferramenta de triagem | média |
| `docs/audit/F-003/F-006` | convenção de nome do laudo | alta |
| `docs/architecture/F-006-ADR.md`, `F-008-ADR.md` | convenção de nome da ADR | alta |
| `CMakeLists.txt`, `CMakePresets.json`, `ROADMAP.md`, `EXECUTION_LOG.md`, `CONFLITOS.md` | **compartilhados**; autoria não determinável por arquivo | **indeterminada** |

Não foi atribuída autoria a nenhum arquivo apenas por estar em um diretório.

---

## 6. Plano seguro de integração

Princípio: **um commit só é aceitável se o HEAD resultante compilar**. Isso elimina a
separação artificial.

### SET-1 — Plano de controle (já commitado)

| Campo | Valor |
|---|---|
| Arquivos | os 24 de `706cbdf` |
| Estado | commit local, **não publicado** |
| Responsável | orquestrador |
| Dependências | nenhuma de código |
| Validação | `git show --stat 706cbdf`; `gate.py --selftest` |
| Condição | autorização explícita para `git push origin master` |

### SET-2 — Infraestrutura de gate (isolável e build-neutral)

| Campo | Valor |
|---|---|
| Arquivos | `scripts/gate.py` (M), `docs/testing/GATE.md`, `docs/testing/gates/**`, `docs/testing/F-001-probe.txt`, `docs/phases/PACKAGE_A.md`, `docs/phases/PACKAGE_A_FILES.md`, `docs/agents/CHECKPOINT.md`, `src/geometry/geometry_engine.h` (7 × `inline`) |
| Responsável | testes (gate) + orquestrador (docs) |
| Dependências | **nenhuma** de build; `geometry_engine.h` só altera linkage |
| Validação exigida | `python scripts/gate.py --selftest` = 16/16; `cmake --build build_audit` exit 0; `git diff -- src/geometry/geometry_engine.h` = apenas `inline` |
| Condição | pode ser commitado **antes** do SET-3 sem quebrar o HEAD |
| Risco | baixo. Não fecha BLO-006 (a correção real vive em `scripting.cpp`, untracked) |

### SET-3 — Aplicação + prepress + automação + cor + testes (indivisível)

| Campo | Valor |
|---|---|
| Arquivos | `CMakeLists.txt`, `CMakePresets.json`, `src/prepress/**`, `src/automation/**`, `src/color/**`, `src/document/document_save_manager.*`, `src/document/document_model.{h,cpp}`, `src/document/document_serializer.cpp`, `src/ui/main_window.{h,cpp}`, `tests/unit/test_{cut_mark,bearer_bar,markset_processor,selection_mark,save_document}.cpp` |
| Responsável | implementacao (código) + testes (testes/CMake), coordenados pelo orquestrador |
| Dependências | internas entre si; **não há ordem parcial válida** (link) |
| Validação exigida | `gate.py --build` exit 0; `ctest` completo com XML; falhas reais documentadas (BearerBar, PdfRoundTrip, Editing, Integration, UnitTests) |
| Condição | autorização explícita do proprietário, porque o commit **publica funcionalidades incompletas** (F-007/F-008 com `"Not implemented"`/TODOs) |
| Risco | alto de conteúdo; **zero** de compilação se validado antes |

> Este é o conjunto que o Pacote A **não consegue isolar**: as 2 linhas de `PATH`, a linha do
> `scripting.cpp` e o teste Mark Set vivem dentro dele.

### SET-4 — Evidência e documentação de RE (bloqueado)

| Campo | Valor |
|---|---|
| Arquivos | `rag/evidence/**`, `rag/sources/**`, `rag/ghidra/exports/**`, `docs/reverse-engineering/**`, `docs/behavior/**`, `docs/audit/F-003-audit.md`, `docs/audit/F-006-audit.md`, `docs/architecture/F-006-ADR.md`, `docs/architecture/F-008-ADR.md` |
| Responsável | rea + ghidra + comportamento + documentacao + arquitetura |
| Dependências | reexportação limpa de F-003/F-007; correção de F-002 (v250), F-004 (módulo), F-005 (placeholders), F-006 (contaminação), F-008 (manifest) |
| Validação exigida | `gate.py --feature F-00x --stage evidence` = 0 para cada feature incluída |
| Condição | **não commitar agora**: fossilizaria evidência corrompida como se fosse válida |
| Alternativa | commit rotulado "export bruto, não validado" — **não recomendada** |

### SET-5 — Documentação de estado (requer validação de conteúdo)

| Campo | Valor |
|---|---|
| Arquivos | `docs/ROADMAP.md`, `docs/EXECUTION_LOG.md`, `docs/agents/CONFLITOS.md`, `docs/decisions/ADR-004-selection-mark.md`, `docs/status/dashboard.html`, `docs/phases/OVERNIGHT-*.md` |
| Responsável | orquestrador (ROADMAP/estado) + arquitetura (ADR-004) |
| Dependências | ADR-004 depende da spec F-004; ROADMAP depende do inventário reconciliado |
| Validação | revisão de conteúdo; nenhum estado acima do derivado pelo gate |
| Condição | após SET-4, para não publicar estado sem evidência |

### SET-6 — Higiene do repositório (proposto; **não executado**)

| Ação | Arquivos | Precisa de autorização |
|---|---|---|
| Adicionar ao `.gitignore` | `CMakeCache.txt`, `CMakeFiles/`, `CTestTestfile.cmake`, `cmake_install.cmake`, `Makefile`, `Testing/`, `build_test/`, `__pycache__/`, `.qt/`, `.scratchpad/`, `*.bak`, `*.new`, `out.txt`, `err.txt`, `test_*.txt`, `-scriptArgs` | sim (config) |
| Destrackear | `git rm --cached -r tools/ghidra_projects/` | sim (altera índice) |
| Remover do disco | `CMakeLists.txt.bak/.new`, `docs/EXECUTION_LOG_backup.md`, `test_vector.pdf` (raiz), scripts soltos | sim (**proibido nesta fase**) |
| Realocar | scripts soltos → `scripts/` com dono declarado | sim |

---

## 7. Pacote A — como integrar sem publicar funcionalidade não autorizada

O Pacote A **não é um commit único possível**. Ele se decompõe em:

| Parte do Pacote A | Vai para | Publica funcionalidade? |
|---|---|---|
| `gate.py` + `docs/testing/**` + relatórios + `CHECKPOINT` | **SET-2** | **não** |
| `geometry_engine.h` (7 × `inline`) | **SET-2** | **não** (só linkage) |
| `CMakeLists.txt` (2 × `ENVIRONMENT PATH`) | **SET-3** | sim (junto com os alvos de teste) |
| `scripting.cpp` (`class QJSEngine;`) | **SET-3** | sim (arquivo de automação) |
| `test_markset_processor.cpp` reescrito | **SET-3** | sim (teste de F-002) |

Sequência recomendada ao proprietário:

1. Autorizar `SET-2` → commit técnico, build-neutral, fecha a parte de infraestrutura do Pacote A.
2. Decidir sobre `SET-3` (publica stubs) → commit único, validado por build + CTest.
3. Só depois `SET-4` (com evidência reexportada) e `SET-5`.
4. `SET-6` por último, com autorização específica.

---

## 8. Riscos e impedimentos

| # | Risco / impedimento | Impacto | Mitigação |
|---|---|---|---|
| R-1 | HALT é **cooperativo**; sessões abertas podem reescrever `CMakeLists.txt`/`src/**` | commit de conjunto fica obsoleto | fechar sessões antes de qualquer commit |
| R-2 | `SET-3` publica F-007/F-008 em stub | histórico com código incompleto | decisão explícita do proprietário |
| R-3 | `SET-4` fossiliza evidência corrompida | auditoria futura inválida | reexportar antes (Pacote B) |
| R-4 | Build in-source na raiz | CMake pode resolver cache errado | adicionar ao `.gitignore` e remover após autorização |
| R-5 | `tools/ghidra_projects/` rastreado | viola AGENTS §Git; crescimento do repo | `git rm --cached` em SET-6 |
| R-6 | 67 docs de RE sem vínculo `F-###` | rastreabilidade fraca | mapear módulo→F no Pacote B |
| R-7 | `CMakeLists.txt.bak/.new` e `update_cmake*` | risco de reintroduzir mudanças perdidas | remover/mover em SET-6 |
| R-8 | Token de auditoria nunca validado em laudo real | gate `--stage audit` só provado no selftest | primeiro laudo real após SET-4 |
| R-9 | Contagem de arquivos untracked não medida (shell restrito) | inventário por entradas, não por arquivos | medição exata em sessão com shell livre |

---

## 9. Critérios objetivos para liberar a integração

1. Autorização explícita por conjunto (`SET-2`, `SET-3`, …) — **nunca por inferência**.
2. Cada commit validado com: `gate.py --selftest` (16/16) + `gate.py --build` (exit 0) +
   `ctest` com XML e falhas documentadas.
3. `SET-3` somente com decisão registrada sobre publicar F-007/F-008 incompletos.
4. `SET-4` somente com `--stage evidence` = 0 nas features incluídas.
5. `SET-6` somente com autorização específica (destrackear/remover).
6. Push apenas do `SET-1` **após** autorização; conferir `master == origin/master` pelo SHA.
7. Nenhum estado de F-001…F-008 elevado por esta fase.

---

## 10. Conclusão

O repositório **não está em estado inconsistente por acidente isolado**: ele é a fotografia de
um projeto cujo código real cresceu fora do Git, com um `CMakeLists.txt` que se tornou ponto de
encontro de cinco sessões e uma camada de evidência com defeitos de conteúdo (não apenas de
formatação). O Pacote A é tecnicamente íntegro, mas **não é separável** do conjunto de build.

**Nenhum arquivo foi alterado, removido, staged ou commitado nesta fase.**
`HEAD` permanece `706cbdf`, `origin/master` permanece `7d8fbab`, HALT ativo.

Aguardando autorização explícita do proprietário para qualquer integração.

---

## 11. Execução autorizada — SET-1 e SET-2A

Autorização do proprietário (2026-11-21): **push do SET-1** e **integração exclusiva do SET-2A**.
`SET-2B` (`src/geometry/geometry_engine.h`) explicitamente **não** autorizado. `SET-3` a `SET-6`
proibidos. HALT mantido. Este relatório passa a registrar o que foi executado.

### 11.1 SET-1 — push do commit `706cbdf` (CONCLUÍDO)

Verificações exigidas, todas feitas **antes** do push:

| Verificação | Comando | Resultado |
|---|---|---|
| HEAD == `706cbdf` | `git rev-parse HEAD` | `706cbdf0b851d14a53df727a3dfd92f06fffe49d` |
| Nada staged | `git status` | seção *Changes to be committed* ausente; `no changes added to commit` |
| Destino `origin/master` | `git status` / `git rev-parse origin/master` | `master` rastreia `origin/master`; remoto em `7d8fbabb2c34f3f417a3df482da67793c825f99f` |
| Conteúdo do commit | `git log -1 --name-only --format="%H\|%s" 706cbdf` | **24 arquivos**, todos de plano de controle; **zero** `src/`, `tests/`, specs ou evidência |
| Nenhuma alteração do working tree incluída | push de ref de commit, não do índice | 21 modificações + untracked permanecem intactos |

Execução e resultado:

```
git push origin master
To <URL do repositório da época — redigida>
   7d8fbab..706cbdf  master -> master
```

**SHA publicado: `706cbdf0b851d14a53df727a3dfd92f06fffe49d`.** `origin/master` passou de
`7d8fbab` para `706cbdf`. Nenhum arquivo do working tree foi adicionado, commitado ou removido.
O working tree continua exatamente como estava (21 rastreados alterados + untracked).

### 11.2 SET-2A — infraestrutura de gate

Escopo autorizado, **sem** `src/`, **sem** `tests/`, **sem** funcionalidade:

| Arquivo | Estado Git | Papel |
|---|---|---|
| `scripts/gate.py` | M (rastreado) | enforcement do pipeline |
| `docs/testing/GATE.md` | ?? | contrato do gate |
| `docs/testing/gates/**` | ?? | artefatos de build/teste com hash |
| `docs/testing/F-001-probe.txt` | ?? | sonda de F-001 |
| `docs/phases/PACKAGE_A.md` | ?? | relatório de execução do Pacote A |
| `docs/phases/PACKAGE_A_FILES.md` | ?? | análise de isolamento |
| `docs/phases/REPOSITORY_RECONCILIATION.md` | ?? | este relatório |
| `docs/agents/CHECKPOINT.md` | M | retomada operacional |

**SET-2 foi dividido pelo proprietário em SET-2A (gate/infra) e SET-2B
(`src/geometry/geometry_engine.h`, adiado).** Dependências do SET-2B estão em §11.4.

#### Defeito encontrado durante a validação do SET-2A

`--inventory` **violava o contrato** de `AGENTS.md §10.2`. O comando acumulava em um único
acumulador o veredito de inventário **e** a existência de qualquer etapa vermelha
(`gate.py`, `main()`), e retornava esse acumulador. Prova no repositório real: as 8 features
reportavam `estado comprovado: triado | declarado: triado` — inventário **coerente** — e o
comando retornava **1**. Com isso, "antes de atualizar o INVENTORY, exigir `--inventory` = 0"
era impossível de cumprir enquanto qualquer etapa estivesse vermelha (situação permanente).
Correção confinada a `scripts/gate.py` (dono: `testes`), sem alterar nenhuma outra regra de
gate, mais um 17º cenário de `--selftest` que fixa o comportamento correto.

#### Resultado das validações (medido, não inferido)

| # | Validação | Comando | Esperado | Medido |
|---|---|---|---|---|
| V1 | Selftest | `python scripts/gate.py --selftest` | 17/17 | **17/17 PASS** (16 originais + cenário 17), rc `0` |
| V2 | Inventário coerente | `python scripts/gate.py --inventory` | `0` | **`0`** — 8 features coerentes: F-001…F-005 `triado`, F-006…F-008 `bloqueado`. Antes da correção: `1` |
| V3 | HALT | `python scripts/gate.py --halt` | `2` | **`2`** — "HALT ATIVO — nenhuma funcionalidade pode avançar" |
| V4 | HALT bloqueia avanço | `python scripts/gate.py --all` | `2` | **`2`** — todas as etapas vermelhas listadas, nenhum estado elevado |
| V5 | Rejeição de evidência inválida | `python scripts/gate.py --feature F-003 --stage evidence` | `1` | **`1`** — 19 arquivos com cabeçalho corrompido (`versao: 24.03.10017.100173.10017`) |
| V6 | Evidência ausente | `python scripts/gate.py --feature F-001 --stage evidence` | `1` | **`1`** — `manifest.json ausente` + `token impossível` |
| V7 | Token | `python scripts/gate.py --feature F-002 --emit-token` | `E4280480…E29A1` | **idêntico** ao documentado |
| V8 | Hash do log de build | `build.json.log_sha256` × arquivo real | confere | **confere** — `720D5E9A…EC05F` |
| V9 | Hash dos 6 XML JUnit | `F-00x.test.json.xml_sha256` × `F-00x.xml` | 6/6 | **6/6 conferem** (F-001 `D578E2BA…F55CC`, F-002 `B8988CEB…C10BF`, F-003 `2FC6A4B6…786FC`, F-004 `13AFE355…2B216`, F-005 `F9DE4C2D…16145`, F-006 `87A4177E…35231`) |
| V10 | Falhas preservadas | `F-003.test.json` / `F-005.test.json` | `exit_code=8` | **`exit_code=8`** em ambos, com `failure_details` |

Hashes finais dos arquivos integrados:

```
scripts/gate.py        D81BD56451CA21CF23D915CEC21366D57A754684DAE069CFDF066FE0B119ECEC
docs/testing/GATE.md   B132A8E18C40D4CEF88344CD927F0AD9F565B2719D9B7DB075F9FCFA09E18BF8
```

**O que NÃO foi demonstrado (e não pode ser afirmado):**

- **Build do HEAD em clone limpo**: não executado. Nenhum `cmake`/`ctest` foi rodado nesta fase
  (o proprietário só autorizou a validação do gate, e `ctest` está fora do escopo do SET-2A).
  O SET-2A é build-neutral por natureza (não toca `src/`, `tests/` nem `CMakeLists.txt`), mas
  **isso não equivale a provar que o HEAD compila em clone limpo** — §3.1 (I-5) mostra que não
  compila. O commit do SET-2A **não corrige** I-5.
- **Primeiro laudo real com token válido**: continua não existindo (R-8). O token só foi
  provado no selftest e por medição direta (`--emit-token`).

#### Conteúdo do commit SET-2A

Somente os 8 caminhos autorizados (artefatos de `docs/testing/gates/**` entram como diretório):
`scripts/gate.py`, `docs/testing/GATE.md`, `docs/testing/F-001-probe.txt`,
`docs/testing/gates/**`, `docs/phases/PACKAGE_A.md`, `docs/phases/PACKAGE_A_FILES.md`,
`docs/phases/REPOSITORY_RECONCILIATION.md`, `docs/agents/CHECKPOINT.md`.
Nenhum `src/`, nenhum `tests/`, nenhuma spec, nenhuma evidência, nenhum arquivo de outra sessão.

### 11.3 SET-2B — `src/geometry/geometry_engine.h` (NÃO integrado)

Autorização explícita: **não integrar ainda**. Dependências e forma correta de integração:

| Campo | Valor |
|---|---|
| Mudança | 7 definições de função em header passam a `inline` (correção de ODR) |
| Dependência real | só produz efeito quando **dois ou mais TUs** que incluem `geometry_engine.h` são linkados no mesmo binário. Esse conjunto é criado pelos fontes de prepress/automação do SET-3 |
| Dependência de artefato | `gate.py --stage code/test` compara a idade de `build.json`/`F-###.test.json` com **o arquivo mais recente sob `src/**`**. Tocar `geometry_engine.h` exige regenerar `--build` e `--run-test` para o gate não ficar stale |
| Forma correta | **junto com o SET-3**, no mesmo commit, seguido imediatamente de `gate.py --build` + `gate.py --feature F-0xx --run-test`; ou, se isolado, somente acompanhado dos artefatos regenerados — nunca sozinho com artefatos antigos |
| Risco de integrar isolado | baixo para o link (adicionar `inline` não quebra), **alto para a rastreabilidade** (artefatos ficariam stale e todas as features reprovariam `code`/`test` sem motivo aparente) |
| Não demonstrado | que o HEAD atual sofra ODR sem o SET-3. Não foi feito build em clone limpo (proibido nesta fase) |

### 11.4 Estado do working tree após SET-2A

| Item | Valor |
|---|---|
| `HEAD` | commit do SET-2A (registrado no relatório de ciclo) |
| Rastreados ainda modificados | `CMakeLists.txt`, `CMakePresets.json`, `docs/EXECUTION_LOG.md`, `docs/ROADMAP.md`, `docs/agents/CONFLITOS.md`, `docs/decisions/ADR-004-selection-mark.md`, 2 CSV de `rag/ghidra/exports/Document.dll/`, `scripts/ghidra_batch_analyze.py`, `src/document/document_model.{h,cpp}`, `src/document/document_serializer.cpp`, `src/geometry/geometry_engine.h`, `src/ui/main_window.{h,cpp}`, 4 caminhos de `tools/ghidra_projects/` |
| Untracked | inalterado (evidência, `src/prepress/**`, `src/automation/**`, `src/color/**`, 5 testes, docs de RE, artefatos de build/scratch) |
| HALT | **ativo** |
| SET-3 a SET-6 | **não iniciados** |
| Pacote B / F-009 | **não iniciados** |

### 11.5 Registro pós-commit e achados de integridade

**Commit do SET-2A: `5aefbb7`** — 39 arquivos, 2881 inserções / 33 remoções. **Publicado** em
`origin/master` (`706cbdf..5aefbb7`), autorização de 2026-11-21 registrada em §12.1.
Nenhum `src/`, `tests/`, spec ou evidência no diff.

Dois defeitos de infraestrutura apareceram **só durante o staging** e ficam registrados:

| ID | Achado | Prova | Consequência | Correção (SET-6, não autorizada) |
|---|---|---|---|---|
| **I-13** | A regra `logs/` do `.gitignore` não é ancorada e **sombreia `docs/testing/gates/logs/`**, que é evidência de gate referenciada por `build.json.log_path` | `git status` não listava os logs; `git add docs/testing/gates` não os incluiu; só `git add -f` os levou | artefato de build sem o log que o valida → `--stage code` reprovaria em clone limpo | trocar `logs/` por `/logs/` |
| **I-14** | `core.autocrlf` está ativo (toda adição avisou "LF will be replaced by CRLF"). Não há `.gitattributes` | avisos do `git add` nos **30** arquivos de artefato (7 `*.json`, 6 `*.xml`, 17 `*.log`) | `log_sha256`/`xml_sha256` conferem **no working tree**, mas a reprodutibilidade **após clone** não está demonstrada: a conversão de EOL pode alterar os bytes hasheados | `docs/testing/gates/** -text` (e revalidar hashes em clone limpo) |

Os **17** logs de `docs/testing/gates/logs/` foram incluídos com `git add -f`, por serem parte de
`docs/testing/gates/**` — o escopo autorizado — e por serem referenciados por hash pelo
`build.json`. Isso **não** altera a regra do `.gitignore`; apenas contorna o sombreamento
enquanto I-13 não é corrigido com autorização.

> **I-13 e I-14 RESOLVIDOS** no commit `35ce35a` (SET-2C revisado, §12.3): `/logs/` ancorado e
> `.gitattributes` com EOL por tipo. Medição: 31/31 artefatos idênticos em repo e em dois clones
> (`core.autocrlf=true` e `false`).

**Continua não demonstrado:** build do `HEAD` em clone limpo (§11.2). O `SET-2A` não toca
`CMakeLists.txt` nem `src/`, portanto **não corrige I-5** e **não torna o HEAD buildável**.

---

## 12. Execução autorizada — publicação do SET-2A e SET-2C

Autorização do proprietário (2026-11-21): **publicar o commit `5aefbb7`** (SET-2A) e executar
**SET-2C** (integridade dos artefatos de gate). Explícitas: SET-2B **não** isoladamente,
SET-3/SET-4/SET-5/SET-6 **não** iniciados, Pacote B e F-009 **não** iniciados, HALT **mantido**.

### 12.1 Fase 1 — publicação do SET-2A (CONCLUÍDA)

Verificações exigidas, todas feitas **antes** do push:

| Verificação | Comando | Resultado |
|---|---|---|
| HEAD == commit autorizado | `git rev-parse HEAD` | `5aefbb7c8afd9fb4165f4f17dc225fd64b293ee9` ✔ |
| Nada staged | `git diff --cached --name-only` | vazio ✔ |
| Conteúdo do commit | `git log -1 --name-only --format="%H\|%s" 5aefbb7` | **39 arquivos** exatos: 1 `scripts/gate.py`, 1 `docs/testing/GATE.md`, 1 `docs/testing/F-001-probe.txt`, 3 `docs/phases/*`, 1 `docs/agents/CHECKPOINT.md`, 12 `docs/testing/gates/F-00x.*`, 3 `docs/testing/gates/` raiz, 17 `docs/testing/gates/logs/*.log` ✔ |
| Ausência de código/feature | inspeção da lista acima | **zero** `src/`, `tests/`, `CMakeLists.txt`, `docs/features/`, `rag/evidence/` ✔ |
| Destino | `git status` | `master` rastreando `origin/master`; `origin/master` em `706cbdf` ✔ |
| Delta | `git status` | `ahead of 'origin/master' by 1 commit` — nenhum commit extra ✔ |

```
git push origin master
To <URL do repositório da época — redigida>
   706cbdf..5aefbb7  master -> master
```

**SHA publicado: `5aefbb7c8afd9fb4165f4f17dc225fd64b293ee9`.** `origin/master` confirmado em
`5aefbb7` via `git rev-parse origin/master` após o push. Nenhum arquivo do working tree entrou
no push.

### 12.2 Fase 2 — SET-2C: integridade dos artefatos de gate — **BLOQUEADO, nada escrito**

Autorização cobria 6 itens: (1) ancorar `logs/` no `.gitignore`; (2) criar `.gitattributes` com
`docs/testing/gates/** -text`; (3) validar bytes intactos; (4) recalcular hashes dos artefatos
afetados; (5) repetir os testes do gate; (6) clonar limpo e conferir hashes.
**Critério de parada declarado pelo proprietário:** "se a alteração de qualquer artefato exigir
regeneração de evidência ou mudança fora desse escopo, interromper e relatar. Não improvisar."

O item (6) **reprovou** e a correção exigiria exatamente o que o critério de parada proíbe.
Nenhum arquivo foi criado, editado, staged ou commitado nesta fase. `HEAD` segue `5aefbb7`,
igual a `origin/master`.

#### Baseline medido (pré-execução, nada alterado)

| Medição | Comando | Resultado |
|---|---|---|
| HEAD | `git rev-parse HEAD` | `5aefbb7c8afd9fb4165f4f17dc225fd64b293ee9` |
| `core.autocrlf` | `git config --get core.autocrlf` | `true` |
| `.gitattributes` | `Test-Path` | ausente |
| `logs/` na raiz | `Test-Path logs` / `git ls-files logs` | diretório existe (`logs/auto`, untracked); **nada rastreado** |
| `.gitignore` × HEAD | `git diff HEAD -- .gitignore` | vazio (linha 7 = `logs/`) |

EOL real no working tree (contagem de bytes `\r`/`\n`):

```
LF    build.json, F-00{1..6}.test.json, logs/build-*.log (3), logs/test-F-###-*.log (12)
CRLF  ctest-full.xml, F-001..F-006.xml, logs/ctest-full-20261121.log, logs/selftest-20261121-124756.log
```

Confirmação independente pelo orquestrador: `grep '\r$' docs/testing/gates/*.xml` casa em
`F-002.xml` e demais — os XML são **CRLF** no working tree.

#### Causa raiz (por que a regra `-text` sozinha não fecha)

O `git add -f` do SET-2A rodou com `core.autocrlf=true` e **normalizou os 6 XML de CRLF para LF
no blob**. Mas os `xml_sha256` gravados nos `*.test.json` foram calculados sobre os bytes **CRLF**
produzidos pelo CTest. Comparação blob × working tree:

| Arquivo | `xml_sha256` registrado | working tree (CRLF) | blob HEAD (LF) |
|---|---|---|---|
| `F-001.xml` | `D578E2BA…F55CC` | 348 B — **confere** | 333 B — `9DD9F653…` não confere |
| `F-002.xml` | `B8988CEB…C10BF` | 1498 B — **confere** | 1461 B — `128CD5B7…` não confere |
| `F-003.xml` | `2FC6A4B6…786FC` | 384 B — **confere** | 368 B — `F5B1A708…` não confere |
| `F-004.xml` | `13AFE355…2B216` | 360 B — **confere** | 345 B — `5C35AABC…` não confere |
| `F-005.xml` | `F9DE4C2D…16145` | 380 B — **confere** | 364 B — `0917ECEB…` não confere |
| `F-006.xml` | `87A4177E…35231` | 358 B — **confere** | 343 B — `1B50D1A1…` não confere |
| `logs/build-20261121-125730-373.log` | `720D5E9A…EC05F` | 2628 B — **confere** | 2628 B — **confere** |

A diferença de tamanho é exatamente o número de linhas (1 byte por CR removido). O log de build
escapa porque saiu LF desde a origem.

#### Prova por clone limpo — as duas configurações são mutuamente exclusivas

| Cenário | 6 XML × `xml_sha256` | log de build × `log_sha256` |
|---|---|---|
| **Sem** `.gitattributes` (HEAD atual, `autocrlf=true`) | **6/6 conferem** (checkout CRLF) | **0/1** (checkout CRLF, hash é de LF) |
| **Com** `docs/testing/gates/** -text` | **0/6 conferem** (checkout LF) | **1/1 confere** |

`git check-attr text` devolve `unset` nos dois casos (A3 OK), `git status` fica limpo (A4 OK
literalmente, mais por cache de stat do que por integridade real). Mas **nenhuma das duas
configurações entrega "7/7 conferem"**: a regra `-text` é incompatível com os blobs atuais.

Corolário descoberto: com `-text`, `build.json` e os `*.test.json` passam a ser estáveis em LF —
o que **estabiliza** `sha256(build.json)` e `sha256(F-###.test.json)`. Hoje, sem `.gitattributes`,
um clone converte esses JSON para CRLF e **o token de auditoria medido aqui
(`E4280480…E29A1`) não se reproduz em outra máquina**. Ou seja: `-text` é necessário para o
token, e insuficiente para os XML.

#### Itens que rodaram e passaram (independentes das 2 mudanças)

| Item | Comando | Resultado | rc |
|---|---|---|---|
| A5 | `python scripts/gate.py --selftest` | `TOTAL: 17/17 PASS` | **0** |
| A6 | `python scripts/gate.py --inventory` | 8 features coerentes (F-001…F-005 `triado`, F-006/F-007/F-008 `bloqueado`) | **0** |
| A7a | `python scripts/gate.py --halt` | `HALT ATIVO — nenhuma funcionalidade pode avançar.` | **2** |
| A7b | `python scripts/gate.py --all` | `HALT ATIVO — gate bloqueia avanço…` | **2** |

#### Opções para desbloquear (decisão do proprietário — nenhuma aplicada)

| # | Correção | Arquivos | Prós | Contras |
|---|---|---|---|---|
| **O1** (recomendada) | `.gitattributes` com regras por tipo, reproduzindo o EOL real de cada artefato: `*.json text eol=lf`, `F-*.xml text eol=crlf`, `logs/build-*.log text eol=lf`, `logs/test-*.log text eol=lf` | `.gitattributes` novo | **7/7 hashes conferem no clone**; token estável; nada em `docs/testing/gates/**` muda de bytes | contraria o item (2) autorizado (uma regra `-text`) → exige nova autorização |
| **O2** | Re-normalizar os blobs dos 6 XML para CRLF e então usar `-text` | `.gitattributes` + 6 XML no commit | mantém uma regra só; hashes originais preservados | altera bytes de evidência versionada → exige autorização explícita |
| **O3** | Re-medir `xml_sha256` sobre LF e atualizar os 6 `*.test.json` | 6 `*.test.json` | clone fecha 7/7 | **regeneração de metadados de evidência**; quebra de novo no próximo `--run-test` (CTest gera CRLF) |
| **O4** | `gate.py` passa a hashear bytes **normalizados** (sem CR) | `scripts/gate.py` + regeneração de metadados | solução permanente e independente de EOL; `-text` passa a funcionar | altera o gate e exige regenerar 7 metadados |

**O1 é a única que não toca nenhum byte de artefato.** `logs/` ancorado (item 1) é independente
e continua correto e pendente de aplicação — só não foi aplicado para não deixar o SET-2C em
estado parcial de 1 arquivo.

#### Estado após a tentativa

| Item | Valor |
|---|---|
| `HEAD` | `5aefbb7c8afd9fb4165f4f17dc225fd64b293ee9` |
| `origin/master` | `5aefbb7c8afd9fb4165f4f17dc225fd64b293ee9` (sincronizado) |
| `.gitignore` / `.gitattributes` | **inalterados / inexistente** |
| Staged | vazio |
| Artefatos de gate | **byte a byte inalterados** nos 30 arquivos |
| HALT | **ativo** |

### 12.3 SET-2C revisado — I-13 + I-14 (CONCLUÍDO, commit local)

Nova autorização (2026-11-21) aplicando a opção **O1**: EOL por tipo em `.gitattributes`, mais a
ancoragem de `logs/`. **Commit `35ce35af892c136632670e81a8e2c2867021f7d5`**, pai `5aefbb7`,
**2 arquivos**, **não publicado**.

```
.gitattributes | 6 ++++++
.gitignore     | 2 +-
2 files changed, 7 insertions(+), 1 deletion(-)
```

#### Conteúdo aplicado

`.gitignore` — **uma única linha** trocada (`git diff --numstat` = `1 1`):

```
-logs/
+/logs/
```

`.gitattributes` (novo) — 4 regras + 2 comentários:

```gitattributes
# EOL dos artefatos de gate: precisa reproduzir os bytes hasheados em build.json / F-00x.test.json.
# Escopo restrito a docs/testing/gates/ para nao afetar outros JSON/XML do repositorio.
docs/testing/gates/*.json text eol=lf
docs/testing/gates/*.xml text eol=crlf
docs/testing/gates/logs/build-*.log text eol=lf
docs/testing/gates/logs/test-*.log text eol=lf
```

**Ajuste de especificidade declarado:** os padrões autorizados (`*.json`, `F-*.xml`,
`logs/*.log`) foram escopados em `docs/testing/gates/` e `F-*.xml` generalizado para `*.xml`.
Motivo medido: `*.json` sem prefixo casaria em **todo** o repositório, inclusive
`rag/evidence/*/manifest.json` — que é componente do token de auditoria — e outros JSON fora do
escopo; e `F-*.xml` deixaria `ctest-full.xml` (XML de teste CRLF real) fora da intenção
"XML de testes: CRLF". A autorização previa ajustar somente a especificidade preservando o
comportamento pretendido.

#### Validações medidas

| Item | Comando | Resultado |
|---|---|---|
| A1 | `git diff --numstat -- .gitignore` | `1	1` — só a linha 7; EOL misto do arquivo preservado (LF nas linhas 1-3,5-7; CRLF nas 4 e 8) |
| A2 | leitura de `.gitattributes` | 4 regras + 2 comentários, nada mais; blob LF |
| A3 | `git check-ignore -v docs/testing/gates/logs/build-20261121-125730-373.log` | **sem saída, rc 1** (não ignorado) |
| A4 | `git check-ignore -v logs/auto` | `.gitignore:7:/logs/` rc 0 (raiz continua ignorada) |
| A5 | `git status --porcelain -- docs/testing/gates` antes do commit | **0 linhas** — nenhum artefato alterado |
| A6 | `git check-attr` | `build.json` → `text: set`, `eol: lf`; `F-001.xml` → `text: set`, `eol: crlf`; `logs/build-*.log` → `eol: lf`; `logs/test-*.log` → `eol: lf` |
| A7 | `git diff --cached --name-only` | **2** caminhos (`.gitattributes`, `.gitignore`) |
| A8 | 2 clones (`-c core.autocrlf=true` e `=false`) | ambos HEAD `35ce35a`, `git status` **0 linhas**, **6/6** XML × `xml_sha256`, **1/1** log × `log_sha256`, `check-attr` idêntico |
| A9 | 31 artefatos × 4 estados (antes / pós-commit / clone T / clone F) | **31/31 idênticos**, `ALL 4-STATE IDENTICAL: True` |
| A10 | gate | `--selftest` 17/17 rc 0; `--inventory` rc 0; `--halt` rc 2; `--all` rc 2; `--stage evidence` F-003 rc 1 |
| A11 | `git status --porcelain` final × baseline | 220 = 220 linhas, diff vazio |

Prova de que o `-c` realmente variou o clone: `README.md` (sem atributo) saiu `w/crlf` no clone
`autocrlf=true` e `w/lf` no `autocrlf=false`.

Prova independente (orquestrador): `python scripts/gate.py --inventory` no repo após o commit
continua exibindo o token esperado de F-002 = `E4280480A05C44A3D4C3AED9342565D2308F5996586CBF66FFC93481BEEE29A1`,
idêntico ao medido **antes** do SET-2C — `sha256(build.json)` e `sha256(F-002.test.json)` não
mudaram.

#### Hashes dos artefatos hasheados (idênticos nos 4 estados)

```
F-001.xml D578E2BADCC48C42BADC16282D4972952A0C9D743366B2DC0F8DBF1307BF55CC
F-002.xml B8988CEB59C6BA4C9E22A6CF63621D3C4F050DA2F058B388B9184DCB34AC10BF
F-003.xml 2FC6A4B68A960E634867EFE6D28E313BCFCC096EF55870ABB832EE0373C786FC
F-004.xml 13AFE355F759939C459C7A74ADD54E40C1A1A6E632FF42B00B5F7A339D2FB216
F-005.xml F9DE4C2D6087EAB376C883280BFDED55D11E0EB683C5B963FF7C636A2A216145
F-006.xml 87A4177EB15CDD48BE984BAB4579EE9E430077C872A5037FC6BE3DF9D9135231
log     720D5E9A13BDFDEB3002157AD8D4744C27FEC92BB1DBB37497F150F0059EC05F
```

#### Correção de contagem

São **31** artefatos versionados em `docs/testing/gates/`, não 30: 7 `*.json` + **7** `*.xml`
(os 6 `F-00x.xml` **e** `ctest-full.xml`) + 17 `*.log`.

`logs/ctest-full-20261121.log` e `logs/selftest-20261121-124756.log` são armazenados como
`i/-text w/-text` (git os detecta como binários): o blob preserva CRLF e os dois clones os
restauraram literalmente. Não é preciso regra de EOL para eles; nenhum metadado os hasheia.

#### Limitações que permanecem

1. **Token completo em clone limpo**: impossível ainda — `rag/evidence/F-002/` é untracked
   (SET-4). Foi possível comparar os componentes versionados (`build.json`, `F-002.test.json`),
   que são exatamente os afetados por EOL.
2. **I-5 (build em clone limpo)**: continua não demonstrado. Nada nesta fase tocou
   `CMakeLists.txt`, `src/` ou `tests/`.
3. **R-8**: nenhum laudo real com token válido existe.
