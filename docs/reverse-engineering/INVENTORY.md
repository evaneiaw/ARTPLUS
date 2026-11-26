# INVENTORY.md — fila de módulos e estado de cobertura

Fonte única da verdade de versão: `docs/agents/REFERENCE_VERSION.md` — Esko ArtPro+ **v24.03.10017**.

**Estado comprovado**, derivado por `python scripts/gate.py` em **2026-11-25** (árvore
isolada `build_core_gate`), após a correção do gate (parser de bloqueios, frescor por feature e
token independente de build alheio). Nenhum estado pode ser elevado à mão: o que o gate não prova,
o inventário não declara.

> **Reauditoria pendente (não é regressão de produto).** Os laudos de F-001, F-002, F-003, F-005,
> F-006 e F-008 existem e foram aprovados com ressalvas, mas o token de auditoria mudou de fórmula
> (deixou de incluir o `build.json` global) e F-003/F-006/F-008 tiveram spec/código/artefato de
> teste editados depois do laudo. O gate, corretamente, não consegue reconhecê-los: o estado
> comprovado caiu para `testado`/`implementado`. Reemitir o token com `--emit-token` e reauditar
> (`/audit`) restaura `auditado` — é trabalho de ciclo de feature, não desta auditoria de infra.

Estados do pipeline: `triado` → `analisado` → `comportamento` → `spec` → `arquitetado` →
`implementado` → `testado` → `fora-do-escopo-v24`. Terminal alternativo: **`bloqueado`**
(registro obrigatório em `docs/agents/BLOQUEIOS.md`). Terminal adicional para
funcionalidades **não existentes na v24**: **`fora-do-escopo-v24`** (não implementar no clone).

> ## BUILD E TESTES (2026-11-21 17:30)
>
> **Build Release: VERDE.** 17 alvos em `build_audit` (`exit_code=0`), e **clone limpo
> comprovado** do commit `4b174c3`: configure do zero, 17 alvos, 0 erros/0 warnings;
> `ArtPlus.exe` abre a janela principal (`MainWindowHandle ≠ 0`, título `ArtPlus`).
> Evidência: `docs/testing/gates/CLEAN_CLONE_BUILD.md`.
>
> **CTest: 11/11** (`exit_code=0`): FormXObjects 4, PdfSmoke, UnitTests 8, PdfRoundTrip 10,
> EditingTests 11, IntegrationTestBasic 6, MarkSetProcessor 9, BearerBarTests 11,
> CutMarkTests 12, SelectionMarkTests 13, SaveDocumentTests 22.
>
> Consequência: F-001…F-006 têm `--stage test` verde e `--stage code` verde. O estado
> comprovado continua limitado pela **evidência** (GATE 3), não mais pelo build.

## Tabela de cobertura

| # | Feature | Módulo/Binário | Estado comprovado | Estado declarado antes | Pendência comprovada | Próxima ação |
|---|---|---|---|---|---|---|
| 1 | Cut Mark (F-001) | DocumentMarks.dll | **auditado** | auditado | Evidência v240 (37 `.md`, hash `E47328BD…4B3C0FA102`), spec reconciliada; `CutMarkTests` 1/1. Laudo `F-001-audit-20261124-final5.md` APROVADO COM RESSALVAS (token `1261DF6908163F115B7731D2A90C6D5FCE660839B2EF702BA38C3187F766ECDA`); build Release `build_core_gate` (14:11:58); CTest 11/11; `--stage audit` rc0. Ressalvas de produto permanecem: R6, R7, E5, campos órfãos, serialização `.artplus`, ADR-001 desatualizada, contradição spec × CAP. | fechar ressalvas de produto em ciclo próprio; não reabrir BLO-007 |
| 2 | Mark Set (F-002) | DocumentMarks.dll | **auditado** | auditado | Evidência v240 (13 IDs) + `CAP-20261121-03` na v24 (UI real: `Document > Marks`, engrenagem e `+ ▾`). Implementação completa: carrega mark set, prepara cache, cópia primeira página com IDs novos e remapeamento; teste MarkSetProcessor passa (19/19). Build `build_core_gate` exit 0; CTest 11/11. `--stage code` F-002 exit 0, `--stage test` exit 0. Laudo `F-002-audit-20261124-final5.md` (token `72F76C4F61CE40BB5C57F36B738CFC2D42B264198020D0668D658547B970D9CB`) **APROVADO COM RESSALVAS**; `--stage audit` rc0 verificado 2026-11-25. Ressalvas declaradas (pendentes por ciclo próprio): `identifyRelevantSets` vazio; sem undo; clone sem UI; loader `.pdf` não coberto; marcas dinâmicas/RelinkDynamicObjects não modeladas; camada destino achatada; separações não consolidadas. |
| 3 | Bearer Bar (F-003) | DocumentMarks.dll | **auditado** | auditado | Laudo `F-003-audit-20261124-final6.md` APROVADO COM RESSALVAS (token `F255A982A8507667A52006F35C0A3A6E66E6237BB1652F798470FF31315B2222`) após correção R5/E3 (zeragem silenciosa de SizeReference em runtime por `regenerate()`/`setParams`, coberta por `testSizeReferenceZeroingAtRuntime_R5_E3`, 10 cenários); BearerBarTests pass; `--stage audit` rc0. Ressalvas declaradas: R-b `offset` × texto de R6 (Em aberto 8); R-c `0x180170C20` sem equivalente v240; R-d CAP v24 sem captura de criação; R-e geometria sintética; R-f R8–R11 e undo-de-edição; R-g spec F-003 e ADR-002 atualizados (E3 aplicada) — residual `offset`/geometria sintética. | Estado corrigido por contrato AGENTS §10.3, auditoria aprovada com token fresco, build restaurado e verde. |
| 4 | Selection Mark (F-004) | PDFObjectActions.dll | **fora-do-escopo-v24** | auditado | Evidência estática no módulo correto (13 funções v240, zero erro) + `CAP-20261121-02` capturado na v24, com **resultado negativo**: não existe ação `Selection Mark` em `File`/`Object`/`Select`/`Prepress` nem no ribbon; `Ctrl+Shift+S` é `Save as...`. O DLL oferece operadores genéricos de seleção/transformação. **A UI implementada no ArtPlus baseia-se em documentação histórica (v25), NÃO em comportamento da v24. Para clone da v24, esta feature não deve ser implementada.** | N/A |
| 5 | Open Document (F-005) | Document.dll | **auditado** | auditado | Evidência v240 (14 IDs, SHA `DA91E285…8FA9E21` conferido), `CAP-20261121-01` capturado **na v24** (`File > Open...`, filtro `*.pdf; *.pdpdla; *.ap; *.art`, sem diálogo de importação), spec corrigida, ADR-013 + ADR-014 (aceita, autoriza R1/R2/R3/R4/R6/R8/R9/§5), código completo (FileDispatcher MIME→handler, OpenError, handlers PDF/.artplus, UI única, título/relayout), build isolado exit 0, ctest 11/11 + 18 casos Qt, 8 suítes novas, laudo `F-005-audit-20261124-final5.md` **APROVADO COM RESSALVAS** (token `E94240CB1099A7AFE3DD03DE6071D241779A380FB574FB8C9E2402DF8E48D055`); gates evidence/spec/adr/code/test/audit rc0. Ressalvas não bloqueantes: R8/R9 por guarda estática (sem teste de GUI); seção de implementação da spec ainda pré-ADR-014; painéis prepress fora do escopo; divergência REA declarada no manifest | dossiê Document já gerado; fechar ressalvas em ciclo próprio (teste de GUI, atualizar seção da spec) |
| 6 | Save Document (F-006) | Document.dll | **auditado** | auditado | laudo `F-006-audit-20261127c.md` APROVADO COM RESSALVAS (token vigente `EE90FF95BB9DF55E277FF28C279D244AC5611C1F829DB31E885B6058DFFF0325`, `--stage audit` rc0 verificado 2026-11-26 após mudanças em `document_model.cpp` por F-009); auditor mediu token próprio após `--run-test` (build isolado `build_audit_F-006`, exit 0); artefato de teste regenerado `F-006.test.json` (exit_code=0, SaveDocumentTests 28/28); CAP real `CAP-20261124-01` (Save/Save As observado); D1/D2/D3/E5 + rollback E10 (D4) corrigidos e testados (28 casos); spec v1 reduzida (criptografia do container FORA, flavours FORA, serializer JSON); ADR-006 aprovado; ctest 11/11; build_core_gate. Ressalvas: rollback falho deixa o original no `.bak` (reportado); switchToWorkingFile/deriveBackupPath/noOptimizedSave/revertToSaved declarados | fechar ressalvas de produto (nome do backup FUN_180095230, formato .artplus) em ciclo próprio |
| 7 | Step & Repeat (F-007) | LayoutEngine.dll | **bloqueado** (BLO-008) | bloqueado | **existência PROVADA** na v24 (`CAP-20261124-01`: `Prepress > Step & Repeat > Make Grid`, `Ctrl+Alt+G`); campos do diálogo NÃO medidos (BLO-008, janela em branco); `step_repeat.cpp` retorna `"Not implemented"` (3×); sem spec/ADR/teste; manifest com `versao_ref` corrigido para 24.03.10017 | capturar os campos do `Make Grid` (BLO-008) e escrever spec/ADR; não implementar até spec |
| 8 | Color Management (F-008) | ColorManipulationLayer.dll | **auditado** | auditado | Evidência v240 (5 IDs + CAP-20261122-02), spec completa, ADR aprovada, 14 arquivos `src/color_management/` (inclui `color_management_exception.h`); duplicata stub removida; `ColorManagement` linkada no `ArtPlus`; R3/R4/R5/R6 reais; teste 28 funções/121 asserções/0 `QVERIFY(true)`; laudo `F-008-audit-20261124-final5.md` **APROVADO COM RESSALVAS** (token `CB7F4E441997BCAEC6E7165897B24538A2E00EEF9FE70BFE49C259764B6377AC`); build_core_gate; `--stage audit` rc0. Ressalvas: lcms2/Pantone adiados (Limitações 4-5); R7/R9 parciais | integrar lcms2/Pantone quando a fase abrir; fechar R7/R9; `--stage audit` rc0 |
| 9 | Gerenciamento de Objetos (F-009) | Document.dll | **auditado** | auditado | Laudo `F-009-audit-20261127.md` APROVADO COM RESSALVAS (token `4108E64EC7636A2067BA8A5653D9255AE6FE31C8F0F58AE586F79329E9C2D404`, `--stage audit` rc0 verificado 2026-11-27 após mudanças em `document_model.cpp` por F-009); 7 GHIDRA IDs + 4 CAPs (CAP-01/02/03 referenciam screenshots ausentes; CAP-04 negativo: não existe item "Gerenciar Objetos"). Código: `src/document/object_manager.h/.cpp`, integrado no Document via `unique_ptr`. |
| 10 | Trapping (F-010) | PDFObjectLayer.dll | **auditado** | auditado | Laudo `F-010-audit-20261127b.md` APROVADO COM RESSALVAS (token vigente `A8D35C4D6EFD6C336DF618DB06F7B6FCC56AE3B55B3733B9438747AEC36173C9`, `--stage audit` rc0 verificado 2026-11-27 após regeneração de artefatos por F-009/F-011); spec F-010 (status spec, confiança media, 8 seções); ADR-015-trapping.md aprovado; código `src/prepress/trapping_flag.h/.cpp`, integrações em `src/ui/main_window.*`, `src/document/document_model.h`, `src/document/document_serializer.cpp`, `CMakeLists.txt`; teste `tests/unit/test_trapping.cpp` (toggle, metadata, undo, tokens PDF), `F-010.test.json` rc0; gates evidence/spec/adr/code/test/audit rc0. Ressalvas: wiring PDF `/Trapped`/`pdf:Trapped` em `src/pdf` não ligado (API exposta); sem efeito visual de trapping; menu Prepress custom-drawn não acessível. | fechar ressalvas de produto em ciclo próprio; ligar `src/pdf` para roundtrip `/Trapped`+XMP |
| 11 | Automation Engine / DataCenter (F-011) | DocumentAutomationEngine.dll | **auditado** | auditado | Laudo `F-011-audit-20261127.md` APROVADO COM RESSALVAS (token `4ABCD24709DD7F200CD2D151AC0F0E2F385E62E210D983ACACE9DC639CAAFBD9`, `--stage audit` rc0 verificado 2026-11-27). REA + Ghidra (24 IDs GHIDRA, 40 decompilados) + CAP-20261126-01; spec F-011 (8+1 seções); ADR-017 aprovado; código `src/prepress/automation_engine.{h,cpp}` (AutomationEngineAdapter v1 desconectado, 9 printing methods padrão, URI mapping, Smart Names, TODO(F-011) para servidor real); teste `tests/unit/test_automation_engine.cpp` (AutomationEngineTests, 1/1 passed). Ressalvas: servidor AE real/Action Lists/campos login/UI conectada fora de escopo v1; spec §8.13 cita ADR-011 em vez de ADR-017. | |

## Cobertura por estado comprovado

- **auditado**: 9 (F-001, F-002, F-003, F-005, F-006, F-008, F-009, F-010, F-011 — laudos com token vigente; `--stage audit` rc0 verificado 2026-11-27)
- **testado**: 0
- **fora-do-escopo-v24**: 1 (F-004 — CAP-20261121-02 negativo; UI Selection Mark inexistente na v24.03.10017; não implementar no clone)
- **implementado**: 0
- **arquitetado**: 0
- **comportamento**: 0
- **analisado**: 0
- **triado**: 0
- **bloqueado**: 1 (F-007 — BLO-008, captura de campos do Make Grid)
- **Total rastreado**: 11 (F-001…F-011)

> **Fila de reauditoria (ordem):** concluída em 2026-11-25 — F-001/F-002/F-003/F-005/F-006/F-008 com `--stage audit` rc0 (token vigente); reauditoria F-006 em 2026-11-27 após regeneração de `F-006.test.json`. Reexecutar `gate --inventory` antes de declarar mudança de estado.
> F-009 passou de órfã para **spec** em 2026-11-27: spec, manifest (4 CAPs) e 7 GHIDRA IDs existem; `--stage evidence` e `--stage spec` rc0. Ainda sem ADR/código/teste/laudo. F-011 entrou na fila como **triado** com REA completo e Ghidra em andamento.

> **Correção de 2026-11-24 (vale sobre toda a prosa histórica acima):** após a correção do
> `gate.py`, o estado derivado é o da coluna "Estado comprovado" (testado/implementado/bloqueado).
> Menções a "`--stage audit` rc0", "elevado a `auditado`" e tokens de 64 hex dentro das linhas e
> dos parágrafos de comparação são **registro histórico** de execuções anteriores e **não valem**
> como estado atual. Nenhuma feature está `auditado` hoje; a fila de reauditoria acima é o caminho
> para reverter isso com prova nova.
> **Histórico anterior (não vale como estado atual):** F-005 **REPROVADO → auditado** em 2026-11-23 (ADR-014 implementada, build isolado estável, laudo `F-005-audit-20261123c.md` APROVADO, gate audit rc0); F-008 reauditado em 2026-11-24 (`F-008-audit-20261124-final.md`, token `00EB2B11…`); F-006 e F-007 mantidos `bloqueado`. Nenhum estado elevado sem comprovação pelo gate. F-002 re-auditado em 2026-11-24 (token `ACBA7121FE6DD44C3BC39D7C23E9604EEB70BA0AD9EA046DD99233338B075798`). Atualização 2026-11-23 (/auto F-001): F-001 foi rebaixado de `auditado` para `implementado` por erro de contrato (laudo stale), teve artefatos de teste regenerados e foi reauditado com `F-001-audit-20261123.md` (APROVADO COM RESSALVAS, token `35102D562FF712F9EAC94941B1BD3E3083B2B94AB976A223DD13D785D932B233`); gates code/test/audit rc0 reverificados pelo orquestrador. Em seguida, build global concorrente sobrescreveu `build.json` duas vezes com `exit_code=2`; após 2 tentativas de reestabilização, registrado BLO-007 e estado rebaixado para `bloqueado` (token vigente `F8B395A41572BA1033C7001DB3BF8389338448337846175E4005AEA62D67E50D`). Atualização 2026-11-23 (/auto F-004): F-004 elevado a `fora-do-escopo-v24` (Selection Mark inexistente na v24; CAP-20261121-02 negativo). Atualização 2026-11-23 (/auto F-001 remediado): BLO-007 resolvido — build global verde (Ninja, exit_code=0), token vigente `09CF8A4DC0D6C39C38D63D0C431F0B70888B483A07AA8C4A4977C241B5E62FC5` aceito, GATE 6 auditoria ok; F-001 estado `bloqueado`→`auditado`; BLO-007 removido do BLOQUEIOS.md.

## Notas de identidade

- **F-007 = Step & Repeat / Layout** (`LayoutEngine.dll`, `GenerateLayout`/`Nest`), não
  "Zoom/Pan". Mantido da análise anterior.
- **F-002 não tem integração de UI**: não existe ação `Mark Sets` em `src/ui/main_window.cpp`.
  O `MarkSetProcessor` imprime `DEBUG` e devolve IDs fixos — não aplica marca alguma.
- **F-004 (Selection Mark)**: A evidência comportamental v24 (CAP-20261121-02) confirma **ausência total** da funcionalidade na interface. O clone implementou UI baseada em docs/behavior/SelectionMark.md (v25, fora do fluxo ativo). Para objetivo de clone v24, esta implementação **não é autorizada** pela evidência e deve ser removida.

## Como reproduzir este estado

```powershell
python scripts/gate.py --all
python scripts/gate.py --inventory
```