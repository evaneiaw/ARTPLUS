# AGENT_SYSTEM_RECOVERY_AUDIT — recuperação do sistema de agentes ArtPlus

**Data:** 2026-11-21 · **Auditor:** `orquestrador` (verificação factual, não declaração)
**Referência:** Esko ArtPro+ **v24.03.10017** (`C:\Esko\bg_prog_artpro+_v240`)
**Modo:** HALT ativo (`docs/agents/HALT.md`) — nenhuma funcionalidade avança.

---

## 0. Sumário executivo

O pipeline não estava apenas "atrasado": ele **declarava estados que os fatos não
sustentavam**. Cinco features constavam como `auditado` sem evidência válida; duas
constavam como `implementado` sendo esqueleto de `TODO`; o build principal estava quebrado;
e três registros oficiais (`INVENTORY.md`, `STATUS.md`, `FEATURE_MATRIX.csv`) se
contradiziam sobre a mesma feature.

Causa raiz: **o orquestrador não tinha ferramenta para verificar** (bash restrito a `git`)
e os subagentes podiam gravar evidência inconsistente sem que nada reclamasse. O gate
existia apenas como regra textual.

Correção aplicada: **trava mecânica** (`scripts/gate.py`) + **HALT** + contrato de gate em
todos os 9 agentes + permissões para o orquestrador verificar + reconciliação dos registros
com o estado comprovado. Nenhuma funcionalidade foi promovida; várias foram **rebaixadas**.

---

## 1. Método e comandos reproduzíveis

```powershell
# versão e consistência
python scripts/check_version.py

# estado comprovado por feature (novo gate)
python scripts/gate.py --all
python scripts/gate.py --inventory

# evidência: hash real dos binários de referência
Get-FileHash 'C:\Esko\bg_prog_artpro+_v240\...\DocumentMarks.dll' -Algorithm SHA256

# build e testes em diretório separado (não toca build/ de outras sessões)
cmake -S . -B build_audit -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release `
      -DCMAKE_PREFIX_PATH=C:/Qt/6.8.3/mingw_64 -DCMAKE_CXX_COMPILER=<WinLibs MSVCRT g++>
cmake --build build_audit -j 6
ctest --test-dir build_audit -R 'BearerBarTests|CutMarkTests|SelectionMarkTests|SaveDocumentTests|...' --output-on-failure
```

Ferramentas: `scripts/gate.py` (novo), `scripts/check_version.py`, CMake Kitware 4.4.4,
WinLibs POSIX.MSVCRT GCC 16.2.0, Qt 6.8.3 mingw_64.

---

## 2. Auditoria do orquestrador

| # | Critério | Achado | Correção |
|---|---|---|---|
| 1 | Função delimitada | Sim, mas sem poder de verificação | mantido + gate |
| 2 | Permissões × responsabilidade | **`bash` só permitia `git`** → não rodava build, ctest nem gate; por isso "aprovava" sem prova | adicionado `python scripts/gate.py*`, `check_version.py*`, `status.py*`, `ctest *`, `cmake --build/--preset/-S *` |
| 3 | Dependências obrigatórias | Regra textual, sem enforcement | **Gate zero** antes de qualquer despacho |
| 4 | Sabe quando parar | Não havia HALT | `docs/agents/HALT.md` + parada obrigatória |
| 5 | Critério verificável de conclusão | "relatório do subagente" | gate por etapa (código de saída 0) |
| 6 | Evidência | Exigia caminho, não conferia hash/existência | gate confere hash, resolução de ID e conteúdo |
| 7 | Pode alterar arquivo alheio | Sim (edição ampla) | HALT + §10.4 + gate; risco residual |
| 8 | Pode aprovar o próprio trabalho | Não audita a si, mas aceitava o laudo sem reexecutar | obrigação de rodar gate/build/ctest |
| 9 | Conflito de instruções | "não leia pseudocódigo" × "verifique você mesmo" | verificação passa a ser mecânica (gate), não leitura de binário |
| 10 | Ferramentas corretas | `bash` insuficiente; `task` ok | corrigido |

**Contradições encontradas no prompt:** (a) "máximo 3 subagentes" sem enforcement;
(b) "nunca pule o auditor" mas auditor aceitava ressalva com build quebrado;
(c) "estado real no roadmap" sem mecanismo para saber o estado real. Todas endereçadas
por `AGENTS.md §10`, `AUTOPILOT §13` e pelo gate.

---

## 3. Auditoria individual dos subagentes

| Agente | 1 Função | 2 Permissões | 3 Dependências | 4 Parada | 5 Conclusão | 6 Evidência | 7 Escreve fora | 8 Autoaprovação | 9 Conflito | 10 Ferramentas |
|---|---|---|---|---|---|---|---|---|---|---|
| `ghidra` | clara | ok | não checava | não | "exportou" sem validar conteúdo | **F-003 corrompido; F-004 módulo errado** | não | n/a | não | ok |
| `rea` | clara | ok | não checava | não | manifest sem validar hash | **hash de v25 em manifest v24** | não | n/a | não | ok |
| `comportamento` | clara | ok | não checava | registrava bloqueio | `CAP-BLOCKED` usado como evidência | docs com "Versão 25.0" | não | n/a | não | pc-control ok |
| `documentacao` | clara | **sem bash** → não rodava gate | não checava | não | escrevia spec sem evidência | F-002 cita `F-001/...` | não | n/a | não | bash insuficiente |
| `arquitetura` | clara | **sem bash** | não checava | não | ADR sem estado aprovado | ADR F-008 em pasta errada | não | n/a | ADR-004 reescrita p/ caber no código | bash insuficiente |
| `implementacao` | clara | ok | não checava ADR | não | "implementado" com TODO e build quebrado | sem saída de build | não | n/a | não | ok |
| `testes` | clara | ok | não checava | não | teste que não compila não bloqueava | build doctor sem enforcement | não | n/a | não | preset com caminho fixo |
| `auditor` | clara | ok | não checava gate | não | **ressalva aprovava build quebrado** | laudo stale não detectado | não | não (independente) | não | ok |

### Evidências dos achados

- **`ghidra` / F-003:** 19 arquivos com `versao: 24.03.10017.100173.10017`, primeiro token
  `yaml` em vez de `---`, e acentuação corrompida. Log `DocumentMarks_v240_export.log`:
  `ERROR Abort due to error: Requested project program file(s) not found: DocumentMarks.dll`.
- **`ghidra` / F-004:** `rag/evidence/F-004/ghidra/` contém **somente**
  `ColorManipulationLayer__*.md` — nenhum `PDFObjectActions__*.md`.
- **`rea` / hash:** `FFA8809D…` (manifest F-002) = SHA-256 de **DocumentMarks.dll da v250**;
  o binário v240 é `E47328BD…`. `92A8B38F…` (evidência F-008) = **ColorManipulationLayer v250**.
- **`comportamento`:** `docs/behavior/BearerBar.md`, `SelectionMark.md`, `TrimMarks.md`,
  `MarkSets.md` declaram **Versão 25.0** (v250) — fora do fluxo ativo.
- **`documentacao` / F-002:** spec cita `rag/evidence/F-001/...`.
- **`testes` / F-002:** `tests/unit/test_markset_processor.cpp` não compila
  (`Page` sem membro, `shared_ptr` mal usado) e tem 2 asserções triviais.

---

## 4. Auditoria de configurações, comandos e skills

| Item | Estado | Observação |
|---|---|---|
| `.opencode/agents/*.md` (9) | válidos | contratos de gate adicionados |
| `.opencode/commands/*.md` (12 → 14) | válidos | todos com `agent:` existente; `/progress` sem `$ARGUMENTS` (aviso) |
| `.opencode/skills/**` (26) | **válidas** | `validate_skills.py`: 0 erros, 1 aviso (`/progress`) |
| `opencode.jsonc` | mínimo | `default_agent: "orquestrador"` **não verificável** na 1.2.27; não confiar |
| `AGENTS.md` | atualizado | §10 gates/HALT |
| `AUTOPILOT.md` | atualizado | §0 HALT, §13 gate |
| `CMakePresets.json` | frágil | caminho absoluto do winget com hash de pacote |
| `scripts/check_version.py` | corrigido | `UnicodeEncodeError` no console cp1252 |
| `scripts/gate.py` | **novo** | trava mecânica |

> **`default_agent`:** não foi possível comprovar suporte na 1.2.27. A trava **não depende
> dele**: comandos como `/auto` fixam `agent: orquestrador` no frontmatter. Recomendação:
> operar por comando, não por agente padrão.

---

## 5. Problemas encontrados (com prova)

| ID | Problema | Prova |
|---|---|---|
| P1 | Manifest usa hash do binário **v25** como se fosse v24 | F-002 `FFA8809D…` = DocumentMarks v250; real v240 = `E47328BD…` |
| P2 | F-001 **não tem pasta de evidência** | `rag/evidence/F-001` não existe; spec cita 14 arquivos |
| P3 | Evidência F-004 é de **outro módulo** | pasta só tem `ColorManipulationLayer__*` |
| P4 | Evidência F-003 **corrompida** e export abortado | `versao: 24.03.10017.100173.10017`; log "program file(s) not found" |
| P5 | F-005/F-006 com **placeholders** `0x...` | manifest `estatico` |
| P6 | F-002 é **demo sem UI**, teste não compila | `markset_processor.cpp` imprime DEBUG e devolve IDs fixos; `main_window.cpp` sem ação Mark Sets |
| P7 | F-007 **"Not implemented"** e BLO-003 **ausente** | `step_repeat.cpp:46,53,60`; `BLOQUEIOS.md` sem BLO-003 |
| P8 | F-008 **esqueleto de TODO**, sem manifest, ADR `proposto` | ~40 `TODO(F-008)`; `rag/evidence/F-008` sem manifest |
| P9 | **Build global quebrado** | `src/automation/scripting.cpp:2: QJSEngine: No such file` |
| P10 | Testes falhando | BearerBar 10/11; PdfRoundTrip 4 falhas; Editing 1; Integration 1 |
| P11 | Registros contraditórios | F-006: INVENTORY "implementado", STATUS "REPROVADO/BLOQUEADO", MATRIX "Auditado com Ressalvas" |
| P12 | Laudos **stale** e ressalvas indevidas | F-001, F-002, F-004, F-005 mais antigos que código/evidência |
| P13 | Orquestrador **sem ferramenta de verificação** | bash restrito a `git` |
| P14 | `default_agent` não comprovado | ausência do token no pacote 1.2.27 |

---

## 6. Correções realizadas

| Arquivo | Mudança |
|---|---|
| `scripts/gate.py` | **novo**: 7 gates factuais (versão, evidência, spec, ADR, código, teste, auditoria) + GATE 7 inventário |
| `scripts/check_version.py` | corrigido crash `UnicodeEncodeError` (stdout utf-8) |
| `AGENTS.md` | §10 Gates/HALT/estado comprovado |
| `docs/agents/AUTOPILOT.md` | §0 HALT; §13 gate prevalece |
| `docs/agents/HALT.md` | **novo**: suspensão obrigatória |
| `docs/agents/BLOQUEIOS.md` | cabeçalho; **BLO-003** restaurado; BLO-005 corrigido; **BLO-006** (build global) |
| `docs/agents/CHECKPOINT.md` | estado real + harness de build |
| `docs/phases/STATUS.md` | estado comprovado |
| `docs/reverse-engineering/INVENTORY.md` | reescrito com estado derivado |
| `FEATURE_MATRIX.csv` | reescrito com estado derivado |
| `.opencode/agents/orquestrador.md` | Gate zero; permissões de verificação; proibição de elevar estado |
| `.opencode/agents/{ghidra,rea,comportamento,documentacao,arquitetura,implementacao,testes,auditor}.md` | contrato de gate; regras de evidência; bash de gate p/ doc/arq |
| `.opencode/commands/auto.md` | Passo 0 (HALT/gate) + gate por seta |
| `.opencode/commands/gate.md`, `halt.md` | **novos** |
| `rag/evidence/F-00{3,4,5,6}/manifest.json` | `versao_ref`/`binario` corrigidos para v240 |
| `rag/ghidra/exports/LayoutEngine.dll/decompiled/*.md` | campo `versao` abreviado (não `24.03.10017`) → `24.03.10017` (10 arquivos) |
| `docs/architecture/F-008-ADR.md` | removida referência residual à v25 |

> Nenhum arquivo em `src/**`, `tests/**`, `docs/features/**` ou `docs/decisions/**` foi
> alterado — o HALT foi respeitado. Trabalho de outras sessões foi preservado (sem reset/clean).

---

## 7. Validação: build e testes reais

Build em `build_audit` (separado de `build/`), log em `%TEMP%\opencode\build_audit.log`.

### Build

| Alvo | Resultado |
|---|---|
| `ArtPlus` | **FALHOU** — `src/automation/scripting.cpp:2:10: fatal error: QJSEngine: No such file or directory` |
| `unit_tests` | **FALHOU** — mesma causa |
| `test_markset_processor` | **FALHOU** — `test_markset_processor.cpp` usa API inexistente |
| `pdf_smoke`, `form_xobject_test`, `form_parser_probe`, `form_transform_probe`, `smask_probe`, `mirror_probe`, `page_placeholders` | construídos |
| `bearer_bar_test`, `test_cut_mark`, `test_selection_mark`, `test_save_document` | construídos |
| `pdf_roundtrip_test`, `editing_test`, `integration_test_basic` | construídos |

### Testes (ctest + execução direta)

| Teste | Resultado | Detalhe |
|---|---|---|
| CutMarkTests (F-001) | **PASS** | 12/12 |
| SelectionMarkTests (F-004) | **PASS** | `resizeSelection` é PLACEHOLDER |
| SaveDocumentTests (F-006) | **PASS** | 91 asserções; criptografia `TODO` |
| BearerBarTests (F-003) | **FAIL** | 10/11 — topologia R4/R6: 5 elementos vs 4 |
| PdfRoundTrip | **FAIL** | 4 falhas — import gera 2 páginas onde espera 1 |
| EditingTests | **FAIL** | objeto deletado ainda exportado: 10 vs 5 |
| IntegrationTestBasic | **FAIL** | roundtrip de imagem |
| MarkSetProcessor | **NOT RUN** | não compila |
| UnitTests | **NOT RUN** | não linka |

---

## 8. Teste do próprio sistema (cenários)

Harness em repositório temporário, copiando o `gate.py` real e variando um fato por cenário.

| # | Cenário | Esperado | Resultado |
|---|---|---|---|
| 1 | Tudo aprovado | gate verde | **PASS** (`auditado`, exit 0) |
| 2 | Teste ausente/reprovado | bloquear | **PASS** (GATE 5) |
| 3 | Auditoria reprovada | bloquear | **PASS** (GATE 6) |
| 4 | Dependência pendente / HALT | bloquear | **PASS** (exit 2) |
| 5 | Bloqueio de licença (`CAP-BLOCKED`) | bloquear | **PASS** (GATE 3) |
| 6 | Documentação incompleta | bloquear | **PASS** (GATE 2) |
| 7 | Duas sessões no mesmo arquivo | preservar | **manual** — `git status` preservado; proibido reset/clean; não é detectável pelo gate |
| 8 | Agente adianta estado no inventário | bloquear | **PASS** (GATE 7: declara `auditado`, prova `implementado`) |
| 9 | Declara conclusão sem evidência | bloquear | **PASS** (GATE 3) |
| 10 | Hash/versão divergentes | bloquear | **PASS** (GATE 3) |
| 10b | Ferramenta ausente / sem shell | não declarar sucesso | **regra** — se o gate não roda, o agente deve delegar ao `testes` e não pode declarar conclusão |

---

## 9. Estado real F-001 … F-008 (comprovado)

| Feature | Comprovado | O que existe de fato | O que falta |
|---|---|---|---|
| F-001 Cut Mark | `triado` | `src/prepress/cut_mark.*`; CutMarkTests 12/12 | **evidência bruta inexistente** (`rag/evidence/F-001`); spec cita 6 GHIDRA sem arquivo; laudo stale |
| F-002 Mark Set | `triado` | `markset_processor.*` (demo) | evidência inválida; sem UI; teste não compila; spec cita F-001 |
| F-003 Bearer Bar | `triado` | `bearer_bar.*`; 19 Ghidra corrompidos; 1 teste falha | reexport limpo + corrigir geometria + reauditar |
| F-004 Selection Mark | `triado` | `selection_mark.*`; testes passam | evidência é de outro módulo; CAPs bloqueados; resize PLACEHOLDER |
| F-005 Open Document | `triado` | `document_model/serializer`, pdf import/export, UI abrir | evidência placeholder; sem teste F-005; import erra páginas |
| F-006 Save Document | `bloqueado` | `document_save_manager.*`; 91 asserções passam | build quebrado; criptografia TODO; laudo reprovado |
| F-007 Step & Repeat | `bloqueado` | `step_repeat.*` retorna "Not implemented" | CAP, spec, ADR, teste; registrar BLO-003 |
| F-008 Color Management | `bloqueado` | `color_manipulation_layer.*` com ~40 TODO | manifest, CAP, implementação real, teste |

---

## 10. Riscos restantes

1. **HALT é cooperativo**: sessões já abertas podem continuar escrevendo. É preciso
   interrompê-las no cliente.
2. **Build oficial (`build/`) não foi tocado**: o estado medido é de `build_audit`; o
   `build/` de outras sessões pode divergir.
3. **Evidência F-003**: conteúdo pode ser aproveitável, mas o cabeçalho é inválido e a
   procedência não é comprovada — tratar como inexistente até reexportar.
4. **Laudos antigos** continuam no repositório; o gate os marca como stale, mas não os apaga.
5. **`CMakePresets.json`** com caminho absoluto do winget quebra em atualização de pacote.
6. **`default_agent`** não comprovado; enforcement depende de comando explícito.
7. **`maxSteps`** de subagentes (32/40) pode ser insuficiente para build+ctest completos.

---

## 11. Pendências que impedem a retomada

1. Corrigir BLO-006 (build global: `QJSEngine`) e `test_markset_processor`.
2. Reevidenciar F-001 (criar manifest + evidência), F-002/F-004 (módulo/hash corretos),
   F-003 (reexport limpo), F-005 (endereços reais).
3. Corrigir a geometria do Bearer Bar (R4/R6) e revalidar.
4. Corrigir import de páginas (PdfRoundTrip) e export de objeto deletado (Editing).
5. Decidir escopo de F-006 (criptografia) e de F-008 (implementação real).
6. Obter CAP real de F-007/F-008 ou manter bloqueado.
7. `python scripts/gate.py --all` sem falha de GATE 0 e sem estado declarado acima do
   comprovado.

---

## 12. Critérios objetivos para liberação (retomada)

O proprietário remove `docs/agents/HALT.md` **somente** quando:

1. `python scripts/gate.py --all` → GATE 0 `ok` e nenhum `GATE 7` reprovado.
2. `python scripts/gate.py --inventory` → 8/8 estados declarados iguais aos comprovados.
3. Build limpo de `ArtPlus` e `unit_tests` com saída colada.
4. `ctest` com resultado por teste anexado; falhas conhecidas explicitamente aceitas.
5. Toda feature `triado`+ tem manifest com hash real, IDs resolvidos e sem placeholder.
6. Nenhum laudo `stale`; nenhum `CAP-BLOCKED` contando como evidência.
7. Este relatório aprovado pelo proprietário, com autorização explícita registrada.

---

## 13. Relação de arquivos criados e modificados

**Criados:** `scripts/gate.py`; `docs/agents/HALT.md`; `.opencode/commands/gate.md`;
`.opencode/commands/halt.md`; este relatório.

**Modificados:** `AGENTS.md`; `docs/agents/AUTOPILOT.md`;
`docs/agents/BLOQUEIOS.md`; `docs/agents/CHECKPOINT.md`; `docs/phases/STATUS.md`;
`docs/reverse-engineering/INVENTORY.md`; `FEATURE_MATRIX.csv`;
`.opencode/agents/orquestrador.md`; `.opencode/agents/ghidra.md`;
`.opencode/agents/rea.md`; `.opencode/agents/comportamento.md`;
`.opencode/agents/documentacao.md`; `.opencode/agents/arquitetura.md`;
`.opencode/agents/implementacao.md`; `.opencode/agents/testes.md`;
`.opencode/agents/auditor.md`; `.opencode/commands/auto.md`;
`scripts/check_version.py`; `rag/evidence/F-003/manifest.json`;
`rag/evidence/F-004/manifest.json`; `rag/evidence/F-005/manifest.json`;
`rag/evidence/F-006/manifest.json`; `rag/ghidra/exports/LayoutEngine.dll/decompiled/*.md`
(10 arquivos); `docs/architecture/F-008-ADR.md`.

**Não alterados por esta auditoria:** `src/**`, `tests/**`, `docs/features/**`,
`docs/decisions/**` e evidência bruta (exceto correção de metadados de manifest).

---

**Veredito do relatório:** sistema de agentes **reprovado no estado anterior**, **corrigido
com trava mecânica**, **HALT ativo**. A retomada de F-XXX depende de autorização explícita
do proprietário após as pendências da §11.
