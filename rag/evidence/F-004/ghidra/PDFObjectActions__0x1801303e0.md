---
modulo: PDFObjectActions.dll
funcao: GOVChangeRotateSelection::Change
endereco: 0x1801303e0
versao: 24.03.10017
confianca: alta
xrefs: []
strings: []
---

# GOVChangeRotateSelection::Change @ 0x1801303e0

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x1801303e0` |
| Nome no binario | `GOVChangeRotateSelection::Change` |
| Assinatura (Ghidra) | `long __thiscall Change(GOPage * param_1)` |
| Parametros | 2 |
| Bytes de corpo | 714 |
| Chamadores | 0 |
| Chamadas diretas | 17 |

## Papel provavel

Fato: `long GOVChangeRotateSelection::Change(GOPage&)`, 714 bytes, vtable em
`.rdata` (ver ponteiro listado). O ponto de referencia vem de
`*(int*)(this+0x1e8)`: valores 1..5 => canto de caixa de pagina
(`GOPage::GetPageBox` + `GPositionSupport::GetCorner`), 6 =>
`GOVGetFixedBoundingBox(true,true)`, 7 => `GOVGetClippedBoundingBox(true,true)`.

Fato: o angulo e `campo(+0x1f0) * DAT_18044ef28`; `DAT_18044ef28` mede
0.017453292519943295 rad = pi/180, portanto o campo esta em graus.
`sin`/`cos` montam a matriz 2D e `GOVChangeMatrix` e criado com id de mudanca
`0x3ea`.

Inferencia: e o operador 'Rotate selection'; o id 0x3ea aparece tambem em
`GOVChangeFlipSelection::Change` e `GOVCloneSelection::ConfigChangeMatrix`
(mesma familia de mudanca de matriz registrada no undo log).

## Xrefs de entrada (quem chama)

- nenhuma chamada direta detectada (provavel entrada por vtable/export)

## Chamadas diretas (quem esta funcao chama)

- `EXTERNAL:0000088d PDFOBJECTLAYER.DLL::GOProcessingStrategyDefault::~GOProcessingStrategyDefault`
- `0x180301a30 GOVGetClippedBoundingBox::GOVGetClippedBoundingBox`
- `0x1803cf4c0 __security_check_cookie`
- `0x180304030 GOVGetFixedBoundingBox::GOVGetFixedBoundingBox`
- `0x1803d0228 API-MS-WIN-CRT-MATH-L1-1-0.DLL::cos`
- `0x180027a60 GOVGetClippedBoundingBox::~GOVGetClippedBoundingBox`
- `EXTERNAL:00000f80 BASICFRAMEWORKCORELAYER.DLL::GPointBase<double>::GPointBase<double>`
- `EXTERNAL:00000889 PDFOBJECTLAYER.DLL::GOPage::GetPageBox`
- `EXTERNAL:00000888 PDFOBJECTLAYER.DLL::GOPage::Accept`
- `0x1803d022e API-MS-WIN-CRT-MATH-L1-1-0.DLL::sin`
- `0x1803cefc4 FUN_1803cefc4`
- `0x180027120 FUN_180027120`
- `EXTERNAL:0000088f PDFOBJECTLAYER.DLL::GODefaultExHandler::~GODefaultExHandler`
- `EXTERNAL:00001088 BASICFRAMEWORKCORELAYER.DLL::GPositionSupport::GetCorner`
- `0x180339f40 GOVChangeMatrix::GOVChangeMatrix`
- `EXTERNAL:00000ee6 BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::GRectBase<double>`
- `EXTERNAL:00000190 PDFOBJECTTOOLSLAYER.DLL::GOVisitorBase::~GOVisitorBase`

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- `.rdata:18044f2b0`

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* public: virtual long __cdecl GOVChangeRotateSelection::Change(class GOPage & __ptr64) __ptr64 */

long __thiscall GOVChangeRotateSelection::Change(GOVChangeRotateSelection *this,GOPage *param_1)

{
  long lVar1;
  undefined8 *puVar2;
  double dVar3;
  double _X;
  long lVar4;
  double *pdVar5;
  undefined8 *puVar6;
  undefined8 in_R9;
  uint uVar7;
  uint uVar8;
  undefined1 auStackY_2f8 [32];
  double local_2c8;
  double dStack_2c0;
  GOVChangeMatrix *local_2b8 [2];
  GRectBase<double> local_2a8 [32];
  double local_288;
  double local_280;
  undefined8 local_278;
  double local_270;
  double local_268;
  double local_260;
  GOVGetFixedBoundingBox local_258 [280];
  undefined1 local_140 [24];
  GOProcessingStrategyDefault local_128 [152];
  GODefaultExHandler local_90 [56];
  ulonglong local_58;

                    /* 0x1303e0  5981  ?Change@GOVChangeRotateSelection@@UEAAJAEAVGOPage@@@Z */
  local_58 = DAT_180723880 ^ (ulonglong)auStackY_2f8;
  GPointBase<double>::GPointBase<double>((GPointBase<double> *)&local_2c8);
  puVar6 = (undefined8 *)0x0;
  switch(*(undefined4 *)(this + 0x1e8)) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    lVar1 = *(long *)(this + 0x1ec);
    lVar4 = GOPage::GetPageBox(param_1,(PageBoxType)local_2a8,SUB41(*(undefined4 *)(this + 0x1e8),0)
                               ,(Type)CONCAT71((int7)((ulonglong)in_R9 >> 8),1));
    pdVar5 = (double *)GPositionSupport::GetCorner((GRectBase<double> *)local_2b8,lVar4,lVar1);
    local_2c8 = *pdVar5;
    dStack_2c0 = pdVar5[1];
    break;
  case 6:
    GRectBase<double>::GRectBase<double>(local_2a8);
    GOVGetFixedBoundingBox::GOVGetFixedBoundingBox
              (local_258,true,true,local_2a8,(GRectBase<double> *)0x0);
    GOPage::Accept(param_1,(GOVisitor *)local_258);
    pdVar5 = (double *)
             GPositionSupport::GetCorner
                       ((GRectBase<double> *)local_2b8,(long)local_2a8,*(long *)(this + 0x1ec));
    local_2c8 = *pdVar5;
    dStack_2c0 = pdVar5[1];
    GODefaultExHandler::~GODefaultExHandler(local_90);
    GOProcessingStrategyDefault::~GOProcessingStrategyDefault(local_128);
    FUN_180027120(local_140);
    GOVisitorBase::~GOVisitorBase((GOVisitorBase *)local_258);
    break;
  case 7:
    GRectBase<double>::GRectBase<double>(local_2a8);
    GOVGetClippedBoundingBox::GOVGetClippedBoundingBox
              ((GOVGetClippedBoundingBox *)local_258,true,true,local_2a8);
    GOPage::Accept(param_1,(GOVisitor *)local_258);
    pdVar5 = (double *)
             GPositionSupport::GetCorner
                       ((GRectBase<double> *)local_2b8,(long)local_2a8,*(long *)(this + 0x1ec));
    local_2c8 = *pdVar5;
    dStack_2c0 = pdVar5[1];
    GOVGetClippedBoundingBox::~GOVGetClippedBoundingBox((GOVGetClippedBoundingBox *)local_258);
  }
  _X = *(double *)(this + 0x1f0) * _DAT_18044ef28;
  dVar3 = cos(_X);
  local_280 = sin(_X);
  uVar7 = SUB84(local_280,0) ^ (uint)DAT_18040d700;
  uVar8 = (uint)((ulonglong)local_280 >> 0x20) ^ DAT_18040d700._4_4_;
  local_268 = (local_2c8 - local_2c8 * dVar3) - dStack_2c0 * (double)CONCAT44(uVar8,uVar7);
  local_260 = (dStack_2c0 - local_2c8 * local_280) - dStack_2c0 * dVar3;
  local_278 = CONCAT44(uVar8,uVar7);
  local_288 = dVar3;
  local_270 = dVar3;
  local_2b8[0] = (GOVChangeMatrix *)FUN_1803cefc4(0x2a0);
  if (local_2b8[0] != (GOVChangeMatrix *)0x0) {
    puVar6 = (undefined8 *)
             GOVChangeMatrix::GOVChangeMatrix
                       (local_2b8[0],(GMatrixBase<double> *)&local_288,(bool)this[0x1f8],0x3ea);
  }
  puVar2 = *(undefined8 **)(this + 0x208);
  if (puVar2 != puVar6) {
    if ((this[0x200] != (GOVChangeRotateSelection)0x0) && (puVar2 != (undefined8 *)0x0)) {
      (**(code **)*puVar2)(puVar2,1);
    }
    *(undefined8 **)(this + 0x208) = puVar6;
  }
  this[0x200] = (GOVChangeRotateSelection)0x1;
  return 0;
}


```

Raw completo: `_raw/PDFObjectActions__1801303e0.txt`.

