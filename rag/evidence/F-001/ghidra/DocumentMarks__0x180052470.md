---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180052470
endereco: 0x180052470
nome: "DocumentMarks::CutMark::PlaceCutMarkSymbol"
confianca: media
xrefs: ["0x180052D22", "0x1803AB628"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# CutMark::PlaceCutMarkSymbol — v24.03.10017

## Identificacao

- Endereco: `0x180052470` (corpo `0x180052470`–`0x1800526EE`, 638 bytes)
- Assinatura: `void __thiscall PlaceCutMarkSymbol(CutMark *this, ArtDoc::ContentObject &symbol, const dm::CPoint &from, const dm::CPoint &to)`
- Chamado por `CutMark::regenerateMarkImp` em `0x180052D22`.

## O que a funcao faz

- Calcula a transformacao do simbolo clonado com `atan2`/`cos`/`sin`
  (biblioteca CRT) e aplica `DocumentEdit::Transform`.
- Usa `GetBoundingBoxForPositioning` (`0x18012A130`) para obter a caixa do
  objeto posicionado.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R12.3: o posicionamento e feito por par de `CPoint` (origem/destino)
  e transformacao geometrica, coerente com "posiciona copias do simbolo" do
  caminho legado.
- Explica por que o caminho legado difere do PDF+ (que gera grupos/geometria).

## Confianca

Media: assinatura e chamadas confirmadas; a formula exata da transformacao nao
foi detalhada nesta passagem.
