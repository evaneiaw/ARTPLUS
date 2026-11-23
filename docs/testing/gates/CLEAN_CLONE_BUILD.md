# Build em clone limpo — HEAD `4b174c3`

Fecha a lacuna **I-5** ("build em clone limpo não demonstrado") e o item **A5** pendente
(smoke do `ArtPlus.exe`).

| Campo | Valor |
|---|---|
| Data | 2026-11-21 |
| Commit testado | `4b174c3d96fd862b867e1aee3d2f7c6183ec8ccb` — `fix(build): restaura HEAD compilavel integrando prepress, automation, color, document e ui` |
| Origem | `H:\Desktop\ArtPlus` (clone local `--no-hardlinks`) |
| Clone | `C:\Users\Evanei\AppData\Local\Temp\opencode\artplus-clean-4b174c3\` |
| CMake | Kitware 4.4.4 (`...\Kitware.CMake_...\cmake-4.4.4-windows-x86_64\bin\cmake.exe`) |
| Compilador | WinLibs **POSIX.MSVCRT** `g++.exe` 16.2.0 (x86_64-msvcrt-posix-seh, Brecht Sanders r3) |
| Make | `mingw32-make.exe` do mesmo pacote POSIX.MSVCRT |
| Qt | `C:/Qt/6.8.3/mingw_64` |
| Logs | `logs/clean-clone-{configure,build,ctest}-4b174c3-20261121.log`, `logs/clean-clone-ctest-4b174c3-20261121.xml` |

Motivo de rodar no clone: outra sessão estava editando `src/**` no working tree principal
(214 entradas em `git status --porcelain`). O clone isola o commit.

---

## A1. Clone

```powershell
git clone --no-hardlinks H:\Desktop\ArtPlus $t
git -C $t rev-parse HEAD
git -C $t status --porcelain
```

| Comando | Saída-chave | Exit |
|---|---|---|
| `git clone --no-hardlinks` | `Cloning into ... done.` | **0** |
| `git rev-parse HEAD` | `4b174c3d96fd862b867e1aee3d2f7c6183ec8ccb` | **0** |
| `git status --porcelain` | 0 linhas | **0** |

**PASS** — clone limpo, HEAD exato, árvore sem modificação.

## A2. Configure do zero

`build/` removido antes do configure; `build_audit` do repo principal não foi usado nem lido
como input (apenas seu `CMakeCache.txt` foi consultado para identificar o mesmo compilador).

```powershell
& $cmake -S $t -B "$t\build" -G "MinGW Makefiles" `
  -DCMAKE_BUILD_TYPE=Release `
  -DCMAKE_PREFIX_PATH=C:/Qt/6.8.3/mingw_64 `
  "-DCMAKE_CXX_COMPILER=$m/g++.exe" `
  "-DCMAKE_MAKE_PROGRAM=$m/mingw32-make.exe"
```

Saída (trecho real):

```
-- The CXX compiler identification is GNU 16.2.0
-- Check for working CXX compiler: C:/Users/Evanei/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.POSIX.MSVCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/g++.exe - skipped
-- Found Threads: TRUE
-- Could NOT find WrapVulkanHeaders (missing: Vulkan_INCLUDE_DIR)
-- Configuring done (6.6s)
-- Generating done (1.2s)
```

Detecção de Qt, do `CMakeCache.txt` do clone:

```
Qt6_DIR:PATH=C:/Qt/6.8.3/mingw_64/lib/cmake/Qt6
Qt6Core_DIR:PATH=C:/Qt/6.8.3/mingw_64/lib/cmake/Qt6Core
Qt6Widgets_DIR:PATH=C:/Qt/6.8.3/mingw_64/lib/cmake/Qt6Widgets
CMAKE_CXX_COMPILER:STRING=C:/Users/Evanei/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.POSIX.MSVCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/g++.exe
```

**PASS** — exit **0**; compilador é POSIX.MSVCRT (não UCRT), Qt 6.8.3 mingw_64 resolvido.

## A3. Build completo

```powershell
& $cmake --build "$t\build" -j 6
```

| Métrica | Valor |
|---|---|
| Exit code | **0** |
| Tempo | **586,9 s** (~9 min 47 s, máquina fria, 6 jobs) |
| `error:` no log | 0 |
| `warning:` no log | 0 |
| Executáveis | **17** |

Artefatos (bytes):

| Executável | Tamanho |
|---|---|
| ArtPlus.exe | 1.534.299 |
| bearer_bar_test.exe | 1.104.989 |
| editing_test.exe | 1.083.992 |
| form_parser_probe.exe | 1.031.460 |
| form_transform_probe.exe | 1.028.655 |
| form_xobject_test.exe | 1.042.250 |
| integration_test_basic.exe | 1.053.219 |
| mirror_probe.exe | 1.023.908 |
| page_placeholders.exe | 1.024.954 |
| pdf_roundtrip_test.exe | 1.088.788 |
| pdf_smoke.exe | 1.030.886 |
| smask_probe.exe | 1.034.002 |
| test_cut_mark.exe | 1.125.005 |
| test_markset_processor.exe | 1.045.351 |
| test_save_document.exe | 1.085.759 |
| test_selection_mark.exe | 1.100.722 |
| unit_tests.exe | 1.170.757 |

**PASS** — 17/17 alvos linkados a partir de clone limpo, sem warning e sem erro.

## A4. CTest

```powershell
ctest --test-dir "$t\build" --output-junit "$t\ctest.xml" --output-on-failure
```

Exit **8** (= número de testes falhos; CTest retorna isso quando há falha — esperado).

| # | Teste | Resultado | Clone | Repo (`build_audit`) |
|---|---|---|---|---|
| 1 | FormXObjects | Passed | 0,23 s | 0,02 s |
| 2 | PdfSmoke | Passed | 0,33 s | 0,03 s |
| 3 | UnitTests | **Failed** | 0,67 s | 0,02 s |
| 4 | PdfRoundTrip | **Failed** | 0,63 s | 0,08 s |
| 5 | EditingTests | **Failed** | 0,54 s | 0,03 s |
| 6 | IntegrationTestBasic | **Failed** | 0,25 s | 0,06 s |
| 7 | MarkSetProcessor | Passed | 0,42 s | 0,02 s |
| 8 | BearerBarTests | **Failed** | 0,56 s | 0,05 s |
| 9 | CutMarkTests | Passed | 0,71 s | 0,05 s |
| 10 | SelectionMarkTests | Passed | 0,90 s | 0,04 s |
| 11 | SaveDocumentTests | Passed | 0,40 s | 0,08 s |

**6/11 passam** — matriz **idêntica** à esperada e à do repo principal
(`logs/ctest-full-20261121-1704.log`, mesma ordem, mesmas 5 falhas).

Exit codes dos binários falhos executados isoladamente (mesmo `PATH` do ctest):

| Binário | Exit | Observação |
|---|---|---|
| `unit_tests.exe` | 1 | imprime até `testColors passed.` e sai 1 sem mensagem — idêntico ao repo principal |
| `pdf_roundtrip_test.exe` | 4 | sem saída (4 falhas de 10, conforme `docs/testing/gates/README.md`) |
| `editing_test.exe` | 1 | sem saída |
| `integration_test_basic.exe` | 1 | sem saída |
| `bearer_bar_test.exe` | 1 | sem saída |

**PASS (como medição)** — a matriz reproduz exatamente o esperado. Nada foi ajustado.

## A5. Smoke do `ArtPlus.exe`

```powershell
$env:PATH = "C:\Qt\6.8.3\mingw_64\bin;" + $mingwBin + ";" + $env:PATH
$p = Start-Process -FilePath "$t\build\ArtPlus.exe" -PassThru -WorkingDirectory "$t\build"
```

| Instante | HasExited | MainWindowHandle | MainWindowTitle |
|---|---|---|---|
| T+2 s | False | 3738504 | `ArtPlus` |
| T+6 s | False | 3738504 | `ArtPlus` |
| T+8 s | False | 3738504 | `ArtPlus` |

`WorkingSet` 37,9 MB, 13 threads, PID 26480. Encerrado com `Stop-Process -Force`;
`ALIVE_AFTER_KILL=False` (sem processo órfão).

**PASS pelo critério forte**: processo vivo em 8 s **com `MainWindowHandle` não nulo
(0x390B88) e título `ArtPlus`** — a janela principal realmente foi criada, não é só
"processo não crashou".

## A6. Clone × repo principal (`build_audit`)

| Item | Clone `4b174c3` | `build_audit` | Diferença |
|---|---|---|---|
| Alvos linkados | 17 | 17 | **nenhuma** (conjuntos de nomes idênticos) |
| Build exit | 0 | 0 | nenhuma |
| Matriz ctest | 6/11 (5 falhas) | 6/11 (5 falhas) | **nenhuma** |
| Falhas | UnitTests, PdfRoundTrip, EditingTests, IntegrationTestBasic, BearerBarTests | idem | nenhuma |
| `unit_tests` output | igual até `testColors passed.`, exit 1 | idem | nenhuma |

Diferenças **não comportamentais**, todas explicadas:

1. **Tamanho dos binários**: delta de 29 a 1.053 bytes em 11 dos 17 `.exe`. Os `.obj` do
   clone embutem caminhos de origem mais longos
   (`C:/Users/Evanei/AppData/Local/Temp/opencode/artplus-clean-4b174c3/src/...` vs
   `H:/Desktop/ArtPlus/src/...`) em info de debug/`__FILE__`. Não é divergência de código.
2. **Tempo de execução dos testes**: 10–30× maior no clone (0,23–0,90 s vs 0,02–0,08 s).
   Binários recém-criados em diretório novo, primeira carga de DLL do Qt e varredura do
   antivírus. Não altera resultado.
3. **Tempo de build**: 586,9 s no clone (frio, `-j 6`) vs 17 min no `build_audit`
   (medição em contexto diferente). Sem relevância para o aceite.

**Nenhum achado de divergência entre clone e repo principal.**

---

## Achados

### AC-1 — Preset depende de caminho absoluto versionado (portabilidade)

`CMakePresets.json` (presente no clone, comitado) fixa:

```
C:/Users/Evanei/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.POSIX.MSVCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/g++.exe
```

Teste: `cmake --preset mingw-msvcrt -S <clone> -B <clone>/build_preset` → **exit 0**
(Qt e GCC detectados). Ou seja, **hoje funciona** nesta máquina, mas o preset quebra em
qualquer outro usuário/máquina e quebra aqui se o pacote winget for atualizado (o hash do
`Source_8wekyb3d8bbwe` muda). É exatamente o problema já listado em `AGENTS.md` §9
("Preset com caminho fixo do winget").

O configure manual do A2 **não precisou** de correção: passou `CMAKE_CXX_COMPILER` e
`CMAKE_MAKE_PROGRAM` explícitos + `CMAKE_PREFIX_PATH`, então o build em clone limpo não
depende do preset. **Não bloqueia I-5**, mas o preset segue não portátil.

### AC-2 — 5 falhas de teste são do commit, não do working tree

As mesmas 5 falhas ocorrem em clone limpo de `4b174c3`, com saída byte-idêntica à do repo
principal. Portanto são defeitos de código/teste **presentes no commit**, não sujeira local.
Causas já localizadas pela sessão principal (página default duplicada, export duplicando
objetos, BearerBar 5≠4, MarkSet sem asserção) permanecem válidas e continuam sendo trabalho
de `implementacao`/`testes`, não de build.

### AC-3 — `UnitTests` falha sem `<failure>` no JUnit

Confirmado no clone: `unit_tests.exe` retorna 1 após `testColors passed.` sem imprimir nada
e o JUnit não traz `<failure>` (o processo termina antes do `QTest::qExec` reportar). O gate
só registra exit code; a causa continua não instrumentada. Registrado para não virar
"ruído" — precisa de um caso explícito.

## Veredito

| Item | Estado |
|---|---|
| A1 clone + HEAD + árvore limpa | PASS |
| A2 configure do zero (MSVCRT + Qt 6.8.3) | PASS, exit 0 |
| A3 build completo, 17 alvos | PASS, exit 0, 0 warning |
| A4 ctest 6/11 | PASS conforme esperado |
| A5 smoke com janela criada | PASS (handle 3738504, título `ArtPlus`) |
| A6 clone == repo principal | PASS, sem divergência |

**I-5 FECHADO**: o HEAD `4b174c3` é buildável e testável a partir de um clone limpo, com a
mesma matriz de testes medida no repo principal, e o `ArtPlus.exe` abre a janela principal.
**A5 FECHADO** com evidência de janela, não apenas de processo vivo.

Ressalvas declaradas e não bloqueantes: AC-1 (preset não portátil), AC-2/AC-3 (5 falhas de
teste do commit, já conhecidas).
