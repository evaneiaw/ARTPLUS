---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::TaskMarkSets::ApplyMarksFromSet"
endereco: 0x180243EC0
versao: 24.03.10017
confianca: alta
xrefs: ["0x180243EA0"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x180243EC0

## Identificacao lida no programa v240

- endereco: `0x180243ec0`
- simbolo: `DocumentMarks::TaskMarkSets::ApplyMarksFromSet`
- assinatura: `bool __thiscall ApplyMarksFromSet(vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_> * param_1, Page * param_2, bool param_3)`
- corpo: `180243ec0..180243f30` (109 bytes), convencao `__thiscall`, thunk=false, external=false
- parametros: 4
- referencias apontando para a entrada: 4 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Aplicacao por mark set -- **equivalente v240** do ID historico
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
validacao de versao nem leitura de arquivo aqui -- isso fica em `ReadMarkSetFile`.

## Chamadores (xrefs de chamada)

- `180243ea0 ApplyExtraMarkSet`

## Chamadas diretas (2)

- `180245380 CopyMarksToPageWithLog`
- `EXTERNAL:00000170 GetPagesBegin`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- Nenhuma: corpo integral reproduzido.

## Confianca

`alta` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
