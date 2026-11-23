---
modulo: PDFObjectActions.dll
funcao: GOVSelectOverlapping::Select
endereco: 0x18028c310
versao: 24.03.10017
confianca: alta
xrefs: []
strings: []
---

# GOVSelectOverlapping::Select @ 0x18028c310

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x18028c310` |
| Nome no binario | `GOVSelectOverlapping::Select` |
| Assinatura (Ghidra) | `bool __thiscall Select(GOElement * param_1)` |
| Parametros | 2 |
| Bytes de corpo | 244 |
| Chamadores | 0 |
| Chamadas diretas | 0 |

## Papel provavel

Fato: `bool GOVSelectOverlapping::Select(GOElement&)` implementa consulta de
pertinencia em tabela hash de endereco aberto: capacidade em `+0x228`,
bucket em `+0x220` (16 bytes por entrada: ponteiro + contador com bit 31 de
marca). O ponteiro e comparado por identidade (`pGVar3 == param_1`).

Inferencia: responde 'este elemento pertence ao conjunto de sobreposicao
calculado por `Select(GOPage&)`' - e o par de leitura do conjunto montado em
0x18028c410.

## Xrefs de entrada (quem chama)

- nenhuma chamada direta detectada (provavel entrada por vtable/export)

## Chamadas diretas (quem esta funcao chama)

- nenhuma

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- `.rdata:1804f1d40`

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* public: virtual bool __cdecl GOVSelectOverlapping::Select(class GOElement & __ptr64) __ptr64 */

bool __thiscall GOVSelectOverlapping::Select(GOVSelectOverlapping *this,GOElement *param_1)

{
  uint uVar1;
  longlong lVar2;
  GOElement *pGVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  uint uVar10;

                    /* 0x28c310  13457  ?Select@GOVSelectOverlapping@@UEAA_NAEAVGOElement@@@Z */
  uVar1 = *(uint *)(this + 0x228);
  lVar2 = *(longlong *)(this + 0x220);
  uVar7 = 0;
  uVar5 = (uint)(((ulonglong)param_1 & 0xffffffff) % (ulonglong)uVar1);
  uVar8 = (ulonglong)(int)uVar5;
  uVar6 = *(uint *)(lVar2 + 8 + uVar8 * 0x10);
  if ((int)uVar6 < 0) {
    pGVar3 = *(GOElement **)(lVar2 + uVar8 * 0x10);
    if (pGVar3 == param_1) goto LAB_18028c3dc;
    uVar7 = 0;
    if (uVar5 == (uint)(((ulonglong)pGVar3 & 0xffffffff) % (ulonglong)uVar1)) {
      uVar7 = 1;
    }
  }
  uVar6 = uVar6 & 0x7fffffff;
  uVar9 = uVar8;
  uVar10 = uVar1;
  if (uVar7 < uVar6) {
    do {
      if ((int)uVar10 < 1) break;
      uVar4 = (int)uVar9 + 1;
      uVar9 = uVar8 + 1;
      uVar8 = 0;
      if (uVar4 != uVar1) {
        uVar8 = uVar9;
      }
      uVar9 = 0;
      if (uVar4 != uVar1) {
        uVar9 = (ulonglong)uVar4;
      }
      if ((*(int *)(lVar2 + 8 + uVar8 * 0x10) < 0) &&
         (uVar5 == *(uint *)(lVar2 + uVar8 * 0x10) % uVar1)) {
        if (*(GOElement **)(lVar2 + uVar8 * 0x10) == param_1) goto LAB_18028c3dc;
        uVar7 = uVar7 + 1;
      }
      uVar10 = uVar10 - 1;
    } while ((int)uVar7 < (int)uVar6);
  }
  uVar5 = 0xffffffff;
LAB_18028c3dc:
  return (bool)((byte)(uVar5 >> 0x1f) ^ 1);
}


```

Raw completo: `_raw/PDFObjectActions__18028c310.txt`.

