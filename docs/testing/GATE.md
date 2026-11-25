# Gate de build, CTest e auditoria

Contrato operacional do `scripts/gate.py`. Todas as afirmações abaixo são verificáveis
por comando e deixam artefato em `docs/testing/gates/`.

> Estado do fluxo: **HALT ativo com escopo reduzido** (`docs/agents/HALT.md`). O HALT
> bloqueia **somente** as features da tabela `## Bloqueado` (hoje só `F-007`), conforme
> `AGENTS.md §10.1`. `--all` e `--halt` retornam `2` quando há escopo bloqueado;
> `--feature F-###` retorna `2` só se a feature estiver nesse escopo; `--build`,
> `--run-test`, `--emit-token`, `--selftest` e as verificações `--stage` retornam o
> veredito factual (0/1).

## Comandos

```powershell
python scripts/gate.py --build
python scripts/gate.py --feature F-001 --run-test
python scripts/gate.py --feature F-001 --emit-token
python scripts/gate.py --feature F-001 --stage code
python scripts/gate.py --feature F-001 --stage test
python scripts/gate.py --feature F-001 --stage audit
python scripts/gate.py --halt
python scripts/gate.py --feature F-001
python scripts/gate.py --all
python scripts/gate.py --all --json
python scripts/gate.py --inventory
python scripts/gate.py --selftest
```

Códigos: `0` aprovado, `1` reprovado, `2` escopo bloqueado/HALT (só para feature no
escopo, `--all`/`--halt`), `3` erro de uso/ambiente.

## Build (`--build`)

- Configura `build_audit` **somente** se `build_audit/CMakeCache.txt` não existir
  (`MinGW Makefiles`, Qt `C:/Qt/6.8.3/mingw_64`, g++ POSIX.MSVCRT descoberto no winget).
- Executa `cmake --build build_audit -j 6` com o CMake Kitware absoluto.
- Captura stdout+stderr em `docs/testing/gates/logs/build-<timestamp>.log`.
- Grava `docs/testing/gates/build.json`:

```json
{
  "timestamp": "2026-11-21T12:37:06-03:00",
  "command": ".../cmake.exe --build build_audit -j 6",
  "exit_code": 0,
  "log_path": "docs/testing/gates/logs/build-20261121-123703-025.log",
  "log_sha256": "8F21C11AE321272457F8BF9539EB578551A1D303728986DF44502F95470C920C",
  "build_dir": "build_audit",
  "configured": false,
  "configure_exit_code": null
}
```

- Retorna `0` somente com `exit_code == 0`.

> **Logs são evidência local, não fonte.** `docs/testing/gates/logs/*.log` (build e
> CTest) são gerados por `--build`/`--run-test` e **não são versionados** (continuam
> ignorados por `*.log`). Em clone limpo o GATE de código reprova com
> `build_dir inexistente`/`log de build ausente` até alguém rodar `--build`: o gate
> exige rebuild local. `build.json`, `build_dir` e log **não entram no token de
> auditoria**, então a reprodutibilidade do laudo não depende deles.

## Teste (`--feature F-### --run-test`)

- Mapeia feature → suíte em `CMakeLists.txt`:
  F-001 `CutMarkTests`, F-002 `MarkSetProcessor`, F-003 `BearerBarTests`,
  F-004 `SelectionMarkTests`, F-005 `PdfRoundTrip`, F-006 `SaveDocumentTests`.
  F-007/F-008 não têm suíte e retornam `3` com mensagem clara.
- Executa `ctest --test-dir build_audit --output-junit <ABS> --output-on-failure -R "^Suite$"`.
- **O `--output-junit` usa caminho absoluto.** Com `--test-dir`, o CTest reancora caminho
  relativo e o XML sairia em `build_audit/build_audit/...`. O gate valida a existência do
  XML **antes** de gravar o `.test.json`; XML ausente = reprovado.
- Grava `docs/testing/gates/F-###.test.json`:

```json
{
  "timestamp": "...",
  "feature": "F-001",
  "test_name": "CutMarkTests",
  "command": ".../ctest.exe --test-dir build_audit --output-junit H:\\...\\F-001.xml --output-on-failure -R ^CutMarkTests$",
  "exit_code": 0,
  "xml_path": "H:\\Desktop\\ArtPlus\\docs\\testing\\gates\\F-001.xml",
  "xml_sha256": "A27E...C803",
  "log_path": "docs/testing/gates/logs/test-F-001-....log",
  "tests": [{"name": "CutMarkTests", "status": "passed", "time": 0.047}],
  "failures": 0,
  "failure_details": []
}
```

- `xml_sha256` é o SHA-256 do XML realmente gerado nesta execução (o XML antigo é
  removido antes do CTest).
- Retorna `0` somente se `exit_code == 0`, `>= 1` teste e `0` falhas/pulados.

## Gate de código (`--stage code`)

Reprova se:

1. a spec não existe ou não declara arquivos `src/**`, ou arquivo declarado está ausente;
2. `build.json` ausente/inválido ou `exit_code != 0`;
3. `log_path` ausente ou `log_sha256` divergente;
4. `build.json` mais antigo que o arquivo mais recente sob `src/**`.

## Gate de teste (`--stage test`)

Reprova se:

1. nenhum teste cita o `F-###` ou o teste não tem asserção;
2. `F-###.test.json` ou o XML JUnit estão ausentes;
3. `exit_code != 0`, `failures > 0` ou nenhum teste registrado;
4. `xml_sha256` não confere com o XML real;
5. `F-###.test.json` mais antigo que o arquivo mais recente em `src/**` ou `tests/**`.

## Token de auditoria

```
token = SHA-256( sha256(F-###.test.json)
                 + sha256(docs/features/F-###.md)
                 + sha256(rag/evidence/F-###/manifest.json)
                 + sha256(src declarado no frontmatter `codigo:`)*
                 + sha256(tests/**/*.cpp que citam F-###)* )
```

`sha256(x)` é o hexadecimal maiúsculo; `(*)` é ordenado por caminho relativo.
`--feature F-### --emit-token` imprime o token. `--stage audit` exige code e test
verdes, laudo `docs/audit/F-###-audit*.md` com `Veredito` aprovado e **o token
exato**; token ausente/divergente = REPROVADO. Isso impede laudo aprovado sem
build/test realmente executados.

**`build.json` não entra no token.** Ele é artefato GLOBAL, reescrito por
qualquer `--build` de qualquer feature; incluí-lo fazia um build concorrente
invalidar o laudo de outra feature (AGENTS.md §10.7). O vigor do build continua
exigido pelo GATE de código (`--stage code`), que valida `build.json`, o log e
o `log_sha256` — só não contamina o token da auditoria.

O token é **endereçado por conteúdo**: muda quando `F-###.test.json`, a spec, o
manifest, um arquivo `src/` declarado pela feature ou um teste que cita a feature
é regenerado/editado. Um valor colado em laudo envelhece no próximo `--run-test`
ou edição da feature; sempre meça com `--emit-token`.

O frescor do laudo (`--stage audit`) é medido contra as dependências da própria
feature — `src/` declarado no `codigo:` da spec, testes que citam o `F-###`,
spec e manifest — e nunca contra todo o `src/`. Editar arquivo de outra feature
não invalida este laudo (AGENTS.md §10.7).

## `--all` e `--inventory`

- `--all` **não executa build nem CTest**; apenas lê os artefatos. Etapa de execução sem
  artefato aparece REPROVADA. Retorna `1` se qualquer etapa (`evidence`, `spec`, `adr`,
  `code`, `test`, `audit`) estiver vermelha, se o inventário estiver adiantado ou se a
  versão falhar. Com escopo bloqueado (`blocked_features()` não vazio) retorna `2`, mas
  **continua avaliando e imprimindo todas as features**.
- `--inventory` mede **apenas** a coerência entre estado declarado e estado comprovado.
  Retorna `0` somente quando `check_version` está ok e nenhum estado declarado supera o
  comprovado (`declarado > comprovado`, ou `bloqueado` sem registro em `BLOQUEIOS.md`).
  **Etapa vermelha não altera o código de saída do `--inventory`**: uma feature com
  build/teste/evidência reprovados e declarada no mesmo estado que o gate comprova
  (ex.: `triado`) mantém `--inventory` = `0`, enquanto `--all` = `1`. Sob HALT a
  inspeção continua permitida e o código reflete só a coerência do inventário.
- Ambos percorrem **todas** as features rastreáveis (INVENTORY + specs + diretórios de
  evidência), imprimem uma linha por feature no resumo (`--inventory`) e **nunca abortam**
  por estado derivado desconhecido: `bloqueado` e `fora-do-escopo-v24` são comparados por
  igualdade, não por índice em `STAGES`.
- `bloqueado` só é derivado da coluna **Feature** da tabela de bloqueios ativos de
  `docs/agents/BLOQUEIOS.md` (linhas `RESOLVIDO`/`SUPERADO` ignoradas) e da primeira
  célula da tabela sob `## Bloqueado` de `docs/agents/HALT.md`. Citar `F-###` em motivo,
  evidência ou caminho **não** bloqueia a feature.

## HALT (`--halt` e `--feature`)

- `--halt` imprime `HALT ATIVO — escopo bloqueado: F-007[, ...]` e retorna `2` quando
  `blocked_features()` não é vazio; caso contrário imprime `HALT inativo.` e retorna `0`.
  Nunca declara parada global.
- `--feature F-###` (sem `--stage`) retorna `2` **somente** se `F-###` estiver no escopo
  bloqueado; fora do escopo retorna o status factual normal (0/1). O banner de HALT
  continua informativo (em stderr quando `--json`).
- `--inventory` continua permitido sob HALT e retorna só a coerência do inventário.

## `--json`

Com `--json`, **stdout recebe apenas um objeto JSON válido**; todo texto humano (banner
HALT, GATE 0, blocos por feature, resumo do inventário, seção de órfãs e avisos) vai para
**stderr**. O exit code é o mesmo da execução humana. O objeto tem as chaves
`version_ok`, `version_details`, `features` e `orphans`. Exemplo:

```powershell
$j = python scripts/gate.py --all --json 2>$null | ConvertFrom-Json
$j.version_ok; $j.features.'F-007'.derived; $j.orphans
```

## Features órfãs (`orphan_features()`)

`--all` e `--inventory` procuram tokens `F-###` em `docs/agents/CHECKPOINT.md`,
`docs/phases/STATUS.md`, `docs/phases/REPOSITORY_RECONCILIATION.md` e `ROADMAP.md`
(só os existentes). É **órfã** a feature citada que não tem linha no `INVENTORY.md`,
nem `docs/features/F-###.md`, nem `rag/evidence/F-###/`. A seção

```
--- features órfãs (citadas, sem INVENTORY/spec/evidência) ---
  F-009  citada em docs/agents/CHECKPOINT.md:4
```

é **aviso de rastreabilidade**: não altera exit code. No JSON aparece como
`"orphans": {"F-009": "docs/agents/CHECKPOINT.md:4"}`.

## Pré-voo de sessão (`scripts/preflight.py`)

```powershell
python scripts/preflight.py
```

Imprime `PASS`/`FAIL` para: raiz canônica `H:/Desktop/ArtPlus`, branch `master`,
`check_version.py --strict` = 0. Informa (sem reprovar) a contagem de entradas de
`git status --short` e o `HEAD <sha>` com a data do último commit. Exit `0` só com
os três itens obrigatórios verdes. Uso previsto em `AGENTS.md` §10.5.

## `--selftest`

Cria repositórios temporários (nunca toca o repo real) e roda o próprio gate via
subprocesso com `ARTPLUS_GATE_REPO`. O fixture base tem duas features completas
(F-001 e F-008) com todos os gates verdes. Cenários (33): tudo ok; teste falho;
auditoria reprovada; HALT; CAP-BLOCKED; doc incompleta; inventário adiantado;
conclusão sem evidência; hash divergente; build não executado; teste não
executado; token divergente; build stale; build com `exit_code != 0`; test stale;
feature sem teste; inventário coerente com etapa vermelha; validade de
`F-###.test.json` por dependência (teste de F-001 não invalida F-008; `src/`
compartilhado invalida dependentes que o declaram; artefato antigo segue
rejeitado); e as regressões de bloqueio/token/HALT/JSON/órfãs:

- **bloqueio por escopo** — tabela com coluna `Feature` e `F-001` na célula:
  INVENTORY `bloqueado` ⇒ `--inventory` = 0; INVENTORY `auditado` ⇒ 1, sem
  traceback;
- **menção não bloqueia** — `F-001` citada só em motivo/caminho de uma linha cuja
  `Feature` é outra ⇒ não bloqueia;
- **bloqueio histórico** — linha `SUPERADO` com `F-001` na coluna `Feature` ⇒ não
  bloqueia;
- **HALT** — tabela sob `## Bloqueado` bloqueia; INVENTORY coerente ⇒ 0,
  divergente ⇒ 1;
- **fora do escopo** — `fora-do-escopo-v24` coerente (feature sem código/teste,
  com evidência+spec+ADR) ⇒ `--inventory` = 0;
- **token independe de build alheio** — trocar o conteúdo de `build.json` não
  muda o token (`--emit-token`) nem invalida o laudo (`--stage audit` = 0);
- **HALT por escopo** — HALT bloqueando F-001 e F-002: `--feature F-001`/`F-002` = 2,
  `--feature F-008` = 0, `--halt` imprime o escopo, `--all` = 2 com F-001 avaliada;
- **`--all --json`** — stdout parseável como JSON com `version_ok`/`features`/`orphans`,
  banner de HALT em stderr;
- **órfãs** — `CHECKPOINT.md` citando F-009 sem artefatos ⇒ aviso presente e
  `--inventory` = 0; com linha no INVENTORY ⇒ sem seção de órfãs.

Retorna `0` só com todos PASS. Um traceback no subprocesso conta como FAIL.

## Resultado real em 2026-11-21 (build_audit)

- `--build`: exit `0`.
- CTest por feature: F-001, F-002, F-004, F-006 passam; F-003 (BearerBarTests) e
  F-005 (PdfRoundTrip) falham — ver `F-003.test.json` / `F-005.test.json`
  (`exit_code` = `8` em ambos).
- CTest completo: **6/11 passam**. Falham: `UnitTests`, `PdfRoundTrip`, `EditingTests`,
  `IntegrationTestBasic`, `BearerBarTests`. Log: `docs/testing/gates/logs/ctest-full-20261121.log`.
- `UnitTests` sai com código `1` **depois** de `testColors` sem registrar `<failure>` no
  JUnit (anomalia do binário; não mascarada).
- `--selftest`: **17/17 PASS**.
- `--inventory`: exit `0` — as 8 features estão coerentes (5 `triado`, 3 `bloqueado`),
  apesar das etapas vermelhas; `--all` continua `2` por HALT e `--halt` = `2`.
- Hashes dos artefatos conferem: `log_sha256` de `build.json` e `xml_sha256` de
  `F-001..F-006.test.json` contra os arquivos reais.

Falhas de teste não são ruído: são devolvidas ao orquestrador com suíte e caso.
