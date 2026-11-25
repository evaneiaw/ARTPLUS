---
description: Implementa uma funcionalidade C++17/Qt a partir da ADR
agent: implementacao
---

Funcionalidade: $ARGUMENTS

Implemente conforme a skill `qt-cpp-development`.

```
ALVO: $ARGUMENTS
SPEC: F-### + ADR-###
SAÍDA: src/** e CMakeLists.txt somente
ACEITE: código compilando (exit 0), regras da spec cobertas, sem stub silencioso, diff completo e relatório com comando + saída de build
LIMITE: incremento pequeno; compile a cada incremento; corrija todos os erros
CONTEXTO: leia a ADR, a spec e o código vizinho; confirme os arquivos que pode tocar
```

Regras de execução:
1. Antes de remover `#include`, símbolo, arquivo ou entrada do CMake, procure quem depende (`rg` em `src/`, `tests/`, `CMakeLists.txt`).
2. Compile a cada incremento; corrija **todos** os erros até `exit 0`, não só o primeiro.
3. Build com o CMake Kitware absoluto e o preset `mingw-msvcrt` → `release-mingw`; se `build/` estiver em uso por outra sessão, use árvore isolada e informe o caminho.
4. Preserve WIP de outra sessão: nada de `git checkout/reset/clean/stash`, nada de reformatar arquivo inteiro.
5. Entregue `git diff --stat` + resumo por arquivo, e o bloco HANDOFF se o limite de passos chegar.

Se falhar por toolchain, devolva ao orquestrador (quem conserta é `testes`). Não edite `tests/`, `docs/`, `rag/`, `CMakePresets.json` nem `opencode.jsonc`. Não adicione dependência sem ADR. Entregue ARQUIVOS/DIFF/BUILD/FALTA/RISCOS.
