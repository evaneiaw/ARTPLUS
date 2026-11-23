# PACKAGE_A — desbloquear a fábrica (relatório de execução)

**Data:** 2026-11-21 · **Executor:** `orquestrador` (coordenação + verificação independente)
**Modo:** HALT ativo; nenhuma funcionalidade F-XXX avançou ou foi aprovada.
**Referência:** Esko ArtPro+ **v24.03.10017**.

---

## 1. Levantamento de estado (antes de alterar)

| Item | Valor |
|---|---|
| Branch / HEAD | `master` / `706cbdf` (1 commit à frente de `origin/master`) |
| Processos pesados | nenhum (`java`, `cmake`, `g++`, `ctest`, `ArtPro+` ausentes) |
| Modificados rastreados | `CMakeLists.txt`, `CMakePresets.json`, `src/document/document_model.*`, `src/ui/main_window.*`, docs de estado, entre outros |
| Untracked críticos | `src/automation/*`, `src/prepress/*`, `src/color/*`, `src/document/document_save_manager.*`, `tests/unit/test_*.cpp`, `rag/evidence/F-00*` |
| HALT | **ativo** (`docs/agents/HALT.md`) |

Nenhum `git reset`, `clean`, `rebase` ou descarte foi executado. Todo o trabalho de outras
sessões foi preservado no working tree.

---

## 2. Diagnóstico (antes de escolher a correção)

### 2.1 BLO-006 — `QJSEngine`

- Varredura de `src/automation/scripting.cpp`: `QJSEngine` aparece **somente** em
  `#include <QJSEngine>` e em `QJSEngine* engine = nullptr;` (struct `Private`), nunca
  instanciado/desreferenciado. Não há `QJSValue` nem chamada de API.
- Portanto a correção mínima é **forward declaration** `class QJSEngine;`, sem linkar
  `Qt6::Qml`. Linkar Qml puxaria qtdeclarative em dois executáveis para um ponteiro nulo.
- **Efeito colateral revelado:** após corrigir o include, o link de `ArtPlus`/`unit_tests`
  chegou a um erro latente de **ODR**: `src/geometry/geometry_engine.h` definia 7 funções
  livres no header **sem `inline`** (linhas 157, 167, 187, 195, 202, 227, 236 no HEAD).
  Qualquer alvo com dois TUs incluindo o header violava a ODR (o `test_markset_processor`
  era o primeiro). Correção: `inline` nas 7 funções — mudança puramente de linkage.

### 2.2 `test_markset_processor.cpp`

- `Page` **não tem `setId`**: o ctor atribui `m_id = nextId++` e `Page::nextId = 1`
  (`document_model.cpp:20`). O caso "target id 0" do teste era **impossível de construir**.
- O contrato real de `copyMarksToPage(const Document&, const Page&)`:
  `false` para documento de origem sem páginas; `true` quando há página e os 4 sets
  hardcoded aplicam. `applyMarksFromSet` recusa apenas id vazio.
- O teste foi reescrito contra o contrato real (6 casos com `QVERIFY`/`QCOMPARE`), incluindo
  um caso que **documenta** por que id 0 não é testável — em vez de omiti-lo.

### 2.3 Testes com `0xc0000135`

`UnitTests` e `PdfRoundTrip` não tinham `set_tests_properties(... ENVIRONMENT "PATH=...")`;
o loader não achava `Qt6Core.dll`. Correção: duas linhas, no mesmo padrão dos demais testes.

---

## 3. Arquivos alterados/criados

| Arquivo | Alteração |
|---|---|
| `src/automation/scripting.cpp` | `#include <QJSEngine>` → `class QJSEngine;` (stub preservado) |
| `src/geometry/geometry_engine.h` | 7 funções ganharam `inline` (ODR) |
| `CMakeLists.txt` | `ENVIRONMENT PATH` para `UnitTests` (l.179) e `PdfRoundTrip` (l.190) |
| `tests/unit/test_markset_processor.cpp` | reescrito contra o contrato real |
| `scripts/gate.py` | `--build`, `--run-test`, `--stage code/test/audit`, `--emit-token`, `--selftest`, artefatos |
| `docs/testing/GATE.md`, `docs/testing/gates/**` | documentação e artefatos verificáveis |
| `docs/agents/CHECKPOINT.md` | estado do Pacote A |

---

## 4. Gate com execução real

Comandos executados **pelo orquestrador** (não apenas relatados):

```powershell
python scripts/gate.py --selftest
python scripts/gate.py --build
python scripts/gate.py --feature F-001 --run-test
python scripts/gate.py --feature F-002 --run-test
python scripts/gate.py --feature F-004 --run-test
python scripts/gate.py --feature F-006 --run-test
python scripts/gate.py --feature F-003 --run-test
python scripts/gate.py --feature F-005 --run-test
python scripts/gate.py --feature F-001 --stage code
python scripts/gate.py --feature F-001 --stage test
python scripts/gate.py --feature F-003 --stage test
python scripts/gate.py --feature F-002 --emit-token
python scripts/gate.py --feature F-002 --stage audit
python scripts/gate.py --feature F-002 --stage code
python scripts/gate.py --inventory
```

### Artefatos (reais, com hash)

- `docs/testing/gates/build.json` — `exit_code=0`, `log_sha256=9EAFDEAE…AD68`, `build_dir=build_audit`.
- `docs/testing/gates/F-001.xml` / `F-001.test.json` — `CutMarkTests passed`, `xml_sha256=D578E2BA…55CC`.
- `docs/testing/gates/F-002.test.json` — `MarkSetProcessor passed`, `xml_sha256=B8988CEB…10BF`.
- `docs/testing/gates/F-003.test.json` — `BearerBarTests failed`, `xml_sha256=2FC6A4B6…86FC`.
- `docs/testing/gates/F-005.test.json` — `PdfRoundTrip failed`, `xml_sha256=F9DE4C2D…6145`.
- Logs em `docs/testing/gates/logs/`.

### `--selftest`

```
TOTAL: 16/16 PASS
```

Cenários: tudo ok; teste falho; auditoria reprovada; HALT; `CAP-BLOCKED`; doc incompleta;
inventário adiantado; conclusão sem evidência; hash divergente; build não executado; teste
não executado; token divergente; build stale; build exit≠0; test stale; feature sem teste.
Repositórios temporários, sem tocar no código real.

### Comportamento dos gates de etapa

| Comando | Exit | Resultado |
|---|---|---|
| `F-001 --stage code` | 0 | código comprovado |
| `F-001 --stage test` | 0 | teste executado e verde |
| `F-003 --stage test` | 1 | `F-003.test.json` registra exit 8 e 1 falha (BearerBar) |
| `F-002 --stage code` | 1 | spec não declara arquivos `src/` |
| `F-002 --stage audit` | 1 | laudo sem token de gate (esperado `602284…6653`) |
| `F-002 --emit-token` | 0 | token impresso |
| `--inventory` | 1 | 8/8 estados declarados = comprovados; avanço bloqueado |

---

## 5. Build Release

`python scripts/gate.py --build` → `cmake --build build_audit -j 6` → **exit 0**.
Todos os alvos construídos, incluindo `ArtPlus`, `unit_tests` e `test_markset_processor`.

---

## 6. CTest completo + XML

`ctest --test-dir build_audit --output-on-failure --output-junit <absoluto>/ctest-full.xml`

| # | Teste | Resultado |
|---|---|---|
| 1 | FormXObjects | Passed |
| 2 | PdfSmoke | Passed |
| 3 | UnitTests | **Failed** (asserção desatualizada) |
| 4 | PdfRoundTrip | **Failed** (4 asserções de import) |
| 5 | EditingTests | **Failed** (objeto deletado ainda exportado) |
| 6 | IntegrationTestBasic | **Failed** (roundtrip de imagem) |
| 7 | MarkSetProcessor | **Passed** |
| 8 | BearerBarTests | **Failed** (topologia R4/R6) |
| 9 | CutMarkTests | Passed |
| 10 | SelectionMarkTests | Passed |
| 11 | SaveDocumentTests | Passed |

**6/11 passam.** XML: `docs/testing/gates/ctest-full.xml`. `0xc0000135` eliminado.

Diagnóstico das duas falhas que estavam escondidas:
- `UnitTests`: `testDocumentCreation` exige `pageOrder().empty()`, mas `Document()` cria
  página+camada por projeto. **Defeito de teste**, não de produto.
- `PdfRoundTrip`: 4 asserções reais de import/roundtrip. **Defeito de produto/import**.

---

## 7. Testes de falha do gate

Cobertos pelo `--selftest` (16/16) e pelos casos reais acima. O gate **reprovou**
corretamente: teste não executado, artefato ausente, hash divergente, build stale,
`CAP-BLOCKED`, HALT e laudo sem token. Nenhum resultado foi simulado.

---

## 8. Problemas ainda pendentes

1. `UnitTests`: expectativa de `testDocumentCreation` desatualizada (teste).
2. `PdfRoundTrip`: 4 falhas de import/roundtrip (produto).
3. `EditingTests`: objeto deletado ainda é exportado (produto).
4. `IntegrationTestBasic`: roundtrip de imagem (produto).
5. `BearerBarTests`: topologia R4/R6, 5 vs 4 elementos (produto).
6. Evidência F-003/F-007 com cabeçalho corrompido (`24.03.10017.100173.10017`,
   `24.03.10017.10017`, `yaml` sem `---`). Parte veio de export da sessão paralela e parte
   de uma substituição em massa feita por este orquestrador — **registrado como erro meu**;
   a correção correta é reexportar, não substituir string.
7. Specs F-002/F-003/F-005/F-006/F-008 não declaram arquivos `src/` → `--stage code` reprova.
8. `rag/evidence/F-001` continua inexistente.
9. `F-004` contém evidência de `ColorManipulationLayer` (módulo errado).

---

## 9. Commit

**Não foi criado commit neste pacote.** Motivo real: o working tree mistura correções do
Pacote A com trabalho não validado de outras sessões. Em particular, `CMakeLists.txt`
referencia `${AUTOMATION_SOURCES}`/`${PREPRESS_SOURCES}` de arquivos **untracked** de outras
sessões (F-007/F-008 em stub). Commitar a correção de build exigiria publicar esse trabalho
não validado; commitar só parte deixaria o build quebrado no HEAD. Nenhuma das opções cumpre
"não commitar trabalho parcial ou não validado".

Opções para o proprietário:
- **(a)** autorizar commit do conjunto entrelaçado (preserva tudo, publica trabalho em
  andamento);
- **(b)** manter no working tree e commitar após o Pacote B reevidenciar e validar;
- **(c)** separar os arquivos por sessão antes de commitar.

SHA do HEAD atual (sem commit novo): `706cbdf0b851d14a53df727a3dfd92f06fffe49d`.

---

## 10. Conclusão do Pacote A

| Entrega | Estado |
|---|---|
| Diagnóstico BLO-006 | concluído (QJSEngine + ODR) |
| Correção BLO-006 | concluída e verificada (build exit 0) |
| Correção do teste Mark Set | concluída e verificada (6 casos, Passed) |
| Gate com build/CTest reais | concluído, `--selftest` 16/16 |
| Artefatos verificáveis | gerados com hash |
| CTest + XML | executado; 6/11, falhas reais documentadas |
| Estados F-001…F-008 | inalterados (nenhum aprovado) |
| Commit | **retido** por entrelaçamento de trabalho não validado |

**Aguardando autorização explícita para o Pacote B.**
