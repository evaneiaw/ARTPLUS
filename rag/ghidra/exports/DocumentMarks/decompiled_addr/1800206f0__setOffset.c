// DocumentMarks.dll 1800206f0 DocumentMarks::BearerBar::setOffset
// signature: void setOffset(BearerBar * this, CoordinateBase<YAGL::MilliPointCoordinateSystem,1> * param_1)

/* public: void __cdecl DocumentMarks::BearerBar::setOffset(class YAGL::CoordinateBase<struct
   YAGL::MilliPointCoordinateSystem,1> const & __ptr64) __ptr64 */

void __thiscall
DocumentMarks::BearerBar::setOffset
          (BearerBar *this,CoordinateBase<YAGL::MilliPointCoordinateSystem,1> *param_1)

{
                    /* 0x206f0  2235
                       ?setOffset@BearerBar@DocumentMarks@@QEAAXAEBV?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@@Z
                        */
  *(undefined8 *)(this + 0x6a8) = *(undefined8 *)param_1;
  return;
}


