---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::ApplyMarkSet"
endereco: 0x1800147F0
versao: 24.03.10017
confianca: alta
xrefs: []
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x1800147F0

## Identificacao lida no programa v240

- endereco: `0x1800147f0`
- simbolo: `DocumentMarks::ApplyMarkSet`
- assinatura: `void __cdecl ApplyMarkSet(Document * param_1, path * param_2, bool param_3, set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_> * param_4)`
- corpo: `1800147f0..1800149f6` (519 bytes), convencao `__cdecl`, thunk=false, external=false
- parametros: 4
- referencias apontando para a entrada: 3 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Carrega um documento de mark set a partir do caminho (`param_2`) usando o helper
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

Nao referencia strings de mensagem: qualquer erro/diagnostico e reportado pelos helpers.

## Chamadores (xrefs de chamada)

- nenhum chamador interno registrado (funcao de entrada/exportada; ver `refTo` do bruto)

## Chamadas diretas (15)

- `1802cbea4 free`
- `EXTERNAL:00000171 GetPagesEnd`
- `EXTERNAL:00000176 ActionGroupCreator`
- `180043340 DeleteMarks`
- `EXTERNAL:00000177 ~ActionGroupCreator`
- `EXTERNAL:0000016d ~Document`
- `1800316e0 GetChangeTracker`
- `180014c80 FUN_180014c80`
- `EXTERNAL:00000170 GetPagesBegin`
- `180013be0 FUN_180013be0`
- `1800138d0 FUN_1800138d0`
- `1800426f0 CopyMarksToPage`
- `180016510 FUN_180016510`
- `EXTERNAL:00000168 GetContent`
- `1802cbfd0 __security_check_cookie`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- Helper de carga (`FUN_180014c80`) nao esta identificado por simbolo; a atribuicao "le o arquivo de mark set" e inferencia pela assinatura (path -> Document*) e pelo uso identico em ApplyMarkSetToPage.

## Confianca

`alta` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
