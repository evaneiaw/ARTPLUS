---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::PDFPlusBearerBar::UpdateSizeReference em 0x18012E950"
endereco: 0x180131DC0
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x180131DC0

`0x180131DC0` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x180131DC0	inMemory=true	isFunctionEntry=false	entryName=-	containing=180131c80 DocumentMarks::PDFPlusClipMark::GetNestedMarkFormulas	codeUnit=false

- container na v240: 0x180131C80 DocumentMarks::PDFPlusClipMark::GetNestedMarkFormulas (outra classe)

## Equivalente v240

- endereco: `0x18012E950`
- simbolo: `DocumentMarks::PDFPlusBearerBar::UpdateSizeReference`
- mangled: `?UpdateSizeReference@PDFPlusBearerBar@DocumentMarks@@QEAAXXZ`
- prova de equivalencia: Correcao silenciosa de `SizeReference` (R5): valores 1..4 e 5..8 sao zerados quando a `Direction` nao casa.
- nota: O container v240 pertence a PDFPlusClipMark; nao e o validador de Bearer Bar. A direcao da regra na v240 e o INVERSO do que a R5 afirma - ver bloqueio no manifest.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012e950.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
