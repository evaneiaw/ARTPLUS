// 180016d70 ApplyMarkSetToPage

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::ApplyMarkSetToPage(class ArtDoc::Page & __ptr64,class
   boost::filesystem::path const & __ptr64,bool,class std::set<unsigned __int64,struct
   std::less<unsigned __int64>,class std::allocator<unsigned __int64> > * __ptr64) */

void __cdecl
DocumentMarks::ApplyMarkSetToPage
          (Page *param_1,path *param_2,bool param_3,
          set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_>
          *param_4)

{
  Page *pPVar1;
  PageContent *pPVar2;
  Document *pDVar3;
  ChangeTracker *pCVar4;
  undefined8 *puVar5;
  __uint64 _Var6;
  Document *pDVar7;
  DynamicMarksController *this;
  undefined1 auStackY_d8 [32];
  Document *local_98 [2];
  ActionGroupCreator local_88 [16];
  undefined **local_78;
  Document *local_70;
  __uint64 local_68;
  undefined ***local_40;
  ulonglong local_38;
  
                    /* 0x16d70  847
                       ?ApplyMarkSetToPage@DocumentMarks@@YAXAEAVPage@ArtDoc@@AEBVpath@filesystem@boost@@_NPEAV?$set@_KU?$less@_K@std@@V?$allocator@_K@2@@std@@@Z
                        */
  local_38 = DAT_180418e00 ^ (ulonglong)auStackY_d8;
  pPVar2 = ArtDoc::Page::GetContent(param_1);
  ArtDoc::Content::GetDocument((Content *)pPVar2);
  FUN_180017010(local_98);
  if (local_98[0] == (Document *)0x0) {
    if (param_3) {
      DeleteMarks(param_1,false);
    }
  }
  else {
    pPVar2 = ArtDoc::Page::GetContent(param_1);
    pDVar3 = ArtDoc::Content::GetDocument((Content *)pPVar2);
    pCVar4 = GetChangeTracker(pDVar3);
    pPVar2 = ArtDoc::Page::GetContent(param_1);
    FUN_180015f90(*(undefined8 *)(pCVar4 + 0xf0),pPVar2);
    pPVar2 = ArtDoc::Page::GetContent(param_1);
    pDVar3 = ArtDoc::Content::GetDocument((Content *)pPVar2);
    ArtDoc::ActionGroupCreator::ActionGroupCreator(local_88,pDVar3,false,false);
    puVar5 = (undefined8 *)ArtDoc::Document::GetPagesBegin(local_98[0]);
    pPVar1 = *(Page **)*puVar5;
    if (param_3) {
      DeleteMarks(param_1,false);
    }
    CopyMarksToPage(pPVar1,param_1,true,
                    (set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
                     *)0x0,(set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
                            *)0x0,param_4,true);
    pPVar2 = ArtDoc::Page::GetContent(param_1);
    pDVar3 = ArtDoc::Content::GetDocument((Content *)pPVar2);
    pPVar2 = ArtDoc::Page::GetContent(param_1);
    _Var6 = ArtDoc::Content::GetID((Content *)pPVar2);
    pPVar2 = ArtDoc::Page::GetContent(param_1);
    pDVar7 = ArtDoc::Content::GetDocument((Content *)pPVar2);
    this = GetDynamicMarksController(pDVar7);
    local_78 = std::
               _Func_impl_no_alloc<`void___cdecl_DocumentMarks::ApplyMarkSetToPage(ArtDoc::Page&___ptr64,boost::filesystem::path_const&___ptr64,bool,std::set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_>*___ptr64)'::`5'::<lambda_1>,void>
               ::vftable;
    local_40 = &local_78;
    local_70 = pDVar3;
    local_68 = _Var6;
    DynamicMarksController::RequestExtraRegeneration(this,(function<void___cdecl(void)> *)&local_78)
    ;
    if (local_40 != (undefined ***)0x0) {
      (*(code *)(*local_40)[4])
                (local_40,CONCAT71((int7)((ulonglong)&local_78 >> 8),local_40 != &local_78));
    }
    ArtDoc::ActionGroupCreator::~ActionGroupCreator(local_88);
  }
  if (local_98[0] != (Document *)0x0) {
    ArtDoc::Document::~Document(local_98[0]);
    free(local_98[0]);
  }
  return;
}


