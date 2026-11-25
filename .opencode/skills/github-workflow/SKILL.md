---
name: GitHub Workflow
description: Versiona e publica o ArtPlus no repositório artplus-phase3 — commits por escopo com evidência, PR via gh, tags de release e higiene de artefatos grandes. Use antes de commitar, ao abrir PR, revisar diff, publicar tag ou auditar o histórico.
metadata:
  version: "2"
---

# Git e GitHub do ArtPlus

Repositório: `H:\Desktop\ArtPlus` → `https://github.com/evaneiaw/artplus-phase3`.
Conta `gh` autenticada: `evaneiaw` (escopos `repo`, `workflow`).

## Identidade do repositório (sempre antes de commitar)

```powershell
git rev-parse --show-toplevel      # deve ser H:/Desktop/ArtPlus
git rev-parse --abbrev-ref HEAD    # deve ser master
git log -1 --format="%H %cI %s"
```

Worktree, clone ou HEAD destacado é **cópia divergente**: não commite nela. Se o comando rodar em
outro diretório, use `git -C H:\Desktop\ArtPlus ...` — nunca assuma o cwd.

## Antes de qualquer commit

```powershell
git -C H:\Desktop\ArtPlus status --short --branch
git -C H:\Desktop\ArtPlus diff --stat
git -C H:\Desktop\ArtPlus diff -- . ':(exclude)build'
```

Confirme que o commit **não** contém:

- `build/`, `build_*/`, `*.obj`, `*.exe` gerado, `CMakeCache.txt`;
- `tools/ghidra_projects/` e `tools/ghidra_12.2_PUBLIC/` (já ignorados);
- `dossiers/`, `rag/ghidra/exports/`, `tools/test_documents/` (pesados);
- binários de `C:\Esko` (nunca entram no repositório);
- tokens, `.env`, credenciais.

`docs/testing/gates/logs/*.log` **é exceção**: o `build.json` referencia o log por `log_sha256`;
sem o log versionado o gate não reproduz em clone limpo. Mantenha a negociação `!docs/testing/gates/logs/*.log`
no `.gitignore`.

## Branches

| Tipo | Padrão | Uso |
|---|---|---|
| Estável | `master` | Sempre compila; é o destino dos commits do pipeline |
| Funcionalidade | `feature/F-025-trim-marks` | Opcional, quando o proprietário pedir PR |
| Análise | `analysis/documentmarks` | Evidência, triagem, Ghidra |
| Correção | `fix/ctest-path` | Build/teste, sem mudar contrato |

Política do projeto: o pipeline publica em `master` por commit coerente. **Não** faça
`rebase`, `reset --hard`, `clean -fd` nem `push --force`. Conflito se resolve preservando o
trabalho existente (merge local), nunca reescrevendo histórico.

## Commit

Formato: `<tipo>(<escopo>): <resumo no imperativo>`

Tipos: `feat`, `fix`, `docs`, `test`, `refactor`, `build`, `chore`, `revert`.
Escopo: módulo ou área (`document`, `pdf`, `marks`, `build`, `skills`, `agents`).

```
feat(marks): implementa trim marks com offset em mm

F-025 / DocumentMarks.dll
Evidência: GHIDRA-DocumentMarks-0x18001A2C0, CAP-20261118-03
Teste: ctest --preset unit-tests (12/12)
Gate: --stage audit -> 0
```

- **`git add` por caminho explícito.** `git add -A`/`git add .` é proibido: mistura WIP de outras
  sessões e artefatos gerados.
- Se o conjunto tocar arquivos de outra feature, commite só os caminhos do seu ciclo e registre o
  resto no relatório.
- Evite o padrão histórico `continue: roadmap execution ongoing` — não diz o que mudou nem permite auditoria.

## Publicação

```powershell
git -C H:\Desktop\ArtPlus push origin master
git -C H:\Desktop\ArtPlus ls-remote origin refs/heads/master   # confirme o SHA publicado
```

O SHA local (`git rev-parse HEAD`) e o do remoto (`ls-remote`) devem ser idênticos. Divergência =
não publique de novo sem investigar.

## Pull request (quando solicitado)

```powershell
git -C H:\Desktop\ArtPlus push -u origin feature/F-025-trim-marks
gh pr create --repo evaneiaw/artplus-phase3 --base master --fill
gh pr checks --watch
```

No corpo do PR: `F-###`, evidência usada, comandos de build/teste e saída, riscos e o que ficou fora.
PR sem comando reproduzível não é revisável.

## Release

```powershell
gh release create v0.1.0 --repo evaneiaw/artplus-phase3 --generate-notes --title "ArtPlus v0.1.0"
```

Tag só depois de: build limpo, `ctest` passando, smoke de inicialização e `docs/audit/` do escopo aprovado.

## Higiene de histórico

- Um commit = uma mudança coerente. Não misture skills, código e evidência no mesmo commit.
- Não reescreva histórico já publicado.
- `docs/EXECUTION_LOG.md` registra a sessão; o commit registra o diff. Não duplique um no outro.
- Antes de publicar, integre `origin/master` com merge (nunca rebase) e resolva conflito localmente.

## Referências

- `references/gh-recipes.md` — comandos de inspeção, PR, release e recuperação.
- `AGENTS.md` §3, §6 e §10 — donos de diretório, regras de ouro e concorrência.
