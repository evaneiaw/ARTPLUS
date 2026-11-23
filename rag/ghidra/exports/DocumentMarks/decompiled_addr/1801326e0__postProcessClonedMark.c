// DocumentMarks.dll 1801326e0 DocumentMarks::PDFPlusBearerBar::postProcessClonedMark
// signature: void postProcessClonedMark(PDFPlusBearerBar * this, CloneStrategy * param_1)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: virtual void __cdecl DocumentMarks::PDFPlusBearerBar::postProcessClonedMark(class
   ArtDoc::CloneStrategy const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusBearerBar::postProcessClonedMark
          (PDFPlusBearerBar *this,CloneStrategy *param_1)

{
  ContentObject CVar1;
  undefined *_Buf1;
  int iVar2;
  __uint64 _Var3;
  ContentObject *pCVar4;
  Content *pCVar5;
  undefined8 uVar6;
  Properties *pPVar7;
  void *_Memory;
  undefined8 *_Buf2;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  bool bVar11;
  undefined1 auStack_148 [32];
  undefined4 local_128;
  void *local_118;
  undefined8 uStack_110;
  undefined8 local_108;
  ulonglong uStack_100;
  char local_f8;
  __uint64 local_e8 [5];
  undefined1 local_c0 [40];
  undefined1 local_98 [40];
  char local_70;
  char local_68;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 local_48;
  undefined8 uStack_40;
  ulonglong local_38;
  
                    /* 0x1326e0  2149
                       ?postProcessClonedMark@PDFPlusBearerBar@DocumentMarks@@UEAAXAEBVCloneStrategy@ArtDoc@@@Z
                        */
  local_38 = DAT_180418e00 ^ (ulonglong)auStack_148;
  uStack_50 = 0;
  puVar9 = (undefined8 *)0x0;
  local_48 = 0;
  uStack_40 = 0xf;
  local_58 = 0;
  local_118 = (void *)0x0;
  uStack_110 = 0;
  local_108 = 0;
  uStack_100 = 0xf;
  local_f8 = '\x01';
  bVar11 = false;
  _Var3 = ArtDoc::ContentObject::GetID((ContentObject *)this);
  pCVar4 = ArtDoc::CloneStrategy::GetOriginalObject(param_1,_Var3);
  local_128 = 0;
  pCVar4 = (ContentObject *)
           __RTDynamicCast(pCVar4,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                           &RTTI_Type_Descriptor);
  if ((pCVar4 != (ContentObject *)0x0) &&
     (pCVar5 = ArtDoc::ContentObject::GetContent(pCVar4), pCVar5 != (Content *)0x0)) {
    local_70 = -1;
    CVar1 = pCVar4[0x728];
    if (CVar1 != (ContentObject)0xff) {
      if (CVar1 == (ContentObject)0x0) {
        local_e8[0] = CONCAT44(local_e8[0]._4_4_,*(undefined4 *)(pCVar4 + 0x6b0));
        local_70 = '\0';
      }
      else if (CVar1 == (ContentObject)0x1) {
        local_e8[0] = *(__uint64 *)(pCVar4 + 0x6b0);
        local_70 = '\x01';
      }
      else {
        FUN_1800135b0(local_e8,pCVar4 + 0x6b0);
        local_70 = '\x02';
      }
    }
    if (local_70 == '\0') {
      if (local_f8 != '\0') {
        if ((local_f8 != -1) && (local_f8 != '\0')) {
          FUN_180016510(&local_118,0);
        }
        local_f8 = '\0';
      }
      local_118 = (void *)CONCAT44(local_118._4_4_,(undefined4)local_e8[0]);
      bVar11 = true;
    }
    else if (local_70 == '\x01') {
      pCVar4 = ArtDoc::Content::GetObjectWithID(pCVar5,local_e8[0]);
      bVar11 = pCVar4 != (ContentObject *)0x0;
      if (bVar11) {
        uVar6 = (**(code **)(*(longlong *)pCVar4 + 0x18))(pCVar4);
        FUN_18012f6b0(&local_118,uVar6);
      }
    }
    if (((local_70 != -1) && (local_70 != '\0')) && (local_70 != '\x01')) {
      FUN_180013c20(local_98);
      FUN_180013c20(local_c0);
      FUN_180013c20(local_e8);
    }
    if (bVar11) goto LAB_18013292d;
  }
  pPVar7 = ArtDoc::ContentObject::GetProperties((ContentObject *)this);
  _Buf1 = PTR_s_PDFPlusBearerBar_OriginalReferen_180322938;
  puVar8 = *(undefined8 **)pPVar7;
  puVar10 = puVar8 + *(longlong *)(pPVar7 + 8) * 0xc;
  if (puVar8 != puVar10) {
    do {
      _Buf2 = puVar8;
      if (0xf < (ulonglong)puVar8[3]) {
        _Buf2 = (undefined8 *)*puVar8;
      }
    } while (((puVar8[2] != 0x26) || (iVar2 = memcmp(_Buf1,_Buf2,0x26), iVar2 != 0)) &&
            (puVar8 = puVar8 + 0xc, puVar8 != puVar10));
    if (puVar8 != puVar10) {
      if (puVar8 + 4 != (undefined8 *)0x0) {
        if ((puVar8[0xb] & 0xfffffffffffffffc) != 0) {
          iVar2 = __std_type_info_compare((puVar8[0xb] & 0xfffffffffffffffc) + 8,0x18041cb58);
          if (iVar2 == 0) {
            puVar9 = puVar8 + 4;
          }
        }
      }
      if (puVar9 != (undefined8 *)0x0) {
        FUN_18012f6b0(&local_118,puVar9);
      }
    }
  }
LAB_18013292d:
  pCVar5 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
  FUN_1802746e0(local_e8,pCVar5,&local_118);
  if (local_68 == '\0') {
    pPVar7 = ArtDoc::ContentObject::GetProperties((ContentObject *)this);
    if (local_f8 != '\x01') {
                    /* WARNING: Subroutine does not return */
      FUN_180025a80();
    }
    FUN_18004e5d0(pPVar7,&PTR_s_PDFPlusBearerBar_OriginalReferen_180322938,&local_118);
  }
  else {
    SetReferenceObject(this,(variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>
                             *)local_e8);
    pPVar7 = ArtDoc::ContentObject::GetProperties((ContentObject *)this);
    ArtDoc::Properties::Erase
              (pPVar7,(basic_string_view<char,std::char_traits<char>_> *)
                      &PTR_s_PDFPlusBearerBar_OriginalReferen_180322938);
  }
  if (((local_68 != '\0') && (local_70 != -1)) && ((local_70 != '\0' && (local_70 != '\x01')))) {
    FUN_180013c20(local_98);
    FUN_180013c20(local_c0);
    FUN_180013c20(local_e8);
  }
  DynamicMark::postProcessClonedMark((DynamicMark *)this,param_1);
  if (((local_f8 != -1) && (local_f8 != '\0')) && (0xf < uStack_100)) {
    _Memory = local_118;
    if ((0xfff < uStack_100 + 1) &&
       (_Memory = *(void **)((longlong)local_118 + -8),
       0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
  }
  return;
}


