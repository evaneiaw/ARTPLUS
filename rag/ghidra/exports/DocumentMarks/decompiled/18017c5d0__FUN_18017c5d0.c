// 18017c5d0 FUN_18017c5d0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_18017c5d0(GADict *param_1,PDFPlusCutMark *param_2,undefined8 param_3,double param_4)

{
  double dVar1;
  bool bVar2;
  long lVar3;
  Reference RVar4;
  undefined8 uVar5;
  GAName *pGVar6;
  Properties *pPVar7;
  GAObject *this;
  GANumber *this_00;
  void *pvVar8;
  Orientation OVar9;
  Repetition RVar10;
  int iVar11;
  undefined1 auStack_1a8 [32];
  char *local_188;
  GName local_180 [8];
  undefined4 local_178 [2];
  GName local_170 [8];
  GName local_168 [8];
  char *local_160;
  GName local_158 [8];
  GName local_150 [8];
  void *local_148 [3];
  ulonglong local_130;
  char local_128;
  int local_120;
  undefined4 uStack_11c;
  char local_118;
  int local_110;
  char local_108;
  PageBox local_100 [10];
  undefined1 local_d8 [40];
  undefined1 local_b0 [40];
  char local_88;
  char local_80;
  void *local_78;
  undefined4 *puStack_70;
  undefined4 *local_68;
  ulonglong local_60;
  ulonglong local_58;
  
  local_58 = DAT_180418e00 ^ (ulonglong)auStack_1a8;
  GName::GName(local_170,"Position");
  GADict::GetDict(param_1,local_180);
  uVar5 = GADict::GADict((GADict *)local_178,(GADict *)local_180);
  FUN_1801861f0(uVar5,param_3);
  GName::GName((GName *)&local_160,"Reference");
  GADict::GetName((GADict *)local_180,local_150);
  bVar2 = GAName::operator==((GAName *)local_150,"AllStructuralDesignStations");
  if (bVar2) {
    GName::GName((GName *)local_178,"Orientation");
    bVar2 = GADict::Has((GADict *)local_180,(GName *)local_178);
    if (!bVar2) {
LAB_18017cdef:
      local_188 = "AllStructuralDesignStations";
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(&local_188,(ThrowInfo *)&DAT_1803b78c8);
    }
    GName::GName((GName *)local_178,"Repetition");
    bVar2 = GADict::Has((GADict *)local_180,(GName *)local_178);
    if (!bVar2) goto LAB_18017cdef;
    GName::GName((GName *)local_178,"LineTypes");
    bVar2 = GADict::Has((GADict *)local_180,(GName *)local_178);
    if (!bVar2) goto LAB_18017cdef;
    local_80 = '\x01';
    DocumentMarks::PDFPlusCutMark::SetReferenceObject
              (param_2,(variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>
                        *)local_100);
    if ((((local_80 != -1) && (local_80 == '\0')) && (local_88 != -1)) &&
       ((local_88 != '\0' && (local_88 != '\x01')))) {
      FUN_180013c20(local_b0);
      FUN_180013c20(local_d8);
      FUN_180013c20(local_100);
    }
    GName::GName((GName *)local_178,"Orientation");
    pGVar6 = (GAName *)GADict::GetName((GADict *)local_180,local_158);
    bVar2 = GAName::operator==(pGVar6,"Horizontal");
    if (bVar2) {
      OVar9 = 0;
    }
    else {
      bVar2 = GAName::operator==(pGVar6,"Vertical");
      if (!bVar2) {
        local_188 = "Cut Mark has invalid Orientation value";
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(&local_188,(ThrowInfo *)&DAT_1803b78c8);
      }
      OVar9 = 1;
    }
    DocumentMarks::PDFPlusCutMark::SetOrientation(param_2,OVar9);
    GAName::~GAName((GAName *)local_158);
    GName::GName(local_158,"Repetition");
    uVar5 = GADict::Get((GADict *)local_180,(GName *)local_178);
    FUN_180185090(&local_120,uVar5);
    if (local_108 == '\0') {
      if (local_118 == '\0') {
        if (CONCAT44(uStack_11c,local_120) != 0) {
          local_160 = "Cut Mark has invalid Repetition value";
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(&local_160,(ThrowInfo *)&DAT_1803b78c8);
        }
        RVar10 = 0;
      }
      else {
        if (local_118 != '\x01') goto LAB_18017cea5;
        if (local_120 != 0) {
          local_160 = "Cut Mark has invalid Repetition value";
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(&local_160,(ThrowInfo *)&DAT_1803b78c8);
        }
        RVar10 = 1;
      }
    }
    else {
      if (local_108 != '\x01') {
LAB_18017cea5:
                    /* WARNING: Subroutine does not return */
        FUN_180025a80();
      }
      if (((local_118 != '\0') || (CONCAT44(uStack_11c,local_120) != 0)) || (local_110 != 1)) {
        local_188 = "Cut Mark has invalid Repetition value";
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(&local_188,(ThrowInfo *)&DAT_1803b78c8);
      }
      RVar10 = 2;
    }
    DocumentMarks::PDFPlusCutMark::SetRepetition(param_2,RVar10);
    GAObject::~GAObject((GAObject *)local_178);
    local_78 = (void *)0x0;
    puStack_70 = (undefined4 *)0x0;
    local_68 = (undefined4 *)0x0;
    GName::GName(local_158,"LineTypes");
    GADict::GetArray((GADict *)local_180,local_170);
    lVar3 = GAArray::GetLength((GAArray *)local_170);
    if ((lVar3 == 0) || (lVar3 = GAArray::GetLength((GAArray *)local_170), 2 < lVar3)) {
      local_188 = "LineTypes";
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(&local_188,(ThrowInfo *)&DAT_1803b78c8);
    }
    iVar11 = 0;
    lVar3 = GAArray::GetLength((GAArray *)local_170);
    if (0 < lVar3) {
      do {
        pGVar6 = (GAName *)GAArray::GetName((GAArray *)local_170,(long)local_168);
        bVar2 = GAName::operator==(pGVar6,"Cutting");
        GAName::~GAName((GAName *)local_168);
        if (bVar2) {
          local_178[0] = 0;
          if (puStack_70 == local_68) {
LAB_18017c9a8:
            FUN_18012f730(&local_78,puStack_70,local_178);
          }
          else {
            *puStack_70 = 0;
            puStack_70 = puStack_70 + 1;
          }
        }
        else {
          pGVar6 = (GAName *)GAArray::GetName((GAArray *)local_170,(long)&local_188);
          bVar2 = GAName::operator==(pGVar6,"Creasing");
          GAName::~GAName((GAName *)&local_188);
          if (!bVar2) {
            local_188 = "LineTypes";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_188,(ThrowInfo *)&DAT_1803b78c8);
          }
          local_178[0] = 1;
          if (puStack_70 == local_68) goto LAB_18017c9a8;
          *puStack_70 = 1;
          puStack_70 = puStack_70 + 1;
        }
        iVar11 = iVar11 + 1;
        lVar3 = GAArray::GetLength((GAArray *)local_170);
      } while (iVar11 < lVar3);
    }
    DocumentMarks::PDFPlusCutMark::SetLineTypes
              (param_2,(vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>
                        *)&local_78);
    GAArray::~GAArray((GAArray *)local_170);
    if (local_78 != (void *)0x0) {
      pvVar8 = local_78;
      if ((0xfff < (ulonglong)(((longlong)local_68 - (longlong)local_78 >> 2) * 4)) &&
         (pvVar8 = *(void **)((longlong)local_78 + -8),
         0x1f < (ulonglong)((longlong)local_78 + (-8 - (longlong)pvVar8)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar8);
    }
  }
  else {
    GName::GName((GName *)&local_188,"Orientation");
    bVar2 = GADict::Has((GADict *)local_180,(GName *)&local_188);
    if (bVar2) {
LAB_18017ce06:
      local_188 = "AllStructuralDesignStations";
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(&local_188,(ThrowInfo *)&DAT_1803b78c8);
    }
    GName::GName((GName *)&local_188,"Repetition");
    bVar2 = GADict::Has((GADict *)local_180,(GName *)&local_188);
    if (bVar2) goto LAB_18017ce06;
    GName::GName((GName *)&local_188,"LineTypes");
    bVar2 = GADict::Has((GADict *)local_180,(GName *)&local_188);
    if (bVar2) goto LAB_18017ce06;
    RVar4 = FUN_1801851b0(local_150);
    if (RVar4 == 5) {
      GName::GName((GName *)&local_188,"ReferenceID");
      GADict::GetName((GADict *)local_180,local_168);
      ArtDocGlue::PDFConverters::UTF8String((GAName *)&local_78);
      GAName::~GAName((GAName *)local_168);
      pPVar7 = ArtDoc::ContentObject::GetProperties((ContentObject *)param_2);
      FUN_18004e5d0(pPVar7,&PTR_s_DocumentMarks_CutMark_ReferenceI_1803263d8,&local_78);
      FUN_1800118b0(&local_78);
    }
    else {
      local_100[0] = DocumentMarks::MarkPosition::ref2box(RVar4);
      local_88 = '\0';
      local_80 = '\0';
      DocumentMarks::PDFPlusCutMark::SetReferenceObject
                (param_2,(variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>
                          *)local_100);
      FUN_1800ac600(local_100);
    }
  }
  GName::GName((GName *)&local_188,"Offset");
  bVar2 = GADict::Has((GADict *)local_180,(GName *)&local_188);
  if (bVar2) {
    GName::GName((GName *)&local_188,"Offset");
    this = (GAObject *)GADict::Get((GADict *)local_180,local_168);
    bVar2 = GAObject::IsString(this);
    GAObject::~GAObject((GAObject *)local_168);
    GName::GName((GName *)&local_188,"Offset");
    if (bVar2) {
      bVar2 = (bool)GADict::GetString((GADict *)local_180,local_168);
      ArtDocGlue::PDFConverters::UTF8String((GAString *)&local_78,bVar2);
      GAString::~GAString((GAString *)local_168);
      FUN_180011ca0(local_148,&local_78);
      local_128 = '\x01';
      DocumentMarks::PDFPlusCutMark::SetOffset
                (param_2,(variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
                          *)local_148);
      if (((local_128 != -1) && (local_128 != '\0')) && (0xf < local_130)) {
        pvVar8 = local_148[0];
        if ((0xfff < local_130 + 1) &&
           (pvVar8 = *(void **)((longlong)local_148[0] + -8),
           0x1f < (ulonglong)((longlong)local_148[0] + (-8 - (longlong)pvVar8)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar8);
      }
      if (0xf < local_60) {
        FUN_1800187d0(&local_78,local_78);
      }
      goto LAB_18017cdab;
    }
    this_00 = (GANumber *)GADict::GetNumber((GADict *)local_180,local_168);
    dVar1 = GANumber::Get(this_00);
    GANumber::~GANumber((GANumber *)local_168);
    local_148[0] = (void *)(dVar1 * param_4 * 1000.0);
    local_128 = '\0';
    DocumentMarks::PDFPlusCutMark::SetOffset
              (param_2,(variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
                        *)local_148);
    if (((local_128 == -1) || (local_128 == '\0')) || (local_130 < 0x10)) goto LAB_18017cdab;
    pvVar8 = local_148[0];
    if ((0xfff < local_130 + 1) &&
       (pvVar8 = *(void **)((longlong)local_148[0] + -8),
       0x1f < (ulonglong)
              ((longlong)local_148[0] + (-8 - (longlong)*(void **)((longlong)local_148[0] + -8)))))
    {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
  }
  else {
    local_148[0] = (void *)(param_4 * 0.0 * 1000.0);
    local_128 = '\0';
    DocumentMarks::PDFPlusCutMark::SetOffset
              (param_2,(variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
                        *)local_148);
    if (((local_128 == -1) || (local_128 == '\0')) || (local_130 < 0x10)) goto LAB_18017cdab;
    pvVar8 = local_148[0];
    if ((0xfff < local_130 + 1) &&
       (pvVar8 = *(void **)((longlong)local_148[0] + -8),
       0x1f < (ulonglong)((longlong)local_148[0] + (-8 - (longlong)pvVar8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
  }
  free(pvVar8);
LAB_18017cdab:
  GAName::~GAName((GAName *)local_150);
  GADict::~GADict((GADict *)local_180);
  return;
}


