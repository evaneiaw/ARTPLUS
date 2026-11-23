// DocumentMarks.dll 18001edf0 FUN_18001edf0
// signature: undefined FUN_18001edf0(void)

RectangleBase<YAGL::MilliPointCoordinateSystem> *
FUN_18001edf0(RectangleBase<YAGL::MilliPointCoordinateSystem> *param_1,double *param_2,int param_3,
             double *param_4,double *param_5,double *param_6)

{
  double *pdVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  char cVar6;
  double dVar7;
  double *pdVar8;
  double *pdVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  double dVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  double dVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined1 local_98 [8];
  undefined8 uStack_90;
  double local_88;
  double dStack_80;
  undefined1 local_78 [8];
  double adStack_70 [2];
  double local_60;
  double dStack_58;
  double local_50;
  double dStack_48;
  double local_40;
  double dStack_38;
  undefined1 local_30;
  
  uVar13 = 0;
  uVar14 = 0;
  _local_78 = ZEXT816(0);
  uVar16 = 0;
  uVar17 = 0;
  _local_98 = ZEXT816(0);
  dVar15 = 0.0;
  dVar12 = 0.0;
  if (param_3 == 0) {
    local_88 = *param_2;
    dVar15 = local_88 - *param_4;
    dVar12 = *param_6;
    uVar13 = SUB84(dVar12,0);
    uVar14 = (undefined4)((ulonglong)dVar12 >> 0x20);
    dVar7 = param_2[1] - *param_5;
    auVar5._8_8_ = 0;
    auVar5._0_8_ = param_2[1] + param_2[3] + *param_5;
    _local_98 = auVar5 << 0x40;
    dVar12 = local_88 - dVar12;
LAB_18001f020:
    dVar15 = dVar15 - (double)CONCAT44(uVar14,uVar13);
  }
  else {
    if (param_3 != 1) {
      if (param_3 == 2) {
        dVar15 = *param_2;
        dVar12 = *param_5;
        uVar13 = SUB84(dVar12,0);
        uVar14 = (undefined4)((ulonglong)dVar12 >> 0x20);
        auVar3._8_8_ = 0;
        auVar3._0_8_ = param_2[1] + param_2[3] + *param_4 + *param_6;
        _local_98 = auVar3 << 0x40;
        dVar7 = param_2[1] + param_2[3] + *param_6;
        local_88 = dVar7;
        dVar12 = dVar15 + param_2[2] + dVar12;
      }
      else {
        uVar10 = 0;
        uVar11 = 0;
        if (param_3 != 3) goto LAB_18001f054;
        dVar15 = *param_2;
        dVar12 = *param_5;
        uVar13 = SUB84(dVar12,0);
        uVar14 = (undefined4)((ulonglong)dVar12 >> 0x20);
        auVar2._8_8_ = 0;
        auVar2._0_8_ = param_2[1] - *param_6;
        _local_98 = auVar2 << 0x40;
        dVar7 = (param_2[1] - *param_4) - *param_6;
        local_88 = dVar7;
        dVar12 = dVar15 + param_2[2] + dVar12;
      }
      goto LAB_18001f020;
    }
    local_88 = *param_2;
    dVar15 = local_88 + param_2[2] + *param_6;
    dVar7 = param_2[1] - *param_5;
    auVar4._8_8_ = 0;
    auVar4._0_8_ = param_2[1] + param_2[3] + *param_5;
    _local_98 = auVar4 << 0x40;
    dVar12 = local_88 + param_2[2] + *param_4 + *param_6;
  }
  uVar13 = (undefined4)uStack_90;
  uVar14 = uStack_90._4_4_;
  uVar16 = SUB84(dVar15,0);
  uVar17 = (undefined4)((ulonglong)dVar15 >> 0x20);
  uStack_90._0_4_ = SUB84(dVar7,0);
  uStack_90._4_4_ = (undefined4)((ulonglong)dVar7 >> 0x20);
  unique0x100004e5 = uVar13;
  local_78 = dVar15;
  unique0x100004e9 = uVar14;
  local_98 = dVar12;
  uVar10 = (undefined4)uStack_90;
  uVar11 = uStack_90._4_4_;
LAB_18001f054:
  local_30 = 0;
  if (dVar15 <= dVar12) {
    if (dVar12 < (double)CONCAT44(uVar17,uVar16) || dVar12 == (double)CONCAT44(uVar17,uVar16)) {
      if (dVar12 == dVar15) {
        cVar6 = '\0';
      }
      else {
        cVar6 = -0x80;
      }
    }
    else {
      cVar6 = '\x01';
    }
  }
  else {
    cVar6 = -1;
  }
  pdVar9 = (double *)local_98;
  pdVar1 = (double *)local_78;
  if (cVar6 == -1) {
    pdVar9 = (double *)local_78;
    pdVar1 = (double *)local_98;
  }
  if ((double)CONCAT44(uVar14,uVar13) < (double)CONCAT44(uVar11,uVar10) ||
      (double)CONCAT44(uVar14,uVar13) == (double)CONCAT44(uVar11,uVar10)) {
    if ((double)CONCAT44(uVar11,uVar10) < (double)CONCAT44(uVar14,uVar13) ||
        (double)CONCAT44(uVar11,uVar10) == (double)CONCAT44(uVar14,uVar13)) {
      if ((double)CONCAT44(uVar11,uVar10) == (double)CONCAT44(uVar14,uVar13)) {
        cVar6 = '\0';
      }
      else {
        cVar6 = -0x80;
      }
    }
    else {
      cVar6 = '\x01';
    }
  }
  else {
    cVar6 = -1;
  }
  pdVar8 = adStack_70;
  if (cVar6 == -1) {
    pdVar8 = (double *)&uStack_90;
  }
  local_50 = *pdVar1;
  local_88 = local_50;
  dStack_48 = *pdVar8;
  dStack_80 = dStack_48;
  local_60 = *pdVar9 - *pdVar1;
  local_88 = adStack_70[0];
  if (cVar6 != -1) {
    local_88 = uStack_90;
  }
  local_88 = local_88 - *pdVar8;
  dStack_58 = local_88;
  local_40 = local_60;
  dStack_38 = local_88;
  YAGL::GetRectangleCompound(param_1);
  return param_1;
}


