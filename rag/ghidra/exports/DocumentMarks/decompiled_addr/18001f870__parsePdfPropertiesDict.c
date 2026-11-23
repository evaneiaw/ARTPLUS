// DocumentMarks.dll 18001f870 DocumentMarks::BearerBar::parsePdfPropertiesDict
// signature: bool parsePdfPropertiesDict(BearerBar * this, map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::ContentObject*___ptr64,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,ArtDoc::ContentObject*___ptr64>_>_> * param_1)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* public: virtual bool __cdecl DocumentMarks::BearerBar::parsePdfPropertiesDict(class
   std::map<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >,class ArtDoc::ContentObject * __ptr64,struct std::less<class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair<class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class
   ArtDoc::ContentObject * __ptr64> > > const & __ptr64) __ptr64 */

bool __thiscall
DocumentMarks::BearerBar::parsePdfPropertiesDict
          (BearerBar *this,
          map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::ContentObject*___ptr64,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,ArtDoc::ContentObject*___ptr64>_>_>
          *param_1)

{
  double dVar1;
  double dVar2;
  bool bVar3;
  int iVar4;
  Dictionary *this_00;
  Content *pCVar5;
  char *_Memory;
  void *pvVar6;
  longlong lVar7;
  longlong lVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  undefined1 auStack_b8 [32];
  void *local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  ulonglong uStack_80;
  char *local_78;
  undefined8 uStack_70;
  undefined *local_68;
  ulonglong uStack_60;
  ulonglong local_58;
  
                    /* 0x1f870  2126
                       ?parsePdfPropertiesDict@BearerBar@DocumentMarks@@UEAA_NAEBV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEAVContentObject@ArtDoc@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEAVContentObject@ArtDoc@@@std@@@2@@std@@@Z
                        */
  local_58 = DAT_180418e00 ^ (ulonglong)auStack_b8;
  bVar3 = DynamicMark::parsePdfPropertiesDict((DynamicMark *)this,param_1);
  if (bVar3) {
    local_78 = (char *)0x0;
    uStack_70 = 0;
    local_68 = (undefined *)0x0;
    uStack_60 = 0;
    lVar7 = -1;
    lVar8 = -1;
    do {
      lVar8 = lVar8 + 1;
    } while (PTR_s_DM_BearerBarParams_180418998[lVar8] != '\0');
    FUN_180010070(&local_78);
    this_00 = ArtDoc::Dictionary::GetDictionaryValue
                        ((Dictionary *)(this + 0x2d0),
                         (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                         &local_78);
    if (0xf < uStack_60) {
      _Memory = local_78;
      if ((0xfff < uStack_60 + 1) &&
         (_Memory = *(char **)(local_78 + -8), (char *)0x1f < local_78 + (-8 - (longlong)_Memory)))
      {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
    local_68 = PTR_180304c20;
    uStack_60 = _UNK_180304c28;
    local_78 = (char *)((ulonglong)local_78 & 0xffffffffffffff00);
    local_98 = (void *)0x0;
    uStack_90 = 0;
    local_88 = 0;
    uStack_80 = 0;
    lVar8 = -1;
    do {
      lVar8 = lVar8 + 1;
    } while (PTR_s_DM_BearerBarParams_Version_180418ad0[lVar8] != '\0');
    FUN_180010070(&local_98);
    iVar4 = ArtDoc::Dictionary::GetIntegerValue
                      (this_00,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                               &local_98);
    if (0xf < uStack_80) {
      pvVar6 = local_98;
      if ((0xfff < uStack_80 + 1) &&
         (pvVar6 = *(void **)((longlong)local_98 + -8),
         0x1f < (ulonglong)((longlong)local_98 + (-8 - (longlong)pvVar6)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar6);
    }
    if (iVar4 < 3) {
      local_98 = (void *)0x0;
      uStack_90 = 0;
      local_88 = 0;
      uStack_80 = 0;
      lVar8 = -1;
      do {
        lVar8 = lVar8 + 1;
      } while (PTR_s_DM_BearerBarParams_Width_180418aa8[lVar8] != '\0');
      FUN_180010070(&local_98);
      dVar9 = ArtDoc::Dictionary::GetFloatValue
                        (this_00,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                 &local_98);
      if (0xf < uStack_80) {
        pvVar6 = local_98;
        if ((0xfff < uStack_80 + 1) &&
           (pvVar6 = *(void **)((longlong)local_98 + -8),
           0x1f < (ulonglong)((longlong)local_98 + (-8 - (longlong)pvVar6)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar6);
      }
      local_98 = (void *)0x0;
      uStack_90 = 0;
      local_88 = 0;
      uStack_80 = 0;
      lVar8 = -1;
      do {
        lVar8 = lVar8 + 1;
      } while (PTR_s_DM_BearerBarParams_Extend_180418ab0[lVar8] != '\0');
      FUN_180010070(&local_98);
      dVar10 = ArtDoc::Dictionary::GetFloatValue
                         (this_00,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *
                                  )&local_98);
      if (0xf < uStack_80) {
        pvVar6 = local_98;
        if ((0xfff < uStack_80 + 1) &&
           (pvVar6 = *(void **)((longlong)local_98 + -8),
           0x1f < (ulonglong)((longlong)local_98 + (-8 - (longlong)pvVar6)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar6);
      }
      local_98 = (void *)0x0;
      uStack_90 = 0;
      local_88 = 0;
      uStack_80 = 0;
      lVar8 = -1;
      do {
        lVar8 = lVar8 + 1;
      } while (PTR_s_DM_BearerBarParams_Offset_180418ab8[lVar8] != '\0');
      FUN_180010070(&local_98);
      dVar11 = ArtDoc::Dictionary::GetFloatValue
                         (this_00,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *
                                  )&local_98);
      if (0xf < uStack_80) {
        pvVar6 = local_98;
        if ((0xfff < uStack_80 + 1) &&
           (pvVar6 = *(void **)((longlong)local_98 + -8),
           0x1f < (ulonglong)((longlong)local_98 + (-8 - (longlong)pvVar6)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar6);
      }
      local_98 = (void *)0x0;
      uStack_90 = 0;
      local_88 = 0;
      uStack_80 = 0;
      if (iVar4 == 1) {
        do {
          lVar7 = lVar7 + 1;
        } while (PTR_s_DM_BearerBarParams_IsVertical_180418ac0[lVar7] != '\0');
        FUN_180010070(&local_98,PTR_s_DM_BearerBarParams_IsVertical_180418ac0,lVar7);
        bVar3 = ArtDoc::Dictionary::GetBoolValue
                          (this_00,(basic_string<char,std::char_traits<char>,std::allocator<char>_>
                                    *)&local_98);
        if (0xf < uStack_80) {
          pvVar6 = local_98;
          if ((0xfff < uStack_80 + 1) &&
             (pvVar6 = *(void **)((longlong)local_98 + -8),
             0x1f < (ulonglong)((longlong)local_98 + (-8 - (longlong)pvVar6)))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(pvVar6);
        }
        iVar4 = 0xc;
        if (bVar3) {
          iVar4 = 3;
        }
      }
      else {
        do {
          lVar7 = lVar7 + 1;
        } while (PTR_s_DM_BearerBarParams_Location_180418ac8[lVar7] != '\0');
        FUN_180010070(&local_98,PTR_s_DM_BearerBarParams_Location_180418ac8,lVar7);
        iVar4 = ArtDoc::Dictionary::GetIntegerValue
                          (this_00,(basic_string<char,std::char_traits<char>,std::allocator<char>_>
                                    *)&local_98);
        if (0xf < uStack_80) {
          pvVar6 = local_98;
          if ((0xfff < uStack_80 + 1) &&
             (pvVar6 = *(void **)((longlong)local_98 + -8),
             0x1f < (ulonglong)((longlong)local_98 + (-8 - (longlong)pvVar6)))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(pvVar6);
        }
      }
      dVar2 = DAT_180305520;
      dVar1 = DAT_180305518;
      *(double *)(this + 0x698) = (dVar9 * DAT_180305520) / DAT_180305518;
      *(double *)(this + 0x6a0) = (dVar10 * dVar2) / dVar1;
      *(double *)(this + 0x6a8) = (dVar11 * dVar2) / dVar1;
      *(int *)(this + 0x6b0) = iVar4;
      return true;
    }
    local_78 = "BearerBar";
    uStack_70 = 9;
    pCVar5 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
    FUN_180103b00(pCVar5,iVar4,2,&local_78);
  }
  return false;
}


