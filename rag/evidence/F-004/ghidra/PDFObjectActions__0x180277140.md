---
modulo: PDFObjectActions.dll
funcao: GOVSelectHitElement::SetRect
endereco: 0x180277140
versao: 24.03.10017
confianca: alta
xrefs: [0x180192a70, 0x1801a2f90, 0x1802755d0, 0x180287370, 0x18027f940]
strings: []
---

# GOVSelectHitElement::SetRect @ 0x180277140

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x180277140` |
| Nome no binario | `GOVSelectHitElement::SetRect` |
| Assinatura (Ghidra) | `void __thiscall SetRect(GRectBase<double> * param_1)` |
| Parametros | 2 |
| Bytes de corpo | 182 |
| Chamadores | 5 |
| Chamadas diretas | 2 |

## Papel provavel

Fato: `SetRect(const GRectBase<double>&)` copia os 4 doubles de origem para
`+0x1e0`, `+0x1e8`, `+0x1f0`, `+0x1f8` (o retangulo de hit-test).

Fato: se `GetHeight()` do retangulo for exatamente 0.0, alarga as duas bordas Y
em `DAT_1804141a0 = 0.5` (medido no arquivo: `000000000000e03f` = 0.5);
se `GetWidth()` for 0.0, faz o mesmo nas bordas X com a mesma constante.

Inferencia: evita retangulo degenerado quando o usuario clica num ponto
(rubber-band de area zero). Unidade da constante nao esta nomeada no binario;
pela convencao do modulo (GRectBase<double> em espaco de usuario do PDF)
trata-se de 0.5 unidade de usuario (tipicamente pt) - inferencia, nao fato.

## Xrefs de entrada (quem chama)

- `0x180192a70 GOVAddPageNumber::Add`
- `0x1801a2f90 GOVCheckAnnotInArea::Visit`
- `0x1802755d0 GOVSelectHitElement::GOVSelectHitElement`
- `0x180287370 GOVSelectNotInSafeTypeZone::Select`
- `0x18027f940 GOVSelectInRegion::Select`

## Chamadas diretas (quem esta funcao chama)

- `EXTERNAL:00000ed5 BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::GetWidth`
- `EXTERNAL:00000ed6 BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::GetHeight`

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- nenhum ponteiro absoluto encontrado (funcao pode ser chamada so por `call rel32`)

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* public: void __cdecl GOVSelectHitElement::SetRect(class GRectBase<double> const & __ptr64)
   __ptr64 */

void __thiscall GOVSelectHitElement::SetRect(GOVSelectHitElement *this,GRectBase<double> *param_1)

{
  GRectBase<double> *this_00;
  double dVar1;
  undefined8 uVar2;
  double dVar3;

                    /* 0x277140  13755  ?SetRect@GOVSelectHitElement@@QEAAXAEBV?$GRectBase@N@@@Z */
  uVar2 = *(undefined8 *)(param_1 + 8);
  this_00 = (GRectBase<double> *)(this + 0x1e0);
  *(undefined8 *)this_00 = *(undefined8 *)param_1;
  *(undefined8 *)(this + 0x1e8) = uVar2;
  uVar2 = *(undefined8 *)(param_1 + 0x18);
  *(undefined8 *)(this + 0x1f0) = *(undefined8 *)(param_1 + 0x10);
  *(undefined8 *)(this + 0x1f8) = uVar2;
  dVar1 = GRectBase<double>::GetHeight(this_00);
  dVar3 = _DAT_1804141a0;
  if (dVar1 == 0.0) {
    dVar1 = *(double *)(this + 0x1e8) - _DAT_1804141a0;
    *(double *)(this + 0x1f8) = *(double *)(this + 0x1f8) + _DAT_1804141a0;
    *(double *)(this + 0x1e8) = dVar1;
  }
  dVar1 = GRectBase<double>::GetWidth(this_00);
  if (dVar1 == 0.0) {
    *(double *)(this + 0x1f0) = *(double *)(this + 0x1f0) + dVar3;
    *(double *)this_00 = *(double *)this_00 - dVar3;
  }
  return;
}


```

Raw completo: `_raw/PDFObjectActions__180277140.txt`.

