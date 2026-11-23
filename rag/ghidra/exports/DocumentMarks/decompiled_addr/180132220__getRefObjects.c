// DocumentMarks.dll 180132220 DocumentMarks::PDFPlusBearerBar::getRefObjects
// signature: vector<unsigned___int64,std::allocator<unsigned___int64>_> getRefObjects(PDFPlusBearerBar * this)

/* public: virtual class std::vector<unsigned __int64,class std::allocator<unsigned __int64> >
   __cdecl DocumentMarks::PDFPlusBearerBar::getRefObjects(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusBearerBar::getRefObjects(PDFPlusBearerBar *this)

{
  undefined8 *in_RDX;
  
                    /* 0x132220  2046
                       ?getRefObjects@PDFPlusBearerBar@DocumentMarks@@UEBA?AV?$vector@_KV?$allocator@_K@std@@@std@@XZ
                        */
  *in_RDX = 0;
  in_RDX[1] = 0;
  in_RDX[2] = 0;
  if ((this != (PDFPlusBearerBar *)0xfffffffffffff950) && (this[0x728] == (PDFPlusBearerBar)0x1)) {
    FUN_18003c5a0();
  }
  if (*(int *)(this + 0x730) != 0) {
    FUN_18003ca10();
  }
  return;
}


