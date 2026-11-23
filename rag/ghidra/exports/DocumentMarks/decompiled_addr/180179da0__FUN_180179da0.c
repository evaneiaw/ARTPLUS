// DocumentMarks.dll 180179da0 FUN_180179da0
// signature: undefined FUN_180179da0(void)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_180179da0(GADict *param_1,ContentObject *param_2,undefined8 param_3,double param_4)

{
  void *pvVar1;
  bool bVar2;
  Anchor AVar3;
  Anchor AVar4;
  undefined8 uVar5;
  GAObject *this;
  Properties *pPVar6;
  variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer> *pvVar7;
  GAArray *pGVar8;
  GANumber *pGVar9;
  void *pvVar10;
  double dVar11;
  double dVar12;
  undefined1 auStack_148 [32];
  GName local_128 [8];
  GADict local_120 [8];
  GName local_118 [8];
  char *local_110;
  GName local_108 [8];
  GName local_100 [8];
  GName local_f8 [8];
  GName local_f0 [8];
  undefined1 local_e8 [40];
  undefined1 local_c0 [40];
  undefined1 local_98 [40];
  char local_70;
  GAName local_68;
  undefined7 uStack_67;
  undefined8 local_58;
  ulonglong local_50;
  ulonglong local_48;
  
  local_48 = DAT_180418e00 ^ (ulonglong)auStack_148;
  GName::GName(local_f0,"Position");
  GADict::GetDict(param_1,local_118);
  uVar5 = GADict::GADict(local_120,(GADict *)local_118);
  FUN_1801861f0(uVar5,param_3);
  GName::GName((GName *)local_120,"SourceAnchor");
  uVar5 = GADict::GetName((GADict *)local_118,local_128);
  AVar3 = FUN_180184b50(uVar5);
  GAName::~GAName((GAName *)local_128);
  GName::GName((GName *)local_120,"ReferenceAnchor");
  uVar5 = GADict::GetName((GADict *)local_118,local_128);
  AVar4 = FUN_180184b50(uVar5);
  GAName::~GAName((GAName *)local_128);
  DocumentMarks::MarkPosition::setAnchors((MarkPosition *)(param_2 + 0x2f0),AVar3,AVar4);
  GName::GName((GName *)local_120,"Reference");
  this = (GAObject *)GADict::Get((GADict *)local_118,local_128);
  bVar2 = GAObject::IsName(this);
  GAObject::~GAObject((GAObject *)local_128);
  if (bVar2) {
    GName::GName(local_100,"Reference");
    GADict::GetName((GADict *)local_118,local_128);
    bVar2 = GAName::operator==((GAName *)local_128,"ObjectID");
    if (bVar2) {
      GName::GName(local_f8,"ReferenceID");
      GADict::GetName((GADict *)local_118,(GName *)local_120);
      ArtDocGlue::PDFConverters::UTF8String(&local_68);
      pPVar6 = ArtDoc::ContentObject::GetProperties(param_2);
      FUN_18004e5d0(pPVar6,&PTR_s_DocumentMarks_BearerBar_Referenc_1803263e8,&local_68);
      if (0xf < local_50) {
        pvVar1 = (void *)CONCAT71(uStack_67,local_68);
        pvVar10 = pvVar1;
        if ((0xfff < local_50 + 1) &&
           (pvVar10 = *(void **)((longlong)pvVar1 + -8),
           0x1f < (ulonglong)((longlong)pvVar1 + (-8 - (longlong)pvVar10)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar10);
      }
      local_58 = 0;
      local_50 = 0xf;
      local_68 = (GAName)0x0;
      GAName::~GAName((GAName *)local_120);
    }
    else {
      pvVar7 = (variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer> *)
               FUN_1801852b0(local_e8,local_128);
      DocumentMarks::PDFPlusBearerBar::SetReferenceObject((PDFPlusBearerBar *)param_2,pvVar7);
      if (((local_70 != -1) && (local_70 != '\0')) && (local_70 != '\x01')) {
        FUN_180013c20(local_98);
        FUN_180013c20(local_c0);
        FUN_180013c20(local_e8);
      }
    }
  }
  else {
    GName::GName(local_f8,"Reference");
    pGVar8 = (GAArray *)GADict::GetArray((GADict *)local_118,local_100);
    GAArray::GetName(pGVar8,(long)local_128);
    GAArray::~GAArray((GAArray *)local_100);
    bVar2 = GAName::operator==((GAName *)local_128,"ObjectID");
    if (bVar2) {
      GName::GName((GName *)&local_110,"ReferenceID");
      pGVar8 = (GAArray *)GADict::GetArray((GADict *)local_118,local_108);
      GAArray::GetName(pGVar8,(long)local_120);
      GAArray::~GAArray((GAArray *)local_108);
      ArtDocGlue::PDFConverters::UTF8String(&local_68);
      pPVar6 = ArtDoc::ContentObject::GetProperties(param_2);
      FUN_18004e5d0(pPVar6,&PTR_s_DocumentMarks_BearerBar_Referenc_1803263e8,&local_68);
      if (0xf < local_50) {
        pvVar1 = (void *)CONCAT71(uStack_67,local_68);
        pvVar10 = pvVar1;
        if ((0xfff < local_50 + 1) &&
           (pvVar10 = *(void **)((longlong)pvVar1 + -8),
           0x1f < (ulonglong)((longlong)pvVar1 + (-8 - (longlong)pvVar10)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar10);
      }
      local_58 = 0;
      local_50 = 0xf;
      local_68 = (GAName)0x0;
      GAName::~GAName((GAName *)local_120);
    }
    else {
      pvVar7 = (variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer> *)
               FUN_1801852b0(local_e8,local_128);
      DocumentMarks::PDFPlusBearerBar::SetReferenceObject((PDFPlusBearerBar *)param_2,pvVar7);
      if (((local_70 != -1) && (local_70 != '\0')) && (local_70 != '\x01')) {
        FUN_180013c20(local_98);
        FUN_180013c20(local_c0);
        FUN_180013c20(local_e8);
      }
    }
  }
  GAName::~GAName((GAName *)local_128);
  GName::GName(local_108,"Offset");
  bVar2 = GADict::Has((GADict *)local_118,local_108);
  if (bVar2) {
    GName::GName(local_108,"Offset");
    GADict::GetArray((GADict *)local_118,local_128);
    pGVar9 = (GANumber *)GAArray::GetNumber((GAArray *)local_128,(long)&local_110);
    dVar11 = GANumber::Get(pGVar9);
    GANumber::~GANumber((GANumber *)&local_110);
    pGVar9 = (GANumber *)GAArray::GetNumber((GAArray *)local_128,(long)&local_110);
    dVar12 = GANumber::Get(pGVar9);
    GANumber::~GANumber((GANumber *)&local_110);
    if (dVar12 != 0.0) {
      local_110 = "Vertical offset in bearer bar not supported.";
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(&local_110,(ThrowInfo *)&DAT_1803b78c8);
    }
    AVar4 = YAGL::ToHorizontal(AVar3);
    if ((AVar4 == 5) || (AVar3 = YAGL::ToVertical(AVar3), AVar3 == 7)) {
      dVar12 = DAT_1803082d0;
    }
    else {
      dVar12 = DAT_1803066c0;
    }
    local_110 = (char *)(dVar12 * dVar11 * param_4 * DAT_1803066e0);
    DocumentMarks::PDFPlusBearerBar::SetOffset
              ((PDFPlusBearerBar *)param_2,
               (CoordinateBase<YAGL::MilliPointCoordinateSystem,1> *)&local_110);
    GAArray::~GAArray((GAArray *)local_128);
  }
  GADict::~GADict((GADict *)local_118);
  return;
}


