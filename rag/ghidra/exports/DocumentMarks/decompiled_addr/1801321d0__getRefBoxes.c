// DocumentMarks.dll 1801321d0 DocumentMarks::PDFPlusBearerBar::getRefBoxes
// signature: vector<ArtDoc::PageBox,std::allocator<ArtDoc::PageBox>_> getRefBoxes(PDFPlusBearerBar * this)

/* public: virtual class std::vector<enum ArtDoc::PageBox,class std::allocator<enum ArtDoc::PageBox>
   > __cdecl DocumentMarks::PDFPlusBearerBar::getRefBoxes(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusBearerBar::getRefBoxes(PDFPlusBearerBar *this)

{
  undefined8 *in_RDX;
  
                    /* 0x1321d0  2019
                       ?getRefBoxes@PDFPlusBearerBar@DocumentMarks@@UEBA?AV?$vector@W4PageBox@ArtDoc@@V?$allocator@W4PageBox@ArtDoc@@@std@@@std@@XZ
                        */
  *in_RDX = 0;
  in_RDX[1] = 0;
  in_RDX[2] = 0;
  if ((this != (PDFPlusBearerBar *)0xfffffffffffff950) && (this[0x728] == (PDFPlusBearerBar)0x0)) {
    FUN_18012f730();
  }
  return;
}


