// DocumentMarks.dll 180113be0 FUN_180113be0
// signature: undefined FUN_180113be0(void)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180113be0(MarkReader *param_1,ContentObject *param_2)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  Dictionary *this;
  int ****ppppiVar5;
  undefined8 uVar6;
  basic_ostream<char,std::char_traits<char>_> *pbVar7;
  __uint64 _Var8;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar9;
  Properties *pPVar10;
  Module *pMVar11;
  MarksModule *this_00;
  undefined **ppuVar12;
  char *pcVar13;
  Content *pCVar14;
  void *pvVar15;
  int ****ppppiVar16;
  undefined8 ****ppppuVar17;
  int ***pppiVar18;
  int ***pppiVar19;
  undefined *puVar20;
  ulonglong uVar21;
  ulonglong uVar22;
  undefined1 auStack_258 [32];
  undefined4 local_238;
  undefined8 local_228;
  int ***pppiStack_220;
  undefined8 local_218;
  ulonglong uStack_210;
  int ****local_208;
  int ***pppiStack_200;
  int ***local_1f8;
  int ***pppiStack_1f0;
  undefined8 ****local_1e8 [2];
  undefined8 local_1d8;
  ulonglong local_1d0;
  undefined8 local_1c8;
  undefined8 uStack_1c0;
  undefined *local_1b8;
  ulonglong uStack_1b0;
  undefined8 local_1a8;
  undefined8 uStack_1a0;
  undefined *local_198;
  ulonglong uStack_190;
  undefined **local_188 [2];
  undefined *local_178;
  ulonglong uStack_170;
  undefined ***local_150;
  VisitorBase local_148 [8];
  Visitor<DocumentBarCode::BarCode> local_140 [8];
  longlong local_138 [7];
  longlong *local_100;
  VisitorBase local_f8 [8];
  Visitor<DocumentBarCode::BarCode> local_f0 [8];
  longlong local_e8 [7];
  longlong *local_b0;
  VisitorBase local_a8 [8];
  Visitor<DocumentBarCode::BarCode> local_a0 [8];
  longlong local_98 [7];
  longlong *local_60;
  ulonglong local_58;
  
  local_58 = DAT_180418e00 ^ (ulonglong)auStack_258;
  local_228 = (int ****)((ulonglong)local_228 & 0xffffffff00000000);
  this = ArtDoc::MarkReader::GetPropertiesAsDictionary(param_1);
  uVar22 = _UNK_180309198;
  uVar6 = _DAT_180309190;
  uStack_1a0 = 0;
  local_198 = (undefined *)_DAT_180309190;
  uStack_190 = _UNK_180309198;
  local_1a8 = (void *)(ulonglong)
                      CONCAT16(s_Private_180320028[6],
                               CONCAT24(s_Private_180320028._4_2_,s_Private_180320028._0_4_));
  bVar2 = ArtDoc::Dictionary::HasDictionaryValue
                    (this,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                          &local_1a8);
  puVar20 = PTR_180304c20;
  uVar21 = _UNK_180304c28;
  if (bVar2) {
    uStack_1c0 = 0;
    local_1b8 = (undefined *)uVar6;
    uStack_1b0 = uVar22;
    local_1c8 = (void *)(ulonglong)
                        CONCAT16(s_Private_180320028[6],
                                 CONCAT24(s_Private_180320028._4_2_,s_Private_180320028._0_4_));
    local_228 = (int ****)CONCAT44(local_228._4_4_,1);
    this = ArtDoc::Dictionary::GetDictionaryValue
                     (this,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                           &local_1c8);
    uVar21 = _UNK_180304c28;
    puVar20 = PTR_180304c20;
    if (0xf < uStack_1b0) {
      pvVar15 = local_1c8;
      if ((0xfff < uStack_1b0 + 1) &&
         (pvVar15 = *(void **)((longlong)local_1c8 + -8),
         0x1f < (ulonglong)((longlong)local_1c8 + (-8 - (longlong)pvVar15)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar15);
    }
    local_1b8 = puVar20;
    uStack_1b0 = uVar21;
    local_1c8 = (void *)((ulonglong)local_1c8 & 0xffffffffffffff00);
  }
  if (0xf < uStack_190) {
    pvVar15 = local_1a8;
    if ((0xfff < uStack_190 + 1) &&
       (pvVar15 = *(void **)((longlong)local_1a8 + -8),
       0x1f < (ulonglong)((longlong)local_1a8 + (-8 - (longlong)pvVar15)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar15);
    puVar20 = PTR_180304c20;
    uVar21 = _UNK_180304c28;
  }
  uVar22 = _UNK_180308bb8;
  uVar6 = _DAT_180308bb0;
  local_1a8 = (void *)((ulonglong)local_1a8 & 0xffffffffffffff00);
  pppiStack_220 = (int ***)0x0;
  local_218 = _DAT_180308bb0;
  uStack_210 = _UNK_180308bb8;
  local_228._0_6_ = CONCAT24(s_markid_18030de94._4_2_,s_markid_18030de94._0_4_);
  local_228 = (int ****)(ulonglong)(uint6)local_228;
  local_198 = puVar20;
  uStack_190 = uVar21;
  bVar2 = ArtDoc::Dictionary::HasStringValue
                    (this,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                          &local_228);
  if (0xf < uStack_210) {
    pvVar15 = local_228;
    if ((0xfff < uStack_210 + 1) &&
       (pvVar15 = *(void **)((longlong)local_228 + -8),
       0x1f < (ulonglong)((longlong)local_228 + (-8 - (longlong)pvVar15)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar15);
    uVar6 = _DAT_180308bb0;
    uVar22 = _UNK_180308bb8;
  }
  if (!bVar2) {
    return;
  }
  pppiStack_220 = (int ***)0x0;
  local_228._0_6_ = CONCAT24(s_markid_18030de94._4_2_,s_markid_18030de94._0_4_);
  local_228 = (int ****)(ulonglong)(uint6)local_228;
  local_218 = uVar6;
  uStack_210 = uVar22;
  ArtDoc::GetEskoStringValue
            ((Dictionary *)local_1e8,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)this);
  if (0xf < uStack_210) {
    pvVar15 = local_228;
    if ((0xfff < uStack_210 + 1) &&
       (pvVar15 = *(void **)((longlong)local_228 + -8),
       0x1f < (ulonglong)((longlong)local_228 + (-8 - (longlong)pvVar15)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar15);
  }
  uVar21 = _UNK_1803096b8;
  uVar6 = _DAT_1803096b0;
  pppiStack_200 = (int ***)0x0;
  local_1f8 = (int ***)0x0;
  pppiStack_1f0 = (int ***)0xf;
  local_208 = (int ****)0x0;
  pppiStack_220 = (int ***)0x0;
  local_218 = _DAT_1803096b0;
  uStack_210 = _UNK_1803096b8;
  local_228 = (int ****)0x65707974;
  bVar2 = ArtDoc::Dictionary::HasStringValue
                    (this,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                          &local_228);
  if (0xf < uStack_210) {
    ppppiVar5 = local_228;
    if ((0xfff < uStack_210 + 1) &&
       (ppppiVar5 = (int ****)local_228[-1],
       0x1f < (ulonglong)((longlong)local_228 + (-8 - (longlong)ppppiVar5)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(ppppiVar5);
    uVar6 = _DAT_1803096b0;
    uVar21 = _UNK_1803096b8;
  }
  if (bVar2) {
    pppiStack_220 = (int ***)0x0;
    local_228 = (int ****)0x65707974;
    local_218 = uVar6;
    uStack_210 = uVar21;
    ppppiVar5 = (int ****)
                ArtDoc::GetEskoStringValue
                          ((Dictionary *)local_188,
                           (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            *)this);
    if (&local_208 != (int *****)ppppiVar5) {
      if ((int ***)0xf < pppiStack_1f0) {
        ppppiVar16 = local_208;
        if ((0xfff < (longlong)pppiStack_1f0 + 1U) &&
           (ppppiVar16 = (int ****)local_208[-1],
           0x1f < (ulonglong)((longlong)local_208 + (-8 - (longlong)ppppiVar16))))
        goto LAB_180113fe3;
        free(ppppiVar16);
      }
      local_208 = (int ****)*ppppiVar5;
      pppiStack_200 = ppppiVar5[1];
      local_1f8 = ppppiVar5[2];
      pppiStack_1f0 = ppppiVar5[3];
      ppppiVar5[2] = (int ***)0x0;
      ppppiVar5[3] = (int ***)0xf;
      *(undefined1 *)ppppiVar5 = 0;
    }
    if (0xf < uStack_170) {
      ppuVar12 = local_188[0];
      if ((0xfff < uStack_170 + 1) &&
         (ppuVar12 = (undefined **)local_188[0][-1],
         0x1f < (ulonglong)((longlong)local_188[0] + (-8 - (longlong)ppuVar12)))) {
LAB_180113fe3:
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(ppuVar12);
    }
    local_178 = PTR_180304c20;
    uStack_170 = _UNK_180304c28;
    local_188[0] = (undefined **)((ulonglong)local_188[0] & 0xffffffffffffff00);
    if (0xf < uStack_210) {
      ppppiVar5 = local_228;
      if ((0xfff < uStack_210 + 1) &&
         (ppppiVar5 = (int ****)local_228[-1],
         0x1f < (ulonglong)((longlong)local_228 + (-8 - (longlong)ppppiVar5)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(ppppiVar5);
    }
  }
  iVar3 = DocumentMarks::GetMarksDebugLevel();
  if (1 < iVar3) {
    uVar6 = FUN_18001b3e0(cout_exref,"MarkReader::PostProcessObject MarkId: ");
    ppppuVar17 = local_1e8;
    if (0xf < local_1d0) {
      ppppuVar17 = local_1e8[0];
    }
    uVar6 = FUN_18001b810(uVar6,ppppuVar17,local_1d8);
    pbVar7 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(uVar6,&DAT_18031ffa4);
    _Var8 = ArtDoc::ContentObject::GetID(param_2);
    pbVar9 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar7,_Var8);
    uVar6 = FUN_18001b3e0(pbVar9," type=");
    ppppiVar5 = (int ****)&local_208;
    if ((int ***)0xf < pppiStack_1f0) {
      ppppiVar5 = local_208;
    }
    uVar6 = FUN_18001b810(uVar6,ppppiVar5,local_1f8);
    pbVar7 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(uVar6,&DAT_180306c80);
    std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar7,FUN_18003dae0);
  }
  if (local_1f8 == (int ***)0x0) {
    pPVar10 = ArtDoc::ContentObject::GetProperties(param_2);
    FUN_18010e240(pPVar10,&PTR_s_MarkObjectID_18030db80,local_1e8);
    goto LAB_18011452b;
  }
  if (1 < iVar3) {
    uVar6 = FUN_18001b3e0(cout_exref,"MarkReader::PostProcessObject");
    ppppiVar5 = (int ****)&local_208;
    if ((int ***)0xf < pppiStack_1f0) {
      ppppiVar5 = local_208;
    }
    uVar6 = FUN_18001b810(uVar6,ppppiVar5,local_1f8);
    uVar6 = FUN_18001b3e0(uVar6," SetParams: ");
    ppppuVar17 = local_1e8;
    if (0xf < local_1d0) {
      ppppuVar17 = local_1e8[0];
    }
    pbVar9 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_18001b810(uVar6,ppppuVar17,local_1d8);
    pbVar7 = ArtDoc::operator<<(pbVar9,this);
    std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar7,FUN_18003dae0);
  }
  pppiVar19 = pppiStack_1f0;
  pppiVar18 = local_1f8;
  ppppiVar5 = local_208;
  puVar20 = PTR_s_AIDynamicMarks_BarcodeMark_180304e60;
  ppppiVar16 = (int ****)&local_208;
  if ((int ***)0xf < pppiStack_1f0) {
    ppppiVar16 = local_208;
  }
  if ((local_1f8 == (int ***)0x1a) &&
     (iVar3 = memcmp(PTR_s_AIDynamicMarks_BarcodeMark_180304e60,ppppiVar16,0x1a), iVar3 == 0)) {
    pPVar10 = ArtDoc::ContentObject::GetProperties(param_2);
    FUN_18010e400(pPVar10,&PTR_s_MarkObjectParams_18030db58,this);
    pppiVar18 = local_1f8;
    ppppiVar5 = local_208;
    pppiVar19 = pppiStack_1f0;
    puVar20 = PTR_s_AIDynamicMarks_BarcodeMark_180304e60;
  }
  ppppiVar16 = (int ****)&local_208;
  if ((int ***)0xf < pppiVar19) {
    ppppiVar16 = ppppiVar5;
  }
  if ((pppiVar18 == (int ***)0x1a) && (iVar3 = memcmp(puVar20,ppppiVar16,0x1a), iVar3 == 0)) {
LAB_18011427a:
    local_188[0] = std::
                   _Func_impl_no_alloc<`public:_virtual_void___cdecl_DocumentMarks::MarkReader::PostProcessObject(ArtDoc::ContentObject&___ptr64)___ptr64'::`20'::<lambda_1>,bool,DocumentBarCode::BarCode&___ptr64>
                   ::vftable;
    local_150 = local_188;
    FUN_18010ea90(local_a8,local_188);
    (**(code **)(*(longlong *)(param_2 + 0x20) + 0x10))(param_2 + 0x20,local_a8);
    local_188[0] = std::
                   _Func_impl_no_alloc<`public:_virtual_void___cdecl_DocumentMarks::MarkReader::PostProcessObject(ArtDoc::ContentObject&___ptr64)___ptr64'::`20'::<lambda_2>,bool,DocumentBarCode::BarCode&___ptr64>
                   ::vftable;
    local_150 = local_188;
    FUN_18010ea90(local_f8,local_188);
    (**(code **)(*(longlong *)(param_2 + 0x20) + 0x10))(param_2 + 0x20,local_f8);
    local_188[0] = std::
                   _Func_impl_no_alloc<`public:_virtual_void___cdecl_DocumentMarks::MarkReader::PostProcessObject(ArtDoc::ContentObject&___ptr64)___ptr64'::`20'::<lambda_3>,bool,DocumentBarCode::BarCode&___ptr64>
                   ::vftable;
    local_150 = local_188;
    FUN_18010ea90(local_148,local_188);
    (**(code **)(*(longlong *)(param_2 + 0x20) + 0x10))(param_2 + 0x20,local_148);
    if (local_100 != (longlong *)0x0) {
      (**(code **)(*local_100 + 0x20))
                (local_100,CONCAT71((int7)((ulonglong)local_138 >> 8),local_100 != local_138));
      local_100 = (longlong *)0x0;
    }
    ArtDoc::Visitor<DocumentBarCode::BarCode>::~Visitor<DocumentBarCode::BarCode>(local_140);
    ArtDoc::VisitorBase::~VisitorBase(local_148);
    if (local_b0 != (longlong *)0x0) {
      (**(code **)(*local_b0 + 0x20))
                (local_b0,CONCAT71((int7)((ulonglong)local_e8 >> 8),local_b0 != local_e8));
      local_b0 = (longlong *)0x0;
    }
    ArtDoc::Visitor<DocumentBarCode::BarCode>::~Visitor<DocumentBarCode::BarCode>(local_f0);
    ArtDoc::VisitorBase::~VisitorBase(local_f8);
    if (local_60 != (longlong *)0x0) {
      (**(code **)(*local_60 + 0x20))
                (local_60,CONCAT71((int7)((ulonglong)local_98 >> 8),local_60 != local_98));
      local_60 = (longlong *)0x0;
    }
    ArtDoc::Visitor<DocumentBarCode::BarCode>::~Visitor<DocumentBarCode::BarCode>(local_a0);
    ArtDoc::VisitorBase::~VisitorBase(local_a8);
  }
  else {
    ppppiVar16 = (int ****)&local_208;
    if ((int ***)0xf < pppiVar19) {
      ppppiVar16 = ppppiVar5;
    }
    if (pppiVar18 == (int ***)0x7) {
      iVar3 = *(int *)PTR_s_Barcode_18031f6b0 - *(int *)ppppiVar16;
      if ((iVar3 == 0) &&
         (iVar3 = (uint)*(ushort *)(PTR_s_Barcode_18031f6b0 + 4) -
                  (uint)*(ushort *)((longlong)ppppiVar16 + 4), iVar3 == 0)) {
        iVar3 = (uint)(byte)PTR_s_Barcode_18031f6b0[6] - (uint)*(byte *)((longlong)ppppiVar16 + 6);
      }
      if (iVar3 == 0) goto LAB_18011427a;
    }
  }
  pMVar11 = ArtDoc::FindModule(0x4d61726b);
  local_238 = 0;
  this_00 = (MarksModule *)
            __RTDynamicCast(pMVar11,0,&ArtDoc::Module::RTTI_Type_Descriptor,
                            &DocumentMarks::MarksModule::RTTI_Type_Descriptor);
  if (this_00 != (MarksModule *)0x0) {
    uVar4 = DocumentMarks::MarksModule::GetFeatures(this_00);
    if (((uVar4 & 1) != 0) ||
       (uVar4 = DocumentMarks::MarksModule::GetFeatures(this_00), bVar2 = true, (uVar4 & 2) != 0)) {
      ppuVar12 = (undefined **)
                 FUN_18010e5c0(&PTR_s_AIDynamicMarks_BearerBar_18031f360,
                               &PTR_s_UniPointText_18031f420,&local_208,0);
      bVar2 = true;
      if (ppuVar12 != &PTR_s_UniPointText_18031f420) {
        bVar2 = false;
      }
    }
    uVar4 = DocumentMarks::MarksModule::GetFeatures(this_00);
    if ((uVar4 & 0x40) != 0) {
      ppuVar12 = (undefined **)
                 FUN_18010e5c0(&PTR_s_UniPointText_18031f420,&PTR_s_AIPointText_18031f480,&local_208
                               ,0);
      bVar1 = false;
      if (ppuVar12 == &PTR_s_AIPointText_18031f480) {
        bVar1 = bVar2;
      }
      bVar2 = bVar1;
      pcVar13 = (char *)FUN_18010e5c0(&PTR_s_AIPointText_18031f480,
                                      "DataMatrixBarCodeUsesOptimalSize",&local_208,0);
      if (pcVar13 != "DataMatrixBarCodeUsesOptimalSize") {
        local_228 = (int ****)&local_208;
        if ((int ***)0xf < pppiStack_1f0) {
          local_228 = local_208;
        }
        pppiStack_220 = local_1f8;
        pCVar14 = ArtDoc::ContentObject::GetContent(param_2);
        FUN_180103860(pCVar14,3,&local_228);
      }
    }
    if (!bVar2) goto LAB_18011452b;
  }
  local_228 = (int ****)&local_208;
  if ((int ***)0xf < pppiStack_1f0) {
    local_228 = local_208;
  }
  pppiStack_220 = local_1f8;
  pCVar14 = ArtDoc::ContentObject::GetContent(param_2);
  FUN_180103860(pCVar14,3,&local_228);
LAB_18011452b:
  if ((int ***)0xf < pppiStack_1f0) {
    ppppiVar5 = local_208;
    if ((0xfff < (longlong)pppiStack_1f0 + 1U) &&
       (ppppiVar5 = (int ****)local_208[-1],
       0x1f < (ulonglong)((longlong)local_208 + (-8 - (longlong)ppppiVar5)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(ppppiVar5);
  }
  local_1f8 = (int ***)0x0;
  pppiStack_1f0 = (int ***)0xf;
  local_208 = (int ****)((ulonglong)local_208 & 0xffffffffffffff00);
  if (0xf < local_1d0) {
    ppppuVar17 = local_1e8[0];
    if ((0xfff < local_1d0 + 1) &&
       (ppppuVar17 = (undefined8 ****)local_1e8[0][-1],
       0x1f < (ulonglong)((longlong)local_1e8[0] + (-8 - (longlong)ppppuVar17)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(ppppuVar17);
  }
  return;
}


