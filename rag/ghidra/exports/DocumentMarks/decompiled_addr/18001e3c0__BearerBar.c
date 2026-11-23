// DocumentMarks.dll 18001e3c0 DocumentMarks::BearerBar::BearerBar
// signature: undefined BearerBar(BearerBar * this, bool param_1)

/* public: __cdecl DocumentMarks::BearerBar::BearerBar(bool) __ptr64 */

BearerBar * __thiscall DocumentMarks::BearerBar::BearerBar(BearerBar *this,bool param_1)

{
                    /* 0x1e3c0  168  ??0BearerBar@DocumentMarks@@QEAA@_N@Z */
  DynamicMark::DynamicMark((DynamicMark *)this,param_1,0xfd);
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  *(undefined8 *)(this + 0x698) = 0x40cbae9d3a74e9d4;
  *(undefined8 *)(this + 0x6a0) = 0;
  *(undefined8 *)(this + 0x6a8) = 0;
  *(undefined4 *)(this + 0x6b0) = 3;
  return this;
}


