# Revalidação final — árvore isolada `build_core_gate` (2026-11-24)

Agente: `testes`. Escopo: Etapa 6 (parte 1). Nenhum arquivo de `src/`, `tests/`,
`docs/features/`, `docs/audit/` ou `rag/evidence/` foi editado. Sem commit.

## Ambiente

- CMake: `C:\Users\Evanei\AppData\Local\Microsoft\WinGet\Packages\Kitware.CMake_Microsoft.Winget.Source_8wekyb3d8bbwe\cmake-4.4.4-windows-x86_64\bin\cmake.exe` (4.4.4)
- Compilador: `C:/Users/Evanei/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.POSIX.MSVCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/g++.exe` (MinGW-W64 x86_64-msvcrt-posix-seh 16.2.0)
- Qt: `C:/Qt/6.8.3/mingw_64`
- Build type: `Release`, generator `MinGW Makefiles`

## 1. Configure do zero

```
Remove-Item -Recurse -Force build_core_gate
& $cmake --preset mingw-msvcrt -B build_core_gate
```

Saída (trecho final):

```
-- The CXX compiler identification is GNU 16.2.0
-- Check for working CXX compiler: .../WinLibs.POSIX.MSVCRT.../g++.exe - skipped
-- Configuring done (2.7s)
-- Generating done (0.8s)
-- Build files have been written to: H:/Desktop/ArtPlus/build_core_gate
CONFIGURE_EXIT=0
```

Verificação do cache:

```
CMAKE_BUILD_TYPE:STRING=Release
CMAKE_CXX_COMPILER:STRING=C:/Users/.../WinLibs.POSIX.MSVCRT.../mingw64/bin/g++.exe
CMAKE_PREFIX_PATH:UNINITIALIZED=C:/Qt/6.8.3/mingw_64
CMAKE_GENERATOR:INTERNAL=MinGW Makefiles
```

## 2. Build completo

```
& $cmake --build build_core_gate
BUILD_EXIT=0 elapsed=1453.2s
...
[100%] Built target test_color_management
```

## 3. CTest — matriz 11/11

```
& $ctest --test-dir build_core_gate --output-on-failure
 1/11 FormXObjects ......... Passed  0.09
 2/11 PdfSmoke ............. Passed  0.11
 3/11 UnitTests ............ Passed  0.09
 4/11 PdfRoundTrip ......... Passed  0.18
 5/11 EditingTests ......... Passed  0.10
 6/11 IntegrationTestBasic . Passed  0.14
 7/11 MarkSetProcessor ..... Passed  0.11
 8/11 BearerBarTests ....... Passed  0.12
 9/11 CutMarkTests ......... Passed  0.12
10/11 SaveDocumentTests .... Passed  0.15
11/11 F-008 ................ Passed  0.06
100% tests passed out of 11
CTEST_EXIT=0 (1.29s real)
```

`PdfSmoke` (novo) passou.

## 4. Gate build

```
$env:ARTPLUS_GATE_BUILD_DIR='build_core_gate'
python scripts/gate.py --build
[build] configure ignorado (cache existente em build_core_gate/CMakeCache.txt)
[build] exit_code=0
[build] log: docs/testing/gates/logs/build-20261124-113704-286.log
[build] APROVADO
GATE_BUILD_EXIT=0
```

`docs/testing/gates/build.json`: `exit_code=0`, `build_dir=build_core_gate`,
`log_sha256=1641EC830D5E2B3C0BAA196F141AC2021D55FB20FF262188782598C204DC0549`
(confere com o log real). Observação: `configured=false` porque o gate reaproveita o cache
já configurado do passo 1 — o configure do zero está registrado acima, exit 0.

## 5. Artefatos de teste regenerados

| Feature | Suíte | tests | failures | exit |
|---|---|---|---|---|
| F-001 | CutMarkTests | 1 | 0 | 0 |
| F-002 | MarkSetProcessor | 1 | 0 | 0 |
| F-003 | BearerBarTests | 1 | 0 | 0 |
| F-005 | PdfRoundTrip | 1 | 0 | 0 |
| F-006 | SaveDocumentTests | 1 | 0 | 0 |
| F-008 | F-008 | 1 | 0 | 0 |

Arquivos: `F-00X.xml`, `F-00X.test.json`, logs `logs/test-F-00X-20261124-11372x-*.log`.

## 6. Gates por etapa

`--stage code` e `--stage test` = **0** para F-001, F-002, F-003, F-005, F-006, F-008.
`--stage audit` continua vermelho em todas: laudo sem o token atual (artefatos foram
regenerados, token mudou). Esperado e registrado abaixo.

## 7. `--inventory`

`INVENTORY_EXIT=1`. Divergências:

- F-001/002/003/005/006/008: declarado `auditado`, comprovado `testado` — GATE 7 reprovado
  porque GATE 6 (auditoria) está vermelho por token stale.
- F-004: declarado `fora-do-escopo-v24`, comprovado `arquitetado`. GATE 4/5 vermelhos
  (`spec não declara arquivos de implementação em src/`, `nenhum teste cita F-004`),
  mas o ramo especial de `fora-do-escopo-v24` considera a coerência OK (GATE 7 sem mensagem).
- F-007: declarado `bloqueado` = comprovado `bloqueado` (BLO-008); demais gates vermelhos por
  ausência de spec/ADR/código/teste/laudo — esperado para feature bloqueada.

## 8. `--all`

`ALL_EXIT=2` (HALT declarado). Nenhum gate vermelho inesperado nos F-00X testáveis:
apenas GATE 6 (token stale) e GATE 7 (consequência). F-004 (fora-do-escopo) e F-007
(bloqueada) vermelhos conforme o estado declarado.

## 9. Tokens frescos

```
F-001 764319C9F727D8939DEE0D08AF4EB391D95503C56D22D9E860792A6EC0FB02F4
F-002 D5C6B77CA5523904886D1A900178D56F9B1383E3F17D56A7CFE406A7D24A1D35
F-003 A8D0A02EB4FBE3D50F45B9146D8EC072786F7C548B78F1E45E2FE33AC20EB245
F-005 F3E1FC010B917ABDE5408BE0A59BCB143316C24C6F564A45B4C30060D1FFD457
F-006 44E87E0F55EC9D456CB4717AFA6DA210034FF0FDF965D60438B3B57D8064CE49
F-008 5354D323F0552DC59F4617AA134BE548665792A581944AF85C4F40E284713C16
```

Todos com exit 0. Laudos de auditoria devem citar o token da própria feature para GATE 6/7
voltarem a verde (edição de `docs/audit/` pertence ao `auditor`).

## 10. Não coberto

- `--stage audit` verde: exige reemissão de laudo com o token novo (fora do escopo do `testes`).
- `--inventory` verde: depende do item anterior.
- Teste `needBackupOnSave+E10` citado como pendência em BLOQUEIOS (risco residual de F-006) não
  foi implementado nesta etapa.
