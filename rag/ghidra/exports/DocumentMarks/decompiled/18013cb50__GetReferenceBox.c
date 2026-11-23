// 18013cb50 GetReferenceBox

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


