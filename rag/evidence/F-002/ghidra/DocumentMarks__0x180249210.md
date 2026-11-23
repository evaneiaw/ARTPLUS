---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::TaskMarkSets::RecreateLoadedMarks"
endereco: 0x180249210
versao: 24.03.10017
confianca: alta
xrefs: ["0x180246120"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x180249210

## Identificacao lida no programa v240

- endereco: `0x180249210`
- simbolo: `DocumentMarks::TaskMarkSets::RecreateLoadedMarks`
- assinatura: `void __thiscall RecreateLoadedMarks(void)`
- corpo: `180249210..180249337` (296 bytes), convencao `__thiscall`, thunk=false, external=false
- parametros: 1
- referencias apontando para a entrada: 4 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Reconstroi as marcas carregadas do documento de mark set (`this+0x8`).
Chamada por `LoadCacheDocument` (0x180246120).

Corpo (296 bytes): percorre `Document::GetPagesBegin/GetPagesEnd(doc)`; para **cada pagina**
executa duas passagens (`iVar5 = 0, 1`) chamando
`DocumentEdit::MakeForm(pageContent, lambda<bool(ContentObject const&)>)` e, quando o retorno e
nao nulo, `FUN_180046160(form, iVar5 != 0)`. No final chama `RemoveStaticContent(this)`
(0x1802493F0).

Leitura: converte em forma estatica os objetos que satisfazem o predicado do lambda, em duas
categorias (flag 0 e flag 1), e remove o conteudo estatico remanescente.

## Chamadores (xrefs de chamada)

- `180246120 LoadCacheDocument`

## Chamadas diretas (8)

- `EXTERNAL:00000168 GetContent`
- `EXTERNAL:000000c9 MakeForm`
- `180046160 FUN_180046160`
- `EXTERNAL:00000171 GetPagesEnd`
- `1802493f0 RemoveStaticContent`
- `EXTERNAL:00000170 GetPagesBegin`
- `180016510 FUN_180016510`
- `1802cbfd0 __security_check_cookie`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- O predicado do lambda nao foi reconstruido (corpo do functor nao decompilado); o efeito exato de cada uma das duas passagens e inferencia.

## Confianca

`alta` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
