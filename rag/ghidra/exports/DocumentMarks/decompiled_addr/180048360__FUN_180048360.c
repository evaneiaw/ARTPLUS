// DocumentMarks.dll 180048360 FUN_180048360
// signature: undefined FUN_180048360(void)

ulonglong FUN_180048360(longlong param_1,PDFPlusBearerBar *param_2)

{
  undefined8 uVar1;
  ulonglong uVar2;
  ulonglong extraout_RAX;
  void *_Memory;
  void *local_28;
  longlong local_18;
  
  uVar1 = DocumentMarks::PDFPlusBearerBar::GetNecessaryReferenceObjects(param_2);
  uVar2 = FUN_180015160(param_1 + 0x10,uVar1);
  if (local_28 != (void *)0x0) {
    _Memory = local_28;
    if ((0xfff < (local_18 - (longlong)local_28 & 0xfffffffffffffff8U)) &&
       (_Memory = *(void **)((longlong)local_28 + -8),
       0x1f < (ulonglong)((longlong)local_28 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
    uVar2 = extraout_RAX;
  }
  return uVar2 & 0xffffffffffffff00;
}


