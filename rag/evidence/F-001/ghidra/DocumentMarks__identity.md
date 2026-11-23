---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180000000
endereco: 0x180000000
nome: "identidade do binario DocumentMarks.dll v24.03.10017"
confianca: alta
xrefs: []
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Identidade do binario — DocumentMarks.dll v24.03.10017

## Arquivo de referencia

- Caminho:
  `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- Tamanho: 4.841.904 bytes
- SHA-256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- MD5 (Ghidra): `4d2f2060555b206bd9f374ca69f8a234`
- Imagem: `x86:LE:64:default`, base `0x180000000`, compilador `windows`.
- Funcoes reconhecidas pelo Ghidra 12.2: 12.006.

## Programa Ghidra usado

- Projeto: `DocMarks_v240` (`tools/ghidra_projects/DocMarks_v240`),
  programa `/DocumentMarks.dll`.
- Importado da v240 em 21/11/2026 com analise padrao
  (`analyzeHeadless ... -import ...`), log em
  `tools/ghidra_analysis/f001_docmarks_v240_import.log`.

## Contraste com a v25 (historico)

O projeto `ArtProPlus` contem um programa `DocumentMarks.dll` cujo
`executablePath` e `/C:/Esko/bg_prog_artpro+_v250/...` e cujo SHA-256 e
`FFA8809D294A7AA08BD2794E0B0C1E64608D898B5F7BA698A4E58A8E575BEE10`
(12.192 funcoes). **Nao foi usado como evidencia de F-001**, exceto para
diagnosticar o deslocamento de enderecos; os enderecos da spec pertencem a ele.

## Ausencia de literal `Trim Marks`

A varredura ASCII/UTF-16 do binario v240 nao encontra `Trim Marks`; os literais
de UI/persistencia usam `Cut Mark`/`CutMark`
(`AIDynamicMarks-CutMark` em `0x1802FDC58`,
`DynamicObject_PDFPlusCutMark` em `0x180305DC8`). Isso sustenta a nota de
nomenclatura de F-001 §1.

## Confianca

Alta: identidade lida de `currentProgram` (caminho e hash) e conferida com
`Get-FileHash` sobre o arquivo real.
