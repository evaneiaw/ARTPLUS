---
description: Roda um ciclo do pipeline ArtPlus para um módulo ou F-###
agent: orquestrador
---

Alvo: $ARGUMENTS

Execute um ciclo do pipeline conforme `AGENTS.md` e a skill `project-orchestration`.

1. Leia `docs/reverse-engineering/INVENTORY.md`, `rag/evidence/F-###/manifest.json`, `docs/features/F-###.md` e `docs/decisions/` do alvo.
2. Determine o gate atual (triagem, estático, comportamento, spec, arquitetura, código, teste, auditoria) rodando `python scripts/gate.py --feature F-### --stage <etapa>`.
3. Despache **somente** o próximo passo pendente, com o pacote obrigatório: ALVO, SPEC, SAÍDA, ACEITE, LIMITE, CONTEXTO.
4. Não repita trabalho que já tem evidência no caminho declarado.
5. Não edite `src/`, `tests/`, specs nem evidência.
6. Ao final, atualize `INVENTORY.md`, `ROADMAP.md`, `FEATURE_MATRIX.csv` e `docs/phases/STATUS.md` com o estado real derivado do gate.
7. Responda no formato de relatório de ciclo (CICLO, FEITO, BLOQUEIOS, PRÓXIMO, COBERTURA).

Se o alvo estiver vazio, escolha a próxima feature pelo INVENTORY (estado mais avançado primeiro) e diga qual escolheu e por quê. Um despacho = uma etapa; ao receber o gate `0`, continue para a etapa seguinte sem pedir confirmação — pare apenas quando a feature fechar, um gate falhar duas vezes ou um bloqueio do HALT/BLOQUEIOS aparecer.
