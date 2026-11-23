// 180042960 CopyMarksToPage

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


