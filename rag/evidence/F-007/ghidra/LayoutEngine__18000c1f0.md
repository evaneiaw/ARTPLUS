---
modulo: LayoutEngine.dll
versao: 24.03.10017
funcao: 18000c1f0
nome: MakeGridLayout
assinatura: bool MakeGridLayout(LayoutEngine * this, GridLayout * param_1)
parametros: 2
retorno: bool
confianca: alta
---

## Callers (xrefs de entrada)
- 1800719dc -> unknown (DATA)
- 18007e978 -> unknown (DATA)
- Entry Point -> unknown (EXTERNAL)

## Callees (xrefs de saida)
- 18000bb40 GetGridBoxForPartialLabel
- 18002e120 ~VectorPath
- EXTERNAL:000000f3 _invalid_parameter_noinfo_noreturn
- 18000b010 ApplyStaggerOnGridLayout
- 18000c410 MakeSimpleGridLayout
- 18000a6f0 ApplyHeadTurnOnGridLayout
- 18000a7f0 ApplyPartialLabelStaggerOrContinuousPrintingOnGridLayout
- 18005d16c free
- 180009fc0 ApplyBleedOnGridLayout
- 18000b4d0 FetchGridStationLayoutList
- 180006ce0 FUN_180006ce0

## Strings referenciadas
- 180063878 : 0007acb4

## Pseudocodigo (Ghidra Decompiler)
```c

/* public: bool __cdecl LayoutEngine::LayoutEngine::MakeGridLayout(class LayoutEngine::GridLayout &
   __ptr64) __ptr64 */

bool __thiscall LayoutEngine::LayoutEngine::MakeGridLayout(LayoutEngine *this,GridLayout *param_1)

{
  VectorPath *pVVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  bool bVar6;
  VectorPath *this_00;
  VectorPath *pVVar7;
  VectorPath *local_88;
  VectorPath *pVStack_80;
  longlong local_78;
  double local_70;
  double dStack_68;
  double local_60;
  double dStack_58;
  
                    /* 0xc1f0  234  ?MakeGridLayout@LayoutEngine@1@QEAA_NAEAVGridLayout@1@@Z */
  if (*(longlong *)this == *(longlong *)(this + 8)) {
    bVar6 = false;
  }
  else {
    bVar6 = MakeSimpleGridLayout(this);
    if ((((!bVar6) && (bVar6 = ApplyHeadTurnOnGridLayout(this), !bVar6)) &&
        (bVar6 = ApplyStaggerOnGridLayout(this), !bVar6)) &&
       ((bVar6 = ApplyPartialLabelStaggerOrContinuousPrintingOnGridLayout(this), !bVar6 &&
        (bVar6 = ApplyBleedOnGridLayout(this), !bVar6)))) {
      local_88 = (VectorPath *)0x0;
      pVStack_80 = (VectorPath *)0x0;
      local_78 = 0;
      bVar6 = FetchGridStationLayoutList
                        (this,(vector<LayoutEngine::GridStationLayout,std::allocator<LayoutEngine::GridStationLayout>_>
                               *)&local_88);
      if (!bVar6) {
        local_70 = 0.0;
        dStack_68 = 0.0;
        local_60 = 0.0;
        dStack_58 = 0.0;
        GetGridBoxForPartialLabel(this,(TBox<double> *)&local_70);
        dVar5 = local_60;
        dVar4 = local_70;
        dVar2 = dStack_58 - local_60;
        dVar3 = dStack_68 - local_70;
        if (param_1 != (GridLayout *)&local_88) {
          FUN_180006ce0((ulonglong *)param_1,(GridStationLayout *)local_88,
                        ((longlong)pVStack_80 - (longlong)local_88) / 0xd8);
        }
        *(double *)(param_1 + 0x18) = dVar4;
        *(double *)(param_1 + 0x20) = dVar5;
        *(double *)(param_1 + 0x28) = dVar3;
        *(double *)(param_1 + 0x30) = dVar2;
        bVar6 = false;
      }
      pVVar7 = pVStack_80;
      if (local_88 != (VectorPath *)0x0) {
        if (local_88 != pVStack_80) {
          this_00 = local_88 + 0x48;
          do {
            VectorPath::~VectorPath(this_00 + 0x48);
            VectorPath::~VectorPath(this_00);
            pVVar1 = this_00 + 0x90;
            this_00 = this_00 + 0xd8;
          } while (pVVar1 != pVVar7);
        }
        pVVar7 = local_88;
        if ((0xfff < (ulonglong)(((local_78 - (longlong)local_88) / 0xd8) * 0xd8)) &&
           (pVVar7 = *(VectorPath **)(local_88 + -8),
           (VectorPath *)0x1f < local_88 + (-8 - (longlong)pVVar7))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pVVar7);
      }
    }
  }
  return bVar6;
}


```