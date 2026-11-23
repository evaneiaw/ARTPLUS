// 1800ad730 SetCutMarkLineTypes

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkLineTypes(class DocumentMarks::PDFPlusCutMark &
   __ptr64,class std::vector<enum DocumentMarks::PDFPlusCutMark::LineType,class std::allocator<enum
   DocumentMarks::PDFPlusCutMark::LineType> > const & __ptr64) */

void __cdecl
DocumentMarks::SetCutMarkLineTypes
          (PDFPlusCutMark *param_1,
          vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>
          *param_2)

{
  void *pvVar1;
  longlong *plVar2;
  Action *pAVar3;
  undefined8 uVar4;
  ActionList *pAVar5;
  void *_Memory;
  undefined1 auStack_138 [32];
  undefined ***local_118;
  Action *local_108;
  Action *local_100;
  Action **local_f8;
  undefined4 uStack_f0;
  uint uStack_ec;
  longlong *local_e8;
  undefined1 local_e0 [24];
  undefined1 local_c8 [32];
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
  
                    /* 0xad730  1509
                       ?SetCutMarkLineTypes@DocumentMarks@@YAXAEAVPDFPlusCutMark@1@AEBV?$vector@W4LineType@PDFPlusCutMark@DocumentMarks@@V?$allocator@W4LineType@PDFPlusCutMark@DocumentMarks@@@std@@@std@@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_138;
  local_68 = std::
             _Func_impl_no_alloc<class_std::vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,std::vector<enum_DocumentMarks::PDFPlusCutMark::LineType,class_std::allocator<enum_DocumentMarks::PDFPlusCutMark::LineType>_>,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_58 = (ulonglong)uStack_ec << 0x20;
  local_60 = PDFPlusCutMark::GetLineTypes;
  local_30 = &local_68;
  local_f8 = (Action **)PDFPlusCutMark::SetLineTypes;
  uStack_f0 = 0;
  local_a8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(std::vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,std::vector<enum_DocumentMarks::PDFPlusCutMark::LineType,class_std::allocator<enum_DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64>
             ::vftable;
  local_a0 = 0x8013d130;
  uStack_9c = 1;
  uStack_98 = 0;
  local_70 = &local_a8;
  plVar2 = (longlong *)FUN_1800ac3f0(local_e0);
  local_e8 = plVar2;
  pAVar3 = (Action *)FUN_1802d6b50(0x110);
  local_100 = pAVar3;
  if (pAVar3 == (Action *)0x0) {
    local_108 = (Action *)0x0;
  }
  else {
    uVar4 = FUN_1800ac3f0(local_c8,plVar2);
    local_118 = &local_68;
    local_108 = (Action *)FUN_1800abe60(pAVar3,param_1,uVar4,&local_a8);
  }
  local_f8 = &local_108;
  pAVar5 = ArtDoc::Action::GetActionList(local_108);
  local_100 = local_108;
  local_108 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar5,&local_100);
  if (local_108 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_108)(local_108,1);
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


