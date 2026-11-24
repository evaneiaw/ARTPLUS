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

- **F-001 Cut Mark**: **auditado** (BLO-007 resolvido, 2026-11-23) — reauditoria `docs/audit/F-001-audit-20261123.md` APROVADA COM RESSALVAS (token `09CF8A4DC0D6C39C38D63D0C431F0B70888B483A07AA8C4A4977C241B5E62FC5`). BLO-007 resolvido: build global verde (Ninja, exit_code=0), token vigente aceito, GATE 6 auditoria ok. Ressalvas: R6/R7/E5, campos órfãos, serialização `.artplus`, ADR-001 desatualizada, contradição spec × CAP.
  Código em `src/prepress/cut_mark.*`; build isolado `build_f001` (alvo `test_cut_mark`) + `CutMarkTests` 1/1. Ressalvas: R6/R7/E5, campos órfãos, serialização `.artplus`, ADR-001 desatualizada, contradição spec × CAP sobre versão da captura; suíte completa e alvo `ArtPlus` não cobertos no build isolado.
- **F-002 Mark Set**: **auditado** (7 gates verdes) — `docs/audit/F-002-audit-20261122.md` (token `77B603A404E2523B6A273A7BC64AF2DDFDEBE47DAF1A983E6EA0E71F7CECA42F`).
  Spec `docs/features/F-002.md`, ADR `docs/decisions/ADR-003.md` (aprovado), código `src/prepress/markset_processor.*`.
  Build isolado `build_f002/` exit_code=0; `MarkSetProcessor` test passed.
  Lacunas declaradas: `identifyRelevantSets` vazio, sem undo, sem UI, sem loader PDF testado, sem marcas dinâmicas, camada achatada, sem separações.
- **F-003 Bearer Bar**: **auditado** (7 gates verdes) — `docs/audit/F-003-audit-20261122.md` (token `045B5CA7812AB9238CA18CD7E68CAC4E2B636BCFA9A1C81644643CF8919ED11C`).
  Lacunas: recapturar CAP na v24, implementar aplicação R5 (F-003b).
- **F-005 Open Document**: **auditado** (7 gates verdes, 2026-11-23) — `docs/audit/F-005-audit-20261123c.md` (token `DC5B57242995E6250A9B5438A23698F6C1EAA5512CE1477D579DBF9CBB4FFAA6`).
  Spec `docs/features/F-005.md`, ADRs `ADR-013` + `ADR-014` (autoriza R1/R2/R3/R4/R6/R8/R9/§5), código `src/document/**` (FileDispatcher/OpenError/handlers) + `src/pdf/**` (pdf_open_handler) + `src/ui/main_window.*` + `src/app/main.cpp`. Build isolado exit 0, ctest 11/11 + 18 casos Qt, 8 suítes novas, dossiê `dossiers/Document/`. Ressalvas não bloqueantes: R8/R9 por guarda estática, seção de implementação da spec pré-ADR-014, painéis prepress fora do escopo.
- **F-006 Save Document**: **bloqueada** (BLO-005) — criptografia não implementada, laudo reprovado.
- **F-007 Step & Repeat**: **bloqueada** (BLO-003) — sem CAP real, sem spec/ADR/teste.
- **F-008 Color Management**: **bloqueada** (BLO-004) — manifest ausente, ADR proposto, TODOs no código.
- **Extração contínua**: dossiês gerados por módulo, export Ghidra em `rag/ghidra/exports/`.
