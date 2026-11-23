// DocumentMarks.dll 1800aa520 DocumentMarks::SetBearerBarSizeReference
// signature: void SetBearerBarSizeReference(Content * param_1, function<bool___cdecl(DocumentMarks::PDFPlusBearerBar_const&___ptr64)> * param_2, SizeReference param_3)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetBearerBarSizeReference(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusBearerBar const & __ptr64)> const &
   __ptr64,enum DocumentMarks::PDFPlusBearerBar::SizeReference) */

void __cdecl
DocumentMarks::SetBearerBarSizeReference
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusBearerBar_const&___ptr64)> *param_2,
          SizeReference param_3)

{
  ActionList *pAVar1;
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
  
                    /* 0xaa520  1498
                       ?SetBearerBarSizeReference@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusBearerBar@DocumentMarks@@@Z@std@@W4SizeReference@PDFPlusBearerBar@1@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_f8;
  local_68 = std::
             _Func_impl_no_alloc<enum_DocumentMarks::PDFPlusBearerBar::SizeReference_(__cdecl_DocumentMarks::PDFPlusBearerBar::*)(void)const___ptr64,DocumentMarks::PDFPlusBearerBar::SizeReference,DocumentMarks::PDFPlusBearerBar_const&___ptr64>
             ::vftable;
  lStack_58 = (ulonglong)uStack_ac << 0x20;
  local_60 = PDFPlusBearerBar::GetSizeReference;
  local_30 = &local_68;
  local_b8 = (Action **)PDFPlusBearerBar::SetSizeReference;
  uStack_b0 = 0;
  local_a8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusBearerBar::*)(DocumentMarks::PDFPlusBearerBar::SizeReference)___ptr64,void,DocumentMarks::PDFPlusBearerBar&___ptr64,DocumentMarks::PDFPlusBearerBar::SizeReference_const&___ptr64>
             ::vftable;
  local_a0 = 0x80131c30;
  uStack_9c = 1;
  uStack_98 = 0;
  local_70 = &local_a8;
  local_c0 = (Action *)FUN_1802d6b50(0x100);
  if (local_c0 == (Action *)0x0) {
    local_c8 = (Action *)0x0;
  }
  else {
    local_d0 = &local_68;
    local_d8 = &local_a8;
    local_c8 = (Action *)FUN_1800a9fd0(local_c0,param_1,param_2,param_3);
  }
  local_b8 = &local_c8;
  pAVar1 = ArtDoc::Action::GetActionList(local_c8);
  local_c0 = local_c8;
  local_c8 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar1,&local_c0);
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


