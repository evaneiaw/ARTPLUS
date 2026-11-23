---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::TaskMarkSets::ReadMarkSetFile"
endereco: 0x180248D30
versao: 24.03.10017
confianca: alta
xrefs: ["0x1802461B0", "0x180246120", "0x1802463E0"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x180248D30

## Identificacao lida no programa v240

- endereco: `0x180248d30`
- simbolo: `DocumentMarks::TaskMarkSets::ReadMarkSetFile`
- assinatura: `unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_> __thiscall ReadMarkSetFile(path * param_1, bool * param_2)`
- corpo: `180248d30..180249203` (1226 bytes), convencao `__thiscall`, thunk=false, external=false
- parametros: 3
- referencias apontando para a entrada: 6 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Le um arquivo de mark set e devolve `std::unique_ptr<ArtDoc::Document>`; o bool por
referencia (`param_2`) recebe a condicao de erro. Chamada por `LoadMarkSets` (0x1802463E0),
`LoadExtraMarkSet` (0x1802461B0) e `LoadCacheDocument` (0x180246120).

Fluxo observado (trechos literais do decompilado):
1. `*in_R9 = 0` (zera a flag de erro) e `boost::filesystem::detail::status(path, err)`.
   - Se `status < 2` (arquivo inexistente/nao regular): emite no reporter `*(this+0x1F8)`
     `"NDLTaskMessages.DocumentMarks.MarkSetFileDoesNotExist"` com severidade 2 e o caminho
     exibido (`filename_v3` + `ToFileURI` + `GetDisplayPath`), seguido do texto
     `"Markset file '%s' does not exist!\n"`. Retorna documento vazio.
2. Se existe: monta `ReadOptions`, chama `Document::Create` + `ForceDocumentLoad`
   (0x180115E90) e valida o resultado.
   - Falha de leitura/parse: emite `"NDLTaskMessages.DocumentMarks.MarkSetFileError"` e o texto
     `"Markset file '%s' error!\n"`.
3. `ContainsInputFileMark` (0x180115040): se o documento de mark set contem marca de arquivo de
   entrada, emite `"NDLTaskMessages.DocumentMarks.MarkSetContainsInputFileMark"`.

Nao ha verificacao de versao (`kVersionTooOld`/`kVersionTooNew`) **dentro desta funcao**: essas
strings existem no binario mas nao sao referenciadas aqui.

## Chamadores (xrefs de chamada)

- `1802461b0 LoadExtraMarkSet`
- `180246120 LoadCacheDocument`
- `1802463e0 LoadMarkSets`

## Chamadas diretas (16)

- `EXTERNAL:000004a2 ToUTF8String`
- `1802cbea4 free`
- `EXTERNAL:000004ec filename_v3`
- `EXTERNAL:0000016d ~Document`
- `EXTERNAL:000005ad _invalid_parameter_noinfo_noreturn`
- `EXTERNAL:0000016c Create`
- `EXTERNAL:0000016b ~ReadOptions`
- `EXTERNAL:0000049f GetDisplayPath`
- `EXTERNAL:000004ee status`
- `EXTERNAL:000004a1 ToFileURI`
- `180115e90 ForceDocumentLoad`
- `180016f40 FUN_180016f40`
- `1800d4b20 FUN_1800d4b20`
- `180115040 ContainsInputFileMark`
- `EXTERNAL:00000169 ReadOptions`
- `1802cbfd0 __security_check_cookie`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- As etapas internas de ReadOptions/Create/ForceDocumentLoad nao foram seguidas linha a linha; a ordem exacta entre elas e inferencia pelo conjunto de callees.

## Confianca

`alta` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
