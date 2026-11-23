---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::ApplyMarkSetToPage"
endereco: 0x180014A00
versao: 24.03.10017
confianca: alta
xrefs: []
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x180014A00

## Identificacao lida no programa v240

- endereco: `0x180014a00`
- simbolo: `DocumentMarks::ApplyMarkSetToPage`
- assinatura: `void __cdecl ApplyMarkSetToPage(Page * param_1, path * param_2, bool param_3, set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_> * param_4)`
- corpo: `180014a00..180014bc1` (450 bytes), convencao `__cdecl`, thunk=false, external=false
- parametros: 4
- referencias apontando para a entrada: 3 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Variante de `ApplyMarkSet` restrita a **uma pagina** (`param_1`). O documento alvo e
obtido por `Page::GetContent(param_1)` -> `Content::GetDocument`, nao pelo documento inteiro.

Fluxo observado:
1. `FUN_180014c80(local_98, param_2)` carrega o mark set do caminho.
2. Falha de carga + `param_3` verdadeiro -> `DeleteMarks(param_1)` (somente a pagina alvo).
3. Carga ok -> toca change tracker, abre `ActionGroupCreator` no documento da pagina, pega a
   primeira pagina do mark set, apaga marcas se `param_3`, chama
   `CopyMarksToPage(primeiraPaginaDoMarkSet, param_1, true, NULL, NULL, param_4, true)`
   e registra o lambda no change tracker.

Diferenca para 0x1800147F0: sem laco sobre paginas; sem `EnableUpdates`.

## Chamadores (xrefs de chamada)

- nenhum chamador interno registrado (funcao de entrada/exportada; ver `refTo` do bruto)

## Chamadas diretas (15)

- `EXTERNAL:0000017c GetDocument`
- `1802cbea4 free`
- `180016510 FUN_180016510`
- `EXTERNAL:00000176 ActionGroupCreator`
- `180043340 DeleteMarks`
- `EXTERNAL:00000168 GetContent`
- `EXTERNAL:00000170 GetPagesBegin`
- `EXTERNAL:0000016d ~Document`
- `1800316e0 GetChangeTracker`
- `180014c80 FUN_180014c80`
- `180013be0 FUN_180013be0`
- `1800138d0 FUN_1800138d0`
- `1800426f0 CopyMarksToPage`
- `EXTERNAL:00000177 ~ActionGroupCreator`
- `1802cbfd0 __security_check_cookie`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- Mesma inferencia do helper de carga de 0x1800147F0.

## Confianca

`alta` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
