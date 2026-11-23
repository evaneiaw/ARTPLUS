---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x1800FAE70
endereco: 0x1800FAE70
nome: "ArtDoc::Page::GetPageBox"
confianca: alta
xrefs: ["0x180134BEF", "0x1801365B3"]
strings: []
fonte: "Ghidra 12.2 headless; projeto ArtProPlus_Document; programa Document.dll v24.03.10017 (sha256 DA91E28574C877D392D3E6BEF9CCBB7C4DCF3117EBD03655DE89834FC8FA9E21)"
---

# ArtDoc::Page::GetPageBox — v24.03.10017 (Document.dll)

## Identificacao

- Modulo: `Document.dll` da instalacao v24.03.10017
  (`C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\Document.dll`,
  sha256 `DA91E28574C877D392D3E6BEF9CCBB7C4DCF3117EBD03655DE89834FC8FA9E21`).
- Endereco: `0x1800FAE70` (corpo `0x1800FAE70`–`0x1800FAECA`, 91 bytes)
- Nome qualificado: `ArtDoc::Page::GetPageBox`
- Assinatura: `const YAGL::RectangleBase<YAGL::MilliPointCoordinateSystem> & __thiscall GetPageBox(ArtDoc::Page *this, ArtDoc::PageBox box) const`
- Chamado por `DocumentMarks::PDFPlusCutMark::GetReferenceBox` (`0x180134BEF`)
  e por `regenerateMarkImp` via `GetReferenceBox` (`0x1801365B3`).

## O que a funcao faz (decompilado)

1. `ArtDoc::Page::Cache(this)` — garante o cache de caixas da pagina.
2. Indexa o array de caixas pelo inteiro **cru** `box` com **stride `0x58`**:
   `this[box * 0x58 + 0x78]`.
3. Enquanto a caixa estiver ausente (`nullptr`), aplica a tabela de fallback
   **`DAT_1802EF6D8`**: `box = *(PageBox*)(&DAT_1802EF6D8 + box * 4)` e tenta de
   novo (permite substituir uma caixa ausente por outra).
4. Devolve o retangulo em `this + box * 0x58 + 0x28`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R3: `GetReferenceBox` entrega o inteiro `PageBox` (`+0x7C0` na v240)
  diretamente a esta funcao; o indice e cru e o stride e `0x58`, exatamente como
  descrito em R3.
- Sustenta E7: a tabela `DAT_1802EF6D8` existe e e consultada quando a caixa nao
  esta presente. O **conteudo** da tabela (qual caixa substitui qual) nao foi
  decodificado nesta passagem — a lacuna de F-001 §8 item 11 permanece.
- Sustenta o default `PageBox = 3` do construtor v240
  (`DocumentMarks__0x1801344E0.md`): o valor e passado sem traducao de nome.

## Confianca

Alta: funcao curta, integralmente legivel; stride, offset da tabela de fallback
e fluxo confirmados no decompilado e nos xrefs de dados.
