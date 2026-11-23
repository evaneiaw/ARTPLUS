---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::BearerBar::regenerateMarkImp em 0x18001DE30"
endereco: 0x18001FDB0
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x18001FDB0

`0x18001FDB0` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x18001FDB0	inMemory=true	isFunctionEntry=false	entryName=-	containing=-	codeUnit=true

- container na v240: (nenhuma) - fora de qualquer funcao reconhecida

## Equivalente v240

- endereco: `0x18001DE30`
- simbolo: `DocumentMarks::BearerBar::regenerateMarkImp`
- mangled: `?regenerateMarkImp@BearerBar@DocumentMarks@@MEAAXXZ`
- prova de equivalencia: Geracao da geometria legada (R6): 1 `Path` por bit de `Location`, insercao depois da origem, remocao dos filhos excedentes, `applyColor` e o log ` Bearer Bar update` quando o nivel de debug > 2.
- nota: Detalhe util: o proprio ID historico `0x18001E3C0` cai DENTRO do corpo desta funcao na v240, o que mostra que o deslocamento nao e constante.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001de30.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
