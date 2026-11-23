---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180051F90
endereco: 0x180051F90
nome: "DocumentMarks::CutMark::CutMark(bool)"
confianca: alta
xrefs: ["0x18010F130", "0x1803AA328"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# CutMark::CutMark(bool) — v24.03.10017

## Identificacao

- Endereco: `0x180051F90` (corpo `0x180051F90`–`0x180051FCD`, 61 bytes)
- Assinatura: `CutMark * __thiscall CutMark(CutMark *this, bool own)` 
- Chamado pelo dispatch legado `FUN_18010E0F0` em `0x18010F130`.

## O que a funcao faz

1. `DynamicMark::DynamicMark(this, own, 0xFD)`.
2. `this+0x750 = 0` (offset/inicializacao da marca legada).
3. Instala as vftables `ListItem` (`this+0x000`) e `Visitable` (`this+0x020`).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R12.1: o objeto criado para `AIDynamicMarks-CutMark` e
  `DocumentMarks::CutMark` e nasce com offset zero.
- E a classe legada distinta de `PDFPlusCutMark`; a v240 mantem os dois caminhos.

## Confianca

Alta.
