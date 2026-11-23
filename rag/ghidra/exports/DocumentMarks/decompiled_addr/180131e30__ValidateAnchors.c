// DocumentMarks.dll 180131e30 DocumentMarks::PDFPlusBearerBar::ValidateAnchors
// signature: void ValidateAnchors(PDFPlusBearerBar * this)

/* protected: void __cdecl DocumentMarks::PDFPlusBearerBar::ValidateAnchors(void) __ptr64 */

void __thiscall DocumentMarks::PDFPlusBearerBar::ValidateAnchors(PDFPlusBearerBar *this)

{
  Anchor AVar1;
  Anchor AVar2;
  
                    /* 0x131e30  1751  ?ValidateAnchors@PDFPlusBearerBar@DocumentMarks@@IEAAXXZ */
  if (*(int *)(this + 0x6a8) == 0) {
    AVar1 = YAGL::ToVertical(*(Anchor *)(this + 0x378));
    AVar2 = YAGL::ToVertical(*(Anchor *)(this + 0x37c));
  }
  else {
    if (*(int *)(this + 0x6a8) != 1) {
      return;
    }
    AVar1 = YAGL::ToHorizontal(*(Anchor *)(this + 0x378));
    AVar2 = YAGL::ToHorizontal(*(Anchor *)(this + 0x37c));
  }
  if ((*(Anchor *)(this + 0x378) != AVar1) || (*(Anchor *)(this + 0x37c) != AVar2)) {
    MarkPosition::setAnchors((MarkPosition *)(this + 0x2f0),AVar1,AVar2);
  }
  return;
}


