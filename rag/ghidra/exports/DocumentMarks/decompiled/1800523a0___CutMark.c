// 1800523a0 ~CutMark

/* public: virtual __cdecl DocumentMarks::CutMark::~CutMark(void) __ptr64 */

void __thiscall DocumentMarks::CutMark::~CutMark(CutMark *this)

{
                    /* 0x523a0  396  ??1CutMark@DocumentMarks@@UEAA@XZ */
  *(undefined ***)this = _vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
  *(undefined ***)(this + 0x20) = _vftable__for__ArtDoc__Visitable__;
  DynamicMark::~DynamicMark((DynamicMark *)this);
  return;
}


