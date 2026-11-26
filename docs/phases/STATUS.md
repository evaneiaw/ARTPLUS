# STATUS — estado do projeto ArtPlus

Atualizado: 2026-11-27 · Supervisor: `orquestrador` · Cobertura derivada de `python scripts/gate.py --inventory` (rc0, 11/11 coerente) e dos laudos em `docs/audit/`.

## Referência de versão

Esko ArtPro+ **v24.03.10017** (`C:\Esko\bg_prog_artpro+_v240`). Fonte única: `docs/agents/REFERENCE_VERSION.md`.

## Modo de operação

Desenvolvimento autônomo do núcleo (H:\Desktop\ArtPlus), isolamento total de ArtPlus-UI. Build Release real (`-O3 -DNDEBUG`) em `build_f008`, CTest 11/11.

## Estado comprovado

| Item | Estado |
|---|---|
| GATE 0 versão | ok (gate) |
| F-001 Cut Mark | **auditado** — `F-001-audit-20261124-final5.md`; `--stage audit` rc0 verificado 2026-11-25 (token vigente). Ressalvas produto: R6 fx; R7 geometria sintetizada; E5 fallback; campos orfaos orientation/repetition/lineTypes; serializacao .artplus; contradicao CAP |
| F-002 Mark Set | **auditado** — `F-002-audit-20261124-final5.md`; `--stage audit` rc0 verificado 2026-11-25 (token vigente). Ressalvas produto: consolidateSeparations stub; relink no-op; sem undo; identifyRelevantSets devolve tudo |
| F-003 Bearer Bar | **auditado** — `F-003-audit-20261124-final6.md`; `--stage audit` rc0 verificado 2026-11-25. Ressalvas: offset x R6; `0x180170C20` sem equiv v240; CAP v24 sem captura de criacao |
| F-004 Selection Mark | **fora-do-escopo-v24** — CAP-20261121-02 negativo (UI inexistente na v24) |
| F-005 Open Document | **auditado** — `F-005-audit-20261124-final5.md`; `--stage audit` rc0 verificado 2026-11-25. ADR-013+ADR-014; PdfRoundTrip pass; ctest 11/11 |
| F-006 Save Document | **auditado** — `F-006-audit-20261127c.md`; `--stage audit` rc0 verificado 2026-11-27 (token `EE90FF95BB9DF55E277FF28C279D244AC5611C1F829DB31E885B6058DFFF0325`). Rollback E10 resolvido (D4); artefato teste regenerado `F-006.test.json` (exit 0, SaveDocumentTests 1/1). Ressalvas: backup nome `.bak`; rollback falho |
| F-007 Step & Repeat | **bloqueado** (BLO-008) — existencia PROVADA (`CAP-20261124-01`); campos Make Grid NAO medidos (janela em branco) |
| F-008 Color Management | **auditado** — `F-008-audit-20261124-final5.md`; `--stage audit` rc0 verificado 2026-11-25. R3/R4/R5/R6 reais; lcms2/Pantone adiados (ADR-008) |
| F-009 Gerenciamento de Objetos | **auditado** — `F-009-audit-20261127.md` APROVADO COM RESSALVAS (token `4108E64EC7636A2067BA8A5653D9255AE6FE31C8F0F58AE586F79329E9C2D404`, `--stage audit` rc0 verificado 2026-11-27); ADR-016; código `src/document/object_manager.{h,cpp}` integrado no Document via unique_ptr; teste `test_object_manager.cpp` (F-009.test.json rc0) |
| F-010 Trapping | **auditado** — `F-010-audit-20261127b.md` APROVADO COM RESSALVAS (token `A8D35C4D6EFD6C336DF618DB06F7B6FCC56AE3B55B3733B9438747AEC36173C9`, `--stage audit` rc0 verificado 2026-11-27); código `src/prepress/trapping_flag.*` + integrações; teste TrappingTests em test_main.cpp (F-010.test.json rc0) |
| F-011 Automation Engine / DataCenter | **auditado** — `F-011-audit-20261127.md` APROVADO COM RESSALVAS (token `4ABCD24709DD7F200CD2D151AC0F0E2F385E62E210D983ACACE9DC639CAAFBD9`, `--stage audit` rc0 verificado 2026-11-27); ADR-017; código `src/prepress/automation_engine.{h,cpp}` (Adapter v1, 9 printing methods); teste `test_automation_engine.cpp` (F-011.test.json rc0) |
| Build Release `build_core_gate` | exit 0 (Release `-O3 -DNDEBUG`, 14:11:58) |
| CTest `build_core_gate` | **11/11** passed |
| `gate --inventory` | 0 (declarado == comprovado, após reconciliacao de 2026-11-25/2026-11-27) |

## Cobertura

- **auditado**: 9 (F-001/F-002/F-003/F-005/F-006/F-008/F-009/F-010/F-011 — `--stage audit` rc0 verificado 2026-11-25/2026-11-27)
- **testado**: 0
- **implementado**: 0
- **fora-do-escopo-v24**: 1 (F-004).
- **bloqueado**: 1 (F-007 — BLO-008, captura de campos do Make Grid).
- **spec**: 0
- **triado**: 0
- **analisado**: 0
- **Total rastreado**: 11 (F-001…F-011)

Detalhe em `docs/reverse-engineering/INVENTORY.md`, `FEATURE_MATRIX.csv`, `ROADMAP.md` e `docs/agents/CHECKPOINT.md`.

## Pendências (não bloqueiam auditoria)

1. **F-006**: rollback E10 resolvido (D4, laudo `F-006-audit-20261127c.md`); ressalva: backup nome `.bak`; rollback falho reporta `.bak`.
2. **F-003b**: zeragem silenciosa de `SizeReference` em runtime — **RESOLVIDA** (R-a do laudo F-003 fechado).
3. **F-007**: capturar os campos do diálogo `Make Grid` (janela em branca) e então escrever spec/ADR/teste (BLO-008, bloqueado por decisão do proprietário; **não redistribuir**).
4. **F-009**: ressalvas de produto — UI "Gerenciar Objetos" não existe na v24 (CAP-04 negativo); CAP-01/02/03 referenciam screenshots ausentes; setZOrder stub honesto `TODO(F-009)`; undo transacional fora do v1 (`p.undoable` ignorado); Scope::ThisLayer/OtherLayers não diferenciado.
5. **F-010**: ressalvas de produto — wiring `/Trapped`+`pdf:Trapped` em `src/pdf` não ligado (API TrappingManager exposta); sem efeito visual de trapping; menu Prepress > Trapping custom-drawn não acessível via UIA.
6. **F-011**: REA + Ghidra + CAP-20261126-01 concluídos; servidor AE real / Action Lists / campos login/UI conectada fora de escopo v1; spec §8.13 cita ADR-011 em vez de ADR-017 (corrigir em ciclo de doc).
7. Infra **corrigida em 2026-11-24**: token de auditoria não depende mais de `build.json` global; frescor por feature (spec `codigo:` + testes que citam), não por todo `src/`; parser de bloqueios por tabela; `--inventory`/`--all` sem traceback; `--json` válido; `preflight.py` criado.
8. Nenhuma reauditoria pendente nas features auditadas (rc 0 confirmado 2026-11-25 e 2026-11-27).
9. **Não confundir** funcionalidade Automation Engine/DataCenter com Action Lists (`NDLModelActionList.dll`) — fora de escopo do F-011 v1.
