// DocumentMarks.dll 18012f8c0 DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar
// signature: undefined PDFPlusBearerBar(PDFPlusBearerBar * this, PDFPlusBearerBar * param_1, CloneStrategy * param_2)

/* protected: __cdecl DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar(class
   DocumentMarks::PDFPlusBearerBar const & __ptr64,class ArtDoc::CloneStrategy & __ptr64) __ptr64 */

PDFPlusBearerBar * __thiscall
DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar
          (PDFPlusBearerBar *this,PDFPlusBearerBar *param_1,CloneStrategy *param_2)

{
  PDFPlusBearerBar *pPVar1;
  PDFPlusBearerBar PVar2;
  void *_Dst;
  longlong lVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  size_t _Size;
  
                    /* 0x12f8c0  221
                       ??0PDFPlusBearerBar@DocumentMarks@@IEAA@AEBV01@AEAVCloneStrategy@ArtDoc@@@Z
                        */
  DynamicMark::DynamicMark((DynamicMark *)this,(DynamicMark *)param_1,param_2);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this + 0x698) = *(undefined8 *)(param_1 + 0x698);
  *(undefined8 *)(this + 0x6a0) = *(undefined8 *)(param_1 + 0x6a0);
  *(undefined4 *)(this + 0x6a8) = *(undefined4 *)(param_1 + 0x6a8);
  pPVar1 = this + 0x6b0;
  this[0x728] = (PDFPlusBearerBar)0xff;
  PVar2 = param_1[0x728];
  if (PVar2 != (PDFPlusBearerBar)0xff) {
    if (PVar2 == (PDFPlusBearerBar)0x0) {
      *(undefined4 *)pPVar1 = *(undefined4 *)(param_1 + 0x6b0);
      this[0x728] = (PDFPlusBearerBar)0x0;
    }
    else if (PVar2 == (PDFPlusBearerBar)0x1) {
      *(undefined8 *)pPVar1 = *(undefined8 *)(param_1 + 0x6b0);
      this[0x728] = (PDFPlusBearerBar)0x1;
    }
    else {
      FUN_1800135b0(pPVar1,param_1 + 0x6b0);
      this[0x728] = (PDFPlusBearerBar)0x2;
    }
  }
  *(undefined4 *)(this + 0x730) = *(undefined4 *)(param_1 + 0x730);
  uVar4 = 0;
  *(undefined8 *)(this + 0x738) = 0;
  *(undefined8 *)(this + 0x740) = 0;
  *(undefined8 *)(this + 0x748) = 0;
  uVar5 = *(longlong *)(param_1 + 0x740) - *(longlong *)(param_1 + 0x738) >> 3;
  if (uVar5 != 0) {
    if (0x1fffffffffffffff < uVar5) {
                    /* WARNING: Subroutine does not return */
      FUN_1800193a0();
    }
    uVar5 = uVar5 * 8;
    if (uVar5 != 0) {
      if (uVar5 < 0x1000) {
        uVar4 = FUN_1802d6b50(uVar5);
      }
      else {
        if (uVar5 + 0x27 <= uVar5) {
                    /* WARNING: Subroutine does not return */
          FUN_180019130();
        }
        lVar3 = FUN_1802d6b50();
        if (lVar3 == 0) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        uVar4 = lVar3 + 0x27U & 0xffffffffffffffe0;
        *(longlong *)(uVar4 - 8) = lVar3;
      }
    }
    *(ulonglong *)(this + 0x738) = uVar4;
    *(ulonglong *)(this + 0x740) = uVar4;
    *(ulonglong *)(this + 0x748) = uVar4 + uVar5;
    _Dst = *(void **)(this + 0x738);
    _Size = *(longlong *)(param_1 + 0x740) - (longlong)*(void **)(param_1 + 0x738);
    memmove(_Dst,*(void **)(param_1 + 0x738),_Size);
    *(void **)(this + 0x740) = (void *)((longlong)_Dst + ((longlong)_Size >> 3) * 8);
  }
  FUN_180026ca0(this + 0x750,4,FUN_1800299e0);
  return this;
}


