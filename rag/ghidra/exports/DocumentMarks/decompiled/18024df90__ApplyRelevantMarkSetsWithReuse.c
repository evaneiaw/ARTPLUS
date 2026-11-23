// 18024df90 ApplyRelevantMarkSetsWithReuse

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: void __cdecl DocumentMarks::TaskMarkSets::ApplyRelevantMarkSetsWithReuse(class
   ArtDoc::Page & __ptr64,class ArtDoc::CloneStrategy & __ptr64,int,bool,bool,bool) __ptr64 */

void __thiscall
DocumentMarks::TaskMarkSets::ApplyRelevantMarkSetsWithReuse
          (TaskMarkSets *this,Page *param_1,CloneStrategy *param_2,int param_3,bool param_4,
          bool param_5,bool param_6)

{
  bool bVar1;
  __uint64 _Var2;
  undefined8 *puVar3;
  Content *this_00;
  longlong *plVar4;
  PageContent *pPVar5;
  Document *pDVar6;
  Document *pDVar7;
  DynamicMarksController *this_01;
  undefined8 uVar8;
  Layer *pLVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined1 auStack_f8 [40];
  uint local_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  Page local_a0 [40];
  undefined **local_78;
  Document *local_70;
  __uint64 local_68;
  undefined ***local_40;
  ulonglong local_38;
  
                    /* 0x24df90  852
                       ?ApplyRelevantMarkSetsWithReuse@TaskMarkSets@DocumentMarks@@QEAAXAEAVPage@ArtDoc@@AEAVCloneStrategy@4@H_N22@Z
                        */
  local_38 = DAT_180418e00 ^ (ulonglong)auStack_f8;
  bVar1 = false;
  local_c8 = 0;
  uStack_c0 = 0;
  local_b8 = 0;
  uStack_b0 = 0;
  local_a8 = CONCAT71(local_a8._1_7_,1);
  local_d0 = param_3;
  _Var2 = ArtDoc::Document::GetNumberOfPages(*(Document **)(this + 8));
  if (_Var2 == 1) {
    puVar3 = (undefined8 *)ArtDoc::Document::GetPagesBegin(*(Document **)(this + 8));
    if (*(longlong *)(this + 0x170) == 0) {
      if (*(longlong *)(this + 0x178) == 0) {
        CopyMarksAsFormsToPage(*(Page **)*puVar3,param_1,param_2);
        local_c8 = *(undefined8 *)(this + 0x108);
        uStack_c0 = *(undefined8 *)(this + 0x110);
        uVar12 = *(undefined4 *)(this + 0x118);
        uVar13 = *(undefined4 *)(this + 0x11c);
        uVar14 = *(undefined4 *)(this + 0x120);
        uVar15 = *(undefined4 *)(this + 0x124);
        uVar10 = (undefined4)*(undefined8 *)(this + 0x128);
        uVar11 = (undefined4)((ulonglong)*(undefined8 *)(this + 0x128) >> 0x20);
        goto LAB_18024e1d0;
      }
    }
    else {
LAB_18024e044:
      pPVar5 = ArtDoc::Page::GetContent(param_1);
      pLVar9 = ArtDoc::Layer::Clone(*(Layer **)(this + 0x170),param_2);
      ArtDoc::Content::AddOnTop((Content *)pPVar5,(ContentObject *)pLVar9);
      if (*(longlong *)(this + 0x178) == 0) {
        return;
      }
    }
LAB_18024e07a:
    this_00 = (Content *)ArtDoc::Page::GetContent(param_1);
    pLVar9 = *(Layer **)(this + 0x178);
LAB_18024e353:
    pLVar9 = ArtDoc::Layer::Clone(pLVar9,param_2);
    ArtDoc::Content::AddOnTop(this_00,(ContentObject *)pLVar9);
  }
  else {
    if (param_3 == 1) {
      puVar3 = (undefined8 *)ArtDoc::Document::GetPagesBegin(*(Document **)(this + 8));
      CopyMarksAsFormsToPage(*(Page **)*puVar3,param_1,param_2);
      local_c8 = *(undefined8 *)(this + 0x108);
      uStack_c0 = *(undefined8 *)(this + 0x110);
      uVar12 = *(undefined4 *)(this + 0x118);
      uVar13 = *(undefined4 *)(this + 0x11c);
      uVar14 = *(undefined4 *)(this + 0x120);
      uVar15 = *(undefined4 *)(this + 0x124);
      uVar10 = (undefined4)*(undefined8 *)(this + 0x128);
      uVar11 = (undefined4)((ulonglong)*(undefined8 *)(this + 0x128) >> 0x20);
    }
    else if ((param_4) &&
            (_Var2 = ArtDoc::Document::GetNumberOfPages(*(Document **)(this + 8)), _Var2 == 4)) {
      plVar4 = (longlong *)ArtDoc::Document::GetPagesBegin(*(Document **)(this + 8));
      CopyMarksAsFormsToPage(*(Page **)(*plVar4 + 0x18),param_1,param_2);
      local_c8 = *(undefined8 *)(this + 0x130);
      uStack_c0 = *(undefined8 *)(this + 0x138);
      uVar12 = *(undefined4 *)(this + 0x140);
      uVar13 = *(undefined4 *)(this + 0x144);
      uVar14 = *(undefined4 *)(this + 0x148);
      uVar15 = *(undefined4 *)(this + 0x14c);
      uVar10 = (undefined4)*(undefined8 *)(this + 0x150);
      uVar11 = (undefined4)((ulonglong)*(undefined8 *)(this + 0x150) >> 0x20);
    }
    else {
      plVar4 = (longlong *)ArtDoc::Document::GetPagesBegin(*(Document **)(this + 8));
      if ((param_3 & 1U) == 0) {
        if (*(longlong *)(this + 0x160) == 0) {
          if (*(longlong *)(this + 0x168) == 0) {
            CopyMarksAsFormsToPage(*(Page **)(*plVar4 + 8),param_1,param_2);
            local_c8 = *(undefined8 *)(this + 0xe0);
            uStack_c0 = *(undefined8 *)(this + 0xe8);
            uVar12 = *(undefined4 *)(this + 0xf0);
            uVar13 = *(undefined4 *)(this + 0xf4);
            uVar14 = *(undefined4 *)(this + 0xf8);
            uVar15 = *(undefined4 *)(this + 0xfc);
            uVar10 = (undefined4)*(undefined8 *)(this + 0x100);
            uVar11 = (undefined4)((ulonglong)*(undefined8 *)(this + 0x100) >> 0x20);
            goto LAB_18024e1d0;
          }
        }
        else {
          pPVar5 = ArtDoc::Page::GetContent(param_1);
          pLVar9 = ArtDoc::Layer::Clone(*(Layer **)(this + 0x160),param_2);
          ArtDoc::Content::AddOnTop((Content *)pPVar5,(ContentObject *)pLVar9);
          if (*(longlong *)(this + 0x168) == 0) {
            return;
          }
        }
        this_00 = (Content *)ArtDoc::Page::GetContent(param_1);
        pLVar9 = *(Layer **)(this + 0x168);
        goto LAB_18024e353;
      }
      if (*(longlong *)(this + 0x170) != 0) goto LAB_18024e044;
      if (*(longlong *)(this + 0x178) != 0) goto LAB_18024e07a;
      CopyMarksAsFormsToPage(*(Page **)(*plVar4 + 0x10),param_1,param_2);
      local_c8 = *(undefined8 *)(this + 0xb8);
      uStack_c0 = *(undefined8 *)(this + 0xc0);
      uVar12 = *(undefined4 *)(this + 200);
      uVar13 = *(undefined4 *)(this + 0xcc);
      uVar14 = *(undefined4 *)(this + 0xd0);
      uVar15 = *(undefined4 *)(this + 0xd4);
      uVar10 = (undefined4)*(undefined8 *)(this + 0xd8);
      uVar11 = (undefined4)((ulonglong)*(undefined8 *)(this + 0xd8) >> 0x20);
LAB_18024e1d0:
      bVar1 = true;
    }
    local_b8 = CONCAT44(uVar13,uVar12);
    uStack_b0 = CONCAT44(uVar15,uVar14);
    local_a8 = CONCAT44(uVar11,uVar10);
    if (param_6) {
      AdjustPageBoxes(param_1,(RectangleBase<YAGL::MilliPointCoordinateSystem> *)&local_c8);
    }
    if (param_5) {
      pPVar5 = ArtDoc::Page::GetContent(param_1);
      pDVar6 = ArtDoc::Content::GetDocument((Content *)pPVar5);
      pPVar5 = ArtDoc::Page::GetContent(param_1);
      _Var2 = ArtDoc::Content::GetID((Content *)pPVar5);
      pPVar5 = ArtDoc::Page::GetContent(param_1);
      pDVar7 = ArtDoc::Content::GetDocument((Content *)pPVar5);
      this_01 = GetDynamicMarksController(pDVar7);
      local_78 = std::
                 _Func_impl_no_alloc<`public:_void___cdecl_DocumentMarks::TaskMarkSets::ApplyRelevantMarkSetsWithReuse(ArtDoc::Page&___ptr64,ArtDoc::CloneStrategy&___ptr64,int,bool,bool,bool)___ptr64'::`53'::<lambda_1>,void>
                 ::vftable;
      local_40 = &local_78;
      local_70 = pDVar6;
      local_68 = _Var2;
      DynamicMarksController::RequestExtraRegeneration
                (this_01,(function<void___cdecl(void)> *)&local_78);
      if (local_40 != (undefined ***)0x0) {
        (*(code *)(*local_40)[4])
                  (local_40,CONCAT71((int7)((ulonglong)&local_78 >> 8),local_40 != &local_78));
      }
      UpdateMarksOnPage(param_1);
      GetDynamicMarksBox(local_a0);
      AdjustPageBoxes(param_1,(RectangleBase<YAGL::MilliPointCoordinateSystem> *)local_a0);
      MakeFormsFromMarks(param_1,false);
      param_3 = local_d0;
    }
    MoveExpandedMarks(param_1,false);
    if (((bVar1) && (!param_5)) && (!param_6)) {
      uVar8 = FUN_1800448c0(param_1,0);
      if ((param_3 & 1U) == 0) {
        *(undefined8 *)(this + 0x160) = uVar8;
        uVar8 = FUN_180044930(param_1,0);
        *(undefined8 *)(this + 0x168) = uVar8;
      }
      else {
        *(undefined8 *)(this + 0x170) = uVar8;
        uVar8 = FUN_180044930(param_1,0);
        *(undefined8 *)(this + 0x178) = uVar8;
      }
    }
  }
  return;
}


