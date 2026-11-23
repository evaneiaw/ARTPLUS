// DocumentMarks.dll 18001e350 DocumentMarks::BearerBar::BearerBar
// signature: undefined BearerBar(BearerBar * this, BearerBar * param_1, CloneStrategy * param_2)

/* protected: __cdecl DocumentMarks::BearerBar::BearerBar(class DocumentMarks::BearerBar const &
   __ptr64,class ArtDoc::CloneStrategy & __ptr64) __ptr64 */

BearerBar * __thiscall
DocumentMarks::BearerBar::BearerBar(BearerBar *this,BearerBar *param_1,CloneStrategy *param_2)

{
                    /* 0x1e350  167
                       ??0BearerBar@DocumentMarks@@IEAA@AEBV01@AEAVCloneStrategy@ArtDoc@@@Z */
  DynamicMark::DynamicMark((DynamicMark *)this,(DynamicMark *)param_1,param_2);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this + 0x698) = *(undefined8 *)(param_1 + 0x698);
  *(undefined8 *)(this + 0x6a0) = *(undefined8 *)(param_1 + 0x6a0);
  *(undefined8 *)(this + 0x6a8) = *(undefined8 *)(param_1 + 0x6a8);
  *(undefined4 *)(this + 0x6b0) = *(undefined4 *)(param_1 + 0x6b0);
  return this;
}


