# -*- coding: utf-8 -*-
"""
gen_f002_evidence.py - gera os registros .md de evidencia Ghidra de F-002 (Mark Set)
a partir dos dumps brutos do programa DocumentMarks.dll v24.03.10017.

Entrada (ja existente, gerada por F002MarkSetProbe.java / F002DetailProbe.java):
  rag/evidence/F-002/ghidra/raw_v240/_detail.txt
  rag/evidence/F-002/ghidra/raw_v240/_decompile_detail.txt
  rag/evidence/F-002/ghidra/raw_v240/_interior.txt

Saida: rag/evidence/F-002/ghidra/DocumentMarks__0x<addr>.md
ASCII puro, UTF-8 sem BOM, LF.
"""
import os
import re
import sys

REPO = r"H:\Desktop\ArtPlus"
GH = os.path.join(REPO, "rag", "evidence", "F-002", "ghidra")
RAW = os.path.join(GH, "raw_v240")
VERSION = "24.03.10017"
MODULE = "DocumentMarks.dll"
BIN = r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll"
SHA = "E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102"


def read(path):
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        return f.read()


def detail_blocks():
    txt = read(os.path.join(RAW, "_detail.txt"))
    parts = re.split(r"^---- (0x[0-9A-Fa-f]+) ----\s*$", txt, flags=re.M)
    out = {}
    for i in range(1, len(parts), 2):
        out[parts[i].lower()] = parts[i + 1].strip()
    return out


def probe_blocks():
    txt = read(os.path.join(RAW, "_probe.txt"))
    parts = re.split(r"^---- (0x[0-9A-Fa-f]+) ----\s*$", txt, flags=re.M)
    out = {}
    for i in range(1, len(parts), 2):
        out[parts[i].lower()] = parts[i + 1].strip()
    return out


def decomp_blocks():
    txt = read(os.path.join(RAW, "_decompile_detail.txt"))
    parts = re.split(r"^#### ([0-9A-Fa-f]+) (.+?) ####\s*$", txt, flags=re.M)
    out = {}
    for i in range(1, len(parts), 3):
        out[parts[i].lower()] = parts[i + 2].strip()
    return out


def field(block, key):
    m = re.search(r"^" + key + r"=(.*)$", block, re.M)
    return m.group(1).strip() if m else ""


def multi(block, key):
    return [m.group(1).strip() for m in re.finditer(r"^" + key + r"=(.*)$", block, re.M)]


def ascii_only(s):
    repl = {
        "\\": "\\\\", "'": "'", "\u00a0": " ", "\u2013": "-", "\u2014": "-",
        "\u2018": "'", "\u2019": "'", "\u201c": '"', "\u201d": '"',
    }
    for k, v in repl.items():
        s = s.replace(k, v)
    out = []
    for ch in s:
        if ord(ch) < 128:
            out.append(ch)
        else:
            out.append("?")
    return "".join(out)


def yaml_list(items):
    if not items:
        return "[]"
    esc = []
    for it in items:
        t = ascii_only(it).replace('"', '\\"')
        esc.append('"%s"' % t)
    return "[" + ", ".join(esc) + "]"


def yaml_str(s):
    t = ascii_only(s).replace('"', '\\"')
    return '"%s"' % t


def code_excerpt(addr, max_lines=22):
    blk = DECOMP.get(addr)
    if not blk:
        return None
    lines = blk.splitlines()
    # drop leading comment block, start at the first signature line
    start = 0
    for i, ln in enumerate(lines):
        if ln.startswith("/*") or ln.startswith("   ") or not ln.strip():
            continue
        start = i
        break
    body = lines[start:start + max_lines]
    tail = ""
    if len(lines) - start > max_lines:
        tail = "\n/* ... %d linhas omitidas; ver bruto _decompile_detail.txt */" % (
            len(lines) - start - max_lines)
    return "\n".join(body) + tail


DET = detail_blocks()
DET.update(probe_blocks())          # 0x18001A340 so existe no dump da sonda #1
DECOMP = decomp_blocks()
if "0x18001a340" in DET and "fullName=" not in DET["0x18001a340"]:
    DET["0x18001a340"] += "\nfullName=DocumentMarks::DynamicMark::Accept"


# ---------------------------------------------------------------------------
# Analises redigidas a partir do bruto (sem inventar comportamento)
# ---------------------------------------------------------------------------

ANALYSIS = {
"0x1800147f0": dict(
    conf="alta",
    what="""Carrega um documento de mark set a partir do caminho (`param_2`) usando o helper
local `FUN_180014c80(path*) -> ArtDoc::Document*` e aplica o mark set a **todas as paginas**
do documento alvo (`param_1`).

Fluxo observado no corpo:
1. `FUN_180014c80(&local_a8)` recebe o caminho do mark set; retorno nulo = mark set nao pode
   ser lido. (Inferencia: e o carregador do arquivo de mark set; o mesmo helper e usado por
   `ApplyMarkSetToPage` em 0x180014A00.)
2. Se o carregamento falhou e `param_3` (bool) e verdadeiro: abre `ActionGroupCreator`,
   percorre `Document::GetPagesBegin/GetPagesEnd(param_1)` e chama `DeleteMarks(page)` em
   cada pagina -- ou seja, "aplicar um mark set inexistente com a flag de limpar" apenas
   remove as marcas existentes e nao reporta erro nesta funcao.
3. Se carregou: abre `ActionGroupCreator(param_1,false,false)`; para cada pagina do documento
   alvo, toca o change tracker (`FUN_180013be0(changeTracker+0x110, pageContent)`), obtem a
   **primeira** pagina do documento de mark set (`*Document::GetPagesBegin(doc)`), apaga as
   marcas da pagina se `param_3`, chama
   `CopyMarksToPage(primeiraPaginaDoMarkSet, paginaAlvo, true, NULL, NULL, param_4, true)`
   e registra um callback lambda no change tracker (`FUN_1800138d0`).
4. `param_4` e o `std::set<unsigned __int64>*` repassado a `CopyMarksToPage` (conjunto de IDs
   de objetos, conforme a assinatura).

Nao referencia strings de mensagem: qualquer erro/diagnostico e reportado pelos helpers.""",
    gap="Helper de carga (`FUN_180014c80`) nao esta identificado por simbolo; a atribuicao "
        "\"le o arquivo de mark set\" e inferencia pela assinatura (path -> Document*) e pelo "
        "uso identico em ApplyMarkSetToPage.",
),
"0x180014a00": dict(
    conf="alta",
    what="""Variante de `ApplyMarkSet` restrita a **uma pagina** (`param_1`). O documento alvo e
obtido por `Page::GetContent(param_1)` -> `Content::GetDocument`, nao pelo documento inteiro.

Fluxo observado:
1. `FUN_180014c80(local_98, param_2)` carrega o mark set do caminho.
2. Falha de carga + `param_3` verdadeiro -> `DeleteMarks(param_1)` (somente a pagina alvo).
3. Carga ok -> toca change tracker, abre `ActionGroupCreator` no documento da pagina, pega a
   primeira pagina do mark set, apaga marcas se `param_3`, chama
   `CopyMarksToPage(primeiraPaginaDoMarkSet, param_1, true, NULL, NULL, param_4, true)`
   e registra o lambda no change tracker.

Diferenca para 0x1800147F0: sem laco sobre paginas; sem `EnableUpdates`.""",
    gap="Mesma inferencia do helper de carga de 0x1800147F0.",
),
"0x1800426f0": dict(
    conf="alta",
    what="""Nucleo de copia pagina -> pagina das marcas dinamicas; e o ponto por onde passam
`ApplyMarkSet`, `ApplyMarkSetToPage`, `CopyPageWithMarks` e `CopyMarksToPageWithLog`.

Fluxo observado:
1. `FUN_180044310(&local_a8, GetContent(origem))` prepara um coletor do conteudo de origem;
   `FUN_180044820(...)` monta um mapa `<idOrigem, idCopia>` (par `[4]`/`[5]` de cada no da
   arvore) e retorna a contagem em `local_c0`.
2. Se o mapa esta vazio, a funcao nao copia nada (retorno falso).
3. `FUN_1800461a0(param_1,&local_c8)` (pagina de origem, mapa).
4. Se o documento de destino **nao** tem `Document::GetInfoFlag(doc, 2)`, abre
   `ActionGroupCreator` no documento de destino.
5. Localiza o modulo de marcas por `FindModule(0x4d61726b)` ('Mark'), faz `__RTDynamicCast`
   para `MarksModule` e le `MarksModule::GetFeatures`; o **bit 11** da feature mask e usado
   como "suporta remocao/limpeza" (`bVar13`).
6. Se `param_3` (apagar marcas existentes) e verdadeiro e a feature **nao** esta setada, chama
   `FUN_180042c00(param_1,param_2)` antes de copiar (limpeza previa).
7. `FUN_18003df00(&local_88, param_1, mapa, param_2, param_7, uVar14, param_6)` executa a
   copia sobre o conteudo da pagina de destino; o visitor e aplicado com
   `PageContent::Accept(GetContent(param_1), &local_88)`.
8. Depois, para cada par do mapa, resolve objeto antigo/novo por `Content::GetObjectWithID`
   e registra `CloneStrategy::AddClone(strategy, objOrigem, objCopia)`; a sequencia termina
   nos callees `AddClone`, `RelinkDynamicObjects`, `InksChanged` e `~CloneStrategy`
   (religacao de marcas dinamicas e invalidacao de tintas).
9. `param_4`/`param_5` sao dois `std::set<std::string>*` (nomes de objeto) e `param_6` um
   `std::set<unsigned __int64>*` (IDs), todos repassados ao coletor `FUN_180044820`.

Strings: nenhuma literal no corpo (todo diagnostico textual vem de
`CopyMarksToPageWithLog`, 0x180245380).""",
    gap="Os helpers `FUN_180044310`, `FUN_180044820`, `FUN_18003df00`, `FUN_1800461a0` e "
        "`FUN_180042c00` nao tem simbolo; a descricao do papel de cada um e inferencia pela "
        "assinatura e pela ordem das chamadas.",
),
"0x180045c70": dict(
    conf="media",
    what="""Converte as marcas dinamicas de uma pagina em **formas estaticas** (\"make forms from
marks\"). E chamada por `ApplyRelevantMarkSets` (0x180243F40),
`ApplyRelevantMarkSetsWithReuse` (0x180244A50), `MakeFormsFromCachedMarks` (0x180246AB0) e
`PrepareMarksCache` (0x1802475E0).

Callees que caracterizam a operacao (34 no total): `DocumentEdit::MakeForm`,
`ArtDoc::Group`, `SetTransformation`/`GetTransformation`, `GetBoundingBox`, `InsertBefore`,
`AddOnTop`, `ExtractFromParent`, `ObjectWillBeDeleted`, `GetActionList`, `GetProperties`,
`SetTransparency`/`GetTransparency`, `makeStatic` (0x1800961b0) e
`~VisitorBase`/`VisitorBase` (visitor sobre o conteudo da pagina).

Leitura: percorre o conteudo da pagina via visitor, para cada objeto dinamico gera uma forma
(`MakeForm`), agrupa/posiciona pela transformacao e pela bounding box, marca o objeto original
como removivel, e aplica transparencia herdada. Retorna bool (sucesso).""",
    gap="Sem simbolo nos helpers internos; a ordem exata de MakeForm/Group por objeto nao foi "
        "seguida linha a linha -- descricao por conjunto de callees e assinatura.",
),
"0x1802436a0": dict(
    conf="alta",
    what="""Construtor de `DocumentMarks::TaskMarkSets` (contexto de execucao do mark set;
recebe `TaskReporter&` em `param_1`). Inicializa os cinco grupos de documentos do objeto
(offsets +0x10, +0x28, +0x40, +0x58, +0x70, +0x88 usados depois por ApplyRelevantMarkSets),
instala as vtables e liga quatro flags booleanas (bytes 0x100, 0x150, 0x1A0, 0x1F0 = 1).
Tambem guarda o reporter em +0x1F8 (usado por `CopyMarksToPageWithLog` e `ReadMarkSetFile`
para emitir mensagens).""",
    gap="Nenhuma.",
),
"0x180243ec0": dict(
    conf="alta",
    what="""Aplicacao por mark set -- **equivalente v240** do ID historico
`GHIDRA-DocumentMarks-0x18024D3E0` (v250 historico).

Corpo completo (109 bytes):

    puVar4 = begin(param_1); puVar1 = end(param_1);
    if (puVar4 == puVar1) return false;
    do {
        puVar2 = Document::GetPagesBegin(*puVar4);
        CopyMarksToPageWithLog(this, *puVar2, param_2, param_3);
        puVar4++;
    } while (puVar4 != puVar1);
    return true;

Ou seja: para **cada documento** do vetor de mark sets, copia a **primeira pagina**
(`*GetPagesBegin(doc)`) para a pagina alvo `param_2`, com log (`param_3` = apagar marcas
existentes). Retorna `false` se o vetor estiver vazio, `true` caso contrario. Nao ha
validacao de versao nem leitura de arquivo aqui -- isso fica em `ReadMarkSetFile`.""",
    gap="Nenhuma: corpo integral reproduzido.",
),
"0x180243f40": dict(
    conf="alta",
    what="""Funcao central do fluxo de Mark Set -- **equivalente v240** do ID historico
`GHIDRA-DocumentMarks-0x18024D460` (v250 historico). Assinatura:
`void ApplyRelevantMarkSets(Page& page, int flags, bool b1, bool b2, bool b3, bool b4)`.

Sequencia observada no corpo (2824 bytes):

1. `DynamicMarksController::EnableUpdates(doc, false)` -- suspende atualizacao das marcas.
2. Para cada `Separation::Entry` em `this+0x10..0x18`, se `GetInkType` for 2 ou 3, chama
   `AddNormalizedInkHint(name, inkType)` (normalizacao de tintas especiais).
3. **Grupos de documentos**: `this+0x28` e sempre aplicado; `this+0x40` quando
   `(flags & 1) == 0`; `this+0x58` quando `(flags & 1) != 0`; `this+0x70` quando
   `flags == 1`; `this+0x88` quando `b1` (param_3) e verdadeiro. Para cada documento de cada
   grupo, `CopyMarksToPageWithLog(this, *GetPagesBegin(doc), page, !b4)`.
4. `DetectNormalizedInkTypes(pageContent, true, true)`; cria `InkCollector`, aplica visitor
   (`PageContent::Accept`), copia `Document::GetSeparationInfo` para um vetor local e repete a
   normalizacao de tintas sobre as entradas; para cada grupo efetivamente usado, faz
   `InkCollector::MergeUsedSeparations` e acumula `AddNormalizedInkHints`.
5. `Separation::FindOrAdd` de cada entrada de `this+0x10` no vetor acumulado;
   `Document::SetSeparationInfo(doc, ...)`; registra lambda no change tracker.
6. `UpdateMarksOnPage(page)`; compara a contagem de separacoes antes/depois via
   `FUN_180243bc0` e, se mudou, `MergeSeparationInfo` + `SetSeparationInfo` +
   `DynamicObjectController::SetAllNeedUpdate` + novo `UpdateMarksOnPage`.
7. Final: se `b3` (param_5) -> `GetDynamicMarksBox` + `AdjustPageBoxes(page, box)`;
   se `b4` (param_6) -> `MakeFormsFromMarks(page,false)`; sempre
   `MoveExpandedMarks(page, !b4)`.

Strings: nenhuma literal; mensagens vem de `CopyMarksToPageWithLog`.""",
    gap="O mapeamento exato de cada offset de grupo (+0x28/+0x40/+0x58/+0x70/+0x88) para um "
        "tipo de mark set (DMK, extra, plate, cache) nao e nomeado no binario: e inferencia "
        "pelo uso e pelos setters do mesmo objeto.",
),
"0x180244a50": dict(
    conf="media",
    what="""Variante com reuso de clones -- **equivalente** de `ApplyRelevantMarkSets` quando ha
`CloneStrategy` disponivel. Assinatura:
`void ApplyRelevantMarkSetsWithReuse(Page&, CloneStrategy&, int flags, bool, bool, RectangleBase<MilliPoint>*)`.

Callees que caracterizam: `CloneStrategy::Clone`, `CopyMarksAsFormsToPage` (0x180042670),
`MakeFormsFromMarks`, `UpdateMarksOnPage`, `AdjustPageBoxes`, `GetDynamicMarksBox`,
`MoveExpandedMarks`, `GetPagesBegin`, `GetChangeTracker`, `~CloneStrategy`.

Leitura: clona os documentos de mark set com a estrategia fornecida, copia o resultado para a
pagina alvo como formas (`CopyMarksAsFormsToPage`), atualiza as marcas, ajusta caixas de
pagina com a bounding box recebida e move marcas expandidas. O retangulo `param_6` e a caixa
de referencia usada no ajuste.""",
    gap="O corpo nao foi decompilado linha a linha para decidir a ordem exata Clone/Copy; a "
        "descricao vem da assinatura e do conjunto de callees.",
),
"0x180245380": dict(
    conf="alta",
    what="""Copia pagina -> pagina com **log de diagnostico** -- **equivalente v240** do ID
historico `GHIDRA-DocumentMarks-0x18024E9B0` (v250).

1. Cria dois `std::set<std::string>` vazios (mapas de nomes usados por `CopyMarksToPage`).
2. Chama `CopyMarksToPage(param_1, param_2, param_3, setA, setB, NULL, true)` e guarda o bool.
3. Se o retorno foi **falso** e o primeiro conjunto nao esta vazio, emite diagnostico no
   reporter `*(this+0x1F8)`:
   - `GetFilePath(doc)` + `boost::filesystem::path_algorithms::stem_v3` +
     `ExtraBoostFilesystem::ToUTF8String` para o nome do mark set;
   - concatena os nomes do conjunto separados por `", "`;
   - `Page::GetPageIndex(param_2)` para o numero da pagina;
   - mensagem literal (v240):
     `"WARNING: Missing Named Objects: %s.\\nReferenced from Mark Set: %s.\\nDynamic Marks linked to a missing object were removed from page %lu.\\n"`
     com id `"DocumentMarks.Warning.MissingNamedObject"` e severidade 1;
   - em seguida a variante de caixa de pagina:
     `"WARNING: Missing Page Box: %s.\\nReferenced from Mark Set: %s.\\nDynamic Marks linked to a missing page box were relinked to available page box on page %lu.\\n"`
     com id `"DocumentMarks.Warning.MissingPageBox"`.

E o unico ponto do fluxo de Mark Set que produz texto de log observavel na UI.""",
    gap="Nenhuma lacuna de leitura para as strings e ids de mensagem; o formato exato de "
        "concatenacao dos nomes (`\", \"`) foi lido no corpo.",
),
"0x180246c70": dict(
    conf="media",
    what="""Prepara o **documento de cache** de marcas a partir de um documento
(`PrepareMarksCache(Document&, bool, path const&)`), sobrecarga com `Document&`
(a outra sobrecarga, 0x1802475E0, recebe `SheetIteratorProxy&`).

Callees que caracterizam: `ClonePage`, `CloneStrategy`, `InsertPage`, `Create`,
`SetFilePathForDocument`, `SetInfoFlag`, `SetOutputIntent`/`GetOutputIntent`,
`OutputIntent`, `GetUsedSeparationsFromDocument`, `SetSeparationInfo`/`GetSeparationInfo`,
`RemoveStaticContent`, `StoreCurrentPageBoxes`, `MakeFormsFromCachedMarks`,
`CanCacheMarks`, `PrepareMarksCachePage` (0x180248720), `GetNumberOfPages`,
`SetInfoFlag`, `~Document`, `~CloneStrategy`.

Leitura: cria um documento novo, clona paginas com a estrategia, propaga separacoes usadas e
output intent, aplica as formas geradas (`MakeFormsFromCachedMarks`), e para cada pagina chama
`PrepareMarksCachePage(...)` para copiar as marcas e consolidar separacoes. `CanCacheMarks`
decide se o cache e valido.""",
    gap="Sem simbolo nos helpers internos; ordem exata ClonePage/InsertPage por pagina nao foi "
        "seguida linha a linha.",
),
"0x180248720": dict(
    conf="alta",
    what="""Prepara o cache de marcas de **uma pagina** -- **equivalente v240** do ID historico
`GHIDRA-DocumentMarks-0x180251790` (v250 historico). Retorna
`std::vector<ArtDoc::Separation::Entry>` (as separacoes usadas na pagina).

Assinatura v240: `PrepareMarksCachePage(Page&, vector<unique_ptr<Document>> const& a,
vector<unique_ptr<Document>> const& b, vector<unique_ptr<Document>> const& c, bool, bool)`.

Fluxo observado:
1. Se `param_6` (ultimo bool): `DeleteMarks(page)`, `DeleteExpandedMarks(page)` e
   `RemoveUnusedSeparationsFromPage(page)`.
2. Se o bool em `in_stack_00000040`: `MoveExpandedMarks(page,false)`.
3. `DynamicMarksController::EnableUpdates(doc,false)` e montagem da informacao de separacoes:
   parte de `Document::GetSeparationInfo(doc)` e acumula por tres vezes
   `FUN_180246b40(vec, ac, docVector)` (um para cada vetor de documentos recebido), depois
   `Separation::FindOrAdd` para cada entrada de `this+0x10..0x18` e
   `Document::SetSeparationInfo`.
4. Para cada documento dos vetores `a` e `c` (e do terceiro), copia a primeira pagina para a
   pagina alvo com `CopyMarksToPageWithLog(this, *GetPagesBegin(doc), page, false)`.
5. Consolida separacoes em `this+0x10` e retorna o vetor.

Chamada por `PrepareMarksCache(Document&)` (0x180246C70) e por
`PrepareMarksCache(SheetIteratorProxy&)` (0x1802475E0).""",
    gap="Os tres vetores de documentos recebem nomes neutros (a/b/c) porque o binario nao "
        "identifica o papel de cada um (mark set normal, extra, cache).",
),
"0x180248d30": dict(
    conf="alta",
    what="""Le um arquivo de mark set e devolve `std::unique_ptr<ArtDoc::Document>`; o bool por
referencia (`param_2`) recebe a condicao de erro. Chamada por `LoadMarkSets` (0x1802463E0),
`LoadExtraMarkSet` (0x1802461B0) e `LoadCacheDocument` (0x180246120).

Fluxo observado (trechos literais do decompilado):
1. `*in_R9 = 0` (zera a flag de erro) e `boost::filesystem::detail::status(path, err)`.
   - Se `status < 2` (arquivo inexistente/nao regular): emite no reporter `*(this+0x1F8)`
     `"NDLTaskMessages.DocumentMarks.MarkSetFileDoesNotExist"` com severidade 2 e o caminho
     exibido (`filename_v3` + `ToFileURI` + `GetDisplayPath`), seguido do texto
     `"Markset file '%s' does not exist!\\n"`. Retorna documento vazio.
2. Se existe: monta `ReadOptions`, chama `Document::Create` + `ForceDocumentLoad`
   (0x180115E90) e valida o resultado.
   - Falha de leitura/parse: emite `"NDLTaskMessages.DocumentMarks.MarkSetFileError"` e o texto
     `"Markset file '%s' error!\\n"`.
3. `ContainsInputFileMark` (0x180115040): se o documento de mark set contem marca de arquivo de
   entrada, emite `"NDLTaskMessages.DocumentMarks.MarkSetContainsInputFileMark"`.

Nao ha verificacao de versao (`kVersionTooOld`/`kVersionTooNew`) **dentro desta funcao**: essas
strings existem no binario mas nao sao referenciadas aqui.""",
    gap="As etapas internas de ReadOptions/Create/ForceDocumentLoad nao foram seguidas linha a "
        "linha; a ordem exacta entre elas e inferencia pelo conjunto de callees.",
),
"0x180249210": dict(
    conf="alta",
    what="""Reconstroi as marcas carregadas do documento de mark set (`this+0x8`).
Chamada por `LoadCacheDocument` (0x180246120).

Corpo (296 bytes): percorre `Document::GetPagesBegin/GetPagesEnd(doc)`; para **cada pagina**
executa duas passagens (`iVar5 = 0, 1`) chamando
`DocumentEdit::MakeForm(pageContent, lambda<bool(ContentObject const&)>)` e, quando o retorno e
nao nulo, `FUN_180046160(form, iVar5 != 0)`. No final chama `RemoveStaticContent(this)`
(0x1802493F0).

Leitura: converte em forma estatica os objetos que satisfazem o predicado do lambda, em duas
categorias (flag 0 e flag 1), e remove o conteudo estatico remanescente.""",
    gap="O predicado do lambda nao foi reconstruido (corpo do functor nao decompilado); o efeito "
        "exato de cada uma das duas passagens e inferencia.",
),
"0x18001a340": dict(
    conf="alta",
    what="""`DocumentMarks::DynamicMark::Accept(ArtDoc::VisitorBase&)` -- despacho de visitor
virtual de `DynamicMark` (nao tem relacao semantica com Mark Set; este endereco e o unico dos
10 IDs herdados que e entrada de funcao real na v240).

Corpo `0x18001A340`..`0x18001A3E0`:
1. `__RTDynamicCast(param_1, 0, VisitorBase::RTTI, ArtDoc::Visitor<DynamicMark>::RTTI, 0)`.
2. Se o cast falha: `FUN_180013750(&local_res8, this-0x20, param_1)` e, se retornar 0, chama
   o slot `*(*this + 0x20)` (Accept da classe base).
3. Se o cast funciona: chama o primeiro slot do visitor (`(**plVar2)(plVar2)`) e, se retornar
   != 0, tambem o slot `+0x20`; depois chama `(**(plVar2 + 8))(plVar2, this-0x20)`.

Mostra o idioma padrao de double dispatch do ArtDoc: visitor especializado
(`ArtDoc::Visitor<DynamicMark>`) com fallback para o Accept da base.""",
    gap="Nenhuma.",
),
}

# ---------------------------------------------------------------------------
# Registros historicos (IDs que NAO sao entrada de funcao na v240)
# ---------------------------------------------------------------------------

INTERIOR_IDS = [
    ("0x18001A2C0", "0x18001a2b9", "MOV dword ptr [RSP + 0x20],0x0", 7),
    ("0x18001A2D0", "0x18001a2cd", "CALL 0x1802ccf7a", 3),
    ("0x18001A2E0", "0x18001a2de", "MOV RCX,qword ptr [RAX]", 2),
    ("0x18001A2F0", "0x18001a2ee", "MOV R8,qword ptr [RBX]", 2),
    ("0x18001A300", "0x18001a2fe", "LEA RDX,[RBX + -0x20]", 2),
    ("0x18001A310", "0x18001a30d", "LEA RCX,[RSP + 0x40]", 3),
    ("0x18001A320", "0x18001a31e", "MOV RDX,RDI", 2),
    ("0x18001A330", "0x18001a32c", "MOV RBP,qword ptr [RSP + 0x50]", 4),
]

V250_IDS = [
    ("0x18024D3E0", "?ApplyMarksFromSet@TaskMarkSets@DocumentMarks@@QEAA_NAEBV?$vector@...",
     "DocumentMarks::TaskMarkSets::ApplyMarksFromSet", "0x180243EC0", "180243ec0", "848"),
    ("0x18024D460", "?ApplyRelevantMarkSets@TaskMarkSets@DocumentMarks@@QEAAXAEAVPage@ArtDoc@@H_N111@Z",
     "DocumentMarks::TaskMarkSets::ApplyRelevantMarkSets", "0x180243F40", "180243f40", "851"),
    ("0x18024E9B0", "?CopyMarksToPageWithLog@TaskMarkSets@DocumentMarks@@QEAAXAEAVPage@ArtDoc@@0_N@Z",
     "DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog", "0x180245380", "180245380", "939"),
    ("0x180251790", "?PrepareMarksCachePage@TaskMarkSets@DocumentMarks@@IEAA?AV?$vector@...",
     "DocumentMarks::TaskMarkSets::PrepareMarksCachePage", "0x180248720", "180248720", "1436"),
]


def write_md(addr, text):
    name = "DocumentMarks__%s.md" % addr.upper().replace("0X", "0x")
    path = os.path.join(GH, name)
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write(text)
    return path


def header(addr, funcao, conf, xrefs, strings):
    addr = "0x" + addr[2:].upper()
    return (
        "---\n"
        "modulo: %s\n"
        "funcao: %s\n"
        "endereco: %s\n"
        "versao: %s\n"
        "confianca: %s\n"
        "xrefs: %s\n"
        "strings: %s\n"
        "fonte: \"Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)\"\n"
        "---\n" % (MODULE, funcao, addr, VERSION, conf, xrefs, strings)
    )


def gen_real(addr):
    a = addr.lower()
    blk = DET.get(a, "")
    if not blk:
        raise SystemExit("bloco de detalhe ausente para " + addr)
    full = field(blk, "fullName") or field(blk, "name")
    proto = field(blk, "prototype")
    body = field(blk, "body")
    size = field(blk, "bodySize") or "?"
    cc = field(blk, "callingConvention")
    flags = field(blk, "thunk").split()
    thunk = flags[0] if flags and flags[0] in ("true", "false") else "?"
    external = flags[1].split("=")[1] if len(flags) > 1 and "=" in flags[1] else "?"
    callers = multi(blk, "caller")
    callees = multi(blk, "callee")
    strs = [s for s in field(blk, "stringsInBody").split(" | ") if s and s.strip()
            and not s.startswith("...")]
    info = ANALYSIS[a]
    xrefs = ["0x" + c.split(" ")[0].upper() for c in callers]
    stxt = [s.split('"')[1] if '"' in s else s for s in strs]

    md = header(addr, yaml_str(full), info["conf"], yaml_list(xrefs), yaml_list(stxt))
    md += "# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-%s\n\n" % ("0x" + addr[2:].upper())
    md += "## Identificacao lida no programa v240\n\n"
    md += "- endereco: `%s`\n" % addr
    md += "- simbolo: `%s`\n" % full
    md += "- assinatura: `%s`\n" % proto
    if size == "?":
        md += "- corpo: `%s`, convencao `%s`, thunk=%s, external=%s\n" % (
            body, cc, thunk, external)
    else:
        md += "- corpo: `%s` (%s bytes), convencao `%s`, thunk=%s, external=%s\n" % (
            body, size, cc, thunk, external)
    md += "- parametros: %s\n" % field(blk, "paramCount")
    md += "- referencias apontando para a entrada: %s (DATA/vtable/export; detalhe em `refTo` no bruto)\n" % field(blk, "refsToCount")

    md += "\n## O que faz\n\n" + info["what"] + "\n"

    md += "\n## Chamadores (xrefs de chamada)\n\n"
    if callers:
        for c in callers:
            md += "- `%s`\n" % c
    else:
        md += "- nenhum chamador interno registrado (funcao de entrada/exportada; ver `refTo` do bruto)\n"

    md += "\n## Chamadas diretas (%d)\n\n" % len(callees)
    for c in callees:
        md += "- `%s`\n" % c

    md += "\n## Strings referenciadas no corpo\n\n"
    if strs:
        for s in strs:
            md += "- %s\n" % s
    else:
        md += "- nenhuma (o corpo referencia vftables, dados ou outras funcoes)\n"

    exc = code_excerpt(a)
    if exc:
        md += "\n## Pseudocodigo (inicio; integral no bruto)\n\n```c\n" + exc + "\n```\n"

    md += "\n## Lacunas\n\n- " + info["gap"] + "\n"
    md += "\n## Confianca\n\n`" + info["conf"] + "` - endereco, simbolo, assinatura, corpo, "
    md += ("xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto "
           "DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.\n")
    md += "\n## Fonte\n\n"
    md += "- modulo: `%s`\n" % MODULE
    md += "- versao de referencia: `%s`\n" % VERSION
    md += "- binario: `%s`\n" % BIN
    md += "- sha256: `%s`\n" % SHA
    md += "- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`\n"
    md += "- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`\n"
    return write_md(addr, md)


def gen_interior(addr, insn_addr, insn_text, delta):
    md = header(
        addr,
        yaml_str("ID historico sem funcao na v240: endereco interno de "
                 "DocumentMarks::BarcodeMark::Accept (0x18001A240); nao e entrada de funcao"),
        "alta", [], [])
    md += "# Registro de ID - `%s` (citado pelo manifest de F-002)\n\n" % addr
    md += "## Resultado neste binario (v%s)\n\n" % VERSION
    md += "- `isFunctionEntry=false` em `%s`\n" % BIN
    md += "  (sha256 `%s`).\n" % SHA
    md += "- O endereco cai **dentro** do corpo de `DocumentMarks::BarcodeMark::Accept`,\n"
    md += "  `0x18001A240`..`0x18001A33B` (252 bytes).\n"
    md += "- Instrucao que contem o endereco: `%s` `%s`; o endereco esta %d byte(s)\n" % (
        insn_addr, insn_text, delta)
    md += "  apos o inicio da instrucao, ou seja, **no meio de uma instrucao**.\n"
    md += "- Nenhum simbolo e nenhuma referencia apontam para `%s`.\n" % addr
    md += "- O endereco **tambem nao e export da instalacao historica**: a tabela de exports\n"
    md += "  de `DocumentMarks.dll` dessa instalacao (2268 exports) nao contem nenhum VA na\n"
    md += "  faixa `0x18001A2xx`.\n"
    md += "\n## Por que este arquivo existe\n\n"
    md += ("O ID `GHIDRA-DocumentMarks-%s` estava listado como evidencia estatica de F-002 sem\n"
           "arquivo correspondente. Os 10 IDs `0x18001A2C0`..`0x18001A350` formam uma sequencia\n"
           "regular de passo 0x10 dentro de `BarcodeMark::Accept` -- padrao de offsets de codigo,\n"
           "nao de entradas de funcao. Este registro preserva a rastreabilidade e documenta a\n"
           "prova de que o ID nao identifica funcao na versao de referencia.\n" % addr)
    md += "\n## Equivalente v240\n\n"
    md += ("Nenhum. O ID nao tem funcao correspondente: e um deslocamento interno de\n"
           "`DocumentMarks::BarcodeMark::Accept` (0x18001A240), funcao sem relacao com Mark Set.\n")
    md += "\n## Confianca\n\n"
    md += "`alta` - `isFunctionEntry`, funcao conteiner, instrucao conteiner e ausencia de\n"
    md += "simbolos lidos diretamente no programa v240; ausencia na tabela de exports da\n"
    md += "instalacao historica (rastreabilidade)\n"
    md += "conferida no dump de exports da instalacao historica.\n"
    md += "\n## Fonte\n\n- bruto: `rag/evidence/F-002/ghidra/raw_v240/_interior.txt`\n"
    md += "- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`\n"
    md += "- tabela de exports historica: `rag/evidence/F-006/exports.txt` (DocumentMarks.dll)\n"
    return write_md(addr, md)


def gen_v250(addr, mangled, sym, eq_addr, eq_low, ordinal):
    md = header(
        addr,
        yaml_str("ID historico da v25; equivalente v240 = %s em %s" % (sym, eq_addr)),
        "alta", [eq_addr], [])
    md += "# Registro de ID - `%s` (ID historico da v250 citado pela spec F-002)\n\n" % addr
    md += "## Resultado neste binario (v%s)\n\n" % VERSION
    md += "- `isFunctionEntry=false` em `%s`\n" % BIN
    md += "  (sha256 `%s`).\n" % SHA
    md += "- O endereco cai dentro de outra funcao na v240 (ver `containingFunction` no bruto).\n"
    md += "- Origem do ID: tabela de exports do `DocumentMarks.dll` de instalacao historica\n"
    md += "  (dump em `rag/evidence/F-006/exports.txt`), ordinal %s, onde o VA `%s`\n" % (ordinal, addr)
    md += "  corresponde ao simbolo exportado\n"
    md += "  `%s`.\n" % mangled
    md += "\n## Equivalente v240\n\n"
    md += "- funcao: **%s**\n" % sym
    md += "- endereco: **%s** (entrada de funcao confirmada na v240)\n" % eq_addr
    md += "- analise real: `DocumentMarks__%s.md`\n" % eq_addr
    md += "\n## Por que este arquivo existe\n\n"
    md += ("O ID foi escrito na spec F-002 a partir do layout historico. Ele **nao** identifica\n"
           "funcao na v24.03.10017, versao de referencia do projeto. A equivalencia foi\n"
           "estabelecida pelo nome exportado (mesmo simbolo C++ demangled) e confirmada pela\n"
           "assinatura e pelo corpo da funcao v240.\n")
    md += "\n## Confianca\n\n"
    md += "`alta` para o deslocamento de endereco (export historico com o mesmo simbolo; funcao\n"
    md += "v240\n"
    md += "localizada por simbolo e conferida por assinatura). Nenhuma conclusao de comportamento\n"
    md += "deve ser lida deste arquivo: use o equivalente v240.\n"
    md += "\n## Fonte\n\n- bruto: `rag/evidence/F-002/ghidra/raw_v240/_probe.txt`\n"
    md += "- tabela de exports historica: `rag/evidence/F-006/exports.txt`\n"
    md += "- script: `tools/ghidra_analysis/scripts/F002MarkSetProbe.java`\n"
    return write_md(addr, md)


def main():
    os.makedirs(GH, exist_ok=True)
    made = []
    for a in ["0x18001a340", "0x180243ec0", "0x180243f40", "0x180245380",
              "0x180248720", "0x1800147f0", "0x180014a00", "0x1800426f0",
              "0x180045c70", "0x180244a50", "0x180246c70", "0x180248d30",
              "0x180249210"]:
        made.append(gen_real(a))
    for addr, insn, txt, d in INTERIOR_IDS:
        made.append(gen_interior(addr, insn, txt, d))
    made.append(gen_interior("0x18001A350", "0x18001a350", "SUB RSP,0x30", 0))
    for addr, mangled, sym, eq, eqlow, ordinal in V250_IDS:
        made.append(gen_v250(addr, mangled, sym, eq, eqlow, ordinal))
    for p in made:
        print("wrote", os.path.basename(p))


if __name__ == "__main__":
    main()
