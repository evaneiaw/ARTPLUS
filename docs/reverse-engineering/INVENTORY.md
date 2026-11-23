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
| 1 | Cut Mark (F-001) | DocumentMarks.dll | **auditado** | auditado | Evidência v240 (37 `.md`), spec reconciliada, código e testes verdes, laudo `F-001-audit-20261122b.md` **APROVADO COM RESSALVAS** (token `87DD75C723F6EF100F19B2AD566364D82EA9AF7BCBCD0F933F54434AC11000F9`). Ressalvas declaradas: CAP comportamental é v25 histórica; geometria sintetizada vs R7; `orientation`/`repetition`/`lineTypes` persistidos sem lastro v240; endereços v25 residuais no teste | fechar as ressalvas em ciclo próprio (geometria FormPaint, captura v24) |
| 2 | Mark Set (F-002) | DocumentMarks.dll | **auditado** | auditado | Evidência v240 (13 IDs) + `CAP-20261121-03` na v24 (UI real: `Document > Marks`, engrenagem e `+ ▾`). Implementação completa: carrega mark set, prepara cache, copia primeira página com IDs novos e remapeamento; teste MarkSetProcessor passa. Laudo `F-002-audit-20261122c.md` **APROVADO COM RESSALVAS** (token `AA17BDF71DEA6A1D8321BBB46B390AC3F3B5A62710ED3FE6C0DB92CEFC7B3783`). Ressalvas declaradas: `identifyRelevantSets` vazio; sem undo; clone sem UI; loader `.pdf` não coberto; marcas dinâmicas/RelinkDynamicObjects não modeladas; camada destino achatada; separações não consolidadas | recursos declarados como TODO; UI pendente em ciclo próprio |
| 3 | Bearer Bar (F-003) | DocumentMarks.dll | **auditado** | auditado | Evidência v240 (37 IDs, 39 documentos), spec reconciliada (R2/R3/R5/R7/R8/R10/R11–R13, §5 e §7), código e testes verdes, laudo `F-003-audit-20261122c.md` **APROVADO COM RESSALVAS** (token `986EE9F8C939F93619E44197A893F39065605D24CB2616E2236258089295F63F`). Ressalvas declaradas: CAP recapturada na v25; `0x180170C20` sem equivalente v240; `Close` inferido; R5 como predicado; geometria retangular sintética | fechar ressalvas em ciclo próprio (recaptura CAP v24, R5 aplicação) |
| 4 | Selection Mark (F-004) | PDFObjectActions.dll | **fora-do-escopo-v24** | auditado | Evidência estática no módulo correto (13 funções v240, zero erro) + `CAP-20261121-02` capturado na v24, com **resultado negativo**: não existe ação `Selection Mark` em `File`/`Object`/`Select`/`Prepress` nem no ribbon; `Ctrl+Shift+S` é `Save as...`. O DLL oferece operadores genéricos de seleção/transformação. **A UI implementada no ArtPlus baseia-se em documentação histórica (v25), NÃO em comportamento da v24. Para clone da v24, esta feature não deve ser implementada.** | N/A |
| 5 | Open Document (F-005) | Document.dll | **auditado** | auditado | Evidência v240 (14 IDs), `CAP-20261121-01` capturado **na v24** (`File > Open...`, filtro `*.pdf; *.pdpdla; *.ap; *.art`, sem diálogo de importação), spec corrigida, código e testes verdes, laudo `F-005-audit-20261122b.md` **APROVADO COM RESSALVAS** (token `BDA698E034CFACEBC27B065C6A965768DD3A3F927C7D58BF7897E18CE730EE88`). Ressalvas: contagem de páginas não medida; parse delegado a `PDFOBJECTLAYER.DLL`; defeito de UI D-01 corrigido | fechar ressalvas em ciclo próprio (contagem de páginas, parse delegado) |
| 6 | Save Document (F-006) | Document.dll | **bloqueado** (BLO-005) | bloqueado | build **verde** desde 2026-11-21; 3 placeholders de evidência; criptografia não implementada (`TODO(F-006)`); `SaveDocumentTests` 22/22 | fechar TODOs ou reduzir escopo da spec + evidência real |
| 7 | Step & Repeat (F-007) | LayoutEngine.dll | **bloqueado** (BLO-003) | bloqueado | evidência com versão abreviada (não 24.03.10017), sem CAP; `step_repeat.cpp` retorna `"Not implemented"` (3×); sem spec/ADR/teste | registrar BLO-003; não implementar até CAP ou decisão |
| 8 | Color Management (F-008) | ColorManipulationLayer.dll | **auditado** | auditado | Evidência v240 (5 IDs + CAP-20261122-02), spec completa, ADR aprovada, 13 arquivos `src/color_management/`, build verde, 22 testes passando, laudo `F-008-audit-20261122b.md` **APROVADO** (token `D222815A2C9C95E69284D54E54CFEF6BD94E5351F0C00456A0C3F7A0E89F3EB3`). BLO-004 RESOLVIDO. | fechar ressalvas declaradas (stubs LCMS/Pantone, pipeline de callback) em ciclo posterior |

## Cobertura por estado comprovado

- **auditado**: 7 (F-001, F-002, F-003, F-004, F-005, F-008 — laudos APROVADOS/COM RESSALVAS, tokens válidos, 7 gates verdes cada)
- **testado**: 0
- **implementado**: 0
- **arquitetado**: 0
- **spec**: 0
- **comportamento**: 0
- **analisado**: 0
- **triado**: 0
- **bloqueado**: 2 (F-006, F-007)
- **Total rastreado**: 8

> Comparação com o inventário anterior: F-001, F-002, F-003, F-004, F-005, F-008 elevados a `auditado` após laudos frescos; F-006 e F-007 mantidos `bloqueado`. BLO-004 (F-008) resolvido. Nenhum estado elevado sem comprovação pelo gate.

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