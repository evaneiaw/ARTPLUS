---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x1801344E0
endereco: 0x1801344E0
nome: "DocumentMarks::PDFPlusCutMark::PDFPlusCutMark"
confianca: alta
xrefs: ["0x18016A40F", "0x1803AA3D0", "0x18048678C"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# PDFPlusCutMark::PDFPlusCutMark (construtor de criacao) — v24.03.10017

## Identificacao

- Endereco: `0x1801344E0` (corpo `0x1801344E0`–`0x1801345DE`, 255 bytes)
- Nome qualificado: `DocumentMarks::PDFPlusCutMark::PDFPlusCutMark`
- Assinatura: `PDFPlusCutMark * __thiscall (PDFPlusCutMark *this, std::shared_ptr<ArtPaint::FormPaint const> formPaint)`
- Convencao: `__thiscall`; nao e thunk; nao e externo.

## Xrefs

- Chamado por `FUN_1801683E0` em `0x18016A40F` (leitor de marcas PDF+), logo apos
  alocar `0x850` bytes.
- Referencias de dados: `0x1803AA3D0`, `0x18048678C` (tabelas de ponteiros do modulo).
- Entrada de vtable: nao e chamado por vtable; e construtor chamado diretamente.

## O que a funcao faz (decompilado)

1. `DynamicMark::DynamicMark(this, false, 0x1CE)` — inicializa a base dinamica.
2. Instala as duas vftables da classe: `this+0x000` (ListItem) e `this+0x020` (Visitable).
3. Zera/inicializa os campos do objeto:
   - `this+0x758 = 0` — coordenada do offset (quantidade);
   - `this+0x770 = 0` — seletor do variant de offset (0 = quantidade);
   - `this+0x7B8 = 0` — referencia de objeto auxiliar;
   - `this+0x7C0 = 3` — `PageBox` de referencia (inteiro cru);
   - `this+0x838 = 0` — seletor de referencia (0 = PageBox);
   - `this+0x840 = 0` e `this+0x848 = 0` — par de ponteiros (`shared_ptr` de estado interno).
4. `DynamicMark::SetSourceContent(this, formPaint)` — guarda o `FormPaint` de origem.
5. `DynamicObject::setColorType(this, 1, 0)` — tipo de cor inicial.
6. `MarkPosition::setReferenceObject(this+0x390, 0)` — referencia inicial nula.

## Por que sustenta F-001 (Cut Mark)

- Prova direta de R2 na v240 para os defaults que existem nesta versao:
  `PageBox = 3` (`+0x7C0`), seletor de referencia `0` (`+0x838`), offset
  quantidade `0` (`+0x758`/`+0x770`) e `setColorType(1,0)`.
- `+0x7C0 = 3` e o valor que `GetReferenceBox` (`0x180134B00`) entrega a
  `ArtDoc::Page::GetPageBox`; a UI exibir `Trim Box` como default e consistente
  com o indice 3, mas a ordem do enum nao tem nome no binario (inferencia mantida
  em F-001 §4, confianca media).
- **Diferenca v240 x v250:** a v25 inicializa tambem `Orientation=1`,
  `Repetition=2` e um vetor `LineTypes=[0]` em `+0x790/+0x794/+0x798`. A v240
  **nao escreve** esses campos neste construtor e o layout de campos mudou
  (`+0x708/+0x780/+0x788` na v25 vs `+0x7C0/+0x838` na v240). Portanto a tabela
  de R2 com `Orientation`/`Repetition`/`LineTypes` **nao vale para a v240**;
  ver `manifest.json` -> `bloqueios`.

## Confianca

Alta: fluxo e valores lidos diretamente do decompilado e dos xrefs; a unica
inferencia e a correspondencia `3 = TrimBox` (media, declarada acima).
