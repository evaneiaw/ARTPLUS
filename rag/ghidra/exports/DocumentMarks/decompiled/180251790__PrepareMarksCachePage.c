// 180251790 PrepareMarksCachePage

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: class std::vector<class ArtDoc::Separation::Entry,class std::allocator<class
   ArtDoc::Separation::Entry> > __cdecl DocumentMarks::TaskMarkSets::PrepareMarksCachePage(class
   ArtDoc::Page & __ptr64,class std::vector<class std::unique_ptr<class ArtDoc::Document,struct
   std::default_delete<class ArtDoc::Document> >,class std::allocator<class std::unique_ptr<class
   ArtDoc::Document,struct std::default_delete<class ArtDoc::Document> > > > const & __ptr64,class
   std::vector<class std::unique_ptr<class ArtDoc::Document,struct std::default_delete<class
   ArtDoc::Document> >,class std::allocator<class std::unique_ptr<class ArtDoc::Document,struct
   std::default_delete<class ArtDoc::Document> > > > const & __ptr64,class std::vector<class
   std::unique_ptr<class ArtDoc::Document,struct std::default_delete<class ArtDoc::Document> >,class
   std::allocator<class std::unique_ptr<class ArtDoc::Document,struct std::default_delete<class
   ArtDoc::Document> > > > const & __ptr64,bool,bool,bool) __ptr64 */

Page * __thiscall
DocumentMarks::TaskMarkSets::PrepareMarksCachePage
          (TaskMarkSets *this,Page *param_1,
          vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
          *param_2,vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
                   *param_3,
          vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
          *param_4,bool param_5,bool param_6,bool param_7)

{
  Entry *pEVar1;
  undefined8 *puVar2;
  vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
  *pvVar3;
  char cVar4;
  PageContent *pPVar5;
  Document *this_00;
  DynamicMarksController *pDVar6;
  vector<ArtDoc::Separation::Entry,std::allocator<ArtDoc::Separation::Entry>_> *pvVar7;
  longlong *plVar8;
  undefined8 uVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  Separations *pSVar12;
  DynamicObjectController *this_01;
  ActionList *this_02;
  void *_Memory;
  longlong lVar13;
  Entry *pEVar14;
  undefined8 *puVar15;
  undefined7 in_stack_00000031;
  char in_stack_00000048;
  undefined1 auStack_168 [32];
  vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
  *local_148;
  longlong local_140;
  longlong local_138;
  longlong local_130;
  void *local_128;
  undefined8 *puStack_120;
  undefined8 *local_118;
  undefined4 local_110;
  vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
  *local_108;
  Document *local_100;
  TaskMarkSets *local_f8;
  vector<class_ArtDoc::Separation::Entry,class_std::allocator<class_ArtDoc::Separation::Entry>_>
  local_f0 [40];
  Page *local_c8;
  undefined1 local_c0 [24];
  undefined1 local_a8 [16];
  longlong local_98;
  longlong local_90;
  undefined1 local_80 [16];
  longlong local_70;
  longlong local_68;
  ulonglong local_58;
  
                    /* 0x251790  1436
                       ?PrepareMarksCachePage@TaskMarkSets@DocumentMarks@@IEAA?AV?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@std@@AEAVPage@ArtDoc@@AEBV?$vector@V?$unique_ptr@VDocument@ArtDoc@@U?$default_delete@VDocument@ArtDoc@@@std@@@std@@V?$allocator@V?$unique_ptr@VDocument@ArtDoc@@U?$default_delete@VDocument@ArtDoc@@@std@@@std@@@2@@4@11_N22@Z
                        */
  local_58 = DAT_180418e00 ^ (ulonglong)auStack_168;
  pvVar3 = (vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
            *)CONCAT71(in_stack_00000031,param_5);
  *(undefined8 *)param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  local_110 = 1;
  local_108 = param_3;
  local_c8 = param_1;
  if (param_7) {
    DeleteMarks((Page *)param_2,false);
    DeleteExpandedMarks((Page *)param_2);
    RemoveUnusedSeparationsFromPage((Page *)param_2);
  }
  if (in_stack_00000048 != '\0') {
    MoveExpandedMarks((Page *)param_2,false);
  }
  pPVar5 = ArtDoc::Page::GetContent((Page *)param_2);
  this_00 = ArtDoc::Content::GetDocument((Content *)pPVar5);
  local_100 = this_00;
  if ((((*(longlong *)param_3 != *(longlong *)(param_3 + 8)) ||
       (*(longlong *)param_4 != *(longlong *)(param_4 + 8))) ||
      (*(longlong *)pvVar3 != *(longlong *)(pvVar3 + 8))) ||
     (*(longlong *)(this + 0x10) != *(longlong *)(this + 0x18))) {
    pDVar6 = GetDynamicMarksController(this_00);
    DynamicMarksController::EnableUpdates(pDVar6,false);
    pvVar7 = ArtDoc::Document::GetSeparationInfo(this_00);
    FUN_1800367a0(&local_140,pvVar7);
    plVar8 = (longlong *)FUN_180250080(&local_128,&local_140,param_3);
    if (&local_140 != plVar8) {
      FUN_18003aac0(&local_140);
      local_140 = *plVar8;
      local_138 = plVar8[1];
      local_130 = plVar8[2];
      *plVar8 = 0;
      plVar8[1] = 0;
      plVar8[2] = 0;
    }
    FUN_18003aac0(&local_128);
    plVar8 = (longlong *)FUN_180250080(&local_128,&local_140,param_4);
    if (&local_140 != plVar8) {
      FUN_18003aac0(&local_140);
      local_140 = *plVar8;
      local_138 = plVar8[1];
      local_130 = plVar8[2];
      *plVar8 = 0;
      plVar8[1] = 0;
      plVar8[2] = 0;
    }
    FUN_18003aac0(&local_128);
    plVar8 = (longlong *)FUN_180250080(&local_128,&local_140,pvVar3);
    if (&local_140 != plVar8) {
      FUN_18003aac0(&local_140);
      local_140 = *plVar8;
      local_138 = plVar8[1];
      local_130 = plVar8[2];
      *plVar8 = 0;
      plVar8[1] = 0;
      plVar8[2] = 0;
    }
    FUN_18003aac0(&local_128);
    local_f8 = this + 0x10;
    pEVar1 = *(Entry **)(this + 0x18);
    for (pEVar14 = *(Entry **)local_f8; pEVar14 != pEVar1; pEVar14 = pEVar14 + 0xf0) {
      ArtDoc::Separation::FindOrAdd
                ((vector<ArtDoc::Separation::Entry,std::allocator<ArtDoc::Separation::Entry>_> *)
                 &local_140,pEVar14);
    }
    uVar9 = FUN_1800367a0(&local_128,&local_140);
    ArtDoc::Document::SetSeparationInfo(local_100,uVar9);
    local_128 = (void *)0x0;
    puStack_120 = (undefined8 *)0x0;
    local_118 = (undefined8 *)0x0;
    puVar15 = *(undefined8 **)local_108;
    puVar2 = *(undefined8 **)(local_108 + 8);
    if (puVar15 != puVar2) {
      do {
        puVar10 = (undefined8 *)ArtDoc::Document::GetPagesBegin((Document *)*puVar15);
        CopyMarksToPageWithLog(this,*(Page **)*puVar10,(Page *)param_2,false);
        puVar15 = puVar15 + 1;
      } while (puVar15 != puVar2);
      local_148 = local_108;
      FUN_18001de60(&local_128,0,&local_148);
    }
    puVar15 = *(undefined8 **)param_4;
    puVar2 = *(undefined8 **)(param_4 + 8);
    if (puVar15 != puVar2) {
      do {
        puVar10 = (undefined8 *)ArtDoc::Document::GetPagesBegin((Document *)*puVar15);
        CopyMarksToPageWithLog(this,*(Page **)*puVar10,(Page *)param_2,false);
        puVar15 = puVar15 + 1;
      } while (puVar15 != puVar2);
      local_148 = param_4;
      if (puStack_120 == local_118) {
        FUN_18001de60(&local_128,puStack_120,&local_148);
      }
      else {
        *puStack_120 = param_4;
        puStack_120 = puStack_120 + 1;
      }
    }
    puVar10 = puStack_120;
    puVar15 = *(undefined8 **)pvVar3;
    puVar2 = *(undefined8 **)(pvVar3 + 8);
    if (puVar15 != puVar2) {
      do {
        puVar11 = (undefined8 *)ArtDoc::Document::GetPagesBegin((Document *)*puVar15);
        CopyMarksToPageWithLog(this,*(Page **)*puVar11,(Page *)param_2,false);
        puVar15 = puVar15 + 1;
      } while (puVar15 != puVar2);
      local_148 = pvVar3;
      if (puVar10 == local_118) {
        FUN_18001de60(&local_128,puVar10,&local_148);
      }
      else {
        *puVar10 = pvVar3;
        puStack_120 = puVar10 + 1;
      }
    }
    pPVar5 = ArtDoc::Page::GetContent((Page *)param_2);
    pSVar12 = ArtDoc::Content::GetSeparations((Content *)pPVar5);
    ArtDoc::Separations::GetList(pSVar12,SUB81(local_80,0));
    UpdateMarksOnPage((Page *)param_2);
    this_00 = local_100;
    pvVar7 = ArtDoc::Document::GetSeparationInfo(local_100);
    FUN_1800367a0(local_c0,pvVar7);
    pPVar5 = ArtDoc::Page::GetContent((Page *)param_2);
    pSVar12 = ArtDoc::Content::GetSeparations((Content *)pPVar5);
    ArtDoc::Separations::GetList(pSVar12,SUB81(local_a8,0));
    cVar4 = FUN_18024d0e0(local_a8,&local_128,local_f8,&local_140);
    lVar13 = (local_90 - local_98) / 6 + (local_90 - local_98 >> 0x3f);
    if (((ulonglong)((local_68 - local_70) / 0x30) < (ulonglong)((lVar13 >> 3) - (lVar13 >> 0x3f)))
       || (cVar4 != '\0')) {
      plVar8 = (longlong *)
               MergeSeparationInfo(local_f0,(vector<class_ArtDoc::Separation::Entry,class_std::allocator<class_ArtDoc::Separation::Entry>_>
                                             *)&local_140);
      if (&local_140 != plVar8) {
        FUN_18003aac0(&local_140);
        local_140 = *plVar8;
        local_138 = plVar8[1];
        local_130 = plVar8[2];
        *plVar8 = 0;
        plVar8[1] = 0;
        plVar8[2] = 0;
      }
      FUN_18003aac0(local_f0);
      uVar9 = FUN_1800367a0(local_f0,&local_140);
      ArtDoc::Document::SetSeparationInfo(this_00,uVar9);
      this_01 = ArtDoc::Document::GetDynamicObjects(this_00);
      ArtDoc::DynamicObjectController::SetAllNeedUpdate(this_01,(Page *)param_2);
      UpdateMarksOnPage((Page *)param_2);
    }
    if (param_6) {
      GetDynamicMarksBox((Page *)local_f0);
      AdjustPageBoxes((Page *)param_2,(RectangleBase<YAGL::MilliPointCoordinateSystem> *)local_f0);
    }
    if (param_1 != (Page *)&local_140) {
      lVar13 = SUB168(SEXT816(-0x7777777777777777) * SEXT816(local_138 - local_140),8) +
               (local_138 - local_140);
      FUN_1800ea0e0(param_1,local_140,(lVar13 >> 7) - (lVar13 >> 0x3f));
    }
    pDVar6 = GetDynamicMarksController(this_00);
    DynamicMarksController::EnableUpdates(pDVar6,false);
    FUN_18003f6e0(local_a8);
    FUN_18003aac0(local_c0);
    FUN_18003f6e0(local_80);
    if (local_128 != (void *)0x0) {
      _Memory = local_128;
      if ((0xfff < (ulonglong)(((longlong)local_118 - (longlong)local_128 >> 3) * 8)) &&
         (_Memory = *(void **)((longlong)local_128 + -8),
         0x1f < (ulonglong)((longlong)local_128 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
    FUN_18003aac0(&local_140);
  }
  this_02 = ArtDoc::Document::GetActionList(this_00);
  ArtDoc::ActionList::Clear(this_02);
  return param_1;
}


