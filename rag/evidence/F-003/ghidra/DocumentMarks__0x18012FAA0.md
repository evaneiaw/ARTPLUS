---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar em 0x18012C640"
endereco: 0x18012FAA0
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x18012FAA0

`0x18012FAA0` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x18012FAA0	inMemory=true	isFunctionEntry=false	entryName=-	containing=18012f6e0 DocumentMarks::PDFPlusBearerBar::regenerateMarkImp	codeUnit=false

- container na v240: 0x18012F6E0 DocumentMarks::PDFPlusBearerBar::regenerateMarkImp (0x420 bytes dentro do corpo)

## Equivalente v240

- endereco: `0x18012C640`
- simbolo: `DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar`
- mangled: `??0PDFPlusBearerBar@DocumentMarks@@QEAA@V?$shared_ptr@$$CBVFormPaint@ArtPaint@@@std@@@Z`
- prova de equivalencia: Ctor PDF+ (R2, tabela "PDF+"): defaults Offset 0, Extend 0, Direction 1, referencia PageBox 3, SizeReference 0, anchors (5,3) em MarkPosition.
- nota: ATENCAO: os offsets dos campos mudaram na v240 (+0x758/+0x768/+0x770/+0x778/+0x7f8) e o objeto passou a ser alocado com 0x858 bytes (fabricante `0x1801652B0`). A tabela de R2 usa os offsets da v25.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012c640.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
