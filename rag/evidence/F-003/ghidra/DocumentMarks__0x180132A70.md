---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::PDFPlusBearerBar::regenerateMarkImp em 0x18012F6E0"
endereco: 0x180132A70
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x180132A70

`0x180132A70` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x180132A70	inMemory=true	isFunctionEntry=false	entryName=-	containing=180132a40 DocumentMarks::PDFPlusClipMark::getRefObjects	codeUnit=false

- container na v240: 0x180132A40 DocumentMarks::PDFPlusClipMark::getRefObjects (outra classe) - 0x30 bytes dentro do corpo dela

## Equivalente v240

- endereco: `0x18012F6E0`
- simbolo: `DocumentMarks::PDFPlusBearerBar::regenerateMarkImp`
- mangled: `?regenerateMarkImp@PDFPlusBearerBar@DocumentMarks@@MEAAXXZ`
- prova de equivalencia: Pipeline PDF+ (R7): UpdateDirection -> ValidateAnchors -> UpdateSizeReference, limpeza do conteudo gerado, Group(0x1FF)/Expander, transformacao com guarda de 0,01 mm, insercao no topo e ApplyPDFPlusColor.
- nota: O container v240 (PDFPlusClipMark::getRefObjects) NAO e o equivalente; ele so reflete a vizinhanca de enderecos no layout do binario.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012f6e0.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
