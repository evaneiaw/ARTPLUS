// DocumentMarks.dll 180131c30 DocumentMarks::PDFPlusBearerBar::SetSizeReference
// signature: void SetSizeReference(PDFPlusBearerBar * this, SizeReference param_1)

/* public: void __cdecl DocumentMarks::PDFPlusBearerBar::SetSizeReference(enum
   DocumentMarks::PDFPlusBearerBar::SizeReference) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusBearerBar::SetSizeReference(PDFPlusBearerBar *this,SizeReference param_1)

{
                    /* 0x131c30  1637
                       ?SetSizeReference@PDFPlusBearerBar@DocumentMarks@@QEAAXW4SizeReference@12@@Z
                        */
  *(SizeReference *)(this + 0x730) = param_1;
  return;
}


