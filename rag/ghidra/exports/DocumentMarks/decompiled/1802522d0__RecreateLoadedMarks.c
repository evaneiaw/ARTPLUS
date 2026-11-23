// 1802522d0 RecreateLoadedMarks

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: void __cdecl DocumentMarks::TaskMarkSets::RecreateLoadedMarks(void) __ptr64 */

void __thiscall DocumentMarks::TaskMarkSets::RecreateLoadedMarks(TaskMarkSets *this)

{
  longlong *plVar1;
  PageContent *pPVar2;
  Path *pPVar3;
  undefined8 *puVar4;
  int iVar5;
  undefined1 auStack_a8 [32];
  undefined8 *local_88;
  undefined **local_78;
  undefined1 local_70;
  undefined ***local_40;
  ulonglong local_38;
  
                    /* 0x2522d0  1444  ?RecreateLoadedMarks@TaskMarkSets@DocumentMarks@@IEAAXXZ */
  local_38 = DAT_180418e00 ^ (ulonglong)auStack_a8;
  ArtDoc::Document::GetPagesBegin(*(Document **)(this + 8));
  plVar1 = (longlong *)ArtDoc::Document::GetPagesEnd(*(Document **)(this + 8));
  if (local_88 != (undefined8 *)*plVar1) {
    do {
      pPVar2 = ArtDoc::Page::GetContent((Page *)*local_88);
      iVar5 = 0;
      do {
        local_78 = std::
                   _Func_impl_no_alloc<`protected:_void___cdecl_DocumentMarks::TaskMarkSets::RecreateLoadedMarks(void)___ptr64'::`6'::<lambda_1>,bool,ArtDoc::ContentObject_const&___ptr64>
                   ::vftable;
        local_40 = &local_78;
        local_70 = iVar5 != 0;
        pPVar3 = DocumentEdit::MakeForm
                           ((Content *)pPVar2,
                            (function<bool___cdecl(ArtDoc::ContentObject_const&___ptr64)> *)
                            &local_78);
        if (local_40 != (undefined ***)0x0) {
          (*(code *)(*local_40)[4])(local_40,local_40 != &local_78);
          local_40 = (undefined ***)0x0;
        }
        if (pPVar3 != (Path *)0x0) {
          FUN_1800465a0(pPVar3,iVar5 != 0);
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < 2);
      local_88 = local_88 + 1;
      puVar4 = (undefined8 *)ArtDoc::Document::GetPagesEnd(*(Document **)(this + 8));
    } while (local_88 != (undefined8 *)*puVar4);
  }
  RemoveStaticContent(this);
  return;
}


