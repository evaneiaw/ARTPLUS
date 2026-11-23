// DocumentMarks.dll 180131ae0 DocumentMarks::PDFPlusBearerBar::SetReferenceObject
// signature: void SetReferenceObject(PDFPlusBearerBar * this, variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer> * param_1)

/* public: void __cdecl DocumentMarks::PDFPlusBearerBar::SetReferenceObject(class std::variant<enum
   ArtDoc::PageBox,unsigned __int64,struct DocumentMarks::ProcessingStepLayer> const & __ptr64)
   __ptr64 */

void __thiscall
DocumentMarks::PDFPlusBearerBar::SetReferenceObject
          (PDFPlusBearerBar *this,
          variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer> *param_1)

{
  PDFPlusBearerBar *pPVar1;
  variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer> vVar2;
  PDFPlusBearerBar PVar3;
  PDFPlusBearerBar *local_res8;
  
                    /* 0x131ae0  1599
                       ?SetReferenceObject@PDFPlusBearerBar@DocumentMarks@@QEAAXAEBV?$variant@W4PageBox@ArtDoc@@_KUProcessingStepLayer@DocumentMarks@@@std@@@Z
                        */
  vVar2 = param_1[0x78];
  pPVar1 = this + 0x6b0;
  local_res8 = pPVar1;
  if (vVar2 == (variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>)0xff) {
    PVar3 = this[0x728];
    if (((PVar3 != (PDFPlusBearerBar)0xff) && (PVar3 != (PDFPlusBearerBar)0x0)) &&
       (PVar3 != (PDFPlusBearerBar)0x1)) {
      FUN_180013c20(this + 0x700);
      FUN_180013c20(this + 0x6d8);
      FUN_180013c20(pPVar1);
    }
    this[0x728] = (PDFPlusBearerBar)0xff;
    return;
  }
  if (vVar2 == (variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>)0x0) {
    PVar3 = this[0x728];
    if (PVar3 == (PDFPlusBearerBar)0x0) {
      *(undefined4 *)pPVar1 = *(undefined4 *)param_1;
      return;
    }
    if (((PVar3 != (PDFPlusBearerBar)0xff) && (PVar3 != (PDFPlusBearerBar)0x0)) &&
       (PVar3 != (PDFPlusBearerBar)0x1)) {
      FUN_180013c20(this + 0x700);
      FUN_180013c20(this + 0x6d8);
      FUN_180013c20(pPVar1);
    }
    this[0x728] = (PDFPlusBearerBar)0xff;
    *(undefined4 *)pPVar1 = *(undefined4 *)param_1;
    this[0x728] = (PDFPlusBearerBar)0x0;
    return;
  }
  if (vVar2 != (variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>)0x1) {
    FUN_1800b2740(&local_res8);
    return;
  }
  PVar3 = this[0x728];
  if (PVar3 == (PDFPlusBearerBar)0x1) {
    *(undefined8 *)pPVar1 = *(undefined8 *)param_1;
    return;
  }
  if (((PVar3 != (PDFPlusBearerBar)0xff) && (PVar3 != (PDFPlusBearerBar)0x0)) &&
     (PVar3 != (PDFPlusBearerBar)0x1)) {
    FUN_180013c20(this + 0x700);
    FUN_180013c20(this + 0x6d8);
    FUN_180013c20(pPVar1);
  }
  this[0x728] = (PDFPlusBearerBar)0xff;
  *(undefined8 *)pPVar1 = *(undefined8 *)param_1;
  this[0x728] = (PDFPlusBearerBar)0x1;
  return;
}


