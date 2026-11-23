// 18013d2c0 SetTargetSeparationsImp

/* protected: virtual void __cdecl DocumentMarks::PDFPlusCutMark::SetTargetSeparationsImp(enum
   DocumentMarks::PaintAttribute) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::SetTargetSeparationsImp(PDFPlusCutMark *this,PaintAttribute param_1)

{
  undefined1 local_res10 [24];
  PDFPlusCutMark *local_88;
  undefined1 *local_80;
  undefined1 local_78 [96];
  char local_18;
  char local_10;
  
                    /* 0x13d2c0  1654
                       ?SetTargetSeparationsImp@PDFPlusCutMark@DocumentMarks@@MEAAXW4PaintAttribute@2@@Z
                        */
  DynamicObject::GetTargetSeparations((DynamicObject *)this,(PaintAttribute)local_78);
  local_80 = local_78;
  local_88 = this;
  FUN_18013b0b0(&local_88,param_1 == 0);
  if ((local_10 != -1) && (local_10 == '\0')) {
    FUN_1800220f0((longlong)local_18 + 1,local_res10,local_78);
  }
  return;
}


