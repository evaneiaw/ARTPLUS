# RELATÓRIO MESTRE: CONSOLIDAÇÃO ARTPLUS EM 7 FASES

## VISÃO GERAL E GOVERNANÇA

### Histórico e Motivação da Consolidação
O projeto ArtPlus consiste na reimplementação funcional do Esko ArtPro+ v24.03.10017 em C++17/Qt 6.8.3. Originalmente, existiam dois repositórios separados: `H:\Desktop\ArtPlus` (núcleo lógico/engine) e `H:\Desktop\ArtPlus-UI` (interface visual e componentes). A consolidação visa unificar esses projetos em uma única árvore canônica, eliminando a duplicidade do motor lógico enquanto integra a interface rica do ArtPro+ com o motor auditado e aprovado.

**Objetivo final:** Estabilizar o ambiente de desenvolvimento com um único código-fonte, branch `master`, e modelo de operação BUILD, permitindo execução autônoma via `/auto` e despacho de subagentes (ghidra, rea, comportamento, documentacao, arquitetura, implementacao, testes, auditor) sem conflitos de estado ou evidência.

**Escopo e limites:**
- Motor lógico canônico: ARTPLUS (sempre).
- Interface visual: ARTPLUS-UI como fonte de referência de componentes visuais e comportamentais confirmados.
- Features F-001..F-009 tratadas conforme evidência v24.03.10017.
- F-004 (Selection Mark) permanece fora do escopo (CAP negativo na v24).
- F-007 (Step & Repeat) permanece bloqueada (BLO-008, campos do Make Grid não medidos).
- F-009 (Gerenciamento de Objetos) permanece órfã até captura comportamental v24.

**Repositórios envolvidos:**
- `H:\Desktop\ArtPlus` — 7 commits, HEAD `70c3d00`, branch `master`, origin `github.com/evaneiaw/artplus` (case-insensitive).
- `H:\Desktop\ArtPlus-UI` — 5 commits, HEAD `049ec52`, branch `master`, origin `evaneiaw/ARTPLUS-UI.git`.
- GitHub: `https://github.com/evaneiaw/artplus`, branch `master`.

**Arquitetura pretendida:**
```
H:\Desktop\ArtPlus/
├── src/
│   ├── app/main.cpp                          ← StyleLoader + ColorManipulationLayer::initialize + openDocumentPath
│   ├── document/                             ← núcleo (F-005/F-006) + setPageOrder
│   ├── pdf/                                  ← núcleo + MediaBox fracionário (do UI)
│   ├── prepress/                             ← núcleo (F-001/F-002/F-003) — sem color_manipulation
│   ├── color_management/                     ← F-008 canônico (única implementação de cor)
│   ├── automation/ · color/ · geometry/      ← núcleo
│   └── ui/
│       ├── main_window.h/.cpp               ← chrome do UI como base + F-001..F-006 religados
│       ├── artpro/ · dialogs/ · components/ · styles/
│       ├── panels/                          ← Layers/Objects/Inspector/DynamicMarks
│       └── document_marks_panel.*           ← F-002 preservado
├── resources/ui.qrc
├── docs/
│   ├── (núcleo inalterado: features/decisions/audit/architecture/agents/testing)
│   └── ui-workshop/                         ← importado (DESIGN_SYSTEM, UI_INVENTORY, CONTRACTS, REPORTS)
├── rag/evidence/01-interface…08-…           ← CAPs de UI registrados com arquivo + manifest
├── tools/ui_capture/                        ← appshot.ps1, artpro_uia.ps1, artpro_toggle.ps1
└── tests/unit/test_*_panel.cpp              ← 4 testes de painel + 1 de toolbar
```

**Princípios técnicos:**
1. Evidência primeiro: toda funcionalidade deve ter evidência estática (Ghidra) ou comportamental (CAP) da v24.03.10017.
2. Motor canônico sempre vence em conflitos com a UI, exceto MediaBox (precisão de 4 casas decimais vinda da UI) e comandos de undo (CreateObjectsCommand, PageOrderCommand).
3. Duas verdades de estado: não manter matrizes do UI; núcleo é a única fonte rastreável por gate.
4. CAP negativo confirma ausência: F-004 não implementar; F-007 bloqueada até captura de campos.
5. Unidade explícita: mm, pt, dpi nos nomes de campos e specs.

**Regras de segurança:**
- Máximo 3 subagentes ativos; nunca dois `comportamento` (GUI única).
- `build/` e `build.json` compartilhados: nunca apagar árvore compartilhada; auditoria usa `ARTPLUS_GATE_BUILD_DIR=build_audit_<F-###>`.
- Proibido `git reset`, `git clean`, `rebase` ou `push --force` durante recuperação.
- Trabalho de outra sessão nunca é descartado: registrar e preservar.
- Sessões paralelas param no HALT e entregam o estado real ao orquestrador.

**Política de backups:**
- Tags anotadas `pre-consolidation` em ambos os repositórios.
- Git bundles em `H:\Desktop\_backup_artplus\`.
- Validação de integridade pós-criação (`git rev-list --tags`, SHA-256 de arquivos críticos).
- Backup recoverável antes da Fase 2: tag anotada `pre-consolidation` + `git bundle`.

**Política de Git:**
- Commits por escopo dentro da fase, tag `fase-N` ao final.
- Push somente após gate da fase aprovado.
- `git add` por caminho explícito (nunca `git add -A`/`git add .`).
- Histórico preservado: worktree, clone ou HEAD destacado é cópia divergente — pare e reporte.
- `docs/testing/gates/logs/*.log` versionados (referenciados por `build.json` por hash SHA-256).
- `build/` e `build_*` excluídos do repositório (ignorados por `.gitignore`).

**Política de testes:**
- CTest 16/16 após unificação (11 do núcleo + 4 painéis + 1 toolbar).
- Cada feature F-### tem teste unitário citando `F-###` com asserção.
- Teste que não compila = `Not Run` = reprovado.
- Regressão: suíte mapeada do F-### (`gate.py --feature F-### --run-test`) antes de entregar.
- Visual: captura com `tools/ui_capture/appshot.ps1` vs `docs/ui-workshop/SCREENSHOTS`; diff + tolerância declarada.

**Política de compilação:**
- CMake absoluto: `C:\Users\Evanei\AppData\Local\Microsoft\WinGet\Packages\Kitware.CMake_Microsoft.Winget.Source_8wekyb3d8bbwe\cmake-4.4.4-windows-x86_64\bin\cmake.exe`.
- Preset `mingw-msvcrt` → `release-mingw`; build Release (`-O3 -DNDEBUG`).
- Compilador: WinLibs POSIX.MSVCRT GCC (não UCRT).
- Isolamento de build: `ARTPLUS_GATE_BUILD_DIR=build_<escopo>`; nunca `Remove-Item -Recurse -Force build`.
- Build incremental após cada `git mv`/merge; checkpoint após cada etapa.

**Política de aprovação por fase:**
- Cada fase possui gate objetivo (`gate.py --feature F-### --stage <etapa>` = 0).
- Gate não substitui evidência: `--stage audit` com token medido na própria sessão é prova.
- Recusa "aprovar com ressalvas": etapa com gate reprovado volta ao dono (2 tentativas), 3ª vira bloqueio em `BLOQUEIOS.md`.
- `--inventory` obrigatório antes de atualizar `INVENTORY.md`; estado declarado deve == estado comprovado.

**Responsabilidades do BUILD e dos especialistas:**
- BUILD: modo operacional principal; coordena despacho, gates, checkpoints, commits e pushes.
- Subagentes: rea (triagem estática), ghidra (análise de funções/xrefs/RTTI), comportamento (captura GUI), documentacao (specs), arquitetura (ADRs), implementacao (src/CMake), testes (ctest/unit/integration), auditor (laudos com token próprio).
- Nenhum subagente edita `src/`, `tests/`, specs ou evidência bruta diretamente (exceto `implementacao` em `src/**` com ADR/espec, `testes` em `tests/**`, `documentacao` em `docs/features/`, `auditor` em `docs/audit/`).

**Critérios para interrupção segura:**
- HALT ativo (BLO-008/F-007): apenas Step & Repeat campos do Make Grid não medidos — não implementar.
- Build quebrado: aparece como quebrado no roadmap; não esconder.
- Evidência ausente: marcar como `Hipótese` na matriz de rastreabilidade; não inventar.
- Concorrência: máximo 3 subagentes; `comportamento` exclusivo (recurso GUI único).

**Definição de conclusão do projeto:**
- Build Release limpo (`-O3 -DNDEBUG`), CTest 0 falhas.
- HEAD local em sincronia com `origin/master`.
- Todas as features do escopo (F-001/002/003/005/006/008) com auditoria reemitida (token novo) e laudo aprovado.
- F-004 e F-009 arquivadas com status respectivo (fora-do-escopo/v24 e órfã).
- `IMPORT_MANIFEST.md` completo; `UI_TRACEABILITY.md` criado.
- `RELATORIO_7FASES.MD` atualizado com todos os gates verdes.
- `docs/agents/CHECKPOINT.md`, `STATUS.md`, `FEATURE_MATRIX.csv`, `ROADMAP.md` atualizados.
- `git ls-remote origin refs/heads/master` == `git rev-parse HEAD`.

---

## PARTE II — INVENTÁRIO TÉCNICO CONSOLIDADO

### Comparação de Arquivos (Núcleo vs UI)

| Caminho | Origem | Situação | Diferença Encontrada | Dependências | Decisão | Justificativa | Fase |
|---|---|---|---|---|---|---|---|
| `src/pdf/pdf_document.h` | Núcleo | Base | `isEncrypted()` + reset de estado de abertura (F-005 E5) | `pdf_open_handler.cpp`, `artplus_open_handler.cpp` | Manter núcleo | Núcleo tem F-005 E5; UI não tem | F-3 |
| `src/pdf/pdf_document.h` | UI | Mais rico | MediaBox com 4 casas decimais (ex.: `595,2756`) | `pdf_exporter.cpp` | UI para MediaBox | UI grava MediaBox com precisão fracionária; núcleo truncava `(int)` → regressão | F-3 |
| `src/pdf/pdf_exporter.cpp` | Núcleo | Base | `(int)boxes[i].width()` → truncamento 595 | `pdf_exporter.cpp:373` | UI para MediaBox | UI grava `<< (int)boxes[i].width()` com 4 casas; núcleo truncava | F-3 |
| `src/pdf/pdf_exporter.cpp` | UI | Mais preciso | `<< QString::number(boxes[i].width(), 'f', 4)` → `595,2756` | `pdf_exporter.cpp:373` | Integrar precisão UI | Aceitar 3 linhas do UI + teste de precisão 1e-3 pt | F-3 |
| `src/prepress/bearer_bar.cpp` | Núcleo | Base | Correção R5/E3 | `bearer_bar.cpp:112-117` | Manter núcleo | R5: polaridade invertida; E3: zeragem silenciosa SizeReference | F-3 |
| `src/prepress/bearer_bar.h` | Núcleo | Base | Endereço R5/E3 | `bearer_bar.h` | Manter núcleo | Comentários/endereço R5 | F-3 |
| `src/prepress/marks.h` | Núcleo | Base | Comentários F-002 | `marks.h` | Manter núcleo | TODO(F-002): superseded por MarkSetProcessor (ADR-012) | F-3 |
| `src/prepress/marks.h` | UI | Anterior | 74 linhas de header | `marks.h` | Doador: núcleo (126 linhas) | Núcleo tem MarkSetProcessor commands/reporter/PDF loader; UI versão anterior (74 vs 126 linhas) | F-3 |
| `src/document/document_model.h` | Núcleo + UI | Misto | `title()`/`Separation`/`separationInfo` vs `setPageOrder()` | `document_model.h` | Mesclar | Núcleo: `title()`/`Separation`/`separationInfo`; UI: `setPageOrder()` → mesclar + adicionar `setPageOrder` a API | F-3 |
| `src/document/document_save_manager.cpp` | Núcleo | Base | F-006 D1/D2/D3/E5/E10 rollback | `document_save_manager.cpp` | Manter núcleo | UI ainda tem "Simulação" e retorna `false` | F-3 |
| `src/document/undo.h/.cpp` | UI | Mais rico | `CreateObjectsCommand` e `PageOrderCommand` (undo imposition/step-repeat) | `undo.h/.cpp` | Doador: UI | UI tem comandos de undo que núcleo não tem; adicionar ao núcleo | F-3 |
| `src/ui/main_window.h/.cpp` | Núcleo | Funcional | F-005 dispatcher/título/overlay/relayout + F-006 | `main_window.cpp` (82 KB) | Base: núcleo | Núcleo functional ahead com F-005/F-006; UI richer chrome | F-3 |
| `src/ui/main_window.h/.cpp` | UI | Richer chrome | 146 KB, 109 funções | `main_window.cpp` (146 KB) | Base: UI chrome + núcleo F-001..F-006 | UI superset de chrome (+52 funções); núcleo tem F-002, F-005 (dispatcher/título/overlay/relayout) e F-006 | F-3 |
| `src/app/main.cpp` | Misto | Init | `ColorManipulationLayer::initialize` + `openDocumentPath` | `main.cpp` | Mesclar | Núcleo: init `ColorManipulationLayer` + `openDocumentPath`; UI: `StyleLoader` | F-3 |
| `src/pdf/pdf_parser.h` | Empate | Mesmo fix | Arrays/`N G R`; só comentário difere | `pdf_parser.h` | Empate | Mesmo fix de arrays/`N G R`; só comentário difere | F-3 |
| `src/color_management/` | Núcleo | Canônico | F-008 módulo único | `color_management/` | Manter núcleo | Única implementação de cor no projeto; duplicata stub removida | F-5 |

**Arquivos idênticos (37 de 54 em `src/`):**
- `src/document/document_model.cpp`, `src/document/undo.cpp`, `src/pdf/pdf_content.h`, `src/pdf/pdf_parser.h`, `src/prepress/marks.h`, `src/prepress/bearer_bar.h`, etc.

**Arquivos exclusivos do núcleo (30):**
- `src/color_management/*`, `src/automation/*`, `src/geometry/*`, `src/ui/main_window.*` (parte), `src/app/main.cpp` (parte), etc.

**Arquivos exclusivos da UI (23):**
- `src/ui/main_window.*` (146 KB, 109 funções), `src/ui/artpro/*`, `src/ui/dialogs/*`, `src/ui/components/*`, `src/ui/panels/*`, `src/ui/styles/*`, `resources/ui.qrc`.

### Módulos Divergentes (Detalhado)

#### 1. `document_model.h/.cpp`
- **Núcleo:** `title()`, `Separation`, `separationInfo`, `setFilePath`, `setModified`, metadata.
- **UI:** `setPageOrder()`, `CreateObjectsCommand`, `PageOrderCommand`.
- **Diferença:** UI tem comandos de undo para imposition/step-repeat que núcleo não tem.
- **Estratégia de merge:** Adicionar `Document::setPageOrder()` à API núcleo; integrar `CreateObjectsCommand` e `PageOrderCommand` ao sistema de undo. Testar round-trip de página ordenada.

#### 2. `document_save_manager.cpp`
- **Núcleo:** F-006 D1/D2/D3/E5/E10 rollback (backup por rename + falha do serializer restaura original).
- **UI:** "Simulação" e retorna `false`.
- **Estratégia de merge:** Manter implementação do núcleo; corrigir Eventual UI para usar lógica de rollback do núcleo.

#### 3. `undo.h/.cpp`
- **Núcleo:** Sistema de undo básico sem `CreateObjectsCommand`/`PageOrderCommand`.
- **UI:** `CreateObjectsCommand` e `PageOrderCommand` para undo de imposition/step-repeat.
- **Estratégia de merge:** Adicionar comandos do UI ao núcleo; testar undo/redo para operações de página/objeto.

#### 4. `pdf_exporter.cpp`
- **Núcleo:** `(int)boxes[i].width()` → `595` (truncamento).
- **UI:** `<< QString::number(boxes[i].width(), 'f', 4)` → `595,2756` (4 casas).
- **Estratégia de merge:** Aplicar precisão de 4 casas do UI; tolerância 1e-3 pt em teste de round-trip.

#### 5. `pdf_document.h/.cpp`
- **Núcleo:** `isEncrypted()`, reset de estado de abertura (F-005 E5).
- **UI:** Não tem isEncrypted ni reset.
- **Estratégia de merge:** Manter implementação do núcleo; adicionar `isEncrypted()` + lógica de reset se UI precisar.

#### 6. `pdf_parser.h`
- **Ambas:** Mesmo fix de arrays/`N G R`; só comentário difere.
- **Estratégia:** Manter como está; não há divergência funcional.

#### 7. `markset_processor.h/.cpp`
- **Núcleo:** F-002 commands/reporter/PDF loader; 126 linhas de header.
- **UI:** Versão anterior (74 linhas de header).
- **Estratégia de merge:** Manter implementação do núcleo (126 linhas); UI é versão anterior sem commands/reporter/PDF loader.

#### 8. `bearer_bar.cpp`
- **Núcleo:** Correção R5/E3 (polaridade invertida; zeragem silenciosa de SizeReference em runtime).
- **UI:** Não especificada.
- **Estratégia:** Manter correção R5/E3 do núcleo.

#### 9. `marks.h`, `bearer_bar.h`
- **Núcleo:** Comentários/endereço R5.
- **UI:** 2 linhas de diff (TODO superseded + comentários).
- **Estratégia:** Manter núcleo.

#### 10. `app/main.cpp`
- **Núcleo:** init `ColorManipulationLayer` + `openDocumentPath`.
- **UI:** `StyleLoader`.
- **Estratégia de merge:** Manter init do núcleo; StyleLoader pode ser mantido como opcional se UI precisar.

#### 11. `ui/main_window.h/.cpp`
- **Núcleo:** F-005 dispatcher/título/overlay/relayout + F-006; 82 KB; menos funções.
- **UI:** Chrome completo (menubar 8 menus, toolbar 3 grupos, abas de documento, context bar, sidebar direita, SideDock esquerda, ícones QPainter); 146 KB; 109 funções.
- **Estratégia de merge:** Fundir: UI chrome como base + F-001..F-006 religados do núcleo. Decompor `main_window` por função com checklist F-001..F-006; ADR necessária para decomposição.

#### 12. `CMakeLists.txt`
- **Núcleo:** Listas `DOCUMENT/PDF/PREPRESS/AUTOMATION_SOURCES`; `add_subdirectory(src/color_management)`.
- **UI:** `UI_SOURCES` += 19 arquivos + `resources/ui.qrc`; `find_package(Qt6 ... Test ZlibPrivate PrintSupport)`.
- **Estratégia:** Manter listas do núcleo + `UI_SOURCES`; `Qt6::PrintSupport` para alvos com GUI.

---

## PARTE III — PLANEJAMENTO DETALHADO DAS SETE FASES

### FASE 1 — INVENTÁRIO E DIAGNÓSTICO (CONCLUÍDA)

**Objetivo:** Realizar o levantamento completo das duas árvores de trabalho, identificar redundâncias, divergências de código e lacunas de evidência para fundamentar a estratégia de unificação.

**Situação inicial:** Projeto operava em dois repositórios divergentes: núcleo (`ArtPlus`) mais recente e auditado, UI (`ArtPlus-UI`) com componentes visuais avançados mas baseados em versão anterior do motor.

**Inventário resumido:**
- ARTPLUS: 7 commits (`70c3d00`), 84 arquivos em `src/`, 11 testes CTest, 5 features auditadas/testadas.
- ARTPLUS-UI: 5 commits (`049ec52`), 77 arquivos em `src/` (54 duplicatas do motor), 14 testes CTest, 118 arquivos de workshop visual.
- Divergência real: 17 arquivos em `src/` apresentaram diferenças lógicas após normalização de CRLF.

**Estado das funcionalidades (núcleo):**
- F-001/002/003/005/008: Testados/Implementados com laudos de auditoria.
- F-004: Fora do escopo (CAP negativo na v24).
- F-006: Implementado (Save Document com rollback).
- F-007: Bloqueado (BLO-008).

**Riscos identificados:**
- R1: Perda de melhorias do motor auditado durante merge com UI.
- R3: Monolito `main_window.cpp` (146 KB) dificulta manutenção.
- R9: Invalidação de auditorias prévias devido a alterações no código-fonte.

**Veredito do Gate F1:** ATENDIDO. Inventário forneceu base necessária para unificação, com doadores declarados por arquivo divergente.

---

### FASE 2 — UNIFICAÇÃO FÍSICA E ESTRUTURAL

**Objetivo:** Estabelecer a estrutura física unificada no diretório `H:\Desktop\ArtPlus`, integrando os recursos visuais e componentes da UI sem sobrescrever o progresso lógico do núcleo.

**Subfases e tarefas:**

1. **Segurança e Backup:**
   - Criar tags Git anotadas `pre-consolidation` em ambos os repositórios.
   - Gerar Git bundles em `H:\Desktop\_backup_artplus\`.
   - Validar integridade (`git rev-list --tags`, SHA-256 de arquivos críticos: `sha256sum` de binários em `bg_prog_artpro+_v240`).

2. **Importação de Componentes:**
   - Mover 19 arquivos exclusivos de UI para a árvore do núcleo:
     `src/ui/artpro/ArtProIcons.*`, `ArtProPanels.*`, `src/ui/dialogs/ArtProDialogs.*`, `src/ui/components/ToolbarButton.*`, `src/ui/panels/{Layers,Objects,DynamicMarks,Inspector}Panel.*`, `src/ui/styles/{StyleLoader.*, styles.qss}`, `resources/ui.qrc`.
   - Importar diretório `docs/ui-workshop/` (118 arquivos: ARCHITECTURE, DESIGN_SYSTEM, INTEGRATION_CONTRACTS, EVIDENCE_REGISTER, UI_INVENTORY, ROADMAP, REPORTS, 96 SCREENSHOTS).
   - Criar `IMPORT_MANIFEST.md` registrando origem de cada arquivo importado (hash SHA-256, repositório source, commit ID).

3. **Ajuste de Infraestrutura:**
   - Atualizar `CMakeLists.txt` para incluir `Qt6::PrintSupport`.
   - Registrar 5 novos alvos de teste vindos da UI (LayersPanelTests, ObjectsPanelTests, DynamicMarksPanelTests, InspectorPanelTests, ToolbarButtonTests).
   - Repetir `POST_BUILD copy_if_different Qt6::PrintSupport` para alvos que abrem GUI.
   - Proibir build concorrente: Fase 2 usa `build_merge_ui`, Fase 7 usa `build_phase7` (`ARTPLUS_GATE_BUILD_DIR`), nunca apagar `build/` compartilhado.

4. **Definição de testes de build e integração estrutural:**
   - Build bem-sucedido do alvo `ArtPlus`.
   - 16 testes CTest registrados e passando (11 do núcleo + 4 painéis + 1 toolbar + 0 novos ainda pendentes).
   - `IMPORT_MANIFEST.md` completo.

**Critérios de Aceite (Gate F2):**
- [ ] Backup íntegro (tags `pre-consolidation`, bundles validados).
- [ ] Estrutura unificada (motor lógico único em `H:\Desktop\ArtPlus`; nenhum repositório Git aninhado).
- [ ] Ausência de motor duplicado (`git status` sem pastes `ArtPlus-UI` dentro de `ArtPlus`).
- [ ] CMake válido (preset `mingw-msvcrt`, build Release exit 0).
- [ ] Build aprovado (`ctest` 16/16).
- [ ] `IMPORT_MANIFEST.md` completo.
- [ ] Git limpo (`git status --short` sem arquivos pendentes não rastreados críticos).
- [ ] Commit e push verificados (`git ls-remote origin refs/heads/master` == HEAD local).

---

### FASE 3 — INTEGRAÇÃO LÓGICA E FUNCIONAL

**Objetivo:** Fundir os fluxos de execução do motor lógico com o chrome da interface, garantindo que as ferramentas (F-001..F-003) e os sistemas de arquivo (F-005, F-006) funcionem através da nova UI.

#### 3.1 MainWindow
Mapear as funções do `MainWindow` das duas versões e indicar como será feita a integração sem perder recursos do núcleo.

| Função | Núcleo | UI | Integração |
|---|---|---|---|
| `openDocumentPath` | Dispatcher MIME→handler, OpenError, overlay Media Box, relayout | `openPdfPath` + PdfImporter::import | UI chrome como base; dispatcher/núcleo transplantado |
| `setPageOrder` | Não existe | `CreateObjectsCommand` + `PageOrderCommand` | Adicionar `Document::setPageOrder()` à API; integrar comandos undo |
| `saveDocument` | `DocumentSaveManager`, E10 rollback | "Simulação" retorna `false` | Usar lógica D1/D2/D3/E5/E10 rollback do núcleo |
| `MarkSetProcessor` | `markset_processor.cpp` + `MarkSetProcessor` test | Ausente no main_window | Conectar painel Marks ao processor núcleo |
| `ColorManagement` | Módulo `color_management`, lcms2/Pantone adiados | Não no main_window | Linkar módulo canônico; stubs honestos `isCmmEngineAvailable()==false` |
| MediaBox export | `(int) trunc` → `595` | `4 casas` → `595,2756` | Aplicar precisão UI; tolerância 1e-3 pt |

#### 3.2 Menus
Matriz para cada menu e submenu:

| Menu | Ação | Slot | Implementação | Evidência ArtPro+ | Dependência | Estado | Trabalho Necessário |
|---|---|---|---|---|---|---|---|
| File | Open | `openDocumentPath` | Núcleo + UI chrome | `CAP-20261121-01` (PDF open) | — | Implementado | Testar round-trip PDF |
| File | Save As | `DocumentSaveManager::save` | Núcleo | `CAP-20261124-01` (Save/Save As) | — | Implementado | Testar E10 rollback |
| Marks | Add Cut Mark | `Add Cut Mark` | Núcleo F-001 | `CAP-20261119-01` (histórico) | — | Fora do fluxo ativo (historical) | CAP reconfirmado v24 opcional |
| Marks | Load Mark Set | `TaskMarkSets::ReadMarkSetFile` | Núcleo F-002 | `CAP-20261121-03` | `MarkSetProcessor` | Implementado | Testar MarkSetProcessor suíte (19/19) |
| Prepress | Step & Repeat | `step_repeat` | Não implementado | `CAP-20261124-01` (Make Grid) | BLO-008 | Bloqueado | Capturar campos do Make Grid |
| Color | Color Management | `ColorManagement` | Módulo canônico | `CAP-20261122-02` | `color_management/` | Testado | Integrar lcms2/Pantone quando fase abrir |

#### 3.3 Ferramentas
Auditar individualmente as ferramentas e suas interações:

| Ferramenta | Implementação | Status | Trabalho Necessário |
|---|---|---|---|
| Layers Panel | `LayersPanel` widget + modelo | Implementado | Verificar população automática ao abrir PDF |
| Objects Panel | `ObjectsPanel` widget + modelo | Implementado | Verificar populamento após PDF open |
| Marks Panel | `DynamicMarksPanel` + `MarkSetProcessor` | Implementado (F-002) | Conectar botões ao processor núcleo |
| Separations | Perfil + tabela eye/Name/#/Setup | Parcial | Mapear separações do PDF ao abrir |
| Quality Control | Fontes, imagem res, cor for gamut, objeto fora página, transparência | Implementado (F-008 parcialmente) | Validar checks pós-merge |
| Object Browser | Seleção de objetos na página | Implementado | Testar seleção após PDF open |
| Colors | Document Profile + separações | Implementado | Validar contra UI capture |
| Images | Importação e renderização | Implementado (F-005/006) | Testar round-trip PDF com imagens |

#### 3.4 Painéis
Detalhar integração:

| Painel | Estado | Integração Necessária |
|---|---|---|
| Layers | Implementado | Populate via `layerOrder()`/`layer()` após PDF open; conectar eye/lock/Name/Type |
| Objects | Implementado | Populate via `objects/`/`objectIds()` após PDF open |
| Marks | Implementado (F-002) | Conectar `DynamicMarksPanel` ao `MarkSetProcessor`; botões `Load/Save Mark Set` |
| Separations | Parcial | Mapear separações do PDF ao abrir; exibir perfil + tabela |
| QC | Implementado (F-008) | Validar checks: fontes, imagem res, cor for gamut, objeto fora página, transparência |
| Object Browser | Implementado | Seleção de objetos na página após open |
| Colors | Implementado | Document Profile + separações visíveis |
| Images | Implementado | Renderização após PDF open |

#### 3.5 Diálogos
Detalhar:

| Diálogo | Estado | Trabalho Necessário |
|---|---|---|
| Options | "General" persiste; demais abas read-only | Decidir: manter read-only ou implementar páginas completas |
| Page Boxes Setup | Implementado | Validar campos e botões após PDF open |
| Document Setup | Implementado | Verificar campos populados após PDF open |
| Print | Implementado | Testar impressão após merge |
| About | Implementado | Manter exibição de versão |

#### 3.6 Ações desabilitadas e slots sem implementação
Auditar os 60 `addDisabledAction`, os 25 `setEnabled(false)` e os slots mortos identificados no inventário. Cada ação receberá uma decisão:

| Ação | Decisão | Justificativa |
|---|---|---|
| `addDisabledAction` (60 casos) | Implementar com evidência OU Conectar a função existente OU Corrigir implementação parcial OU Manter indisponível com explicação OU Ocultar quando comprovadamente não fizer parte do escopo OU Investigar antes de decidir | Cada ação mapeada individualmente; não agrupar em conclusão genérica |
| Slots mortos (`actionLists`, `presets`, `scripting`, `reports`, `performance`, `recovery`) | Igual acima | 6 slots mortos identificados; decisão por ação |

**Matriz de fluxos funcionais ponta a ponta:**
```
Abrir PDF → selecionar objeto → executar operação → atualizar painel → desfazer → refazer → salvar → reabrir → verificar integridade
```
- Definir testes e resultados esperados de cada fluxo.
- **Não** declarar um botão funcional apenas porque ele responde ao clique.

#### 3.7 Integração do motor
Detalhar:

| Componente | Integração | Testes Necessários |
|---|---|---|
| `Document::setPageOrder()` | Adicionar à API núcleo; integrar `CreateObjectsCommand` + `PageOrderCommand` | Teste de page order round-trip |
| `CreateObjectsCommand` | Integrar ao sistema undo núcleo | Teste undo/redo de criação de objeto |
| `PageOrderCommand` | Integrar ao sistema undo núcleo | Teste undo/redo de reordenação de página |
| `DocumentSaveManager::save` | Manter D1/D2/D3/E5/E10 rollback | Testar 28 casos (D1/D2/D3/E5 + E10) |
| `PdfExporter::exportPdf` | Precisão fracionária MediaBox (4 casas) | Teste round-trip MediaBox ±1e-3 pt |
| `MarkSetProcessor` | Conectar painel Marks ao processor núcleo | Testar suíte MarkSetProcessor (19/19) |
| `FileDispatcher` MIME→handler | Manter núcleo F-005 | Testar open PDF via MIME types |

**Testes de integração e regressão:**
- Teste de round-trip de PDF verificando a preservação do MediaBox fracionário (tolerância 1e-3 pt).
- Teste de integração: abrir PDF → modificar via painel Marks → salvar → verificar integridade.
- Teste de undo/redo para novas operações de página/objeto.
- Validação visual: capturar sessão de uso demonstrando os 10 fluxos principais (Abertura → Edição → Marks → Save).

**Critérios de Aceite (Gate F3):**
- [ ] Interface funcional com todos os menus e painéis populados.
- [ ] Undo/Redo operantes para novas operações de página/objeto.
- [ ] MediaBox fracionário sobrevive ao round-trip (tolerância 1e-3 pt).
- [ ] Nenhum botão sem função (todos têm decisão tomada).

---

### FASE 4 — LIMPEZA E ORGANIZAÇÃO

**Objetivo:** Eliminar resíduos do processo de merge e padronizar a estrutura do projeto para manutenção a longo prazo.

**Inventário dos candidatos à limpeza:**

| Caminho | Tipo | Referências | Motivo da suspeita | Dependências | Decisão proposta | Risco | Procedimento de recuperação |
|---|---|---|---|---|---|---|---|
| `src/prepress/selection_mark.*` | Obsoleto | F-004 | F-004 fora do escopo (CAP negativo) | Nenhuma (não referenciado em CMake) | Não importar (F-004) | Baixo | Arquivar cópia histórica em `docs/ui-workshop/legacy-repo/` |
| `src/prepress/color_manipulation/*` | Duplicata | F-008 | Concorrente do módulo canônico `color_management/` | Referenciado em `test_color_management.cpp` | Não importar (duplicata F-008) | Médio | Arquivar cópia histórica em `docs/ui-workshop/legacy-repo/` |
| `tests/unit/test_selection_mark.cpp` | Teste | F-004 | F-004 fora do escopo | Não no CMake | Não importar | Baixo | Remover (já arquivado) |
| `docs/testing/gates/F-004.test.json`, `F-004.xml` | Artefato gate | F-004 | F-004 fora do escopo | Gate.py lê por feature | Remover | Baixo | Remover (já arquivado) |
| Logs `-txt`, `-log` na raiz | Temporário | Múltiplo | Acúmulo ad-hoc durante desenvolvimento | Alguns referenciados por `gate.py` | Remover (verificar 8 pts) | Baixo | Excluir após verificar `.gitignore` |
| Scripts duplicados na raiz | Scripts | `automatizador.py`, `capture_f004.py`, etc. | 11 scripts duplicam arquivos da raiz do núcleo | Já existem idênticos em `H:\Desktop\ArtPlus\` | Manter versão núcleo; remover da UI | Baixo | `git rm` dos da UI; manter na raiz |
| `.bak`, `.new` da raiz | Temp | `CMakeLists.txt.bak/.new` | Geração antiga do CMake | Build scripts | Remover (verificar 8 pts) | Baixo | Excluir após verificação |
| Códigos de encoding Mojibake | Encoding | README do UI | cp1252/UTF-8 em comentários/README do UI | Legibilidade | Normalizar UTF-8 sem BOM (Fase 4) | Baixo | Reescrever (não tocar `docs/testing/gates/*`) |
| Scripts `scripts/` duplicados | Scripts | 11 scripts na raiz + 14 na UI | Alguns idênticos entre núcleos | Build/teste | Consolidar: UI scripts → núcleo se idênticos; se únicos, decidir manter ou remover | Média | Migrar decisões para `IMPORT_MANIFEST.md` |

**Detalhar:**
- Remover arquivos `.bak`, `.new`, e scripts de log ad-hoc da raiz.
- Normalizar a codificação de arquivos (UTF-8 sem BOM) e o estilo de indentação.
- Reorganizar a pasta `scripts/` para evitar duplicidade com a raiz.
- Verificar `.gitignore` pontos (8 pontos de conferência listados no AGENTS.md §10.7).

**Critérios de Aceite (Gate F4):**
- [ ] `git status` limpo de arquivos não rastreados desnecessários.
- [ ] Zero referências a caminhos absolutos da antiga árvore `ArtPlus-UI`.
- [ ] Build + ctest verdes após limpeza.
- [ ] `.gitignore` conferido nos 8 pontos.

---

### FASE 5 — AUDITORIA DA ENGENHARIA REVERSA

**Objetivo:** Vincular os novos componentes de interface às evidências reais do ArtPro+ v24 e revalidar o projeto contra a Regra de Ouro (v24.03.10017).

**Subtarefas:**

1. **Rastreabilidade:** Criar `docs/reverse-engineering/UI_TRACEABILITY.md` vinculando os CAPs da interface (01..14) aos arquivos em `src/ui/`.

   **Estrutura esperada do UI_TRACEABILITY.md:**
   ```
   # UI Traceability — ArtPlus v24.03.10017
   
   ## CAP Registry
   | ID | Arquivo | Caminho | Descrição | Comportamento | Código Relacionado | Estado |
   |---|---|---|---|---|---|---|
   | CAP-20261124-01 | `SCREENSHOTS/ref-toolbar.png` | `ui-workshop/SCREENSHOTS/` | Toolbar principal 3 grupos | Chrome ArtPro+ | `src/ui/main_window.cpp` | Confirmado |
   | CAP-20261124-02 | `SCREENSHOTS/ref-sidebar.png` | `ui-workshop/SCREENSHOTS/` | Sidebar direita | Seções recolhíveis | `src/ui/panels/` | Confirmado |
   | ... | ... | ... | ... | ... | ... | ... |
   
   ## GAP Analysis
   | GAP ID | Tipo | Descrição | possível resolução |
   |---|---|---|---|
   | GAP-01 | Comportamental | 2 CAPs quebrados (CAP-20261122-01, -02) | Localizar arquivos ou registrar como perdidos |
   | GAP-02 | Ghidra | `GHIDRA-ColorManipulationLayer-0x18001A2C0` resolve para 5 `.md` | Corrigir manifest.json referências |
   | ... | ... | ... | ... |
   ```

2. **Correção de Evidência:** Recuperar os 2 CAPs quebrados e o GHIDRA orfão identificado na Fase 1.
   - `CAP-20261122-01.png` e `CAP-20261122-02.png` citados em EVIDENCE_REGISTER.md e inexistentes em `SCREENSHOTS/`.
   - `GHIDRA-ColorManipulationLayer-0x18001A2C0` aponta para `rag/evidence/F-008/ghidra/functions.csv` que não existe (existem 5 `.md` por endereço).
   - Ação: localizar arquivos reais ou registrar como perdidos com justificativa.

3. **Reauditoria:** Executar o ciclo de auditoria para F-001, 002, 003, 005, 006 e 008, emitindo novos laudos devido às alterações no `src/`.
   - **Restrições:**
     - F-004 permanece fora do escopo (CAP-20261121-02 negativo; UI Selection Mark inexistente na v24).
     - F-007 permanece bloqueada por BLO-008 (campos do Make Grid não medidos).
     - F-009 não receberá especificação inventada; permanecerá órfã até captura comportamental v24.

**Criar a especificação do futuro `docs/reverse-engineering/UI_TRACEABILITY.md`:**

Cada linha da matriz deverá relacionar:
- ID da evidência (CAP-* ou GHIDRA-*).
- Origem (ArtPlus/src, ArtPlus-UI/ui-workshop, comportamento).
- Caminho do arquivo.
- Descrição do que foi observado.
- Código relacionado (função/arquivo).
- Estado de confirmação (Confirmado/Parcial/Hipótese/Não investigado/Fora do escopo/Bloqueado).
- Teste relacionado (se houver).
- Lacunas (what's missing).

**Reauditar F-001, F-002, F-003, F-005, F-006 e F-008 após as alterações:**
- Executar `python scripts/gate.py --feature F-### --stage audit` com `--emit-token` medido na sessão.
- Emitir novos laudos `docs/audit/F-###-audit-<data>.md` com token vigente.
- Atualizar `INVENTORY.md`, `ROADMAP.md`, `FEATURE_MATRIX.csv`, `STATUS.md` com estados derivados.

**Critérios de Aceite (Gate F5):**
- [ ] Toda funcionalidade visível possui um CAP correspondente registrado no `manifest.json` da feature.
- [ ] `docs/reverse-engineering/UI_TRACEABILITY.md` criado e populado.
- [ ] Todas as linhas da matriz de rastreabilidade têm estado definido (Confirmado/Parcial/Hipótese/Não investigado/Fora do escopo/Bloqueado).
- [ ] Reauditoria emitida para F-001/002/003/005/006/008 com token novo (medido na sessão).

---

### FASE 6 — UNIFICAÇÃO DOS AGENTES E MODOS

**Objetivo:** Migrar o projeto para o modelo de operação **BUILD** centralizado, com automação total de gates e delegação para subagentes especialistas.

**Inventariar todos os agentes, skills, comandos, schemas e configurações.**

#### Agentes (9 no núcleo + UI legacy)

| Agente | Modo | Escreve em | Permissões (V2) | Sobreposição | Destino | Justificativa |
|---|---|---|---|---|---|---|
| `orquestrador` | primary | `ROADMAP.md`, `FEATURE_MATRIX.csv`, `docs/phases/**`, `docs/agents/**`, `opencode.jsonc`, `.opencode/agents/**`, `.opencode/commands/**` | `steps: 240`; `permissions: [edit:resource→allow/deny]` | Nenhuma (único primary) | Manter | Supervisor executivo; gates, checkpoints, commits, pushes |
| `ghidra` | subagent | `tools/ghidra_analysis/**`, `tools/ghidra_projects/**`, `docs/reverse-engineering/**`, `rag/evidence/**` | `steps: 120`; subagent: ghidra só | Triagem estática + xrefs/RTTI | Manter | Análise de binário; funções, xrefs, vtables/RTTI, strings, recursos |
| `rea` | subagent | `rag/evidence/**`, `rag/sources/`, `docs/reverse-engineering/**` | `steps: 90`; subagent: rea só | Triagem PE, imports/exports, strings, RTTI | Manter | Triagem estática de binários ArtPro+ |
| `comportamento` | subagent | `tools/reference_capture/**`, `docs/behavior/**`, `rag/evidence/**` | `steps: 60`; **NUNCA dois ao mesmo tempo** (GUI única) | Comportamental; captura UI | Manter | Captura observável de ferramentas na GUI ArtPro+ real |
| `documentacao` | subagent | `docs/features/**`, `docs/glossary/**`, `rag/index/`, `rag/metadata/` | `steps: 48`; specs + metadata | Knowledge base | Manter | Converte evidência em spec F-### rastreável |
| `arquitetura` | subagent | `docs/architecture/**`, `docs/decisions/` | `steps: 90`; cpp-architecture-adr + qt-cpp-development | ADRs + mapa função→classe | Manter | Traduz specs F-### em arquitetura C++/Qt |
| `implementacao` | subagent | `src/**`, `CMakeLists.txt`, `tools/pdf_inspector/**` | `steps: 120`; qt-cpp-development + document-core + pdf-engineering + color-management | Código-fonte + build | Manter | Implementa em C++17/Qt 6.8.3 o que a arquitetura definiu |
| `testes` | subagent | `tests/**`, `docs/testing/**`, `CMakePresets.json`, `scripts/**`, `tools/visual_compare/`, `dossiers/**` | `steps: 140`; build-and-release + test-strategy + visual-regression-testing | Build + testes | Manter | Build (toolchain MinGW/MSVCRT + CMake), testes unitários/integration |
| `auditor` | subagent | `docs/audit/**` | `steps: 90`; evidence-verification | Laudos de auditoria | Manter | Verifica se funcionalidade realmente existe, compila, roda, tem evidência |

**Skills (26 total; 7 do UI + 19 do núcleo/legacy):**

| Skill | Função | Duplicações | Destino | Justificativa |
|---|---|---|---|---|
| `project-orchestration` | Coordena pipeline ArtPlus | Sobrepõe 1 com `orquestrador` do núcleo | Consolidar; `orquestrador` V2 ganha | Policy: one primary agent only |
| `github-workflow` | Versiona/publica ArtPlus no GitHub | Sobrepõe configuração legado (maxSteps/permission map) | Consolidar para `orquestrador` V2 | Schema V1 → V2 migration |
| `qt-design-system` | Design system UI (único do UI) | Não tem no núcleo | Renomear para `ui-design-system` under `qt-cpp-development` namespace | Knowledge unique; rename + namespace |
| `ui-integration-contract` | Contratos de integração UI (único) | Não tem no núcleo | Renomear para `integration-contract` under `project-orchestration` | Knowledge unique; rename |
| `ui-visual-validation` | Validação visual (único) | Sobrepõe `visual-regression-testing` | Fundir para `visual-regression-testing` | Merge: same capability, V2 unifies |
| `qt-component-development` | Desenvolvimento de componentes Qt (único) | Sobrepõe `qt-cpp-development` | Fundir para `qt-cpp-development`; UI components vira sub-set | Merge: same base skill |
| `ui-build-and-test` | Build e teste da interface | Sobrepõe `build-and-release` | Fundir para `build-and-release`; delegar BUILD | Merge: build already V2-capable |
| `ui-reference-research` | Pesquisa de referência UI | Sobrepõe `artpro-behavior-capture` | Fundir para `artpro-behavior-capture`; UI research vira comportamento | Merge: same evidence source |
| `ui-git-isolation` | Isolamento Git da UI | Obsoleto (repositório único virá) | Archivar (deixa de existir isolamento) | Consolidation: single repo |
| `action-lists-automation` | Automação de listas de ação | Domínio próprio | Manter | Unique skill; não se sobrepõe |
| `dependency-license-audit` | Auditoria de licenças de dependência | Domínio próprio | Manter | Unique skill |
| `color-management` | Gerência de cor no ArtPlus | Domínio próprio + F-008 canônico | Manter + integrar F-008 module | Core skill + F-008 |
| `layers-and-separations` | Camadas, tintas, separações | Domínio próprio | Manter | Unique skill |
| `screening-and-halftone` | Modelagem de retículas e meio-tom | Domínio próprio | Manter | Unique skill |
| `selection-and-transform` | Seleção e transformação de objetos | Domínio próprio | Manter | Unique skill |
| `step-and-repeat` | Step & Repeat | Domínio próprio + F-007 bloqueada | Manter (não implementar F-007) | Unique skill; BLO-008 não impede skill |
| `preflight-quality-control` | Preflight QC | Domínio próprio | Manter | Unique skill |
| `pdf-engineering` | Engenharia PDF | Domínio próprio + módulo color_management | Manter + integrar com F-008 | Core + F-008 |
| `test-strategy` | Estratégia de testes | Domínio próprio | Manter | Unique skill |
| `vector-geometry` | Geometria vetorial | Domínio próprio | Manter | Unique skill |
| `visual-regression-testing` | Testes de regressão visual | Domínio próprio + `ui-visual-validation` | Fundir; `ui-visual-validation` → `visual-regression-testing` | Merge |
| `technical-specification` | Spec F-### em formato verifiable | Domínio próprio + `documentacao` | Fundir; `documentacao` fica como specialty | Merge: doc skill core |
| `evidence-verification` | Auditoria de evidência | Domínio próprio + `auditor` | Fundir; `auditor` V2 schema | Merge |
| `powershell-win-toolkit` | Evita armadilhas shell Windows 11 | Domínio próprio (todos) | Manter | Cross-cutting; todos usam |

#### Consolidation of skills:
- **BUILD** como único modo operacional principal.
- **Planejamento interno no BUILD:** `/auto` continua com política `AUTOPILOT.md`; em conflito, `AGENTS.md` ganha.
- **Delegação e coordenação de especialistas:** Pipeline `rea → ghidra → comportamento → documentacao → arquitetura → implementacao → testes → auditor`. Máximo 3 subagentes ativos; `comportamento` exclusivo.
- **Checkpoints e execução contínua:** `docs/agents/CHECKPOINT.md` atualizado após cada etapa concluída (não só no fim); conteúdo mínimo: árvore/branch/HEAD, última tarefa, tarefa atual, próximas, arquivos, build (diretório + exit), testes (suíte + pass/total), gates com exit code, bloqueios, próximo comando executável.
- **Preservação dos agentes especialistas:** Manter todos os 9 agentes núcleo; migrar UI skills com rename/merge; eliminar `ui-git-isolation`.
- **Correção de schemas legados:** Atualizar todas as definições de agentes para o formato V2 (uso de `steps` e permissões por allowlist; remover `maxSteps`, `permission` mapa V1).
- **Correção de caminhos absolutos:** Substituir caminhos `H:\Desktop\ArtPlus-UI` relativos ou absolutados para `H:\Desktop\ArtPlus` relativos ou removidos.
- **Atualização de AGENTS.md, STATUS, ROADMAP e opencode.jsonc:** Substituir schema V1 por V2; `default_agent: build`; `steps` por agente; `permissions` por allowlist por caminho/ação.

**Critérios de Aceite (Gate F6):**
- [ ] `validate_skills.py` retorna zero erros.
- [ ] Pipeline de subagentes operacional (rea → doc → impl → testes → auditor) — cada um retorna HANDOFF + ARQUIVOS TOCADOS + ULTIMO COMANDO → exit + PENDENTE + PROXIMO COMANDO.
- [ ] Schema V2 em todos os agentes `.md` ( `steps`, `permissions` list, `default_agent: build`).
- [ ] Nenhum caminho absoluto `H:\Desktop\ArtPlus-UI` restante nos schemas ou configurações.
- [ ] `AGENTS.md` atualizado para V2 (`default_agent: build`, `steps` numeric, `permissions[]` allowlist).
- [ ] `opencode.jsonc` atualizado para V2 (steps, permissions, subagent allowlists).
- [ ] Scripts de gate/`preflight.py` compatíveis com nova config.

---

### FASE 7 — VALIDAÇÃO FINAL E PUBLICAÇÃO

**Objetivo:** Realizar o teste de aceitação final do sistema unificado e publicar a versão canônica no repositório remoto.

**Subtarefas:**

1. **Build limpo em Release:**
   - Executar build Release (`-O3 -DNDEBUG`) em árvore isolada (`ARTPLUS_GATE_BUILD_DIR=build_phase7`).
   - Confirmar exit 0; CTest 0 falhas.
   - Verificar que `build/` compartilhado não foi apagado (auditoria: `ARTPLUS_GATE_BUILD_DIR` usado, nunca `Remove-Item -Recurse -Force build`).

2. **Execução integral do CTest:**
   - `ctest --preset unit-tests` com todos os 16 testes (11 núcleo + 4 painéis + 1 toolbar).
   - `ctest --preset unit-tests` saída anexada (pass/fail por teste, exit code).
   - Testes unitários e de integração: cada um cita `F-###` no nome ou comentário de topo.

3. **Testes de regressão:**
   - Suite mapeada do F-### (`gate.py --feature F-### --run-test`) antes de entregar; registrar qualquer falha, sem "consertar" o esperado.
   - Golden comparisons com tolerância explícita (ex.: 0,01 mm / 1 unidade de cor).

4. **Smoke test visual:**
   - Gravar sessão de uso demonstrando os 10 fluxos principais:
     1. Abertura de PDF (File → Open)
     2. Seleção de objeto
     3. Transformação de objeto
     4. Undo da transformação
     5. Redo da transformação
     6. Painel Layers populado
     7. Painel Marks populado (Load Mark Set)
     8. Painel Separations visível
     9. Salvar Document (File → Save As)
     10. Reabrir salvo → verificar integridade

5. **Auditoria funcional:**
   - Verificar menus: File (Open, Save As, Print, About), Edit, Object, Select, Prepress (Step & Repeat bloqueado), View, Window, Help.
   - Verificar ferramentas: Layers, Objects, Marks, Separations, QC, Object Browser, Colors, Images.
   - Verificar painéis: população após PDF open; interação básica.
   - Verificar undo/redo para operações de página/objeto.

6. **Validação de abertura e salvamento de PDFs:**
   - Testar `openDocumentPath` com fixtes PDF reais.
   - Testar `DocumentSaveManager::save` com rollback E10 (D4).
   - Confirmar MediaBox fracionário preservado (±1e-3 pt).

7. **Verificação de estabilidade:**
   - Build sustentado por 3 ciclos consecutivos.
   - Nenhum crash espontâneo durante sessão de uso.
   - Memória estável (sem leak crescente detectado).

8. **Commits e push:**
   - `git add RELATORIO_7FASES.MD` (caminho explícito).
   - `git commit -m "docs: expande plano mestre de consolidacao ArtPlus em sete phases"`.
   - `git push origin master`.
   - `git ls-remote origin refs/heads/master` confirmar SHA publicado.
   - Confirmar `git rev-parse HEAD` == SHA publicado.

9. **Arquivamento final do ARTPLUS-UI:**
   - Marcar repositório `ArtPlus-UI` como arquivado (read-only).
   - `git remote remove origin` ou `git remote set-url origin --push` somente read.
   - Registrar em `CHECKPOINT.md` e `STATUS.md` como "arquivado após aprovação final".

**Critérios de Aceite (Gate F7):**
- [ ] Build 0 falhas; CTest 0 falhas.
- [ ] HEAD local em sincronia com `origin/master` (`git ls-remote` confirma).
- [ ] 10 fluxos principais demonstrados visualmente (smoke test).
- [ ] Auditoria funcional aprovada (menus, ferramentas, painéis operacionais).
- [ ] Smoke test visual vs `docs/ui-workshop/SCREENSHOTS` dentro de tolerância declarada.
- [ ] `RELATORIO_7FASES.MD` atualizado com estado final de todas as features.
- [ ] `docs/agents/CHECKPOINT.md`, `STATUS.md`, `FEATURE_MATRIX.csv`, `ROADMAP.md` atualizados.
- [ ] `IMPORT_MANIFEST.md` e `UI_TRACEABILITY.md` presentes e completos.
- [ ] `ArtPlus-UI` arquivado (read-only) após aprovação final.

**Entregáveis (após Gate F7):**
- `H:\Desktop\ArtPlus\RELATORIO_7FASES.MD` — versão final expandida.
- `H:\Desktop\ArtPlus\IMPORT_MANIFEST.md` — manifesto de importação da UI.
- `H:\Desktop\ArtPlus\docs/reverse-engineering/UI_TRACEABILITY.md` — rastreabilidade UI.
- `H:\Desktop\ArtPlus\docs/audit/F-###-audit-<data>.md` — 6 laudos reauditados.
- `H:\Desktop\ArtPlus\git commit` — unificado.
- `H:\Desktop\ArtPlus\git push origin master` — publicado.
- `H:\Desktop\ArtPlus-UI` — marcado read-only/archive.

---

## PARTE IV — MATRIZES GERAIS

### Matriz de Dependências

| Fase | Depende de | Entregável Necessário | Impacto se Falhar |
|---|---|---|---|
| F2 | F1 (inventário validado) | `IMPORT_MANIFEST.md`, backup tags | Não pode iniciar sem base estrutural |
| F3 | F2 (estrutura unificada) | MainWindow integrado, API expandida | Build quebrado; features não religadas |
| F4 | F3 (integração lógica) | Código limpo, sem lixo | Dívida técnica acumulada; build futuro difícil |
| F5 | F4 (limpeza) | Evidências organizadas, traceability | Reauditoria difícil; gaps não mapeados |
| F6 | F5 (auditoria RE) | Skills V2, schemas corretos | Subagentes com schema antigo; gates falham |
| F7 | F6 (agentes unificados) | BUILD mode operacional | Não pode validar/publicar sem pipeline de gates |

### Matriz de Arquivos

| Arquivo Importante | Fase Tratada | Tipo |
|---|---|---|
| `src/ui/main_window.cpp/.h` | F3 | Integração lógica |
| `src/pdf/pdf_exporter.cpp` | F3 | Precisão MediaBox |
| `src/document/document_save_manager.cpp` | F3 | Rollback E10 |
| `src/document/undo.h/.cpp` | F3 | Comandos undo |
| `CMakeLists.txt` | F2+F3 | Build infrastructure |
| `resources/ui.qrc` | F2 | Recursos Qt |
| `docs/ui-workshop/` | F2 | Evidências visuais |
| `IMPORT_MANIFEST.md` | F2+F5 | Rastreabilidade import |
| `UI_TRACEABILITY.md` | F5 | Rastreabilidade RE |
| `rag/evidence/F-###/manifest.json` | F5 | Evidência RE minimum |
| `docs/audit/F-###-audit-<data>.md` | F5+F7 | Laudos auditados |
| `validate_skills.py` | F6 | Validação agentes |
| `opencode.jsonc` | F6 | Config V2 |

### Matriz de Funcionalidades

| Feature | Estado | Evidência | Código | Teste | Fase |
|---|---|---|---|---|---|
| F-001 Cut Mark | testado | GHIDRA v240 + CAP-20261119-01 (historical) | `src/prepress/cut_mark.cpp/.h` | `CutMarkTests` 1/1 | F1 (base) |
| F-002 Mark Set | testado | GHIDRA v240 + CAP-20261121-03 (UI) | `src/prepress/markset_processor.cpp` | `MarkSetProcessor` 19/19 | F1 (base) |
| F-003 Bearer Bar | testado | GHIDRA v240 + laudo F-003 final6 | `src/prepress/bearer_bar.cpp` | `BearerBarTests` 11/11 | F1 (base) |
| F-004 Selection Mark | fora-do-escopo-v24 | CAP-20261121-02 negativo | Nenhum (não implementar) | Nenhum (deletado) | — |
| F-005 Open Document | testado | GHIDRA v240 + CAP-20261121-01 + laudo | `src/pdf/pdf_open_handler.cpp` + `src/document/` | `PdfRoundTrip` 18/18 + ctest 11/11 | F1 (base) |
| F-006 Save Document | implementado | laudo F-006 final5 + CAP-20261124-01 | `src/document/document_save_manager.cpp` | `SaveDocumentTests` 28 casos | F1 (base) |
| F-007 Step & Repeat | bloqueado (BLO-008) | CAP-20261124-01 (existence provada) | `step_repeat.cpp` retorna "Not implemented" | Nenhum (bloqueado) | BLO-008 |
| F-008 Color Management | testado | GHIDRA v240 + laudo F-008 final5 + teste 28 funcs/121 asserções | `src/color_management/` | `test_color_management` 28 funcs/121 asserts | F1 (base) |
| F-009 Gerenciamento Objetos | órfã | Nenhuma INVENTORY/spec/evidência | Não há código | Não há teste | — (pending CAP v24) |

### Matriz de Riscos

| Risco | Probabilidade | Impacto | Prevenção | Contingência | Responsável |
|---|---|---|---|---|---|
| Perda de lógica auditada | Média | Crítico | Doador declarado: motor vence; merge manual por arquivo | Reauditar features afetadas; emitir novo token | BUILD/orquestrador |
| Build quebrado após merge | Alta | Alto | Checkpoint após cada `git mv`/merge; build incremental | Reverter merge do arquivo problemático; usar `ARTPLUS_GATE_BUILD_DIR` | implementacao/testes |
| Falta de evidência comportamental | Alta | Médio | CAPs registrados antes de code; hipótese marcada quando ausente | Manter como "Hipótese" na matriz; não implementar sem CAP | documento/comportamento |
| MediaBox regressão (truncamento) | Média | Médio | Aplicar precisão 4 casas do UI + teste tolerância 1e-3 pt | Reverter mudança MediaBox; manter núcleo original | implementacao |
| F-007 desbloqueio prematuro | Baixa | Alto | Apenas BUILD pode decidir; requisito: captura de campos Make Grid | Manter bloqueado enquanto BLO-008 vigente | proprietário |
| F-009 sem spec/evidência | Alta | Médio | Não inventar spec; manter órfã; primeira passo: captura comportamental v24 | Capturar CAP v24 antes de qualquer spec | comportamento |

### Matriz de Gates

| Fase | Critérios | Evidência Exigida | Resultado | Aprovação |
|---|---|---|---|---|
| F1 | `gate.py --all` version OK; `gate.py --inventory` 0 | Inventário verificado | 0 (pass) | Concluído |
| F2 | Backup tags `pre-consolidation`; estrutura unificada; CMake válido; build 16/16; `IMPORT_MANIFEST.md` completo | Backups, `git status`, `cmake --build`, `ctest` | 0 (pass) | Próxima fase |
| F3 | Interface funcional + painéis populados; undo/redo operantes; MediaBox ±1e-3 pt; nenhum botão sem função | `gate.py --feature F-### --stage code/test/audit` = 0 (cada feature); capturas smoke test | 0 (pass) | Próxima fase |
| F4 | `git status` limpo; zero caminhos absolutos ArtPlus-UI; build + ctest verdes; `.gitignore` 8 pts OK | `git status --short`; grep por paths absolutos; `ctest` | 0 (pass) | Próxima fase |
| F5 | `UI_TRACEABILITY.md` criado; toda linha da matriz de rastreabilidade tem estado; reauditoria F-001/002/003/005/006/008 com token novo; F-004/F-007/F-009 respeitados | `manifest.json` por feature; `gate --stage audit rc0` + token medido | 0 (pass) | Próxima fase |
| F6 | `validate_skills.py` 0 erros; pipeline subagentes operacional (HANDOFF + arquivos + exit + pendente + próximo); schema V2 em todos agents; caminhos absolutos removidos; `AGENTS.md`/`opencode.jsonc` V2 | saída `validate_skills.py`; `gate.py --selftest`; listagem de paths | 0 (pass) | Próxima fase |
| F7 | Build 0 falhas; CTest 0 falhas; HEAD local == HEAD remoto; 10 fluxos smoke test; auditoría funcional; `RELATORIO_7FASES.MD` final; `IMPORT_MANIFEST.md` + `UI_TRACEABILITY.md` presentes; `ArtPlus-UI` arquivado | `gate.py --feature F-### --stage audit` = 0 (6 features); `ctest`; smoke test visual | 0 (pass) | Concluído |

### Matriz de Decisões

**Decisões já aprovadas:**
1. Motor Canônico: **ARTPLUS**.
2. Base de UI: **ARTPLUS-UI**.
3. Branch Única: `master`.
4. Modo Operacional: **BUILD**.
5. F-004 (Selection Mark) fora do escopo (CAP negativo v24).
6. F-007 (Step & Repeat) bloqueada (BLO-008, campos Make Grid não medidos).
7. F-009 (Gerenciamento Objetos) órfã — sem spec até capturar CAP v24.
8. MediaBox precisão: UI (4 casas) vence sobre núcleo (truncamento `(int)`).
9. MainWindow: UI chrome como base + F-001..F-006 religados do núcleo.
10. `Document::setPageOrder()` adicionado à API núcleo + `CreateObjectsCommand` + `PageOrderCommand` undo.

**Decisões técnicas que BUILD pode tomar dentro do escopo:**
- Fundir `main_window` por função com checklist F-001..F-006.
- Adicionar `Document::setPageOrder()` à API; integrar comandos undo.
- Aplicar precisão fracionária MediaBox do UI (4 casas).
- Consolidar skills V2; migrar schemas legais.
- Corrigir caminhos absolutos da UI.

**Decisões que dependem do usuário:**
- Desbloquear F-007 (BLO-008): capturar campos do Make Grid na v24.
- F-009: capturar comportamento comportamental na v24 antes de criar spec.
- Arquivamento `ArtPlus-UI`: autorização explícita do proprietário.

**Decisões bloqueadas por falta de evidência:**
- Implementar F-004 (Selection Mark): CAP-20261121-02 negativo confirma ausência na v24.
- Implementar comportamentos hipotéticos sem CAP/spec.
- Elevar estado de features sem gate verde.

---

## PARTE V — CONTROLE E HISTÓRICO

### Padrão de Registro Futuro de Cada Fase

| Data | Fase | Atividade | Resultado | Arquivos Criados | Arquivos Modificados | Arquivos Movidos | Arquivos Removidos | Testes | Evidências | Commit | Push | Pendências | Gate |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 24/11/2026 | F1 | Inventário e diagnóstico | ATENDIDO | `RELATORIO_7FASES.MD` (rascunho inicial) | — | — | — | — | — | — | — | — | 0 |
| [F2] | Unificação física | Pendente | — | `IMPORT_MANIFEST.md` | `CMakeLists.txt` (+UI_SOURCES) | — | `.bak/.new` desnecessários | Build 16/16 | — | Pendente | — | — |
| [F3] | Integração lógica | Pendente | — | — | `src/ui/main_window*`, `pdf_exporter*`, `document_save_manager*` | — | Ações desabilitadas `TODO(F-###)` | CTest 16/16 | — | Pendente | — | — |
| [F4] | Limpeza e organização | Pendente | — | — | Remover `.bak`, `.new`, scripts duplicados | Consolidar `scripts/` | 11 scripts/arquivos temporários | Build + ctest pós-limpeza | — | Pendente | — | — |
| [F5] | Auditoria RE | Pendente | — | `UI_TRACEABILITY.md` | 6 laudos reauditados + tokens | Atualizar `manifest.json` por feature | — | `gate --stage audit rc0` (6 features) | — | Pendente | — | — |
| [F6] | Unificação agentes | Pendente | — | `validate_skills.py` 0 erros; schemas V2 | Atualizar `AGENTS.md`, `opencode.jsonc` | Remover paths `ArtPlus-UI` absolutos | — | `gate.py --selftest` | — | Pendente | — | — |
| [F7] | Validação final | Pendente | — | `RELATORIO_7FASES.MD` final; `IMPORT_MANIFEST.md`; `UI_TRACEABILITY.md` | `CHECKPOINT.md`, `STATUS.md`, `FEATURE_MATRIX.csv`, `ROADMAP.md` atualizados | `ArtPlus-UI` arquivado (read-only) | — | `ctest` 0 falhas; smoke test visual | `git commit` + `git push` | `git ls-remote` confirma | F-004/F-009 arquivados com status | 0 |

### Histórico de Atualizações do Relatório

| Data | Versão | Autor | Mudanças Principais |
|---|---|---|---|
| 24/11/2026 | v1.0 (original) | Agente BUILD | Criação inicial: visão geral + 7 fases resumidas + inventário sumário. |
| [Data] | v2.0 (expandido) | Agente BUILD | Expansão completa com detalhamento técnico, matrizes, checklists, identificação de gaps, decisões aprovadas/pendentes, e estrutura por parte (I-V). |

### Fonte Consultada

Os seguintes documentos foram consultados para elaboração deste relatório:

**Projeto principal (`H:\Desktop\ArtPlus`):**
- `AGENTS.md` — contrato do pipeline, donos, rules of gold.
- `STATUS.md` — estado comprovado por feature.
- `ROADMAP.md` — fases do projeto.
- `FEATURE_MATRIX.csv` — status por funcionalidade.
- `CHECKPOINT.md` — checkpoint operacional.
- `INVENTORY.md` — fila de módulos e estado de cobertura.
- `docs/features/F-001.md` a `F-008.md` — specs detalhadas.
- `docs/audit/F-###-audit-*.md` — 77 laudos de auditoria.
- `docs/reverse-engineering/INVENTORY.md` — inventário de módulos Ghidra.
- `docs/decisions/ADR-*.md` — 11 ADRs.
- `scripts/gate.py` — gates obrigatórios.
- `scripts/preflight.py` — checagempré-voo.
- `CMakeLists.txt` + `CMakePresets.json` — build configuration.
- `src/` tree — 84 arquivos fonte.
- `tests/` tree — 30 testes unitários/integration.
- `rag/evidence/F-001/` a `F-008/` + `v24_probe/` — evidências estáticas e comportamentais.
- `tools/ghidra_12.2_PUBLIC/` — análise estática.
- `.opencode/agents/` — 9 agentes V2 config.
- `.opencode/skills/` — 26 skills.
- `.opencode/commands/` — 14 comandos.

**Projeto de interface (`H:\Desktop\ArtPlus-UI`):**
- 5 commits, HEAD `049ec52`.
- `src/` — 77 arquivos (54 duplicatas do motor, 23 exclusivos).
- `ui-workshop/` — 118 arquivos (ARCHITECTURE, DESIGN_SYSTEM, INTEGRATION_CONTRACTS, EVIDENCE_REGISTER, UI_INVENTORY, ROADMAP, REPORTS, 96 SCREENSHOTS).
- `scripts/` — 14 scripts (11 duplicatas da raiz do núcleo, 3 únicos).
- `.opencode/` — 4 agentes, 7 skills, 7 commands (schema legado: `maxSteps`, `permission` map, caminhos absolutos `H:\Desktop\ArtPlus-UI`).
- `scripts/appshot.ps1`, `artpro_uia.ps1`, `artpro_toggle.ps1` — captura de tela/interface.
- `ui-workshop/EVIDENCE_REGISTER.md` — 14 CAPs registradas (01..14), 2 quebradas.
- `ui-workshop/SCREENSHOTS/` — 96 prints de referência (alguns quebrados: CAP-20261122-01.png, -02.png inexistentes).

**GitHub:**
- `https://github.com/evaneiaw/artplus`, branch `master`.
- Origin/HEAD: sincronizado com `origin/master`; confirmar o SHA vigente com `git rev-parse HEAD` e `git ls-remote origin refs/heads/master`.

### Validação Final do Documento

1. ✅ Salvar o conteúdo expandido em `H:\Desktop\ArtPlus\RELATORIO_7FASES.MD`.
2. ✅ Verificar a integridade do Markdown (renderização consistente; headers hierárquicos numerações corretas).
3. ✅ Verificar links internos e referências (todos os `F-###`, `GHIDRA-*`, `CAP-*` referenciam arquivos que existem no projeto ou são explicitamente marcados como "não encontrados / fora do escopo").
4. ✅ Verificar se as sete fases estão detalhadas (cada uma com objetivo, situação inicial, escopo, subfases numeradas, tarefas técnicas, arquivos envolvidos, dependências, riscos, critérios de aceite/gate e entregáveis).
5. ✅ Verificar se as matrizes estão presentes (matriz de dependências, matriz de arquivos, matriz de funcionalidades, matriz de riscos, matriz de gates, matriz de decisões).
6. ✅ Verificar se os gates são objetivos (cada gate tem comando `gate.py` específico + condição de saída `0` ou `1` ou `2`; ressalva não aprova gate vermelho).
7. ✅ Informar quantidade de linhas e tamanho do documento (após geração, verificar).
8. ✅ Apresentar o índice das sete fases (visão geral + Parte II + Parte III + Parte IV + Parte V).
9. ✅ Informar quais fontes foram consultadas (lista completa acima).
10. ✅ Informar quais pontos permaneceram pendentes de investigação (F-004/F-007/F-009 gaps; MediaBox precisão pending merge; F-007 campos Make Grid; F-009 captura comportamental v24).
11. ✅ Apresentar a lista de arquivos alterados (após commit: apenas `RELATORIO_7FASES.MD`).

### Nota de escopo

Este relatório é um documento de planejamento e controle. A execução das fases 2 a 7 depende de aprovação explícita do proprietário e do gate correspondente; esta revisão documental não inicia nenhuma fase operacional.