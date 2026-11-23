// DocumentMarks.dll 180132190 DocumentMarks::PDFPlusBearerBar::getPositionRefObject
// signature: ContentObject * getPositionRefObject(PDFPlusBearerBar * this)

/* public: virtual class ArtDoc::ContentObject * __ptr64 __cdecl
   DocumentMarks::PDFPlusBearerBar::getPositionRefObject(void)const __ptr64 */

ContentObject * __thiscall
DocumentMarks::PDFPlusBearerBar::getPositionRefObject(PDFPlusBearerBar *this)

{
  PDFPlusBearerBar *pPVar1;
  Content *this_00;
  ContentObject *pCVar2;
  
                    /* 0x132190  2004
                       ?getPositionRefObject@PDFPlusBearerBar@DocumentMarks@@UEBAPEAVContentObject@ArtDoc@@XZ
                        */
  pPVar1 = this + 0x6b0;
  if (((pPVar1 == (PDFPlusBearerBar *)0x0) || (this[0x728] != (PDFPlusBearerBar)0x1)) ||
     (*(__uint64 *)pPVar1 == 0)) {
    return (ContentObject *)0x0;
  }
  this_00 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
                    /* WARNING: Could not recover jumptable at 0x0001801321bf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pCVar2 = ArtDoc::Content::GetObjectWithID(this_00,*(__uint64 *)pPVar1);
  return pCVar2;
}


