---
description: Estudo reverso de F-### (REA + Ghidra + comportamento + spec), sem implementação
agent: orquestrador
---

Alvo: $ARGUMENTS

Execute o **estudo reverso** do alvo conforme `AGENTS.md`, `docs/agents/AUTOPILOT.md`
e a skill `project-orchestration`. Versão de referência: ArtPro+ **v24.03.10017**
(`docs/agents/REFERENCE_VERSION.md`).

```
ALVO: $ARGUMENTS   (F-### ou módulo .dll)
SPEC: docs/features/F-###.md (criar quando não existir)
SAÍDA: docs/reverse-engineering/F-###-TRIAGE.md + <Modulo>_FUNCTIONS.md,
       rag/evidence/F-###/{rea,ghidra,behavior}/ + manifest.json,
       docs/features/F-###.md, docs/agents/CHECKPOINT.md
ACEITE: gate --feature F-### --stage evidence rc0 e --stage spec rc0;
        manifest com versao_ref 24.03.10017 + sha256 real do binário v24;
        >=1 ID GHIDRA resolvido + 1 CAP válido (CAP-BLOCKED não conta)
LIMITE: estudo apenas — SEM ADR, src/, tests/ nem auditoria.
        Máx. 3 subagentes ativos; 1 comportamento por vez (GUI única)
CONTEXTO: INVENTORY.md, DEPENDENCY_MAP.md e projetos Ghidra existentes;
          não refazer evidência já gravada
```

Interpretação dos argumentos:
- `F-###`: feature alvo. Se ainda não houver módulo mapeado, o `rea` propõe o
  binário candidato em `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows`
  antes do Ghidra e registra em `docs/reverse-engineering/F-###-TRIAGE.md`.
- `<Modulo>.dll`: módulo alvo; derive o `F-###` do manifest/INVENTORY ou crie um novo.
- vazio: **pare** e pergunte qual `F-###` estudar — nunca escolha sozinho.
- `--static`: só REA + Ghidra + dossiê; sem GUI e sem spec.
- `--full`: após a spec, continue ADR → código → teste → auditoria
  (equivalente a `/auto F-###`).

## Passo 0 — pré-voo (obrigatório, antes de qualquer despacho)
1. `python scripts/preflight.py` (ou `git rev-parse --show-toplevel`,
   `--abbrev-ref HEAD`, `status --short`, `log -1`). Árvore canônica =
   `H:/Desktop/ArtPlus`, branch `master`. Worktree/clone/HEAD destacado = pare.
2. Leia `docs/agents/HALT.md` e `docs/agents/BLOQUEIOS.md`: pule só as features
   da tabela de bloqueio (hoje: F-007/BLO-008).
3. `python scripts/check_version.py --strict` e `python scripts/gate.py --inventory`.
4. Se o alvo estiver bloqueado, pare e reporte; não reatribua.

## Passo 1 — REA + Ghidra em paralelo (2 subagentes)
Despache **juntos**, cada um com o pacote completo `ALVO / SPEC / SAÍDA / ACEITE / LIMITE / CONTEXTO`:
- `rea` → conforme `.opencode/commands/triage.md` e skill `rea-reverse-engineering`:
  DIE, `strings64`, `inspect_pe.py`, exports/imports, RTTI, dependências, hash SHA-256.
  Grava `rag/evidence/F-###/rea/`, `rag/sources/`,
  `docs/reverse-engineering/<Modulo>_TRIAGE.md`.
- `ghidra` → conforme `.opencode/commands/ghidra.md` e skill `ghidra-analysis`:
  import headless (JDK 25), funções/xrefs/vtables/strings, pseudocódigo via REA CLI
  ou script (nunca screenshot). Grava `rag/evidence/F-###/ghidra/` com IDs
  `GHIDRA-<Modulo>-0x<addr>` e `docs/reverse-engineering/<Modulo>_FUNCTIONS.md`.

Regra: se o projeto `.rep`/`.gpr` ou o relatório já existir, **não reimporte**.
Nenhum dos dois escreve `manifest.json` com placeholder; o `ghidra` só registra ID
cujo arquivo de evidência existe de fato.

## Passo 2 — comportamento (1 subagent, GUI única)
Após os dois terminarem, despache `comportamento` conforme
`.opencode/commands/capture.md`: `CAP-AAAAMMDD-nn` com passos reais, rótulos
literais, campos medidos (default/unidade/faixa), saída e capturas. Grava
`tools/reference_capture/F-###/`, `docs/behavior/`, `rag/evidence/F-###/behavior/`.
Se a GUI falhar, registre `CAP-BLOCKED-*` — ele **não** conta como evidência válida.

## Passo 3 — documentação (1 subagent)
Despache `documentacao` conforme `.opencode/commands/spec.md` e skill
`technical-specification`: `docs/features/F-###.md` com 8 seções, regras numeradas,
unidades explícitas (`mm`, `pt`, `dpi`), exceções, em aberto e rastreabilidade.
**Regra dura:** exige >=1 evidência estática e >=1 comportamental válidas.
Se faltar, devolva `BLOQUEIO / FALTA / ONDE OBTER / IMPACTO` — não escreva spec.

## Passo 4 — gates e checkpoint

**Passo 4.1 — GATE-BASED (padrão / `--full`)**
1. `python scripts/gate.py --feature F-### --stage evidence` → rc0 obrigatório.
2. `python scripts/gate.py --feature F-### --stage spec` → rc0 obrigatório.
3. Depois segue ADR → código → testes → auditoria (se `--full` ou vazio, como `/auto`).

**Passo 4.2 — GATE-STATIC (`--static`)**
1. `python scripts/gate.py --feature F-### --stage evidence` → rc0 obrigatório.
2. **Não exige gate de spec** — `--static` para só triagem/estático. Se quiser continuar, usar `/auto F-###` ou `/estudar F-###` (padrão) depois.
3. Peça ao `testes` o dossié (`python scripts/dossier.py --module <Modulo>`).

**Passo 5 — geral** (padrão, `--full`, ou `--static`)
3. Atualize **somente** `docs/agents/CHECKPOINT.md` e, se aplicável, peça ao
   agente `testes` o dossiê (`python scripts/dossier.py --module <Modulo>`).
   `INVENTORY.md`, `ROADMAP.md`, `FEATURE_MATRIX.csv` e `STATUS.md` só com
   estado derivado de `gate.py --inventory` — nunca elevado à mão.
4. Relatório final: `ESTUDO / FEITO / BLOQUEADO / PRÓXIMO / COBERTURA / ONDE LER`.

## Regras duras
- O orquestrador não edita `src/`, `tests/`, specs, evidência bruta nem `manifest.json`.
- Spec sem evidência não vira ADR; v25 (histórica) nunca serve como evidência da v24.
- Gate != 0 devolve ao dono (máx. 2 tentativas); a 3ª vira `BLOQUEIOS.md` e a
  feature fica `bloqueado`.
- Ao atingir limite real da sessão, grave `CHECKPOINT.md` + `STATUS.md` com
  FEITO / BLOQUEADO / PRÓXIMO / COBERTURA / ONDE LER — limite não é conclusão.
