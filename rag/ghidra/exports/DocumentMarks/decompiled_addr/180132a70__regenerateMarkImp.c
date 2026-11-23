// DocumentMarks.dll 180132a70 DocumentMarks::PDFPlusBearerBar::regenerateMarkImp
// signature: void regenerateMarkImp(PDFPlusBearerBar * this)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: virtual void __cdecl DocumentMarks::PDFPlusBearerBar::regenerateMarkImp(void) __ptr64
    */

void __thiscall DocumentMarks::PDFPlusBearerBar::regenerateMarkImp(PDFPlusBearerBar *this)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 auVar5 [12];
  char cVar6;
  Anchor AVar7;
  Anchor AVar8;
  Group *this_00;
  Content *pCVar9;
  Document *pDVar10;
  undefined8 *puVar11;
  ContentObject *pCVar12;
  Page *this_01;
  RectangleBase<YAGL::MilliPointCoordinateSystem> *pRVar13;
  double *pdVar14;
  double *pdVar15;
  longlong lVar16;
  longlong lVar17;
  double dVar18;
  Group *pGVar19;
  PDFPlusBearerBar *pPVar20;
  double dVar21;
  undefined4 uVar22;
  undefined4 uVar24;
  undefined8 extraout_XMM0_Qb;
  undefined8 extraout_XMM0_Qb_00;
  undefined8 uVar25;
  undefined1 auVar23 [16];
  double dVar26;
  undefined4 uVar27;
  uint uVar28;
  undefined4 uVar29;
  uint uVar30;
  undefined4 uVar31;
  undefined4 uVar32;
  undefined4 uVar33;
  undefined4 uVar34;
  undefined4 uVar35;
  undefined4 uVar36;
  undefined1 auStackY_538 [32];
  double local_500;
  longlong *local_4f8;
  double local_4f0;
  double local_4e8 [2];
  undefined8 local_4d8;
  undefined8 uStack_4d0;
  undefined8 local_4c8;
  undefined8 uStack_4c0;
  double dStack_4b8;
  double dStack_4b0;
  double local_4a8 [2];
  double local_498;
  double dStack_490;
  double local_488;
  double dStack_480;
  double local_478;
  double local_470;
  Group *local_468;
  undefined4 local_460;
  undefined4 uStack_45c;
  undefined4 uStack_458;
  undefined4 uStack_454;
  undefined4 local_450;
  undefined4 uStack_44c;
  undefined4 uStack_448;
  undefined4 uStack_444;
  undefined8 local_440;
  double local_430;
  double local_428;
  double local_420;
  double local_418;
  ActionGroupCreator local_400 [16];
  Visitable local_3f0 [16];
  double local_3e0;
  double local_3d8;
  char local_3c8;
  undefined **local_3b8 [7];
  undefined ***local_380;
  undefined **local_378 [7];
  undefined ***local_340;
  undefined **local_338 [7];
  undefined ***local_300;
  Expander local_2f8 [640];
  ulonglong local_78;
  
                    /* 0x132a70  2185  ?regenerateMarkImp@PDFPlusBearerBar@DocumentMarks@@MEAAXXZ */
  local_78 = DAT_180418e00 ^ (ulonglong)auStackY_538;
  UpdateDirection(this);
  ValidateAnchors(this);
  UpdateSizeReference(this);
  pCVar12 = *(ContentObject **)(this + 0x2c0);
  while (pCVar12 != (ContentObject *)0x0) {
    DocumentEdit::Delete(pCVar12);
    pCVar12 = *(ContentObject **)(this + 0x2c0);
  }
  this_00 = (Group *)FUN_1802d6b50(0x2d0);
  if (this_00 == (Group *)0x0) {
    this_00 = (Group *)0x0;
  }
  else {
    local_468 = this_00;
    ArtDoc::Group::Group(this_00,0x1ff);
    *(undefined ***)this_00 = ArtDoc::Group::vftable;
    *(undefined ***)(this_00 + 0x20) = ArtDoc::Group::vftable;
  }
  local_338[0] = std::
                 _Func_impl_no_alloc<`protected:_virtual_void___cdecl_DocumentMarks::PDFPlusBearerBar::regenerateMarkImp(void)___ptr64'::`2'::<lambda_3>,bool,ArtDoc::Group_const&___ptr64>
                 ::vftable;
  local_300 = local_338;
  local_378[0] = std::
                 _Func_impl_no_alloc<`protected:_virtual_void___cdecl_DocumentMarks::PDFPlusBearerBar::regenerateMarkImp(void)___ptr64'::`2'::<lambda_2>,bool,ArtDoc::Group_const&___ptr64>
                 ::vftable;
  local_340 = local_378;
  local_3b8[0] = std::
                 _Func_impl_no_alloc<`protected:_virtual_void___cdecl_DocumentMarks::PDFPlusBearerBar::regenerateMarkImp(void)___ptr64'::`2'::<lambda_1>,bool,ArtDoc::Layer_const&___ptr64>
                 ::vftable;
  local_380 = local_3b8;
  local_468 = this_00;
  pCVar9 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
  pDVar10 = ArtDoc::Content::GetDocument(pCVar9);
  DocumentEdit::Expander::Expander
            (local_2f8,this_00,pDVar10,
             (function<bool___cdecl(ArtDoc::Layer_const&___ptr64)> *)local_3b8,
             (function<bool___cdecl(ArtDoc::Group_const&___ptr64)> *)local_378,
             (function<bool___cdecl(ArtDoc::Group_const&___ptr64)> *)local_338);
  if (local_380 != (undefined ***)0x0) {
    (*(code *)(*local_380)[4])
              (local_380,CONCAT71((int7)((ulonglong)local_3b8 >> 8),local_380 != local_3b8));
    local_380 = (undefined ***)0x0;
  }
  if (local_340 != (undefined ***)0x0) {
    (*(code *)(*local_340)[4])
              (local_340,CONCAT71((int7)((ulonglong)local_378 >> 8),local_340 != local_378));
    local_340 = (undefined ***)0x0;
  }
  if (local_300 != (undefined ***)0x0) {
    (*(code *)(*local_300)[4])
              (local_300,CONCAT71((int7)((ulonglong)local_338 >> 8),local_300 != local_338));
    local_300 = (undefined ***)0x0;
  }
  puVar11 = (undefined8 *)DynamicMark::GetSourceContent((DynamicMark *)this);
  pCVar9 = ArtPaint::FormPaint::GetContent((FormPaint *)*puVar11);
  (**(code **)(*(longlong *)pCVar9 + 8))(pCVar9,local_2f8);
  if (local_4f8 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_4f8 + 1;
    lVar16 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar16 == 1) {
      (**(code **)*local_4f8)(local_4f8);
      LOCK();
      piVar2 = (int *)((longlong)local_4f8 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_4f8 + 8))(local_4f8);
      }
    }
  }
  pPVar20 = this + 0x6b0;
  pGVar19 = this_00;
  if ((pPVar20 != (PDFPlusBearerBar *)0x0) && (this[0x728] == (PDFPlusBearerBar)0x1)) {
    pCVar9 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
    pCVar12 = ArtDoc::Content::GetObjectWithID(pCVar9,*(undefined8 *)pPVar20);
    if (pCVar12 == (ContentObject *)0x0) goto LAB_18013333e;
  }
  pCVar9 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
  dVar21 = local_478;
  if (pPVar20 == (PDFPlusBearerBar *)0x0) {
LAB_180132d1e:
    pPVar20 = (PDFPlusBearerBar *)0x0;
LAB_180132d21:
    if (pPVar20 == (PDFPlusBearerBar *)0x0) {
      uVar33 = 0;
      uVar34 = 0;
      uVar35 = 0;
      uVar36 = 0;
      uVar27 = 0;
      uVar29 = 0;
      uVar31 = 0;
      uVar32 = 0;
      local_478 = (double)CONCAT71(local_478._1_7_,1);
      uVar22 = SUB84(local_478,0);
      uVar24 = (undefined4)((ulonglong)dVar21 >> 0x20);
      uVar25 = extraout_XMM0_Qb;
    }
    else {
      ArtDoc::Content::GetObjectWithID(pCVar9,*(undefined8 *)pPVar20);
      GetBoundingBoxForPositioning((ContentObject *)&local_4d8);
      dVar21 = local_478;
      if (dStack_4b0._0_1_ == '\0') {
        uVar33 = 0;
        uVar34 = 0;
        uVar35 = 0;
        uVar36 = 0;
        uVar27 = 0;
        uVar29 = 0;
        uVar31 = 0;
        uVar32 = 0;
        local_478 = (double)CONCAT71(local_478._1_7_,1);
        uVar25 = 0;
        uVar22 = SUB84(local_478,0);
        uVar24 = (undefined4)((ulonglong)dVar21 >> 0x20);
      }
      else {
        uVar25 = 0;
        uVar22 = SUB84(dStack_4b8,0);
        uVar24 = (undefined4)((ulonglong)dStack_4b8 >> 0x20);
        uVar27 = (undefined4)local_4c8;
        uVar29 = local_4c8._4_4_;
        uVar31 = (undefined4)uStack_4c0;
        uVar32 = uStack_4c0._4_4_;
        uVar33 = (undefined4)local_4d8;
        uVar34 = local_4d8._4_4_;
        uVar35 = (undefined4)uStack_4d0;
        uVar36 = uStack_4d0._4_4_;
      }
    }
  }
  else {
    if (this[0x728] != (PDFPlusBearerBar)0x0) {
      if ((pPVar20 == (PDFPlusBearerBar *)0x0) || (this[0x728] != (PDFPlusBearerBar)0x1))
      goto LAB_180132d1e;
      goto LAB_180132d21;
    }
    this_01 = ArtDoc::PageContent::GetPage((PageContent *)pCVar9);
    pRVar13 = ArtDoc::Page::GetPageBox(this_01,*(PageBox *)pPVar20);
    uVar22 = (undefined4)*(undefined8 *)(pRVar13 + 0x20);
    uVar24 = (undefined4)((ulonglong)*(undefined8 *)(pRVar13 + 0x20) >> 0x20);
    uVar27 = *(undefined4 *)(pRVar13 + 0x10);
    uVar29 = *(undefined4 *)(pRVar13 + 0x14);
    uVar31 = *(undefined4 *)(pRVar13 + 0x18);
    uVar32 = *(undefined4 *)(pRVar13 + 0x1c);
    uVar33 = *(undefined4 *)pRVar13;
    uVar34 = *(undefined4 *)(pRVar13 + 4);
    uVar35 = *(undefined4 *)(pRVar13 + 8);
    uVar36 = *(undefined4 *)(pRVar13 + 0xc);
    uVar25 = extraout_XMM0_Qb_00;
  }
  if ((double)CONCAT44(uVar29,uVar27) <= 0.0 && (double)CONCAT44(uVar29,uVar27) != 0.0)
  goto LAB_18013333e;
  if ((double)CONCAT44(uVar29,uVar27) < 0.0 || (double)CONCAT44(uVar29,uVar27) == 0.0) {
    if ((double)CONCAT44(uVar29,uVar27) == 0.0) {
      cVar6 = '\0';
    }
    else {
      cVar6 = -0x80;
    }
  }
  else {
    cVar6 = -1;
  }
  if ((-1 < cVar6) ||
     (auVar5._4_8_ = uVar25, auVar5._0_4_ = uVar29, auVar23._0_8_ = auVar5._0_8_ << 0x20,
     auVar23._8_4_ = uVar31, auVar23._12_4_ = uVar32, dVar21 = auVar23._8_8_, dVar21 < 0.0))
  goto LAB_18013333e;
  if (dVar21 <= 0.0) {
    if (dVar21 == 0.0) {
      cVar6 = '\0';
    }
    else {
      cVar6 = -0x80;
    }
  }
  else {
    cVar6 = -1;
  }
  if (-1 < cVar6) goto LAB_18013333e;
  GetPDFPlusBoundingBox(local_3f0);
  if (*(int *)(this + 0x6a8) == 0) {
    if (((local_3c8 == '\0') || (local_3e0 < 0.0)) || (dVar21 = local_3e0, local_3e0 <= 0.0)) {
      dVar21 = 0.0;
    }
    uVar4 = *(undefined4 *)(this + 0x730);
    local_500 = dVar21;
    pCVar9 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
    FUN_180130e10(&local_498,pCVar9,uVar4);
    dVar26 = 28.346456692913385;
    local_4e8[0] = 28.346456692913385;
    if (local_488 + *(double *)(this + 0x6a0) != 0.0) {
      local_4e8[0] = local_488 + *(double *)(this + 0x6a0);
    }
    if (local_500 != 0.0) {
      dVar26 = dVar21;
    }
    local_4d8 = local_4e8[0] / dVar26;
    uStack_4d0 = 0.0;
    local_4c8 = 0.0;
    uStack_4c0 = _DAT_1803066f0;
    dStack_4b8 = _UNK_1803066f8;
    dStack_4b0 = 0.0;
    local_500 = dVar26;
    ArtDoc::Transformable::SetTransformation
              ((Transformable *)this_00,
               (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_4d8,7);
    GetPDFPlusBoundingBox((Visitable *)&local_430);
    local_440 = CONCAT44(uVar24,uVar22);
    local_460 = uVar33;
    uStack_45c = uVar34;
    uStack_458 = uVar35;
    uStack_454 = uVar36;
    local_450 = uVar27;
    uStack_44c = uVar29;
    uStack_448 = uVar31;
    uStack_444 = uVar32;
    AVar7 = YAGL::ToVertical(*(Anchor *)(this + 0x37c));
    AVar8 = YAGL::ToVertical(*(Anchor *)(this + 0x378));
    lVar16 = FUN_180084f50(&local_430,local_4e8,AVar8);
    uVar28 = (uint)*(undefined8 *)(this + 0x698);
    uVar30 = (uint)((ulonglong)*(undefined8 *)(this + 0x698) >> 0x20);
    if (AVar7 != 1) {
      uVar28 = uVar28 ^ (uint)DAT_180308300;
      uVar30 = uVar30 ^ DAT_180308300._4_4_;
    }
    lVar17 = FUN_180084f50(&local_460,local_4a8,AVar7);
    local_470 = (*(double *)(lVar17 + 8) + (double)CONCAT44(uVar30,uVar28)) -
                *(double *)(lVar16 + 8);
    local_4a8[0] = local_420;
    local_4f0 = local_430;
    local_4e8[0] = local_498;
    local_500 = (local_488 * DAT_180308e18 + local_498) - (local_420 * DAT_180308e18 + local_430);
    local_498 = _DAT_1803066f0;
    dStack_490 = _UNK_1803066f8;
    local_488 = _DAT_180306700;
    dStack_480 = _UNK_180306708;
    local_478 = local_500;
    pdVar14 = (double *)FUN_180040520(&local_460,&local_498,&local_4d8);
    local_4d8 = *pdVar14;
    uStack_4d0 = pdVar14[1];
    local_4c8 = pdVar14[2];
    uStack_4c0 = pdVar14[3];
    dStack_4b8 = pdVar14[4];
    dStack_4b0 = pdVar14[5];
LAB_1801332d7:
    ArtDoc::Transformable::SetTransformation
              ((Transformable *)this_00,
               (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_4d8,7);
  }
  else if (*(int *)(this + 0x6a8) == 1) {
    if (((local_3c8 == '\0') || (local_3d8 < 0.0)) || (dVar21 = local_3d8, local_3d8 <= 0.0)) {
      dVar21 = 0.0;
    }
    uVar4 = *(undefined4 *)(this + 0x730);
    local_4f0 = dVar21;
    pCVar9 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
    FUN_180130e10(&local_498,pCVar9,uVar4);
    dVar26 = dStack_480;
    dVar18 = 28.346456692913385;
    uStack_4c0 = 28.346456692913385;
    if (dStack_480 + *(double *)(this + 0x6a0) != 0.0) {
      uStack_4c0 = dStack_480 + *(double *)(this + 0x6a0);
    }
    if (local_4f0 != 0.0) {
      dVar18 = dVar21;
    }
    uStack_4c0 = uStack_4c0 / dVar18;
    local_4d8 = _DAT_1803066f0;
    uStack_4d0 = _UNK_1803066f8;
    local_4c8 = 0.0;
    dStack_4b8 = 0.0;
    dStack_4b0 = 0.0;
    local_4f0 = dVar18;
    ArtDoc::Transformable::SetTransformation
              ((Transformable *)this_00,
               (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_4d8,7);
    GetPDFPlusBoundingBox((Visitable *)&local_430);
    local_440 = CONCAT44(uVar24,uVar22);
    local_460 = uVar33;
    uStack_45c = uVar34;
    uStack_458 = uVar35;
    uStack_454 = uVar36;
    local_450 = uVar27;
    uStack_44c = uVar29;
    uStack_448 = uVar31;
    uStack_444 = uVar32;
    AVar7 = YAGL::ToHorizontal(*(Anchor *)(this + 0x37c));
    AVar8 = YAGL::ToHorizontal(*(Anchor *)(this + 0x378));
    pdVar14 = (double *)FUN_180084f50(&local_430,&local_500,AVar8);
    uVar28 = (uint)*(undefined8 *)(this + 0x698);
    uVar30 = (uint)((ulonglong)*(undefined8 *)(this + 0x698) >> 0x20);
    if (AVar7 != 5) {
      uVar28 = uVar28 ^ (uint)DAT_180308300;
      uVar30 = uVar30 ^ DAT_180308300._4_4_;
    }
    pdVar15 = (double *)FUN_180084f50(&local_460,local_4e8,AVar7);
    local_478 = ((double)CONCAT44(uVar30,uVar28) + *pdVar15) - *pdVar14;
    local_4f0 = dVar26;
    local_470 = (dVar26 * DAT_180308e18 + dStack_490) - (local_418 * DAT_180308e18 + local_428);
    dVar21 = local_4d8 * 0.0;
    dVar26 = local_4c8 * 0.0;
    local_4a8[0] = dStack_4b0 * 0.0 + dStack_4b8 + local_478;
    local_4e8[0] = dStack_4b0;
    local_500 = dStack_4b8 * 0.0 + dStack_4b0 + local_470;
    local_4d8 = local_4d8 + uStack_4d0 * 0.0;
    uStack_4d0 = uStack_4d0 + dVar21;
    local_4c8 = local_4c8 + uStack_4c0 * 0.0;
    uStack_4c0 = uStack_4c0 + dVar26;
    dStack_4b8 = local_4a8[0];
    dStack_4b0 = local_500;
    goto LAB_1801332d7;
  }
  pCVar9 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
  pDVar10 = ArtDoc::Content::GetDocument(pCVar9);
  ArtDoc::ActionGroupCreator::ActionGroupCreator(local_400,pDVar10,false,false);
  pGVar19 = (Group *)0x0;
  local_468 = (Group *)0x0;
  pCVar12 = DocumentEdit::InsertNewObjectOnTop((ContentObject *)this_00,(Group *)this,true);
  DynamicMark::ApplyPDFPlusColor((DynamicMark *)this,pCVar12);
  ArtDoc::ActionGroupCreator::~ActionGroupCreator(local_400);
LAB_18013333e:
  DocumentEdit::Expander::~Expander(local_2f8);
  if (pGVar19 != (Group *)0x0) {
    (*(code *)**(undefined8 **)pGVar19)(pGVar19,1);
  }
  return;
}


