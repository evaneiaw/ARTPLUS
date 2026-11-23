# ROADMAP - ArtPlus

> **Referência funcional:** Esko ArtPro+ **v24.03.10017** (`C:\Esko\bg_prog_artpro+_v240`).
> Fonte única da verdade: `docs/agents/REFERENCE_VERSION.md`.

## Fases do Projeto

1.  **FASE 1**: Ambiente, inventário e documentação.
2.  **FASE 2**: Arquitetura, agentes, skills, RAG e dependências.
3.  **FASE 3**: Modelo central de documento e engine PDF.
4.  **FASE 4**: Visualização, seleção, edição e transformação.
5.  **FASE 5**: Layers, Separations, cores e geometria.
6.  **FASE 6**: Pré-impressão e Quality Control.
7.  **FASE 7**: Marks, Step & Repeat e produção.
8.  **FASE 8**: Action Lists e automação.
9.  **FASE 9**: Recursos avançados e distribuição.

## Estado atual (2026-11-22)

- **F-001 Cut Mark**: auditado com ressalvas — `docs/audit/F-001-audit-20261121.md`.
  Código em `src/prepress/cut_mark.*`, `CutMarkTests` 12/12.
- **F-002 Mark Set**: **auditado** (7 gates verdes) — `docs/audit/F-002-audit-20261122.md` (token `77B603A404E2523B6A273A7BC64AF2DDFDEBE47DAF1A983E6EA0E71F7CECA42F`).
  Spec `docs/features/F-002.md`, ADR `docs/decisions/ADR-003.md` (aprovado), código `src/prepress/markset_processor.*`.
  Build isolado `build_f002/` exit_code=0; `MarkSetProcessor` test passed.
  Lacunas declaradas: `identifyRelevantSets` vazio, sem undo, sem UI, sem loader PDF testado, sem marcas dinâmicas, camada achatada, sem separações.
- **F-003 Bearer Bar**: **auditado** (7 gates verdes) — `docs/audit/F-003-audit-20261122.md` (token `045B5CA7812AB9238CA18CD7E68CAC4E2B636BCFA9A1C81644643CF8919ED11C`).
  Lacunas: recapturar CAP na v24, implementar aplicação R5 (F-003b).
- **F-005 Open Document**: auditado com ressalvas — `docs/audit/F-005-audit-20261121b.md`.
  Spec `docs/features/F-005.md`, ADR `docs/decisions/ADR-013`, código `src/document/**` + `src/pdf/**`.
- **F-006 Save Document**: **bloqueada** (BLO-005) — criptografia não implementada, laudo reprovado.
- **F-007 Step & Repeat**: **bloqueada** (BLO-003) — sem CAP real, sem spec/ADR/teste.
- **F-008 Color Management**: **bloqueada** (BLO-004) — manifest ausente, ADR proposto, TODOs no código.
- **Extração contínua**: dossiês gerados por módulo, export Ghidra em `rag/ghidra/exports/`.
