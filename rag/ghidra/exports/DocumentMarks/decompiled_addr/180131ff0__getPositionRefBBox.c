// DocumentMarks.dll 180131ff0 DocumentMarks::PDFPlusBearerBar::getPositionRefBBox
// signature: RectangleBase<YAGL::MilliPointCoordinateSystem> getPositionRefBBox(PDFPlusBearerBar * this)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* public: virtual class YAGL::RectangleBase<struct YAGL::MilliPointCoordinateSystem> __cdecl
   DocumentMarks::PDFPlusBearerBar::getPositionRefBBox(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusBearerBar::getPositionRefBBox(PDFPlusBearerBar *this)

{
  PDFPlusBearerBar *pPVar1;
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
  
                    /* 0x131ff0  2000
                       ?getPositionRefBBox@PDFPlusBearerBar@DocumentMarks@@UEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@XZ
                        */
  pCVar4 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
  pPVar1 = this + 0x6b0;
  if (pPVar1 != (PDFPlusBearerBar *)0x0) {
    if (this[0x728] == (PDFPlusBearerBar)0x0) {
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
LAB_1801320a9:
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
    else if ((((pPVar1 != (PDFPlusBearerBar *)0x0) && (this[0x728] == (PDFPlusBearerBar)0x1)) &&
             (*(undefined8 *)pPVar1 != 0)) &&
            ((bVar3 = DynamicObject::isNotLinkedYet((DynamicObject *)this), !bVar3 &&
             (pCVar6 = ArtDoc::Content::GetObjectWithID(pCVar4,*(undefined8 *)pPVar1),
             pCVar6 != (ContentObject *)0x0)))) {
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
      goto LAB_1801320a9;
    }
  }
  in_RDX[3] = 0;
  in_RDX[2] = 0;
  in_RDX[1] = 0;
  *in_RDX = 0;
  *(undefined1 *)(in_RDX + 4) = 1;
  return;
}


