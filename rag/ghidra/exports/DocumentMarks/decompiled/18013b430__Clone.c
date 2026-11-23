// 18013b430 Clone

/* public: virtual class DocumentMarks::PDFPlusCutMark * __ptr64 __cdecl
   DocumentMarks::PDFPlusCutMark::Clone(class ArtDoc::CloneStrategy & __ptr64)const __ptr64 */

PDFPlusCutMark * __thiscall
DocumentMarks::PDFPlusCutMark::Clone(PDFPlusCutMark *this,CloneStrategy *param_1)

{
  PDFPlusCutMark *pPVar1;
  
                    /* 0x13b430  874
                       ?Clone@PDFPlusCutMark@DocumentMarks@@UEBAPEAV12@AEAVCloneStrategy@ArtDoc@@@Z
                        */
  pPVar1 = (PDFPlusCutMark *)FUN_1802d6b50(0x7c0);
  if (pPVar1 == (PDFPlusCutMark *)0x0) {
    return (PDFPlusCutMark *)0x0;
  }
  pPVar1 = (PDFPlusCutMark *)PDFPlusCutMark(pPVar1,this,param_1);
  return pPVar1;
}


