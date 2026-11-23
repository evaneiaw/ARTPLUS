// DocumentMarks.dll 18012faa0 DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar
// signature: undefined PDFPlusBearerBar(PDFPlusBearerBar * this, shared_ptr<ArtPaint::FormPaint_const_> param_1)

/* public: __cdecl DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar(class std::shared_ptr<class
   ArtPaint::FormPaint const >) __ptr64 */

PDFPlusBearerBar * __thiscall
DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar(PDFPlusBearerBar *this,undefined8 *param_2)

{
  int *piVar1;
  longlong *plVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
  *local_res18;
  variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
  *local_res20;
  undefined8 local_98;
  undefined8 uStack_90;
  variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
  local_88 [96];
  undefined1 local_28;
  char local_20;
  
                    /* 0x12faa0  222
                       ??0PDFPlusBearerBar@DocumentMarks@@QEAA@V?$shared_ptr@$$CBVFormPaint@ArtPaint@@@std@@@Z
                        */
  DynamicMark::DynamicMark((DynamicMark *)this,false,0x1ce);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this + 0x698) = 0;
  *(undefined8 *)(this + 0x6a0) = 0;
  *(undefined4 *)(this + 0x6a8) = 1;
  *(undefined4 *)(this + 0x6b0) = 3;
  this[0x728] = (PDFPlusBearerBar)0x0;
  *(undefined4 *)(this + 0x730) = 0;
  *(undefined8 *)(this + 0x738) = 0;
  *(undefined8 *)(this + 0x740) = 0;
  *(undefined8 *)(this + 0x748) = 0;
  FUN_180026ca0(this + 0x750,4);
  if (param_2[1] != 0) {
    LOCK();
    piVar1 = (int *)(param_2[1] + 8);
    *piVar1 = *piVar1 + 1;
    UNLOCK();
  }
  local_98 = *param_2;
  uStack_90 = param_2[1];
  DynamicMark::SetSourceContent((DynamicMark *)this,&local_98);
  DynamicObject::setColorType((DynamicObject *)this,5,0);
  lVar5 = FUN_180201680();
  local_res20 = local_88;
  local_28 = 0xff;
  local_res18 = local_88;
  FUN_1800919c0((longlong)*(char *)(lVar5 + 0x60) + 1,&local_res18);
  local_20 = '\0';
  DynamicObject::SetTargetSeparations((DynamicObject *)this,local_88,0);
  if ((local_20 != -1) && (local_20 == '\0')) {
    FUN_180022e80(local_88);
  }
  MarkPosition::setReferenceObject((MarkPosition *)(this + 0x2f0),0);
  MarkPosition::setAnchors((MarkPosition *)(this + 0x2f0),5,3);
  plVar4 = (longlong *)param_2[1];
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar2 = plVar4 + 1;
    lVar5 = *plVar2;
    *(int *)plVar2 = (int)*plVar2 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar1 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return this;
}


