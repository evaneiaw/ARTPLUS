// DocumentMarks.dll 180020950 DocumentMarks::BearerBar::updatePdfPropertiesDictImp
// signature: void updatePdfPropertiesDictImp(BearerBar * this, Dictionary * param_1)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: virtual void __cdecl DocumentMarks::BearerBar::updatePdfPropertiesDictImp(class
   ArtDoc::Dictionary & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::BearerBar::updatePdfPropertiesDictImp(BearerBar *this,Dictionary *param_1)

{
  int iVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  Dictionary *pDVar5;
  void *pvVar6;
  longlong lVar7;
  longlong lVar8;
  undefined1 auStack_c8 [32];
  Dictionary local_a8 [16];
  void *local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  ulonglong uStack_80;
  void *local_78;
  undefined8 uStack_70;
  undefined *local_68;
  ulonglong uStack_60;
  ulonglong local_58;
  
                    /* 0x20950  2259
                       ?updatePdfPropertiesDictImp@BearerBar@DocumentMarks@@MEAAXAEAVDictionary@ArtDoc@@@Z
                        */
  local_58 = DAT_180418e00 ^ (ulonglong)auStack_c8;
  DynamicObject::updatePdfPropertiesDictImp((DynamicObject *)this,param_1);
  dVar2 = (*(double *)(this + 0x698) * DAT_180305518) / DAT_180305520;
  dVar3 = (*(double *)(this + 0x6a0) * DAT_180305518) / DAT_180305520;
  dVar4 = (*(double *)(this + 0x6a8) * DAT_180305518) / DAT_180305520;
  iVar1 = *(int *)(this + 0x6b0);
  local_78 = (void *)0x0;
  uStack_70 = 0;
  local_68 = (undefined *)0x0;
  uStack_60 = 0;
  lVar7 = -1;
  lVar8 = -1;
  do {
    lVar8 = lVar8 + 1;
  } while (PTR_s_DM_BearerBarParams_180418998[lVar8] != '\0');
  FUN_180010070(&local_78);
  pDVar5 = ArtDoc::Dictionary::AddDictionary
                     (param_1,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                              &local_78);
  ArtDoc::Dictionary::Dictionary(local_a8,pDVar5);
  if (0xf < uStack_60) {
    pvVar6 = local_78;
    if ((0xfff < uStack_60 + 1) &&
       (pvVar6 = *(void **)((longlong)local_78 + -8),
       0x1f < (ulonglong)((longlong)local_78 + (-8 - (longlong)pvVar6)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar6);
  }
  local_68 = PTR_180304c20;
  uStack_60 = _UNK_180304c28;
  local_78 = (void *)((ulonglong)local_78 & 0xffffffffffffff00);
  local_98 = (void *)0x0;
  uStack_90 = 0;
  local_88 = 0;
  uStack_80 = 0;
  lVar8 = -1;
  do {
    lVar8 = lVar8 + 1;
  } while (PTR_s_DM_BearerBarParams_Version_180418ad0[lVar8] != '\0');
  FUN_180010070(&local_98);
  ArtDoc::Dictionary::AddInteger
            (local_a8,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_98,2
            );
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
  } while (PTR_s_DM_BearerBarParams_Width_180418aa8[lVar8] != '\0');
  FUN_180010070(&local_98);
  ArtDoc::Dictionary::AddFloat
            (local_a8,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_98,
             dVar2);
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
  ArtDoc::Dictionary::AddFloat
            (local_a8,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_98,
             dVar3);
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
  ArtDoc::Dictionary::AddFloat
            (local_a8,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_98,
             dVar4);
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
  do {
    lVar7 = lVar7 + 1;
  } while (PTR_s_DM_BearerBarParams_Location_180418ac8[lVar7] != '\0');
  FUN_180010070(&local_98,PTR_s_DM_BearerBarParams_Location_180418ac8,lVar7);
  ArtDoc::Dictionary::AddInteger
            (local_a8,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_98,
             iVar1);
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
  ArtDoc::Dictionary::~Dictionary(local_a8);
  return;
}


