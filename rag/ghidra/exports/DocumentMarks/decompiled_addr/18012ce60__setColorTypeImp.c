// DocumentMarks.dll 18012ce60 DocumentMarks::PDFPlusBarcodeMark::setColorTypeImp
// signature: void setColorTypeImp(PDFPlusBarcodeMark * this)

/* protected: virtual void __cdecl DocumentMarks::PDFPlusBarcodeMark::setColorTypeImp(void) __ptr64
    */

void __thiscall DocumentMarks::PDFPlusBarcodeMark::setColorTypeImp(PDFPlusBarcodeMark *this)

{
  ColorType CVar1;
  ColorType CVar2;
  
                    /* 0x12ce60  2225  ?setColorTypeImp@PDFPlusBarcodeMark@DocumentMarks@@MEAAXXZ
                       0x12ce60  2226  ?setColorTypeImp@PDFPlusBearerBar@DocumentMarks@@MEAAXXZ
                       0x12ce60  2227  ?setColorTypeImp@PDFPlusCutMark@DocumentMarks@@MEAAXXZ */
  CVar1 = DynamicObject::getColorType((DynamicObject *)this,0);
  CVar2 = DynamicObject::getColorType((DynamicObject *)this,1);
  if (CVar1 != CVar2) {
    DynamicObject::setColorType((DynamicObject *)this,CVar1,1);
  }
  return;
}


