---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180135160
endereco: 0x180135160
nome: "DocumentMarks::PDFPlusCutMark::SetOffset"
confianca: alta
xrefs: ["0x180172375", "0x180172450", "0x1801724D5", "0x1800AA206"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::SetOffset — v24.03.10017

## Identificacao

- Endereco: `0x180135160` (corpo `0x180135160`–`0x18013522C`, 205 bytes)
- Assinatura: `void __thiscall SetOffset(PDFPlusCutMark *this, const std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem>, std::string> &v)`
- Chamado pelo parser em `0x180172375`, `0x180172450` e `0x1801724D5`.
- Usado como ponteiro de metodo pelo wrapper `SetCutMarkOffset` (dados em
  `0x1800AA206`/`0x1800AA20D`).

## O que a funcao faz (decompilado)

O seletor do variant esta em `v[0x20]`:

- `0xFF` -> limpa o offset: `FUN_18006C1A0(this+0x750)` e `this+0x770 = 0xFF`
  (offset nao definido);
- `0x00` -> quantidade: grava 16 bytes em `this+0x750`/`this+0x758`; se o
  seletor anterior era `0xFF`, limpa antes;
- `0x01` -> formula: copia a string para `this+0x750` (`FUN_180017070`);
- transicao de quantidade para formula: limpa o estado anterior com
  `FUN_18000F510` e grava o novo variant, marcando `this+0x770 = 1`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R5/R6 na v240: o offset e um variant de tres estados
  (`0xFF` vazio, `0` quantidade, `1` formula) nos campos `+0x770` (seletor) e
  `+0x750/+0x758` (valor). A v25 usa `+0x6B8/+0x698`, com a mesma semantica.
- O parser v240 grava a formula como string e a quantidade escalada, exatamente
  o contrato que o `fx` da UI precisa produzir.

## Confianca

Alta: fluxo e offsets lidos diretamente no decompilado.
