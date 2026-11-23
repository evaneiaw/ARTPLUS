// DocumentMarks.dll 1801300a0 DocumentMarks::PDFPlusBearerBar::ContentChangedSelf
// signature: void ContentChangedSelf(PDFPlusBearerBar * this, Content * param_1, Content * param_2)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: virtual void __cdecl DocumentMarks::PDFPlusBearerBar::ContentChangedSelf(class
   ArtDoc::Content * __ptr64,class ArtDoc::Content * __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusBearerBar::ContentChangedSelf
          (PDFPlusBearerBar *this,Content *param_1,Content *param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  void *pvVar6;
  char cVar7;
  int iVar8;
  Document *pDVar9;
  ChangeTracker *pCVar10;
  ChangeTracker *pCVar11;
  undefined8 uVar12;
  ChangeCollector *pCVar13;
  void *pvVar14;
  PDFPlusBearerBar *pPVar15;
  undefined1 *puVar16;
  undefined1 *puVar17;
  bool bVar18;
  undefined1 auStack_208 [32];
  undefined4 local_1e8;
  PDFPlusBearerBar *local_1d8;
  longlong *local_1d0;
  undefined1 local_1c8 [8];
  longlong *local_1c0;
  ulonglong local_1b8;
  PDFPlusBearerBar *local_1b0 [5];
  void *local_188;
  void *pvStack_180;
  longlong local_178;
  ulonglong local_168;
  undefined1 local_160 [40];
  ulonglong local_138;
  undefined1 local_130 [40];
  undefined1 local_108 [160];
  ulonglong local_68;
  undefined1 *local_60;
  longlong local_58;
  undefined8 local_50;
  ulonglong local_48;
  
                    /* 0x1300a0  914
                       ?ContentChangedSelf@PDFPlusBearerBar@DocumentMarks@@MEAAXPEAVContent@ArtDoc@@0@Z
                        */
  local_48 = DAT_180418e00 ^ (ulonglong)auStack_208;
  DynamicMark::ContentChangedSelf((DynamicMark *)this,param_1,param_2);
  if (*(longlong *)(this + 0x738) != *(longlong *)(this + 0x740)) {
    *(longlong *)(this + 0x740) = *(longlong *)(this + 0x738);
  }
  if (param_1 != (Content *)0x0) {
    for (pPVar15 = this + 0x750; pPVar15 != this + 0x790; pPVar15 = pPVar15 + 0x10) {
      local_1d8 = (PDFPlusBearerBar *)0x0;
      local_1d0 = *(longlong **)(pPVar15 + 8);
      if (local_1d0 != (longlong *)0x0) {
        iVar8 = (int)local_1d0[1];
        do {
          if (iVar8 == 0) {
            local_1d0 = (longlong *)0x0;
            goto LAB_180130165;
          }
          LOCK();
          iVar3 = (int)local_1d0[1];
          bVar18 = iVar8 == iVar3;
          if (bVar18) {
            *(int *)(local_1d0 + 1) = iVar8 + 1;
          }
          else {
            iVar8 = iVar3;
          }
          UNLOCK();
        } while (!bVar18);
        if (local_1d0 != (longlong *)0x0) {
          local_1d8 = *(PDFPlusBearerBar **)pPVar15;
        }
      }
LAB_180130165:
      plVar4 = local_1d0;
      if (local_1d8 != (PDFPlusBearerBar *)0x0) {
        FUN_180019f60(local_1d8);
      }
      if (plVar4 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar4 + 1;
        lVar5 = *plVar1;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)lVar5 == 1) {
          (**(code **)(*plVar4 + 8))(plVar4);
          LOCK();
          piVar2 = (int *)((longlong)plVar4 + 0xc);
          iVar8 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar8 == 1) {
            (**(code **)(*plVar4 + 0x10))(plVar4);
          }
        }
      }
    }
  }
  if (param_2 != (Content *)0x0) {
    CollectGrids(this,param_2);
    pDVar9 = ArtDoc::Content::GetDocument(param_2);
    pCVar10 = ArtDoc::Document::GetChangeTrackerToConnectOn(pDVar9);
    local_188 = (void *)0x0;
    pvStack_180 = (void *)0x0;
    local_178 = 0;
    local_168 = 0;
    local_1d8 = this;
    cVar7 = FUN_18002ce80(&local_1d8);
    if (cVar7 == '\0') {
      local_1b0[0] = local_1d8;
      local_1b8 = 0x180322c69;
    }
    else {
      local_1b8 = 0;
    }
    local_138 = 0;
    FUN_18002dbc0(&local_138,&local_1b8);
    FUN_18002dbc0(&local_1b8,&local_168);
    FUN_18002dbc0(&local_168,&local_138);
    if (((local_138 != 0) && ((local_138 & 1) == 0)) &&
       (*(code **)(local_138 & 0xfffffffffffffffe) != (code *)0x0)) {
      (**(code **)(local_138 & 0xfffffffffffffffe))(local_130,local_130,2);
    }
    if (((local_1b8 != 0) && ((local_1b8 & 1) == 0)) &&
       (*(code **)(local_1b8 & 0xfffffffffffffffe) != (code *)0x0)) {
      (**(code **)(local_1b8 & 0xfffffffffffffffe))(local_1b0,local_1b0,2);
    }
    local_50 = *(undefined8 *)(*(longlong *)(pCVar10 + 0x210) + 0x18);
    local_68 = 10;
    local_58 = 0;
    local_1e8 = 0;
    local_60 = local_108;
    FUN_18009da20(*(longlong *)(pCVar10 + 0x210),&local_1d8,local_108,&local_188);
    if (local_60 != (undefined1 *)0x0) {
      if (local_58 != 0) {
        puVar16 = local_60 + local_58 * 0x10 + -0x10;
        puVar17 = puVar16 + local_58 * -0x10;
        for (; puVar17 < puVar16; puVar16 = puVar16 + -0x10) {
          plVar4 = *(longlong **)(puVar16 + 8);
          if (plVar4 != (longlong *)0x0) {
            LOCK();
            plVar1 = plVar4 + 1;
            lVar5 = *plVar1;
            *(int *)plVar1 = (int)*plVar1 + -1;
            UNLOCK();
            if ((int)lVar5 == 1) {
              (**(code **)(*plVar4 + 8))(plVar4);
              LOCK();
              piVar2 = (int *)((longlong)plVar4 + 0xc);
              iVar8 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar8 == 1) {
                (**(code **)(*plVar4 + 0x10))(plVar4);
              }
            }
          }
        }
      }
      if (10 < local_68) {
        puVar16 = local_60;
        if ((0xfff < local_68 << 4) &&
           (puVar16 = *(undefined1 **)(local_60 + -8),
           (undefined1 *)0x1f < local_60 + (-8 - (longlong)puVar16))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(puVar16);
      }
    }
    FUN_180029bc0(this + 0x750,&local_1d8);
    if (local_1d0 != (longlong *)0x0) {
      LOCK();
      piVar2 = (int *)((longlong)local_1d0 + 0xc);
      iVar8 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar8 == 1) {
        (**(code **)(*local_1d0 + 0x10))();
      }
    }
    if (local_168 != 0) {
      if (((local_168 & 1) == 0) && (*(code **)(local_168 & 0xfffffffffffffffe) != (code *)0x0)) {
        (**(code **)(local_168 & 0xfffffffffffffffe))(local_160,local_160,2);
      }
      local_168 = 0;
    }
    pvVar6 = pvStack_180;
    pvVar14 = local_188;
    if (local_188 != (void *)0x0) {
      for (; pvVar14 != pvVar6; pvVar14 = (void *)((longlong)pvVar14 + 0x18)) {
        FUN_18002c1e0(pvVar14);
      }
      pvVar14 = local_188;
      if ((0xfff < (ulonglong)(((local_178 - (longlong)local_188) / 0x18) * 0x18)) &&
         (pvVar14 = *(void **)((longlong)local_188 + -8),
         0x1f < (ulonglong)((longlong)local_188 + (-8 - (longlong)pvVar14)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar14);
    }
    pDVar9 = ArtDoc::Content::GetDocument(param_2);
    pCVar11 = GetChangeTracker(pDVar9);
    local_188 = (void *)0x0;
    pvStack_180 = (void *)0x0;
    local_178 = 0;
    local_168 = 0;
    local_1d8 = this;
    cVar7 = FUN_18002ce80(&local_1d8);
    if (cVar7 == '\0') {
      local_1b0[0] = local_1d8;
      local_1b8 = 0x180322c79;
    }
    else {
      local_1b8 = 0;
    }
    FUN_18002e680(&local_1b8,&local_168);
    if (((local_1b8 != 0) && ((local_1b8 & 1) == 0)) &&
       (*(code **)(local_1b8 & 0xfffffffffffffffe) != (code *)0x0)) {
      (**(code **)(local_1b8 & 0xfffffffffffffffe))(local_1b0,local_1b0,2);
    }
    uVar12 = FUN_180032cc0(pCVar11 + 0x1a0,local_1c8,&local_188,0);
    FUN_180029bc0(this + 0x760,uVar12);
    if (local_1c0 != (longlong *)0x0) {
      LOCK();
      piVar2 = (int *)((longlong)local_1c0 + 0xc);
      iVar8 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar8 == 1) {
        (**(code **)(*local_1c0 + 0x10))();
      }
    }
    if (local_168 != 0) {
      if (((local_168 & 1) == 0) && (*(code **)(local_168 & 0xfffffffffffffffe) != (code *)0x0)) {
        (**(code **)(local_168 & 0xfffffffffffffffe))(local_160,local_160,2);
      }
      local_168 = 0;
    }
    FUN_18002b2e0(&local_188);
    pDVar9 = ArtDoc::Content::GetDocument(param_2);
    pCVar11 = GetChangeTracker(pDVar9);
    local_188 = (void *)0x0;
    pvStack_180 = (void *)0x0;
    local_178 = 0;
    local_168 = 0;
    local_1d8 = this;
    cVar7 = FUN_18002ce80(&local_1d8);
    if (cVar7 == '\0') {
      local_1b0[0] = local_1d8;
      local_1b8 = 0x180322c89;
    }
    else {
      local_1b8 = 0;
    }
    FUN_18002e680(&local_1b8,&local_168);
    if (((local_1b8 != 0) && ((local_1b8 & 1) == 0)) &&
       (*(code **)(local_1b8 & 0xfffffffffffffffe) != (code *)0x0)) {
      (**(code **)(local_1b8 & 0xfffffffffffffffe))(local_1b0,local_1b0,2);
    }
    uVar12 = FUN_180032cc0(pCVar11 + 0x180,local_1c8,&local_188,0);
    FUN_180029bc0(this + 0x770,uVar12);
    if (local_1c0 != (longlong *)0x0) {
      LOCK();
      piVar2 = (int *)((longlong)local_1c0 + 0xc);
      iVar8 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar8 == 1) {
        (**(code **)(*local_1c0 + 0x10))();
      }
    }
    if (local_168 != 0) {
      if (((local_168 & 1) == 0) && (*(code **)(local_168 & 0xfffffffffffffffe) != (code *)0x0)) {
        (**(code **)(local_168 & 0xfffffffffffffffe))(local_160,local_160,2);
      }
      local_168 = 0;
    }
    pvVar6 = pvStack_180;
    pvVar14 = local_188;
    if (local_188 != (void *)0x0) {
      for (; pvVar14 != pvVar6; pvVar14 = (void *)((longlong)pvVar14 + 0x18)) {
        FUN_18002c1e0(pvVar14);
      }
      pvVar14 = local_188;
      if ((0xfff < (ulonglong)(((local_178 - (longlong)local_188) / 0x18) * 0x18)) &&
         (pvVar14 = *(void **)((longlong)local_188 + -8),
         0x1f < (ulonglong)((longlong)local_188 + (-8 - (longlong)pvVar14)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar14);
    }
    cVar7 = FUN_180119ee0();
    if (cVar7 == '\0') {
      pDVar9 = ArtDoc::Content::GetDocument(param_2);
      pCVar13 = ArtDoc::Document::GetChangeCollector(pDVar9);
      local_188 = (void *)0x0;
      pvStack_180 = (void *)0x0;
      local_178 = 0;
      local_168 = 0;
      local_1d8 = this;
      cVar7 = FUN_18002ce80(&local_1d8);
      if (cVar7 == '\0') {
        local_1b0[0] = local_1d8;
        local_1b8 = 0x180322c99;
      }
      else {
        local_1b8 = 0;
      }
      local_138 = 0;
      FUN_18002dbc0(&local_138,&local_1b8);
      FUN_18002dbc0(&local_1b8,&local_168);
      FUN_18002dbc0(&local_168,&local_138);
      if (((local_138 != 0) && ((local_138 & 1) == 0)) &&
         (*(code **)(local_138 & 0xfffffffffffffffe) != (code *)0x0)) {
        (**(code **)(local_138 & 0xfffffffffffffffe))(local_130,local_130,2);
      }
      if (((local_1b8 != 0) && ((local_1b8 & 1) == 0)) &&
         (*(code **)(local_1b8 & 0xfffffffffffffffe) != (code *)0x0)) {
        (**(code **)(local_1b8 & 0xfffffffffffffffe))(local_1b0,local_1b0,2);
      }
      local_50 = *(undefined8 *)(*(longlong *)(pCVar13 + 0x30) + 0x18);
      local_68 = 10;
      local_58 = 0;
      local_1e8 = 0;
      local_60 = local_108;
      FUN_18008d310(*(longlong *)(pCVar13 + 0x30),&local_1d8,local_108,&local_188);
      if (local_60 != (undefined1 *)0x0) {
        if (local_58 != 0) {
          puVar16 = local_60 + local_58 * 0x10 + -0x10;
          puVar17 = puVar16 + local_58 * -0x10;
          for (; puVar17 < puVar16; puVar16 = puVar16 + -0x10) {
            plVar4 = *(longlong **)(puVar16 + 8);
            if (plVar4 != (longlong *)0x0) {
              LOCK();
              plVar1 = plVar4 + 1;
              lVar5 = *plVar1;
              *(int *)plVar1 = (int)*plVar1 + -1;
              UNLOCK();
              if ((int)lVar5 == 1) {
                (**(code **)(*plVar4 + 8))(plVar4);
                LOCK();
                piVar2 = (int *)((longlong)plVar4 + 0xc);
                iVar8 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar8 == 1) {
                  (**(code **)(*plVar4 + 0x10))(plVar4);
                }
              }
            }
          }
        }
        if (10 < local_68) {
          puVar16 = local_60;
          if ((0xfff < local_68 << 4) &&
             (puVar16 = *(undefined1 **)(local_60 + -8),
             (undefined1 *)0x1f < local_60 + (-8 - (longlong)puVar16))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(puVar16);
        }
      }
      FUN_180029bc0(this + 0x780,&local_1d8);
      if (local_1d0 != (longlong *)0x0) {
        LOCK();
        piVar2 = (int *)((longlong)local_1d0 + 0xc);
        iVar8 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar8 == 1) {
          (**(code **)(*local_1d0 + 0x10))();
        }
      }
      if (local_168 != 0) {
        if (((local_168 & 1) == 0) && (*(code **)(local_168 & 0xfffffffffffffffe) != (code *)0x0)) {
          (**(code **)(local_168 & 0xfffffffffffffffe))(local_160,local_160,2);
        }
        local_168 = 0;
      }
      pvVar6 = pvStack_180;
      pvVar14 = local_188;
      if (local_188 != (void *)0x0) {
        for (; pvVar14 != pvVar6; pvVar14 = (void *)((longlong)pvVar14 + 0x18)) {
          FUN_18002c1e0(pvVar14);
        }
        pvVar14 = local_188;
        if ((0xfff < (ulonglong)(((local_178 - (longlong)local_188) / 0x18) * 0x18)) &&
           (pvVar14 = *(void **)((longlong)local_188 + -8),
           0x1f < (ulonglong)((longlong)local_188 + (-8 - (longlong)pvVar14)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar14);
      }
    }
  }
  return;
}


