// 18013aba0 ~PDFPlusCutMark

/* public: virtual __cdecl DocumentMarks::PDFPlusCutMark::~PDFPlusCutMark(void) __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::~PDFPlusCutMark(PDFPlusCutMark *this)

{
  int *piVar1;
  int iVar2;
  PDFPlusCutMark PVar3;
  longlong *plVar4;
  void *pvVar5;
  void *_Memory;
  
                    /* 0x13aba0  414  ??1PDFPlusCutMark@DocumentMarks@@UEAA@XZ */
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  FUN_18002c560(this + 0x7b0);
  plVar4 = *(longlong **)(this + 0x7b8);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    piVar1 = (int *)((longlong)plVar4 + 0xc);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 == 1) {
      (**(code **)(*plVar4 + 0x10))();
    }
  }
  pvVar5 = *(void **)(this + 0x798);
  if (pvVar5 != (void *)0x0) {
    _Memory = pvVar5;
    if ((0xfff < (ulonglong)((*(longlong *)(this + 0x7a8) - (longlong)pvVar5 >> 2) * 4)) &&
       (_Memory = *(void **)((longlong)pvVar5 + -8),
       0x1f < (ulonglong)((longlong)pvVar5 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
    *(undefined8 *)(this + 0x798) = 0;
    *(undefined8 *)(this + 0x7a0) = 0;
    *(undefined8 *)(this + 0x7a8) = 0;
  }
  if ((((this[0x788] != (PDFPlusCutMark)0xff) && (this[0x788] == (PDFPlusCutMark)0x0)) &&
      (PVar3 = this[0x780], PVar3 != (PDFPlusCutMark)0xff)) &&
     ((PVar3 != (PDFPlusCutMark)0x0 && (PVar3 != (PDFPlusCutMark)0x1)))) {
    FUN_180013c20(this + 0x758);
    FUN_180013c20(this + 0x730);
    FUN_180013c20(this + 0x708);
  }
  if (this[0x700] != (PDFPlusCutMark)0x0) {
    FUN_1800651a0();
  }
  FUN_18006da40(this + 0x698);
  DynamicMark::~DynamicMark((DynamicMark *)this);
  return;
}


