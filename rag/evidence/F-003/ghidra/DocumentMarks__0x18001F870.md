---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::BearerBar::parsePdfPropertiesDict em 0x18001D8E0"
endereco: 0x18001F870
versao: 24.03.10017
confianca: alta
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x18001F870

`0x18001F870` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. O equivalente efetivo na v240 esta registrado abaixo.

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x18001F870	inMemory=true	isFunctionEntry=false	entryName=-	containing=-	codeUnit=true

- container na v240: (nenhuma) - o endereco nao esta dentro de nenhuma funcao reconhecida; so coincide com o inicio de uma instrucao

## Equivalente v240

- endereco: `0x18001D8E0`
- simbolo: `DocumentMarks::BearerBar::parsePdfPropertiesDict`
- mangled: `?parsePdfPropertiesDict@BearerBar@DocumentMarks@@UEAA_NAEBV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEAVContentObject@ArtDoc@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEAVContentObject@ArtDoc@@@std@@@2@@std@@@Z`
- prova de equivalencia: Parser legado de `DM-BearerBarParams` (R9): Version >= 3 falha nomeando `BearerBar`, converte mm->mp e trata `IsVertical` da versao 1.
- nota: Simbolo mangled e nome qualificado lidos em `getFunctionAt(0x18001D8E0)`. O parser v240 le as 7 chaves `DM-BearerBarParams*` do binario v240.

## Confianca

`alta` - deslocamento e equivalencia lidos no programa v240 (sonda de
endereco, simbolo e xrefs de chamada), nao inferidos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001d8e0.txt`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
