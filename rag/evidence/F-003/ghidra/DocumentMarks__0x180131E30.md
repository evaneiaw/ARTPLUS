---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::PDFPlusBearerBar::ValidateAnchors em 0x18012E9C0"
endereco: 0x180131E30
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x180131E30

`0x180131E30` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x180131E30	inMemory=true	isFunctionEntry=false	entryName=-	containing=180131e00 DocumentMarks::PDFPlusClipMark::PostProcessFormulasImp	codeUnit=false

- container na v240: 0x180131E00 DocumentMarks::PDFPlusClipMark::PostProcessFormulasImp (outra classe)

## Equivalente v240

- endereco: `0x18012E9C0`
- simbolo: `DocumentMarks::PDFPlusBearerBar::ValidateAnchors`
- mangled: `?ValidateAnchors@PDFPlusBearerBar@DocumentMarks@@IEAAXXZ`
- prova de equivalencia: Normalizacao do par de anchors antes da geracao (R5/R7 passo 1): `ToVertical` quando Direction == 0, `ToHorizontal` quando Direction == 1, aplicando `MarkPosition::setAnchors` so se algo mudou.
- nota: A spec registra esta funcao como lacuna ("regra de normalizacao nao lida"); o descompilado completo esta no arquivo do equivalente.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012e9c0.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
