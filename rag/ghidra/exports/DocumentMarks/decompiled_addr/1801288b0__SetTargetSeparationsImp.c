// DocumentMarks.dll 1801288b0 DocumentMarks::PDFPlusBarcodeMark::SetTargetSeparationsImp
// signature: void SetTargetSeparationsImp(PDFPlusBarcodeMark * this, PaintAttribute param_1)

/* protected: virtual void __cdecl DocumentMarks::PDFPlusBarcodeMark::SetTargetSeparationsImp(enum
   DocumentMarks::PaintAttribute) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusBarcodeMark::SetTargetSeparationsImp
          (PDFPlusBarcodeMark *this,PaintAttribute param_1)

{
  PDFPlusBarcodeMark *local_88;
  undefined1 *local_80;
  undefined1 local_78 [104];
  char local_10;
  
                    /* 0x1288b0  1652
                       ?SetTargetSeparationsImp@PDFPlusBarcodeMark@DocumentMarks@@MEAAXW4PaintAttribute@2@@Z
                       0x1288b0  1653
                       ?SetTargetSeparationsImp@PDFPlusBearerBar@DocumentMarks@@MEAAXW4PaintAttribute@2@@Z
                       0x1288b0  1655
                       ?SetTargetSeparationsImp@PDFPlusInputFileMark@DocumentMarks@@MEAAXW4PaintAttribute@2@@Z
                       0x1288b0  1656
                       ?SetTargetSeparationsImp@PDFPlusRepeatForSeparationsMark@DocumentMarks@@MEAAXW4PaintAttribute@2@@Z
                        */
  DynamicObject::GetTargetSeparations((DynamicObject *)this,(PaintAttribute)local_78);
  local_80 = local_78;
  local_88 = this;
  FUN_1801263f0(&local_88,param_1 == 0);
  if ((local_10 != -1) && (local_10 == '\0')) {
    FUN_180022e80(local_78);
  }
  return;
}


