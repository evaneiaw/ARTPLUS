// 18013d750 UpdateMarkErrors

/* public: virtual void __cdecl DocumentMarks::PDFPlusCutMark::UpdateMarkErrors(bool) __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::UpdateMarkErrors(PDFPlusCutMark *this,bool param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  void *pvVar7;
  undefined1 local_48 [8];
  longlong *local_40;
  void *local_38;
  undefined8 *local_30;
  undefined8 *local_28;
  void *local_20;
  undefined8 local_18;
  longlong lStack_10;
  
                    /* 0x13d750  1733  ?UpdateMarkErrors@PDFPlusCutMark@DocumentMarks@@UEAAX_N@Z */
  uVar5 = FUN_180105b40(&local_20,this,&DAT_180417790);
  FUN_180130a20(&local_38,uVar5);
  if (local_20 != (void *)0x0) {
    FUN_180010320(local_20,local_18,&local_20);
    pvVar7 = local_20;
    if ((0xfff < (lStack_10 - (longlong)local_20 & 0xfffffffffffffff0U)) &&
       (pvVar7 = *(void **)((longlong)local_20 + -8),
       0x1f < (ulonglong)((longlong)local_20 + (-8 - (longlong)pvVar7)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar7);
    local_20 = (void *)0x0;
    local_18 = 0;
    lStack_10 = 0;
  }
  if (this[0x700] != (PDFPlusCutMark)0x0) {
    puVar6 = (undefined8 *)FUN_1801068f0(local_48,this + 0x6c0,this + 0x6e0,0x7d,0x7e);
    if (local_30 == local_28) {
      FUN_1801040c0(&local_38,local_30,puVar6);
    }
    else {
      *local_30 = 0;
      local_30[1] = 0;
      *local_30 = *puVar6;
      local_30[1] = puVar6[1];
      *puVar6 = 0;
      puVar6[1] = 0;
      local_30 = local_30 + 2;
    }
    if (local_40 != (longlong *)0x0) {
      LOCK();
      plVar1 = local_40 + 1;
      lVar4 = *plVar1;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)lVar4 == 1) {
        (**(code **)*local_40)(local_40);
        LOCK();
        piVar2 = (int *)((longlong)local_40 + 0xc);
        iVar3 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar3 == 1) {
          (**(code **)(*local_40 + 8))(local_40);
        }
      }
    }
  }
  FUN_180108070(this,&local_38,param_1);
  if (local_38 != (void *)0x0) {
    FUN_180010320(local_38,local_30,&local_38);
    pvVar7 = local_38;
    if ((0xfff < ((longlong)local_28 - (longlong)local_38 & 0xfffffffffffffff0U)) &&
       (pvVar7 = *(void **)((longlong)local_38 + -8),
       0x1f < (ulonglong)((longlong)local_38 + (-8 - (longlong)pvVar7)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar7);
  }
  return;
}


