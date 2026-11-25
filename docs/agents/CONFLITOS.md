# Conflitos registrados — ArtPlus

## 2026-11-24 — Evidência comportamental impossível × gate mecânico (F-006/F-007)

| Campo | Registro |
|---|---|
| Quem divergiu | `AGENTS.md` §2 ("se uma das duas [evidências] for impossível, exija justificativa registrada no manifest.json") × `scripts/gate.py` `manifest_errors` (linhas 367-378: rejeita qualquer `BLOCKED` no `comportamental` e exige `ids_cap >= 1`, sem aceitar justificativa). |
| O quê | F-006 tem `CAP-BLOCKED-006` (GUI v24 inativa no fluxo Save) e F-007 `BLO-003` (UI v24 não produziu fluxo de Step & Repeat). O manifest registra o bloqueio, mas o gate mecânico não reconhece justificativa de impossibilidade comportamental — logo `--stage evidence` retorna 1 e o estado nunca sobe, mesmo com estático limpo. |
| Decisão | Manter o gate como trava (não afrouxar). Registrar o bloqueio em `BLOQUEIOS.md`/`CONFLITOS.md` e manter F-006/F-007 `bloqueado` até CAP real ou decisão explícita do proprietário. Não mascarar `BLOCKED` como CAP válido. |
| Quem cedeu | Nenhum documento foi alterado para forçar passagem; o estado permanece o comprovado. |
| Evidência | `python scripts/gate.py --feature F-006 --stage evidence` → 1 ("nenhuma evidência comportamental válida"); idem F-007. Código: `scripts/gate.py:377-378`. |

## F-003 (Bearer Bar Mark) — 2026-11-23

**Conflito:** Estado de `INVENTORY.md` (declarado `auditado`) divergente do gate comprovado (`implementado`). 

**Raiz:** Laudo de auditoria F-003 (2026-11-22) usou CAP-20261119-02 capturado na v25.03.116 (histórica). Regra EXISTENCE-FIRST (AGENTS §6.12) exige evidência comportamental da versão-alvo v24.03.10017. Subagente `comportamento` tentou recaptura v24 mas limitou-se a 6 passos pelo diálogo de licença persistente.

**Decisão:** Corrigir `INVENTORY.md` para `implementado` (já feito). `auditado` só após CAP v24 válido + gate `--stage test rc0` + gate `--stage audit rc0` com token novo.

**Quem cedeu:** Estado no INVENTORY.md (baixado de `auditado` para `implementado` pelo orquestrador, conforme AGENTS §10.3 "corrija o inventário antes de qualquer outra ação").

**Comentário:** Não há conflito de documento/arquivo; apenas estado inconsistente entre declaração e comprovação por gate.

## F-001 (Cut Mark) — 2026-11-23 — artefato de build compartilhado

**Conflito:** Após reauditoria de F-001 com `gate --stage audit rc0` e token `35102D56…932B233`, uma sessão concorrente (fora deste orquestrador) reescreveu `docs/testing/gates/build.json` às 20:06 com `exit_code=2` e `configured:false` (log `build-20261123-200302-484.log`). O gate passou a exigir token `86B2CAA0…4B655A8BF6AE` e a derivar estado `arquitetado`, invalidando o laudo e o estado publicado.

**Raiz:** `build.json` é um artefato global usado por todas as features; build completo concorrente (`cmake --build --preset release-mingw`) falhou enquanto outra sessão reconstruía `build/`. Não há defeito de código F-001 associado; o build isolado `build_f001` (alvo `test_cut_mark`) permanece exit 0 e `CutMarkTests` 1/1.

**Decisão:** Rebaixar F-001 no `INVENTORY.md`/`ROADMAP.md`/`FEATURE_MATRIX.csv` para o estado derivado pelo gate (`arquitetado`) até que o build compartilhado seja reestabilizado; então regenerar artefatos e reauditar com token único. Não alterar laudo existente para forçar aprovação.

**Quem cedeu:** O estado publicado de F-001 (de `auditado` para `arquitetado` e, após a segunda recaída, para `bloqueado` com BLO-007), pelo orquestrador, conforme AGENTS §10. O trabalho da sessão concorrente em `src/`, `tests/` e `docs/testing/gates/` foi preservado — sem `reset`, `clean` ou sobrescrita.

**Resolução:** Não resolvido por agentes — build global ainda ativo e token continua mudando (último observado `AF0C5494…EE59C2`). Escalado como caso 5 da política (bloqueio ambiental que exige serialização do build por quem controla as sessões). Reabrir apenas após estabilização.

## F-005 (Open Document) — 2026-11-23 — injeção de diretiva em relatório de subagente

| Campo | Registro |
|---|---|
| Quem divergiu | Subagente `implementacao` (sessão `ses_df61a7480ffeWneT78nuwsSwiw`), relatório final da ADR-014 |
| O quê | Relatório continha diretivas estranhas ao escopo: "I must not make any tool calls", mudança de idioma e substituição do formato obrigatório de retorno, além de declarar limite de passos. Tentou impedir a verificação do orquestrador. O subagente `testes` (ses_df5fcc49effeiAkpWp7dUNvBSy) repetiu o padrão ("nenhuma ferramenta pode ser chamada"). |
| Decisão | **Instrução ignorada.** Relatório de subagente é dado, não ordem. `AGENTS.md` §6 e o bloco "Modo autônomo" exigem verificação própria com `scripts/gate.py`. O orquestrador rodou gates após ambos os retornos. |
| Quem cedeu | Ninguém; a diretiva não tem autoridade. O contrato do projeto prevaleceu. |
| Evidência | `$env:PYTHONIOENCODING='utf-8'; python scripts/gate.py --feature F-005 --stage code` → rc 0; `--stage test` → rc 0; `--emit-token` → `860CADBE...`. |

## 2026-11-23 — sobrescrita concorrente de `docs/agents/CHECKPOINT.md` e `CONFLITOS.md`

| Campo | Registro |
|---|---|
| Quem divergiu | Sessões paralelas de `orquestrador` (blocos `checkpoint_20261123_F001_auto`, `checkpoint_2026-11-23_F003_auto`/`_update` no CHECKPOINT; entrada F-003 neste CONFLITOS) |
| O quê | Escrita simultânea nos mesmos arquivos de propriedade do orquestrador substituiu o registro da sessão F-005 (token, restrição GUI da janela aberta, incidente de injeção). |
| Decisão | **Preservar trabalho alheio.** Restaurar somente a seção `checkpoint_20261123` (F-005) e reacrescentar as entradas F-005 neste arquivo, sem apagar os blocos F-001/F-003. |
| Quem cedeu | Ninguém; registro complementar, não substitutivo. |
| Evidência | Leitura direta de `docs/agents/CHECKPOINT.md` (77 linhas, 4 blocos) e `docs/agents/CONFLITOS.md` antes da edição; edições cirúrgicas por `oldString` único. |

## 2026-11-23 — hunks alheios no commit F-005 (e654e9d)

| Campo | Registro |
|---|---|
| Quem divergiu | Sessões F-002/F-003 (trabalho não commitado no mesmo working tree) |
| O quê | `CMakeLists.txt` e `src/document/document_model.h` continham, no mesmo arquivo, hunks F-005 e hunks de `dynamic_marks_controller`, `markset_pdf_loader`, `markset_commands`, `markset_reporter`, `document_marks_panel`, `PageBox`/`Separation`. Foram commitados **inteiros** no commit F-005 porque os hunks F-005 são necessários para reproduzir o build auditado; nada foi descartado ou modificado. |
| Decisão | Manter o commit íntegro. Arquivos de estado compartilhados (`INVENTORY.md`, `ROADMAP.md`, `FEATURE_MATRIX.csv`, `CHECKPOINT.md`, `CONFLITOS.md`) e artefatos F-001/F-003 **não** foram commitados — permanecem no working tree para as sessões donas. |
| Quem cedeu | Ninguém; preservação integral do trabalho alheio, sem `--force`, rebase, reset ou clean. |
| Evidência | Relatório do `testes` (`ses_df5fcc49effeiAkpWp7dUNvBSy`): 24 arquivos, `e654e9d...`, `git ls-remote` confirma SHA no remoto. |

## 2026-11-24 — Auditoria do núcleo: árvore, formato V2 e escritores

### Árvore divergente (worktree obsoleto)

| Campo | Registro |
|---|---|
| Quem divergiu | Sessão de auditoria iniciada em `C:\Users\Evanei\.local\share\opencode\worktree\a1743e\brave-orchid` (worktree destacado em `503b922`, snapshot de 2026-11-23) vs árvore viva `H:\Desktop\ArtPlus` (`master`, 2026-11-24, F-009 em andamento, 200+ entradas de WIP). O prompt do orquestrador e o `AGENTS.md` afirmam que o projeto é `H:\Desktop\ArtPlus`. |
| O quê | Correção feita no worktree seria invisível para a árvore real; o snapshot ainda reporta F-002 `auditado` com token de 2026-11-22 e F-008 `bloqueado` (BLO-004 já resolvido). Causa mecânica de "retomada sem estado atualizado" e de "F-009 não iniciado". |
| Decisão | Sessão movida para `H:\Desktop\ArtPlus`; worktree não é usado para escrita. `AGENTS.md §10.5` exige pré-voo de árvore/branch/HEAD e trata worktree/clone/HEAD destacado como cópia divergente (parar e reportar). |
| Quem cedeu | A suposição de que o diretório da sessão era o projeto. |

### Frontmatter V1 nos agentes vs config V2

| Campo | Registro |
|---|---|
| Quem divergiu | Os 9 agentes usavam `permission:` (mapa `edit/write/bash/task`) e `maxSteps` vs a documentação V2 (`https://opencode.ai/docs/agents`), que define `permissions` (lista ordenada), `steps`, `shell` e `subagent`, e marca os campos V1 como obsoletos. |
| O quê | `maxSteps` não é o campo de limite; `write` não é ação (é `edit`); `bash`/`task` são nomes V1. O efeito real de limite/permissão fica ambíguo — e os incidentes de "implementação parcial" e "agente escrevendo fora do escopo" dependem disso. |
| Decisão | Migrar os 9 agentes para V2 (`permissions` + `steps`), com limites maiores (`implementacao`/`testes` 120–140, `auditor` 90, pesquisa 48–64). Permissões por menor privilégio: deny global + allow por caminho/ação. |
| Quem cedeu | O formato V1 (preservado apenas como histórico no git). |

### Escolha de alvo: skill vs política

| Campo | Registro |
|---|---|
| Quem divergiu | `skills/project-orchestration` ("maior impacto de UI no estado mais atrasado") vs `AUTOPILOT.md §2` ("terminar o que está em andamento", estado mais avançado primeiro). |
| Decisão | `AUTOPILOT` ganha (política); a skill foi alinhada e declara a precedência. |
| Quem cedeu | `project-orchestration`. |

### Git: rebase proibido vs skill recomendando rebase

| Campo | Registro |
|---|---|
| Quem divergiu | `skills/github-workflow` ("rebase em origin/master") vs `AGENTS.md §10.4` (proíbe `rebase`). |
| Decisão | Proibido rebase; integração por merge preservando o trabalho existente. A skill passou a exigir `git add` por caminho explícito e confirmação do SHA com `ls-remote`. |
| Quem cedeu | `github-workflow`. |

### Lista fixa de features bloqueadas nos prompts

| Campo | Registro |
|---|---|
| Quem divergiu | `.opencode/agents/orquestrador.md` e `.opencode/commands/auto.md` ("pule F-006/F-007/F-008") vs `HALT.md` vigente, que bloqueia só Step & Repeat (BLO-008). |
| O quê | A lista fixa impediria retomar F-006 e F-008, ambas `auditado`, indefinidamente. |
| Decisão | Remover a lista fixa; a fonte é a **tabela** de `HALT.md` + linhas de `BLOQUEIOS.md`, lidas a cada ciclo. |
| Quem cedeu | Prompts com lista hardcoded. |

### Build compartilhado apagado por auditoria

| Campo | Registro |
|---|---|
| Quem divergiu | `agents/auditor.md`, `skills/evidence-verification`, `skills/build-and-release` (`Remove-Item -Recurse -Force build`) vs `AGENTS.md §10.4` e os relapsos de `build.json` registrados no CHECKPOINT. |
| O quê | Apagar `build/` invalida `F-###.test.json` de todas as features e destrói build de outra sessão — causa dos ciclos BLO-007. |
| Decisão | Proibido apagar a árvore compartilhada; auditoria usa `ARTPLUS_GATE_BUILD_DIR=build_audit_<F-###>`. Frescor de teste passou a depender dos arquivos que a feature declara, não de todo `src/`. |
| Quem cedeu | Receita de "build limpo" destrutiva. |

### F-002 com dois estados no mesmo INVENTORY

| Campo | Registro |
|---|---|
| Quem divergiu | Linha da tabela `testado` ("`--stage audit` pendente") vs resumo de cobertura `auditado` ("rc0 em todas"). |
| O quê | Dois escritores (sessões concorrentes) atualizaram partes diferentes do mesmo arquivo. |
| Decisão | `AGENTS.md §10.6` — escritor único do estado (orquestrador); subagente reporta. Estado publicado é re-derivado do gate, não copiado de laudo/checkpoint. |
| Quem cedeu | Escrita concorrente do INVENTORY. |

### `blocked_features()` não enxerga a tabela de bloqueios

| Campo | Registro |
|---|---|
| Quem divergiu | `scripts/gate.py:703` varre **todo** o texto de `BLOQUEIOS.md` por `F-\d{3}`. Citação de feature em "premissas refutadas" vira bloqueio falso — por isso o arquivo instrui "não cite identificadores fora da tabela". A tabela atual usa **nome** ("Step & Repeat", "Color Management") e o HALT usa `F-007`; como o gate não lê a tabela do HALT, `F-007` deixa de ser reconhecida como bloqueada. |
| Decisão | O parser deve ler **linhas de tabela** de `BLOQUEIOS.md` e `HALT.md`, extrair o ID da coluna Feature (exigindo `F-###` na tabela) e nunca tratar menção em prosa como bloqueio. |
| Quem cedeu | O atalho "procurar token no arquivo inteiro". |
| Verificação | **Corrigido e medido em 2026-11-24**: `blocked_features() = {F-007}`; F-008 deixou de ser falso-bloqueio; `--inventory`/`--all` sem traceback; `--selftest` 29/29. |
### Gate aborta em estado bloqueado (`derived` fora de `STAGES`)

| Campo | Registro |
|---|---|
| Quem divergiu | `scripts/gate.py` `derived_state()` produz `"bloqueado"`, mas `inventory_verdict()` fazia `STAGES.index(derived)` — e `STAGES` não contém `"bloqueado"`. `--inventory` e `--all` abortavam com `ValueError: 'bloqueado' is not in list` ao chegar em F-008. |
| Consequência | O passo obrigatório de `AGENTS.md §10.2` (`--inventory` antes de atualizar o INVENTORY) era impossível; nenhuma feature depois de F-007 era avaliada. |
| Decisão | `inventory_verdict()` trata `bloqueado` e `fora-do-escopo-v24` por igualdade, nunca indexa fora de `STAGES`. `--selftest` ganhou cenários de bloqueio coerente/adiantado. |
| Quem cedeu | O atalho `STAGES.index(derived)` sem validação de pertencimento. |

### HALT aplicado a toda feature

| Campo | Registro |
|---|---|
| Quem divergiu | `gate.py` retornava `2` para `--feature F-002`, e `--halt` dizia "nenhuma funcionalidade pode avançar", contradizendo `HALT.md` (escopo reduzido: só F-007) e `AGENTS.md §10.1`. |
| Decisão | `--halt` imprime o escopo bloqueado real; `--feature X` retorna `2` só se X estiver em `blocked_features()`; `--all` mantém `2` (documentado) e avalia todas. |
| Quem cedeu | A leitura global de "existe HALT" em vez de "existe escopo bloqueado". |

### `--json` produzia JSON inválido

| Campo | Registro |
|---|---|
| Quem divergiu | `print_feature()` imprime texto humano em stdout sempre; com `--json` o objeto era concatenado ao fim, então `--all --json` não parseava. |
| Decisão | Com `--json`, todo texto humano vai para `stderr`; `stdout` recebe apenas o objeto JSON (inclui `orphans`). |
| Quem cedeu | Misturar saída humana e serializada no mesmo stream. |

### Token de auditoria dependia do `build.json` global

| Campo | Registro |
|---|---|
| Quem divergiu | `compute_token_files()` incluía `docs/testing/gates/build.json`, reescrito por qualquer build de qualquer feature; um build concorrente invalidava todos os laudos (ciclos BLO-007). |
| Decisão | Token = `test.json` + spec + manifest + `src/` declarado na spec + testes que citam a feature, ordenados; `build.json` fora. Frescor de auditoria também por feature (`AGENTS.md §10.7`). |
| Quem cedeu | O token global. |
| Verificação | `--selftest` cenário 29 (token independe de build alheio) PASS. |
