---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::BearerBar::BearerBar em 0x18001C200"
endereco: 0x18001E350
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x18001E350

`0x18001E350` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x18001E350	inMemory=true	isFunctionEntry=false	entryName=-	containing=18001de30 DocumentMarks::BearerBar::regenerateMarkImp	codeUnit=true

- container na v240: 0x18001DE30 DocumentMarks::BearerBar::regenerateMarkImp (mesmo container do ID anterior); `codeUnit=true` apenas indica que o endereco coincide com o inicio de uma instrucao

## Equivalente v240

- endereco: `0x18001C200`
- simbolo: `DocumentMarks::BearerBar::BearerBar`
- mangled: `??0BearerBar@DocumentMarks@@IEAA@AEBV01@AEAVCloneStrategy@ArtDoc@@@Z`
- prova de equivalencia: Construtor de clone legado (protected): a spec (R13) diz que o ctor de clone delega a copia a DynamicMark/CloneStrategy. O v240 faz isso e ainda copia os campos +0x750..+0x780.
- nota: Unico caller: `0x18001CC10 DocumentMarks::BearerBar::Clone`. Nao ha outro xref de chamada.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001c200.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
