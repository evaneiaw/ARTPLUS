// 18013cef0 RemoveInvalidCustomFormulasImp

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: virtual bool __cdecl
   DocumentMarks::PDFPlusCutMark::RemoveInvalidCustomFormulasImp(void) __ptr64 */

bool __thiscall DocumentMarks::PDFPlusCutMark::RemoveInvalidCustomFormulasImp(PDFPlusCutMark *this)

{
  PDFPlusCutMark *pPVar1;
  void *pvVar2;
  int iVar3;
  Content *pCVar4;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar5;
  Document *this_00;
  ErrorReporter *pEVar6;
  undefined8 *puVar7;
  void *pvVar8;
  bool bVar9;
  undefined1 auStack_d8 [32];
  void *local_b8;
  PDFPlusCutMark *local_b0;
  void *local_a8 [3];
  ulonglong local_90;
  char local_88;
  undefined1 local_80 [8];
  undefined **local_78 [7];
  undefined4 local_40;
  undefined1 local_38;
  undefined7 uStack_37;
  undefined8 local_28;
  ulonglong local_20;
  ulonglong local_18;
  
                    /* 0x13cef0  1460
                       ?RemoveInvalidCustomFormulasImp@PDFPlusCutMark@DocumentMarks@@MEAA_NXZ */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_d8;
  bVar9 = false;
  pPVar1 = this + 0x698;
  if ((pPVar1 != (PDFPlusCutMark *)0x0) && (this[0x6b8] == (PDFPlusCutMark)0x1)) {
    local_b0 = this;
    iVar3 = FUN_180155530(pPVar1,this);
    if (iVar3 - 1U < 3) {
      pCVar4 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
      if (pCVar4 != (Content *)0x0) {
        pbVar5 = ArtDoc::ContentObject::GetName((ContentObject *)this);
        ArtSys::Core::Error::Error((Error *)local_78,2);
        local_78[0] = MarkActionError::_vftable_;
        local_40 = 4;
        if (iVar3 == 3) {
          local_40 = 7;
        }
        FUN_180011ca0(&local_38,pbVar5);
        pCVar4 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
        this_00 = ArtDoc::Content::GetDocument(pCVar4);
        pEVar6 = ArtDoc::Document::GetErrorReporter(this_00);
        (**(code **)(*(longlong *)pEVar6 + 0x10))(pEVar6,local_78);
        if (0xf < local_20) {
          pvVar2 = (void *)CONCAT71(uStack_37,local_38);
          pvVar8 = pvVar2;
          if ((0xfff < local_20 + 1) &&
             (pvVar8 = *(void **)((longlong)pvVar2 + -8),
             0x1f < (ulonglong)((longlong)pvVar2 + (-8 - (longlong)pvVar8)))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(pvVar8);
        }
        local_28 = 0;
        local_20 = 0xf;
        local_38 = 0;
        ArtSys::Core::Error::~Error((Error *)local_78);
      }
      local_b8 = (void *)0x0;
      if (iVar3 == 3) {
        puVar7 = (undefined8 *)FUN_18013bdc0(local_80,this,pPVar1);
        local_b8 = (void *)*puVar7;
      }
      local_a8[0] = local_b8;
      local_88 = '\0';
      SetCutMarkOffset(this,(variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
                             *)local_a8);
      if (((local_88 != -1) && (local_88 != '\0')) && (0xf < local_90)) {
        pvVar8 = local_a8[0];
        if ((0xfff < local_90 + 1) &&
           (pvVar8 = *(void **)((longlong)local_a8[0] + -8),
           0x1f < (ulonglong)((longlong)local_a8[0] + (-8 - (longlong)pvVar8)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar8);
      }
      bVar9 = true;
    }
  }
  return bVar9;
}


