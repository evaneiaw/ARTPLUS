---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::PDFPlusBearerBar::getMarkType em 0x18012EB70"
endereco: 0x180131FE0
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x180131FE0

`0x180131FE0` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x180131FE0	inMemory=true	isFunctionEntry=false	entryName=-	containing=180131fd0 DocumentMarks::PDFPlusClipMark::RemoveInvalidCustomFormulasImp	codeUnit=false

- container na v240: 0x180131FD0 DocumentMarks::PDFPlusClipMark::RemoveInvalidCustomFormulasImp (outra classe)

## Equivalente v240

- endereco: `0x18012EB70`
- simbolo: `DocumentMarks::PDFPlusBearerBar::getMarkType`
- mangled: `?getMarkType@PDFPlusBearerBar@DocumentMarks@@UEBA?AV?$basic_string_view@DU?$char_traits@D@std@@@std@@XZ`
- prova de equivalencia: Identidade de tipo (R13): devolve o `string_view` de `DynamicObject_PDFPlusBearerBar` (literal em 0x180316458, 30 bytes).
- nota: Para o tipo legado o equivalente e `DocumentMarks::BearerBar::getMarkType` em 0x18001D6F0 (literal `AIDynamicMarks-BearerBar` em 0x1802FA130, 24 bytes).

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012eb70.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
