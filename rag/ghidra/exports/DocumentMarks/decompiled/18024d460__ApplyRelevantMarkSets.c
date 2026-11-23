// 18024d460 ApplyRelevantMarkSets

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: void __cdecl DocumentMarks::TaskMarkSets::ApplyRelevantMarkSets(class ArtDoc::Page &
   __ptr64,int,bool,bool,bool,bool) __ptr64 */

void __thiscall
DocumentMarks::TaskMarkSets::ApplyRelevantMarkSets
          (TaskMarkSets *this,Page *param_1,int param_2,bool param_3,bool param_4,bool param_5,
          bool param_6)

{
  TaskMarkSets *pTVar1;
  Content *this_00;
  bool bVar2;
  char cVar3;
  InkType IVar4;
  Document *pDVar5;
  DynamicMarksController *pDVar6;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar7;
  undefined8 *puVar8;
  PageContent *pPVar9;
  vector<ArtDoc::Separation::Entry,std::allocator<ArtDoc::Separation::Entry>_> *pvVar10;
  Entry **ppEVar11;
  undefined8 uVar12;
  Separations *pSVar13;
  __uint64 _Var14;
  Document *pDVar15;
  DynamicObjectController *this_01;
  bool bVar16;
  void *_Memory;
  longlong lVar17;
  undefined8 *puVar18;
  undefined8 *puVar19;
  longlong *plVar20;
  Entry *pEVar21;
  Entry *pEVar22;
  longlong *plVar23;
  undefined1 auStack_288 [32];
  char local_268;
  char local_267;
  char local_266;
  char local_265;
  char local_264;
  TaskMarkSets *local_260;
  Entry *local_258;
  Entry *local_250;
  Entry *local_248;
  void *local_240;
  longlong *plStack_238;
  longlong *local_230;
  vector<class_ArtDoc::Separation::Entry,class_std::allocator<class_ArtDoc::Separation::Entry>_>
  local_228 [24];
  Content *local_210;
  TaskMarkSets *local_208;
  undefined1 local_200 [24];
  InkCollector local_1e8 [8];
  undefined **local_1e0;
  undefined **local_1d8;
  undefined1 local_1b8 [24];
  undefined1 local_1a0 [200];
  Page local_d8 [16];
  longlong local_c8;
  longlong local_c0;
  undefined1 local_b0 [16];
  longlong local_a0;
  longlong local_98;
  undefined **local_88;
  Document *local_80;
  __uint64 local_78;
  undefined ***local_50;
  ulonglong local_48;
  
                    /* 0x24d460  851
                       ?ApplyRelevantMarkSets@TaskMarkSets@DocumentMarks@@QEAAXAEAVPage@ArtDoc@@H_N111@Z
                        */
  local_48 = DAT_180418e00 ^ (ulonglong)auStack_288;
  local_268 = '\0';
  local_267 = '\0';
  local_266 = '\0';
  local_265 = '\0';
  local_264 = param_3;
  local_210 = (Content *)ArtDoc::Page::GetContent(param_1);
  pDVar5 = ArtDoc::Content::GetDocument(local_210);
  pDVar6 = GetDynamicMarksController(pDVar5);
  DynamicMarksController::EnableUpdates(pDVar6,false);
  local_208 = this + 0x10;
  pEVar22 = *(Entry **)(this + 0x18);
  for (pEVar21 = *(Entry **)local_208; pEVar21 != pEVar22; pEVar21 = pEVar21 + 0xf0) {
    IVar4 = ArtDoc::Separation::Entry::GetInkType(pEVar21);
    if ((IVar4 == 2) || (IVar4 = ArtDoc::Separation::Entry::GetInkType(pEVar21), IVar4 == 3)) {
      IVar4 = ArtDoc::Separation::Entry::GetInkType(pEVar21);
      pbVar7 = ArtDoc::Separation::Entry::GetName(pEVar21);
      AddNormalizedInkHint(pbVar7,IVar4);
    }
  }
  puVar18 = *(undefined8 **)(this + 0x28);
  puVar19 = *(undefined8 **)(this + 0x30);
  if (puVar18 == puVar19) {
    bVar2 = false;
  }
  else {
    do {
      puVar8 = (undefined8 *)ArtDoc::Document::GetPagesBegin((Document *)*puVar18);
      CopyMarksToPageWithLog(this,*(Page **)*puVar8,param_1,!param_6);
      puVar18 = puVar18 + 1;
    } while (puVar18 != puVar19);
    bVar2 = true;
  }
  bVar16 = true;
  if (!bVar2) {
    bVar16 = param_4;
  }
  if ((param_2 & 1U) == 0) {
    puVar18 = *(undefined8 **)(this + 0x40);
    puVar19 = *(undefined8 **)(this + 0x48);
    if (puVar18 != puVar19) {
      do {
        puVar8 = (undefined8 *)ArtDoc::Document::GetPagesBegin((Document *)*puVar18);
        CopyMarksToPageWithLog(this,*(Page **)*puVar8,param_1,!param_6);
        puVar18 = puVar18 + 1;
      } while (puVar18 != puVar19);
      local_267 = '\x01';
      goto LAB_18024d631;
    }
  }
  else {
    puVar18 = *(undefined8 **)(this + 0x58);
    puVar19 = *(undefined8 **)(this + 0x60);
    if (puVar18 == puVar19) {
      local_268 = '\0';
    }
    else {
      do {
        puVar8 = (undefined8 *)ArtDoc::Document::GetPagesBegin((Document *)*puVar18);
        CopyMarksToPageWithLog(this,*(Page **)*puVar8,param_1,!param_6);
        puVar18 = puVar18 + 1;
      } while (puVar18 != puVar19);
      local_268 = '\x01';
LAB_18024d631:
      bVar16 = true;
    }
  }
  if (param_2 == 1) {
    puVar18 = *(undefined8 **)(this + 0x70);
    puVar19 = *(undefined8 **)(this + 0x78);
    if (puVar18 != puVar19) {
      do {
        puVar8 = (undefined8 *)ArtDoc::Document::GetPagesBegin((Document *)*puVar18);
        CopyMarksToPageWithLog(this,*(Page **)*puVar8,param_1,!param_6);
        puVar18 = puVar18 + 1;
      } while (puVar18 != puVar19);
      local_266 = '\x01';
      bVar16 = true;
    }
  }
  if (local_264 == '\0') {
LAB_18024d6f3:
    if (bVar16 == false) goto LAB_18024df1c;
  }
  else {
    puVar18 = *(undefined8 **)(this + 0x88);
    puVar19 = *(undefined8 **)(this + 0x90);
    if (puVar18 == puVar19) goto LAB_18024d6f3;
    do {
      puVar8 = (undefined8 *)ArtDoc::Document::GetPagesBegin((Document *)*puVar18);
      CopyMarksToPageWithLog(this,*(Page **)*puVar8,param_1,!param_6);
      puVar18 = puVar18 + 1;
    } while (puVar18 != puVar19);
    local_265 = '\x01';
  }
  pPVar9 = ArtDoc::Page::GetContent(param_1);
  DetectNormalizedInkTypes((Content *)pPVar9,true,true);
  InkCollector::InkCollector
            (local_1e8,param_1,false,
             (set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_> *)
             0x0);
  ArtDoc::PageContent::Accept((PageContent *)local_210,(ConstVisitorBase *)local_1e8);
  pDVar5 = ArtDoc::Content::GetDocument(local_210);
  pvVar10 = ArtDoc::Document::GetSeparationInfo(pDVar5);
  FUN_1800367a0(&local_258,pvVar10);
  pEVar21 = local_250;
  for (pEVar22 = local_258; pEVar22 != pEVar21; pEVar22 = pEVar22 + 0xf0) {
    IVar4 = ArtDoc::Separation::Entry::GetInkType(pEVar22);
    if ((IVar4 == 2) || (IVar4 = ArtDoc::Separation::Entry::GetInkType(pEVar22), IVar4 == 3)) {
      IVar4 = ArtDoc::Separation::Entry::GetInkType(pEVar22);
      pbVar7 = ArtDoc::Separation::Entry::GetName(pEVar22);
      AddNormalizedInkHint(pbVar7,IVar4);
    }
  }
  local_240 = (void *)0x0;
  plStack_238 = (longlong *)0x0;
  local_230 = (longlong *)0x0;
  if (bVar2) {
    local_260 = this + 0x28;
    FUN_18001de60(&local_240,0,&local_260);
    puVar18 = *(undefined8 **)(this + 0x30);
    for (puVar19 = *(undefined8 **)(this + 0x28); puVar19 != puVar18; puVar19 = puVar19 + 1) {
      bVar2 = ArtDoc::Document::GetInfoFlag((Document *)*puVar19,2);
      if (bVar2) {
        pvVar10 = ArtDoc::Document::GetSeparationInfo((Document *)*puVar19);
        AddNormalizedInkHints(pvVar10);
      }
    }
    ppEVar11 = (Entry **)
               InkCollector::MergeUsedSeparations
                         (local_1e8,local_228,
                          (vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
                           *)&local_258);
    if (&local_258 != ppEVar11) {
      FUN_18003aac0(&local_258);
      local_258 = *ppEVar11;
      local_250 = ppEVar11[1];
      local_248 = ppEVar11[2];
      *ppEVar11 = (Entry *)0x0;
      ppEVar11[1] = (Entry *)0x0;
      ppEVar11[2] = (Entry *)0x0;
    }
    FUN_18003aac0(local_228);
  }
  plVar20 = plStack_238;
  plVar23 = local_230;
  if (local_267 != '\0') {
    pTVar1 = this + 0x40;
    local_260 = pTVar1;
    if (plStack_238 == local_230) {
      FUN_18001de60(&local_240,plStack_238,&local_260);
    }
    else {
      *plStack_238 = (longlong)pTVar1;
      plStack_238 = plStack_238 + 1;
    }
    plVar23 = local_230;
    plVar20 = plStack_238;
    puVar18 = *(undefined8 **)(this + 0x48);
    for (puVar19 = *(undefined8 **)pTVar1; puVar19 != puVar18; puVar19 = puVar19 + 1) {
      bVar2 = ArtDoc::Document::GetInfoFlag((Document *)*puVar19,2);
      if (bVar2) {
        pvVar10 = ArtDoc::Document::GetSeparationInfo((Document *)*puVar19);
        AddNormalizedInkHints(pvVar10);
      }
    }
    ppEVar11 = (Entry **)
               InkCollector::MergeUsedSeparations
                         (local_1e8,local_228,
                          (vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
                           *)&local_258);
    if (&local_258 != ppEVar11) {
      FUN_18003aac0(&local_258);
      local_258 = *ppEVar11;
      local_250 = ppEVar11[1];
      local_248 = ppEVar11[2];
      *ppEVar11 = (Entry *)0x0;
      ppEVar11[1] = (Entry *)0x0;
      ppEVar11[2] = (Entry *)0x0;
    }
    FUN_18003aac0(local_228);
  }
  if (local_268 != '\0') {
    pTVar1 = this + 0x58;
    local_260 = pTVar1;
    if (plVar20 == plVar23) {
      FUN_18001de60(&local_240,plVar20,&local_260);
      plVar23 = local_230;
    }
    else {
      *plVar20 = (longlong)pTVar1;
      plStack_238 = plVar20 + 1;
    }
    plVar20 = plStack_238;
    puVar18 = *(undefined8 **)(this + 0x60);
    for (puVar19 = *(undefined8 **)pTVar1; puVar19 != puVar18; puVar19 = puVar19 + 1) {
      bVar2 = ArtDoc::Document::GetInfoFlag((Document *)*puVar19,2);
      if (bVar2) {
        pvVar10 = ArtDoc::Document::GetSeparationInfo((Document *)*puVar19);
        AddNormalizedInkHints(pvVar10);
      }
    }
    ppEVar11 = (Entry **)
               InkCollector::MergeUsedSeparations
                         (local_1e8,local_228,
                          (vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
                           *)&local_258);
    if (&local_258 != ppEVar11) {
      FUN_18003aac0(&local_258);
      local_258 = *ppEVar11;
      local_250 = ppEVar11[1];
      local_248 = ppEVar11[2];
      *ppEVar11 = (Entry *)0x0;
      ppEVar11[1] = (Entry *)0x0;
      ppEVar11[2] = (Entry *)0x0;
    }
    FUN_18003aac0(local_228);
  }
  if (local_266 != '\0') {
    pTVar1 = this + 0x70;
    local_260 = pTVar1;
    if (plVar20 == plVar23) {
      FUN_18001de60(&local_240,plVar20,&local_260);
      plVar23 = local_230;
    }
    else {
      *plVar20 = (longlong)pTVar1;
      plStack_238 = plVar20 + 1;
    }
    plVar20 = plStack_238;
    puVar18 = *(undefined8 **)(this + 0x78);
    for (puVar19 = *(undefined8 **)pTVar1; puVar19 != puVar18; puVar19 = puVar19 + 1) {
      bVar2 = ArtDoc::Document::GetInfoFlag((Document *)*puVar19,2);
      if (bVar2) {
        pvVar10 = ArtDoc::Document::GetSeparationInfo((Document *)*puVar19);
        AddNormalizedInkHints(pvVar10);
      }
    }
    ppEVar11 = (Entry **)
               InkCollector::MergeUsedSeparations
                         (local_1e8,local_228,
                          (vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
                           *)&local_258);
    if (&local_258 != ppEVar11) {
      FUN_18003aac0(&local_258);
      local_258 = *ppEVar11;
      local_250 = ppEVar11[1];
      local_248 = ppEVar11[2];
      *ppEVar11 = (Entry *)0x0;
      ppEVar11[1] = (Entry *)0x0;
      ppEVar11[2] = (Entry *)0x0;
    }
    FUN_18003aac0(local_228);
  }
  if (local_265 != '\0') {
    pTVar1 = this + 0x88;
    local_260 = pTVar1;
    if (plVar20 == plVar23) {
      FUN_18001de60(&local_240,plVar20,&local_260);
    }
    else {
      *plVar20 = (longlong)pTVar1;
      plStack_238 = plVar20 + 1;
    }
    puVar18 = *(undefined8 **)(this + 0x90);
    for (puVar19 = *(undefined8 **)pTVar1; puVar19 != puVar18; puVar19 = puVar19 + 1) {
      bVar2 = ArtDoc::Document::GetInfoFlag((Document *)*puVar19,2);
      if (bVar2) {
        pvVar10 = ArtDoc::Document::GetSeparationInfo((Document *)*puVar19);
        AddNormalizedInkHints(pvVar10);
      }
    }
    ppEVar11 = (Entry **)
               InkCollector::MergeUsedSeparations
                         (local_1e8,local_228,
                          (vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
                           *)&local_258);
    if (&local_258 != ppEVar11) {
      FUN_18003aac0(&local_258);
      local_258 = *ppEVar11;
      local_250 = ppEVar11[1];
      local_248 = ppEVar11[2];
      *ppEVar11 = (Entry *)0x0;
      ppEVar11[1] = (Entry *)0x0;
      ppEVar11[2] = (Entry *)0x0;
    }
    FUN_18003aac0(local_228);
  }
  pEVar22 = *(Entry **)(this + 0x18);
  this_00 = local_210;
  for (pEVar21 = *(Entry **)(this + 0x10); local_210 = this_00, pEVar21 != pEVar22;
      pEVar21 = pEVar21 + 0xf0) {
    ArtDoc::Separation::FindOrAdd
              ((vector<ArtDoc::Separation::Entry,std::allocator<ArtDoc::Separation::Entry>_> *)
               &local_258,pEVar21);
    this_00 = local_210;
  }
  pDVar5 = ArtDoc::Content::GetDocument(this_00);
  uVar12 = FUN_1800367a0(local_228,&local_258);
  ArtDoc::Document::SetSeparationInfo(pDVar5,uVar12);
  pSVar13 = ArtDoc::Content::GetSeparations(this_00);
  ArtDoc::Separations::GetList(pSVar13,SUB81(local_d8,0));
  pDVar5 = ArtDoc::Content::GetDocument(this_00);
  _Var14 = ArtDoc::Content::GetID(this_00);
  pDVar15 = ArtDoc::Content::GetDocument(this_00);
  pDVar6 = GetDynamicMarksController(pDVar15);
  local_88 = std::
             _Func_impl_no_alloc<`public:_void___cdecl_DocumentMarks::TaskMarkSets::ApplyRelevantMarkSets(ArtDoc::Page&___ptr64,int,bool,bool,bool,bool)___ptr64'::`37'::<lambda_1>,void>
             ::vftable;
  local_50 = &local_88;
  local_80 = pDVar5;
  local_78 = _Var14;
  DynamicMarksController::RequestExtraRegeneration(pDVar6,(function<void___cdecl(void)> *)&local_88)
  ;
  if (local_50 != (undefined ***)0x0) {
    (*(code *)(*local_50)[4])
              (local_50,CONCAT71((int7)((ulonglong)&local_88 >> 8),local_50 != &local_88));
  }
  UpdateMarksOnPage(param_1);
  pDVar5 = ArtDoc::Content::GetDocument(this_00);
  pvVar10 = ArtDoc::Document::GetSeparationInfo(pDVar5);
  FUN_1800367a0(local_200,pvVar10);
  pSVar13 = ArtDoc::Content::GetSeparations(this_00);
  ArtDoc::Separations::GetList(pSVar13,SUB81(local_b0,0));
  cVar3 = FUN_18024d0e0(local_b0,&local_240,local_208,&local_258);
  lVar17 = (local_c0 - local_c8) / 6 + (local_c0 - local_c8 >> 0x3f);
  if (((ulonglong)((lVar17 >> 3) - (lVar17 >> 0x3f)) < (ulonglong)((local_98 - local_a0) / 0x30)) ||
     (cVar3 != '\0')) {
    ppEVar11 = (Entry **)
               MergeSeparationInfo(local_228,
                                   (vector<class_ArtDoc::Separation::Entry,class_std::allocator<class_ArtDoc::Separation::Entry>_>
                                    *)&local_258);
    if (&local_258 != ppEVar11) {
      FUN_18003aac0(&local_258);
      local_258 = *ppEVar11;
      local_250 = ppEVar11[1];
      local_248 = ppEVar11[2];
      *ppEVar11 = (Entry *)0x0;
      ppEVar11[1] = (Entry *)0x0;
      ppEVar11[2] = (Entry *)0x0;
    }
    FUN_18003aac0(local_228);
    pDVar5 = ArtDoc::Content::GetDocument(this_00);
    uVar12 = FUN_1800367a0(local_228,&local_258);
    ArtDoc::Document::SetSeparationInfo(pDVar5,uVar12);
    pDVar5 = ArtDoc::Content::GetDocument(this_00);
    this_01 = ArtDoc::Document::GetDynamicObjects(pDVar5);
    ArtDoc::DynamicObjectController::SetAllNeedUpdate(this_01,param_1);
    UpdateMarksOnPage(param_1);
  }
  FUN_18003f6e0(local_b0);
  FUN_18003aac0(local_200);
  FUN_18003f6e0(local_d8);
  if (local_240 != (void *)0x0) {
    _Memory = local_240;
    if ((0xfff < (ulonglong)(((longlong)local_230 - (longlong)local_240 >> 3) * 8)) &&
       (_Memory = *(void **)((longlong)local_240 + -8),
       0x1f < (ulonglong)((longlong)local_240 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
  }
  FUN_18003aac0(&local_258);
  FUN_18001e460(local_1a0);
  FUN_180019170(local_1b8);
  local_1d8 = ArtDoc::ConstVisitor<DocumentMarks::SNRGrid>::_vftable_;
  local_1e0 = ArtDoc::ConstVisitor<DocumentMarks::DynamicObject>::_vftable_;
  ArtDoc::ConstVisitorBase::~ConstVisitorBase((ConstVisitorBase *)local_1e8);
LAB_18024df1c:
  if (param_5) {
    GetDynamicMarksBox(local_d8);
    AdjustPageBoxes(param_1,(RectangleBase<YAGL::MilliPointCoordinateSystem> *)local_d8);
  }
  if (param_6) {
    MakeFormsFromMarks(param_1,false);
  }
  MoveExpandedMarks(param_1,!param_6);
  return;
}


