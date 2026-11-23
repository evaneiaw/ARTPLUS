---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = FUN_18016FA10 em 0x18016FA10"
endereco: 0x180179DA0
versao: 24.03.10017
confianca: media
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x180179DA0

`0x180179DA0` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x180179DA0	inMemory=true	isFunctionEntry=false	entryName=-	containing=1801798e0 FUN_1801798e0	codeUnit=true

- container na v240: 0x1801798E0 FUN_1801798E0 (outro assunto: le `Width`/`Height` de um dicionario de TextAreaMark conforme as strings referenciadas)

## Equivalente v240

- endereco: `0x18016FA10`
- simbolo: `FUN_18016FA10 (parser `Position` do PDF+)`
- mangled: `(sem simbolo; funcao anonima)`
- prova de equivalencia: Parser de `Position` (R10/R11): SourceAnchor/ReferenceAnchor, Reference/ObjectID/ReferenceID, array `Offset` com 2 numeros e a excecao literal `Vertical offset in bearer bar not supported.`
- nota: Na v240 o parser foi dividido: `Position`/`Offset` ficam em 0x18016FA10 e `Extends`/`Reference` de tamanho em 0x180166B70 (ver o arquivo do equivalente).

## Confianca

`media` - equivalencia parcial: na v240 o parser foi dividido em duas funcoes, e o equivalente cobre Position/Offset mas nao Extends/Reference.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18016fa10.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
