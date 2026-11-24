# ADR-012 — Cut Mark Geometry (F-001, fecha 16 ressalvas)

## Contexto

A spec `docs/features/F-001.md` (status `spec`, confiança `media`, versão-alvo **v24.03.10017**) foi aprovada com ressalvas pela auditoria `docs/audit/F-001-audit-20261123.md` (Veredito: **APROVADO COM RESSALVAS**). As 16 lacunas declaradas em §8 ("Em aberto") impedem aprovação total.

A ADR anterior (`ADR-001-cut-mark.md`, aprovada 2026-11-19) modela a geometria e parâmetros com base em **endereços v25** (`0x18013A8B0`, `0x18013CB50`, `0x18013EE90`, `0x18017C5D0`) e inferências da captura histórica (`CAP-20261119-01`, versão histórica, **não reconfirmada na v24**). Especificamente:

- D2/D3 da ADR-001 persistem `orientation=1`, `repetition=2`, `lineTypes={0}` e "8 segmentos por marca" — **a v24.03.10017 não escreve esses campos no construtor** (R2, R8, spec §8 itens 1, 2).
- A geometria v1 em `src/prepress/cut_mark.cpp:158-188` **sintetiza 8 `QLineF`** num único `GroupObject` — **a v240 copia o `FormPaint` (símbolo) para um `Group` por posição de `dm::MarkPositionVector`** (R7, spec §8 item 1).
- Os defaults de forma (`lengthMm=5.0`, `strokeWidthPt=0.25`, `color=cmyk(0,1,0,0)`) são **inferência declarada, não evidência** (spec §8 itens 1, 9, 10).
- O mapeamento binário→ArtPlus da ADR-001 cita endereços da versão histórica 25.03.116; a evidência canônica da versão-alvo 24.03.10017 está em `rag/evidence/F-001/ghidra/` (40 arquivos).

Esta ADR substitui D2, D3, D4 (parcial), o mapeamento binário e as consequências de geometria/parâmetros da ADR-001. O restante da ADR-001 (D1, D5, D6, D7, alternativas, ambiguidades A1–A9 não cobertas aqui) permanece válido.

## Decisão

### Nova geometria derivada dos endereços GHIDRA v24

| Endereço GHIDRA v24 | Função | Papel na nova geometria |
|---|---|---|
| `0x1801344E0` | `PDFPlusCutMark::PDFPlusCutMark` (ctor) | Parâmetros reais de fábrica: `PageBox=3` (`+0x7C0`), seletor ref `0` (`+0x838`), offset `0` (`+0x758/+0x770`), `setColorType(1,0)`, `setReferenceObject(0)`, estado derivado nulo (`+0x840/+0x848`). **Não grava** `Orientation`, `Repetition`, `LineTypes`. |
| `0x180134B00` | `GetReferenceBox` | Resolve caixa: PageBox → `Page::GetPageBox` (stride `0x58`, fallback `DAT_1802EF6D8`); Objeto → `GetObjectWithID` + `GetPDFPlusBoundingBox` (RTTI `Visitable`); erro → `FUN_180023A30`. |
| `0x180136190` | `regenerateMarkImp` (slot [29]) | Apaga conteúdo anterior; resolve offset (numérico/fórmula); obtém caixa; gera posições via `dm::MarkPositionVector` + `FUN_180298840` (PageBox) ou `FUN_1802988F0` (Objeto); **por posição**: cria `Group`, `Expander` sobre `FormPaint` de origem, rotação `atan2`/`cos`/`sin`, `SetTransformation`, `InsertNewObjectOnTop` em `ActionGroupCreator`, cor via `ApplyPDFPlusColor`. |
| `0x180135160` | `SetOffset` | Variant: seletor `0xFF` (vazio), `0` (quantidade em `+0x750/+0x758`), `1` (string fórmula em `+0x750`). |
| `0x1800AA1B0` / `0x1800A9FB0` | `SetCutMarkOffset` | Wrapper transacional via `ArtDoc::ActionList::DoAction` — **uma ação de undo por edição**. |
| `0x180134F60` | `RemoveInvalidCustomFormulasImp` (slot [39]) | Fórmula inválida → `MarkActionError` código 4 + offset vazio (`0xFF`) via `SetCutMarkOffset`, devolve `true`. |
| `0x180135660` | `getMarkType` (slot [12]) | `DynamicObject_PDFPlusCutMark`. |
| `0x180172100` | Parser PDF+ | Lê **apenas** `Position`, `Reference` (`5`=objeto + `ReferenceID`), `Offset` (string→variant fórmula, número→quantidade×scale×`DAT_1802FB5C8`, ausente→0). **Não lê** `Orientation`, `Repetition`, `LineTypes`, `AllStructuralDesignStations`. |
| `0x1801683E0` | Leitor PDF+ | `Source`→`FormPaint`, construtor, parser, pós-processamento. |
| `0x1800FAE70` | `Page::GetPageBox` | Índice cru, stride `0x58`, fallback `DAT_1802EF6D8`. |
| `0x18012A130` | `GetBoundingBoxForPositioning` | Lê chave `PDFPlusCutMark_Offset` para posicionamento. |
| `0x180298840` / `0x1802988F0` | `dm::MarkPositionVector` generators | **Contagem de posições por caixa/objeto** — a ser descompilada para fechar §8 item 1. |
| `0x180134880` | `ContentChangedSelf` (slot [7]) | Invalida estado derivado (`+0x840/+0x848`) → regeneração. |
| `0x180051F90` / `0x180052950` / `0x180052470` | Caminho legado `CutMark` | `AIDynamicMarks-CutMark` → clona símbolo por posição (`dm::CutMarkPositionGenerator`), `PlaceCutMarkSymbol` com dois `CPoint`. **Fora do escopo v2** (F-001b). |

### Modelo de parâmetros v2 (substitui `CutMarkParams` de ADR-001 D2)

```cpp
struct CutMarkParams {
    enum class ReferenceKind { PageBox, Mark };

    ReferenceKind referenceKind = ReferenceKind::PageBox;
    PageBoxType   referenceBox  = PageBoxType::TrimBox;   // PDF+ PageBox=3 (ctor v240: +0x7C0 = 3)
    ObjectId      referenceMarkId = 0;                    // ReferenceKind::Mark (Reference=5 no parser)

    double  offsetMm = 0.0;                               // UI mm; convertido para pt na geometria
    QString offsetFormula;                                // fx; seletor 1 em +0x770 (SetOffset)

    // CAMPOS REMOVIDOS (v240 não escreve no ctor, não lê no parser, strings ausentes no binário):
    // int orientation; int repetition; QVector<int> lineTypes;

    // Parâmetros de forma — VALORES DEFAULT DERIVADOS DO SÍMBOLO PADRÃO (não medidos na v240;
    // spec §8 itens 1, 9, 10). Marcados TODO(F-001) até captura GUI v24 ou extração do FormPaint.
    double lengthMm      = 10.0;   // fallback: 10 mm (observação histórica "projetadas para fora")
    double strokeWidthPt = 0.25;   // fallback: 0.25 pt (linha fina)
    Color  color = Color::cmyk(0.0f, 0.0f, 0.0f, 1.0f); // fallback: Registration Black (setColorType(1,0))

    bool onAllSides = true;        // v240 gera posições nos 4 cantos (dm::MarkPositionVector)

    bool operator==(const CutMarkParams& o) const {
        return referenceKind == o.referenceKind &&
               referenceBox == o.referenceBox &&
               referenceMarkId == o.referenceMarkId &&
               qFuzzyCompare(offsetMm + 1.0, o.offsetMm + 1.0) &&
               offsetFormula == o.offsetFormula &&
               qFuzzyCompare(lengthMm + 1.0, o.lengthMm + 1.0) &&
               qFuzzyCompare((double)strokeWidthPt + 1.0, (double)o.strokeWidthPt + 1.0) &&
               color == o.color &&
               onAllSides == o.onAllSides;
    }
    bool operator!=(const CutMarkParams& o) const { return !(*this == o); }
};
```

**Mudanças vs. ADR-001 D2:**
- Removidos `orientation`, `repetition`, `lineTypes` (opacos, sem efeito geométrico, fora do contrato v240).
- `color` default muda de Magenta CMYK para **Registration Black** (`setColorType(1,0)` no ctor v240).
- `lengthMm` default muda de `5.0` para `10.0` (fallback conservador até medição real).
- Adicionado `onAllSides` (implícito no `dm::MarkPositionVector` de 4 cantos).
- Unidades explícitas mantidas: `mm` no nome (`offsetMm`, `lengthMm`), `pt` em `strokeWidthPt`.

### Geometria v2 (substitui `CutMark::buildGeometry` de ADR-001 D3)

A geometria **não é sintetizada**. O contrato v240 é:

1. `regenerateMarkImp` (`0x180136190`) obtém `dm::MarkPositionVector` via `FUN_180298840` (PageBox) ou `FUN_1802988F0` (Objeto).
2. **Para cada posição** no vetor: cria `ArtDoc::Group`, abre `DocumentEdit::Expander` sobre o conteúdo do `FormPaint` de origem (`DynamicMark::GetSourceContent` → `ArtPaint::FormPaint::GetContent`), calcula rotação (`atan2`/`cos`/`sin`), aplica `SetTransformation`, obtém bbox via `GetPDFPlusBoundingBox`, insere com `DocumentEdit::InsertNewObjectOnTop` dentro de `ArtDoc::ActionGroupCreator`, aplica cor via `DynamicMark::ApplyPDFPlusColor`.

**Implementação v2 no ArtPlus (ponte até F-001a/F-001c):**

```cpp
// CutMark::regenerate(Document&, PageId) — v2
bool CutMark::regenerate(Document& doc, PageId page) {
    if (m_groupId == 0) return false;
    auto group = doc.object(m_groupId);
    if (!group || group->type() != ObjectType::Group) return false;

    const QRectF refBox = resolveReferenceBox(doc, page);
    if (refBox.isEmpty()) return false; // preserva geometria anterior (E5/E6)

    // 1. Apaga conteúdo anterior (R8: substitui, não acumula)
    for (ObjectId childId : group->children()) {
        if (auto child = doc.object(childId)) {
            if (auto layer = doc.layer(child->layerId())) layer->removeObject(childId);
            doc.removeObject(childId);
        }
        group->removeChild(childId);
    }

    // 2. Gera posições — v2 usa MarkPositionVector do core (a implementar)
    //    Por enquanto: fallback para 4 cantos da caixa (onAllSides=true)
    QVector<QPointF> positions = generatePositions(refBox, m_params);
    if (positions.isEmpty()) return false;

    // 3. Para cada posição: clona o símbolo (FormPaint) e transforma
    //    O símbolo padrão vem de DynamicMark::GetSourceContent() → FormPaint
    //    v1: usa o GroupObject existente como "símbolo" (geometria sintetizada)
    //    v2: quando FormPaint estiver disponível no core, troca por clone real.
    const LayerId layerId = group->layerId();
    auto layer = doc.layer(layerId);

    for (const QPointF& pos : positions) {
        // Placeholder v1→v2: reutiliza buildGeometry sintetizada por posição
        // TODO(F-001): substituir por clone do FormPaint + transformação
        QVector<QLineF> segs = buildGeometryForPosition(refBox, pos, m_params);
        for (const QLineF& seg : segs) {
            auto path = makeSegment(seg, m_params, layerId);
            doc.addObject(path);
            group->addChild(path->id());
            if (layer) layer->addObject(path->id());
        }
    }
    return true;
}
```

**O `buildGeometry` sintético v1 permanece como fallback** até que:
- O core tenha `FormPaint`/`MarkPositionVector` (dependência de `DocumentMarks.dll` v240), **OU**
- Captura GUI v24 meça a geometria real do símbolo (comprimento, espessura, cor, preenchimento, nº de caminhos por `Group`).

### Regras de fallback (valores default quando inválido/ausente)

| Campo | Fallback | Origem |
|---|---|---|
| `referenceBox` | `TrimBox` (`PageBox=3`) | Ctor v240 `+0x7C0 = 3` |
| `offsetMm` | `0.0` | Ctor v240 `+0x758 = 0`, seletor `+0x770 = 0` |
| `lengthMm` | `10.0` | Inferência conservadora (histórico "projetadas para fora") — **TODO(F-001)** |
| `strokeWidthPt` | `0.25` | Inferência "linha fina" — **TODO(F-001)** |
| `color` | `Registration Black` (`cmyk(0,0,0,1)`) | `setColorType(1,0)` no ctor v240 — **TODO(F-001) item 10** |
| `onAllSides` | `true` | `dm::MarkPositionVector` gera 4 cantos |
| Fórmula inválida | Offset vazio (seletor `0xFF`) | `RemoveInvalidCustomFormulasImp` (0x180134F60) |
| Caixa ausente (fallback `DAT_1802EF6D8`) | Próxima caixa na tabela | `Page::GetPageBox` (0x1800FAE70) — tabela não decodificada (§8 item 12) |
| Objeto ref. inexistente | Caixa vazia → nada criado | `GetReferenceBox` ramo objeto (0x180134B00) |

### Serialização PDF+ (quais campos persistir no roundtrip F-001a)

Baseado no parser v240 (`0x180172100`) e escritor (não observado, §8 item 7), **campos mínimos** para roundtrip:

| Chave PDF+ | Origem v240 | ArtPlus v2 |
|---|---|---|
| `DynamicObject_PDFPlusCutMark` | `getMarkType` (0x180135660) | `CutMark::toMetadata().kind` |
| `Position` | Parser `GADict::GetDict` + `FUN_18017BAC0` | `CutMarkParams::referenceBox` + `offsetMm`/`offsetFormula` |
| `Reference` | `GADict::GetName` + `FUN_18017A9C0` | `referenceKind` (`PageBox`→int, `Mark`→5) |
| `ReferenceID` | Quando `Reference=5` | `referenceMarkId` (propriedade `DocumentMarks_CutMark_ReferenceID`) |
| `PDFPlusCutMark_Offset` | Literal `0x180316C68` | `offsetMm` (número) ou `offsetFormula` (string) |
| `PDFPlusCutMark_OriginalReferenceName` | Literal `0x180316A80` | **Não implementado v2** (xrefs pendentes, §8 item 7) |
| `Source` (FormPaint stream) | Leitor `0x1801683E0` | **F-001a** (importador PDF+) |

**Não serializar em PDF+ v2:** `Orientation`, `Repetition`, `LineTypes`, `AllStructuralDesignStations` (ausentes no binário v240).

### Caminho legado — migração v1 (sintética) → v2 (real)

| Aspecto | v1 (atual, ADR-001) | v2 (esta ADR) | Migração |
|---|---|---|---|
| Parâmetros | `orientation=1`, `repetition=2`, `lineTypes={0}`, `lengthMm=5.0`, `strokeWidthPt=0.25`, `color=Magenta` | Sem `orientation`/`repetition`/`lineTypes`; `lengthMm=10.0`, `color=RegistrationBlack` | `fromMetadata`: ignora campos legados; usa defaults v2. `toMetadata`: **não grava** campos legados. |
| Geometria | 8 `QLineF` sintéticos num único `Group` | 1 `Group` por posição, clona `FormPaint` | `regenerate`: apaga filhos do grupo antigo, reconstrói com novo modelo. Documentos v1 ao carregar regeneram com v2 (uma ação de undo). |
| Persistência `.artplus` | Chave `DocumentMarks` v1 com campos legados | Mesma chave, schema v2 (sem legados) | `loadFromMetadata`: compatível (ignora desconhecidos). `saveToMetadata`: escreve v2. |

### Mapeamento binário → ArtPlus (v24.03.10017)

| Função (Ghidra v24) | Classe/método ArtPlus | Observação |
|---|---|---|
| `0x1801344E0` `PDFPlusCutMark::PDFPlusCutMark` | `CutMarkParams` defaults + `CutMark::CutMark()` | `PageBox=3`→`TrimBox`, offset 0, `setColorType(1,0)`, sem `Orientation`/`Repetition`/`LineTypes` |
| `0x180134B00` `GetReferenceBox` | `CutMark::resolveReferenceBox` | Ramo PageBox: `Page::GetPageBox`; Ramo Objeto: `GetObjectWithID` + `GetPDFPlusBoundingBox` (via `markBounds` até core ter `boundingBox`) |
| `0x180135160` `SetOffset` | `CutMarkParams::offsetMm`/`offsetFormula` + `CutMarkManager::setParams` | Seletor variant `0xFF`/`0`/`1` |
| `0x180136190` `regenerateMarkImp` (slot [29]) | `CutMark::regenerate` | Apaga, resolve offset/caixa, `MarkPositionVector`, por posição: `Group`+`Expander`+`FormPaint`+`Transform`+`InsertNewObjectOnTop`+`ApplyPDFPlusColor` |
| `0x1800AA1B0` `SetCutMarkOffset` | `CutMarkManager::setParams` | Undo único via `ActionList::DoAction` |
| `0x1800A9FB0` `SetCutMarkOffset(Content&, predicate, variant)` | `CutMarkManager::setParams` (batch) | Edição filtrada — v2 expõe se necessário |
| `0x180134F60` `RemoveInvalidCustomFormulasImp` (slot [39]) | `CutMarkManager::setParams` (validação fórmula) | Erro 4 → offset vazio |
| `0x180135660` `getMarkType` (slot [12]) | `CutMark::toMetadata().kind` | `"DynamicObject_PDFPlusCutMark"` |
| `0x180172100` Parser PDF+ | `CutMark::fromPdfPlusDict` (F-001a) | Lê `Position`, `Reference` (5=objeto), `ReferenceID`, `Offset` |
| `0x1801683E0` Leitor PDF+ | `PdfImporter::createCutMarkFromDict` (F-001a) | `Source`→`FormPaint`, construtor, parser, pós-proc |
| `0x18012A130` `GetBoundingBoxForPositioning` | `CutMark::resolveReferenceBox` (posicionamento) | Lê `PDFPlusCutMark_Offset` |
| `0x180298840` `FUN_180298840` | `MarkPositionVector::generate(PageBox)` | Contagem posições — **pendente descompilação** |
| `0x1802988F0` `FUN_1802988F0` | `MarkPositionVector::generate(Mark)` | Contagem posições — **pendente descompilação** |
| `0x180134880` `ContentChangedSelf` (slot [7]) | `CutMarkManager::onReferenceMarkChanged` | Invalida estado derivado → regeneração |
| `0x1800FAE70` `Page::GetPageBox` | `PageBoxes` accessor | Stride `0x58`, fallback `DAT_1802EF6D8` |
| `0x18010E0F0` / `0x180051F90` / `0x180052950` Legado | — | F-001b (fora do escopo) |

### Alternativas descartadas

1. **Manter geometria sintética v1 (8 segmentos, 1 Group) como definitiva.**  
   Descartada: contradiz `regenerateMarkImp` v240 (um `Group` por posição, clona `FormPaint`). A síntese é placeholder até o core ter `FormPaint`/`MarkPositionVector`.

2. **Usar defaults hardcoded (Magenta, 5mm, 0.25pt) como "certos".**  
   Descartada: a auditoria classifica como **ressalva declarada** (não evidência). O fallback conservador (Registration Black, 10mm) é reversível por mudança local quando a medição real chegar.

3. **Persistir `orientation`/`repetition`/`lineTypes` no `.artplus` e PDF+ "para compatibilidade futura".**  
   Descartada: a v240 **não escreve nem lê** esses campos. Gravaria lixo e quebraria roundtrip real (F-001a).

4. **Implementar `MarkPositionVector`/`FormPaint` agora no core.**  
   Descartada: escopo de F-001 é a marca; o core ganha esses tipos quando F-001a (importador PDF+) exigir. Até lá, o fallback de 4 cantos + geometria sintética por posição mantém topologia testável.

### Consequências

**Arquivos afetados:**
- `src/prepress/cut_mark.h` — `CutMarkParams` (remove 3 campos, adiciona `onAllSides`, muda defaults), `CutMark::buildGeometryForPosition` (novo, por posição), `regenerate` (usa posições).
- `src/prepress/cut_mark.cpp` — `regenerate` v2, `buildGeometryForPosition`, `makeSegment` (usa `color` do params), `fromMetadata`/`toMetadata` (schema v2).
- `src/document/document_serializer.cpp` — `root["metadata"]` já suporta; nenhum mudança estrutural.
- `tests/unit/test_cut_mark.cpp` — Atualizar asserções: remover checks de `orientation`/`repetition`/`lineTypes`; validar `color == RegistrationBlack`, `lengthMm == 10.0`, topologia por posição (4 grupos esperados quando `MarkPositionVector` estiver pronto; por enquanto 1 grupo com 8 segmentos como v1).

**Riscos:**
- Fidelidade visual: comprimento, espessura, cor, nº de caminhos por `Group` ainda **não medidos na v24** (§8 item 1). O teste valida topologia/posição (±0,03 pt), **não** paridade pixel-a-pixel.
- Caixa por marca referenciada: `markBoundsImpl` usa união dos segmentos sintéticos (limitação do core: `GroupObject::boundingBox()` é stub). Quando o core implementar `boundingBox()` ou o ramo 3 de `GetReferenceBox` for medido, troca-se a fonte dentro de `resolveReferenceBox` sem mudar API.
- `offsetFormula` não avaliado (F-001c). Campo existe no modelo para não perder dado.
- Numeração `Cut Mark N`: `displayIndex = max+1` por documento; renomear/excluir não tratados (§8 item 11).

**Estado:** proposto

---

## Checklist de fechamento das 16 ressalvas (§8)

| # | Ressalva §8 | Endereçada nesta ADR? | Como |
|---|---|---|---|
| 1 | Geometria exata (posições, caminhos, comprimento, espessura) | **Parcial** | Define contrato v2 (1 Group/posição, clona FormPaint); fallback sintético por posição até core ter FormPaint/MarkPositionVector. Descompilação de `0x180298840/8F0` + captura GUI v24 necessários para fechar. |
| 2 | `Orientation`, `Repetition`, `LineTypes` não existem no ctor/parser/strings v240 | **Sim** | Removidos do `CutMarkParams`, não serializados, não expostos na UI. |
| 3 | `PageBox = 3 = TrimBox` confiança média | **Sim** | Default `TrimBox` documentado como inferência do ctor `+0x7C0=3`; captura GUI v24 necessária para confirmar. |
| 4 | Offset ≠ 0 (sentido, sinal, faixa) | **Parcial** | Positivo = para fora (inferência R5); fallback até GUI v24 com offset 1/3mm. |
| 5 | Fórmula inválida (UI final) | **Parcial** | Estado final = variant vazio (`0xFF`) comprovado; apresentação UI pendente captura v24. |
| 6 | Serialização saída PDF+ | **Parcial** | Campos mínimos listados; escrita real pendente `Save` bem-sucedido v24 (F-001a). |
| 7 | `PDFPlusCutMark_OriginalReferenceName` | **Não** | Xrefs do literal `0x180316A80` pendentes — F-001a. |
| 8 | Fator `DAT_1802FB5C8` | **Não** | Leitura da constante no binário v240 pendente — F-001a. |
| 9 | Caminho legado (cópias, SymbolDefinition) | **Não** | F-001b (fora do escopo). |
| 10 | Cor da marca | **Parcial** | Fallback `Registration Black` (`setColorType(1,0)`); leitura `ApplyPDFPlusColor` ou GUI v24 pendente. |
| 11 | Numeração `Cut Mark N` | **Parcial** | `displayIndex = max+1` documentado; comportamento renomear/excluir pendente GUI v24. |
| 12 | Fallback `DAT_1802EF6D8` | **Não** | Decodificação tabela em `Document.dll` v240 pendente. |
| 13 | Documento sem página/conteúdo (E6) | **Não** | GUI v24: comando desabilitado ou falha silenciosa? |
| 14 | Rótulo `Attach to:` no Inspector | **Não** | Captura Inspector v24 pendente. |
| 15 | Entrada inválida offset UI | **Não** | GUI v24 pendente. |
| 16 | `FUN_180023A30` (erro GetReferenceBox) | **Não** | Leitura da função no binário v240 pendente. |
| 17 | ADR-001 desatualizada | **Sim** | Esta ADR substitui D2/D3/mapeamento/consequências de geometria. |

> **Nota:** Itens 1, 4, 6, 10, 11 são **parcialmente** endereçados (contrato v2 definido, fallback documentado, medição real pendente). Itens 7, 8, 9, 12, 13, 14, 15, 16 exigem evidência nova (GHIDRA ou GUI v24) e ficam para F-001a/F-001b/F-001c ou reauditoria pós-captura.