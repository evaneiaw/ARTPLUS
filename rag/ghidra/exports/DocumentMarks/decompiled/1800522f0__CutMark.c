// 1800522f0 CutMark

/* protected: __cdecl DocumentMarks::CutMark::CutMark(class DocumentMarks::CutMark const &
   __ptr64,class ArtDoc::CloneStrategy & __ptr64) __ptr64 */

CutMark * __thiscall
DocumentMarks::CutMark::CutMark(CutMark *this,CutMark *param_1,CloneStrategy *param_2)

{
                    /* 0x522f0  183
                       ??0CutMark@DocumentMarks@@IEAA@AEBV01@AEAVCloneStrategy@ArtDoc@@@Z */
  DynamicMark::DynamicMark((DynamicMark *)this,(DynamicMark *)param_1,param_2);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this + 0x698) = *(undefined8 *)(param_1 + 0x698);
  return this;
}


