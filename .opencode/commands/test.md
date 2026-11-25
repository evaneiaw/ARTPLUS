---
description: Escreve e roda os testes de um F-###
agent: testes
---

Funcionalidade: $ARGUMENTS

Escreva e execute os testes conforme a skill `test-strategy`.

```
ALVO: $ARGUMENTS
SPEC: F-### + ADR-### + código implementado
SAÍDA: tests/**, docs/testing/**
ACEITE: cada regra da spec com teste rastreável, tolerância explícita, gate --stage test = 0 e saída colada
LIMITE: um F-###; não altere src
CONTEXTO: golden nasce de rag/evidence/F-###/behavior/; leia CMakeLists para o target correto
```

Passos:
1. Identifique a suíte mapeada em `scripts/gate.py` (`FEATURE_TEST_MAP`) e o `add_test` real no `CMakeLists.txt`.
2. Escreva o teste citando `F-###`, com caso normal, limite e falha; sem mock do objeto sob teste.
3. Build na árvore configurada (ou isolada, se houver build concorrente) e rode:
   `python scripts/gate.py --feature F-### --run-test` → grava `F-###.test.json` + XML.
4. Rode `python scripts/gate.py --feature F-### --stage test` e cole a saída.
5. Rode a suíte completa como regressão; relate falhas, sem desativar teste.

Não edite `src/`, specs, evidência nem `CMakeLists.txt`. Se o código estiver errado, relate `arquivo:linha` e devolva. Relate comando, pass/fail por teste, exit code, tempo e o que não foi coberto.
