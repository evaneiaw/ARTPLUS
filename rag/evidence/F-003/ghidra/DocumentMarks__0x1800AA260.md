---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::SetBearerBarExtend em 0x1800A8860"
endereco: 0x1800AA260
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x1800AA260

`0x1800AA260` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x1800AA260	inMemory=true	isFunctionEntry=false	entryName=-	containing=1800aa1b0 DocumentMarks::SetCutMarkOffset	codeUnit=false

- container na v240: 0x1800AA1B0 DocumentMarks::SetCutMarkOffset (outra marca) - o endereco cai no corpo dele

## Equivalente v240

- endereco: `0x1800A8860`
- simbolo: `DocumentMarks::SetBearerBarExtend`
- mangled: `?SetBearerBarExtend@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusBearerBar@DocumentMarks@@@Z@std@@AEBV?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@@Z`
- prova de equivalencia: Setter transacional de `Extend` (R12): monta `Action` com getter/setter de membro, pega a `ActionList` e chama `DoAction`.
- nota: O container v240 e um setter de CUT MARK: mesma familia de codigo, marca diferente. Nao usar como equivalente.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_1800a8860.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
