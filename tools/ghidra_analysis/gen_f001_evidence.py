# -*- coding: utf-8 -*-
"""Gera a evidencia Ghidra de F-001 (Cut Mark) a partir das extracoes reais
do programa DocumentMarks.dll v24.03.10017 (projeto Ghidra DocMarks_v240).

Nao inventa: cada arquivo usa nome/assinatura/tamanho/xrefs/strings lidos dos
dumps em rag/evidence/F-001/ghidra/raw_v240/addr_<hex>.txt.
"""
import os

OUT = r"H:\Desktop\ArtPlus\rag\evidence\F-001\ghidra"
SHA = "E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102"
SRC = "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"

FILES = []


def add(name, nome, addr, confianca, xrefs, strings, body):
    header = [
        "---",
        "modulo: DocumentMarks.dll",
        "versao: 24.03.10017",
        "funcao: %s" % addr,
        "endereco: %s" % addr,
        "nome: %s" % ('"' + nome.replace('"', "'") + '"'),
        "confianca: %s" % confianca,
        "xrefs: [%s]" % ", ".join('"%s"' % x for x in xrefs),
        "strings: [%s]" % ", ".join('"%s"' % s.replace('"', "'") for s in strings),
        'fonte: "%s"' % SRC,
        "---",
        "",
    ]
    FILES.append((name, "\n".join(header) + body.strip() + "\n"))


# ---------------------------------------------------------------- ctor v240
add(
    "DocumentMarks__0x1801344E0.md",
    "DocumentMarks::PDFPlusCutMark::PDFPlusCutMark",
    "0x1801344E0",
    "alta",
    ["0x18016A40F", "0x1803AA3D0", "0x18048678C"],
    [],
    """
# PDFPlusCutMark::PDFPlusCutMark (construtor de criacao) — v24.03.10017

## Identificacao

- Endereco: `0x1801344E0` (corpo `0x1801344E0`–`0x1801345DE`, 255 bytes)
- Nome qualificado: `DocumentMarks::PDFPlusCutMark::PDFPlusCutMark`
- Assinatura: `PDFPlusCutMark * __thiscall (PDFPlusCutMark *this, std::shared_ptr<ArtPaint::FormPaint const> formPaint)`
- Convencao: `__thiscall`; nao e thunk; nao e externo.

## Xrefs

- Chamado por `FUN_1801683E0` em `0x18016A40F` (leitor de marcas PDF+), logo apos
  alocar `0x850` bytes.
- Referencias de dados: `0x1803AA3D0`, `0x18048678C` (tabelas de ponteiros do modulo).
- Entrada de vtable: nao e chamado por vtable; e construtor chamado diretamente.

## O que a funcao faz (decompilado)

1. `DynamicMark::DynamicMark(this, false, 0x1CE)` — inicializa a base dinamica.
2. Instala as duas vftables da classe: `this+0x000` (ListItem) e `this+0x020` (Visitable).
3. Zera/inicializa os campos do objeto:
   - `this+0x758 = 0` — coordenada do offset (quantidade);
   - `this+0x770 = 0` — seletor do variant de offset (0 = quantidade);
   - `this+0x7B8 = 0` — referencia de objeto auxiliar;
   - `this+0x7C0 = 3` — `PageBox` de referencia (inteiro cru);
   - `this+0x838 = 0` — seletor de referencia (0 = PageBox);
   - `this+0x840 = 0` e `this+0x848 = 0` — par de ponteiros (`shared_ptr` de estado interno).
4. `DynamicMark::SetSourceContent(this, formPaint)` — guarda o `FormPaint` de origem.
5. `DynamicObject::setColorType(this, 1, 0)` — tipo de cor inicial.
6. `MarkPosition::setReferenceObject(this+0x390, 0)` — referencia inicial nula.

## Por que sustenta F-001 (Cut Mark)

- Prova direta de R2 na v240 para os defaults que existem nesta versao:
  `PageBox = 3` (`+0x7C0`), seletor de referencia `0` (`+0x838`), offset
  quantidade `0` (`+0x758`/`+0x770`) e `setColorType(1,0)`.
- `+0x7C0 = 3` e o valor que `GetReferenceBox` (`0x180134B00`) entrega a
  `ArtDoc::Page::GetPageBox`; a UI exibir `Trim Box` como default e consistente
  com o indice 3, mas a ordem do enum nao tem nome no binario (inferencia mantida
  em F-001 §4, confianca media).
- **Diferenca v240 x v250:** a v25 inicializa tambem `Orientation=1`,
  `Repetition=2` e um vetor `LineTypes=[0]` em `+0x790/+0x794/+0x798`. A v240
  **nao escreve** esses campos neste construtor e o layout de campos mudou
  (`+0x708/+0x780/+0x788` na v25 vs `+0x7C0/+0x838` na v240). Portanto a tabela
  de R2 com `Orientation`/`Repetition`/`LineTypes` **nao vale para a v240**;
  ver `manifest.json` -> `bloqueios`.

## Confianca

Alta: fluxo e valores lidos diretamente do decompilado e dos xrefs; a unica
inferencia e a correspondencia `3 = TrimBox` (media, declarada acima).
""",
)

# ------------------------------------------------------------ regenerate v240
add(
    "DocumentMarks__0x180136190.md",
    "DocumentMarks::PDFPlusCutMark::regenerateMarkImp",
    "0x180136190",
    "alta",
    ["0x180316B98", "0x1803AC1EC", "0x1804868D0"],
    [],
    """
# PDFPlusCutMark::regenerateMarkImp — v24.03.10017

## Identificacao

- Endereco: `0x180136190` (corpo `0x180136190`–`0x180136DE2`, 3143 bytes)
- Nome qualificado: `DocumentMarks::PDFPlusCutMark::regenerateMarkImp`
- Assinatura: `void __thiscall regenerateMarkImp(PDFPlusCutMark *this)`
- Slot de vtable: `0x180316B98` = vftable `0x180316AB0` + 29 * 8 -> **slot [29]**.

## Xrefs

- Referencia de dados `0x180316B98` (slot [29] da vftable principal).
- Referencias de dados `0x1803AC1EC` e `0x1804868D0` (tabelas do modulo).
- Nao ha chamador direto: e invocado por vtable/regeneracao de marca.

## O que a funcao faz (decompilado)

1. **Apaga o conteudo anterior**: `DocumentEdit::Delete` em `0x180136223`.
2. **Zera estado derivado** e resolve o offset:
   - se `this+0x770 == 1` (formula), avalia a string com
     `Localization::Evaluate` e o functor `EvaluateFunction` (aprox. `0x180136314`);
   - se `this+0x770 == 0` (quantidade), converte `*(double*)(this+0x758)`
     pela unidade (`Localization::PointUnit`, `CanConvert`, `GetValueForUnit`).
3. **Obtem a caixa de referencia** com `GetReferenceBox` em `0x1801365B3`.
4. **Gera as posicoes**: instala um `dm::MarkPositionVector` (vftable em
   `local_9D8`) e chama `FUN_180298840(rect, vector)` para o caso PageBox; no
   caso referencia por objeto (`this+0x838 == 1`), obtem o objeto por
   `GetObjectWithID(this+0x7C0)`, valida `GridInterface` por RTTI e chama
   `FUN_1802988F0` para gerar as posicoes a partir do grid.
5. **Por posicao**, cria um `ArtDoc::Group` (`Group::Group(group, 0x1FF)`), abre
   um `DocumentEdit::Expander` com o conteudo do `FormPaint` de origem
   (`DynamicMark::GetSourceContent` -> `ArtPaint::FormPaint::GetContent`),
   calcula a rotacao com `atan2`/`cos`/`sin`, aplica `SetTransformation`, obtem
   o bounding box (`GetPDFPlusBoundingBox`) e, dentro de
   `ArtDoc::ActionGroupCreator`, insere com `DocumentEdit::InsertNewObjectOnTop`
   e aplica a cor com `DynamicMark::ApplyPDFPlusColor` (`0x180136CFx`).
6. Termina com `FUN_18004A3B0`/`FUN_180297130` liberando o vetor de posicoes.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R7 na v240 no essencial: apaga o conteudo anterior, resolve o offset
  (quantidade ou formula), resolve a caixa por `GetReferenceBox`, aplica cor e
  insere no topo do conteudo dentro de `ActionGroupCreator` (transacao de undo).
- Sustenta a regeneracao de R8: o conteudo e substituido, nao acumulado
  (`DocumentEdit::Delete` antes de inserir).
- **Diferenca v240 x v250:** na v240 a geometria e obtida **copiando o conteudo
  do `FormPaint` de origem** (via `Expander`) para um `Group` por posicao; a v25
  gera a geometria diretamente (8 `PathObject`). A contagem de posicoes vem de
  `dm::MarkPositionVector` e **nao foi contada** nesta extracao. Portanto o teste
  de R7 ("1 GroupObject com 8 PathObject") e uma expectativa da v25 e precisa ser
  revalidado/ajustado para a v240.

## Confianca

Alta para o fluxo de chamadas e para as operacoes de undo/insercao; media para
a forma geometrica final (depende de `dm::MarkPositionVector` e do conteudo do
`FormPaint`, nao decodificados nesta passagem).
""",
)

# ------------------------------------------------------------ GetReferenceBox
add(
    "DocumentMarks__0x180134B00.md",
    "DocumentMarks::PDFPlusCutMark::GetReferenceBox",
    "0x180134B00",
    "alta",
    ["0x1801365B3", "0x1803AB3D0", "0x1804867D4"],
    [],
    """
# PDFPlusCutMark::GetReferenceBox — v24.03.10017

## Identificacao

- Endereco: `0x180134B00` (corpo `0x180134B00`–`0x180134D91`, 658 bytes)
- Nome qualificado: `DocumentMarks::PDFPlusCutMark::GetReferenceBox`
- Assinatura: `YAGL::RectangleBase<YAGL::MilliPointCoordinateSystem> __thiscall GetReferenceBox(PDFPlusCutMark *this) const`
- Chamador unico: `regenerateMarkImp` (`0x1801365B3`).

## O que a funcao faz (decompilado)

1. `ContentObject::GetContent(this)`; se `nullptr`, devolve retangulo vazio
   (quatro doubles `0` + flag `1`).
2. Se `this+0x838 != 0`:
   - `+0x838 == 1` -> referencia por objeto: `Content::GetObjectWithID(content,
     *(uint64*)(this+0x7C0))`; objeto inexistente -> retangulo vazio; existente ->
     `DocumentMarks::GetPDFPlusBoundingBox` (com `RTTI` de `Visitable`).
   - qualquer outro valor -> `FUN_180023A30()` (caminho de erro sem retorno).
3. Se `this+0x838 == 0` -> referencia por caixa de pagina:
   `ContentObject::GetContent` -> `__RTDynamicCast` para `ArtDoc::PageContent`;
   se o cast falhar, retangulo vazio; senao `PageContent::GetPage` e
   `ArtDoc::Page::GetPageBox(page, *(PageBox*)(this+0x7C0))`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R3 e as excecoes E5/E6/E8 na v240, com os offsets desta versao:
  seletor em `+0x838`, `PageBox` em `+0x7C0`.
- Confirma que o caminho por caixa chama `Page::GetPageBox` (import de
  `DOCUMENT.DLL`), que indexa o array de caixas pelo inteiro cru.
- Confirma que referencia por objeto usa `GetObjectWithID` + bounding box e que
  objeto inexistente produz retangulo vazio (E5).
- **Diferenca v240 x v250:** a v25 usa `+0x780/+0x788/+0x708`; a v240 usa
  `+0x838/+0x7C0`. O comportamento e equivalente, os offsets nao.

## Confianca

Alta: leitura direta do decompilado e dos xrefs.
""",
)

# ------------------------------------------------------------ parser PDF+ v240
add(
    "DocumentMarks__0x180172100.md",
    "FUN_180172100 (parser PDF+ do Cut Mark)",
    "0x180172100",
    "alta",
    ["0x18016A437", "0x18048855C"],
    ["Position", "Reference", "ReferenceID", "Offset"],
    """
# Parser PDF+ do Cut Mark (FUN_180172100) — v24.03.10017

## Identificacao

- Endereco: `0x180172100` (corpo `0x180172100`–`0x180172593`, 1129 bytes)
- Nome atual: `FUN_180172100` (sem simbolo; identificado pelo chamador e pelas
  chaves lidas)
- Assinatura observada: `void __fastcall (GADict *dict, ArtDoc::ContentObject *mark, ... , double scale)`
- Chamado pelo leitor de marcas PDF+ `FUN_1801683E0` em `0x18016A437`, logo
  apos `DocumentMarks::PDFPlusCutMark::PDFPlusCutMark` (`0x18016A40F`).

## Chaves e fluxo (decompilado)

1. `Position`: `GADict::GetDict` + `FUN_18017BAC0` (parser de posicao).
2. `Reference`: `GADict::GetName` + `FUN_18017A9C0` (mapeia o nome para o enum):
   - valor `5` -> referencia por objeto: le `ReferenceID`, converte para UTF-8 e
     grava a propriedade **`DocumentMarks_CutMark_ReferenceID`**
     (ponteiro `0x180319958`);
   - qualquer outro valor -> `MarkPosition::ref2box` e
     `PDFPlusCutMark::SetReferenceObject` com a `PageBox` resultante.
3. `Offset`:
   - presente e string -> variant **formula** (`SetOffset` com seletor 1);
   - presente e numero -> variant **quantidade**: `valor * scale *
     DAT_1802FB5C8` (`SetOffset` com seletor 0);
   - ausente -> `0 * scale` (offset zero, seletor 0).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R3/R4 (referencia por PageBox e por `ReferenceID`), R5/R6 (offset
  quantidade/formula) e as chaves `Position`, `Reference`, `ReferenceID`,
  `DocumentMarks_CutMark_ReferenceID` de R10/R11.
- **Contradiz R11/E1/E2/E3 para a v240:** este parser **nao le** `Orientation`,
  `Repetition`, `LineTypes` nem `AllStructuralDesignStations`. Uma varredura
  ASCII/UTF-16 do binario v240 nao encontra os literais
  `AllStructuralDesignStations`, `LineTypes`, `Cut Mark has invalid Orientation
  value` ou `Cut Mark has invalid Repetition value` (existem na v250, nao na
  v240). A validacao descrita em R11 e as excecoes E1/E2/E3 sao da v25 e
  precisam ser revalidadas/removidas para a v24.
- O leitor v240 usa um esquema mais simples (Position/Reference/ReferenceID/
  Offset); a estrutura de `Orientation`/`Repetition` aparece em outras marcas,
  nao neste parser de Cut Mark.

## Confianca

Alta para chaves, ramos e chamadas (decompilado + strings referenciadas +
ausencia confirmada por varredura binaria). Media para o significado exato do
enum `Reference` (5 = objeto; os demais valores mapeiam para PageBox via
`ref2box`, sem nomes no binario).
""",
)

# ------------------------------------------------------------ SetOffset
add(
    "DocumentMarks__0x180135160.md",
    "DocumentMarks::PDFPlusCutMark::SetOffset",
    "0x180135160",
    "alta",
    ["0x180172375", "0x180172450", "0x1801724D5", "0x1800AA206"],
    [],
    """
# PDFPlusCutMark::SetOffset — v24.03.10017

## Identificacao

- Endereco: `0x180135160` (corpo `0x180135160`–`0x18013522C`, 205 bytes)
- Assinatura: `void __thiscall SetOffset(PDFPlusCutMark *this, const std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem>, std::string> &v)`
- Chamado pelo parser em `0x180172375`, `0x180172450` e `0x1801724D5`.
- Usado como ponteiro de metodo pelo wrapper `SetCutMarkOffset` (dados em
  `0x1800AA206`/`0x1800AA20D`).

## O que a funcao faz (decompilado)

O seletor do variant esta em `v[0x20]`:

- `0xFF` -> limpa o offset: `FUN_18006C1A0(this+0x750)` e `this+0x770 = 0xFF`
  (offset nao definido);
- `0x00` -> quantidade: grava 16 bytes em `this+0x750`/`this+0x758`; se o
  seletor anterior era `0xFF`, limpa antes;
- `0x01` -> formula: copia a string para `this+0x750` (`FUN_180017070`);
- transicao de quantidade para formula: limpa o estado anterior com
  `FUN_18000F510` e grava o novo variant, marcando `this+0x770 = 1`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R5/R6 na v240: o offset e um variant de tres estados
  (`0xFF` vazio, `0` quantidade, `1` formula) nos campos `+0x770` (seletor) e
  `+0x750/+0x758` (valor). A v25 usa `+0x6B8/+0x698`, com a mesma semantica.
- O parser v240 grava a formula como string e a quantidade escalada, exatamente
  o contrato que o `fx` da UI precisa produzir.

## Confianca

Alta: fluxo e offsets lidos diretamente no decompilado.
""",
)

# ------------------------------------------------------------ SetCutMarkOffset (v240, 2 overloads)
add(
    "DocumentMarks__0x1800AA1B0.md",
    "DocumentMarks::SetCutMarkOffset(PDFPlusCutMark&, variant)",
    "0x1800AA1B0",
    "alta",
    ["0x1801350D2", "0x1803AB78C", "0x180481DD0"],
    [],
    """
# SetCutMarkOffset(PDFPlusCutMark&, const variant&) — v24.03.10017

## Identificacao

- Endereco: `0x1800AA1B0` (corpo `0x1800AA1B0`–`0x1800AA339`, 393 bytes)
- Assinatura: `void __cdecl DocumentMarks::SetCutMarkOffset(DocumentMarks::PDFPlusCutMark &mark, const std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem>, std::string> &value)`
- Chamador unico: `PDFPlusCutMark::RemoveInvalidCustomFormulasImp` (`0x1801350D2`).

## O que a funcao faz (decompilado)

1. Monta um `std::function` getter do offset e um `std::function` setter que
   aponta para `PDFPlusCutMark::SetOffset` (`0x180135160`).
2. Normaliza o variant recebido (`0xFF` vazio, `0` quantidade, `1` string).
3. Cria a acao com `FUN_1800A9420` e executa
   `ArtDoc::Action::GetActionList` -> **`ArtDoc::ActionList::DoAction`**.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R5/R8 na v240: **toda alteracao de offset passa por
  `ActionList::DoAction`**, ou seja, e uma acao undoable unica.
- E o caminho usado por `RemoveInvalidCustomFormulasImp` (E4) para remover a
  formula invalida.

## Confianca

Alta: presenca de `ActionList::DoAction` e do setter `SetOffset` e explicita no
decompilado.
""",
)

add(
    "DocumentMarks__0x1800A9FB0.md",
    "DocumentMarks::SetCutMarkOffset(Content&, predicate, variant)",
    "0x1800A9FB0",
    "alta",
    ["0x1803AB788", "0x180481DC4"],
    [],
    """
# SetCutMarkOffset(Content&, predicate, const variant&) — v24.03.10017

## Identificacao

- Endereco: `0x1800A9FB0` (corpo `0x1800A9FB0`–`0x1800AA1B1`, 505 bytes)
- Assinatura: `void __cdecl DocumentMarks::SetCutMarkOffset(ArtDoc::Content &content, const std::function<bool(const PDFPlusCutMark&)> &predicate, const std::variant<...> &value)`
- Sem chamadores diretos no binario (variante usada por callbacks/acoes da UI).

## O que a funcao faz (decompilado)

1. Empacota getter/setter (`PDFPlusCutMark::SetOffset` em `0x180135160`).
2. Aloca uma acao (`0x120` bytes) e valida o predicado recebido.
3. Obtem `ArtDoc::Action::GetActionList` e executa
   **`ArtDoc::ActionList::DoAction`**.

## Por que sustenta F-001 (Cut Mark)

- Complementa R5/R8: a edicao de offset na v240 e uma acao undoable, com
  predicado de aplicabilidade (permite so aplicar a marcas que satisfacam a
  condicao, tipico de edicao em lote/selecao).
- O predicado explica por que existem duas sobrecargas: uma dirigida a uma marca
  (usada por E4) e uma dirigida a `Content` com filtro.

## Confianca

Alta para o uso de `ActionList::DoAction`; media para o papel do predicado na UI
(nao rastreado ate o chamador).
""",
)

# ------------------------------------------------------------ RemoveInvalid...
add(
    "DocumentMarks__0x180134F60.md",
    "DocumentMarks::PDFPlusCutMark::RemoveInvalidCustomFormulasImp",
    "0x180134F60",
    "alta",
    ["0x180316BE8", "0x1803AB6CC"],
    [],
    """
# PDFPlusCutMark::RemoveInvalidCustomFormulasImp — v24.03.10017

## Identificacao

- Endereco: `0x180134F60` (corpo `0x180134F60`–`0x180135154`, 500 bytes)
- Assinatura: `bool __thiscall RemoveInvalidCustomFormulasImp(PDFPlusCutMark *this)`
- Slot de vtable: `0x180316BE8` = `0x180316AB0 + 39*8` -> slot [39].

## O que a funcao faz (decompilado)

1. Só age se o offset for formula (`this+0x770 == 1`).
2. Valida a formula com `FUN_180147EE0` e `FUN_180148050`; se **ambas** falham:
   - reporta `MarkActionError` (codigo `4`) com o nome do objeto via
     `ArtDoc::Document::GetErrorReporter`;
   - chama `DocumentMarks::SetCutMarkOffset(this, variant vazio)` em `0x1801350D2`;
   - devolve `true`.
3. Se o offset nao e formula ou a formula e valida, devolve `false`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta E4/R6 na v240: formula invalida e **removida** por
  `SetCutMarkOffset`, e o estado final do offset e o variant vazio (`0xFF`),
  nao "ultimo valor valido". O erro e reportado ao `ErrorReporter` do documento.
- O slot [39] confirma que e um hook de pos-leitura da classe.

## Confianca

Alta para o fluxo e para o estado final vazio; media para a semantica exata dos
dois validadores (nao decompilados nesta passagem).
""",
)

# ------------------------------------------------------------ getPositionRefBBox
add(
    "DocumentMarks__0x180135670.md",
    "DocumentMarks::PDFPlusCutMark::getPositionRefBBox",
    "0x180135670",
    "media",
    ["0x180316BB0", "0x1803ABF04"],
    [],
    """
# PDFPlusCutMark::getPositionRefBBox — v24.03.10017

## Identificacao

- Endereco: `0x180135670` (corpo `0x180135670`–`0x1801358E1`, 625 bytes)
- Assinatura: `YAGL::RectangleBase<YAGL::MilliPointCoordinateSystem> __thiscall getPositionRefBBox(PDFPlusCutMark *this) const`
- Slot de vtable: `0x180316BB0` = `0x180316AB0 + 32*8` -> slot [32].

## O que a funcao faz (decompilado)

- Resolve a caixa de referencia de posicionamento a partir de
  `this+0x7C0`/`this+0x838`:
  - seletor 0 -> `PageContent::GetPage` + `Page::GetPageBox`;
  - seletor 1 -> `Content::GetObjectWithID` + `GetBoundingBoxForPositioning`
    (`0x18012A130`);
  - estados invalidos/nao ligados -> caminho vazio.
- Consulta `DynamicObject::isNotLinkedYet` e `GetTopLevelTargetContent` antes de
  resolver o objeto.

## Por que sustenta F-001 (Cut Mark)

- Fornece o bounding box usado na resolucao de formulas/posicionamento (R6):
  `GetBoundingBoxForPositioning` e quem referencia a chave
  `PDFPlusCutMark_Offset` (dados em `0x18012A2CF`/`0x18012A2D6`).
- Confirma que a mesma dupla `PageBox`/objeto de `GetReferenceBox` alimenta o
  posicionamento da marca.

## Confianca

Media: fluxo principal confirmado; a ligacao com a avaliacao da formula e
indireta (via `GetBoundingBoxForPositioning`) e nao foi seguida ate o avaliador.
""",
)

# ------------------------------------------------------------ getMarkType
add(
    "DocumentMarks__0x180135660.md",
    "DocumentMarks::PDFPlusCutMark::getMarkType",
    "0x180135660",
    "alta",
    ["0x180316B10", "0x1803ABE6C"],
    ["DynamicObject_PDFPlusCutMark"],
    """
# PDFPlusCutMark::getMarkType — v24.03.10017

## Identificacao

- Endereco: `0x180135660` (corpo `0x180135660`–`0x18013566E`, 14 bytes)
- Assinatura: `std::string_view __thiscall getMarkType(PDFPlusCutMark *this) const`
- Slot de vtable: `0x180316B10` = `0x180316AB0 + 12*8` -> slot [12].

## O que a funcao faz

Devolve um `std::string_view` apontando para o literal
`DynamicObject_PDFPlusCutMark`:
`*out = *(void**)0x180316C58; out[1] = *(uint64*)0x180316C60`.
O literal foi localizado em `0x180305DC8` na varredura de strings do binario.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R9/R10: o tipo persistido da marca na v240 e exatamente
  `DynamicObject_PDFPlusCutMark`, o que permite ao parser PDF+ reconhecer o
  objeto e ao painel `Marks` lista-lo como Cut Mark.

## Confianca

Alta: 14 bytes, retorno constante e literal conferido na varredura.
""",
)

# ------------------------------------------------------------ legacy dispatch
add(
    "DocumentMarks__0x18010E0F0.md",
    "FUN_18010E0F0 (createDynamicObject legado)",
    "0x18010E0F0",
    "alta",
    ["0x1803130E8", "0x180485328"],
    ["AIDynamicMarks-CutMark", "AIDynamicMarks-BearerBar", "AIDynamicMarks-CustomMark"],
    """
# createDynamicObject legado (FUN_18010E0F0) — v24.03.10017

## Identificacao

- Endereco: `0x18010E0F0` (corpo `0x18010E0F0`–`0x18010FD37`, 7239 bytes)
- Nome atual: `FUN_18010E0F0` (sem simbolo)
- Assinatura observada: `MarkReader` -> cria objeto dinamico a partir do
  dicionario de propriedades do mark set.

## O que a funcao faz (para Cut Mark)

1. Le o dicionario de propriedades (`MarkReader::GetPropertiesAsDictionary`).
2. Compara o nome do objeto com os tipos `AIDynamicMarks-*` via `memcmp`.
3. No ramo do Cut Mark:
   - `memcmp(PTR_s_AIDynamicMarks_CutMark_1802FDC48, name, 0x16)` em
     `0x18010F0DD` (22 bytes = `AIDynamicMarks-CutMark`);
   - aloca o objeto e chama **`DocumentMarks::CutMark::CutMark(this, true)`** em
     `0x18010F130`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R12.1 na v240: o caminho legado identifica
  `AIDynamicMarks-CutMark` por comparacao de 22 bytes e instancia
  `CutMark(true)`.
- Confirma que o nome do tipo legado e exatamente `AIDynamicMarks-CutMark`
  (literal em `0x1802FDC58`).

## Confianca

Alta: comparacao, tamanho e chamada do construtor sao explicitos no decompilado.
""",
)

# ------------------------------------------------------------ CutMark ctor
add(
    "DocumentMarks__0x180051F90.md",
    "DocumentMarks::CutMark::CutMark(bool)",
    "0x180051F90",
    "alta",
    ["0x18010F130", "0x1803AA328"],
    [],
    """
# CutMark::CutMark(bool) — v24.03.10017

## Identificacao

- Endereco: `0x180051F90` (corpo `0x180051F90`–`0x180051FCD`, 61 bytes)
- Assinatura: `CutMark * __thiscall CutMark(CutMark *this, bool own)` 
- Chamado pelo dispatch legado `FUN_18010E0F0` em `0x18010F130`.

## O que a funcao faz

1. `DynamicMark::DynamicMark(this, own, 0xFD)`.
2. `this+0x750 = 0` (offset/inicializacao da marca legada).
3. Instala as vftables `ListItem` (`this+0x000`) e `Visitable` (`this+0x020`).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R12.1: o objeto criado para `AIDynamicMarks-CutMark` e
  `DocumentMarks::CutMark` e nasce com offset zero.
- E a classe legada distinta de `PDFPlusCutMark`; a v240 mantem os dois caminhos.

## Confianca

Alta.
""",
)

# ------------------------------------------------------------ legacy regenerate
add(
    "DocumentMarks__0x180052950.md",
    "DocumentMarks::CutMark::regenerateMarkImp (legado)",
    "0x180052950",
    "alta",
    ["0x1802FDB48", "0x1803AC1CC"],
    [" Cut Mark update at \\n", "gridParams:\\n", "GridBbox mm:", "] -> ["],
    """
# CutMark::regenerateMarkImp (caminho legado) — v24.03.10017

## Identificacao

- Endereco: `0x180052950` (corpo `0x180052950`–`0x18005307C`, 1827 bytes)
- Assinatura: `void __thiscall regenerateMarkImp(CutMark *this)`
- Referencia de dados `0x1802FDB48` (slot de vtable da classe legada).

## O que a funcao faz (decompilado)

1. Obtem a caixa/objeto de referencia com
   `DynamicObject::getPositionRefBBox`/`getPositionRefObject` e
   `GetBoundingBoxForPositioning` (`0x18012A130`).
2. Gera as posicoes (`dm::CutMarkPositionGenerator`/vetor de posicoes) — as
   posicoes nao foram contadas nesta extracao.
3. Para cada posicao:
   - `ArtDoc::CloneStrategy::CloneStrategy(strategy, document, 1)`;
   - `DocumentEdit::ExtractObjectFromParent` + `DocumentEdit::InsertNewObjectAfter`;
   - `CutMark::PlaceCutMarkSymbol(this, newObj, CPoint*, CPoint*)` em
     `0x180052D22`.
4. Com nivel de debug (`GetMarksDebugLevel`) imprime, entre outros,
   `" Cut Mark update at \n"` (literal em `0x1802FDC78`).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R12.3/R12.4: o caminho legado **clona o simbolo** e o posiciona apos
  a marca, com `CPoint` de origem e destino — diferenca estrutural em relacao ao
  caminho PDF+.
- O literal de debug ` Cut Mark update at \n` confirma a identidade do fluxo.

## Confianca

Alta para a sequencia de clonagem/insercao; media para a quantidade de copias
(o vetor de posicoes de `dm::CutMarkPositionGenerator` nao foi contado).
""",
)

# ------------------------------------------------------------ PlaceCutMarkSymbol
add(
    "DocumentMarks__0x180052470.md",
    "DocumentMarks::CutMark::PlaceCutMarkSymbol",
    "0x180052470",
    "media",
    ["0x180052D22", "0x1803AB628"],
    [],
    """
# CutMark::PlaceCutMarkSymbol — v24.03.10017

## Identificacao

- Endereco: `0x180052470` (corpo `0x180052470`–`0x1800526EE`, 638 bytes)
- Assinatura: `void __thiscall PlaceCutMarkSymbol(CutMark *this, ArtDoc::ContentObject &symbol, const dm::CPoint &from, const dm::CPoint &to)`
- Chamado por `CutMark::regenerateMarkImp` em `0x180052D22`.

## O que a funcao faz

- Calcula a transformacao do simbolo clonado com `atan2`/`cos`/`sin`
  (biblioteca CRT) e aplica `DocumentEdit::Transform`.
- Usa `GetBoundingBoxForPositioning` (`0x18012A130`) para obter a caixa do
  objeto posicionado.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R12.3: o posicionamento e feito por par de `CPoint` (origem/destino)
  e transformacao geometrica, coerente com "posiciona copias do simbolo" do
  caminho legado.
- Explica por que o caminho legado difere do PDF+ (que gera grupos/geometria).

## Confianca

Media: assinatura e chamadas confirmadas; a formula exata da transformacao nao
foi detalhada nesta passagem.
""",
)

# ------------------------------------------------------------ parsePdfPropertiesDict
add(
    "DocumentMarks__0x180052700.md",
    "DocumentMarks::CutMark::parsePdfPropertiesDict",
    "0x180052700",
    "alta",
    ["0x1802FDAF8", "0x1803AC100"],
    ["CutMark", "DM-CutMarkParams", "DM-CutMarkParams-Offset", "DM-CutMarkParams-Version"],
    """
# CutMark::parsePdfPropertiesDict — v24.03.10017

## Identificacao

- Endereco: `0x180052700` (corpo `0x180052700`–`0x180052940`, 576 bytes)
- Assinatura: `bool __thiscall parsePdfPropertiesDict(CutMark *this, const std::map<std::string, ArtDoc::ContentObject*> &props)`
- Referencia de dados `0x1802FDAF8` (slot de vtable).

## O que a funcao faz (decompilado)

1. Chama `DynamicMark::parsePdfPropertiesDict` (parser da base).
2. Le o sub-dicionario **`DM-CutMarkParams`** do dicionario da marca.
3. Le as chaves `DM-CutMarkParams-Offset` e `DM-CutMarkParams-Version`
   (strings em `0x1803302A0` e `0x1803302E0`).
4. `DM-CutMarkParams-SymbolDefinition` existe no binario (`0x1803302B8`), mas
   **nao aparece referenciada nesta funcao** — o uso dessa chave esta em outro
   ponto do leitor legado (nao localizado nesta passagem).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R12.2 para as chaves `DM-CutMarkParams`, `-Offset` e `-Version`.
- Delimita a lacuna: `-SymbolDefinition` nao esta confirmado neste parser.

## Confianca

Alta para as chaves efetivamente referenciadas; media para o conjunto completo
do dicionario legado.
""",
)

# ------------------------------------------------------------ ApplyMarksFromSet
add(
    "DocumentMarks__0x180243EC0.md",
    "DocumentMarks::TaskMarkSets::ApplyMarksFromSet",
    "0x180243EC0",
    "alta",
    ["0x180243EB1", "0x1803AAD68"],
    [],
    """
# TaskMarkSets::ApplyMarksFromSet — v24.03.10017

## Identificacao

- Endereco: `0x180243EC0` (corpo `0x180243EC0`–`0x180243F2D`, 109 bytes)
- Assinatura: `bool __thiscall ApplyMarksFromSet(TaskMarkSets *this, const std::vector<std::unique_ptr<ArtDoc::Document>> &documents, ArtDoc::Page &target, bool flag)`
- Chamado por `ApplyExtraMarkSet` (`0x180243EB1`).

## O que a funcao faz

1. Itera o vetor de documentos.
2. Para cada documento, `ArtDoc::Document::GetPagesBegin` pega a **primeira
   pagina**.
3. Chama `TaskMarkSets::CopyMarksToPageWithLog(this, firstPage, target, flag)`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R13: a aplicacao por mark set copia o conteudo da primeira pagina de
  cada documento para a pagina alvo. Esse fluxo pertence a **F-002 (Mark Sets)**,
  nao a criacao da marca em F-001.
- Confirma que a entrada de marcas por mark set e um caminho separado da criacao
  direta (`Add Cut Mark`).

## Confianca

Alta: fluxo curto e integralmente legivel.
""",
)

# ------------------------------------------------------------ CopyMarksToPageWithLog
add(
    "DocumentMarks__0x180245380.md",
    "DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog",
    "0x180245380",
    "alta",
    ["0x180243F0E", "0x18024405E", "0x1802440BE", "0x1802440FE", "0x18024415E"],
    ["WARNING: Missing Named Objects", "WARNING: Missing Page Box"],
    """
# TaskMarkSets::CopyMarksToPageWithLog — v24.03.10017

## Identificacao

- Endereco: `0x180245380` (corpo `0x180245380`–`0x180245B79`, 2041 bytes)
- Assinatura: `void __thiscall CopyMarksToPageWithLog(TaskMarkSets *this, ArtDoc::Page &source, ArtDoc::Page &target, bool flag)`

## O que a funcao faz

1. Monta conjuntos de nomes/IDs ausentes e de page boxes ausentes.
2. Chama `DocumentMarks::CopyMarksToPage` (`0x1800426F0`) com esses conjuntos.
3. Emite avisos localizados quando ha objetos nomeados ausentes
   (`"WARNING: Missing Named Objects: %s.\nReferenced from Mark Set: %s.\nDynamic Marks linked to a missing object were removed from page %lu.\n"`,
   `0x18032AC70`) ou page boxes ausentes (`0x18032AD30`), usando as chaves
   `DocumentMarks.Warning.MissingNamedObject` / `...MissingPageBox`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta E5/E7 no contexto de mark set (F-002): referencias ausentes sao
  removidas/religadas com aviso, nao geram marca silenciosamente quebrada.
- Complementa R13 com o comportamento de log do caminho de aplicacao.

## Confianca

Alta para as chamadas e mensagens; media para o detalhe fino das religacoes.
""",
)

# ------------------------------------------------------------ ContentChangedSelf
add(
    "DocumentMarks__0x180134880.md",
    "DocumentMarks::PDFPlusCutMark::ContentChangedSelf",
    "0x180134880",
    "media",
    ["0x180316AE8", "0x1803AAE78"],
    [],
    """
# PDFPlusCutMark::ContentChangedSelf — v24.03.10017

## Identificacao

- Endereco: `0x180134880` (corpo `0x180134880`–`0x180134B03`, 636 bytes)
- Assinatura: `void __thiscall ContentChangedSelf(PDFPlusCutMark *this, ArtDoc::Content *changed, ArtDoc::Content *owner)`
- Slot de vtable: `0x180316AE8` = `0x180316AB0 + 7*8` -> slot [7].

## O que a funcao faz

1. Chama `DynamicMark::ContentChangedSelf` (base).
2. Se o objeto mudou (`changed != nullptr`), invalida o estado em `this+0x840`
   (`FUN_18002AB30`).
3. Para o documento dono, consulta o `ChangeCollector`
   (`ArtDoc::Document::GetChangeCollector`) e atualiza o `shared_ptr` interno
   (`this+0x840`/`this+0x848`).

## Por que sustenta F-001 (Cut Mark)

- Fornece o mecanismo de propagacao de mudanca que sustenta R4/R8: quando a
  referencia/conteudo muda, o estado derivado da marca e invalidado para a
  proxima regeneracao.
- Nao foi capturado em execucao; a evidencia e estatica.

## Confianca

Media: fluxo de invalidacao identificado; a semantica exata do estado em
`+0x840` nao foi decodificada.
""",
)

# ------------------------------------------------------------ getRefBoxes
add(
    "DocumentMarks__0x180135930.md",
    "DocumentMarks::PDFPlusCutMark::getRefBoxes",
    "0x180135930",
    "alta",
    ["0x180316B78", "0x1803ABF54"],
    [],
    """
# PDFPlusCutMark::getRefBoxes — v24.03.10017

## Identificacao

- Endereco: `0x180135930` (corpo `0x180135930`–`0x1801359A1`, 113 bytes)
- Assinatura: `std::vector<ArtDoc::PageBox> __thiscall getRefBoxes(PDFPlusCutMark *this) const`
- Slot de vtable: `0x180316B78` = `0x180316AB0 + 25*8` -> slot [25].

## O que a funcao faz

- Se o seletor de referencia (`this+0x838`) nao e `0`, devolve vetor vazio.
- Se e `0`, devolve um vetor com **um** elemento: `*(uint32*)(this+0x7C0)`
  (a PageBox de referencia).

## Por que sustenta F-001 (Cut Mark)

- Sustenta o dropdown `Attach to:` de R3: a marca oferece exatamente a caixa
  configurada quando referencia por PageBox; a lista das cinco caixas e
  construida pelos menus/UI, nao por esta funcao.
- Confirma que referencia por objeto nao produz page boxes.

## Confianca

Alta.
""",
)

# ------------------------------------------------------------ postProcessClonedMark
add(
    "DocumentMarks__0x180135CB0.md",
    "DocumentMarks::PDFPlusCutMark::postProcessClonedMark",
    "0x180135CB0",
    "media",
    ["0x180316B30", "0x1803AC15C"],
    ["PDFPlusCutMark_OriginalReferenceName", "PDFPlusCutMark_Offset"],
    """
# PDFPlusCutMark::postProcessClonedMark — v24.03.10017

## Identificacao

- Endereco: `0x180135CB0` (corpo `0x180135CB0`–`0x1801360DF`, 1231 bytes)
- Assinatura: `void __thiscall postProcessClonedMark(PDFPlusCutMark *this, ArtDoc::CloneStrategy *strategy)`
- Slot de vtable: `0x180316B30` = `0x180316AB0 + 16*8` -> slot [16].

## O que a funcao faz

1. Chama `DynamicMark::postProcessClonedMark`.
2. Ajusta referencias do clone: `CloneStrategy::GetOriginalObject`,
   `Content::GetObjectWithID`, `GetProperties`.
3. Referencia as chaves **`PDFPlusCutMark_OriginalReferenceName`**
   (`0x180316A80`) e **`PDFPlusCutMark_Offset`** (`0x180316C68`).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R10 (chaves de persistencia) e R4: ao clonar/duplicar a marca, a
  referencia por objeto e o nome original sao reescritos a partir do original.
- Explica a existencia de `PDFPlusCutMark_OriginalReferenceName` no dicionario.

## Confianca

Media: chaves e operacoes confirmadas; a regra exata de reescrita nao foi
detalhada.
""",
)

# ------------------------------------------------------------ Clone
add(
    "DocumentMarks__0x180134830.md",
    "DocumentMarks::PDFPlusCutMark::Clone",
    "0x180134830",
    "alta",
    ["0x180316AB8", "0x1803AADD0"],
    [],
    """
# PDFPlusCutMark::Clone — v24.03.10017

## Identificacao

- Endereco: `0x180134830` (corpo `0x180134830`–`0x18013487B`, 75 bytes)
- Assinatura: `PDFPlusCutMark * __thiscall Clone(PDFPlusCutMark *this, ArtDoc::CloneStrategy *strategy)`
- Slot de vtable: `0x180316AB8` = `0x180316AB0 + 1*8` -> slot [1].

## O que a funcao faz

1. Aloca `0x850` bytes (`FUN_1802CBE68`).
2. Chama o construtor de copia `PDFPlusCutMark::PDFPlusCutMark(this, other, strategy)`
   (`0x1801343D0`).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R4/R8 no aspecto de duplicacao: a marca clonada preserva o tipo
  `PDFPlusCutMark` e passa pelo pos-processamento (`0x180135CB0`) que reescreve
  referencias.
- E o slot [1] da vtable, usado por copiar/colar e mark sets.

## Confianca

Alta.
""",
)

# ------------------------------------------------------------ GetBoundingBoxForPositioning
add(
    "DocumentMarks__0x18012A130.md",
    "DocumentMarks::GetBoundingBoxForPositioning",
    "0x18012A130",
    "media",
    ["0x18009560F", "0x180052559", "0x180052A55", "0x1803AB17C"],
    ["PDFPlusCutMark_Offset"],
    """
# GetBoundingBoxForPositioning — v24.03.10017

## Identificacao

- Endereco: `0x18012A130` (corpo `0x18012A130`–`0x18012A3C5`, 661 bytes)
- Assinatura: `std::optional<YAGL::RectangleBase<YAGL::MilliPointCoordinateSystem>> __cdecl GetBoundingBoxForPositioning(const ArtDoc::ContentObject &obj)`

## O que a funcao faz

1. Se nao ha `Content`, devolve `optional` vazio.
2. Tenta obter o objeto como `GridInterface` (RTTI); se nao for grid, percorre o
   conteudo/dynamic objects (`isMarkNormalized`, `GetPDFPlusBoundingBox`,
   `GetBoundingBox`).
3. Referencia a chave de propriedade **`PDFPlusCutMark_Offset`**
   (dados em `0x18012A2CF`/`0x18012A2D6`) ao montar a caixa para posicionamento.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R6: e o ponto onde o nome `PDFPlusCutMark_Offset` e lido para o
  posicionamento, usado por `getPositionRefBBox` e pelo regenerador legado.
- Complementa R3/R4 para o caso de referencia por objeto.

## Confianca

Media: chamadas e string confirmadas; a composicao exata da caixa nao foi
traduzida linha a linha.
""",
)

# ------------------------------------------------------------ reader
add(
    "DocumentMarks__0x1801683E0.md",
    "FUN_1801683E0 (leitor de marcas PDF+)",
    "0x1801683E0",
    "media",
    ["0x180488448", "0x18031A098"],
    ["Reference", "ReferenceID", "Position", "RepeatForObjects", "Custom Mark"],
    """
# Leitor de marcas PDF+ (FUN_1801683E0) — v24.03.10017

## Identificacao

- Endereco: `0x1801683E0` (corpo `0x1801683E0`–`0x18016D5BF`, 20888 bytes)
- Nome atual: `FUN_1801683E0` (sem simbolo)
- Referencia de dados `0x180488448` (tabela do modulo) e `0x18031A098`.

## O que a funcao faz (ramo Cut Mark)

1. Le o dicionario da marca e o `ObjectType`.
2. No ramo do Cut Mark (comparacao de 4 bytes em `0x18016A4xx`):
   - `GADict::GetStream("Source")` e materializa o `FormPaint`;
   - aloca `0x850` bytes e chama
     `DocumentMarks::PDFPlusCutMark::PDFPlusCutMark` em `0x18016A40F`;
   - chama o parser de Cut Mark **`FUN_180172100`** em `0x18016A437`;
   - chama `FUN_180171DE0` para o pos-processamento do objeto.
3. Para outros tipos, despacha para parsers especificos
   (`FUN_180174210`, `FUN_1801756A0`, `FUN_1801753D0`, `FUN_180175170`,
   `FUN_180176810`, ...).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R11 na v240 no que diz respeito a construcao do objeto: o leitor PDF+
  instancia `PDFPlusCutMark` e delega a leitura de parametros ao parser
  `FUN_180172100`.
- Mostra que o `FormPaint` (conteudo-simbolo) e lido de `Source` antes do parser,
  coerente com a geometria por copia de conteudo observada em
  `regenerateMarkImp` na v240.
- **Nao** confirma `Orientation`/`Repetition`/`LineTypes`: essas chaves nao
  aparecem neste parser de Cut Mark (ver `DocumentMarks__0x180172100.md`).

## Confianca

Media: o ramo do Cut Mark foi localizado e seguido (construtor + parser +
pos-processamento), mas a funcao tem 20 KB e os demais ramos nao foram
auditados por completo.
""",
)

# ------------------------------------------------------------ drift records (6 spec IDs)
DRIFT = [
    ("18013A8B0", "0x18013A8B0", "0x1801344E0", "DocumentMarks::PDFPlusCutMark::PDFPlusCutMark (construtor)",
     "DocumentMarks__0x1801344E0.md", "R2 (defaults do objeto)"),
    ("18013EE90", "0x18013EE90", "0x180136190", "DocumentMarks::PDFPlusCutMark::regenerateMarkImp",
     "DocumentMarks__0x180136190.md", "R7/R8 (geracao e regeneracao da geometria)"),
    ("18013CB50", "0x18013CB50", "0x180134B00", "DocumentMarks::PDFPlusCutMark::GetReferenceBox",
     "DocumentMarks__0x180134B00.md", "R3/R4/E5/E6/E8 (resolucao da caixa)"),
    ("18017C5D0", "0x18017C5D0", "0x180172100", "FUN_180172100 (parser PDF+ do Cut Mark)",
     "DocumentMarks__0x180172100.md", "R5/R6/R10/R11 (leitura de Position/Reference/Offset)"),
    ("180111410", "0x180111410", "0x18010E0F0", "FUN_18010E0F0 (createDynamicObject legado)",
     "DocumentMarks__0x18010E0F0.md", "R12.1 (dispatch AIDynamicMarks-CutMark)"),
    ("180052CA0", "0x180052CA0", "0x180052950", "DocumentMarks::CutMark::regenerateMarkImp (legado)",
     "DocumentMarks__0x180052950.md", "R12.3 (clonagem/posicionamento do simbolo)"),
    ("18013D160", "0x18013D160", "0x180135160", "DocumentMarks::PDFPlusCutMark::SetOffset",
     "DocumentMarks__0x180135160.md", "R5/R6 (variant quantidade/formula)"),
    ("1800ADB10", "0x1800ADB10", "0x1800AA1B0", "DocumentMarks::SetCutMarkOffset (sobrecarga PDFPlusCutMark&)",
     "DocumentMarks__0x1800AA1B0.md", "R5/R8 (edicao de offset como acao undoable)"),
    ("180172550", "0x180172550", "0x1801683E0", "FUN_1801683E0 (leitor de marcas PDF+)",
     "DocumentMarks__0x1801683E0.md", "R11 (construcao do PDFPlusCutMark e chamada do parser)"),
    ("18024D3E0", "0x18024D3E0", "0x180243EC0", "DocumentMarks::TaskMarkSets::ApplyMarksFromSet",
     "DocumentMarks__0x180243EC0.md", "R13/F-002 (aplicacao por mark set)"),
]

for tag, cited, real, fname, target, rules in DRIFT:
    add(
        "DocumentMarks__%s.md" % cited,
        "ID de %s: endereco da v25.03.116; equivalente v240 = %s" % (cited, real),
        cited,
        "alta",
        [real],
        [],
        """
# Registro de ID — `%s` (citado pela spec F-001)

## Resultado neste binario (v24.03.10017)

- O endereco `%s` **nao e entrada de funcao** em
  `C:\\Esko\\bg_prog_artpro+_v240\\ArtPro+.app\\Contents\\Windows\\DocumentMarks.dll`
  (sha256 `%s`).
- Ele pertence a imagem da **v25.03.116** (`bg_prog_artpro+_v250`), de onde a
  spec F-001 foi originalmente escrita. O proprio frontmatter de F-001 registra
  "evidencia capturada na v25; requer revalidacao contra 24.03.10017".
- A funcao equivalente na v240 e **%s**, em **%s**.
  A analise real da v240 esta em `%s`.

## Por que este arquivo existe

O ID `GHIDRA-DocumentMarks-%s` e citado em `docs/features/F-001.md` (%s).
Este arquivo preserva a rastreabilidade do ID sem inventar uma funcao no
endereco errado: ele e um **registro de deslocamento de endereco entre versoes**,
nao uma analise da v25 como se fosse v24.

## Impacto na spec

- A spec continua apontando para enderecos da v25. O orquestrador/documentacao
  precisa reapontar os IDs de F-001 para os enderecos v240 listados no
  `manifest.json` (`estatico`) antes de considerar a spec revalidada.
- Nenhuma conclusao de comportamento deste arquivo deve ser lida como
  comportamento v240: para isso, use o arquivo `%s`.

## Confianca

Alta para o deslocamento (evidencia direta: os enderecos citados estao no meio de
funcoes diferentes na v240; as funcoes equivalentes foram localizadas por
simbolo e assinatura no programa v240).
""" % (cited, cited, SHA, fname, real, target, cited, rules, target),
    )

# ------------------------------------------------------------ identity / strings / vtables
add(
    "DocumentMarks__identity.md",
    "identidade do binario DocumentMarks.dll v24.03.10017",
    "0x180000000",
    "alta",
    [],
    [],
    """
# Identidade do binario — DocumentMarks.dll v24.03.10017

## Arquivo de referencia

- Caminho:
  `C:\\Esko\\bg_prog_artpro+_v240\\ArtPro+.app\\Contents\\Windows\\DocumentMarks.dll`
- Tamanho: 4.841.904 bytes
- SHA-256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- MD5 (Ghidra): `4d2f2060555b206bd9f374ca69f8a234`
- Imagem: `x86:LE:64:default`, base `0x180000000`, compilador `windows`.
- Funcoes reconhecidas pelo Ghidra 12.2: 12.006.

## Programa Ghidra usado

- Projeto: `DocMarks_v240` (`tools/ghidra_projects/DocMarks_v240`),
  programa `/DocumentMarks.dll`.
- Importado da v240 em 21/11/2026 com analise padrao
  (`analyzeHeadless ... -import ...`), log em
  `tools/ghidra_analysis/f001_docmarks_v240_import.log`.

## Contraste com a v25 (historico)

O projeto `ArtProPlus` contem um programa `DocumentMarks.dll` cujo
`executablePath` e `/C:/Esko/bg_prog_artpro+_v250/...` e cujo SHA-256 e
`FFA8809D294A7AA08BD2794E0B0C1E64608D898B5F7BA698A4E58A8E575BEE10`
(12.192 funcoes). **Nao foi usado como evidencia de F-001**, exceto para
diagnosticar o deslocamento de enderecos; os enderecos da spec pertencem a ele.

## Ausencia de literal `Trim Marks`

A varredura ASCII/UTF-16 do binario v240 nao encontra `Trim Marks`; os literais
de UI/persistencia usam `Cut Mark`/`CutMark`
(`AIDynamicMarks-CutMark` em `0x1802FDC58`,
`DynamicObject_PDFPlusCutMark` em `0x180305DC8`). Isso sustenta a nota de
nomenclatura de F-001 §1.

## Confianca

Alta: identidade lida de `currentProgram` (caminho e hash) e conferida com
`Get-FileHash` sobre o arquivo real.
""",
)

add(
    "DocumentMarks__strings.md",
    "literais de Cut Mark na v24.03.10017",
    "0x1802FDC58",
    "alta",
    [],
    [
        "AIDynamicMarks-CutMark", "DynamicObject_PDFPlusCutMark",
        "PDFPlusCutMark_Offset", "DocumentMarks_CutMark_ReferenceID",
        "PDFPlusCutMark_OriginalReferenceName", "DM-CutMarkParams",
    ],
    """
# Strings de Cut Mark — v24.03.10017

Enderecos lidos da tabela de dados definidos do programa v240
(`Listing.getDefinedData`), nao de offsets de arquivo.

| Endereco | Valor | Papel |
|---|---|---|
| `0x1802FDC58` | `AIDynamicMarks-CutMark` | tipo do mark set legado (R12) |
| `0x1802FDC70` | `CutMark` | identificador curto legado |
| `0x1802FDC78` | ` Cut Mark update at \\n` | log de debug do regenerador legado |
| `0x180305DC8` | `DynamicObject_PDFPlusCutMark` | tipo persistido (R9/R10) |
| `0x180316A80` | `PDFPlusCutMark_OriginalReferenceName` | chave de referencia clonada |
| `0x180316C68` | `PDFPlusCutMark_Offset` | nome do offset (R6/R10) |
| `0x180319368` | `DocumentMarks_CutMark_ReferenceID` | ID da referencia por objeto (R4) |
| `0x18032FDD8` | `DM-CutMarkParams` | dicionario legado (R12.2) |
| `0x1803302A0` | `DM-CutMarkParams-Offset` | offset legado |
| `0x1803302B8` | `DM-CutMarkParams-SymbolDefinition` | simbolo legado (chave existe; uso nao localizado) |
| `0x1803302E0` | `DM-CutMarkParams-Version` | versao legada |
| `0x18031AA50` | `Invalid Repetition Direction value` | mensagem de outra marca/contexto (nao e a de Cut Mark) |

## Literais que NAO existem na v240

Varredura binaria ASCII e UTF-16 (script
`tools/ghidra_analysis/scan_strings_v240.py`) retorna **zero ocorrencias** de:

- `AllStructuralDesignStations`
- `LineTypes`
- `Cut Mark has invalid Orientation value`
- `Cut Mark has invalid Repetition value`

Esses literais existem na v25 e sustentam R11/E1/E2/E3 **apenas na v25**.
Na v240 o parser e outro (`0x180172100`) e nao le essas chaves.

## Confianca

Alta para presenca/endereco dos literais listados; alta para a ausencia dos
literais v25 (duas buscas independentes: tabela do Ghidra e varredura de bytes).
""",
)

add(
    "DocumentMarks__vtables_rtti.md",
    "vtables e slots de PDFPlusCutMark na v24.03.10017",
    "0x180316AB0",
    "alta",
    [],
    ["PDFPlusCutMark"],
    """
# Vtables e slots — DocumentMarks::PDFPlusCutMark (v24.03.10017)

## Vtables instaladas pelo construtor (`0x1801344E0`)

- `this+0x000` -> `0x180316AB0` (`vftable` para
  `ArtDoc::Detail::ListItem<ArtDoc::ContentObject>`)
- `this+0x020` -> `0x180316C30` (`vftable` para `ArtDoc::Visitable`)

## Slots confirmados por xref de dados (vftable `0x180316AB0`)

| Slot | Endereco do slot | Funcao |
|---|---|---|
| [1] | `0x180316AB8` | `PDFPlusCutMark::Clone` (`0x180134830`) |
| [7] | `0x180316AE8` | `PDFPlusCutMark::ContentChangedSelf` (`0x180134880`) |
| [12] | `0x180316B10` | `PDFPlusCutMark::getMarkType` (`0x180135660`) |
| [16] | `0x180316B30` | `PDFPlusCutMark::postProcessClonedMark` (`0x180135CB0`) |
| [25] | `0x180316B78` | `PDFPlusCutMark::getRefBoxes` (`0x180135930`) |
| [29] | `0x180316B98` | `PDFPlusCutMark::regenerateMarkImp` (`0x180136190`) |
| [32] | `0x180316BB0` | `PDFPlusCutMark::getPositionRefBBox` (`0x180135670`) |
| [39] | `0x180316BE8` | `PDFPlusCutMark::RemoveInvalidCustomFormulasImp` (`0x180134F60`) |

A aritmetica `slot = (endereco_do_slot - 0x180316AB0) / 8` confere para todos
os itens acima. Em particular, **`regenerateMarkImp` e o slot [29]**, igual ao
observado na v25.

## RTTI / hierarquia

Os nomes qualificados (vindos do RTTI e dos simbolos) confirmam a cadeia
`ContentObject` -> `Group` -> `DynamicObject` -> `DynamicMark` ->
`PDFPlusCutMark`, com as interfaces `Visitable` e
`ArtDoc::Detail::ListItem<ArtDoc::ContentObject>`. Os type descriptors
`PDFPlusCutMark` aparecem em `0x1803B...` (RTTI), conforme o import log.

## Confianca

Alta: cada slot foi derivado de uma referencia de dados real do binario v240.
""",
)

os.makedirs(OUT, exist_ok=True)
for name, text in FILES:
    p = os.path.join(OUT, name)
    with open(p, "w", encoding="utf-8", newline="\n") as f:
        f.write(text)
    print("wrote", p, len(text.encode("utf-8")), "bytes")

print("total files:", len(FILES))
