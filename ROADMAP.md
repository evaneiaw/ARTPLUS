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

## Estado atual (2026-11-27)

- **F-001 Cut Mark**: **auditado** — laudo `docs/audit/F-001-audit-20261124-final5.md`; `--stage audit` rc0 verificado (token vigente). Evidência v240 (24 IDs GHIDRA, hash `E47328BD…0FA102`, CAP v24), build Release `build_core_gate`, `CutMarkTests` pass. Ressalvas: R6 (`fx`), R7 geometria sintetizada, E5 fallback, campos órfãos, serialização `.artplus`.
- **F-002 Mark Set**: **auditado** — laudo `docs/audit/F-002-audit-20261124-final5.md`; `--stage audit` rc0 verificado. Evidência v240 (13 IDs + `CAP-20261121-03`), `MarkSetProcessor` pass. Ressalvas: `consolidateSeparations` stub, sem undo, `.tmp` residual.
- **F-003 Bearer Bar**: **auditado** — laudo `docs/audit/F-003-audit-20261124-final6.md`; `--stage audit` rc0 verificado. Correção R5/E3 aplicada. Ressalvas: offset×R6, geometria sintética.
- **F-004 Selection Mark**: **fora-do-escopo-v24** — CAP-20261121-02 negativo (UI inexistente na v24).
- **F-005 Open Document**: **auditado** — laudo `docs/audit/F-005-audit-20261124-final5.md`; `--stage audit` rc0 verificado. ADR-013 + ADR-014; ctest 11/11. Ressalvas: R8/R9 por guarda estática, painéis prepress fora de escopo.
- **F-006 Save Document**: **auditado** — laudo `docs/audit/F-006-audit-20261127b.md`; `--stage audit` rc0 verificado. `F-006.test.json` (28/28 testes), CAP-20261124-01. Ressalvas: rollback falho deixa `.bak` não removido.
- **F-007 Step & Repeat**: **bloqueado** (BLO-008) — aguarda captura de campos Make Grid.
- **F-008 Color Management**: **auditado** — laudo `docs/audit/F-008-audit-20261124-final5.md`; `--stage audit` rc0 verificado. R3/R4/R5/R6 reais. Ressalvas: lcms2/Pantone adiados, R7/R9 parciais.
- **F-009 Gerenciamento de Objetos**: **auditado** — laudo `docs/audit/F-009-audit-20261127.md`; `--stage audit` rc0 verificado. Codificado em `src/document/object_manager.h/.cpp` (ADR-016). Testes `test_object_manager.cpp` passam. NOTA: CAPs referenciam screenshots ausentes, mas não impede auditoria.
- **F-010 Trapping**: **auditado** — laudo `docs/audit/F-010-audit-20261126.md` APROVADO COM RESSALVAS (token `A8D35C4D6EFD6C336DF618DB06F7B6FCC56AE3B55B3733B9438747AEC36173C9`); `--stage audit` rc0 verificado. Ressalvas: wiring `/Trapped` desconectado, sem efeito visual, menu custom-drawn.
- **F-011 Automation Engine / DataCenter**: **auditado** — laudo `docs/audit/F-011-audit-20261127.md`; `--stage audit` rc0 verificado. ADR-017 aprovada, código `src/prepress/automation_engine.h/.cpp`. Testes passam. Ressalvas: conexão real, campos de login/UI conectada fora de escopo v1.
- **Build/testes**: Release (`-O3 -DNDEBUG`) em `build_core_gate`, exit 0; CTest **11/11**. `gate --inventory` = 0 (declarado == comprovado).
