---
modulo: PDFObjectActions.dll
funcao: GOVSelectOverlappingObjects::Select
endereco: 0x18028df80
versao: 24.03.10017
confianca: alta
xrefs: []
strings: []
---

# GOVSelectOverlappingObjects::Select @ 0x18028df80

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x18028df80` |
| Nome no binario | `GOVSelectOverlappingObjects::Select` |
| Assinatura (Ghidra) | `bool __thiscall Select(GOPage * param_1)` |
| Parametros | 2 |
| Bytes de corpo | 2073 |
| Chamadores | 0 |
| Chamadas diretas | 38 |

## Papel provavel

Fato: `bool GOVSelectOverlappingObjects::Select(GOPage&)`, 2073 bytes, vtable
em `.rdata:1804f2240`. Usa GEOMAPPER (`GeoMapper::TGraph`, `TRegionIterator`,
`TElementAttributeIterator`), `GOVGeoMapperTStackBuilder`, `GOPage::Accept`,
`GOVSelectOperator`, `GMatrixBase<double>::GetInverse` e
`GTable<GOObject*>::GetItemAt`/`GetCount`.

Inferencia: reconstroi as regioes geometricas da pagina (grafo GeoMapper) e
seleciona os objetos cujas regioes se sobrepoem, preenchendo a tabela de
selecao (`GTable<GOObject*>`). E o operador citado em F-004 secao 8 como
`GOVSelectOverlappingObjects` - o nome da classe e fato; o comportamento
detalhado e inferido do grafo de chamadas.

## Xrefs de entrada (quem chama)

- nenhuma chamada direta detectada (provavel entrada por vtable/export)

## Chamadas diretas (quem esta funcao chama)

- `EXTERNAL:0000009f GEOMAPPER.DLL::GeoMapper::Input::TStack::TStack`
- `EXTERNAL:0000019c PDFOBJECTTOOLSLAYER.DLL::GOVSelectOperator::GOVSelectOperator`
- `0x1802fe5d0 GOVGeoMapperTStackBuilder::~GOVGeoMapperTStackBuilder`
- `0x1803cf4c0 __security_check_cookie`
- `0x18028c870 FUN_18028c870`
- `0x1801237f0 FUN_1801237f0`
- `EXTERNAL:000000b3 GEOMAPPER.DLL::GeoMapper::TElementAttributeIterator::TElementAttributeIterator`
- `EXTERNAL:00000ef1 BASICFRAMEWORKCORELAYER.DLL::GProgress::~GProgress`
- `EXTERNAL:00000b7b PDFOBJECTLAYER.DLL::GOElement::GetClassType`
- `EXTERNAL:00000888 PDFOBJECTLAYER.DLL::GOPage::Accept`
- `EXTERNAL:000000bc GEOMAPPER.DLL::GeoMapper::TGraph::TRegion::~TRegion`
- `0x18028d7b0 FUN_18028d7b0`
- `EXTERNAL:00000f8d BASICFRAMEWORKCORELAYER.DLL::GAllocator::Free`
- `EXTERNAL:000000b5 GEOMAPPER.DLL::GeoMapper::TElementAttributeIterator::NextAttribute`
- `EXTERNAL:00000743 PDFOBJECTLAYER.DLL::GTable<GOObject*___ptr64>::RemoveAllItems`
- `EXTERNAL:000000b1 GEOMAPPER.DLL::GeoMapper::TGraph::TRegionIterator::~TRegionIterator`
- `0x1802c6ca0 FUN_1802c6ca0`
- `EXTERNAL:0000019d PDFOBJECTTOOLSLAYER.DLL::GOVSelectOperator::~GOVSelectOperator`
- `EXTERNAL:000000b2 GEOMAPPER.DLL::GeoMapper::TGraph::TRegionIterator::NextRegion`
- `EXTERNAL:000000bb GEOMAPPER.DLL::GeoMapper::TGraph::TRegion::TRegion`
- `EXTERNAL:000000b4 GEOMAPPER.DLL::GeoMapper::TElementAttributeIterator::~TElementAttributeIterator`
- `EXTERNAL:00000ef9 BASICFRAMEWORKCORELAYER.DLL::ScopeGuardImplBase::ScopeGuardImplBase`
- `0x1803cf000 API-MS-WIN-CRT-HEAP-L1-1-0.DLL::free`
- `EXTERNAL:00000ef8 BASICFRAMEWORKCORELAYER.DLL::ScopeGuardImplBase::~ScopeGuardImplBase`
- `EXTERNAL:00000f8e BASICFRAMEWORKCORELAYER.DLL::GAllocator::GetInstance`

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- `.rdata:1804f2240`

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: virtual bool __cdecl GOVSelectOverlappingObjects::Select(class GOPage & __ptr64)
   __ptr64 */

bool __thiscall
GOVSelectOverlappingObjects::Select(GOVSelectOverlappingObjects *this,GOPage *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  void *pvVar4;
  GOObject *pGVar5;
  GOObject *pGVar6;
  undefined8 uVar7;
  bool bVar8;
  longlong *_Memory;
  bool bVar9;
  char cVar10;
  long lVar11;
  GOObjectType *pGVar12;
  GOObject **ppGVar13;
  uint *puVar14;
  undefined8 *puVar15;
  longlong *_Memory_00;
  TElementAttribute *pTVar16;
  int *piVar17;
  GAllocator *this_00;
  uint uVar18;
  int *piVar19;
  void *pvVar20;
  undefined4 *puVar21;
  uint uVar22;
  int *piVar23;
  longlong lVar24;
  uint uVar25;
  int *piVar26;
  ulonglong uVar27;
  uint uVar28;
  ulonglong uVar29;
  ulonglong uVar30;
  int iVar31;
  uint uVar32;
  undefined1 auStack_928 [32];
  GProgress local_908 [8];
  undefined8 local_900;
  TRegion local_8f8 [8];
  void *local_8f0;
  int local_8e8;
  int iStack_8e4;
  longlong local_8e0;
  char local_8d8 [8];
  longlong *local_8d0;
  undefined8 local_8c8;
  undefined8 uStack_8c0;
  undefined1 local_8b8 [8];
  longlong *local_8b0;
  undefined1 local_8a8;
  undefined8 local_8a0;
  ScopeGuardImplBase local_898 [8];
  GOPage *local_890;
  undefined1 *local_888;
  undefined4 local_880;
  undefined4 local_87c;
  GOVSelectOperator *local_878;
  TRegionIterator local_860 [32];
  undefined **local_840;
  void **local_838;
  GOVSelectOverlappingObjects *local_830;
  undefined ***local_808;
  TStack local_800 [40];
  undefined **local_7d8;
  undefined4 local_7d0;
  undefined4 uStack_7cc;
  undefined4 uStack_7c8;
  undefined4 uStack_7c4;
  undefined ***local_7a0;
  undefined1 local_798 [48];
  TGraph local_768 [96];
  GOVSelectOperator local_708 [496];
  GOVSelectOperator local_518 [496];
  GOVGeoMapperTStackBuilder local_328 [736];
  ulonglong local_48;

                    /* 0x28df80  13460  ?Select@GOVSelectOverlappingObjects@@MEAA_NAEAVGOPage@@@Z */
  local_48 = DAT_180723880 ^ (ulonglong)auStack_928;
  if (*(int *)(this + 0x1e0) - 2U < 2) {
    bVar9 = false;
    lVar11 = GTable<GOObject*___ptr64>::GetCount
                       ((GTable<GOObject*___ptr64> *)**(undefined8 **)(this + 0x1e8));
    lVar11 = lVar11 + -1;
    if (-1 < lVar11) {
      do {
        if (bVar9) goto LAB_18028e05c;
        pGVar12 = GOElement::GetClassType();
        ppGVar13 = GTable<GOObject*___ptr64>::GetItemAt
                             ((GTable<GOObject*___ptr64> *)**(undefined8 **)(this + 0x1e8),lVar11);
        puVar14 = (uint *)(**(code **)(*(longlong *)*ppGVar13 + 8))();
        if (((*(uint *)(pGVar12 + 8) & puVar14[2]) != 0 ||
            (*(uint *)(pGVar12 + 4) & puVar14[1]) != 0) || (*(uint *)pGVar12 & *puVar14) != 0) {
          bVar9 = true;
        }
        lVar11 = lVar11 + -1;
      } while (-1 < lVar11);
      if (bVar9) goto LAB_18028e05c;
    }
    GTable<GOObject*___ptr64>::RemoveAllItems
              ((GTable<GOObject*___ptr64> *)**(undefined8 **)(this + 0x1e8));
  }
/* ... 299 linhas omitidas ... */
```

Raw completo: `_raw/PDFObjectActions__18028df80.txt`.

