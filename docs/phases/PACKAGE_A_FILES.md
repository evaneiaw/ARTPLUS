# PACKAGE_A_FILES — separação de alterações (opção C)

**Data:** 2026-11-21 · **Objetivo:** separar o Pacote A do trabalho de outras sessões,
sem descartar nada, e decidir se há commit exclusivo possível.
**Resultado:** **não é possível isolar o Pacote A completo**. Nenhum commit foi feito.

---

## 1. Inventário do working tree

- Branch `master`, HEAD `706cbdf` (1 commit à frente de `origin/master`).
- 21 arquivos rastreados modificados; ~150 arquivos untracked.
- `git diff --stat` total: **21.603 inserções / 20.119 remoções**.
- `CMakeLists.txt` sozinho: **140 linhas alteradas** (não são apenas as 2 do PATH).
- Nenhum processo de build/Ghidra ativo; HALT ativo.

---

## 2. Arquivos do Pacote A

### 2.1 Exclusivos (podem ser isolados)

| Arquivo | Origem | Observação |
|---|---|---|
| `src/geometry/geometry_engine.h` | Pacote A | diff = 7 × `inline` (14 linhas); nenhuma outra alteração |
| `scripts/gate.py` | Pacote A | diff = 933 linhas; execução real de build/CTest, artefatos, token |
| `docs/agents/CHECKPOINT.md` | Pacote A | 14 linhas (estado do Pacote A) |
| `docs/testing/GATE.md` | Pacote A | documentação do gate |
| `docs/testing/gates/**` | Pacote A | artefatos JSON/XML/logs com hash |
| `docs/phases/PACKAGE_A.md` | Pacote A | relatório do pacote |
| `docs/phases/PACKAGE_A_FILES.md` | Pacote A | este arquivo |

### 2.2 Compartilhados (contêm alteração do Pacote A dentro de arquivo de outra sessão)

| Arquivo | Situação |
|---|---|
| `CMakeLists.txt` | **140 linhas alteradas** por várias sessões (listas de fontes, alvos novos, BOM) + **2 linhas** do Pacote A (`ENVIRONMENT PATH` em `UnitTests` e `PdfRoundTrip`). Não há como commitar só as 2 linhas sem reescrever o arquivo. |
| `src/automation/scripting.cpp` | Arquivo **untracked** da sessão de automação; o Pacote A alterou **1 linha** (`#include <QJSEngine>` → `class QJSEngine;`). Commitar o arquivo publica o stub inteiro de outra sessão; não commitar perde a correção do BLO-006. |

### 2.3 Arquivo de teste do Pacote A com dependência untracked

| Arquivo | Situação |
|---|---|
| `tests/unit/test_markset_processor.cpp` | Reescrito pelo Pacote A, mas **untracked** e depende de `src/prepress/markset_processor.h/.cpp` (também untracked, sessão F-002). Isolado, não compila. |

---

## 3. Prova do impedimento (dependências do CMakeLists)

`CMakeLists.txt` não usa GLOB: ele **lista arquivo por arquivo**.

```
DOCUMENT_SOURCES   -> src/document/{document_model,document_serializer,undo,
                      document_save_manager}.cpp/.h
PREPRESS_SOURCES   -> src/prepress/{selection_mark,bearer_bar,cut_mark,
                      markset_processor,trapping,step_repeat,packaging,marks,
                      imposition}.cpp/.h + color_manipulation/...
AUTOMATION_SOURCES -> src/automation/{action_list,scripting,recovery,performance}.cpp/.h
UI_SOURCES         -> src/ui/main_window.cpp/.h
```

Estado desses arquivos no Git:

- `src/prepress/**` — **untracked** (F-001 a F-008).
- `src/automation/**` — **untracked** (sessão de automação).
- `src/document/document_save_manager.*` — **untracked** (F-006).
- `src/document/document_model.*`, `document_serializer.cpp`, `src/ui/main_window.*` — **modificados** por outras sessões.
- `src/color/**` — **untracked** (F-008).

Consequência: o build verde do Pacote A (`ArtPlus`, `unit_tests`, `test_markset_processor`)
**depende de dezenas de arquivos untracked de outras sessões**. Um commit do `CMakeLists.txt`
publicaria referências a arquivos não rastreados (build quebrado no HEAD) ou exigiria
commitar todo esse trabalho alheio — proibido pela autorização.

---

## 4. Classificação do restante (outras sessões — preservado, não commitado)

| Grupo | Arquivos (exemplos) |
|---|---|
| F-001…F-005 | `src/prepress/{cut_mark,bearer_bar,markset_processor,selection_mark,marks}.*`; `tests/unit/test_{cut_mark,bearer_bar,selection_mark}.cpp`; `rag/evidence/F-00{1..5}/**` |
| F-006 | `src/document/document_save_manager.*`; `tests/unit/test_save_document.cpp`; `docs/audit/F-006-audit.md` |
| F-007 | `src/prepress/{step_repeat,imposition,packaging,trapping}.*`; `rag/evidence/F-007/**`; `docs/reverse-engineering/LayoutEngine_GHIDRA.md` |
| F-008 | `src/prepress/color_manipulation/**`; `src/color/**`; `rag/evidence/F-008/**`; `docs/architecture/F-008-ADR.md`; `docs/behavior/F-008.md` |
| Automação | `src/automation/{action_list,performance,recovery,scripting}.*` |
| Documento/UI | `src/document/document_model.*`, `document_serializer.cpp`, `src/ui/main_window.*` |
| Evidência/tooling | `rag/ghidra/exports/**`, `rag/sources/**`, `docs/reverse-engineering/*AUTO_TRIAGE.md`, `tools/ghidra_analysis/**`, `tools/ghidra_projects/**` |
| Artefatos de execução | `build_audit/`, `build_test/`, `CMakeCache.txt`, `CMakeFiles/`, `Makefile`, `Testing/`, `*.ps1`, `*.txt` de scratch, `test_vector.pdf` |
| Docs de estado de outras sessões | `docs/ROADMAP.md`, `docs/EXECUTION_LOG.md`, `docs/agents/CONFLITOS.md`, `docs/decisions/ADR-004-*.md` |

---

## 5. Veredito de isolamento

| Tentativa | Resultado |
|---|---|
| Commit do Pacote A completo | **Impossível** sem publicar `scripting.cpp` (stub de outra sessão) e o `CMakeLists.txt` com 140 linhas alheias + fontes untracked |
| Commit só das partes exclusivas (`geometry_engine.h`, `gate.py`, docs) | **Possível tecnicamente, mas inválido** como Pacote A: não inclui BLO-006, PATH dos testes nem o teste Mark Set; seria commit parcial, proibido pela autorização |
| Commit do teste Mark Set isolado | **Não compila**: depende de `src/prepress/markset_processor.*` untracked |
| Commit do `CMakeLists.txt` isolado | **Quebra o HEAD**: referencia fontes untracked |

**Decisão:** nenhum commit. Working tree preservado integralmente.

---

## 6. Validação após a separação lógica

Comandos reexecutados (nenhum arquivo de código alterado nesta etapa):

- `python scripts/gate.py --build` → exit 0.
- `ctest --test-dir build_audit --output-on-failure --output-junit <absoluto>` → 6/11.
- `python scripts/gate.py --selftest` → 16/16 PASS.

Resultados detalhados em `docs/phases/PACKAGE_A.md` §5–§7.

---

## 7. Caminho recomendado para commit futuro

1. Cada dono (sessão) valida e commita seu próprio conjunto (F-006, F-007, F-008, automação).
2. Depois, o Pacote A commita `geometry_engine.h`, `gate.py`, `docs/testing/**`, `CHECKPOINT`,
   `PACKAGE_A*` e — em um commit separado — as 2 linhas do `CMakeLists.txt` e a linha do
   `scripting.cpp`, quando esses arquivos já estiverem rastreados pelo dono.
3. Alternativa: autorização explícita para um commit-snapshot do working tree inteiro
   (publica trabalho em andamento, mas preserva tudo).

**Nada foi descartado, sobrescrito ou revertido. Nenhum push executado.**
