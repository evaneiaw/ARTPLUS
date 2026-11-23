// DocumentMarks.dll 18001ea10 FUN_18001ea10
// signature: undefined FUN_18001ea10(void)

DynamicMark * FUN_18001ea10(DynamicMark *param_1,uint param_2)

{
  if ((param_2 & 2) == 0) {
    *(undefined ***)param_1 =
         DocumentMarks::BearerBar::_vftable__for__ArtDoc__Detail__ListItem<ArtDoc::ContentObject>__;
    *(undefined ***)(param_1 + 0x20) = DocumentMarks::BearerBar::_vftable__for__ArtDoc__Visitable__;
    DocumentMarks::DynamicMark::~DynamicMark(param_1);
    if ((param_2 & 1) != 0) {
      free(param_1);
    }
    return param_1;
  }
  _eh_vector_destructor_iterator_
            (param_1,0x6b8,*(__uint64 *)(param_1 + -8),DocumentMarks::BearerBar::~BearerBar);
  if ((param_2 & 1) != 0) {
    free(param_1 + -8);
  }
  return param_1 + -8;
}


