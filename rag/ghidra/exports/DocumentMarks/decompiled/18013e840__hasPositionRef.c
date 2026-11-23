// 18013e840 hasPositionRef

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


