# STATUS — estado do projeto ArtPlus

Atualizado: 2026-11-23 20:20 · Supervisor: `orquestrador` · Cobertura derivada de `python scripts/gate.py --inventory` (F-001 bloqueado por BLO-007; demais estados em `docs/reverse-engineering/INVENTORY.md`).

## Referência de versão

Esko ArtPro+ **v24.03.10017** (`C:\Esko\bg_prog_artpro+_v240`). Fonte única:
`docs/agents/REFERENCE_VERSION.md`.

## Modo de operação

**Desenvolvimento autônomo** (ordem do proprietário, 2026-11-21/22).
O escopo ativo F-008 foi avançado pelo pipeline:
- Evidência v24 comprovada por gate (`[GATE 3 evidência] ok`, SHA-256 v24 `A8C268...B34`, 5 arquivos GHIDRA + `CAP-20261122-02`).
- BLO-004 marcado **RESOLVIDO**.
- Spec F-008 atualizada com UI real v24 (Colors panel + Recolor + Convert Separations) e declaração formal dos arquivos `src/color_management/`.
- ADR-008 aprovado.
- Implementação de `src/color_management/` concluída (13 arquivos).

## Estado comprovado

| Item | Estado |
|---|---|
| GATE 0 versão | ok (gate) |
| F-008 GATE 3 (evidência) | **ok** (5 GHIDRA IDs v24 resolvem + `CAP-20261122-02` resolve) |
| F-008 GATE 2 (spec) | **ok** (declarados 13 arquivos em `src/color_management/`) |
| F-008 GATE 2 (arquitetura) | **ok** (`docs/architecture/F-008-ADR.md` aprovado) |
| F-008 GATE 4 (código) | ok (target ColorManagement compila; gate completo bloqueado por build infra `smask_probe` antigo) |
| Bloqueios ativos | F-006 (BLO-005), F-007 (BLO-003). F-008 (BLO-004) resolvido. |

## Cobertura de funcionalidades

- **auditado**: F-002, F-003, F-005 (laudos aprovados com ressalvas).
- **fora-do-escopo-v24**: F-004 (Selection Mark ausente na v24.03.10017).
- **implementado**: F-001 (BLO-007 — build global concorrente reescreveu `build.json` com `exit_code=2`, invalidando laudo aprovado; aguardando estabilização).
- **bloqueado**: F-006 (BLO-005), F-007 (BLO-003).

Detalhe em `docs/reverse-engineering/INVENTORY.md`, `docs/agents/CHECKPOINT.md` e `FEATURE_MATRIX.csv`.

## Próximos passos

1. Executar auditor `auditor` → laudo F-008-audit.md.
2. Remover BLO-004 de `BLOQUEIOS.md` e `INVENTORY.md`.
3. Resolver build infrastructure (target `smask_probe_autogen` antigo).
4. Completar gates `test` e `audit` de F-008.