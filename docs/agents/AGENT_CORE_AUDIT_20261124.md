# AGENT CORE AUDIT — 2026-11-24

Auditoria corretiva do ambiente de agentes do ArtPlus (agentes, skills, hooks, commands,
permissões, MCPs, gates, estado e retomada). Não inclui a infraestrutura da parte visual
(ArtPlus-UI), que permanece intocada.

- **Árvore canônica:** `H:\Desktop\ArtPlus` (branch `master`)
- **Versão de referência:** Esko ArtPro+ **v24.03.10017**
- **Supervisor:** `orquestrador`
- **Método:** leitura de configuração + documentação oficial V2 do OpenCode + execução real de
  `gate.py`/`check_version.py`/`validate_skills.py` em sessão `testes` (o orquestrador não executa
  build). Nenhuma etapa foi declarada concluída por relatório.

---

## 0. Sumário executivo

Sete falhas explicam os onze incidentes relatados:

1. **A sessão rodava num worktree git destacado e obsoleto** (`503b922`, snapshot de 2026-11-23),
   enquanto a árvore viva estava em 2026-11-24 com F-009 em andamento. Toda leitura de estado vinha
   de um retrato de um dia antes.
2. **Os 9 agentes usavam frontmatter V1** (`permission`/`maxSteps`), obsoleto na configuração V2
   (`permissions`/`steps`/`shell`/`subagent`). O limite de passos e o escopo de escrita não eram os
   que o prompt dizia.
3. **Dois escritores no mesmo arquivo de estado**: INVENTORY/STATUS/matriz foram editados por
   sessões concorrentes, produzindo F-002 `testado` na linha e `auditado` no resumo.
4. **`build/` e `build.json` compartilhados** e apagados por auditoria, invalidando laudos de outras
   features (ciclos BLO-007) — o token de auditoria inclui `build.json`, que qualquer sessão reescreve.
5. **Lista fixa de bloqueios nos prompts** ("pule F-006/F-007/F-008") divergente do `HALT.md`, que
   bloqueia só Step & Repeat.
6. **`gate.py` não enxerga a tabela de bloqueios**: varre qualquer `F-###` no texto de
   `BLOQUEIOS.md`, mas a tabela usa nomes — então `F-007` deixa de ser reconhecida como bloqueada.
7. **Nenhum hook existe** (projeto e global): não há enforcement automático de limite de subagentes,
   build pós-edição ou proteção de artefato. A correção foi feita no que é verificável — permissões,
   scripts, gate e contrato — em vez de instalar plugin não testado.
8. **O próprio `gate.py` estava quebrado no estado atual** (medido, não inferido): abortava
   `--inventory`/`--all` com `ValueError: 'bloqueado' is not in list`; marcava F-008 como bloqueada
   por causa de um caminho citado em `BLOQUEIOS.md`; media frescor de auditoria contra todo `src/`;
   e o token incluía o `build.json` global. Consequência: nenhuma feature podia chegar a `auditado`,
   e o passo obrigatório de `AGENTS.md §10.2` era impossível. Os 5 defeitos foram corrigidos,
   com 12 cenários novos de regressão no `--selftest` (29 → 33).

Correções aplicadas nesta sessão: 9 agentes, 10 skills, 14 commands, `AGENTS.md`, `AUTOPILOT.md`,
`CONFLITOS.md`, `BLOQUEIOS.md`, os registros de estado (`INVENTORY`/`ROADMAP`/`MATRIX`/`STATUS`)
re-derivados do gate, e `scripts/gate.py` + `scripts/preflight.py` + `.gitignore` + `GATE.md`
(executados pelo `testes`, dono de `scripts/**`). Nenhum hook foi instalado. Estado de feature
**não foi elevado**; os laudos existentes foram rebaixados ao que o gate prova (`testado`/
`implementado`) até reauditoria.

---

## 1. Inventário (o que existe de fato)

### 1.1 Agentes (`.opencode/agents/`, 9)

| Agente | Modo | `steps` antes → depois | Escreve em | Lacuna corrigida |
|---|---|---|---|---|
| `orquestrador` | primary | 200 (`maxSteps`) → 240 | estado, docs/agents, `.opencode/**`, AGENTS.md, opencode.jsonc | lista fixa de bloqueios; shell/git descrito como indisponível; sem pré-voo; sem escritor único |
| `rea` | subagent | 32 → 48 | rag/evidence, rag/sources, docs/reverse-engineering | não separava fato/hipótese/desconhecido |
| `ghidra` | subagent | 40 → 64 | tools/ghidra_*, docs/RE, rag/evidence | ok; limite ajustado |
| `comportamento` | subagent | 32 → 60 | tools/reference_capture, docs/behavior, rag/evidence | limite de passos tratado como captura concluída |
| `documentacao` | subagent | 32 → 60 | docs/features, docs/glossary, rag/index, rag/metadata | `status` nunca avançava com o gate |
| `arquitetura` | subagent | 32 → 48 | docs/architecture, docs/decisions | ok |
| `implementacao` | subagent | 40 → 120 | src/**, CMakeLists.txt, tools/pdf_inspector | parava no primeiro erro; sem checagem de dependência; sem diff; sem handoff |
| `testes` | subagent | 40 → 140 | tests/**, docs/testing/**, scripts/**, .gitignore, dossiers/**, CMakePresets | apagava `build/` compartilhado; sem artefato de gate; commit em bloco |
| `auditor` | subagent | 32 → 90 | docs/audit/** | apagava `build/`; token copiado em vez de medido |

Permissões: todas migradas de mapa V1 (`edit/write/bash/task`) para lista V2
(`edit`/`shell`/`subagent`/`external_directory`), deny global + allow por caminho, mantendo o menor
privilégio (ex.: `documentacao` e `arquitetura` só executam `gate.py`/`check_version.py`).

### 1.2 Skills (`.opencode/skills/`, 26)

Pipeline: `project-orchestration`, `technical-specification`, `cpp-architecture-adr`,
`evidence-verification`, `test-strategy`, `build-and-release`, `github-workflow`,
`ghidra-analysis`, `rea-reverse-engineering`, `artpro-behavior-capture`, `powershell-win-toolkit`.
Domínio: 15 (`document-core`, `pdf-engineering`, `color-management`, `marks-and-barcodes`,
`prepress-trapping`, `layers-and-separations`, `step-and-repeat`, `screening-and-halftone`,
`selection-and-transform`, `vector-geometry`, `preflight-quality-control`,
`action-lists-automation`, `dependency-license-audit`, `qt-cpp-development`,
`visual-regression-testing`).

Corrigidas: `project-orchestration` (+referência `gates-and-states`), `evidence-verification`,
`test-strategy`, `build-and-release`, `github-workflow`, `technical-specification`,
`qt-cpp-development`, `rea-reverse-engineering`, `artpro-behavior-capture`.
Sem alteração (sem defeito comprovado): as 15 de domínio + `ghidra-analysis` + `powershell-win-toolkit`.

### 1.3 Hooks

**Zero hooks/plugins.** Verificado em `H:\Desktop\ArtPlus\.opencode` (nenhum `plugin/`, nenhum
`*.ts/*.js/*.mjs`), em `C:\Users\Evanei\.config\opencode` (nenhum `plugin/`; `opencode.jsonc` só tem
`mcp`) e em `%ProgramData%\opencode` (não existe).

Consequência: nada executava build/teste automaticamente, nada bloqueava escrita fora do escopo e
nada protegia artefato compartilhado. Instalar plugin sem poder testá-lo nesta sessão seria trocar
um risco conhecido por um risco desconhecido; a correção foi feita em permissões + scripts + gate.

### 1.4 Commands (`.opencode/commands/`, 14)

`auto`, `cycle`, `gate`, `build`, `test`, `implement`, `audit`, `spec`, `adr`, `capture`, `triage`,
`ghidra`, `progress`, `halt`. Todos revisados; 8 corrigidos (ver §4).

### 1.5 MCPs e ferramentas

| Servidor | Config | Estado |
|---|---|---|
| `pc-control` | global `opencode.jsonc`, `python -m desktop_control.server` | ativo; 12 ferramentas expostas |
| `rea` | global, Node 26 portátil + `rea-side`, provider Ghidra em `H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC` | ativo; 255 ferramentas |

Observação: o config global usa a forma V1 de `mcp` (`mcp.<nome>`), aceita pela compatibilidade V2.
Migrar para `mcp.servers` exige reiniciar/testar os dois servidores e não foi feito nesta sessão —
registrado como risco baixo (depreciação, não falha).

### 1.6 Gates e estado

`scripts/gate.py` (~2.000 linhas após a correção), `check_version.py`, `validate_skills.py`,
`preflight.py` (**criado nesta sessão**), `dossier.py`, `status.py`. Estado em `INVENTORY.md`,
`ROADMAP.md`, `FEATURE_MATRIX.csv`, `docs/phases/STATUS.md`, `docs/agents/CHECKPOINT.md`.

Defeitos do gate corrigidos (com evidência em Anexo A): parser de bloqueios por tabela
(`BLOQUEIOS` + `HALT`); `inventory_verdict` sem crash para `bloqueado`/`fora-do-escopo-v24`;
frescor de auditoria por dependência da feature; token sem `build.json` global; `--json` puro;
HALT por escopo; detecção de feature órfã; `discover_features` cobrindo INVENTORY + specs +
evidência.

---

## 2. Incidentes: sintoma → evidência → causa → correção

| # | Incidente | Evidência | Causa | Correção |
|---|---|---|---|---|
| 1 | CMake removido sem eliminar referências | `REPOSITORY_RECONCILIATION.md` e falhas de link por unidade ausente | agente removeu entrada sem procurar dependentes | `implementacao` e `qt-cpp-development` passam a exigir busca de referências antes de remover |
| 2 | Implementação parcial após limite de passos | `maxSteps: 40` + relatórios "limite atingido" no CHECKPOINT | campo V1 (não é `steps`) e instrução não definia handoff | V2 `steps` 120; regra "limite é handoff, não conclusão"; bloco HANDOFF obrigatório |
| 3 | Retomada sem estado atualizado | sessão no worktree `503b922` (2026-11-23) vs `master` (2026-11-24) | diretório da sessão não era o projeto; nenhum pré-voo | `AGENTS.md §10.5` + pré-voo obrigatório no orquestrador e em `auto.md` |
| 4 | Build aprovado sem comprovação comportamental | laudos com build/ctest mas sem CAP em versões antigas | gate de auditoria aceitava laudo sem comportamento | auditoria exige verificação da cadeia spec→evidência→código→teste e CAP/BLOCKED explícito |
| 5 | F-009 "não iniciado" após Gate Code | `F-009` só aparece em CHECKPOINT/`REPOSITORY_RECONCILIATION.md`; não há spec, src, teste nem linha no INVENTORY | ausência de detecção de feature órfã + estado copiado de prosa histórica | `gate.py` detecta órfãs (`F-009 citada em CHECKPOINT.md:4`) sem inventar estado; retomada só por gate/INVENTORY |
| 6 | F-002 divergente no INVENTORY | linha `testado`, resumo `auditado` | dois escritores concorrentes | `AGENTS.md §10.6` escritor único; INVENTORY re-derivado do gate: F-002 `testado` na linha e no resumo |
| 7 | Agentes nos mesmos arquivos | `git status` com 200+ entradas; CONFLITOS 2026-11-23 (hunks alheios no commit F-005) | sem disciplina de WIP nem checagem antes de editar | regra de preservação de WIP em todos os agentes/skills; commit por caminho explícito |
| 8 | Artefatos de gate alterados por vários agentes | `build.json` sobrescrito com `exit_code=2` duas vezes (CHECKPOINT BLO-007) | `build.json` global + token global + auditoria apagando `build/` | token sem `build.json`; frescor por feature; árvore isolada; proibição de apagar `build/` — **medido em Anexo A.10/A.11** |
| 9 | Orquestrador pedindo autorização repetidamente | prompt dizia que shell/git "só em sessão nova" | instrução desatualizada frente à permissão real | prompt e `AGENTS.md` atualizados; allowlist explícita de git/gate; autonomia reafirmada |
| 10 | Agentes interrompendo tarefas autorizadas | `cycle.md` "não avance duas etapas" lido como "pare"; auditoria reprovada sem retorno claro | instrução ambígua | `cycle.md`: um despacho = uma etapa, mas continua até fechar/falhar 2×/bloqueio; retorno com lacuna exata |
| 11 | Skills/hooks contribuindo | skills recomendando `rebase`, apagar `build/`, build em `build/`; nenhum hook | texto desatualizado e ausência de enforcement | 10 skills corrigidas; hook ausente documentado |

---

## 3. Correções estruturais

- **Formato de agente V2** em todos os 9 agentes (`steps` + `permissions`), conforme
  `https://opencode.ai/docs/agents` e `/permissions`.
- **Pré-voo de árvore** e proibição de trabalhar em worktree/clone/HEAD destacado.
- **Escritor único do estado** e proibição de editar artefato de gate à mão.
- **Build/artefato compartilhado**: árvore isolada para auditoria; proibição de apagar `build/`.
- **Continuidade**: handoff obrigatório; retomada por checkpoint + gate, não por memória.
- **Prova de etapa**: gate `0` + artefato; token medido na sessão do laudo.
- **Alvos**: ordem da política (terminar o em andamento) prevalece sobre a skill.
- **Git**: sem rebase/force; `add` por caminho; SHA confirmado por `ls-remote`.

---

## 4. Arquivos alterados nesta sessão

| Arquivo | Mudança |
|---|---|
| `AGENTS.md` | §3 (shell real), §10.5–10.9 (árvore, escritor único, build compartilhado, handoff, prova) |
| `.opencode/agents/orquestrador.md` | V2; pré-voo; bloqueios pela tabela; escritor único; concorrência; handoff |
| `.opencode/agents/{rea,ghidra,comportamento,documentacao,arquitetura,implementacao,testes,auditor}.md` | V2; limites; regras de WIP, build e prova |
| `.opencode/skills/project-orchestration/SKILL.md` + `references/gates-and-states.md` | escolha de alvo; escritor único; estados reais |
| `.opencode/skills/evidence-verification/SKILL.md` | build isolado; token; WIP |
| `.opencode/skills/test-strategy/SKILL.md` | artefato de gate; sem mock do SUT; sem desativar teste |
| `.opencode/skills/build-and-release/SKILL.md` | limpeza não destrutiva; gate |
| `.opencode/skills/github-workflow/SKILL.md` | sem rebase; `add` explícito; SHA; logs de gate |
| `.opencode/skills/technical-specification/SKILL.md` | ciclo de vida do `status` |
| `.opencode/skills/qt-cpp-development/SKILL.md` | dependências, correção total, diff, WIP |
| `.opencode/skills/rea-reverse-engineering/SKILL.md` | fato/hipótese/desconhecido |
| `.opencode/skills/artpro-behavior-capture/SKILL.md` | handoff de captura |
| `.opencode/commands/{auto,cycle,build,test,implement,audit,progress,capture,gate,halt}.md` | pré-voo, gate, isolamento, limites, bloco ALVO/ACEITE/LIMITE |
| `docs/agents/AUTOPILOT.md` | §2 pré-voo; §8 checkpoint mínimo; §13 escritor único/handoff |
| `docs/agents/BLOQUEIOS.md` | coluna `Feature` com `F-007`; nota do parser; BLO-009 marcado como dependência que não bloqueia |
| `docs/agents/CONFLITOS.md` | 12 registros (8 da 1ª rodada + gate/HALT/`--json`/token) |
| `scripts/gate.py` | 9 correções (ver Anexo A); `--selftest` 21 → 33 cenários |
| `scripts/preflight.py` | **novo** — pré-voo de árvore/branch/versão |
| `docs/testing/GATE.md` | comportamento real do gate, token, HALT por escopo, órfãs |
| `docs/reverse-engineering/INVENTORY.md` | estados re-derivados; nota de reauditoria; F-009 órfã |
| `ROADMAP.md`, `FEATURE_MATRIX.csv`, `docs/phases/STATUS.md`, `AGENTS.md §7` | estado re-derivado do gate |

---

## 5. Delegações (dono correto)

| Item | Dono | Estado |
|---|---|---|
| `gate.py`: parser de bloqueios por tabela (BLOQUEIOS + HALT), crash de estado bloqueado, frescor por feature, token sem `build.json`, HALT por escopo, `--json` puro, detecção de órfã, `discover_features` | `testes` | **executado** — `--selftest` 33/33; Anexo A |
| `.gitignore`: exceção para logs de gate | `testes` | **revertido** — 304 untracked/1,4 MB sem corrigir falha real (clone limpo precisa rebuild de qualquer forma) |
| `docs/testing/GATE.md` atualizado ao gate real | `testes` | **executado** |
| `scripts/preflight.py` (novo) | `testes` | **executado** — `PASS (3/3)` |
| `docs/features/F-00x.md`: `status` alinhado ao gate | `documentacao` | **pendente** — fazer junto da reauditoria (muda o hash da spec) |
| INVENTORY/ROADMAP/MATRIZ/STATUS/AGENTS §7 re-derivados | `orquestrador` | **executado** — `--inventory` = 0 |
| Laudos reemitidos sob o token novo | `auditor` | **pendente** — ciclo de feature, fora desta auditoria |

---

## 6. Verificação (reproduzível)

```powershell
$env:PYTHONIOENCODING='utf-8'
git rev-parse --show-toplevel
git rev-parse --abbrev-ref HEAD
python scripts/check_version.py --strict
python scripts/gate.py --inventory
python scripts/gate.py --all
python scripts/gate.py --selftest
python scripts/validate_skills.py
```

Anexo A (abaixo) registra a saída real medida nesta auditoria.

---

## 7. Riscos residuais

- O limite de 3 subagentes continua sem enforcement automático (nenhum hook). Depende da disciplina
  do orquestrador.
- O config global de MCP usa forma V1; funciona por compatibilidade, mas não foi migrado/testado.
- **Reauditoria pendente**: F-001/F-002/F-003/F-005/F-008 estão `testado` e F-006 `implementado`
  porque os laudos têm token da fórmula antiga (e F-003/F-006/F-008 tiveram spec/código/artefato
  editados depois do laudo). O gate prova o que existe; elevar de volta exige `--emit-token` +
  laudo novo do `auditor`, não edição de estado.
- `docs/features/*` continuam com `status: spec` enquanto o estado derivado é `testado`/
  `implementado`; alinhar o `status` é trabalho do `documentacao` e altera o hash das specs
  (portanto o token). Fazer isso junto da reauditoria, não antes.
- `F-009` é órfã: citada em `CHECKPOINT.md`/`REPOSITORY_RECONCILIATION.md`, sem INVENTORY/spec/
  evidência. O gate a reporta; transformá-la em feature exige captura comportamental na v24.
- `validate_skills.py` emite 2 avisos (`/halt` e `/progress` não usam `$ARGUMENTS` — por desenho).
  Não são erros; corrigir o validador seria ruído de baixo valor.

---

## Anexo A — saída real dos gates

Medido em `H:\Desktop\ArtPlus` (`master`, HEAD `503b922`) em 2026-11-24, após as correções de
`scripts/gate.py` (rodadas 1 e 2 do `testes`). Saída colada com exit code.

### A.1 `check_version.py --strict` → **0**

```
RESULTADO: APROVADO
```

### A.2 `gate.py --selftest` → **0**

```
TOTAL: 33/33 PASS
```

Cobre, entre outros: tudo ok; teste falho; auditoria reprovada; HALT **escopado**; `CAP-BLOCKED`;
spec incompleta; inventário adiantado; conclusão sem evidência; hash divergente; build não
executado/falho/stale; teste não executado/stale; feature sem teste; inventário coerente com etapa
vermelha; test de uma feature não invalida outra; `src` compartilhado invalida dependentes; token
independente de build alheio; feature bloqueada; menção em caminho não bloqueia; HALT coerente e
divergente; fora-do-escopo; **`--all --json` parseável**; **órfã citada vira aviso**; **órfã com
INVENTORY não é órfã**.

### A.3 `gate.py --halt` → **2**

```
HALT ATIVO — escopo bloqueado: F-007
```

### A.4 `gate.py --feature F-002` → **1** (não bloqueada)

```
HALT ATIVO: F-002 fora do escopo bloqueado; verificação factual.
estado comprovado: testado
```

### A.5 `gate.py --feature F-007` → **2** (bloqueada)

```
HALT ATIVO: F-007 está no escopo bloqueado (avanço bloqueado).
estado comprovado: bloqueado
```

### A.6 `gate.py --inventory` → **0** (sem traceback)

```
F-001  declarado=testado              comprovado=testado            coerente
F-002  declarado=testado              comprovado=testado            coerente
F-003  declarado=testado              comprovado=testado            coerente
F-004  declarado=fora-do-escopo-v24   comprovado=arquitetado        coerente
F-005  declarado=testado              comprovado=testado            coerente
F-006  declarado=implementado         comprovado=implementado       coerente
F-007  declarado=bloqueado            comprovado=bloqueado          coerente
F-008  declarado=testado              comprovado=testado            coerente
F-009  citada em docs/agents/CHECKPOINT.md:14   (órfã, aviso)
```

### A.7 `gate.py --all --json` → **2** (HALT escopado) + **JSON válido**

```
keys = version_ok, version_details, features, orphans
features = F-001..F-008
orphans  = F-009
```

`2` é o contrato documentado em `HALT.md` ("existe escopo bloqueado"), não falha de gate.

### A.8 `preflight.py` → **0**

```
INFO  WIP: 256 entrada(s) em git status --short (não reprova)
INFO  HEAD 503b922068af07ca21d8032c3465e2738a2b436f (2026-11-23 21:57:45 -0300)
PASS  raiz: H:/Desktop/ArtPlus
PASS  branch: master
PASS  versão: exit 0 — RESULTADO: APROVADO
RESULTADO: PASS (3/3 itens obrigatórios)
```

### A.9 `validate_skills.py` → **0**

```
agents: 9 | skills: 26 | commands: 14
ERROS: 0
AVISOS: 2 (command /halt e /progress sem $ARGUMENTS — comandos sem argumento por desenho)
```

### A.10 Token de auditoria: determinístico e por feature

```
F-002 token (1ª) = 20B03DF2DB4413A6B4E525543EE989B4DBDA24614149E2201D0594981D96C45C
F-002 token (2ª) = 20B03DF2DB4413A6B4E525543EE989B4DBDA24614149E2201D0594981D96C45C
deterministic=True
F-008 token     = 7CEC7E6315C9F18E1759D41AA41988C854C12BEF8C2B95477615F8098EBF45CA
differ=True
```

### A.11 Defeitos do gate que existiam antes (linha de base)

| Comando | Antes | Depois |
|---|---|---|
| `--inventory` | exit 1 + `ValueError: 'bloqueado' is not in list` | exit 0, sem traceback |
| `--all` | exit 1 + traceback em F-007 | exit 2 (HALT), 8 features avaliadas |
| `--feature F-008` | `estado comprovado: bloqueado` (falso positivo por caminho) | `testado` |
| `--all --json` | JSON inválido (texto humano antes) | JSON válido |
| `--feature F-002` | exit 2 (HALT global) | exit 1 (fora do escopo bloqueado) |
| token | mudava com `build.json` de qualquer feature | independe de build alheio |
| frescor de auditoria | `stale` por qualquer `src/**` | `stale` só por dependência da feature |
_
