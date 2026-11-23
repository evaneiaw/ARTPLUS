modulo: LayoutEngine.dll
versao: 24.03.10017.10017
funcao: 180025820
nome: ClassicFillSheet
assinatura: IntermediateSheet ClassicFillSheet(NestingSheetGenerator * this, vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> * param_1)
parametros: 2
retorno: IntermediateSheet

## Callers (xrefs de entrada)
- 180071808 -> unknown (DATA)
- 18007f6ec -> unknown (DATA)
- Entry Point -> unknown (EXTERNAL)
- 1800288cd -> GenerateClassicSolution @ 180028490 (UNCONDITIONAL_CALL)

## Callees (xrefs de saida)
- 180006af0 FUN_180006af0
- 18000f8e0 FUN_18000f8e0
- 18001bb40 FUN_18001bb40
- EXTERNAL:0000001b Guard
- EXTERNAL:000000a4 operator<<
- 18002bf60 FUN_18002bf60
- 18005d130 FUN_18005d130
- EXTERNAL:0000001d HasLevel
- EXTERNAL:000000f3 _invalid_parameter_noinfo_noreturn
- 180027830 FUN_180027830
- EXTERNAL:000000c6 operator<<
- EXTERNAL:000000b9 basic_ios<char,std::char_traits<char>_>
- EXTERNAL:000000bc ~basic_iostream<char,std::char_traits<char>_>
- 180007860 FUN_180007860
- 180025680 AddStationsToNester
- 18000fbe0 IntermediateSheet
- 18005d370 __security_check_cookie
- 18001ba80 FUN_18001ba80
- EXTERNAL:0000001c ~Guard
- 18002d570 Nest
- EXTERNAL:000000b6 ~basic_ios<char,std::char_traits<char>_>
- EXTERNAL:0000001e IncreaseIndentation
- 18005e2a6 memcmp
- 180005ae0 FUN_180005ae0
- 180024630 FUN_180024630
- EXTERNAL:000000a9 basic_streambuf<char,std::char_traits<char>_>
- 180005060 FUN_180005060
- 180040920 FUN_180040920
- 18000fb30 IntermediateSheet
- 180001280 FUN_180001280
- 18000ef50 FUN_18000ef50
- 18005d16c free
- EXTERNAL:0000001f DecreaseIndentation
- 180005d00 FUN_180005d00
- EXTERNAL:000000bb basic_iostream<char,std::char_traits<char>_>
- 180040320 FUN_180040320

## Strings referenciadas
- 18007c380 : 0x2b992ddfa232
- 1800649d0 : NestingSheetGenerator.LayoutEngine
- 1800633f0 : 000786de
- 180064f20 : class LayoutEngine::IntermediateSheet __cdecl LayoutEngine::NestingSheetGenerator::ClassicFillSheet(const class std::vector<class LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > &)
- 1800633e0 : 000786a6
- 180063b48 : 0x3e
- 1800634b0 : 00079fd2
- 180063498 : 00079ef6
- 1800633f8 : 0007873e
- 1800633e8 : 000786c2
- 180063878 : 0007acb4
- 180063dd0 : 0x0
- 180063540 : 0007a450
- 180063550 : 0007a4c8
- 180063dd4 : 0x98
- 1800634c0 : 0007a034
- 180063558 : 0007a534
- 180063528 : 0007a396
- 180063de0 : -0x8000000000000000
- 180063df0 : 0x3fe0000000000000
- 180064ec0 : NSG::GSF: Nesting with 
- 180064ed8 : NSG::GSF: Nest done: 
- 1800635a8 : 0007a7e4
- 180063400 : 00078764
- 180063b4c : 0x3c

## Pseudocodigo (Ghidra Decompiler)
```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* private: class LayoutEngine::IntermediateSheet __cdecl
   LayoutEngine::NestingSheetGenerator::ClassicFillSheet(class std::vector<class
   LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > const &
   __ptr64) __ptr64 */

IntermediateSheet * __thiscall
LayoutEngine::NestingSheetGenerator::ClassicFillSheet
          (NestingSheetGenerator *this,
          vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_>
          *param_1)

{
  ulonglong *puVar1;
  double dVar2;
  undefined8 *puVar3;
  ulonglong uVar4;
  longlong *plVar5;
  void *pvVar6;
  char cVar7;
  bool bVar8;
  int iVar9;
  nesterror_type nVar10;
  basic_ostream<char,std::char_traits<char>_> *pbVar11;
  longlong *plVar12;
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *pvVar13;
  longlong *plVar14;
  basic_ostream<char,struct_std::char_traits<char>_> *this_00;
  undefined8 *puVar15;
  char *pcVar16;
  void *pvVar17;
  undefined8 *puVar18;
  longlong *in_R8;
  ulonglong _Size;
  ulonglong uVar19;
  undefined8 *puVar20;
  undefined1 auStackY_2d8 [32];
  Guard local_2a8 [4];
  undefined4 local_2a4;
  longlong *local_2a0 [2];
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *local_290;
  NestingSheetGenerator *local_288 [2];
  NestingSheetGenerator *local_278;
  char local_270;
  char *local_268;
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *local_260;
  ulonglong local_258 [3];
  int iStack_23c;
  undefined *local_238 [2];
  undefined *local_228;
  undefined **local_220;
  basic_iostream<char,std::char_traits<char>_> local_218 [96];
  undefined8 local_1b8;
  undefined4 local_1b0;
  basic_ios<char,std::char_traits<char>_> local_1a0 [104];
  IntermediateSheet local_138 [24];
  longlong local_120 [2];
  longlong local_110 [3];
  char *local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  ulonglong local_e0;
  undefined1 local_d0;
  undefined7 uStack_cf;
  ulonglong local_c0;
  ulonglong local_b8;
  void *local_a8 [3];
  ulonglong local_90;
  IntermediateSheet local_88 [24];
  longlong local_70 [2];
  longlong local_60 [3];
  ulonglong local_48;
  
                    /* 0x25820  117
                       ?ClassicFillSheet@NestingSheetGenerator@LayoutEngine@@AEAA?AVIntermediateSheet@2@AEBV?$vector@VOrderedStation@LayoutEngine@@V?$allocator@VOrderedStation@LayoutEngine@@@std@@@std@@@Z
                        */
  local_48 = DAT_18007c380 ^ (ulonglong)auStackY_2d8;
  local_2a4 = 0;
  local_f8 = (char *)0x0;
  uStack_f0 = 0;
  local_e8 = 0;
  local_e0 = 0xf;
  local_2a0[0] = in_R8;
  local_290 = param_1;
  local_288[0] = this;
  local_260 = param_1;
  local_f8 = (char *)FUN_18005d130(0x30);
  local_e8 = 0x22;
  local_e0 = 0x2f;
  builtin_strncpy(local_f8,"NestingSheetGenerator.LayoutEngine",0x23);
  local_270 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                &local_f8,0x14);
  local_268 = 
  "class LayoutEngine::IntermediateSheet __cdecl LayoutEngine::NestingSheetGenerator::ClassicFillSheet(const class std::vector<class LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > &)"
  ;
  if ((bool)local_270) {
    Logging::Guard::Guard(local_2a8);
    pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,"> ");
    pbVar11 = FUN_180001280(pbVar11,
                            "class LayoutEngine::IntermediateSheet __cdecl LayoutEngine::NestingSheetGenerator::ClassicFillSheet(const class std::vector<class LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > &)"
                           );
    std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,FUN_180001dd0);
    Logging::IncreaseIndentation();
    Logging::Guard::~Guard(local_2a8);
  }
  if (0xf < local_e0) {
    pcVar16 = local_f8;
    if ((0xfff < local_e0 + 1) &&
       (pcVar16 = *(char **)(local_f8 + -8), (char *)0x1f < local_f8 + (-8 - (longlong)pcVar16))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pcVar16);
  }
  local_e8 = 0;
  local_e0 = 0xf;
  local_f8 = (char *)((ulonglong)local_f8 & 0xffffffffffffff00);
  local_238[0] = &DAT_180063dd0;
  local_228 = &DAT_180063dd8;
  std::basic_ios<char,std::char_traits<char>_>::basic_ios<char,std::char_traits<char>_>(local_1a0);
  local_2a4 = 2;
  std::basic_iostream<char,std::char_traits<char>_>::basic_iostream<char,std::char_traits<char>_>
            ((basic_iostream<char,std::char_traits<char>_> *)local_238,
             (basic_streambuf<char,std::char_traits<char>_> *)&local_220);
  *(undefined ***)((longlong)local_238 + (longlong)*(int *)(local_238[0] + 4)) =
       std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  *(int *)((longlong)local_238 + (longlong)*(int *)(local_238[0] + 4) + -4) =
       *(int *)(local_238[0] + 4) + -0x98;
  std::basic_streambuf<char,std::char_traits<char>_>::basic_streambuf<char,std::char_traits<char>_>
            ((basic_streambuf<char,std::char_traits<char>_> *)&local_220);
  local_220 = std::basic_stringbuf<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  local_1b8 = 0;
  local_1b0 = 0;
  plVar12 = FUN_18002bf60((longlong *)&local_f8,in_R8);
  puVar1 = (ulonglong *)(plVar12 + 2);
  if (0xf < (ulonglong)plVar12[3]) {
    plVar12 = (longlong *)*plVar12;
  }
  FUN_180005060((basic_ostream<char,std::char_traits<char>_> *)&local_228,(char *)plVar12,*puVar1);
  if (0xf < local_e0) {
    pcVar16 = local_f8;
    if ((0xfff < local_e0 + 1) &&
       (pcVar16 = *(char **)(local_f8 + -8), (char *)0x1f < local_f8 + (-8 - (longlong)pcVar16))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pcVar16);
  }
  FUN_180006af0((longlong)local_238,(longlong *)&local_d0);
  uVar19 = local_b8;
  local_278 = this + 0x50;
  puVar3 = *(undefined8 **)local_278;
  plVar12 = (longlong *)CONCAT71(uStack_cf,local_d0);
  puVar18 = (undefined8 *)puVar3[1];
  puVar20 = puVar3;
  if (*(char *)((longlong)puVar3[1] + 0x19) == '\0') {
    do {
      puVar15 = puVar18 + 4;
      plVar14 = (longlong *)&local_d0;
      if (0xf < uVar19) {
        plVar14 = plVar12;
      }
      uVar4 = puVar18[6];
      if (0xf < (ulonglong)puVar18[7]) {
        puVar15 = (undefined8 *)*puVar15;
      }
      _Size = uVar4;
      if (local_c0 < uVar4) {
        _Size = local_c0;
      }
      iVar9 = memcmp(puVar15,plVar14,_Size);
      if (iVar9 == 0) {
        if (uVar4 < local_c0) {
          cVar7 = -1;
          goto LAB_180025b18;
        }
        if (local_c0 < uVar4) goto LAB_180025b16;
LAB_180025b22:
        puVar15 = (undefined8 *)*puVar18;
        puVar20 = puVar18;
      }
      else {
        if (iVar9 < 0) {
          cVar7 = -1;
        }
        else {
LAB_180025b16:
          cVar7 = '\x01';
        }
LAB_180025b18:
        if (-1 < cVar7) goto LAB_180025b22;
        puVar15 = (undefined8 *)puVar18[2];
      }
      puVar18 = puVar15;
    } while (*(char *)((longlong)puVar15 + 0x19) == '\0');
    this = local_288[0];
  }
  if (*(char *)((longlong)puVar20 + 0x19) == '\0') {
    puVar18 = puVar20 + 4;
    uVar4 = puVar20[6];
    if (0xf < (ulonglong)puVar20[7]) {
      puVar18 = (undefined8 *)*puVar18;
    }
    plVar14 = (longlong *)&local_d0;
    if (0xf < uVar19) {
      plVar14 = plVar12;
    }
    uVar19 = local_c0;
    if (uVar4 < local_c0) {
      uVar19 = uVar4;
    }
    iVar9 = memcmp(plVar14,puVar18,uVar19);
    pvVar13 = local_290;
    if (iVar9 == 0) {
      if (local_c0 < uVar4) {
        cVar7 = -1;
        goto LAB_180025b85;
      }
      if (uVar4 < local_c0) goto LAB_180025b83;
    }
    else {
      if (iVar9 < 0) {
        cVar7 = -1;
      }
      else {
LAB_180025b83:
        cVar7 = '\x01';
      }
LAB_180025b85:
      if (cVar7 < '\0') goto LAB_180025c59;
    }
    if (puVar20 != puVar3) {
      *(longlong *)(this + 0x60) = *(longlong *)(this + 0x60) + 1;
      IntermediateSheet::IntermediateSheet
                ((IntermediateSheet *)local_290,(IntermediateSheet *)(puVar20 + 8));
      local_2a4 = 3;
      if (0xf < local_b8) {
        pvVar6 = (void *)CONCAT71(uStack_cf,local_d0);
        pvVar17 = pvVar6;
        if ((0xfff < local_b8 + 1) &&
           (pvVar17 = *(void **)((longlong)pvVar6 + -8),
           0x1f < (ulonglong)((longlong)pvVar6 + (-8 - (longlong)pvVar17)))) goto LAB_1800260fe;
        free(pvVar17);
      }
      local_c0 = 0;
      local_b8 = 0xf;
      local_d0 = 0;
      *(undefined ***)((longlong)local_238 + (longlong)*(int *)(local_238[0] + 4)) =
           std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
      *(int *)((longlong)local_238 + (longlong)*(int *)(local_238[0] + 4) + -4) =
           *(int *)(local_238[0] + 4) + -0x98;
      FUN_180005d00((basic_streambuf<char,std::char_traits<char>_> *)&local_220);
      std::basic_iostream<char,std::char_traits<char>_>::
      ~basic_iostream<char,std::char_traits<char>_>(local_218);
      std::basic_ios<char,std::char_traits<char>_>::~basic_ios<char,std::char_traits<char>_>
                (local_1a0);
      goto LAB_180026167;
    }
  }
LAB_180025c59:
  dVar2 = *(double *)(this + 0x18);
  pvVar13 = (vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *)
            FUN_180040920(-dVar2 * 0.5,-dVar2 * 0.5,dVar2 + *(double *)(this + 0x10),
                          dVar2 + *(double *)(this + 8),0);
  local_f8 = (char *)0x0;
  uStack_f0 = 0;
  local_e8 = 0;
  local_e0 = 0xf;
  local_f8 = (char *)FUN_18005d130(0x30);
  local_e8 = 0x22;
  local_e0 = 0x2f;
  builtin_strncpy(local_f8,"NestingSheetGenerator.LayoutEngine",0x23);
  bVar8 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                            &local_f8,0xc);
  if (0xf < local_e0) {
    pcVar16 = local_f8;
    if ((0xfff < local_e0 + 1) &&
       (pcVar16 = *(char **)(local_f8 + -8), (char *)0x1f < local_f8 + (-8 - (longlong)pcVar16))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pcVar16);
  }
  if (bVar8) {
    Logging::Guard::Guard(local_2a8);
    pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                            "NSG::GSF: Nesting with ");
    plVar12 = local_2a0[0];
    plVar14 = FUN_18002bf60((longlong *)&local_f8,local_2a0[0]);
    puVar1 = (ulonglong *)(plVar14 + 2);
    if (0xf < (ulonglong)plVar14[3]) {
      plVar14 = (longlong *)*plVar14;
    }
    pbVar11 = FUN_180005060(pbVar11,(char *)plVar14,*puVar1);
    std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,FUN_180001dd0);
    if (0xf < local_e0) {
      pcVar16 = local_f8;
      if ((0xfff < local_e0 + 1) &&
         (pcVar16 = *(char **)(local_f8 + -8), (char *)0x1f < local_f8 + (-8 - (longlong)pcVar16)))
      {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pcVar16);
    }
    Logging::Guard::~Guard(local_2a8);
  }
  else {
    plVar12 = local_2a0[0];
  }
  AddStationsToNester(this,(Nesting *)local_2a0,pvVar13);
  plVar14 = (longlong *)local_2a0[0][1];
  if (*(char *)((longlong)plVar14 + 0x19) == '\0') {
    do {
      FUN_180007860(local_2a0,local_2a0,(longlong *)plVar14[2]);
      plVar5 = (longlong *)*plVar14;
      free(plVar14);
      plVar14 = plVar5;
    } while (*(char *)((longlong)plVar5 + 0x19) == '\0');
  }
  free(local_2a0[0]);
  nVar10 = Nest(this,(Nesting *)pvVar13,100);
  local_f8 = (char *)0x0;
  uStack_f0 = 0;
  local_e8 = 0;
  local_e0 = 0xf;
  local_f8 = (char *)FUN_18005d130(0x30);
  local_e8 = 0x22;
  local_e0 = 0x2f;
  builtin_strncpy(local_f8,"NestingSheetGenerator.LayoutEngine",0x23);
  bVar8 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                            &local_f8,0xf);
  if (0xf < local_e0) {
    pcVar16 = local_f8;
    if ((0xfff < local_e0 + 1) &&
       (pcVar16 = *(char **)(local_f8 + -8), (char *)0x1f < local_f8 + (-8 - (longlong)pcVar16))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pcVar16);
  }
  if (bVar8) {
    Logging::Guard::Guard(local_2a8);
    pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                            "NSG::GSF: Nest done: ");
    this_00 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,nVar10);
    std::basic_ostream<char,std::char_traits<char>_>::operator<<
              ((basic_ostream<char,std::char_traits<char>_> *)this_00,FUN_180001dd0);
    Logging::Guard::~Guard(local_2a8);
  }
  FUN_18000f8e0(local_258,plVar12);
  FUN_180027830(local_138,(double *)pvVar13,local_258,*(double *)(local_288[0] + 8),
                *(double *)(local_288[0] + 0x10));
  FUN_180040320(pvVar13);
  FUN_180005ae0(local_a8,(undefined8 *)&local_d0);
  IntermediateSheet::IntermediateSheet(local_88,local_138);
  local_2a4 = 6;
  FUN_180024630((longlong *)local_278,(longlong *)local_288,(longlong *)local_a8);
  FUN_18001bb40(local_60);
  FUN_18000ef50(local_70,local_70);
  if (0xf < local_90) {
    pvVar17 = local_a8[0];
    if ((0xfff < local_90 + 1) &&
       (pvVar17 = *(void **)((longlong)local_a8[0] + -8),
       0x1f < (ulonglong)((longlong)local_a8[0] + (-8 - (longlong)pvVar17)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar17);
  }
  pvVar13 = local_290;
  IntermediateSheet::IntermediateSheet((IntermediateSheet *)local_290,local_138);
  local_2a4 = 7;
  FUN_18001bb40(local_110);
  FUN_18000ef50(local_120,local_120);
  FUN_18001ba80((longlong *)local_258);
  if (0xf < local_b8) {
    pvVar6 = (void *)CONCAT71(uStack_cf,local_d0);
    pvVar17 = pvVar6;
    if ((0xfff < local_b8 + 1) &&
       (pvVar17 = *(void **)((longlong)pvVar6 + -8),
       0x1f < (ulonglong)((longlong)pvVar6 + (-8 - (longlong)pvVar17)))) {
LAB_1800260fe:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar17);
  }
  local_c0 = 0;
  local_b8 = 0xf;
  local_d0 = 0;
  *(undefined ***)((longlong)local_238 + (longlong)*(int *)(local_238[0] + 4)) =
       std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  *(int *)((longlong)local_238 + (longlong)*(int *)(local_238[0] + 4) + -4) =
       *(int *)(local_238[0] + 4) + -0x98;
  FUN_180005d00((basic_streambuf<char,std::char_traits<char>_> *)&local_220);
  std::basic_iostream<char,std::char_traits<char>_>::~basic_iostream<char,std::char_traits<char>_>
            (local_218);
  std::basic_ios<char,std::char_traits<char>_>::~basic_ios<char,std::char_traits<char>_>(local_1a0);
LAB_180026167:
  if (local_270 != '\0') {
    Logging::Guard::Guard(local_2a8);
    Logging::DecreaseIndentation();
    pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,"< ");
    pbVar11 = FUN_180001280(pbVar11,
                            "class LayoutEngine::IntermediateSheet __cdecl LayoutEngine::NestingSheetGenerator::ClassicFillSheet(const class std::vector<class LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > &)"
                           );
    std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,FUN_180001dd0);
    Logging::Guard::~Guard(local_2a8);
  }
  return (IntermediateSheet *)pvVar13;
}


```
