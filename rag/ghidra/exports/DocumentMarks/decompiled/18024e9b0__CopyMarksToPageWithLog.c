// 18024e9b0 CopyMarksToPageWithLog

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: void __cdecl DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog(class ArtDoc::Page &
   __ptr64,class ArtDoc::Page & __ptr64,bool) __ptr64 */

void __thiscall
DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog
          (TaskMarkSets *this,Page *param_1,Page *param_2,bool param_3)

{
  undefined2 *puVar1;
  char cVar2;
  code *pcVar3;
  undefined1 uVar4;
  longlong lVar5;
  longlong *plVar6;
  bool bVar7;
  PageContent *pPVar8;
  Document *pDVar9;
  __uint64 _Var10;
  undefined8 *****pppppuVar11;
  ulonglong uVar12;
  longlong *plVar13;
  undefined8 *****pppppuVar14;
  ulonglong uVar15;
  char *pcVar16;
  longlong *plVar17;
  void *pvVar18;
  undefined1 auStackY_158 [32];
  undefined1 local_118 [8];
  longlong *local_110;
  longlong local_108;
  longlong *local_100;
  longlong local_f8;
  Page *local_f0;
  TaskMarkSets *local_e8;
  Page *local_d8;
  undefined8 *****local_d0;
  undefined8 uStack_c8;
  longlong local_c0;
  ulonglong local_b8;
  undefined8 *****local_b0 [3];
  ulonglong local_98;
  undefined8 *****local_90 [3];
  ulonglong local_78;
  char local_5c [4];
  ulonglong local_58;
  
                    /* 0x24e9b0  939
                       ?CopyMarksToPageWithLog@TaskMarkSets@DocumentMarks@@QEAAXAEAVPage@ArtDoc@@0_N@Z
                        */
  local_58 = DAT_180418e00 ^ (ulonglong)auStackY_158;
  local_100 = (longlong *)0x0;
  local_f8 = 0;
  local_f0 = param_2;
  local_e8 = this;
  local_d8 = param_1;
  local_100 = (longlong *)FUN_1802d6b50(0x40);
  *local_100 = (longlong)local_100;
  local_100[1] = (longlong)local_100;
  local_100[2] = (longlong)local_100;
  *(undefined2 *)(local_100 + 3) = 0x101;
  local_110 = (longlong *)0x0;
  local_108 = 0;
  local_110 = (longlong *)FUN_1802d6b50(0x40);
  *local_110 = (longlong)local_110;
  local_110[1] = (longlong)local_110;
  local_110[2] = (longlong)local_110;
  *(undefined2 *)(local_110 + 3) = 0x101;
  bVar7 = CopyMarksToPage(param_1,param_2,param_3,
                          (set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
                           *)&local_100,
                          (set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
                           *)&local_110,
                          (set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_>
                           *)0x0,true);
  if ((!bVar7) && (local_f8 != 0)) {
    pPVar8 = ArtDoc::Page::GetContent(param_1);
    pDVar9 = ArtDoc::Content::GetDocument((Content *)pPVar8);
    ArtDoc::Document::GetFilePath(pDVar9);
    boost::filesystem::detail::path_algorithms::stem_v3((path *)local_b0);
    ExtraBoostFilesystem::ToUTF8String((path *)local_90);
    FUN_180019310(local_b0);
    uVar4 = local_118[0];
    uStack_c8 = 0;
    local_c0 = 0;
    local_b8 = 0xf;
    local_d0 = (undefined8 *****)0x0;
    plVar13 = (longlong *)*local_100;
    if (*(char *)((longlong)plVar13 + 0x19) == '\0') {
      do {
        lVar5 = local_c0;
        plVar17 = plVar13 + 4;
        if (local_c0 != 0) {
          if (local_b8 - local_c0 < 2) {
            FUN_18003ccc0(&local_d0,2,uVar4,&DAT_180335d14);
          }
          else {
            pppppuVar11 = &local_d0;
            if (0xf < local_b8) {
              pppppuVar11 = local_d0;
            }
            puVar1 = (undefined2 *)((longlong)pppppuVar11 + local_c0);
            local_c0 = local_c0 + 2;
            *puVar1 = 0x202c;
            *(undefined1 *)((longlong)pppppuVar11 + lVar5 + 2) = 0;
          }
        }
        uVar15 = plVar13[6];
        if (0xf < (ulonglong)plVar13[7]) {
          plVar17 = (longlong *)*plVar17;
        }
        if (local_b8 - local_c0 < uVar15) {
          FUN_18003ccc0(&local_d0,uVar15,uVar4,plVar17);
        }
        else {
          pppppuVar11 = &local_d0;
          if (0xf < local_b8) {
            pppppuVar11 = local_d0;
          }
          pvVar18 = (void *)((longlong)pppppuVar11 + local_c0);
          local_c0 = local_c0 + uVar15;
          memmove(pvVar18,plVar17,uVar15);
          *(undefined1 *)((longlong)pvVar18 + uVar15) = 0;
        }
        plVar17 = (longlong *)plVar13[2];
        if (*(char *)((longlong)plVar17 + 0x19) == '\0') {
          cVar2 = *(char *)(*plVar17 + 0x19);
          plVar13 = plVar17;
          plVar17 = (longlong *)*plVar17;
          while (cVar2 == '\0') {
            cVar2 = *(char *)(*plVar17 + 0x19);
            plVar13 = plVar17;
            plVar17 = (longlong *)*plVar17;
          }
        }
        else {
          cVar2 = *(char *)(plVar13[1] + 0x19);
          plVar6 = (longlong *)plVar13[1];
          plVar17 = plVar13;
          while ((plVar13 = plVar6, cVar2 == '\0' && (plVar17 == (longlong *)plVar13[2]))) {
            cVar2 = *(char *)(plVar13[1] + 0x19);
            plVar6 = (longlong *)plVar13[1];
            plVar17 = plVar13;
          }
        }
      } while (*(char *)((longlong)plVar13 + 0x19) == '\0');
      param_2 = local_f0;
      param_1 = local_d8;
      this = local_e8;
    }
    plVar13 = *(longlong **)(this + 0x158);
    pcVar3 = *(code **)(*plVar13 + 0x48);
    ArtDoc::Page::GetPageIndex(param_2);
    pppppuVar11 = local_90;
    if (0xf < local_78) {
      pppppuVar11 = local_90[0];
    }
    pppppuVar14 = &local_d0;
    if (0xf < local_b8) {
      pppppuVar14 = local_d0;
    }
    (*pcVar3)(plVar13,
              "WARNING: Missing Named Objects: %s.\nReferenced from Mark Set: %s.\nDynamic Marks linked to a missing object were removed from page %lu.\n"
              ,pppppuVar14,pppppuVar11);
    plVar13 = *(longlong **)(this + 0x158);
    pcVar3 = *(code **)(*plVar13 + 0x18);
    _Var10 = ArtDoc::Page::GetPageIndex(param_2);
    pcVar16 = local_5c + 1;
    uVar15 = _Var10 + 1;
    do {
      pcVar16 = pcVar16 + -1;
      uVar12 = uVar15 / 10;
      *pcVar16 = (char)uVar15 + (char)uVar12 * -10 + '0';
      uVar15 = uVar12;
    } while (uVar12 != 0);
    FUN_18000f620(local_b0,pcVar16,local_5c + 1,local_118);
    pppppuVar11 = local_b0;
    if (0xf < local_98) {
      pppppuVar11 = local_b0[0];
    }
    (*pcVar3)(plVar13,1,"DocumentMarks.Warning.MissingNamedObject",pppppuVar11);
    if (0xf < local_98) {
      pppppuVar11 = local_b0[0];
      if ((0xfff < local_98 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_b0[0][-1],
         0x1f < (ulonglong)((longlong)local_b0[0] + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
    if (0xf < local_b8) {
      pppppuVar11 = local_d0;
      if ((0xfff < local_b8 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_d0[-1],
         0x1f < (ulonglong)((longlong)local_d0 + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
    local_c0 = 0;
    local_b8 = 0xf;
    local_d0 = (undefined8 *****)((ulonglong)local_d0 & 0xffffffffffffff00);
    if (0xf < local_78) {
      pppppuVar11 = local_90[0];
      if ((0xfff < local_78 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_90[0][-1],
         0x1f < (ulonglong)((longlong)local_90[0] + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
  }
  if (local_108 != 0) {
    pPVar8 = ArtDoc::Page::GetContent(param_1);
    pDVar9 = ArtDoc::Content::GetDocument((Content *)pPVar8);
    ArtDoc::Document::GetFilePath(pDVar9);
    boost::filesystem::detail::path_algorithms::stem_v3((path *)local_90);
    ExtraBoostFilesystem::ToUTF8String((path *)local_b0);
    FUN_180019310(local_90);
    uStack_c8 = 0;
    local_c0 = 0;
    local_b8 = 0xf;
    local_d0 = (undefined8 *****)0x0;
    plVar13 = (longlong *)*local_110;
    if (*(char *)((longlong)plVar13 + 0x19) == '\0') {
      do {
        lVar5 = local_c0;
        plVar17 = plVar13 + 4;
        if (local_c0 != 0) {
          if (local_b8 - local_c0 < 2) {
            FUN_18003ccc0(&local_d0,2,local_118[0],&DAT_180335d14);
          }
          else {
            pppppuVar11 = &local_d0;
            if (0xf < local_b8) {
              pppppuVar11 = local_d0;
            }
            puVar1 = (undefined2 *)((longlong)pppppuVar11 + local_c0);
            local_c0 = local_c0 + 2;
            *puVar1 = 0x202c;
            *(undefined1 *)((longlong)pppppuVar11 + lVar5 + 2) = 0;
          }
        }
        lVar5 = local_c0;
        uVar15 = plVar13[6];
        if (0xf < (ulonglong)plVar13[7]) {
          plVar17 = (longlong *)*plVar17;
        }
        if (local_b8 - local_c0 < uVar15) {
          FUN_18003ccc0(&local_d0,uVar15,local_118[0],plVar17);
        }
        else {
          pppppuVar11 = &local_d0;
          if (0xf < local_b8) {
            pppppuVar11 = local_d0;
          }
          pvVar18 = (void *)((longlong)pppppuVar11 + local_c0);
          local_c0 = local_c0 + uVar15;
          memmove(pvVar18,plVar17,uVar15);
          *(undefined1 *)((longlong)pppppuVar11 + lVar5 + uVar15) = 0;
        }
        plVar17 = (longlong *)plVar13[2];
        if (*(char *)((longlong)plVar17 + 0x19) == '\0') {
          cVar2 = *(char *)(*plVar17 + 0x19);
          plVar13 = plVar17;
          plVar17 = (longlong *)*plVar17;
          while (cVar2 == '\0') {
            cVar2 = *(char *)(*plVar17 + 0x19);
            plVar13 = plVar17;
            plVar17 = (longlong *)*plVar17;
          }
        }
        else {
          cVar2 = *(char *)(plVar13[1] + 0x19);
          plVar6 = (longlong *)plVar13[1];
          plVar17 = plVar13;
          while ((plVar13 = plVar6, cVar2 == '\0' && (plVar17 == (longlong *)plVar13[2]))) {
            cVar2 = *(char *)(plVar13[1] + 0x19);
            plVar6 = (longlong *)plVar13[1];
            plVar17 = plVar13;
          }
        }
      } while (*(char *)((longlong)plVar13 + 0x19) == '\0');
      param_2 = local_f0;
      this = local_e8;
    }
    plVar13 = *(longlong **)(this + 0x158);
    pcVar3 = *(code **)(*plVar13 + 0x48);
    ArtDoc::Page::GetPageIndex(param_2);
    pppppuVar11 = local_b0;
    if (0xf < local_98) {
      pppppuVar11 = local_b0[0];
    }
    pppppuVar14 = &local_d0;
    if (0xf < local_b8) {
      pppppuVar14 = local_d0;
    }
    (*pcVar3)(plVar13,
              "WARNING: Missing Page Box: %s.\nReferenced from Mark Set: %s.\nDynamic Marks linked to a missing page box were relinked to available page box on page %lu.\n"
              ,pppppuVar14,pppppuVar11);
    plVar13 = *(longlong **)(this + 0x158);
    pcVar3 = *(code **)(*plVar13 + 0x18);
    _Var10 = ArtDoc::Page::GetPageIndex(param_2);
    pcVar16 = local_5c + 1;
    uVar15 = _Var10 + 1;
    do {
      pcVar16 = pcVar16 + -1;
      uVar12 = uVar15 / 10;
      *pcVar16 = (char)uVar15 + (char)uVar12 * -10 + '0';
      uVar15 = uVar12;
    } while (uVar12 != 0);
    FUN_18000f620(local_90,pcVar16,local_5c + 1,local_118);
    pppppuVar11 = local_90;
    if (0xf < local_78) {
      pppppuVar11 = local_90[0];
    }
    (*pcVar3)(plVar13,1,"DocumentMarks.Warning.MissingPageBox",pppppuVar11);
    if (0xf < local_78) {
      pppppuVar11 = local_90[0];
      if ((0xfff < local_78 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_90[0][-1],
         0x1f < (ulonglong)((longlong)local_90[0] + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
    if (0xf < local_b8) {
      pppppuVar11 = local_d0;
      if ((0xfff < local_b8 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_d0[-1],
         0x1f < (ulonglong)((longlong)local_d0 + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
    local_c0 = 0;
    local_b8 = 0xf;
    local_d0 = (undefined8 *****)((ulonglong)local_d0 & 0xffffffffffffff00);
    if (0xf < local_98) {
      pppppuVar11 = local_b0[0];
      if ((0xfff < local_98 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_b0[0][-1],
         0x1f < (ulonglong)((longlong)local_b0[0] + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
  }
  FUN_18005fae0(&local_110,&local_110,local_110[1]);
  free(local_110);
  FUN_18005fae0(&local_100,&local_100,local_100[1]);
  free(local_100);
  return;
}


