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

## Estado atual (2026-11-24)

- **F-001 Cut Mark**: **testado** — laudo `docs/audit/F-001-audit-20261124-final5.md` existente, mas com token antigo (fórmula anterior); reemitir `--emit-token` e reauditar restaura `auditado`. Evidência v240 (24 IDs GHIDRA, hash `E47328BD…0FA102`, CAP v24), build Release `build_core_gate`, `CutMarkTests` pass. Ressalvas: R6 (`fx`), R7 geometria sintetizada, E5 fallback, campos órfãos `orientation/repetition/lineTypes`, serialização `.artplus`, contradição de CAP; F-001a/b sem spec.
- **F-002 Mark Set**: **testado** — laudo `docs/audit/F-002-audit-20261124-final5.md` existente, token antigo; reemitir e reauditar. Evidência v240 (13 IDs + `CAP-20261121-03`), `MarkSetProcessor` pass. Ressalvas: `consolidateSeparations` stub, relink no-op, sem undo, `identifyRelevantSets` devolve tudo, `MissingPageBox` nunca emitida, E3 ausente, spec §8.1/§9 desatualizada, `.tmp` residual.
- **F-003 Bearer Bar**: **testado** — laudo `docs/audit/F-003-audit-20261124-final6.md` existente, mas a spec foi editada depois dele (stale) e o token mudou; reauditar. Correção R5/E3 aplicada (polaridade invertida; zeragem silenciosa de `SizeReference` em runtime). Ressalvas: offset×R6, `0x180170C20` sem equivalente v240, CAP v24 sem captura de criação, geometria sintética.
- **F-004 Selection Mark**: **fora-do-escopo-v24** — CAP-20261121-02 negativo (UI inexistente na v24); não implementar no núcleo. Spec reconciliada.
- **F-005 Open Document**: **testado** — laudo `docs/audit/F-005-audit-20261124-final5.md` existente, token antigo; reemitir e reauditar. ADR-013 + ADR-014; `src/document/**` + `src/pdf/**` + UI; `PdfRoundTrip` pass; ctest 11/11. Ressalvas: R8/R9 por guarda estática, spec pré-ADR-014, painéis prepress fora de escopo.
- **F-006 Save Document**: **implementado** — `F-006.test.json` é mais antigo que `src/document/document_model.cpp`; regenerar com `--run-test` e reauditar. Laudo `docs/audit/F-006-audit-20261124f.md` existe. CAP real `CAP-20261124-01` (Save/Save As observado na v24: menu File, diálogo `ArtPlus Files (*.artplus)`, gravação silenciosa); D1/D2/D3/E5 + rollback E10 (D4) corrigidos e testados (28 casos); spec v1 reduzida (criptografia do container FORA, flavours FORA, serializer JSON); ADR-006 aprovado. Ressalvas: rollback falho deixa o original no `.bak` (reportado); nome do backup `FUN_180095230`, formato `.artplus`.
- **F-007 Step & Repeat**: **bloqueada** (BLO-008) — existência PROVADA na v24 (`CAP-20261124-01`: `Prepress > Step & Repeat > Make Grid`, `Ctrl+Alt+G`); campos do diálogo não medidos (falha de render); `step_repeat` retorna "Not implemented"; sem spec/ADR/teste. Não implementar até capturar campos e escrever spec.
- **F-008 Color Management**: **testado** — laudo `docs/audit/F-008-audit-20261124-final5.md` existente, mas spec/CMake/teste mudaram depois dele e o token mudou; reauditar. Duplicata stub removida, `ColorManagement` linkada no `ArtPlus`, R3/R4/R5/R6 reais, teste 28 funções/121 asserções/0 `QVERIFY(true)`. Ressalvas: lcms2/Pantone adiados (Limitações 4–5), R7/R9 parciais por dependência declarada.
- **Build/testes**: Release real (`-O3 -DNDEBUG`) em `build_core_gate`, exit 0; CTest **11/11**. `gate --inventory` = 0 após a reconciliação de 2026-11-24 (declarado == comprovado).
- **F-009 Gerenciamento de Objetos**: **órfã** — citada em `CHECKPOINT.md` e `REPOSITORY_RECONCILIATION.md`, sem linha no INVENTORY, sem spec e sem evidência v24. Não é feature rastreada; primeiro passo é captura comportamental na v24 (`comportamento`), depois spec. `gate.py --inventory` a reporta como órfã.
- **Extração contínua**: dossiês gerados por módulo, export Ghidra em `rag/ghidra/exports/`.
