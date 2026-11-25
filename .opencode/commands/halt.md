---
description: Suspende o fluxo de funcionalidades (HALT) até autorização do proprietário
agent: orquestrador
---

Ative a suspensão conforme `AGENTS.md` §10.1:

```
ALVO: registrar bloqueio por escopo em docs/agents/HALT.md
SPEC: AGENTS.md §10.1 (HALT é escopo, não trava global automática)
SAÍDA: HALT.md + STATUS.md + CHECKPOINT.md atualizados
ACEITE: o escopo suspenso e o permitido estão explícitos; nenhum bloqueio é ampliado sem autorização
LIMITE: não suspende o projeto inteiro por conta própria; não remove HALT existente
FALHA: sem autorização do proprietário, apenas registre e reporte — não altere escopo
```

1. Crie/atualize `docs/agents/HALT.md` com data, motivo e escopo.
2. Atualize `docs/phases/STATUS.md` e `docs/agents/CHECKPOINT.md` informando HALT ativo.
3. Responda com: o que está suspenso, o que continua permitido (auditoria read-only e
   recuperação do sistema de agentes) e como o HALT é removido.

**Não** remova o HALT você mesmo. A remoção é exclusiva do proprietário do projeto, após
autorização registrada em `docs/audit/AGENT_SYSTEM_RECOVERY_AUDIT.md`.
