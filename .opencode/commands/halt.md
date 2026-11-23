---
description: Suspende o fluxo de funcionalidades (HALT) até autorização do proprietário
agent: orquestrador
---

Ative a suspensão conforme `AGENTS.md` §10.1:

1. Crie/atualize `docs/agents/HALT.md` com data, motivo e escopo.
2. Atualize `docs/phases/STATUS.md` e `docs/agents/CHECKPOINT.md` informando HALT ativo.
3. Responda com: o que está suspenso, o que continua permitido (auditoria read-only e
   recuperação do sistema de agentes) e como o HALT é removido.

**Não** remova o HALT você mesmo. A remoção é exclusiva do proprietário do projeto, após
autorização registrada em `docs/audit/AGENT_SYSTEM_RECOVERY_AUDIT.md`.
