// 180052820 PlaceCutMarkSymbol

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* private: void __cdecl DocumentMarks::CutMark::PlaceCutMarkSymbol(class ArtDoc::ContentObject &
   __ptr64,struct dm::CPoint const & __ptr64,struct dm::CPoint const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::CutMark::PlaceCutMarkSymbol
          (CutMark *this,ContentObject *param_1,CPoint *param_2,CPoint *param_3)

{
  undefined1 auVar1 [12];
  double dVar2;
  double dVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  double local_e8;
  double local_e0;
  double local_d8;
  double local_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  double local_b8;
  double dStack_b0;
  undefined1 local_a8 [16];
  char local_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  double local_68;
  double local_60;
  undefined1 local_38;
  
                    /* 0x52820  1417
                       ?PlaceCutMarkSymbol@CutMark@DocumentMarks@@AEAAXAEAVContentObject@ArtDoc@@AEBUCPoint@dm@@1@Z
                        */
  auVar4._0_8_ = *(double *)param_3 * 360000.0;
  auVar4._8_8_ = *(double *)(param_3 + 8) * 360000.0;
  auVar4 = divpd(auVar4,_DAT_1803082e0);
  auVar5 = auVar4 >> 0x40;
  dVar2 = atan2(auVar4._8_8_ - (*(double *)(param_2 + 8) * 360000.0) / 127.0,
                auVar4._0_8_ - (*(double *)param_2 * 360000.0) / 127.0);
  dVar2 = dVar2 + _DAT_180488498;
  dVar3 = cos(dVar2);
  local_e0 = sin(dVar2);
  local_d8 = -local_e0;
  local_c8 = 0;
  uStack_c0 = 0;
  local_e8 = dVar3;
  local_d0 = dVar3;
  DocumentEdit::Transform
            ((Transformable *)param_1,
             (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_e8,7);
  GetBoundingBoxForPositioning((ContentObject *)&local_b8);
  if (local_90 == '\0') {
    local_b8 = 0.0;
    dStack_b0 = 0.0;
    local_38 = 1;
    local_a8 = ZEXT816(0);
  }
  dVar2 = *(double *)param_2;
  auVar1._4_8_ = auVar5._8_8_;
  auVar1._0_4_ = local_a8._4_4_;
  auVar5._0_8_ = auVar1._0_8_ << 0x20;
  auVar5._8_4_ = local_a8._8_4_;
  auVar5._12_4_ = local_a8._12_4_;
  dVar3 = auVar5._8_8_;
  if (dVar2 == *(double *)param_3) {
    local_68 = local_a8._0_8_ * 0.5;
    local_60 = 0.0;
    if (*(double *)(param_2 + 8) <= *(double *)(param_3 + 8) &&
        *(double *)(param_3 + 8) != *(double *)(param_2 + 8)) {
      local_60 = dVar3;
    }
  }
  else {
    local_60 = dVar3 * 0.5;
    local_68 = 0.0;
    if (*(double *)param_3 < dVar2) {
      local_68 = local_a8._0_8_;
    }
  }
  local_88 = 0x3ff0000000000000;
  uStack_80 = 0;
  local_78 = 0;
  uStack_70 = 0x3ff0000000000000;
  local_68 = (dVar2 * 2834.645669291339 - local_b8) - local_68;
  local_60 = (*(double *)(param_2 + 8) * 2834.645669291339 - (dVar3 + dStack_b0)) + local_60;
  DocumentEdit::Transform
            ((Transformable *)param_1,
             (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_88,7);
  return;
}


