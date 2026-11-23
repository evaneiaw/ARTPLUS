---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = NAO CONFIRMADO (nenhuma funcao equivalente provada)"
endereco: 0x180170C20
versao: 24.03.10017
confianca: media
---
# Evidencia Ghidra - ID historico GHIDRA-DocumentMarks-0x180170C20

`0x180170C20` e um ID **historico**: o endereco pertence ao layout antigo (fora do
fluxo ativo) e NAO identifica uma funcao na versao de referencia
24.03.10017. Nenhum equivalente foi confirmado na v240 (ver Conflito).

## Prova de deslocamento (sonda raw_v240/_probe.txt)

     0x180170C20	inMemory=true	isFunctionEntry=false	entryName=-	containing=180170540 FUN_180170540	codeUnit=false

- container na v240: 0x180170540 FUN_180170540 (2933 bytes) - 0x6E0 bytes dentro do corpo

## Equivalente v240

- endereco: nenhum confirmado
- simbolo: nenhum confirmado
- mangled: nao aplicavel
- prova de equivalencia: nenhuma confirmada; o ID permanece historico

## Confianca

`media` - nenhum equivalente confirmado na v240: o endereco cai em FUN_180170540 e a funcao de parser de tamanho do PDF+ nao foi provada; registro mantido como ID historico sem equivalente.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sonda dos 19 IDs historicos: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
