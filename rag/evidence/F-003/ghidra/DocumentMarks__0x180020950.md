---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::BearerBar::updatePdfPropertiesDictImp em 0x18001E9A0"
endereco: 0x180020950
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x180020950

`0x180020950` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x180020950	inMemory=true	isFunctionEntry=false	entryName=-	containing=1800208d0 FUN_1800208d0	codeUnit=true

- container na v240: 0x1800208D0 FUN_1800208D0 (funcao sem simbolo, outro assunto) - 0x80 bytes dentro dela

## Equivalente v240

- endereco: `0x18001E9A0`
- simbolo: `DocumentMarks::BearerBar::updatePdfPropertiesDictImp`
- mangled: `?updatePdfPropertiesDictImp@BearerBar@DocumentMarks@@MEAAXAEAVDictionary@ArtDoc@@@Z`
- prova de equivalencia: Escritor legado de `DM-BearerBarParams` (R8): sempre `Version = 2`, grava Width/Extend/Offset em mm e Location; nao grava `IsVertical`.
- nota: O container v240 `0x1800208D0` nao e o escritor; o escritor e o membro virtual `0x18001E9A0` (vtable de `BearerBar`).

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001e9a0.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
