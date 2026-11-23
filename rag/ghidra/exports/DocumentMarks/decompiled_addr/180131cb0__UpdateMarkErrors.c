// DocumentMarks.dll 180131cb0 DocumentMarks::PDFPlusBearerBar::UpdateMarkErrors
// signature: void UpdateMarkErrors(PDFPlusBearerBar * this, bool param_1)

/* public: virtual void __cdecl DocumentMarks::PDFPlusBearerBar::UpdateMarkErrors(bool) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusBearerBar::UpdateMarkErrors(PDFPlusBearerBar *this,bool param_1)

{
  undefined8 uVar1;
  void *pvVar2;
  void *local_38;
  undefined8 local_30;
  longlong lStack_28;
  void *local_20;
  undefined8 local_18;
  longlong local_10;
  
                    /* 0x131cb0  1731  ?UpdateMarkErrors@PDFPlusBearerBar@DocumentMarks@@UEAAX_N@Z
                        */
  uVar1 = FUN_180105b40(&local_38,this,&DAT_180417788);
  FUN_180130a20(&local_20,uVar1);
  if (local_38 != (void *)0x0) {
    FUN_180010320(local_38,local_30,&local_38);
    pvVar2 = local_38;
    if ((0xfff < (lStack_28 - (longlong)local_38 & 0xfffffffffffffff0U)) &&
       (pvVar2 = *(void **)((longlong)local_38 + -8),
       0x1f < (ulonglong)((longlong)local_38 + (-8 - (longlong)pvVar2)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar2);
    local_38 = (void *)0x0;
    local_30 = 0;
    lStack_28 = 0;
  }
  FUN_180108070(this,&local_20,param_1);
  if (local_20 != (void *)0x0) {
    FUN_180010320(local_20,local_18,&local_20);
    pvVar2 = local_20;
    if ((0xfff < (local_10 - (longlong)local_20 & 0xfffffffffffffff0U)) &&
       (pvVar2 = *(void **)((longlong)local_20 + -8),
       0x1f < (ulonglong)((longlong)local_20 + (-8 - (longlong)pvVar2)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar2);
  }
  return;
}


