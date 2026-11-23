modulo: LayoutEngine.dll
versao: 24.03.10017.10017
funcao: 180028490
nome: GenerateClassicSolution
assinatura: vector<LayoutEngine::IntermediateSheet,std::allocator<LayoutEngine::IntermediateSheet>_> GenerateClassicSolution(NestingSheetGenerator * this, vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> * param_1, bool param_2)
parametros: 3
retorno: vector<LayoutEngine::IntermediateSheet,std::allocator<LayoutEngine::IntermediateSheet>_>

## Callers (xrefs de entrada)
- 180071828 -> unknown (DATA)
- 18007f734 -> unknown (DATA)
- Entry Point -> unknown (EXTERNAL)
- 1800649b8 -> unknown (DATA)

## Callees (xrefs de saida)
- 18003e100 FUN_18003e100
- 18000f8e0 FUN_18000f8e0
- 180004720 FUN_180004720
- 180004800 FUN_180004800
- 18003cc70 FUN_18003cc70
- 18001bb40 FUN_18001bb40
- EXTERNAL:0000001b Guard
- 18005e2dc floor
- 18003a1b0 SetProduceCount
- EXTERNAL:000000a4 operator<<
- 18005d130 FUN_18005d130
- EXTERNAL:0000001d HasLevel
- EXTERNAL:000000c7 operator<<
- EXTERNAL:000000f3 _invalid_parameter_noinfo_noreturn
- 180039bd0 GetOrderedQuantity
- 180025820 ClassicFillSheet
- 18003d4e0 FUN_18003d4e0
- 1800429b0 FUN_1800429b0
- 18000fbe0 IntermediateSheet
- 18000c160 GetOneUpHandle
- 18005d370 __security_check_cookie
- 18003dba0 FUN_18003dba0
- 18001ba80 FUN_18001ba80
- 180039c00 GetProduceCount
- EXTERNAL:0000001c ~Guard
- 180039c60 IsMaximumFill
- 180038fd0 OrderedStation
- 1800261f0 ClassicMinimalLayouts
- 180001280 FUN_180001280
- 18000ef50 FUN_18000ef50
- 18005d16c free
- 18000e4a0 FUN_18000e4a0
- 18000e640 FUN_18000e640
- 180039bf0 GetPlacedStations
- 180040910 FUN_180040910

## Strings referenciadas
- 18007c380 : 0x2b992ddfa232
- 180063878 : 0007acb4
- 180064b98 : nesting.timings
- 1800633f0 : 000786de
- 1800633e0 : 000786a6
- 180064bb0 : #nestingchecks : 
- 1800634b0 : 00079fd2
- 1800635b0 : 0007a826
- 180064bac : 0x2e
- 180064ba8 : 0x20
- 180063498 : 00079ef6
- 1800633e8 : 000786c2

## Pseudocodigo (Ghidra Decompiler)
```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: virtual class std::vector<class LayoutEngine::IntermediateSheet,class
   std::allocator<class LayoutEngine::IntermediateSheet> > __cdecl
   LayoutEngine::NestingSheetGenerator::GenerateClassicSolution(class std::vector<class
   LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > const &
   __ptr64,bool) __ptr64 */

vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> * __thiscall
LayoutEngine::NestingSheetGenerator::GenerateClassicSolution
          (NestingSheetGenerator *this,
          vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_>
          *param_1,bool param_2)

{
  undefined8 uVar1;
  IntermediateSheet *this_00;
  undefined1 auVar2 [16];
  double dVar3;
  longlong *plVar4;
  bool bVar5;
  bool bVar6;
  __uint64 _Var7;
  __int64 _Var8;
  undefined8 *puVar9;
  longlong lVar10;
  vector<LayoutEngine::OutputStation,std::allocator<LayoutEngine::OutputStation>_> *pvVar11;
  ulonglong *puVar12;
  basic_ostream<char,std::char_traits<char>_> *pbVar13;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar14;
  longlong *plVar15;
  ulonglong uVar16;
  OrderedStation *pOVar17;
  OrderedStation *pOVar18;
  OrderedStation *pOVar19;
  undefined7 in_register_00000081;
  Guard in_R9B;
  char cVar20;
  undefined4 uVar21;
  uint uVar22;
  undefined1 auStack_1b8 [32];
  Guard local_198;
  char local_197;
  uint local_194;
  OrderedStation *local_190;
  OrderedStation *local_188;
  OrderedStation *local_180;
  OrderedStation **local_178;
  longlong *local_170;
  OrderedStation *local_168;
  OrderedStation *pOStack_160;
  OrderedStation *local_158;
  OrderedStation *local_150;
  OrderedStation *pOStack_148;
  OrderedStation *local_140;
  undefined8 local_138;
  undefined8 local_130;
  undefined8 local_128;
  longlong local_120;
  undefined8 local_118;
  longlong local_110;
  undefined8 local_108;
  undefined8 local_100;
  NestingSheetGenerator *local_f8;
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *local_f0;
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> *local_e8;
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> local_e0 [24];
  longlong local_c8 [2];
  longlong local_b8 [3];
  vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> local_a0 [24];
  longlong local_88 [2];
  longlong local_78 [3];
  OrderedStation *local_60;
  OrderedStation *pOStack_58;
  OrderedStation **local_50;
  ulonglong local_48;
  ulonglong local_40;
  
                    /* 0x28490  125
                       ?GenerateClassicSolution@NestingSheetGenerator@LayoutEngine@@UEAA?AV?$vector@VIntermediateSheet@LayoutEngine@@V?$allocator@VIntermediateSheet@LayoutEngine@@@std@@@std@@AEBV?$vector@VOrderedStation@LayoutEngine@@V?$allocator@VOrderedStation@LayoutEngine@@@std@@@4@_N@Z
                        */
  plVar15 = (longlong *)CONCAT71(in_register_00000081,param_2);
  local_40 = DAT_18007c380 ^ (ulonglong)auStack_1b8;
  local_194 = 0;
  local_198 = in_R9B;
  local_170 = plVar15;
  local_f8 = this;
  local_f0 = param_1;
  local_e8 = param_1;
  FUN_1800429b0();
  FUN_18000f8e0((ulonglong *)&local_190,plVar15);
  *(undefined8 *)param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  uVar22 = 1;
  local_194 = 1;
  local_197 = FUN_18003cc70(plVar15);
  if (local_190 == local_188) {
LAB_180028add:
    puVar12 = (ulonglong *)FUN_180040910();
    local_50 = (OrderedStation **)0xf;
    local_48 = 0xf;
    local_60 = (void *)0x2e676e697473656e;
    pOStack_58 = (OrderedStation *)0x73676e696d6974;
    bVar6 = Logging::HasLevel((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                              &local_60,10);
    if (0xf < local_48) {
      pOVar17 = local_60;
      if ((0xfff < local_48 + 1) &&
         (pOVar17 = *(OrderedStation **)((longlong)local_60 + -8),
         0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)pOVar17)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pOVar17);
    }
    if (bVar6) {
      Logging::Guard::Guard(&local_198);
      pbVar13 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)clog_exref,
                              "#nestingchecks : ");
      pbVar14 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          (pbVar13,*puVar12 / 1000000);
      pbVar13 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)pbVar14,".");
      auVar2._8_8_ = 0;
      auVar2._0_8_ = *puVar12 % 1000000;
      lVar10 = SUB168(ZEXT816(0x624dd2f1a9fbe77) * auVar2,8);
      pbVar14 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          (pbVar13,lVar10 + (*puVar12 % 1000000 - lVar10 >> 1) >> 9);
      pbVar13 = FUN_180001280((basic_ostream<char,std::char_traits<char>_> *)pbVar14," M");
      std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_180001dd0);
      Logging::Guard::~Guard(&local_198);
    }
    FUN_18001ba80((longlong *)&local_190);
    return param_1;
  }
  do {
    bVar6 = true;
    uVar21 = 1;
    local_178 = (OrderedStation **)CONCAT44(local_178._4_4_,1);
    pOVar17 = local_190;
    if (local_190 != local_188) {
      do {
        bVar5 = OrderedStation::IsMaximumFill(pOVar17);
        if (!bVar5) {
          bVar6 = false;
          _Var7 = OrderedStation::GetOrderedQuantity(pOVar17);
          if (1 < _Var7) {
            uVar21 = 0;
          }
        }
        pOVar17 = pOVar17 + 0x90;
      } while (pOVar17 != local_188);
      local_178 = (OrderedStation **)CONCAT44(local_178._4_4_,uVar21);
    }
    plVar4 = local_170;
    cVar20 = (char)uVar21;
    if ((local_197 != '\0') && (!bVar6)) {
      pOVar17 = (OrderedStation *)*plVar15;
      if (pOVar17 != (OrderedStation *)local_170[1]) {
        do {
          bVar5 = OrderedStation::IsMaximumFill(pOVar17);
          if (bVar5) {
            _Var8 = GridStationLayout::GetOneUpHandle((GridStationLayout *)pOVar17);
            pOVar19 = local_188;
            pOVar18 = local_190;
            if (local_190 != local_188) {
              do {
                bVar5 = FUN_18003dba0((GridStationLayout *)pOVar18,_Var8);
                if (bVar5) break;
                pOVar18 = pOVar18 + 0x90;
              } while (pOVar18 != pOVar19);
              if (pOVar18 != local_188) goto LAB_18002863f;
            }
            if (local_188 == local_180) {
              FUN_18000e640((longlong *)&local_190,local_188,pOVar17);
            }
            else {
              OrderedStation::OrderedStation(local_188,pOVar17);
              local_188 = local_188 + 0x90;
            }
          }
LAB_18002863f:
          pOVar17 = pOVar17 + 0x90;
        } while (pOVar17 != (OrderedStation *)plVar4[1]);
        cVar20 = (char)local_178;
      }
    }
    pOVar17 = local_190;
    if (cVar20 == '\0') {
      if (bVar6) goto LAB_180028697;
      if (local_198 == (Guard)0x0) goto LAB_1800287a5;
      puVar9 = (undefined8 *)ClassicMinimalLayouts(local_f8,local_a0);
      uVar22 = uVar22 | 2;
    }
    else {
      if (bVar6) {
LAB_180028697:
        pOVar19 = local_190 + 0x90;
        local_150 = (OrderedStation *)0x0;
        pOStack_148 = (OrderedStation *)0x0;
        local_140 = (OrderedStation *)0x0;
        uVar16 = ((longlong)pOVar19 - (longlong)local_190) / 0x90;
        if (uVar16 != 0) {
          if (0x1c71c71c71c71c7 < uVar16) {
LAB_180028c6b:
                    /* WARNING: Subroutine does not return */
            FUN_180004800();
          }
          uVar16 = uVar16 * 0x90;
          if (uVar16 < 0x1000) {
            if (uVar16 == 0) {
              pOVar18 = (OrderedStation *)0x0;
            }
            else {
              pOVar18 = (OrderedStation *)FUN_18005d130(uVar16);
            }
          }
          else {
            if (uVar16 + 0x27 <= uVar16) {
LAB_180028c71:
                    /* WARNING: Subroutine does not return */
              FUN_180004720();
            }
            lVar10 = FUN_18005d130(uVar16 + 0x27);
            if (lVar10 == 0) {
LAB_180028abc:
                    /* WARNING: Subroutine does not return */
              _invalid_parameter_noinfo_noreturn();
            }
            pOVar18 = (OrderedStation *)(lVar10 + 0x27U & 0xffffffffffffffe0);
            *(longlong *)(pOVar18 + -8) = lVar10;
          }
          local_140 = pOVar18 + uVar16;
          local_178 = &local_150;
          local_50 = &local_150;
          local_150 = pOVar18;
          pOStack_148 = pOVar18;
          local_60 = pOVar18;
          for (; pOStack_58 = pOVar18, pOVar17 != pOVar19; pOVar17 = pOVar17 + 0x90) {
            OrderedStation::OrderedStation(pOVar18,pOVar17);
            pOVar18 = pOVar18 + 0x90;
          }
          pOStack_148 = pOVar18;
        }
        uVar22 = uVar22 | 4;
      }
      else {
LAB_1800287a5:
        local_168 = (OrderedStation *)0x0;
        pOStack_160 = (OrderedStation *)0x0;
        local_158 = (OrderedStation *)0x0;
        uVar16 = ((longlong)local_188 - (longlong)local_190) / 0x90;
        if (uVar16 != 0) {
          if (0x1c71c71c71c71c7 < uVar16) goto LAB_180028c6b;
          uVar16 = uVar16 * 0x90;
          if (uVar16 < 0x1000) {
            if (uVar16 == 0) {
              pOVar17 = (OrderedStation *)0x0;
            }
            else {
              pOVar17 = (OrderedStation *)FUN_18005d130(uVar16);
            }
          }
          else {
            if (uVar16 + 0x27 <= uVar16) goto LAB_180028c71;
            lVar10 = FUN_18005d130(uVar16 + 0x27);
            if (lVar10 == 0) goto LAB_180028abc;
            pOVar17 = (OrderedStation *)(lVar10 + 0x27U & 0xffffffffffffffe0);
            *(longlong *)(pOVar17 + -8) = lVar10;
          }
          pOVar18 = local_188;
          local_158 = pOVar17 + uVar16;
          local_178 = &local_168;
          local_50 = &local_168;
          local_168 = pOVar17;
          pOStack_160 = pOVar17;
          local_60 = pOVar17;
          for (pOVar19 = local_190; pOStack_58 = pOVar17, pOVar19 != pOVar18;
              pOVar19 = pOVar19 + 0x90) {
            OrderedStation::OrderedStation(pOVar17,pOVar19);
            pOVar17 = pOVar17 + 0x90;
          }
          pOStack_160 = pOVar17;
        }
        uVar22 = uVar22 | 8;
      }
      local_194 = uVar22;
      puVar9 = (undefined8 *)ClassicFillSheet(local_f8,local_e0);
      uVar22 = uVar22 | 0x10;
    }
    local_138 = *puVar9;
    local_130 = puVar9[1];
    local_128 = puVar9[2];
    local_120 = 0;
    local_118 = 0;
    local_194 = uVar22;
    lVar10 = FUN_18005d130(0x30);
    *(longlong *)lVar10 = lVar10;
    *(longlong *)(lVar10 + 8) = lVar10;
    *(longlong *)(lVar10 + 0x10) = lVar10;
    *(undefined2 *)(lVar10 + 0x18) = 0x101;
    local_120 = puVar9[3];
    puVar9[3] = lVar10;
    uVar1 = puVar9[4];
    puVar9[4] = local_118;
    local_100 = puVar9[7];
    puVar9[7] = 0;
    local_108 = puVar9[6];
    puVar9[6] = 0;
    local_110 = puVar9[5];
    puVar9[5] = 0;
    local_118 = uVar1;
    if ((uVar22 & 0x10) != 0) {
      uVar22 = uVar22 & 0xffffffef;
      local_194 = uVar22;
      FUN_18001bb40(local_b8);
      FUN_18000ef50(local_c8,local_c8);
    }
    if ((uVar22 & 8) != 0) {
      uVar22 = uVar22 & 0xfffffff7;
      local_194 = uVar22;
      FUN_18001ba80((longlong *)&local_168);
    }
    if ((uVar22 & 4) != 0) {
      uVar22 = uVar22 & 0xfffffffb;
      local_194 = uVar22;
      FUN_18001ba80((longlong *)&local_150);
    }
    if ((uVar22 & 2) != 0) {
      uVar22 = uVar22 & 0xfffffffd;
      local_194 = uVar22;
      FUN_18001bb40(local_78);
      FUN_18000ef50(local_88,local_88);
    }
    pvVar11 = OutputSheet::GetPlacedStations((OutputSheet *)&local_138);
    dVar3 = FUN_18003d4e0((longlong *)&local_190,(longlong *)pvVar11);
    dVar3 = floor(dVar3);
    IntermediateSheet::SetProduceCount((IntermediateSheet *)&local_138,(longlong)(int)dVar3);
    _Var7 = IntermediateSheet::GetProduceCount((IntermediateSheet *)&local_138);
    if (_Var7 == 0) {
      FUN_18001bb40(&local_110);
      FUN_18000ef50(&local_120,&local_120);
      param_1 = local_f0;
      goto LAB_180028add;
    }
    uVar16 = 0;
    _Var7 = IntermediateSheet::GetProduceCount((IntermediateSheet *)&local_138);
    if (_Var7 != 0) {
      do {
        pvVar11 = OutputSheet::GetPlacedStations((OutputSheet *)&local_138);
        FUN_18003e100(&local_190,(longlong *)pvVar11);
        uVar16 = uVar16 + 1;
        _Var7 = IntermediateSheet::GetProduceCount((IntermediateSheet *)&local_138);
      } while (uVar16 < _Var7);
    }
    param_1 = local_f0;
    this_00 = *(IntermediateSheet **)(local_f0 + 8);
    if (this_00 == *(IntermediateSheet **)(local_f0 + 0x10)) {
      FUN_18000e4a0((longlong *)local_f0,this_00,(IntermediateSheet *)&local_138);
    }
    else {
      IntermediateSheet::IntermediateSheet(this_00,(IntermediateSheet *)&local_138);
      *(longlong *)(param_1 + 8) = *(longlong *)(param_1 + 8) + 0x40;
    }
    FUN_18001bb40(&local_110);
    FUN_18000ef50(&local_120,&local_120);
    if (local_190 == local_188) goto LAB_180028add;
    plVar15 = local_170;
  } while( true );
}


```
