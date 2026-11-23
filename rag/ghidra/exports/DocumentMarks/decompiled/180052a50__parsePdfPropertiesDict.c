// 180052a50 parsePdfPropertiesDict

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: virtual bool __cdecl DocumentMarks::CutMark::parsePdfPropertiesDict(class std::map<class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class
   ArtDoc::ContentObject * __ptr64,struct std::less<class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair<class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class
   ArtDoc::ContentObject * __ptr64> > > const & __ptr64) __ptr64 */

bool __thiscall
DocumentMarks::CutMark::parsePdfPropertiesDict
          (CutMark *this,
          map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::ContentObject*___ptr64,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,ArtDoc::ContentObject*___ptr64>_>_>
          *param_1)

{
  bool bVar1;
  int iVar2;
  Dictionary *this_00;
  Content *pCVar3;
  char *_Memory;
  void *pvVar4;
  longlong lVar5;
  longlong lVar6;
  double dVar7;
  undefined1 auStack_88 [32];
  char *local_68;
  undefined8 uStack_60;
  undefined *local_58;
  ulonglong uStack_50;
  void *local_48;
  undefined8 uStack_40;
  undefined8 local_38;
  ulonglong uStack_30;
  ulonglong local_28;
  
                    /* 0x52a50  2128
                       ?parsePdfPropertiesDict@CutMark@DocumentMarks@@UEAA_NAEBV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEAVContentObject@ArtDoc@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEAVContentObject@ArtDoc@@@std@@@2@@std@@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_88;
  bVar1 = DynamicMark::parsePdfPropertiesDict((DynamicMark *)this,param_1);
  if (bVar1) {
    local_68 = (char *)0x0;
    uStack_60 = 0;
    local_58 = (undefined *)0x0;
    uStack_50 = 0;
    lVar5 = -1;
    lVar6 = -1;
    do {
      lVar6 = lVar6 + 1;
    } while (PTR_s_DM_CutMarkParams_1804189a8[lVar6] != '\0');
    FUN_180010070(&local_68);
    this_00 = ArtDoc::Dictionary::GetDictionaryValue
                        ((Dictionary *)(this + 0x2d0),
                         (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                         &local_68);
    if (0xf < uStack_50) {
      _Memory = local_68;
      if ((0xfff < uStack_50 + 1) &&
         (_Memory = *(char **)(local_68 + -8), (char *)0x1f < local_68 + (-8 - (longlong)_Memory)))
      {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
    local_58 = (undefined *)0x0;
    uStack_50 = 0xf;
    local_68 = (char *)((ulonglong)local_68 & 0xffffffffffffff00);
    local_48 = (void *)0x0;
    uStack_40 = 0;
    local_38 = 0;
    uStack_30 = 0;
    lVar6 = -1;
    do {
      lVar6 = lVar6 + 1;
    } while (PTR_s_DM_CutMarkParams_Version_180418b10[lVar6] != '\0');
    FUN_180010070(&local_48);
    iVar2 = ArtDoc::Dictionary::GetIntegerValue
                      (this_00,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                               &local_48);
    if (0xf < uStack_30) {
      pvVar4 = local_48;
      if ((0xfff < uStack_30 + 1) &&
         (pvVar4 = *(void **)((longlong)local_48 + -8),
         0x1f < (ulonglong)((longlong)local_48 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    if (iVar2 < 2) {
      local_48 = (void *)0x0;
      uStack_40 = 0;
      local_38 = 0;
      uStack_30 = 0;
      do {
        lVar5 = lVar5 + 1;
      } while (PTR_s_DM_CutMarkParams_Offset_180418b00[lVar5] != '\0');
      FUN_180010070(&local_48,PTR_s_DM_CutMarkParams_Offset_180418b00,lVar5);
      dVar7 = ArtDoc::Dictionary::GetFloatValue
                        (this_00,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                 &local_48);
      *(double *)(this + 0x698) = dVar7;
      if (0xf < uStack_30) {
        pvVar4 = local_48;
        if ((0xfff < uStack_30 + 1) &&
           (pvVar4 = *(void **)((longlong)local_48 + -8),
           0x1f < (ulonglong)((longlong)local_48 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar4);
      }
      return true;
    }
    local_68 = "CutMark";
    uStack_60 = 7;
    pCVar3 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
    FUN_180103b00(pCVar3,iVar2,1,&local_68);
  }
  return false;
}


