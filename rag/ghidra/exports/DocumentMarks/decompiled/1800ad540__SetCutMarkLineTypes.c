// 1800ad540 SetCutMarkLineTypes

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkLineTypes(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusCutMark const & __ptr64)> const &
   __ptr64,class std::vector<enum DocumentMarks::PDFPlusCutMark::LineType,class std::allocator<enum
   DocumentMarks::PDFPlusCutMark::LineType> > const & __ptr64) */

void __cdecl
DocumentMarks::SetCutMarkLineTypes
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> *param_2,
          vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>
          *param_3)

{
  void *pvVar1;
  longlong *plVar2;
  Action *pAVar3;
  undefined8 uVar4;
  ActionList *pAVar5;
  void *_Memory;
  undefined1 auStack_148 [32];
  undefined ***local_128;
  undefined ***local_120;
  Action *local_118;
  Action *local_110;
  Action **local_108;
  undefined4 uStack_100;
  uint uStack_fc;
  longlong *local_f8;
  undefined1 local_f0 [24];
  undefined1 local_d8 [32];
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
  
                    /* 0xad540  1508
                       ?SetCutMarkLineTypes@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusCutMark@DocumentMarks@@@Z@std@@AEBV?$vector@W4LineType@PDFPlusCutMark@DocumentMarks@@V?$allocator@W4LineType@PDFPlusCutMark@DocumentMarks@@@std@@@5@@Z
                        */
  local_38 = DAT_180418e00 ^ (ulonglong)auStack_148;
  local_78 = std::
             _Func_impl_no_alloc<class_std::vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,std::vector<enum_DocumentMarks::PDFPlusCutMark::LineType,class_std::allocator<enum_DocumentMarks::PDFPlusCutMark::LineType>_>,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_68 = (ulonglong)uStack_fc << 0x20;
  local_70 = PDFPlusCutMark::GetLineTypes;
  local_40 = &local_78;
  local_108 = (Action **)PDFPlusCutMark::SetLineTypes;
  uStack_100 = 0;
  local_b8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(std::vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,std::vector<enum_DocumentMarks::PDFPlusCutMark::LineType,class_std::allocator<enum_DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64>
             ::vftable;
  local_b0 = 0x8013d130;
  uStack_ac = 1;
  uStack_a8 = 0;
  local_80 = &local_b8;
  plVar2 = (longlong *)FUN_1800ac3f0(local_f0,param_3);
  local_f8 = plVar2;
  pAVar3 = (Action *)FUN_1802d6b50(0x110);
  local_110 = pAVar3;
  if (pAVar3 == (Action *)0x0) {
    local_118 = (Action *)0x0;
  }
  else {
    uVar4 = FUN_1800ac3f0(local_d8,plVar2);
    local_120 = &local_78;
    local_128 = &local_b8;
    local_118 = (Action *)FUN_1800abc40(pAVar3,param_1,param_2,uVar4);
  }
  local_108 = &local_118;
  pAVar5 = ArtDoc::Action::GetActionList(local_118);
  local_110 = local_118;
  local_118 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar5,&local_110);
  if (local_118 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_118)(local_118,1);
  }
  pvVar1 = (void *)*plVar2;
  if (pvVar1 != (void *)0x0) {
    _Memory = pvVar1;
    if ((0xfff < (ulonglong)((plVar2[2] - (longlong)pvVar1 >> 2) * 4)) &&
       (_Memory = *(void **)((longlong)pvVar1 + -8),
       0x1f < (ulonglong)((longlong)pvVar1 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
    *plVar2 = 0;
    plVar2[1] = 0;
    plVar2[2] = 0;
  }
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


