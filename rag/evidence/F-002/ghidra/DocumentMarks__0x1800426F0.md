---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::CopyMarksToPage"
endereco: 0x1800426F0
versao: 24.03.10017
confianca: alta
xrefs: ["0x1800147F0", "0x180042B40", "0x180245380", "0x180014A00"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x1800426F0

## Identificacao lida no programa v240

- endereco: `0x1800426f0`
- simbolo: `DocumentMarks::CopyMarksToPage`
- assinatura: `bool __cdecl CopyMarksToPage(Page * param_1, Page * param_2, bool param_3, set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_> * param_4, set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_> * param_5, set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_> * param_6, bool param_7)`
- corpo: `1800426f0..180042b3d` (1102 bytes), convencao `__cdecl`, thunk=false, external=false
- parametros: 7
- referencias apontando para a entrada: 7 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

Nucleo de copia pagina -> pagina das marcas dinamicas; e o ponto por onde passam
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
`CopyMarksToPageWithLog`, 0x180245380).

## Chamadores (xrefs de chamada)

- `1800147f0 ApplyMarkSet`
- `180042b40 CopyPageWithMarks`
- `180245380 CopyMarksToPageWithLog`
- `180014a00 ApplyMarkSetToPage`

## Chamadas diretas (27)

- `EXTERNAL:0000017c GetDocument`
- `180115f40 GetFeatures`
- `EXTERNAL:00000267 FindModule`
- `180044820 FUN_180044820`
- `EXTERNAL:0000022c AddClone`
- `180044310 FUN_180044310`
- `EXTERNAL:0000023b GetDynamicObjects`
- `EXTERNAL:00000245 InksChanged`
- `EXTERNAL:000001a4 ~ConstVisitorBase`
- `EXTERNAL:0000022d RelinkDynamicObjects`
- `18003bf60 FUN_18003bf60`
- `EXTERNAL:00000231 GetContent`
- `EXTERNAL:0000016f GetInfoFlag`
- `18003df00 FUN_18003df00`
- `EXTERNAL:00000177 ~ActionGroupCreator`
- `EXTERNAL:00000261 Accept`
- `1802cbea4 free`
- `1800461a0 FUN_1800461a0`
- `1802cbe68 FUN_1802cbe68`
- `EXTERNAL:00000176 ActionGroupCreator`
- `EXTERNAL:00000168 GetContent`
- `EXTERNAL:0000022a ~CloneStrategy`
- `EXTERNAL:00000201 GetDocument`
- `EXTERNAL:0000025b GetObjectWithID`
- `18003c1c0 FUN_18003c1c0`
- `1802ccf7a __RTDynamicCast`
- `180042c00 FUN_180042c00`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- Os helpers `FUN_180044310`, `FUN_180044820`, `FUN_18003df00`, `FUN_1800461a0` e `FUN_180042c00` nao tem simbolo; a descricao do papel de cada um e inferencia pela assinatura e pela ordem das chamadas.

## Confianca

`alta` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
