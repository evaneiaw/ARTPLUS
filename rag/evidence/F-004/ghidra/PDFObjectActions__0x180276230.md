---
modulo: PDFObjectActions.dll
funcao: GOVSelectHitElement::Select
endereco: 0x180276230
versao: 24.03.10017
confianca: alta
xrefs: [0x1802544f0, 0x1802549d0, 0x180254690, 0x180254830, 0x1802542f0]
strings: []
---

# GOVSelectHitElement::Select @ 0x180276230

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x180276230` |
| Nome no binario | `GOVSelectHitElement::Select` |
| Assinatura (Ghidra) | `bool __thiscall Select(GOElement * param_1)` |
| Parametros | 2 |
| Bytes de corpo | 2441 |
| Chamadores | 5 |
| Chamadas diretas | 10 |

## Papel provavel

Fato (Ghidra): metodo virtual `bool GOVSelectHitElement::Select(GOElement&)`,
2441 bytes, vtable em `.rdata:1804e7590`. Chama `GRectBase<double>::Contains`,
`GRectBase<double>::Intersects`, `GRectBase<double>::IsInfinite`,
`GOLocation::IsInPropertyContent`, `GOVComparator::RoundValue` e tres rotinas
internas (180275430, 180275850, 180277200).

Fato: os 5 chamadores diretos sao `GOVSelectCloseToPageEdge::DetectCloseToBottomEdge`,
`DetectCloseToTopEdge`, `DetectCloseToLeftEdge`, `DetectCloseToRightEdge` e
`ElementVisibleOnRect` - ou seja, o teste geometrico e reutilizado como
'elemento visivel dentro do retangulo'.

Inferencia: e o primitivo de hit-test por retangulo (rubber-band) referido em
F-004 R1/E2; o retorno booleano e o resultado do teste. Nao ha string de UI
nesta funcao (0 referencias a string), portanto ela nao produz a mensagem de
status citada na spec.

## Xrefs de entrada (quem chama)

- `0x1802544f0 GOVSelectCloseToPageEdge::DetectCloseToLeftEdge`
- `0x1802549d0 GOVSelectCloseToPageEdge::ElementVisibleOnRect`
- `0x180254690 GOVSelectCloseToPageEdge::DetectCloseToRightEdge`
- `0x180254830 GOVSelectCloseToPageEdge::DetectCloseToTopEdge`
- `0x1802542f0 GOVSelectCloseToPageEdge::DetectCloseToBottomEdge`

## Chamadas diretas (quem esta funcao chama)

- `EXTERNAL:00000990 PDFOBJECTLAYER.DLL::GOLocation::IsInPropertyContent`
- `0x180277200 FUN_180277200`
- `EXTERNAL:0000108c BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::IsInfinite`
- `0x180275430 FUN_180275430`
- `0x180275850 FUN_180275850`
- `EXTERNAL:00000f79 BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::Contains`
- `EXTERNAL:00000f6f BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::Intersects`
- `EXTERNAL:00000ee6 BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::GRectBase<double>`
- `EXTERNAL:0000035e PDFOBJECTTOOLSLAYER.DLL::GOVComparator::RoundValue`
- `EXTERNAL:00000f0d BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::Set`

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- `.rdata:1804e7590`

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* public: virtual bool __cdecl GOVSelectHitElement::Select(class GOElement & __ptr64) __ptr64 */

bool __thiscall GOVSelectHitElement::Select(GOVSelectHitElement *this,GOElement *param_1)

{
  code *pcVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  char cVar9;
  longlong *plVar10;
  undefined8 uVar11;
  uint uVar12;
  int iVar13;
  double local_148;
  double local_140;
  double local_138;
  double local_130;
  char local_128;
  double local_120;
  double dStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 local_100;
  double local_f8;
  double dStack_f0;
  double local_e8;
  double dStack_e0;
  double local_d8;
  double dStack_d0;
  undefined4 local_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined8 local_b8;
  undefined1 local_90 [120];

                    /* 0x276230  13390  ?Select@GOVSelectHitElement@@UEAA_NAEAVGOElement@@@Z */
  bVar6 = GOLocation::IsInPropertyContent();
  if ((bVar6) ||
     ((this[0x200] != (GOVSelectHitElement)0x0 && (this[0x201] != (GOVSelectHitElement)0x0)))) {
    return false;
  }
  FUN_180275430(&local_148,this + 0x1e0);
  GRectBase<double>::GRectBase<double>((GRectBase<double> *)&local_f8);
  (**(code **)(*(longlong *)param_1 + 0x38))(param_1,&local_f8,2);
  local_100 = CONCAT71(local_100._1_7_,1);
  local_120 = local_f8;
  dStack_118 = dStack_f0;
  local_110 = local_e8;
  uStack_108 = dStack_e0;
  bVar6 = GRectBase<double>::IsInfinite((GRectBase<double> *)&local_120);
  if (!bVar6) {
    dVar2 = GOVComparator::RoundValue(2,uStack_108,2,0.0);
    dVar3 = GOVComparator::RoundValue(2,local_110,2,0.0);
    dVar4 = GOVComparator::RoundValue(2,dStack_118,2,0.0);
    dVar5 = GOVComparator::RoundValue(2,local_120,2,0.0);
    GRectBase<double>::Set((GRectBase<double> *)&local_120,dVar5,dVar4,dVar3,dVar2);
  }
  plVar10 = (longlong *)(**(code **)(*(longlong *)param_1 + 0x50))(param_1);
  if (plVar10 == (longlong *)0x0) {
    if (this[0x20b] == (GOVSelectHitElement)0x0) {
      if (this[0x209] == (GOVSelectHitElement)0x0) {
        uVar12 = (this[0x20a] != (GOVSelectHitElement)0x0) + 2;
      }
      else {
        uVar12 = (uint)(this[0x20a] != (GOVSelectHitElement)0x0);
      }
    }
    else {
      uVar12 = 4;
    }
    bVar6 = false;
    if ((char)local_100 == '\0') goto LAB_180276b87;
    if (uVar12 == 0) {
LAB_180276b33:
      bVar6 = false;
      if (((local_128 == '\0') ||
          (bVar8 = GRectBase<double>::Contains
                             ((GRectBase<double> *)&local_148,(GRectBase<double> *)&local_120),
          !bVar8)) ||
         ((local_138 <= local_120 ||
          (((local_110 <= local_148 || (local_130 <= dStack_118)) || (uStack_108 <= local_140))))))
      goto LAB_180276b87;
    }
    else {
      if (uVar12 == 1) {
        bVar8 = false;
        if (local_128 != '\0') {
          bVar8 = GRectBase<double>::Contains
                            ((GRectBase<double> *)&local_148,(GRectBase<double> *)&local_120);
        }
        bVar6 = true;
        if (bVar8 != false) goto LAB_180276b87;
        if ((((local_138 <= local_120) || (local_110 <= local_148)) || (local_130 <= dStack_118)) ||
           (bVar6 = false, uStack_108 <= local_140)) {
          bVar6 = true;
        }
        if (((!bVar6) && (local_128 != '\0')) &&
           (((char)local_100 != '\0' &&
            (bVar6 = GRectBase<double>::Intersects
                               ((GRectBase<double> *)&local_148,(GRectBase<double> *)&local_120),
            bVar6)))) {
          pcVar1 = *(code **)(*(longlong *)param_1 + 0x48);
          uVar11 = FUN_180277200(&local_d8,&local_148);
/* ... 238 linhas omitidas ... */
```

Raw completo: `_raw/PDFObjectActions__180276230.txt`.

