---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::SetBearerBarOffset em 0x1800A89D0"
endereco: 0x1800AA3C0
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x1800AA3C0

`0x1800AA3C0` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x1800AA3C0	inMemory=true	isFunctionEntry=true	entryName=FUN_1800aa3c0	containing=1800aa3c0 FUN_1800aa3c0	codeUnit=true

- container na v240: ATENCAO: `isFunctionEntry=true` - na v240 este endereco e a entrada de uma funcao DIFERENTE (`FUN_1800AA3C0`), nao do setter de Bearer Bar

## Equivalente v240

- endereco: `0x1800A89D0`
- simbolo: `DocumentMarks::SetBearerBarOffset`
- mangled: `?SetBearerBarOffset@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusBearerBar@DocumentMarks@@@Z@std@@AEBV?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@@Z`
- prova de equivalencia: Setter transacional de `Offset` (R12). E o par que a spec usa para a nota de ICF `SetOffset` <-> `setWidth`.
- nota: Este e o unico dos 19 IDs em que o endereco antigo coincide com uma entrada de funcao valida na v240 - e justamente por isso e o caso mais perigoso: resolver o ID por endereco aqui devolve a funcao errada.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_1800a89d0.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
