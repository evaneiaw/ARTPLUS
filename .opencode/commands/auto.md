---
description: Executa o pipeline completo sem pedir decisões
agent: orquestrador
---

Escopo: $ARGUMENTS

Siga `docs/agents/AUTOPILOT.md` e o bloco "Modo autônomo" do seu prompt.
Versão de referência: ArtPro+ **v24.03.10017** (ver `docs/agents/REFERENCE_VERSION.md`).

```
ALVO: próxima tarefa elegível (ou o alvo de $ARGUMENTS), pipeline completo por feature
SPEC: docs/features/F-###.md + ADR aprovada + rag/evidence/F-###/manifest.json
SAÍDA: INVENTORY.md, ROADMAP.md, FEATURE_MATRIX.csv, docs/phases/STATUS.md e CHECKPOINT.md
       atualizados com o estado DERIVADO do gate
ACEITE: cada etapa com gate 0; auditoria aprovada, fresca e com token válido; WIP alheio preservado
LIMITE: orquestrador não edita src/, tests/, specs, evidência nem scripts; máx. 3 subagentes;
        1 comportamento por vez
FALHA: gate != 0 devolve ao dono (máx. 2 tentativas); a terceira vira BLOQUEIOS.md e o ciclo
       segue na próxima feature independente
```

## Passo 0 — pré-voo, HALT e gate (obrigatório, antes de tudo)

0. **Árvore canônica e WIP.** Rode `python scripts/preflight.py` (se existir) ou, no mínimo:
   `git rev-parse --show-toplevel` (= `H:/Desktop/ArtPlus`), `git rev-parse --abbrev-ref HEAD`
   (= `master`), `git status --short` e `git log -1 --format=%H`. Worktree/clone/HEAD destacado
   = cópia divergente: pare e reporte. Registre o WIP alheio antes de tocar em qualquer arquivo.
1. Leia `docs/agents/HALT.md` e `docs/agents/BLOQUEIOS.md`. A lista de bloqueio é a **tabela**:
   pule só as features nela listadas. Retorno `2` de `--halt` significa "há escopo bloqueado
   declarado", não parada global.
2. Rode `python scripts/check_version.py --strict` e `python scripts/gate.py --inventory`.
   `python scripts/gate.py --all` é diagnóstico global; uma falha em alvo bloqueado não impede
   a execução de outro alvo elegível.
3. Antes de cada etapa, rode o gate específico da feature. Não avance aquela etapa se retornar
   diferente de 0; registre bloqueio e continue a próxima tarefa independente.

Interpretação dos argumentos:
- vazio: execute a **próxima tarefa elegível** (§2 da política) e **continue**;
- `F-###` ou nome de módulo: **priorize** esse alvo.
  - Se `F-###` **já existe** no INVENTORY/manifest: retome do gate mais avançado.
  - Se `F-###` **não existe** (órfão): **bootstrap automático**. O orquestrador:
    - executa `rea` para triagem leve dos binários v24 não cobertos;
    - escolhe o candidato de maior valor (UI própria Esko, tamanho, menus/dialogs);
    - cria `rag/evidence/F-###/manifest.json` com id, versao_ref: 24.03.10017, binario, sha256;
    - segue o pipeline normal (ghidra → comportamento → spec → ...). **Nunca pergunte ao usuário.**
- `--extract`: investigação, evidência, spec e dossiê — **sem implementação**;
- `--static`: triagem estática, **sem GUI**;
- `--max N`: no máximo N módulos nesta execução (limite solicitado pelo usuário, **não** uma regra padrão de encerramento).

Se `--static` estiver presente:
1. despache `rea` para triagem leve: `diec`, `strings64`, `scripts/inspect_pe.py` e exports existentes. **Proibido** `rea analyze`/`decompile` com Ghidra neste modo. **Não crie `manifest.json` nem IDs de evidência sem um `F-###` válido**; registre a triagem em `docs/reverse-engineering/`;
2. peça ao `testes` para gerar o dossiê;
3. se não houver export Ghidra e o módulo tiver até 12 MB, despache `ghidra` e peça o dossiê de novo. O `ghidra` grava só em `rag/ghidra/exports/` e `docs/reverse-engineering/`; não invente `manifest.json` sem `F-###`;
4. não acione `comportamento`, `documentacao`, `arquitetura`, `implementacao` nem `auditor`;
5. registre lacunas no dossiê e siga.

Execute o pipeline por funcionalidade: `rea` + `ghidra` + `comportamento`
(paralelo quando possível) → `documentacao` → `arquitetura` → `implementacao`
→ `testes` → `auditor`.

**Cada seta é um gate, não uma opinião.** Após cada etapa rode
`python scripts/gate.py --feature F-### --stage <evidence|spec|adr|code|test|audit>`.
Saída diferente de `0` = etapa NÃO concluída: devolva ao dono (máx. 2 tentativas) e,
na terceira, registre bloqueio. Nunca eleve o estado no `INVENTORY.md` acima do comprovado.

Não faça perguntas entre etapas. Escale apenas nos cinco casos da política.
Auditoria reprovada volta **uma vez** com a lacuna exata; a segunda reprovação vira
bloqueio registrado e o ciclo segue.

Continue para a próxima tarefa elegível — **não há limite padrão** de 1 módulo /
90 minutos / 6 ciclos. `--max N` é o único limite de quantidade, quando solicitado.
Feature bloqueada (tabela do `HALT.md`/`BLOQUEIOS.md`) **não** é motivo para parar o `/auto`:
avance a próxima feature independente com gate verde.

Cada subagente devolve, além do relatório, o bloco `HANDOFF` (arquivos tocados, último comando
+ exit, pendente, próximo comando). Limite de passos não é conclusão: ao retomar, continue do
handoff sem refazer etapa provada.

Ao concluir cada feature auditada: atualize `INVENTORY.md`, `ROADMAP.md`,
`FEATURE_MATRIX.csv` e `docs/agents/CHECKPOINT.md`; peça ao `testes` para rodar
`python scripts/dossier.py --module <módulo>`.

Ao atingir um limite **real** da sessão: escreva `docs/agents/CHECKPOINT.md` +
`docs/phases/STATUS.md` e informe **exatamente como retomar** (FEITO, BLOQUEADO,
PRÓXIMO, COBERTURA, ONDE LER).
