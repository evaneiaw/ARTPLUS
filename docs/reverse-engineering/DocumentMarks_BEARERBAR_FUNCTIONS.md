# DocumentMarks.dll — Bearer Bar (F-003)

Módulo: `C:\Esko\bg_prog_artpro+_v250\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
versão 25.0 · SHA-256 `ffa8809d294a7aa08bd2794e0b0c1e64608d898b5f7ba698a4e58a8e575bee10`
PE32+ x64 · MSVC 19.41 · image base `0x180000000`

Programa Ghidra: projeto `ArtProPlus`, programa `DocumentMarks.dll` (análise padrão já existente).
Todo o material desta página vem de **`-process -noanalysis -readOnly`** (nenhum import novo).

Export bruto usado:

| Arquivo | Conteúdo |
|---|---|
| `rag/ghidra/exports/DocumentMarks.dll/decompiled_addr/*.c` | 59 descompilações geradas para Bearer Bar |
| `rag/ghidra/exports/DocumentMarks.dll/xrefs_focus.txt` | referências/callers/callees dos endereços de Bearer Bar |
| `rag/ghidra/exports/DocumentMarks.dll/data_dump.txt` | constantes numéricas resolvidas |
| `rag/ghidra/exports/DocumentMarks.dll/strings.csv` | 106 literais com `Bearer` |
| `rag/ghidra/exports/DocumentMarks.dll/symbols.csv` | nomes de export PE (a fonte de verdade dos nomes) |

Evidência por função: `rag/evidence/F-003/ghidra/`.

## Nomenclatura

Diferente de "Trim Marks" (F-001), **Bearer Bar existe literalmente no binário**:
`BearerBar`, `PDFPlusBearerBar`, `AIDynamicMarks-BearerBar`,
`DynamicObject_PDFPlusBearerBar`, `DM-BearerBarParams*`. Não há ambiguidade de mapeamento
F-003 → família `BearerBar`.

Duas implementações coexistem na v250:

| Família | Chave de tipo | Uso |
|---|---|---|
| `DocumentMarks::BearerBar` | `AIDynamicMarks-BearerBar` | formato legado (AI Dynamic Marks) |
| `DocumentMarks::PDFPlusBearerBar` | `DynamicObject_PDFPlusBearerBar` | formato PDF+ (caminho atual) |

## Classes

| Classe | Base imediata (pelo ctor) | Tamanho alocado | Vtable `ListItem<ContentObject>` | Vtable `Visitable` |
|---|---|---|---|---|
| `DocumentMarks::BearerBar` | `DynamicMark` | `0x6B8` | `0x180305178` | `0x1803052F8` |
| `DocumentMarks::PDFPlusBearerBar` | `DynamicMark` (+ `MarkPosition` em `this+0x2F0`) | `0x790` | `0x1803229B0` | `0x180322B30` |

Herança observada (nomes de export + escritas de vtable nos ctors):
`ContentObject` → `Group` → `DynamicObject` → `DynamicMark` → `{BearerBar, PDFPlusBearerBar}`;
interfaces `ArtDoc::Visitable` e `ArtDoc::Detail::ListItem<ArtDoc::ContentObject>`.
Cada ctor grava a vtable ListItem em `this+0x00` e a Visitable em `this+0x20`
(herdado do padrão do módulo, ver F-001).

Vtables de visitante (RTTI presente, sem uso direto nesta análise):
`Visitor<BearerBar>` `0x180305328` · `ConstVisitor<BearerBar>` `0x180305348` ·
`Visitor<PDFPlusBearerBar>` `0x180306EE0` · `ConstVisitor<PDFPlusBearerBar>` `0x180306F00`.

**Limitação:** Ghidra não gerou símbolos `??_R*`/COL para este módulo; os endereços de
*Complete Object Locator* não foram extraídos nestas vtables (gap). Os endereços de dados
`0x1803B89C0`/`0x1803B89C4` (PDF+) e `0x1803B893C`/`0x1803B8940` (legado) referenciam as
vtables a partir do bloco RTTI, conforme `xrefs_focus.txt`.

## Funções-chave

| Endereço | Nome (export PE) | Papel | Confiança | Evidência |
|---|---|---|---|---|
| `0x18001E3C0` | `BearerBar::BearerBar(bool)` | ctor legado; grava defaults | alta | [0x18001E3C0](../../rag/evidence/F-003/ghidra/DocumentMarks__0x18001E3C0.md) |
| `0x18001E350` | `BearerBar::BearerBar(BearerBar const&, CloneStrategy&)` | ctor de clone; chamado por `Clone` em `0x18001EDCD` | alta | [0x18001E350](../../rag/evidence/F-003/ghidra/DocumentMarks__0x18001E350.md) |
| `0x18001EDA0` | `BearerBar::Clone` | `new (0x…)` + ctor de clone; escreve vtable ListItem em `0x180305180` | alta | índice |
| `0x18001F870` | `BearerBar::parsePdfPropertiesDict` | lê `DM-BearerBarParams*`; version < 3 | alta | [0x18001F870](../../rag/evidence/F-003/ghidra/DocumentMarks__0x18001F870.md) |
| `0x180020950` | `BearerBar::updatePdfPropertiesDictImp` | grava Version=2, Width/Extend/Offset (mm), Location | alta | [0x180020950](../../rag/evidence/F-003/ghidra/DocumentMarks__0x180020950.md) |
| `0x18001FDB0` | `BearerBar::regenerateMarkImp` | gera 1 `Path` por lado do bitmask `Location` | alta | [0x18001FDB0](../../rag/evidence/F-003/ghidra/DocumentMarks__0x18001FDB0.md) |
| `0x18001EDF0` | helper de geometria por lado (sintético) | retângulo = bbox + width/extend/offset do lado `i` | média | índice |
| `0x18012FAA0` | `PDFPlusBearerBar::PDFPlusBearerBar(shared_ptr<FormPaint const>)` | ctor PDF+; defaults | alta | [0x18012FAA0](../../rag/evidence/F-003/ghidra/DocumentMarks__0x18012FAA0.md) |
| `0x180132A70` | `PDFPlusBearerBar::regenerateMarkImp` | direção → anchors → size ref → `Group`/`Expander` | média | [0x180132A70](../../rag/evidence/F-003/ghidra/DocumentMarks__0x180132A70.md) |
| `0x180131C40` | `PDFPlusBearerBar::UpdateDirection` | deriva `Direction` dos anchors | alta | [0x180131C40](../../rag/evidence/F-003/ghidra/DocumentMarks__0x180131C40.md) |
| `0x180131DC0` | `PDFPlusBearerBar::UpdateSizeReference` | zera `SizeReference` incompatível com `Direction` | alta | [0x180131DC0](../../rag/evidence/F-003/ghidra/DocumentMarks__0x180131DC0.md) |
| `0x180131E30` | `PDFPlusBearerBar::ValidateAnchors` | normaliza o par de anchors | média | [0x180131E30](../../rag/evidence/F-003/ghidra/DocumentMarks__0x180131E30.md) |
| `0x180131FE0` | `PDFPlusBearerBar::getMarkType` | devolve `DynamicObject_PDFPlusBearerBar` | alta | [0x180131FE0](../../rag/evidence/F-003/ghidra/DocumentMarks__0x180131FE0.md) |
| `0x180179DA0` | parser PDF+ de `Position` (sintético) | `SourceAnchor`/`ReferenceAnchor`/`Reference`/`Offset` | alta | [0x180179DA0](../../rag/evidence/F-003/ghidra/DocumentMarks__0x180179DA0.md) |
| `0x180170C20` | parser PDF+ de tamanho (sintético) | `Reference`→`SizeReference`, `Extends`→`Extend` | alta | [0x180170C20](../../rag/evidence/F-003/ghidra/DocumentMarks__0x180170C20.md) |
| `0x18016F250` | fábrica PDF+ (sintético) | `new (0x790) PDFPlusBearerBar` | alta | [0x18016F250](../../rag/evidence/F-003/ghidra/DocumentMarks__0x18016F250.md) |
| `0x1800AA260` | `SetBearerBarExtend(Content&, function, Coordinate const&)` | setter transacional (ActionList/undo) | alta | [0x1800AA260](../../rag/evidence/F-003/ghidra/DocumentMarks__0x1800AA260.md) |
| `0x1800AA3C0` | `SetBearerBarOffset(...)` | idem, para Offset | alta | [0x1800AA3C0](../../rag/evidence/F-003/ghidra/DocumentMarks__0x1800AA3C0.md) |
| `0x1800AA520` | `SetBearerBarSizeReference(...)` | idem, para SizeReference | alta | [0x1800AA520](../../rag/evidence/F-003/ghidra/DocumentMarks__0x1800AA520.md) |
| `0x180111410` | `createDynamicObject` legado (sintético) | `memcmp "AIDynamicMarks-BearerBar"` → `new (0x6B8) BearerBar(true)` em `0x180111792` | alta | índice |

Funções auxiliares confirmadas (sem arquivo de evidência próprio):

| Endereço | Função | Nota |
|---|---|---|
| `0x18001F650` / `0x18001F6A0` / `0x18001F6B0` / `0x18001F680` | `BearerBar::getExtend` / `getOffset` / `getWidth` / `getLocation` | getters triviais de `+0x6A0` / `+0x6A8` / `+0x698` / `+0x6B0` |
| `0x1800206D0` / `0x1800206F0` / `0x180020700` / `0x1800206E0` | `SetExtend` / `setOffset` / `SetOffset` / `setLocation` | setters diretos, sem undo; `0x1800206D0` e `0x180020700` são ICF (`BearerBar::setExtend`, `BearerBar::setWidth`) |
| `0x18001C690` | `PDFPlusBearerBar::GetOffset` | ICF com ~10 getters de outras classes; devolve `this+0x698` |
| `0x18012FF20` | `PDFPlusBearerBar::Clone` | chama o ctor de clone `0x18012F8C0` |
| `0x18012FF70` | `PDFPlusBearerBar::CollectGrids` | `ConstVisitorBase` sobre o `Content` |
| `0x180130CC0` | `GetDirection` | devolve `int` em `+0x6A8` |
| `0x180131AD0` / `0x180131C30` | `GetSizeReference` / `SetSizeReference` | `+0x730` |
| `0x180131AC0` / `0x180131AE0` | `GetReferenceObject` / `SetReferenceObject` | `variant<PageBox, uint64, ProcessingStepLayer>` em `+0x6B0` (índice em `+0x728`) |
| `0x180131CB0` | `UpdateMarkErrors` | registra erros de marca |
| `0x1801322B0` | `hasPositionRef` | `+0x728 == 1` e id `!= 0` |
| `0x1801326E0` | `postProcessClonedMark` | apaga `PDFPlusBearerBar_OriginalReferenceName`, resolve `ReferenceID` |
| `0x180127BF0` | `PDFPlusBearerBar::GetBoundingBoxSelf` (ICF) | — |
| `0x18012CE60` / `0x1801288B0` | `setColorTypeImp` / `SetTargetSeparationsImp` | — |
| `0x180113BE0` | `MarkReader::PostProcessObject` | referencia `PTR_s_AIDynamicMarks-BearerBar_18031F360` — papel exato não confirmado (gap) |

## Defaults observáveis

### Legado — `BearerBar(bool)` em `0x18001E3C0`

| Campo | Offset | Default gravado | Interpretação |
|---|---|---|---|
| width | `+0x698` | `0x40CBAE9D3A74E9D4` = `14173.2283464567` | **exatamente 5 mm** em milipontos |
| extend | `+0x6A0` | `0` | 0 mm |
| offset | `+0x6A8` | `0` | 0 mm |
| location | `+0x6B0` | `3` | bitmask bits 0+1 (left+right) |
| tipo/base | — | `DynamicMark(this, true, 0xFD)` | — |

### PDF+ — `PDFPlusBearerBar(shared_ptr<FormPaint const>)` em `0x18012FAA0`

| Campo | Offset | Default | Interpretação |
|---|---|---|---|
| offset | `+0x698` | `0` | 0 mm |
| extend | `+0x6A0` | `0` | 0 mm |
| direction | `+0x6A8` | `1` | inferido como horizontal (ver abaixo) |
| reference object | `+0x6B0` | `PageBox = 3` | **inferência** (ver lacunas) |
| índice da variante | `+0x728` | `0` | alternativa `PageBox` |
| size reference | `+0x730` | `0` | não definido |
| lista/auxiliar | `+0x738` / `+0x740` / `+0x748` | `0/0/0` | vector (inferência) |
| container | `+0x750` | `FUN_180026ca0(this+0x750, 4)` | inicializado com capacidade 4 (inferência) |
| anchors | `MarkPosition@0x2F0` | `setReferenceObject(0)`, `setAnchors(5,3)` | — |
| cor | — | `setColorType(5, 0)` | — |
| tipo/base | — | `DynamicMark(this, false, 0x1CE)` | — |

## Semântica de `Location` (legado) — bitmask de 4 lados

`regenerateMarkImp` (`0x18001FDB0`) faz, para `i` em `0..3`:

```
if ((*(uint *)(this + 0x6b0) >> i) & 1)  →  gera um Path para o lado i
```

`DumpInfo` (`0x18001F160`) decodifica os mesmos bits em rótulos:

| Bit | Valor | Rótulo literal | Lado |
|---|---|---|---|
| 1 | `0x1` | `l` (`0x1803054B0`) | left |
| 2 | `0x2` | `r` (`0x1803054AC`) | right |
| 4 | `0x4` | `t` (`0x1803054A8`) | top |
| 8 | `0x8` | `b` (`0x1803054A4`) | bottom |

(Os quatro bytes são strings de 2 caracteres; a ordem no dump é `b`, `t`, `r`, `l` nos
endereços `0x1803054A4`, `4A8`, `4AC`, `4B0`.)

Combinações nomeadas:

- `IsVertical = true` → `Location = 3` → left + right (barras verticais)
- `IsVertical = false` → `Location = 0xC` → top + bottom (barras horizontais)
- default do ctor = `3`

Confiança **alta**: os índices de lado em `FUN_18001EDF0` (0 = fora da borda esquerda,
1 = fora da direita, 2 = acima do topo, 3 = abaixo da base) e os rótulos de `DumpInfo`
concordam.

## `SizeReference` (PDF+) — valores 1..8

Nomes vêm literalmente do parser `0x180170C20` (comparação de `GAName`):

| Valor | Nome no PDF+ |
|---|---|
| 0 | (não definido — default do ctor) |
| 1 | `LeftMostGridLayout` |
| 2 | `RightMostGridLayout` |
| 3 | `LeftMostGridLayoutColumn` |
| 4 | `RightMostGridLayoutColumn` |
| 5 | `TopMostGridLayout` |
| 6 | `BottomMostGridLayout` |
| 7 | `TopMostGridLayoutRow` |
| 8 | `BottomMostGridLayoutRow` |

`UpdateSizeReference` (`0x180131DC0`) invalida (`= 0`) a referência se ela não combinar com a
direção: `1..4` exigem `Direction == 0`; `5..8` exigem `Direction == 1`.

## Unidades, escalas e constantes

| Constante | Endereço | Valor | Uso |
|---|---|---|---|
| fator mm→interno | `0x180305518` / `0x180305520` | `127.0` / `360000.0` | `interno = mm * 360000 / 127` |
| fator interno→mm | idem | `127/360000` | `mm = interno * 127 / 360000` |
| escala PDF+ | `0x1803066E0` | `1000.0` | `Extends`/`Offset` (mm) → milipontos |
| sinal do offset | `0x1803082D0` / `0x1803066C0` | `-1.0` / `+1.0` | conforme o anchor (5 ou 7) |
| identidade/escala | `0x1803066F0` | `1.0` | transformação |
| meio | `0x180308E18` | `0.5` | composição de bbox no PDF+ |
| guarda anti-zero | (literal no código) | `28.346456692913385` | = 0,01 mm em milipontos |
| default width | `0x40CBAE9D3A74E9D4` | `14173.2283464567` | = 5 mm |

`360000/127 = 2834.6456692913...` = `72*1000/25.4` — logo a **unidade interna é o
miliponto** (1/1000 pt) e o dicionário legado grava **mm**. Verificação independente: o
default `14173.2283` milipontos = exatamente `5 mm`; e o log de debug converte para mm com
`valor * 127 / 360000` antes de imprimir, com o rótulo literal `Reference object Bbox mm:`
(`0x180305450`).

## Strings literais

| Endereço | Literal | Onde é usada |
|---|---|---|
| `0x180305370` | `AIDynamicMarks-BearerBar` (len 24) | `memcmp` em `0x180111410` (`0x18011170F`, `0x180111724`) |
| `0x180305428` | `BearerBar` | nome do tipo no erro de versão (`0x18001F9CB`) |
| `0x180305438` | ` Bearer Bar update ` | log de debug em `regenerateMarkImp` (`0x18002022B`) |
| `0x180305470` | `BearerBar(` | prefixo do `DumpInfo` (`0x18001F285`) |
| `0x180305480` | `width=` | `DumpInfo` |
| `0x180305488` | `; extend=` | `DumpInfo` |
| `0x180305498` | `; offset=` | `DumpInfo` |
| `0x1803054B8` | `; location=` | `DumpInfo` |
| `0x1803054A4/4A8/4AC/4B0` | `b` / `t` / `r` / `l` | rótulos dos lados no `DumpInfo` |
| `0x180305450` | `   Reference object Bbox mm:` | log de `regenerateMarkImp` |
| `0x1803054C8` | ` [ <initial/default state> ]` | log de `regenerateMarkImp` |
| `0x1803054E8..0x180305510` | `; H: ` ` (W: ` `; B: ` `; R: ` `; T: ` [ L: ` | log da bbox |
| `0x180322B68` | `DynamicObject_PDFPlusBearerBar` (len 30) | `getMarkType` (`0x180131FE0`) |
| `0x180322980` | `PDFPlusBearerBar_OriginalReferenceName` | `postProcessClonedMark` |
| `0x180326A30` | `DocumentMarks_BearerBar_ReferenceID` | parser (`0x180179DA0`) e `postProcessClonedMark` |
| `0x180327930` | `Vertical offset in bearer bar not supported.` | exceção no parser `0x180179DA0` (`0x18017A30A`) |
| `0x180327960` | `No width or height dictionary in size dictionary.` | contexto de parser de tamanho (não confinado a Bearer Bar) |

Chaves de persistência:

| Chave | Endereço | Formato |
|---|---|---|
| `DM-BearerBarParams` | `0x18033D058` | dicionário aninhado (legado) |
| `DM-BearerBarParams-Version` | `0x18033D478` | inteiro; escrito **2**, lido exige `< 3` |
| `DM-BearerBarParams-Width` | `0x18033D3D8` | float **mm** |
| `DM-BearerBarParams-Extend` | `0x18033D3F8` | float **mm** |
| `DM-BearerBarParams-Offset` | `0x18033D418` | float **mm** |
| `DM-BearerBarParams-IsVertical` | `0x18033D438` | bool — **só lido** (versão 1); o writer não grava |
| `DM-BearerBarParams-Location` | `0x18033D458` | inteiro (bitmask) |

Chaves do PDF+ (nomes `GName`, lidas com `GADict`):

`Position`, `SourceAnchor`, `ReferenceAnchor`, `Reference`, `ReferenceID`, `ObjectID`,
`Offset` (array; 2º elemento deve ser `0.0`), `Extends`, e os 8 nomes de `SizeReference`.

## Pipeline reconstruído

```
LEGADO (AI Dynamic Marks)
  createDynamicObject 0x180111410
    └─ memcmp "AIDynamicMarks-BearerBar" (24)   0x18011170F
         └─ new (0x6B8) BearerBar(true)         0x180111792  → ctor 0x18001E3C0
              └─ parsePdfPropertiesDict 0x18001F870
                   ├─ DM-BearerBarParams-Version  (>=3 → erro "BearerBar")
                   ├─ Width / Extend / Offset     (mm → miliponto, ×360000/127)
                   ├─ versão 1: IsVertical → Location = 3 | 0xC
                   └─ versão 2: Location (bitmask)
  regenerateMarkImp 0x18001FDB0
    ├─ getPositionRefBBox  → bbox de referência
    ├─ for i in 0..3: if (Location >> i) & 1
    │     FUN_18001EDF0 (retângulo do lado i: width/extend/offset) → Path
    │     Fillable::GetFillPaint | FlatPaint::Factory::Get → SetFillPaint
    │     DocumentEdit::InsertNewObjectAfter
    ├─ remove filhos excedentes (ExtractObjectFromParent)
    └─ applyColor + log de debug (nível > 2)

PDF+ (caminho atual)
  funções de leitura (fábrica 0x18016F250 → new (0x790) 0x18012FAA0)
    ├─ 0x180179DA0  Position{SourceAnchor,ReferenceAnchor,Reference,Offset}
    │     └─ y != 0 → throw "Vertical offset in bearer bar not supported."
    └─ 0x180170C20  Reference{…}→SizeReference, Extends→Extend
  setters transacionais (undo): 0x1800AA260 / 0x1800AA3C0 / 0x1800AA520
  regenerateMarkImp 0x180132A70
    ├─ UpdateDirection 0x180131C40 → ValidateAnchors 0x180131E30
    ├─ UpdateSizeReference 0x180131DC0
    ├─ apaga conteúdo gerado anterior (DocumentEdit::Delete)
    ├─ Group(0x1ff) + Expander + FormPaint::GetContent (pinta o form de origem)
    ├─ resolve referência: ObjectID → Content::GetObjectWithID | PageBox → Page::GetPageBox
    ├─ GetPDFPlusBoundingBox / GetBoundingBoxForPositioning
    ├─ SetTransformation (escala derivada de Extend/tamanho da referência)
    ├─ InsertNewObjectOnTop + ApplyPDFPlusColor
    └─ Delete das sobras
```

## Cobertura e lacunas

- 59 funções descompiladas; 50 endereços com xrefs resolvidos; 106 literais `Bearer`
  catalogados; 9 constantes numéricas resolvidas.
- **Geometria fechada do PDF+ não extraída.** `0x180132A70` (427 linhas) foi mapeada em
  estrutura — `UpdateDirection` → `ValidateAnchors` → `UpdateSizeReference` → bbox →
  `SetTransformation` — mas a fórmula final do retângulo (uso combinado de
  `_DAT_1803066F0`, `_UNK_1803066F8`, `0.5` e do XOR de sinal em `0x180308300` para
  `anchor != 1`) não foi derivada. Trechos `346..427` ficaram sem interpretação.
- **String de menu/UI não localizada.** Nenhum literal de menu/inspetor com
  "Bearer Bar" foi encontrado em `strings.csv`; o nome só aparece como tipo, chave de
  persistência e mensagem. A UI pode estar em outro módulo — **não** concluir ausência de
  funcionalidade.
- **`PageBox = 3` continua inferência.** O ctor grava `3` e o padrão é idêntico ao do
  `PDFPlusCutMark` (F-001, `PageBox = 3`), onde a leitura de
  `ArtDoc::Page::GetPageBox` + ordem canônica do produto sugere `3 = TrimBox`. Falta captura
  de UI ou teste com documento de caixas distintas.
- **`Direction` 0/1 → vertical/horizontal é inferência (média).** Base: `SizeReference`
  1..4 (`LeftMost`/`RightMost`) exige `Direction == 0` em `UpdateSizeReference`.
- **`ValidateAnchors` só foi lido por callees** (`YAGL::ToHorizontal`, `YAGL::ToVertical`,
  `MarkPosition::setAnchors`); a regra exata de normalização não foi reconstruída.
- **`0x180113BE0` (`MarkReader::PostProcessObject`)** referencia
  `PTR_s_AIDynamicMarks-BearerBar_18031F360`; o efeito (registro de tipo vs. criação) não foi
  confirmado.
- **COL/RTTI:** endereços de *Complete Object Locator* e símbolos `??_R*` não existem no
  formato exportado; slots de vtable (índice de `regenerateMarkImp`, `Clone`, etc.) não foram
  numerados para estas classes.
- **Diff v240×v250:** não executado. Nenhuma afirmação de comportamento idêntico entre
  versões deve ser feita.

## Reprodução

```powershell
$env:JAVA_HOME = 'C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot'
$headless = 'H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat'
$sp = 'H:\Desktop\ArtPlus\tools\ghidra_analysis\ghidra_scripts'

# xrefs + descompilação (sem import)
& $headless 'H:\Desktop\ArtPlus\tools\ghidra_projects' ArtProPlus `
  -process DocumentMarks.dll -noanalysis -readOnly -scriptPath $sp `
  -postScript DumpXrefs.java 0x18001E3C0 0x18001F870 0x18012FAA0 0x180132A70 0x180305370 `
  -postScript DecompileAddr.java 0x18001E3C0 0x18001F870 0x18001FDB0 0x18012FAA0 0x180132A70

# constantes numéricas
& $headless 'H:\Desktop\ArtPlus\tools\ghidra_projects' ArtProPlus `
  -process DocumentMarks.dll -noanalysis -readOnly -scriptPath $sp `
  -postScript DumpData.java 0x180305518 0x180305520 0x1803066E0 0x1803082D0 0x1803066C0
```

Logs: `tools/ghidra_analysis/bearerbar_run.log`, `bearerbar_run2.log`, `bearerbar_run3.log`.
Saídas: `xrefs_focus.txt`, `data_dump.txt`, `decompiled_addr/` (em `rag/ghidra/exports/DocumentMarks.dll/`).
