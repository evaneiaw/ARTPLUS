// 18013e970 postProcessClonedMark

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: virtual void __cdecl DocumentMarks::PDFPlusCutMark::postProcessClonedMark(class
   ArtDoc::CloneStrategy const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::postProcessClonedMark(PDFPlusCutMark *this,CloneStrategy *param_1)

{
  PDFPlusCutMark *pPVar1;
  bool bVar2;
  int iVar3;
  __uint64 _Var4;
  ContentObject *pCVar5;
  Content *pCVar6;
  Properties *pPVar7;
  undefined8 uVar8;
  void *pvVar9;
  char *_Memory;
  undefined8 *_Buf2;
  undefined8 *puVar10;
  undefined8 *puVar11;
  PDFPlusCutMark *pPVar12;
  undefined1 auStack_1d8 [32];
  undefined8 local_1b8;
  __uint64 local_1a8 [5];
  undefined1 local_180 [40];
  undefined1 local_158 [40];
  char local_130;
  undefined1 local_128;
  __uint64 *local_118;
  undefined4 local_108;
  undefined4 uStack_104;
  undefined1 local_e0 [40];
  undefined1 local_b8 [40];
  char local_90;
  char local_88;
  void *local_78;
  undefined8 uStack_70;
  undefined8 local_68;
  ulonglong uStack_60;
  char local_58;
  char *local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  ulonglong uStack_38;
  ulonglong local_30;
  
                    /* 0x13e970  2151
                       ?postProcessClonedMark@PDFPlusCutMark@DocumentMarks@@UEAAXAEBVCloneStrategy@ArtDoc@@@Z
                        */
  local_30 = DAT_180418e00 ^ (ulonglong)auStack_1d8;
  if (this[0x788] != (PDFPlusCutMark)0x0) goto LAB_18013ed0e;
  uStack_48 = 0;
  local_40 = 0;
  uStack_38 = 0xf;
  local_50 = (char *)0x0;
  local_78 = (void *)0x0;
  uStack_70 = 0;
  local_68 = 0;
  uStack_60 = 0xf;
  local_58 = '\x01';
  bVar2 = false;
  _Var4 = ArtDoc::ContentObject::GetID((ContentObject *)this);
  pCVar5 = ArtDoc::CloneStrategy::GetOriginalObject(param_1,_Var4);
  local_1b8 = (char **)((ulonglong)local_1b8._4_4_ << 0x20);
  pCVar5 = (ContentObject *)
           __RTDynamicCast(pCVar5,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                           &RTTI_Type_Descriptor);
  if ((pCVar5 == (ContentObject *)0x0) ||
     (pCVar6 = ArtDoc::ContentObject::GetContent(pCVar5), pCVar6 == (Content *)0x0)) {
LAB_18013eb12:
    pPVar7 = ArtDoc::ContentObject::GetProperties((ContentObject *)this);
    puVar10 = *(undefined8 **)pPVar7;
    puVar11 = puVar10 + *(longlong *)(pPVar7 + 8) * 0xc;
    if (puVar10 != puVar11) {
      do {
        _Buf2 = puVar10;
        if (0xf < (ulonglong)puVar10[3]) {
          _Buf2 = (undefined8 *)*puVar10;
        }
      } while (((puVar10[2] != 0x24) ||
               (iVar3 = memcmp("PDFPlusCutMark_OriginalReferenceName",_Buf2,0x24), iVar3 != 0)) &&
              (puVar10 = puVar10 + 0xc, puVar10 != puVar11));
      if (puVar10 != puVar11) {
        puVar11 = puVar10 + 4;
        if (((puVar11 == (undefined8 *)0x0) || ((puVar10[0xb] & 0xfffffffffffffffc) == 0)) ||
           (iVar3 = __std_type_info_compare((puVar10[0xb] & 0xfffffffffffffffc) + 8,0x18041cb58),
           iVar3 != 0)) {
          puVar11 = (undefined8 *)0x0;
        }
        if (puVar11 != (undefined8 *)0x0) {
          FUN_18012f6b0(&local_78,puVar11);
        }
      }
    }
  }
  else {
    if (pCVar5[0x788] != (ContentObject)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_180025a80();
    }
    FUN_1800ac3a0(local_1a8);
    if (local_130 == '\0') {
      if (local_58 != '\0') {
        if ((local_58 != -1) && (local_58 != '\0')) {
          FUN_180016510(&local_78,0);
        }
        local_58 = '\0';
      }
      local_78 = (void *)CONCAT44(local_78._4_4_,(undefined4)local_1a8[0]);
LAB_18013ead4:
      bVar2 = true;
    }
    else if ((local_130 == '\x01') &&
            (pCVar5 = ArtDoc::Content::GetObjectWithID(pCVar6,local_1a8[0]),
            pCVar5 != (ContentObject *)0x0)) {
      uVar8 = (**(code **)(*(longlong *)pCVar5 + 0x18))(pCVar5);
      FUN_18012f6b0(&local_78,uVar8);
      goto LAB_18013ead4;
    }
    if (((local_130 != -1) && (local_130 != '\0')) && (local_130 != '\x01')) {
      FUN_180013c20(local_158);
      FUN_180013c20(local_180);
      FUN_180013c20(local_1a8);
    }
    if (!bVar2) goto LAB_18013eb12;
  }
  pCVar6 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
  FUN_1802746e0(&local_108,pCVar6,&local_78);
  if (local_88 == '\0') {
    pPVar7 = ArtDoc::ContentObject::GetProperties((ContentObject *)this);
    if (local_58 != '\x01') {
                    /* WARNING: Subroutine does not return */
      FUN_180025a80();
    }
    FUN_18004e5d0(pPVar7,&PTR_s_PDFPlusCutMark_OriginalReference_180323170,&local_78);
  }
  else {
    local_118 = local_1a8;
    local_130 = -1;
    if (local_90 != -1) {
      if (local_90 == '\0') {
        local_1a8[0] = CONCAT44(local_1a8[0]._4_4_,local_108);
        local_130 = '\0';
      }
      else if (local_90 == '\x01') {
        local_1a8[0] = CONCAT44(uStack_104,local_108);
        local_130 = '\x01';
      }
      else {
        FUN_1800135b0(local_1a8,&local_108);
        local_130 = '\x02';
      }
    }
    local_128 = 0;
    SetReferenceObject(this,(variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>
                             *)local_1a8);
    FUN_1800ac600(local_1a8);
    pPVar7 = ArtDoc::ContentObject::GetProperties((ContentObject *)this);
    ArtDoc::Properties::Erase
              (pPVar7,(basic_string_view<char,std::char_traits<char>_> *)
                      &PTR_s_PDFPlusCutMark_OriginalReference_180323170);
  }
  if ((((local_88 != '\0') && (local_90 != -1)) && (local_90 != '\0')) && (local_90 != '\x01')) {
    FUN_180013c20(local_b8);
    FUN_180013c20(local_e0);
    FUN_180013c20(&local_108);
  }
  if (((local_58 != -1) && (local_58 != '\0')) && (0xf < uStack_60)) {
    pvVar9 = local_78;
    if ((0xfff < uStack_60 + 1) &&
       (pvVar9 = *(void **)((longlong)local_78 + -8),
       0x1f < (ulonglong)((longlong)local_78 + (-8 - (longlong)pvVar9)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar9);
  }
LAB_18013ed0e:
  pPVar1 = this + 0x698;
  if ((pPVar1 == (PDFPlusCutMark *)0x0) || (pPVar12 = pPVar1, this[0x6b8] != (PDFPlusCutMark)0x1)) {
    pPVar12 = (PDFPlusCutMark *)0x0;
  }
  if (pPVar12 != (PDFPlusCutMark *)0x0) {
    local_50 = (char *)0x0;
    uStack_48 = 0;
    local_40 = 0;
    uStack_38 = 0;
    local_50 = (char *)FUN_1802d6b50(0x20);
    local_40 = 0x15;
    uStack_38 = 0x1f;
    builtin_strncpy(local_50,"PDFPlusCutMark_Offset",0x16);
    local_1b8 = &local_50;
    uVar8 = FUN_180154640(&local_78,pPVar12,this,param_1);
    FUN_180133520(pPVar1,uVar8);
    if (0xf < uStack_60) {
      pvVar9 = local_78;
      if ((0xfff < uStack_60 + 1) &&
         (pvVar9 = *(void **)((longlong)local_78 + -8),
         0x1f < (ulonglong)((longlong)local_78 + (-8 - (longlong)pvVar9)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar9);
    }
    local_68 = 0;
    uStack_60 = 0xf;
    local_78 = (void *)((ulonglong)local_78 & 0xffffffffffffff00);
    if (0xf < uStack_38) {
      _Memory = local_50;
      if ((0xfff < uStack_38 + 1) &&
         (_Memory = *(char **)(local_50 + -8), (char *)0x1f < local_50 + (-8 - (longlong)_Memory)))
      {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
  }
  DynamicMark::postProcessClonedMark((DynamicMark *)this,param_1);
  return;
}


