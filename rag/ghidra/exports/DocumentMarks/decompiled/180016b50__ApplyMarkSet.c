// 180016b50 ApplyMarkSet

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::ApplyMarkSet(class ArtDoc::Document & __ptr64,class
   boost::filesystem::path const & __ptr64,bool,class std::set<unsigned __int64,struct
   std::less<unsigned __int64>,class std::allocator<unsigned __int64> > * __ptr64) */

void __cdecl
DocumentMarks::ApplyMarkSet
          (Document *param_1,path *param_2,bool param_3,
          set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_>
          *param_4)

{
  Page *this;
  Page *pPVar1;
  ChangeTracker *pCVar2;
  PageContent *pPVar3;
  undefined8 *puVar4;
  __uint64 _Var5;
  DynamicMarksController *this_00;
  undefined1 auStackY_f8 [32];
  undefined8 *local_b8;
  undefined8 *local_b0;
  Document *local_a8;
  ActionGroupCreator local_a0 [24];
  undefined **local_88;
  Document *local_80;
  __uint64 local_78;
  undefined ***local_50;
  ulonglong local_48;
  
                    /* 0x16b50  846
                       ?ApplyMarkSet@DocumentMarks@@YAXAEAVDocument@ArtDoc@@AEBVpath@filesystem@boost@@_NPEAV?$set@_KU?$less@_K@std@@V?$allocator@_K@2@@std@@@Z
                        */
  local_48 = DAT_180418e00 ^ (ulonglong)auStackY_f8;
  FUN_180017010(&local_a8);
  if (local_a8 == (Document *)0x0) {
    if (!param_3) goto LAB_180016d27;
    ArtDoc::ActionGroupCreator::ActionGroupCreator(local_a0,param_1,false,false);
    ArtDoc::Document::GetPagesBegin(param_1);
    ArtDoc::Document::GetPagesEnd(param_1);
    for (; local_b8 != local_b0; local_b8 = local_b8 + 1) {
      DeleteMarks((Page *)*local_b8,false);
    }
  }
  else {
    ArtDoc::ActionGroupCreator::ActionGroupCreator(local_a0,param_1,false,false);
    ArtDoc::Document::GetPagesBegin(param_1);
    ArtDoc::Document::GetPagesEnd(param_1);
    for (; local_b8 != local_b0; local_b8 = local_b8 + 1) {
      this = (Page *)*local_b8;
      pCVar2 = GetChangeTracker(param_1);
      pPVar3 = ArtDoc::Page::GetContent(this);
      FUN_180015f90(*(undefined8 *)(pCVar2 + 0xf0),pPVar3);
      puVar4 = (undefined8 *)ArtDoc::Document::GetPagesBegin(local_a8);
      pPVar1 = *(Page **)*puVar4;
      if (param_3) {
        DeleteMarks(this,false);
      }
      CopyMarksToPage(pPVar1,this,true,
                      (set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
                       *)0x0,(set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
                              *)0x0,param_4,true);
      pPVar3 = ArtDoc::Page::GetContent(this);
      _Var5 = ArtDoc::Content::GetID((Content *)pPVar3);
      this_00 = GetDynamicMarksController(param_1);
      local_88 = std::
                 _Func_impl_no_alloc<`void___cdecl_DocumentMarks::ApplyMarkSet(ArtDoc::Document&___ptr64,boost::filesystem::path_const&___ptr64,bool,std::set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_>*___ptr64)'::`9'::<lambda_1>,void>
                 ::vftable;
      local_50 = &local_88;
      local_80 = param_1;
      local_78 = _Var5;
      DynamicMarksController::RequestExtraRegeneration
                (this_00,(function<void___cdecl(void)> *)&local_88);
      if (local_50 != (undefined ***)0x0) {
        (*(code *)(*local_50)[4])
                  (local_50,CONCAT71((int7)((ulonglong)&local_88 >> 8),local_50 != &local_88));
      }
    }
  }
  ArtDoc::ActionGroupCreator::~ActionGroupCreator(local_a0);
LAB_180016d27:
  if (local_a8 != (Document *)0x0) {
    ArtDoc::Document::~Document(local_a8);
    free(local_a8);
  }
  return;
}


