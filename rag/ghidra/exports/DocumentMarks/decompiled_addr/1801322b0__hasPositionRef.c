// DocumentMarks.dll 1801322b0 DocumentMarks::PDFPlusBearerBar::hasPositionRef
// signature: bool hasPositionRef(PDFPlusBearerBar * this)

/* public: virtual bool __cdecl DocumentMarks::PDFPlusBearerBar::hasPositionRef(void)const __ptr64
    */

bool __thiscall DocumentMarks::PDFPlusBearerBar::hasPositionRef(PDFPlusBearerBar *this)

{
                    /* 0x1322b0  2087  ?hasPositionRef@PDFPlusBearerBar@DocumentMarks@@UEBA_NXZ */
  if (((this + 0x6b0 == (PDFPlusBearerBar *)0x0) || (this[0x728] != (PDFPlusBearerBar)0x1)) ||
     (*(longlong *)(this + 0x6b0) != 0)) {
    return true;
  }
  return false;
}


