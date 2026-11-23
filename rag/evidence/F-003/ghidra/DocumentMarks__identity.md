---
modulo: DocumentMarks.dll
funcao: identidade do programa (DocumentMarks.dll v24.03.10017)
endereco: 0x180000000 (imageBase)
versao: 24.03.10017
confianca: alta
---
# Identidade do programa v240 - DocumentMarks.dll

Registro da identidade do programa importado no Ghidra para a extracao dos equivalentes de F-003.
Gerado a partir de `raw_v240/_identity.txt`; nao ha inferencia neste arquivo.

## Programa

- modulo: `DocumentMarks.dll`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- md5: `4D2F2060555B206BD9F374CA69F8A234`
- imageBase: `0x180000000`
- linguagem: `x86:LE:64:default`
- compilador (marcacao Ghidra): `windows`
- funcoes analisadas: `12006`
- simbolos: RTTI/vtables e nomes mangled recuperados; funcoes sem simbolo aparecem como `FUN_<addr>`

## Sonda desta passada

A sonda de `raw_v240/_probe.txt` resolveu 19 IDs historicos v25 em enderecos v240 e permitiu montar a
tabela de equivalentes: 18 confirmados e 1 sem equivalente (`0x180170C20`). Cerca de 35 enderecos
candidatos foram despejados em `raw_v240/addr_<addr>.txt` (assinatura, xrefs, strings e pseudocodigo).

## Limitacoes declaradas

- O binario nao esta empacotado nem ofuscado; a analise padrao do Ghidra 12.2 resolveu chamadas diretas.
- Varias funcoes virtuais ficam sem chamador direto (xref so de vtable/DATA), o que limita o call graph.
- O literal devolvido por `PDFPlusBearerBar::getMarkType` nao foi capturado como string; ver
  `DocumentMarks__0x18012EB70.md`.

## Fonte

- identidade bruta: `rag/evidence/F-003/ghidra/raw_v240/_identity.txt`
- sonda: `rag/evidence/F-003/ghidra/raw_v240/_probe.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
