---
description: Roda o gate factual do pipeline e mostra o estado comprovado
agent: orquestrador
---

Escopo opcional: $ARGUMENTS (ex.: `F-003`).

Rode, sem alterar nada:

1. `python scripts/gate.py --halt`
2. `python scripts/gate.py --all`
3. `python scripts/check_version.py --strict`
4. `python scripts/gate.py --inventory`

Apresente:

- estado **comprovado** por F-###;
- gates reprovados com o motivo exato (arquivo/ID);
- diferença entre o declarado no `INVENTORY.md` e o comprovado.

Não corrija nada neste comando. Correção é etapa separada, com gate próprio.
