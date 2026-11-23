modulo: LayoutEngine.dll
versao: 24.03.10017.10017
funcao: 1800261f0
nome: ClassicMinimalLayouts
assinatura: IntermediateSheet ClassicMinimalLayouts(NestingSheetGenerator * this, vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> * param_1)
parametros: 2
retorno: IntermediateSheet

## Callers (xrefs de entrada)
- 18007180c -> unknown (DATA)
- 18007f6f8 -> unknown (DATA)
- Entry Point -> unknown (EXTERNAL)
- 18002867d -> GenerateClassicSolution @ 180028490 (UNCONDITIONAL_CALL)

## Callees (xrefs de saida)
- 18001bbf0 FUN_18001bbf0
- 18002bd90 FUN_18002bd90
- 18003cb90 FUN_18003cb90
- 18003cc70 FUN_18003cc70
- EXTERNAL:0000001b Guard
- EXTERNAL:000000a4 operator<<
- EXTERNAL:0000001d HasLevel
- 18005d130 FUN_18005d130
- EXTERNAL:000000c7 operator<<
- 180027830 FUN_180027830
- 180009770 FUN_180009770
- EXTERNAL:000000c6 operator<<
- 180025480 AddStationsToNester
- 180039380 ~OrderedStation
- 180010190 operator=
- 18003d4e0 FUN_18003d4e0
- 180039b40 GetArea
- 1800044c0 FUN_1800044c0
- 1800028c0 FUN_1800028c0
- 180004480 FUN_180004480
- EXTERNAL:0000001e IncreaseIndentation
- 1800252f0 AddRemainingStationsToNester
- 1800016f0 FUN_1800016f0
- 18003d1a0 FUN_18003d1a0
- 180040920 FUN_180040920
- 180001280 FUN_180001280
- 18000ef50 FUN_18000ef50
- EXTERNAL:000000c8 operator<<
- 180039bf0 GetPlacedStations
- 180040320 FUN_180040320
- 18003e470 FUN_18003e470
- 18001bce0 FUN_18001bce0
- EXTERNAL:000000c9 operator<<
- 18001bb40 FUN_18001bb40
- 180002520 FUN_180002520
- 18005e2dc floor
- EXTERNAL:000000f3 _invalid_parameter_noinfo_noreturn
- 180038f60 IntermediateSheet
- 18003feb0 FUN_18003feb0
- 180039bd0 GetOrderedQuantity
- 18002d7e0 FUN_18002d7e0
- 180042530 FUN_180042530
- 18002d650 FUN_18002d650
- 180007860 FUN_180007860
- 180025150 AddRemainingOptionalStationsToNester
- 180004740 FUN_180004740
- 18003d470 FUN_18003d470
- 18005d370 __security_check_cookie
- 18003d280 FUN_18003d280
- 18002d610 SetUpNest
- EXTERNAL:0000001c ~Guard
- 18002d570 Nest
- 180038fd0 OrderedStation
- 180039c60 IsMaximumFill
- 18005e2ca ceil
- 180005060 FUN_180005060
- 18005d16c free
- 18001cf60 FUN_18001cf60

## Strings referenciadas
- 18007c380 : 0x2b992ddfa232
- 1800649d0 : NestingSheetGenerator.LayoutEngine
- 1800633f0 : 000786de
- 180065010 : class LayoutEngine::IntermediateSheet __cdecl LayoutEngine::NestingSheetGenerator::ClassicMinimalLayouts(const class std::vector<class LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > &)
- 1800633e0 : 000786a6
- 180063b48 : 0x3e
- 1800634b0 : 00079fd2
- 180063498 : 00079ef6
- 1800633f8 : 0007873e
- 1800633e8 : 000786c2
- 180064520 : 0x0
- 180065588 : -0x4010000000000000
- 180063de0 : -0x8000000000000000
- 1800647e0 : 0x4000000000000000
- 180063cf8 : 0x3ff0000000000000
- 180063d10 : 0x4008000000000000
- 180063df0 : 0x3fe0000000000000
- 1800650f8 : NSG::CML: Nesting with 
- 180065110 : NSG::CML: Nest done: 
- 1800635b8 : 0007a868
- 180065128 : NSG::CML: Weights: 
- 180065140 : NSG::CML: Add one 
- 1800635c0 : 0007a8aa
- 180065168 : NSG::CML: AddOne done, handle 
- 180065158 : , errorStatus: 
- 1800635a8 : 0007a7e4
- 180063878 : 0007acb4
- 180065188 : NSG::CML: nesting restarts: 
- 1800635b0 : 0007a826
- 1800651a8 : NSG::CML: Nesting (max fill) with 
- 180064ed8 : NSG::GSF: Nest done: 

## Pseudocodigo (Ghidra Decompiler)
```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* private: class LayoutEngine::IntermediateSheet __cdecl
   LayoutEngine::NestingSheetGenerator::ClassicMinimalLayouts(class std::vector<class
   LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > const &
   __ptr64) __ptr64 */

OutputSheet * __thiscall
LayoutEngine::NestingSheetGenerator::ClassicMinimalLayouts
          (NestingSheetGenerator *this,
          vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_>
          *param_1)

{
  ulonglong *puVar1;
  IntermediateSheet *pIVar2;
  longlong lVar3;
  double dVar4;
  longlong *plVar5;
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *pvVar6;
  NestingSheetGenerator *this_00;
  bool bVar7;
  bool bVar8;
  char cVar9;
  nesterror_type nVar10;
  basic_ostream<char,std::char_traits<char>_> *pbVar11;
  map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
  *pmVar12;
  longlong *plVar13;
  undefined8 uVar14;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar15;
  GridStationLayout *pGVar16;
  IntermediateSheet *pIVar17;
  char *pcVar18;
  __uint64 _Var19;
  longlong *plVar20;
  longlong *plVar21;
  Nesting *pNVar22;
  vector<LayoutEngine::OutputStation,std::allocator<LayoutEngine::OutputStation>_> *pvVar23;
  IntermediateSheet *pIVar24;
  Guard GVar25;
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *in_R8;
  map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
  *pmVar26;
  map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
  *pmVar27;
  int iVar28;
  undefined4 uVar29;
  double dVar30;
  undefined4 uVar32;
  double _X;
  double dVar31;
  undefined1 auStackY_3d8 [32];
  Guard local_3a8;
  Guard local_3a7;
  Guard local_3a6;
  Guard local_3a5;
  Guard local_3a4;
  Guard local_3a3 [3];
  longlong *local_3a0;
  longlong local_398;
  char local_390;
  char cStack_38f;
  char cStack_38e;
  char cStack_38d;
  char cStack_38c;
  char cStack_38b;
  char cStack_38a;
  char cStack_389;
  char cStack_388;
  char cStack_387;
  char cStack_386;
  char cStack_385;
  char cStack_384;
  char cStack_383;
  char cStack_382;
  char cStack_381;
  ulonglong local_380;
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *local_378;
  longlong *local_370;
  longlong local_368;
  NestingSheetGenerator *local_360;
  undefined4 local_358;
  __uint64 local_350;
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *local_348;
  longlong **local_340;
  undefined8 local_338;
  longlong local_330 [3];
  longlong **local_318;
  undefined8 local_310;
  longlong **local_308;
  undefined8 local_300;
  longlong **local_2f8;
  undefined8 local_2f0;
  longlong **local_2e8;
  undefined8 local_2e0;
  char local_2d8 [8];
  char *local_2d0;
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *local_2c8;
  OrderedStation local_2b8 [144];
  void *local_228;
  undefined8 uStack_220;
  undefined8 local_218;
  ulonglong uStack_210;
  longlong *local_208;
  undefined8 uStack_200;
  ulonglong local_1f0 [2];
  longlong local_1e0 [3];
  char *local_1c8;
  undefined8 uStack_1c0;
  undefined8 local_1b8;
  ulonglong local_1b0;
  char *local_1a0;
  undefined8 uStack_198;
  undefined8 local_190;
  ulonglong local_188;
  char *local_178;
  undefined8 uStack_170;
  undefined8 local_168;
  ulonglong local_160;
  char *local_150;
  undefined8 uStack_148;
  undefined8 local_140;
  ulonglong local_138;
  char *local_128;
  undefined8 uStack_120;
  undefined8 local_118;
  ulonglong local_110 [2];
  longlong local_100 [3];
  ulonglong local_e8;
  
                    /* 0x261f0  118
                       ?ClassicMinimalLayouts@NestingSheetGenerator@LayoutEngine@@AEAA?AVIntermediateSheet@2@AEBV?$vector@VOrderedStation@LayoutEngine@@V?$allocator@VOrderedStation@LayoutEngine@@@std@@@std@@@Z
                        */
  local_e8 = DAT_18007c380 ^ (ulonglong)auStackY_3d8;
  local_358 = 0;
  local_228 = (void *)0x0;
  uStack_220 = 0;
  local_218 = 0;
  uStack_210 = 0;
  local_378 = param_1;
  local_360 = this;
  local_348 = in_R8;
  local_2c8 = param_1;
  FUN_1800016f0(&local_228,"NestingSheetGenerator.LayoutEngine",0x22);
  local_2d8[0] = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_>
                                    *)&local_228,0x14);
  local_2d0 = 
  "class LayoutEngine::IntermediateSheet __cdecl LayoutEngine::NestingSheetGenerator::ClassicMinimalLayouts(const class std::vector<class LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > &)"
  ;
  if ((bool)local_2d8[0]) {
    Logging::Guard::Guard(&local_3a8);
    pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,"> ");
    pbVar11 = FUN_180001280(pbVar11,
                            "class LayoutEngine::IntermediateSheet __cdecl LayoutEngine::NestingSheetGenerator::ClassicMinimalLayouts(const class std::vector<class LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > &)"
                           );
    std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,FUN_180001dd0);
    Logging::IncreaseIndentation();
    Logging::Guard::~Guard(&local_3a8);
  }
  if (0xf < uStack_210) {
    FUN_180004480(&local_228,local_228,uStack_210);
  }
  local_218 = 0;
  uStack_210 = 0xf;
  local_228 = (void *)((ulonglong)local_228 & 0xffffffffffffff00);
  local_3a0 = (longlong *)0x0;
  local_398 = 0;
  local_3a0 = (longlong *)FUN_18005d130(0x30);
  *local_3a0 = (longlong)local_3a0;
  local_3a0[1] = (longlong)local_3a0;
  local_3a0[2] = (longlong)local_3a0;
  *(undefined2 *)(local_3a0 + 3) = 0x101;
  FUN_18003d1a0(local_330,(longlong *)in_R8);
  IntermediateSheet::IntermediateSheet
            ((IntermediateSheet *)param_1,*(double *)(this + 8),*(double *)(this + 0x10));
  local_358 = 1;
  bVar8 = false;
  uVar29 = 0;
  uVar32 = 0xbff00000;
  local_380 = 0;
  local_390 = '\0';
  pmVar26 = (map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
             *)0x0;
  pmVar27 = (map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
             *)0x0;
  local_3a8 = (Guard)0x0;
  dVar4 = *(double *)(this + 8) * *(double *)(this + 0x10);
  local_350 = 0;
  do {
    if (pmVar27 !=
        (map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
         *)0x0) {
      FUN_180040320(pmVar27);
    }
    dVar30 = *(double *)(this + 0x18);
    pmVar12 = (map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
               *)FUN_180040920(-dVar30 * 0.5,-dVar30 * 0.5,dVar30 + *(double *)(this + 0x10),
                               dVar30 + *(double *)(this + 8),0);
    local_1c8 = (char *)0x0;
    uStack_1c0 = 0;
    local_1b8 = 0;
    local_1b0 = 0xf;
    local_1c8 = (char *)FUN_18005d130(0x30);
    local_1b8 = 0x22;
    local_1b0 = 0x2f;
    builtin_strncpy(local_1c8,"NestingSheetGenerator.LayoutEngine",0x23);
    bVar7 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                              &local_1c8,0xc);
    if (0xf < local_1b0) {
      pcVar18 = local_1c8;
      if ((0xfff < local_1b0 + 1) &&
         (pcVar18 = *(char **)(local_1c8 + -8), (char *)0x1f < local_1c8 + (-8 - (longlong)pcVar18))
         ) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pcVar18);
    }
    local_1b8 = 0;
    local_1b0 = 0xf;
    local_1c8 = (char *)((ulonglong)local_1c8 & 0xffffffffffffff00);
    if (bVar7) {
      Logging::Guard::Guard(&local_3a6);
      pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                              "NSG::CML: Nesting with ");
      plVar13 = FUN_18002bd90((longlong *)&local_208,(longlong *)&local_3a0);
      puVar1 = (ulonglong *)(plVar13 + 2);
      if (0xf < (ulonglong)plVar13[3]) {
        plVar13 = (longlong *)*plVar13;
      }
      pbVar11 = FUN_180005060(pbVar11,(char *)plVar13,*puVar1);
      std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,FUN_180001dd0);
      if (0xf < local_1f0[0]) {
        FUN_180004480(&local_208,local_208,local_1f0[0]);
      }
      Logging::Guard::~Guard(&local_3a6);
    }
    AddStationsToNester(this,(Nesting *)&local_370,pmVar12,
                        (vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_>
                         *)&local_3a0);
    AddRemainingStationsToNester
              (this,(Nesting *)pmVar12,in_R8,
               (map<__int64,void*___ptr64,std::less<__int64>,std::allocator<std::pair<__int64_const_,void*___ptr64>_>_>
                *)&local_370);
    Nest(this,(Nesting *)pmVar12,100);
    local_350 = local_350 + 1;
    uVar14 = FUN_18002d7e0((double *)pmVar12,&local_3a0,(undefined8 *)in_R8);
    local_1a0 = (char *)0x0;
    uStack_198 = 0;
    local_190 = 0;
    local_188 = 0xf;
    local_1a0 = (char *)FUN_18005d130(0x30);
    local_190 = 0x22;
    local_188 = 0x2f;
    builtin_strncpy(local_1a0,"NestingSheetGenerator.LayoutEngine",0x23);
    bVar7 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                              &local_1a0,0xf);
    if (0xf < local_188) {
      pcVar18 = local_1a0;
      if ((0xfff < local_188 + 1) &&
         (pcVar18 = *(char **)(local_1a0 + -8), (char *)0x1f < local_1a0 + (-8 - (longlong)pcVar18))
         ) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pcVar18);
    }
    local_190 = 0;
    local_188 = 0xf;
    local_1a0 = (char *)((ulonglong)local_1a0 & 0xffffffffffffff00);
    if (bVar7) {
      Logging::Guard::Guard(&local_3a5);
      pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                              "NSG::CML: Nest done: ");
      pbVar15 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          (pbVar11,SUB81(uVar14,0));
      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                ((basic_ostream<char,std::char_traits<char>_> *)pbVar15,FUN_180001dd0);
      Logging::Guard::~Guard(&local_3a5);
    }
    plVar13 = local_3a0;
    pmVar27 = pmVar26;
    if (SUB81(uVar14,0) == false) {
      if (pmVar26 ==
          (map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
           *)0x0) {
        FUN_180009770((longlong *)&local_370);
        goto LAB_18002747a;
      }
      plVar20 = (longlong *)local_3a0[1];
      uStack_200 = uStack_200 & 0xffffffff00000000;
      lVar3 = CONCAT17(cStack_381,
                       CONCAT16(cStack_382,
                                CONCAT15(cStack_383,
                                         CONCAT14(cStack_384,
                                                  CONCAT13(cStack_385,
                                                           CONCAT12(cStack_386,
                                                                    CONCAT11(cStack_387,cStack_388))
                                                          )))));
      cVar9 = *(char *)((longlong)plVar20 + 0x19);
      local_208 = plVar20;
      plVar21 = local_3a0;
      while (plVar5 = plVar20, cVar9 == '\0') {
        uStack_200._4_4_ = (uint)(uStack_200 >> 0x20);
        if (plVar5[4] < lVar3) {
          uStack_200 = (ulonglong)uStack_200._4_4_ << 0x20;
          plVar20 = (longlong *)plVar5[2];
        }
        else {
          uStack_200 = CONCAT44(uStack_200._4_4_,1);
          plVar20 = (longlong *)*plVar5;
          plVar21 = plVar5;
        }
        cVar9 = *(char *)((longlong)plVar20 + 0x19);
        local_208 = plVar5;
      }
      if ((*(char *)((longlong)plVar21 + 0x19) != '\0') || (lVar3 < plVar21[4])) {
        if (local_398 == 0x555555555555555) {
                    /* WARNING: Subroutine does not return */
          FUN_180004740();
        }
        local_318 = &local_3a0;
        local_310 = 0;
        plVar20 = (longlong *)FUN_18001bbf0(&local_3a0,1);
        plVar20[4] = CONCAT17(cStack_381,
                              CONCAT16(cStack_382,
                                       CONCAT15(cStack_383,
                                                CONCAT14(cStack_384,
                                                         CONCAT13(cStack_385,
                                                                  CONCAT12(cStack_386,
                                                                           CONCAT11(cStack_387,
                                                                                    cStack_388))))))
                             );
        plVar20[5] = 0;
        *plVar20 = (longlong)plVar13;
        plVar20[1] = (longlong)plVar13;
        plVar20[2] = (longlong)plVar13;
        *(undefined2 *)(plVar20 + 3) = 0;
        local_310 = 0;
        plVar21 = FUN_1800044c0((longlong *)&local_3a0,(longlong *)&local_208,plVar20);
      }
      plVar21[5] = plVar21[5] + -1;
      FUN_18003e470(local_330,
                    CONCAT17(cStack_381,
                             CONCAT16(cStack_382,
                                      CONCAT15(cStack_383,
                                               CONCAT14(cStack_384,
                                                        CONCAT13(cStack_385,
                                                                 CONCAT12(cStack_386,
                                                                          CONCAT11(cStack_387,
                                                                                   cStack_388)))))))
                    ,'\0');
      local_380 = local_380 + 1;
      bVar8 = false;
      uVar14 = FUN_18002d7e0((double *)pmVar12,&local_3a0,(undefined8 *)in_R8);
      if ((char)uVar14 != '\0') goto LAB_180026783;
      FUN_180040320(pmVar12);
      pmVar27 = (map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
                 *)0x0;
      FUN_180042530((double *)pmVar26,2);
    }
    else {
      if (local_390 != '\0') {
        pGVar16 = FUN_18003d470((longlong *)in_R8,(longlong *)&cStack_388);
        OrderedStation::OrderedStation(local_2b8,(OrderedStation *)pGVar16);
        dVar30 = OrderedStation::GetArea(local_2b8);
        dVar4 = dVar4 - dVar30;
        OrderedStation::~OrderedStation(local_2b8);
      }
      if (pmVar26 !=
          (map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
           *)0x0) {
        FUN_180040320(pmVar26);
        pmVar27 = (map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
                   *)0x0;
      }
LAB_180026783:
      FUN_180042530((double *)pmVar12,2);
      pmVar26 = pmVar12;
      if (bVar8) {
        dVar30 = FUN_18003d4e0((longlong *)in_R8,(longlong *)&local_3a0);
        uVar29 = SUB84(dVar30,0);
        uVar32 = (undefined4)((ulonglong)dVar30 >> 0x20);
        pIVar17 = FUN_180027830((IntermediateSheet *)&local_208,(double *)pmVar12,
                                (undefined8 *)in_R8,*(double *)(local_360 + 8),
                                *(double *)(local_360 + 0x10));
        *(undefined8 *)param_1 = *(undefined8 *)pIVar17;
        *(undefined8 *)(param_1 + 8) = *(undefined8 *)(pIVar17 + 8);
        *(undefined8 *)(param_1 + 0x10) = *(undefined8 *)(pIVar17 + 0x10);
        pIVar24 = pIVar17 + 0x18;
        pIVar2 = (IntermediateSheet *)(param_1 + 0x18);
        if (pIVar2 != pIVar24) {
          FUN_18001bce0((longlong *)pIVar2);
          lVar3 = *(longlong *)pIVar2;
          *(longlong *)pIVar2 = *(longlong *)pIVar24;
          *(longlong *)pIVar24 = lVar3;
          uVar14 = *(undefined8 *)(param_1 + 0x20);
          *(undefined8 *)(param_1 + 0x20) = *(undefined8 *)(pIVar17 + 0x20);
          *(undefined8 *)(pIVar17 + 0x20) = uVar14;
        }
        pIVar24 = pIVar17 + 0x28;
        pIVar2 = (IntermediateSheet *)(param_1 + 0x28);
        if (pIVar2 != pIVar24) {
          FUN_18001bb40((longlong *)pIVar2);
          *(longlong *)pIVar2 = *(longlong *)pIVar24;
          *(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(pIVar17 + 0x30);
          *(undefined8 *)(param_1 + 0x38) = *(undefined8 *)(pIVar17 + 0x38);
          *(longlong *)pIVar24 = 0;
          *(undefined8 *)(pIVar17 + 0x30) = 0;
          *(undefined8 *)(pIVar17 + 0x38) = 0;
        }
        FUN_18001bb40(local_1e0);
        FUN_18000ef50((longlong *)local_1f0,local_1f0);
        in_R8 = local_348;
      }
    }
    do {
      uVar14 = FUN_18003cb90((longlong *)in_R8,(longlong *)&local_3a0,1,'\x01');
      if ((char)uVar14 != '\0') {
LAB_1800273d6:
        GVar25 = (Guard)0x1;
        local_3a8 = (Guard)0x1;
        goto LAB_1800273de;
      }
      local_178 = (char *)0x0;
      uStack_170 = 0;
      local_168 = 0;
      local_160 = 0xf;
      local_178 = (char *)FUN_18005d130(0x30);
      local_168 = 0x22;
      local_160 = 0x2f;
      builtin_strncpy(local_178,"NestingSheetGenerator.LayoutEngine",0x23);
      bVar7 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                &local_178,0xf);
      if (0xf < local_160) {
        pcVar18 = local_178;
        if ((0xfff < local_160 + 1) &&
           (pcVar18 = *(char **)(local_178 + -8),
           (char *)0x1f < local_178 + (-8 - (longlong)pcVar18))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pcVar18);
      }
      local_168 = 0;
      local_160 = 0xf;
      local_178 = (char *)((ulonglong)local_178 & 0xffffffffffffff00);
      if (bVar7) {
        Logging::Guard::Guard(&local_3a4);
        pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                                "NSG::CML: Weights: ");
        plVar13 = FUN_18002d650((longlong *)&local_208,local_330);
        puVar1 = (ulonglong *)(plVar13 + 2);
        if (0xf < (ulonglong)plVar13[3]) {
          plVar13 = (longlong *)*plVar13;
        }
        pbVar11 = FUN_180005060(pbVar11,(char *)plVar13,*puVar1);
        std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,FUN_180001dd0);
        if (0xf < local_1f0[0]) {
          plVar13 = local_208;
          if ((0xfff < local_1f0[0] + 1) &&
             (plVar13 = (longlong *)local_208[-1],
             0x1f < (ulonglong)((longlong)local_208 + (-8 - (longlong)plVar13)))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(plVar13);
        }
        Logging::Guard::~Guard(&local_3a4);
      }
      pcVar18 = FUN_18003d280((undefined1 *)&local_228,local_330,local_380);
      local_390 = *pcVar18;
      cStack_38f = pcVar18[1];
      cStack_38e = pcVar18[2];
      cStack_38d = pcVar18[3];
      cStack_38c = pcVar18[4];
      cStack_38b = pcVar18[5];
      cStack_38a = pcVar18[6];
      cStack_389 = pcVar18[7];
      cStack_388 = pcVar18[8];
      cStack_387 = pcVar18[9];
      cStack_386 = pcVar18[10];
      cStack_385 = pcVar18[0xb];
      cStack_384 = pcVar18[0xc];
      cStack_383 = pcVar18[0xd];
      cStack_382 = pcVar18[0xe];
      cStack_381 = pcVar18[0xf];
      if (local_390 == '\0') goto LAB_1800273d6;
      pGVar16 = FUN_18003d470((longlong *)in_R8,(longlong *)&cStack_388);
      OrderedStation::OrderedStation(local_2b8,(OrderedStation *)pGVar16);
      bVar7 = OrderedStation::IsMaximumFill(local_2b8);
      plVar13 = local_3a0;
      if (bVar7) {
LAB_1800273c3:
        GVar25 = (Guard)0x1;
        local_3a8 = (Guard)0x1;
        OrderedStation::~OrderedStation(local_2b8);
        goto LAB_1800273de;
      }
      plVar20 = (longlong *)local_3a0[1];
      uStack_200 = uStack_200 & 0xffffffff00000000;
      lVar3 = CONCAT17(cStack_381,
                       CONCAT16(cStack_382,
                                CONCAT15(cStack_383,
                                         CONCAT14(cStack_384,
                                                  CONCAT13(cStack_385,
                                                           CONCAT12(cStack_386,
                                                                    CONCAT11(cStack_387,cStack_388))
                                                          )))));
      cVar9 = *(char *)((longlong)plVar20 + 0x19);
      local_208 = plVar20;
      plVar21 = local_3a0;
      while (plVar5 = plVar20, cVar9 == '\0') {
        uStack_200._4_4_ = (uint)(uStack_200 >> 0x20);
        if (plVar5[4] < lVar3) {
          uStack_200 = (ulonglong)uStack_200._4_4_ << 0x20;
          plVar20 = (longlong *)plVar5[2];
        }
        else {
          uStack_200 = CONCAT44(uStack_200._4_4_,1);
          plVar20 = (longlong *)*plVar5;
          plVar21 = plVar5;
        }
        cVar9 = *(char *)((longlong)plVar20 + 0x19);
        local_208 = plVar5;
      }
      if ((*(char *)((longlong)plVar21 + 0x19) != '\0') || (lVar3 < plVar21[4])) {
        if (local_398 == 0x555555555555555) goto LAB_180027828;
        local_308 = &local_3a0;
        local_300 = 0;
        plVar20 = (longlong *)FUN_18005d130(0x30);
        plVar20[4] = CONCAT17(cStack_381,
                              CONCAT16(cStack_382,
                                       CONCAT15(cStack_383,
                                                CONCAT14(cStack_384,
                                                         CONCAT13(cStack_385,
                                                                  CONCAT12(cStack_386,
                                                                           CONCAT11(cStack_387,
                                                                                    cStack_388))))))
                             );
        plVar20[5] = 0;
        *plVar20 = (longlong)plVar13;
        plVar20[1] = (longlong)plVar13;
        plVar20[2] = (longlong)plVar13;
        *(undefined2 *)(plVar20 + 3) = 0;
        local_300 = 0;
        plVar21 = FUN_1800044c0((longlong *)&local_3a0,(longlong *)&local_208,plVar20);
      }
      _Var19 = OrderedStation::GetOrderedQuantity(local_2b8);
      plVar13 = local_3a0;
      if (_Var19 < plVar21[5] + 1U) goto LAB_1800273c3;
      plVar20 = (longlong *)local_3a0[1];
      uStack_200 = uStack_200 & 0xffffffff00000000;
      lVar3 = CONCAT17(cStack_381,
                       CONCAT16(cStack_382,
                                CONCAT15(cStack_383,
                                         CONCAT14(cStack_384,
                                                  CONCAT13(cStack_385,
                                                           CONCAT12(cStack_386,
                                                                    CONCAT11(cStack_387,cStack_388))
                                                          )))));
      cVar9 = *(char *)((longlong)plVar20 + 0x19);
      local_208 = plVar20;
      plVar21 = local_3a0;
      while (plVar5 = plVar20, cVar9 == '\0') {
        uStack_200._4_4_ = (uint)(uStack_200 >> 0x20);
        if (plVar5[4] < lVar3) {
          uStack_200 = (ulonglong)uStack_200._4_4_ << 0x20;
          plVar20 = (longlong *)plVar5[2];
        }
        else {
          uStack_200 = CONCAT44(uStack_200._4_4_,1);
          plVar20 = (longlong *)*plVar5;
          plVar21 = plVar5;
        }
        cVar9 = *(char *)((longlong)plVar20 + 0x19);
        local_208 = plVar5;
      }
      if ((*(char *)((longlong)plVar21 + 0x19) != '\0') || (lVar3 < plVar21[4])) {
        if (local_398 == 0x555555555555555) goto LAB_180027828;
        local_2f8 = &local_3a0;
        local_2f0 = 0;
        plVar20 = (longlong *)FUN_18005d130(0x30);
        plVar20[4] = CONCAT17(cStack_381,
                              CONCAT16(cStack_382,
                                       CONCAT15(cStack_383,
                                                CONCAT14(cStack_384,
                                                         CONCAT13(cStack_385,
                                                                  CONCAT12(cStack_386,
                                                                           CONCAT11(cStack_387,
                                                                                    cStack_388))))))
                             );
        plVar20[5] = 0;
        *plVar20 = (longlong)plVar13;
        plVar20[1] = (longlong)plVar13;
        plVar20[2] = (longlong)plVar13;
        *(undefined2 *)(plVar20 + 3) = 0;
        local_2f0 = 0;
        plVar21 = FUN_1800044c0((longlong *)&local_3a0,(longlong *)&local_208,plVar20);
      }
      plVar21[5] = plVar21[5] + 1;
      FUN_18003e470(local_330,
                    CONCAT17(cStack_381,
                             CONCAT16(cStack_382,
                                      CONCAT15(cStack_383,
                                               CONCAT14(cStack_384,
                                                        CONCAT13(cStack_385,
                                                                 CONCAT12(cStack_386,
                                                                          CONCAT11(cStack_387,
                                                                                   cStack_388)))))))
                    ,'\x01');
      local_150 = (char *)0x0;
      uStack_148 = 0;
      local_140 = 0;
      local_138 = 0xf;
      local_150 = (char *)FUN_18005d130(0x30);
      local_140 = 0x22;
      local_138 = 0x2f;
      builtin_strncpy(local_150,"NestingSheetGenerator.LayoutEngine",0x23);
      bVar8 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                &local_150,0xf);
      if (0xf < local_138) {
        pcVar18 = local_150;
        if ((0xfff < local_138 + 1) &&
           (pcVar18 = *(char **)(local_150 + -8),
           (char *)0x1f < local_150 + (-8 - (longlong)pcVar18))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pcVar18);
      }
      local_140 = 0;
      local_138 = 0xf;
      local_150 = (char *)((ulonglong)local_150 & 0xffffffffffffff00);
      if (bVar8) {
        Logging::Guard::Guard(local_3a3);
        pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                                "NSG::CML: Add one ");
        pbVar15 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            (pbVar11,CONCAT17(cStack_381,
                                              CONCAT16(cStack_382,
                                                       CONCAT15(cStack_383,
                                                                CONCAT14(cStack_384,
                                                                         CONCAT13(cStack_385,
                                                                                  CONCAT12(
                                                  cStack_386,CONCAT11(cStack_387,cStack_388))))))));
        std::basic_ostream<char,std::char_traits<char>_>::operator<<
                  ((basic_ostream<char,std::char_traits<char>_> *)pbVar15,FUN_180001dd0);
        Logging::Guard::~Guard(local_3a3);
      }
      plVar21 = local_370;
      plVar13 = (longlong *)local_370[1];
      uStack_200 = uStack_200 & 0xffffffff00000000;
      lVar3 = CONCAT17(cStack_381,
                       CONCAT16(cStack_382,
                                CONCAT15(cStack_383,
                                         CONCAT14(cStack_384,
                                                  CONCAT13(cStack_385,
                                                           CONCAT12(cStack_386,
                                                                    CONCAT11(cStack_387,cStack_388))
                                                          )))));
      cVar9 = *(char *)((longlong)plVar13 + 0x19);
      local_208 = plVar13;
      plVar20 = local_370;
      while (plVar5 = plVar13, cVar9 == '\0') {
        uStack_200._4_4_ = (uint)(uStack_200 >> 0x20);
        if (plVar5[4] < lVar3) {
          uStack_200 = (ulonglong)uStack_200._4_4_ << 0x20;
          plVar13 = (longlong *)plVar5[2];
        }
        else {
          uStack_200 = CONCAT44(uStack_200._4_4_,1);
          plVar13 = (longlong *)*plVar5;
          plVar20 = plVar5;
        }
        cVar9 = *(char *)((longlong)plVar13 + 0x19);
        local_208 = plVar5;
      }
      if ((*(char *)((longlong)plVar20 + 0x19) != '\0') || (lVar3 < plVar20[4])) {
        if (local_368 == 0x555555555555555) goto LAB_180027828;
        local_2e8 = &local_370;
        local_2e0 = 0;
        plVar13 = (longlong *)FUN_18001bbf0(&local_370,1);
        plVar13[4] = CONCAT17(cStack_381,
                              CONCAT16(cStack_382,
                                       CONCAT15(cStack_383,
                                                CONCAT14(cStack_384,
                                                         CONCAT13(cStack_385,
                                                                  CONCAT12(cStack_386,
                                                                           CONCAT11(cStack_387,
                                                                                    cStack_388))))))
                             );
        plVar13[5] = 0;
        *plVar13 = (longlong)plVar21;
        plVar13[1] = (longlong)plVar21;
        plVar13[2] = (longlong)plVar21;
        *(undefined2 *)(plVar13 + 3) = 0;
        local_2e0 = 0;
        plVar20 = FUN_1800044c0((longlong *)&local_370,(longlong *)&local_208,plVar13);
      }
      uVar14 = FUN_18003feb0((longlong)pmVar26,plVar20[5]);
      iVar28 = (int)uVar14;
      local_128 = (char *)0x0;
      uStack_120 = 0;
      local_118 = 0;
      local_110[0] = 0xf;
      local_128 = (char *)FUN_18005d130(0x30);
      local_118 = 0x22;
      local_110[0] = 0x2f;
      builtin_strncpy(local_128,"NestingSheetGenerator.LayoutEngine",0x23);
      bVar8 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                &local_128,0xf);
      if (0xf < local_110[0]) {
        pcVar18 = local_128;
        if ((0xfff < local_110[0] + 1) &&
           (pcVar18 = *(char **)(local_128 + -8),
           (char *)0x1f < local_128 + (-8 - (longlong)pcVar18))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pcVar18);
      }
      local_118 = 0;
      local_110[0] = 0xf;
      local_128 = (char *)((ulonglong)local_128 & 0xffffffffffffff00);
      if (bVar8) {
        Logging::Guard::Guard(&local_3a7);
        pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                                "NSG::CML: AddOne done, handle ");
        pbVar15 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            (pbVar11,CONCAT17(cStack_381,
                                              CONCAT16(cStack_382,
                                                       CONCAT15(cStack_383,
                                                                CONCAT14(cStack_384,
                                                                         CONCAT13(cStack_385,
                                                                                  CONCAT12(
                                                  cStack_386,CONCAT11(cStack_387,cStack_388))))))));
        pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)pbVar15,
                                ", errorStatus: ");
        pbVar15 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,iVar28);
        std::basic_ostream<char,std::char_traits<char>_>::operator<<
                  ((basic_ostream<char,std::char_traits<char>_> *)pbVar15,FUN_180001dd0);
        Logging::Guard::~Guard(&local_3a7);
      }
      _X = FUN_18003d4e0((longlong *)in_R8,(longlong *)&local_3a0);
      dVar31 = ceil(_X);
      dVar30 = dVar31;
      if (((_X == 2.0) || (_X == 1.0)) &&
         (uVar14 = FUN_18003cb90((longlong *)in_R8,(longlong *)&local_3a0,(int)_X,'\0'),
         (char)uVar14 == '\0')) {
        dVar30 = dVar31 + 1.0;
      }
      if (((double)CONCAT44(uVar32,uVar29) <= 0.0 && (double)CONCAT44(uVar32,uVar29) != 0.0) ||
         (dVar30 <= (double)CONCAT44(uVar32,uVar29) && (double)CONCAT44(uVar32,uVar29) != dVar30)) {
LAB_180027195:
        bVar8 = true;
      }
      else {
        dVar30 = ceil((double)CONCAT44(uVar32,uVar29));
        if (dVar31 <= dVar30) {
          dVar30 = floor(_X);
          dVar31 = floor((double)CONCAT44(uVar32,uVar29));
          if (dVar30 == dVar31) goto LAB_180027195;
        }
        bVar8 = false;
      }
      if (iVar28 == 0) {
        if (bVar8) {
          pIVar17 = FUN_180027830((IntermediateSheet *)&local_208,(double *)pmVar26,
                                  (undefined8 *)in_R8,*(double *)(local_360 + 8),
                                  *(double *)(local_360 + 0x10));
          pvVar6 = local_378;
          *(undefined8 *)local_378 = *(undefined8 *)pIVar17;
          *(undefined8 *)(local_378 + 8) = *(undefined8 *)(pIVar17 + 8);
          *(undefined8 *)(local_378 + 0x10) = *(undefined8 *)(pIVar17 + 0x10);
          pIVar24 = pIVar17 + 0x18;
          pIVar2 = (IntermediateSheet *)(local_378 + 0x18);
          if (pIVar2 != pIVar24) {
            FUN_18001bce0((longlong *)pIVar2);
            lVar3 = *(longlong *)pIVar2;
            *(longlong *)pIVar2 = *(longlong *)pIVar24;
            *(longlong *)pIVar24 = lVar3;
            uVar14 = *(undefined8 *)(pvVar6 + 0x20);
            *(undefined8 *)(pvVar6 + 0x20) = *(undefined8 *)(pIVar17 + 0x20);
            *(undefined8 *)(pIVar17 + 0x20) = uVar14;
          }
          pvVar6 = local_378;
          pIVar24 = pIVar17 + 0x28;
          pIVar2 = (IntermediateSheet *)(local_378 + 0x28);
          if (pIVar2 != pIVar24) {
            FUN_18001bb40((longlong *)pIVar2);
            *(longlong *)pIVar2 = *(longlong *)pIVar24;
            *(undefined8 *)(pvVar6 + 0x30) = *(undefined8 *)(pIVar17 + 0x30);
            *(undefined8 *)(pvVar6 + 0x38) = *(undefined8 *)(pIVar17 + 0x38);
            *(longlong *)pIVar24 = 0;
            *(undefined8 *)(pIVar17 + 0x30) = 0;
            *(undefined8 *)(pIVar17 + 0x38) = 0;
          }
          FUN_18001bb40(local_1e0);
          FUN_18000ef50((longlong *)local_1f0,local_1f0);
          in_R8 = local_348;
          uVar29 = SUB84(_X,0);
          uVar32 = (int)((ulonglong)_X >> 0x20);
        }
        dVar30 = OrderedStation::GetArea(local_2b8);
        dVar4 = dVar4 - dVar30;
      }
      else {
        dVar30 = OrderedStation::GetArea(local_2b8);
        plVar13 = local_3a0;
        if (dVar4 <= dVar30 * 3.0) {
          local_380 = local_380 + 1;
          iVar28 = 0;
          plVar20 = (longlong *)local_3a0[1];
          uStack_200 = uStack_200 & 0xffffffff00000000;
          lVar3 = CONCAT17(cStack_381,
                           CONCAT16(cStack_382,
                                    CONCAT15(cStack_383,
                                             CONCAT14(cStack_384,
                                                      CONCAT13(cStack_385,
                                                               CONCAT12(cStack_386,
                                                                        CONCAT11(cStack_387,
                                                                                 cStack_388)))))));
          cVar9 = *(char *)((longlong)plVar20 + 0x19);
          local_208 = plVar20;
          plVar21 = local_3a0;
          while (plVar5 = plVar20, cVar9 == '\0') {
            uStack_200._4_4_ = (uint)(uStack_200 >> 0x20);
            if (plVar5[4] < lVar3) {
              uStack_200 = (ulonglong)uStack_200._4_4_ << 0x20;
              plVar20 = (longlong *)plVar5[2];
            }
            else {
              uStack_200 = CONCAT44(uStack_200._4_4_,1);
              plVar20 = (longlong *)*plVar5;
              plVar21 = plVar5;
            }
            cVar9 = *(char *)((longlong)plVar20 + 0x19);
            local_208 = plVar5;
          }
          if ((*(char *)((longlong)plVar21 + 0x19) != '\0') || (lVar3 < plVar21[4])) {
            if (local_398 == 0x555555555555555) {
LAB_180027828:
                    /* WARNING: Subroutine does not return */
              FUN_180004740();
            }
            local_340 = &local_3a0;
            local_338 = 0;
            plVar20 = (longlong *)FUN_18001bbf0(&local_3a0,1);
            plVar20[4] = CONCAT17(cStack_381,
                                  CONCAT16(cStack_382,
                                           CONCAT15(cStack_383,
                                                    CONCAT14(cStack_384,
                                                             CONCAT13(cStack_385,
                                                                      CONCAT12(cStack_386,
                                                                               CONCAT11(cStack_387,
                                                                                        cStack_388))
                                                                     )))));
            plVar20[5] = 0;
            *plVar20 = (longlong)plVar13;
            plVar20[1] = (longlong)plVar13;
            plVar20[2] = (longlong)plVar13;
            *(undefined2 *)(plVar20 + 3) = 0;
            local_338 = 0;
            plVar21 = FUN_1800044c0((longlong *)&local_3a0,(longlong *)&local_208,plVar20);
          }
          plVar21[5] = plVar21[5] + -1;
          FUN_18003e470(local_330,
                        CONCAT17(cStack_381,
                                 CONCAT16(cStack_382,
                                          CONCAT15(cStack_383,
                                                   CONCAT14(cStack_384,
                                                            CONCAT13(cStack_385,
                                                                     CONCAT12(cStack_386,
                                                                              CONCAT11(cStack_387,
                                                                                       cStack_388)))
                                                           )))),'\0');
        }
      }
      OrderedStation::~OrderedStation(local_2b8);
    } while (iVar28 == 0);
    GVar25 = local_3a8;
LAB_1800273de:
    cVar9 = *(char *)(local_370[1] + 0x19);
    plVar13 = (longlong *)local_370[1];
    while (cVar9 == '\0') {
      FUN_180007860(&local_370,&local_370,(longlong *)plVar13[2]);
      plVar20 = (longlong *)*plVar13;
      free(plVar13);
      plVar13 = plVar20;
      cVar9 = *(char *)((longlong)plVar20 + 0x19);
    }
    free(local_370);
    if (GVar25 != (Guard)0x0) {
      if (pmVar27 !=
          (map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
           *)0x0) {
        FUN_180040320(pmVar27);
      }
      pmVar12 = pmVar26;
      param_1 = local_378;
LAB_18002747a:
      FUN_180040320(pmVar12);
      local_228 = (void *)0x0;
      uStack_220 = 0;
      local_218 = 0;
      uStack_210 = 0;
      FUN_1800016f0(&local_228,"NestingSheetGenerator.LayoutEngine",0x22);
      bVar8 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                &local_228,0xf);
      if (0xf < uStack_210) {
        FUN_180004480(&local_228,local_228,uStack_210);
      }
      if (bVar8) {
        Logging::Guard::Guard(&local_3a7);
        pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                                "NSG::CML: nesting restarts: ");
        pbVar15 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,local_350);
        std::basic_ostream<char,std::char_traits<char>_>::operator<<
                  ((basic_ostream<char,std::char_traits<char>_> *)pbVar15,FUN_180001dd0);
        Logging::Guard::~Guard(&local_3a7);
      }
      cVar9 = FUN_18003cc70((undefined8 *)in_R8);
      this_00 = local_360;
      if (cVar9 != '\0') {
        pNVar22 = SetUpNest(local_360);
        local_228 = (void *)0x0;
        uStack_220 = 0;
        local_218 = 0;
        uStack_210 = 0;
        FUN_1800016f0(&local_228,"NestingSheetGenerator.LayoutEngine",0x22);
        bVar8 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *
                                  )&local_228,0xc);
        if (0xf < uStack_210) {
          FUN_180004480(&local_228,local_228,uStack_210);
        }
        if (bVar8) {
          Logging::Guard::Guard(&local_3a7);
          pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                                  "NSG::CML: Nesting (max fill) with ");
          plVar13 = FUN_18002bd90((longlong *)&local_228,(longlong *)&local_3a0);
          puVar1 = (ulonglong *)(plVar13 + 2);
          if (0xf < (ulonglong)plVar13[3]) {
            plVar13 = (longlong *)*plVar13;
          }
          pbVar11 = FUN_180005060(pbVar11,(char *)plVar13,*puVar1);
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,FUN_180001dd0);
          FUN_180002520((longlong *)&local_228);
          Logging::Guard::~Guard(&local_3a7);
        }
        pvVar23 = OutputSheet::GetPlacedStations((OutputSheet *)param_1);
        AddStationsToNester(this_00,(Nesting *)&local_340,
                            (map<__int64,unsigned___int64,std::less<__int64>,std::allocator<std::pair<__int64_const_,unsigned___int64>_>_>
                             *)pNVar22,
                            (vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_>
                             *)pvVar23);
        AddRemainingOptionalStationsToNester
                  (this_00,pNVar22,in_R8,
                   (map<__int64,void*___ptr64,std::less<__int64>,std::allocator<std::pair<__int64_const_,void*___ptr64>_>_>
                    *)&local_340);
        nVar10 = Nest(this_00,pNVar22,100);
        local_228 = (void *)0x0;
        uStack_220 = 0;
        local_218 = 0;
        uStack_210 = 0;
        FUN_1800016f0(&local_228,"NestingSheetGenerator.LayoutEngine",0x22);
        bVar8 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *
                                  )&local_228,0xf);
        if (0xf < uStack_210) {
          FUN_180004480(&local_228,local_228,uStack_210);
        }
        if (bVar8) {
          Logging::Guard::Guard(&local_3a7);
          pbVar11 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                                  "NSG::GSF: Nest done: ");
          pbVar15 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar11,nVar10);
          std::basic_ostream<char,std::char_traits<char>_>::operator<<
                    ((basic_ostream<char,std::char_traits<char>_> *)pbVar15,FUN_180001dd0);
          Logging::Guard::~Guard(&local_3a7);
        }
        if (nVar10 == 0) {
          pIVar24 = FUN_180027830((IntermediateSheet *)&local_128,(double *)pNVar22,
                                  (undefined8 *)local_348,*(double *)(this_00 + 8),
                                  *(double *)(this_00 + 0x10));
          IntermediateSheet::operator=((IntermediateSheet *)param_1,pIVar24);
          FUN_18001bb40(local_100);
          FUN_18000ef50((longlong *)local_110,local_110);
        }
        FUN_180040320(pNVar22);
        FUN_180009770((longlong *)&local_340);
      }
      FUN_18001cf60(local_330);
      FUN_18000ef50((longlong *)&local_3a0,&local_3a0);
      FUN_1800028c0(local_2d8);
      return (OutputSheet *)param_1;
    }
    this = local_360;
    param_1 = local_378;
  } while( true );
}


```
