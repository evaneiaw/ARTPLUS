// 18013e570 getPositionRefObject

/* public: virtual class ArtDoc::ContentObject * __ptr64 __cdecl
   DocumentMarks::PDFPlusCutMark::getPositionRefObject(void)const __ptr64 */

ContentObject * __thiscall DocumentMarks::PDFPlusCutMark::getPositionRefObject(PDFPlusCutMark *this)

{
  PDFPlusCutMark *pPVar1;
  Content *this_00;
  ContentObject *pCVar2;
  
                    /* 0x13e570  2005
                       ?getPositionRefObject@PDFPlusCutMark@DocumentMarks@@UEBAPEAVContentObject@ArtDoc@@XZ
                        */
  pPVar1 = this + 0x708;
  if ((((pPVar1 == (PDFPlusCutMark *)0x0) || (this[0x788] != (PDFPlusCutMark)0x0)) ||
      (this[0x780] != (PDFPlusCutMark)0x1)) || (*(__uint64 *)pPVar1 == 0)) {
    return (ContentObject *)0x0;
  }
  this_00 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
                    /* WARNING: Could not recover jumptable at 0x00018013e5a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pCVar2 = ArtDoc::Content::GetObjectWithID(this_00,*(__uint64 *)pPVar1);
  return pCVar2;
}


