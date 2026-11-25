# AGENTS.md — contrato do projeto ArtPlus

ArtPlus é uma reimplementação funcional do Esko ArtPro+ em C++17/Qt 6.8.3.
Este arquivo define como os agentes trabalham. Em qualquer conflito, **este arquivo ganha**.

## 0. Versão de referência (regra absoluta)

A única referência válida do projeto é **Esko ArtPro+ v24.03.10017**, instalada em
`C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows`. Fonte única da verdade:
`docs/agents/REFERENCE_VERSION.md`.

- Nenhum documento, agente, comando, skill, script ou evidência ativa usa outra versão como referência.
- A versão `25.03.116` (`C:\Esko\bg_prog_artpro+_v250`) é **histórica e fora do fluxo ativo**;
  registros derivados dela são preservados para rastreabilidade, nunca como especificação/evidência da versão-alvo.
- Não alterar hashes, nomes de binário ou resultados históricos para simular evidência da v24.
- `scripts/check_version.py` valida esta regra e reporta `caminho:linha` de cada ocorrência.

## 1. Postura do projeto

- Engenharia reversa **profunda e declarada** do ArtPro+ (Ghidra + triagem + operação do original).
- O objetivo é **clone funcional completo**, não uma ferramenta inspirada.
- Toda funcionalidade implementada precisa de evidência rastreável; nada de "achismo" virando código.
- Decisão do proprietário do projeto: o ArtPlus é de uso próprio e não será distribuído como
  substituto do produto comercial. Responsabilidade de distribuição/licenciamento é de quem publicar.

## 2. Pipeline

```
ghidra ─┐
rea ────┼─► evidência bruta ─► documentacao ─► F-### ─► arquitetura ─► ADR
comportamento ─┘                                              │
                                                              ▼
                                                        implementacao
                                                              │
                                                              ▼
                                                           testes
                                                              │
                                                              ▼
                                                           auditor
```

Nenhuma etapa começa sem o artefato da anterior. O `auditor` tem veto.

## 3. Agentes e donos de diretório

| Agente | Modo | Escreve em | Não pode |
|---|---|---|---|
| `orquestrador` | primary | `ROADMAP.md`, `FEATURE_MATRIX.csv`, `docs/phases/**`, `docs/agents/**`, `docs/reverse-engineering/INVENTORY.md`, `AGENTS.md`, `opencode.jsonc`, `.opencode/agents/**`, `.opencode/commands/**`, `.opencode/skills/**` | editar `src/`, analisar binário, rodar shell fora do allowlist (git status/add/commit/push-master/log/diff/rev-parse/ls-remote/remote + `python scripts/{gate,check_version,preflight,status,validate_skills}.py`) |
| `ghidra` | subagent | `tools/ghidra_analysis/**`, `tools/ghidra_projects/**`, `docs/reverse-engineering/**`, `rag/evidence/**` | editar `src/`, `tests/`, specs |
| `rea` | subagent | `rag/evidence/**`, `rag/sources/**`, `docs/reverse-engineering/**` | editar `src/`, `tests/`, specs |
| `comportamento` | subagent | `tools/reference_capture/**`, `docs/behavior/**`, `rag/evidence/**` | editar `src/`, `tests/`, specs |
| `documentacao` | subagent | `docs/features/**`, `docs/glossary/**`, `rag/index/**`, `rag/metadata/**` | editar `src/`, evidência bruta |
| `arquitetura` | subagent | `docs/architecture/**`, `docs/decisions/**` | editar `src/`, `tests/` |
| `implementacao` | subagent | `src/**`, `CMakeLists.txt`, `tools/pdf_inspector/**` | editar `tests/`, `docs/`, `rag/` |
| `testes` | subagent | `tests/**`, `docs/testing/**`, `CMakePresets.json`, `scripts/**`, `tools/visual_compare/**`, `dossiers/**` | editar `src/` |
| `auditor` | subagent | `docs/audit/**` | editar qualquer outra coisa |

Nenhum subagente lança subagente. O `orquestrador` é o único que despacha.

> **Shell do `orquestrador`**: na config V2 (`.opencode/agents/orquestrador.md`) o shell é
> liberado por allowlist (`git` de inspeção/commit/push-master e os scripts de gate) e o limite é
> `steps`, não `maxSteps`. O orquestrador **não** usa `cd`/`&&` (o scanner avalia cada subcomando)
> e passa o diretório de trabalho na própria chamada. O limite de **3 subagentes ativos** é
> obrigatório, mas **não** é imposto automaticamente pelo runtime.

## 4. Identificadores e evidência

- Spec: `F-###` em `docs/features/F-###.md` (funcionalidade grande: `F-025a`, `F-025b`).
- Decisão: `ADR-###` em `docs/decisions/`.
- Evidência: `rag/evidence/F-###/` com subpastas `ghidra/`, `rea/`, `behavior/`.
- Todo achado estático é identificado como `GHIDRA-<modulo>-<endereco>`.
- Toda captura é identificada como `CAP-<AAAAMMDD>-<nn>`.

`rag/evidence/F-###/manifest.json` mínimo:

```json
{
  "id": "F-025",
  "versao_ref": "24.03.10017",
  "binario": "C:\\Esko\\bg_prog_artpro+_v240\\ArtPro+.app\\Contents\\Windows\\DocumentMarks.dll",
  "sha256": "...",
  "estatico": ["GHIDRA-DocumentMarks-0x18001A2C0"],
  "comportamental": ["CAP-20261118-03"],
  "bloqueios": []
}
```

## 5. Comandos canônicos

```powershell
# CMake correto (o do PATH é WinLibs UCRT e mistura CRT com o Qt)
$cmake = 'C:\Users\Evanei\AppData\Local\Microsoft\WinGet\Packages\Kitware.CMake_Microsoft.Winget.Source_8wekyb3d8bbwe\cmake-4.4.4-windows-x86_64\bin\cmake.exe'

& $cmake --preset mingw-msvcrt
& $cmake --build --preset release-mingw
& $cmake --build build --target ArtPlus
ctest --preset unit-tests
```

```powershell
# Ghidra 12.2 (exige JDK 25; JDK 21 falha)
$env:JAVA_HOME = 'C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot'
& 'H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat' `
  'H:\Desktop\ArtPlus\tools\ghidra_projects' 'ArtProPlus' -import '<binário>'
```

```powershell
# Triagem
diec -j <binário>
strings64 -n 8 <binário>
python scripts\inspect_pe.py <binário>
python scripts\scan_binary.py <diretório>
```

Alvos de referência:

```
v24.03.10017 (referência): C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows
v25 (histórico, fora do fluxo ativo): C:\Esko\bg_prog_artpro+_v250\ArtPro+.app\Contents\Windows
```

> **Instalação única do Ghidra:** `H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC`.
> Não baixe nem extraia outra versão. Os zips antigos foram removidos da área de trabalho.

## 6. Regras de ouro

1. **Evidência primeiro.** Spec sem evidência não vira ADR; ADR sem spec não vira código.
2. **Um dono por diretório.** Quem não é dono não escreve — pede ao orquestrador.
3. **Nada de "feito" sem comando reproduzível.** Relatório sem caminho + saída é relatório vazio.
4. **Estado real no roadmap.** Build quebrado aparece como quebrado.
5. **Uma sessão de GUI por vez.** O ArtPro+ é recurso único.
6. **Nada de stub silencioso.** `TODO(F-###)` é aceitável; função que finge funcionar não é.
7. **Unidade explícita.** `mm`, `pt`, `dpi` no nome do campo e na spec.
8. **Conflito de contrato** vai para `docs/agents/CONFLITOS.md` antes de virar código.
9. **Autonomia.** Decisões técnicas pertencem aos agentes; escalar só nos cinco casos da política (`docs/agents/AUTOPILOT.md` §9).
10. **Execução contínua com checkpoint.** O `/auto` continua até a fila elegível esgotar ou um limite real da sessão; a cada etapa concluída grava `docs/agents/CHECKPOINT.md`, e a retomada continua sem repetir trabalho.
11. **Estado bloqueado.** Feature em `docs/agents/BLOQUEIOS.md` vira `bloqueado` no `INVENTORY.md` e não é redistribuída até o bloqueio ser resolvido.
12. **EXISTENCE-FIRST.** Toda funcionalidade (menu, botão, atalho, diálogo) em qualquer agente/skill deve ser referenciada por evidência comportamental/estática da versão de referência (v24.03.10017). Evidência estática de binário, nome de classe ou roadmap não é prova de existência de UI/comportamento na v24.03.10017. Documentação histórica (v25) e inferências não autorizam implementação de UI. CAP negativo confirma ausência.

## 7. Estado atual do projeto

- Fase: inventário e reverse engineering (ROADMAP fase 1–2).
- Build: existem alvos de teste compilando; o link do `ArtPlus` já teve falha de toolchain
  (UCRT × MSVCRT), tratada pelo `build doctor` do agente `testes`.
- Módulos já mapeados em `docs/reverse-engineering/`: `Document.dll` (call graph, estruturas,
  workflows), inventário de binários, mapa de dependências e estratégia Ghidra.
- Fila de cobertura: `docs/reverse-engineering/INVENTORY.md`.
- Cobertura comprovada (2026-11-24, `gate.py --inventory`): F-001/F-002/F-003/F-005/F-008
  `testado`; F-006 `implementado`; F-004 `fora-do-escopo-v24`; F-007 `bloqueado` (BLO-008);
  F-009 órfã (sem INVENTORY/spec/evidência). **Nenhuma feature está `auditado`** — os laudos
  existentes têm token da fórmula antiga e precisam ser reemitidos/reauditados.
  Ver `FEATURE_MATRIX.csv` e `docs/phases/STATUS.md`.
- Referência de versão: **v24.03.10017** (ver §0 e `docs/agents/REFERENCE_VERSION.md`).

## 8. Skills

As 26 skills em `.opencode/skills/` são o conhecimento técnico por domínio. Todas têm
frontmatter `name` + `description` e são anunciadas ao modelo. Consulte antes de inventar
abordagem; a `description` da skill diz quando ela se aplica.

| Agente | Skills principais |
|---|---|
| `orquestrador` | `project-orchestration`, `github-workflow` |
| `ghidra` | `ghidra-analysis` |
| `rea` | `rea-reverse-engineering` |
| `comportamento` | `artpro-behavior-capture` |
| `documentacao` | `technical-specification` |
| `arquitetura` | `cpp-architecture-adr`, `qt-cpp-development` |
| `implementacao` | `qt-cpp-development`, `document-core`, `pdf-engineering`, `color-management` |
| `testes` | `build-and-release`, `test-strategy`, `visual-regression-testing` |
| `auditor` | `evidence-verification` |
| todos | `powershell-win-toolkit` + skills de domínio (trapping, marcas, layers, etc.) |

Skills de domínio: `prepress-trapping`, `marks-and-barcodes`, `layers-and-separations`,
`screening-and-halftone`, `selection-and-transform`, `step-and-repeat`, `vector-geometry`,
`preflight-quality-control`, `action-lists-automation`, `dependency-license-audit`.

## 9. Problemas conhecidos do ambiente

| Problema | Estado | Correção |
|---|---|---|
| `rea` MCP falhava: exigia Node ≥ 24.22.1; o Node do sistema é 24.13.1 | resolvido em 2026-11-18 | Node 26.13.1 portátil em `C:\Users\Evanei\.local\share\opencode\node-v26.13.1\node.exe`. Não troque o Node do sistema para "consertar" isso. |
| Instalação global do `rea-agents` tem addon nativo com SHA-256 divergente (`native\windows\build\rea-windows-x64.node`), o que **rejeita o provider Ghidra** | resolvido em 2026-11-18 | Cópia limpa em `C:\Users\Evanei\.local\share\opencode\rea-side`; o MCP `rea` e o agente `rea` usam essa cópia. Se o MCP ainda não expuser `ghidra`, reinicie o OpenCode. |
| `pc-control` MCP falhava: `desktop-control-mcp` 0.1.0 usa FastMCP, mas havia `mcp` 2.3.0 | resolvido em 2026-11-18 | `python -m pip install "mcp<2"` (agora 1.30.0). Não atualize `mcp` sem migrar o `desktop_control`. |
| `C:\RE-Tools` não existe | — | Use caminhos absolutos: Ghidra em `H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC`. |
| `analyzeHeadless.bat` pausa em erro | — | Rode via `Start-Process -RedirectStandardInput <arquivo vazio>` em background e leia o log. |
| `cmake` do PATH é WinLibs UCRT | — | Use o CMake Kitware absoluto (seção 5). |
| Preset com caminho fixo do winget | — | Primeira tarefa do agente `testes`: tornar a descoberta do GCC dinâmica. |

### Smoke test registrado

`DocumentMarks.dll` importado com sucesso no Ghidra 12.2/JDK 25 (`-noanalysis -deleteProject`),
log em `tools/ghidra_analysis/smoke.log`. Ambiente de análise validado.

## 10. Gates, HALT e estado comprovado (regra dura)

**Nenhuma etapa avança por declaração de agente.** O estado de cada `F-###` é derivado de
fatos verificáveis por `python scripts/gate.py`, nunca escrito à mão no `INVENTORY.md`.

### 10.1 HALT

- `docs/agents/HALT.md` é um **registro de bloqueios por escopo**, não uma trava global automática.
- Leia a tabela `Bloqueado` e impeça somente as features nela listadas e tarefas sem pré-condições.
- Features fora da lista podem avançar pelo pipeline normal, desde que os gates da etapa retornem `0`.
- Se o arquivo declarar explicitamente suspensão global, pare o pipeline de features e trabalhe apenas na recuperação indicada.
- Nunca remova nem amplie/reduza bloqueios por conta própria; isso exige autorização do proprietário.

### 10.2 Gate obrigatório

| Momento | Comando | Condição para seguir |
|---|---|---|
| Antes de qualquer despacho | `python scripts/gate.py --all` | GATE 0 versão e gates do alvo sem falha |
| Depois de `rea`/`ghidra` | `python scripts/gate.py --feature F-### --stage evidence` | evidência resolve e hash confere |
| Depois de `documentacao` | `... --stage spec` | spec completa e rastreável |
| Depois de `arquitetura` | `... --stage adr` | ADR aprovada citando F-### |
| Depois de `implementacao` | `... --stage code` | arquivos existem + build real |
| Depois de `testes` | `... --stage test` | teste cita F-### e passa |
| Depois de `auditor` | `... --stage audit` | laudo válido, não stale, aprovado |
| Antes de atualizar `INVENTORY.md` | `python scripts/gate.py --inventory` | estado declarado == estado comprovado |

- Gate reprovado **não é opinião**: é saída de comando com caminho e código de saída.
- Falha de gate volta para o dono da etapa, no máximo **2 tentativas**; a terceira vira
  bloqueio em `docs/agents/BLOQUEIOS.md` e a feature fica `bloqueado`.
- É proibido "aprovar com ressalvas" uma etapa cujo gate falhou. Ressalva só existe para
  lacuna **declarada e não bloqueante**, com evidência do que está comprovado.

### 10.3 Fatos que o gate exige

1. `versao_ref == 24.03.10017` em manifest e spec.
2. `sha256` do manifest confere com o binário real em `bg_prog_artpro+_v240`.
3. Todo `GHIDRA-*` resolve para arquivo em `rag/evidence/F-###/ghidra/`.
4. Todo `CAP-*` resolve para artefato de comportamento; `CAP-BLOCKED-*` **não** conta.
5. Nenhum placeholder (`0x...`, `MANUAL_PENDING`, `TBD`, `<...>`) em campo de evidência.
6. Laudo de auditoria existe, tem `Veredito`, registra build/teste e **não é mais antigo**
   que o código/evidência que pretende cobrir.
7. Teste cita o `F-###` e possui asserção; teste que não compila = `Not Run` = reprovado.

### 10.4 Concorrência e preservação

- Máximo **3 subagentes** ativos; nunca dois `comportamento` (GUI única).
- Proibido `git reset`, `git clean`, `rebase` ou `push --force` durante recuperação.
- Trabalho de outra sessão nunca é descartado: registrar e preservar.
- Sessões paralelas devem parar no HALT e entregar o estado real ao orquestrador.

### 10.5 Árvore canônica e pré-voo de sessão

Antes de qualquer despacho ou retomada, prove onde você está:

```powershell
git rev-parse --show-toplevel     # H:/Desktop/ArtPlus
git rev-parse --abbrev-ref HEAD   # master
git status --short                # WIP de outras sessões (não alterar)
git log -1 --format=%H
```

- Worktree, clone paralelo ou HEAD destacado é **cópia divergente**: pare e reporte. Foi assim que
  uma sessão inteira trabalhou por um dia em snapshot obsoleto e reportou trabalho já feito como
  "não iniciado".
- `scripts/preflight.py` (quando presente) automatiza essas checagens e imprime `PASS`/`FAIL`.
- O estado do projeto só é válido na árvore canônica; artefatos de gate de outra árvore não contam.

### 10.6 Escritor único do estado

- `INVENTORY.md`, `ROADMAP.md`, `FEATURE_MATRIX.csv`, `docs/phases/STATUS.md` e
  `docs/agents/CHECKPOINT.md`: **somente o orquestrador**.
- `docs/testing/gates/{build.json,F-###.test.json,*.xml}`: **somente** `python scripts/gate.py`.
- `docs/features/**` e `rag/index/**`: `documentacao`. `docs/audit/**`: `auditor`.
- Subagente reporta o que fez; se precisar de mudança de estado, pede ao orquestrador.
- Dois escritores no mesmo registro = o segundo apaga o primeiro (causou F-002 `testado` no corpo
  e `auditado` no resumo).

### 10.7 Build e artefatos compartilhados

- `build/` e `docs/testing/gates/build.json` são compartilhados entre sessões.
- Proibido `Remove-Item -Recurse -Force build` em árvore compartilhada. Use
  `ARTPLUS_GATE_BUILD_DIR=build_<escopo>` (auditoria: `build_audit_<F-###>`) e declare o diretório.
- Um build concorrente não pode invalidar laudo de outra feature: o frescor é medido pelos arquivos
  que a feature declara (`codigo:` na spec + testes que a citam), não por todo o `src/`.

### 10.8 Continuidade e handoff

- Limite de passos/contexto **não é conclusão**. É ponto de handoff.
- Todo subagente devolve: `HANDOFF`, `ARQUIVOS TOCADOS`, `ULTIMO COMANDO -> exit`, `PENDENTE`,
  `PROXIMO COMANDO`.
- Retomada não reinicia missão: lê `CHECKPOINT.md`, `git status --short`, `git log -1`, artefatos de
  gate e executa a próxima ação pendente.
- Implementação que chega ao limite entrega o que compila + a lista exata do que falta; nunca
  "compila parcialmente" nem stub para fechar a conta.

### 10.9 Prova de etapa

- Etapa concluída = `python scripts/gate.py --feature F-### --stage <etapa>` retorna `0` **e** o
  artefato existe no caminho declarado. Saída colada, exit code incluído.
- Relatório de subagente não é prova. O orquestrador reexecuta o gate antes de registrar estado.
- Laudo de auditoria sem token medido na própria sessão é REPROVADO.
