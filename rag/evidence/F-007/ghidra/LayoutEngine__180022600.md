---
modulo: LayoutEngine.dll
versao: 24.03.10017
funcao: 180022600
nome: GenerateBleedLayout
assinatura: vector<LayoutEngine::PlacedPath,std::allocator<LayoutEngine::PlacedPath>_> GenerateBleedLayout(ManualLayoutEngine * this, vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_> * param_1, vector<double,std::allocator<double>_> * param_2)
parametros: 3
retorno: vector<LayoutEngine::PlacedPath,std::allocator<LayoutEngine::PlacedPath>_>
confianca: alta
---

## Callers (xrefs de entrada)
- 180071820 -> unknown (DATA)
- 18007f4a0 -> unknown (DATA)
- Entry Point -> unknown (EXTERNAL)

## Callees (xrefs de saida)
- 180022180 FUN_180022180
- 180004800 FUN_180004800
- 180002520 FUN_180002520
- 180003f90 FUN_180003f90
- EXTERNAL:0000001b Guard
- 180009840 ~PlacedPath
- EXTERNAL:000000a4 operator<<
- EXTERNAL:0000001d HasLevel
- 18005d130 FUN_18005d130
- EXTERNAL:000000c7 operator<<
- EXTERNAL:000000f3 _invalid_parameter_noinfo_noreturn
- 180002fa0 FUN_180002fa0
- 18002eb20 IsEmpty
- 1800049e0 deallocate
- 18002e8f0 GetBoundingBox
- 180007860 FUN_180007860
- 180004740 FUN_180004740
- 180023250 FUN_180023250
- 180022460 ManualLayoutEngine
- 1800220c0 FUN_1800220c0
- 18002e120 ~VectorPath
- 180002ef0 FUN_180002ef0
- 18000c160 GetOneUpHandle
- 18005d370 __security_check_cookie
- 1800044c0 FUN_1800044c0
- 180003d70 FUN_180003d70
- EXTERNAL:0000001c ~Guard
- 1800020e0 VectorPath
- EXTERNAL:0000001e IncreaseIndentation
- 1800016f0 FUN_1800016f0
- 180001c80 FUN_180001c80
- 180039350 PlacedPath
- 180001280 FUN_180001280
- 1800014e0 FUN_1800014e0
- 18005d16c free
- 1800223f0 FUN_1800223f0
- EXTERNAL:0000001f DecreaseIndentation
- 180001ff0 FUN_180001ff0

## Strings referenciadas
- 18007c380 : 0x2b992ddfa232
- 180063bb8 : bleedgenerator.layoutengine
- 1800633f0 : 000786de
- 180064820 : class std::vector<class LayoutEngine::PlacedPath,class std::allocator<class LayoutEngine::PlacedPath> > __cdecl LayoutEngine::ManualLayoutEngine::GenerateBleedLayout(const class std::vector<class LayoutEngine::PlacedPath,class std::allocator<class LayoutEngine::PlacedPath> > &,const class std::vector<double,class std::allocator<double> > &)
- 1800633e0 : 000786a6
- 180063b48 : 0x3e
- 1800634b0 : 00079fd2
- 180063498 : 00079ef6
- 1800633f8 : 0007873e
- 1800633e8 : 000786c2
- 180063878 : 0007acb4
- 1800635b0 : 0007a826
- 180064978 :  masks added
- 180063400 : 00078764
- 180063b4c : 0x3c

## Pseudocodigo (Ghidra Decompiler)
```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: class std::vector<class LayoutEngine::PlacedPath,class std::allocator<class
   LayoutEngine::PlacedPath> > __cdecl LayoutEngine::ManualLayoutEngine::GenerateBleedLayout(class
   std::vector<class LayoutEngine::PlacedPath,class std::allocator<class LayoutEngine::PlacedPath> >
   const & __ptr64,class std::vector<double,class std::allocator<double> > const & __ptr64) __ptr64
    */

vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_> *
__thiscall
LayoutEngine::ManualLayoutEngine::GenerateBleedLayout
          (ManualLayoutEngine *this,
          vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_>
          *param_1,vector<double,std::allocator<double>_> *param_2)

{
  undefined8 uVar1;
  vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_>
  *pvVar2;
  longlong *plVar3;
  longlong *plVar4;
  PlacedPath *pPVar5;
  PlacedPath *pPVar6;
  bool bVar7;
  char cVar8;
  basic_ostream<char,std::char_traits<char>_> *pbVar9;
  ulonglong *puVar10;
  double *pdVar11;
  undefined8 *puVar12;
  Rectangle *pRVar13;
  longlong lVar14;
  longlong *plVar15;
  longlong *plVar16;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar17;
  __int64 _Var18;
  VectorPath *pVVar19;
  OrderedStation *this_00;
  PlacedPath *pPVar20;
  GridStationLayout *this_01;
  int iVar21;
  longlong *in_R9;
  undefined1 auStack_1e8 [32];
  Guard local_1c8 [8];
  longlong *local_1c0;
  longlong local_1b8;
  PlacedPath *local_1b0;
  PlacedPath *pPStack_1a8;
  PlacedPath *local_1a0;
  undefined4 local_198;
  vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_>
  *local_190;
  vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_>
  *local_188;
  undefined8 local_180;
  char local_178;
  char *local_170;
  Rectangle local_168 [8];
  Rectangle local_160 [24];
  undefined8 local_148;
  undefined8 uStack_140;
  undefined8 local_138;
  undefined8 uStack_130;
  Rectangle local_128;
  vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_>
  *local_118;
  VectorPath *local_108;
  VectorPath *local_100;
  longlong local_f8;
  void *local_f0 [2];
  ulonglong local_e0;
  undefined1 local_d8 [32];
  longlong *local_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  ulonglong uStack_a0;
  ulonglong local_68;
  
                    /* 0x22600  123
                       ?GenerateBleedLayout@ManualLayoutEngine@LayoutEngine@@QEAA?AV?$vector@VPlacedPath@LayoutEngine@@V?$allocator@VPlacedPath@LayoutEngine@@@std@@@std@@AEBV34@AEBV?$vector@NV?$allocator@N@std@@@4@@Z
                        */
  local_68 = DAT_18007c380 ^ (ulonglong)auStack_1e8;
  iVar21 = 0;
  local_198 = 0;
  local_b8 = (longlong *)0x0;
  uStack_b0 = 0;
  local_a8 = 0;
  uStack_a0 = 0;
  local_190 = param_1;
  local_118 = param_1;
  FUN_1800016f0(&local_b8,"bleedgenerator.layoutengine",0x1b);
  local_178 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                &local_b8,0x14);
  local_170 = 
  "class std::vector<class LayoutEngine::PlacedPath,class std::allocator<class LayoutEngine::PlacedPath> > __cdecl LayoutEngine::ManualLayoutEngine::GenerateBleedLayout(const class std::vector<class LayoutEngine::PlacedPath,class std::allocator<class LayoutEngine::PlacedPath> > &,const class std::vector<double,class std::allocator<double> > &)"
  ;
  if ((bool)local_178) {
    Logging::Guard::Guard(local_1c8);
    pbVar9 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,"> ");
    pbVar9 = FUN_180001280(pbVar9,
                           "class std::vector<class LayoutEngine::PlacedPath,class std::allocator<class LayoutEngine::PlacedPath> > __cdecl LayoutEngine::ManualLayoutEngine::GenerateBleedLayout(const class std::vector<class LayoutEngine::PlacedPath,class std::allocator<class LayoutEngine::PlacedPath> > &,const class std::vector<double,class std::allocator<double> > &)"
                          );
    std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar9,FUN_180001dd0);
    Logging::IncreaseIndentation();
    Logging::Guard::~Guard(local_1c8);
  }
  FUN_180002520((longlong *)&local_b8);
  FUN_180001ff0(&local_108);
  puVar10 = (ulonglong *)ManualLayoutEngine((ManualLayoutEngine *)&local_b8,this);
  FUN_180003f90((longlong)&local_108,puVar10);
  local_1b0 = (PlacedPath *)0x0;
  pPStack_1a8 = (PlacedPath *)0x0;
  local_1a0 = (PlacedPath *)0x0;
  local_1c0 = (longlong *)0x0;
  local_1b8 = 0;
  local_1c0 = (longlong *)FUN_18005d130(0x30);
  *local_1c0 = (longlong)local_1c0;
  local_1c0[1] = (longlong)local_1c0;
  local_1c0[2] = (longlong)local_1c0;
  *(undefined2 *)(local_1c0 + 3) = 0x101;
  pdVar11 = (double *)*in_R9;
  do {
    if (pdVar11 == (double *)in_R9[1]) {
      *(undefined8 *)param_1 = 0;
      *(undefined8 *)(param_1 + 8) = 0;
      *(undefined8 *)(param_1 + 0x10) = 0;
      pvVar2 = (vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_>
                *)((*(longlong *)(param_2 + 8) - *(longlong *)param_2) / 0x50);
      if (pvVar2 != (vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_>
                     *)0x0) {
        if ((vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_>
             *)0x333333333333333 < pvVar2) {
                    /* WARNING: Subroutine does not return */
          FUN_180004800();
        }
        local_190 = pvVar2;
        puVar12 = (undefined8 *)FUN_1800220c0(param_1,(ulonglong *)&local_190);
        *(undefined8 **)param_1 = puVar12;
        *(undefined8 **)(param_1 + 8) = puVar12;
        *(undefined8 **)(param_1 + 0x10) = puVar12 + (longlong)pvVar2 * 10;
        local_188 = param_1;
        puVar12 = FUN_1800223f0(*(undefined8 **)param_2,*(undefined8 **)(param_2 + 8),puVar12);
        *(undefined8 **)(param_1 + 8) = puVar12;
      }
      local_198 = 1;
      cVar8 = *(char *)(local_1c0[1] + 0x19);
      plVar15 = (longlong *)local_1c0[1];
      while (cVar8 == '\0') {
        FUN_180007860(&local_1c0,&local_1c0,(longlong *)plVar15[2]);
        plVar16 = (longlong *)*plVar15;
        free(plVar15);
        plVar15 = plVar16;
        cVar8 = *(char *)((longlong)plVar16 + 0x19);
      }
      free(local_1c0);
      pPVar5 = pPStack_1a8;
      pPVar20 = local_1b0;
      if (local_1b0 != (PlacedPath *)0x0) {
        for (; pPVar20 != pPVar5; pPVar20 = pPVar20 + 0x50) {
          PlacedPath::~PlacedPath(pPVar20);
        }
        deallocate(&local_1b0,local_1b0,((longlong)local_1a0 - (longlong)local_1b0) / 0x50);
        local_1b0 = (PlacedPath *)0x0;
        pPStack_1a8 = (PlacedPath *)0x0;
        local_1a0 = (PlacedPath *)0x0;
      }
      if (local_e0 != 0) {
        if (((local_e0 & 1) == 0) && (*(code **)(local_e0 & 0xfffffffffffffffe) != (code *)0x0)) {
          (**(code **)(local_e0 & 0xfffffffffffffffe))(local_d8,local_d8,2);
        }
        local_e0 = 0;
      }
      FUN_180001c80(local_f0,local_f0,*(longlong **)((longlong)local_f0[0] + 8));
      free(local_f0[0]);
      if (local_108 != (VectorPath *)0x0) {
        pVVar19 = local_108;
        if (local_108 != local_100) {
          do {
            VectorPath::~VectorPath(pVVar19);
            pVVar19 = pVVar19 + 0x50;
          } while (pVVar19 != local_100);
        }
        pVVar19 = local_108;
        if ((0xfff < (ulonglong)(((local_f8 - (longlong)local_108) / 0x50) * 0x50)) &&
           (pVVar19 = *(VectorPath **)(local_108 + -8),
           (VectorPath *)0x1f < local_108 + (-8 - (longlong)pVVar19))) {
LAB_180022988:
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pVVar19);
        local_108 = (VectorPath *)0x0;
        local_100 = (VectorPath *)0x0;
        local_f8 = 0;
      }
LAB_180023110:
      if (local_178 != '\0') {
        Logging::Guard::Guard(local_1c8);
        Logging::DecreaseIndentation();
        pbVar9 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,"< ");
        pbVar9 = FUN_180001280(pbVar9,
                               "class std::vector<class LayoutEngine::PlacedPath,class std::allocator<class LayoutEngine::PlacedPath> > __cdecl LayoutEngine::ManualLayoutEngine::GenerateBleedLayout(const class std::vector<class LayoutEngine::PlacedPath,class std::allocator<class LayoutEngine::PlacedPath> > &,const class std::vector<double,class std::allocator<double> > &)"
                              );
        std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar9,FUN_180001dd0);
        Logging::Guard::~Guard(local_1c8);
      }
      return param_1;
    }
    if (*pdVar11 != 0.0) {
      this_00 = *(OrderedStation **)param_2;
      if (this_00 != *(OrderedStation **)(param_2 + 8)) {
        do {
          uVar1 = *(undefined8 *)(*in_R9 + (longlong)iVar21 * 8);
          pRVar13 = OrderedStation::GetBoundingBox(this_00);
          lVar14 = FUN_180002ef0((longlong *)&local_108,(VectorPath *)pRVar13,uVar1);
          plVar4 = local_1c0;
          plVar15 = (longlong *)local_1c0[1];
          uStack_b0 = uStack_b0 & 0xffffffff00000000;
          cVar8 = *(char *)((longlong)plVar15 + 0x19);
          local_b8 = plVar15;
          plVar16 = local_1c0;
          while (plVar3 = plVar15, cVar8 == '\0') {
            uStack_b0._4_4_ = (uint)(uStack_b0 >> 0x20);
            if ((int)plVar3[4] < iVar21) {
              uStack_b0 = (ulonglong)uStack_b0._4_4_ << 0x20;
              plVar15 = (longlong *)plVar3[2];
            }
            else {
              uStack_b0 = CONCAT44(uStack_b0._4_4_,1);
              plVar15 = (longlong *)*plVar3;
              plVar16 = plVar3;
            }
            cVar8 = *(char *)((longlong)plVar15 + 0x19);
            local_b8 = plVar3;
          }
          if ((*(char *)((longlong)plVar16 + 0x19) != '\0') || (iVar21 < (int)plVar16[4])) {
            if (local_1b8 == 0x555555555555555) {
                    /* WARNING: Subroutine does not return */
              FUN_180004740();
            }
            local_188 = (vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_>
                         *)&local_1c0;
            local_180 = 0;
            plVar15 = (longlong *)FUN_18005d130(0x30);
            *(int *)(plVar15 + 4) = iVar21;
            plVar15[5] = 0;
            *plVar15 = (longlong)plVar4;
            plVar15[1] = (longlong)plVar4;
            plVar15[2] = (longlong)plVar4;
            *(undefined2 *)(plVar15 + 3) = 0;
            local_180 = 0;
            plVar16 = FUN_1800044c0((longlong *)&local_1c0,(longlong *)&local_b8,plVar15);
          }
          plVar16[5] = lVar14;
          this_00 = this_00 + 0x50;
          iVar21 = iVar21 + 1;
        } while (this_00 != *(OrderedStation **)(param_2 + 8));
        param_1 = local_190;
      }
      local_b8 = (longlong *)0x0;
      uStack_b0 = 0;
      local_a8 = 0;
      uStack_a0 = 0xf;
      local_b8 = (longlong *)FUN_18005d130(0x20);
      local_a8 = 0x1b;
      uStack_a0 = 0x1f;
      *local_b8 = 0x6e65676465656c62;
      local_b8[1] = 0x6c2e726f74617265;
      local_b8[2] = 0x676e6574756f7961;
      *(undefined2 *)(local_b8 + 3) = 0x6e69;
      *(char *)((longlong)local_b8 + 0x1a) = 'e';
      *(char *)((longlong)local_b8 + 0x1b) = '\0';
      bVar7 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                &local_b8,0x14);
      if (0xf < uStack_a0) {
        plVar15 = local_b8;
        if ((0xfff < uStack_a0 + 1) &&
           (plVar15 = (longlong *)local_b8[-1],
           (char *)0x1f < (char *)((longlong)local_b8 + (-8 - (longlong)plVar15)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(plVar15);
      }
      if (bVar7) {
        Logging::Guard::Guard(local_1c8);
        pbVar17 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            ((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                             (*(longlong *)(param_2 + 8) - *(longlong *)param_2) / 0x50);
        pbVar9 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)pbVar17," masks added"
                              );
        std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar9,FUN_180001dd0);
        Logging::Guard::~Guard(local_1c8);
      }
      FUN_180002fa0((longlong *)&local_108);
      if (*(ulonglong *)this != 0) {
        cVar8 = (**(code **)((*(ulonglong *)this & 0xfffffffffffffffe) + 8))(this + 8);
        pPVar6 = local_1a0;
        pPVar5 = pPStack_1a8;
        pPVar20 = local_1b0;
        if (cVar8 != '\0') {
          local_1a0 = (PlacedPath *)0x0;
          pPStack_1a8 = (PlacedPath *)0x0;
          local_1b0 = (PlacedPath *)0x0;
          *(PlacedPath **)param_1 = pPVar20;
          *(PlacedPath **)(param_1 + 8) = pPVar5;
          *(PlacedPath **)(param_1 + 0x10) = pPVar6;
          local_198 = 1;
          cVar8 = *(char *)(local_1c0[1] + 0x19);
          plVar15 = (longlong *)local_1c0[1];
          while (cVar8 == '\0') {
            FUN_180007860(&local_1c0,&local_1c0,(longlong *)plVar15[2]);
            plVar16 = (longlong *)*plVar15;
            free(plVar15);
            plVar15 = plVar16;
            cVar8 = *(char *)((longlong)plVar16 + 0x19);
          }
          free(local_1c0);
          pPVar5 = pPStack_1a8;
          pPVar20 = local_1b0;
          if (local_1b0 != (PlacedPath *)0x0) {
            for (; pPVar20 != pPVar5; pPVar20 = pPVar20 + 0x50) {
              PlacedPath::~PlacedPath(pPVar20);
            }
            pPVar20 = local_1b0;
            if ((0xfff < (ulonglong)((((longlong)local_1a0 - (longlong)local_1b0) / 0x50) * 0x50))
               && (pPVar20 = *(PlacedPath **)(local_1b0 + -8),
                  (PlacedPath *)0x1f < local_1b0 + (-8 - (longlong)pPVar20))) {
                    /* WARNING: Subroutine does not return */
              _invalid_parameter_noinfo_noreturn();
            }
            free(pPVar20);
            local_1b0 = (PlacedPath *)0x0;
            pPStack_1a8 = (PlacedPath *)0x0;
            local_1a0 = (PlacedPath *)0x0;
          }
          if (local_e0 != 0) {
            if (((local_e0 & 1) == 0) && (*(code **)(local_e0 & 0xfffffffffffffffe) != (code *)0x0))
            {
              (**(code **)(local_e0 & 0xfffffffffffffffe))(local_d8,local_d8,2);
            }
            local_e0 = 0;
          }
          FUN_180001c80(local_f0,local_f0,*(longlong **)((longlong)local_f0[0] + 8));
          free(local_f0[0]);
          if (local_108 != (VectorPath *)0x0) {
            pVVar19 = local_108;
            if (local_108 != local_100) {
              do {
                VectorPath::~VectorPath(pVVar19);
                pVVar19 = pVVar19 + 0x50;
              } while (pVVar19 != local_100);
            }
            pVVar19 = local_108;
            if (((ulonglong)(((local_f8 - (longlong)local_108) / 0x50) * 0x50) < 0x1000) ||
               (pVVar19 = *(VectorPath **)(local_108 + -8),
               local_108 + (-8 - (longlong)pVVar19) < (VectorPath *)&DAT_00000020)) {
              free(pVVar19);
              local_108 = (VectorPath *)0x0;
              local_100 = (VectorPath *)0x0;
              local_f8 = 0;
              goto LAB_180023110;
            }
            goto LAB_180022988;
          }
          goto LAB_180023110;
        }
      }
      iVar21 = 0;
      this_01 = *(GridStationLayout **)param_2;
      if (this_01 != *(GridStationLayout **)(param_2 + 8)) {
        do {
          plVar4 = local_1c0;
          plVar15 = (longlong *)local_1c0[1];
          uStack_b0 = uStack_b0 & 0xffffffff00000000;
          cVar8 = *(char *)((longlong)plVar15 + 0x19);
          local_b8 = plVar15;
          plVar16 = local_1c0;
          while (plVar3 = plVar15, cVar8 == '\0') {
            uStack_b0._4_4_ = (uint)(uStack_b0 >> 0x20);
            if ((int)plVar3[4] < iVar21) {
              uStack_b0 = (ulonglong)uStack_b0._4_4_ << 0x20;
              plVar15 = (longlong *)plVar3[2];
            }
            else {
              uStack_b0 = CONCAT44(uStack_b0._4_4_,1);
              plVar15 = (longlong *)*plVar3;
              plVar16 = plVar3;
            }
            cVar8 = *(char *)((longlong)plVar15 + 0x19);
            local_b8 = plVar3;
          }
          if ((*(char *)((longlong)plVar16 + 0x19) != '\0') || (iVar21 < (int)plVar16[4])) {
            if (local_1b8 == 0x555555555555555) {
                    /* WARNING: Subroutine does not return */
              FUN_180004740();
            }
            local_188 = (vector<class_LayoutEngine::PlacedPath,class_std::allocator<class_LayoutEngine::PlacedPath>_>
                         *)&local_1c0;
            local_180 = 0;
            plVar15 = (longlong *)FUN_18005d130(0x30);
            *(int *)(plVar15 + 4) = iVar21;
            plVar15[5] = 0;
            *plVar15 = (longlong)plVar4;
            plVar15[1] = (longlong)plVar4;
            plVar15[2] = (longlong)plVar4;
            *(undefined2 *)(plVar15 + 3) = 0;
            local_180 = 0;
            plVar16 = FUN_1800044c0((longlong *)&local_1c0,(longlong *)&local_b8,plVar15);
          }
          FUN_180003d70((longlong)&local_108,(VectorPath *)local_168,plVar16[5]);
          bVar7 = VectorPath::IsEmpty((VectorPath *)local_168);
          if (bVar7) {
            pRVar13 = OrderedStation::GetBoundingBox
                                ((OrderedStation *)((longlong)iVar21 * 0x50 + *(longlong *)param_2))
            ;
            local_168[0] = *pRVar13;
            if (local_160 != pRVar13 + 8) {
              puVar12 = *(undefined8 **)(pRVar13 + 8);
              FUN_1800014e0((ulonglong *)local_160,puVar12,
                            (*(longlong *)(pRVar13 + 0x10) - (longlong)puVar12) / 0x18);
            }
            local_148 = *(undefined8 *)(pRVar13 + 0x20);
            uStack_140 = *(undefined8 *)(pRVar13 + 0x28);
            local_138 = *(undefined8 *)(pRVar13 + 0x30);
            uStack_130 = *(undefined8 *)(pRVar13 + 0x38);
            local_128 = pRVar13[0x40];
          }
          _Var18 = GridStationLayout::GetOneUpHandle(this_01);
          puVar12 = (undefined8 *)
                    PlacedPath::PlacedPath((PlacedPath *)&local_b8,_Var18,(VectorPath *)local_168);
          if (pPStack_1a8 == local_1a0) {
            FUN_180022180((longlong *)&local_1b0,(undefined8 *)pPStack_1a8,puVar12);
          }
          else {
            *(undefined8 *)pPStack_1a8 = *puVar12;
            VectorPath::VectorPath((VectorPath *)(pPStack_1a8 + 8),(VectorPath *)(puVar12 + 1));
            pPStack_1a8 = pPStack_1a8 + 0x50;
          }
          PlacedPath::~PlacedPath((PlacedPath *)&local_b8);
          VectorPath::~VectorPath((VectorPath *)local_168);
          this_01 = this_01 + 0x50;
          iVar21 = iVar21 + 1;
        } while (this_01 != *(GridStationLayout **)(param_2 + 8));
        param_1 = local_190;
      }
      pPVar6 = local_1a0;
      pPVar5 = pPStack_1a8;
      pPVar20 = local_1b0;
      local_1a0 = (PlacedPath *)0x0;
      pPStack_1a8 = (PlacedPath *)0x0;
      local_1b0 = (PlacedPath *)0x0;
      *(PlacedPath **)param_1 = pPVar20;
      *(PlacedPath **)(param_1 + 8) = pPVar5;
      *(PlacedPath **)(param_1 + 0x10) = pPVar6;
      local_198 = 1;
      cVar8 = *(char *)(local_1c0[1] + 0x19);
      plVar15 = (longlong *)local_1c0[1];
      while (cVar8 == '\0') {
        FUN_180007860(&local_1c0,&local_1c0,(longlong *)plVar15[2]);
        plVar16 = (longlong *)*plVar15;
        free(plVar15);
        plVar15 = plVar16;
        cVar8 = *(char *)((longlong)plVar16 + 0x19);
      }
      free(local_1c0);
      FUN_180023250((longlong *)&local_1b0);
      if (local_e0 != 0) {
        if (((local_e0 & 1) == 0) && (*(code **)(local_e0 & 0xfffffffffffffffe) != (code *)0x0)) {
          (**(code **)(local_e0 & 0xfffffffffffffffe))(local_d8,local_d8,2);
        }
        local_e0 = 0;
      }
      FUN_180001c80(local_f0,local_f0,*(longlong **)((longlong)local_f0[0] + 8));
      free(local_f0[0]);
      if (local_108 != (VectorPath *)0x0) {
        pVVar19 = local_108;
        if (local_108 != local_100) {
          do {
            VectorPath::~VectorPath(pVVar19);
            pVVar19 = pVVar19 + 0x50;
          } while (pVVar19 != local_100);
        }
        pVVar19 = local_108;
        if (((ulonglong)(((local_f8 - (longlong)local_108) / 0x50) * 0x50) < 0x1000) ||
           (pVVar19 = *(VectorPath **)(local_108 + -8),
           local_108 + (-8 - (longlong)pVVar19) < (VectorPath *)&DAT_00000020)) {
          free(pVVar19);
          local_108 = (VectorPath *)0x0;
          local_100 = (VectorPath *)0x0;
          local_f8 = 0;
          goto LAB_180023110;
        }
        goto LAB_180022988;
      }
      goto LAB_180023110;
    }
    pdVar11 = pdVar11 + 1;
  } while( true );
}


```