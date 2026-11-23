// 180111410 FUN_180111410

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_180111410(MarkReader *param_1,undefined8 *param_2)

{
  longlong *plVar1;
  int *piVar2;
  void *pvVar3;
  longlong *plVar4;
  ulonglong uVar5;
  bool bVar6;
  uint uVar7;
  int iVar8;
  Dictionary *pDVar9;
  Module *pMVar10;
  longlong lVar11;
  longlong lVar12;
  basic_ostream<char,std::char_traits<char>_> *pbVar13;
  ContentObject *pCVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  __uint64 _Var17;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar18;
  Dictionary *pDVar19;
  ContentObject *this;
  Dictionary *pDVar20;
  Properties *pPVar21;
  void *pvVar22;
  uint uVar23;
  double dVar24;
  undefined4 uVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  undefined4 uVar28;
  undefined1 auStack_218 [32];
  undefined4 local_1f8;
  uint local_1e8;
  ContentObject *local_1e0;
  ContentObject *local_1d8;
  undefined8 *local_1d0;
  MarksModule *local_1c8;
  undefined4 local_1b8 [14];
  undefined1 local_180;
  undefined8 local_178;
  longlong *plStack_170;
  void *local_168;
  undefined8 uStack_160;
  longlong local_158;
  undefined1 local_140;
  Dictionary local_138;
  undefined7 uStack_137;
  longlong local_128;
  ulonglong local_120;
  void *local_118;
  undefined8 uStack_110;
  undefined *local_108;
  ulonglong uStack_100;
  ContentObject *local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  ulonglong uStack_e0;
  void *local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  ulonglong uStack_c0;
  void *local_b8;
  undefined8 uStack_b0;
  undefined *local_a8;
  ulonglong uStack_a0;
  void *local_98 [3];
  ulonglong local_80;
  ulonglong local_78;
  
  local_78 = DAT_180418e00 ^ (ulonglong)auStack_218;
  uVar23 = 0;
  local_1e8 = 0;
  local_1e0 = (ContentObject *)((ulonglong)local_1e0 & 0xffffffff00000000);
  local_1d0 = param_2;
  local_1c8 = (MarksModule *)param_2;
  pDVar9 = ArtDoc::MarkReader::GetPropertiesAsDictionary(param_1);
  uStack_110 = 0;
  local_108 = (undefined *)0x4;
  uStack_100 = 0xf;
  local_118 = (void *)0x65707974;
  bVar6 = ArtDoc::Dictionary::HasStringValue
                    (pDVar9,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                            &local_118);
  if (0xf < uStack_100) {
    pvVar22 = local_118;
    if ((0xfff < uStack_100 + 1) &&
       (pvVar22 = *(void **)((longlong)local_118 + -8),
       0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar22);
  }
  if (!bVar6) {
    *param_2 = 0;
    return param_2;
  }
  uStack_f0 = 0;
  local_e8 = 6;
  uStack_e0 = 0xf;
  local_f8 = (ContentObject *)0x64696b72616d;
  ArtDoc::GetEskoStringValue
            ((Dictionary *)local_98,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)pDVar9)
  ;
  if (0xf < uStack_e0) {
    pCVar14 = local_f8;
    if ((0xfff < uStack_e0 + 1) &&
       (pCVar14 = *(ContentObject **)(local_f8 + -8),
       (ContentObject *)0x1f < local_f8 + (-8 - (longlong)pCVar14))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pCVar14);
  }
  uStack_110 = 0;
  local_108 = (undefined *)0x4;
  uStack_100 = 0xf;
  local_118 = (void *)0x65707974;
  ArtDoc::GetEskoStringValue
            (&local_138,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)pDVar9)
  ;
  if (0xf < uStack_100) {
    pvVar22 = local_118;
    if ((0xfff < uStack_100 + 1) &&
       (pvVar22 = *(void **)((longlong)local_118 + -8),
       0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar22);
  }
  pCVar14 = (ContentObject *)0x0;
  local_1d8 = (ContentObject *)0x0;
  pMVar10 = ArtDoc::FindModule(0x4d61726b);
  local_1f8 = 0;
  local_1c8 = (MarksModule *)
              __RTDynamicCast(pMVar10,0,&ArtDoc::Module::RTTI_Type_Descriptor,
                              &DocumentMarks::MarksModule::RTTI_Type_Descriptor);
  if (local_1c8 == (MarksModule *)0x0) {
    *param_2 = 0;
    if (0xf < local_120) {
      pvVar3 = (void *)CONCAT71(uStack_137,local_138);
      pvVar22 = pvVar3;
      if ((0xfff < local_120 + 1) &&
         (pvVar22 = *(void **)((longlong)pvVar3 + -8),
         0x1f < (ulonglong)((longlong)pvVar3 + (-8 - (longlong)pvVar22)))) goto LAB_180112f55;
      free(pvVar22);
    }
    if (local_80 < 0x10) {
      return param_2;
    }
    if (local_80 + 1 < 0x1000) goto LAB_1801116a3;
    lVar11 = (longlong)local_98[0] - (longlong)*(void **)((longlong)local_98[0] + -8);
    local_98[0] = *(void **)((longlong)local_98[0] + -8);
  }
  else {
    uVar7 = DocumentMarks::MarksModule::GetFeatures(local_1c8);
    uVar5 = local_120;
    lVar11 = local_128;
    if ((uVar7 & 1) != 0) {
      pDVar19 = (Dictionary *)CONCAT71(uStack_137,local_138);
      pDVar20 = &local_138;
      if (0xf < local_120) {
        pDVar20 = pDVar19;
      }
      if (local_128 == 0x18) {
        lVar12 = 0x696d616e79444941 - *(longlong *)pDVar20;
        if ((lVar12 == 0) && (lVar12 = 0x422d736b72614d63 - *(longlong *)(pDVar20 + 8), lVar12 == 0)
           ) {
          lVar12 = 0x7261427265726165 - *(longlong *)(pDVar20 + 0x10);
        }
        if (lVar12 != 0) goto LAB_18011185d;
        iVar8 = DocumentMarks::GetMarksDebugLevel();
        if (2 < iVar8) {
          pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(cout_exref,"createDynamicObject ");
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
        }
        local_1e0 = (ContentObject *)FUN_1802d6b50(0x6b8);
        if (local_1e0 == (ContentObject *)0x0) {
          pCVar14 = (ContentObject *)0x0;
        }
        else {
          pCVar14 = (ContentObject *)
                    DocumentMarks::BearerBar::BearerBar((BearerBar *)local_1e0,true);
        }
        local_1e8 = 0x60;
        local_1e0 = pCVar14;
        iVar8 = DocumentMarks::GetMarksDebugLevel();
        if (3 < iVar8) {
          uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
          uVar16 = __std_type_info_name(0x180447900,&DAT_18048b550);
          uVar15 = FUN_18001b3e0(uVar15,uVar16);
          pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(uVar15,&DAT_18031ffa4);
          _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
          pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,_Var17);
          pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                    FUN_18001b3e0(pbVar18,&DAT_180306c80);
          pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
        }
        DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
        uVar23 = 0x40;
        local_1e8 = 0x40;
        local_1d8 = pCVar14;
      }
      else {
LAB_18011185d:
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if ((local_128 == 0x19) &&
           (iVar8 = memcmp("AIDynamicMarks-CustomMark",pDVar20,0x19), iVar8 == 0)) {
          local_118 = (void *)0x0;
          uStack_110 = 0;
          local_108 = (undefined *)0x0;
          uStack_100 = 0;
          lVar11 = -1;
          do {
            lVar11 = lVar11 + 1;
          } while (PTR_s_DM_TextParams_180418990[lVar11] != '\0');
          FUN_180010070((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                        &local_118);
          bVar6 = ArtDoc::Dictionary::HasDictionaryValue
                            (pDVar9,(basic_string<char,std::char_traits<char>,std::allocator<char>_>
                                     *)&local_118);
          if (0xf < uStack_100) {
            pvVar22 = local_118;
            if ((0xfff < uStack_100 + 1) &&
               (pvVar22 = *(void **)((longlong)local_118 + -8),
               0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
              _invalid_parameter_noinfo_noreturn();
            }
            free(pvVar22);
          }
          if (bVar6) {
            local_b8 = (void *)0x0;
            uStack_b0 = 0;
            local_a8 = (undefined *)0x0;
            uStack_a0 = 0;
            lVar11 = -1;
            do {
              lVar11 = lVar11 + 1;
            } while (PTR_s_DM_TextParams_180418990[lVar11] != '\0');
            FUN_180010070(&local_b8);
            pDVar19 = ArtDoc::Dictionary::GetDictionaryValue
                                (pDVar9,(basic_string<char,std::char_traits<char>,std::allocator<char>_>
                                         *)&local_b8);
            ArtDoc::Dictionary::Dictionary((Dictionary *)&local_f8,pDVar19);
            if (0xf < uStack_a0) {
              pvVar22 = local_b8;
              if ((0xfff < uStack_a0 + 1) &&
                 (pvVar22 = *(void **)((longlong)local_b8 + -8),
                 0x1f < (ulonglong)((longlong)local_b8 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                _invalid_parameter_noinfo_noreturn();
              }
              free(pvVar22);
            }
            local_a8 = (undefined *)0x0;
            uStack_a0 = 0xf;
            local_b8 = (void *)((ulonglong)local_b8 & 0xffffffffffffff00);
            local_118 = (void *)0x0;
            uStack_110 = 0;
            local_108 = (undefined *)0x0;
            uStack_100 = 0;
            lVar11 = -1;
            do {
              lVar11 = lVar11 + 1;
            } while (PTR_s_DM_TextParams_Version_180418bc8[lVar11] != '\0');
            FUN_180010070((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                          &local_118);
            iVar8 = ArtDoc::Dictionary::GetIntegerValue
                              ((Dictionary *)&local_f8,
                               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                               &local_118);
            if (0xf < uStack_100) {
              pvVar22 = local_118;
              if ((0xfff < uStack_100 + 1) &&
                 (pvVar22 = *(void **)((longlong)local_118 + -8),
                 0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                _invalid_parameter_noinfo_noreturn();
              }
              free(pvVar22);
            }
            uVar27 = 0;
            uVar28 = 0;
            uVar25 = 0;
            uVar26 = 0;
            local_d8 = (void *)0x0;
            uStack_d0 = 0;
            local_c8 = 0;
            uStack_c0 = 0;
            lVar11 = -1;
            do {
              lVar11 = lVar11 + 1;
            } while (PTR_s_DM_TextParams_Area_Width_180418be0[lVar11] != '\0');
            FUN_180010070(&local_d8);
            uVar23 = 2;
            local_1e8 = 2;
            bVar6 = ArtDoc::Dictionary::HasFloatValue
                              ((Dictionary *)&local_f8,
                               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                               &local_d8);
            if (bVar6) {
              local_118 = (void *)0x0;
              uStack_110 = 0;
              local_108 = (undefined *)0x0;
              uStack_100 = 0;
              lVar11 = -1;
              do {
                lVar11 = lVar11 + 1;
              } while (PTR_s_DM_TextParams_Area_Height_180418be8[lVar11] != '\0');
              FUN_180010070((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                            &local_118);
              uVar23 = 6;
              local_1e8 = 6;
              bVar6 = ArtDoc::Dictionary::HasFloatValue
                                ((Dictionary *)&local_f8,
                                 (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                 &local_118);
              if (!bVar6) goto LAB_180111ad3;
              bVar6 = true;
            }
            else {
LAB_180111ad3:
              bVar6 = false;
            }
            if ((uVar23 & 4) != 0) {
              uVar23 = uVar23 & 0xfffffffb;
              local_1e8 = uVar23;
              if (0xf < uStack_100) {
                pvVar22 = local_118;
                if ((0xfff < uStack_100 + 1) &&
                   (pvVar22 = *(void **)((longlong)local_118 + -8),
                   0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                  _invalid_parameter_noinfo_noreturn();
                }
                free(pvVar22);
              }
              local_108 = (undefined *)0x0;
              uStack_100 = 0xf;
              local_118 = (void *)((ulonglong)local_118 & 0xffffffffffffff00);
            }
            if (((uVar23 & 2) != 0) &&
               (uVar23 = uVar23 & 0xfffffffd, local_1e8 = uVar23, 0xf < uStack_c0)) {
              pvVar22 = local_d8;
              if ((0xfff < uStack_c0 + 1) &&
                 (pvVar22 = *(void **)((longlong)local_d8 + -8),
                 0x1f < (ulonglong)((longlong)local_d8 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                _invalid_parameter_noinfo_noreturn();
              }
              free(pvVar22);
            }
            if (bVar6) {
              local_d8 = (void *)0x0;
              uStack_d0 = 0;
              local_c8 = 0;
              uStack_c0 = 0;
              lVar11 = -1;
              do {
                lVar11 = lVar11 + 1;
              } while (PTR_s_DM_TextParams_Area_Width_180418be0[lVar11] != '\0');
              FUN_180010070(&local_d8);
              dVar24 = ArtDoc::Dictionary::GetFloatValue
                                 ((Dictionary *)&local_f8,
                                  (basic_string<char,std::char_traits<char>,std::allocator<char>_> *
                                  )&local_d8);
              uVar27 = SUB84(dVar24,0);
              uVar28 = (undefined4)((ulonglong)dVar24 >> 0x20);
              if (0xf < uStack_c0) {
                pvVar22 = local_d8;
                if ((0xfff < uStack_c0 + 1) &&
                   (pvVar22 = *(void **)((longlong)local_d8 + -8),
                   0x1f < (ulonglong)((longlong)local_d8 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                  _invalid_parameter_noinfo_noreturn();
                }
                free(pvVar22);
              }
              local_d8 = (void *)0x0;
              uStack_d0 = 0;
              local_c8 = 0;
              uStack_c0 = 0;
              lVar11 = -1;
              do {
                lVar11 = lVar11 + 1;
              } while (PTR_s_DM_TextParams_Area_Height_180418be8[lVar11] != '\0');
              FUN_180010070(&local_d8);
              dVar24 = ArtDoc::Dictionary::GetFloatValue
                                 ((Dictionary *)&local_f8,
                                  (basic_string<char,std::char_traits<char>,std::allocator<char>_> *
                                  )&local_d8);
              uVar25 = SUB84(dVar24,0);
              uVar26 = (undefined4)((ulonglong)dVar24 >> 0x20);
              if (0xf < uStack_c0) {
                pvVar22 = local_d8;
                if ((0xfff < uStack_c0 + 1) &&
                   (pvVar22 = *(void **)((longlong)local_d8 + -8),
                   0x1f < (ulonglong)((longlong)local_d8 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                  _invalid_parameter_noinfo_noreturn();
                }
                free(pvVar22);
              }
            }
            if (((iVar8 < 2) ||
                ((double)CONCAT44(uVar28,uVar27) < 0.0 || (double)CONCAT44(uVar28,uVar27) == 0.0))
               || ((double)CONCAT44(uVar26,uVar25) < 0.0 || (double)CONCAT44(uVar26,uVar25) == 0.0))
            {
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (2 < iVar8) {
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(cout_exref,"createDynamicObject ");
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              local_1e0 = (ContentObject *)FUN_1802d6b50(0x750);
              if (local_1e0 == (ContentObject *)0x0) {
                pCVar14 = (ContentObject *)0x0;
              }
              else {
                pCVar14 = (ContentObject *)
                          DocumentMarks::TextMark::TextMark((TextMark *)local_1e0,true);
              }
              local_1e8 = uVar23 | 0x18000;
              local_1e0 = pCVar14;
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (3 < iVar8) {
                uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                uVar16 = __std_type_info_name(0x18042cab0,&DAT_18048b550);
                uVar15 = FUN_18001b3e0(uVar15,uVar16);
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                    (pbVar13,_Var17);
                pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                          FUN_18001b3e0(pbVar18,&DAT_180306c80);
                pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
              uVar23 = uVar23 | 0x10000;
              local_1b8[0] = 3;
              local_180 = 0;
              local_178 = 0;
              plStack_170 = (longlong *)0x0;
              local_168 = (void *)0x0;
              uStack_160 = 0;
              local_158 = 0;
              local_140 = 0;
              local_1e8 = uVar23;
              local_1d8 = pCVar14;
              DocumentTypesetting::SetRecognitionContext(pCVar14,(RecognitionContext *)local_1b8);
            }
            else {
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (2 < iVar8) {
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(cout_exref,"createDynamicObject ");
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              local_1e0 = (ContentObject *)FUN_1802d6b50(0x858);
              if (local_1e0 == (ContentObject *)0x0) {
                pCVar14 = (ContentObject *)0x0;
              }
              else {
                pCVar14 = (ContentObject *)
                          DocumentMarks::TextAreaMark::TextAreaMark((TextAreaMark *)local_1e0,true);
              }
              local_1e8 = uVar23 | 0x6000000;
              local_1e0 = pCVar14;
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (3 < iVar8) {
                uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                uVar16 = __std_type_info_name(0x18042c1e8,&DAT_18048b550);
                uVar15 = FUN_18001b3e0(uVar15,uVar16);
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                    (pbVar13,_Var17);
                pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                          FUN_18001b3e0(pbVar18,&DAT_180306c80);
                pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
              uVar23 = uVar23 | 0x4000000;
              local_1b8[0] = 1;
              local_180 = 0;
              local_178 = 0;
              plStack_170 = (longlong *)0x0;
              local_168 = (void *)0x0;
              uStack_160 = 0;
              local_158 = 0;
              local_140 = 0;
              local_1e8 = uVar23;
              local_1d8 = pCVar14;
              DocumentTypesetting::SetRecognitionContext(pCVar14,(RecognitionContext *)local_1b8);
            }
            FUN_1800653d0(local_1b8);
            ArtDoc::Dictionary::~Dictionary((Dictionary *)&local_f8);
          }
          else {
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (2 < iVar8) {
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(cout_exref,"createDynamicObject ");
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            local_1e0 = (ContentObject *)FUN_1802d6b50(0x698);
            if (local_1e0 == (ContentObject *)0x0) {
              pCVar14 = (ContentObject *)0x0;
            }
            else {
              pCVar14 = (ContentObject *)
                        DocumentMarks::CustomMark::CustomMark((CustomMark *)local_1e0,true,0xff);
            }
            local_1e8 = 0x6000;
            local_1e0 = pCVar14;
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (3 < iVar8) {
              uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
              uVar16 = __std_type_info_name(0x18044e738,&DAT_18048b550);
              uVar15 = FUN_18001b3e0(uVar15,uVar16);
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(uVar15,&DAT_18031ffa4);
              _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
              pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,_Var17)
              ;
              pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                        FUN_18001b3e0(pbVar18,&DAT_180306c80);
              pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
            uVar23 = 0x4000;
            local_1e8 = 0x4000;
            local_1d8 = pCVar14;
          }
        }
        else {
          pDVar20 = &local_138;
          if (0xf < uVar5) {
            pDVar20 = pDVar19;
          }
          if ((lVar11 == 0x17) &&
             (iVar8 = memcmp("AIDynamicMarks-GridMark",pDVar20,0x17), iVar8 == 0)) {
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (2 < iVar8) {
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(cout_exref,"createDynamicObject ");
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            local_1e0 = (ContentObject *)FUN_1802d6b50(0x710);
            if (local_1e0 == (ContentObject *)0x0) {
              pCVar14 = (ContentObject *)0x0;
            }
            else {
              pCVar14 = (ContentObject *)
                        DocumentMarks::GridMark::GridMark((GridMark *)local_1e0,true);
            }
            local_1e8 = 0x1800;
            local_1e0 = pCVar14;
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (3 < iVar8) {
              uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
              uVar16 = __std_type_info_name(0x1804669e0,&DAT_18048b550);
              uVar15 = FUN_18001b3e0(uVar15,uVar16);
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(uVar15,&DAT_18031ffa4);
              _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
              pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,_Var17)
              ;
              pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                        FUN_18001b3e0(pbVar18,&DAT_180306c80);
              pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
            uVar23 = 0x1000;
            local_1e8 = 0x1000;
            local_1d8 = pCVar14;
          }
          else {
            pDVar20 = &local_138;
            if (0xf < uVar5) {
              pDVar20 = pDVar19;
            }
            if ((lVar11 == 0x1d) &&
               (iVar8 = memcmp("AIDynamicMarks-GradationStrip",pDVar20,0x1d), iVar8 == 0)) {
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (2 < iVar8) {
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(cout_exref,"createDynamicObject ");
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              local_1e0 = (ContentObject *)FUN_1802d6b50(0x6a0);
              if (local_1e0 == (ContentObject *)0x0) {
                pCVar14 = (ContentObject *)0x0;
              }
              else {
                pCVar14 = (ContentObject *)
                          DocumentMarks::GradationMark::GradationMark
                                    ((GradationMark *)local_1e0,true);
              }
              local_1e8 = 0x60000;
              local_1e0 = pCVar14;
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (3 < iVar8) {
                uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                uVar16 = __std_type_info_name(0x1804664f8,&DAT_18048b550);
                uVar15 = FUN_18001b3e0(uVar15,uVar16);
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                    (pbVar13,_Var17);
                pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                          FUN_18001b3e0(pbVar18,&DAT_180306c80);
                pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
              uVar23 = 0x40000;
              local_1e8 = 0x40000;
              local_1d8 = pCVar14;
            }
            else {
              pDVar20 = &local_138;
              if (0xf < uVar5) {
                pDVar20 = pDVar19;
              }
              if ((lVar11 == 0x16) &&
                 (iVar8 = memcmp("AIDynamicMarks-CutMark",pDVar20,0x16), iVar8 == 0)) {
                iVar8 = DocumentMarks::GetMarksDebugLevel();
                if (2 < iVar8) {
                  pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                            FUN_18001b3e0(cout_exref,"createDynamicObject ");
                  std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            (pbVar13,FUN_18003dae0);
                }
                local_1e0 = (ContentObject *)FUN_1802d6b50(0x6a0);
                if (local_1e0 == (ContentObject *)0x0) {
                  pCVar14 = (ContentObject *)0x0;
                }
                else {
                  pCVar14 = (ContentObject *)
                            DocumentMarks::CutMark::CutMark((CutMark *)local_1e0,true);
                }
                local_1e8 = 0x1800000;
                local_1e0 = pCVar14;
                iVar8 = DocumentMarks::GetMarksDebugLevel();
                if (3 < iVar8) {
                  uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                  uVar16 = __std_type_info_name(0x18044eda8,&DAT_18048b550);
                  uVar15 = FUN_18001b3e0(uVar15,uVar16);
                  pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                            FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                  _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                  pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                      (pbVar13,_Var17);
                  pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                            FUN_18001b3e0(pbVar18,&DAT_180306c80);
                  pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                  std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            (pbVar13,FUN_18003dae0);
                }
                DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
                uVar23 = 0x1000000;
                local_1e8 = 0x1000000;
                local_1d8 = pCVar14;
              }
              else {
                pDVar20 = &local_138;
                if (0xf < uVar5) {
                  pDVar20 = pDVar19;
                }
                if ((lVar11 == 0x19) &&
                   (iVar8 = memcmp("AIDynamicMarks-CornerMark",pDVar20,0x19), iVar8 == 0)) {
                  iVar8 = DocumentMarks::GetMarksDebugLevel();
                  if (2 < iVar8) {
                    pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                              FUN_18001b3e0(cout_exref,"createDynamicObject ");
                    std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              (pbVar13,FUN_18003dae0);
                  }
                  local_1e0 = (ContentObject *)FUN_1802d6b50(0x6b0);
                  if (local_1e0 == (ContentObject *)0x0) {
                    pCVar14 = (ContentObject *)0x0;
                  }
                  else {
                    pCVar14 = (ContentObject *)
                              DocumentMarks::CornerMark::CornerMark((CornerMark *)local_1e0,true);
                  }
                  local_1e8 = 0x18000000;
                  local_1e0 = pCVar14;
                  iVar8 = DocumentMarks::GetMarksDebugLevel();
                  if (3 < iVar8) {
                    uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                    uVar16 = __std_type_info_name(0x18044e638,&DAT_18048b550);
                    uVar15 = FUN_18001b3e0(uVar15,uVar16);
                    pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                              FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                    _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                    pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                        (pbVar13,_Var17);
                    pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                              FUN_18001b3e0(pbVar18,&DAT_180306c80);
                    pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                    std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              (pbVar13,FUN_18003dae0);
                  }
                  DocumentMarks::DynamicObject::setPdfPropertiesDict
                            ((DynamicObject *)pCVar14,pDVar9);
                  uVar23 = 0x10000000;
                  local_1e8 = 0x10000000;
                  local_1d8 = pCVar14;
                }
                else {
                  pDVar20 = &local_138;
                  if (0xf < uVar5) {
                    pDVar20 = pDVar19;
                  }
                  if ((lVar11 == 0x1a) &&
                     (iVar8 = memcmp("AIDynamicMarks-BarcodeMark",pDVar20,0x1a), iVar8 == 0)) {
                    iVar8 = DocumentMarks::GetMarksDebugLevel();
                    if (2 < iVar8) {
                      pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                                FUN_18001b3e0(cout_exref,"createDynamicObject ");
                      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                (pbVar13,FUN_18003dae0);
                    }
                    local_1e0 = (ContentObject *)FUN_1802d6b50(0x6d8);
                    if (local_1e0 == (ContentObject *)0x0) {
                      pCVar14 = (ContentObject *)0x0;
                    }
                    else {
                      pCVar14 = (ContentObject *)
                                DocumentMarks::BarcodeMark::BarcodeMark
                                          ((BarcodeMark *)local_1e0,true);
                    }
                    local_1e8 = 0x80000000;
                    local_1e0 = pCVar14;
                    iVar8 = DocumentMarks::GetMarksDebugLevel();
                    if (3 < iVar8) {
                      uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                      uVar16 = __std_type_info_name(0x180447398,&DAT_18048b550);
                      uVar15 = FUN_18001b3e0(uVar15,uVar16);
                      pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                                FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                      _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                      pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                          (pbVar13,_Var17);
                      pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                                FUN_18001b3e0(pbVar18,&DAT_180306c80);
                      pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                (pbVar13,FUN_18003dae0);
                    }
                    DocumentMarks::DynamicObject::setPdfPropertiesDict
                              ((DynamicObject *)pCVar14,pDVar9);
                    uVar23 = 0;
                    local_1e8 = 0;
                    local_1d8 = pCVar14;
                  }
                  else {
                    pDVar20 = &local_138;
                    if (0xf < uVar5) {
                      pDVar20 = pDVar19;
                    }
                    if (lVar11 == 0x18) {
                      lVar11 = 0x696d616e79444941 - *(longlong *)pDVar20;
                      if ((lVar11 == 0) &&
                         (lVar11 = 0x492d736b72614d63 - *(longlong *)(pDVar20 + 8), lVar11 == 0)) {
                        lVar11 = 0x6b72614d6567616d - *(longlong *)(pDVar20 + 0x10);
                      }
                      if (lVar11 == 0) {
                        iVar8 = DocumentMarks::GetMarksDebugLevel();
                        if (2 < iVar8) {
                          pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                                    FUN_18001b3e0(cout_exref,"createDynamicObject ");
                          std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                    (pbVar13,FUN_18003dae0);
                        }
                        local_f8 = (ContentObject *)FUN_1802d6b50(0x708);
                        if (local_f8 == (ContentObject *)0x0) {
                          pCVar14 = (ContentObject *)0x0;
                        }
                        else {
                          pCVar14 = (ContentObject *)
                                    DocumentMarks::ImageMark::ImageMark((ImageMark *)local_f8,true);
                        }
                        local_1e0 = (ContentObject *)CONCAT44(local_1e0._4_4_,6);
                        local_f8 = pCVar14;
                        iVar8 = DocumentMarks::GetMarksDebugLevel();
                        if (3 < iVar8) {
                          uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                          uVar16 = __std_type_info_name(0x180467380,&DAT_18048b550);
                          uVar15 = FUN_18001b3e0(uVar15,uVar16);
                          pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                                    FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                          _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                          pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                              (pbVar13,_Var17);
                          pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                                    FUN_18001b3e0(pbVar18,&DAT_180306c80);
                          pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                          std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                    (pbVar13,FUN_18003dae0);
                        }
                        DocumentMarks::DynamicObject::setPdfPropertiesDict
                                  ((DynamicObject *)pCVar14,pDVar9);
                        local_1d8 = pCVar14;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      param_2 = local_1d0;
    }
    uVar7 = DocumentMarks::MarksModule::GetFeatures(local_1c8);
    this = pCVar14;
    if ((uVar7 & 0x40) == 0) {
LAB_180112ef3:
      pDVar19 = (Dictionary *)CONCAT71(uStack_137,local_138);
LAB_180112efb:
      if (this != (ContentObject *)0x0) {
        pPVar21 = ArtDoc::ContentObject::GetProperties(this);
        FUN_18010e240(pPVar21,&PTR_s_MarkObjectID_18030db80,local_98);
        goto LAB_180112f1f;
      }
    }
    else {
      pDVar19 = (Dictionary *)CONCAT71(uStack_137,local_138);
      pDVar20 = &local_138;
      if (0xf < local_120) {
        pDVar20 = pDVar19;
      }
      if (local_128 != 0xc) {
LAB_180112a5e:
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if (local_128 == 0xb) {
          lVar11 = 0x5461657241696e55 - *(longlong *)pDVar20;
          if ((lVar11 == 0) && (lVar11 = 0x7865 - (ulonglong)*(ushort *)(pDVar20 + 8), lVar11 == 0))
          {
            lVar11 = 0x74 - (ulonglong)(byte)pDVar20[10];
          }
          if (lVar11 != 0) goto LAB_180112b3a;
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (2 < iVar8) {
            pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                      FUN_18001b3e0(cout_exref,"createDynamicObject ");
            std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
          }
          local_f8 = (ContentObject *)FUN_1802d6b50(0x6e8);
          if (local_f8 == (ContentObject *)0x0) {
            this = (ContentObject *)0x0;
          }
          else {
            this = (ContentObject *)
                   DocumentMarks::VDPAreaText::VDPAreaText((VDPAreaText *)local_f8,true);
          }
          local_1e8 = uVar23 | 0x180;
          local_f8 = this;
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (iVar8 < 4) goto LAB_180112ecd;
          uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
          uVar16 = 0x18042cb18;
LAB_180112e61:
          uVar16 = __std_type_info_name(uVar16,&DAT_18048b550);
          uVar15 = FUN_18001b3e0(uVar15,uVar16);
          pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(uVar15,&DAT_18031ffa4);
          _Var17 = ArtDoc::ContentObject::GetID(this);
          pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,_Var17);
          pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                    FUN_18001b3e0(pbVar18,&DAT_180306c80);
          pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
LAB_180112ecd:
          DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)this,pDVar9);
          local_1d8 = this;
          if (pCVar14 != (ContentObject *)0x0) {
            (*(code *)**(undefined8 **)pCVar14)(pCVar14,1);
          }
          goto LAB_180112ef3;
        }
LAB_180112b3a:
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if (local_128 == 7) {
          iVar8 = 0x63726142 - *(int *)pDVar20;
          if ((iVar8 == 0) && (iVar8 = 0x646f - (uint)*(ushort *)(pDVar20 + 4), iVar8 == 0)) {
            iVar8 = 0x65 - (uint)(byte)pDVar20[6];
          }
          if (iVar8 != 0) goto LAB_180112c13;
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (2 < iVar8) {
            pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                      FUN_18001b3e0(cout_exref,"createDynamicObject ");
            std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
          }
          local_f8 = (ContentObject *)FUN_1802d6b50(0x6d8);
          if (local_f8 == (ContentObject *)0x0) {
            this = (ContentObject *)0x0;
          }
          else {
            this = (ContentObject *)
                   DocumentMarks::VDPBarcode::VDPBarcode((VDPBarcode *)local_f8,true);
          }
          local_1e8 = uVar23 | 0x600;
          local_f8 = this;
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (3 < iVar8) {
            uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
            uVar16 = 0x18042cb48;
            goto LAB_180112e61;
          }
          goto LAB_180112ecd;
        }
LAB_180112c13:
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if (local_128 == 9) {
          lVar11 = 0x6e6f4d6567616d49 - *(longlong *)pDVar20;
          if (lVar11 == 0) {
            lVar11 = 0x6f - (ulonglong)(byte)pDVar20[8];
          }
          if (lVar11 == 0) {
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (2 < iVar8) {
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(cout_exref,"createDynamicObject ");
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            local_f8 = (ContentObject *)FUN_1802d6b50(0x808);
            if (local_f8 == (ContentObject *)0x0) {
              this = (ContentObject *)0x0;
            }
            else {
              this = (ContentObject *)
                     DocumentMarks::VDPImageMono::VDPImageMono((VDPImageMono *)local_f8,true);
            }
            local_1e8 = uVar23 | 0x180000;
            local_f8 = this;
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (3 < iVar8) {
              uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
              uVar16 = 0x18042cb78;
              goto LAB_180112e61;
            }
            goto LAB_180112ecd;
          }
        }
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if (local_128 == 10) {
          lVar11 = 0x6c6f436567616d49 - *(longlong *)pDVar20;
          if (lVar11 == 0) {
            lVar11 = 0x726f - (ulonglong)*(ushort *)(pDVar20 + 8);
          }
          if (lVar11 == 0) {
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (2 < iVar8) {
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(cout_exref,"createDynamicObject ");
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            local_f8 = (ContentObject *)FUN_1802d6b50(0x808);
            if (local_f8 == (ContentObject *)0x0) {
              this = (ContentObject *)0x0;
            }
            else {
              this = (ContentObject *)
                     DocumentMarks::VDPImageColor::VDPImageColor((VDPImageColor *)local_f8,true);
            }
            local_1e8 = uVar23 | 0x600000;
            local_f8 = this;
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (3 < iVar8) {
              uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
              uVar16 = 0x18042cbb0;
              goto LAB_180112e61;
            }
            goto LAB_180112ecd;
          }
        }
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if ((local_128 == 8) && (*(longlong *)pDVar20 == 0x4644506567616d49)) {
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (2 < iVar8) {
            pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                      FUN_18001b3e0(cout_exref,"createDynamicObject ");
            std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
          }
          local_f8 = (ContentObject *)FUN_1802d6b50(0x838);
          if (local_f8 == (ContentObject *)0x0) {
            this = (ContentObject *)0x0;
          }
          else {
            this = (ContentObject *)
                   DocumentMarks::VDPImagePDF::VDPImagePDF((VDPImagePDF *)local_f8,true);
          }
          local_1e8 = uVar23 | 0x60000000;
          local_f8 = this;
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (3 < iVar8) {
            uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
            uVar16 = 0x18042cbe8;
            goto LAB_180112e61;
          }
          goto LAB_180112ecd;
        }
        goto LAB_180112efb;
      }
      lVar11 = 0x746e696f50696e55 - *(longlong *)pDVar20;
      if (lVar11 == 0) {
        lVar11 = 0x74786554 - (ulonglong)*(uint *)(pDVar20 + 8);
      }
      if (lVar11 != 0) goto LAB_180112a5e;
      iVar8 = DocumentMarks::GetMarksDebugLevel();
      if (2 < iVar8) {
        pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                  FUN_18001b3e0(cout_exref,"createDynamicObject ");
        std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
      }
      local_f8 = (ContentObject *)FUN_1802d6b50(0x6d8);
      if (local_f8 == (ContentObject *)0x0) {
        this = (ContentObject *)0x0;
      }
      else {
        this = (ContentObject *)
               DocumentMarks::VDPPointText::VDPPointText((VDPPointText *)local_f8,true);
      }
      local_1e8 = uVar23 | 0x18;
      local_f8 = this;
      iVar8 = DocumentMarks::GetMarksDebugLevel();
      if (3 < iVar8) {
        uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
        uVar16 = __std_type_info_name(0x18042cae0,&DAT_18048b550);
        uVar15 = FUN_18001b3e0(uVar15,uVar16);
        pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                  FUN_18001b3e0(uVar15,&DAT_18031ffa4);
        _Var17 = ArtDoc::ContentObject::GetID(this);
        pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,_Var17);
        pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                  FUN_18001b3e0(pbVar18,&DAT_180306c80);
        pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
        std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
      }
      DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)this,pDVar9);
      local_1d8 = this;
      if (pCVar14 != (ContentObject *)0x0) {
        (*(code *)**(undefined8 **)pCVar14)(pCVar14,1);
      }
      if (this != (ContentObject *)0x0) {
        local_1b8[0] = 3;
        local_180 = 0;
        local_178 = 0;
        plStack_170 = (longlong *)0x0;
        local_168 = (void *)0x0;
        uStack_160 = 0;
        local_158 = 0;
        local_140 = 0;
        DocumentTypesetting::SetRecognitionContext(this,(RecognitionContext *)local_1b8);
        if (local_168 != (void *)0x0) {
          pvVar22 = local_168;
          if ((0xfff < (ulonglong)(((local_158 - (longlong)local_168) / 0xb0) * 0xb0)) &&
             (pvVar22 = *(void **)((longlong)local_168 + -8),
             0x1f < (ulonglong)((longlong)local_168 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(pvVar22);
          local_168 = (void *)0x0;
          uStack_160 = 0;
          local_158 = 0;
        }
        plVar4 = plStack_170;
        if (plStack_170 != (longlong *)0x0) {
          LOCK();
          plVar1 = plStack_170 + 1;
          lVar11 = *plVar1;
          *(int *)plVar1 = (int)*plVar1 + -1;
          UNLOCK();
          if ((int)lVar11 == 1) {
            (**(code **)*plStack_170)(plStack_170);
            LOCK();
            piVar2 = (int *)((longlong)plVar4 + 0xc);
            iVar8 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar8 == 1) {
              (**(code **)(*plVar4 + 8))(plVar4);
            }
          }
        }
        goto LAB_180112ef3;
      }
LAB_180112f1f:
      pDVar19 = (Dictionary *)CONCAT71(uStack_137,local_138);
    }
    *param_2 = this;
    if (0xf < local_120) {
      pDVar9 = pDVar19;
      if ((0xfff < local_120 + 1) &&
         (pDVar9 = *(Dictionary **)(pDVar19 + -8),
         (Dictionary *)0x1f < pDVar19 + (-8 - (longlong)pDVar9))) {
LAB_180112f55:
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pDVar9);
    }
    if (local_80 < 0x10) {
      return param_2;
    }
    if (local_80 + 1 < 0x1000) goto LAB_1801116a3;
    lVar11 = (longlong)local_98[0] - (longlong)*(void **)((longlong)local_98[0] + -8);
    local_98[0] = *(void **)((longlong)local_98[0] + -8);
  }
  if (0x1f < lVar11 - 8U) {
    local_120 = 0xf;
    local_128 = 0;
    local_138 = (Dictionary)0x0;
                    /* WARNING: Subroutine does not return */
    _invalid_parameter_noinfo_noreturn();
  }
LAB_1801116a3:
  local_120 = 0xf;
  local_128 = 0;
  local_138 = (Dictionary)0x0;
  free(local_98[0]);
  return param_2;
}


