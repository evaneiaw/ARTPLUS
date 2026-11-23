// 180052340 CutMark

/* public: __cdecl DocumentMarks::CutMark::CutMark(bool) __ptr64 */

CutMark * __thiscall DocumentMarks::CutMark::CutMark(CutMark *this,bool param_1)

{
                    /* 0x52340  184  ??0CutMark@DocumentMarks@@QEAA@_N@Z */
  DynamicMark::DynamicMark((DynamicMark *)this,param_1,0xfd);
  *(undefined8 *)(this + 0x698) = 0;
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  return this;
}


