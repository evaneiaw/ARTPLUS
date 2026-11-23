---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog"
endereco: 0x180245380
versao: 24.03.10017
confianca: alta
xrefs: ["0x180243F40", "0x180243EC0", "0x180248720"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x180245380

## Identificacao lida no programa v240

- endereco: `0x180245380`
- simbolo: `DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog`
- assinatura: `void __thiscall CopyMarksToPageWithLog(Page * param_1, Page * param_2, bool param_3)`
- corpo: `180245380..180245b7e` (2041 bytes), convencao `__thiscall`, thunk=false, external=false
- parametros: 4
- referencias apontando para a entrada: 12 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Copia pagina -> pagina com **log de diagnostico** -- **equivalente v240** do ID
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
     `"WARNING: Missing Named Objects: %s.\nReferenced from Mark Set: %s.\nDynamic Marks linked to a missing object were removed from page %lu.\n"`
     com id `"DocumentMarks.Warning.MissingNamedObject"` e severidade 1;
   - em seguida a variante de caixa de pagina:
     `"WARNING: Missing Page Box: %s.\nReferenced from Mark Set: %s.\nDynamic Marks linked to a missing page box were relinked to available page box on page %lu.\n"`
     com id `"DocumentMarks.Warning.MissingPageBox"`.

E o unico ponto do fluxo de Mark Set que produz texto de log observavel na UI.

## Chamadores (xrefs de chamada)

- `180243f40 ApplyRelevantMarkSets`
- `180243ec0 ApplyMarksFromSet`
- `180248720 PrepareMarksCachePage`

## Chamadas diretas (16)

- `EXTERNAL:000004a2 ToUTF8String`
- `1802cbea4 free`
- `18005db00 FUN_18005db00`
- `EXTERNAL:0000016e GetFilePath`
- `EXTERNAL:000005ad _invalid_parameter_noinfo_noreturn`
- `18000cc20 FUN_18000cc20`
- `1802cbe68 FUN_1802cbe68`
- `EXTERNAL:00000168 GetContent`
- `EXTERNAL:000002ae GetPageIndex`
- `180016f40 FUN_180016f40`
- `EXTERNAL:000004e8 stem_v3`
- `1802ccf86 memmove`
- `1800426f0 CopyMarksToPage`
- `18003c5b0 FUN_18003c5b0`
- `EXTERNAL:0000017c GetDocument`
- `1802cbfd0 __security_check_cookie`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- Nenhuma lacuna de leitura para as strings e ids de mensagem; o formato exato de concatenacao dos nomes (`", "`) foi lido no corpo.

## Confianca

`alta` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
