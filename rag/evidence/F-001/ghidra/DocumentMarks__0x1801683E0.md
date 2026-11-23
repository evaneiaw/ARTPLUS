---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x1801683E0
endereco: 0x1801683E0
nome: "FUN_1801683E0 (leitor de marcas PDF+)"
confianca: media
xrefs: ["0x180488448", "0x18031A098"]
strings: ["Reference", "ReferenceID", "Position", "RepeatForObjects", "Custom Mark"]
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Leitor de marcas PDF+ (FUN_1801683E0) — v24.03.10017

## Identificacao

- Endereco: `0x1801683E0` (corpo `0x1801683E0`–`0x18016D5BF`, 20888 bytes)
- Nome atual: `FUN_1801683E0` (sem simbolo)
- Referencia de dados `0x180488448` (tabela do modulo) e `0x18031A098`.

## O que a funcao faz (ramo Cut Mark)

1. Le o dicionario da marca e o `ObjectType`.
2. No ramo do Cut Mark (comparacao de 4 bytes em `0x18016A4xx`):
   - `GADict::GetStream("Source")` e materializa o `FormPaint`;
   - aloca `0x850` bytes e chama
     `DocumentMarks::PDFPlusCutMark::PDFPlusCutMark` em `0x18016A40F`;
   - chama o parser de Cut Mark **`FUN_180172100`** em `0x18016A437`;
   - chama `FUN_180171DE0` para o pos-processamento do objeto.
3. Para outros tipos, despacha para parsers especificos
   (`FUN_180174210`, `FUN_1801756A0`, `FUN_1801753D0`, `FUN_180175170`,
   `FUN_180176810`, ...).

## Por que sustenta F-001 (Cut Mark)

- Sustenta R11 na v240 no que diz respeito a construcao do objeto: o leitor PDF+
  instancia `PDFPlusCutMark` e delega a leitura de parametros ao parser
  `FUN_180172100`.
- Mostra que o `FormPaint` (conteudo-simbolo) e lido de `Source` antes do parser,
  coerente com a geometria por copia de conteudo observada em
  `regenerateMarkImp` na v240.
- **Nao** confirma `Orientation`/`Repetition`/`LineTypes`: essas chaves nao
  aparecem neste parser de Cut Mark (ver `DocumentMarks__0x180172100.md`).

## Confianca

Media: o ramo do Cut Mark foi localizado e seguido (construtor + parser +
pos-processamento), mas a funcao tem 20 KB e os demais ramos nao foram
auditados por completo.
