// 18013bb50 ContentChangedSelf

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: virtual void __cdecl DocumentMarks::PDFPlusCutMark::ContentChangedSelf(class
   ArtDoc::Content * __ptr64,class ArtDoc::Content * __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::ContentChangedSelf
          (PDFPlusCutMark *this,Content *param_1,Content *param_2)

{
  int *piVar1;
  int iVar2;
  longlong *plVar3;
  void *pvVar4;
  char cVar5;
  Document *this_00;
  ChangeCollector *pCVar6;
  void *pvVar7;
  undefined1 auStack_108 [32];
  PDFPlusCutMark *local_e8;
  undefined8 local_e0;
  longlong *local_d8;
  ulonglong local_d0;
  PDFPlusCutMark *local_c8 [4];
  void *local_a8;
  void *pvStack_a0;
  longlong local_98;
  ulonglong local_88;
  undefined1 local_80 [40];
  ulonglong local_58;
  undefined1 local_50 [32];
  ulonglong local_30;
  
                    /* 0x13bb50  916
                       ?ContentChangedSelf@PDFPlusCutMark@DocumentMarks@@MEAAXPEAVContent@ArtDoc@@0@Z
                        */
  local_30 = DAT_180418e00 ^ (ulonglong)auStack_108;
  DynamicMark::ContentChangedSelf((DynamicMark *)this,param_1,param_2);
  cVar5 = FUN_180119ee0();
  if (cVar5 == '\0') {
    if (param_1 != (Content *)0x0) {
      FUN_18002c560(this + 0x7b0);
    }
    if (param_2 != (Content *)0x0) {
      this_00 = ArtDoc::Content::GetDocument(param_2);
      pCVar6 = ArtDoc::Document::GetChangeCollector(this_00);
      local_a8 = (void *)0x0;
      pvStack_a0 = (void *)0x0;
      local_98 = 0;
      local_88 = 0;
      local_e8 = this;
      cVar5 = FUN_18002ce80(&local_e8);
      if (cVar5 == '\0') {
        local_c8[0] = local_e8;
        local_d0 = 0x180323499;
      }
      else {
        local_d0 = 0;
      }
      local_58 = 0;
      FUN_18002dbc0(&local_58,&local_d0);
      FUN_18002dbc0(&local_d0,&local_88);
      FUN_18002dbc0(&local_88,&local_58);
      if (((local_58 != 0) && ((local_58 & 1) == 0)) &&
         (*(code **)(local_58 & 0xfffffffffffffffe) != (code *)0x0)) {
        (**(code **)(local_58 & 0xfffffffffffffffe))(local_50,local_50,2);
      }
      if (((local_d0 != 0) && ((local_d0 & 1) == 0)) &&
         (*(code **)(local_d0 & 0xfffffffffffffffe) != (code *)0x0)) {
        (**(code **)(local_d0 & 0xfffffffffffffffe))(local_c8,local_c8,2);
      }
      FUN_18008afb0(*(undefined8 *)(pCVar6 + 0x30),&local_e0,&local_a8,0);
      if ((PDFPlusCutMark *)&local_e0 != this + 0x7b0) {
        *(undefined8 *)(this + 0x7b0) = local_e0;
        plVar3 = *(longlong **)(this + 0x7b8);
        *(longlong **)(this + 0x7b8) = local_d8;
        if (plVar3 != (longlong *)0x0) {
          LOCK();
          piVar1 = (int *)((longlong)plVar3 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            (**(code **)(*plVar3 + 0x10))();
          }
        }
        local_d8 = (longlong *)0x0;
      }
      if (local_d8 != (longlong *)0x0) {
        LOCK();
        piVar1 = (int *)((longlong)local_d8 + 0xc);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 == 1) {
          (**(code **)(*local_d8 + 0x10))();
        }
      }
      if (local_88 != 0) {
        if (((local_88 & 1) == 0) && (*(code **)(local_88 & 0xfffffffffffffffe) != (code *)0x0)) {
          (**(code **)(local_88 & 0xfffffffffffffffe))(local_80,local_80,2);
        }
        local_88 = 0;
      }
      pvVar4 = pvStack_a0;
      pvVar7 = local_a8;
      if (local_a8 != (void *)0x0) {
        for (; pvVar7 != pvVar4; pvVar7 = (void *)((longlong)pvVar7 + 0x18)) {
          FUN_18002c1e0(pvVar7);
        }
        pvVar7 = local_a8;
        if ((0xfff < (ulonglong)(((local_98 - (longlong)local_a8) / 0x18) * 0x18)) &&
           (pvVar7 = *(void **)((longlong)local_a8 + -8),
           0x1f < (ulonglong)((longlong)local_a8 + (-8 - (longlong)pvVar7)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar7);
      }
    }
  }
  return;
}


