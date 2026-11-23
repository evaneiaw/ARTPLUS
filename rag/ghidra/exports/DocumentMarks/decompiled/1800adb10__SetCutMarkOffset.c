// 1800adb10 SetCutMarkOffset

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkOffset(class DocumentMarks::PDFPlusCutMark & __ptr64,class
   std::variant<class YAGL::CoordinateBase<struct YAGL::MilliPointCoordinateSystem,1>,class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > const &
   __ptr64) */

void __cdecl
DocumentMarks::SetCutMarkOffset
          (PDFPlusCutMark *param_1,
          variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
          *param_2)

{
  undefined8 *puVar1;
  longlong *plVar2;
  ActionList *pAVar3;
  undefined1 auStack_118 [32];
  undefined ***local_f8;
  longlong local_e8;
  undefined8 *local_e0;
  code *local_d8;
  undefined4 uStack_d0;
  uint uStack_cc;
  undefined8 local_c8 [4];
  undefined1 local_a8;
  undefined8 *local_a0;
  undefined **local_98;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined ***local_60;
  undefined **local_58;
  code *local_50;
  longlong lStack_48;
  undefined ***local_20;
  ulonglong local_18;
  
                    /* 0xadb10  1511
                       ?SetCutMarkOffset@DocumentMarks@@YAXAEAVPDFPlusCutMark@1@AEBV?$variant@V?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@Z
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_118;
  local_58 = std::
             _Func_impl_no_alloc<class_std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,std::variant<class_YAGL::CoordinateBase<struct_YAGL::MilliPointCoordinateSystem,1>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_48 = (ulonglong)uStack_cc << 0x20;
  local_50 = PDFPlusBearerBar::GetOffset;
  local_20 = &local_58;
  local_d8 = PDFPlusCutMark::SetOffset;
  uStack_d0 = 0;
  local_98 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,std::variant<class_YAGL::CoordinateBase<struct_YAGL::MilliPointCoordinateSystem,1>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_const&___ptr64>
             ::vftable;
  local_90 = 0x8013d160;
  uStack_8c = 1;
  uStack_88 = 0;
  local_60 = &local_98;
  local_e0 = local_c8;
  local_a8 = 0xff;
  if (param_2[0x20] !=
      (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
       )0xff) {
    if (param_2[0x20] ==
        (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
         )0x0) {
      local_c8[0] = *(undefined8 *)param_2;
      local_a8 = 0;
    }
    else {
      FUN_180011ca0(local_c8);
      local_a8 = 1;
    }
  }
  local_a0 = local_c8;
  local_f8 = &local_58;
  plVar2 = (longlong *)FUN_1800ab640(&local_e0,param_1,local_c8,&local_98);
  local_d8 = (code *)plVar2;
  pAVar3 = ArtDoc::Action::GetActionList((Action *)*plVar2);
  local_e8 = *plVar2;
  *plVar2 = 0;
  ArtDoc::ActionList::DoAction(pAVar3,&local_e8);
  puVar1 = (undefined8 *)*plVar2;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  FUN_18006da40(local_c8);
  if (local_60 != (undefined ***)0x0) {
    (*(code *)(*local_60)[4])
              (local_60,CONCAT71((int7)((ulonglong)&local_98 >> 8),local_60 != &local_98));
    local_60 = (undefined ***)0x0;
  }
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])
              (local_20,CONCAT71((int7)((ulonglong)&local_58 >> 8),local_20 != &local_58));
  }
  return;
}


