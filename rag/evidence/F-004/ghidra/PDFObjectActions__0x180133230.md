---
modulo: PDFObjectActions.dll
funcao: GOVChangeScaleSelection::Change
endereco: 0x180133230
versao: 24.03.10017
confianca: alta
xrefs: []
strings: []
---

# GOVChangeScaleSelection::Change @ 0x180133230

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x180133230` |
| Nome no binario | `GOVChangeScaleSelection::Change` |
| Assinatura (Ghidra) | `long __thiscall Change(GOPage * param_1)` |
| Parametros | 2 |
| Bytes de corpo | 1098 |
| Chamadores | 0 |
| Chamadas diretas | 25 |

## Papel provavel

Fato: `long GOVChangeScaleSelection::Change(GOPage&)`, 1098 bytes, vtable em
`.rdata:18040ade0`. Monta a selecao com `GOVSelectOperator(8)`,
`GOVSelectContentsFromForm(0)` e `GOVSelectOperator(3)`, calcula a caixa com
`GOVGetClippedBoundingBox(true,false)` e a transforma por
`GOPage::GetPageMatrix` + `GRectBase<double>::Transform`.

Fato: o modo de escala vem de `*(int*)(this+0x1e8)` com 6 ramos observados:
`1` (sem matriz explicita), `2` (matriz em `+0x200`), `3` (razao
`campo(+0x1f0) / largura`), `4` (`(largura + campo) / largura`) e
`5` (razao entre a largura da caixa de pagina - `GOPage::GetPageBox`, tipo em
`+0x210` - e a largura da selecao). A matriz resultante e aplicada via
`GOVChangeMatrix::Set`.

Inferencia: e o operador de Action List 'Scale selection' (string existente no
binario; o titulo real vem de `GStringPool::GetString(0x73faa)` em
`GOVChangeScaleSelection::GetTitle` @ 0x180133940, cujo texto nao e
resolvivel estaticamente sem a tabela do GStringPool).

## Xrefs de entrada (quem chama)

- nenhuma chamada direta detectada (provavel entrada por vtable/export)

## Chamadas diretas (quem esta funcao chama)

- `EXTERNAL:0000019c PDFOBJECTTOOLSLAYER.DLL::GOVSelectOperator::GOVSelectOperator`
- `0x180301a30 GOVGetClippedBoundingBox::GOVGetClippedBoundingBox`
- `0x1803cf4c0 __security_check_cookie`
- `0x180027a60 GOVGetClippedBoundingBox::~GOVGetClippedBoundingBox`
- `EXTERNAL:00000198 PDFOBJECTTOOLSLAYER.DLL::GOVDefaultSelect::~GOVDefaultSelect`
- `EXTERNAL:00000ef1 BASICFRAMEWORKCORELAYER.DLL::GProgress::~GProgress`
- `EXTERNAL:00000888 PDFOBJECTLAYER.DLL::GOPage::Accept`
- `EXTERNAL:00000ed8 BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::Transform`
- `EXTERNAL:0000088a PDFOBJECTLAYER.DLL::GOPage::GetPageMatrix`
- `EXTERNAL:00000ef4 BASICFRAMEWORKCORELAYER.DLL::GPositionSupport::AdjustMatrixToKeepCornerFixed`
- `EXTERNAL:00000ed5 BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::GetWidth`
- `EXTERNAL:00000ed6 BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::GetHeight`
- `0x18033c190 GOVChangeMatrix::Set`
- `EXTERNAL:0000019d PDFOBJECTTOOLSLAYER.DLL::GOVSelectOperator::~GOVSelectOperator`
- `EXTERNAL:00000ef9 BASICFRAMEWORKCORELAYER.DLL::ScopeGuardImplBase::ScopeGuardImplBase`
- `EXTERNAL:00000ef8 BASICFRAMEWORKCORELAYER.DLL::ScopeGuardImplBase::~ScopeGuardImplBase`
- `0x180035bb0 FUN_180035bb0`
- `EXTERNAL:00000889 PDFOBJECTLAYER.DLL::GOPage::GetPageBox`
- `0x1803cefc4 FUN_1803cefc4`
- `0x180262ef0 GOVSelectContentsFromForm::GOVSelectContentsFromForm`
- `0x180035290 FUN_180035290`
- `0x180339f40 GOVChangeMatrix::GOVChangeMatrix`
- `EXTERNAL:00000ee6 BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::GRectBase<double>`
- `EXTERNAL:00000ef0 BASICFRAMEWORKCORELAYER.DLL::GProgress::GProgress`
- `EXTERNAL:0000102e BASICFRAMEWORKCORELAYER.DLL::GMatrixBase<double>::operator==`

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- `.rdata:18040ade0`

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: virtual long __cdecl GOVChangeScaleSelection::Change(class GOPage & __ptr64) __ptr64
    */

long __thiscall GOVChangeScaleSelection::Change(GOVChangeScaleSelection *this,GOPage *param_1)

{
  int iVar1;
  undefined8 *puVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  GOVChangeMatrix *pGVar6;
  GOVChangeMatrix *pGVar7;
  bool bVar8;
  GMatrixBase<double> *pGVar9;
  GRectBase<double> *pGVar10;
  undefined8 *puVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined1 auStack_928 [32];
  undefined4 local_908;
  GProgress local_8f8 [8];
  GRectBase<double> local_8f0 [32];
  GOVChangeMatrix *local_8d0;
  GOPage *local_8c8;
  undefined8 uStack_8c0;
  GOVChangeMatrix *local_8b8;
  undefined8 local_8b0;
  undefined8 uStack_8a8;
  GOVChangeMatrix *local_8a0;
  undefined8 uStack_898;
  undefined8 uStack_890;
  GOVChangeMatrix *pGStack_888;
  undefined8 local_880;
  undefined8 uStack_878;
  GMatrixBase<double> local_870 [56];
  GOVSelectContentsFromForm local_838 [488];
  undefined1 local_650 [24];
  GOVSelectOperator local_638 [496];
  GOVSelectOperator local_448 [496];
  GOVGetClippedBoundingBox local_258 [512];
  ulonglong local_58;

                    /* 0x133230  5989  ?Change@GOVChangeScaleSelection@@MEAAJAEAVGOPage@@@Z */
  local_58 = DAT_180723880 ^ (ulonglong)auStack_928;
  GProgress::GProgress(local_8f8,0.0);
  GOVSelectOperator::GOVSelectOperator(local_448,8);
  GOPage::Accept(param_1,(GOVisitor *)local_448);
  GOVSelectContentsFromForm::GOVSelectContentsFromForm(local_838,0);
  GOPage::Accept(param_1,(GOVisitor *)local_838);
  GOVSelectOperator::GOVSelectOperator(local_638,3);
  GOPage::Accept(param_1,(GOVisitor *)local_638);
  ScopeGuardImplBase::ScopeGuardImplBase((ScopeGuardImplBase *)&local_8d0);
  local_8c8 = param_1;
  GRectBase<double>::GRectBase<double>(local_8f0);
  GOVGetClippedBoundingBox::GOVGetClippedBoundingBox(local_258,true,false,local_8f0);
  GOPage::Accept(param_1,(GOVisitor *)local_258);
  pGVar9 = (GMatrixBase<double> *)GOPage::GetPageMatrix(param_1);
  GRectBase<double>::Transform(local_8f0,pGVar9);
  GOVGetClippedBoundingBox::~GOVGetClippedBoundingBox(local_258);
  FUN_180035290(&local_8d0);
  ScopeGuardImplBase::~ScopeGuardImplBase((ScopeGuardImplBase *)&local_8d0);
  GOVSelectOperator::~GOVSelectOperator(local_638);
  FUN_180035bb0(local_650);
  GOVDefaultSelect::~GOVDefaultSelect((GOVDefaultSelect *)local_838);
  GOVSelectOperator::~GOVSelectOperator(local_448);
  GProgress::~GProgress(local_8f8);
  pGVar7 = DAT_18040a028;
  iVar1 = *(int *)(this + 0x1e8);
  pGVar6 = DAT_18040a028;
  if (iVar1 != 0) {
    if (iVar1 == 2) {
      pGVar6 = *(GOVChangeMatrix **)(this + 0x200);
    }
    else if (iVar1 == 3) {
      dVar3 = GRectBase<double>::GetWidth(local_8f0);
      pGVar6 = (GOVChangeMatrix *)(*(double *)(this + 0x1f0) / dVar3);
    }
    else if (iVar1 == 4) {
      dVar4 = GRectBase<double>::GetWidth(local_8f0);
      dVar3 = *(double *)(this + 0x1f0);
      dVar5 = GRectBase<double>::GetWidth(local_8f0);
      pGVar6 = (GOVChangeMatrix *)((dVar4 + dVar3) / dVar5);
    }
    else {
      pGVar6 = (GOVChangeMatrix *)0x0;
      if (iVar1 == 5) {
        local_908 = 2;
        pGVar10 = (GRectBase<double> *)
                  GOPage::GetPageBox(param_1,(PageBoxType)&local_8d0,
                                     SUB41(*(undefined4 *)(this + 0x210),0),0);
        dVar3 = GRectBase<double>::GetWidth(pGVar10);
        dVar4 = GRectBase<double>::GetWidth(local_8f0);
        pGVar6 = (GOVChangeMatrix *)(dVar3 / dVar4);
      }
    }
  }
  pGStack_888 = (GOVChangeMatrix *)0x0;
  switch(*(undefined4 *)(this + 0x1ec)) {
  case 0:
    pGStack_888 = pGVar7;
    break;
  case 1:
    pGStack_888 = pGVar6;
    break;
  case 2:
    pGStack_888 = *(GOVChangeMatrix **)(this + 0x208);
    break;
/* ... 87 linhas omitidas ... */
```

Raw completo: `_raw/PDFObjectActions__180133230.txt`.

