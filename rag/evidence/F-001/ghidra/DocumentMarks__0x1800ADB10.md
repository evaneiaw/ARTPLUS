---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x1800ADB10
endereco: 0x1800ADB10
nome: "ID de 0x1800ADB10: endereco da v25.03.116; equivalente v240 = 0x1800AA1B0"
confianca: alta
xrefs: ["0x1800AA1B0"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Registro de ID — `0x1800ADB10` (citado pela spec F-001)

## Resultado neste binario (v24.03.10017)

- O endereco `0x1800ADB10` **nao e entrada de funcao** em
  `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
  (sha256 `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`).
- Ele pertence a imagem da **v25.03.116** (`bg_prog_artpro+_v250`), de onde a
  spec F-001 foi originalmente escrita. O proprio frontmatter de F-001 registra
  "evidencia capturada na v25; requer revalidacao contra 24.03.10017".
- A funcao equivalente na v240 e **DocumentMarks::SetCutMarkOffset (sobrecarga PDFPlusCutMark&)**, em **0x1800AA1B0**.
  A analise real da v240 esta em `DocumentMarks__0x1800AA1B0.md`.

## Por que este arquivo existe

O ID `GHIDRA-DocumentMarks-0x1800ADB10` e citado em `docs/features/F-001.md` (R5/R8 (edicao de offset como acao undoable)).
Este arquivo preserva a rastreabilidade do ID sem inventar uma funcao no
endereco errado: ele e um **registro de deslocamento de endereco entre versoes**,
nao uma analise da v25 como se fosse v24.

## Impacto na spec

- A spec continua apontando para enderecos da v25. O orquestrador/documentacao
  precisa reapontar os IDs de F-001 para os enderecos v240 listados no
  `manifest.json` (`estatico`) antes de considerar a spec revalidada.
- Nenhuma conclusao de comportamento deste arquivo deve ser lida como
  comportamento v240: para isso, use o arquivo `DocumentMarks__0x1800AA1B0.md`.

## Confianca

Alta para o deslocamento (evidencia direta: os enderecos citados estao no meio de
funcoes diferentes na v240; as funcoes equivalentes foram localizadas por
simbolo e assinatura no programa v240).
