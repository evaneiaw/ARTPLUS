// 1800adf00 SetCutMarkReferenceToAllStructuralDesignStations

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkReferenceToAllStructuralDesignStations(class
   ArtDoc::Content & __ptr64,class std::function<bool __cdecl(class DocumentMarks::PDFPlusCutMark
   const & __ptr64)> const & __ptr64) */

void __cdecl
DocumentMarks::SetCutMarkReferenceToAllStructuralDesignStations
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> *param_2)

{
  Action *pAVar1;
  undefined8 uVar2;
  ActionList *pAVar3;
  undefined1 auStack_218 [32];
  undefined ***local_1f8;
  undefined ***local_1f0;
  Action *local_1e8;
  Action *local_1e0;
  Action **local_1d8;
  undefined4 uStack_1d0;
  uint uStack_1cc;
  undefined1 *local_1c8;
  undefined1 local_1c0 [40];
  undefined1 local_198 [40];
  undefined1 local_170 [40];
  char local_148;
  char local_140;
  undefined1 local_138 [144];
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
  
                    /* 0xadf00  1514
                       ?SetCutMarkReferenceToAllStructuralDesignStations@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusCutMark@DocumentMarks@@@Z@std@@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_218;
  local_68 = std::
             _Func_impl_no_alloc<class_std::variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,std::variant<class_std::variant<enum_ArtDoc::PageBox,unsigned___int64,struct_DocumentMarks::ProcessingStepLayer>,struct_DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_58 = (ulonglong)uStack_1cc << 0x20;
  local_60 = PDFPlusClipMark::GetHeight;
  local_30 = &local_68;
  local_1d8 = (Action **)PDFPlusCutMark::SetReferenceObject;
  uStack_1d0 = 0;
  local_a8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(std::variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,std::variant<class_std::variant<enum_ArtDoc::PageBox,unsigned___int64,struct_DocumentMarks::ProcessingStepLayer>,struct_DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>_const&___ptr64>
             ::vftable;
  local_a0 = 0x8013d240;
  uStack_9c = 1;
  uStack_98 = 0;
  local_70 = &local_a8;
  local_140 = '\x01';
  local_1c8 = local_1c0;
  pAVar1 = (Action *)FUN_1802d6b50(0x180);
  local_1e0 = pAVar1;
  if (pAVar1 == (Action *)0x0) {
    local_1e8 = (Action *)0x0;
  }
  else {
    uVar2 = FUN_1800ac320(local_138,local_1c0);
    local_1f0 = &local_68;
    local_1f8 = &local_a8;
    local_1e8 = (Action *)FUN_1800aba10(pAVar1,param_1,param_2,uVar2);
  }
  local_1d8 = &local_1e8;
  pAVar3 = ArtDoc::Action::GetActionList(local_1e8);
  local_1e0 = local_1e8;
  local_1e8 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar3,&local_1e0);
  if (local_1e8 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_1e8)(local_1e8,1);
  }
  if ((((local_140 != -1) && (local_140 == '\0')) && (local_148 != -1)) &&
     ((local_148 != '\0' && (local_148 != '\x01')))) {
    FUN_180013c20(local_170);
    FUN_180013c20(local_198);
    FUN_180013c20(local_1c0);
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


