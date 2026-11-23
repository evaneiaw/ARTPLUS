# Gate de build, CTest e auditoria

Contrato operacional do `scripts/gate.py`. Todas as afirmações abaixo são verificáveis
por comando e deixam artefato em `docs/testing/gates/`.

> Estado do fluxo: **HALT ativo** (`docs/agents/HALT.md`). A infraestrutura de gate
> continua executável porque é correção do sistema de agentes, não avanço de feature.
> `--all` continua retornando `2` sob HALT; `--build`, `--run-test`, `--emit-token`,
> `--selftest` e as verificações `--stage` retornam o veredito factual (0/1) e imprimem
> aviso de HALT.

## Comandos

```powershell
python scripts/gate.py --build
python scripts/gate.py --feature F-001 --run-test
python scripts/gate.py --feature F-001 --emit-token
python scripts/gate.py --feature F-001 --stage code
python scripts/gate.py --feature F-001 --stage test
python scripts/gate.py --feature F-001 --stage audit
python scripts/gate.py --all
python scripts/gate.py --inventory
python scripts/gate.py --selftest
```

Códigos: `0` aprovado, `1` reprovado, `2` bloqueado/HALT, `3` erro de uso/ambiente.

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
token = SHA-256( sha256(build.json)
                 + sha256(F-###.test.json)
                 + sha256(docs/features/F-###.md)
                 + sha256(rag/evidence/F-###/manifest.json) )
```

`sha256(x)` é o hexadecimal maiúsculo. `--feature F-### --emit-token` imprime o token.
`--stage audit` exige code e test verdes, laudo `docs/audit/F-###-audit*.md` com
`Veredito` aprovado e **o token exato**; token ausente/divergente = REPROVADO. Isso impede
laudo aprovado sem build/test realmente executados.

O token é **endereçado por conteúdo**: muda sempre que qualquer um dos quatro arquivos
(`build.json`, `F-###.test.json`, `docs/features/F-###.md`, `manifest.json`) é regenerado
ou editado. Um valor colado em laudo ou em documento envelhece no próximo `--build` /
`--run-test`; sempre meça com o comando. Valor medido em **2026-11-21** para F-002:
`E4280480A05C44A3D4C3AED9342565D2308F5996586CBF66FFC93481BEEE29A1`
(`python scripts/gate.py --feature F-002 --emit-token`) — não é constante e vale só para
o estado corrente de `build.json`/`F-002.test.json`/spec/manifest.

F-001 não emite token hoje porque `rag/evidence/F-001/manifest.json` não existe — o gate
reporta `token impossível` em vez de inventar valor.

## `--all` e `--inventory`

- `--all` **não executa build nem CTest**; apenas lê os artefatos. Etapa de execução sem
  artefato aparece REPROVADA. Retorna `1` se qualquer etapa (`evidence`, `spec`, `adr`,
  `code`, `test`, `audit`) estiver vermelha, se o inventário estiver adiantado ou se a
  versão falhar; sob HALT retorna `2`.
- `--inventory` mede **apenas** a coerência entre estado declarado e estado comprovado.
  Retorna `0` somente quando `check_version` está ok e nenhum estado declarado supera o
  comprovado (`declarado > comprovado`, ou `bloqueado` sem registro em `BLOQUEIOS.md`).
  **Etapa vermelha não altera o código de saída do `--inventory`**: uma feature com
  build/teste/evidência reprovados e declarada no mesmo estado que o gate comprova
  (ex.: `triado`) mantém `--inventory` = `0`, enquanto `--all` = `1`. Sob HALT a
  inspeção continua permitida e o código reflete só a coerência do inventário.

## `--selftest`

Cria repositórios temporários (nunca toca o repo real) e roda o próprio gate via
subprocesso com `ARTPLUS_GATE_REPO`. Cenários (17): tudo ok; teste falho; auditoria
reprovada; HALT; CAP-BLOCKED; doc incompleta; inventário adiantado; conclusão sem
evidência; hash divergente; build não executado; teste não executado; token divergente;
build stale; build com `exit_code != 0`; test stale; feature sem teste; inventário
coerente com etapa vermelha (declarado `triado` + manifest com `sha256` divergente ⇒
`--inventory` = `0` e `--all` = `1`). Retorna `0` só com todos PASS.

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
