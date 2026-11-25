# STATUS — estado do projeto ArtPlus

Atualizado: 2026-11-24 · Supervisor: `orquestrador` · Cobertura derivada de `python scripts/gate.py --inventory` (gate corrigido nesta data) e dos laudos em `docs/audit/`.

## Referência de versão

Esko ArtPro+ **v24.03.10017** (`C:\Esko\bg_prog_artpro+_v240`). Fonte única: `docs/agents/REFERENCE_VERSION.md`.

## Modo de operação

Desenvolvimento autônomo do núcleo (H:\Desktop\ArtPlus), isolamento total de ArtPlus-UI. Build Release real (`-O3 -DNDEBUG`) em `build_f008`, CTest 11/11.

## Estado comprovado

| Item | Estado |
|---|---|
| GATE 0 versão | ok (gate) |
| F-001 Cut Mark | **testado** — `F-001-audit-20261124-final5.md` existe; token antigo, reemitir e reauditar |
| F-002 Mark Set | **testado** — `F-002-audit-20261124-final5.md` existe; token antigo, reemitir e reauditar |
| F-003 Bearer Bar | **testado** — `F-003-audit-20261124-final6.md` existe; spec editada depois do laudo (stale) |
| F-004 Selection Mark | **fora-do-escopo-v24** — CAP-20261121-02 negativo |
| F-005 Open Document | **testado** — `F-005-audit-20261124-final5.md` existe; token antigo, reemitir e reauditar |
| F-006 Save Document | **implementado** — `F-006.test.json` mais antigo que `src/document/document_model.cpp`; regenerar com `--run-test` |
| F-007 Step & Repeat | **bloqueado** (BLO-008) — existência provada; campos do Make Grid não medidos |
| F-008 Color Management | **testado** — `F-008-audit-20261124-final5.md` existe; spec/CMake/teste mudaram depois do laudo |
| F-009 Gerenciamento de Objetos | **órfã** — citada em CHECKPOINT/REPOSITORY_RECONCILIATION, sem INVENTORY/spec/evidência |
| Build Release `build_core_gate` | exit 0 (Release `-O3 -DNDEBUG`, 14:11:58) |
| CTest `build_core_gate` | **11/11** passed |
| `gate --inventory` | 0 (declarado == comprovado, após reconciliação de 2026-11-24) |

## Cobertura

- **auditado**: 0 (laudos existentes precisam ser reemitidos sob o token novo; reauditoria é ciclo de feature)
- **testado**: 5 (F-001, F-002, F-003, F-005, F-008 — `--stage test` verde, `--stage audit` vermelho)
- **implementado**: 1 (F-006 — regenerar `F-006.test.json`)
- **fora-do-escopo-v24**: 1 (F-004).
- **bloqueado**: 1 (F-007 — BLO-008, captura de campos do Make Grid).
- **órfã**: 1 (F-009 — sem INVENTORY/spec/evidência)

Detalhe em `docs/reverse-engineering/INVENTORY.md`, `FEATURE_MATRIX.csv`, `ROADMAP.md` e `docs/agents/CHECKPOINT.md`.

## Pendências (não bloqueiam auditoria)

1. **F-006**: rolback E10 resolvido (D4, laudo `F-006-audit-20261124f.md`); ressalvas de produto: nome do backup `FUN_180095230`, formato `.artplus`.
2. **F-003b**: zeragem silenciosa de `SizeReference` aplicada em runtime e testada — **RESOLVIDA** (R-a do laudo F-003 fechado em `F-003-audit-20261124-final5.md`).
3. **F-007**: capturar os campos do diálogo `Make Grid` (janela em branco) e então escrever spec/ADR/teste.
4. Ressalvas de produto (F-001/F-002/F-005/F-008) a fechar em ciclos próprios.
5. Infra **corrigida em 2026-11-24**: token de auditoria não depende mais de `build.json` global; frescor por feature (spec `codigo:` + testes que citam), não por todo `src/`; parser de bloqueios por tabela; `--inventory`/`--all` sem traceback; `--json` válido; `preflight.py` criado.
6. **Reauditoria**: F-001/F-002/F-003/F-005/F-008 precisam de `--emit-token` + laudo novo; F-006 precisa de `--run-test` antes.
7. **F-009**: capturar comportamento na v24 antes de qualquer spec (órfã).
