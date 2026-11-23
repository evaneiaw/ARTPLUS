// DocumentMarks.dll - decompiled trim/cut mark functions
// program: DocumentMarks.dll base: 180000000

// ---------------------------------------------------------------
// FUNC 180016b50 ApplyMarkSet
// signature: void ApplyMarkSet(Document * param_1, path * param_2, bool param_3, set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_> * param_4)
// ---------------------------------------------------------------

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



// ---------------------------------------------------------------
// FUNC 180016d70 ApplyMarkSetToPage
// signature: void ApplyMarkSetToPage(Page * param_1, path * param_2, bool param_3, set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_> * param_4)
// ---------------------------------------------------------------

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



// ---------------------------------------------------------------
// FUNC 180042960 CopyMarksToPage
// signature: bool CopyMarksToPage(Page * param_1, Page * param_2, bool param_3, set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_> * param_4, set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_> * param_5, set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_> * param_6, bool param_7)
// ---------------------------------------------------------------

/* bool __cdecl DocumentMarks::CopyMarksToPage(class ArtDoc::Page const & __ptr64,class ArtDoc::Page
   & __ptr64,bool,class std::set<class std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >,struct std::less<class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > >,class std::allocator<class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > *
   __ptr64,class std::set<class std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >,struct std::less<class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > >,class std::allocator<class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > *
   __ptr64,class std::set<unsigned __int64,struct std::less<unsigned __int64>,class
   std::allocator<unsigned __int64> > * __ptr64,bool) */

bool __cdecl
DocumentMarks::CopyMarksToPage
          (Page *param_1,Page *param_2,bool param_3,
          set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
          *param_4,set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
                   *param_5,
          set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_>
          *param_6,bool param_7)

{
  char cVar1;
  longlong *plVar2;
  CloneStrategy *this;
  longlong *plVar3;
  bool bVar4;
  uint uVar5;
  PageContent *pPVar6;
  PageContent *pPVar7;
  Document *pDVar8;
  ActionGroupCreator *pAVar9;
  Module *pMVar10;
  MarksModule *this_00;
  ContentObject *pCVar11;
  ContentObject *pCVar12;
  DynamicObjectController *this_01;
  byte bVar13;
  undefined1 uVar14;
  longlong *plVar15;
  longlong **pplVar16;
  void *local_c8;
  longlong local_c0;
  longlong *local_b8;
  undefined8 uStack_b0;
  void *local_a8;
  longlong local_a0;
  ActionGroupCreator *local_98;
  ActionGroupCreator *local_90;
  undefined **local_88;
  undefined **local_80;
  void *local_50 [2];
  CloneStrategy *local_40;
  
                    /* 0x42960  938
                       ?CopyMarksToPage@DocumentMarks@@YA_NAEBVPage@ArtDoc@@AEAV23@_NPEAV?$set@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@3PEAV?$set@_KU?$less@_K@std@@V?$allocator@_K@2@@5@2@Z
                        */
  pPVar6 = ArtDoc::Page::GetContent(param_1);
  local_b8 = (longlong *)0x0;
  uStack_b0 = 0;
  local_b8 = (longlong *)FUN_1802d6b50(0x30);
  *local_b8 = (longlong)local_b8;
  local_b8[1] = (longlong)local_b8;
  local_b8[2] = (longlong)local_b8;
  *(undefined2 *)(local_b8 + 3) = 0x101;
  FUN_1800446d0(&local_a8,pPVar6);
  pplVar16 = &local_b8;
  FUN_180044be0(&local_c8,pPVar6,&local_a8,param_2,pplVar16,param_4,param_5);
  if (local_c0 != 0) {
    pPVar6 = ArtDoc::Page::GetContent(param_2);
    FUN_1800465e0(param_1,&local_c8);
    pAVar9 = (ActionGroupCreator *)0x0;
    local_98 = (ActionGroupCreator *)0x0;
    pPVar7 = ArtDoc::Page::GetContent(param_1);
    pDVar8 = ArtDoc::Content::GetDocument((Content *)pPVar7);
    bVar4 = ArtDoc::Document::GetInfoFlag(pDVar8,2);
    if (!bVar4) {
      pAVar9 = (ActionGroupCreator *)FUN_1802d6b50(0x10);
      local_90 = pAVar9;
      if (pAVar9 == (ActionGroupCreator *)0x0) {
        pAVar9 = (ActionGroupCreator *)0x0;
      }
      else {
        pPVar7 = ArtDoc::Page::GetContent(param_2);
        pDVar8 = ArtDoc::Content::GetDocument((Content *)pPVar7);
        pAVar9 = (ActionGroupCreator *)
                 ArtDoc::ActionGroupCreator::ActionGroupCreator(pAVar9,pDVar8,false,false);
      }
      local_98 = pAVar9;
    }
    bVar13 = 0;
    pMVar10 = ArtDoc::FindModule(0x4d61726b);
    this_00 = (MarksModule *)
              __RTDynamicCast(pMVar10,0,&ArtDoc::Module::RTTI_Type_Descriptor,
                              &MarksModule::RTTI_Type_Descriptor,
                              (ulonglong)pplVar16 & 0xffffffff00000000);
    if (this_00 != (MarksModule *)0x0) {
      uVar5 = MarksModule::GetFeatures(this_00);
      bVar13 = (byte)(uVar5 >> 0xb) & 1;
    }
    if ((!param_3) || (bVar13 != 0)) {
      uVar14 = 0;
    }
    else {
      uVar14 = 1;
      FUN_180042ed0(param_1,param_2);
    }
    FUN_18003e300(&local_88,param_1,&local_c8,param_2,param_7,uVar14,param_6);
    pPVar7 = ArtDoc::Page::GetContent(param_1);
    ArtDoc::PageContent::Accept(pPVar7,(ConstVisitorBase *)&local_88);
    this = local_40;
    plVar15 = (longlong *)*local_b8;
    cVar1 = *(char *)((longlong)plVar15 + 0x19);
    while (cVar1 == '\0') {
      pCVar11 = ArtDoc::Content::GetObjectWithID((Content *)pPVar7,plVar15[4]);
      pCVar12 = ArtDoc::Content::GetObjectWithID((Content *)pPVar6,plVar15[5]);
      ArtDoc::CloneStrategy::AddClone(this,pCVar11,pCVar12);
      plVar2 = (longlong *)plVar15[2];
      if (*(char *)((longlong)plVar2 + 0x19) == '\0') {
        cVar1 = *(char *)(*plVar2 + 0x19);
        plVar15 = plVar2;
        plVar2 = (longlong *)*plVar2;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar2 + 0x19);
          plVar15 = plVar2;
          plVar2 = (longlong *)*plVar2;
        }
      }
      else {
        cVar1 = *(char *)(plVar15[1] + 0x19);
        plVar3 = (longlong *)plVar15[1];
        plVar2 = plVar15;
        while ((plVar15 = plVar3, cVar1 == '\0' && (plVar2 == (longlong *)plVar15[2]))) {
          cVar1 = *(char *)(plVar15[1] + 0x19);
          plVar3 = (longlong *)plVar15[1];
          plVar2 = plVar15;
        }
      }
      cVar1 = *(char *)((longlong)plVar15 + 0x19);
    }
    ArtDoc::CloneStrategy::RelinkDynamicObjects(this,true);
    pDVar8 = ArtDoc::Content::GetDocument((Content *)pPVar6);
    this_01 = ArtDoc::Document::GetDynamicObjects(pDVar8);
    ArtDoc::DynamicObjectController::InksChanged(this_01);
    local_88 = _anon_A573A748::MarksCloner::vftable;
    local_80 = _anon_A573A748::MarksCloner::vftable;
    if (local_40 != (CloneStrategy *)0x0) {
      ArtDoc::CloneStrategy::~CloneStrategy(local_40);
      free(local_40);
    }
    plVar15 = *(longlong **)((longlong)local_50[0] + 8);
    if (*(char *)((longlong)*(longlong **)((longlong)local_50[0] + 8) + 0x19) == '\0') {
      do {
        FUN_18003c8e0(local_50,local_50,plVar15[2]);
        plVar2 = (longlong *)*plVar15;
        free(plVar15);
        plVar15 = plVar2;
      } while (*(char *)((longlong)plVar2 + 0x19) == '\0');
    }
    free(local_50[0]);
    local_80 = ArtDoc::ConstVisitor<DocumentMarks::DynamicMark>::_vftable_;
    ArtDoc::ConstVisitorBase::~ConstVisitorBase((ConstVisitorBase *)&local_88);
    if (pAVar9 != (ActionGroupCreator *)0x0) {
      ArtDoc::ActionGroupCreator::~ActionGroupCreator(pAVar9);
      free(pAVar9);
    }
  }
  plVar15 = *(longlong **)((longlong)local_c8 + 8);
  if (*(char *)((longlong)*(longlong **)((longlong)local_c8 + 8) + 0x19) == '\0') {
    do {
      FUN_18003c700(&local_c8,&local_c8,plVar15[2]);
      plVar2 = (longlong *)*plVar15;
      free(plVar15);
      plVar15 = plVar2;
    } while (*(char *)((longlong)plVar2 + 0x19) == '\0');
  }
  free(local_c8);
  plVar15 = *(longlong **)((longlong)local_a8 + 8);
  if (*(char *)((longlong)plVar15 + 0x19) == '\0') {
    do {
      FUN_18003c700(&local_a8,&local_a8,plVar15[2]);
      plVar2 = (longlong *)*plVar15;
      free(plVar15);
      plVar15 = plVar2;
    } while (*(char *)((longlong)plVar2 + 0x19) == '\0');
  }
  free(local_a8);
  cVar1 = *(char *)(local_b8[1] + 0x19);
  plVar15 = (longlong *)local_b8[1];
  while (cVar1 == '\0') {
    FUN_18003c8e0(&local_b8,&local_b8,plVar15[2]);
    plVar2 = (longlong *)*plVar15;
    free(plVar15);
    plVar15 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x19);
  }
  free(local_b8);
  return local_c0 == local_a0;
}



// ---------------------------------------------------------------
// FUNC 1800522d0 ConstVisitor<DocumentMarks::CutMark>
// signature: undefined ConstVisitor<DocumentMarks::CutMark>(ConstVisitor<DocumentMarks::CutMark> * this, ConstVisitor<class_DocumentMarks::CutMark> * param_1)
// ---------------------------------------------------------------

/* public: __cdecl ArtDoc::ConstVisitor<class DocumentMarks::CutMark>::ConstVisitor<class
   DocumentMarks::CutMark>(class ArtDoc::ConstVisitor<class DocumentMarks::CutMark> const & __ptr64)
   __ptr64 */

ConstVisitor<DocumentMarks::CutMark> * __thiscall
ArtDoc::ConstVisitor<DocumentMarks::CutMark>::ConstVisitor<DocumentMarks::CutMark>
          (ConstVisitor<DocumentMarks::CutMark> *this,
          ConstVisitor<class_DocumentMarks::CutMark> *param_1)

{
                    /* 0x522d0  9  ??0?$ConstVisitor@VCutMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z
                       0x522d0  10  ??0?$ConstVisitor@VCutMark@DocumentMarks@@@ArtDoc@@QEAA@XZ */
  *(undefined ***)this = _vftable_;
  return this;
}



// ---------------------------------------------------------------
// FUNC 1800522e0 Visitor<DocumentMarks::CutMark>
// signature: undefined Visitor<DocumentMarks::CutMark>(Visitor<DocumentMarks::CutMark> * this, Visitor<class_DocumentMarks::CutMark> * param_1)
// ---------------------------------------------------------------

/* public: __cdecl ArtDoc::Visitor<class DocumentMarks::CutMark>::Visitor<class
   DocumentMarks::CutMark>(class ArtDoc::Visitor<class DocumentMarks::CutMark> const & __ptr64)
   __ptr64 */

Visitor<DocumentMarks::CutMark> * __thiscall
ArtDoc::Visitor<DocumentMarks::CutMark>::Visitor<DocumentMarks::CutMark>
          (Visitor<DocumentMarks::CutMark> *this,Visitor<class_DocumentMarks::CutMark> *param_1)

{
                    /* 0x522e0  91  ??0?$Visitor@VCutMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z
                       0x522e0  92  ??0?$Visitor@VCutMark@DocumentMarks@@@ArtDoc@@QEAA@XZ */
  *(undefined ***)this = _vftable_;
  return this;
}



// ---------------------------------------------------------------
// FUNC 1800522f0 CutMark
// signature: undefined CutMark(CutMark * this, CutMark * param_1, CloneStrategy * param_2)
// ---------------------------------------------------------------

/* protected: __cdecl DocumentMarks::CutMark::CutMark(class DocumentMarks::CutMark const &
   __ptr64,class ArtDoc::CloneStrategy & __ptr64) __ptr64 */

CutMark * __thiscall
DocumentMarks::CutMark::CutMark(CutMark *this,CutMark *param_1,CloneStrategy *param_2)

{
                    /* 0x522f0  183
                       ??0CutMark@DocumentMarks@@IEAA@AEBV01@AEAVCloneStrategy@ArtDoc@@@Z */
  DynamicMark::DynamicMark((DynamicMark *)this,(DynamicMark *)param_1,param_2);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this + 0x698) = *(undefined8 *)(param_1 + 0x698);
  return this;
}



// ---------------------------------------------------------------
// FUNC 180052340 CutMark
// signature: undefined CutMark(CutMark * this, bool param_1)
// ---------------------------------------------------------------

/* public: __cdecl DocumentMarks::CutMark::CutMark(bool) __ptr64 */

CutMark * __thiscall DocumentMarks::CutMark::CutMark(CutMark *this,bool param_1)

{
                    /* 0x52340  184  ??0CutMark@DocumentMarks@@QEAA@_N@Z */
  DynamicMark::DynamicMark((DynamicMark *)this,param_1,0xfd);
  *(undefined8 *)(this + 0x698) = 0;
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  return this;
}



// ---------------------------------------------------------------
// FUNC 180052380 ~ConstVisitor<DocumentMarks::CutMark>
// signature: void ~ConstVisitor<DocumentMarks::CutMark>(ConstVisitor<DocumentMarks::CutMark> * this)
// ---------------------------------------------------------------

/* protected: virtual __cdecl ArtDoc::ConstVisitor<class
   DocumentMarks::CutMark>::~ConstVisitor<class DocumentMarks::CutMark>(void) __ptr64 */

void __thiscall
ArtDoc::ConstVisitor<DocumentMarks::CutMark>::~ConstVisitor<DocumentMarks::CutMark>
          (ConstVisitor<DocumentMarks::CutMark> *this)

{
                    /* 0x52380  309  ??1?$ConstVisitor@VCutMark@DocumentMarks@@@ArtDoc@@MEAA@XZ */
  *(undefined ***)this = _vftable_;
  return;
}



// ---------------------------------------------------------------
// FUNC 180052390 ~Visitor<DocumentMarks::CutMark>
// signature: void ~Visitor<DocumentMarks::CutMark>(Visitor<DocumentMarks::CutMark> * this)
// ---------------------------------------------------------------

/* protected: virtual __cdecl ArtDoc::Visitor<class DocumentMarks::CutMark>::~Visitor<class
   DocumentMarks::CutMark>(void) __ptr64 */

void __thiscall
ArtDoc::Visitor<DocumentMarks::CutMark>::~Visitor<DocumentMarks::CutMark>
          (Visitor<DocumentMarks::CutMark> *this)

{
                    /* 0x52390  350  ??1?$Visitor@VCutMark@DocumentMarks@@@ArtDoc@@MEAA@XZ */
  *(undefined ***)this = _vftable_;
  return;
}



// ---------------------------------------------------------------
// FUNC 1800523a0 ~CutMark
// signature: void ~CutMark(CutMark * this)
// ---------------------------------------------------------------

/* public: virtual __cdecl DocumentMarks::CutMark::~CutMark(void) __ptr64 */

void __thiscall DocumentMarks::CutMark::~CutMark(CutMark *this)

{
                    /* 0x523a0  396  ??1CutMark@DocumentMarks@@UEAA@XZ */
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  DynamicMark::~DynamicMark((DynamicMark *)this);
  return;
}



// ---------------------------------------------------------------
// FUNC 180052590 Accept
// signature: void Accept(CutMark * this, VisitorBase * param_1)
// ---------------------------------------------------------------

/* public: virtual void __cdecl DocumentMarks::CutMark::Accept(class ArtDoc::VisitorBase & __ptr64)
   __ptr64 */

void __thiscall DocumentMarks::CutMark::Accept(CutMark *this,VisitorBase *param_1)

{
  char cVar1;
  longlong *plVar2;
  undefined1 local_res8 [8];
  
                    /* 0x52590  758  ?Accept@CutMark@DocumentMarks@@UEAAXAEAVVisitorBase@ArtDoc@@@Z
                        */
  plVar2 = (longlong *)
           __RTDynamicCast(param_1,0,&ArtDoc::VisitorBase::RTTI_Type_Descriptor,
                           &ArtDoc::Visitor<DocumentMarks::CutMark>::RTTI_Type_Descriptor,0);
  if (plVar2 == (longlong *)0x0) {
    plVar2 = (longlong *)
             __RTDynamicCast(param_1,0,&ArtDoc::VisitorBase::RTTI_Type_Descriptor,
                             &ArtDoc::Visitor<DocumentMarks::DynamicMark>::RTTI_Type_Descriptor,0);
    if (plVar2 == (longlong *)0x0) {
      cVar1 = FUN_180015e10(local_res8,this + -0x20,param_1);
      if (cVar1 == '\0') {
        (**(code **)(*(longlong *)this + 0x20))(this,param_1);
      }
    }
    else {
      cVar1 = (**(code **)*plVar2)(plVar2);
      if (cVar1 != '\0') {
        (**(code **)(*(longlong *)this + 0x20))(this,param_1);
      }
      (**(code **)(*plVar2 + 8))(plVar2,this + -0x20);
    }
  }
  else {
    cVar1 = (**(code **)*plVar2)(plVar2,this + -0x20);
    if (cVar1 != '\0') {
      (**(code **)(*(longlong *)this + 0x20))(this,param_1);
    }
    (**(code **)(*plVar2 + 8))(plVar2,this + -0x20);
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 180052690 Accept
// signature: void Accept(CutMark * this, ConstVisitorBase * param_1)
// ---------------------------------------------------------------

/* public: virtual void __cdecl DocumentMarks::CutMark::Accept(class ArtDoc::ConstVisitorBase &
   __ptr64)const __ptr64 */

void __thiscall DocumentMarks::CutMark::Accept(CutMark *this,ConstVisitorBase *param_1)

{
  char cVar1;
  longlong *plVar2;
  undefined1 local_res8 [8];
  
                    /* 0x52690  759
                       ?Accept@CutMark@DocumentMarks@@UEBAXAEAVConstVisitorBase@ArtDoc@@@Z */
  plVar2 = (longlong *)
           __RTDynamicCast(param_1,0,&ArtDoc::ConstVisitorBase::RTTI_Type_Descriptor,
                           &ArtDoc::ConstVisitor<DocumentMarks::CutMark>::RTTI_Type_Descriptor,0);
  if (plVar2 == (longlong *)0x0) {
    plVar2 = (longlong *)
             __RTDynamicCast(param_1,0,&ArtDoc::ConstVisitorBase::RTTI_Type_Descriptor,
                             &ArtDoc::ConstVisitor<DocumentMarks::DynamicMark>::RTTI_Type_Descriptor
                             ,0);
    if (plVar2 == (longlong *)0x0) {
      cVar1 = FUN_180015ed0(local_res8,this + -0x20,param_1);
      if (cVar1 == '\0') {
        (**(code **)(*(longlong *)this + 0x18))(this,param_1);
      }
    }
    else {
      cVar1 = (**(code **)*plVar2)(plVar2);
      if (cVar1 != '\0') {
        (**(code **)(*(longlong *)this + 0x18))(this,param_1);
      }
      (**(code **)(*plVar2 + 8))(plVar2,this + -0x20);
    }
  }
  else {
    cVar1 = (**(code **)*plVar2)(plVar2,this + -0x20);
    if (cVar1 != '\0') {
      (**(code **)(*(longlong *)this + 0x18))(this,param_1);
    }
    (**(code **)(*plVar2 + 8))(plVar2,this + -0x20);
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 180052790 Clone
// signature: CutMark * Clone(CutMark * this, CloneStrategy * param_1)
// ---------------------------------------------------------------

/* public: virtual class DocumentMarks::CutMark * __ptr64 __cdecl
   DocumentMarks::CutMark::Clone(class ArtDoc::CloneStrategy & __ptr64)const __ptr64 */

CutMark * __thiscall DocumentMarks::CutMark::Clone(CutMark *this,CloneStrategy *param_1)

{
  DynamicMark *this_00;
  
                    /* 0x52790  865
                       ?Clone@CutMark@DocumentMarks@@UEBAPEAV12@AEAVCloneStrategy@ArtDoc@@@Z */
  this_00 = (DynamicMark *)FUN_1802d6b50(0x6a0);
  if (this_00 == (DynamicMark *)0x0) {
    return (CutMark *)0x0;
  }
  DynamicMark::DynamicMark(this_00,(DynamicMark *)this,param_1);
  *(undefined ***)this_00 = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this_00 + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this_00 + 0x698) = *(undefined8 *)(this + 0x698);
  return (CutMark *)this_00;
}



// ---------------------------------------------------------------
// FUNC 180052820 PlaceCutMarkSymbol
// signature: void PlaceCutMarkSymbol(CutMark * this, ContentObject * param_1, CPoint * param_2, CPoint * param_3)
// ---------------------------------------------------------------

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* private: void __cdecl DocumentMarks::CutMark::PlaceCutMarkSymbol(class ArtDoc::ContentObject &
   __ptr64,struct dm::CPoint const & __ptr64,struct dm::CPoint const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::CutMark::PlaceCutMarkSymbol
          (CutMark *this,ContentObject *param_1,CPoint *param_2,CPoint *param_3)

{
  undefined1 auVar1 [12];
  double dVar2;
  double dVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  double local_e8;
  double local_e0;
  double local_d8;
  double local_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  double local_b8;
  double dStack_b0;
  undefined1 local_a8 [16];
  char local_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  double local_68;
  double local_60;
  undefined1 local_38;
  
                    /* 0x52820  1417
                       ?PlaceCutMarkSymbol@CutMark@DocumentMarks@@AEAAXAEAVContentObject@ArtDoc@@AEBUCPoint@dm@@1@Z
                        */
  auVar4._0_8_ = *(double *)param_3 * 360000.0;
  auVar4._8_8_ = *(double *)(param_3 + 8) * 360000.0;
  auVar4 = divpd(auVar4,_DAT_1803082e0);
  auVar5 = auVar4 >> 0x40;
  dVar2 = atan2(auVar4._8_8_ - (*(double *)(param_2 + 8) * 360000.0) / 127.0,
                auVar4._0_8_ - (*(double *)param_2 * 360000.0) / 127.0);
  dVar2 = dVar2 + _DAT_180488498;
  dVar3 = cos(dVar2);
  local_e0 = sin(dVar2);
  local_d8 = -local_e0;
  local_c8 = 0;
  uStack_c0 = 0;
  local_e8 = dVar3;
  local_d0 = dVar3;
  DocumentEdit::Transform
            ((Transformable *)param_1,
             (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_e8,7);
  GetBoundingBoxForPositioning((ContentObject *)&local_b8);
  if (local_90 == '\0') {
    local_b8 = 0.0;
    dStack_b0 = 0.0;
    local_38 = 1;
    local_a8 = ZEXT816(0);
  }
  dVar2 = *(double *)param_2;
  auVar1._4_8_ = auVar5._8_8_;
  auVar1._0_4_ = local_a8._4_4_;
  auVar5._0_8_ = auVar1._0_8_ << 0x20;
  auVar5._8_4_ = local_a8._8_4_;
  auVar5._12_4_ = local_a8._12_4_;
  dVar3 = auVar5._8_8_;
  if (dVar2 == *(double *)param_3) {
    local_68 = local_a8._0_8_ * 0.5;
    local_60 = 0.0;
    if (*(double *)(param_2 + 8) <= *(double *)(param_3 + 8) &&
        *(double *)(param_3 + 8) != *(double *)(param_2 + 8)) {
      local_60 = dVar3;
    }
  }
  else {
    local_60 = dVar3 * 0.5;
    local_68 = 0.0;
    if (*(double *)param_3 < dVar2) {
      local_68 = local_a8._0_8_;
    }
  }
  local_88 = 0x3ff0000000000000;
  uStack_80 = 0;
  local_78 = 0;
  uStack_70 = 0x3ff0000000000000;
  local_68 = (dVar2 * 2834.645669291339 - local_b8) - local_68;
  local_60 = (*(double *)(param_2 + 8) * 2834.645669291339 - (dVar3 + dStack_b0)) + local_60;
  DocumentEdit::Transform
            ((Transformable *)param_1,
             (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_88,7);
  return;
}



// ---------------------------------------------------------------
// FUNC 180052a40 getMarkType
// signature: basic_string_view<char,std::char_traits<char>_> getMarkType(CutMark * this)
// ---------------------------------------------------------------

/* public: virtual class std::basic_string_view<char,struct std::char_traits<char> > __cdecl
   DocumentMarks::CutMark::getMarkType(void)const __ptr64 */

void __thiscall DocumentMarks::CutMark::getMarkType(CutMark *this)

{
  undefined8 *in_RDX;
  
                    /* 0x52a40  1956
                       ?getMarkType@CutMark@DocumentMarks@@UEBA?AV?$basic_string_view@DU?$char_traits@D@std@@@std@@XZ
                        */
  *in_RDX = "AIDynamicMarks-CutMark";
  in_RDX[1] = 0x16;
  return;
}



// ---------------------------------------------------------------
// FUNC 180052a50 parsePdfPropertiesDict
// signature: bool parsePdfPropertiesDict(CutMark * this, map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::ContentObject*___ptr64,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,ArtDoc::ContentObject*___ptr64>_>_> * param_1)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: virtual bool __cdecl DocumentMarks::CutMark::parsePdfPropertiesDict(class std::map<class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class
   ArtDoc::ContentObject * __ptr64,struct std::less<class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair<class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class
   ArtDoc::ContentObject * __ptr64> > > const & __ptr64) __ptr64 */

bool __thiscall
DocumentMarks::CutMark::parsePdfPropertiesDict
          (CutMark *this,
          map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::ContentObject*___ptr64,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,ArtDoc::ContentObject*___ptr64>_>_>
          *param_1)

{
  bool bVar1;
  int iVar2;
  Dictionary *this_00;
  Content *pCVar3;
  char *_Memory;
  void *pvVar4;
  longlong lVar5;
  longlong lVar6;
  double dVar7;
  undefined1 auStack_88 [32];
  char *local_68;
  undefined8 uStack_60;
  undefined *local_58;
  ulonglong uStack_50;
  void *local_48;
  undefined8 uStack_40;
  undefined8 local_38;
  ulonglong uStack_30;
  ulonglong local_28;
  
                    /* 0x52a50  2128
                       ?parsePdfPropertiesDict@CutMark@DocumentMarks@@UEAA_NAEBV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEAVContentObject@ArtDoc@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEAVContentObject@ArtDoc@@@std@@@2@@std@@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_88;
  bVar1 = DynamicMark::parsePdfPropertiesDict((DynamicMark *)this,param_1);
  if (bVar1) {
    local_68 = (char *)0x0;
    uStack_60 = 0;
    local_58 = (undefined *)0x0;
    uStack_50 = 0;
    lVar5 = -1;
    lVar6 = -1;
    do {
      lVar6 = lVar6 + 1;
    } while (PTR_s_DM_CutMarkParams_1804189a8[lVar6] != '\0');
    FUN_180010070(&local_68);
    this_00 = ArtDoc::Dictionary::GetDictionaryValue
                        ((Dictionary *)(this + 0x2d0),
                         (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                         &local_68);
    if (0xf < uStack_50) {
      _Memory = local_68;
      if ((0xfff < uStack_50 + 1) &&
         (_Memory = *(char **)(local_68 + -8), (char *)0x1f < local_68 + (-8 - (longlong)_Memory)))
      {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
    local_58 = (undefined *)0x0;
    uStack_50 = 0xf;
    local_68 = (char *)((ulonglong)local_68 & 0xffffffffffffff00);
    local_48 = (void *)0x0;
    uStack_40 = 0;
    local_38 = 0;
    uStack_30 = 0;
    lVar6 = -1;
    do {
      lVar6 = lVar6 + 1;
    } while (PTR_s_DM_CutMarkParams_Version_180418b10[lVar6] != '\0');
    FUN_180010070(&local_48);
    iVar2 = ArtDoc::Dictionary::GetIntegerValue
                      (this_00,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                               &local_48);
    if (0xf < uStack_30) {
      pvVar4 = local_48;
      if ((0xfff < uStack_30 + 1) &&
         (pvVar4 = *(void **)((longlong)local_48 + -8),
         0x1f < (ulonglong)((longlong)local_48 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    if (iVar2 < 2) {
      local_48 = (void *)0x0;
      uStack_40 = 0;
      local_38 = 0;
      uStack_30 = 0;
      do {
        lVar5 = lVar5 + 1;
      } while (PTR_s_DM_CutMarkParams_Offset_180418b00[lVar5] != '\0');
      FUN_180010070(&local_48,PTR_s_DM_CutMarkParams_Offset_180418b00,lVar5);
      dVar7 = ArtDoc::Dictionary::GetFloatValue
                        (this_00,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                 &local_48);
      *(double *)(this + 0x698) = dVar7;
      if (0xf < uStack_30) {
        pvVar4 = local_48;
        if ((0xfff < uStack_30 + 1) &&
           (pvVar4 = *(void **)((longlong)local_48 + -8),
           0x1f < (ulonglong)((longlong)local_48 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar4);
      }
      return true;
    }
    local_68 = "CutMark";
    uStack_60 = 7;
    pCVar3 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
    FUN_180103b00(pCVar3,iVar2,1,&local_68);
  }
  return false;
}



// ---------------------------------------------------------------
// FUNC 180052ca0 regenerateMarkImp
// signature: void regenerateMarkImp(CutMark * this)
// ---------------------------------------------------------------

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: virtual void __cdecl DocumentMarks::CutMark::regenerateMarkImp(void) __ptr64 */

void __thiscall DocumentMarks::CutMark::regenerateMarkImp(CutMark *this)

{
  longlong *plVar1;
  int *piVar2;
  ContentObject *this_00;
  CPoint *pCVar3;
  void *pvVar4;
  int iVar5;
  ContentObject *pCVar6;
  longlong lVar7;
  longlong *plVar8;
  Content *this_01;
  Document *pDVar9;
  basic_ostream<char,std::char_traits<char>_> *pbVar10;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar11;
  double *pdVar12;
  undefined8 uVar13;
  int iVar14;
  ulonglong uVar15;
  longlong *plVar16;
  ulonglong uVar17;
  void *_Memory;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  longlong local_res8;
  double local_res10;
  undefined1 local_1d8 [16];
  undefined1 local_1c8 [16];
  undefined8 local_1b8;
  void *local_1b0;
  longlong *plStack_1a8;
  longlong *local_1a0;
  undefined **local_198;
  longlong local_190;
  longlong lStack_188;
  undefined8 local_180;
  undefined1 local_178 [8];
  double local_170;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 uStack_158;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined8 local_140;
  char local_138;
  undefined1 local_130 [16];
  undefined1 local_110;
  undefined7 uStack_10f;
  CloneStrategy local_d8 [160];
  
                    /* 0x52ca0  2179  ?regenerateMarkImp@CutMark@DocumentMarks@@MEAAXXZ */
  pCVar6 = DynamicObject::getPositionRefObject((DynamicObject *)this);
  if (*(longlong *)(this + 0x2c0) != 0) {
    local_1b0 = (void *)0x0;
    plStack_1a8 = (longlong *)0x0;
    iVar14 = 0;
    plVar16 = (longlong *)0x0;
    local_1a0 = (longlong *)0x0;
    lVar7 = __RTDynamicCast(*(longlong *)(this + 0x2c0),0,
                            &ArtDoc::ContentObject::RTTI_Type_Descriptor,
                            &ArtDoc::Group::RTTI_Type_Descriptor,0);
    if (lVar7 != 0) {
      lVar7 = *(longlong *)(lVar7 + 0x2c0);
                    /* WARNING: Read-only address (ram,0x0001803082f0) is written */
      for (plStack_1a8 = (longlong *)0x0; (lVar7 != 0 && (plStack_1a8 != (longlong *)0x0));
          plStack_1a8 = plStack_1a8 + 1) {
        *plStack_1a8 = lVar7;
        lVar7 = *(longlong *)(lVar7 + 8);
      }
      for (; lVar7 != 0; lVar7 = *(longlong *)(lVar7 + 8)) {
        local_res8 = lVar7;
        if (plStack_1a8 == plVar16) {
          FUN_18001de60(&local_1b0,plStack_1a8,&local_res8);
          plVar16 = local_1a0;
        }
        else {
          *plStack_1a8 = lVar7;
          plStack_1a8 = plStack_1a8 + 1;
        }
      }
    }
    plVar1 = plStack_1a8;
    this_00 = (ContentObject *)plStack_1a8[-1];
    GetBoundingBoxForPositioning((ContentObject *)&local_160);
    if (local_138 == '\0') {
      uStack_148 = 0;
      uStack_144 = 0;
      local_110 = 1;
      local_1d8 = ZEXT816(0);
      uVar18 = (undefined4)CONCAT71(uStack_10f,1);
      uVar19 = (undefined4)((uint7)uStack_10f >> 0x18);
    }
    else {
      local_1d8._8_8_ = uStack_158;
      local_1d8._0_8_ = local_160;
      uVar18 = (undefined4)local_140;
      uVar19 = (undefined4)((ulonglong)local_140 >> 0x20);
    }
    local_1b8 = CONCAT44(uVar19,uVar18);
    iVar5 = GetMarksDebugLevel();
    local_res8 = CONCAT44(local_res8._4_4_,iVar5);
    FUN_1802a1ce0(local_178);
    local_168 = *(undefined8 *)(this + 0x698);
    local_198 = dm::MarkPositionVector::vftable;
    local_190 = 0;
    lStack_188 = 0;
    local_180 = 0;
    local_170 = ((double)CONCAT44(uStack_144,uStack_148) * 127.0) / 360000.0;
    plVar8 = (longlong *)
             __RTDynamicCast(pCVar6,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                             &GridInterface::RTTI_Type_Descriptor,0);
    if (plVar8 == (longlong *)0x0) {
      pdVar12 = (double *)DynamicObject::getPositionRefBBox((DynamicObject *)this);
      auVar21._0_8_ = *pdVar12 * 127.0;
      auVar21._8_8_ = pdVar12[1] * 127.0;
      local_130 = divpd(auVar21,_DAT_1803082f0);
      local_1d8._8_8_ = local_130._8_8_ + (pdVar12[3] * 127.0) / 360000.0;
      local_1d8._0_8_ = local_130._0_8_;
      local_res10 = (double)local_130._0_8_;
      local_1c8._8_8_ = local_130._8_8_;
      local_1c8._0_8_ = (double)local_130._0_8_ + (pdVar12[2] * 127.0) / 360000.0;
      FUN_1802a26c0(local_178,local_1d8,&local_198);
    }
    else {
      (**(code **)(*plVar8 + 8))(plVar8,local_d8);
      if (2 < iVar5) {
        FUN_18001b3e0(cout_exref,"gridParams:\n");
        FUN_18029f2e0(cout_exref,local_d8);
      }
      FUN_1802a2780(local_178,local_d8,&local_198);
    }
    uVar17 = 0;
    uVar15 = lStack_188 - local_190 >> 3;
    if (uVar15 != 0) {
      do {
        this_01 = ArtDoc::ContentObject::GetContent(this_00);
        pDVar9 = ArtDoc::Content::GetDocument(this_01);
        ArtDoc::CloneStrategy::CloneStrategy(local_d8,pDVar9,1);
        pCVar6 = (ContentObject *)(**(code **)(*(longlong *)this_00 + 8))(this_00,local_d8);
        pCVar6 = DocumentEdit::InsertNewObjectAfter(pCVar6,this_00,true);
        pCVar3 = *(CPoint **)(local_190 + uVar17 * 8);
        PlaceCutMarkSymbol(this,pCVar6,pCVar3,pCVar3 + 0x10);
        ArtDoc::CloneStrategy::~CloneStrategy(local_d8);
        uVar17 = uVar17 + 1;
      } while (uVar17 < uVar15);
    }
    if (2 < (int)local_res8) {
      FUN_18001b3e0(cout_exref," Cut Mark update at \n");
      uVar17 = lStack_188 - local_190 >> 3;
      uVar15 = 0;
      if (uVar17 != 0) {
        do {
          pdVar12 = *(double **)(local_190 + uVar15 * 8);
          pbVar10 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(cout_exref,&DAT_180308290);
          iVar14 = iVar14 + 1;
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar10,iVar14);
          pbVar10 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(pbVar11,&DAT_180306bac);
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar10,*pdVar12);
          pbVar10 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(pbVar11,&DAT_180307580);
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar10,pdVar12[1])
          ;
          pbVar10 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(pbVar11,"] -> [");
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar10,pdVar12[2])
          ;
          pbVar10 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(pbVar11,&DAT_180307580);
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar10,pdVar12[3])
          ;
          FUN_18001b3e0(pbVar11,&DAT_18030828c);
          uVar15 = uVar15 + 1;
        } while (uVar15 < uVar17);
      }
      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_18003dae0);
      pdVar12 = (double *)DynamicObject::getPositionRefBBox((DynamicObject *)this);
      auVar20._0_8_ = *pdVar12 * 127.0;
      auVar20._8_8_ = pdVar12[1] * 127.0;
      local_1d8 = divpd(auVar20,_DAT_1803082f0);
      auVar22._0_8_ = pdVar12[2] * 127.0;
      auVar22._8_8_ = pdVar12[3] * 127.0;
      local_1c8 = divpd(auVar22,_DAT_1803082f0);
      local_1b8 = CONCAT71(local_1b8._1_7_,*(undefined1 *)(pdVar12 + 4));
      uVar13 = FUN_18001b3e0(cout_exref,"GridBbox mm:");
      uVar13 = FUN_18001dcb0(uVar13,local_1d8);
      FUN_18001b3e0(uVar13,&DAT_18030544c);
    }
    pvVar4 = local_1b0;
    uVar15 = 0;
    uVar17 = (longlong)plVar1 - (longlong)local_1b0 >> 3;
    if (uVar17 != 0) {
      do {
        DocumentEdit::ExtractObjectFromParent((ContentObject *)local_1d8);
        uVar13 = local_1d8._8_8_;
        if ((longlong *)local_1d8._8_8_ != (longlong *)0x0) {
          LOCK();
          plVar1 = (longlong *)(local_1d8._8_8_ + 8);
          lVar7 = *plVar1;
          *(int *)plVar1 = (int)*plVar1 + -1;
          UNLOCK();
          if ((int)lVar7 == 1) {
            (*(code *)**(undefined8 **)local_1d8._8_8_)(local_1d8._8_8_);
            LOCK();
            piVar2 = (int *)(uVar13 + 0xc);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 == 1) {
              (**(code **)(*(longlong *)uVar13 + 8))(uVar13);
            }
          }
        }
        uVar15 = uVar15 + 1;
      } while (uVar15 < uVar17);
    }
    DynamicObject::applyColor((DynamicObject *)this,(ContentObject *)this);
    FUN_18004a7b0(&local_198);
    FUN_1802a0fa0(local_178);
    if (pvVar4 != (void *)0x0) {
      _Memory = pvVar4;
      if ((0xfff < ((longlong)plVar16 - (longlong)pvVar4 & 0xfffffffffffffff8U)) &&
         (_Memory = *(void **)((longlong)pvVar4 + -8),
         0x1f < (ulonglong)((longlong)pvVar4 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800ab7e0 ConstVisitor<DocumentMarks::PDFPlusCutMark>
// signature: undefined ConstVisitor<DocumentMarks::PDFPlusCutMark>(ConstVisitor<DocumentMarks::PDFPlusCutMark> * this, ConstVisitor<class_DocumentMarks::PDFPlusCutMark> * param_1)
// ---------------------------------------------------------------

/* public: __cdecl ArtDoc::ConstVisitor<class DocumentMarks::PDFPlusCutMark>::ConstVisitor<class
   DocumentMarks::PDFPlusCutMark>(class ArtDoc::ConstVisitor<class DocumentMarks::PDFPlusCutMark>
   const & __ptr64) __ptr64 */

ConstVisitor<DocumentMarks::PDFPlusCutMark> * __thiscall
ArtDoc::ConstVisitor<DocumentMarks::PDFPlusCutMark>::ConstVisitor<DocumentMarks::PDFPlusCutMark>
          (ConstVisitor<DocumentMarks::PDFPlusCutMark> *this,
          ConstVisitor<class_DocumentMarks::PDFPlusCutMark> *param_1)

{
                    /* 0xab7e0  29
                       ??0?$ConstVisitor@VPDFPlusCutMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z
                       0xab7e0  30
                       ??0?$ConstVisitor@VPDFPlusCutMark@DocumentMarks@@@ArtDoc@@QEAA@XZ */
  *(undefined ***)this = _vftable_;
  return this;
}



// ---------------------------------------------------------------
// FUNC 1800ac310 Visitor<DocumentMarks::PDFPlusCutMark>
// signature: undefined Visitor<DocumentMarks::PDFPlusCutMark>(Visitor<DocumentMarks::PDFPlusCutMark> * this, Visitor<class_DocumentMarks::PDFPlusCutMark> * param_1)
// ---------------------------------------------------------------

/* public: __cdecl ArtDoc::Visitor<class DocumentMarks::PDFPlusCutMark>::Visitor<class
   DocumentMarks::PDFPlusCutMark>(class ArtDoc::Visitor<class DocumentMarks::PDFPlusCutMark> const &
   __ptr64) __ptr64 */

Visitor<DocumentMarks::PDFPlusCutMark> * __thiscall
ArtDoc::Visitor<DocumentMarks::PDFPlusCutMark>::Visitor<DocumentMarks::PDFPlusCutMark>
          (Visitor<DocumentMarks::PDFPlusCutMark> *this,
          Visitor<class_DocumentMarks::PDFPlusCutMark> *param_1)

{
                    /* 0xac310  111
                       ??0?$Visitor@VPDFPlusCutMark@DocumentMarks@@@ArtDoc@@QEAA@AEBV01@@Z
                       0xac310  112  ??0?$Visitor@VPDFPlusCutMark@DocumentMarks@@@ArtDoc@@QEAA@XZ */
  *(undefined ***)this = _vftable_;
  return this;
}



// ---------------------------------------------------------------
// FUNC 1800ac590 ~ConstVisitor<DocumentMarks::PDFPlusCutMark>
// signature: void ~ConstVisitor<DocumentMarks::PDFPlusCutMark>(ConstVisitor<DocumentMarks::PDFPlusCutMark> * this)
// ---------------------------------------------------------------

/* protected: virtual __cdecl ArtDoc::ConstVisitor<class
   DocumentMarks::PDFPlusCutMark>::~ConstVisitor<class DocumentMarks::PDFPlusCutMark>(void) __ptr64
    */

void __thiscall
ArtDoc::ConstVisitor<DocumentMarks::PDFPlusCutMark>::~ConstVisitor<DocumentMarks::PDFPlusCutMark>
          (ConstVisitor<DocumentMarks::PDFPlusCutMark> *this)

{
                    /* 0xac590  319
                       ??1?$ConstVisitor@VPDFPlusCutMark@DocumentMarks@@@ArtDoc@@MEAA@XZ */
  *(undefined ***)this = _vftable_;
  return;
}



// ---------------------------------------------------------------
// FUNC 1800ac5f0 ~Visitor<DocumentMarks::PDFPlusCutMark>
// signature: void ~Visitor<DocumentMarks::PDFPlusCutMark>(Visitor<DocumentMarks::PDFPlusCutMark> * this)
// ---------------------------------------------------------------

/* protected: virtual __cdecl ArtDoc::Visitor<class DocumentMarks::PDFPlusCutMark>::~Visitor<class
   DocumentMarks::PDFPlusCutMark>(void) __ptr64 */

void __thiscall
ArtDoc::Visitor<DocumentMarks::PDFPlusCutMark>::~Visitor<DocumentMarks::PDFPlusCutMark>
          (Visitor<DocumentMarks::PDFPlusCutMark> *this)

{
                    /* 0xac5f0  360  ??1?$Visitor@VPDFPlusCutMark@DocumentMarks@@@ArtDoc@@MEAA@XZ */
  *(undefined ***)this = _vftable_;
  return;
}



// ---------------------------------------------------------------
// FUNC 1800acd30 Accept
// signature: void Accept(PDFPlusCutMark * this, VisitorBase * param_1)
// ---------------------------------------------------------------

/* public: virtual void __cdecl DocumentMarks::PDFPlusCutMark::Accept(class ArtDoc::VisitorBase &
   __ptr64) __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::Accept(PDFPlusCutMark *this,VisitorBase *param_1)

{
  char cVar1;
  longlong *plVar2;
  undefined1 local_res8 [8];
  
                    /* 0xacd30  778
                       ?Accept@PDFPlusCutMark@DocumentMarks@@UEAAXAEAVVisitorBase@ArtDoc@@@Z */
  plVar2 = (longlong *)
           __RTDynamicCast(param_1,0,&ArtDoc::VisitorBase::RTTI_Type_Descriptor,
                           &ArtDoc::Visitor<DocumentMarks::PDFPlusCutMark>::RTTI_Type_Descriptor,0);
  if (plVar2 == (longlong *)0x0) {
    plVar2 = (longlong *)
             __RTDynamicCast(param_1,0,&ArtDoc::VisitorBase::RTTI_Type_Descriptor,
                             &ArtDoc::Visitor<DocumentMarks::DynamicMark>::RTTI_Type_Descriptor,0);
    if (plVar2 == (longlong *)0x0) {
      cVar1 = FUN_180015e10(local_res8,this + -0x20,param_1);
      if (cVar1 == '\0') {
        (**(code **)(*(longlong *)this + 0x20))(this,param_1);
      }
    }
    else {
      cVar1 = (**(code **)*plVar2)(plVar2);
      if (cVar1 != '\0') {
        (**(code **)(*(longlong *)this + 0x20))(this,param_1);
      }
      (**(code **)(*plVar2 + 8))(plVar2,this + -0x20);
    }
  }
  else {
    cVar1 = (**(code **)*plVar2)(plVar2,this + -0x20);
    if (cVar1 != '\0') {
      (**(code **)(*(longlong *)this + 0x20))(this,param_1);
    }
    (**(code **)(*plVar2 + 8))(plVar2,this + -0x20);
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800ace30 Accept
// signature: void Accept(PDFPlusCutMark * this, ConstVisitorBase * param_1)
// ---------------------------------------------------------------

/* public: virtual void __cdecl DocumentMarks::PDFPlusCutMark::Accept(class ArtDoc::ConstVisitorBase
   & __ptr64)const __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::Accept(PDFPlusCutMark *this,ConstVisitorBase *param_1)

{
  char cVar1;
  longlong *plVar2;
  undefined1 local_res8 [8];
  
                    /* 0xace30  779
                       ?Accept@PDFPlusCutMark@DocumentMarks@@UEBAXAEAVConstVisitorBase@ArtDoc@@@Z */
  plVar2 = (longlong *)
           __RTDynamicCast(param_1,0,&ArtDoc::ConstVisitorBase::RTTI_Type_Descriptor,
                           &ArtDoc::ConstVisitor<DocumentMarks::PDFPlusCutMark>::
                            RTTI_Type_Descriptor,0);
  if (plVar2 == (longlong *)0x0) {
    plVar2 = (longlong *)
             __RTDynamicCast(param_1,0,&ArtDoc::ConstVisitorBase::RTTI_Type_Descriptor,
                             &ArtDoc::ConstVisitor<DocumentMarks::DynamicMark>::RTTI_Type_Descriptor
                             ,0);
    if (plVar2 == (longlong *)0x0) {
      cVar1 = FUN_180015ed0(local_res8,this + -0x20,param_1);
      if (cVar1 == '\0') {
        (**(code **)(*(longlong *)this + 0x18))(this,param_1);
      }
    }
    else {
      cVar1 = (**(code **)*plVar2)(plVar2);
      if (cVar1 != '\0') {
        (**(code **)(*(longlong *)this + 0x18))(this,param_1);
      }
      (**(code **)(*plVar2 + 8))(plVar2,this + -0x20);
    }
  }
  else {
    cVar1 = (**(code **)*plVar2)(plVar2,this + -0x20);
    if (cVar1 != '\0') {
      (**(code **)(*(longlong *)this + 0x18))(this,param_1);
    }
    (**(code **)(*plVar2 + 8))(plVar2,this + -0x20);
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800ad540 SetCutMarkLineTypes
// signature: void SetCutMarkLineTypes(Content * param_1, function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> * param_2, vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_> * param_3)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkLineTypes(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusCutMark const & __ptr64)> const &
   __ptr64,class std::vector<enum DocumentMarks::PDFPlusCutMark::LineType,class std::allocator<enum
   DocumentMarks::PDFPlusCutMark::LineType> > const & __ptr64) */

void __cdecl
DocumentMarks::SetCutMarkLineTypes
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> *param_2,
          vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>
          *param_3)

{
  void *pvVar1;
  longlong *plVar2;
  Action *pAVar3;
  undefined8 uVar4;
  ActionList *pAVar5;
  void *_Memory;
  undefined1 auStack_148 [32];
  undefined ***local_128;
  undefined ***local_120;
  Action *local_118;
  Action *local_110;
  Action **local_108;
  undefined4 uStack_100;
  uint uStack_fc;
  longlong *local_f8;
  undefined1 local_f0 [24];
  undefined1 local_d8 [32];
  undefined **local_b8;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined ***local_80;
  undefined **local_78;
  code *local_70;
  longlong lStack_68;
  undefined ***local_40;
  ulonglong local_38;
  
                    /* 0xad540  1508
                       ?SetCutMarkLineTypes@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusCutMark@DocumentMarks@@@Z@std@@AEBV?$vector@W4LineType@PDFPlusCutMark@DocumentMarks@@V?$allocator@W4LineType@PDFPlusCutMark@DocumentMarks@@@std@@@5@@Z
                        */
  local_38 = DAT_180418e00 ^ (ulonglong)auStack_148;
  local_78 = std::
             _Func_impl_no_alloc<class_std::vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,std::vector<enum_DocumentMarks::PDFPlusCutMark::LineType,class_std::allocator<enum_DocumentMarks::PDFPlusCutMark::LineType>_>,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_68 = (ulonglong)uStack_fc << 0x20;
  local_70 = PDFPlusCutMark::GetLineTypes;
  local_40 = &local_78;
  local_108 = (Action **)PDFPlusCutMark::SetLineTypes;
  uStack_100 = 0;
  local_b8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(std::vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,std::vector<enum_DocumentMarks::PDFPlusCutMark::LineType,class_std::allocator<enum_DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64>
             ::vftable;
  local_b0 = 0x8013d130;
  uStack_ac = 1;
  uStack_a8 = 0;
  local_80 = &local_b8;
  plVar2 = (longlong *)FUN_1800ac3f0(local_f0,param_3);
  local_f8 = plVar2;
  pAVar3 = (Action *)FUN_1802d6b50(0x110);
  local_110 = pAVar3;
  if (pAVar3 == (Action *)0x0) {
    local_118 = (Action *)0x0;
  }
  else {
    uVar4 = FUN_1800ac3f0(local_d8,plVar2);
    local_120 = &local_78;
    local_128 = &local_b8;
    local_118 = (Action *)FUN_1800abc40(pAVar3,param_1,param_2,uVar4);
  }
  local_108 = &local_118;
  pAVar5 = ArtDoc::Action::GetActionList(local_118);
  local_110 = local_118;
  local_118 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar5,&local_110);
  if (local_118 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_118)(local_118,1);
  }
  pvVar1 = (void *)*plVar2;
  if (pvVar1 != (void *)0x0) {
    _Memory = pvVar1;
    if ((0xfff < (ulonglong)((plVar2[2] - (longlong)pvVar1 >> 2) * 4)) &&
       (_Memory = *(void **)((longlong)pvVar1 + -8),
       0x1f < (ulonglong)((longlong)pvVar1 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
    *plVar2 = 0;
    plVar2[1] = 0;
    plVar2[2] = 0;
  }
  if (local_80 != (undefined ***)0x0) {
    (*(code *)(*local_80)[4])
              (local_80,CONCAT71((int7)((ulonglong)&local_b8 >> 8),local_80 != &local_b8));
    local_80 = (undefined ***)0x0;
  }
  if (local_40 != (undefined ***)0x0) {
    (*(code *)(*local_40)[4])
              (local_40,CONCAT71((int7)((ulonglong)&local_78 >> 8),local_40 != &local_78));
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800ad730 SetCutMarkLineTypes
// signature: void SetCutMarkLineTypes(PDFPlusCutMark * param_1, vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_> * param_2)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkLineTypes(class DocumentMarks::PDFPlusCutMark &
   __ptr64,class std::vector<enum DocumentMarks::PDFPlusCutMark::LineType,class std::allocator<enum
   DocumentMarks::PDFPlusCutMark::LineType> > const & __ptr64) */

void __cdecl
DocumentMarks::SetCutMarkLineTypes
          (PDFPlusCutMark *param_1,
          vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>
          *param_2)

{
  void *pvVar1;
  longlong *plVar2;
  Action *pAVar3;
  undefined8 uVar4;
  ActionList *pAVar5;
  void *_Memory;
  undefined1 auStack_138 [32];
  undefined ***local_118;
  Action *local_108;
  Action *local_100;
  Action **local_f8;
  undefined4 uStack_f0;
  uint uStack_ec;
  longlong *local_e8;
  undefined1 local_e0 [24];
  undefined1 local_c8 [32];
  undefined **local_a8;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined ***local_70;
  undefined **local_68;
  code *local_60;
  longlong lStack_58;
  undefined ***local_30;
  ulonglong local_28;
  
                    /* 0xad730  1509
                       ?SetCutMarkLineTypes@DocumentMarks@@YAXAEAVPDFPlusCutMark@1@AEBV?$vector@W4LineType@PDFPlusCutMark@DocumentMarks@@V?$allocator@W4LineType@PDFPlusCutMark@DocumentMarks@@@std@@@std@@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_138;
  local_68 = std::
             _Func_impl_no_alloc<class_std::vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,std::vector<enum_DocumentMarks::PDFPlusCutMark::LineType,class_std::allocator<enum_DocumentMarks::PDFPlusCutMark::LineType>_>,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_58 = (ulonglong)uStack_ec << 0x20;
  local_60 = PDFPlusCutMark::GetLineTypes;
  local_30 = &local_68;
  local_f8 = (Action **)PDFPlusCutMark::SetLineTypes;
  uStack_f0 = 0;
  local_a8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(std::vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,std::vector<enum_DocumentMarks::PDFPlusCutMark::LineType,class_std::allocator<enum_DocumentMarks::PDFPlusCutMark::LineType>_>_const&___ptr64>
             ::vftable;
  local_a0 = 0x8013d130;
  uStack_9c = 1;
  uStack_98 = 0;
  local_70 = &local_a8;
  plVar2 = (longlong *)FUN_1800ac3f0(local_e0);
  local_e8 = plVar2;
  pAVar3 = (Action *)FUN_1802d6b50(0x110);
  local_100 = pAVar3;
  if (pAVar3 == (Action *)0x0) {
    local_108 = (Action *)0x0;
  }
  else {
    uVar4 = FUN_1800ac3f0(local_c8,plVar2);
    local_118 = &local_68;
    local_108 = (Action *)FUN_1800abe60(pAVar3,param_1,uVar4,&local_a8);
  }
  local_f8 = &local_108;
  pAVar5 = ArtDoc::Action::GetActionList(local_108);
  local_100 = local_108;
  local_108 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar5,&local_100);
  if (local_108 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_108)(local_108,1);
  }
  pvVar1 = (void *)*plVar2;
  if (pvVar1 != (void *)0x0) {
    _Memory = pvVar1;
    if ((0xfff < (ulonglong)((plVar2[2] - (longlong)pvVar1 >> 2) * 4)) &&
       (_Memory = *(void **)((longlong)pvVar1 + -8),
       0x1f < (ulonglong)((longlong)pvVar1 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
    *plVar2 = 0;
    plVar2[1] = 0;
    plVar2[2] = 0;
  }
  if (local_70 != (undefined ***)0x0) {
    (*(code *)(*local_70)[4])
              (local_70,CONCAT71((int7)((ulonglong)&local_a8 >> 8),local_70 != &local_a8));
    local_70 = (undefined ***)0x0;
  }
  if (local_30 != (undefined ***)0x0) {
    (*(code *)(*local_30)[4])
              (local_30,CONCAT71((int7)((ulonglong)&local_68 >> 8),local_30 != &local_68));
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800ad910 SetCutMarkOffset
// signature: void SetCutMarkOffset(Content * param_1, function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> * param_2, variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_> * param_3)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkOffset(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusCutMark const & __ptr64)> const &
   __ptr64,class std::variant<class YAGL::CoordinateBase<struct
   YAGL::MilliPointCoordinateSystem,1>,class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > > const & __ptr64) */

void __cdecl
DocumentMarks::SetCutMarkOffset
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> *param_2,
          variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
          *param_3)

{
  Action *pAVar1;
  ActionList *pAVar2;
  undefined1 auStack_168 [32];
  undefined ***local_148;
  undefined ***local_140;
  Action *local_138;
  Action *local_130;
  Action **local_128;
  undefined4 uStack_120;
  uint uStack_11c;
  undefined8 local_118 [4];
  char local_f8;
  undefined8 local_f0 [4];
  undefined1 local_d0;
  undefined8 *local_c8;
  undefined **local_b8;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined ***local_80;
  undefined **local_78;
  code *local_70;
  longlong lStack_68;
  undefined ***local_40;
  ulonglong local_38;
  
                    /* 0xad910  1510
                       ?SetCutMarkOffset@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusCutMark@DocumentMarks@@@Z@std@@AEBV?$variant@V?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@5@@Z
                        */
  local_38 = DAT_180418e00 ^ (ulonglong)auStack_168;
  local_78 = std::
             _Func_impl_no_alloc<class_std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,std::variant<class_YAGL::CoordinateBase<struct_YAGL::MilliPointCoordinateSystem,1>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_68 = (ulonglong)uStack_11c << 0x20;
  local_70 = PDFPlusBearerBar::GetOffset;
  local_40 = &local_78;
  local_128 = (Action **)PDFPlusCutMark::SetOffset;
  uStack_120 = 0;
  local_b8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,std::variant<class_YAGL::CoordinateBase<struct_YAGL::MilliPointCoordinateSystem,1>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_const&___ptr64>
             ::vftable;
  local_b0 = 0x8013d160;
  uStack_ac = 1;
  uStack_a8 = 0;
  local_80 = &local_b8;
  local_130 = (Action *)local_118;
  local_f8 = -1;
  if (param_3[0x20] !=
      (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
       )0xff) {
    if (param_3[0x20] ==
        (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
         )0x0) {
      local_118[0] = *(undefined8 *)param_3;
      local_f8 = '\0';
    }
    else {
      FUN_180011ca0(local_118,param_3);
      local_f8 = '\x01';
    }
  }
  local_c8 = local_118;
  pAVar1 = (Action *)FUN_1802d6b50(0x120);
  local_130 = pAVar1;
  if (pAVar1 == (Action *)0x0) {
    local_138 = (Action *)0x0;
  }
  else {
    local_128 = (Action **)local_f0;
    local_d0 = 0xff;
    if (local_f8 != -1) {
      if (local_f8 == '\0') {
        local_f0[0] = local_118[0];
        local_d0 = 0;
      }
      else {
        FUN_180011ca0(local_f0,local_118);
        local_d0 = 1;
      }
    }
    local_140 = &local_78;
    local_148 = &local_b8;
    local_138 = (Action *)FUN_1800ab7f0(pAVar1,param_1,param_2,local_f0);
  }
  local_128 = &local_138;
  pAVar2 = ArtDoc::Action::GetActionList(local_138);
  local_130 = local_138;
  local_138 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar2,&local_130);
  if (local_138 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_138)(local_138,1);
  }
  FUN_18006da40(local_118);
  if (local_80 != (undefined ***)0x0) {
    (*(code *)(*local_80)[4])
              (local_80,CONCAT71((int7)((ulonglong)&local_b8 >> 8),local_80 != &local_b8));
    local_80 = (undefined ***)0x0;
  }
  if (local_40 != (undefined ***)0x0) {
    (*(code *)(*local_40)[4])
              (local_40,CONCAT71((int7)((ulonglong)&local_78 >> 8),local_40 != &local_78));
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800adb10 SetCutMarkOffset
// signature: void SetCutMarkOffset(PDFPlusCutMark * param_1, variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_> * param_2)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkOffset(class DocumentMarks::PDFPlusCutMark & __ptr64,class
   std::variant<class YAGL::CoordinateBase<struct YAGL::MilliPointCoordinateSystem,1>,class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > const &
   __ptr64) */

void __cdecl
DocumentMarks::SetCutMarkOffset
          (PDFPlusCutMark *param_1,
          variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
          *param_2)

{
  undefined8 *puVar1;
  longlong *plVar2;
  ActionList *pAVar3;
  undefined1 auStack_118 [32];
  undefined ***local_f8;
  longlong local_e8;
  undefined8 *local_e0;
  code *local_d8;
  undefined4 uStack_d0;
  uint uStack_cc;
  undefined8 local_c8 [4];
  undefined1 local_a8;
  undefined8 *local_a0;
  undefined **local_98;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined ***local_60;
  undefined **local_58;
  code *local_50;
  longlong lStack_48;
  undefined ***local_20;
  ulonglong local_18;
  
                    /* 0xadb10  1511
                       ?SetCutMarkOffset@DocumentMarks@@YAXAEAVPDFPlusCutMark@1@AEBV?$variant@V?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@Z
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_118;
  local_58 = std::
             _Func_impl_no_alloc<class_std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,std::variant<class_YAGL::CoordinateBase<struct_YAGL::MilliPointCoordinateSystem,1>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_48 = (ulonglong)uStack_cc << 0x20;
  local_50 = PDFPlusBearerBar::GetOffset;
  local_20 = &local_58;
  local_d8 = PDFPlusCutMark::SetOffset;
  uStack_d0 = 0;
  local_98 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(std::variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,std::variant<class_YAGL::CoordinateBase<struct_YAGL::MilliPointCoordinateSystem,1>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_const&___ptr64>
             ::vftable;
  local_90 = 0x8013d160;
  uStack_8c = 1;
  uStack_88 = 0;
  local_60 = &local_98;
  local_e0 = local_c8;
  local_a8 = 0xff;
  if (param_2[0x20] !=
      (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
       )0xff) {
    if (param_2[0x20] ==
        (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
         )0x0) {
      local_c8[0] = *(undefined8 *)param_2;
      local_a8 = 0;
    }
    else {
      FUN_180011ca0(local_c8);
      local_a8 = 1;
    }
  }
  local_a0 = local_c8;
  local_f8 = &local_58;
  plVar2 = (longlong *)FUN_1800ab640(&local_e0,param_1,local_c8,&local_98);
  local_d8 = (code *)plVar2;
  pAVar3 = ArtDoc::Action::GetActionList((Action *)*plVar2);
  local_e8 = *plVar2;
  *plVar2 = 0;
  ArtDoc::ActionList::DoAction(pAVar3,&local_e8);
  puVar1 = (undefined8 *)*plVar2;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  FUN_18006da40(local_c8);
  if (local_60 != (undefined ***)0x0) {
    (*(code *)(*local_60)[4])
              (local_60,CONCAT71((int7)((ulonglong)&local_98 >> 8),local_60 != &local_98));
    local_60 = (undefined ***)0x0;
  }
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])
              (local_20,CONCAT71((int7)((ulonglong)&local_58 >> 8),local_20 != &local_58));
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800adca0 SetCutMarkOrientation
// signature: void SetCutMarkOrientation(Content * param_1, function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> * param_2, Orientation param_3)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkOrientation(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusCutMark const & __ptr64)> const &
   __ptr64,enum DocumentMarks::PDFPlusCutMark::Orientation) */

void __cdecl
DocumentMarks::SetCutMarkOrientation
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> *param_2,
          Orientation param_3)

{
  ActionList *pAVar1;
  undefined1 auStack_f8 [32];
  undefined ***local_d8;
  undefined ***local_d0;
  Action *local_c8;
  Action *local_c0;
  Action **local_b8;
  undefined4 uStack_b0;
  uint uStack_ac;
  undefined **local_a8;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined ***local_70;
  undefined **local_68;
  code *local_60;
  longlong lStack_58;
  undefined ***local_30;
  ulonglong local_28;
  
                    /* 0xadca0  1512
                       ?SetCutMarkOrientation@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusCutMark@DocumentMarks@@@Z@std@@W4Orientation@PDFPlusCutMark@1@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_f8;
  local_68 = std::
             _Func_impl_no_alloc<enum_DocumentMarks::PDFPlusCutMark::Orientation_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,DocumentMarks::PDFPlusCutMark::Orientation,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_58 = (ulonglong)uStack_ac << 0x20;
  local_60 = PDFPlusCutMark::GetOrientation;
  local_30 = &local_68;
  local_b8 = (Action **)PDFPlusCutMark::SetOrientation;
  uStack_b0 = 0;
  local_a8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(DocumentMarks::PDFPlusCutMark::Orientation)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,DocumentMarks::PDFPlusCutMark::Orientation_const&___ptr64>
             ::vftable;
  local_a0 = 0x8013d230;
  uStack_9c = 1;
  uStack_98 = 0;
  local_70 = &local_a8;
  local_c0 = (Action *)FUN_1802d6b50(0x100);
  if (local_c0 == (Action *)0x0) {
    local_c8 = (Action *)0x0;
  }
  else {
    local_d0 = &local_68;
    local_d8 = &local_a8;
    local_c8 = (Action *)FUN_1800abf90(local_c0,param_1,param_2,param_3);
  }
  local_b8 = &local_c8;
  pAVar1 = ArtDoc::Action::GetActionList(local_c8);
  local_c0 = local_c8;
  local_c8 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar1,&local_c0);
  if (local_c8 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_c8)(local_c8,1);
  }
  if (local_70 != (undefined ***)0x0) {
    (*(code *)(*local_70)[4])
              (local_70,CONCAT71((int7)((ulonglong)&local_a8 >> 8),local_70 != &local_a8));
    local_70 = (undefined ***)0x0;
  }
  if (local_30 != (undefined ***)0x0) {
    (*(code *)(*local_30)[4])
              (local_30,CONCAT71((int7)((ulonglong)&local_68 >> 8),local_30 != &local_68));
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800ade00 SetCutMarkOrientation
// signature: void SetCutMarkOrientation(PDFPlusCutMark * param_1, Orientation param_2)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkOrientation(class DocumentMarks::PDFPlusCutMark &
   __ptr64,enum DocumentMarks::PDFPlusCutMark::Orientation) */

void __cdecl DocumentMarks::SetCutMarkOrientation(PDFPlusCutMark *param_1,Orientation param_2)

{
  undefined1 auStack_d8 [32];
  Orientation local_b8 [2];
  code *local_b0;
  undefined4 uStack_a8;
  uint uStack_a4;
  undefined **local_98;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined ***local_60;
  undefined **local_58;
  code *local_50;
  longlong lStack_48;
  undefined ***local_20;
  ulonglong local_18;
  
                    /* 0xade00  1513
                       ?SetCutMarkOrientation@DocumentMarks@@YAXAEAVPDFPlusCutMark@1@W4Orientation@21@@Z
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_d8;
  local_58 = std::
             _Func_impl_no_alloc<enum_DocumentMarks::PDFPlusCutMark::Orientation_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,DocumentMarks::PDFPlusCutMark::Orientation,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_48 = (ulonglong)uStack_a4 << 0x20;
  local_50 = PDFPlusCutMark::GetOrientation;
  local_20 = &local_58;
  local_b0 = PDFPlusCutMark::SetOrientation;
  uStack_a8 = 0;
  local_98 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(DocumentMarks::PDFPlusCutMark::Orientation)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,DocumentMarks::PDFPlusCutMark::Orientation_const&___ptr64>
             ::vftable;
  local_90 = 0x8013d230;
  uStack_8c = 1;
  uStack_88 = 0;
  local_60 = &local_98;
  local_b8[0] = param_2;
  FUN_1800aa980(0x8013d230,local_b8,&local_98,&local_58);
  if (local_60 != (undefined ***)0x0) {
    (*(code *)(*local_60)[4])
              (local_60,CONCAT71((int7)((ulonglong)&local_98 >> 8),local_60 != &local_98));
    local_60 = (undefined ***)0x0;
  }
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])
              (local_20,CONCAT71((int7)((ulonglong)&local_58 >> 8),local_20 != &local_58));
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800adf00 SetCutMarkReferenceToAllStructuralDesignStations
// signature: void SetCutMarkReferenceToAllStructuralDesignStations(Content * param_1, function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> * param_2)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkReferenceToAllStructuralDesignStations(class
   ArtDoc::Content & __ptr64,class std::function<bool __cdecl(class DocumentMarks::PDFPlusCutMark
   const & __ptr64)> const & __ptr64) */

void __cdecl
DocumentMarks::SetCutMarkReferenceToAllStructuralDesignStations
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> *param_2)

{
  Action *pAVar1;
  undefined8 uVar2;
  ActionList *pAVar3;
  undefined1 auStack_218 [32];
  undefined ***local_1f8;
  undefined ***local_1f0;
  Action *local_1e8;
  Action *local_1e0;
  Action **local_1d8;
  undefined4 uStack_1d0;
  uint uStack_1cc;
  undefined1 *local_1c8;
  undefined1 local_1c0 [40];
  undefined1 local_198 [40];
  undefined1 local_170 [40];
  char local_148;
  char local_140;
  undefined1 local_138 [144];
  undefined **local_a8;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined ***local_70;
  undefined **local_68;
  code *local_60;
  longlong lStack_58;
  undefined ***local_30;
  ulonglong local_28;
  
                    /* 0xadf00  1514
                       ?SetCutMarkReferenceToAllStructuralDesignStations@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusCutMark@DocumentMarks@@@Z@std@@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_218;
  local_68 = std::
             _Func_impl_no_alloc<class_std::variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>_const&___ptr64_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,std::variant<class_std::variant<enum_ArtDoc::PageBox,unsigned___int64,struct_DocumentMarks::ProcessingStepLayer>,struct_DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_58 = (ulonglong)uStack_1cc << 0x20;
  local_60 = PDFPlusClipMark::GetHeight;
  local_30 = &local_68;
  local_1d8 = (Action **)PDFPlusCutMark::SetReferenceObject;
  uStack_1d0 = 0;
  local_a8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(std::variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>_const&___ptr64)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,std::variant<class_std::variant<enum_ArtDoc::PageBox,unsigned___int64,struct_DocumentMarks::ProcessingStepLayer>,struct_DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>_const&___ptr64>
             ::vftable;
  local_a0 = 0x8013d240;
  uStack_9c = 1;
  uStack_98 = 0;
  local_70 = &local_a8;
  local_140 = '\x01';
  local_1c8 = local_1c0;
  pAVar1 = (Action *)FUN_1802d6b50(0x180);
  local_1e0 = pAVar1;
  if (pAVar1 == (Action *)0x0) {
    local_1e8 = (Action *)0x0;
  }
  else {
    uVar2 = FUN_1800ac320(local_138,local_1c0);
    local_1f0 = &local_68;
    local_1f8 = &local_a8;
    local_1e8 = (Action *)FUN_1800aba10(pAVar1,param_1,param_2,uVar2);
  }
  local_1d8 = &local_1e8;
  pAVar3 = ArtDoc::Action::GetActionList(local_1e8);
  local_1e0 = local_1e8;
  local_1e8 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar3,&local_1e0);
  if (local_1e8 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_1e8)(local_1e8,1);
  }
  if ((((local_140 != -1) && (local_140 == '\0')) && (local_148 != -1)) &&
     ((local_148 != '\0' && (local_148 != '\x01')))) {
    FUN_180013c20(local_170);
    FUN_180013c20(local_198);
    FUN_180013c20(local_1c0);
  }
  if (local_70 != (undefined ***)0x0) {
    (*(code *)(*local_70)[4])
              (local_70,CONCAT71((int7)((ulonglong)&local_a8 >> 8),local_70 != &local_a8));
    local_70 = (undefined ***)0x0;
  }
  if (local_30 != (undefined ***)0x0) {
    (*(code *)(*local_30)[4])
              (local_30,CONCAT71((int7)((ulonglong)&local_68 >> 8),local_30 != &local_68));
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800ae100 SetCutMarkRepetition
// signature: void SetCutMarkRepetition(Content * param_1, function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> * param_2, Repetition param_3)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkRepetition(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusCutMark const & __ptr64)> const &
   __ptr64,enum DocumentMarks::PDFPlusCutMark::Repetition) */

void __cdecl
DocumentMarks::SetCutMarkRepetition
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusCutMark_const&___ptr64)> *param_2,
          Repetition param_3)

{
  ActionList *pAVar1;
  undefined1 auStack_f8 [32];
  undefined ***local_d8;
  undefined ***local_d0;
  Action *local_c8;
  Action *local_c0;
  Action **local_b8;
  undefined4 uStack_b0;
  uint uStack_ac;
  undefined **local_a8;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined ***local_70;
  undefined **local_68;
  code *local_60;
  longlong lStack_58;
  undefined ***local_30;
  ulonglong local_28;
  
                    /* 0xae100  1515
                       ?SetCutMarkRepetition@DocumentMarks@@YAXAEAVContent@ArtDoc@@AEBV?$function@$$A6A_NAEBVPDFPlusCutMark@DocumentMarks@@@Z@std@@W4Repetition@PDFPlusCutMark@1@@Z
                        */
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_f8;
  local_68 = std::
             _Func_impl_no_alloc<enum_DocumentMarks::PDFPlusCutMark::Repetition_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,DocumentMarks::PDFPlusCutMark::Repetition,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_58 = (ulonglong)uStack_ac << 0x20;
  local_60 = PDFPlusCutMark::GetRepetition;
  local_30 = &local_68;
  local_b8 = (Action **)PDFPlusCutMark::SetRepetition;
  uStack_b0 = 0;
  local_a8 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(DocumentMarks::PDFPlusCutMark::Repetition)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,DocumentMarks::PDFPlusCutMark::Repetition_const&___ptr64>
             ::vftable;
  local_a0 = 0x8013d2b0;
  uStack_9c = 1;
  uStack_98 = 0;
  local_70 = &local_a8;
  local_c0 = (Action *)FUN_1802d6b50(0x100);
  if (local_c0 == (Action *)0x0) {
    local_c8 = (Action *)0x0;
  }
  else {
    local_d0 = &local_68;
    local_d8 = &local_a8;
    local_c8 = (Action *)FUN_1800ac150(local_c0,param_1,param_2,param_3);
  }
  local_b8 = &local_c8;
  pAVar1 = ArtDoc::Action::GetActionList(local_c8);
  local_c0 = local_c8;
  local_c8 = (Action *)0x0;
  ArtDoc::ActionList::DoAction(pAVar1,&local_c0);
  if (local_c8 != (Action *)0x0) {
    (*(code *)**(undefined8 **)local_c8)(local_c8,1);
  }
  if (local_70 != (undefined ***)0x0) {
    (*(code *)(*local_70)[4])
              (local_70,CONCAT71((int7)((ulonglong)&local_a8 >> 8),local_70 != &local_a8));
    local_70 = (undefined ***)0x0;
  }
  if (local_30 != (undefined ***)0x0) {
    (*(code *)(*local_30)[4])
              (local_30,CONCAT71((int7)((ulonglong)&local_68 >> 8),local_30 != &local_68));
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800ae260 SetCutMarkRepetition
// signature: void SetCutMarkRepetition(PDFPlusCutMark * param_1, Repetition param_2)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkRepetition(class DocumentMarks::PDFPlusCutMark &
   __ptr64,enum DocumentMarks::PDFPlusCutMark::Repetition) */

void __cdecl DocumentMarks::SetCutMarkRepetition(PDFPlusCutMark *param_1,Repetition param_2)

{
  undefined1 auStack_d8 [32];
  Repetition local_b8 [2];
  code *local_b0;
  undefined4 uStack_a8;
  uint uStack_a4;
  undefined **local_98;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined ***local_60;
  undefined **local_58;
  code *local_50;
  longlong lStack_48;
  undefined ***local_20;
  ulonglong local_18;
  
                    /* 0xae260  1516
                       ?SetCutMarkRepetition@DocumentMarks@@YAXAEAVPDFPlusCutMark@1@W4Repetition@21@@Z
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_d8;
  local_58 = std::
             _Func_impl_no_alloc<enum_DocumentMarks::PDFPlusCutMark::Repetition_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,DocumentMarks::PDFPlusCutMark::Repetition,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_48 = (ulonglong)uStack_a4 << 0x20;
  local_50 = PDFPlusCutMark::GetRepetition;
  local_20 = &local_58;
  local_b0 = PDFPlusCutMark::SetRepetition;
  uStack_a8 = 0;
  local_98 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(DocumentMarks::PDFPlusCutMark::Repetition)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,DocumentMarks::PDFPlusCutMark::Repetition_const&___ptr64>
             ::vftable;
  local_90 = 0x8013d2b0;
  uStack_8c = 1;
  uStack_88 = 0;
  local_60 = &local_98;
  local_b8[0] = param_2;
  FUN_1800aaae0(0x8013d2b0,local_b8,&local_98,&local_58);
  if (local_60 != (undefined ***)0x0) {
    (*(code *)(*local_60)[4])
              (local_60,CONCAT71((int7)((ulonglong)&local_98 >> 8),local_60 != &local_98));
    local_60 = (undefined ***)0x0;
  }
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])
              (local_20,CONCAT71((int7)((ulonglong)&local_58 >> 8),local_20 != &local_58));
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 1800d0750 TrimSymbol
// signature: void TrimSymbol(ContentObject * param_1, bool param_2, double param_3)
// ---------------------------------------------------------------

/* private: static void __cdecl DocumentMarks::GradationMark::TrimSymbol(class ArtDoc::ContentObject
   & __ptr64,bool,double) */

void __cdecl
DocumentMarks::GradationMark::TrimSymbol(ContentObject *param_1,bool param_2,double param_3)

{
  int *piVar1;
  longlong *plVar2;
  int iVar3;
  void *pvVar4;
  double dVar5;
  double dVar6;
  longlong lVar7;
  ulonglong uVar8;
  longlong *plVar9;
  ulonglong uVar10;
  void *_Memory;
  ulonglong uVar11;
  longlong *plVar12;
  bool bVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  longlong local_138;
  longlong *local_130;
  void *local_128;
  longlong *plStack_120;
  longlong *local_118;
  undefined1 local_108;
  double local_100;
  double dStack_f8;
  undefined8 local_f0;
  double dStack_e8;
  double local_d8;
  double dStack_d0;
  undefined8 local_c8;
  double dStack_c0;
  char local_b0;
  double local_a8;
  double dStack_a0;
  double local_98;
  undefined8 local_88;
  char local_80;
  undefined8 local_58;
  
                    /* 0xd0750  1717
                       ?TrimSymbol@GradationMark@DocumentMarks@@CAXAEAVContentObject@ArtDoc@@_NN@Z
                        */
  GetBoundingBoxForPositioning((ContentObject *)&local_d8);
  if (local_b0 == '\0') {
    local_d8 = 0.0;
    dStack_d0 = 0.0;
    local_c8 = 0;
    dStack_c0 = 0.0;
    local_108 = 1;
  }
  local_128 = (void *)0x0;
  plStack_120 = (longlong *)0x0;
  plVar12 = (longlong *)0x0;
  local_118 = (longlong *)0x0;
  uVar11 = 0;
  local_100 = local_d8;
  dStack_f8 = dStack_d0;
  local_f0 = local_c8;
  dStack_e8 = dStack_c0;
  lVar7 = __RTDynamicCast(param_1,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                          &ArtDoc::Group::RTTI_Type_Descriptor,0);
  dVar6 = dStack_e8;
  dVar5 = dStack_f8;
  plVar9 = plStack_120;
  if ((lVar7 != 0) && (lVar7 = *(longlong *)(lVar7 + 0x2c0), lVar7 != 0)) {
    do {
      uVar11 = uVar11 + 1;
      local_138 = lVar7;
      GetBoundingBoxForPositioning((ContentObject *)&local_a8);
      if (local_80 == '\0') {
        dVar14 = 0.0;
        dVar15 = 0.0;
        dVar16 = 0.0;
        local_58 = CONCAT71(local_58._1_7_,1);
      }
      else {
        dVar16 = local_98;
        local_58 = local_88;
        dVar14 = local_a8;
        dVar15 = dStack_a0;
      }
      if (param_2) {
        bVar13 = local_100 + param_3 < dVar16 + dVar14;
      }
      else {
        bVar13 = dVar15 < (dVar6 + dVar5) - param_3;
      }
      if (bVar13) {
        if (plVar9 == plVar12) {
          FUN_18001de60(&local_128,plVar9,&local_138);
          plVar9 = plStack_120;
          plVar12 = local_118;
        }
        else {
          *plVar9 = lVar7;
          plStack_120 = plVar9 + 1;
          plVar9 = plStack_120;
        }
      }
      lVar7 = *(longlong *)(lVar7 + 8);
    } while (lVar7 != 0);
  }
  pvVar4 = local_128;
  uVar8 = 0;
  uVar10 = (longlong)plVar9 - (longlong)local_128 >> 3;
  if (((uVar10 == 0) || (uVar11 != uVar10)) && (uVar11 != 0)) {
    if (uVar10 != 0) {
      do {
        DocumentEdit::ExtractObjectFromParent((ContentObject *)&local_138);
        plVar9 = local_130;
        if (local_130 != (longlong *)0x0) {
          LOCK();
          plVar2 = local_130 + 1;
          lVar7 = *plVar2;
          *(int *)plVar2 = (int)*plVar2 + -1;
          UNLOCK();
          if ((int)lVar7 == 1) {
            (**(code **)*local_130)(local_130);
            LOCK();
            piVar1 = (int *)((longlong)plVar9 + 0xc);
            iVar3 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar3 == 1) {
              (**(code **)(*plVar9 + 8))(plVar9);
            }
          }
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar10);
    }
  }
  else {
    DocumentEdit::ExtractObjectFromParent((ContentObject *)&local_138);
    if (local_130 != (longlong *)0x0) {
      LOCK();
      plVar9 = local_130 + 1;
      lVar7 = *plVar9;
      *(int *)plVar9 = (int)*plVar9 + -1;
      UNLOCK();
      if ((int)lVar7 == 1) {
        (**(code **)*local_130)(local_130);
        LOCK();
        piVar1 = (int *)((longlong)local_130 + 0xc);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 == 1) {
          (**(code **)(*local_130 + 8))(local_130);
        }
      }
    }
  }
  if (pvVar4 != (void *)0x0) {
    _Memory = pvVar4;
    if ((0xfff < ((longlong)plVar12 - (longlong)pvVar4 & 0xfffffffffffffff8U)) &&
       (_Memory = *(void **)((longlong)pvVar4 + -8),
       0x1f < (ulonglong)((longlong)pvVar4 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 180111410 FUN_180111410
// signature: undefined FUN_180111410(void)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_180111410(MarkReader *param_1,undefined8 *param_2)

{
  longlong *plVar1;
  int *piVar2;
  void *pvVar3;
  longlong *plVar4;
  ulonglong uVar5;
  bool bVar6;
  uint uVar7;
  int iVar8;
  Dictionary *pDVar9;
  Module *pMVar10;
  longlong lVar11;
  longlong lVar12;
  basic_ostream<char,std::char_traits<char>_> *pbVar13;
  ContentObject *pCVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  __uint64 _Var17;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar18;
  Dictionary *pDVar19;
  ContentObject *this;
  Dictionary *pDVar20;
  Properties *pPVar21;
  void *pvVar22;
  uint uVar23;
  double dVar24;
  undefined4 uVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  undefined4 uVar28;
  undefined1 auStack_218 [32];
  undefined4 local_1f8;
  uint local_1e8;
  ContentObject *local_1e0;
  ContentObject *local_1d8;
  undefined8 *local_1d0;
  MarksModule *local_1c8;
  undefined4 local_1b8 [14];
  undefined1 local_180;
  undefined8 local_178;
  longlong *plStack_170;
  void *local_168;
  undefined8 uStack_160;
  longlong local_158;
  undefined1 local_140;
  Dictionary local_138;
  undefined7 uStack_137;
  longlong local_128;
  ulonglong local_120;
  void *local_118;
  undefined8 uStack_110;
  undefined *local_108;
  ulonglong uStack_100;
  ContentObject *local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  ulonglong uStack_e0;
  void *local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  ulonglong uStack_c0;
  void *local_b8;
  undefined8 uStack_b0;
  undefined *local_a8;
  ulonglong uStack_a0;
  void *local_98 [3];
  ulonglong local_80;
  ulonglong local_78;
  
  local_78 = DAT_180418e00 ^ (ulonglong)auStack_218;
  uVar23 = 0;
  local_1e8 = 0;
  local_1e0 = (ContentObject *)((ulonglong)local_1e0 & 0xffffffff00000000);
  local_1d0 = param_2;
  local_1c8 = (MarksModule *)param_2;
  pDVar9 = ArtDoc::MarkReader::GetPropertiesAsDictionary(param_1);
  uStack_110 = 0;
  local_108 = (undefined *)0x4;
  uStack_100 = 0xf;
  local_118 = (void *)0x65707974;
  bVar6 = ArtDoc::Dictionary::HasStringValue
                    (pDVar9,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                            &local_118);
  if (0xf < uStack_100) {
    pvVar22 = local_118;
    if ((0xfff < uStack_100 + 1) &&
       (pvVar22 = *(void **)((longlong)local_118 + -8),
       0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar22);
  }
  if (!bVar6) {
    *param_2 = 0;
    return param_2;
  }
  uStack_f0 = 0;
  local_e8 = 6;
  uStack_e0 = 0xf;
  local_f8 = (ContentObject *)0x64696b72616d;
  ArtDoc::GetEskoStringValue
            ((Dictionary *)local_98,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)pDVar9)
  ;
  if (0xf < uStack_e0) {
    pCVar14 = local_f8;
    if ((0xfff < uStack_e0 + 1) &&
       (pCVar14 = *(ContentObject **)(local_f8 + -8),
       (ContentObject *)0x1f < local_f8 + (-8 - (longlong)pCVar14))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pCVar14);
  }
  uStack_110 = 0;
  local_108 = (undefined *)0x4;
  uStack_100 = 0xf;
  local_118 = (void *)0x65707974;
  ArtDoc::GetEskoStringValue
            (&local_138,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)pDVar9)
  ;
  if (0xf < uStack_100) {
    pvVar22 = local_118;
    if ((0xfff < uStack_100 + 1) &&
       (pvVar22 = *(void **)((longlong)local_118 + -8),
       0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar22);
  }
  pCVar14 = (ContentObject *)0x0;
  local_1d8 = (ContentObject *)0x0;
  pMVar10 = ArtDoc::FindModule(0x4d61726b);
  local_1f8 = 0;
  local_1c8 = (MarksModule *)
              __RTDynamicCast(pMVar10,0,&ArtDoc::Module::RTTI_Type_Descriptor,
                              &DocumentMarks::MarksModule::RTTI_Type_Descriptor);
  if (local_1c8 == (MarksModule *)0x0) {
    *param_2 = 0;
    if (0xf < local_120) {
      pvVar3 = (void *)CONCAT71(uStack_137,local_138);
      pvVar22 = pvVar3;
      if ((0xfff < local_120 + 1) &&
         (pvVar22 = *(void **)((longlong)pvVar3 + -8),
         0x1f < (ulonglong)((longlong)pvVar3 + (-8 - (longlong)pvVar22)))) goto LAB_180112f55;
      free(pvVar22);
    }
    if (local_80 < 0x10) {
      return param_2;
    }
    if (local_80 + 1 < 0x1000) goto LAB_1801116a3;
    lVar11 = (longlong)local_98[0] - (longlong)*(void **)((longlong)local_98[0] + -8);
    local_98[0] = *(void **)((longlong)local_98[0] + -8);
  }
  else {
    uVar7 = DocumentMarks::MarksModule::GetFeatures(local_1c8);
    uVar5 = local_120;
    lVar11 = local_128;
    if ((uVar7 & 1) != 0) {
      pDVar19 = (Dictionary *)CONCAT71(uStack_137,local_138);
      pDVar20 = &local_138;
      if (0xf < local_120) {
        pDVar20 = pDVar19;
      }
      if (local_128 == 0x18) {
        lVar12 = 0x696d616e79444941 - *(longlong *)pDVar20;
        if ((lVar12 == 0) && (lVar12 = 0x422d736b72614d63 - *(longlong *)(pDVar20 + 8), lVar12 == 0)
           ) {
          lVar12 = 0x7261427265726165 - *(longlong *)(pDVar20 + 0x10);
        }
        if (lVar12 != 0) goto LAB_18011185d;
        iVar8 = DocumentMarks::GetMarksDebugLevel();
        if (2 < iVar8) {
          pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(cout_exref,"createDynamicObject ");
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
        }
        local_1e0 = (ContentObject *)FUN_1802d6b50(0x6b8);
        if (local_1e0 == (ContentObject *)0x0) {
          pCVar14 = (ContentObject *)0x0;
        }
        else {
          pCVar14 = (ContentObject *)
                    DocumentMarks::BearerBar::BearerBar((BearerBar *)local_1e0,true);
        }
        local_1e8 = 0x60;
        local_1e0 = pCVar14;
        iVar8 = DocumentMarks::GetMarksDebugLevel();
        if (3 < iVar8) {
          uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
          uVar16 = __std_type_info_name(0x180447900,&DAT_18048b550);
          uVar15 = FUN_18001b3e0(uVar15,uVar16);
          pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(uVar15,&DAT_18031ffa4);
          _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
          pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,_Var17);
          pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                    FUN_18001b3e0(pbVar18,&DAT_180306c80);
          pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
        }
        DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
        uVar23 = 0x40;
        local_1e8 = 0x40;
        local_1d8 = pCVar14;
      }
      else {
LAB_18011185d:
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if ((local_128 == 0x19) &&
           (iVar8 = memcmp("AIDynamicMarks-CustomMark",pDVar20,0x19), iVar8 == 0)) {
          local_118 = (void *)0x0;
          uStack_110 = 0;
          local_108 = (undefined *)0x0;
          uStack_100 = 0;
          lVar11 = -1;
          do {
            lVar11 = lVar11 + 1;
          } while (PTR_s_DM_TextParams_180418990[lVar11] != '\0');
          FUN_180010070((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                        &local_118);
          bVar6 = ArtDoc::Dictionary::HasDictionaryValue
                            (pDVar9,(basic_string<char,std::char_traits<char>,std::allocator<char>_>
                                     *)&local_118);
          if (0xf < uStack_100) {
            pvVar22 = local_118;
            if ((0xfff < uStack_100 + 1) &&
               (pvVar22 = *(void **)((longlong)local_118 + -8),
               0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
              _invalid_parameter_noinfo_noreturn();
            }
            free(pvVar22);
          }
          if (bVar6) {
            local_b8 = (void *)0x0;
            uStack_b0 = 0;
            local_a8 = (undefined *)0x0;
            uStack_a0 = 0;
            lVar11 = -1;
            do {
              lVar11 = lVar11 + 1;
            } while (PTR_s_DM_TextParams_180418990[lVar11] != '\0');
            FUN_180010070(&local_b8);
            pDVar19 = ArtDoc::Dictionary::GetDictionaryValue
                                (pDVar9,(basic_string<char,std::char_traits<char>,std::allocator<char>_>
                                         *)&local_b8);
            ArtDoc::Dictionary::Dictionary((Dictionary *)&local_f8,pDVar19);
            if (0xf < uStack_a0) {
              pvVar22 = local_b8;
              if ((0xfff < uStack_a0 + 1) &&
                 (pvVar22 = *(void **)((longlong)local_b8 + -8),
                 0x1f < (ulonglong)((longlong)local_b8 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                _invalid_parameter_noinfo_noreturn();
              }
              free(pvVar22);
            }
            local_a8 = (undefined *)0x0;
            uStack_a0 = 0xf;
            local_b8 = (void *)((ulonglong)local_b8 & 0xffffffffffffff00);
            local_118 = (void *)0x0;
            uStack_110 = 0;
            local_108 = (undefined *)0x0;
            uStack_100 = 0;
            lVar11 = -1;
            do {
              lVar11 = lVar11 + 1;
            } while (PTR_s_DM_TextParams_Version_180418bc8[lVar11] != '\0');
            FUN_180010070((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                          &local_118);
            iVar8 = ArtDoc::Dictionary::GetIntegerValue
                              ((Dictionary *)&local_f8,
                               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                               &local_118);
            if (0xf < uStack_100) {
              pvVar22 = local_118;
              if ((0xfff < uStack_100 + 1) &&
                 (pvVar22 = *(void **)((longlong)local_118 + -8),
                 0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                _invalid_parameter_noinfo_noreturn();
              }
              free(pvVar22);
            }
            uVar27 = 0;
            uVar28 = 0;
            uVar25 = 0;
            uVar26 = 0;
            local_d8 = (void *)0x0;
            uStack_d0 = 0;
            local_c8 = 0;
            uStack_c0 = 0;
            lVar11 = -1;
            do {
              lVar11 = lVar11 + 1;
            } while (PTR_s_DM_TextParams_Area_Width_180418be0[lVar11] != '\0');
            FUN_180010070(&local_d8);
            uVar23 = 2;
            local_1e8 = 2;
            bVar6 = ArtDoc::Dictionary::HasFloatValue
                              ((Dictionary *)&local_f8,
                               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                               &local_d8);
            if (bVar6) {
              local_118 = (void *)0x0;
              uStack_110 = 0;
              local_108 = (undefined *)0x0;
              uStack_100 = 0;
              lVar11 = -1;
              do {
                lVar11 = lVar11 + 1;
              } while (PTR_s_DM_TextParams_Area_Height_180418be8[lVar11] != '\0');
              FUN_180010070((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                            &local_118);
              uVar23 = 6;
              local_1e8 = 6;
              bVar6 = ArtDoc::Dictionary::HasFloatValue
                                ((Dictionary *)&local_f8,
                                 (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                 &local_118);
              if (!bVar6) goto LAB_180111ad3;
              bVar6 = true;
            }
            else {
LAB_180111ad3:
              bVar6 = false;
            }
            if ((uVar23 & 4) != 0) {
              uVar23 = uVar23 & 0xfffffffb;
              local_1e8 = uVar23;
              if (0xf < uStack_100) {
                pvVar22 = local_118;
                if ((0xfff < uStack_100 + 1) &&
                   (pvVar22 = *(void **)((longlong)local_118 + -8),
                   0x1f < (ulonglong)((longlong)local_118 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                  _invalid_parameter_noinfo_noreturn();
                }
                free(pvVar22);
              }
              local_108 = (undefined *)0x0;
              uStack_100 = 0xf;
              local_118 = (void *)((ulonglong)local_118 & 0xffffffffffffff00);
            }
            if (((uVar23 & 2) != 0) &&
               (uVar23 = uVar23 & 0xfffffffd, local_1e8 = uVar23, 0xf < uStack_c0)) {
              pvVar22 = local_d8;
              if ((0xfff < uStack_c0 + 1) &&
                 (pvVar22 = *(void **)((longlong)local_d8 + -8),
                 0x1f < (ulonglong)((longlong)local_d8 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                _invalid_parameter_noinfo_noreturn();
              }
              free(pvVar22);
            }
            if (bVar6) {
              local_d8 = (void *)0x0;
              uStack_d0 = 0;
              local_c8 = 0;
              uStack_c0 = 0;
              lVar11 = -1;
              do {
                lVar11 = lVar11 + 1;
              } while (PTR_s_DM_TextParams_Area_Width_180418be0[lVar11] != '\0');
              FUN_180010070(&local_d8);
              dVar24 = ArtDoc::Dictionary::GetFloatValue
                                 ((Dictionary *)&local_f8,
                                  (basic_string<char,std::char_traits<char>,std::allocator<char>_> *
                                  )&local_d8);
              uVar27 = SUB84(dVar24,0);
              uVar28 = (undefined4)((ulonglong)dVar24 >> 0x20);
              if (0xf < uStack_c0) {
                pvVar22 = local_d8;
                if ((0xfff < uStack_c0 + 1) &&
                   (pvVar22 = *(void **)((longlong)local_d8 + -8),
                   0x1f < (ulonglong)((longlong)local_d8 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                  _invalid_parameter_noinfo_noreturn();
                }
                free(pvVar22);
              }
              local_d8 = (void *)0x0;
              uStack_d0 = 0;
              local_c8 = 0;
              uStack_c0 = 0;
              lVar11 = -1;
              do {
                lVar11 = lVar11 + 1;
              } while (PTR_s_DM_TextParams_Area_Height_180418be8[lVar11] != '\0');
              FUN_180010070(&local_d8);
              dVar24 = ArtDoc::Dictionary::GetFloatValue
                                 ((Dictionary *)&local_f8,
                                  (basic_string<char,std::char_traits<char>,std::allocator<char>_> *
                                  )&local_d8);
              uVar25 = SUB84(dVar24,0);
              uVar26 = (undefined4)((ulonglong)dVar24 >> 0x20);
              if (0xf < uStack_c0) {
                pvVar22 = local_d8;
                if ((0xfff < uStack_c0 + 1) &&
                   (pvVar22 = *(void **)((longlong)local_d8 + -8),
                   0x1f < (ulonglong)((longlong)local_d8 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
                  _invalid_parameter_noinfo_noreturn();
                }
                free(pvVar22);
              }
            }
            if (((iVar8 < 2) ||
                ((double)CONCAT44(uVar28,uVar27) < 0.0 || (double)CONCAT44(uVar28,uVar27) == 0.0))
               || ((double)CONCAT44(uVar26,uVar25) < 0.0 || (double)CONCAT44(uVar26,uVar25) == 0.0))
            {
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (2 < iVar8) {
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(cout_exref,"createDynamicObject ");
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              local_1e0 = (ContentObject *)FUN_1802d6b50(0x750);
              if (local_1e0 == (ContentObject *)0x0) {
                pCVar14 = (ContentObject *)0x0;
              }
              else {
                pCVar14 = (ContentObject *)
                          DocumentMarks::TextMark::TextMark((TextMark *)local_1e0,true);
              }
              local_1e8 = uVar23 | 0x18000;
              local_1e0 = pCVar14;
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (3 < iVar8) {
                uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                uVar16 = __std_type_info_name(0x18042cab0,&DAT_18048b550);
                uVar15 = FUN_18001b3e0(uVar15,uVar16);
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                    (pbVar13,_Var17);
                pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                          FUN_18001b3e0(pbVar18,&DAT_180306c80);
                pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
              uVar23 = uVar23 | 0x10000;
              local_1b8[0] = 3;
              local_180 = 0;
              local_178 = 0;
              plStack_170 = (longlong *)0x0;
              local_168 = (void *)0x0;
              uStack_160 = 0;
              local_158 = 0;
              local_140 = 0;
              local_1e8 = uVar23;
              local_1d8 = pCVar14;
              DocumentTypesetting::SetRecognitionContext(pCVar14,(RecognitionContext *)local_1b8);
            }
            else {
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (2 < iVar8) {
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(cout_exref,"createDynamicObject ");
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              local_1e0 = (ContentObject *)FUN_1802d6b50(0x858);
              if (local_1e0 == (ContentObject *)0x0) {
                pCVar14 = (ContentObject *)0x0;
              }
              else {
                pCVar14 = (ContentObject *)
                          DocumentMarks::TextAreaMark::TextAreaMark((TextAreaMark *)local_1e0,true);
              }
              local_1e8 = uVar23 | 0x6000000;
              local_1e0 = pCVar14;
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (3 < iVar8) {
                uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                uVar16 = __std_type_info_name(0x18042c1e8,&DAT_18048b550);
                uVar15 = FUN_18001b3e0(uVar15,uVar16);
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                    (pbVar13,_Var17);
                pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                          FUN_18001b3e0(pbVar18,&DAT_180306c80);
                pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
              uVar23 = uVar23 | 0x4000000;
              local_1b8[0] = 1;
              local_180 = 0;
              local_178 = 0;
              plStack_170 = (longlong *)0x0;
              local_168 = (void *)0x0;
              uStack_160 = 0;
              local_158 = 0;
              local_140 = 0;
              local_1e8 = uVar23;
              local_1d8 = pCVar14;
              DocumentTypesetting::SetRecognitionContext(pCVar14,(RecognitionContext *)local_1b8);
            }
            FUN_1800653d0(local_1b8);
            ArtDoc::Dictionary::~Dictionary((Dictionary *)&local_f8);
          }
          else {
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (2 < iVar8) {
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(cout_exref,"createDynamicObject ");
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            local_1e0 = (ContentObject *)FUN_1802d6b50(0x698);
            if (local_1e0 == (ContentObject *)0x0) {
              pCVar14 = (ContentObject *)0x0;
            }
            else {
              pCVar14 = (ContentObject *)
                        DocumentMarks::CustomMark::CustomMark((CustomMark *)local_1e0,true,0xff);
            }
            local_1e8 = 0x6000;
            local_1e0 = pCVar14;
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (3 < iVar8) {
              uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
              uVar16 = __std_type_info_name(0x18044e738,&DAT_18048b550);
              uVar15 = FUN_18001b3e0(uVar15,uVar16);
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(uVar15,&DAT_18031ffa4);
              _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
              pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,_Var17)
              ;
              pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                        FUN_18001b3e0(pbVar18,&DAT_180306c80);
              pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
            uVar23 = 0x4000;
            local_1e8 = 0x4000;
            local_1d8 = pCVar14;
          }
        }
        else {
          pDVar20 = &local_138;
          if (0xf < uVar5) {
            pDVar20 = pDVar19;
          }
          if ((lVar11 == 0x17) &&
             (iVar8 = memcmp("AIDynamicMarks-GridMark",pDVar20,0x17), iVar8 == 0)) {
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (2 < iVar8) {
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(cout_exref,"createDynamicObject ");
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            local_1e0 = (ContentObject *)FUN_1802d6b50(0x710);
            if (local_1e0 == (ContentObject *)0x0) {
              pCVar14 = (ContentObject *)0x0;
            }
            else {
              pCVar14 = (ContentObject *)
                        DocumentMarks::GridMark::GridMark((GridMark *)local_1e0,true);
            }
            local_1e8 = 0x1800;
            local_1e0 = pCVar14;
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (3 < iVar8) {
              uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
              uVar16 = __std_type_info_name(0x1804669e0,&DAT_18048b550);
              uVar15 = FUN_18001b3e0(uVar15,uVar16);
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(uVar15,&DAT_18031ffa4);
              _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
              pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,_Var17)
              ;
              pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                        FUN_18001b3e0(pbVar18,&DAT_180306c80);
              pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
            uVar23 = 0x1000;
            local_1e8 = 0x1000;
            local_1d8 = pCVar14;
          }
          else {
            pDVar20 = &local_138;
            if (0xf < uVar5) {
              pDVar20 = pDVar19;
            }
            if ((lVar11 == 0x1d) &&
               (iVar8 = memcmp("AIDynamicMarks-GradationStrip",pDVar20,0x1d), iVar8 == 0)) {
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (2 < iVar8) {
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(cout_exref,"createDynamicObject ");
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              local_1e0 = (ContentObject *)FUN_1802d6b50(0x6a0);
              if (local_1e0 == (ContentObject *)0x0) {
                pCVar14 = (ContentObject *)0x0;
              }
              else {
                pCVar14 = (ContentObject *)
                          DocumentMarks::GradationMark::GradationMark
                                    ((GradationMark *)local_1e0,true);
              }
              local_1e8 = 0x60000;
              local_1e0 = pCVar14;
              iVar8 = DocumentMarks::GetMarksDebugLevel();
              if (3 < iVar8) {
                uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                uVar16 = __std_type_info_name(0x1804664f8,&DAT_18048b550);
                uVar15 = FUN_18001b3e0(uVar15,uVar16);
                pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                          FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                    (pbVar13,_Var17);
                pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                          FUN_18001b3e0(pbVar18,&DAT_180306c80);
                pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
              }
              DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
              uVar23 = 0x40000;
              local_1e8 = 0x40000;
              local_1d8 = pCVar14;
            }
            else {
              pDVar20 = &local_138;
              if (0xf < uVar5) {
                pDVar20 = pDVar19;
              }
              if ((lVar11 == 0x16) &&
                 (iVar8 = memcmp("AIDynamicMarks-CutMark",pDVar20,0x16), iVar8 == 0)) {
                iVar8 = DocumentMarks::GetMarksDebugLevel();
                if (2 < iVar8) {
                  pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                            FUN_18001b3e0(cout_exref,"createDynamicObject ");
                  std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            (pbVar13,FUN_18003dae0);
                }
                local_1e0 = (ContentObject *)FUN_1802d6b50(0x6a0);
                if (local_1e0 == (ContentObject *)0x0) {
                  pCVar14 = (ContentObject *)0x0;
                }
                else {
                  pCVar14 = (ContentObject *)
                            DocumentMarks::CutMark::CutMark((CutMark *)local_1e0,true);
                }
                local_1e8 = 0x1800000;
                local_1e0 = pCVar14;
                iVar8 = DocumentMarks::GetMarksDebugLevel();
                if (3 < iVar8) {
                  uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                  uVar16 = __std_type_info_name(0x18044eda8,&DAT_18048b550);
                  uVar15 = FUN_18001b3e0(uVar15,uVar16);
                  pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                            FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                  _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                  pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                      (pbVar13,_Var17);
                  pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                            FUN_18001b3e0(pbVar18,&DAT_180306c80);
                  pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                  std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            (pbVar13,FUN_18003dae0);
                }
                DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)pCVar14,pDVar9);
                uVar23 = 0x1000000;
                local_1e8 = 0x1000000;
                local_1d8 = pCVar14;
              }
              else {
                pDVar20 = &local_138;
                if (0xf < uVar5) {
                  pDVar20 = pDVar19;
                }
                if ((lVar11 == 0x19) &&
                   (iVar8 = memcmp("AIDynamicMarks-CornerMark",pDVar20,0x19), iVar8 == 0)) {
                  iVar8 = DocumentMarks::GetMarksDebugLevel();
                  if (2 < iVar8) {
                    pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                              FUN_18001b3e0(cout_exref,"createDynamicObject ");
                    std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              (pbVar13,FUN_18003dae0);
                  }
                  local_1e0 = (ContentObject *)FUN_1802d6b50(0x6b0);
                  if (local_1e0 == (ContentObject *)0x0) {
                    pCVar14 = (ContentObject *)0x0;
                  }
                  else {
                    pCVar14 = (ContentObject *)
                              DocumentMarks::CornerMark::CornerMark((CornerMark *)local_1e0,true);
                  }
                  local_1e8 = 0x18000000;
                  local_1e0 = pCVar14;
                  iVar8 = DocumentMarks::GetMarksDebugLevel();
                  if (3 < iVar8) {
                    uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                    uVar16 = __std_type_info_name(0x18044e638,&DAT_18048b550);
                    uVar15 = FUN_18001b3e0(uVar15,uVar16);
                    pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                              FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                    _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                    pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                        (pbVar13,_Var17);
                    pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                              FUN_18001b3e0(pbVar18,&DAT_180306c80);
                    pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                    std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              (pbVar13,FUN_18003dae0);
                  }
                  DocumentMarks::DynamicObject::setPdfPropertiesDict
                            ((DynamicObject *)pCVar14,pDVar9);
                  uVar23 = 0x10000000;
                  local_1e8 = 0x10000000;
                  local_1d8 = pCVar14;
                }
                else {
                  pDVar20 = &local_138;
                  if (0xf < uVar5) {
                    pDVar20 = pDVar19;
                  }
                  if ((lVar11 == 0x1a) &&
                     (iVar8 = memcmp("AIDynamicMarks-BarcodeMark",pDVar20,0x1a), iVar8 == 0)) {
                    iVar8 = DocumentMarks::GetMarksDebugLevel();
                    if (2 < iVar8) {
                      pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                                FUN_18001b3e0(cout_exref,"createDynamicObject ");
                      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                (pbVar13,FUN_18003dae0);
                    }
                    local_1e0 = (ContentObject *)FUN_1802d6b50(0x6d8);
                    if (local_1e0 == (ContentObject *)0x0) {
                      pCVar14 = (ContentObject *)0x0;
                    }
                    else {
                      pCVar14 = (ContentObject *)
                                DocumentMarks::BarcodeMark::BarcodeMark
                                          ((BarcodeMark *)local_1e0,true);
                    }
                    local_1e8 = 0x80000000;
                    local_1e0 = pCVar14;
                    iVar8 = DocumentMarks::GetMarksDebugLevel();
                    if (3 < iVar8) {
                      uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                      uVar16 = __std_type_info_name(0x180447398,&DAT_18048b550);
                      uVar15 = FUN_18001b3e0(uVar15,uVar16);
                      pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                                FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                      _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                      pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                          (pbVar13,_Var17);
                      pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                                FUN_18001b3e0(pbVar18,&DAT_180306c80);
                      pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                (pbVar13,FUN_18003dae0);
                    }
                    DocumentMarks::DynamicObject::setPdfPropertiesDict
                              ((DynamicObject *)pCVar14,pDVar9);
                    uVar23 = 0;
                    local_1e8 = 0;
                    local_1d8 = pCVar14;
                  }
                  else {
                    pDVar20 = &local_138;
                    if (0xf < uVar5) {
                      pDVar20 = pDVar19;
                    }
                    if (lVar11 == 0x18) {
                      lVar11 = 0x696d616e79444941 - *(longlong *)pDVar20;
                      if ((lVar11 == 0) &&
                         (lVar11 = 0x492d736b72614d63 - *(longlong *)(pDVar20 + 8), lVar11 == 0)) {
                        lVar11 = 0x6b72614d6567616d - *(longlong *)(pDVar20 + 0x10);
                      }
                      if (lVar11 == 0) {
                        iVar8 = DocumentMarks::GetMarksDebugLevel();
                        if (2 < iVar8) {
                          pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                                    FUN_18001b3e0(cout_exref,"createDynamicObject ");
                          std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                    (pbVar13,FUN_18003dae0);
                        }
                        local_f8 = (ContentObject *)FUN_1802d6b50(0x708);
                        if (local_f8 == (ContentObject *)0x0) {
                          pCVar14 = (ContentObject *)0x0;
                        }
                        else {
                          pCVar14 = (ContentObject *)
                                    DocumentMarks::ImageMark::ImageMark((ImageMark *)local_f8,true);
                        }
                        local_1e0 = (ContentObject *)CONCAT44(local_1e0._4_4_,6);
                        local_f8 = pCVar14;
                        iVar8 = DocumentMarks::GetMarksDebugLevel();
                        if (3 < iVar8) {
                          uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
                          uVar16 = __std_type_info_name(0x180467380,&DAT_18048b550);
                          uVar15 = FUN_18001b3e0(uVar15,uVar16);
                          pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                                    FUN_18001b3e0(uVar15,&DAT_18031ffa4);
                          _Var17 = ArtDoc::ContentObject::GetID(pCVar14);
                          pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                              (pbVar13,_Var17);
                          pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                                    FUN_18001b3e0(pbVar18,&DAT_180306c80);
                          pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
                          std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                    (pbVar13,FUN_18003dae0);
                        }
                        DocumentMarks::DynamicObject::setPdfPropertiesDict
                                  ((DynamicObject *)pCVar14,pDVar9);
                        local_1d8 = pCVar14;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      param_2 = local_1d0;
    }
    uVar7 = DocumentMarks::MarksModule::GetFeatures(local_1c8);
    this = pCVar14;
    if ((uVar7 & 0x40) == 0) {
LAB_180112ef3:
      pDVar19 = (Dictionary *)CONCAT71(uStack_137,local_138);
LAB_180112efb:
      if (this != (ContentObject *)0x0) {
        pPVar21 = ArtDoc::ContentObject::GetProperties(this);
        FUN_18010e240(pPVar21,&PTR_s_MarkObjectID_18030db80,local_98);
        goto LAB_180112f1f;
      }
    }
    else {
      pDVar19 = (Dictionary *)CONCAT71(uStack_137,local_138);
      pDVar20 = &local_138;
      if (0xf < local_120) {
        pDVar20 = pDVar19;
      }
      if (local_128 != 0xc) {
LAB_180112a5e:
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if (local_128 == 0xb) {
          lVar11 = 0x5461657241696e55 - *(longlong *)pDVar20;
          if ((lVar11 == 0) && (lVar11 = 0x7865 - (ulonglong)*(ushort *)(pDVar20 + 8), lVar11 == 0))
          {
            lVar11 = 0x74 - (ulonglong)(byte)pDVar20[10];
          }
          if (lVar11 != 0) goto LAB_180112b3a;
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (2 < iVar8) {
            pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                      FUN_18001b3e0(cout_exref,"createDynamicObject ");
            std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
          }
          local_f8 = (ContentObject *)FUN_1802d6b50(0x6e8);
          if (local_f8 == (ContentObject *)0x0) {
            this = (ContentObject *)0x0;
          }
          else {
            this = (ContentObject *)
                   DocumentMarks::VDPAreaText::VDPAreaText((VDPAreaText *)local_f8,true);
          }
          local_1e8 = uVar23 | 0x180;
          local_f8 = this;
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (iVar8 < 4) goto LAB_180112ecd;
          uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
          uVar16 = 0x18042cb18;
LAB_180112e61:
          uVar16 = __std_type_info_name(uVar16,&DAT_18048b550);
          uVar15 = FUN_18001b3e0(uVar15,uVar16);
          pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(uVar15,&DAT_18031ffa4);
          _Var17 = ArtDoc::ContentObject::GetID(this);
          pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,_Var17);
          pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                    FUN_18001b3e0(pbVar18,&DAT_180306c80);
          pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
LAB_180112ecd:
          DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)this,pDVar9);
          local_1d8 = this;
          if (pCVar14 != (ContentObject *)0x0) {
            (*(code *)**(undefined8 **)pCVar14)(pCVar14,1);
          }
          goto LAB_180112ef3;
        }
LAB_180112b3a:
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if (local_128 == 7) {
          iVar8 = 0x63726142 - *(int *)pDVar20;
          if ((iVar8 == 0) && (iVar8 = 0x646f - (uint)*(ushort *)(pDVar20 + 4), iVar8 == 0)) {
            iVar8 = 0x65 - (uint)(byte)pDVar20[6];
          }
          if (iVar8 != 0) goto LAB_180112c13;
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (2 < iVar8) {
            pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                      FUN_18001b3e0(cout_exref,"createDynamicObject ");
            std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
          }
          local_f8 = (ContentObject *)FUN_1802d6b50(0x6d8);
          if (local_f8 == (ContentObject *)0x0) {
            this = (ContentObject *)0x0;
          }
          else {
            this = (ContentObject *)
                   DocumentMarks::VDPBarcode::VDPBarcode((VDPBarcode *)local_f8,true);
          }
          local_1e8 = uVar23 | 0x600;
          local_f8 = this;
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (3 < iVar8) {
            uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
            uVar16 = 0x18042cb48;
            goto LAB_180112e61;
          }
          goto LAB_180112ecd;
        }
LAB_180112c13:
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if (local_128 == 9) {
          lVar11 = 0x6e6f4d6567616d49 - *(longlong *)pDVar20;
          if (lVar11 == 0) {
            lVar11 = 0x6f - (ulonglong)(byte)pDVar20[8];
          }
          if (lVar11 == 0) {
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (2 < iVar8) {
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(cout_exref,"createDynamicObject ");
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            local_f8 = (ContentObject *)FUN_1802d6b50(0x808);
            if (local_f8 == (ContentObject *)0x0) {
              this = (ContentObject *)0x0;
            }
            else {
              this = (ContentObject *)
                     DocumentMarks::VDPImageMono::VDPImageMono((VDPImageMono *)local_f8,true);
            }
            local_1e8 = uVar23 | 0x180000;
            local_f8 = this;
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (3 < iVar8) {
              uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
              uVar16 = 0x18042cb78;
              goto LAB_180112e61;
            }
            goto LAB_180112ecd;
          }
        }
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if (local_128 == 10) {
          lVar11 = 0x6c6f436567616d49 - *(longlong *)pDVar20;
          if (lVar11 == 0) {
            lVar11 = 0x726f - (ulonglong)*(ushort *)(pDVar20 + 8);
          }
          if (lVar11 == 0) {
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (2 < iVar8) {
              pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                        FUN_18001b3e0(cout_exref,"createDynamicObject ");
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
            }
            local_f8 = (ContentObject *)FUN_1802d6b50(0x808);
            if (local_f8 == (ContentObject *)0x0) {
              this = (ContentObject *)0x0;
            }
            else {
              this = (ContentObject *)
                     DocumentMarks::VDPImageColor::VDPImageColor((VDPImageColor *)local_f8,true);
            }
            local_1e8 = uVar23 | 0x600000;
            local_f8 = this;
            iVar8 = DocumentMarks::GetMarksDebugLevel();
            if (3 < iVar8) {
              uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
              uVar16 = 0x18042cbb0;
              goto LAB_180112e61;
            }
            goto LAB_180112ecd;
          }
        }
        pDVar20 = &local_138;
        if (0xf < local_120) {
          pDVar20 = pDVar19;
        }
        if ((local_128 == 8) && (*(longlong *)pDVar20 == 0x4644506567616d49)) {
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (2 < iVar8) {
            pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                      FUN_18001b3e0(cout_exref,"createDynamicObject ");
            std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
          }
          local_f8 = (ContentObject *)FUN_1802d6b50(0x838);
          if (local_f8 == (ContentObject *)0x0) {
            this = (ContentObject *)0x0;
          }
          else {
            this = (ContentObject *)
                   DocumentMarks::VDPImagePDF::VDPImagePDF((VDPImagePDF *)local_f8,true);
          }
          local_1e8 = uVar23 | 0x60000000;
          local_f8 = this;
          iVar8 = DocumentMarks::GetMarksDebugLevel();
          if (3 < iVar8) {
            uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
            uVar16 = 0x18042cbe8;
            goto LAB_180112e61;
          }
          goto LAB_180112ecd;
        }
        goto LAB_180112efb;
      }
      lVar11 = 0x746e696f50696e55 - *(longlong *)pDVar20;
      if (lVar11 == 0) {
        lVar11 = 0x74786554 - (ulonglong)*(uint *)(pDVar20 + 8);
      }
      if (lVar11 != 0) goto LAB_180112a5e;
      iVar8 = DocumentMarks::GetMarksDebugLevel();
      if (2 < iVar8) {
        pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                  FUN_18001b3e0(cout_exref,"createDynamicObject ");
        std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
      }
      local_f8 = (ContentObject *)FUN_1802d6b50(0x6d8);
      if (local_f8 == (ContentObject *)0x0) {
        this = (ContentObject *)0x0;
      }
      else {
        this = (ContentObject *)
               DocumentMarks::VDPPointText::VDPPointText((VDPPointText *)local_f8,true);
      }
      local_1e8 = uVar23 | 0x18;
      local_f8 = this;
      iVar8 = DocumentMarks::GetMarksDebugLevel();
      if (3 < iVar8) {
        uVar15 = FUN_18001b3e0(cout_exref,"createDynamicObject params: ");
        uVar16 = __std_type_info_name(0x18042cae0,&DAT_18048b550);
        uVar15 = FUN_18001b3e0(uVar15,uVar16);
        pbVar13 = (basic_ostream<char,std::char_traits<char>_> *)
                  FUN_18001b3e0(uVar15,&DAT_18031ffa4);
        _Var17 = ArtDoc::ContentObject::GetID(this);
        pbVar18 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,_Var17);
        pbVar18 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                  FUN_18001b3e0(pbVar18,&DAT_180306c80);
        pbVar13 = ArtDoc::operator<<(pbVar18,pDVar9);
        std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar13,FUN_18003dae0);
      }
      DocumentMarks::DynamicObject::setPdfPropertiesDict((DynamicObject *)this,pDVar9);
      local_1d8 = this;
      if (pCVar14 != (ContentObject *)0x0) {
        (*(code *)**(undefined8 **)pCVar14)(pCVar14,1);
      }
      if (this != (ContentObject *)0x0) {
        local_1b8[0] = 3;
        local_180 = 0;
        local_178 = 0;
        plStack_170 = (longlong *)0x0;
        local_168 = (void *)0x0;
        uStack_160 = 0;
        local_158 = 0;
        local_140 = 0;
        DocumentTypesetting::SetRecognitionContext(this,(RecognitionContext *)local_1b8);
        if (local_168 != (void *)0x0) {
          pvVar22 = local_168;
          if ((0xfff < (ulonglong)(((local_158 - (longlong)local_168) / 0xb0) * 0xb0)) &&
             (pvVar22 = *(void **)((longlong)local_168 + -8),
             0x1f < (ulonglong)((longlong)local_168 + (-8 - (longlong)pvVar22)))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(pvVar22);
          local_168 = (void *)0x0;
          uStack_160 = 0;
          local_158 = 0;
        }
        plVar4 = plStack_170;
        if (plStack_170 != (longlong *)0x0) {
          LOCK();
          plVar1 = plStack_170 + 1;
          lVar11 = *plVar1;
          *(int *)plVar1 = (int)*plVar1 + -1;
          UNLOCK();
          if ((int)lVar11 == 1) {
            (**(code **)*plStack_170)(plStack_170);
            LOCK();
            piVar2 = (int *)((longlong)plVar4 + 0xc);
            iVar8 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar8 == 1) {
              (**(code **)(*plVar4 + 8))(plVar4);
            }
          }
        }
        goto LAB_180112ef3;
      }
LAB_180112f1f:
      pDVar19 = (Dictionary *)CONCAT71(uStack_137,local_138);
    }
    *param_2 = this;
    if (0xf < local_120) {
      pDVar9 = pDVar19;
      if ((0xfff < local_120 + 1) &&
         (pDVar9 = *(Dictionary **)(pDVar19 + -8),
         (Dictionary *)0x1f < pDVar19 + (-8 - (longlong)pDVar9))) {
LAB_180112f55:
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pDVar9);
    }
    if (local_80 < 0x10) {
      return param_2;
    }
    if (local_80 + 1 < 0x1000) goto LAB_1801116a3;
    lVar11 = (longlong)local_98[0] - (longlong)*(void **)((longlong)local_98[0] + -8);
    local_98[0] = *(void **)((longlong)local_98[0] + -8);
  }
  if (0x1f < lVar11 - 8U) {
    local_120 = 0xf;
    local_128 = 0;
    local_138 = (Dictionary)0x0;
                    /* WARNING: Subroutine does not return */
    _invalid_parameter_noinfo_noreturn();
  }
LAB_1801116a3:
  local_120 = 0xf;
  local_128 = 0;
  local_138 = (Dictionary)0x0;
  free(local_98[0]);
  return param_2;
}



// ---------------------------------------------------------------
// FUNC 18013a6f0 PDFPlusCutMark
// signature: undefined PDFPlusCutMark(PDFPlusCutMark * this, PDFPlusCutMark * param_1, CloneStrategy * param_2)
// ---------------------------------------------------------------

/* protected: __cdecl DocumentMarks::PDFPlusCutMark::PDFPlusCutMark(class
   DocumentMarks::PDFPlusCutMark const & __ptr64,class ArtDoc::CloneStrategy & __ptr64) __ptr64 */

PDFPlusCutMark * __thiscall
DocumentMarks::PDFPlusCutMark::PDFPlusCutMark
          (PDFPlusCutMark *this,PDFPlusCutMark *param_1,CloneStrategy *param_2)

{
  PDFPlusCutMark *pPVar1;
  PDFPlusCutMark PVar2;
  void *_Dst;
  ulonglong uVar3;
  size_t _Size;
  
                    /* 0x13a6f0  225
                       ??0PDFPlusCutMark@DocumentMarks@@IEAA@AEBV01@AEAVCloneStrategy@ArtDoc@@@Z */
  DynamicMark::DynamicMark((DynamicMark *)this,(DynamicMark *)param_1,param_2);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  this[0x6b8] = (PDFPlusCutMark)0xff;
  if (param_1[0x6b8] != (PDFPlusCutMark)0xff) {
    if (param_1[0x6b8] == (PDFPlusCutMark)0x0) {
      *(undefined8 *)(this + 0x698) = *(undefined8 *)(param_1 + 0x698);
      this[0x6b8] = (PDFPlusCutMark)0x0;
    }
    else {
      FUN_180011ca0(this + 0x698,param_1 + 0x698);
      this[0x6b8] = (PDFPlusCutMark)0x1;
    }
  }
  this[0x700] = (PDFPlusCutMark)0x0;
  pPVar1 = this + 0x708;
  this[0x788] = (PDFPlusCutMark)0xff;
  if (param_1[0x788] != (PDFPlusCutMark)0xff) {
    if (param_1[0x788] == (PDFPlusCutMark)0x0) {
      this[0x780] = (PDFPlusCutMark)0xff;
      PVar2 = param_1[0x780];
      if (PVar2 != (PDFPlusCutMark)0xff) {
        if (PVar2 == (PDFPlusCutMark)0x0) {
          *(undefined4 *)pPVar1 = *(undefined4 *)(param_1 + 0x708);
          this[0x780] = (PDFPlusCutMark)0x0;
        }
        else if (PVar2 == (PDFPlusCutMark)0x1) {
          *(undefined8 *)pPVar1 = *(undefined8 *)(param_1 + 0x708);
          this[0x780] = (PDFPlusCutMark)0x1;
        }
        else {
          FUN_1800135b0(pPVar1,param_1 + 0x708);
          this[0x780] = (PDFPlusCutMark)0x2;
        }
      }
      this[0x788] = (PDFPlusCutMark)0x0;
    }
    else {
      this[0x788] = (PDFPlusCutMark)0x1;
    }
  }
  *(undefined4 *)(this + 0x790) = *(undefined4 *)(param_1 + 0x790);
  *(undefined4 *)(this + 0x794) = *(undefined4 *)(param_1 + 0x794);
  pPVar1 = this + 0x798;
  *(undefined8 *)pPVar1 = 0;
  *(undefined8 *)(this + 0x7a0) = 0;
  *(undefined8 *)(this + 0x7a8) = 0;
  uVar3 = *(longlong *)(param_1 + 0x7a0) - *(longlong *)(param_1 + 0x798) >> 2;
  if (uVar3 != 0) {
    if (0x3fffffffffffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_1800193a0();
    }
    FUN_18003a6a0(pPVar1);
    _Dst = *(void **)pPVar1;
    _Size = *(longlong *)(param_1 + 0x7a0) - (longlong)*(void **)(param_1 + 0x798);
    memmove(_Dst,*(void **)(param_1 + 0x798),_Size);
    *(void **)(this + 0x7a0) = (void *)((longlong)_Dst + ((longlong)_Size >> 2) * 4);
  }
  *(undefined8 *)(this + 0x7b0) = 0;
  *(undefined8 *)(this + 0x7b8) = 0;
  return this;
}



// ---------------------------------------------------------------
// FUNC 18013a8b0 PDFPlusCutMark
// signature: undefined PDFPlusCutMark(PDFPlusCutMark * this, shared_ptr<ArtPaint::FormPaint_const_> param_1)
// ---------------------------------------------------------------

/* public: __cdecl DocumentMarks::PDFPlusCutMark::PDFPlusCutMark(class std::shared_ptr<class
   ArtPaint::FormPaint const >) __ptr64 */

PDFPlusCutMark * __thiscall
DocumentMarks::PDFPlusCutMark::PDFPlusCutMark(PDFPlusCutMark *this,undefined8 *param_2)

{
  int *piVar1;
  longlong *plVar2;
  PDFPlusCutMark *pPVar3;
  int iVar4;
  undefined4 *puVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined8 local_28;
  undefined8 uStack_20;
  
                    /* 0x13a8b0  226
                       ??0PDFPlusCutMark@DocumentMarks@@QEAA@V?$shared_ptr@$$CBVFormPaint@ArtPaint@@@std@@@Z
                        */
  DynamicMark::DynamicMark((DynamicMark *)this,false,0x1ce);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this + 0x698) = 0;
  this[0x6b8] = (PDFPlusCutMark)0x0;
  this[0x700] = (PDFPlusCutMark)0x0;
  *(undefined4 *)(this + 0x708) = 3;
  this[0x780] = (PDFPlusCutMark)0x0;
  this[0x788] = (PDFPlusCutMark)0x0;
  *(undefined4 *)(this + 0x790) = 1;
  *(undefined4 *)(this + 0x794) = 2;
  pPVar3 = this + 0x798;
  *(undefined8 *)pPVar3 = 0;
  *(undefined8 *)(this + 0x7a0) = 0;
  *(undefined8 *)(this + 0x7a8) = 0;
  FUN_18003a6a0(pPVar3,1);
  puVar5 = *(undefined4 **)pPVar3;
  *puVar5 = 0;
  *(undefined4 **)(this + 0x7a0) = puVar5 + 1;
  *(undefined8 *)(this + 0x7b0) = 0;
  *(undefined8 *)(this + 0x7b8) = 0;
  if (param_2[1] != 0) {
    LOCK();
    piVar1 = (int *)(param_2[1] + 8);
    *piVar1 = *piVar1 + 1;
    UNLOCK();
  }
  local_28 = *param_2;
  uStack_20 = param_2[1];
  DynamicMark::SetSourceContent((DynamicMark *)this,&local_28);
  DynamicObject::setColorType((DynamicObject *)this,1,0);
  MarkPosition::setReferenceObject((MarkPosition *)(this + 0x2f0),0);
  plVar6 = (longlong *)param_2[1];
  if (plVar6 != (longlong *)0x0) {
    LOCK();
    plVar2 = plVar6 + 1;
    lVar7 = *plVar2;
    *(int *)plVar2 = (int)*plVar2 + -1;
    UNLOCK();
    if ((int)lVar7 == 1) {
      (**(code **)*plVar6)(plVar6);
      LOCK();
      piVar1 = (int *)((longlong)plVar6 + 0xc);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 == 1) {
        (**(code **)(*plVar6 + 8))(plVar6);
      }
    }
  }
  return this;
}



// ---------------------------------------------------------------
// FUNC 18013aba0 ~PDFPlusCutMark
// signature: void ~PDFPlusCutMark(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* public: virtual __cdecl DocumentMarks::PDFPlusCutMark::~PDFPlusCutMark(void) __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::~PDFPlusCutMark(PDFPlusCutMark *this)

{
  int *piVar1;
  int iVar2;
  PDFPlusCutMark PVar3;
  longlong *plVar4;
  void *pvVar5;
  void *_Memory;
  
                    /* 0x13aba0  414  ??1PDFPlusCutMark@DocumentMarks@@UEAA@XZ */
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  FUN_18002c560(this + 0x7b0);
  plVar4 = *(longlong **)(this + 0x7b8);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    piVar1 = (int *)((longlong)plVar4 + 0xc);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 == 1) {
      (**(code **)(*plVar4 + 0x10))();
    }
  }
  pvVar5 = *(void **)(this + 0x798);
  if (pvVar5 != (void *)0x0) {
    _Memory = pvVar5;
    if ((0xfff < (ulonglong)((*(longlong *)(this + 0x7a8) - (longlong)pvVar5 >> 2) * 4)) &&
       (_Memory = *(void **)((longlong)pvVar5 + -8),
       0x1f < (ulonglong)((longlong)pvVar5 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
    *(undefined8 *)(this + 0x798) = 0;
    *(undefined8 *)(this + 0x7a0) = 0;
    *(undefined8 *)(this + 0x7a8) = 0;
  }
  if ((((this[0x788] != (PDFPlusCutMark)0xff) && (this[0x788] == (PDFPlusCutMark)0x0)) &&
      (PVar3 = this[0x780], PVar3 != (PDFPlusCutMark)0xff)) &&
     ((PVar3 != (PDFPlusCutMark)0x0 && (PVar3 != (PDFPlusCutMark)0x1)))) {
    FUN_180013c20(this + 0x758);
    FUN_180013c20(this + 0x730);
    FUN_180013c20(this + 0x708);
  }
  if (this[0x700] != (PDFPlusCutMark)0x0) {
    FUN_1800651a0();
  }
  FUN_18006da40(this + 0x698);
  DynamicMark::~DynamicMark((DynamicMark *)this);
  return;
}



// ---------------------------------------------------------------
// FUNC 18013b430 Clone
// signature: PDFPlusCutMark * Clone(PDFPlusCutMark * this, CloneStrategy * param_1)
// ---------------------------------------------------------------

/* public: virtual class DocumentMarks::PDFPlusCutMark * __ptr64 __cdecl
   DocumentMarks::PDFPlusCutMark::Clone(class ArtDoc::CloneStrategy & __ptr64)const __ptr64 */

PDFPlusCutMark * __thiscall
DocumentMarks::PDFPlusCutMark::Clone(PDFPlusCutMark *this,CloneStrategy *param_1)

{
  PDFPlusCutMark *pPVar1;
  
                    /* 0x13b430  874
                       ?Clone@PDFPlusCutMark@DocumentMarks@@UEBAPEAV12@AEAVCloneStrategy@ArtDoc@@@Z
                        */
  pPVar1 = (PDFPlusCutMark *)FUN_1802d6b50(0x7c0);
  if (pPVar1 == (PDFPlusCutMark *)0x0) {
    return (PDFPlusCutMark *)0x0;
  }
  pPVar1 = (PDFPlusCutMark *)PDFPlusCutMark(pPVar1,this,param_1);
  return pPVar1;
}



// ---------------------------------------------------------------
// FUNC 18013bb50 ContentChangedSelf
// signature: void ContentChangedSelf(PDFPlusCutMark * this, Content * param_1, Content * param_2)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: virtual void __cdecl DocumentMarks::PDFPlusCutMark::ContentChangedSelf(class
   ArtDoc::Content * __ptr64,class ArtDoc::Content * __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::ContentChangedSelf
          (PDFPlusCutMark *this,Content *param_1,Content *param_2)

{
  int *piVar1;
  int iVar2;
  longlong *plVar3;
  void *pvVar4;
  char cVar5;
  Document *this_00;
  ChangeCollector *pCVar6;
  void *pvVar7;
  undefined1 auStack_108 [32];
  PDFPlusCutMark *local_e8;
  undefined8 local_e0;
  longlong *local_d8;
  ulonglong local_d0;
  PDFPlusCutMark *local_c8 [4];
  void *local_a8;
  void *pvStack_a0;
  longlong local_98;
  ulonglong local_88;
  undefined1 local_80 [40];
  ulonglong local_58;
  undefined1 local_50 [32];
  ulonglong local_30;
  
                    /* 0x13bb50  916
                       ?ContentChangedSelf@PDFPlusCutMark@DocumentMarks@@MEAAXPEAVContent@ArtDoc@@0@Z
                        */
  local_30 = DAT_180418e00 ^ (ulonglong)auStack_108;
  DynamicMark::ContentChangedSelf((DynamicMark *)this,param_1,param_2);
  cVar5 = FUN_180119ee0();
  if (cVar5 == '\0') {
    if (param_1 != (Content *)0x0) {
      FUN_18002c560(this + 0x7b0);
    }
    if (param_2 != (Content *)0x0) {
      this_00 = ArtDoc::Content::GetDocument(param_2);
      pCVar6 = ArtDoc::Document::GetChangeCollector(this_00);
      local_a8 = (void *)0x0;
      pvStack_a0 = (void *)0x0;
      local_98 = 0;
      local_88 = 0;
      local_e8 = this;
      cVar5 = FUN_18002ce80(&local_e8);
      if (cVar5 == '\0') {
        local_c8[0] = local_e8;
        local_d0 = 0x180323499;
      }
      else {
        local_d0 = 0;
      }
      local_58 = 0;
      FUN_18002dbc0(&local_58,&local_d0);
      FUN_18002dbc0(&local_d0,&local_88);
      FUN_18002dbc0(&local_88,&local_58);
      if (((local_58 != 0) && ((local_58 & 1) == 0)) &&
         (*(code **)(local_58 & 0xfffffffffffffffe) != (code *)0x0)) {
        (**(code **)(local_58 & 0xfffffffffffffffe))(local_50,local_50,2);
      }
      if (((local_d0 != 0) && ((local_d0 & 1) == 0)) &&
         (*(code **)(local_d0 & 0xfffffffffffffffe) != (code *)0x0)) {
        (**(code **)(local_d0 & 0xfffffffffffffffe))(local_c8,local_c8,2);
      }
      FUN_18008afb0(*(undefined8 *)(pCVar6 + 0x30),&local_e0,&local_a8,0);
      if ((PDFPlusCutMark *)&local_e0 != this + 0x7b0) {
        *(undefined8 *)(this + 0x7b0) = local_e0;
        plVar3 = *(longlong **)(this + 0x7b8);
        *(longlong **)(this + 0x7b8) = local_d8;
        if (plVar3 != (longlong *)0x0) {
          LOCK();
          piVar1 = (int *)((longlong)plVar3 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            (**(code **)(*plVar3 + 0x10))();
          }
        }
        local_d8 = (longlong *)0x0;
      }
      if (local_d8 != (longlong *)0x0) {
        LOCK();
        piVar1 = (int *)((longlong)local_d8 + 0xc);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 == 1) {
          (**(code **)(*local_d8 + 0x10))();
        }
      }
      if (local_88 != 0) {
        if (((local_88 & 1) == 0) && (*(code **)(local_88 & 0xfffffffffffffffe) != (code *)0x0)) {
          (**(code **)(local_88 & 0xfffffffffffffffe))(local_80,local_80,2);
        }
        local_88 = 0;
      }
      pvVar4 = pvStack_a0;
      pvVar7 = local_a8;
      if (local_a8 != (void *)0x0) {
        for (; pvVar7 != pvVar4; pvVar7 = (void *)((longlong)pvVar7 + 0x18)) {
          FUN_18002c1e0(pvVar7);
        }
        pvVar7 = local_a8;
        if ((0xfff < (ulonglong)(((local_98 - (longlong)local_a8) / 0x18) * 0x18)) &&
           (pvVar7 = *(void **)((longlong)local_a8 + -8),
           0x1f < (ulonglong)((longlong)local_a8 + (-8 - (longlong)pvVar7)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar7);
      }
    }
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 18013cb30 GetLineTypes
// signature: vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_> * GetLineTypes(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* public: class std::vector<enum DocumentMarks::PDFPlusCutMark::LineType,class std::allocator<enum
   DocumentMarks::PDFPlusCutMark::LineType> > const & __ptr64 __cdecl
   DocumentMarks::PDFPlusCutMark::GetLineTypes(void)const __ptr64 */

vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>
* __thiscall DocumentMarks::PDFPlusCutMark::GetLineTypes(PDFPlusCutMark *this)

{
                    /* 0x13cb30  1205
                       ?GetLineTypes@PDFPlusCutMark@DocumentMarks@@QEBAAEBV?$vector@W4LineType@PDFPlusCutMark@DocumentMarks@@V?$allocator@W4LineType@PDFPlusCutMark@DocumentMarks@@@std@@@std@@XZ
                        */
  return (vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>
          *)(this + 0x798);
}



// ---------------------------------------------------------------
// FUNC 18013cb40 GetOrientation
// signature: Orientation GetOrientation(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* public: enum DocumentMarks::PDFPlusCutMark::Orientation __cdecl
   DocumentMarks::PDFPlusCutMark::GetOrientation(void)const __ptr64 */

Orientation __thiscall DocumentMarks::PDFPlusCutMark::GetOrientation(PDFPlusCutMark *this)

{
                    /* 0x13cb40  1244
                       ?GetOrientation@PDFPlusCutMark@DocumentMarks@@QEBA?AW4Orientation@12@XZ */
  return *(Orientation *)(this + 0x790);
}



// ---------------------------------------------------------------
// FUNC 18013cb50 GetReferenceBox
// signature: RectangleBase<YAGL::MilliPointCoordinateSystem> GetReferenceBox(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* private: class YAGL::RectangleBase<struct YAGL::MilliPointCoordinateSystem> __cdecl
   DocumentMarks::PDFPlusCutMark::GetReferenceBox(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::GetReferenceBox(PDFPlusCutMark *this)

{
  PDFPlusCutMark *pPVar1;
  undefined8 uVar2;
  Content *pCVar3;
  PageContent *this_00;
  Page *this_01;
  RectangleBase<YAGL::MilliPointCoordinateSystem> *pRVar4;
  ContentObject *pCVar5;
  undefined8 *in_RDX;
  undefined8 local_68;
  undefined8 uStack_60;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 uStack_38;
  undefined8 local_30;
  undefined8 uStack_28;
  undefined8 local_20;
  char local_18;
  
                    /* 0x13cb50  1260
                       ?GetReferenceBox@PDFPlusCutMark@DocumentMarks@@AEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@XZ
                        */
  pCVar3 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
  if (pCVar3 == (Content *)0x0) {
    *in_RDX = 0;
    in_RDX[1] = 0;
    in_RDX[2] = 0;
    in_RDX[3] = 0;
    *(undefined1 *)(in_RDX + 4) = 1;
    return;
  }
  pPVar1 = this + 0x708;
  if ((pPVar1 == (PDFPlusCutMark *)0x0) || (this[0x788] != (PDFPlusCutMark)0x0)) {
LAB_18013cc9a:
    *in_RDX = 0;
    in_RDX[1] = 0;
    in_RDX[2] = 0;
    in_RDX[3] = 0;
    *(undefined1 *)(in_RDX + 4) = 1;
  }
  else {
    if (this[0x780] == (PDFPlusCutMark)0x0) {
      pCVar3 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
      this_00 = (PageContent *)
                __RTDynamicCast(pCVar3,0,&ArtDoc::Content::RTTI_Type_Descriptor,
                                &ArtDoc::PageContent::RTTI_Type_Descriptor,0);
      if (this_00 == (PageContent *)0x0) goto LAB_18013cc9a;
      this_01 = ArtDoc::PageContent::GetPage(this_00);
      pRVar4 = ArtDoc::Page::GetPageBox(this_01,*(PageBox *)pPVar1);
    }
    else {
      if (this[0x780] != (PDFPlusCutMark)0x1) {
                    /* WARNING: Subroutine does not return */
        FUN_180025a80();
      }
      uVar2 = *(undefined8 *)pPVar1;
      pCVar3 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
      pCVar5 = ArtDoc::Content::GetObjectWithID(pCVar3,uVar2);
      if (pCVar5 == (ContentObject *)0x0) goto LAB_18013cc9a;
      GetPDFPlusBoundingBox((Visitable *)&local_40);
      pRVar4 = (RectangleBase<YAGL::MilliPointCoordinateSystem> *)&local_68;
      if (local_18 == '\0') {
        local_48 = CONCAT71(local_48._1_7_,1);
        local_68 = 0;
        uStack_60 = 0;
        local_58 = 0;
        uStack_50 = 0;
      }
      else {
        local_68 = local_40;
        uStack_60 = uStack_38;
        local_48 = local_20;
        local_58 = local_30;
        uStack_50 = uStack_28;
      }
    }
    uVar2 = *(undefined8 *)(pRVar4 + 8);
    *in_RDX = *(undefined8 *)pRVar4;
    in_RDX[1] = uVar2;
    uVar2 = *(undefined8 *)(pRVar4 + 0x18);
    in_RDX[2] = *(undefined8 *)(pRVar4 + 0x10);
    in_RDX[3] = uVar2;
    in_RDX[4] = *(undefined8 *)(pRVar4 + 0x20);
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 18013cce0 GetRepetition
// signature: Repetition GetRepetition(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* public: enum DocumentMarks::PDFPlusCutMark::Repetition __cdecl
   DocumentMarks::PDFPlusCutMark::GetRepetition(void)const __ptr64 */

Repetition __thiscall DocumentMarks::PDFPlusCutMark::GetRepetition(PDFPlusCutMark *this)

{
                    /* 0x13cce0  1271
                       ?GetRepetition@PDFPlusCutMark@DocumentMarks@@QEBA?AW4Repetition@12@XZ */
  return *(Repetition *)(this + 0x794);
}



// ---------------------------------------------------------------
// FUNC 18013ccf0 GetStayAwayAreas
// signature: vector<YAGL::RectangleBase<YAGL::MilliPointCoordinateSystem>,std::allocator<YAGL::RectangleBase<YAGL::MilliPointCoordinateSystem>_>_> GetStayAwayAreas(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* public: virtual class std::vector<class YAGL::RectangleBase<struct
   YAGL::MilliPointCoordinateSystem>,class std::allocator<class YAGL::RectangleBase<struct
   YAGL::MilliPointCoordinateSystem> > > __cdecl
   DocumentMarks::PDFPlusCutMark::GetStayAwayAreas(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::GetStayAwayAreas(PDFPlusCutMark *this)

{
  ContentObject *this_00;
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  undefined8 *in_RDX;
  undefined8 in_R9;
  undefined4 extraout_XMM0_Da;
  undefined4 uVar4;
  undefined1 local_30 [40];
  
                    /* 0x13ccf0  1302
                       ?GetStayAwayAreas@PDFPlusCutMark@DocumentMarks@@UEBA?AV?$vector@V?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@V?$allocator@V?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@@std@@@std@@XZ
                       0x13ccf0  1306
                       ?GetStayAwayAreas@PDFPlusRepeatForGridMark@DocumentMarks@@MEBA?AV?$vector@V?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@V?$allocator@V?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@@std@@@std@@XZ
                        */
  *in_RDX = 0;
  in_RDX[1] = 0;
  in_RDX[2] = 0;
  uVar4 = 1;
  for (this_00 = *(ContentObject **)(this + 0x2c0); this_00 != (ContentObject *)0x0;
      this_00 = *(ContentObject **)(this_00 + 8)) {
    puVar3 = (undefined8 *)ArtDoc::ContentObject::GetBoundingBox(this_00,(BoxKind)local_30);
    puVar1 = (undefined8 *)in_RDX[1];
    if (puVar1 == (undefined8 *)in_RDX[2]) {
      FUN_1800552a0(extraout_XMM0_Da,puVar1,puVar3,in_R9,uVar4);
    }
    else {
      uVar2 = puVar3[1];
      *puVar1 = *puVar3;
      puVar1[1] = uVar2;
      uVar2 = puVar3[3];
      puVar1[2] = puVar3[2];
      puVar1[3] = uVar2;
      puVar1[4] = puVar3[4];
      in_RDX[1] = in_RDX[1] + 0x28;
    }
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 18013cdf0 PostProcessFormulasImp
// signature: void PostProcessFormulasImp(PDFPlusCutMark * this, PostReadContext * param_1)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: virtual void __cdecl DocumentMarks::PDFPlusCutMark::PostProcessFormulasImp(class
   ArtDoc::PostReadContext const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::PostProcessFormulasImp(PDFPlusCutMark *this,PostReadContext *param_1)

{
  PDFPlusCutMark *pPVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  void *_Memory;
  PDFPlusCutMark *pPVar4;
  undefined1 auStack_58 [32];
  void *local_38 [3];
  ulonglong local_20;
  ulonglong local_18;
  
                    /* 0x13cdf0  1425
                       ?PostProcessFormulasImp@PDFPlusCutMark@DocumentMarks@@MEAAXAEBVPostReadContext@ArtDoc@@@Z
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_58;
  pPVar1 = this + 0x698;
  if ((pPVar1 == (PDFPlusCutMark *)0x0) || (this[0x6b8] != (PDFPlusCutMark)0x1)) {
    pPVar4 = (PDFPlusCutMark *)0x0;
  }
  else {
    pPVar4 = pPVar1;
  }
  if (pPVar4 != (PDFPlusCutMark *)0x0) {
    puVar3 = (undefined8 *)FUN_180150a50(local_38,pPVar4,param_1);
    if (this[0x6b8] == (PDFPlusCutMark)0x1) {
      FUN_180014e90(pPVar1,puVar3);
    }
    else {
      FUN_18006da40(pPVar1);
      this[0x6b8] = (PDFPlusCutMark)0xff;
      *(undefined8 *)pPVar1 = 0;
      *(undefined8 *)(this + 0x6a0) = 0;
      *(undefined8 *)(this + 0x6a8) = 0;
      *(undefined8 *)(this + 0x6b0) = 0;
      uVar2 = puVar3[1];
      *(undefined8 *)pPVar1 = *puVar3;
      *(undefined8 *)(this + 0x6a0) = uVar2;
      uVar2 = puVar3[3];
      *(undefined8 *)(this + 0x6a8) = puVar3[2];
      *(undefined8 *)(this + 0x6b0) = uVar2;
      puVar3[2] = 0;
      puVar3[3] = 0xf;
      *(undefined1 *)puVar3 = 0;
      this[0x6b8] = (PDFPlusCutMark)0x1;
    }
    if (0xf < local_20) {
      _Memory = local_38[0];
      if ((0xfff < local_20 + 1) &&
         (_Memory = *(void **)((longlong)local_38[0] + -8),
         0x1f < (ulonglong)((longlong)local_38[0] + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 18013cef0 RemoveInvalidCustomFormulasImp
// signature: bool RemoveInvalidCustomFormulasImp(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* protected: virtual bool __cdecl
   DocumentMarks::PDFPlusCutMark::RemoveInvalidCustomFormulasImp(void) __ptr64 */

bool __thiscall DocumentMarks::PDFPlusCutMark::RemoveInvalidCustomFormulasImp(PDFPlusCutMark *this)

{
  PDFPlusCutMark *pPVar1;
  void *pvVar2;
  int iVar3;
  Content *pCVar4;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar5;
  Document *this_00;
  ErrorReporter *pEVar6;
  undefined8 *puVar7;
  void *pvVar8;
  bool bVar9;
  undefined1 auStack_d8 [32];
  void *local_b8;
  PDFPlusCutMark *local_b0;
  void *local_a8 [3];
  ulonglong local_90;
  char local_88;
  undefined1 local_80 [8];
  undefined **local_78 [7];
  undefined4 local_40;
  undefined1 local_38;
  undefined7 uStack_37;
  undefined8 local_28;
  ulonglong local_20;
  ulonglong local_18;
  
                    /* 0x13cef0  1460
                       ?RemoveInvalidCustomFormulasImp@PDFPlusCutMark@DocumentMarks@@MEAA_NXZ */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_d8;
  bVar9 = false;
  pPVar1 = this + 0x698;
  if ((pPVar1 != (PDFPlusCutMark *)0x0) && (this[0x6b8] == (PDFPlusCutMark)0x1)) {
    local_b0 = this;
    iVar3 = FUN_180155530(pPVar1,this);
    if (iVar3 - 1U < 3) {
      pCVar4 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
      if (pCVar4 != (Content *)0x0) {
        pbVar5 = ArtDoc::ContentObject::GetName((ContentObject *)this);
        ArtSys::Core::Error::Error((Error *)local_78,2);
        local_78[0] = MarkActionError::_vftable_;
        local_40 = 4;
        if (iVar3 == 3) {
          local_40 = 7;
        }
        FUN_180011ca0(&local_38,pbVar5);
        pCVar4 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
        this_00 = ArtDoc::Content::GetDocument(pCVar4);
        pEVar6 = ArtDoc::Document::GetErrorReporter(this_00);
        (**(code **)(*(longlong *)pEVar6 + 0x10))(pEVar6,local_78);
        if (0xf < local_20) {
          pvVar2 = (void *)CONCAT71(uStack_37,local_38);
          pvVar8 = pvVar2;
          if ((0xfff < local_20 + 1) &&
             (pvVar8 = *(void **)((longlong)pvVar2 + -8),
             0x1f < (ulonglong)((longlong)pvVar2 + (-8 - (longlong)pvVar8)))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(pvVar8);
        }
        local_28 = 0;
        local_20 = 0xf;
        local_38 = 0;
        ArtSys::Core::Error::~Error((Error *)local_78);
      }
      local_b8 = (void *)0x0;
      if (iVar3 == 3) {
        puVar7 = (undefined8 *)FUN_18013bdc0(local_80,this,pPVar1);
        local_b8 = (void *)*puVar7;
      }
      local_a8[0] = local_b8;
      local_88 = '\0';
      SetCutMarkOffset(this,(variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
                             *)local_a8);
      if (((local_88 != -1) && (local_88 != '\0')) && (0xf < local_90)) {
        pvVar8 = local_a8[0];
        if ((0xfff < local_90 + 1) &&
           (pvVar8 = *(void **)((longlong)local_a8[0] + -8),
           0x1f < (ulonglong)((longlong)local_a8[0] + (-8 - (longlong)pvVar8)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar8);
      }
      bVar9 = true;
    }
  }
  return bVar9;
}



// ---------------------------------------------------------------
// FUNC 18013d130 SetLineTypes
// signature: void SetLineTypes(PDFPlusCutMark * this, vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_> * param_1)
// ---------------------------------------------------------------

/* public: void __cdecl DocumentMarks::PDFPlusCutMark::SetLineTypes(class std::vector<enum
   DocumentMarks::PDFPlusCutMark::LineType,class std::allocator<enum
   DocumentMarks::PDFPlusCutMark::LineType> > const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::SetLineTypes
          (PDFPlusCutMark *this,
          vector<DocumentMarks::PDFPlusCutMark::LineType,std::allocator<DocumentMarks::PDFPlusCutMark::LineType>_>
          *param_1)

{
                    /* 0x13d130  1566
                       ?SetLineTypes@PDFPlusCutMark@DocumentMarks@@QEAAXAEBV?$vector@W4LineType@PDFPlusCutMark@DocumentMarks@@V?$allocator@W4LineType@PDFPlusCutMark@DocumentMarks@@@std@@@std@@@Z
                        */
  if (this + 0x798 == (PDFPlusCutMark *)param_1) {
    return;
  }
  FUN_180137900(this + 0x798,*(longlong *)param_1,
                *(longlong *)(param_1 + 8) - *(longlong *)param_1 >> 2);
  return;
}



// ---------------------------------------------------------------
// FUNC 18013d160 SetOffset
// signature: void SetOffset(PDFPlusCutMark * this, variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_> * param_1)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: void __cdecl DocumentMarks::PDFPlusCutMark::SetOffset(class std::variant<class
   YAGL::CoordinateBase<struct YAGL::MilliPointCoordinateSystem,1>,class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > const &
   __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::SetOffset
          (PDFPlusCutMark *this,
          variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
          *param_1)

{
  variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
  *pvVar1;
  PDFPlusCutMark *pPVar2;
  undefined1 auStack_58 [32];
  undefined8 local_38;
  undefined8 uStack_30;
  undefined8 local_28;
  undefined8 uStack_20;
  ulonglong local_18;
  
                    /* 0x13d160  1575
                       ?SetOffset@PDFPlusCutMark@DocumentMarks@@QEAAXAEBV?$variant@V?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@Z
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_58;
  pPVar2 = this + 0x698;
  if (param_1[0x20] ==
      (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
       )0xff) {
    FUN_18006da40(pPVar2);
    this[0x6b8] = (PDFPlusCutMark)0xff;
  }
  else if (param_1[0x20] ==
           (variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
            )0x0) {
    if (this[0x6b8] == (PDFPlusCutMark)0x0) {
      *(undefined8 *)pPVar2 = *(undefined8 *)param_1;
    }
    else {
      FUN_18006da40(pPVar2);
      this[0x6b8] = (PDFPlusCutMark)0xff;
      *(undefined8 *)pPVar2 = *(undefined8 *)param_1;
      this[0x6b8] = (PDFPlusCutMark)0x0;
    }
  }
  else if (this[0x6b8] == (PDFPlusCutMark)0x1) {
    if (pPVar2 != (PDFPlusCutMark *)param_1) {
      pvVar1 = param_1 + 0x10;
      if (0xf < *(ulonglong *)(param_1 + 0x18)) {
        param_1 = *(variant<YAGL::CoordinateBase<YAGL::MilliPointCoordinateSystem,1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
                    **)param_1;
      }
      FUN_180019430(pPVar2,param_1,*(undefined8 *)pvVar1);
    }
  }
  else {
    FUN_180011ca0(&local_38);
    FUN_18006da40(pPVar2);
    *(undefined8 *)pPVar2 = local_38;
    *(undefined8 *)(this + 0x6a0) = uStack_30;
    *(undefined8 *)(this + 0x6a8) = local_28;
    *(undefined8 *)(this + 0x6b0) = uStack_20;
    this[0x6b8] = (PDFPlusCutMark)0x1;
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 18013d230 SetOrientation
// signature: void SetOrientation(PDFPlusCutMark * this, Orientation param_1)
// ---------------------------------------------------------------

/* public: void __cdecl DocumentMarks::PDFPlusCutMark::SetOrientation(enum
   DocumentMarks::PDFPlusCutMark::Orientation) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::SetOrientation(PDFPlusCutMark *this,Orientation param_1)

{
                    /* 0x13d230  1584
                       ?SetOrientation@PDFPlusCutMark@DocumentMarks@@QEAAXW4Orientation@12@@Z */
  *(Orientation *)(this + 0x790) = param_1;
  return;
}



// ---------------------------------------------------------------
// FUNC 18013d240 SetReferenceObject
// signature: void SetReferenceObject(PDFPlusCutMark * this, variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations> * param_1)
// ---------------------------------------------------------------

/* public: void __cdecl DocumentMarks::PDFPlusCutMark::SetReferenceObject(class std::variant<class
   std::variant<enum ArtDoc::PageBox,unsigned __int64,struct
   DocumentMarks::ProcessingStepLayer>,struct
   DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations> const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::SetReferenceObject
          (PDFPlusCutMark *this,
          variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>
          *param_1)

{
  PDFPlusCutMark *local_res8 [4];
  
                    /* 0x13d240  1600
                       ?SetReferenceObject@PDFPlusCutMark@DocumentMarks@@QEAAXAEBV?$variant@V?$variant@W4PageBox@ArtDoc@@_KUProcessingStepLayer@DocumentMarks@@@std@@UAllStructuralDesignStations@PDFPlusCutMark@DocumentMarks@@@std@@@Z
                        */
  local_res8[0] = this + 0x708;
  if (param_1[0x80] ==
      (variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>
       )0xff) {
    FUN_1800b9b20(local_res8[0]);
    return;
  }
  if (param_1[0x80] ==
      (variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>
       )0x0) {
    FUN_1800b28c0(local_res8);
    return;
  }
  if (this[0x788] == (PDFPlusCutMark)0x1) {
    return;
  }
  FUN_1800b9b20(local_res8[0]);
  this[0x788] = (PDFPlusCutMark)0x1;
  return;
}



// ---------------------------------------------------------------
// FUNC 18013d2b0 SetRepetition
// signature: void SetRepetition(PDFPlusCutMark * this, Repetition param_1)
// ---------------------------------------------------------------

/* public: void __cdecl DocumentMarks::PDFPlusCutMark::SetRepetition(enum
   DocumentMarks::PDFPlusCutMark::Repetition) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::SetRepetition(PDFPlusCutMark *this,Repetition param_1)

{
                    /* 0x13d2b0  1622
                       ?SetRepetition@PDFPlusCutMark@DocumentMarks@@QEAAXW4Repetition@12@@Z */
  *(Repetition *)(this + 0x794) = param_1;
  return;
}



// ---------------------------------------------------------------
// FUNC 18013d2c0 SetTargetSeparationsImp
// signature: void SetTargetSeparationsImp(PDFPlusCutMark * this, PaintAttribute param_1)
// ---------------------------------------------------------------

/* protected: virtual void __cdecl DocumentMarks::PDFPlusCutMark::SetTargetSeparationsImp(enum
   DocumentMarks::PaintAttribute) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::SetTargetSeparationsImp(PDFPlusCutMark *this,PaintAttribute param_1)

{
  undefined1 local_res10 [24];
  PDFPlusCutMark *local_88;
  undefined1 *local_80;
  undefined1 local_78 [96];
  char local_18;
  char local_10;
  
                    /* 0x13d2c0  1654
                       ?SetTargetSeparationsImp@PDFPlusCutMark@DocumentMarks@@MEAAXW4PaintAttribute@2@@Z
                        */
  DynamicObject::GetTargetSeparations((DynamicObject *)this,(PaintAttribute)local_78);
  local_80 = local_78;
  local_88 = this;
  FUN_18013b0b0(&local_88,param_1 == 0);
  if ((local_10 != -1) && (local_10 == '\0')) {
    FUN_1800220f0((longlong)local_18 + 1,local_res10,local_78);
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 18013d750 UpdateMarkErrors
// signature: void UpdateMarkErrors(PDFPlusCutMark * this, bool param_1)
// ---------------------------------------------------------------

/* public: virtual void __cdecl DocumentMarks::PDFPlusCutMark::UpdateMarkErrors(bool) __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::UpdateMarkErrors(PDFPlusCutMark *this,bool param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  void *pvVar7;
  undefined1 local_48 [8];
  longlong *local_40;
  void *local_38;
  undefined8 *local_30;
  undefined8 *local_28;
  void *local_20;
  undefined8 local_18;
  longlong lStack_10;
  
                    /* 0x13d750  1733  ?UpdateMarkErrors@PDFPlusCutMark@DocumentMarks@@UEAAX_N@Z */
  uVar5 = FUN_180105b40(&local_20,this,&DAT_180417790);
  FUN_180130a20(&local_38,uVar5);
  if (local_20 != (void *)0x0) {
    FUN_180010320(local_20,local_18,&local_20);
    pvVar7 = local_20;
    if ((0xfff < (lStack_10 - (longlong)local_20 & 0xfffffffffffffff0U)) &&
       (pvVar7 = *(void **)((longlong)local_20 + -8),
       0x1f < (ulonglong)((longlong)local_20 + (-8 - (longlong)pvVar7)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar7);
    local_20 = (void *)0x0;
    local_18 = 0;
    lStack_10 = 0;
  }
  if (this[0x700] != (PDFPlusCutMark)0x0) {
    puVar6 = (undefined8 *)FUN_1801068f0(local_48,this + 0x6c0,this + 0x6e0,0x7d,0x7e);
    if (local_30 == local_28) {
      FUN_1801040c0(&local_38,local_30,puVar6);
    }
    else {
      *local_30 = 0;
      local_30[1] = 0;
      *local_30 = *puVar6;
      local_30[1] = puVar6[1];
      *puVar6 = 0;
      puVar6[1] = 0;
      local_30 = local_30 + 2;
    }
    if (local_40 != (longlong *)0x0) {
      LOCK();
      plVar1 = local_40 + 1;
      lVar4 = *plVar1;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)lVar4 == 1) {
        (**(code **)*local_40)(local_40);
        LOCK();
        piVar2 = (int *)((longlong)local_40 + 0xc);
        iVar3 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar3 == 1) {
          (**(code **)(*local_40 + 8))(local_40);
        }
      }
    }
  }
  FUN_180108070(this,&local_38,param_1);
  if (local_38 != (void *)0x0) {
    FUN_180010320(local_38,local_30,&local_38);
    pvVar7 = local_38;
    if ((0xfff < ((longlong)local_28 - (longlong)local_38 & 0xfffffffffffffff0U)) &&
       (pvVar7 = *(void **)((longlong)local_38 + -8),
       0x1f < (ulonglong)((longlong)local_38 + (-8 - (longlong)pvVar7)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar7);
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 18013e2a0 getFormulas
// signature: vector<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_> getFormulas(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: virtual class std::vector<class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> >,class std::allocator<class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > __cdecl
   DocumentMarks::PDFPlusCutMark::getFormulas(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::getFormulas(PDFPlusCutMark *this)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  void *_Memory;
  undefined8 *in_RDX;
  PDFPlusCutMark *pPVar4;
  undefined4 extraout_XMM0_Da;
  undefined1 auStack_68 [32];
  undefined4 local_48;
  void *local_38 [3];
  ulonglong local_20;
  ulonglong local_18;
  
                    /* 0x13e2a0  1923
                       ?getFormulas@PDFPlusCutMark@DocumentMarks@@UEBA?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_68;
  *in_RDX = 0;
  in_RDX[1] = 0;
  in_RDX[2] = 0;
  local_48 = 1;
  pPVar4 = this + 0x698;
  if ((pPVar4 == (PDFPlusCutMark *)0x0) || (this[0x6b8] != (PDFPlusCutMark)0x1)) {
    pPVar4 = (PDFPlusCutMark *)0x0;
  }
  if (pPVar4 != (PDFPlusCutMark *)0x0) {
    puVar3 = (undefined8 *)FUN_180150650(local_38);
    puVar1 = (undefined8 *)in_RDX[1];
    if (puVar1 == (undefined8 *)in_RDX[2]) {
      FUN_18005f930(extraout_XMM0_Da,puVar1,puVar3);
    }
    else {
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1[2] = 0;
      puVar1[3] = 0;
      uVar2 = puVar3[1];
      *puVar1 = *puVar3;
      puVar1[1] = uVar2;
      uVar2 = puVar3[3];
      puVar1[2] = puVar3[2];
      puVar1[3] = uVar2;
      puVar3[2] = 0;
      puVar3[3] = 0xf;
      *(undefined1 *)puVar3 = 0;
      in_RDX[1] = in_RDX[1] + 0x20;
    }
    if (0xf < local_20) {
      _Memory = local_38[0];
      if ((0xfff < local_20 + 1) &&
         (_Memory = *(void **)((longlong)local_38[0] + -8),
         0x1f < (ulonglong)((longlong)local_38[0] + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
  }
  return;
}



// ---------------------------------------------------------------
// FUNC 18013e3b0 getMarkType
// signature: basic_string_view<char,std::char_traits<char>_> getMarkType(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* public: virtual class std::basic_string_view<char,struct std::char_traits<char> > __cdecl
   DocumentMarks::PDFPlusCutMark::getMarkType(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::getMarkType(PDFPlusCutMark *this)

{
  undefined8 *in_RDX;
  
                    /* 0x13e3b0  1963
                       ?getMarkType@PDFPlusCutMark@DocumentMarks@@UEBA?AV?$basic_string_view@DU?$char_traits@D@std@@@std@@XZ
                        */
  *in_RDX = "DynamicObject_PDFPlusCutMark";
  in_RDX[1] = 0x1c;
  return;
}



// ---------------------------------------------------------------
// FUNC 18013e3c0 getPositionRefBBox
// signature: RectangleBase<YAGL::MilliPointCoordinateSystem> getPositionRefBBox(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* public: virtual class YAGL::RectangleBase<struct YAGL::MilliPointCoordinateSystem> __cdecl
   DocumentMarks::PDFPlusCutMark::getPositionRefBBox(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::getPositionRefBBox(PDFPlusCutMark *this)

{
  PDFPlusCutMark *pPVar1;
  undefined8 uVar2;
  bool bVar3;
  Content *pCVar4;
  PageContent *this_00;
  Page *this_01;
  RectangleBase<YAGL::MilliPointCoordinateSystem> *pRVar5;
  ContentObject *pCVar6;
  undefined8 *in_RDX;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 uStack_60;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 uStack_38;
  undefined8 local_30;
  undefined8 uStack_28;
  undefined8 local_20;
  char local_18;
  
                    /* 0x13e3c0  2001
                       ?getPositionRefBBox@PDFPlusCutMark@DocumentMarks@@UEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@XZ
                        */
  pCVar4 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
  pPVar1 = this + 0x708;
  if ((pPVar1 != (PDFPlusCutMark *)0x0) && (this[0x788] == (PDFPlusCutMark)0x0)) {
    if (this[0x780] == (PDFPlusCutMark)0x0) {
      local_78 = &kPageContext;
      if (0xf < DAT_1804172c0) {
        local_78 = _kPageContext;
      }
      local_70 = DAT_1804172b8;
      pCVar4 = ArtDoc::GetTopLevelTargetContent
                         (pCVar4,(basic_string_view<char,std::char_traits<char>_> *)&local_78);
      this_00 = (PageContent *)
                __RTDynamicCast(pCVar4,0,&ArtDoc::Content::RTTI_Type_Descriptor,
                                &ArtDoc::PageContent::RTTI_Type_Descriptor,0);
      if (this_00 != (PageContent *)0x0) {
        this_01 = ArtDoc::PageContent::GetPage(this_00);
        pRVar5 = ArtDoc::Page::GetPageBox(this_01,*(PageBox *)pPVar1);
LAB_18013e486:
        uVar2 = *(undefined8 *)(pRVar5 + 8);
        *in_RDX = *(undefined8 *)pRVar5;
        in_RDX[1] = uVar2;
        uVar2 = *(undefined8 *)(pRVar5 + 0x18);
        in_RDX[2] = *(undefined8 *)(pRVar5 + 0x10);
        in_RDX[3] = uVar2;
        in_RDX[4] = *(undefined8 *)(pRVar5 + 0x20);
        return;
      }
    }
    else if ((((this[0x780] == (PDFPlusCutMark)0x1) && (*(undefined8 *)pPVar1 != 0)) &&
             (bVar3 = DynamicObject::isNotLinkedYet((DynamicObject *)this), !bVar3)) &&
            (pCVar6 = ArtDoc::Content::GetObjectWithID(pCVar4,*(undefined8 *)pPVar1),
            pCVar6 != (ContentObject *)0x0)) {
      GetBoundingBoxForPositioning((ContentObject *)&local_40);
      pRVar5 = (RectangleBase<YAGL::MilliPointCoordinateSystem> *)&local_68;
      if (local_18 == '\0') {
        local_48 = CONCAT71(local_48._1_7_,1);
        local_68 = 0;
        uStack_60 = 0;
        local_58 = 0;
        uStack_50 = 0;
      }
      else {
        local_68 = local_40;
        uStack_60 = uStack_38;
        local_48 = local_20;
        local_58 = local_30;
        uStack_50 = uStack_28;
      }
      goto LAB_18013e486;
    }
  }
  *in_RDX = 0;
  in_RDX[1] = 0;
  in_RDX[2] = 0;
  in_RDX[3] = 0;
  *(undefined1 *)(in_RDX + 4) = 1;
  return;
}



// ---------------------------------------------------------------
// FUNC 18013e570 getPositionRefObject
// signature: ContentObject * getPositionRefObject(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* public: virtual class ArtDoc::ContentObject * __ptr64 __cdecl
   DocumentMarks::PDFPlusCutMark::getPositionRefObject(void)const __ptr64 */

ContentObject * __thiscall DocumentMarks::PDFPlusCutMark::getPositionRefObject(PDFPlusCutMark *this)

{
  PDFPlusCutMark *pPVar1;
  Content *this_00;
  ContentObject *pCVar2;
  
                    /* 0x13e570  2005
                       ?getPositionRefObject@PDFPlusCutMark@DocumentMarks@@UEBAPEAVContentObject@ArtDoc@@XZ
                        */
  pPVar1 = this + 0x708;
  if ((((pPVar1 == (PDFPlusCutMark *)0x0) || (this[0x788] != (PDFPlusCutMark)0x0)) ||
      (this[0x780] != (PDFPlusCutMark)0x1)) || (*(__uint64 *)pPVar1 == 0)) {
    return (ContentObject *)0x0;
  }
  this_00 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
                    /* WARNING: Could not recover jumptable at 0x00018013e5a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pCVar2 = ArtDoc::Content::GetObjectWithID(this_00,*(__uint64 *)pPVar1);
  return pCVar2;
}



// ---------------------------------------------------------------
// FUNC 18013e5c0 getRefBoxes
// signature: vector<ArtDoc::PageBox,std::allocator<ArtDoc::PageBox>_> getRefBoxes(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* public: virtual class std::vector<enum ArtDoc::PageBox,class std::allocator<enum ArtDoc::PageBox>
   > __cdecl DocumentMarks::PDFPlusCutMark::getRefBoxes(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::getRefBoxes(PDFPlusCutMark *this)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined8 *in_RDX;
  
                    /* 0x13e5c0  2021
                       ?getRefBoxes@PDFPlusCutMark@DocumentMarks@@UEBA?AV?$vector@W4PageBox@ArtDoc@@V?$allocator@W4PageBox@ArtDoc@@@std@@@std@@XZ
                        */
  if (((this + 0x708 == (PDFPlusCutMark *)0x0) || (this[0x788] != (PDFPlusCutMark)0x0)) ||
     (this[0x780] != (PDFPlusCutMark)0x0)) {
    *in_RDX = 0;
    in_RDX[1] = 0;
    in_RDX[2] = 0;
    return;
  }
  uVar1 = *(undefined4 *)(this + 0x708);
  *in_RDX = 0;
  in_RDX[1] = 0;
  in_RDX[2] = 0;
  puVar2 = (undefined4 *)FUN_1802d6b50(4);
  *in_RDX = puVar2;
  in_RDX[2] = puVar2 + 1;
  *puVar2 = uVar1;
  in_RDX[1] = puVar2 + 1;
  return;
}



// ---------------------------------------------------------------
// FUNC 18013e640 getRefObjects
// signature: vector<unsigned___int64,std::allocator<unsigned___int64>_> getRefObjects(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* public: virtual class std::vector<unsigned __int64,class std::allocator<unsigned __int64> >
   __cdecl DocumentMarks::PDFPlusCutMark::getRefObjects(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::getRefObjects(PDFPlusCutMark *this)

{
  longlong *plVar1;
  longlong *plVar2;
  void *_Memory;
  void *pvVar3;
  longlong *plVar4;
  longlong *in_RDX;
  PDFPlusCutMark *pPVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined4 uVar8;
  void *local_20 [2];
  longlong local_10;
  
                    /* 0x13e640  2048
                       ?getRefObjects@PDFPlusCutMark@DocumentMarks@@UEBA?AV?$vector@_KV?$allocator@_K@std@@@std@@XZ
                        */
  *in_RDX = 0;
  in_RDX[1] = 0;
  in_RDX[2] = 0;
  uVar8 = 1;
  pPVar5 = this + 0x698;
  if ((pPVar5 == (PDFPlusCutMark *)0x0) || (this[0x6b8] != (PDFPlusCutMark)0x1)) {
    pPVar5 = (PDFPlusCutMark *)0x0;
  }
  if (pPVar5 != (PDFPlusCutMark *)0x0) {
    plVar1 = (longlong *)FUN_1801503a0(local_20);
    if (in_RDX != plVar1) {
      pvVar3 = (void *)*in_RDX;
      if (pvVar3 != (void *)0x0) {
        _Memory = pvVar3;
        if ((0xfff < (in_RDX[2] - (longlong)pvVar3 & 0xfffffffffffffff8U)) &&
           (_Memory = *(void **)((longlong)pvVar3 + -8),
           0x1f < (ulonglong)((longlong)pvVar3 + (-8 - (longlong)_Memory)))) goto LAB_18013e744;
        free(_Memory);
        *in_RDX = 0;
        in_RDX[1] = 0;
        in_RDX[2] = 0;
      }
      *in_RDX = *plVar1;
      in_RDX[1] = plVar1[1];
      in_RDX[2] = plVar1[2];
      *plVar1 = 0;
      plVar1[1] = 0;
      plVar1[2] = 0;
    }
    if (local_20[0] != (void *)0x0) {
      pvVar3 = local_20[0];
      if ((0xfff < (local_10 - (longlong)local_20[0] & 0xfffffffffffffff8U)) &&
         (pvVar3 = *(void **)((longlong)local_20[0] + -8),
         0x1f < (ulonglong)((longlong)local_20[0] + (-8 - (longlong)pvVar3)))) {
LAB_18013e744:
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar3);
    }
  }
  if (((this + 0x708 != (PDFPlusCutMark *)0x0) && (this[0x788] == (PDFPlusCutMark)0x0)) &&
     (this[0x780] == (PDFPlusCutMark)0x1)) {
    if ((undefined8 *)in_RDX[1] == (undefined8 *)in_RDX[2]) {
      FUN_18003c5a0();
    }
    else {
      *(undefined8 *)in_RDX[1] = *(undefined8 *)(this + 0x708);
      in_RDX[1] = in_RDX[1] + 8;
    }
  }
  FUN_18006b9e0(*in_RDX,in_RDX[1],in_RDX[1] - *in_RDX >> 3,0,uVar8);
  plVar1 = (longlong *)in_RDX[1];
  plVar6 = (longlong *)*in_RDX;
  if (plVar6 == plVar1) {
    return;
  }
  if (plVar6 + 1 == plVar1) {
    return;
  }
  plVar2 = plVar6 + 1;
  lVar7 = *plVar6;
  do {
    plVar4 = plVar2;
    plVar2 = plVar4 + 1;
    if (lVar7 == *plVar4) {
      for (; plVar2 != plVar1; plVar2 = plVar2 + 1) {
        if (*plVar6 != *plVar2) {
          plVar6 = plVar6 + 1;
          *plVar6 = *plVar2;
        }
      }
      plVar6 = plVar6 + 1;
      if (plVar6 != plVar1) {
        lVar7 = in_RDX[1];
        memmove(plVar6,plVar1,lVar7 - (longlong)plVar1);
        in_RDX[1] = (lVar7 - (longlong)plVar1) + (longlong)plVar6;
      }
      return;
    }
    plVar6 = plVar4;
    lVar7 = *plVar4;
  } while (plVar2 != plVar1);
  return;
}



// ---------------------------------------------------------------
// FUNC 18013e840 hasPositionRef
// signature: bool hasPositionRef(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* public: virtual bool __cdecl DocumentMarks::PDFPlusCutMark::hasPositionRef(void)const __ptr64 */

bool __thiscall DocumentMarks::PDFPlusCutMark::hasPositionRef(PDFPlusCutMark *this)

{
                    /* 0x13e840  2088  ?hasPositionRef@PDFPlusCutMark@DocumentMarks@@UEBA_NXZ */
  if (((this + 0x708 == (PDFPlusCutMark *)0x0) || (this[0x788] != (PDFPlusCutMark)0x0)) ||
     ((this[0x780] == (PDFPlusCutMark)0x1 && (*(longlong *)(this + 0x708) == 0)))) {
    return false;
  }
  return true;
}



// ---------------------------------------------------------------
// FUNC 18013e970 postProcessClonedMark
// signature: void postProcessClonedMark(PDFPlusCutMark * this, CloneStrategy * param_1)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: virtual void __cdecl DocumentMarks::PDFPlusCutMark::postProcessClonedMark(class
   ArtDoc::CloneStrategy const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::postProcessClonedMark(PDFPlusCutMark *this,CloneStrategy *param_1)

{
  PDFPlusCutMark *pPVar1;
  bool bVar2;
  int iVar3;
  __uint64 _Var4;
  ContentObject *pCVar5;
  Content *pCVar6;
  Properties *pPVar7;
  undefined8 uVar8;
  void *pvVar9;
  char *_Memory;
  undefined8 *_Buf2;
  undefined8 *puVar10;
  undefined8 *puVar11;
  PDFPlusCutMark *pPVar12;
  undefined1 auStack_1d8 [32];
  undefined8 local_1b8;
  __uint64 local_1a8 [5];
  undefined1 local_180 [40];
  undefined1 local_158 [40];
  char local_130;
  undefined1 local_128;
  __uint64 *local_118;
  undefined4 local_108;
  undefined4 uStack_104;
  undefined1 local_e0 [40];
  undefined1 local_b8 [40];
  char local_90;
  char local_88;
  void *local_78;
  undefined8 uStack_70;
  undefined8 local_68;
  ulonglong uStack_60;
  char local_58;
  char *local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  ulonglong uStack_38;
  ulonglong local_30;
  
                    /* 0x13e970  2151
                       ?postProcessClonedMark@PDFPlusCutMark@DocumentMarks@@UEAAXAEBVCloneStrategy@ArtDoc@@@Z
                        */
  local_30 = DAT_180418e00 ^ (ulonglong)auStack_1d8;
  if (this[0x788] != (PDFPlusCutMark)0x0) goto LAB_18013ed0e;
  uStack_48 = 0;
  local_40 = 0;
  uStack_38 = 0xf;
  local_50 = (char *)0x0;
  local_78 = (void *)0x0;
  uStack_70 = 0;
  local_68 = 0;
  uStack_60 = 0xf;
  local_58 = '\x01';
  bVar2 = false;
  _Var4 = ArtDoc::ContentObject::GetID((ContentObject *)this);
  pCVar5 = ArtDoc::CloneStrategy::GetOriginalObject(param_1,_Var4);
  local_1b8 = (char **)((ulonglong)local_1b8._4_4_ << 0x20);
  pCVar5 = (ContentObject *)
           __RTDynamicCast(pCVar5,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                           &RTTI_Type_Descriptor);
  if ((pCVar5 == (ContentObject *)0x0) ||
     (pCVar6 = ArtDoc::ContentObject::GetContent(pCVar5), pCVar6 == (Content *)0x0)) {
LAB_18013eb12:
    pPVar7 = ArtDoc::ContentObject::GetProperties((ContentObject *)this);
    puVar10 = *(undefined8 **)pPVar7;
    puVar11 = puVar10 + *(longlong *)(pPVar7 + 8) * 0xc;
    if (puVar10 != puVar11) {
      do {
        _Buf2 = puVar10;
        if (0xf < (ulonglong)puVar10[3]) {
          _Buf2 = (undefined8 *)*puVar10;
        }
      } while (((puVar10[2] != 0x24) ||
               (iVar3 = memcmp("PDFPlusCutMark_OriginalReferenceName",_Buf2,0x24), iVar3 != 0)) &&
              (puVar10 = puVar10 + 0xc, puVar10 != puVar11));
      if (puVar10 != puVar11) {
        puVar11 = puVar10 + 4;
        if (((puVar11 == (undefined8 *)0x0) || ((puVar10[0xb] & 0xfffffffffffffffc) == 0)) ||
           (iVar3 = __std_type_info_compare((puVar10[0xb] & 0xfffffffffffffffc) + 8,0x18041cb58),
           iVar3 != 0)) {
          puVar11 = (undefined8 *)0x0;
        }
        if (puVar11 != (undefined8 *)0x0) {
          FUN_18012f6b0(&local_78,puVar11);
        }
      }
    }
  }
  else {
    if (pCVar5[0x788] != (ContentObject)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_180025a80();
    }
    FUN_1800ac3a0(local_1a8);
    if (local_130 == '\0') {
      if (local_58 != '\0') {
        if ((local_58 != -1) && (local_58 != '\0')) {
          FUN_180016510(&local_78,0);
        }
        local_58 = '\0';
      }
      local_78 = (void *)CONCAT44(local_78._4_4_,(undefined4)local_1a8[0]);
LAB_18013ead4:
      bVar2 = true;
    }
    else if ((local_130 == '\x01') &&
            (pCVar5 = ArtDoc::Content::GetObjectWithID(pCVar6,local_1a8[0]),
            pCVar5 != (ContentObject *)0x0)) {
      uVar8 = (**(code **)(*(longlong *)pCVar5 + 0x18))(pCVar5);
      FUN_18012f6b0(&local_78,uVar8);
      goto LAB_18013ead4;
    }
    if (((local_130 != -1) && (local_130 != '\0')) && (local_130 != '\x01')) {
      FUN_180013c20(local_158);
      FUN_180013c20(local_180);
      FUN_180013c20(local_1a8);
    }
    if (!bVar2) goto LAB_18013eb12;
  }
  pCVar6 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
  FUN_1802746e0(&local_108,pCVar6,&local_78);
  if (local_88 == '\0') {
    pPVar7 = ArtDoc::ContentObject::GetProperties((ContentObject *)this);
    if (local_58 != '\x01') {
                    /* WARNING: Subroutine does not return */
      FUN_180025a80();
    }
    FUN_18004e5d0(pPVar7,&PTR_s_PDFPlusCutMark_OriginalReference_180323170,&local_78);
  }
  else {
    local_118 = local_1a8;
    local_130 = -1;
    if (local_90 != -1) {
      if (local_90 == '\0') {
        local_1a8[0] = CONCAT44(local_1a8[0]._4_4_,local_108);
        local_130 = '\0';
      }
      else if (local_90 == '\x01') {
        local_1a8[0] = CONCAT44(uStack_104,local_108);
        local_130 = '\x01';
      }
      else {
        FUN_1800135b0(local_1a8,&local_108);
        local_130 = '\x02';
      }
    }
    local_128 = 0;
    SetReferenceObject(this,(variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>
                             *)local_1a8);
    FUN_1800ac600(local_1a8);
    pPVar7 = ArtDoc::ContentObject::GetProperties((ContentObject *)this);
    ArtDoc::Properties::Erase
              (pPVar7,(basic_string_view<char,std::char_traits<char>_> *)
                      &PTR_s_PDFPlusCutMark_OriginalReference_180323170);
  }
  if ((((local_88 != '\0') && (local_90 != -1)) && (local_90 != '\0')) && (local_90 != '\x01')) {
    FUN_180013c20(local_b8);
    FUN_180013c20(local_e0);
    FUN_180013c20(&local_108);
  }
  if (((local_58 != -1) && (local_58 != '\0')) && (0xf < uStack_60)) {
    pvVar9 = local_78;
    if ((0xfff < uStack_60 + 1) &&
       (pvVar9 = *(void **)((longlong)local_78 + -8),
       0x1f < (ulonglong)((longlong)local_78 + (-8 - (longlong)pvVar9)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar9);
  }
LAB_18013ed0e:
  pPVar1 = this + 0x698;
  if ((pPVar1 == (PDFPlusCutMark *)0x0) || (pPVar12 = pPVar1, this[0x6b8] != (PDFPlusCutMark)0x1)) {
    pPVar12 = (PDFPlusCutMark *)0x0;
  }
  if (pPVar12 != (PDFPlusCutMark *)0x0) {
    local_50 = (char *)0x0;
    uStack_48 = 0;
    local_40 = 0;
    uStack_38 = 0;
    local_50 = (char *)FUN_1802d6b50(0x20);
    local_40 = 0x15;
    uStack_38 = 0x1f;
    builtin_strncpy(local_50,"PDFPlusCutMark_Offset",0x16);
    local_1b8 = &local_50;
    uVar8 = FUN_180154640(&local_78,pPVar12,this,param_1);
    FUN_180133520(pPVar1,uVar8);
    if (0xf < uStack_60) {
      pvVar9 = local_78;
      if ((0xfff < uStack_60 + 1) &&
         (pvVar9 = *(void **)((longlong)local_78 + -8),
         0x1f < (ulonglong)((longlong)local_78 + (-8 - (longlong)pvVar9)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar9);
    }
    local_68 = 0;
    uStack_60 = 0xf;
    local_78 = (void *)((ulonglong)local_78 & 0xffffffffffffff00);
    if (0xf < uStack_38) {
      _Memory = local_50;
      if ((0xfff < uStack_38 + 1) &&
         (_Memory = *(char **)(local_50 + -8), (char *)0x1f < local_50 + (-8 - (longlong)_Memory)))
      {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
  }
  DynamicMark::postProcessClonedMark((DynamicMark *)this,param_1);
  return;
}



// ---------------------------------------------------------------
// FUNC 18013ee90 regenerateMarkImp
// signature: void regenerateMarkImp(PDFPlusCutMark * this)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Removing unreachable block (ram,0x00018013fe2d) */
/* WARNING: Removing unreachable block (ram,0x00018013fe43) */
/* WARNING: Removing unreachable block (ram,0x00018013fe5c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: virtual void __cdecl DocumentMarks::PDFPlusCutMark::regenerateMarkImp(void) __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::regenerateMarkImp(PDFPlusCutMark *this)

{
  int *piVar1;
  longlong *plVar2;
  PDFPlusCutMark *pPVar3;
  ulonglong uVar4;
  int iVar5;
  double dVar6;
  ulonglong uVar7;
  undefined1 auVar8 [12];
  undefined *puVar9;
  undefined **ppuVar10;
  undefined **ppuVar11;
  Compound *pCVar12;
  undefined *puVar13;
  undefined *puVar14;
  bool bVar15;
  undefined8 *puVar16;
  Content *pCVar17;
  ContentObject *pCVar18;
  longlong *plVar19;
  double **ppdVar20;
  Group *pGVar21;
  longlong lVar22;
  undefined1 (*pauVar23) [16];
  undefined **ppuVar24;
  double *pdVar25;
  undefined8 uVar26;
  Document *pDVar27;
  TransformationBase<YAGL::MilliPointCoordinateSystem> *pTVar28;
  longlong *plVar29;
  longlong *plVar30;
  undefined *puVar31;
  char cVar32;
  undefined **ppuVar33;
  double *pdVar34;
  undefined4 uVar35;
  double dVar36;
  double dVar37;
  undefined *puVar38;
  undefined1 auVar39 [16];
  undefined *puVar40;
  undefined *puVar41;
  undefined1 auVar42 [16];
  double dVar43;
  undefined1 auVar44 [16];
  undefined1 auStackY_728 [32];
  double local_6e8;
  longlong *local_6e0;
  PDFPlusCutMark *local_6d8;
  double *local_6d0;
  PDFPlusCutMark *local_6c8;
  undefined8 local_6b8;
  undefined4 uStack_6b0;
  undefined4 uStack_6ac;
  longlong *local_6a8;
  longlong *local_6a0;
  double local_698;
  double local_690;
  undefined **local_688;
  undefined **ppuStack_680;
  undefined **ppuStack_678;
  undefined8 local_670;
  undefined8 local_668;
  Group *local_660;
  undefined1 local_658 [16];
  double local_648;
  double dStack_640;
  undefined *local_638;
  double dStack_630;
  PDFPlusCutMark *local_628;
  double *local_620;
  double *pdStack_618;
  double *local_610;
  Compound *local_608;
  longlong *plStack_600;
  Group *local_5f8;
  Group *pGStack_5f0;
  longlong local_5e8;
  Compound *local_5d8;
  longlong *plStack_5d0;
  undefined *local_5c8;
  undefined *puStack_5c0;
  undefined *local_5b8;
  undefined *puStack_5b0;
  undefined *local_5a8;
  undefined *puStack_5a0;
  Compound *local_598;
  undefined *puStack_590;
  longlong *local_588;
  longlong *plStack_580;
  longlong *local_578;
  undefined1 local_570 [8];
  double local_568;
  double local_560;
  undefined **local_558;
  Group **local_550;
  undefined ***local_520;
  Visitable local_510 [16];
  double local_500;
  char local_4e8;
  undefined **local_4d8;
  undefined **local_4d0 [7];
  undefined ***local_498;
  undefined *local_488;
  undefined *puStack_480;
  undefined *local_478;
  undefined *puStack_470;
  undefined *local_468;
  char cStack_460;
  undefined7 uStack_45f;
  undefined **local_408 [7];
  undefined ***local_3d0;
  undefined **local_3c8 [7];
  undefined ***local_390;
  undefined **local_388 [7];
  undefined ***local_350;
  Expander local_348 [640];
  ulonglong local_c8;
  
                    /* 0x13ee90  2187  ?regenerateMarkImp@PDFPlusCutMark@DocumentMarks@@MEAAXXZ */
  local_c8 = DAT_180418e00 ^ (ulonglong)auStackY_728;
  local_668 = (Group *)((ulonglong)local_668 & 0xffffffff00000000);
  local_6e8 = (double)((ulonglong)local_6e8 & 0xffffffff00000000);
  pCVar18 = *(ContentObject **)(this + 0x2c0);
  local_6c8 = this;
  local_628 = this;
  while (pCVar18 != (ContentObject *)0x0) {
                    /* WARNING: Read-only address (ram,0x0001803082f0) is written */
    DocumentEdit::Delete(pCVar18);
    pCVar18 = *(ContentObject **)(this + 0x2c0);
  }
                    /* WARNING: Read-only address (ram,0x0001803082f0) is written */
  FUN_1802a1ce0(local_570);
  if (this[0x700] != (PDFPlusCutMark)0x0) {
    FUN_1800651a0(this + 0x6c0);
    this[0x700] = (PDFPlusCutMark)0x0;
  }
  local_6d0 = (double *)0x0;
  pPVar3 = this + 0x698;
  if ((pPVar3 == (PDFPlusCutMark *)0x0) || (this[0x6b8] != (PDFPlusCutMark)0x1)) {
    if (this[0x6b8] != (PDFPlusCutMark)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_180025a80();
    }
    local_6d0 = *(double **)pPVar3;
  }
  else {
    local_6d8 = pPVar3;
    puVar16 = (undefined8 *)FUN_18013bdc0(&local_6e0,this,pPVar3);
    local_6d0 = (double *)*puVar16;
  }
  local_560 = ((double)local_6d0 * 127.0) / 360000.0;
  puVar16 = (undefined8 *)DynamicMark::GetSourceContent((DynamicMark *)this);
  ArtPaint::FormPaint::GetContent((FormPaint *)*puVar16);
  GetPDFPlusBoundingBox(local_510);
  plVar19 = plStack_600;
  if (plStack_600 != (longlong *)0x0) {
    LOCK();
    plVar29 = plStack_600 + 1;
    lVar22 = *plVar29;
    *(int *)plVar29 = (int)*plVar29 + -1;
    UNLOCK();
    if ((int)lVar22 == 1) {
      (**(code **)*plStack_600)(plStack_600);
      LOCK();
      piVar1 = (int *)((longlong)plVar19 + 0xc);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 == 1) {
        (**(code **)(*plVar19 + 8))(plVar19);
      }
    }
  }
  if ((local_4e8 == '\0') || (local_500 < 0.0)) {
LAB_18013f099:
    local_500 = 0.0;
  }
  else if (local_500 <= 0.0) {
    if (local_500 == 0.0) {
      cVar32 = '\0';
    }
    else {
      cVar32 = -0x80;
    }
    if (cVar32 < '\0') goto LAB_18013f099;
  }
  local_568 = (local_500 * 127.0) / 360000.0;
  local_620 = (double *)0x0;
  pdStack_618 = (double *)0x0;
  local_6c8 = (PDFPlusCutMark *)0x0;
  local_610 = (double *)0x0;
  local_6d8 = (PDFPlusCutMark *)local_500;
  if (((this + 0x708 == (PDFPlusCutMark *)0x0) || (this[0x788] != (PDFPlusCutMark)0x0)) ||
     (this[0x780] != (PDFPlusCutMark)0x1)) {
LAB_18013f2be:
    if (this[0x788] == (PDFPlusCutMark)0x1) {
      local_688 = (undefined **)0x0;
      ppuStack_680 = (undefined **)0x0;
      ppuStack_678 = (undefined **)0x0;
      local_658 = ZEXT816(0);
      local_648 = 0.0;
      dStack_640 = 0.0;
      cVar32 = '\x01';
      local_638 = (undefined *)CONCAT71(local_638._1_7_,1);
      pCVar17 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
      local_5f8 = (Group *)0x0;
      pGStack_5f0 = (Group *)0x0;
      local_5e8 = 0;
      local_668 = (Group *)CONCAT44(local_668._4_4_,2);
      local_6e8 = (double)CONCAT44(local_6e8._4_4_,2);
      local_558 = std::
                  _Func_impl_no_alloc<`class_std::vector<DocumentMarks::StationInterface_const*___ptr64,std::allocator<DocumentMarks::StationInterface_const*___ptr64>_>___cdecl__anon_E70A8568::CollectStations(ArtDoc::Content&___ptr64)'::`2'::<lambda_1>,bool,ArtDoc::Group&___ptr64>
                  ::vftable;
      local_550 = &local_5f8;
      local_520 = &local_558;
      ArtDoc::VisitorBase::VisitorBase((VisitorBase *)&local_4d8);
      local_4d8 = ArtDoc::SimpleVisitor<ArtDoc::Group>::vftable;
      local_498 = (undefined ***)0x0;
      if (local_520 != (undefined ***)0x0) {
        if (local_520 == &local_558) {
          local_498 = (undefined ***)(*(code *)(*local_520)[1])(local_520,local_4d0);
          if (local_520 == (undefined ***)0x0) goto LAB_18013f3e5;
          (*(code *)(*local_520)[4])
                    (local_520,CONCAT71((int7)((ulonglong)&local_558 >> 8),local_520 != &local_558))
          ;
        }
        else {
          local_498 = local_520;
        }
        local_520 = (undefined ***)0x0;
      }
LAB_18013f3e5:
      (**(code **)(*(longlong *)pCVar17 + 0x10))(pCVar17,&local_4d8);
      if (local_498 != (undefined ***)0x0) {
        (*(code *)(*local_498)[4])
                  (local_498,CONCAT71((int7)((ulonglong)local_4d0 >> 8),local_498 != local_4d0));
        local_498 = (undefined ***)0x0;
      }
      ArtDoc::VisitorBase::~VisitorBase((VisitorBase *)&local_4d8);
      local_660 = pGStack_5f0;
      ppuVar33 = ppuStack_680;
      uVar35 = 0;
      if (local_5f8 != pGStack_5f0) {
        uVar26 = 0;
        auVar42._8_8_ = 0;
        auVar42._0_8_ = local_658._0_8_;
        pGVar21 = local_5f8;
        dVar37 = local_648;
        dVar43 = dStack_640;
        dVar36 = (double)local_658._8_8_;
        do {
          (**(code **)(**(longlong **)pGVar21 + 0x28))(*(longlong **)pGVar21,&local_488);
          (**(code **)(**(longlong **)pGVar21 + 0x18))(*(longlong **)pGVar21,&local_6b8);
          (**(code **)(**(longlong **)pGVar21 + 0x20))(*(longlong **)pGVar21,&local_6a8);
          if (local_6b8 == (Compound *)0x0) {
LAB_18013fa8d:
            if (local_6a8 != (longlong *)0x0) {
              FUN_180137b30(local_6a8,local_6a0,&local_6a8);
              plVar19 = local_6a8;
              if ((0xfff < (ulonglong)((((longlong)local_698 - (longlong)local_6a8) / 0x18) * 0x18))
                 && (plVar19 = (longlong *)local_6a8[-1],
                    0x1f < (ulonglong)((longlong)local_6a8 + (-8 - (longlong)plVar19)))) {
LAB_18013fbe3:
                    /* WARNING: Subroutine does not return */
                _invalid_parameter_noinfo_noreturn();
              }
LAB_18013fb05:
              free(plVar19);
              local_6a8 = (longlong *)0x0;
              local_698 = 0.0;
              local_6a0 = (longlong *)0x0;
            }
          }
          else {
            bVar15 = YAGL::Compound::IsEmpty(local_6b8);
            puVar14 = local_468;
            puVar13 = puStack_470;
            puVar41 = local_478;
            puVar40 = puStack_480;
            puVar38 = local_488;
            pCVar12 = local_6b8;
            if ((bVar15) || (local_6a8 == local_6a0)) goto LAB_18013fa8d;
            local_5c8 = local_488;
            puStack_5c0 = puStack_480;
            local_5b8 = local_478;
            puStack_5b0 = puStack_470;
            puVar9 = (undefined *)CONCAT71(uStack_45f,cStack_460);
            local_5a8 = local_468;
            if (CONCAT44(uStack_6ac,uStack_6b0) != 0) {
              LOCK();
              piVar1 = (int *)(CONCAT44(uStack_6ac,uStack_6b0) + 8);
              *piVar1 = *piVar1 + 1;
              UNLOCK();
            }
            puVar31 = (undefined *)CONCAT44(uStack_6ac,uStack_6b0);
            local_598 = local_6b8;
            local_588 = (longlong *)0x0;
            plStack_580 = (longlong *)0x0;
            local_578 = (longlong *)0x0;
            uVar7 = ((longlong)local_6a0 - (longlong)local_6a8) / 0x18;
            plVar19 = (longlong *)0x0;
            puStack_5a0 = puVar9;
            puStack_590 = puVar31;
            if (uVar7 != 0) {
              if (0xaaaaaaaaaaaaaaa < uVar7) {
                    /* WARNING: Subroutine does not return */
                FUN_1800193a0();
              }
              uVar4 = uVar7 * 0x18;
              if (uVar4 != 0) {
                if (uVar4 < 0x1000) {
                  plVar19 = (longlong *)FUN_1802d6b50(uVar4);
                }
                else {
                  if (uVar4 + 0x27 <= uVar4) {
                    /* WARNING: Subroutine does not return */
                    FUN_180019130();
                  }
                  lVar22 = FUN_1802d6b50();
                  if (lVar22 == 0) {
                    /* WARNING: Subroutine does not return */
                    _invalid_parameter_noinfo_noreturn();
                  }
                  plVar19 = (longlong *)(lVar22 + 0x27U & 0xffffffffffffffe0);
                  plVar19[-1] = lVar22;
                }
              }
              local_578 = plVar19 + uVar7 * 3;
              plStack_580 = plVar19;
              if (local_6a8 != local_6a0) {
                plVar29 = local_6a8 + 1;
                do {
                  *plStack_580 = 0;
                  plStack_580[1] = 0;
                  if (*plVar29 != 0) {
                    LOCK();
                    piVar1 = (int *)(*plVar29 + 8);
                    *piVar1 = *piVar1 + 1;
                    UNLOCK();
                  }
                  *plStack_580 = plVar29[-1];
                  plStack_580[1] = *plVar29;
                  plStack_580[2] = plVar29[1];
                  plStack_580 = plStack_580 + 3;
                  plVar30 = plVar29 + 2;
                  plVar29 = plVar29 + 3;
                } while (plVar30 != local_6a0);
              }
              local_588 = plVar19;
            }
            plVar30 = local_578;
            plVar29 = plStack_580;
            plVar19 = local_588;
            if (ppuVar33 == ppuStack_678) {
              FUN_180137e20(&local_688,ppuVar33,&local_5c8);
            }
            else {
              *ppuVar33 = puVar38;
              ppuVar33[1] = puVar40;
              ppuVar33[2] = puVar41;
              ppuVar33[3] = puVar13;
              ppuVar33[4] = puVar14;
              ppuVar33[5] = puVar9;
              ppuVar33[6] = pCVar12;
              ppuVar33[7] = puVar31;
              local_598 = (Compound *)0x0;
              puStack_590 = (undefined *)0x0;
              local_578 = (longlong *)0x0;
              plStack_580 = (longlong *)0x0;
              local_588 = (longlong *)0x0;
              ppuVar33[8] = (undefined *)plVar19;
              ppuVar33[9] = (undefined *)plVar29;
              ppuVar33[10] = (undefined *)plVar30;
              ppuStack_680 = ppuVar33 + 0xb;
            }
            plVar29 = local_578;
            plVar19 = local_588;
            ppuVar33 = ppuStack_680;
            if (local_588 != (longlong *)0x0) {
              FUN_180137b30(local_588,plStack_580,&local_588);
              plVar30 = plVar19;
              if ((0xfff < (ulonglong)((((longlong)plVar29 - (longlong)plVar19) / 0x18) * 0x18)) &&
                 (plVar30 = (longlong *)plVar19[-1],
                 0x1f < (ulonglong)((longlong)plVar19 + (-8 - (longlong)plVar30)))) {
                    /* WARNING: Subroutine does not return */
                _invalid_parameter_noinfo_noreturn();
              }
              free(plVar30);
              local_588 = (longlong *)0x0;
              plStack_580 = (longlong *)0x0;
              local_578 = (longlong *)0x0;
            }
            FUN_180013ed0(&local_598);
            if (CONCAT44(uStack_6ac,uStack_6b0) != 0) {
              LOCK();
              piVar1 = (int *)(CONCAT44(uStack_6ac,uStack_6b0) + 8);
              *piVar1 = *piVar1 + 1;
              UNLOCK();
            }
            plStack_600 = (longlong *)CONCAT44(uStack_6ac,uStack_6b0);
            local_608 = local_6b8;
            puVar16 = (undefined8 *)YAGL::operator*(&local_5d8,&local_488,&local_608);
            pauVar23 = (undefined1 (*) [16])YAGL::Compound::GetBoundingBox((Compound *)*puVar16);
            plVar19 = plStack_5d0;
            if (cVar32 == '\0') {
              if (pauVar23[2][0] == '\0') {
                if (*(double *)*pauVar23 < auVar42._0_8_) {
                  dVar37 = (auVar42._0_8_ + local_648) - *(double *)*pauVar23;
                  cVar32 = '\0';
                  local_638 = (undefined *)((ulonglong)local_638 & 0xffffffffffffff00);
                  local_658._0_8_ = *(ulonglong *)*pauVar23;
                  auVar42._8_8_ = 0;
                  auVar42._0_8_ = *(ulonglong *)*pauVar23;
                  local_648 = dVar37;
                }
                dVar6 = (*(double *)pauVar23[1] + *(double *)*pauVar23) - auVar42._0_8_;
                if ((dVar37 <= dVar6) && (dVar37 < dVar6)) {
                  dVar37 = (*(double *)pauVar23[1] + *(double *)*pauVar23) - auVar42._0_8_;
                  cVar32 = '\0';
                  local_638 = (undefined *)((ulonglong)local_638 & 0xffffffffffffff00);
                  local_648 = dVar37;
                }
                if (*(double *)(*pauVar23 + 8) < dVar36) {
                  dVar43 = (dVar36 + dStack_640) - *(double *)(*pauVar23 + 8);
                  cVar32 = '\0';
                  local_638 = (undefined *)((ulonglong)local_638 & 0xffffffffffffff00);
                  dVar36 = *(double *)(*pauVar23 + 8);
                  local_658._8_8_ = dVar36;
                  uVar26 = 0;
                  dStack_640 = dVar43;
                }
                local_6e0 = *(longlong **)(*pauVar23 + 8);
                dVar6 = (*(double *)(pauVar23[1] + 8) + (double)local_6e0) - dVar36;
                if ((dVar43 <= dVar6) && (dVar43 < dVar6)) {
                  dVar43 = (*(double *)(pauVar23[1] + 8) + (double)local_6e0) - dVar36;
                  cVar32 = '\0';
                  local_638 = (undefined *)((ulonglong)local_638 & 0xffffffffffffff00);
                  dStack_640 = dVar43;
                }
              }
            }
            else {
              auVar42 = *pauVar23;
              dVar37 = *(double *)pauVar23[1];
              dVar43 = *(double *)(pauVar23[1] + 8);
              local_638 = *(undefined **)pauVar23[2];
              auVar8._4_8_ = uVar26;
              auVar8._0_4_ = auVar42._4_4_;
              auVar44._0_8_ = auVar8._0_8_ << 0x20;
              auVar44._8_4_ = auVar42._8_4_;
              auVar44._12_4_ = auVar42._12_4_;
              dVar36 = auVar44._8_8_;
              uVar26 = auVar42._8_8_;
              cVar32 = (char)local_638;
              local_658 = auVar42;
              local_648 = dVar37;
              dStack_640 = dVar43;
            }
            if (plStack_5d0 != (longlong *)0x0) {
              LOCK();
              plVar29 = plStack_5d0 + 1;
              lVar22 = *plVar29;
              *(int *)plVar29 = (int)*plVar29 + -1;
              UNLOCK();
              if ((int)lVar22 == 1) {
                (**(code **)*plStack_5d0)(plStack_5d0);
                LOCK();
                piVar1 = (int *)((longlong)plVar19 + 0xc);
                iVar5 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar5 == 1) {
                  (**(code **)(*plVar19 + 8))(plVar19);
                }
              }
            }
            plVar29 = local_6a0;
            plVar19 = local_6a8;
            if (local_6a8 != (longlong *)0x0) {
              for (; plVar19 != plVar29; plVar19 = plVar19 + 3) {
                plVar30 = (longlong *)plVar19[1];
                if (plVar30 != (longlong *)0x0) {
                  LOCK();
                  plVar2 = plVar30 + 1;
                  lVar22 = *plVar2;
                  *(int *)plVar2 = (int)*plVar2 + -1;
                  UNLOCK();
                  if ((int)lVar22 == 1) {
                    (**(code **)*plVar30)(plVar30);
                    LOCK();
                    piVar1 = (int *)((longlong)plVar30 + 0xc);
                    iVar5 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar5 == 1) {
                      (**(code **)(*plVar30 + 8))(plVar30);
                    }
                  }
                }
              }
              plVar19 = local_6a8;
              if ((0xfff < (ulonglong)((((longlong)local_698 - (longlong)local_6a8) / 0x18) * 0x18))
                 && (plVar19 = (longlong *)local_6a8[-1],
                    0x1f < (ulonglong)((longlong)local_6a8 + (-8 - (longlong)plVar19))))
              goto LAB_18013fbe3;
              goto LAB_18013fb05;
            }
          }
          plVar19 = (longlong *)CONCAT44(uStack_6ac,uStack_6b0);
          if (plVar19 != (longlong *)0x0) {
            LOCK();
            plVar29 = plVar19 + 1;
            lVar22 = *plVar29;
            *(int *)plVar29 = (int)*plVar29 + -1;
            UNLOCK();
            if ((int)lVar22 == 1) {
              (**(code **)*plVar19)(plVar19);
              LOCK();
              piVar1 = (int *)((longlong)plVar19 + 0xc);
              iVar5 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar5 == 1) {
                (**(code **)(*plVar19 + 8))(plVar19);
              }
            }
          }
          pGVar21 = pGVar21 + 8;
        } while (pGVar21 != local_660);
        this = local_628;
        uVar35 = (undefined4)local_668;
      }
      local_668 = (Group *)(CONCAT44(local_668._4_4_,uVar35) & 0xfffffffffffffffd);
      if (local_5f8 != (Group *)0x0) {
        pGVar21 = local_5f8;
        if ((0xfff < (ulonglong)((local_5e8 - (longlong)local_5f8 >> 3) * 8)) &&
           (pGVar21 = *(Group **)(local_5f8 + -8),
           (Group *)0x1f < local_5f8 + (-8 - (longlong)pGVar21))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pGVar21);
      }
      ppuVar24 = local_688;
      if (local_688 == ppuVar33) {
        local_6d0 = local_620;
        pdVar25 = local_620;
      }
      else {
        uVar35 = *(undefined4 *)(this + 0x790);
        if (*(int *)(this + 0x794) != 2) {
          local_6e8 = (double)CONCAT44(local_6e8._4_4_,uVar35);
          uStack_6b0 = uVar35;
          ppuVar10 = local_688;
          local_6b8 = *(Compound **)(this + 0x790);
          ppuVar11 = local_688;
          while (ppuVar11 = ppuVar11 + 0xb, ppuVar11 != ppuVar33) {
            FUN_18013af70(&uStack_6b0,&local_6e0,ppuVar10);
            FUN_18013af70(&uStack_6b0,&local_660,ppuVar11);
            if ((local_6b8._4_4_ == 0) == ((int)local_6b8 == 1)) {
              if ((double)local_660 <= (double)local_6e0) {
                if ((double)local_6e0 <= (double)local_660) {
                  if ((double)local_6e0 == (double)local_660) {
                    bVar15 = false;
                  }
                  else {
                    bVar15 = false;
                  }
                }
                else {
                  bVar15 = false;
                }
              }
              else {
                bVar15 = true;
              }
            }
            else {
              if ((double)local_660 <= (double)local_6e0) {
                if ((double)local_6e0 <= (double)local_660) {
                  if ((double)local_6e0 == (double)local_660) {
                    cVar32 = '\0';
                  }
                  else {
                    cVar32 = -0x80;
                  }
                }
                else {
                  cVar32 = '\x01';
                }
              }
              else {
                cVar32 = -1;
              }
              bVar15 = '\0' < cVar32;
            }
            if (bVar15) {
              ppuVar10 = ppuVar11;
            }
          }
          FUN_18013af70(&local_6e8,&local_6e0,ppuVar10);
          local_608 = (Compound *)CONCAT44(local_608._4_4_,uVar35);
          plStack_600 = local_6e0;
          local_5d8 = local_608;
          plStack_5d0 = local_6e0;
          ppuVar24 = (undefined **)FUN_18013a1b0(ppuVar24,ppuVar33,&local_5d8);
          if (ppuVar24 != ppuVar33) {
            ppuVar24 = (undefined **)FUN_180138780(ppuVar33,ppuVar33,ppuVar24);
            FUN_180137ab0(ppuVar24,ppuVar33,&local_688);
            ppuStack_680 = ppuVar24;
          }
          this = local_628;
        }
        local_6e0 = (longlong *)0x40ebae9d3a74e9d4;
        FUN_18013c230(&local_5f8,&local_688,&local_6e0,*(undefined4 *)(this + 0x790));
        ppdVar20 = (double **)
                   FUN_18013d350(&local_6a8,&local_5f8,*(undefined4 *)(this + 0x790),
                                 *(undefined4 *)(this + 0x794));
        if (&local_620 != ppdVar20) {
          local_620 = *ppdVar20;
          pdStack_618 = ppdVar20[1];
          local_6c8 = (PDFPlusCutMark *)ppdVar20[2];
          *ppdVar20 = (double *)0x0;
          ppdVar20[1] = (double *)0x0;
          ppdVar20[2] = (double *)0x0;
          local_610 = (double *)local_6c8;
        }
        pdVar25 = local_620;
        local_6d0 = local_620;
        if (local_6a8 != (longlong *)0x0) {
          plVar19 = local_6a8;
          if ((0xfff < ((longlong)local_698 - (longlong)local_6a8 & 0xffffffffffffffe0U)) &&
             (plVar19 = (longlong *)local_6a8[-1],
             0x1f < (ulonglong)((longlong)local_6a8 + (-8 - (longlong)plVar19)))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(plVar19);
        }
        if (local_5f8 != (Group *)0x0) {
          pGVar21 = local_5f8;
          if ((0xfff < (ulonglong)((local_5e8 - (longlong)local_5f8 >> 3) * 8)) &&
             (pGVar21 = *(Group **)(local_5f8 + -8),
             (Group *)0x1f < local_5f8 + (-8 - (longlong)pGVar21))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(pGVar21);
        }
        ppuVar33 = ppuStack_680;
      }
      ppuVar24 = local_688;
      if (local_688 != (undefined **)0x0) {
        FUN_180137ab0(local_688,ppuVar33,&local_688);
        ppuVar33 = ppuVar24;
        if ((0xfff < (ulonglong)((((longlong)ppuStack_678 - (longlong)ppuVar24) / 0x58) * 0x58)) &&
           (ppuVar33 = (undefined **)ppuVar24[-1],
           0x1f < (ulonglong)((longlong)ppuVar24 + (-8 - (longlong)ppuVar33)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(ppuVar33);
      }
      goto LAB_18013f247;
    }
    pdVar25 = (double *)GetReferenceBox(this);
    auVar39._0_8_ = *pdVar25 * 127.0;
    auVar39._8_8_ = pdVar25[1] * 127.0;
    local_658 = divpd(auVar39,_DAT_1803082f0);
    dVar36 = (pdVar25[2] * 127.0) / 360000.0;
    dVar37 = (pdVar25[3] * 127.0) / 360000.0;
    if (dVar36 < 0.0) goto LAB_1801406e3;
    if (dVar36 <= 0.0) {
      if (dVar36 == 0.0) {
        cVar32 = '\0';
      }
      else {
        cVar32 = -0x80;
      }
    }
    else {
      cVar32 = -1;
    }
    if ((-1 < cVar32) || (dVar37 < 0.0)) goto LAB_1801406e3;
    if (dVar37 <= 0.0) {
      if (dVar37 == 0.0) {
        cVar32 = '\0';
      }
      else {
        cVar32 = -0x80;
      }
    }
    else {
      cVar32 = -1;
    }
    if (-1 < cVar32) goto LAB_1801406e3;
    local_698 = dVar36 + (double)local_658._0_8_;
    local_6d8 = local_658._8_8_;
    local_6a8 = (longlong *)local_658._0_8_;
    local_6a0 = (longlong *)(dVar37 + (double)local_6d8);
    local_688 = dm::MarkPositionVector::vftable;
    ppuStack_680 = (undefined **)0x0;
    ppuStack_678 = (undefined **)0x0;
    local_670 = 0;
    local_690 = (double)local_6d8;
    FUN_1802a26c0(local_570,&local_6a8,&local_688);
    uVar26 = FUN_18013d660(&local_5f8,&local_688);
    FUN_18013ae40(&local_620,uVar26);
    FUN_18013aaa0(&local_5f8);
    FUN_18004a7b0(&local_688);
    local_6c8 = (PDFPlusCutMark *)local_610;
    local_6d0 = local_620;
    pdVar25 = local_620;
  }
  else {
    pCVar17 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
    pCVar18 = ArtDoc::Content::GetObjectWithID(pCVar17,*(__uint64 *)(this + 0x708));
    plVar19 = (longlong *)
              __RTDynamicCast(pCVar18,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                              &GridInterface::RTTI_Type_Descriptor);
    if (plVar19 == (longlong *)0x0) goto LAB_18013f2be;
    (**(code **)(*plVar19 + 8))(plVar19,&local_488);
    local_688 = dm::MarkPositionVector::vftable;
    ppuStack_680 = (undefined **)0x0;
    ppuStack_678 = (undefined **)0x0;
    local_670 = 0;
    FUN_1802a2780(local_570,&local_488,&local_688);
    ppdVar20 = (double **)FUN_18013d660(&local_5f8,&local_688);
    if (&local_620 != ppdVar20) {
      local_620 = *ppdVar20;
      pdStack_618 = ppdVar20[1];
      local_6c8 = (PDFPlusCutMark *)ppdVar20[2];
      *ppdVar20 = (double *)0x0;
      ppdVar20[1] = (double *)0x0;
      ppdVar20[2] = (double *)0x0;
      local_610 = (double *)local_6c8;
    }
    pdVar25 = local_620;
    local_6d0 = local_620;
    if (local_5f8 != (Group *)0x0) {
      pGVar21 = local_5f8;
      if ((0xfff < (local_5e8 - (longlong)local_5f8 & 0xffffffffffffffe0U)) &&
         (pGVar21 = *(Group **)(local_5f8 + -8),
         (Group *)0x1f < local_5f8 + (-8 - (longlong)pGVar21))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pGVar21);
    }
    FUN_18004a7b0(&local_688);
LAB_18013f247:
  }
  if (pdVar25 != pdStack_618) {
    pdVar25 = pdVar25 + 1;
    do {
      pGVar21 = (Group *)FUN_1802d6b50(0x2d0);
      local_668 = pGVar21;
      if (pGVar21 == (Group *)0x0) {
        pGVar21 = (Group *)0x0;
      }
      else {
        ArtDoc::Group::Group(pGVar21,0x1ff);
        *(undefined ***)pGVar21 = ArtDoc::Group::vftable;
        *(undefined ***)(pGVar21 + 0x20) = ArtDoc::Group::vftable;
      }
      local_388[0] = std::
                     _Func_impl_no_alloc<`protected:_virtual_void___cdecl_DocumentMarks::PDFPlusCutMark::regenerateMarkImp(void)___ptr64'::`42'::<lambda_3>,bool,ArtDoc::Group_const&___ptr64>
                     ::vftable;
      local_350 = local_388;
      local_3c8[0] = std::
                     _Func_impl_no_alloc<`protected:_virtual_void___cdecl_DocumentMarks::PDFPlusCutMark::regenerateMarkImp(void)___ptr64'::`42'::<lambda_2>,bool,ArtDoc::Group_const&___ptr64>
                     ::vftable;
      local_390 = local_3c8;
      local_408[0] = std::
                     _Func_impl_no_alloc<`protected:_virtual_void___cdecl_DocumentMarks::PDFPlusCutMark::regenerateMarkImp(void)___ptr64'::`42'::<lambda_1>,bool,ArtDoc::Layer_const&___ptr64>
                     ::vftable;
      local_3d0 = local_408;
      local_660 = pGVar21;
      pCVar17 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
      pDVar27 = ArtDoc::Content::GetDocument(pCVar17);
      DocumentEdit::Expander::Expander
                (local_348,pGVar21,pDVar27,
                 (function<bool___cdecl(ArtDoc::Layer_const&___ptr64)> *)local_408,
                 (function<bool___cdecl(ArtDoc::Group_const&___ptr64)> *)local_3c8,
                 (function<bool___cdecl(ArtDoc::Group_const&___ptr64)> *)local_388);
      if (local_3d0 != (undefined ***)0x0) {
        (*(code *)(*local_3d0)[4])
                  (local_3d0,CONCAT71((int7)((ulonglong)local_408 >> 8),local_3d0 != local_408));
        local_3d0 = (undefined ***)0x0;
      }
      if (local_390 != (undefined ***)0x0) {
        (*(code *)(*local_390)[4])
                  (local_390,CONCAT71((int7)((ulonglong)local_3c8 >> 8),local_390 != local_3c8));
        local_390 = (undefined ***)0x0;
      }
      if (local_350 != (undefined ***)0x0) {
        (*(code *)(*local_350)[4])
                  (local_350,CONCAT71((int7)((ulonglong)local_388 >> 8),local_350 != local_388));
        local_350 = (undefined ***)0x0;
      }
      puVar16 = (undefined8 *)DynamicMark::GetSourceContent((DynamicMark *)this);
      pCVar17 = ArtPaint::FormPaint::GetContent((FormPaint *)*puVar16);
      (**(code **)(*(longlong *)pCVar17 + 8))(pCVar17,local_348);
      plVar19 = plStack_5d0;
      if (plStack_5d0 != (longlong *)0x0) {
        LOCK();
        plVar29 = plStack_5d0 + 1;
        lVar22 = *plVar29;
        *(int *)plVar29 = (int)*plVar29 + -1;
        UNLOCK();
        if ((int)lVar22 == 1) {
          (**(code **)*plStack_5d0)(plStack_5d0);
          LOCK();
          piVar1 = (int *)((longlong)plVar19 + 0xc);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 == 1) {
            (**(code **)(*plVar19 + 8))(plVar19);
          }
        }
      }
      local_6e0 = (longlong *)pdVar25[1];
      local_6d8 = (PDFPlusCutMark *)pdVar25[2];
      dVar36 = atan2((double)local_6d8 - *pdVar25,(double)local_6e0 - pdVar25[-1]);
      dVar37 = cos(dVar36);
      local_658._8_8_ = sin(dVar36);
      local_658._0_8_ = dVar37;
      local_648 = -(double)local_658._8_8_;
      local_638 = (undefined *)0x0;
      dStack_630 = 0.0;
      dStack_640 = dVar37;
      ArtDoc::Transformable::SetTransformation
                ((Transformable *)pGVar21,
                 (TransformationBase<YAGL::MilliPointCoordinateSystem> *)local_658,7);
      GetPDFPlusBoundingBox((Visitable *)&local_488);
      if (cStack_460 == '\0') {
        puVar41 = (undefined *)0x0;
        local_6d8 = (PDFPlusCutMark *)0x0;
        puVar38 = (undefined *)0x0;
        puVar40 = (undefined *)0x0;
        local_638 = (undefined *)CONCAT71(local_638._1_7_,1);
      }
      else {
        local_638 = local_468;
        puVar38 = local_478;
        puVar40 = puStack_470;
        puVar41 = local_488;
        local_6d8 = (PDFPlusCutMark *)puStack_480;
      }
      local_6e8 = pdVar25[-1] - (double)puVar41;
      if (pdVar25[-1] == pdVar25[1]) {
        local_6e8 = local_6e8 - (double)puVar38 * 0.5;
      }
      else if (pdVar25[1] < pdVar25[-1]) {
        local_6e8 = local_6e8 - (double)puVar38;
      }
      dVar43 = local_6e8;
      local_6e8 = *pdVar25 - ((double)puVar40 + (double)local_6d8);
      dVar36 = *pdVar25;
      dVar37 = pdVar25[2];
      if (dVar36 == dVar37) {
        local_6e8 = local_6e8 + (double)puVar40 * 0.5;
        local_6d8 = (PDFPlusCutMark *)puVar40;
      }
      else if ((dVar36 <= dVar37) && (dVar36 < dVar37)) {
        local_6e8 = local_6e8 + (double)puVar40;
      }
      dVar36 = local_6e8;
      pTVar28 = ArtDoc::Transformable::GetTransformation((Transformable *)pGVar21);
      local_638 = (undefined *)dVar43;
      dStack_630 = dVar36;
      local_5c8 = (undefined *)(*(double *)(pTVar28 + 8) * 0.0 + *(double *)pTVar28);
      puStack_5c0 = (undefined *)(*(double *)pTVar28 * 0.0 + *(double *)(pTVar28 + 8));
      local_5b8 = (undefined *)(*(double *)(pTVar28 + 0x18) * 0.0 + *(double *)(pTVar28 + 0x10));
      puStack_5b0 = (undefined *)(*(double *)(pTVar28 + 0x10) * 0.0 + *(double *)(pTVar28 + 0x18));
      local_5a8 = (undefined *)
                  (dVar43 + *(double *)(pTVar28 + 0x28) * 0.0 + *(double *)(pTVar28 + 0x20));
      local_6e0 = *(longlong **)(pTVar28 + 0x28);
      local_6d8 = *(PDFPlusCutMark **)(pTVar28 + 0x20);
      puStack_5a0 = (undefined *)(dVar36 + (double)local_6e0 + (double)local_6d8 * 0.0);
      ArtDoc::Transformable::SetTransformation
                ((Transformable *)pGVar21,
                 (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_5c8,7);
      this = local_628;
      pCVar17 = ArtDoc::ContentObject::GetContent((ContentObject *)local_628);
      pDVar27 = ArtDoc::Content::GetDocument(pCVar17);
      ArtDoc::ActionGroupCreator::ActionGroupCreator
                ((ActionGroupCreator *)&local_608,pDVar27,false,false);
      local_660 = (Group *)0x0;
      pCVar18 = DocumentEdit::InsertNewObjectOnTop((ContentObject *)pGVar21,(Group *)this,true);
      DynamicMark::ApplyPDFPlusColor((DynamicMark *)this,pCVar18);
      ArtDoc::ActionGroupCreator::~ActionGroupCreator((ActionGroupCreator *)&local_608);
      DocumentEdit::Expander::~Expander(local_348);
      pdVar34 = pdVar25 + 3;
      pdVar25 = pdVar25 + 4;
    } while (pdVar34 != pdStack_618);
    pdVar25 = local_6d0;
  }
  if (pdVar25 != (double *)0x0) {
    pdVar34 = pdVar25;
    if ((0xfff < ((longlong)local_6c8 - (longlong)pdVar25 & 0xffffffffffffffe0U)) &&
       (pdVar34 = (double *)pdVar25[-1],
       0x1f < (ulonglong)((longlong)pdVar25 + (-8 - (longlong)pdVar34)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pdVar34);
  }
LAB_1801406e3:
  FUN_1802a0fa0(local_570);
  return;
}



// ---------------------------------------------------------------
// FUNC 180172550 FUN_180172550
// signature: undefined FUN_180172550(void)
// ---------------------------------------------------------------

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Removing unreachable block (ram,0x000180172ff8) */
/* WARNING: Removing unreachable block (ram,0x000180174e6e) */
/* WARNING: Removing unreachable block (ram,0x000180174b07) */
/* WARNING: Removing unreachable block (ram,0x00018017796d) */
/* WARNING: Removing unreachable block (ram,0x000180175af2) */
/* WARNING: Removing unreachable block (ram,0x00018017481d) */
/* WARNING: Type propagation algorithm not settling */

longlong * FUN_180172550(MarkReader *param_1,longlong *param_2)

{
  int *piVar1;
  size_t _Size;
  Document *pDVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  code *pcVar5;
  void *pvVar6;
  longlong lVar7;
  DynamicObject *pDVar8;
  TextAreaMark *pTVar9;
  TextOnPathMark *pTVar10;
  DynamicMark *pDVar11;
  PDFPlusRepeatForGridMark *pPVar12;
  bool bVar13;
  bool bVar14;
  char cVar15;
  byte bVar16;
  Type TVar17;
  int iVar18;
  uint uVar19;
  TextFittingStyle TVar20;
  ColorType CVar21;
  Type TVar22;
  Dictionary *pDVar23;
  Content *pCVar24;
  PropertiesWithNotification *pPVar25;
  undefined8 *_Buf2;
  undefined8 uVar26;
  GADict *pGVar27;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar28;
  longlong *plVar29;
  Module *pMVar30;
  MarksModule *this;
  int *******pppppppiVar31;
  ulonglong *puVar32;
  DynamicTextObject *pDVar33;
  GANumber *pGVar34;
  GAName *this_00;
  ContentObject *this_01;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar35;
  List<ArtDoc::ContentObject> *pLVar36;
  ContentObject *pCVar37;
  Factory *this_02;
  Properties *pPVar38;
  GAObject *pGVar39;
  ColorList<ArtColor::ColorSpacePolicy> *pCVar40;
  variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
  *pvVar41;
  longlong lVar42;
  Parameters *this_03;
  Errors *this_04;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar43;
  int *******pppppppiVar44;
  void *pvVar45;
  undefined8 *******pppppppuVar46;
  undefined8 *puVar47;
  undefined8 *puVar48;
  longlong lVar49;
  longlong *plVar50;
  uint uVar51;
  ulonglong _Size_00;
  undefined4 uVar52;
  double dVar53;
  undefined4 uVar54;
  undefined4 uVar55;
  undefined1 auStack_1d78 [32];
  undefined8 local_1d58;
  GAObject local_1d48 [8];
  char local_1d40;
  byte local_1d3f;
  uint local_1d3c;
  uint local_1d38;
  GADict *local_1d28;
  GADict *pGStack_1d20;
  undefined8 local_1d18;
  Error *local_1d08;
  longlong *plStack_1d00;
  DynamicObject *local_1cf8;
  TextAreaMark *local_1cf0;
  TextOnPathMark *local_1ce8;
  DynamicTextObject *local_1ce0;
  DynamicMark *local_1cd8;
  DynamicMark *local_1cd0;
  DynamicObject *local_1cc8;
  Dictionary *local_1cc0;
  PDFPlusRepeatForGridMark *local_1cb8;
  DynamicObject *local_1cb0;
  undefined1 local_1ca8;
  undefined1 local_1ca7;
  undefined1 local_1ca6;
  undefined1 local_1ca5;
  undefined1 local_1ca4;
  undefined1 local_1ca3;
  undefined1 local_1ca2;
  undefined1 local_1ca1;
  longlong local_1ca0;
  longlong local_1c98;
  DynamicObject *local_1c90;
  DynamicObject *local_1c88;
  PDFPlusRepeatForGridMark *local_1c80;
  longlong local_1c78;
  longlong local_1c70;
  DynamicObject *local_1c68;
  longlong local_1c60;
  GName local_1c58 [8];
  GName local_1c50 [8];
  longlong local_1c48;
  DynamicObject *local_1c40;
  GName local_1c38 [5];
  undefined2 local_1c33;
  undefined1 local_1c31;
  longlong local_1c30;
  GName local_1c28 [8];
  GName local_1c20 [8];
  longlong local_1c18;
  Group *local_1c10;
  GName local_1c08 [8];
  GName local_1c00 [8];
  FormPaint *local_1bf8;
  longlong lStack_1bf0;
  undefined8 local_1be8;
  longlong lStack_1be0;
  undefined8 local_1bd8;
  undefined1 uStack_1bd0;
  undefined7 uStack_1bcf;
  FormPaint *local_1bc8 [2];
  GName local_1bb8 [8];
  GName local_1bb0 [8];
  GName local_1ba8 [8];
  GName local_1ba0 [8];
  GName local_1b98 [8];
  GName local_1b90 [8];
  GName local_1b88 [8];
  GName local_1b80 [8];
  GName local_1b78 [8];
  GName local_1b70 [8];
  GName local_1b68 [8];
  GName local_1b60 [8];
  undefined1 local_1b58 [16];
  FormPaint *local_1b48;
  longlong lStack_1b40;
  undefined1 local_1b38 [16];
  undefined1 local_1b28 [16];
  GName local_1b18 [8];
  GName local_1b10 [8];
  GName local_1b08 [8];
  GName local_1b00 [8];
  GName local_1af8 [8];
  GName local_1af0 [8];
  GName local_1ae8 [8];
  GName local_1ae0 [8];
  GADict local_1ad8 [8];
  GName local_1ad0 [8];
  GName local_1ac8 [8];
  GName local_1ac0 [8];
  GName local_1ab8 [8];
  GName local_1ab0 [8];
  GName local_1aa8 [8];
  GName local_1aa0 [8];
  GName local_1a98 [8];
  GADict local_1a90 [8];
  GName local_1a88 [8];
  GName local_1a80 [8];
  GName local_1a78 [8];
  GName local_1a70 [8];
  GName local_1a68 [8];
  GName local_1a60 [8];
  GName local_1a58 [8];
  GADict local_1a50 [8];
  char *local_1a48;
  char *local_1a40;
  GName local_1a38 [8];
  GName local_1a30 [8];
  GName local_1a28 [8];
  GName local_1a20 [8];
  GName local_1a18 [8];
  GName local_1a10 [8];
  char *local_1a08;
  char *local_1a00;
  GName local_19f8 [8];
  GName local_19f0 [8];
  char *local_19e8;
  GName local_19e0 [8];
  GName local_19d8 [8];
  GName local_19d0 [8];
  GName local_19c8 [8];
  GName local_19c0 [8];
  GName local_19b8 [8];
  GName local_19b0 [8];
  GName local_19a8 [8];
  char *local_19a0;
  GName local_1998 [8];
  GName local_1990 [8];
  GName local_1988 [8];
  char *local_1980;
  GName local_1978 [8];
  GName local_1970 [8];
  GName local_1968 [8];
  DynamicObject **local_1960;
  GName local_1958 [8];
  GName local_1950 [8];
  GName local_1948 [8];
  char *local_1940;
  GName local_1938 [8];
  DynamicObject **local_1930;
  char *local_1928;
  GName local_1920 [8];
  GName local_1918 [8];
  char *local_1910;
  GName local_1908 [8];
  GName local_1900 [8];
  GName local_18f8 [8];
  MarkReader *local_18f0;
  longlong *local_18e8;
  GName local_18e0 [8];
  GName local_18d8 [8];
  GAObject local_18d0 [8];
  char *local_18c8;
  GADict local_18c0 [8];
  GName local_18b8 [8];
  char *local_18b0;
  GName local_18a8 [8];
  GName local_18a0 [8];
  char *local_1898 [2];
  undefined8 local_1888;
  longlong lStack_1880;
  undefined8 local_1878;
  longlong lStack_1870;
  FormPaint *local_1868;
  longlong lStack_1860;
  FormPaint *local_1858;
  longlong lStack_1850;
  FormPaint *local_1848;
  longlong lStack_1840;
  undefined8 local_1838;
  longlong lStack_1830;
  undefined8 local_1828;
  longlong lStack_1820;
  undefined8 local_1818;
  longlong lStack_1810;
  undefined8 local_1808;
  longlong lStack_1800;
  Error *local_17f8;
  longlong *plStack_17f0;
  longlong local_17e8;
  longlong lStack_17e0;
  undefined8 local_17d8;
  BarCode *local_17d0;
  longlong local_17c8 [2];
  undefined8 local_17b8;
  longlong local_17b0 [2];
  undefined1 local_17a0 [16];
  FormPaint *local_1790 [3];
  GADict *local_1778;
  GADict *pGStack_1770;
  undefined1 local_1768 [16];
  FormPaint *local_1758 [2];
  GADict *local_1748;
  GADict *pGStack_1740;
  GADict *local_1738;
  GADict *pGStack_1730;
  GADict *local_1728;
  ulonglong *puStack_1720;
  GADict *local_1718;
  GADict *pGStack_1710;
  GADict *local_1708;
  undefined1 *puStack_1700;
  GADict *local_16f8;
  GADict *pGStack_16f0;
  undefined1 local_16e8 [16];
  GADict *local_16d8;
  undefined1 *puStack_16d0;
  VisitorBase local_16c8 [8];
  undefined **local_16c0;
  DynamicMark *local_16b8;
  VisitorBase local_16a8 [8];
  undefined **local_16a0;
  DynamicMark *local_1698;
  undefined **local_1688;
  longlong *local_1680;
  undefined ***local_1650;
  undefined1 local_1648 [16];
  undefined1 local_1638 [16];
  undefined1 local_1628 [16];
  undefined1 local_1618 [16];
  undefined1 local_1608 [16];
  undefined1 local_15f8 [16];
  undefined1 local_15e8 [16];
  undefined1 local_15d8 [16];
  undefined1 local_15c8 [16];
  undefined1 local_15b8 [16];
  undefined1 local_15a8 [16];
  undefined1 local_1598 [16];
  undefined1 local_1588 [16];
  undefined1 local_1578 [16];
  undefined1 local_1568 [16];
  undefined1 local_1558 [16];
  undefined1 local_1548 [16];
  undefined1 local_1538 [16];
  undefined1 local_1528 [16];
  undefined1 local_1518 [16];
  undefined1 local_1508 [16];
  undefined1 local_14f8 [16];
  undefined8 local_14e8;
  undefined8 uStack_14e0;
  undefined1 local_14d8 [16];
  undefined1 local_14c8 [16];
  undefined1 local_14b8 [16];
  undefined1 local_14a8 [16];
  undefined1 local_1498 [16];
  undefined1 local_1488 [24];
  undefined1 local_1470 [24];
  undefined1 local_1458 [24];
  undefined1 local_1440 [24];
  undefined1 local_1428 [24];
  undefined1 local_1410 [24];
  undefined1 local_13f8 [24];
  undefined1 local_13e0 [40];
  undefined4 local_13b8 [2];
  longlong local_13b0;
  undefined8 uStack_13a8;
  uint local_13a0;
  undefined1 local_1398;
  undefined1 local_1390 [8];
  longlong local_1388;
  undefined1 local_1378 [8];
  undefined1 local_1370 [40];
  undefined1 local_1348 [40];
  undefined1 local_1320 [40];
  undefined4 local_12f8;
  char local_12f4;
  undefined2 local_12f3;
  undefined1 local_12f1;
  undefined4 local_12f0;
  char local_12ec;
  undefined2 local_12eb;
  undefined1 local_12e9;
  uint local_12e8 [12];
  undefined4 local_12b8 [14];
  undefined1 local_1280;
  undefined8 local_1278;
  longlong lStack_1270;
  void *local_1268;
  undefined8 uStack_1260;
  longlong local_1258;
  undefined1 local_1240;
  undefined8 local_1238;
  undefined8 uStack_1230;
  undefined8 local_1228;
  undefined8 uStack_1220;
  undefined8 local_1218;
  undefined8 uStack_1210;
  undefined4 local_1208 [14];
  undefined1 local_11d0;
  undefined8 local_11c8;
  longlong lStack_11c0;
  undefined8 local_11b8;
  undefined8 uStack_11b0;
  undefined8 local_11a8;
  undefined1 local_1190;
  undefined4 local_1188 [14];
  undefined1 local_1150;
  undefined8 local_1148;
  undefined8 uStack_1140;
  undefined8 local_1138;
  undefined8 uStack_1130;
  undefined8 local_1128;
  undefined1 local_1110;
  undefined1 local_1108 [8];
  undefined1 local_1100 [40];
  undefined1 local_10d8 [40];
  undefined1 local_10b0 [56];
  CloneStrategy local_1078 [144];
  undefined1 local_fe8 [112];
  undefined1 local_f78 [112];
  undefined1 local_f08 [112];
  undefined1 local_e98 [184];
  undefined1 local_de0 [184];
  Factory local_d28 [312];
  int *******local_bf0;
  undefined8 uStack_be8;
  longlong local_be0;
  ulonglong local_bd8;
  void *local_bd0;
  ulonglong uStack_bc8;
  undefined *local_bc0;
  ulonglong uStack_bb8;
  undefined1 local_bb0;
  undefined7 uStack_baf;
  undefined *local_ba0;
  ulonglong uStack_b98;
  undefined8 *******local_b90 [2];
  longlong local_b80;
  ulonglong local_b78;
  ulonglong local_b70;
  undefined4 uStack_b68;
  undefined2 uStack_b64;
  undefined2 uStack_b62;
  undefined *local_b60;
  ulonglong uStack_b58;
  void *local_b50;
  undefined8 uStack_b48;
  undefined *local_b40;
  ulonglong uStack_b38;
  void *local_b30;
  undefined8 uStack_b28;
  undefined *local_b20;
  ulonglong uStack_b18;
  ulonglong local_b10 [2];
  undefined *local_b00;
  ulonglong uStack_af8;
  undefined8 *******local_af0 [2];
  longlong local_ae0;
  ulonglong local_ad8;
  void *local_ad0;
  undefined8 uStack_ac8;
  undefined *local_ac0;
  ulonglong uStack_ab8;
  ulonglong local_ab0 [2];
  undefined *local_aa0;
  ulonglong uStack_a98;
  void *local_a90;
  undefined8 uStack_a88;
  undefined *local_a80;
  ulonglong uStack_a78;
  undefined8 local_a70;
  undefined8 uStack_a68;
  undefined8 local_a60;
  undefined8 uStack_a58;
  undefined8 local_a50;
  undefined8 uStack_a48;
  undefined8 local_a40;
  undefined8 uStack_a38;
  undefined4 local_a30 [2];
  undefined8 local_a28;
  undefined8 uStack_a20;
  undefined *local_a18;
  undefined8 uStack_a10;
  undefined **local_a08;
  TextAreaMark **local_a00;
  undefined ***local_9d0;
  undefined **local_9c8;
  TextOnPathMark **local_9c0;
  undefined ***local_990;
  undefined **local_988;
  DynamicTextObject **local_980;
  undefined ***local_950;
  undefined **local_948;
  undefined **local_940;
  undefined1 local_938 [56];
  undefined ***local_900;
  undefined8 local_8f8;
  undefined8 uStack_8f0;
  undefined8 local_8e8;
  undefined8 uStack_8e0;
  undefined8 local_8d8;
  undefined8 uStack_8d0;
  undefined8 local_8c8;
  undefined8 uStack_8c0;
  undefined8 local_8b8;
  undefined8 uStack_8b0;
  undefined8 local_8a8;
  undefined8 uStack_8a0;
  undefined8 local_898;
  undefined8 uStack_890;
  undefined8 local_888;
  undefined8 uStack_880;
  undefined8 local_878;
  undefined8 uStack_870;
  undefined8 local_868;
  undefined8 uStack_860;
  undefined1 local_858 [32];
  char local_838;
  GAString local_830 [32];
  Content local_810 [32];
  undefined1 local_7f0 [32];
  undefined1 local_7d0 [32];
  undefined1 local_7b0 [32];
  GAName local_790 [40];
  GADict local_768 [32];
  undefined1 local_748 [32];
  undefined1 local_728 [32];
  undefined1 local_708 [32];
  undefined1 local_6e8 [8];
  int local_6e0;
  char local_660;
  int local_648;
  char local_640;
  char local_638;
  undefined1 local_628 [64];
  undefined1 local_5e8 [64];
  GADict local_5a8 [32];
  undefined1 local_588 [32];
  undefined1 local_568 [32];
  undefined1 local_548 [32];
  undefined1 local_528 [32];
  undefined1 local_508 [32];
  GADict local_4e8 [32];
  undefined1 local_4c8 [32];
  undefined1 local_4a8 [32];
  undefined1 local_488 [32];
  undefined1 local_468 [32];
  undefined1 local_448 [32];
  GADict local_428 [32];
  undefined1 local_408 [32];
  undefined1 local_3e8 [32];
  undefined1 local_3c8 [32];
  undefined1 local_3a8 [32];
  undefined1 local_388 [32];
  GADict local_368 [32];
  undefined1 local_348 [32];
  undefined1 local_328 [32];
  undefined1 local_308 [32];
  undefined1 local_2e8 [32];
  undefined1 local_2c8 [32];
  GADict local_2a8 [32];
  undefined1 local_288 [32];
  undefined1 local_268 [32];
  undefined1 local_248 [32];
  undefined1 local_228 [32];
  undefined1 local_208 [32];
  undefined1 local_1e8 [32];
  GADict local_1c8 [32];
  undefined1 local_1a8 [32];
  undefined1 local_188 [32];
  undefined1 local_168 [32];
  undefined1 local_148 [32];
  undefined1 local_128 [32];
  undefined1 local_108 [32];
  undefined1 local_e8 [32];
  undefined1 local_c8 [32];
  undefined1 local_a8 [32];
  undefined1 local_88 [32];
  ulonglong local_68 [8];
  
  local_68[0] = DAT_180418e00 ^ (ulonglong)auStack_1d78;
  bVar14 = false;
  local_1d3c = 0;
  local_18f0 = param_1;
  local_18e8 = param_2;
  pDVar23 = ArtDoc::MarkReader::GetPropertiesAsDictionary(param_1);
  local_1d08 = (Error *)0x0;
  plStack_1d00 = (longlong *)0x0;
  uStack_be8 = 0;
  local_be0 = 0;
  local_bd8 = 0xf;
  local_bf0 = (int *******)0x0;
  local_1d18 = pDVar23;
  pCVar24 = (Content *)(**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
  TVar17 = ArtDoc::Content::GetType(pCVar24);
  local_1d40 = (char)TVar17;
  pCVar24 = (Content *)(**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
  pPVar25 = ArtDoc::Content::GetProperties(pCVar24);
  pcVar5 = kUserScaling_exref;
  puVar47 = *(undefined8 **)pPVar25;
  puVar48 = puVar47 + *(longlong *)(pPVar25 + 8) * 0xc;
  if (puVar47 == puVar48) {
LAB_1801726d1:
    uVar55 = 0;
    uVar52 = 0x3ff00000;
  }
  else {
    do {
      _Buf2 = puVar47;
      if (0xf < (ulonglong)puVar47[3]) {
        _Buf2 = (undefined8 *)*puVar47;
      }
      _Size = *(size_t *)(pcVar5 + 8);
    } while (((_Size != puVar47[2]) ||
             ((_Size != 0 && (iVar18 = memcmp(*(void **)pcVar5,_Buf2,_Size), iVar18 != 0)))) &&
            (puVar47 = puVar47 + 0xc, puVar47 != puVar48));
    pDVar23 = local_1d18;
    if (puVar47 == puVar48) goto LAB_1801726d1;
    puVar48 = puVar47 + 4;
    if (((puVar48 == (undefined8 *)0x0) || ((puVar47[0xb] & 0xfffffffffffffffc) == 0)) ||
       (iVar18 = __std_type_info_compare((puVar47[0xb] & 0xfffffffffffffffc) + 8,0x18041c6e8),
       iVar18 != 0)) {
      puVar48 = (undefined8 *)0x0;
    }
    if (puVar48 == (undefined8 *)0x0) goto LAB_1801726d1;
    uVar55 = (undefined4)*puVar48;
    uVar52 = (undefined4)((ulonglong)*puVar48 >> 0x20);
  }
  uVar26 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
  local_1d38 = FUN_180177fe0(uVar26);
  local_1d3f = (byte)local_1d38 & 1;
  local_1d18 = (Dictionary *)
               (CONCAT44(local_1d18._4_4_,CONCAT31((uint3)(local_1d38 >> 9),(char)(local_1d38 >> 1))
                        ) & 0xffffffffffffff01);
  if ((local_1d40 == '\0') || ((local_1d38 & 1) != 0)) {
    uStack_b48 = 0;
    local_b40 = &DAT_00000007;
    uStack_b38 = 0xf;
    local_b50 = (void *)0x65746176697250;
    bVar14 = true;
    local_1d3c = 1;
    bVar13 = ArtDoc::Dictionary::HasDictionaryValue
                       (pDVar23,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                &local_b50);
    if (!bVar13) goto LAB_18017277f;
    bVar13 = true;
  }
  else {
LAB_18017277f:
    bVar13 = false;
  }
  if (bVar14) {
    if (0xf < uStack_b38) {
      pvVar45 = local_b50;
      if (0xfff < uStack_b38 + 1) {
        pvVar45 = *(void **)((longlong)local_b50 + -8);
        if (0x1f < (ulonglong)((longlong)local_b50 + (-8 - (longlong)pvVar45))) goto LAB_1801728a0;
      }
      free(pvVar45);
    }
    local_b40 = (undefined *)0x0;
    uStack_b38 = 0xf;
    local_b50 = (void *)((ulonglong)local_b50 & 0xffffffffffffff00);
  }
  if (!bVar13) goto LAB_180177860;
  uStack_b28 = 0;
  local_b20 = &DAT_00000007;
  uStack_b18 = 0xf;
  local_b30 = (void *)0x65746176697250;
  pDVar23 = ArtDoc::Dictionary::GetDictionaryValue
                      (pDVar23,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                               &local_b30);
  local_1cc0 = pDVar23;
  if (0xf < uStack_b18) {
    pvVar45 = local_b30;
    if ((0xfff < uStack_b18 + 1) &&
       (pvVar45 = *(void **)((longlong)local_b30 + -8),
       0x1f < (ulonglong)((longlong)local_b30 + (-8 - (longlong)pvVar45)))) {
LAB_1801728a0:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar45);
  }
  local_b20 = (undefined *)0x0;
  uStack_b18 = 0xf;
  local_b30 = (void *)((ulonglong)local_b30 & 0xffffffffffffff00);
  pGVar27 = (GADict *)GADict::Cast(local_18d0);
  GName::GName(local_18e0,"Private");
  GADict::Get(pGVar27,local_18d8);
  GADict::Cast(local_1d48);
  GAObject::~GAObject((GAObject *)local_18d8);
  GADict::~GADict((GADict *)local_18d0);
  local_ac0 = (undefined *)0xa;
  uStack_ab8 = 0xf;
  local_ad0 = (void *)0x79547463656a624f;
  uStack_ac8 = 0x6570;
  bVar14 = ArtDoc::Dictionary::HasStringValue
                     (pDVar23,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                              &local_ad0);
  if (0xf < uStack_ab8) {
    pvVar45 = local_ad0;
    if ((0xfff < uStack_ab8 + 1) &&
       (pvVar45 = *(void **)((longlong)local_ad0 + -8),
       0x1f < (ulonglong)((longlong)local_ad0 + (-8 - (longlong)pvVar45)))) goto LAB_1801730ba;
    free(pvVar45);
  }
  local_ac0 = (undefined *)0x0;
  uStack_ab8 = 0xf;
  local_ad0 = (void *)((ulonglong)local_ad0 & 0xffffffffffffff00);
  if (!bVar14) {
LAB_180177854:
    GADict::~GADict((GADict *)local_1d48);
LAB_180177860:
    local_1c10 = (Group *)FUN_1802d6b50(0x2d0);
    local_1d28 = (GADict *)local_1c10;
    if (local_1c10 == (Group *)0x0) {
      local_1c10 = (Group *)0x0;
    }
    else {
      ArtDoc::Group::Group(local_1c10,4);
      *(undefined ***)local_1c10 = ArtDoc::Group::vftable;
      *(undefined ***)(local_1c10 + 0x20) = ArtDoc::Group::vftable;
    }
    if (local_1d08 != (Error *)0x0) {
      pCVar24 = (Content *)(**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
      this_04 = ArtDoc::Content::GetActiveErrors(pCVar24);
      if (plStack_1d00 != (longlong *)0x0) {
        LOCK();
        *(int *)(plStack_1d00 + 1) = (int)plStack_1d00[1] + 1;
        UNLOCK();
      }
      local_17f8 = local_1d08;
      plStack_17f0 = plStack_1d00;
      ArtDoc::Errors::AddError(this_04,(shared_ptr<ArtSys::Core::Error> *)&local_17f8);
      if (plStack_17f0 != (longlong *)0x0) {
        FUN_180018860();
      }
      pCVar24 = (Content *)(**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
      ArtDoc::AssociateObjectWithError(local_1d08,(ContentObject *)local_1c10,pCVar24);
    }
    *param_2 = (longlong)local_1c10;
    local_1c10 = (Group *)0x0;
    if (0xf < local_bd8) {
      pppppppiVar31 = local_bf0;
      if ((0xfff < local_bd8 + 1) &&
         (pppppppiVar31 = (int *******)local_bf0[-1],
         0x1f < (ulonglong)((longlong)local_bf0 + (-8 - (longlong)pppppppiVar31)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppppiVar31);
    }
    plVar50 = plStack_1d00;
    local_be0 = 0;
    local_bd8 = 0xf;
    local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
    if (plStack_1d00 != (longlong *)0x0) {
      LOCK();
      plVar29 = plStack_1d00 + 1;
      lVar42 = *plVar29;
      *(int *)plVar29 = (int)*plVar29 + -1;
      UNLOCK();
      if ((int)lVar42 == 1) {
        (**(code **)*plStack_1d00)(plStack_1d00);
        LOCK();
        piVar1 = (int *)((longlong)plVar50 + 0xc);
        iVar18 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar18 == 1) {
          (**(code **)(*plVar50 + 8))(plVar50);
        }
      }
    }
    return param_2;
  }
  local_a80 = (undefined *)0xa;
  uStack_a78 = 0xf;
  local_a90 = (void *)0x79547463656a624f;
  uStack_a88 = 0x6570;
  pbVar28 = ArtDoc::Dictionary::GetStringValue
                      (pDVar23,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)&local_a90);
  if ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_bf0 != pbVar28) {
    pbVar43 = pbVar28 + 0x10;
    if (0xf < *(ulonglong *)(pbVar28 + 0x18)) {
      pbVar28 = *(basic_string<char,std::char_traits<char>,std::allocator<char>_> **)pbVar28;
    }
    FUN_180019430(&local_bf0,pbVar28,*(undefined8 *)pbVar43);
  }
  if (0xf < uStack_a78) {
    pvVar45 = local_a90;
    if ((0xfff < uStack_a78 + 1) &&
       (pvVar45 = *(void **)((longlong)local_a90 + -8),
       0x1f < (ulonglong)((longlong)local_a90 + (-8 - (longlong)pvVar45)))) goto LAB_1801730ba;
    free(pvVar45);
  }
  local_a80 = (undefined *)0x0;
  uStack_a78 = 0xf;
  local_a90 = (void *)((ulonglong)local_a90 & 0xffffffffffffff00);
  FUN_180184a80(&local_bb0,local_1d48);
  plVar29 = (longlong *)FUN_180178260(local_1390,&local_bf0,&local_bb0);
  local_1d08 = (Error *)*plVar29;
  plVar50 = (longlong *)plVar29[1];
  *plVar29 = 0;
  plVar29[1] = 0;
  bVar14 = plStack_1d00 != (longlong *)0x0;
  plStack_1d00 = plVar50;
  if (bVar14) {
    FUN_180018860();
  }
  if (local_1388 != 0) {
    FUN_180018860();
  }
  if (local_1d08 != (Error *)0x0) {
    local_18c8 = "Unsupported type or version";
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(&local_18c8,(ThrowInfo *)&DAT_1803b78c8);
  }
  pDVar2 = *(Document **)(param_1 + 0x28);
  pGVar27 = (GADict *)GADict::GADict(local_18c0,(GADict *)local_1d48);
  local_1d28 = pGVar27;
  pMVar30 = ArtDoc::FindModule(0x4d61726b);
  local_1d58 = (ulonglong)local_1d58._4_4_ << 0x20;
  this = (MarksModule *)
         __RTDynamicCast(pMVar30,0,&ArtDoc::Module::RTTI_Type_Descriptor,
                         &DocumentMarks::MarksModule::RTTI_Type_Descriptor);
  if ((this != (MarksModule *)0x0) &&
     (uVar19 = DocumentMarks::MarksModule::GetFeatures(this), (uVar19 >> 9 & 1) != 0)) {
    GName::GName(local_18b8,"Context");
    bVar14 = GADict::Has(pGVar27,local_18b8);
    bVar13 = DocumentMarks::IsReportTemplate(pDVar2);
    if (bVar13) {
      if (!bVar14) {
        local_18b0 = "Context mismatch";
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(&local_18b0,(ThrowInfo *)&DAT_1803b78c8);
      }
    }
    else if (!bVar14) goto LAB_180172c69;
    pppppppiVar31 = (int *******)&local_bf0;
    if (0xf < local_bd8) {
      pppppppiVar31 = local_bf0;
    }
    if (local_be0 == 4) {
      bVar14 = *(int *)pppppppiVar31 == 0x74786554;
    }
    else {
      bVar14 = false;
    }
    GName::GName(local_18a8,"Context");
    uVar26 = GADict::GetDict(pGVar27,local_18a0);
    cVar15 = FUN_180178a00(uVar26,bVar13,bVar14);
    GADict::~GADict((GADict *)local_18a0);
    if (cVar15 == '\0') {
      local_1898[0] = "Mark contains invalid Context.";
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(local_1898,(ThrowInfo *)&DAT_1803b78c8);
    }
  }
LAB_180172c69:
  GADict::~GADict(pGVar27);
  GName::GName(local_1b18,"Context");
  bVar14 = GADict::Has((GADict *)local_1d48,local_1b18);
  if (bVar14) {
    GName::GName(local_1b10,"Context");
    pGVar27 = (GADict *)GADict::GetDict((GADict *)local_1d48,local_1af8);
    local_1d3c = 2;
    GName::GName(local_1b08,"Type");
    GADict::GetName(pGVar27,local_1b00);
    local_1d3c = 6;
    puVar32 = (ulonglong *)ArtDocGlue::PDFConverters::UTF8String(local_790);
    uVar19 = 0xe;
  }
  else {
    uStack_b62 = 0;
    local_b60 = (undefined *)0xe;
    uStack_b58 = 0xf;
    local_b70 = 0x696e6961746e6f43;
    uStack_b68 = 0x6150676e;
    uStack_b64 = 0x6567;
    puVar32 = &local_b70;
    uVar19 = 0x10;
  }
  local_bd0 = (void *)0x0;
  uStack_bc8 = 0;
  local_bc0 = (undefined *)0x0;
  uStack_bb8 = 0;
  local_bd0 = (void *)*puVar32;
  uStack_bc8 = puVar32[1];
  local_bc0 = (undefined *)puVar32[2];
  uStack_bb8 = puVar32[3];
  puVar32[2] = 0;
  puVar32[3] = 0xf;
  *(undefined1 *)puVar32 = 0;
  if ((uVar19 & 0x10) != 0) {
    uVar19 = uVar19 & 0xffffffef;
    if (0xf < uStack_b58) {
      FUN_1800187d0(&local_b70,local_b70);
    }
    local_b60 = (undefined *)0x0;
    uStack_b58 = 0xf;
    local_b70 = local_b70 & 0xffffffffffffff00;
  }
  if ((uVar19 & 8) != 0) {
    uVar19 = uVar19 & 0xfffffff7;
    FUN_1800118b0(local_790);
  }
  if ((uVar19 & 4) != 0) {
    uVar19 = uVar19 & 0xfffffffb;
    GAName::~GAName((GAName *)local_1b00);
  }
  if ((uVar19 & 2) != 0) {
    uVar19 = uVar19 & 0xfffffffd;
    GADict::~GADict((GADict *)local_1af8);
  }
  uVar3 = local_bd8;
  lVar42 = local_be0;
  pppppppiVar31 = local_bf0;
  pppppppiVar44 = (int *******)&local_bf0;
  if (0xf < local_bd8) {
    pppppppiVar44 = local_bf0;
  }
  iVar18 = FUN_180021700(pppppppiVar44,local_be0,"Generic",7);
  if (iVar18 != 0) {
    pppppppiVar44 = (int *******)&local_bf0;
    if (0xf < uVar3) {
      pppppppiVar44 = pppppppiVar31;
    }
    iVar18 = FUN_180021700(pppppppiVar44,lVar42,&DAT_180312a38,4);
    if (iVar18 == 0) {
      local_aa0 = (undefined *)0x8;
      uStack_a98 = 0xf;
      local_ab0[0] = 0x6570795474786554;
      local_ab0[1] = 0;
      pbVar28 = ArtDoc::Dictionary::GetStringValue
                          (local_1cc0,
                           (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            *)local_ab0);
      if (0xf < uStack_a98) {
        FUN_1800187d0(local_ab0,local_ab0[0]);
      }
      local_aa0 = (undefined *)0x0;
      uStack_a98 = 0xf;
      local_ab0[0] = local_ab0[0] & 0xffffffffffffff00;
      uVar3 = *(ulonglong *)(pbVar28 + 0x10);
      uVar4 = *(ulonglong *)(pbVar28 + 0x18);
      pbVar43 = pbVar28;
      if (0xf < uVar4) {
        pbVar43 = *(basic_string<char,std::char_traits<char>,std::allocator<char>_> **)pbVar28;
      }
      _Size_00 = uVar3;
      if (9 < uVar3) {
        _Size_00 = 9;
      }
      iVar18 = memcmp(pbVar43,"PointText",_Size_00);
      if ((iVar18 != 0) || (uVar3 != 9)) {
        if (0xf < uVar4) {
          pbVar28 = *(basic_string<char,std::char_traits<char>,std::allocator<char>_> **)pbVar28;
        }
        iVar18 = FUN_180021700(pbVar28,uVar3,"ContainedText",0xd);
        if (iVar18 != 0) {
LAB_180177ada:
          local_1a40 = "Unsupported type or Text Mark";
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(&local_1a40,(ThrowInfo *)&DAT_1803b78c8);
        }
        local_a50 = 0;
        uStack_a48 = 0;
        local_a40 = 0;
        uStack_a38 = 0;
        FUN_180010070(&local_a50,"Source",6);
        pbVar28 = ArtDoc::Dictionary::GetStringValue
                            (local_1cc0,
                             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              *)&local_a50);
        FUN_1800118b0(&local_a50);
        GName::GName(local_1ad0,"Container");
        GADict::GetDict((GADict *)local_1d48,local_1c50);
        GName::GName(local_1ac8,"Type");
        GADict::GetName((GADict *)local_1c50,local_1c58);
        bVar14 = GAName::operator==((GAName *)local_1c58,"InsideBox");
        if ((!bVar14) && (bVar14 = GAName::operator==((GAName *)local_1c58,"InPath"), !bVar14)) {
          bVar14 = GAName::operator==((GAName *)local_1c58,"OnPath");
          if (!bVar14) {
            GAName::~GAName((GAName *)local_1c58);
            GADict::~GADict((GADict *)local_1c50);
            goto LAB_180177ada;
          }
          local_1d28 = (GADict *)FUN_1802d6b50(0x770);
          if (local_1d28 == (GADict *)0x0) {
            pDVar33 = (DynamicTextObject *)0x0;
          }
          else {
            pDVar33 = (DynamicTextObject *)
                      DocumentMarks::TextOnPathMark::TextOnPathMark
                                ((TextOnPathMark *)local_1d28,false);
          }
          uVar51 = 0;
          local_1ce8 = (TextOnPathMark *)pDVar33;
          pbVar28 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                    FUN_1801cd320(local_7d0,pbVar28);
          DocumentMarks::DynamicTextObject::setUniversalText(pDVar33,pbVar28);
          FUN_1800118b0(local_7d0);
          pTVar10 = local_1ce8;
          uVar26 = FUN_180184510(local_1638,local_1c50,*(undefined8 *)(param_1 + 0x30));
          DocumentMarks::TextOnPathMark::SetTextPath(pTVar10,uVar26);
          pTVar10 = local_1ce8;
          GName::GName(local_1ac0,"Reflow");
          bVar14 = GADict::Has((GADict *)local_1d48,local_1ac0);
          if (bVar14) {
            GName::GName(local_1ab8,"Reflow");
            GADict::GetDict((GADict *)local_1d48,local_1c00);
            GName::GName(local_1ab0,"MinimumFontSize");
            bVar14 = GADict::Has((GADict *)local_1c00,local_1ab0);
            if (bVar14) {
              GName::GName(local_1aa8,"MinimumFontSize");
              pGVar34 = (GANumber *)GADict::GetNumber((GADict *)local_1c00,local_1aa0);
              uVar51 = uVar19 | 0x1800000;
              local_1d3c = uVar51;
              dVar53 = GANumber::Get(pGVar34);
              uVar52 = SUB84(dVar53,0);
              uVar54 = (undefined4)((ulonglong)dVar53 >> 0x20);
            }
            else {
              uVar52 = 0;
              uVar54 = 0x401c0000;
            }
            if ((uVar51 >> 0x17 & 1) != 0) {
              GANumber::~GANumber((GANumber *)local_1aa0);
            }
            DocumentMarks::TextOnPathMark::SetMinimumFontSize
                      (pTVar10,(double)CONCAT44(uVar54,uVar52));
            GADict::~GADict((GADict *)local_1c00);
          }
          if (local_1d40 != '\0') {
            GName::GName(local_1a98,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1a98);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1ce8 + 0x2f0),0);
              }
              goto LAB_18017398c;
            }
          }
          FUN_180180330(local_1d48,local_1ce8,&local_bd0,uVar55);
LAB_18017398c:
          FUN_18017b590(local_1d48,local_1ce8,(ulonglong)local_1d18 & 0xff);
          local_9c8 = std::
                      _Func_impl_no_alloc<`public:_virtual_class_std::unique_ptr<ArtDoc::Group,std::default_delete<ArtDoc::Group>_>___cdecl_DocumentMarks::PDFPlusMarkReader::CreateGroup(void)___ptr64'::`54'::<lambda_3>,void,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
                      ::vftable;
          local_9c0 = &local_1ce8;
          local_990 = &local_9c8;
          FUN_1801837d0(local_1d48,&local_9c8);
          if (local_990 != (undefined ***)0x0) {
            (*(code *)(*local_990)[4])(local_990,local_990 != &local_9c8);
            local_990 = (undefined ***)0x0;
          }
          local_1188[0] = 2;
          local_1150 = 0;
          local_1148 = 0;
          uStack_1140 = 0;
          local_1138 = 0;
          uStack_1130 = 0;
          local_1128 = 0;
          local_1110 = 0;
          DocumentTypesetting::SetRecognitionContext
                    ((ContentObject *)local_1ce8,(RecognitionContext *)local_1188);
          pTVar10 = local_1ce8;
          uVar26 = GADict::GADict(local_1a90,(GADict *)local_1d48);
          bVar16 = FUN_180178cd0(uVar26);
          DocumentMarks::DynamicTextObject::SetUseStationInformation
                    ((DynamicTextObject *)pTVar10,(bool)(bVar16 ^ 1));
          pTVar10 = local_1ce8;
          local_1ce8 = (TextOnPathMark *)0x0;
          *param_2 = (longlong)pTVar10;
          FUN_1800653d0(local_1188);
          pTVar10 = local_1ce8;
          if (local_1ce8 != (TextOnPathMark *)0x0) {
            DocumentMarks::TextOnPathMark::~TextOnPathMark(local_1ce8);
            free(pTVar10);
          }
          GAName::~GAName((GAName *)local_1c58);
          GADict::~GADict((GADict *)local_1c50);
          if (0xf < uStack_bb8) {
            FUN_1800187d0(&local_bd0,local_bd0);
          }
          local_bc0 = (undefined *)0x0;
          uStack_bb8 = 0xf;
          local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
          if (0xf < uStack_b98) {
            FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
          }
          local_ba0 = (undefined *)0x0;
          uStack_b98 = 0xf;
          local_bb0 = 0;
          GADict::~GADict((GADict *)local_1d48);
          if (0xf < local_bd8) {
            FUN_1800187d0(&local_bf0,local_bf0);
          }
          local_be0 = 0;
          local_bd8 = 0xf;
          local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
          if (plStack_1d00 == (longlong *)0x0) {
            return param_2;
          }
          FUN_180018860();
          return param_2;
        }
        local_1d28 = (GADict *)FUN_1802d6b50(0x858);
        if (local_1d28 == (GADict *)0x0) {
          pDVar33 = (DynamicTextObject *)0x0;
        }
        else {
          pDVar33 = (DynamicTextObject *)
                    DocumentMarks::TextAreaMark::TextAreaMark((TextAreaMark *)local_1d28,false);
        }
        uVar51 = 0;
        local_1cf0 = (TextAreaMark *)pDVar33;
        pbVar28 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                  FUN_1801cd320(local_7f0,pbVar28);
        DocumentMarks::DynamicTextObject::setUniversalText(pDVar33,pbVar28);
        FUN_1800118b0(local_7f0);
        FUN_180184000(local_1c50,*(undefined8 *)(param_1 + 0x30),local_1cf0,uVar55);
        pTVar9 = local_1cf0;
        GName::GName(local_1a88,"Reflow");
        GADict::GetDict((GADict *)local_1d48,local_1c08);
        GName::GName(local_1a80,"ReflowStyle");
        this_00 = (GAName *)GADict::GetName((GADict *)local_1c08,local_1a78);
        bVar14 = GAName::operator==(this_00,"WrapThenShrink");
        if (bVar14) {
          TVar20 = 2;
        }
        else {
          bVar14 = GAName::operator==(this_00,"ShrinkWithoutWrapping");
          if (!bVar14) {
            local_1a48 = "Unknown text fitting style.";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_1a48,(ThrowInfo *)&DAT_1803b78c8);
          }
          TVar20 = 1;
        }
        DocumentMarks::TextAreaMark::SetTextFittingStyle(pTVar9,TVar20);
        GAName::~GAName((GAName *)local_1a78);
        GName::GName(local_1a70,"MinimumFontSize");
        bVar14 = GADict::Has((GADict *)local_1c08,local_1a70);
        if (bVar14) {
          GName::GName(local_1a68,"MinimumFontSize");
          pGVar34 = (GANumber *)GADict::GetNumber((GADict *)local_1c08,local_1a60);
          uVar51 = uVar19 | 0x600000;
          local_1d3c = uVar51;
          dVar53 = GANumber::Get(pGVar34);
          uVar52 = SUB84(dVar53,0);
          uVar54 = (undefined4)((ulonglong)dVar53 >> 0x20);
        }
        else {
          uVar52 = 0;
          uVar54 = 0x401c0000;
        }
        if ((uVar51 >> 0x15 & 1) != 0) {
          GANumber::~GANumber((GANumber *)local_1a60);
        }
        DocumentMarks::TextAreaMark::SetMinimumFontSize(pTVar9,(double)CONCAT44(uVar54,uVar52));
        GADict::~GADict((GADict *)local_1c08);
        if (local_1d40 != '\0') {
          GName::GName(local_1a58,"Position");
          bVar14 = GADict::Has((GADict *)local_1d48,local_1a58);
          if (!bVar14) {
            if (local_1d3f != 0) {
              DocumentMarks::MarkPosition::setReferenceObject
                        ((MarkPosition *)(local_1cf0 + 0x2f0),0);
            }
            goto LAB_180173e23;
          }
        }
        FUN_180180330(local_1d48,local_1cf0,&local_bd0,uVar55);
LAB_180173e23:
        FUN_18017b590(local_1d48,local_1cf0,(ulonglong)local_1d18 & 0xff);
        local_a08 = std::
                    _Func_impl_no_alloc<`public:_virtual_class_std::unique_ptr<ArtDoc::Group,std::default_delete<ArtDoc::Group>_>___cdecl_DocumentMarks::PDFPlusMarkReader::CreateGroup(void)___ptr64'::`43'::<lambda_2>,void,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
                    ::vftable;
        local_a00 = &local_1cf0;
        local_9d0 = &local_a08;
        FUN_1801837d0(local_1d48,&local_a08);
        if (local_9d0 != (undefined ***)0x0) {
          (*(code *)(*local_9d0)[4])(local_9d0,local_9d0 != &local_a08);
          local_9d0 = (undefined ***)0x0;
        }
        local_1208[0] = 1;
        local_11d0 = 0;
        local_11c8 = 0;
        lStack_11c0 = 0;
        local_11b8 = 0;
        uStack_11b0 = 0;
        local_11a8 = 0;
        local_1190 = 0;
        DocumentTypesetting::SetRecognitionContext
                  ((ContentObject *)local_1cf0,(RecognitionContext *)local_1208);
        pTVar9 = local_1cf0;
        uVar26 = GADict::GADict(local_1a50,(GADict *)local_1d48);
        bVar16 = FUN_180178cd0(uVar26);
        DocumentMarks::DynamicTextObject::SetUseStationInformation
                  ((DynamicTextObject *)pTVar9,(bool)(bVar16 ^ 1));
        pTVar9 = local_1cf0;
        local_1cf0 = (TextAreaMark *)0x0;
        *param_2 = (longlong)pTVar9;
        thunk_FUN_180066380(&local_11b8);
        if (lStack_11c0 != 0) {
          FUN_180018860();
        }
        pTVar9 = local_1cf0;
        if (local_1cf0 != (TextAreaMark *)0x0) {
          DocumentMarks::TextAreaMark::~TextAreaMark(local_1cf0);
          free(pTVar9);
        }
        GAName::~GAName((GAName *)local_1c58);
        GADict::~GADict((GADict *)local_1c50);
        if (0xf < uStack_bb8) {
          FUN_1800187d0(&local_bd0,local_bd0);
        }
        local_bc0 = (undefined *)0x0;
        uStack_bb8 = 0xf;
        local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
        if (0xf < uStack_b98) {
          FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
        }
        local_ba0 = (undefined *)0x0;
        uStack_b98 = 0xf;
        local_bb0 = 0;
        GADict::~GADict((GADict *)local_1d48);
        if (0xf < local_bd8) {
          FUN_1800187d0(&local_bf0,local_bf0);
        }
        local_be0 = 0;
        local_bd8 = 0xf;
        local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
        if (plStack_1d00 == (longlong *)0x0) {
          return param_2;
        }
        FUN_180018860();
        return param_2;
      }
      local_1d28 = (GADict *)FUN_1802d6b50(0x750);
      if (local_1d28 == (GADict *)0x0) {
        local_1ce0 = (DynamicTextObject *)0x0;
      }
      else {
        local_1ce0 = (DynamicTextObject *)
                     DocumentMarks::TextMark::TextMark((TextMark *)local_1d28,false);
      }
      local_b10[1] = 0;
      local_b00 = (undefined *)0x6;
      uStack_af8 = 0xf;
      local_b10[0] = 0x656372756f53;
      pbVar28 = ArtDoc::Dictionary::GetStringValue
                          (local_1cc0,
                           (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            *)local_b10);
      if (0xf < uStack_af8) {
        FUN_1800187d0(local_b10,local_b10[0]);
      }
      pDVar33 = local_1ce0;
      local_b00 = (undefined *)0x0;
      uStack_af8 = 0xf;
      local_b10[0] = local_b10[0] & 0xffffffffffffff00;
      pbVar28 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                FUN_1801cd320(local_7b0,pbVar28);
      DocumentMarks::DynamicTextObject::setUniversalText(pDVar33,pbVar28);
      FUN_1800118b0(local_7b0);
      if (local_1d40 != '\0') {
        GName::GName(local_1ae0,"Position");
        bVar14 = GADict::Has((GADict *)local_1d48,local_1ae0);
        if (!bVar14) {
          if (local_1d3f != 0) {
            DocumentMarks::MarkPosition::setReferenceObject((MarkPosition *)(local_1ce0 + 0x2f0),0);
          }
          goto LAB_1801733a5;
        }
      }
      FUN_180180330(local_1d48,local_1ce0,&local_bd0,uVar55);
LAB_1801733a5:
      FUN_18017b590(local_1d48,local_1ce0,(ulonglong)local_1d18 & 0xff);
      local_988 = std::
                  _Func_impl_no_alloc<`public:_virtual_class_std::unique_ptr<ArtDoc::Group,std::default_delete<ArtDoc::Group>_>___cdecl_DocumentMarks::PDFPlusMarkReader::CreateGroup(void)___ptr64'::`29'::<lambda_1>,void,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
                  ::vftable;
      local_980 = &local_1ce0;
      local_950 = &local_988;
      FUN_1801837d0(local_1d48,&local_988);
      if (local_950 != (undefined ***)0x0) {
        (*(code *)(*local_950)[4])(local_950,local_950 != &local_988);
        local_950 = (undefined ***)0x0;
      }
      local_12b8[0] = 3;
      local_1280 = 0;
      local_1278 = 0;
      lStack_1270 = 0;
      local_1268 = (void *)0x0;
      uStack_1260 = 0;
      local_1258 = 0;
      local_1240 = 0;
      DocumentTypesetting::SetRecognitionContext
                ((ContentObject *)local_1ce0,(RecognitionContext *)local_12b8);
      pDVar33 = local_1ce0;
      uVar26 = GADict::GADict(local_1ad8,(GADict *)local_1d48);
      bVar16 = FUN_180178cd0(uVar26);
      DocumentMarks::DynamicTextObject::SetUseStationInformation(pDVar33,(bool)(bVar16 ^ 1));
      pDVar33 = local_1ce0;
      local_1ce0 = (DynamicTextObject *)0x0;
      *param_2 = (longlong)pDVar33;
      if (local_1268 != (void *)0x0) {
        pvVar45 = local_1268;
        if ((0xfff < (ulonglong)(((local_1258 - (longlong)local_1268) / 0xb0) * 0xb0)) &&
           (pvVar45 = *(void **)((longlong)local_1268 + -8),
           0x1f < (ulonglong)((longlong)local_1268 + (-8 - (longlong)pvVar45)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar45);
        local_1268 = (void *)0x0;
        uStack_1260 = 0;
        local_1258 = 0;
      }
      if (lStack_1270 != 0) {
        FUN_180018860();
      }
      pDVar33 = local_1ce0;
      if (local_1ce0 != (DynamicTextObject *)0x0) {
        DocumentMarks::DynamicTextObject::~DynamicTextObject(local_1ce0);
        free(pDVar33);
      }
      if (0xf < uStack_bb8) {
        FUN_1800187d0(&local_bd0,local_bd0);
      }
      local_bc0 = (undefined *)0x0;
      uStack_bb8 = 0xf;
      local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
      if (0xf < uStack_b98) {
        FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
      }
      local_ba0 = (undefined *)0x0;
      uStack_b98 = 0xf;
      local_bb0 = 0;
      GADict::~GADict((GADict *)local_1d48);
      if (0xf < local_bd8) {
        FUN_1800187d0(&local_bf0,local_bf0);
      }
      local_be0 = 0;
      local_bd8 = 0xf;
      local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
      if (plStack_1d00 == (longlong *)0x0) {
        return param_2;
      }
      FUN_180018860();
      return param_2;
    }
    pppppppiVar44 = (int *******)&local_bf0;
    if (0xf < uVar3) {
      pppppppiVar44 = pppppppiVar31;
    }
    iVar18 = FUN_180021700(pppppppiVar44,lVar42,"GridMark",8);
    if (iVar18 != 0) {
      iVar18 = FUN_18016ef10(&local_bf0,&PTR_DAT_180326b90);
      if (iVar18 == 0) {
        GName::GName(local_1a30,"Source");
        GADict::GetStream((GADict *)local_1d48,local_1ba8);
        local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
        uVar26 = FUN_1801788e0(local_1608,*(undefined8 *)(param_1 + 0x30),local_1ba8,
                               *(undefined8 *)(param_1 + 0x28));
        FUN_1801716a0(&local_1828,uVar26);
        local_1d28 = (GADict *)FUN_1802d6b50(0x7c0);
        if (local_1d28 == (GADict *)0x0) {
          local_1c30 = 0;
        }
        else {
          if (lStack_1820 != 0) {
            LOCK();
            *(int *)(lStack_1820 + 8) = *(int *)(lStack_1820 + 8) + 1;
            UNLOCK();
          }
          local_1838 = local_1828;
          lStack_1830 = lStack_1820;
          local_1c30 = DocumentMarks::PDFPlusCutMark::PDFPlusCutMark
                                 ((PDFPlusCutMark *)local_1d28,&local_1838);
        }
        FUN_18017c5d0(local_1d48,local_1c30,&local_bd0,uVar55);
        FUN_18017c2b0(local_1d48,local_1c30,(ulonglong)local_1d18 & 0xff);
        *param_2 = local_1c30;
        local_1c30 = 0;
        FUN_180013ed0(&local_1828);
        GAStream::~GAStream((GAStream *)local_1ba8);
        if (0xf < uStack_bb8) {
          FUN_1800187d0(&local_bd0,local_bd0);
        }
        local_bc0 = (undefined *)0x0;
        uStack_bb8 = 0xf;
        local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
        if (0xf < uStack_b98) {
          FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
        }
        local_ba0 = (undefined *)0x0;
        uStack_b98 = 0xf;
        local_bb0 = 0;
        GADict::~GADict((GADict *)local_1d48);
        if (0xf < local_bd8) {
          FUN_1800187d0(&local_bf0,local_bf0);
        }
        local_be0 = 0;
        local_bd8 = 0xf;
        local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
        if (plStack_1d00 == (longlong *)0x0) {
          return param_2;
        }
        FUN_180018860();
        return param_2;
      }
      iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_RepeatForSeparations_180326bb0);
      if (iVar18 == 0) {
        FUN_180184a80(local_b90,local_1d48);
        pppppppuVar46 = local_b90;
        if (0xf < local_b78) {
          pppppppuVar46 = local_b90[0];
        }
        if ((local_b80 == 3) && (iVar18 = memcmp(pppppppuVar46,&DAT_180326c58,3), iVar18 == 0)) {
          GName::GName(local_1a28,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1ba0);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
          uVar26 = FUN_1801788e0(local_15f8,*(undefined8 *)(param_1 + 0x30),local_1ba0,
                                 *(undefined8 *)(param_1 + 0x28));
          FUN_1801716a0(local_1b38,uVar26);
          uVar26 = FUN_180172110(local_15e8,local_1b38,*(undefined8 *)(param_1 + 0x28));
          FUN_1800233b0(local_1b38,uVar26);
          FUN_180013ed0(local_15e8);
          FUN_18016f770(&local_1ca0,local_1b38);
          if (local_1d40 != '\0') {
            GName::GName(local_1a20,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1a20);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1ca0 + 0x2f0),0);
              }
              goto LAB_180174abf;
            }
          }
          FUN_180180330(local_1d48,local_1ca0,&local_bd0,uVar55);
LAB_180174abf:
          FUN_180182ce0(local_1d48,local_1ca0,uVar55);
          FUN_1801819b0(local_1d48,local_1ca0);
          *param_2 = local_1ca0;
          local_1ca0 = 0;
          FUN_180013ed0(local_1b38);
          GAStream::~GAStream((GAStream *)local_1ba0);
          FUN_1800118b0(local_b90);
          if (0xf < uStack_bb8) {
            FUN_1800187d0(&local_bd0,local_bd0);
          }
          local_bc0 = (undefined *)0x0;
          uStack_bb8 = 0xf;
          local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
          if (0xf < uStack_b98) {
            FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
          }
          local_ba0 = (undefined *)0x0;
          uStack_b98 = 0xf;
          local_bb0 = 0;
          GADict::~GADict((GADict *)local_1d48);
          if (0xf < local_bd8) {
            FUN_1800187d0(&local_bf0,local_bf0);
          }
          local_be0 = 0;
          local_bd8 = 0xf;
          local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
          if (plStack_1d00 == (longlong *)0x0) {
            return param_2;
          }
          FUN_180018860();
          return param_2;
        }
        pppppppuVar46 = local_b90;
        if (0xf < local_b78) {
          pppppppuVar46 = local_b90[0];
        }
        if ((local_b80 != 3) || (iVar18 = memcmp(pppppppuVar46,&DAT_180326c5c,3), iVar18 != 0)) {
          pppppppuVar46 = local_b90;
          if (0xf < local_b78) {
            pppppppuVar46 = local_b90[0];
          }
          if ((local_b80 != 3) || (iVar18 = memcmp(pppppppuVar46,&DAT_180326c60,3), iVar18 != 0)) {
            pppppppuVar46 = local_b90;
            if (0xf < local_b78) {
              pppppppuVar46 = local_b90[0];
            }
            if (((((local_b80 != 3) ||
                  (iVar18 = memcmp(pppppppuVar46,&DAT_180326c64,3), iVar18 != 0)) &&
                 (cVar15 = FUN_180021010(local_b90,&DAT_180326c68), cVar15 == '\0')) &&
                ((cVar15 = FUN_180021010(local_b90,&DAT_180326c6c), cVar15 == '\0' &&
                 (cVar15 = FUN_180021010(local_b90,&DAT_180326c70), cVar15 == '\0')))) &&
               (cVar15 = FUN_180021010(local_b90,&DAT_180326c74), cVar15 == '\0')) {
              FUN_1800118b0(local_b90);
              goto LAB_180177838;
            }
          }
        }
        GName::GName(local_1a18,"Source");
        GADict::GetStream((GADict *)local_1d48,local_1b98);
        local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
        uVar26 = FUN_1801788e0(local_15d8,*(undefined8 *)(param_1 + 0x30),local_1b98,
                               *(undefined8 *)(param_1 + 0x28));
        FUN_1801716a0(local_16e8,uVar26);
        FUN_18016f770(&local_1c98,local_16e8);
        if (local_1d40 != '\0') {
          GName::GName(local_1a10,"Position");
          bVar14 = GADict::Has((GADict *)local_1d48,local_1a10);
          if (!bVar14) {
            if (local_1d3f != 0) {
              DocumentMarks::MarkPosition::setReferenceObject
                        ((MarkPosition *)(local_1c98 + 0x2f0),0);
            }
            goto LAB_180174e1e;
          }
        }
        FUN_180180330(local_1d48,local_1c98,&local_bd0,uVar55);
LAB_180174e1e:
        FUN_18016e200(local_1d48,local_1c98,&local_bd0,uVar55);
        FUN_1801819b0(local_1d48,local_1c98);
        *param_2 = local_1c98;
        local_1c98 = 0;
        FUN_180013ed0(local_16e8);
        GAStream::~GAStream((GAStream *)local_1b98);
        FUN_1800118b0(local_b90);
        if (0xf < uStack_bb8) {
          FUN_1800187d0(&local_bd0,local_bd0);
        }
        local_bc0 = (undefined *)0x0;
        uStack_bb8 = 0xf;
        local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
        if (0xf < uStack_b98) {
          FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
        }
        local_ba0 = (undefined *)0x0;
        uStack_b98 = 0xf;
        local_bb0 = 0;
        GADict::~GADict((GADict *)local_1d48);
        if (0xf < local_bd8) {
          FUN_1800187d0(&local_bf0,local_bf0);
        }
        local_be0 = 0;
        local_bd8 = 0xf;
        local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
        if (plStack_1d00 == (longlong *)0x0) {
          return param_2;
        }
        FUN_180018860();
        return param_2;
      }
      iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_RepeatForGrid_180326ba0);
      if (iVar18 == 0) {
        GName::GName(local_1c38,"Source");
        GADict::GetStream((GADict *)local_1d48,local_1b90);
        local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
        uVar26 = FUN_1801788e0(local_15c8,*(undefined8 *)(param_1 + 0x30),local_1b90,
                               *(undefined8 *)(param_1 + 0x28));
        FUN_1801716a0(local_17a0,uVar26);
        local_1cc0 = (Dictionary *)0x0;
        FUN_18016f5b0(&local_1cb8,&local_1cc0,local_17a0);
        local_8f8 = 0;
        uStack_8f0 = 0;
        local_8e8 = 0;
        uStack_8e0 = 0;
        FUN_180010070(&local_8f8,"ObjectType",10);
        local_8d8 = 0;
        uStack_8d0 = 0;
        local_8c8 = 0;
        uStack_8c0 = 0;
        FUN_180010070(&local_8d8,"Context",7);
        local_8b8 = 0;
        uStack_8b0 = 0;
        local_8a8 = 0;
        uStack_8a0 = 0;
        FUN_180010070(&local_8b8,"Source",6);
        local_898 = 0;
        uStack_890 = 0;
        local_888 = 0;
        uStack_880 = 0;
        FUN_180010070(&local_898,"Position",8);
        local_878 = 0;
        uStack_870 = 0;
        local_868 = 0;
        uStack_860 = 0;
        FUN_180010070(&local_878,"Repetition",10);
        local_1d28 = (GADict *)&local_8f8;
        pGStack_1d20 = (GADict *)local_858;
        local_16d8 = local_1d28;
        puStack_16d0 = pGStack_1d20;
        FUN_180012730(local_1488,&local_1d28,&local_1ca8);
        cVar15 = FUN_180169530(local_1d48,local_1488);
        FUN_180019170(local_1488);
        _eh_vector_destructor_iterator_(&local_8f8,0x20,5,FUN_1800118b0);
        if (cVar15 != '\0') {
          DocumentMarks::DynamicObject::SetHasNewFeatures((DynamicObject *)local_1cb8,true);
        }
        local_1d58 = CONCAT44(uVar52,uVar55);
        FUN_180180480(local_1378,local_1d48,local_1cb8,&local_bd0);
        pPVar38 = ArtDoc::ContentObject::GetProperties((ContentObject *)local_1cb8);
        FUN_18016e9f0(pPVar38,&PTR_s_DocumentMarks_RepeatForGridMark__1803263a8,local_1378);
        FUN_180180ff0(local_12e8,local_1d48,local_1cb8);
        pPVar38 = ArtDoc::ContentObject::GetProperties((ContentObject *)local_1cb8);
        FUN_18016ebb0(pPVar38,&PTR_s_DocumentMarks_RepeatForGridMark__1803263b8,local_12e8);
        pPVar12 = local_1cb8;
        if (local_12ec == '\0') {
          local_12f0 = 1;
          local_12ec = '\x01';
          local_12eb = local_1c33;
          local_12e9 = local_1c31;
        }
        else if ((local_12e8[0] & 0xfffffffd) != 0) {
          local_1a08 = "HorizontalReference";
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(&local_1a08,(ThrowInfo *)&DAT_1803b78c8);
        }
        if (local_12f4 == '\0') {
          local_12f8 = 1;
          local_12f4 = '\x01';
          local_12f3 = local_1c33;
          local_12f1 = local_1c31;
        }
        else if (1 < local_12e8[0]) {
          local_1a00 = "VerticalReference";
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(&local_1a00,(ThrowInfo *)&DAT_1803b78c8);
        }
        local_1cb8 = (PDFPlusRepeatForGridMark *)0x0;
        *param_2 = (longlong)pPVar12;
        FUN_18006da40(local_1320);
        FUN_18006da40(local_1348);
        FUN_180022d90(local_1370);
        pPVar12 = local_1cb8;
        if (local_1cb8 != (PDFPlusRepeatForGridMark *)0x0) {
          DocumentMarks::PDFPlusRepeatForGridMark::~PDFPlusRepeatForGridMark(local_1cb8);
          free(pPVar12);
        }
        FUN_180013ed0(local_17a0);
        GAStream::~GAStream((GAStream *)local_1b90);
        if (0xf < uStack_bb8) {
          FUN_1800187d0(&local_bd0,local_bd0);
        }
        local_bc0 = (undefined *)0x0;
        uStack_bb8 = 0xf;
        local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
        if (0xf < uStack_b98) {
          FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
        }
        local_ba0 = (undefined *)0x0;
        uStack_b98 = 0xf;
        local_bb0 = 0;
        GADict::~GADict((GADict *)local_1d48);
        if (0xf < local_bd8) {
          FUN_1800187d0(&local_bf0,local_bf0);
        }
        local_be0 = 0;
        local_bd8 = 0xf;
        local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
        if (plStack_1d00 == (longlong *)0x0) {
          return param_2;
        }
        FUN_180018860();
        return param_2;
      }
      iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_RepeatForCount_180326bc0);
      if (iVar18 == 0) {
        GName::GName(local_19f8,"Source");
        GADict::GetStream((GADict *)local_1d48,local_1c28);
        local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
        uVar26 = FUN_1801788e0(local_15b8,*(undefined8 *)(param_1 + 0x30),local_1c28,
                               *(undefined8 *)(param_1 + 0x28));
        FUN_1801716a0(local_1bc8,uVar26);
        FUN_180184a80(local_af0,local_1d48);
        pppppppuVar46 = local_af0;
        if (0xf < local_ad8) {
          pppppppuVar46 = local_af0[0];
        }
        if ((local_ae0 == 3) && (iVar18 = memcmp(pppppppuVar46,&DAT_180326c58,3), iVar18 == 0)) {
          local_17e8 = 0;
          lStack_17e0 = 0;
          local_17d8 = 0;
          local_1688 = std::
                       _Func_impl_no_alloc<`public:_virtual_class_std::unique_ptr<ArtDoc::Group,std::default_delete<ArtDoc::Group>_>___cdecl_DocumentMarks::PDFPlusMarkReader::CreateGroup(void)___ptr64'::`115'::<lambda_4>,bool,DocumentMarks::PDFPlusRepeatForSeparationsMark&___ptr64>
                       ::vftable;
          local_1680 = &local_17e8;
          local_1650 = &local_1688;
          ArtDoc::VisitorBase::VisitorBase((VisitorBase *)&local_948);
          local_948 = ArtDoc::SimpleVisitor<DocumentMarks::PDFPlusRepeatForSeparationsMark>::vftable
          ;
          local_940 = ArtDoc::SimpleVisitor<DocumentMarks::PDFPlusRepeatForSeparationsMark>::vftable
          ;
          local_900 = (undefined ***)0x0;
          if (local_1650 != (undefined ***)0x0) {
            if (local_1650 == &local_1688) {
              local_900 = (undefined ***)(*(code *)(*local_1650)[1])(local_1650,local_938);
              FUN_180013b30(&local_1688);
            }
            else {
              local_900 = local_1650;
              local_1650 = (undefined ***)0x0;
            }
          }
          FUN_180013b30(&local_1688);
          pCVar24 = ArtPaint::FormPaint::GetContent(local_1bc8[0]);
          (**(code **)(*(longlong *)pCVar24 + 0x10))(pCVar24,&local_948);
          if ((lStack_17e0 - local_17e8 & 0xfffffffffffffff8U) != 8) {
            local_19e8 = "Wrong number of inner marks.";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_19e8,(ThrowInfo *)&DAT_1803b78c8);
          }
          FUN_18016f530(&local_1c48,local_1bc8);
          if (local_1d40 != '\0') {
            GName::GName(local_19f0,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_19f0);
            if (!bVar14) goto LAB_18017569f;
          }
          FUN_180180330(local_1d48,local_1c48,&local_bd0,uVar55);
LAB_18017569f:
          FUN_180182740(local_1d48,local_1c48,uVar55);
          lVar42 = local_1c48;
          local_1c48 = 0;
          *param_2 = lVar42;
          FUN_1801702d0(&local_1c48);
          FUN_1800bc8d0(&local_948);
          FID_conflict__vector<CHN*___ptr64,std::allocator<CHN*___ptr64>_>(&local_17e8);
          FUN_1800118b0(local_af0);
          FUN_180013ed0(local_1bc8);
          GAStream::~GAStream((GAStream *)local_1c28);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        pppppppuVar46 = local_af0;
        if (0xf < local_ad8) {
          pppppppuVar46 = local_af0[0];
        }
        if ((((local_ae0 == 3) && (iVar18 = memcmp(pppppppuVar46,&DAT_180326c5c,3), iVar18 == 0)) ||
            (cVar15 = FUN_180021010(local_af0,&DAT_180326c64), cVar15 != '\0')) ||
           (cVar15 = FUN_180021010(local_af0,&DAT_180326c68), cVar15 != '\0')) {
          FUN_18016f530(&local_1c78,local_1bc8);
          if (local_1d40 != '\0') {
            GName::GName(local_19e0,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_19e0);
            if (!bVar14) goto LAB_18017585d;
          }
          FUN_180180330(local_1d48,local_1c78,&local_bd0,uVar55);
LAB_18017585d:
          FUN_18016dc70(local_1d48,local_1c78,&local_bd0,uVar55);
          FUN_180183340(local_1d48,local_1c78,&local_bd0);
          lVar42 = local_1c78;
          local_1c78 = 0;
          *param_2 = lVar42;
          FUN_1801702d0(&local_1c78);
          FUN_1800118b0(local_af0);
          FUN_180013ed0(local_1bc8);
          GAStream::~GAStream((GAStream *)local_1c28);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        FUN_1800118b0(local_af0);
        FUN_180013ed0(local_1bc8);
        GAStream::~GAStream((GAStream *)local_1c28);
      }
      else {
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_RepeatForStations_180326bd0);
        if (iVar18 == 0) {
          GName::GName(local_19d8,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1b60);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38) | 2;
          FUN_1801788e0(&local_1be8,*(undefined8 *)(param_1 + 0x30),local_1b60,
                        *(undefined8 *)(param_1 + 0x28));
          if (lStack_1be0 != 0) {
            LOCK();
            *(int *)(lStack_1be0 + 8) = *(int *)(lStack_1be0 + 8) + 1;
            UNLOCK();
          }
          local_1818 = local_1be8;
          lStack_1810 = lStack_1be0;
          FUN_180177c50(&local_1818);
          if (lStack_1be0 != 0) {
            LOCK();
            *(int *)(lStack_1be0 + 8) = *(int *)(lStack_1be0 + 8) + 1;
            UNLOCK();
          }
          local_1808 = local_1be8;
          lStack_1800 = lStack_1be0;
          uVar26 = FUN_1801716a0(local_15a8,&local_1808);
          FUN_1800233b0(&local_1be8,uVar26);
          FUN_180013ed0(local_15a8);
          local_a30[0] = 0;
          uStack_a20 = 0;
          local_a18 = (undefined *)0x0;
          uStack_a10 = 0xf;
          local_a28 = 0;
          FUN_18016f7f0(&local_1c70,&local_1be8,local_a30);
          DocumentMarks::VDPSimpleRule::~VDPSimpleRule((VDPSimpleRule *)local_a30);
          FUN_180181cc0(local_1d48,local_1c70,&local_bd0,uVar55);
          FUN_180182410(local_1d48,local_1c70);
          FUN_18017b590(local_1d48,local_1c70,(ulonglong)local_1d18 & 0xff);
          *param_2 = local_1c70;
          local_1c70 = 0;
          FUN_180013ed0(&local_1be8);
          GAStream::~GAStream((GAStream *)local_1b60);
          if (0xf < uStack_bb8) {
            FUN_1800187d0(&local_bd0,local_bd0);
          }
          local_bc0 = (undefined *)0x0;
          uStack_bb8 = 0xf;
          local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
          if (0xf < uStack_b98) {
            FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
          }
          local_ba0 = (undefined *)0x0;
          uStack_b98 = 0xf;
          local_bb0 = 0;
          GADict::~GADict((GADict *)local_1d48);
          if (0xf < local_bd8) {
            FUN_1800187d0(&local_bf0,local_bf0);
          }
          local_be0 = 0;
          local_bd8 = 0xf;
          local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
          if (plStack_1d00 == (longlong *)0x0) {
            return param_2;
          }
          FUN_180018860();
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_Resize_180326be0);
        if (iVar18 == 0) {
          GName::GName(local_19d0,"Size");
          GADict::GetDict((GADict *)local_1d48,local_1c20);
          GName::GName(local_19c8,"Width");
          pGVar39 = (GAObject *)GADict::Get((GADict *)local_1c20,local_19b0);
          uVar51 = uVar19 | 0x40;
          local_1d3c = uVar51;
          bVar14 = GAObject::IsDict(pGVar39);
          if (bVar14) {
LAB_180175cd3:
            bVar14 = true;
          }
          else {
            GName::GName(local_19c0,"Height");
            pGVar39 = (GAObject *)GADict::Get((GADict *)local_1c20,local_19b8);
            uVar51 = uVar19 | 0xc0;
            local_1d3c = uVar51;
            bVar14 = GAObject::IsDict(pGVar39);
            if (bVar14) goto LAB_180175cd3;
            bVar14 = false;
          }
          if ((char)uVar51 < '\0') {
            uVar51 = uVar51 & 0xffffff7f;
            GAObject::~GAObject((GAObject *)local_19b8);
          }
          if ((uVar51 & 0x40) != 0) {
            GAObject::~GAObject((GAObject *)local_19b0);
          }
          if (bVar14) {
            GName::GName(local_19a8,"Source");
            GADict::GetStream((GADict *)local_1d48,local_1b88);
            local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
            uVar26 = FUN_1801788e0(local_1598,*(undefined8 *)(param_1 + 0x30),local_1b88,
                                   *(undefined8 *)(param_1 + 0x28));
            FUN_1801716a0(local_1790,uVar26);
            FUN_18016fed0(local_16a8);
            pCVar24 = ArtPaint::FormPaint::GetContent(local_1790[0]);
            (**(code **)(*(longlong *)pCVar24 + 0x10))(pCVar24,local_16a8);
            if (local_1698 == (DynamicMark *)0x0) {
              local_19a0 = "Mark contains unexpected objects.";
                    /* WARNING: Subroutine does not return */
              _CxxThrowException(&local_19a0,(ThrowInfo *)&DAT_1803b78c8);
            }
            uVar26 = DocumentMarks::DynamicMark::GetSourceContent(local_1698);
            uVar26 = FUN_180172110(local_1588,uVar26);
            FUN_18016f250(&local_1cd0,uVar26);
            FUN_180013ed0(local_1588);
            FUN_180013ed0(local_1578);
            pDVar11 = local_1cd0;
            pCVar40 = (ColorList<ArtColor::ColorSpacePolicy> *)
                      DocumentMarks::DynamicMark::GetOrderedSourceColorSpace(local_1698);
            DocumentMarks::DynamicMark::setSourceColorants(pDVar11,pCVar40);
            FUN_180022cb0(local_de0);
            pDVar11 = local_1cd0;
            CVar21 = DocumentMarks::DynamicObject::getColorType((DynamicObject *)local_1698,0);
            DocumentMarks::DynamicObject::setColorType((DynamicObject *)pDVar11,CVar21,0);
            pDVar11 = local_1cd0;
            pvVar41 = (variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
                       *)DocumentMarks::DynamicObject::GetTargetSeparations
                                   ((DynamicObject *)local_1698,(PaintAttribute)local_f08);
            DocumentMarks::DynamicObject::SetTargetSeparations((DynamicObject *)pDVar11,pvVar41,0);
            FUN_18006d990(local_f08);
            pDVar11 = local_1cd0;
            CVar21 = DocumentMarks::DynamicObject::getColorType((DynamicObject *)local_1698,1);
            DocumentMarks::DynamicObject::setColorType((DynamicObject *)pDVar11,CVar21,1);
            FUN_180185ff0(local_1d48);
            FUN_180179da0(local_1d48,local_1cd0,&local_bd0,uVar55);
            FUN_18017a330(local_1d48,local_1cd0,&local_bd0,uVar55);
            pDVar11 = local_1cd0;
            local_1cd0 = (DynamicMark *)0x0;
            *param_2 = (longlong)pDVar11;
            FUN_180170150(&local_1cd0);
            local_16a0 = ArtDoc::Visitor<DocumentMarks::CustomMark>::_vftable_;
            ArtDoc::VisitorBase::~VisitorBase(local_16a8);
            FUN_180013ed0(local_1790);
            GAStream::~GAStream((GAStream *)local_1b88);
            GADict::~GADict((GADict *)local_1c20);
            FUN_1800118b0(&local_bd0);
            FUN_1800118b0(&local_bb0);
            GADict::~GADict((GADict *)local_1d48);
            FUN_1800118b0(&local_bf0);
            FUN_180013ed0(&local_1d08);
            return param_2;
          }
          GName::GName(local_1998,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1b80);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
          uVar26 = FUN_1801788e0(local_1568,*(undefined8 *)(param_1 + 0x30),local_1b80,
                                 *(undefined8 *)(param_1 + 0x28));
          FUN_1801716a0(local_1768,uVar26);
          local_1d18 = (Dictionary *)CONCAT44(local_1d18._4_4_,1);
          FUN_18016f870(&local_1c90,local_1768,&local_1d18);
          FUN_180011dc0(local_5a8,"Version");
          FUN_180011dc0(local_588,"ObjectType");
          FUN_180011dc0(local_568,"Context");
          FUN_180011dc0(local_548,"Source");
          FUN_180011dc0(local_528,"Position");
          FUN_180011dc0(local_508,&DAT_180327254);
          local_1d28 = local_5a8;
          pGStack_1d20 = local_4e8;
          local_1778 = local_1d28;
          pGStack_1770 = pGStack_1d20;
          FUN_180012730(local_1470,&local_1d28,&local_1ca7);
          cVar15 = FUN_180169530(local_1d48,local_1470);
          FUN_180019170(local_1470);
          _eh_vector_destructor_iterator_(local_5a8,0x20,6,FUN_1800118b0);
          if (cVar15 != '\0') {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1c90,true);
          }
          FUN_18017eff0(local_1d48,local_1c90,&local_bd0,uVar55);
          if (local_1d40 != '\0') {
            GName::GName(local_1990,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1990);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1c90 + 0x2f0),0);
              }
              goto LAB_1801761dd;
            }
          }
          FUN_180180330(local_1d48,local_1c90,&local_bd0,uVar55);
LAB_1801761dd:
          pDVar8 = local_1c90;
          local_1c90 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_1801703c0(&local_1c90);
          FUN_180013ed0(local_1768);
          GAStream::~GAStream((GAStream *)local_1b80);
          GADict::~GADict((GADict *)local_1c20);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_DAT_180326bf0);
        if (iVar18 == 0) {
          GName::GName(local_1988,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1b78);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
          uVar26 = FUN_1801788e0(local_1558,*(undefined8 *)(param_1 + 0x30),local_1b78,
                                 *(undefined8 *)(param_1 + 0x28));
          FUN_1801716a0(local_1758,uVar26);
          FUN_18016fed0(local_16c8);
          pCVar24 = ArtPaint::FormPaint::GetContent(local_1758[0]);
          (**(code **)(*(longlong *)pCVar24 + 0x10))(pCVar24,local_16c8);
          if (local_16b8 == (DynamicMark *)0x0) {
            local_1980 = "Mark contains unexpected objects.";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_1980,(ThrowInfo *)&DAT_1803b78c8);
          }
          uVar26 = DocumentMarks::DynamicMark::GetSourceContent(local_16b8);
          uVar26 = FUN_180172110(local_1548,uVar26);
          FUN_18016f2c0(&local_1cd8,uVar26);
          FUN_180013ed0(local_1548);
          FUN_180013ed0(local_1538);
          pDVar11 = local_1cd8;
          pCVar40 = (ColorList<ArtColor::ColorSpacePolicy> *)
                    DocumentMarks::DynamicMark::GetOrderedSourceColorSpace(local_16b8);
          DocumentMarks::DynamicMark::setSourceColorants(pDVar11,pCVar40);
          FUN_180022cb0(local_e98);
          pDVar11 = local_1cd8;
          CVar21 = DocumentMarks::DynamicObject::getColorType((DynamicObject *)local_16b8,0);
          DocumentMarks::DynamicObject::setColorType((DynamicObject *)pDVar11,CVar21,0);
          pDVar11 = local_1cd8;
          pvVar41 = (variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
                     *)DocumentMarks::DynamicObject::GetTargetSeparations
                                 ((DynamicObject *)local_16b8,(PaintAttribute)local_f78);
          DocumentMarks::DynamicObject::SetTargetSeparations((DynamicObject *)pDVar11,pvVar41,0);
          FUN_18006d990(local_f78);
          pDVar11 = local_1cd8;
          CVar21 = DocumentMarks::DynamicObject::getColorType((DynamicObject *)local_16b8,1);
          DocumentMarks::DynamicObject::setColorType((DynamicObject *)pDVar11,CVar21,1);
          pDVar11 = local_1cd8;
          pvVar41 = (variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
                     *)DocumentMarks::DynamicObject::GetTargetSeparations
                                 ((DynamicObject *)local_16b8,(PaintAttribute)local_fe8);
          DocumentMarks::DynamicObject::SetTargetSeparations((DynamicObject *)pDVar11,pvVar41,1);
          FUN_18006d990(local_fe8);
          FUN_180180330(local_1d48,local_1cd8,&local_bd0,uVar55);
          FUN_18017a450(local_1d48,local_1cd8,uVar55);
          pDVar11 = local_1cd8;
          local_1cd8 = (DynamicMark *)0x0;
          *param_2 = (longlong)pDVar11;
          FUN_180170180(&local_1cd8);
          local_16c0 = ArtDoc::Visitor<DocumentMarks::CustomMark>::_vftable_;
          ArtDoc::VisitorBase::~VisitorBase(local_16c8);
          FUN_180013ed0(local_1758);
          GAStream::~GAStream((GAStream *)local_1b78);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_ExternalFile_180326c00);
        if (iVar18 == 0) {
          GName::GName(local_1978,"URI");
          bVar14 = (bool)GADict::GetString((GADict *)local_1d48,local_1970);
          ArtDocGlue::PDFConverters::UTF8String(local_830,bVar14);
          GAString::~GAString((GAString *)local_1970);
          FUN_18016f3a0(&local_1cb0,local_830);
          FUN_180011dc0(local_2a8,"ObjectType");
          FUN_180011dc0(local_288,"Context");
          FUN_180011dc0(local_268,&DAT_180326ccc);
          FUN_180011dc0(local_248,"ResolvedURI");
          FUN_180011dc0(local_228,"Position");
          FUN_180011dc0(local_208,"Rotation");
          FUN_180011dc0(local_1e8,"Color");
          local_1d28 = local_2a8;
          pGStack_1d20 = local_1c8;
          local_1748 = local_1d28;
          pGStack_1740 = pGStack_1d20;
          FUN_180012730(local_1458,&local_1d28,&local_1ca6);
          cVar15 = FUN_180169530(local_1d48,local_1458);
          FUN_180019170(local_1458);
          _eh_vector_destructor_iterator_(local_2a8,0x20,7,FUN_1800118b0);
          if (cVar15 != '\0') {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1cb0,true);
          }
          if (local_1d40 != '\0') {
            GName::GName(local_1968,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1968);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1cb0 + 0x2f0),0);
              }
              goto LAB_18017676e;
            }
          }
          FUN_180180330(local_1d48,local_1cb0,&local_bd0,uVar55);
LAB_18017676e:
          local_1960 = &local_1cb0;
          FUN_18016db00(local_628,&local_1960);
          FUN_1801837d0(local_1d48,local_628);
          FUN_180013b30(local_628);
          FUN_18017b590(local_1d48,local_1cb0,(ulonglong)local_1d18 & 0xff);
          pDVar8 = local_1cb0;
          local_1cb0 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_180170210(&local_1cb0);
          FUN_1800118b0(local_830);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_InputFile_180326c10);
        if (iVar18 == 0) {
          FUN_18016f400(&local_1cc8);
          FUN_180011dc0(local_4e8,"ObjectType");
          FUN_180011dc0(local_4c8,"Context");
          FUN_180011dc0(local_4a8,"Position");
          FUN_180011dc0(local_488,"Rotation");
          FUN_180011dc0(local_468,&DAT_1803272f0);
          FUN_180011dc0(local_448,"Color");
          local_1d28 = local_4e8;
          pGStack_1d20 = local_428;
          local_1738 = local_1d28;
          pGStack_1730 = pGStack_1d20;
          FUN_180012730(local_1440,&local_1d28,&local_1ca5);
          cVar15 = FUN_180169530(local_1d48,local_1440);
          FUN_180019170(local_1440);
          _eh_vector_destructor_iterator_(local_4e8,0x20,6,FUN_1800118b0);
          if (cVar15 != '\0') {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1cc8,true);
          }
          if (local_1d40 != '\0') {
            GName::GName(local_1958,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1958);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1cc8 + 0x2f0),0);
              }
              goto LAB_1801769f8;
            }
          }
          FUN_180180330(local_1d48,local_1cc8,&local_bd0,uVar55);
LAB_1801769f8:
          FUN_18017ec00(local_1d48,local_1cc8);
          FUN_18017e400(local_1d48,local_1cc8);
          FUN_18017e820(local_1d48,local_1cc8);
          pDVar8 = local_1cc8;
          local_1cc8 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_180170240(&local_1cc8);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_Barcode_180326b70);
        if (iVar18 == 0) {
          plVar50 = *(longlong **)(param_1 + 0x30);
          pcVar5 = *(code **)(*plVar50 + 0x10);
          GName::GName(local_1950,"Source");
          uVar26 = GADict::GetStream((GADict *)local_1d48,local_1948);
          (*pcVar5)(plVar50,&local_17d0,uVar26);
          GAStream::~GAStream((GAStream *)local_1948);
          if (local_17c8[0] == 0) {
LAB_180177bf8:
            local_1928 = "Invalid source content for barcode mark";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_1928,(ThrowInfo *)&DAT_1803b78c8);
          }
          local_1d58 = local_1d58 & 0xffffffff00000000;
          lVar42 = __RTDynamicCast(local_17d0,0,&ArtDoc::Group::RTTI_Type_Descriptor,
                                   &DocumentBarCode::BarCode::RTTI_Type_Descriptor);
          if (lVar42 == 0) goto LAB_180177bf8;
          this_03 = DocumentBarCode::BarCode::GetParameters(local_17d0);
          TVar22 = BarCodeWrapper::Parameters::GetType(this_03);
          bVar14 = DocumentMarks::IsAllowedInPDFPlusBarcodeMark(TVar22);
          if (!bVar14) {
            local_1940 = "Barcode type unsupported for barcode mark";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_1940,(ThrowInfo *)&DAT_1803b78c8);
          }
          uVar26 = FUN_18001e320(local_1528,local_17c8);
          uVar26 = FUN_1801716a0(local_1518,uVar26);
          FUN_18016f1e0(&local_1cf8,uVar26);
          FUN_180013ed0(local_1518);
          FUN_180011dc0(local_1c8,"ObjectType");
          FUN_180011dc0(local_1a8,"Context");
          FUN_180011dc0(local_188,"Source");
          FUN_180011dc0(local_168,"Value");
          FUN_180011dc0(local_148,"DecimalValue");
          FUN_180011dc0(local_128,"SupplementalValue");
          FUN_180011dc0(local_108,"CompositeValue");
          FUN_180011dc0(local_e8,"AutoVersion");
          FUN_180011dc0(local_c8,"Position");
          FUN_180011dc0(local_a8,"Rotation");
          FUN_180011dc0(local_88,"Color");
          local_1d28 = local_1c8;
          pGStack_1d20 = (GADict *)local_68;
          local_1728 = local_1d28;
          puStack_1720 = (ulonglong *)pGStack_1d20;
          FUN_180012730(local_1428,&local_1d28,&local_1ca4);
          cVar15 = FUN_180169530(local_1d48,local_1428);
          FUN_180019170(local_1428);
          _eh_vector_destructor_iterator_(local_1c8,0x20,0xb,FUN_1800118b0);
          if (cVar15 != '\0') {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1cf8,true);
          }
          FUN_180184710(local_1d48,local_1cf8);
          FUN_180183e70(local_1d48,local_1cf8);
          FUN_18017c0d0(local_1d48,local_1cf8);
          FUN_180179b90(local_1d48,local_1cf8);
          if (local_1d40 != '\0') {
            GName::GName(local_1938,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1938);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1cf8 + 0x2f0),0);
              }
              goto LAB_180176dee;
            }
          }
          FUN_180180330(local_1d48,local_1cf8,&local_bd0,uVar55);
LAB_180176dee:
          local_1930 = &local_1cf8;
          FUN_18016db30(local_5e8,&local_1930);
          FUN_1801837d0(local_1d48,local_5e8);
          FUN_180013b30(local_5e8);
          FUN_180179c30(local_1d48,local_1cf8,(ulonglong)local_1d18 & 0xff);
          pDVar8 = local_1cf8;
          local_1cf8 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_180170120(&local_1cf8);
          FUN_1800d5170(&local_17d0);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_Dimension_180326b80);
        if (iVar18 == 0) {
          plVar50 = *(longlong **)(param_1 + 0x30);
          pcVar5 = *(code **)(*plVar50 + 0x10);
          GName::GName(local_1920,"Source");
          uVar26 = GADict::GetStream((GADict *)local_1d48,local_1918);
          (*pcVar5)(plVar50,&local_17b8,uVar26);
          GAStream::~GAStream((GAStream *)local_1918);
          if (local_17b0[0] != 0) {
            local_1d58 = local_1d58 & 0xffffffff00000000;
            lVar42 = __RTDynamicCast(local_17b8,0,&ArtDoc::Group::RTTI_Type_Descriptor,
                                     &DocumentDimensions::Box::RTTI_Type_Descriptor);
            if (lVar42 != 0) {
              uVar26 = FUN_18001e320(local_1508,local_17b0);
              uVar26 = FUN_1801716a0(local_14f8,uVar26);
              FUN_18016f330(&local_1c40,uVar26);
              FUN_180013ed0(local_14f8);
              FUN_180011dc0(local_428,"ObjectType");
              FUN_180011dc0(local_408,"Context");
              FUN_180011dc0(local_3e8,"Source");
              FUN_180011dc0(local_3c8,"Reference");
              FUN_180011dc0(local_3a8,"ReferenceID");
              FUN_180011dc0(local_388,"ReferenceBounds");
              local_1d28 = local_428;
              pGStack_1d20 = local_368;
              local_1718 = local_1d28;
              pGStack_1710 = pGStack_1d20;
              FUN_180012730(local_1410,&local_1d28,&local_1ca3);
              cVar15 = FUN_180169530(local_1d48,local_1410);
              FUN_180019170(local_1410);
              _eh_vector_destructor_iterator_(local_428,0x20,6,FUN_1800118b0);
              if (cVar15 != '\0') {
                DocumentMarks::DynamicObject::SetHasNewFeatures(local_1c40,true);
              }
              FUN_18017ced0(local_1d48,local_1c40);
              pDVar8 = local_1c40;
              local_1c40 = (DynamicObject *)0x0;
              *param_2 = (longlong)pDVar8;
              FUN_1801701e0(&local_1c40);
              FUN_1800d5170(&local_17b8);
              FUN_1800118b0(&local_bd0);
              FUN_1800118b0(&local_bb0);
              GADict::~GADict((GADict *)local_1d48);
              FUN_1800118b0(&local_bf0);
              FUN_180013ed0(&local_1d08);
              return param_2;
            }
          }
          local_1910 = "Invalid source content for dimensions mark";
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(&local_1910,(ThrowInfo *)&DAT_1803b78c8);
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_Position_180326c20);
        if (iVar18 == 0) {
          local_14e8 = 0;
          uStack_14e0 = 0;
          FUN_18016f4d0(&local_1c88,&local_14e8);
          FUN_180011dc0(local_768,"ObjectType");
          FUN_180011dc0(local_748,"Context");
          FUN_180011dc0(local_728,"Position");
          FUN_180011dc0(local_708,&DAT_180327254);
          local_1d28 = local_768;
          pGStack_1d20 = (GADict *)local_6e8;
          local_1708 = local_1d28;
          puStack_1700 = pGStack_1d20;
          FUN_180012730(local_13f8,&local_1d28,&local_1ca1);
          cVar15 = FUN_180169530(local_1d48,local_13f8);
          FUN_180019170(local_13f8);
          _eh_vector_destructor_iterator_(local_768,0x20,4,FUN_1800118b0);
          if (cVar15 != '\0') {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1c88,true);
          }
          FUN_18017ee50(local_1d48,local_1c88,&local_bd0,uVar55);
          if (local_1d40 != '\0') {
            GName::GName(local_1908,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1908);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1c88 + 0x2f0),0);
              }
              goto LAB_180177319;
            }
          }
          FUN_180180330(local_1d48,local_1c88,&local_bd0,uVar55);
LAB_180177319:
          pDVar8 = local_1c88;
          local_1c88 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_1801702a0(&local_1c88);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_RepeatForObjects_180326c30);
        if (iVar18 == 0) {
          GName::GName(local_1900,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1b70);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
          FUN_1801788e0(local_1b58,*(undefined8 *)(param_1 + 0x30),local_1b70,
                        *(undefined8 *)(param_1 + 0x28));
          uVar26 = FUN_18001e320(local_14d8,local_1b58);
          FUN_180177c50(uVar26);
          uVar26 = FUN_18001e320(local_14c8,local_1b58);
          uVar26 = FUN_1801716a0(local_14b8,uVar26);
          FUN_1800233b0(local_1b58,uVar26);
          FUN_180013ed0(local_14b8);
          FUN_18016f640(&local_1c18,local_1b58,&DAT_1803050d0);
          FUN_180181440(local_1d48,local_1c18,uVar55);
          lVar42 = local_1c18;
          local_1c18 = 0;
          *param_2 = lVar42;
          FUN_180170330(&local_1c18);
          FUN_180013ed0(local_1b58);
          GAStream::~GAStream((GAStream *)local_1b70);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_PlateID_180326c40);
        if (iVar18 == 0) {
          GName::GName(local_18f8,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1b68);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
          FUN_1801788e0(local_1b28,*(undefined8 *)(param_1 + 0x30),local_1b68,
                        *(undefined8 *)(param_1 + 0x28));
          uVar26 = FUN_18001e320(local_14a8,local_1b28);
          uVar26 = FUN_1801716a0(local_1498,uVar26);
          FUN_1800233b0(local_1b28,uVar26);
          FUN_180013ed0(local_1498);
          FUN_18017f870(local_858,local_1d48,*(undefined8 *)(param_1 + 0x28));
          FUN_18016f450(&local_1c68,local_1b28,local_858);
          FUN_180180030(local_1d48,local_1c68);
          FUN_18017fda0(local_1d48,local_1c68,&local_bd0,uVar55);
          if (local_838 == '\0') {
            FUN_180011dc0(local_368,"ObjectType");
            local_1d3c = uVar19 | 0x100;
            FUN_180011dc0(local_348,"Context");
            local_1d3c = uVar19 | 0x300;
            FUN_180011dc0(local_328,"Source");
            local_1d3c = uVar19 | 0x700;
            FUN_180011dc0(local_308,"Repetition");
            local_1d3c = uVar19 | 0xf00;
            FUN_180011dc0(local_2e8,"Color");
            local_1d3c = uVar19 | 0x1f00;
            FUN_180011dc0(local_2c8,"Position");
            local_1d3c = uVar19 | 0x7f00;
            local_1d28 = local_368;
            pGStack_1d20 = local_2a8;
            local_16f8 = local_1d28;
            pGStack_16f0 = pGStack_1d20;
            FUN_180012730(local_13e0,&local_1d28,&local_1ca2);
            uVar19 = uVar19 | 0xff00;
            local_1d3c = uVar19;
            cVar15 = FUN_180169530(local_1d48,local_13e0);
            if (cVar15 == '\0') {
              bVar14 = false;
              goto LAB_180177753;
            }
          }
          bVar14 = true;
LAB_180177753:
          if (uVar19 >> 0xf != 0) {
            uVar19 = uVar19 & 0xffff7fff;
            FUN_180019170(local_13e0);
          }
          if ((uVar19 >> 0xe & 1) != 0) {
            _eh_vector_destructor_iterator_(local_368,0x20,6,FUN_1800118b0);
          }
          if (bVar14) {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1c68,true);
          }
          pDVar8 = local_1c68;
          local_1c68 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_180170270(&local_1c68);
          FUN_1800118b0(local_858);
          FUN_180013ed0(local_1b28);
          GAStream::~GAStream((GAStream *)local_1b68);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
      }
LAB_180177838:
      FUN_1800118b0(&local_bd0);
      FUN_1800118b0(&local_bb0);
      goto LAB_180177854;
    }
    GName::GName(local_1a38,"Source");
    GADict::GetStream((GADict *)local_1d48,local_1bb0);
    local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
    uVar26 = FUN_1801788e0(local_1628,*(undefined8 *)(param_1 + 0x30),local_1bb0,
                           *(undefined8 *)(param_1 + 0x28));
    FUN_1801716a0(&local_1b48,uVar26);
    FUN_18017d6a0(local_6e8,local_1d48,&local_bd0,uVar55);
    local_1d28 = (GADict *)FUN_1802d6b50(0x698);
    if (local_1d28 == (GADict *)0x0) {
      this_01 = (ContentObject *)0x0;
    }
    else {
      if (lStack_1b40 != 0) {
        LOCK();
        *(int *)(lStack_1b40 + 8) = *(int *)(lStack_1b40 + 8) + 1;
        UNLOCK();
      }
      local_1868 = local_1b48;
      lStack_1860 = lStack_1b40;
      this_01 = (ContentObject *)
                DocumentMarks::CustomMark::CustomMark((CustomMark *)local_1d28,&local_1868,0x1cf);
    }
    local_a70 = 0;
    uStack_a68 = 0;
    local_a60 = 0;
    uStack_a58 = 0;
    lVar42 = -1;
    do {
      lVar49 = lVar42 + 1;
      lVar7 = lVar42 + 1;
      lVar42 = lVar49;
    } while ("Custom Mark"[lVar7] != '\0');
    FUN_180010070(&local_a70,"Custom Mark",lVar49);
    pbVar35 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              (**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
    pbVar28 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
              DocumentMarks::CreateMarkName(local_810,pbVar35);
    ArtDoc::ContentObject::SetName(this_01,pbVar28);
    FUN_1800118b0(local_810);
    FUN_1800118b0(&local_a70);
    DocumentMarks::MarkPosition::setReferenceObject((MarkPosition *)(this_01 + 0x2f0),0);
    ArtDoc::CloneStrategy::CloneStrategy(local_1078,*(Document **)(param_1 + 0x28),1);
    pCVar24 = ArtPaint::FormPaint::GetContent(local_1b48);
    pLVar36 = ArtDoc::Content::GetChildren(pCVar24);
    plVar50 = *(longlong **)pLVar36;
    while( true ) {
      if (plVar50 == (longlong *)0x0) break;
      pCVar37 = (ContentObject *)(**(code **)(*plVar50 + 8))(plVar50,local_1078);
      ArtDoc::Group::AddOnTop((Group *)this_01,pCVar37);
      plVar50 = (longlong *)plVar50[1];
    }
    if (local_6e0 == 1) {
      local_1238 = 0xbff0000000000000;
      uStack_1230 = 0;
      local_1228 = 0;
      uStack_1220 = 0xbff0000000000000;
      local_1218 = 0;
      uStack_1210 = 0;
      ArtDoc::Transformable::SetTransformation
                ((Transformable *)this_01,
                 (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_1238,7);
    }
    FUN_18017d2b0(local_1d48,this_01,(ulonglong)local_1d18 & 0xff);
    this_02 = (Factory *)
              ArtPaint::FormPaint::Factory::Factory(local_d28,*(Document **)(param_1 + 0x28));
    ArtPaint::FormPaint::Factory::Get(this_02);
    ArtPaint::FormPaint::Factory::~Factory(local_d28);
    pCVar24 = ArtPaint::FormPaint::GetContent(local_1bf8);
    ArtDoc::Content::AddOnTop(pCVar24,this_01);
    if (lStack_1bf0 != 0) {
      LOCK();
      *(int *)(lStack_1bf0 + 8) = *(int *)(lStack_1bf0 + 8) + 1;
      UNLOCK();
    }
    local_1858 = local_1bf8;
    lStack_1850 = lStack_1bf0;
    uVar26 = FUN_1801716a0(local_1618,&local_1858);
    FUN_1800233b0(&local_1bf8,uVar26);
    FUN_180013ed0(local_1618);
    local_1d28 = (GADict *)FUN_1802d6b50(0x860);
    if (local_1d28 == (GADict *)0x0) {
      local_1c80 = (PDFPlusRepeatForGridMark *)0x0;
    }
    else {
      if (lStack_1bf0 != 0) {
        LOCK();
        *(int *)(lStack_1bf0 + 8) = *(int *)(lStack_1bf0 + 8) + 1;
        UNLOCK();
      }
      local_1848 = local_1bf8;
      lStack_1840 = lStack_1bf0;
      local_1c80 = (PDFPlusRepeatForGridMark *)
                   DocumentMarks::PDFPlusRepeatForGridMark::PDFPlusRepeatForGridMark
                             ((PDFPlusRepeatForGridMark *)local_1d28,0,&local_1848);
    }
    DocumentMarks::DynamicObject::linkMarkProperties((DynamicObject *)this_01);
    DocumentMarks::DynamicObject::setMarkDirty((DynamicObject *)this_01);
    FUN_1801853c0(local_1108,local_6e8);
    pPVar38 = ArtDoc::ContentObject::GetProperties((ContentObject *)local_1c80);
    FUN_18016e9f0(pPVar38,&PTR_s_DocumentMarks_RepeatForGridMark__1803263a8,local_1108);
    local_1398 = 0;
    if (local_638 == '\0') {
      cVar15 = (local_660 != '\0') + '\x02';
    }
    else {
      cVar15 = local_660 != '\0';
    }
    if (((cVar15 == '\0') || (cVar15 == '\x01')) || ((cVar15 != '\x02' && (cVar15 != '\x03')))) {
      local_13b8[0] = 0;
    }
    else {
      local_13b8[0] = 1;
    }
    if ((local_638 == '\0') || (local_640 != '\x01')) {
      local_1bd8 = (ulonglong)local_1bd8._4_4_ << 0x20;
LAB_1801744d0:
      uStack_1bd0 = 0;
    }
    else {
      if (local_648 == 1) {
        local_1bd8 = CONCAT44(local_1bd8._4_4_,2);
        goto LAB_1801744d0;
      }
      local_1bd8 = (longlong)local_648;
      uStack_1bd0 = 1;
    }
    uStack_13a8 = CONCAT71(uStack_1bcf,uStack_1bd0);
    local_13b0 = local_1bd8;
    local_13a0 = (uint)(local_6e0 != 0);
    pPVar38 = ArtDoc::ContentObject::GetProperties((ContentObject *)local_1c80);
    FUN_18016ebb0(pPVar38,&PTR_s_DocumentMarks_RepeatForGridMark__1803263b8,local_13b8);
    DocumentMarks::PDFPlusRepeatForGridMark::SetIsConvertedGridMark(local_1c80,true);
    pPVar12 = local_1c80;
    local_1c80 = (PDFPlusRepeatForGridMark *)0x0;
    *param_2 = (longlong)pPVar12;
    FUN_18006da40(local_10b0);
    FUN_18006da40(local_10d8);
    FUN_180022d90(local_1100);
    pPVar12 = local_1c80;
    if (local_1c80 != (PDFPlusRepeatForGridMark *)0x0) {
      DocumentMarks::PDFPlusRepeatForGridMark::~PDFPlusRepeatForGridMark(local_1c80);
      free(pPVar12);
    }
    FUN_180013ed0(&local_1bf8);
    ArtDoc::CloneStrategy::~CloneStrategy(local_1078);
    FUN_1801706d0(local_6e8);
    FUN_180013ed0(&local_1b48);
    GAStream::~GAStream((GAStream *)local_1bb0);
    if (0xf < uStack_bb8) {
      pvVar45 = local_bd0;
      if ((0xfff < uStack_bb8 + 1) &&
         (pvVar45 = *(void **)((longlong)local_bd0 + -8),
         0x1f < (ulonglong)((longlong)local_bd0 + (-8 - (longlong)pvVar45)))) goto LAB_180174612;
      free(pvVar45);
    }
    local_bc0 = (undefined *)0x0;
    uStack_bb8 = 0xf;
    local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
    if (0xf < uStack_b98) {
      FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
    }
    local_ba0 = (undefined *)0x0;
    uStack_b98 = 0xf;
    local_bb0 = 0;
    GADict::~GADict((GADict *)local_1d48);
    if (local_bd8 < 0x10) {
LAB_1801746b7:
      local_be0 = 0;
      local_bd8 = 0xf;
      local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
      if (plStack_1d00 == (longlong *)0x0) {
        return param_2;
      }
      FUN_180018860();
      return param_2;
    }
    pppppppiVar31 = local_bf0;
    if ((local_bd8 + 1 < 0x1000) ||
       (pppppppiVar31 = (int *******)local_bf0[-1],
       (ulonglong)((longlong)local_bf0 + (-8 - (longlong)pppppppiVar31)) < 0x20)) {
      free(pppppppiVar31);
      goto LAB_1801746b7;
    }
    goto LAB_1801746ab;
  }
  GName::GName(local_1af0,"Source");
  GADict::GetStream((GADict *)local_1d48,local_1bb8);
  local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
  uVar26 = FUN_1801788e0(local_1648,*(undefined8 *)(param_1 + 0x30),local_1bb8,
                         *(undefined8 *)(param_1 + 0x28));
  FUN_1801716a0(&local_1878,uVar26);
  local_1d28 = (GADict *)FUN_1802d6b50(0x698);
  if (local_1d28 == (GADict *)0x0) {
    local_1c60 = 0;
  }
  else {
    if (lStack_1870 != 0) {
      LOCK();
      *(int *)(lStack_1870 + 8) = *(int *)(lStack_1870 + 8) + 1;
      UNLOCK();
    }
    local_1888 = local_1878;
    lStack_1880 = lStack_1870;
    local_1c60 = DocumentMarks::CustomMark::CustomMark((CustomMark *)local_1d28,&local_1888,0x1cf);
  }
  if (local_1d40 == '\0') {
LAB_180172fa7:
    FUN_180180330(local_1d48,local_1c60,&local_bd0,uVar55);
  }
  else {
    GName::GName(local_1ae8,"Position");
    bVar14 = GADict::Has((GADict *)local_1d48,local_1ae8);
    if (bVar14) goto LAB_180172fa7;
    if (local_1d3f != 0) {
      DocumentMarks::MarkPosition::setReferenceObject((MarkPosition *)(local_1c60 + 0x2f0),0);
    }
  }
  FUN_18017b590(local_1d48,local_1c60,(ulonglong)local_1d18 & 0xff);
  *param_2 = local_1c60;
  local_1c60 = 0;
  FUN_180013ed0(&local_1878);
  GAStream::~GAStream((GAStream *)local_1bb8);
  if (0xf < uStack_bb8) {
    pvVar45 = local_bd0;
    if ((0xfff < uStack_bb8 + 1) &&
       (pvVar45 = *(void **)((longlong)local_bd0 + -8),
       0x1f < (ulonglong)((longlong)local_bd0 + (-8 - (longlong)pvVar45)))) {
LAB_180174612:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar45);
  }
  local_bc0 = (undefined *)0x0;
  uStack_bb8 = 0xf;
  local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
  if (0xf < uStack_b98) {
    pvVar6 = (void *)CONCAT71(uStack_baf,local_bb0);
    pvVar45 = pvVar6;
    if ((0xfff < uStack_b98 + 1) &&
       (pvVar45 = *(void **)((longlong)pvVar6 + -8),
       0x1f < (ulonglong)((longlong)pvVar6 + (-8 - (longlong)pvVar45)))) {
LAB_1801730ba:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar45);
  }
  local_ba0 = (undefined *)0x0;
  uStack_b98 = 0xf;
  local_bb0 = 0;
  GADict::~GADict((GADict *)local_1d48);
  if (0xf < local_bd8) {
    pppppppiVar31 = local_bf0;
    if ((0xfff < local_bd8 + 1) &&
       (pppppppiVar31 = (int *******)local_bf0[-1],
       0x1f < (ulonglong)((longlong)local_bf0 + (-8 - (longlong)pppppppiVar31)))) {
LAB_1801746ab:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pppppppiVar31);
  }
  local_be0 = 0;
  local_bd8 = 0xf;
  local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
  if (plStack_1d00 == (longlong *)0x0) {
    return param_2;
  }
  FUN_180018860();
  return param_2;
}



// ---------------------------------------------------------------
// FUNC 18017c5d0 FUN_18017c5d0
// signature: undefined FUN_18017c5d0(void)
// ---------------------------------------------------------------

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



// ---------------------------------------------------------------
// FUNC 18024d3e0 ApplyMarksFromSet
// signature: bool ApplyMarksFromSet(TaskMarkSets * this, vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_> * param_1, Page * param_2, bool param_3)
// ---------------------------------------------------------------

/* public: bool __cdecl DocumentMarks::TaskMarkSets::ApplyMarksFromSet(class std::vector<class
   std::unique_ptr<class ArtDoc::Document,struct std::default_delete<class ArtDoc::Document> >,class
   std::allocator<class std::unique_ptr<class ArtDoc::Document,struct std::default_delete<class
   ArtDoc::Document> > > > const & __ptr64,class ArtDoc::Page & __ptr64,bool) __ptr64 */

bool __thiscall
DocumentMarks::TaskMarkSets::ApplyMarksFromSet
          (TaskMarkSets *this,
          vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
          *param_1,Page *param_2,bool param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  bool bVar3;
  undefined8 *puVar4;
  
                    /* 0x24d3e0  848
                       ?ApplyMarksFromSet@TaskMarkSets@DocumentMarks@@QEAA_NAEBV?$vector@V?$unique_ptr@VDocument@ArtDoc@@U?$default_delete@VDocument@ArtDoc@@@std@@@std@@V?$allocator@V?$unique_ptr@VDocument@ArtDoc@@U?$default_delete@VDocument@ArtDoc@@@std@@@std@@@2@@std@@AEAVPage@ArtDoc@@_N@Z
                        */
  puVar4 = *(undefined8 **)param_1;
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (puVar4 == puVar1) {
    bVar3 = false;
  }
  else {
    do {
      puVar2 = (undefined8 *)ArtDoc::Document::GetPagesBegin((Document *)*puVar4);
      CopyMarksToPageWithLog(this,*(Page **)*puVar2,param_2,param_3);
      puVar4 = puVar4 + 1;
    } while (puVar4 != puVar1);
    bVar3 = true;
  }
  return bVar3;
}



// ---------------------------------------------------------------
// FUNC 18024d460 ApplyRelevantMarkSets
// signature: void ApplyRelevantMarkSets(TaskMarkSets * this, Page * param_1, int param_2, bool param_3, bool param_4, bool param_5, bool param_6)
// ---------------------------------------------------------------

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



// ---------------------------------------------------------------
// FUNC 18024df90 ApplyRelevantMarkSetsWithReuse
// signature: void ApplyRelevantMarkSetsWithReuse(TaskMarkSets * this, Page * param_1, CloneStrategy * param_2, int param_3, bool param_4, bool param_5, bool param_6)
// ---------------------------------------------------------------

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



// ---------------------------------------------------------------
// FUNC 18024e9b0 CopyMarksToPageWithLog
// signature: void CopyMarksToPageWithLog(TaskMarkSets * this, Page * param_1, Page * param_2, bool param_3)
// ---------------------------------------------------------------

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: void __cdecl DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog(class ArtDoc::Page &
   __ptr64,class ArtDoc::Page & __ptr64,bool) __ptr64 */

void __thiscall
DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog
          (TaskMarkSets *this,Page *param_1,Page *param_2,bool param_3)

{
  undefined2 *puVar1;
  char cVar2;
  code *pcVar3;
  undefined1 uVar4;
  longlong lVar5;
  longlong *plVar6;
  bool bVar7;
  PageContent *pPVar8;
  Document *pDVar9;
  __uint64 _Var10;
  undefined8 *****pppppuVar11;
  ulonglong uVar12;
  longlong *plVar13;
  undefined8 *****pppppuVar14;
  ulonglong uVar15;
  char *pcVar16;
  longlong *plVar17;
  void *pvVar18;
  undefined1 auStackY_158 [32];
  undefined1 local_118 [8];
  longlong *local_110;
  longlong local_108;
  longlong *local_100;
  longlong local_f8;
  Page *local_f0;
  TaskMarkSets *local_e8;
  Page *local_d8;
  undefined8 *****local_d0;
  undefined8 uStack_c8;
  longlong local_c0;
  ulonglong local_b8;
  undefined8 *****local_b0 [3];
  ulonglong local_98;
  undefined8 *****local_90 [3];
  ulonglong local_78;
  char local_5c [4];
  ulonglong local_58;
  
                    /* 0x24e9b0  939
                       ?CopyMarksToPageWithLog@TaskMarkSets@DocumentMarks@@QEAAXAEAVPage@ArtDoc@@0_N@Z
                        */
  local_58 = DAT_180418e00 ^ (ulonglong)auStackY_158;
  local_100 = (longlong *)0x0;
  local_f8 = 0;
  local_f0 = param_2;
  local_e8 = this;
  local_d8 = param_1;
  local_100 = (longlong *)FUN_1802d6b50(0x40);
  *local_100 = (longlong)local_100;
  local_100[1] = (longlong)local_100;
  local_100[2] = (longlong)local_100;
  *(undefined2 *)(local_100 + 3) = 0x101;
  local_110 = (longlong *)0x0;
  local_108 = 0;
  local_110 = (longlong *)FUN_1802d6b50(0x40);
  *local_110 = (longlong)local_110;
  local_110[1] = (longlong)local_110;
  local_110[2] = (longlong)local_110;
  *(undefined2 *)(local_110 + 3) = 0x101;
  bVar7 = CopyMarksToPage(param_1,param_2,param_3,
                          (set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
                           *)&local_100,
                          (set<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
                           *)&local_110,
                          (set<unsigned___int64,std::less<unsigned___int64>,std::allocator<unsigned___int64>_>
                           *)0x0,true);
  if ((!bVar7) && (local_f8 != 0)) {
    pPVar8 = ArtDoc::Page::GetContent(param_1);
    pDVar9 = ArtDoc::Content::GetDocument((Content *)pPVar8);
    ArtDoc::Document::GetFilePath(pDVar9);
    boost::filesystem::detail::path_algorithms::stem_v3((path *)local_b0);
    ExtraBoostFilesystem::ToUTF8String((path *)local_90);
    FUN_180019310(local_b0);
    uVar4 = local_118[0];
    uStack_c8 = 0;
    local_c0 = 0;
    local_b8 = 0xf;
    local_d0 = (undefined8 *****)0x0;
    plVar13 = (longlong *)*local_100;
    if (*(char *)((longlong)plVar13 + 0x19) == '\0') {
      do {
        lVar5 = local_c0;
        plVar17 = plVar13 + 4;
        if (local_c0 != 0) {
          if (local_b8 - local_c0 < 2) {
            FUN_18003ccc0(&local_d0,2,uVar4,&DAT_180335d14);
          }
          else {
            pppppuVar11 = &local_d0;
            if (0xf < local_b8) {
              pppppuVar11 = local_d0;
            }
            puVar1 = (undefined2 *)((longlong)pppppuVar11 + local_c0);
            local_c0 = local_c0 + 2;
            *puVar1 = 0x202c;
            *(undefined1 *)((longlong)pppppuVar11 + lVar5 + 2) = 0;
          }
        }
        uVar15 = plVar13[6];
        if (0xf < (ulonglong)plVar13[7]) {
          plVar17 = (longlong *)*plVar17;
        }
        if (local_b8 - local_c0 < uVar15) {
          FUN_18003ccc0(&local_d0,uVar15,uVar4,plVar17);
        }
        else {
          pppppuVar11 = &local_d0;
          if (0xf < local_b8) {
            pppppuVar11 = local_d0;
          }
          pvVar18 = (void *)((longlong)pppppuVar11 + local_c0);
          local_c0 = local_c0 + uVar15;
          memmove(pvVar18,plVar17,uVar15);
          *(undefined1 *)((longlong)pvVar18 + uVar15) = 0;
        }
        plVar17 = (longlong *)plVar13[2];
        if (*(char *)((longlong)plVar17 + 0x19) == '\0') {
          cVar2 = *(char *)(*plVar17 + 0x19);
          plVar13 = plVar17;
          plVar17 = (longlong *)*plVar17;
          while (cVar2 == '\0') {
            cVar2 = *(char *)(*plVar17 + 0x19);
            plVar13 = plVar17;
            plVar17 = (longlong *)*plVar17;
          }
        }
        else {
          cVar2 = *(char *)(plVar13[1] + 0x19);
          plVar6 = (longlong *)plVar13[1];
          plVar17 = plVar13;
          while ((plVar13 = plVar6, cVar2 == '\0' && (plVar17 == (longlong *)plVar13[2]))) {
            cVar2 = *(char *)(plVar13[1] + 0x19);
            plVar6 = (longlong *)plVar13[1];
            plVar17 = plVar13;
          }
        }
      } while (*(char *)((longlong)plVar13 + 0x19) == '\0');
      param_2 = local_f0;
      param_1 = local_d8;
      this = local_e8;
    }
    plVar13 = *(longlong **)(this + 0x158);
    pcVar3 = *(code **)(*plVar13 + 0x48);
    ArtDoc::Page::GetPageIndex(param_2);
    pppppuVar11 = local_90;
    if (0xf < local_78) {
      pppppuVar11 = local_90[0];
    }
    pppppuVar14 = &local_d0;
    if (0xf < local_b8) {
      pppppuVar14 = local_d0;
    }
    (*pcVar3)(plVar13,
              "WARNING: Missing Named Objects: %s.\nReferenced from Mark Set: %s.\nDynamic Marks linked to a missing object were removed from page %lu.\n"
              ,pppppuVar14,pppppuVar11);
    plVar13 = *(longlong **)(this + 0x158);
    pcVar3 = *(code **)(*plVar13 + 0x18);
    _Var10 = ArtDoc::Page::GetPageIndex(param_2);
    pcVar16 = local_5c + 1;
    uVar15 = _Var10 + 1;
    do {
      pcVar16 = pcVar16 + -1;
      uVar12 = uVar15 / 10;
      *pcVar16 = (char)uVar15 + (char)uVar12 * -10 + '0';
      uVar15 = uVar12;
    } while (uVar12 != 0);
    FUN_18000f620(local_b0,pcVar16,local_5c + 1,local_118);
    pppppuVar11 = local_b0;
    if (0xf < local_98) {
      pppppuVar11 = local_b0[0];
    }
    (*pcVar3)(plVar13,1,"DocumentMarks.Warning.MissingNamedObject",pppppuVar11);
    if (0xf < local_98) {
      pppppuVar11 = local_b0[0];
      if ((0xfff < local_98 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_b0[0][-1],
         0x1f < (ulonglong)((longlong)local_b0[0] + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
    if (0xf < local_b8) {
      pppppuVar11 = local_d0;
      if ((0xfff < local_b8 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_d0[-1],
         0x1f < (ulonglong)((longlong)local_d0 + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
    local_c0 = 0;
    local_b8 = 0xf;
    local_d0 = (undefined8 *****)((ulonglong)local_d0 & 0xffffffffffffff00);
    if (0xf < local_78) {
      pppppuVar11 = local_90[0];
      if ((0xfff < local_78 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_90[0][-1],
         0x1f < (ulonglong)((longlong)local_90[0] + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
  }
  if (local_108 != 0) {
    pPVar8 = ArtDoc::Page::GetContent(param_1);
    pDVar9 = ArtDoc::Content::GetDocument((Content *)pPVar8);
    ArtDoc::Document::GetFilePath(pDVar9);
    boost::filesystem::detail::path_algorithms::stem_v3((path *)local_90);
    ExtraBoostFilesystem::ToUTF8String((path *)local_b0);
    FUN_180019310(local_90);
    uStack_c8 = 0;
    local_c0 = 0;
    local_b8 = 0xf;
    local_d0 = (undefined8 *****)0x0;
    plVar13 = (longlong *)*local_110;
    if (*(char *)((longlong)plVar13 + 0x19) == '\0') {
      do {
        lVar5 = local_c0;
        plVar17 = plVar13 + 4;
        if (local_c0 != 0) {
          if (local_b8 - local_c0 < 2) {
            FUN_18003ccc0(&local_d0,2,local_118[0],&DAT_180335d14);
          }
          else {
            pppppuVar11 = &local_d0;
            if (0xf < local_b8) {
              pppppuVar11 = local_d0;
            }
            puVar1 = (undefined2 *)((longlong)pppppuVar11 + local_c0);
            local_c0 = local_c0 + 2;
            *puVar1 = 0x202c;
            *(undefined1 *)((longlong)pppppuVar11 + lVar5 + 2) = 0;
          }
        }
        lVar5 = local_c0;
        uVar15 = plVar13[6];
        if (0xf < (ulonglong)plVar13[7]) {
          plVar17 = (longlong *)*plVar17;
        }
        if (local_b8 - local_c0 < uVar15) {
          FUN_18003ccc0(&local_d0,uVar15,local_118[0],plVar17);
        }
        else {
          pppppuVar11 = &local_d0;
          if (0xf < local_b8) {
            pppppuVar11 = local_d0;
          }
          pvVar18 = (void *)((longlong)pppppuVar11 + local_c0);
          local_c0 = local_c0 + uVar15;
          memmove(pvVar18,plVar17,uVar15);
          *(undefined1 *)((longlong)pppppuVar11 + lVar5 + uVar15) = 0;
        }
        plVar17 = (longlong *)plVar13[2];
        if (*(char *)((longlong)plVar17 + 0x19) == '\0') {
          cVar2 = *(char *)(*plVar17 + 0x19);
          plVar13 = plVar17;
          plVar17 = (longlong *)*plVar17;
          while (cVar2 == '\0') {
            cVar2 = *(char *)(*plVar17 + 0x19);
            plVar13 = plVar17;
            plVar17 = (longlong *)*plVar17;
          }
        }
        else {
          cVar2 = *(char *)(plVar13[1] + 0x19);
          plVar6 = (longlong *)plVar13[1];
          plVar17 = plVar13;
          while ((plVar13 = plVar6, cVar2 == '\0' && (plVar17 == (longlong *)plVar13[2]))) {
            cVar2 = *(char *)(plVar13[1] + 0x19);
            plVar6 = (longlong *)plVar13[1];
            plVar17 = plVar13;
          }
        }
      } while (*(char *)((longlong)plVar13 + 0x19) == '\0');
      param_2 = local_f0;
      this = local_e8;
    }
    plVar13 = *(longlong **)(this + 0x158);
    pcVar3 = *(code **)(*plVar13 + 0x48);
    ArtDoc::Page::GetPageIndex(param_2);
    pppppuVar11 = local_b0;
    if (0xf < local_98) {
      pppppuVar11 = local_b0[0];
    }
    pppppuVar14 = &local_d0;
    if (0xf < local_b8) {
      pppppuVar14 = local_d0;
    }
    (*pcVar3)(plVar13,
              "WARNING: Missing Page Box: %s.\nReferenced from Mark Set: %s.\nDynamic Marks linked to a missing page box were relinked to available page box on page %lu.\n"
              ,pppppuVar14,pppppuVar11);
    plVar13 = *(longlong **)(this + 0x158);
    pcVar3 = *(code **)(*plVar13 + 0x18);
    _Var10 = ArtDoc::Page::GetPageIndex(param_2);
    pcVar16 = local_5c + 1;
    uVar15 = _Var10 + 1;
    do {
      pcVar16 = pcVar16 + -1;
      uVar12 = uVar15 / 10;
      *pcVar16 = (char)uVar15 + (char)uVar12 * -10 + '0';
      uVar15 = uVar12;
    } while (uVar12 != 0);
    FUN_18000f620(local_90,pcVar16,local_5c + 1,local_118);
    pppppuVar11 = local_90;
    if (0xf < local_78) {
      pppppuVar11 = local_90[0];
    }
    (*pcVar3)(plVar13,1,"DocumentMarks.Warning.MissingPageBox",pppppuVar11);
    if (0xf < local_78) {
      pppppuVar11 = local_90[0];
      if ((0xfff < local_78 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_90[0][-1],
         0x1f < (ulonglong)((longlong)local_90[0] + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
    if (0xf < local_b8) {
      pppppuVar11 = local_d0;
      if ((0xfff < local_b8 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_d0[-1],
         0x1f < (ulonglong)((longlong)local_d0 + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
    local_c0 = 0;
    local_b8 = 0xf;
    local_d0 = (undefined8 *****)((ulonglong)local_d0 & 0xffffffffffffff00);
    if (0xf < local_98) {
      pppppuVar11 = local_b0[0];
      if ((0xfff < local_98 + 1) &&
         (pppppuVar11 = (undefined8 *****)local_b0[0][-1],
         0x1f < (ulonglong)((longlong)local_b0[0] + (-8 - (longlong)pppppuVar11)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppuVar11);
    }
  }
  FUN_18005fae0(&local_110,&local_110,local_110[1]);
  free(local_110);
  FUN_18005fae0(&local_100,&local_100,local_100[1]);
  free(local_100);
  return;
}



// ---------------------------------------------------------------
// FUNC 180251790 PrepareMarksCachePage
// signature: vector<ArtDoc::Separation::Entry,std::allocator<ArtDoc::Separation::Entry>_> PrepareMarksCachePage(TaskMarkSets * this, Page * param_1, vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_> * param_2, vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_> * param_3, vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_> * param_4, bool param_5, bool param_6, bool param_7)
// ---------------------------------------------------------------

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



// ---------------------------------------------------------------
// FUNC 1802522d0 RecreateLoadedMarks
// signature: void RecreateLoadedMarks(TaskMarkSets * this)
// ---------------------------------------------------------------

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



