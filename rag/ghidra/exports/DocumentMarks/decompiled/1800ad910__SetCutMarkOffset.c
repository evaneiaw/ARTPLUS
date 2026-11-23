// 1800ad910 SetCutMarkOffset

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkOffset(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusCutMark const & __ptr64)> const &
   __ptr64,class std::variant<class YAGL::CoordinateBase<struct
   YAGL::MilliPointCoordinateSystem,1>,class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > > const & __ptr64) */

void __cdecl
DocumentMarks::SetCutMarkOffset
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> *param_2,
          variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
          *param_3)

{
  Action *pAVar1;
  ActionList *pAVar2;
  undefined1 auStack_168 [32];
  undefined ***local_148;
  undefined ***local_140;
  Action *local_138;
  Action *local_130;
  Action **local_128;
  undefined4 uStack_120;
  uint uStack_11c;
  undefined8 local_118 [4];
  char local_f8;
  undefined8 local_f0 [4];
  undefined1 local_d0;
  undefined8 *local_c8;
  undefined **local_b8;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined ***local_80;
  undefined **local_78;
  code *local_70;
  longlong lStack_68;
  undefined ***local_40;
  ulonglong local_38;
  
                    /* 0xad910  1510
                       ?SetCutMarkOffset@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusCutMark@DocumentMarks@@@Z@std@@AEBV?$variant@V?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@5@@Z
                        */
  local_38 = DAT_180418e00 ^ (ulonglong)auStack_168;
  local_78 = std::
             _Func_impl_no_alloc<class_std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,std::variant<class_YAGL::CoordinateBase<struct_YAGL::MilliPointCoordinateSystem,1>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_68 = (ulonglong)uStack_11c << 0x20;
  local_70 = PDFPlusBearerBar::GetOffset;
  local_40 = &local_78;
  local_128 = (Action **)PDFPlusCutMark::SetOffset;
  uStack_120 = 0;
  local_b8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,std::variant<class_YAGL::CoordinateBase<struct_YAGL::MilliPointCoordinateSystem,1>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_const&___ptr64>
             ::vftable;
  local_b0 = 0x8013d160;
  uStack_ac = 1;
  uStack_a8 = 0;
  local_80 = &local_b8;
  local_130 = (Action *)local_118;
  local_f8 = -1;
  if (param_3[0x20] !=
      (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
       )0xff) {
    if (param_3[0x20] ==
        (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
         )0x0) {
      local_118[0] = *(undefined8 *)param_3;
      local_f8 = '\0';
    }
    else {
      FUN_180011ca0(local_118,param_3);
      local_f8 = '\x01';
    }
  }
  local_c8 = local_118;
  pAVar1 = (Action *)FUN_1802d6b50(0x120);
  local_130 = pAVar1;
  if (pAVar1 == (Action *)0x0) {
    local_138 = (Action *)0x0;
  }
  else {
    local_128 = (Action **)local_f0;
    local_d0 = 0xff;
    if (local_f8 != -1) {
      if (local_f8 == '\0') {
        local_f0[0] = local_118[0];
        local_d0 = 0;
      }
      else {
        FUN_180011ca0(local_f0,local_118);
        local_d0 = 1;
      }
    }
    local_140 = &local_78;
    local_148 = &local_b8;
    local_138 = (Action *)FUN_1800ab7f0(pAVar1,param_1,param_2,local_f0);
  }
  local_128 = &local_138;
  pAVar2 = ArtDoc::Action::GetActionList(local_138);
  local_130 = local_138;
  local_138 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar2,&local_130);
  if (local_138 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_138)(local_138,1);
  }
  FUN_18006da40(local_118);
  if (local_80 != (undefined ***)0x0) {
    (*(code *)(*local_80)[4])
              (local_80,CONCAT71((int7)((ulonglong)&local_b8 >> 8),local_80 != &local_b8));
    local_80 = (undefined ***)0x0;
  }
  if (local_40 != (undefined ***)0x0) {
    (*(code *)(*local_40)[4])
              (local_40,CONCAT71((int7)((ulonglong)&local_78 >> 8),local_40 != &local_78));
  }
  return;
}


