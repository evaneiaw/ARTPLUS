---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = FUN_1801652B0 em 0x1801652B0"
endereco: 0x18016F250
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x18016F250

`0x18016F250` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x18016F250	inMemory=true	isFunctionEntry=false	entryName=-	containing=18016edc0 FUN_18016edc0	codeUnit=false

- container na v240: 0x18016EDC0 FUN_18016EDC0 (2612 bytes, outro assunto)

## Equivalente v240

- endereco: `0x1801652B0`
- simbolo: `FUN_1801652B0 (fabricante do PDFPlusBearerBar)`
- mangled: `(sem simbolo; funcao anonima)`
- prova de equivalencia: Fabrica (R2/"Entrada"): aloca o objeto, transfere o `shared_ptr<FormPaint const>` do chamador (zerando o do chamador) e chama o ctor 0x18012C640.
- nota: A spec cita `new (0x790)`; na v240 a alocacao e de 0x858 bytes.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_1801652b0.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
