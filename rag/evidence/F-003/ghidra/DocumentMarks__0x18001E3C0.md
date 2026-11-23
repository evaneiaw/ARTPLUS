---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::BearerBar::BearerBar em 0x18001C270"
endereco: 0x18001E3C0
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x18001E3C0

`0x18001E3C0` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x18001E3C0	inMemory=true	isFunctionEntry=false	entryName=-	containing=18001de30 DocumentMarks::BearerBar::regenerateMarkImp	codeUnit=false

- container na v240: 0x18001DE30 DocumentMarks::BearerBar::regenerateMarkImp (corpo 0x18001DE30..0x18001E417, 1511 bytes) - o endereco cai 0x57 bytes DEPOIS do fim do corpo, na regiao nao atribuida a funcao

## Equivalente v240

- endereco: `0x18001C270`
- simbolo: `DocumentMarks::BearerBar::BearerBar`
- mangled: `??0BearerBar@DocumentMarks@@QEAA@_N@Z`
- prova de equivalencia: Construtor legado. A spec (R2, tabela "Legado") descreve exatamente este ctor: escreve width/extend/offset/location e chama DynamicMark(this, true, 0xFD).
- nota: Prova de chamada no binario v240: `0x18010E4CE` (UNCONDITIONAL_CALL dentro de `FUN_18010E0F0`) -> `0x18001C270`. E o ponto em que `createDynamicObject` instancia a BearerBar depois do `memcmp` de `AIDynamicMarks-BearerBar`.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001c270.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
