---
modulo: PDFObjectActions.dll
funcao: GOVSelectHitElement::SetHitType
endereco: 0x1802770d0
versao: 24.03.10017
confianca: alta
xrefs: [0x18027e220, 0x1802a10b0, 0x18027e6c0, 0x18027ecc0, 0x18027e0a0]
strings: []
---

# GOVSelectHitElement::SetHitType @ 0x1802770d0

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x1802770d0` |
| Nome no binario | `GOVSelectHitElement::SetHitType` |
| Assinatura (Ghidra) | `void __thiscall SetHitType(HitType param_1)` |
| Parametros | 2 |
| Bytes de corpo | 99 |
| Chamadores | 5 |
| Chamadas diretas | 0 |

## Papel provavel

Fato: `SetHitType(HitType)` grava flags em `+0x209`, `+0x20a`, `+0x20b`.
Mapeamento observado do enum (0..4):

| HitType | +0x209 | +0x20a | +0x20b |
|---|---|---|---|
| 0 | 1 | 0 | inalterado |
| 1 | 1 | 1 | inalterado |
| 2 | 0 | 0 | inalterado |
| 3 | 0 | 1 | inalterado |
| 4 | inalterado | inalterado | 1 |

Inferencia: os dois bytes de flag correspondem a 'casar dentro' e 'casar borda',
mas os nomes do enum nao estao disponiveis no binario (apenas `HitType`).

## Xrefs de entrada (quem chama)

- `0x18027e220 GOVSelectInRegion::GOVSelectInRegion`
- `0x1802a10b0 GOVSelectSingleImagePageImage::Select`
- `0x18027e6c0 GOVSelectInRegion::InitSelectHit`
- `0x18027ecc0 GOVSelectInRegion::LoadSelf`
- `0x18027e0a0 GOVSelectInRegion::GOVSelectInRegion`

## Chamadas diretas (quem esta funcao chama)

- nenhuma

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- nenhum ponteiro absoluto encontrado (funcao pode ser chamada so por `call rel32`)

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* public: void __cdecl GOVSelectHitElement::SetHitType(enum GOVSelectHitElement::HitType) __ptr64
    */

void __thiscall GOVSelectHitElement::SetHitType(GOVSelectHitElement *this,HitType param_1)

{
                    /* 0x2770d0  13670  ?SetHitType@GOVSelectHitElement@@QEAAXW4HitType@1@@Z */
  if (param_1 == 0) {
    this[0x209] = (GOVSelectHitElement)0x1;
    *(undefined2 *)(this + 0x20a) = 0;
  }
  else {
    if (param_1 == 1) {
      *(undefined2 *)(this + 0x20a) = 1;
      this[0x209] = (GOVSelectHitElement)0x1;
      return;
    }
    if (param_1 == 2) {
      this[0x209] = (GOVSelectHitElement)0x0;
      *(undefined2 *)(this + 0x20a) = 0;
      return;
    }
    if (param_1 == 3) {
      *(undefined2 *)(this + 0x20a) = 1;
      this[0x209] = (GOVSelectHitElement)0x0;
      return;
    }
    if (param_1 == 4) {
      this[0x20b] = (GOVSelectHitElement)0x1;
      return;
    }
  }
  return;
}


```

Raw completo: `_raw/PDFObjectActions__1802770d0.txt`.

