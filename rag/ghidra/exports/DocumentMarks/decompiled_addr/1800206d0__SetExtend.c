// DocumentMarks.dll 1800206d0 DocumentMarks::PDFPlusBearerBar::SetExtend
// signature: void SetExtend(PDFPlusBearerBar * this, CoordinateBase<YAGL::MilliPointCoordinateSystem,1> * param_1)

/* public: void __cdecl DocumentMarks::PDFPlusBearerBar::SetExtend(class YAGL::CoordinateBase<struct
   YAGL::MilliPointCoordinateSystem,1> const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusBearerBar::SetExtend
          (PDFPlusBearerBar *this,CoordinateBase<YAGL::MilliPointCoordinateSystem,1> *param_1)

{
                    /* 0x206d0  1544
                       ?SetExtend@PDFPlusBearerBar@DocumentMarks@@QEAAXAEBV?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@@Z
                       0x206d0  2228
                       ?setExtend@BearerBar@DocumentMarks@@QEAAXAEBV?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@@Z
                        */
  *(undefined8 *)(this + 0x6a0) = *(undefined8 *)param_1;
  return;
}


