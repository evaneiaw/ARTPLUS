---
description: Audita uma entrega e emite veredito com evidência
agent: auditor
---

Funcionalidade: $ARGUMENTS

Audite conforme a skill `evidence-verification`.

```
ALVO: $ARGUMENTS
SPEC: F-### + evidência + código + teste
SAÍDA: docs/audit/F-###-audit.md (reauditoria: F-###-audit-2.md)
ACEITE: veredito com comando reproduzível, saída colada, token medido nesta sessão e cadeia spec→evidência→código→teste
LIMITE: uma auditoria; não corrigir nada
CONTEXTO: verifique o manifest, o hash do binário e os arquivos citados antes de confiar
```

Passos:
1. `python scripts/gate.py --all` e `python scripts/gate.py --feature F-### --stage audit` — cole a saída.
2. Confira `rag/evidence/F-###/manifest.json` (sha256 real, versão, IDs resolvem).
3. Build isolado: `$env:ARTPLUS_GATE_BUILD_DIR='build_audit_<F-###>'` + `python scripts/gate.py --build`.
4. Rode o teste: `python scripts/gate.py --feature F-### --run-test` (ou `ctest`).
5. Meça o token **depois** do build/teste: `python scripts/gate.py --feature F-### --emit-token` e cole no laudo (`Gate-Token:`).
6. Veredito: sem comando + saída + token desta sessão = REPROVADO.

Não edite nada fora de `docs/audit/`. Não apague `build/` compartilhado. Reauditoria cita o que mudou.
