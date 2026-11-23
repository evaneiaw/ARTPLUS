// 18013e640 getRefObjects

/* public: virtual class std::vector<unsigned __int64,class std::allocator<unsigned __int64> >
   __cdecl DocumentMarks::PDFPlusCutMark::getRefObjects(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::getRefObjects(PDFPlusCutMark *this)

{
  longlong *plVar1;
  longlong *plVar2;
  void *_Memory;
  void *pvVar3;
  longlong *plVar4;
  longlong *in_RDX;
  PDFPlusCutMark *pPVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined4 uVar8;
  void *local_20 [2];
  longlong local_10;
  
                    /* 0x13e640  2048
                       ?getRefObjects@PDFPlusCutMark@DocumentMarks@@UEBA?AV?$vector@_KV?$allocator@_K@std@@@std@@XZ
                        */
  *in_RDX = 0;
  in_RDX[1] = 0;
  in_RDX[2] = 0;
  uVar8 = 1;
  pPVar5 = this + 0x698;
  if ((pPVar5 == (PDFPlusCutMark *)0x0) || (this[0x6b8] != (PDFPlusCutMark)0x1)) {
    pPVar5 = (PDFPlusCutMark *)0x0;
  }
  if (pPVar5 != (PDFPlusCutMark *)0x0) {
    plVar1 = (longlong *)FUN_1801503a0(local_20);
    if (in_RDX != plVar1) {
      pvVar3 = (void *)*in_RDX;
      if (pvVar3 != (void *)0x0) {
        _Memory = pvVar3;
        if ((0xfff < (in_RDX[2] - (longlong)pvVar3 & 0xfffffffffffffff8U)) &&
           (_Memory = *(void **)((longlong)pvVar3 + -8),
           0x1f < (ulonglong)((longlong)pvVar3 + (-8 - (longlong)_Memory)))) goto LAB_18013e744;
        free(_Memory);
        *in_RDX = 0;
        in_RDX[1] = 0;
        in_RDX[2] = 0;
      }
      *in_RDX = *plVar1;
      in_RDX[1] = plVar1[1];
      in_RDX[2] = plVar1[2];
      *plVar1 = 0;
      plVar1[1] = 0;
      plVar1[2] = 0;
    }
    if (local_20[0] != (void *)0x0) {
      pvVar3 = local_20[0];
      if ((0xfff < (local_10 - (longlong)local_20[0] & 0xfffffffffffffff8U)) &&
         (pvVar3 = *(void **)((longlong)local_20[0] + -8),
         0x1f < (ulonglong)((longlong)local_20[0] + (-8 - (longlong)pvVar3)))) {
LAB_18013e744:
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar3);
    }
  }
  if (((this + 0x708 != (PDFPlusCutMark *)0x0) && (this[0x788] == (PDFPlusCutMark)0x0)) &&
     (this[0x780] == (PDFPlusCutMark)0x1)) {
    if ((undefined8 *)in_RDX[1] == (undefined8 *)in_RDX[2]) {
      FUN_18003c5a0();
    }
    else {
      *(undefined8 *)in_RDX[1] = *(undefined8 *)(this + 0x708);
      in_RDX[1] = in_RDX[1] + 8;
    }
  }
  FUN_18006b9e0(*in_RDX,in_RDX[1],in_RDX[1] - *in_RDX >> 3,0,uVar8);
  plVar1 = (longlong *)in_RDX[1];
  plVar6 = (longlong *)*in_RDX;
  if (plVar6 == plVar1) {
    return;
  }
  if (plVar6 + 1 == plVar1) {
    return;
  }
  plVar2 = plVar6 + 1;
  lVar7 = *plVar6;
  do {
    plVar4 = plVar2;
    plVar2 = plVar4 + 1;
    if (lVar7 == *plVar4) {
      for (; plVar2 != plVar1; plVar2 = plVar2 + 1) {
        if (*plVar6 != *plVar2) {
          plVar6 = plVar6 + 1;
          *plVar6 = *plVar2;
        }
      }
      plVar6 = plVar6 + 1;
      if (plVar6 != plVar1) {
        lVar7 = in_RDX[1];
        memmove(plVar6,plVar1,lVar7 - (longlong)plVar1);
        in_RDX[1] = (lVar7 - (longlong)plVar1) + (longlong)plVar6;
      }
      return;
    }
    plVar6 = plVar4;
    lVar7 = *plVar4;
  } while (plVar2 != plVar1);
  return;
}


