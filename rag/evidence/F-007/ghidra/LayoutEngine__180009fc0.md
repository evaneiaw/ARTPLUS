modulo: LayoutEngine.dll
versao: 24.03.10017.10017
funcao: 180009fc0
nome: ApplyBleedOnGridLayout
assinatura: bool ApplyBleedOnGridLayout(LayoutEngine * this)
parametros: 1
retorno: bool

## Callers (xrefs de entrada)
- 1800717f4 -> unknown (DATA)
- 18007e8ac -> unknown (DATA)
- Entry Point -> unknown (EXTERNAL)
- 18000c26f -> MakeGridLayout @ 18000c1f0 (UNCONDITIONAL_CALL)

## Callees (xrefs de saida)
- 18002e120 ~VectorPath
- 180002ef0 FUN_180002ef0
- 18005d370 __security_check_cookie
- 1800044c0 FUN_1800044c0
- EXTERNAL:0000000e GetBleed
- 180003d70 FUN_180003d70
- 18002eff0 Transform
- 18000bef0 GetMaskFromOneUp
- 18003e740 FUN_18003e740
- 180001c80 FUN_180001c80
- 18005d130 FUN_18005d130
- 180002fa0 FUN_180002fa0
- EXTERNAL:000000f3 _invalid_parameter_noinfo_noreturn
- 1800014e0 FUN_1800014e0
- 18005d16c free
- 180001ff0 FUN_180001ff0
- 18002e0f0 VectorPath
- 180007860 FUN_180007860
- 180004740 FUN_180004740

## Strings referenciadas
- 18007c380 : 0x2b992ddfa232
- 180063cf8 : 0x3ff0000000000000
- 180063370 : 000782fa
- 180063878 : 0007acb4

## Pseudocodigo (Ghidra Decompiler)
```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* private: bool __cdecl LayoutEngine::LayoutEngine::ApplyBleedOnGridLayout(void) __ptr64 */

bool __thiscall LayoutEngine::LayoutEngine::ApplyBleedOnGridLayout(LayoutEngine *this)

{
  char cVar1;
  undefined8 *puVar2;
  double dVar3;
  longlong *plVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  VectorPath *pVVar10;
  int iVar11;
  undefined1 auStack_218 [32];
  longlong *local_1f8;
  longlong local_1f0;
  longlong *local_1d8;
  undefined8 uStack_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  undefined8 uStack_1b8;
  undefined8 local_1b0;
  longlong **local_1a8;
  undefined8 local_1a0;
  VectorPath local_198 [8];
  undefined8 *local_190;
  longlong local_188;
  undefined4 local_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined4 local_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined1 local_158;
  VectorPath local_148 [8];
  ulonglong local_140 [3];
  longlong local_128;
  longlong lStack_120;
  longlong local_118;
  longlong lStack_110;
  undefined1 local_108;
  VectorPath local_f8 [8];
  undefined8 *local_f0;
  longlong local_e8;
  longlong local_d8;
  longlong lStack_d0;
  longlong local_c8;
  longlong lStack_c0;
  undefined1 local_b8;
  VectorPath *local_a8;
  VectorPath *local_a0;
  longlong local_98;
  void *local_90 [2];
  ulonglong local_80;
  undefined1 local_78 [32];
  ulonglong local_58;
  
                    /* 0x9fc0  112  ?ApplyBleedOnGridLayout@LayoutEngine@1@AEAA_NXZ */
  local_58 = DAT_18007c380 ^ (ulonglong)auStack_218;
  plVar9 = (longlong *)**(longlong **)(this + 0x90);
  cVar1 = *(char *)((longlong)plVar9 + 0x19);
  while (cVar1 == '\0') {
    VectorPath::VectorPath(local_198);
    GetMaskFromOneUp(this,(GridStation *)(plVar9 + 5),local_198);
    local_1c0 = 0;
    uStack_1b8 = 0;
    local_1d8 = (longlong *)0x0;
    uStack_1d0 = 0;
    local_1b0 = 0x3ff0000000000000;
    local_1c8 = 0x3ff0000000000000;
    FUN_18003e740((longlong)(plVar9 + 5),(GridParameters *)(this + 0x18),(TTrafo *)&local_1d8);
    VectorPath::Transform(local_198,(TTrafo *)&local_1d8);
    *(VectorPath *)(plVar9 + 0xd) = local_198[0];
    if ((undefined8 **)(plVar9 + 0xe) != &local_190) {
      FUN_1800014e0((ulonglong *)(plVar9 + 0xe),local_190,(local_188 - (longlong)local_190) / 0x18);
    }
    *(undefined4 *)(plVar9 + 0x11) = local_178;
    *(undefined4 *)((longlong)plVar9 + 0x8c) = uStack_174;
    *(undefined4 *)(plVar9 + 0x12) = uStack_170;
    *(undefined4 *)((longlong)plVar9 + 0x94) = uStack_16c;
    *(undefined4 *)(plVar9 + 0x13) = local_168;
    *(undefined4 *)((longlong)plVar9 + 0x9c) = uStack_164;
    *(undefined4 *)(plVar9 + 0x14) = uStack_160;
    *(undefined4 *)((longlong)plVar9 + 0xa4) = uStack_15c;
    *(undefined1 *)(plVar9 + 0x15) = local_158;
    *(VectorPath *)(plVar9 + 0x16) = local_198[0];
    if ((undefined8 **)(plVar9 + 0x17) != &local_190) {
      FUN_1800014e0((ulonglong *)(plVar9 + 0x17),local_190,(local_188 - (longlong)local_190) / 0x18)
      ;
    }
    *(undefined4 *)(plVar9 + 0x1a) = local_178;
    *(undefined4 *)((longlong)plVar9 + 0xd4) = uStack_174;
    *(undefined4 *)(plVar9 + 0x1b) = uStack_170;
    *(undefined4 *)((longlong)plVar9 + 0xdc) = uStack_16c;
    *(undefined4 *)(plVar9 + 0x1c) = local_168;
    *(undefined4 *)((longlong)plVar9 + 0xe4) = uStack_164;
    *(undefined4 *)(plVar9 + 0x1d) = uStack_160;
    *(undefined4 *)((longlong)plVar9 + 0xec) = uStack_15c;
    *(undefined1 *)(plVar9 + 0x1e) = local_158;
    VectorPath::~VectorPath(local_198);
    plVar6 = (longlong *)plVar9[2];
    if (*(char *)((longlong)plVar6 + 0x19) == '\0') {
      cVar1 = *(char *)(*plVar6 + 0x19);
      plVar9 = plVar6;
      plVar6 = (longlong *)*plVar6;
      while (cVar1 == '\0') {
        cVar1 = *(char *)(*plVar6 + 0x19);
        plVar9 = plVar6;
        plVar6 = (longlong *)*plVar6;
      }
    }
    else {
      cVar1 = *(char *)(plVar9[1] + 0x19);
      plVar7 = (longlong *)plVar9[1];
      plVar6 = plVar9;
      while ((plVar9 = plVar7, cVar1 == '\0' && (plVar6 == (longlong *)plVar9[2]))) {
        cVar1 = *(char *)(plVar9[1] + 0x19);
        plVar7 = (longlong *)plVar9[1];
        plVar6 = plVar9;
      }
    }
    cVar1 = *(char *)((longlong)plVar9 + 0x19);
  }
  dVar3 = LayoutParameters::GridParameters::GetBleed((GridParameters *)(this + 0x18));
  if (dVar3 != 0.0) {
    FUN_180001ff0(&local_a8);
    local_1f8 = (longlong *)0x0;
    local_1f0 = 0;
    local_1f8 = (longlong *)FUN_18005d130(0x30);
    *local_1f8 = (longlong)local_1f8;
    local_1f8[1] = (longlong)local_1f8;
    local_1f8[2] = (longlong)local_1f8;
    *(undefined2 *)(local_1f8 + 3) = 0x101;
    plVar9 = (longlong *)**(longlong **)(this + 0x90);
    cVar1 = *(char *)((longlong)plVar9 + 0x19);
    while (cVar1 == '\0') {
      if ((char)plVar9[9] == '\0') {
        iVar11 = (int)plVar9[7];
      }
      else {
        iVar11 = *(int *)((longlong)plVar9 + 0x3c);
      }
      VectorPath::VectorPath(local_148);
      local_148[0] = *(VectorPath *)(plVar9 + 0xd);
      if (local_140 != (ulonglong *)(plVar9 + 0xe)) {
        puVar2 = (undefined8 *)plVar9[0xe];
        FUN_1800014e0(local_140,puVar2,(plVar9[0xf] - (longlong)puVar2) / 0x18);
      }
      local_128 = plVar9[0x11];
      lStack_120 = plVar9[0x12];
      local_118 = plVar9[0x13];
      lStack_110 = plVar9[0x14];
      local_108 = (undefined1)plVar9[0x15];
      lVar5 = FUN_180002ef0((longlong *)&local_a8,local_148,dVar3);
      plVar8 = local_1f8;
      plVar6 = (longlong *)local_1f8[1];
      uStack_1d0 = uStack_1d0 & 0xffffffff00000000;
      cVar1 = *(char *)((longlong)plVar6 + 0x19);
      local_1d8 = plVar6;
      plVar7 = local_1f8;
      while (plVar4 = plVar6, cVar1 == '\0') {
        uStack_1d0._4_4_ = (uint)(uStack_1d0 >> 0x20);
        if ((int)plVar4[4] < iVar11) {
          uStack_1d0 = (ulonglong)uStack_1d0._4_4_ << 0x20;
          plVar6 = (longlong *)plVar4[2];
        }
        else {
          uStack_1d0 = CONCAT44(uStack_1d0._4_4_,1);
          plVar6 = (longlong *)*plVar4;
          plVar7 = plVar4;
        }
        cVar1 = *(char *)((longlong)plVar6 + 0x19);
        local_1d8 = plVar4;
      }
      if ((*(char *)((longlong)plVar7 + 0x19) != '\0') || (iVar11 < (int)plVar7[4])) {
        if (local_1f0 == 0x555555555555555) {
                    /* WARNING: Subroutine does not return */
          FUN_180004740();
        }
        local_1a8 = &local_1f8;
        local_1a0 = 0;
        plVar6 = (longlong *)FUN_18005d130(0x30);
        *(int *)(plVar6 + 4) = iVar11;
        plVar6[5] = 0;
        *plVar6 = (longlong)plVar8;
        plVar6[1] = (longlong)plVar8;
        plVar6[2] = (longlong)plVar8;
        *(undefined2 *)(plVar6 + 3) = 0;
        local_1a0 = 0;
        plVar7 = FUN_1800044c0((longlong *)&local_1f8,(longlong *)&local_1d8,plVar6);
      }
      plVar7[5] = lVar5;
      VectorPath::~VectorPath(local_148);
      plVar6 = (longlong *)plVar9[2];
      if (*(char *)((longlong)plVar6 + 0x19) == '\0') {
        cVar1 = *(char *)(*plVar6 + 0x19);
        plVar9 = plVar6;
        plVar6 = (longlong *)*plVar6;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar6 + 0x19);
          plVar9 = plVar6;
          plVar6 = (longlong *)*plVar6;
        }
      }
      else {
        cVar1 = *(char *)(plVar9[1] + 0x19);
        plVar7 = (longlong *)plVar9[1];
        plVar6 = plVar9;
        while ((plVar9 = plVar7, cVar1 == '\0' && (plVar6 == (longlong *)plVar9[2]))) {
          cVar1 = *(char *)(plVar9[1] + 0x19);
          plVar7 = (longlong *)plVar9[1];
          plVar6 = plVar9;
        }
      }
      cVar1 = *(char *)((longlong)plVar9 + 0x19);
    }
    FUN_180002fa0((longlong *)&local_a8);
    plVar9 = (longlong *)**(longlong **)(this + 0x90);
    cVar1 = *(char *)((longlong)plVar9 + 0x19);
    plVar6 = local_1f8;
    while (local_1f8 = plVar6, cVar1 == '\0') {
      if ((char)plVar9[9] == '\0') {
        iVar11 = (int)plVar9[7];
      }
      else {
        iVar11 = *(int *)((longlong)plVar9 + 0x3c);
      }
      plVar7 = (longlong *)plVar6[1];
      uStack_1d0 = uStack_1d0 & 0xffffffff00000000;
      cVar1 = *(char *)((longlong)plVar7 + 0x19);
      local_1d8 = plVar7;
      plVar8 = plVar6;
      while (plVar4 = plVar7, cVar1 == '\0') {
        uStack_1d0._4_4_ = (uint)(uStack_1d0 >> 0x20);
        if ((int)plVar4[4] < iVar11) {
          uStack_1d0 = (ulonglong)uStack_1d0._4_4_ << 0x20;
          plVar7 = (longlong *)plVar4[2];
        }
        else {
          uStack_1d0 = CONCAT44(uStack_1d0._4_4_,1);
          plVar7 = (longlong *)*plVar4;
          plVar8 = plVar4;
        }
        cVar1 = *(char *)((longlong)plVar7 + 0x19);
        local_1d8 = plVar4;
      }
      if ((*(char *)((longlong)plVar8 + 0x19) != '\0') || (iVar11 < (int)plVar8[4])) {
        if (local_1f0 == 0x555555555555555) {
                    /* WARNING: Subroutine does not return */
          FUN_180004740();
        }
        local_1a8 = &local_1f8;
        local_1a0 = 0;
        plVar7 = (longlong *)FUN_18005d130(0x30);
        *(int *)(plVar7 + 4) = iVar11;
        plVar7[5] = 0;
        *plVar7 = (longlong)plVar6;
        plVar7[1] = (longlong)plVar6;
        plVar7[2] = (longlong)plVar6;
        *(undefined2 *)(plVar7 + 3) = 0;
        local_1a0 = 0;
        plVar8 = FUN_1800044c0((longlong *)&local_1f8,(longlong *)&local_1d8,plVar7);
      }
      FUN_180003d70((longlong)&local_a8,local_f8,plVar8[5]);
      *(VectorPath *)(plVar9 + 0x16) = local_f8[0];
      if ((undefined8 **)(plVar9 + 0x17) != &local_f0) {
        FUN_1800014e0((ulonglong *)(plVar9 + 0x17),local_f0,(local_e8 - (longlong)local_f0) / 0x18);
      }
      plVar9[0x1a] = local_d8;
      plVar9[0x1b] = lStack_d0;
      plVar9[0x1c] = local_c8;
      plVar9[0x1d] = lStack_c0;
      *(undefined1 *)(plVar9 + 0x1e) = local_b8;
      VectorPath::~VectorPath(local_f8);
      plVar6 = (longlong *)plVar9[2];
      if (*(char *)((longlong)plVar6 + 0x19) == '\0') {
        cVar1 = *(char *)(*plVar6 + 0x19);
        plVar9 = plVar6;
        plVar6 = (longlong *)*plVar6;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar6 + 0x19);
          plVar9 = plVar6;
          plVar6 = (longlong *)*plVar6;
        }
      }
      else {
        cVar1 = *(char *)(plVar9[1] + 0x19);
        plVar7 = (longlong *)plVar9[1];
        plVar6 = plVar9;
        while ((plVar9 = plVar7, cVar1 == '\0' && (plVar6 == (longlong *)plVar9[2]))) {
          cVar1 = *(char *)(plVar9[1] + 0x19);
          plVar7 = (longlong *)plVar9[1];
          plVar6 = plVar9;
        }
      }
      plVar6 = local_1f8;
      cVar1 = *(char *)((longlong)plVar9 + 0x19);
    }
    plVar9 = (longlong *)plVar6[1];
    if (*(char *)((longlong)plVar9 + 0x19) == '\0') {
      do {
        FUN_180007860(&local_1f8,&local_1f8,(longlong *)plVar9[2]);
        plVar6 = (longlong *)*plVar9;
        free(plVar9);
        plVar9 = plVar6;
      } while (*(char *)((longlong)plVar6 + 0x19) == '\0');
    }
    free(local_1f8);
    if (local_80 != 0) {
      if (((local_80 & 1) == 0) && (*(code **)(local_80 & 0xfffffffffffffffe) != (code *)0x0)) {
        (**(code **)(local_80 & 0xfffffffffffffffe))(local_78,local_78,2);
      }
      local_80 = 0;
    }
    FUN_180001c80(local_90,local_90,*(longlong **)((longlong)local_90[0] + 8));
    free(local_90[0]);
    if (local_a8 != (VectorPath *)0x0) {
      pVVar10 = local_a8;
      if (local_a8 != local_a0) {
        do {
          VectorPath::~VectorPath(pVVar10);
          pVVar10 = pVVar10 + 0x50;
        } while (pVVar10 != local_a0);
      }
      pVVar10 = local_a8;
      if ((0xfff < (ulonglong)(((local_98 - (longlong)local_a8) / 0x50) * 0x50)) &&
         (pVVar10 = *(VectorPath **)(local_a8 + -8),
         (VectorPath *)0x1f < local_a8 + (-8 - (longlong)pVVar10))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pVVar10);
    }
  }
  return false;
}


```
