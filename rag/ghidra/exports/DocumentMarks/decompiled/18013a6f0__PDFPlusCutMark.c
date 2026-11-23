// 18013a6f0 PDFPlusCutMark

/* protected: __cdecl DocumentMarks::PDFPlusCutMark::PDFPlusCutMark(class
   DocumentMarks::PDFPlusCutMark const & __ptr64,class ArtDoc::CloneStrategy & __ptr64) __ptr64 */

PDFPlusCutMark * __thiscall
DocumentMarks::PDFPlusCutMark::PDFPlusCutMark
          (PDFPlusCutMark *this,PDFPlusCutMark *param_1,CloneStrategy *param_2)

{
  PDFPlusCutMark *pPVar1;
  PDFPlusCutMark PVar2;
  void *_Dst;
  ulonglong uVar3;
  size_t _Size;
  
                    /* 0x13a6f0  225
                       ??0PDFPlusCutMark@DocumentMarks@@IEAA@AEBV01@AEAVCloneStrategy@ArtDoc@@@Z */
  DynamicMark::DynamicMark((DynamicMark *)this,(DynamicMark *)param_1,param_2);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  this[0x6b8] = (PDFPlusCutMark)0xff;
  if (param_1[0x6b8] != (PDFPlusCutMark)0xff) {
    if (param_1[0x6b8] == (PDFPlusCutMark)0x0) {
      *(undefined8 *)(this + 0x698) = *(undefined8 *)(param_1 + 0x698);
      this[0x6b8] = (PDFPlusCutMark)0x0;
    }
    else {
      FUN_180011ca0(this + 0x698,param_1 + 0x698);
      this[0x6b8] = (PDFPlusCutMark)0x1;
    }
  }
  this[0x700] = (PDFPlusCutMark)0x0;
  pPVar1 = this + 0x708;
  this[0x788] = (PDFPlusCutMark)0xff;
  if (param_1[0x788] != (PDFPlusCutMark)0xff) {
    if (param_1[0x788] == (PDFPlusCutMark)0x0) {
      this[0x780] = (PDFPlusCutMark)0xff;
      PVar2 = param_1[0x780];
      if (PVar2 != (PDFPlusCutMark)0xff) {
        if (PVar2 == (PDFPlusCutMark)0x0) {
          *(undefined4 *)pPVar1 = *(undefined4 *)(param_1 + 0x708);
          this[0x780] = (PDFPlusCutMark)0x0;
        }
        else if (PVar2 == (PDFPlusCutMark)0x1) {
          *(undefined8 *)pPVar1 = *(undefined8 *)(param_1 + 0x708);
          this[0x780] = (PDFPlusCutMark)0x1;
        }
        else {
          FUN_1800135b0(pPVar1,param_1 + 0x708);
          this[0x780] = (PDFPlusCutMark)0x2;
        }
      }
      this[0x788] = (PDFPlusCutMark)0x0;
    }
    else {
      this[0x788] = (PDFPlusCutMark)0x1;
    }
  }
  *(undefined4 *)(this + 0x790) = *(undefined4 *)(param_1 + 0x790);
  *(undefined4 *)(this + 0x794) = *(undefined4 *)(param_1 + 0x794);
  pPVar1 = this + 0x798;
  *(undefined8 *)pPVar1 = 0;
  *(undefined8 *)(this + 0x7a0) = 0;
  *(undefined8 *)(this + 0x7a8) = 0;
  uVar3 = *(longlong *)(param_1 + 0x7a0) - *(longlong *)(param_1 + 0x798) >> 2;
  if (uVar3 != 0) {
    if (0x3fffffffffffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_1800193a0();
    }
    FUN_18003a6a0(pPVar1);
    _Dst = *(void **)pPVar1;
    _Size = *(longlong *)(param_1 + 0x7a0) - (longlong)*(void **)(param_1 + 0x798);
    memmove(_Dst,*(void **)(param_1 + 0x798),_Size);
    *(void **)(this + 0x7a0) = (void *)((longlong)_Dst + ((longlong)_Size >> 2) * 4);
  }
  *(undefined8 *)(this + 0x7b0) = 0;
  *(undefined8 *)(this + 0x7b8) = 0;
  return this;
}


