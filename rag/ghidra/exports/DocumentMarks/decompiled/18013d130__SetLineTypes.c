// 18013d130 SetLineTypes

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


