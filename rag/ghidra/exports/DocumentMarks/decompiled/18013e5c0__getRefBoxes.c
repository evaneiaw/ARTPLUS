// 18013e5c0 getRefBoxes

/* public: virtual class std::vector<enum ArtDoc::PageBox,class std::allocator<enum ArtDoc::PageBox>
   > __cdecl DocumentMarks::PDFPlusCutMark::getRefBoxes(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::getRefBoxes(PDFPlusCutMark *this)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined8 *in_RDX;
  
                    /* 0x13e5c0  2021
                       ?getRefBoxes@PDFPlusCutMark@DocumentMarks@@UEBA?AV?$vector@W4PageBox@ArtDoc@@V?$allocator@W4PageBox@ArtDoc@@@std@@@std@@XZ
                        */
  if (((this + 0x708 == (PDFPlusCutMark *)0x0) || (this[0x788] != (PDFPlusCutMark)0x0)) ||
     (this[0x780] != (PDFPlusCutMark)0x0)) {
    *in_RDX = 0;
    in_RDX[1] = 0;
    in_RDX[2] = 0;
    return;
  }
  uVar1 = *(undefined4 *)(this + 0x708);
  *in_RDX = 0;
  in_RDX[1] = 0;
  in_RDX[2] = 0;
  puVar2 = (undefined4 *)FUN_1802d6b50(4);
  *in_RDX = puVar2;
  in_RDX[2] = puVar2 + 1;
  *puVar2 = uVar1;
  in_RDX[1] = puVar2 + 1;
  return;
}


