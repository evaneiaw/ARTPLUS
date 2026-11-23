// 180052790 Clone

/* public: virtual class DocumentMarks::CutMark * __ptr64 __cdecl
   DocumentMarks::CutMark::Clone(class ArtDoc::CloneStrategy & __ptr64)const __ptr64 */

CutMark * __thiscall DocumentMarks::CutMark::Clone(CutMark *this,CloneStrategy *param_1)

{
  DynamicMark *this_00;
  
                    /* 0x52790  865
                       ?Clone@CutMark@DocumentMarks@@UEBAPEAV12@AEAVCloneStrategy@ArtDoc@@@Z */
  this_00 = (DynamicMark *)FUN_1802d6b50(0x6a0);
  if (this_00 == (DynamicMark *)0x0) {
    return (CutMark *)0x0;
  }
  DynamicMark::DynamicMark(this_00,(DynamicMark *)this,param_1);
  *(undefined ***)this_00 = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this_00 + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this_00 + 0x698) = *(undefined8 *)(this + 0x698);
  return (CutMark *)this_00;
}


