// DocumentMarks.dll 1800aa3c0 DocumentMarks::SetBearerBarOffset
// signature: void SetBearerBarOffset(Content * param_1, function<bool___cdecl(DocumentMarks::PDFPlusBearerBar_const&___ptr64)> * param_2, CoordinateBase<YAGL::MilliPointCoordinateSystem,1> * param_3)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetBearerBarOffset(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusBearerBar const & __ptr64)> const &
   __ptr64,class YAGL::CoordinateBase<struct YAGL::MilliPointCoordinateSystem,1> const & __ptr64) */

void __cdecl
DocumentMarks::SetBearerBarOffset
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusBearerBar_const&___ptr64)> *param_2,
          CoordinateBase<YAGL::MilliPointCoordinateSystem,1> *param_3)

{
  undefined8 uVar1;
  ActionList *pAVar2;
  undefined1 auStack_f8 [32];
  undefined ***local_d8;
  undefined ***local_d0;
  Action *local_c8;
  Action *local_c0;
  Action **local_b8;
  undefined4 uStack_b0;
  uint uStack_ac;
  undefined **local_a8;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined ***local_70;
  undefined **local_68;
  code *local_60;
  longlong lStack_58;
  undefined ***local_30;
  ulonglong local_28;
  
                    /* 0xaa3c0  1497
                       ?SetBearerBarOffset@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusBearerBar@DocumentMarks@@@Z@std@@AEBV?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_f8;
  local_68 = std::
             _Func_impl_no_alloc<class_YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusBearerBar::*)(void)const___ptr64,YAGL::CoordinateBase<struct_YAGL::MilliPointCoordinateSystem,1>,DocumentMarks::PDFPlusBearerBar_const&___ptr64>
             ::vftable;
  lStack_58 = (ulonglong)uStack_ac << 0x20;
  local_60 = PDFPlusBearerBar::GetOffset;
  local_30 = &local_68;
  local_b8 = (Action **)PDFPlusBearerBar::SetOffset;
  uStack_b0 = 0;
  local_a8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusBearerBar::*)(YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusBearerBar&___ptr64,YAGL::CoordinateBase<struct_YAGL::MilliPointCoordinateSystem,1>_const&___ptr64>
             ::vftable;
  local_a0 = 0x80020700;
  uStack_9c = 1;
  uStack_98 = 0;
  local_70 = &local_a8;
  uVar1 = *(undefined8 *)param_3;
  local_c0 = (Action *)FUN_1802d6b50(0x100);
  if (local_c0 == (Action *)0x0) {
    local_c8 = (Action *)0x0;
  }
  else {
    local_d0 = &local_68;
    local_d8 = &local_a8;
    local_c8 = (Action *)FUN_1800a9e10(local_c0,param_1,param_2,uVar1);
  }
  local_b8 = &local_c8;
  pAVar2 = ArtDoc::Action::GetActionList(local_c8);
  local_c0 = local_c8;
  local_c8 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar2,&local_c0);
  if (local_c8 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_c8)(local_c8,1);
  }
  if (local_70 != (undefined ***)0x0) {
    (*(code *)(*local_70)[4])
              (local_70,CONCAT71((int7)((ulonglong)&local_a8 >> 8),local_70 != &local_a8));
    local_70 = (undefined ***)0x0;
  }
  if (local_30 != (undefined ***)0x0) {
    (*(code *)(*local_30)[4])
              (local_30,CONCAT71((int7)((ulonglong)&local_68 >> 8),local_30 != &local_68));
  }
  return;
}


