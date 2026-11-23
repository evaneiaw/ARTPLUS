// 18013d160 SetOffset

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: void __cdecl DocumentMarks::PDFPlusCutMark::SetOffset(class std::variant<class
   YAGL::CoordinateBase<struct YAGL::MilliPointCoordinateSystem,1>,class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > const &
   __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::SetOffset
          (PDFPlusCutMark *this,
          variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
          *param_1)

{
  variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
  *pvVar1;
  PDFPlusCutMark *pPVar2;
  undefined1 auStack_58 [32];
  undefined8 local_38;
  undefined8 uStack_30;
  undefined8 local_28;
  undefined8 uStack_20;
  ulonglong local_18;
  
                    /* 0x13d160  1575
                       ?SetOffset@PDFPlusCutMark@DocumentMarks@@QEAAXAEBV?$variant@V?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@Z
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_58;
  pPVar2 = this + 0x698;
  if (param_1[0x20] ==
      (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
       )0xff) {
    FUN_18006da40(pPVar2);
    this[0x6b8] = (PDFPlusCutMark)0xff;
  }
  else if (param_1[0x20] ==
           (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
            )0x0) {
    if (this[0x6b8] == (PDFPlusCutMark)0x0) {
      *(undefined8 *)pPVar2 = *(undefined8 *)param_1;
    }
    else {
      FUN_18006da40(pPVar2);
      this[0x6b8] = (PDFPlusCutMark)0xff;
      *(undefined8 *)pPVar2 = *(undefined8 *)param_1;
      this[0x6b8] = (PDFPlusCutMark)0x0;
    }
  }
  else if (this[0x6b8] == (PDFPlusCutMark)0x1) {
    if (pPVar2 != (PDFPlusCutMark *)param_1) {
      pvVar1 = param_1 + 0x10;
      if (0xf < *(ulonglong *)(param_1 + 0x18)) {
        param_1 = *(variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
                    **)param_1;
      }
      FUN_180019430(pPVar2,param_1,*(undefined8 *)pvVar1);
    }
  }
  else {
    FUN_180011ca0(&local_38);
    FUN_18006da40(pPVar2);
    *(undefined8 *)pPVar2 = local_38;
    *(undefined8 *)(this + 0x6a0) = uStack_30;
    *(undefined8 *)(this + 0x6a8) = local_28;
    *(undefined8 *)(this + 0x6b0) = uStack_20;
    this[0x6b8] = (PDFPlusCutMark)0x1;
  }
  return;
}


