---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::BearerBar::Clone em 0x18001CC10"
endereco: 0x18001EDA0
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x18001EDA0

`0x18001EDA0` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x18001EDA0	inMemory=true	isFunctionEntry=false	entryName=-	containing=18001ed80 FUN_18001ed80	codeUnit=false

- container na v240: 0x18001ED80 FUN_18001ED80 (funcao sem simbolo) - o endereco cai no corpo dela, 0x20 bytes apos o inicio

## Equivalente v240

- endereco: `0x18001CC10`
- simbolo: `DocumentMarks::BearerBar::Clone`
- mangled: `?Clone@BearerBar@DocumentMarks@@UEBAPEAV12@AEAVCloneStrategy@ArtDoc@@@Z`
- prova de equivalencia: `BearerBar::Clone` e a unica rotina que aloca a classe e chama o ctor de clone; no v240 aloca 0x788 bytes e chama 0x18001C200. A spec cita a mesma funcao na R13 (clone preserva parametros).
- nota: `0x18001ED80` (container v240) e uma funcao de outro assunto; o v25 `0x18001EDA0` nao tem relacao com ela. Nao usar o container como equivalente.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001cc10.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
