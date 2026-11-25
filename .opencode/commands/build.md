---
description: Build doctor e testes do estado atual do projeto
agent: testes
---

Execute o build doctor e a suíte conforme a skill `build-and-release`.

Alvo opcional: $ARGUMENTS (se informado, limite o build a esse alvo; senão, projeto inteiro).

```
ALVO: estado atual do repositório
SPEC: não se aplica
SAÍDA: docs/testing/gates/build.json + logs/build-*.log (via gate.py); opcionalmente docs/testing/CLEAN_CLONE_BUILD.md
ACEITE: configure com toolchain correto, build Release com exit 0 e ctest com saída real e exit code
LIMITE: não alterar src/
CONTEXTO: build atual precisa de mingw-msvcrt e CMake Kitware absoluto
```

Passos:
1. `git status --short` — registre o WIP alheio; não reverta nada.
2. Se outro build estiver ativo em `build/`, use árvore isolada: `$env:ARTPLUS_GATE_BUILD_DIR='build_<escopo>'`.
3. Rode `python scripts/gate.py --build` — ele grava `docs/testing/gates/build.json` com comando, exit code, log e hash. Não grave esse arquivo à mão.
4. Rode `ctest` na mesma árvore (`ctest --test-dir <dir> --output-on-failure`) ou, por feature, `python scripts/gate.py --feature F-### --run-test`.
5. Confirme `CMAKE_CXX_COMPILER` POSIX.MSVCRT e `CMAKE_PREFIX_PATH=C:/Qt/6.8.3/mingw_64`; use `PATH=C:\Qt\6.8.3\mingw_64\bin` no teste.

Se falhar, diagnostique por etapa (configure/compile/link/run) e devolva o erro exato; não edite `src/` para passar. Não apague `build/` compartilhado. Relate comando, resultado, exit code e tempo.
