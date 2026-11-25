# LayoutEngine.dll — Análise estática Ghidra (v240)

**Binário:** `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\LayoutEngine.dll`  
**Versão de referência:** 24.03.10017  
**SHA-256:** `7BB0ACD6CFE3AC669CBCCD4B99A634687F0B660608A244070FEEED15016497A5`  
**Formato:** PE64 (x64) DLL, assinado Windows Authenticode (PKCS #7)  
**Compilador:** MSVC 19.38.33134 (VS 2022 17.8), Linker 14.38.33134, runtime dinâmico  
**Tamanho:** 533.424 bytes  
**Projeto Ghidra:** `LayoutEngine` (em `tools/ghidra_projects`)  
**Evidência:** `rag/evidence/F-007/ghidra/` (10 arquivos, um por função)  
**Espec:** F-007  

---

## Dependências (imports)

YAGL.dll, LayoutParameters.dll, Logging.dll, Offset.dll, ROD.dll, GeoMapper.dll, ADT.dll, KERNEL32.dll, MSVCP140.dll, VCRUNTIME140.dll, VCRUNTIME140_1.dll, api-ms-win-crt-*.

---

## Tabela sumário — funções analisadas (limite 10)

| # | Endereço | Nome (desmangling) | Classe | Assinatura resumida | Xrefs entrada | Xrefs saída | Confiança | Papel no pipeline |
|---|----------|--------------------|--------|---------------------|---------------|-------------|-----------|-------------------|
| 1 | `0x180013d00` | `GenerateLayout` | `GlobalEngine` | `vector<OutputSheet> GenerateLayout(void) const` | vtable `18007182c`, `18007eee8`, Entry Point | `FUN_180013d20` (thunk virtual) | média | Ponto de entrada do engine: gera as folhas de saída (OutputSheet) a partir da ordem de estações. Wrapper que delega via vtable. |
| 2 | `0x18002d570` | `Nest` | `NestingSheetGenerator` | `nesterror_type Nest(Nesting*, long) const` | vtable, ClassicFillSheet, ClassicMinimalLayouts (2x), GenerateSheetFilling, GenerateSheetLeftovers, GenerateSheetWeighed | `FUN_180040240` | média | Configura flags de rotação/preenchimento (`this+0x24`, `this+0x20`) e invoca o motor de nesting (`FUN_180040240`). |
| 3 | `0x18001d5a0` | `GenerateClassicSolution` | `GuillotineSheetGenerator` | `vector<IntermediateSheet> GenerateClassicSolution(vector<OrderedStation>, bool) override` | vtable `180071824`, `18007f2d8`, Entry Point, DATA `180064648` | (nenhuma — thin override) | alta | Override de guilhotina: zera o vetor de retorno (stub de override virtual; a solução real fica em `180028490`). |
| 4 | `0x180028490` | `GenerateClassicSolution` | `NestingSheetGenerator` | `vector<IntermediateSheet> GenerateClassicSolution(vector<OrderedStation>, bool) override` | vtable `180071828`, `18007f734`, Entry Point, DATA `1800649b8` | ClassicFillSheet, ClassicMinimalLayouts, GetOrderedQuantity, GetProduceCount, GetPlacedStations, IsMaximumFill, SetProduceCount, floor, Guard, operator<< | alta | Solução clássica de nesting (Nesting): itera ClassicFillSheet / ClassicMinimalLayouts, acompanha custos ("nesting.timings", "#nestingchecks"). |
| 5 | `0x180022600` | `GenerateBleedLayout` | `ManualLayoutEngine` | `vector<PlacedPath> GenerateBleedLayout(vector<PlacedPath>, vector<double>)` | vtable `180071820`, `18007f4a0`, Entry Point | GetBoundingBox, GetOneUpHandle, IsEmpty, VectorPath, PlacedPath, Transform, `FUN_180023250`, `FUN_1800223f0` | alta | Gera o layout de sangria (bleed) de caminhos colocados (PlacedPath). Strings: "bleedgenerator.layoutengine". |
| 6 | `0x18000c1f0` | `MakeGridLayout` | `LayoutEngine` | `bool MakeGridLayout(GridLayout&)` | vtable `1800719dc`, `18007e978`, Entry Point | MakeSimpleGridLayout, ApplyStaggerOnGridLayout, ApplyBleedOnGridLayout, ApplyHeadTurnOnGridLayout, ApplyPartialLabelStaggerOrContinuousPrintingOnGridLayout, FetchGridStationLayoutList, GetGridBoxForPartialLabel | alta | Monta o grid de estações: grid simples + stagger + head turn + bleed + partial-label. Orquestra as "Apply*" do grid. |
| 7 | `0x180025820` | `ClassicFillSheet` | `NestingSheetGenerator` | `IntermediateSheet ClassicFillSheet(vector<OrderedStation>)` | `GenerateClassicSolution(180028490)` | AddStationsToNester, Nest, GetOrderedQuantity, GetPlacedStations, IsMaximumFill, Guard | média | Preenche uma folha intermediária com estações (usada pelo classic solution de nesting). |
| 8 | `0x1800261f0` | `ClassicMinimalLayouts` | `NestingSheetGenerator` | `IntermediateSheet ClassicMinimalLayouts(vector<OrderedStation>)` | `GenerateClassicSolution(180028490)` | AddStationsToNester, SetUpNest, GetArea, GetPlacedStations, AddRemainingStationsToNester, Guard | média | Layouts mínimos clássicos de nesting; chama SetUpNest para montar o objeto Nesting. |
| 9 | `0x18002d610` | `SetUpNest` | `NestingSheetGenerator` | `Nesting* SetUpNest(void) const` | ClassicMinimalLayouts, GenerateSheetFilling | `FUN_180040920` | média | Constrói o objeto `Nesting` com dimensões da folha (`-d*0.5`, largura+offset). Chamado pelos geradores de folha de nesting. |
| 10 | `0x180009fc0` | `ApplyBleedOnGridLayout` | `LayoutEngine` | `bool ApplyBleedOnGridLayout(void)` | `MakeGridLayout(18000c1f0)` | GetBleed (LayoutParameters.dll), GetMaskFromOneUp, Transform, `FUN_18003e740` | média | Aplica o sangrado (bleed) no grid: lê `GetBleed` do LayoutParameters e transforma caminhos. |

---

## Detalhe por função

Cada entrada abaixo aponta para o arquivo de evidência em `rag/evidence/F-007/ghidra/`.

### 1. GenerateLayout — `0x180013d00` (GlobalEngine)
- **Evidência:** `LayoutEngine__180013d00.md`
- **Assinatura:** `vector<LayoutEngine::OutputSheet> GenerateLayout(GlobalEngine *this) const`
- **Pseudocódigo:** thin wrapper — chama `FUN_180013d20(*(undefined8 **)this, in_RDX, in_R8, in_R9)` (dispatch virtual via vtable).
- **Xrefs de entrada:** `18007182c` (DATA/vtable), `18007eee8` (DATA/vtable), Entry Point (EXTERNAL).
- **Xrefs de saída:** `180013d20` `FUN_180013d20`.
- **Strings:** nenhuma.
- **Confiança:** média — assinatura certa via export demangled, mas o corpo é um thunk virtual; o comportamento real está em `FUN_180013d20`.
- **Papel:** ponto de entrada público do `GlobalEngine`; produz o `vector<OutputSheet>` final.

### 2. Nest — `0x18002d570` (NestingSheetGenerator)
- **Evidência:** `LayoutEngine__18002d570.md`
- **Assinatura:** `nesterror_type Nest(NestingSheetGenerator *this, Nesting *param_1, long param_2) const`
- **Pseudocódigo:** lê flags `*(int *)(this + 0x24)` (rotation) e `*(int *)(this + 0x20)` (filling direction), mapeia para enums, chama `FUN_180040240(...)` e retorna `nesterror_type`.
- **Xrefs de entrada:** vtable `1800719e8`, `18007f7b8`, Entry Point; **ClassicFillSheet `180025e84`**, **ClassicMinimalLayouts `1800265ea` / `18002766f`**, **GenerateSheetFilling `180029e65`**, **GenerateSheetLeftovers `18002ab34`**, **GenerateSheetWeighed `18002b255`**.
- **Xrefs de saída:** `180040240` `FUN_180040240` (motor de nesting).
- **Strings:** nenhuma.
- **Confiança:** média — corpo concreto (flags + chamada ao motor) mas `FUN_180040240` não desmangla (provavelmente membro de `Nesting` ou função local).
- **Papel:** executa o nesting propriamente dito (alocação de estações na folha).

### 3. GenerateClassicSolution (Guillotine) — `0x18001d5a0`
- **Evidência:** `LayoutEngine__18001d5a0.md`
- **Assinatura:** `vector<IntermediateSheet> GenerateClassicSolution(GuillotineSheetGenerator *this, vector<OrderedStation> *param_1, bool param_2) override`
- **Pseudocódigo:** zera o vetor de retorno (`param_1 = {0,0,0}`) e retorna `param_1` — override vazio/thin.
- **Xrefs de entrada:** vtable `180071824`, `18007f2d8`, Entry Point, DATA `180064648`.
- **Xrefs de saída:** nenhuma.
- **Strings:** nenhuma.
- **Confiança:** alta — corpo trivial confirmado; é o stub de override da classe Guillotine (a lógica real está no Nesting, `0x180028490`).
- **Papel:** interface virtual da solução clássica (guilhotina delega para o nesting).

### 4. GenerateClassicSolution (Nesting) — `0x180028490`
- **Evidência:** `LayoutEngine__180028490.md`
- **Assinatura:** `vector<IntermediateSheet> GenerateClassicSolution(NestingSheetGenerator *this, vector<OrderedStation> *param_1, bool param_2) override`
- **Pseudocódigo (substancial):** itera soluções clássicas via `ClassicFillSheet` e `ClassicMinimalLayouts`, lê `GetOrderedQuantity`, `GetProduceCount`, `GetPlacedStations`, `IsMaximumFill`, `SetProduceCount`, chama `floor` (cálculo de custo), usa `Guard` (logging) e `operator<<` (saída de log).
- **Xrefs de entrada:** vtable `180071828`, `18007f734`, Entry Point, DATA `1800649b8`.
- **Xrefs de saída (chave):** `ClassicFillSheet 180025820`, `ClassicMinimalLayouts 1800261f0`, `GetOrderedQuantity 180039bd0`, `GetProduceCount 180039c00`, `GetPlacedStations 180039bf0`, `IsMaximumFill 180039c60`, `SetProduceCount 18003a1b0`, `floor 18005e2dc`, `Guard` EXTERNAL.
- **Strings:** `nesting.timings` (`180064b98`), `#nestingchecks : ` (`180064bb0`), hashes internos.
- **Confiança:** alta — pseudocódigo completo, dezenas de callees identificados.
- **Papel:** coração do algoritmo de solução clássica de nesting (NestingSheetGenerator).

### 5. GenerateBleedLayout — `0x180022600` (ManualLayoutEngine)
- **Evidência:** `LayoutEngine__180022600.md`
- **Assinatura:** `vector<PlacedPath> GenerateBleedLayout(ManualLayoutEngine *this, vector<PlacedPath> *param_1, vector<double> *param_2)`
- **Pseudocódigo (substancial):** itera caminhos colocados, chama `GetBoundingBox`, `GetOneUpHandle`, `IsEmpty`, `Transform`, constrói `PlacedPath`/`VectorPath`, gerencia alocação/liberação (`free`, `deallocate`).
- **Xrefs de entrada:** vtable `180071820`, `18007f4a0`, Entry Point.
- **Xrefs de saída (chave):** `GetBoundingBox 18002e8f0`, `GetOneUpHandle 18000c160`, `IsEmpty 18002eb20`, `Transform 18002eff0`, `FUN_180023250`, `~PlacedPath 180009840`, `~VectorPath 18002e120`.
- **Strings:** `bleedgenerator.layoutengine` (`180063bb8`), assinatura completa da função (`180064820`).
- **Confiança:** alta — pseudocódigo completo.
- **Papel:** gera o layout de margem de sangria (bleed) para corte.

### 6. MakeGridLayout — `0x18000c1f0` (LayoutEngine)
- **Evidência:** `LayoutEngine__18000c1f0.md`
- **Assinatura:** `bool MakeGridLayout(LayoutEngine *this, GridLayout *param_1)`
- **Pseudocódigo (substancial):** se o grid já estiver inicializado (`*(longlong *)this == *(longlong *)(this + 8)`) retorna false; senão chama `MakeSimpleGridLayout(this)` e, em seguida, `ApplyStaggerOnGridLayout`, `ApplyBleedOnGridLayout`, `ApplyHeadTurnOnGridLayout`, `ApplyPartialLabelStaggerOrContinuousPrintingOnGridLayout`, `FetchGridStationLayoutList`, `GetGridBoxForPartialLabel`.
- **Xrefs de entrada:** vtable `1800719dc`, `18007e978`, Entry Point.
- **Xrefs de saída (chave):** `MakeSimpleGridLayout 18000c410`, `ApplyStaggerOnGridLayout 18000b010`, `ApplyBleedOnGridLayout 180009fc0`, `ApplyHeadTurnOnGridLayout 18000a6f0`, `ApplyPartialLabelStaggerOrContinuousPrintingOnGridLayout 18000a7f0`, `FetchGridStationLayoutList 18000b4d0`, `GetGridBoxForPartialLabel 18000bb40`.
- **Strings:** `0007acb4` (`180063878`).
- **Confiança:** alta — pseudocódigo completo, orquestrador explícito do grid.
- **Papel:** monta o grid de estações (one-up) aplicando stagger, head turn, bleed e partial labels.

### 7. ClassicFillSheet — `0x180025820` (NestingSheetGenerator)
- **Evidência:** `LayoutEngine__180025820.md`
- **Assinatura:** `IntermediateSheet ClassicFillSheet(NestingSheetGenerator *this, vector<OrderedStation> *param_1)`
- **Pseudocódigo:** preenche uma folha intermediária; chama `AddStationsToNester`, `Nest`, `GetOrderedQuantity`, `GetPlacedStations`, `IsMaximumFill`, `Guard`, `operator<<`.
- **Xrefs de entrada:** `GenerateClassicSolution(180028490)` @ `1800288cd`.
- **Xrefs de saída (chave):** `AddStationsToNester 180025680`, `Nest 18002d570`, `GetOrderedQuantity 180039bd0`, `GetPlacedStations 180039bf0`, `IsMaximumFill 180039c60`.
- **Confiança:** média.
- **Papel:** preenchimento clássico de uma única folha de nesting.

### 8. ClassicMinimalLayouts — `0x1800261f0` (NestingSheetGenerator)
- **Evidência:** `LayoutEngine__1800261f0.md`
- **Assinatura:** `IntermediateSheet ClassicMinimalLayouts(NestingSheetGenerator *this, vector<OrderedStation> *param_1)`
- **Pseudocódigo:** layouts mínimos clássicos; chama `AddStationsToNester`, `SetUpNest`, `GetArea`, `GetPlacedStations`, `AddRemainingStationsToNester`, `Guard`.
- **Xrefs de entrada:** `GenerateClassicSolution(180028490)` @ `18002867d`.
- **Xrefs de saída (chave):** `SetUpNest 18002d610`, `GetArea 180039b40`, `GetPlacedStations 180039bf0`, `AddRemainingStationsToNester 1800252f0`.
- **Confiança:** média.
- **Papel:** gera layouts mínimos (mínimo de folhas) para o classic solution de nesting.

### 9. SetUpNest — `0x18002d610` (NestingSheetGenerator)
- **Evidência:** `LayoutEngine__18002d610.md`
- **Assinatura:** `Nesting* SetUpNest(NestingSheetGenerator *this) const`
- **Pseudocódigo:** lê dimensões `*(double *)(this + 0x18)` e `*(double *)(this + 0x10)` / `*(double *)(this + 8)`, chama `FUN_180040920(-d*0.5, -d*0.5, d + ..., d + ..., 0)` para construir o objeto `Nesting`.
- **Xrefs de entrada:** `ClassicMinimalLayouts 1800261f0` @ `18002754a`, `GenerateSheetFilling 1800298a0` @ `180029c34`.
- **Xrefs de saída:** `180040920` `FUN_180040920` (construtor/factory de Nesting).
- **Strings:** constantes de double (`-0x8000000000000000`, `0x3fe0000000000000` = 0.5).
- **Confiança:** média.
- **Papel:** inicializa o objeto `Nesting` com a caixa da folha (sheet bounds).

### 10. ApplyBleedOnGridLayout — `0x180009fc0` (LayoutEngine)
- **Evidência:** `LayoutEngine__180009fc0.md`
- **Assinatura:** `bool ApplyBleedOnGridLayout(LayoutEngine *this)`
- **Pseudocódigo:** aplica sangrado; chama `GetBleed` (import de `LayoutParameters.dll`), `GetMaskFromOneUp`, `Transform`, `FUN_18003e740`.
- **Xrefs de entrada:** `MakeGridLayout 18000c1f0` @ `18000c26f` (UNCONDITIONAL_CALL).
- **Xrefs de saída (chave):** `GetBleed` EXTERNAL (LayoutParameters.dll), `GetMaskFromOneUp 18000bef0`, `Transform 18002eff0`, `FUN_18003e740`.
- **Confiança:** média.
- **Papel:** aplica a margem de sangria ao grid de estações.

---

## Vtables e RTTI (endereços relevantes)

| Endereço | Símbolo | Classe |
|----------|---------|--------|
| `0x180063e10` | `??_7SheetGenerator@LayoutEngine@@6B@` | `SheetGenerator` (base abstrata) |
| `0x180064620` | `??_7GuillotineSheetGenerator@LayoutEngine@@6B@` | `GuillotineSheetGenerator` |
| `0x180064990` | `??_7NestingSheetGenerator@LayoutEngine@@6B@` | `NestingSheetGenerator` |

Strings de RTTI/vtable em `.rdata`: `180073500` (Guillotine vtable), `18007352f` (Nesting vtable), `18007355b` (SheetGenerator vtable).

---

## Observações e limitações

- `GenerateLayout` (`0x180013d00`) e `GenerateClassicSolution` guilhotina (`0x18001d5a0`) decompilam como **thunks/wrappers virtuais** (delegam via vtable ou retornam vazio). O comportamento real está nos alvos apontados (`FUN_180013d20`, e o Nesting `0x180028490`). Isso é esperado para overrides virtuais finos e não invalida a assinatura (confirmada pelo export demangled).
- `Nest` (`0x18002d570`) chama `FUN_180040240`, que não se desmangla (provável membro de `Nesting` ou função local estática) — o motor interno de nesting não foi resolvido por nome neste escopo.
- Nenhuma das funções analisadas depende diretamente de `Offset.dll`, `ROD.dll` ou `GeoMapper.dll` no nível de chamada direto visível no pseudocódigo exportado; essas dependências aparecem nos símbolos/RTTI e nas funções de suporte (`BleedGenerator::Bleed` usa GeoMapper/ROD/Offset).
- O solver linear (`solver.layoutengine`, strings "Pivoted on / Constructed phase1 / Solved phase1 / Basic feasible solution") aparece nas strings do binário mas **não** está entre as 10 funções exportadas analisadas — pertence a funções auxiliares não exportadas.
- Todas as 10 funções respeitam o limite máximo de 10 funções.

---

## Rastreabilidade

- Espec: `docs/features/F-007.md`
- Manifesto de evidência: `rag/evidence/F-007/manifest.json`
- Arquivos de evidência (Ghidra): `rag/evidence/F-007/ghidra/LayoutEngine__<endereco>.md` (10 arquivos)
- Exportações brutas do Ghidra: `rag/ghidra/exports/LayoutEngine.dll/` (functions.csv, symbols.csv, xrefs.csv, strings.csv, callgraph_simplified.csv, decompiled/)
