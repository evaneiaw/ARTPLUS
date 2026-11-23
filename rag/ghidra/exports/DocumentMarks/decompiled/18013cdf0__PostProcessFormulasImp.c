// 18013cdf0 PostProcessFormulasImp

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: virtual void __cdecl DocumentMarks::PDFPlusCutMark::PostProcessFormulasImp(class
   ArtDoc::PostReadContext const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::PostProcessFormulasImp(PDFPlusCutMark *this,PostReadContext *param_1)

{
  PDFPlusCutMark *pPVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  void *_Memory;
  PDFPlusCutMark *pPVar4;
  undefined1 auStack_58 [32];
  void *local_38 [3];
  ulonglong local_20;
  ulonglong local_18;
  
                    /* 0x13cdf0  1425
                       ?PostProcessFormulasImp@PDFPlusCutMark@DocumentMarks@@MEAAXAEBVPostReadContext@ArtDoc@@@Z
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_58;
  pPVar1 = this + 0x698;
  if ((pPVar1 == (PDFPlusCutMark *)0x0) || (this[0x6b8] != (PDFPlusCutMark)0x1)) {
    pPVar4 = (PDFPlusCutMark *)0x0;
  }
  else {
    pPVar4 = pPVar1;
  }
  if (pPVar4 != (PDFPlusCutMark *)0x0) {
    puVar3 = (undefined8 *)FUN_180150a50(local_38,pPVar4,param_1);
    if (this[0x6b8] == (PDFPlusCutMark)0x1) {
      FUN_180014e90(pPVar1,puVar3);
    }
    else {
      FUN_18006da40(pPVar1);
      this[0x6b8] = (PDFPlusCutMark)0xff;
      *(undefined8 *)pPVar1 = 0;
      *(undefined8 *)(this + 0x6a0) = 0;
      *(undefined8 *)(this + 0x6a8) = 0;
      *(undefined8 *)(this + 0x6b0) = 0;
      uVar2 = puVar3[1];
      *(undefined8 *)pPVar1 = *puVar3;
      *(undefined8 *)(this + 0x6a0) = uVar2;
      uVar2 = puVar3[3];
      *(undefined8 *)(this + 0x6a8) = puVar3[2];
      *(undefined8 *)(this + 0x6b0) = uVar2;
      puVar3[2] = 0;
      puVar3[3] = 0xf;
      *(undefined1 *)puVar3 = 0;
      this[0x6b8] = (PDFPlusCutMark)0x1;
    }
    if (0xf < local_20) {
      _Memory = local_38[0];
      if ((0xfff < local_20 + 1) &&
         (_Memory = *(void **)((longlong)local_38[0] + -8),
         0x1f < (ulonglong)((longlong)local_38[0] + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
  }
  return;
}


