---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180052700
endereco: 0x180052700
nome: "DocumentMarks::CutMark::parsePdfPropertiesDict"
confianca: alta
xrefs: ["0x1802FDAF8", "0x1803AC100"]
strings: ["CutMark", "DM-CutMarkParams", "DM-CutMarkParams-Offset", "DM-CutMarkParams-Version"]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# CutMark::parsePdfPropertiesDict — v24.03.10017

## Identificacao

- Endereco: `0x180052700` (corpo `0x180052700`–`0x180052940`, 576 bytes)
- Assinatura: `bool __thiscall parsePdfPropertiesDict(CutMark *this, const std::map<std::string, ArtDoc::ContentObject*> &props)`
- Referencia de dados `0x1802FDAF8` (slot de vtable).

## O que a funcao faz (decompilado)

1. Chama `DynamicMark::parsePdfPropertiesDict` (parser da base).
2. Le o sub-dicionario **`DM-CutMarkParams`** do dicionario da marca.
3. Le as chaves `DM-CutMarkParams-Offset` e `DM-CutMarkParams-Version`
   (strings em `0x1803302A0` e `0x1803302E0`).
4. `DM-CutMarkParams-SymbolDefinition` existe no binario (`0x1803302B8`), mas
   **nao aparece referenciada nesta funcao** — o uso dessa chave esta em outro
   ponto do leitor legado (nao localizado nesta passagem).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R12.2 para as chaves `DM-CutMarkParams`, `-Offset` e `-Version`.
- Delimita a lacuna: `-SymbolDefinition` nao esta confirmado neste parser.

## Confianca

Alta para as chaves efetivamente referenciadas; media para o conjunto completo
do dicionario legado.
