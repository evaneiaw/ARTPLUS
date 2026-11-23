// DocumentMarks.dll 180127bf0 DocumentMarks::PDFPlusBarcodeMark::GetBoundingBoxSelf
// signature: RectangleBase<YAGL::MilliPointCoordinateSystem> GetBoundingBoxSelf(PDFPlusBarcodeMark * this, BoxKind param_1, TransformationBase<YAGL::MilliPointCoordinateSystem> * param_2)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: virtual class YAGL::RectangleBase<struct YAGL::MilliPointCoordinateSystem> __cdecl
   DocumentMarks::PDFPlusBarcodeMark::GetBoundingBoxSelf(enum ArtDoc::BoxKind,class
   YAGL::TransformationBase<struct YAGL::MilliPointCoordinateSystem> const & __ptr64)const __ptr64
    */

undefined8 __thiscall
DocumentMarks::PDFPlusBarcodeMark::GetBoundingBoxSelf
          (PDFPlusBarcodeMark *this,BoxKind param_1,
          TransformationBase<YAGL::MilliPointCoordinateSystem> *param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 in_register_00000014;
  
                    /* 0x127bf0  1112
                       ?GetBoundingBoxSelf@PDFPlusBarcodeMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1113
                       ?GetBoundingBoxSelf@PDFPlusBearerBar@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1114
                       ?GetBoundingBoxSelf@PDFPlusClipMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1115
                       ?GetBoundingBoxSelf@PDFPlusCutMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1116
                       ?GetBoundingBoxSelf@PDFPlusDimensionsMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1117
                       ?GetBoundingBoxSelf@PDFPlusExternalFileMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1118
                       ?GetBoundingBoxSelf@PDFPlusInputFileMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1119
                       ?GetBoundingBoxSelf@PDFPlusPlateIDMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1120
                       ?GetBoundingBoxSelf@PDFPlusPositionMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1121
                       ?GetBoundingBoxSelf@PDFPlusRepeatByCountMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1122
                       ?GetBoundingBoxSelf@PDFPlusRepeatForGridMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1123
                       ?GetBoundingBoxSelf@PDFPlusRepeatForSeparationsMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1124
                       ?GetBoundingBoxSelf@PDFPlusRepeatForStationsMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                       0x127bf0  1125
                       ?GetBoundingBoxSelf@PDFPlusResizeMark@DocumentMarks@@MEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@W4BoxKind@ArtDoc@@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@4@@Z
                        */
  uVar2 = (int)param_2 - 4;
  if (((uVar2 < 0x3d) && ((0x1000000000000111U >> ((ulonglong)uVar2 & 0x3f) & 1) != 0)) &&
     (cVar1 = FUN_18004c280(), cVar1 != '\0')) {
    DynamicObject::GetPDFPlusBoundingBox((DynamicObject *)this);
    return CONCAT44(in_register_00000014,param_1);
  }
  ArtDoc::Group::GetBoundingBoxSelf
            ((Group *)this,param_1,
             (TransformationBase<YAGL::MilliPointCoordinateSystem> *)
             ((ulonglong)param_2 & 0xffffffff));
  return CONCAT44(in_register_00000014,param_1);
}


