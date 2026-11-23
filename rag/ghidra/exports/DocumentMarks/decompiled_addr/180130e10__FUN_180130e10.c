// DocumentMarks.dll 180130e10 FUN_180130e10
// signature: undefined FUN_180130e10(void)

undefined8 *
FUN_180130e10(undefined8 *param_1,Content *param_2,int param_3,PageBox *param_4,longlong *param_5,
             int param_6)

{
  double *pdVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined1 auVar9 [12];
  undefined8 uVar10;
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  double dVar14;
  bool bVar15;
  bool bVar16;
  bool bVar17;
  bool bVar18;
  double *pdVar19;
  double *pdVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  char cVar24;
  ContentObject *pCVar25;
  longlong *plVar26;
  Page *this;
  RectangleBase<YAGL::MilliPointCoordinateSystem> *pRVar27;
  int iVar28;
  double *pdVar29;
  double dVar30;
  double dVar31;
  undefined1 auVar32 [16];
  double dVar33;
  uint uVar34;
  uint uVar35;
  undefined4 uVar36;
  undefined4 uVar37;
  undefined4 uVar38;
  undefined4 uVar39;
  undefined4 uVar40;
  undefined4 uVar41;
  undefined4 uVar42;
  undefined4 uVar43;
  undefined4 uVar44;
  undefined4 uVar45;
  undefined4 uVar46;
  undefined4 uVar47;
  undefined4 uVar48;
  undefined4 uVar49;
  undefined4 uVar50;
  undefined4 uVar51;
  undefined4 uVar52;
  undefined4 uVar53;
  undefined4 uVar54;
  undefined4 uVar55;
  undefined4 uVar56;
  undefined4 uVar57;
  undefined4 uVar58;
  undefined4 uVar59;
  undefined4 uVar60;
  undefined4 uVar61;
  undefined4 uVar62;
  undefined4 uVar63;
  undefined4 uVar64;
  undefined4 uVar65;
  double local_300;
  double local_2f8;
  double *local_2f0;
  undefined8 local_2e8;
  double *local_2e0;
  double local_2d8;
  double *local_2d0;
  double *local_2c8;
  double *local_2c0;
  double local_2b8;
  double *local_2b0;
  double *pdStack_2a8;
  undefined4 local_2a0;
  undefined4 uStack_29c;
  undefined4 uStack_298;
  undefined4 uStack_294;
  undefined4 local_290;
  undefined4 uStack_28c;
  double dStack_288;
  double *local_280;
  double *local_278;
  double *local_270;
  double *local_268;
  double *local_260;
  double *local_258;
  double local_250;
  double *local_248;
  double *local_240;
  undefined1 auStack_238 [12];
  undefined4 uStack_22c;
  undefined1 auStack_228 [12];
  undefined4 uStack_21c;
  double local_218;
  double *local_208;
  undefined1 auStack_200 [12];
  undefined4 uStack_1f4;
  undefined1 local_1f0 [16];
  undefined4 local_1e0;
  undefined4 uStack_1dc;
  int local_1c8;
  int local_1c4;
  double local_190;
  double local_188;
  int local_180;
  double local_178;
  int local_170;
  char local_16c;
  double *local_148;
  undefined1 auStack_140 [12];
  undefined4 uStack_134;
  undefined1 auStack_130 [16];
  double dStack_120;
  double *local_110;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  double dStack_f8;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  
  if (param_3 == 0) {
    FUN_180130d20(param_1,param_2,param_4);
    return param_1;
  }
  bVar16 = false;
  local_2f0 = (double *)param_5[1];
  pdVar29 = (double *)*param_5;
  if (pdVar29 != local_2f0) {
    local_270 = (double *)auStack_140._0_8_;
    bVar17 = false;
    bVar15 = false;
    bVar18 = false;
    uVar50 = auStack_228._0_4_;
    uVar51 = auStack_228._4_4_;
    local_278 = (double *)auStack_238._0_8_;
    local_260 = stack0xfffffffffffffe08;
    local_268 = (double *)CONCAT44(uStack_fc,uStack_100);
    uVar38 = local_1f0._8_4_;
    uVar39 = local_1f0._12_4_;
    local_2d0 = local_148;
    local_258 = local_240;
    local_2f8 = dStack_120;
    local_300 = local_218;
    local_250 = (double)CONCAT44(uStack_1dc,local_1e0);
    local_280 = local_110;
    local_2c8 = local_208;
    uVar36 = local_1f0._0_4_;
    uVar37 = local_1f0._4_4_;
    uVar40 = uStack_108;
    uVar41 = uStack_104;
    uVar42 = uStack_100;
    uVar43 = uStack_fc;
    uVar44 = auStack_140._0_4_;
    uVar45 = auStack_140._4_4_;
    uVar46 = auStack_140._8_4_;
    uVar47 = uStack_134;
    uVar48 = uVar38;
    uVar49 = uVar39;
    uVar52 = auStack_228._8_4_;
    uVar53 = uStack_21c;
    uVar54 = auStack_238._0_4_;
    uVar55 = auStack_238._4_4_;
    uVar56 = auStack_238._8_4_;
    uVar57 = uStack_22c;
    uVar58 = auStack_200._0_4_;
    uVar59 = auStack_200._4_4_;
    uVar60 = auStack_200._8_4_;
    uVar61 = uStack_1f4;
    uVar62 = uVar50;
    uVar63 = uVar51;
    uVar64 = uStack_e8;
    uVar65 = uStack_e4;
    do {
      pdVar1 = (double *)*pdVar29;
      ArtDoc::Content::GetObjectWithID(param_2,(__uint64)pdVar1);
      DocumentMarks::GetPDFPlusBoundingBox((Visitable *)&local_2b0);
      uVar23 = uStack_28c;
      uVar22 = local_290;
      uVar21 = uStack_294;
      uVar6 = uStack_298;
      uVar4 = uStack_29c;
      uVar2 = local_2a0;
      pdVar20 = pdStack_2a8;
      pdVar19 = local_2b0;
      if (dStack_288._0_1_ == '\0') goto LAB_18013133c;
      dVar14 = (double)CONCAT44(uStack_28c,local_290);
      dVar33 = (double)CONCAT44(uStack_29c,local_2a0);
      auVar12._8_4_ = uStack_298;
      auVar12._0_8_ = dVar33;
      auVar12._12_4_ = uStack_294;
      auVar11._8_8_ = pdStack_2a8;
      auVar11._0_8_ = local_2b0;
      uVar3 = SUB84(local_2b0,0);
      uVar5 = (undefined4)((ulonglong)local_2b0 >> 0x20);
      uVar7 = SUB84(pdStack_2a8,0);
      uVar8 = (undefined4)((ulonglong)pdStack_2a8 >> 0x20);
      if (bVar15) {
        local_2e0 = local_270;
        local_2c0 = local_2b0;
        if ((double)local_2b0 < (double)local_270) goto LAB_180131019;
        if ((double)local_2b0 <= (double)local_270) {
          if ((double)local_2b0 == (double)local_270) {
            cVar24 = '\0';
          }
          else {
            cVar24 = -0x80;
          }
          if (cVar24 == -1) goto LAB_180131019;
        }
      }
      else {
LAB_180131019:
        pdStack_2a8 = local_2b0;
        uStack_28c = uStack_294;
        uVar44 = uVar3;
        uVar45 = uVar5;
        uVar46 = uVar7;
        uVar47 = uVar8;
        local_2f8 = dVar14;
        local_2d0 = pdVar1;
        if (bVar15) {
          local_270 = local_2b0;
          local_2b0 = pdVar1;
          local_2a0 = uVar7;
          uStack_29c = uVar8;
          uStack_298 = uVar2;
          uStack_294 = uVar4;
          local_290 = uVar6;
          dStack_288 = dVar14;
          _auStack_140 = auVar11;
          auStack_130 = auVar12;
        }
        else {
          bVar15 = true;
          auStack_130._12_4_ = uStack_294;
          auStack_130._8_4_ = uStack_298;
          auStack_130._0_8_ = dVar33;
          stack0xfffffffffffffec8 = (double)pdVar20;
          auStack_140._0_8_ = local_2b0;
          local_270 = local_2b0;
          local_2b0 = pdVar1;
          local_2a0 = uVar7;
          uStack_29c = uVar8;
          uStack_298 = uVar2;
          uStack_294 = uVar4;
          local_290 = uVar6;
          dStack_288 = dVar14;
          local_148 = pdVar1;
          dStack_120 = dVar14;
        }
      }
      if (bVar17) {
        dVar30 = dVar33 + (double)pdVar19;
        local_2e0 = (double *)((double)CONCAT44(uVar63,uVar62) + (double)local_278);
        if ((double)local_2e0 <= dVar30) {
          if (dVar30 <= (double)local_2e0) {
            if (dVar30 == (double)local_2e0) {
              cVar24 = '\0';
            }
            else {
              cVar24 = -0x80;
            }
            if (cVar24 < '\x01') goto LAB_18013117b;
          }
          goto LAB_1801310f6;
        }
      }
      else {
LAB_1801310f6:
        pdStack_2a8 = pdVar19;
        uStack_28c = uVar21;
        uVar50 = uVar2;
        uVar51 = uVar4;
        uVar52 = uVar6;
        uVar53 = uVar21;
        uVar54 = uVar3;
        uVar55 = uVar5;
        uVar56 = uVar7;
        uVar57 = uVar8;
        uVar62 = uVar2;
        uVar63 = uVar4;
        local_300 = dVar14;
        local_258 = pdVar1;
        if (bVar17) {
          local_278 = pdVar19;
          local_2b0 = pdVar1;
          local_2a0 = uVar7;
          uStack_29c = uVar8;
          uStack_298 = uVar2;
          uStack_294 = uVar4;
          local_290 = uVar6;
          dStack_288 = dVar14;
          _auStack_238 = auVar11;
          _auStack_228 = auVar12;
        }
        else {
          bVar17 = true;
          uStack_21c = uVar21;
          auStack_228._8_4_ = uVar6;
          auStack_238._8_4_ = uVar7;
          uStack_22c = uVar8;
          auStack_228._0_8_ = dVar33;
          auStack_238._0_8_ = pdVar19;
          local_278 = pdVar19;
          local_2b0 = pdVar1;
          local_2a0 = uVar7;
          uStack_29c = uVar8;
          uStack_298 = uVar2;
          uStack_294 = uVar4;
          local_290 = uVar6;
          dStack_288 = dVar14;
          local_240 = pdVar1;
          local_218 = dVar14;
        }
      }
LAB_18013117b:
      dVar30 = 0.0;
      if (bVar18) {
        dVar30 = auVar12._8_8_;
        dVar31 = dVar30 + (double)pdVar20;
        local_2e0 = (double *)((double)CONCAT44(uVar49,uVar48) + (double)local_260);
        if ((double)local_2e0 <= dVar31) {
          if (dVar31 <= (double)local_2e0) {
            if (dVar31 == (double)local_2e0) {
              cVar24 = '\0';
            }
            else {
              cVar24 = -0x80;
            }
            if (cVar24 < '\x01') goto LAB_18013126c;
          }
          goto LAB_1801311e5;
        }
      }
      else {
LAB_1801311e5:
        pdStack_2a8 = pdVar19;
        uStack_28c = uVar21;
        uVar36 = uVar2;
        uVar37 = uVar4;
        uVar38 = uVar6;
        uVar39 = uVar21;
        uVar48 = uVar6;
        uVar49 = uVar21;
        uVar58 = uVar3;
        uVar59 = uVar5;
        uVar60 = uVar7;
        uVar61 = uVar8;
        local_2c8 = pdVar1;
        if (bVar18) {
          local_260 = pdVar20;
          local_2b0 = pdVar1;
          local_2a0 = uVar7;
          uStack_29c = uVar8;
          uStack_298 = uVar2;
          uStack_294 = uVar4;
          local_290 = uVar6;
          dStack_288 = dVar14;
          local_250 = dVar14;
          _auStack_200 = auVar11;
          local_1f0 = auVar12;
        }
        else {
          bVar18 = true;
          auVar9._4_8_ = dVar30;
          auVar9._0_4_ = uVar21;
          auVar32._0_8_ = auVar9._0_8_ << 0x20;
          auVar32._8_4_ = uVar22;
          auVar32._12_4_ = uVar23;
          local_250 = auVar32._8_8_;
          stack0xfffffffffffffe08 = pdVar20;
          auStack_200._0_8_ = pdVar19;
          local_1f0._8_4_ = uVar6;
          local_1f0._0_8_ = dVar33;
          local_1f0._12_4_ = uVar21;
          local_1e0 = uVar22;
          uStack_1dc = uVar23;
          local_260 = pdVar20;
          local_2b0 = pdVar1;
          local_2a0 = uVar7;
          uStack_29c = uVar8;
          uStack_298 = uVar2;
          uStack_294 = uVar4;
          local_290 = uVar6;
          dStack_288 = dVar14;
          local_208 = pdVar1;
        }
      }
LAB_18013126c:
      if (bVar16) {
        local_2c0 = local_268;
        local_2e0 = pdVar20;
        if ((double)pdVar20 < (double)local_268) goto LAB_1801312b1;
        if ((double)pdVar20 <= (double)local_268) {
          if ((double)pdVar20 == (double)local_268) {
            cVar24 = '\0';
          }
          else {
            cVar24 = -0x80;
          }
          if (cVar24 == -1) goto LAB_1801312b1;
        }
      }
      else {
LAB_1801312b1:
        pdStack_2a8 = pdVar19;
        uStack_28c = uVar21;
        uVar40 = uVar3;
        uVar41 = uVar5;
        uVar42 = uVar7;
        uVar43 = uVar8;
        uVar64 = uVar22;
        uVar65 = uVar23;
        local_280 = pdVar1;
        uStack_108 = uVar3;
        uStack_104 = uVar5;
        uStack_100 = uVar7;
        uStack_fc = uVar8;
        if (bVar16) {
          local_268 = pdVar20;
          uStack_ec = uVar21;
          local_2b0 = pdVar1;
          local_2a0 = uVar7;
          uStack_29c = uVar8;
          uStack_298 = uVar2;
          uStack_294 = uVar4;
          local_290 = uVar6;
          dStack_288 = dVar14;
          dStack_f8 = dVar33;
          uStack_f0 = uVar6;
        }
        else {
          bVar16 = true;
          auVar13._8_4_ = uVar2;
          auVar13._0_8_ = pdVar20;
          auVar13._12_4_ = uVar4;
          local_268 = pdVar20;
          uStack_f0 = uVar6;
          uStack_ec = uVar21;
          uStack_e8 = uVar22;
          uStack_e4 = uVar23;
          dStack_f8 = auVar13._8_8_;
          local_2b0 = pdVar1;
          local_2a0 = uVar7;
          uStack_29c = uVar8;
          uStack_298 = uVar2;
          uStack_294 = uVar4;
          local_290 = uVar6;
          dStack_288 = dVar14;
          local_110 = pdVar1;
        }
      }
LAB_18013133c:
      pdVar29 = pdVar29 + 1;
    } while (pdVar29 != local_2f0);
    if ((((bVar15) && (bVar17)) && (bVar18)) && (bVar16)) {
      if (param_6 == 0) {
        if (param_3 == 5) {
LAB_18013196b:
          *(undefined4 *)param_1 = uVar58;
          *(undefined4 *)((longlong)param_1 + 4) = uVar59;
          *(undefined4 *)(param_1 + 1) = uVar60;
          *(undefined4 *)((longlong)param_1 + 0xc) = uVar61;
          *(undefined4 *)(param_1 + 2) = uVar36;
          *(undefined4 *)((longlong)param_1 + 0x14) = uVar37;
          *(undefined4 *)(param_1 + 3) = uVar38;
          *(undefined4 *)((longlong)param_1 + 0x1c) = uVar39;
          param_1[4] = local_250;
          return param_1;
        }
        if (param_3 == 6) {
LAB_180131951:
          *(undefined4 *)param_1 = uVar40;
          *(undefined4 *)((longlong)param_1 + 4) = uVar41;
          *(undefined4 *)(param_1 + 1) = uVar42;
          *(undefined4 *)((longlong)param_1 + 0xc) = uVar43;
          param_1[2] = dStack_f8;
          param_1[3] = CONCAT44(uStack_ec,uStack_f0);
          param_1[4] = CONCAT44(uVar65,uVar64);
          return param_1;
        }
        if (param_3 == 7) {
          pCVar25 = ArtDoc::Content::GetObjectWithID(param_2,(__uint64)local_2c8);
          iVar28 = 0;
          plVar26 = (longlong *)
                    __RTDynamicCast(pCVar25,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                                    &DocumentMarks::GridInterface::RTTI_Type_Descriptor,0);
          (**(code **)(*plVar26 + 8))(plVar26,&local_1c8);
          if ((local_180 != 1) || (local_16c != '\0')) goto LAB_18013196b;
          if (local_178 < 0.0) {
            iVar28 = local_170;
            if (local_1c8 < local_170) {
              iVar28 = local_1c8;
            }
            iVar28 = iVar28 + -1;
          }
          if (local_1c8 < local_170) {
            local_170 = local_1c8;
          }
          dVar33 = (local_188 * DAT_180305520) / DAT_180305518;
          local_2c8 = (double *)
                      ((double)auStack_200._0_8_ -
                      ((double)iVar28 * local_178 * DAT_180305520) / DAT_180305518);
          local_2b8 = (double)local_260 + (double)CONCAT44(uVar49,uVar48);
          local_2f0 = (double *)
                      ((double)local_1f0._0_8_ -
                      (double)(local_170 + -1) *
                      (((double)CONCAT44((uint)((ulonglong)local_178 >> 0x20) & DAT_18030d9a0._4_4_,
                                         SUB84(local_178,0) & (uint)DAT_18030d9a0) * DAT_180305520)
                      / DAT_180305518));
          local_2c0 = local_2c8;
        }
        else {
          pCVar25 = ArtDoc::Content::GetObjectWithID(param_2,(__uint64)local_280);
          iVar28 = 0;
          plVar26 = (longlong *)
                    __RTDynamicCast(pCVar25,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                                    &DocumentMarks::GridInterface::RTTI_Type_Descriptor,0);
          (**(code **)(*plVar26 + 8))(plVar26,&local_1c8);
          if ((local_180 != 1) || (local_16c != '\0')) goto LAB_180131951;
          if (local_178 <= 0.0) {
            if (local_170 < local_1c8) {
              iVar28 = (local_170 - (local_1c8 + -1) % local_170) + -1;
            }
          }
          else {
            iVar28 = (local_1c8 + -1) % local_170;
          }
          uVar34 = SUB84(local_178,0) & (uint)DAT_18030d9a0;
          uVar35 = (uint)((ulonglong)local_178 >> 0x20) & DAT_18030d9a0._4_4_;
          if (local_1c8 < local_170) {
            local_170 = local_1c8;
          }
          dVar33 = (local_188 * DAT_180305520) / DAT_180305518;
          local_2b8 = (double)local_268 - dVar33;
          local_2c0 = (double *)
                      ((double)CONCAT44(uStack_104,uStack_108) +
                      ((double)iVar28 * (double)CONCAT44(uVar35,uVar34) * DAT_180305520) /
                      DAT_180305518);
          local_2f0 = (double *)
                      (dStack_f8 -
                      (double)(local_170 + -1) *
                      (((double)CONCAT44(uVar35,uVar34) * DAT_180305520) / DAT_180305518));
          local_2d0 = local_2f0;
        }
        local_2e8 = CONCAT44((uint)((ulonglong)dVar33 >> 0x20) ^ DAT_180308300._4_4_,
                             SUB84(dVar33,0) ^ (uint)DAT_180308300);
        FUN_1800d82d0(param_1,&local_2c0,&local_2f0);
        return param_1;
      }
      if (param_3 == 1) {
LAB_180131675:
        *(undefined4 *)param_1 = uVar44;
        *(undefined4 *)((longlong)param_1 + 4) = uVar45;
        *(undefined4 *)(param_1 + 1) = uVar46;
        *(undefined4 *)((longlong)param_1 + 0xc) = uVar47;
        param_1[2] = auStack_130._0_8_;
        param_1[3] = auStack_130._8_8_;
        param_1[4] = local_2f8;
        return param_1;
      }
      if (param_3 != 2) {
        if (param_3 == 3) {
          pCVar25 = ArtDoc::Content::GetObjectWithID(param_2,(__uint64)local_2d0);
          iVar28 = 0;
          plVar26 = (longlong *)
                    __RTDynamicCast(pCVar25,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                                    &DocumentMarks::GridInterface::RTTI_Type_Descriptor,0);
          (**(code **)(*plVar26 + 8))(plVar26,&local_1c8);
          if ((local_180 == 2) && (local_16c == '\0')) {
            if (local_178 < 0.0) {
              iVar28 = local_170;
              if (local_1c4 < local_170) {
                iVar28 = local_1c4;
              }
              iVar28 = iVar28 + -1;
            }
            if (local_1c4 < local_170) {
              local_170 = local_1c4;
            }
            local_2e0 = local_270;
            local_2f0 = (double *)((local_190 * DAT_180305520) / DAT_180305518);
            local_2d8 = (double)auStack_130._8_8_ + stack0xfffffffffffffec8 +
                        ((double)iVar28 * local_178 * DAT_180305520) / DAT_180305518;
            local_2c0 = (double *)auStack_130._8_8_;
            dVar33 = (double)auStack_130._8_8_ -
                     (double)(local_170 + -1) *
                     (((double)CONCAT44((uint)((ulonglong)local_178 >> 0x20) & DAT_18030d9a0._4_4_,
                                        SUB84(local_178,0) & (uint)DAT_18030d9a0) * DAT_180305520) /
                     DAT_180305518);
            local_2e8 = CONCAT44((uint)((ulonglong)dVar33 >> 0x20) ^ DAT_180308300._4_4_,
                                 SUB84(dVar33,0) ^ (uint)DAT_180308300);
            FUN_1800d82d0(param_1,&local_2e0,&local_2f0);
            return param_1;
          }
          goto LAB_180131675;
        }
        pCVar25 = ArtDoc::Content::GetObjectWithID(param_2,(__uint64)local_258);
        iVar28 = 0;
        plVar26 = (longlong *)
                  __RTDynamicCast(pCVar25,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                                  &DocumentMarks::GridInterface::RTTI_Type_Descriptor,0);
        (**(code **)(*plVar26 + 8))(plVar26,&local_1c8);
        if ((local_180 == 2) && (local_16c == '\0')) {
          if (local_178 <= 0.0) {
            if (local_170 < local_1c4) {
              iVar28 = (local_170 - (local_1c4 + -1) % local_170) + -1;
            }
          }
          else {
            iVar28 = (local_1c4 + -1) % local_170;
          }
          uVar34 = SUB84(local_178,0) & (uint)DAT_18030d9a0;
          uVar35 = (uint)((ulonglong)local_178 >> 0x20) & DAT_18030d9a0._4_4_;
          if (local_1c4 < local_170) {
            local_170 = local_1c4;
          }
          local_2f0 = (double *)((local_190 * DAT_180305520) / DAT_180305518);
          local_2c0 = (double *)
                      (((double)stack0xfffffffffffffde0 + stack0xfffffffffffffdd0) -
                      ((double)iVar28 * (double)CONCAT44(uVar35,uVar34) * DAT_180305520) /
                      DAT_180305518);
          local_2e0 = stack0xfffffffffffffde0;
          local_250 = ((double)CONCAT44(uVar63,uVar62) + (double)local_278) - (double)local_2f0;
          dVar33 = (double)stack0xfffffffffffffde0 -
                   (double)(local_170 + -1) *
                   (((double)CONCAT44(uVar35,uVar34) * DAT_180305520) / DAT_180305518);
          local_2e8 = CONCAT44((uint)((ulonglong)dVar33 >> 0x20) ^ DAT_180308300._4_4_,
                               SUB84(dVar33,0) ^ (uint)DAT_180308300);
          local_248 = local_2c0;
          FUN_1800d82d0(param_1,&local_250,&local_2f0);
          return param_1;
        }
      }
      *(undefined4 *)param_1 = uVar54;
      *(undefined4 *)((longlong)param_1 + 4) = uVar55;
      *(undefined4 *)(param_1 + 1) = uVar56;
      *(undefined4 *)((longlong)param_1 + 0xc) = uVar57;
      *(undefined4 *)(param_1 + 2) = uVar50;
      *(undefined4 *)((longlong)param_1 + 0x14) = uVar51;
      *(undefined4 *)(param_1 + 3) = uVar52;
      *(undefined4 *)((longlong)param_1 + 0x1c) = uVar53;
      param_1[4] = local_300;
      return param_1;
    }
  }
  if ((param_4 == (PageBox *)0x0) || ((char)param_4[0x1e] != 0)) {
    if ((param_4 == (PageBox *)0x0) || ((char)param_4[0x1e] != 1)) {
      param_4 = (PageBox *)0x0;
    }
    if (param_4 == (PageBox *)0x0) {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      *(undefined1 *)(param_1 + 4) = 1;
      return param_1;
    }
    ArtDoc::Content::GetObjectWithID(param_2,*(undefined8 *)param_4);
    DocumentMarks::GetBoundingBoxForPositioning((ContentObject *)&local_240);
    pRVar27 = (RectangleBase<YAGL::MilliPointCoordinateSystem> *)&local_2b0;
    if (local_218._0_1_ == '\0') {
      local_290 = CONCAT31(local_290._1_3_,1);
      local_2b0 = (double *)0x0;
      pdStack_2a8 = (double *)0x0;
      local_2a0 = 0;
      uStack_29c = 0;
      uStack_298 = 0;
      uStack_294 = 0;
    }
    else {
      local_2b0 = local_240;
      pdStack_2a8 = (double *)auStack_238._0_8_;
      local_290 = auStack_228._8_4_;
      uStack_28c = auStack_228._12_4_;
      local_2a0 = auStack_238._8_4_;
      uStack_29c = auStack_238._12_4_;
      uStack_298 = auStack_228._0_4_;
      uStack_294 = auStack_228._4_4_;
    }
  }
  else {
    this = ArtDoc::PageContent::GetPage((PageContent *)param_2);
    pRVar27 = ArtDoc::Page::GetPageBox(this,*param_4);
  }
  uVar10 = *(undefined8 *)(pRVar27 + 8);
  *param_1 = *(undefined8 *)pRVar27;
  param_1[1] = uVar10;
  uVar10 = *(undefined8 *)(pRVar27 + 0x18);
  param_1[2] = *(undefined8 *)(pRVar27 + 0x10);
  param_1[3] = uVar10;
  param_1[4] = *(undefined8 *)(pRVar27 + 0x20);
  return param_1;
}


