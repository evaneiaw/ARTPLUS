// 18013d240 SetReferenceObject

/* public: void __cdecl DocumentMarks::PDFPlusCutMark::SetReferenceObject(class std::variant<class
   std::variant<enum ArtDoc::PageBox,unsigned __int64,struct
   DocumentMarks::ProcessingStepLayer>,struct
   DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations> const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusCutMark::SetReferenceObject
          (PDFPlusCutMark *this,
          variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>
          *param_1)

{
  PDFPlusCutMark *local_res8 [4];
  
                    /* 0x13d240  1600
                       ?SetReferenceObject@PDFPlusCutMark@DocumentMarks@@QEAAXAEBV?$variant@V?$variant@W4PageBox@ArtDoc@@_KUProcessingStepLayer@DocumentMarks@@@std@@UAllStructuralDesignStations@PDFPlusCutMark@DocumentMarks@@@std@@@Z
                        */
  local_res8[0] = this + 0x708;
  if (param_1[0x80] ==
      (variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>
       )0xff) {
    FUN_1800b9b20(local_res8[0]);
    return;
  }
  if (param_1[0x80] ==
      (variant<std::variant<ArtDoc::PageBox,unsigned___int64,DocumentMarks::ProcessingStepLayer>,DocumentMarks::PDFPlusCutMark::AllStructuralDesignStations>
       )0x0) {
    FUN_1800b28c0(local_res8);
    return;
  }
  if (this[0x788] == (PDFPlusCutMark)0x1) {
    return;
  }
  FUN_1800b9b20(local_res8[0]);
  this[0x788] = (PDFPlusCutMark)0x1;
  return;
}


