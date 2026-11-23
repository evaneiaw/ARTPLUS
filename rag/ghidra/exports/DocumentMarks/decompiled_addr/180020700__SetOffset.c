// DocumentMarks.dll 180020700 DocumentMarks::PDFPlusBearerBar::SetOffset
// signature: void SetOffset(PDFPlusBearerBar * this, CoordinateBase<YAGL::MilliPointCoordinateSystem,1> * param_1)

/* public: void __cdecl DocumentMarks::PDFPlusBearerBar::SetOffset(class YAGL::CoordinateBase<struct
   YAGL::MilliPointCoordinateSystem,1> const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusBearerBar::SetOffset
          (PDFPlusBearerBar *this,CoordinateBase<YAGL::MilliPointCoordinateSystem,1> *param_1)

{
                    /* 0x20700  1574
                       ?SetOffset@PDFPlusBearerBar@DocumentMarks@@QEAAXAEBV?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@@Z
                       0x20700  2253
                       ?setWidth@BearerBar@DocumentMarks@@QEAAXAEBV?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@@Z
                        */
  *(undefined8 *)(this + 0x698) = *(undefined8 *)param_1;
  return;
}


