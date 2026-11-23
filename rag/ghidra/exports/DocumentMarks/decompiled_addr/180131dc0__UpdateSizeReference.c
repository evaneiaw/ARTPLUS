// DocumentMarks.dll 180131dc0 DocumentMarks::PDFPlusBearerBar::UpdateSizeReference
// signature: void UpdateSizeReference(PDFPlusBearerBar * this)

/* public: void __cdecl DocumentMarks::PDFPlusBearerBar::UpdateSizeReference(void) __ptr64 */

void __thiscall DocumentMarks::PDFPlusBearerBar::UpdateSizeReference(PDFPlusBearerBar *this)

{
  bool bVar1;
  
                    /* 0x131dc0  1749  ?UpdateSizeReference@PDFPlusBearerBar@DocumentMarks@@QEAAXXZ
                        */
  switch(*(undefined4 *)(this + 0x730)) {
  default:
    goto switchD_180131dde_caseD_0;
  case 1:
  case 2:
  case 3:
  case 4:
    bVar1 = *(int *)(this + 0x6a8) == 0;
    break;
  case 5:
  case 6:
  case 7:
  case 8:
    bVar1 = *(int *)(this + 0x6a8) == 1;
  }
  if (bVar1) {
    *(undefined4 *)(this + 0x730) = 0;
  }
switchD_180131dde_caseD_0:
  return;
}


