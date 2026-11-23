// 1800ae100 SetCutMarkRepetition

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkRepetition(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusCutMark const & __ptr64)> const &
   __ptr64,enum DocumentMarks::PDFPlusCutMark::Repetition) */

void __cdecl
DocumentMarks::SetCutMarkRepetition
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> *param_2,
          Repetition param_3)

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
  
                    /* 0xae100  1515
                       ?SetCutMarkRepetition@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusCutMark@DocumentMarks@@@Z@std@@W4Repetition@PDFPlusCutMark@1@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_f8;
  local_68 = std::
             _Func_impl_no_alloc<enum_DocumentMarks::PDFPlusCutMark::Repetition_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,DocumentMarks::PDFPlusCutMark::Repetition,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_58 = (ulonglong)uStack_ac << 0x20;
  local_60 = PDFPlusCutMark::GetRepetition;
  local_30 = &local_68;
  local_b8 = (Action **)PDFPlusCutMark::SetRepetition;
  uStack_b0 = 0;
  local_a8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(DocumentMarks::PDFPlusCutMark::Repetition)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,DocumentMarks::PDFPlusCutMark::Repetition_const&___ptr64>
             ::vftable;
  local_a0 = 0x8013d2b0;
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
    local_c8 = (Action *)FUN_1800ac150(local_c0,param_1,param_2,param_3);
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


