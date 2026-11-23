---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::PDFPlusBearerBar::UpdateDirection em 0x18012E7D0"
endereco: 0x180131C40
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x180131C40

`0x180131C40` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x180131C40	inMemory=true	isFunctionEntry=false	entryName=-	containing=180131ae0 FUN_180131ae0	codeUnit=true

- container na v240: 0x180131AE0 FUN_180131AE0 (funcao sem simbolo, outro assunto)

## Equivalente v240

- endereco: `0x18012E7D0`
- simbolo: `DocumentMarks::PDFPlusBearerBar::UpdateDirection`
- mangled: `?UpdateDirection@PDFPlusBearerBar@DocumentMarks@@AEAAXXZ`
- prova de equivalencia: Deriva Direction dos dois anchors (R5): 0 quando `YAGL::ToVertical` nao altera nenhum dos dois; 1 caso contrario.
- nota: Na v240 os anchors ficam em +0x418/+0x41C e Direction em +0x770 (a spec cita +0x378/+0x37C e +0x6A8).

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012e7d0.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
