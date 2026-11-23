---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = FUN_18010E0F0 em 0x18010E0F0"
endereco: 0x180111410
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x180111410

`0x180111410` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x180111410	inMemory=true	isFunctionEntry=false	entryName=-	containing=180111320 FUN_180111320	codeUnit=true

- container na v240: 0x180111320 FUN_180111320 - na v240 esta funcao e `PostProcessVDPObjects(ArtDoc::Content&)` (coleta de IDs de VDPObject), sem relacao com Bearer Bar

## Equivalente v240

- endereco: `0x18010E0F0`
- simbolo: `FUN_18010E0F0 (createDynamicObject legado)`
- mangled: `(sem simbolo; funcao anonima)`
- prova de equivalencia: Criacao legada (secao Entrada): `memcmp` de 24 bytes contra `AIDynamicMarks-BearerBar`, `new (0x788)`, `BearerBar(ptr, true)` e `setPdfPropertiesDict`.
- nota: Prova no binario v240: o literal `AIDynamicMarks-BearerBar` (0x1802FA140) e referenciado em `0x18010E474` (PARAM) dentro de `FUN_18010E0F0`, e a chamada do ctor esta em `0x18010E4CE`.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18010e0f0.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
