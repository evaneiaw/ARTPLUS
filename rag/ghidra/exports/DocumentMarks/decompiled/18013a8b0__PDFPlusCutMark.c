// 18013a8b0 PDFPlusCutMark

/* public: __cdecl DocumentMarks::PDFPlusCutMark::PDFPlusCutMark(class std::shared_ptr<class
   ArtPaint::FormPaint const >) __ptr64 */

PDFPlusCutMark * __thiscall
DocumentMarks::PDFPlusCutMark::PDFPlusCutMark(PDFPlusCutMark *this,undefined8 *param_2)

{
  int *piVar1;
  longlong *plVar2;
  PDFPlusCutMark *pPVar3;
  int iVar4;
  undefined4 *puVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined8 local_28;
  undefined8 uStack_20;
  
                    /* 0x13a8b0  226
                       ??0PDFPlusCutMark@DocumentMarks@@QEAA@V?$shared_ptr@$$CBVFormPaint@ArtPaint@@@std@@@Z
                        */
  DynamicMark::DynamicMark((DynamicMark *)this,false,0x1ce);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this + 0x698) = 0;
  this[0x6b8] = (PDFPlusCutMark)0x0;
  this[0x700] = (PDFPlusCutMark)0x0;
  *(undefined4 *)(this + 0x708) = 3;
  this[0x780] = (PDFPlusCutMark)0x0;
  this[0x788] = (PDFPlusCutMark)0x0;
  *(undefined4 *)(this + 0x790) = 1;
  *(undefined4 *)(this + 0x794) = 2;
  pPVar3 = this + 0x798;
  *(undefined8 *)pPVar3 = 0;
  *(undefined8 *)(this + 0x7a0) = 0;
  *(undefined8 *)(this + 0x7a8) = 0;
  FUN_18003a6a0(pPVar3,1);
  puVar5 = *(undefined4 **)pPVar3;
  *puVar5 = 0;
  *(undefined4 **)(this + 0x7a0) = puVar5 + 1;
  *(undefined8 *)(this + 0x7b0) = 0;
  *(undefined8 *)(this + 0x7b8) = 0;
  if (param_2[1] != 0) {
    LOCK();
    piVar1 = (int *)(param_2[1] + 8);
    *piVar1 = *piVar1 + 1;
    UNLOCK();
  }
  local_28 = *param_2;
  uStack_20 = param_2[1];
  DynamicMark::SetSourceContent((DynamicMark *)this,&local_28);
  DynamicObject::setColorType((DynamicObject *)this,1,0);
  MarkPosition::setReferenceObject((MarkPosition *)(this + 0x2f0),0);
  plVar6 = (longlong *)param_2[1];
  if (plVar6 != (longlong *)0x0) {
    LOCK();
    plVar2 = plVar6 + 1;
    lVar7 = *plVar2;
    *(int *)plVar2 = (int)*plVar2 + -1;
    UNLOCK();
    if ((int)lVar7 == 1) {
      (**(code **)*plVar6)(plVar6);
      LOCK();
      piVar1 = (int *)((longlong)plVar6 + 0xc);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 == 1) {
        (**(code **)(*plVar6 + 8))(plVar6);
      }
    }
  }
  return this;
}


