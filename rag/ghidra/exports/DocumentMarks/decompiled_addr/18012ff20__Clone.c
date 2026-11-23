// DocumentMarks.dll 18012ff20 DocumentMarks::PDFPlusBearerBar::Clone
// signature: PDFPlusBearerBar * Clone(PDFPlusBearerBar * this, CloneStrategy * param_1)

/* public: virtual class DocumentMarks::PDFPlusBearerBar * __ptr64 __cdecl
   DocumentMarks::PDFPlusBearerBar::Clone(class ArtDoc::CloneStrategy & __ptr64)const __ptr64 */

PDFPlusBearerBar * __thiscall
DocumentMarks::PDFPlusBearerBar::Clone(PDFPlusBearerBar *this,CloneStrategy *param_1)

{
  PDFPlusBearerBar *pPVar1;
  
                    /* 0x12ff20  872
                       ?Clone@PDFPlusBearerBar@DocumentMarks@@UEBAPEAV12@AEAVCloneStrategy@ArtDoc@@@Z
                        */
  pPVar1 = (PDFPlusBearerBar *)FUN_1802d6b50(0x790);
  if (pPVar1 == (PDFPlusBearerBar *)0x0) {
    return (PDFPlusBearerBar *)0x0;
  }
  pPVar1 = (PDFPlusBearerBar *)PDFPlusBearerBar(pPVar1,this,param_1);
  return pPVar1;
}


