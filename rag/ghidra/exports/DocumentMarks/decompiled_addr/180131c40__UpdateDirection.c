// DocumentMarks.dll 180131c40 DocumentMarks::PDFPlusBearerBar::UpdateDirection
// signature: void UpdateDirection(PDFPlusBearerBar * this)

/* private: void __cdecl DocumentMarks::PDFPlusBearerBar::UpdateDirection(void) __ptr64 */

void __thiscall DocumentMarks::PDFPlusBearerBar::UpdateDirection(PDFPlusBearerBar *this)

{
  Anchor AVar1;
  Anchor AVar2;
  
                    /* 0x131c40  1724  ?UpdateDirection@PDFPlusBearerBar@DocumentMarks@@AEAAXXZ */
  AVar1 = YAGL::ToVertical(*(Anchor *)(this + 0x378));
  AVar2 = YAGL::ToVertical(*(Anchor *)(this + 0x37c));
  if ((*(Anchor *)(this + 0x378) == AVar1) && (*(Anchor *)(this + 0x37c) == AVar2)) {
    *(undefined4 *)(this + 0x6a8) = 0;
    return;
  }
  *(undefined4 *)(this + 0x6a8) = 1;
  return;
}


