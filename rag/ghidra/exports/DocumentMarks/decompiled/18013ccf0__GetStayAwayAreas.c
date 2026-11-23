// 18013ccf0 GetStayAwayAreas

/* public: virtual class std::vector<class YAGL::RectangleBase<struct
   YAGL::MilliPointCoordinateSystem>,class std::allocator<class YAGL::RectangleBase<struct
   YAGL::MilliPointCoordinateSystem> > > __cdecl
   DocumentMarks::PDFPlusCutMark::GetStayAwayAreas(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::GetStayAwayAreas(PDFPlusCutMark *this)

{
  ContentObject *this_00;
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  undefined8 *in_RDX;
  undefined8 in_R9;
  undefined4 extraout_XMM0_Da;
  undefined4 uVar4;
  undefined1 local_30 [40];
  
                    /* 0x13ccf0  1302
                       ?GetStayAwayAreas@PDFPlusCutMark@DocumentMarks@@UEBA?AV?$vector@V?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@V?$allocator@V?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@@std@@@std@@XZ
                       0x13ccf0  1306
                       ?GetStayAwayAreas@PDFPlusRepeatForGridMark@DocumentMarks@@MEBA?AV?$vector@V?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@V?$allocator@V?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@@std@@@std@@XZ
                        */
  *in_RDX = 0;
  in_RDX[1] = 0;
  in_RDX[2] = 0;
  uVar4 = 1;
  for (this_00 = *(ContentObject **)(this + 0x2c0); this_00 != (ContentObject *)0x0;
      this_00 = *(ContentObject **)(this_00 + 8)) {
    puVar3 = (undefined8 *)ArtDoc::ContentObject::GetBoundingBox(this_00,(BoxKind)local_30);
    puVar1 = (undefined8 *)in_RDX[1];
    if (puVar1 == (undefined8 *)in_RDX[2]) {
      FUN_1800552a0(extraout_XMM0_Da,puVar1,puVar3,in_R9,uVar4);
    }
    else {
      uVar2 = puVar3[1];
      *puVar1 = *puVar3;
      puVar1[1] = uVar2;
      uVar2 = puVar3[3];
      puVar1[2] = puVar3[2];
      puVar1[3] = uVar2;
      puVar1[4] = puVar3[4];
      in_RDX[1] = in_RDX[1] + 0x28;
    }
  }
  return;
}


