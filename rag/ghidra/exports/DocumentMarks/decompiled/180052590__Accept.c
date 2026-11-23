// 180052590 Accept

/* public: virtual void __cdecl DocumentMarks::CutMark::Accept(class ArtDoc::VisitorBase & __ptr64)
   __ptr64 */

void __thiscall DocumentMarks::CutMark::Accept(CutMark *this,VisitorBase *param_1)

{
  char cVar1;
  longlong *plVar2;
  undefined1 local_res8 [8];
  
                    /* 0x52590  758  ?Accept@CutMark@DocumentMarks@@UEAAXAEAVVisitorBase@ArtDoc@@@Z
                        */
  plVar2 = (longlong *)
           __RTDynamicCast(param_1,0,&ArtDoc::VisitorBase::RTTI_Type_Descriptor,
                           &ArtDoc::Visitor<DocumentMarks::CutMark>::RTTI_Type_Descriptor,0);
  if (plVar2 == (longlong *)0x0) {
    plVar2 = (longlong *)
             __RTDynamicCast(param_1,0,&ArtDoc::VisitorBase::RTTI_Type_Descriptor,
                             &ArtDoc::Visitor<DocumentMarks::DynamicMark>::RTTI_Type_Descriptor,0);
    if (plVar2 == (longlong *)0x0) {
      cVar1 = FUN_180015e10(local_res8,this + -0x20,param_1);
      if (cVar1 == '\0') {
        (**(code **)(*(longlong *)this + 0x20))(this,param_1);
      }
    }
    else {
      cVar1 = (**(code **)*plVar2)(plVar2);
      if (cVar1 != '\0') {
        (**(code **)(*(longlong *)this + 0x20))(this,param_1);
      }
      (**(code **)(*plVar2 + 8))(plVar2,this + -0x20);
    }
  }
  else {
    cVar1 = (**(code **)*plVar2)(plVar2,this + -0x20);
    if (cVar1 != '\0') {
      (**(code **)(*(longlong *)this + 0x20))(this,param_1);
    }
    (**(code **)(*plVar2 + 8))(plVar2,this + -0x20);
  }
  return;
}


