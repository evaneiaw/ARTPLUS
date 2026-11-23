#!/usr/bin/env python3
# Gera rag/evidence/F-004/ghidra/PDFObjectActions__0x<addr>.md a partir de _raw/*.txt
# Entrada: _raw/index.tsv + _raw/PDFObjectActions__0x<addr>.txt
# Saida: .md com cabecalho YAML e corpo ASCII (acentos transliterados).
import os
import re
import glob
import unicodedata

BASE = r"H:\Desktop\ArtPlus\rag\evidence\F-004\ghidra"
RAW = os.path.join(BASE, "_raw")

# confianca por endereco (definida apos revisao manual do pseudocodigo)
CONF = {
    "180276230": "alta",
    "1802770d0": "alta",
    "180277140": "alta",
    "18028c310": "alta",
    "18028c410": "alta",
    "18028df80": "alta",
    "18028d3b0": "media",
    "180133230": "alta",
    "1801303e0": "alta",
    "1800940d0": "alta",
    "18022c220": "media",
    "18030b240": "alta",
    "180341480": "media",
}

NOTES = {
"180276230": [
"Fato (Ghidra): metodo virtual `bool GOVSelectHitElement::Select(GOElement&)`,",
"2441 bytes, vtable em `.rdata:1804e7590`. Chama `GRectBase<double>::Contains`,",
"`GRectBase<double>::Intersects`, `GRectBase<double>::IsInfinite`,",
"`GOLocation::IsInPropertyContent`, `GOVComparator::RoundValue` e tres rotinas",
"internas (180275430, 180275850, 180277200).",
"",
"Fato: os 5 chamadores diretos sao `GOVSelectCloseToPageEdge::DetectCloseToBottomEdge`,",
"`DetectCloseToTopEdge`, `DetectCloseToLeftEdge`, `DetectCloseToRightEdge` e",
"`ElementVisibleOnRect` - ou seja, o teste geometrico e reutilizado como",
"'elemento visivel dentro do retangulo'.",
"",
"Inferencia: e o primitivo de hit-test por retangulo (rubber-band) referido em",
"F-004 R1/E2; o retorno booleano e o resultado do teste. Nao ha string de UI",
"nesta funcao (0 referencias a string), portanto ela nao produz a mensagem de",
"status citada na spec.",
],
"1802770d0": [
"Fato: `SetHitType(HitType)` grava flags em `+0x209`, `+0x20a`, `+0x20b`.",
"Mapeamento observado do enum (0..4):",
"",
"| HitType | +0x209 | +0x20a | +0x20b |",
"|---|---|---|---|",
"| 0 | 1 | 0 | inalterado |",
"| 1 | 1 | 1 | inalterado |",
"| 2 | 0 | 0 | inalterado |",
"| 3 | 0 | 1 | inalterado |",
"| 4 | inalterado | inalterado | 1 |",
"",
"Inferencia: os dois bytes de flag correspondem a 'casar dentro' e 'casar borda',",
"mas os nomes do enum nao estao disponiveis no binario (apenas `HitType`).",
],
"180277140": [
"Fato: `SetRect(const GRectBase<double>&)` copia os 4 doubles de origem para",
"`+0x1e0`, `+0x1e8`, `+0x1f0`, `+0x1f8` (o retangulo de hit-test).",
"",
"Fato: se `GetHeight()` do retangulo for exatamente 0.0, alarga as duas bordas Y",
"em `DAT_1804141a0 = 0.5` (medido no arquivo: `000000000000e03f` = 0.5);",
"se `GetWidth()` for 0.0, faz o mesmo nas bordas X com a mesma constante.",
"",
"Inferencia: evita retangulo degenerado quando o usuario clica num ponto",
"(rubber-band de area zero). Unidade da constante nao esta nomeada no binario;",
"pela convencao do modulo (GRectBase<double> em espaco de usuario do PDF)",
"trata-se de 0.5 unidade de usuario (tipicamente pt) - inferencia, nao fato.",
],
"18028c310": [
"Fato: `bool GOVSelectOverlapping::Select(GOElement&)` implementa consulta de",
"pertinencia em tabela hash de endereco aberto: capacidade em `+0x228`,",
"bucket em `+0x220` (16 bytes por entrada: ponteiro + contador com bit 31 de",
"marca). O ponteiro e comparado por identidade (`pGVar3 == param_1`).",
"",
"Inferencia: responde 'este elemento pertence ao conjunto de sobreposicao",
"calculado por `Select(GOPage&)`' - e o par de leitura do conjunto montado em",
"0x18028c410.",
],
"18028c410": [
"Fato: `bool GOVSelectOverlapping::Select(GOPage&)` monta dois visitantes",
"`GOVGetObjectBBoxes` e dois `GOVSelectOperatorRoll`, percorre a pagina com",
"`GOPage::Accept` e usa `GRectBase<double>::Intersects` para cruzar caixas.",
"",
"Fato: alimenta `GSet<GOOCGroup const*>::AddItem` (grupos de conteudo opcional)",
"e usa `GAllocator::GetInstance`/`GAllocator::Free` para as tabelas temporarias.",
"",
"Inferencia: e a implementacao do operador de Action List descrito pela string",
"do proprio binario 'This Action needs to be preceded by 2 Selects. It will",
"select the objects from the first selection that have a bounding box that",
"intersects with the bounding box of an object from the second selection.'",
"(string presente no binario; associacao ao endereco marcada como inferencia).",
],
"18028df80": [
"Fato: `bool GOVSelectOverlappingObjects::Select(GOPage&)`, 2073 bytes, vtable",
"em `.rdata:1804f2240`. Usa GEOMAPPER (`GeoMapper::TGraph`, `TRegionIterator`,",
"`TElementAttributeIterator`), `GOVGeoMapperTStackBuilder`, `GOPage::Accept`,",
"`GOVSelectOperator`, `GMatrixBase<double>::GetInverse` e",
"`GTable<GOObject*>::GetItemAt`/`GetCount`.",
"",
"Inferencia: reconstroi as regioes geometricas da pagina (grafo GeoMapper) e",
"seleciona os objetos cujas regioes se sobrepoem, preenchendo a tabela de",
"selecao (`GTable<GOObject*>`). E o operador citado em F-004 secao 8 como",
"`GOVSelectOverlappingObjects` - o nome da classe e fato; o comportamento",
"detalhado e inferido do grafo de chamadas.",
],
"18028d3b0": [
"Fato: `GOVSelectOverlappingObjects::Expand(GOPage&)` (205 bytes) e chamado a",
"partir do proprio operador para expandir a selecao corrente; usa",
"`GOVSelectOperator` e `GOPage::Accept`.",
"",
"Inferencia: aplica o conjunto sobreposto a selecao existente (expansao),",
"sem substituir os objetos ja selecionados. Nao foi decompilado linha a linha",
"para confirmar a semantica exata de uniao vs. substituicao.",
],
"180133230": [
"Fato: `long GOVChangeScaleSelection::Change(GOPage&)`, 1098 bytes, vtable em",
"`.rdata:18040ade0`. Monta a selecao com `GOVSelectOperator(8)`,",
"`GOVSelectContentsFromForm(0)` e `GOVSelectOperator(3)`, calcula a caixa com",
"`GOVGetClippedBoundingBox(true,false)` e a transforma por",
"`GOPage::GetPageMatrix` + `GRectBase<double>::Transform`.",
"",
"Fato: o modo de escala vem de `*(int*)(this+0x1e8)` com 6 ramos observados:",
"`1` (sem matriz explicita), `2` (matriz em `+0x200`), `3` (razao",
"`campo(+0x1f0) / largura`), `4` (`(largura + campo) / largura`) e",
"`5` (razao entre a largura da caixa de pagina - `GOPage::GetPageBox`, tipo em",
"`+0x210` - e a largura da selecao). A matriz resultante e aplicada via",
"`GOVChangeMatrix::Set`.",
"",
"Inferencia: e o operador de Action List 'Scale selection' (string existente no",
"binario; o titulo real vem de `GStringPool::GetString(0x73faa)` em",
"`GOVChangeScaleSelection::GetTitle` @ 0x180133940, cujo texto nao e",
"resolvivel estaticamente sem a tabela do GStringPool).",
],
"1801303e0": [
"Fato: `long GOVChangeRotateSelection::Change(GOPage&)`, 714 bytes, vtable em",
"`.rdata` (ver ponteiro listado). O ponto de referencia vem de",
"`*(int*)(this+0x1e8)`: valores 1..5 => canto de caixa de pagina",
"(`GOPage::GetPageBox` + `GPositionSupport::GetCorner`), 6 =>",
"`GOVGetFixedBoundingBox(true,true)`, 7 => `GOVGetClippedBoundingBox(true,true)`.",
"",
"Fato: o angulo e `campo(+0x1f0) * DAT_18044ef28`; `DAT_18044ef28` mede",
"0.017453292519943295 rad = pi/180, portanto o campo esta em graus.",
"`sin`/`cos` montam a matriz 2D e `GOVChangeMatrix` e criado com id de mudanca",
"`0x3ea`.",
"",
"Inferencia: e o operador 'Rotate selection'; o id 0x3ea aparece tambem em",
"`GOVChangeFlipSelection::Change` e `GOVCloneSelection::ConfigChangeMatrix`",
"(mesma familia de mudanca de matriz registrada no undo log).",
],
"1800940d0": [
"Fato: `long GOVChangeFlipSelection::Change(GOPage&)`, 668 bytes, vtable em",
"`.rdata` (ver ponteiro listado). Modo 0 => `GOVGetFixedBoundingBox(true,true)`;",
"modo 1 => `GOVGetClippedBoundingBox(true,true)`; em ambos aplica",
"`GOPage::GetPageMatrix` + `GRectBase<double>::Transform` e pega um canto com",
"`GPositionSupport::GetCorner(...,0)`.",
"",
"Fato: `this[0x1ec]` seleciona o eixo do espelhamento e alimenta os dois",
"fatores da matriz; apos montar o `GOVChangeMatrix(...,0x3ea)` a funcao grava",
"o ponteiro em `+0x1f8` e liga a flag `this[0x1f0] = 1`.",
"",
"Inferencia: e o operador 'Flip selection' (horizontal/vertical). O Ghidra nao",
"recupera com fidelidade os doubles movidos em registradores nesta funcao",
"(sequencias `CONCAT44`), por isso a forma exata da matriz NAO e afirmada aqui.",
],
"18022c220": [
"Fato: `GOVCloneSelection::ConfigChangeMatrix()` cria/caches um",
"`GOVChangeMatrix` a partir de `GOLocation::GetCurrentToUserMatrix`",
"pos-concatenada com a matriz em `+0x1f8` (`GMatrixBase<double>::PostConcat`),",
"com id de mudanca `0x3ea`; o cache fica na tabela em `+0x290` indexada por",
"`*(int*)(this+0x29c)`.",
"",
"Inferencia: e a matriz usada para clonar/copiar a selecao mantendo-a no mesmo",
"lugar em coordenadas de usuario; o unico chamador direto e",
"`GOVCloneSelection::AddContentObjectToCurrentContent`.",
],
"18030b240": [
"Fato: `GOVGetSelectedObjects::GetObjects()` tem 11 bytes e retorna",
"`**(undefined8**)(this+0x1e0)` - ou seja, desreferencia o campo `+0x1e0` e",
"devolve a `GTable<GOObject*>` corrente.",
"",
"Fato: o unico chamador direto e `GOVChangeIsolateClippaths::Visit`",
"(0x1800ADc30).",
"",
"Inferencia: accessor da selecao corrente usada pelos operadores; nao",
"produz nem altera o estado de selecao.",
],
"180341480": [
"Fato: `bool GOVSelectObjects::Select(GOObject&)` tem 32 bytes: se o ponteiro",
"em `+0x220` for nulo chama `std::_Xbad_function_call` (MSVCP140), caso",
"contrario invoca o functor no deslocamento `+0x10` do objeto apontado.",
"",
"Inferencia: `GOVSelectObjects` recebe um predicado (`std::function`) e o",
"aplica a cada objeto; a funcao aqui e apenas o despacho do predicado.",
"Confianca media: a logica real esta no functor configurado em tempo de",
"execucao (nao resolvivel estaticamente).",
],
}


def ascii_text(s):
    s = unicodedata.normalize("NFKD", s)
    s = s.encode("ascii", "ignore").decode("ascii")
    return s


def parse(path):
    d = {"callers": [], "callees": [], "strings": [], "ptrs": [], "code": []}
    section = None
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        for line in f:
            line = line.rstrip("\n")
            if line.startswith("[callers]"):
                section = "callers"; continue
            if line.startswith("[callees]"):
                section = "callees"; continue
            if line.startswith("[string_refs]"):
                section = "strings"; continue
            if line.startswith("[pointer_hits_non_exec]"):
                section = "ptrs"; continue
            if line.startswith("[decompiled]"):
                section = "code"; continue
            if section is None:
                m = re.match(r"^(\w+):\s*(.*)$", line)
                if m:
                    d[m.group(1)] = m.group(2)
            elif section == "code":
                d["code"].append(line)
            elif line.strip():
                d[section].append(line.strip())
    return d


def main():
    index = {}
    with open(os.path.join(RAW, "index.tsv"), "r", encoding="utf-8") as f:
        next(f)
        for line in f:
            p = line.rstrip("\n").split("\t")
            if len(p) >= 7:
                index[p[0]] = p
    out = []
    for addr, row in sorted(index.items(), key=lambda kv: int(kv[0], 16)):
        name = row[1]
        txt = os.path.join(RAW, "PDFObjectActions__%s.txt" % addr)
        if not os.path.exists(txt):
            continue
        d = parse(txt)
        short = name.split("::")[-1]
        conf = CONF.get(addr, "media")
        strings = [s.split(" ", 1)[1] if " " in s else s for s in d["strings"]]
        xrefs = [c.split(" ")[0] for c in d["callers"]]
        safe_strings = [s.replace('"', "'") for s in strings][:8]

        lines = []
        lines.append("---")
        lines.append("modulo: PDFObjectActions.dll")
        lines.append("funcao: %s" % name)
        lines.append("endereco: 0x%s" % addr)
        lines.append("versao: 24.03.10017")
        lines.append("confianca: %s" % conf)
        lines.append("xrefs: [%s]" % ", ".join("0x" + x for x in xrefs[:12]))
        lines.append("strings: [%s]" % ", ".join('"%s"' % s for s in safe_strings))
        lines.append("---")
        lines.append("")
        lines.append("# %s @ 0x%s" % (name, addr))
        lines.append("")
        lines.append("Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.")
        lines.append("")
        lines.append("## Identidade")
        lines.append("")
        lines.append("| Campo | Valor |")
        lines.append("|---|---|")
        lines.append("| Endereco | `0x%s` |" % addr)
        lines.append("| Nome no binario | `%s` |" % name)
        lines.append("| Assinatura (Ghidra) | `%s` |" % ascii_text(d.get("signature", "")))
        lines.append("| Parametros | %s |" % d.get("param_count", "?"))
        lines.append("| Bytes de corpo | %s |" % d.get("body_bytes", "?"))
        lines.append("| Chamadores | %d |" % len(d["callers"]))
        lines.append("| Chamadas diretas | %d |" % len(d["callees"]))
        lines.append("")
        note = NOTES.get(addr)
        if note:
            lines.append("## Papel provavel")
            lines.append("")
            for n in note:
                lines.append(n)
            lines.append("")
        lines.append("## Xrefs de entrada (quem chama)")
        lines.append("")
        if d["callers"]:
            for c in d["callers"][:20]:
                lines.append("- `%s`" % (("0x" + c) if c[0].isdigit() else c))
        else:
            lines.append("- nenhuma chamada direta detectada (provavel entrada por vtable/export)")
        lines.append("")
        lines.append("## Chamadas diretas (quem esta funcao chama)")
        lines.append("")
        if d["callees"]:
            for c in d["callees"][:25]:
                lines.append("- `%s`" % (("0x" + c) if c[0].isdigit() else c))
        else:
            lines.append("- nenhuma")
        lines.append("")
        lines.append("## Strings referenciadas pela propria funcao")
        lines.append("")
        if d["strings"]:
            lines.append("| Endereco | String |")
            lines.append("|---|---|")
            for s in d["strings"][:25]:
                parts = s.split(" ", 1)
                val = parts[1] if len(parts) > 1 else ""
                lines.append("| `%s` | `%s` |" % (parts[0], val.replace("|", "\\|")))
        else:
            lines.append("- nenhuma string literal referenciada diretamente")
        lines.append("")
        lines.append("## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)")
        lines.append("")
        if d["ptrs"]:
            for p in d["ptrs"][:12]:
                lines.append("- `%s`" % p)
        else:
            lines.append("- nenhum ponteiro absoluto encontrado (funcao pode ser chamada so por `call rel32`)")
        lines.append("")
        code = d["code"]
        # corta cabecalho de prototipo redundante e limita tamanho
        limit = 110
        snippet = code[:limit]
        lines.append("## Pseudocodigo (extrato do Ghidra, cortado em %d linhas)" % limit)
        lines.append("")
        lines.append("```c")
        for c in snippet:
            lines.append(ascii_text(c).rstrip())
        if len(code) > limit:
            lines.append("/* ... %d linhas omitidas ... */" % (len(code) - limit))
        lines.append("```")
        lines.append("")
        lines.append("Raw completo: `_raw/PDFObjectActions__%s.txt`." % addr)
        lines.append("")
        body = "\n".join(ascii_text(x) if not x.startswith("---") else x for x in lines) + "\n"
        outp = os.path.join(BASE, "PDFObjectActions__0x%s.md" % addr)
        with open(outp, "w", encoding="utf-8", newline="\n") as f:
            f.write(body)
        out.append(outp)
    print("gerados: %d" % len(out))


if __name__ == "__main__":
    main()
