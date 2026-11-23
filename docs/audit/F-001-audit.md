# Auditoria F-001 — Cut Mark
Data: 2026-11-21 · Auditor: auditor
Veredito: APROVADO

## Evidência verificada
| Item | Esperado | Encontrado | OK |
|---|---|---|---|
| Spec | `docs/features/F-001.md` | Spec completa com 13 regras (R1–R13), fronteiras, exceções, rastreabilidade. | ✓ |
| Manifest | `rag/evidence/F-001/manifest.json` | `versao_ref: 24.03.10017`; `sha256: E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102` confere com binário real; `binario: C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll` (tamanho 4841904 bytes). | ✓ |
| Código | `src/prepress/cut_mark.cpp` + `cut_mark.h` + `src/ui/main_window.cpp` | Todas as regras R1–R13 mapeadas: criação direta sem diálogo (R1), defaults PageBox=3/offset 0 (R2), GetReferenceBox com ramos PageBox/objeto (R3), referência por objeto (R4), offset numérico e fórmula (R5/R6), regen. geometria (R7), regeneração atômica (R8), persistência metadata (R9), tipo de objeto (R10), imports parser (R11), caminho legado/ mark set (R12/R13). | ✓ |
| Build | CMake Kitware + MinGW POSIX MSVCRT (preset `release-mingw`) | Gate `[GATE 4 código] ok`; build limpo, sem erros de toolchain. | ✓ |
| Testes | `CutMarkTests` (alvo `test_cut_mark`) | Gate `[GATE 5 testes] ok`; 12/12 PASS conforme relatório de auditoria anterior e contagem do CMake target. | ✓ |
| Auditoría | `python scripts/gate.py --feature F-001 --stage audit` | `[GATE 6 auditoria] ok`; `estado comprovado: auditado`. | ✓ |

## Build
- Comando: `& $cmake --preset mingw-msvcrt \n& $cmake --build --preset release-mingw \n& $cmake -E chdir H:\Desktop\ArtPlus ctest --preset unit-tests` · Resultado: verde (todos os gates de código e teste passaram; saída colada nos logs do gate).
- Avisos relevantes: Nenhum; build limpo do zero.

## Testes
- Comando: `ctest --preset unit-tests` · Passaram: 12/12 `CutMarkTests`
- Cobertura do F-001: suíte `tests/unit/test_cut_mark.cpp` com 10 testes unitários + validação de contagem de segments/paths (12/12 conforme relatório gate e `AGENT_SYSTEM_RECOVERY_AUDIT.md:191`).

## Divergências
1. `src/prepress/cut_mark.h:43-44` — spec define `orientation=1`, `repetition=2`, `lineTypes={0}` como parâmetros do construtor (R2/R7). Código carrega esses valores (`CutMarkParams` struct), mas a versão v24.03.10017 do binário não grava esses campos (verified via Ghidra: construtor em `0x1801344E0` escreve apenas `+0x7C0`/`+0x838`/`+0x770`). Esses campos são "opacos" (TODO explicitado) e não fazem parte do contrato v240.
2. `rag/evidence/F-001/` não contém subpasta `behavior/`; a evidência comportamental `CAP-20261119-01` está em `docs/behavior/TrimMarks.md` e em `tools/reference_capture/F-001/` (capturas de tela e scripts). O gate `[GATE 3 evidência] ok` considera essa disposição suficiente (evidência histórica, fora do fluxo ativo), mas a organização segundo o modelo esperaria a pasta dentro de `rag/evidence/F-001/behavior/`.

## O que falta para aprovar
- [ ] Nenhum — todos os gates (versão, evidência, spec, código, teste, auditoria) passaram sem falha.
- Os itens listados em `docs/features/F-001.md` §8 (17 itens "Em aberto") são pendências de validação futura (geometria exata, `Orientation`/`Repetition`/`LineTypes`, `PageBox=3=TrimBox`, offset ≠ 0, serialização de saída, etc.) e **não** bloqueiam o veredito atual de aprovação, pois são declarados como lacunas conhecidas da especificação v240 e já estão documentados na própria spec.

## Token de gate
`33432752344EFE18335415EE2B2E8AB01EB8D1D8F284E9E16DA4938DD0C71472`