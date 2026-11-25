---
description: Roda o gate factual do pipeline e mostra o estado comprovado
agent: orquestrador
---

Escopo opcional: $ARGUMENTS (ex.: `F-003`).

```
ALVO: estado comprovado do pipeline (global ou do escopo de $ARGUMENTS)
SPEC: não se aplica (comando somente leitura)
SAÍDA: saída real dos gates, colada com exit code de cada comando
ACEITE: os quatro comandos executados sem alterar arquivo; divergência declarado x comprovado explícita
LIMITE: não corrige nada, não eleva estado, não roda build
FALHA: comando com erro/exit != 0 é reportado como está — nunca interpretado como sucesso
```

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
