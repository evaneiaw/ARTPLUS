---
modulo: PDFObjectActions.dll
funcao: GOVSelectOverlapping::Select
endereco: 0x18028c410
versao: 24.03.10017
confianca: alta
xrefs: []
strings: []
---

# GOVSelectOverlapping::Select @ 0x18028c410

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x18028c410` |
| Nome no binario | `GOVSelectOverlapping::Select` |
| Assinatura (Ghidra) | `bool __thiscall Select(GOPage * param_1)` |
| Parametros | 2 |
| Bytes de corpo | 778 |
| Chamadores | 0 |
| Chamadas diretas | 11 |

## Papel provavel

Fato: `bool GOVSelectOverlapping::Select(GOPage&)` monta dois visitantes
`GOVGetObjectBBoxes` e dois `GOVSelectOperatorRoll`, percorre a pagina com
`GOPage::Accept` e usa `GRectBase<double>::Intersects` para cruzar caixas.

Fato: alimenta `GSet<GOOCGroup const*>::AddItem` (grupos de conteudo opcional)
e usa `GAllocator::GetInstance`/`GAllocator::Free` para as tabelas temporarias.

Inferencia: e a implementacao do operador de Action List descrito pela string
do proprio binario 'This Action needs to be preceded by 2 Selects. It will
select the objects from the first selection that have a bounding box that
intersects with the bounding box of an object from the second selection.'
(string presente no binario; associacao ao endereco marcada como inferencia).

## Xrefs de entrada (quem chama)

- nenhuma chamada direta detectada (provavel entrada por vtable/export)

## Chamadas diretas (quem esta funcao chama)

- `EXTERNAL:00000888 PDFOBJECTLAYER.DLL::GOPage::Accept`
- `0x180304aa0 GOVGetObjectBBoxes::~GOVGetObjectBBoxes`
- `EXTERNAL:00000f8d BASICFRAMEWORKCORELAYER.DLL::GAllocator::Free`
- `0x180304a00 GOVGetObjectBBoxes::GOVGetObjectBBoxes`
- `EXTERNAL:00000fd3 BASICFRAMEWORKCORELAYER.DLL::GRectBase<double>::Intersects`
- `0x180289680 GOVSelectOperatorRoll::GOVSelectOperatorRoll`
- `0x1800396c0 GSet<GOOCGroup_const*___ptr64>::AddItem`
- `EXTERNAL:00000198 PDFOBJECTTOOLSLAYER.DLL::GOVDefaultSelect::~GOVDefaultSelect`
- `EXTERNAL:00000f8e BASICFRAMEWORKCORELAYER.DLL::GAllocator::GetInstance`
- `EXTERNAL:00000ef0 BASICFRAMEWORKCORELAYER.DLL::GProgress::GProgress`
- `EXTERNAL:00000ef1 BASICFRAMEWORKCORELAYER.DLL::GProgress::~GProgress`

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- `.rdata:1804f1d10`

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* public: virtual bool __cdecl GOVSelectOverlapping::Select(class GOPage & __ptr64) __ptr64 */

bool __thiscall GOVSelectOverlapping::Select(GOVSelectOverlapping *this,GOPage *param_1)

{
  bool bVar1;
  GAllocator *pGVar2;
  void *pvVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  void *pvVar7;
  int iVar8;
  GProgress local_res18 [8];
  void *local_818;
  undefined8 local_810;
  longlong local_808;
  void *local_800;
  undefined8 local_7f8;
  longlong local_7f0;
  GOVSelectOperatorRoll local_7e8 [496];
  GOVGetObjectBBoxes local_5f8 [496];
  GOVSelectOperatorRoll local_408 [496];
  GOVGetObjectBBoxes local_218 [496];

                    /* 0x28c410  13458  ?Select@GOVSelectOverlapping@@UEAA_NAEAVGOPage@@@Z */
  local_800 = (void *)0x0;
  local_7f8 = 0;
  local_7f0 = 0;
  local_818 = (void *)0x0;
  local_810 = 0;
  local_808 = 0;
  GProgress::GProgress(local_res18,0.0);
  GOVGetObjectBBoxes::GOVGetObjectBBoxes
            (local_218,(GTable<GPair<GOElement*___ptr64,GRectBase<double>_>_> *)&local_800);
  GOPage::Accept(param_1,(GOVisitor *)local_218);
  GOVSelectOperatorRoll::GOVSelectOperatorRoll(local_408,2,1);
  GOPage::Accept(param_1,(GOVisitor *)local_408);
  GOVGetObjectBBoxes::GOVGetObjectBBoxes
            (local_5f8,(GTable<GPair<GOElement*___ptr64,GRectBase<double>_>_> *)&local_818);
  GOPage::Accept(param_1,(GOVisitor *)local_5f8);
  GOVSelectOperatorRoll::GOVSelectOperatorRoll(local_7e8,2,1);
  GOPage::Accept(param_1,(GOVisitor *)local_7e8);
  iVar8 = 0;
  if (0 < local_810._4_4_) {
    lVar5 = 0;
    pvVar3 = local_818;
    pvVar7 = local_800;
    do {
      iVar4 = 0;
      if (0 < local_7f8._4_4_) {
        lVar6 = 0;
        do {
          if (*(longlong *)(lVar5 + (longlong)pvVar3) != *(longlong *)(lVar6 + (longlong)pvVar7)) {
            bVar1 = GRectBase<double>::Intersects
                              ((GRectBase<double> *)((longlong)pvVar3 + (longlong)iVar8 * 0x28 + 8),
                               (GRectBase<double> *)
                               ((longlong)pvVar7 + ((longlong)iVar4 * 5 + 1) * 8),
                               (GComparator<double> *)(this + 0x1e0),
                               (GComparator<double> *)(this + 0x200));
            if (bVar1) {
              GSet<GOOCGroup_const*___ptr64>::AddItem
                        ((GSet<GOOCGroup_const*___ptr64> *)(this + 0x220),
                         (GOOCGroup **)((longlong)local_818 + (longlong)iVar8 * 0x28));
              pvVar3 = local_818;
              pvVar7 = local_800;
              break;
            }
            pvVar3 = local_818;
            pvVar7 = local_800;
          }
          iVar4 = iVar4 + 1;
          lVar6 = lVar6 + 0x28;
        } while (iVar4 < local_7f8._4_4_);
      }
      iVar8 = iVar8 + 1;
      lVar5 = lVar5 + 0x28;
    } while (iVar8 < local_810._4_4_);
  }
  GOVDefaultSelect::~GOVDefaultSelect((GOVDefaultSelect *)local_7e8);
  GOVGetObjectBBoxes::~GOVGetObjectBBoxes(local_5f8);
  GOVDefaultSelect::~GOVDefaultSelect((GOVDefaultSelect *)local_408);
  GOVGetObjectBBoxes::~GOVGetObjectBBoxes(local_218);
  GProgress::~GProgress(local_res18);
  lVar5 = local_808;
  if ((int)local_810 != 0) {
    local_810 = local_810 & 0xffffffff;
    for (; lVar5 != 0; lVar5 = *(longlong *)(lVar5 + 0x18)) {
      if ((*(int *)(lVar5 + 0x10) != 1) && (-1 < *(int *)(lVar5 + 0xc))) {
        *(int *)(lVar5 + 0xc) = *(int *)(lVar5 + 0xc);
      }
    }
    pGVar2 = GAllocator::GetInstance();
    GAllocator::Free(pGVar2,local_818,(longlong)(int)local_810 * 0x28);
    lVar5 = local_808;
  }
  for (; lVar5 != 0; lVar5 = *(longlong *)(lVar5 + 0x18)) {
    *(undefined4 *)(lVar5 + 0xc) = 0xffffffff;
    *(undefined4 *)(lVar5 + 0x10) = 1;
  }
  if ((int)local_7f8 != 0) {
    local_7f8 = local_7f8 & 0xffffffff;
    for (lVar5 = local_7f0; lVar5 != 0; lVar5 = *(longlong *)(lVar5 + 0x18)) {
      if ((*(int *)(lVar5 + 0x10) != 1) && (-1 < *(int *)(lVar5 + 0xc))) {
        *(int *)(lVar5 + 0xc) = *(int *)(lVar5 + 0xc);
      }
    }
    pGVar2 = GAllocator::GetInstance();
    GAllocator::Free(pGVar2,local_800,(longlong)(int)local_7f8 * 0x28);
/* ... 9 linhas omitidas ... */
```

Raw completo: `_raw/PDFObjectActions__18028c410.txt`.

