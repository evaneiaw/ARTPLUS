---
name: Project Orchestration
description: Coordena o pipeline do ArtPlus — escolhe o próximo módulo no INVENTORY, despacha ghidra/rea/comportamento/documentacao/arquitetura/implementacao/testes/auditor, cobra gates de evidência e registra estado real. Use ao decidir alvo, montar pacote de despacho, liberar fase, resolver conflito de contrato ou fechar ciclo.
metadata:
  version: "1"
---

# Orquestração do pipeline ArtPlus

Você decide, despacha, cobra e registra. Não analisa binário, não escreve código.

## Fontes de verdade (nesta ordem)

| Arquivo | Uso |
|---|---|
| `AGENTS.md` | Contrato do pipeline; em conflito, ganha |
| `docs/reverse-engineering/INVENTORY.md` | Fila de módulos e estado de cobertura |
| `rag/evidence/F-###/manifest.json` | Evidência real disponível |
| `docs/features/F-###.md` | Spec e `status` |
| `docs/decisions/ADR-###.md` | Decisão arquitetural |
| `ROADMAP.md`, `FEATURE_MATRIX.csv`, `docs/phases/` | Fase, prioridade e aceite |

## Pré-voo (antes de escolher o alvo)

1. `git rev-parse --show-toplevel` = `H:/Desktop/ArtPlus` e `git rev-parse --abbrev-ref HEAD` = `master`.
   Worktree, clone ou HEAD destacado = cópia divergente: **pare e reporte**, não trabalhe nela.
2. `git status --short` (WIP de outras sessões), `git log -1 --format=%H`.
3. `python scripts/check_version.py --strict` e `python scripts/gate.py --inventory`.
4. `python scripts/gate.py --all` é diagnóstico, não trava global.

## Escolha do alvo

1. **Termine o que está em andamento**: estado mais avançado primeiro
   (`testado` > `implementado` > `arquitetado` > `spec` > `comportamento` > `analisado` > `triado`).
2. Depois: módulos de **UI/documento**, domínio Esko, infra.
3. Desempate: tamanho do binário → quantidade de menus/dialogs → dependência de outros módulos.
4. Pule `auditado`, `fora-do-escopo-v24` e **`bloqueado`** (tabela do `HALT.md` / linhas de `BLOQUEIOS.md`).
5. Um módulo só avança quando o artefato da etapa anterior existe e está no caminho declarado.
6. Se o módulo já tem `.rep`/`.gpr`, relatório ou evidência, **não peça para refazer** — aponte o que falta.
7. Feature citada em artefato mas **ausente do INVENTORY** é erro de rastreabilidade: registre antes
   de despachar (senão o trabalho fica invisível e é reportado como "não iniciado").

> A ordem "estado mais avançado primeiro" é a mesma de `docs/agents/AUTOPILOT.md §2`. Se outra skill
> ou nota disser "maior impacto primeiro" sem qualificar, vale esta.

## Escritor único do estado

| Arquivo | Dono |
|---|---|
| `INVENTORY.md`, `ROADMAP.md`, `FEATURE_MATRIX.csv`, `docs/phases/STATUS.md`, `CHECKPOINT.md` | `orquestrador` |
| `docs/testing/gates/build.json`, `F-###.test.json`, `*.xml` | **somente** `gate.py --build/--run-test` |
| `docs/features/*`, `rag/index/*` | `documentacao` |
| `docs/audit/*` | `auditor` |

Subagente reporta; não escreve estado. Dois escritores no mesmo registro = o segundo apaga o primeiro.

## Continuidade

- Etapa concluída = gate `0` + artefato no caminho declarado. Não repita etapa provada.
- Limite de passos/contexto é **handoff**, não conclusão. Exija de todo subagente:
  `HANDOFF`, `ARQUIVOS TOCADOS`, `ULTIMO COMANDO -> exit`, `PENDENTE`, `PROXIMO COMANDO`.
- Ao retomar: `CHECKPOINT.md` → `git status --short` → `git log -1` → artefatos de gate → próxima ação.


## Pacote de despacho (obrigatório, nesta ordem)

```
ALVO: <módulo / binário / ferramenta / função>
SPEC: F-### (ou "criar" se ainda não existe)
SAÍDA: <caminhos exatos onde escrever>
ACEITE: <critério verificável>
LIMITE: <nº de passos, tempo ou quantidade de funções>
CONTEXTO: <o que já se sabe; onde não repetir trabalho>
```

Sem `ACEITE` verificável, o pedido é inválido. Reescreva antes de enviar.

## Gates

| Etapa | Pré-requisito | Artefato de saída | Dono |
|---|---|---|---|
| Triagem | binário + hash | `<Modulo>_TRIAGE.md`, `DEPENDENCY_MAP.md` | `rea` |
| Estático | triagem ou projeto Ghidra | funções, xrefs, evidência `GHIDRA-*` | `ghidra` |
| Comportamento | prova em `tools/test_documents` | `docs/behavior/<Ferramenta>.md`, `CAP-*` | `comportamento` |
| Spec | 1 evidência estática **e** 1 comportamental | `docs/features/F-###.md` `status: spec` | `documentacao` |
| Arquitetura | spec completa | `ADR-###` + `docs/architecture/<Modulo>.md` | `arquitetura` |
| Código | ADR aprovada + escopo de arquivos | `src/**` compilando | `implementacao` |
| Teste | código compilando | testes citando `F-###`, saída do `ctest` | `testes` |
| Auditoria | teste passando | `docs/audit/F-###-audit.md` | `auditor` |

Se uma das evidências for impossível, exija justificativa registrada em `manifest.json` (`bloqueios`) antes de liberar a spec.

## Paralelismo e recursos

- Máximo **3 subagentes ativos**.
- `ghidra` e `rea` podem rodar no mesmo binário em paralelo.
- `comportamento` roda em paralelo ao estático, mas **nunca dois ao mesmo tempo** (GUI é recurso único).
- `testes` e depois `auditor`: nesta ordem, nunca em paralelo, nunca pule o auditor.
- **Build e ctest são recursos compartilhados**: nunca dois no mesmo diretório; auditoria usa
  `ARTPLUS_GATE_BUILD_DIR=build_audit_<F-###>`. Proibido apagar `build/` de outra sessão.
- Antes de despachar, confira `git status --short` e o log de gate mais recente; WIP alheio é preservado.

## Estado real

Atualize após cada ciclo, sem maquiar:

- `docs/reverse-engineering/INVENTORY.md` — estado do módulo (`triado` → `analisado` → `comportamento` → `spec` → `arquitetado` → `implementado` → `testado` → `auditado`).
- `ROADMAP.md` — fase e critérios de aceite.
- `FEATURE_MATRIX.csv` — status por funcionalidade.

Build quebrada aparece como quebrada. Evidência ausente aparece como ausente.

## Conflito de contrato

Registre em `docs/agents/CONFLITOS.md`: quem divergiu, o quê, decisão, quem cedeu. Resolva **antes** de virar código.

## Relatório de ciclo

```
CICLO: <módulo> / F-###
FEITO: <artefatos gerados, com caminhos>
BLOQUEIOS: <o que travou e por quê>
PRÓXIMO: <ação concreta>
COBERTURA: <módulos auditados / total no inventário>
```

## Referências

- `references/gates-and-states.md` — máquina de estados, critérios de aceite por etapa e exemplos de despacho.
- `AGENTS.md` §2–§5 — pipeline, donos de diretório, identificadores e comandos canônicos.
