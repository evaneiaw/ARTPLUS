---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::SetBearerBarSizeReference em 0x1800A8B40"
endereco: 0x1800AA520
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x1800AA520

`0x1800AA520` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x1800AA520	inMemory=true	isFunctionEntry=false	entryName=-	containing=1800aa510 FUN_1800aa510	codeUnit=false

- container na v240: 0x1800AA510 FUN_1800AA510 (funcao vizinha, outro assunto; o alvo esta 0x10 bytes depois do inicio dela)

## Equivalente v240

- endereco: `0x1800A8B40`
- simbolo: `DocumentMarks::SetBearerBarSizeReference`
- mangled: `?SetBearerBarSizeReference@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusBearerBar@DocumentMarks@@@Z@std@@W4SizeReference@PDFPlusBearerBar@1@@Z`
- prova de equivalencia: Setter transacional de `SizeReference` (R12), com getter `GetSizeReference` (0x18012E780) e setter `SetSizeReference` (0x18012E7C0).
- nota: A spec cita `SetSizeReference` em 0x180131C30 (v25); na v240 e 0x18012E7C0.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_1800a8b40.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
