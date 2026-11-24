# INVENTORY.md — fila de módulos e estado de cobertura

Fonte única da verdade de versão: `docs/agents/REFERENCE_VERSION.md` — Esko ArtPro+ **v24.03.10017**.

**Estado comprovado**, derivado por `python scripts/gate.py` em **2026-11-22** (recuperação
do sistema de agentes + pipeline F-002 completo). Nenhum estado pode ser elevado à mão: o que o gate não prova,
o inventário não declara.

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
| 1 | Cut Mark (F-001) | DocumentMarks.dll | **auditado** | auditado | Evidência v240 (37 `.md`, hash `E47328BD…4B3C0FA102`), spec reconciliada, build isolado `test_cut_mark` em `build_f001` (exit 0) e `CutMarkTests` 1/1. Laudo `F-001-audit-20261123.md` APROVADO COM RESSALVAS, reauditado com token vigente `09CF8A4DC0D6C39C38D63D0C431F0B70888B483A07AA8C4A4977C241B5E62FC5` (gate `--stage audit` ok). Build global verde (Ninja, exit_code=0). BLO-007 resolvido — artefato `build.json` estabilizado. Ressalvas de produto permanecem: R6, R7, E5, campos órfãos, serialização `.artplus`, ADR-001 desatualizada, contradição spec × CAP. | fechar ressalvas de produto em ciclo próprio; não reabrir BLO-007 |
| 2 | Mark Set (F-002) | DocumentMarks.dll | **auditado** | auditado | Evidência v240 (13 IDs) + `CAP-20261121-03` na v24 (UI real: `Document > Marks`, engrenagem e `+ ▾`). Implementação completa: carrega mark set, prepara cache, cópia primeira página com IDs novos e remapeamento; teste MarkSetProcessor passa (19/19). Laudo `F-002-audit-20261124.md` **APROVADO COM RESSALVAS** (token `ACBA7121FE6DD44C3BC39D7C23E9604EEB70BA0AD9EA046DD99233338B075798`). Ressalvas declaradas: `identifyRelevantSets` vazio; sem undo; clone sem UI; loader `.pdf` não coberto; marcas dinâmicas/RelinkDynamicObjects não modeladas; camada destino achatada; separações não consolidadas | fechar as ressalvas em ciclo próprio (identifyRelevantSets, undo, relink dinâmico, reporter, camada, separações, UI) |
| 3 | Bearer Bar (F-003) | DocumentMarks.dll | **auditado** | auditado | Gate 2026-11-23: all stages green (evidence=0, spec=0, adr=0, code=0, test=0, audit=0). Laudo `F-003-audit-20261123.md` APROVADO COM RESSALVAS (token `E51DD6A9D01947E715A5954A8045CEF8368BF63BF16CC784AAC707C5629463B9`). Ressalvas declaradas: CAP comportamental v24 incompleta (CAP-04 não capturado devido a diálogo de licença bloqueante; CAP-20261119-02 como referência histórica v25); `0x180170C20` sem equivalente v240; `Close` inferido; R5 como predicado; geometria retangular sintética; fórmula fechada PDF+ não derivada. Build limpo, BearerBarTests 1/1 passed. | Estado corrigido por contrato AGENTS §10.3, auditoria aprovada com token fresco, build restaurado e verde. |
| 4 | Selection Mark (F-004) | PDFObjectActions.dll | **fora-do-escopo-v24** | auditado | Evidência estática no módulo correto (13 funções v240, zero erro) + `CAP-20261121-02` capturado na v24, com **resultado negativo**: não existe ação `Selection Mark` em `File`/`Object`/`Select`/`Prepress` nem no ribbon; `Ctrl+Shift+S` é `Save as...`. O DLL oferece operadores genéricos de seleção/transformação. **A UI implementada no ArtPlus baseia-se em documentação histórica (v25), NÃO em comportamento da v24. Para clone da v24, esta feature não deve ser implementada.** | N/A |
| 5 | Open Document (F-005) | Document.dll | **auditado** | auditado | Evidência v240 (14 IDs, SHA `DA91E285…8FA9E21` conferido), `CAP-20261121-01` capturado **na v24** (`File > Open...`, filtro `*.pdf; *.pdpdla; *.ap; *.art`, sem diálogo de importação), spec corrigida, ADR-013 + ADR-014 (aceita, autoriza R1/R2/R3/R4/R6/R8/R9/§5), código completo (FileDispatcher MIME→handler, OpenError, handlers PDF/.artplus, UI única, título/relayout), build isolado exit 0, ctest 11/11 + 18 casos Qt, 8 suítes novas, laudo `F-005-audit-20261123c.md` **APROVADO** (token `DC5B57242995E6250A9B5438A23698F6C1EAA5512CE1477D579DBF9CBB4FFAA6`), gates evidence/spec/adr/code/test/audit rc0 reverificados pelo orquestrador. Ressalvas não bloqueantes: R8/R9 por guarda estática (sem teste de GUI); seção de implementação da spec ainda pré-ADR-014; painéis prepress fora do escopo; divergência REA declarada no manifest | dossiê Document já gerado; fechar ressalvas em ciclo próprio (teste de GUI, atualizar seção da spec) |
| 6 | Save Document (F-006) | Document.dll | **bloqueado** (BLO-005) | bloqueado | build **verde** desde 2026-11-21; 3 placeholders de evidência; criptografia não implementada (`TODO(F-006)`); `SaveDocumentTests` 22/22 | fechar TODOs ou reduzir escopo da spec + evidência real |
| 7 | Step & Repeat (F-007) | LayoutEngine.dll | **bloqueado** (BLO-003) | bloqueado | evidência com versão abreviada (não 24.03.10017), sem CAP; `step_repeat.cpp` retorna `"Not implemented"` (3×); sem spec/ADR/teste | registrar BLO-003; não implementar até CAP ou decisão |
| 8 | Color Management (F-008) | ColorManipulationLayer.dll | **testado** | auditado | Evidência v240 (5 IDs + CAP-20261122-02), spec completa, ADR aprovada, 13 arquivos `src/color_management/`, build verde, 22 testes passando, laudo `F-008-audit-20261122b.md` **APROVADO** (token `D222815A2C9C95E69284D54E54CFEF6BD94E5351F0C00456A0C3F7A0E89F3EB3`). BLO-004 RESOLVIDO. Laudo stale — token não confere com `build.json`/`F-008.test.json` atuais. Requer re-auditoria. | re-auditoria para `auditado`; fechar ressalvas declaradas (stubs LCMS/Pantone, pipeline de callback) em ciclo posterior |

## Cobertura por estado comprovado

- **auditado**: 4 (F-001, F-002, F-003, F-005 — laudos APROVADOS/COM RESSALVAS na data do laudo, revalidação pendente em ciclo próprio; F-005 aprovado em 2026-11-23 com laudo `F-005-audit-20261123c.md`, token `DC5B5724…`)
- **testado**: 1 (F-008 — build + testes verdes, laudo stale, requer re-auditoria)
- **fora-do-escopo-v24**: 1 (F-004 — CAP-20261121-02 negativo; UI Selection Mark inexistente na v24.03.10017; não implementar no clone)
- **implementado**: 0
- **arquitetado**: 0
- **spec**: 0
- **comportamento**: 0
- **analisado**: 0
- **triado**: 0
- **bloqueado**: 2 (F-006 — BLO-005; F-007 — BLO-003)
- **Total rastreado**: 8

> Comparação com o inventário anterior: F-001, F-002, F-003, F-004 elevados a `auditado` após laudos frescos (2026-11-24); F-005 **REPROVADO → auditado** em 2026-11-23 (ADR-014 implementada, build isolado estável, laudo `F-005-audit-20261123c.md` APROVADO, gate audit rc0); F-008 mantido `testado` (laudo stale); F-006 e F-007 mantidos `bloqueado`. BLO-004 (F-008) resolvido. Nenhum estado elevado sem comprovação pelo gate. F-002 re-auditado em 2026-11-24 (token `ACBA7121FE6DD44C3BC39D7C23E9604EEB70BA0AD9EA046DD99233338B075798`). Atualização 2026-11-23 (/auto F-001): F-001 foi rebaixado de `auditado` para `implementado` por erro de contrato (laudo stale), teve artefatos de teste regenerados e foi reauditado com `F-001-audit-20261123.md` (APROVADO COM RESSALVAS, token `35102D562FF712F9EAC94941B1BD3E3083B2B94AB976A223DD13D785D932B233`); gates code/test/audit rc0 reverificados pelo orquestrador. Em seguida, build global concorrente sobrescreveu `build.json` duas vezes com `exit_code=2`; após 2 tentativas de reestabilização, registrado BLO-007 e estado rebaixado para `bloqueado` (token vigente `F8B395A41572BA1033C7001DB3BF8389338448337846175E4005AEA62D67E50D`). Atualização 2026-11-23 (/auto F-004): F-004 elevado a `fora-do-escopo-v24` (Selection Mark inexistente na v24; CAP-20261121-02 negativo). Atualização 2026-11-23 (/auto F-001 remediado): BLO-007 resolvido — build global verde (Ninja, exit_code=0), token vigente `09CF8A4DC0D6C39C38D63D0C431F0B70888B483A07AA8C4A4977C241B5E62FC5` aceito, GATE 6 auditoria ok; F-001 estado `bloqueado`→`auditado`; BLO-007 removido do BLOQUEIOS.md. |

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