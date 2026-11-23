// 18013ee90 regenerateMarkImp

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Removing unreachable block (ram,0x00018013fe2d) */
/* WARNING: Removing unreachable block (ram,0x00018013fe43) */
/* WARNING: Removing unreachable block (ram,0x00018013fe5c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: virtual void __cdecl DocumentMarks::PDFPlusCutMark::regenerateMarkImp(void) __ptr64 */

void __thiscall DocumentMarks::PDFPlusCutMark::regenerateMarkImp(PDFPlusCutMark *this)

{
  int *piVar1;
  longlong *plVar2;
  PDFPlusCutMark *pPVar3;
  ulonglong uVar4;
  int iVar5;
  double dVar6;
  ulonglong uVar7;
  undefined1 auVar8 [12];
  undefined *puVar9;
  undefined **ppuVar10;
  undefined **ppuVar11;
  Compound *pCVar12;
  undefined *puVar13;
  undefined *puVar14;
  bool bVar15;
  undefined8 *puVar16;
  Content *pCVar17;
  ContentObject *pCVar18;
  longlong *plVar19;
  double **ppdVar20;
  Group *pGVar21;
  longlong lVar22;
  undefined1 (*pauVar23) [16];
  undefined **ppuVar24;
  double *pdVar25;
  undefined8 uVar26;
  Document *pDVar27;
  TransformationBase<YAGL::MilliPointCoordinateSystem> *pTVar28;
  longlong *plVar29;
  longlong *plVar30;
  undefined *puVar31;
  char cVar32;
  undefined **ppuVar33;
  double *pdVar34;
  undefined4 uVar35;
  double dVar36;
  double dVar37;
  undefined *puVar38;
  undefined1 auVar39 [16];
  undefined *puVar40;
  undefined *puVar41;
  undefined1 auVar42 [16];
  double dVar43;
  undefined1 auVar44 [16];
  undefined1 auStackY_728 [32];
  double local_6e8;
  longlong *local_6e0;
  PDFPlusCutMark *local_6d8;
  double *local_6d0;
  PDFPlusCutMark *local_6c8;
  undefined8 local_6b8;
  undefined4 uStack_6b0;
  undefined4 uStack_6ac;
  longlong *local_6a8;
  longlong *local_6a0;
  double local_698;
  double local_690;
  undefined **local_688;
  undefined **ppuStack_680;
  undefined **ppuStack_678;
  undefined8 local_670;
  undefined8 local_668;
  Group *local_660;
  undefined1 local_658 [16];
  double local_648;
  double dStack_640;
  undefined *local_638;
  double dStack_630;
  PDFPlusCutMark *local_628;
  double *local_620;
  double *pdStack_618;
  double *local_610;
  Compound *local_608;
  longlong *plStack_600;
  Group *local_5f8;
  Group *pGStack_5f0;
  longlong local_5e8;
  Compound *local_5d8;
  longlong *plStack_5d0;
  undefined *local_5c8;
  undefined *puStack_5c0;
  undefined *local_5b8;
  undefined *puStack_5b0;
  undefined *local_5a8;
  undefined *puStack_5a0;
  Compound *local_598;
  undefined *puStack_590;
  longlong *local_588;
  longlong *plStack_580;
  longlong *local_578;
  undefined1 local_570 [8];
  double local_568;
  double local_560;
  undefined **local_558;
  Group **local_550;
  undefined ***local_520;
  Visitable local_510 [16];
  double local_500;
  char local_4e8;
  undefined **local_4d8;
  undefined **local_4d0 [7];
  undefined ***local_498;
  undefined *local_488;
  undefined *puStack_480;
  undefined *local_478;
  undefined *puStack_470;
  undefined *local_468;
  char cStack_460;
  undefined7 uStack_45f;
  undefined **local_408 [7];
  undefined ***local_3d0;
  undefined **local_3c8 [7];
  undefined ***local_390;
  undefined **local_388 [7];
  undefined ***local_350;
  Expander local_348 [640];
  ulonglong local_c8;
  
                    /* 0x13ee90  2187  ?regenerateMarkImp@PDFPlusCutMark@DocumentMarks@@MEAAXXZ */
  local_c8 = DAT_180418e00 ^ (ulonglong)auStackY_728;
  local_668 = (Group *)((ulonglong)local_668 & 0xffffffff00000000);
  local_6e8 = (double)((ulonglong)local_6e8 & 0xffffffff00000000);
  pCVar18 = *(ContentObject **)(this + 0x2c0);
  local_6c8 = this;
  local_628 = this;
  while (pCVar18 != (ContentObject *)0x0) {
                    /* WARNING: Read-only address (ram,0x0001803082f0) is written */
    DocumentEdit::Delete(pCVar18);
    pCVar18 = *(ContentObject **)(this + 0x2c0);
  }
                    /* WARNING: Read-only address (ram,0x0001803082f0) is written */
  FUN_1802a1ce0(local_570);
  if (this[0x700] != (PDFPlusCutMark)0x0) {
    FUN_1800651a0(this + 0x6c0);
    this[0x700] = (PDFPlusCutMark)0x0;
  }
  local_6d0 = (double *)0x0;
  pPVar3 = this + 0x698;
  if ((pPVar3 == (PDFPlusCutMark *)0x0) || (this[0x6b8] != (PDFPlusCutMark)0x1)) {
    if (this[0x6b8] != (PDFPlusCutMark)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_180025a80();
    }
    local_6d0 = *(double **)pPVar3;
  }
  else {
    local_6d8 = pPVar3;
    puVar16 = (undefined8 *)FUN_18013bdc0(&local_6e0,this,pPVar3);
    local_6d0 = (double *)*puVar16;
  }
  local_560 = ((double)local_6d0 * 127.0) / 360000.0;
  puVar16 = (undefined8 *)DynamicMark::GetSourceContent((DynamicMark *)this);
  ArtPaint::FormPaint::GetContent((FormPaint *)*puVar16);
  GetPDFPlusBoundingBox(local_510);
  plVar19 = plStack_600;
  if (plStack_600 != (longlong *)0x0) {
    LOCK();
    plVar29 = plStack_600 + 1;
    lVar22 = *plVar29;
    *(int *)plVar29 = (int)*plVar29 + -1;
    UNLOCK();
    if ((int)lVar22 == 1) {
      (**(code **)*plStack_600)(plStack_600);
      LOCK();
      piVar1 = (int *)((longlong)plVar19 + 0xc);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 == 1) {
        (**(code **)(*plVar19 + 8))(plVar19);
      }
    }
  }
  if ((local_4e8 == '\0') || (local_500 < 0.0)) {
LAB_18013f099:
    local_500 = 0.0;
  }
  else if (local_500 <= 0.0) {
    if (local_500 == 0.0) {
      cVar32 = '\0';
    }
    else {
      cVar32 = -0x80;
    }
    if (cVar32 < '\0') goto LAB_18013f099;
  }
  local_568 = (local_500 * 127.0) / 360000.0;
  local_620 = (double *)0x0;
  pdStack_618 = (double *)0x0;
  local_6c8 = (PDFPlusCutMark *)0x0;
  local_610 = (double *)0x0;
  local_6d8 = (PDFPlusCutMark *)local_500;
  if (((this + 0x708 == (PDFPlusCutMark *)0x0) || (this[0x788] != (PDFPlusCutMark)0x0)) ||
     (this[0x780] != (PDFPlusCutMark)0x1)) {
LAB_18013f2be:
    if (this[0x788] == (PDFPlusCutMark)0x1) {
      local_688 = (undefined **)0x0;
      ppuStack_680 = (undefined **)0x0;
      ppuStack_678 = (undefined **)0x0;
      local_658 = ZEXT816(0);
      local_648 = 0.0;
      dStack_640 = 0.0;
      cVar32 = '\x01';
      local_638 = (undefined *)CONCAT71(local_638._1_7_,1);
      pCVar17 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
      local_5f8 = (Group *)0x0;
      pGStack_5f0 = (Group *)0x0;
      local_5e8 = 0;
      local_668 = (Group *)CONCAT44(local_668._4_4_,2);
      local_6e8 = (double)CONCAT44(local_6e8._4_4_,2);
      local_558 = std::
                  _Func_impl_no_alloc<`class_std::vector<DocumentMarks::StationInterface_const*___ptr64,std::allocator<DocumentMarks::StationInterface_const*___ptr64>_>___cdecl__anon_E70A8568::CollectStations(ArtDoc::Content&___ptr64)'::`2'::<lambda_1>,bool,ArtDoc::Group&___ptr64>
                  ::vftable;
      local_550 = &local_5f8;
      local_520 = &local_558;
      ArtDoc::VisitorBase::VisitorBase((VisitorBase *)&local_4d8);
      local_4d8 = ArtDoc::SimpleVisitor<ArtDoc::Group>::vftable;
      local_498 = (undefined ***)0x0;
      if (local_520 != (undefined ***)0x0) {
        if (local_520 == &local_558) {
          local_498 = (undefined ***)(*(code *)(*local_520)[1])(local_520,local_4d0);
          if (local_520 == (undefined ***)0x0) goto LAB_18013f3e5;
          (*(code *)(*local_520)[4])
                    (local_520,CONCAT71((int7)((ulonglong)&local_558 >> 8),local_520 != &local_558))
          ;
        }
        else {
          local_498 = local_520;
        }
        local_520 = (undefined ***)0x0;
      }
LAB_18013f3e5:
      (**(code **)(*(longlong *)pCVar17 + 0x10))(pCVar17,&local_4d8);
      if (local_498 != (undefined ***)0x0) {
        (*(code *)(*local_498)[4])
                  (local_498,CONCAT71((int7)((ulonglong)local_4d0 >> 8),local_498 != local_4d0));
        local_498 = (undefined ***)0x0;
      }
      ArtDoc::VisitorBase::~VisitorBase((VisitorBase *)&local_4d8);
      local_660 = pGStack_5f0;
      ppuVar33 = ppuStack_680;
      uVar35 = 0;
      if (local_5f8 != pGStack_5f0) {
        uVar26 = 0;
        auVar42._8_8_ = 0;
        auVar42._0_8_ = local_658._0_8_;
        pGVar21 = local_5f8;
        dVar37 = local_648;
        dVar43 = dStack_640;
        dVar36 = (double)local_658._8_8_;
        do {
          (**(code **)(**(longlong **)pGVar21 + 0x28))(*(longlong **)pGVar21,&local_488);
          (**(code **)(**(longlong **)pGVar21 + 0x18))(*(longlong **)pGVar21,&local_6b8);
          (**(code **)(**(longlong **)pGVar21 + 0x20))(*(longlong **)pGVar21,&local_6a8);
          if (local_6b8 == (Compound *)0x0) {
LAB_18013fa8d:
            if (local_6a8 != (longlong *)0x0) {
              FUN_180137b30(local_6a8,local_6a0,&local_6a8);
              plVar19 = local_6a8;
              if ((0xfff < (ulonglong)((((longlong)local_698 - (longlong)local_6a8) / 0x18) * 0x18))
                 && (plVar19 = (longlong *)local_6a8[-1],
                    0x1f < (ulonglong)((longlong)local_6a8 + (-8 - (longlong)plVar19)))) {
LAB_18013fbe3:
                    /* WARNING: Subroutine does not return */
                _invalid_parameter_noinfo_noreturn();
              }
LAB_18013fb05:
              free(plVar19);
              local_6a8 = (longlong *)0x0;
              local_698 = 0.0;
              local_6a0 = (longlong *)0x0;
            }
          }
          else {
            bVar15 = YAGL::Compound::IsEmpty(local_6b8);
            puVar14 = local_468;
            puVar13 = puStack_470;
            puVar41 = local_478;
            puVar40 = puStack_480;
            puVar38 = local_488;
            pCVar12 = local_6b8;
            if ((bVar15) || (local_6a8 == local_6a0)) goto LAB_18013fa8d;
            local_5c8 = local_488;
            puStack_5c0 = puStack_480;
            local_5b8 = local_478;
            puStack_5b0 = puStack_470;
            puVar9 = (undefined *)CONCAT71(uStack_45f,cStack_460);
            local_5a8 = local_468;
            if (CONCAT44(uStack_6ac,uStack_6b0) != 0) {
              LOCK();
              piVar1 = (int *)(CONCAT44(uStack_6ac,uStack_6b0) + 8);
              *piVar1 = *piVar1 + 1;
              UNLOCK();
            }
            puVar31 = (undefined *)CONCAT44(uStack_6ac,uStack_6b0);
            local_598 = local_6b8;
            local_588 = (longlong *)0x0;
            plStack_580 = (longlong *)0x0;
            local_578 = (longlong *)0x0;
            uVar7 = ((longlong)local_6a0 - (longlong)local_6a8) / 0x18;
            plVar19 = (longlong *)0x0;
            puStack_5a0 = puVar9;
            puStack_590 = puVar31;
            if (uVar7 != 0) {
              if (0xaaaaaaaaaaaaaaa < uVar7) {
                    /* WARNING: Subroutine does not return */
                FUN_1800193a0();
              }
              uVar4 = uVar7 * 0x18;
              if (uVar4 != 0) {
                if (uVar4 < 0x1000) {
                  plVar19 = (longlong *)FUN_1802d6b50(uVar4);
                }
                else {
                  if (uVar4 + 0x27 <= uVar4) {
                    /* WARNING: Subroutine does not return */
                    FUN_180019130();
                  }
                  lVar22 = FUN_1802d6b50();
                  if (lVar22 == 0) {
                    /* WARNING: Subroutine does not return */
                    _invalid_parameter_noinfo_noreturn();
                  }
                  plVar19 = (longlong *)(lVar22 + 0x27U & 0xffffffffffffffe0);
                  plVar19[-1] = lVar22;
                }
              }
              local_578 = plVar19 + uVar7 * 3;
              plStack_580 = plVar19;
              if (local_6a8 != local_6a0) {
                plVar29 = local_6a8 + 1;
                do {
                  *plStack_580 = 0;
                  plStack_580[1] = 0;
                  if (*plVar29 != 0) {
                    LOCK();
                    piVar1 = (int *)(*plVar29 + 8);
                    *piVar1 = *piVar1 + 1;
                    UNLOCK();
                  }
                  *plStack_580 = plVar29[-1];
                  plStack_580[1] = *plVar29;
                  plStack_580[2] = plVar29[1];
                  plStack_580 = plStack_580 + 3;
                  plVar30 = plVar29 + 2;
                  plVar29 = plVar29 + 3;
                } while (plVar30 != local_6a0);
              }
              local_588 = plVar19;
            }
            plVar30 = local_578;
            plVar29 = plStack_580;
            plVar19 = local_588;
            if (ppuVar33 == ppuStack_678) {
              FUN_180137e20(&local_688,ppuVar33,&local_5c8);
            }
            else {
              *ppuVar33 = puVar38;
              ppuVar33[1] = puVar40;
              ppuVar33[2] = puVar41;
              ppuVar33[3] = puVar13;
              ppuVar33[4] = puVar14;
              ppuVar33[5] = puVar9;
              ppuVar33[6] = pCVar12;
              ppuVar33[7] = puVar31;
              local_598 = (Compound *)0x0;
              puStack_590 = (undefined *)0x0;
              local_578 = (longlong *)0x0;
              plStack_580 = (longlong *)0x0;
              local_588 = (longlong *)0x0;
              ppuVar33[8] = (undefined *)plVar19;
              ppuVar33[9] = (undefined *)plVar29;
              ppuVar33[10] = (undefined *)plVar30;
              ppuStack_680 = ppuVar33 + 0xb;
            }
            plVar29 = local_578;
            plVar19 = local_588;
            ppuVar33 = ppuStack_680;
            if (local_588 != (longlong *)0x0) {
              FUN_180137b30(local_588,plStack_580,&local_588);
              plVar30 = plVar19;
              if ((0xfff < (ulonglong)((((longlong)plVar29 - (longlong)plVar19) / 0x18) * 0x18)) &&
                 (plVar30 = (longlong *)plVar19[-1],
                 0x1f < (ulonglong)((longlong)plVar19 + (-8 - (longlong)plVar30)))) {
                    /* WARNING: Subroutine does not return */
                _invalid_parameter_noinfo_noreturn();
              }
              free(plVar30);
              local_588 = (longlong *)0x0;
              plStack_580 = (longlong *)0x0;
              local_578 = (longlong *)0x0;
            }
            FUN_180013ed0(&local_598);
            if (CONCAT44(uStack_6ac,uStack_6b0) != 0) {
              LOCK();
              piVar1 = (int *)(CONCAT44(uStack_6ac,uStack_6b0) + 8);
              *piVar1 = *piVar1 + 1;
              UNLOCK();
            }
            plStack_600 = (longlong *)CONCAT44(uStack_6ac,uStack_6b0);
            local_608 = local_6b8;
            puVar16 = (undefined8 *)YAGL::operator*(&local_5d8,&local_488,&local_608);
            pauVar23 = (undefined1 (*) [16])YAGL::Compound::GetBoundingBox((Compound *)*puVar16);
            plVar19 = plStack_5d0;
            if (cVar32 == '\0') {
              if (pauVar23[2][0] == '\0') {
                if (*(double *)*pauVar23 < auVar42._0_8_) {
                  dVar37 = (auVar42._0_8_ + local_648) - *(double *)*pauVar23;
                  cVar32 = '\0';
                  local_638 = (undefined *)((ulonglong)local_638 & 0xffffffffffffff00);
                  local_658._0_8_ = *(ulonglong *)*pauVar23;
                  auVar42._8_8_ = 0;
                  auVar42._0_8_ = *(ulonglong *)*pauVar23;
                  local_648 = dVar37;
                }
                dVar6 = (*(double *)pauVar23[1] + *(double *)*pauVar23) - auVar42._0_8_;
                if ((dVar37 <= dVar6) && (dVar37 < dVar6)) {
                  dVar37 = (*(double *)pauVar23[1] + *(double *)*pauVar23) - auVar42._0_8_;
                  cVar32 = '\0';
                  local_638 = (undefined *)((ulonglong)local_638 & 0xffffffffffffff00);
                  local_648 = dVar37;
                }
                if (*(double *)(*pauVar23 + 8) < dVar36) {
                  dVar43 = (dVar36 + dStack_640) - *(double *)(*pauVar23 + 8);
                  cVar32 = '\0';
                  local_638 = (undefined *)((ulonglong)local_638 & 0xffffffffffffff00);
                  dVar36 = *(double *)(*pauVar23 + 8);
                  local_658._8_8_ = dVar36;
                  uVar26 = 0;
                  dStack_640 = dVar43;
                }
                local_6e0 = *(longlong **)(*pauVar23 + 8);
                dVar6 = (*(double *)(pauVar23[1] + 8) + (double)local_6e0) - dVar36;
                if ((dVar43 <= dVar6) && (dVar43 < dVar6)) {
                  dVar43 = (*(double *)(pauVar23[1] + 8) + (double)local_6e0) - dVar36;
                  cVar32 = '\0';
                  local_638 = (undefined *)((ulonglong)local_638 & 0xffffffffffffff00);
                  dStack_640 = dVar43;
                }
              }
            }
            else {
              auVar42 = *pauVar23;
              dVar37 = *(double *)pauVar23[1];
              dVar43 = *(double *)(pauVar23[1] + 8);
              local_638 = *(undefined **)pauVar23[2];
              auVar8._4_8_ = uVar26;
              auVar8._0_4_ = auVar42._4_4_;
              auVar44._0_8_ = auVar8._0_8_ << 0x20;
              auVar44._8_4_ = auVar42._8_4_;
              auVar44._12_4_ = auVar42._12_4_;
              dVar36 = auVar44._8_8_;
              uVar26 = auVar42._8_8_;
              cVar32 = (char)local_638;
              local_658 = auVar42;
              local_648 = dVar37;
              dStack_640 = dVar43;
            }
            if (plStack_5d0 != (longlong *)0x0) {
              LOCK();
              plVar29 = plStack_5d0 + 1;
              lVar22 = *plVar29;
              *(int *)plVar29 = (int)*plVar29 + -1;
              UNLOCK();
              if ((int)lVar22 == 1) {
                (**(code **)*plStack_5d0)(plStack_5d0);
                LOCK();
                piVar1 = (int *)((longlong)plVar19 + 0xc);
                iVar5 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar5 == 1) {
                  (**(code **)(*plVar19 + 8))(plVar19);
                }
              }
            }
            plVar29 = local_6a0;
            plVar19 = local_6a8;
            if (local_6a8 != (longlong *)0x0) {
              for (; plVar19 != plVar29; plVar19 = plVar19 + 3) {
                plVar30 = (longlong *)plVar19[1];
                if (plVar30 != (longlong *)0x0) {
                  LOCK();
                  plVar2 = plVar30 + 1;
                  lVar22 = *plVar2;
                  *(int *)plVar2 = (int)*plVar2 + -1;
                  UNLOCK();
                  if ((int)lVar22 == 1) {
                    (**(code **)*plVar30)(plVar30);
                    LOCK();
                    piVar1 = (int *)((longlong)plVar30 + 0xc);
                    iVar5 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar5 == 1) {
                      (**(code **)(*plVar30 + 8))(plVar30);
                    }
                  }
                }
              }
              plVar19 = local_6a8;
              if ((0xfff < (ulonglong)((((longlong)local_698 - (longlong)local_6a8) / 0x18) * 0x18))
                 && (plVar19 = (longlong *)local_6a8[-1],
                    0x1f < (ulonglong)((longlong)local_6a8 + (-8 - (longlong)plVar19))))
              goto LAB_18013fbe3;
              goto LAB_18013fb05;
            }
          }
          plVar19 = (longlong *)CONCAT44(uStack_6ac,uStack_6b0);
          if (plVar19 != (longlong *)0x0) {
            LOCK();
            plVar29 = plVar19 + 1;
            lVar22 = *plVar29;
            *(int *)plVar29 = (int)*plVar29 + -1;
            UNLOCK();
            if ((int)lVar22 == 1) {
              (**(code **)*plVar19)(plVar19);
              LOCK();
              piVar1 = (int *)((longlong)plVar19 + 0xc);
              iVar5 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar5 == 1) {
                (**(code **)(*plVar19 + 8))(plVar19);
              }
            }
          }
          pGVar21 = pGVar21 + 8;
        } while (pGVar21 != local_660);
        this = local_628;
        uVar35 = (undefined4)local_668;
      }
      local_668 = (Group *)(CONCAT44(local_668._4_4_,uVar35) & 0xfffffffffffffffd);
      if (local_5f8 != (Group *)0x0) {
        pGVar21 = local_5f8;
        if ((0xfff < (ulonglong)((local_5e8 - (longlong)local_5f8 >> 3) * 8)) &&
           (pGVar21 = *(Group **)(local_5f8 + -8),
           (Group *)0x1f < local_5f8 + (-8 - (longlong)pGVar21))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pGVar21);
      }
      ppuVar24 = local_688;
      if (local_688 == ppuVar33) {
        local_6d0 = local_620;
        pdVar25 = local_620;
      }
      else {
        uVar35 = *(undefined4 *)(this + 0x790);
        if (*(int *)(this + 0x794) != 2) {
          local_6e8 = (double)CONCAT44(local_6e8._4_4_,uVar35);
          uStack_6b0 = uVar35;
          ppuVar10 = local_688;
          local_6b8 = *(Compound **)(this + 0x790);
          ppuVar11 = local_688;
          while (ppuVar11 = ppuVar11 + 0xb, ppuVar11 != ppuVar33) {
            FUN_18013af70(&uStack_6b0,&local_6e0,ppuVar10);
            FUN_18013af70(&uStack_6b0,&local_660,ppuVar11);
            if ((local_6b8._4_4_ == 0) == ((int)local_6b8 == 1)) {
              if ((double)local_660 <= (double)local_6e0) {
                if ((double)local_6e0 <= (double)local_660) {
                  if ((double)local_6e0 == (double)local_660) {
                    bVar15 = false;
                  }
                  else {
                    bVar15 = false;
                  }
                }
                else {
                  bVar15 = false;
                }
              }
              else {
                bVar15 = true;
              }
            }
            else {
              if ((double)local_660 <= (double)local_6e0) {
                if ((double)local_6e0 <= (double)local_660) {
                  if ((double)local_6e0 == (double)local_660) {
                    cVar32 = '\0';
                  }
                  else {
                    cVar32 = -0x80;
                  }
                }
                else {
                  cVar32 = '\x01';
                }
              }
              else {
                cVar32 = -1;
              }
              bVar15 = '\0' < cVar32;
            }
            if (bVar15) {
              ppuVar10 = ppuVar11;
            }
          }
          FUN_18013af70(&local_6e8,&local_6e0,ppuVar10);
          local_608 = (Compound *)CONCAT44(local_608._4_4_,uVar35);
          plStack_600 = local_6e0;
          local_5d8 = local_608;
          plStack_5d0 = local_6e0;
          ppuVar24 = (undefined **)FUN_18013a1b0(ppuVar24,ppuVar33,&local_5d8);
          if (ppuVar24 != ppuVar33) {
            ppuVar24 = (undefined **)FUN_180138780(ppuVar33,ppuVar33,ppuVar24);
            FUN_180137ab0(ppuVar24,ppuVar33,&local_688);
            ppuStack_680 = ppuVar24;
          }
          this = local_628;
        }
        local_6e0 = (longlong *)0x40ebae9d3a74e9d4;
        FUN_18013c230(&local_5f8,&local_688,&local_6e0,*(undefined4 *)(this + 0x790));
        ppdVar20 = (double **)
                   FUN_18013d350(&local_6a8,&local_5f8,*(undefined4 *)(this + 0x790),
                                 *(undefined4 *)(this + 0x794));
        if (&local_620 != ppdVar20) {
          local_620 = *ppdVar20;
          pdStack_618 = ppdVar20[1];
          local_6c8 = (PDFPlusCutMark *)ppdVar20[2];
          *ppdVar20 = (double *)0x0;
          ppdVar20[1] = (double *)0x0;
          ppdVar20[2] = (double *)0x0;
          local_610 = (double *)local_6c8;
        }
        pdVar25 = local_620;
        local_6d0 = local_620;
        if (local_6a8 != (longlong *)0x0) {
          plVar19 = local_6a8;
          if ((0xfff < ((longlong)local_698 - (longlong)local_6a8 & 0xffffffffffffffe0U)) &&
             (plVar19 = (longlong *)local_6a8[-1],
             0x1f < (ulonglong)((longlong)local_6a8 + (-8 - (longlong)plVar19)))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(plVar19);
        }
        if (local_5f8 != (Group *)0x0) {
          pGVar21 = local_5f8;
          if ((0xfff < (ulonglong)((local_5e8 - (longlong)local_5f8 >> 3) * 8)) &&
             (pGVar21 = *(Group **)(local_5f8 + -8),
             (Group *)0x1f < local_5f8 + (-8 - (longlong)pGVar21))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(pGVar21);
        }
        ppuVar33 = ppuStack_680;
      }
      ppuVar24 = local_688;
      if (local_688 != (undefined **)0x0) {
        FUN_180137ab0(local_688,ppuVar33,&local_688);
        ppuVar33 = ppuVar24;
        if ((0xfff < (ulonglong)((((longlong)ppuStack_678 - (longlong)ppuVar24) / 0x58) * 0x58)) &&
           (ppuVar33 = (undefined **)ppuVar24[-1],
           0x1f < (ulonglong)((longlong)ppuVar24 + (-8 - (longlong)ppuVar33)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(ppuVar33);
      }
      goto LAB_18013f247;
    }
    pdVar25 = (double *)GetReferenceBox(this);
    auVar39._0_8_ = *pdVar25 * 127.0;
    auVar39._8_8_ = pdVar25[1] * 127.0;
    local_658 = divpd(auVar39,_DAT_1803082f0);
    dVar36 = (pdVar25[2] * 127.0) / 360000.0;
    dVar37 = (pdVar25[3] * 127.0) / 360000.0;
    if (dVar36 < 0.0) goto LAB_1801406e3;
    if (dVar36 <= 0.0) {
      if (dVar36 == 0.0) {
        cVar32 = '\0';
      }
      else {
        cVar32 = -0x80;
      }
    }
    else {
      cVar32 = -1;
    }
    if ((-1 < cVar32) || (dVar37 < 0.0)) goto LAB_1801406e3;
    if (dVar37 <= 0.0) {
      if (dVar37 == 0.0) {
        cVar32 = '\0';
      }
      else {
        cVar32 = -0x80;
      }
    }
    else {
      cVar32 = -1;
    }
    if (-1 < cVar32) goto LAB_1801406e3;
    local_698 = dVar36 + (double)local_658._0_8_;
    local_6d8 = local_658._8_8_;
    local_6a8 = (longlong *)local_658._0_8_;
    local_6a0 = (longlong *)(dVar37 + (double)local_6d8);
    local_688 = dm::MarkPositionVector::vftable;
    ppuStack_680 = (undefined **)0x0;
    ppuStack_678 = (undefined **)0x0;
    local_670 = 0;
    local_690 = (double)local_6d8;
    FUN_1802a26c0(local_570,&local_6a8,&local_688);
    uVar26 = FUN_18013d660(&local_5f8,&local_688);
    FUN_18013ae40(&local_620,uVar26);
    FUN_18013aaa0(&local_5f8);
    FUN_18004a7b0(&local_688);
    local_6c8 = (PDFPlusCutMark *)local_610;
    local_6d0 = local_620;
    pdVar25 = local_620;
  }
  else {
    pCVar17 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
    pCVar18 = ArtDoc::Content::GetObjectWithID(pCVar17,*(__uint64 *)(this + 0x708));
    plVar19 = (longlong *)
              __RTDynamicCast(pCVar18,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                              &GridInterface::RTTI_Type_Descriptor);
    if (plVar19 == (longlong *)0x0) goto LAB_18013f2be;
    (**(code **)(*plVar19 + 8))(plVar19,&local_488);
    local_688 = dm::MarkPositionVector::vftable;
    ppuStack_680 = (undefined **)0x0;
    ppuStack_678 = (undefined **)0x0;
    local_670 = 0;
    FUN_1802a2780(local_570,&local_488,&local_688);
    ppdVar20 = (double **)FUN_18013d660(&local_5f8,&local_688);
    if (&local_620 != ppdVar20) {
      local_620 = *ppdVar20;
      pdStack_618 = ppdVar20[1];
      local_6c8 = (PDFPlusCutMark *)ppdVar20[2];
      *ppdVar20 = (double *)0x0;
      ppdVar20[1] = (double *)0x0;
      ppdVar20[2] = (double *)0x0;
      local_610 = (double *)local_6c8;
    }
    pdVar25 = local_620;
    local_6d0 = local_620;
    if (local_5f8 != (Group *)0x0) {
      pGVar21 = local_5f8;
      if ((0xfff < (local_5e8 - (longlong)local_5f8 & 0xffffffffffffffe0U)) &&
         (pGVar21 = *(Group **)(local_5f8 + -8),
         (Group *)0x1f < local_5f8 + (-8 - (longlong)pGVar21))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pGVar21);
    }
    FUN_18004a7b0(&local_688);
LAB_18013f247:
  }
  if (pdVar25 != pdStack_618) {
    pdVar25 = pdVar25 + 1;
    do {
      pGVar21 = (Group *)FUN_1802d6b50(0x2d0);
      local_668 = pGVar21;
      if (pGVar21 == (Group *)0x0) {
        pGVar21 = (Group *)0x0;
      }
      else {
        ArtDoc::Group::Group(pGVar21,0x1ff);
        *(undefined ***)pGVar21 = ArtDoc::Group::vftable;
        *(undefined ***)(pGVar21 + 0x20) = ArtDoc::Group::vftable;
      }
      local_388[0] = std::
                     _Func_impl_no_alloc<`protected:_virtual_void___cdecl_DocumentMarks::PDFPlusCutMark::regenerateMarkImp(void)___ptr64'::`42'::<lambda_3>,bool,ArtDoc::Group_const&___ptr64>
                     ::vftable;
      local_350 = local_388;
      local_3c8[0] = std::
                     _Func_impl_no_alloc<`protected:_virtual_void___cdecl_DocumentMarks::PDFPlusCutMark::regenerateMarkImp(void)___ptr64'::`42'::<lambda_2>,bool,ArtDoc::Group_const&___ptr64>
                     ::vftable;
      local_390 = local_3c8;
      local_408[0] = std::
                     _Func_impl_no_alloc<`protected:_virtual_void___cdecl_DocumentMarks::PDFPlusCutMark::regenerateMarkImp(void)___ptr64'::`42'::<lambda_1>,bool,ArtDoc::Layer_const&___ptr64>
                     ::vftable;
      local_3d0 = local_408;
      local_660 = pGVar21;
      pCVar17 = ArtDoc::ContentObject::GetContent((ContentObject *)this);
      pDVar27 = ArtDoc::Content::GetDocument(pCVar17);
      DocumentEdit::Expander::Expander
                (local_348,pGVar21,pDVar27,
                 (function<bool___cdecl(ArtDoc::Layer_const&___ptr64)> *)local_408,
                 (function<bool___cdecl(ArtDoc::Group_const&___ptr64)> *)local_3c8,
                 (function<bool___cdecl(ArtDoc::Group_const&___ptr64)> *)local_388);
      if (local_3d0 != (undefined ***)0x0) {
        (*(code *)(*local_3d0)[4])
                  (local_3d0,CONCAT71((int7)((ulonglong)local_408 >> 8),local_3d0 != local_408));
        local_3d0 = (undefined ***)0x0;
      }
      if (local_390 != (undefined ***)0x0) {
        (*(code *)(*local_390)[4])
                  (local_390,CONCAT71((int7)((ulonglong)local_3c8 >> 8),local_390 != local_3c8));
        local_390 = (undefined ***)0x0;
      }
      if (local_350 != (undefined ***)0x0) {
        (*(code *)(*local_350)[4])
                  (local_350,CONCAT71((int7)((ulonglong)local_388 >> 8),local_350 != local_388));
        local_350 = (undefined ***)0x0;
      }
      puVar16 = (undefined8 *)DynamicMark::GetSourceContent((DynamicMark *)this);
      pCVar17 = ArtPaint::FormPaint::GetContent((FormPaint *)*puVar16);
      (**(code **)(*(longlong *)pCVar17 + 8))(pCVar17,local_348);
      plVar19 = plStack_5d0;
      if (plStack_5d0 != (longlong *)0x0) {
        LOCK();
        plVar29 = plStack_5d0 + 1;
        lVar22 = *plVar29;
        *(int *)plVar29 = (int)*plVar29 + -1;
        UNLOCK();
        if ((int)lVar22 == 1) {
          (**(code **)*plStack_5d0)(plStack_5d0);
          LOCK();
          piVar1 = (int *)((longlong)plVar19 + 0xc);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 == 1) {
            (**(code **)(*plVar19 + 8))(plVar19);
          }
        }
      }
      local_6e0 = (longlong *)pdVar25[1];
      local_6d8 = (PDFPlusCutMark *)pdVar25[2];
      dVar36 = atan2((double)local_6d8 - *pdVar25,(double)local_6e0 - pdVar25[-1]);
      dVar37 = cos(dVar36);
      local_658._8_8_ = sin(dVar36);
      local_658._0_8_ = dVar37;
      local_648 = -(double)local_658._8_8_;
      local_638 = (undefined *)0x0;
      dStack_630 = 0.0;
      dStack_640 = dVar37;
      ArtDoc::Transformable::SetTransformation
                ((Transformable *)pGVar21,
                 (TransformationBase<YAGL::MilliPointCoordinateSystem> *)local_658,7);
      GetPDFPlusBoundingBox((Visitable *)&local_488);
      if (cStack_460 == '\0') {
        puVar41 = (undefined *)0x0;
        local_6d8 = (PDFPlusCutMark *)0x0;
        puVar38 = (undefined *)0x0;
        puVar40 = (undefined *)0x0;
        local_638 = (undefined *)CONCAT71(local_638._1_7_,1);
      }
      else {
        local_638 = local_468;
        puVar38 = local_478;
        puVar40 = puStack_470;
        puVar41 = local_488;
        local_6d8 = (PDFPlusCutMark *)puStack_480;
      }
      local_6e8 = pdVar25[-1] - (double)puVar41;
      if (pdVar25[-1] == pdVar25[1]) {
        local_6e8 = local_6e8 - (double)puVar38 * 0.5;
      }
      else if (pdVar25[1] < pdVar25[-1]) {
        local_6e8 = local_6e8 - (double)puVar38;
      }
      dVar43 = local_6e8;
      local_6e8 = *pdVar25 - ((double)puVar40 + (double)local_6d8);
      dVar36 = *pdVar25;
      dVar37 = pdVar25[2];
      if (dVar36 == dVar37) {
        local_6e8 = local_6e8 + (double)puVar40 * 0.5;
        local_6d8 = (PDFPlusCutMark *)puVar40;
      }
      else if ((dVar36 <= dVar37) && (dVar36 < dVar37)) {
        local_6e8 = local_6e8 + (double)puVar40;
      }
      dVar36 = local_6e8;
      pTVar28 = ArtDoc::Transformable::GetTransformation((Transformable *)pGVar21);
      local_638 = (undefined *)dVar43;
      dStack_630 = dVar36;
      local_5c8 = (undefined *)(*(double *)(pTVar28 + 8) * 0.0 + *(double *)pTVar28);
      puStack_5c0 = (undefined *)(*(double *)pTVar28 * 0.0 + *(double *)(pTVar28 + 8));
      local_5b8 = (undefined *)(*(double *)(pTVar28 + 0x18) * 0.0 + *(double *)(pTVar28 + 0x10));
      puStack_5b0 = (undefined *)(*(double *)(pTVar28 + 0x10) * 0.0 + *(double *)(pTVar28 + 0x18));
      local_5a8 = (undefined *)
                  (dVar43 + *(double *)(pTVar28 + 0x28) * 0.0 + *(double *)(pTVar28 + 0x20));
      local_6e0 = *(longlong **)(pTVar28 + 0x28);
      local_6d8 = *(PDFPlusCutMark **)(pTVar28 + 0x20);
      puStack_5a0 = (undefined *)(dVar36 + (double)local_6e0 + (double)local_6d8 * 0.0);
      ArtDoc::Transformable::SetTransformation
                ((Transformable *)pGVar21,
                 (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_5c8,7);
      this = local_628;
      pCVar17 = ArtDoc::ContentObject::GetContent((ContentObject *)local_628);
      pDVar27 = ArtDoc::Content::GetDocument(pCVar17);
      ArtDoc::ActionGroupCreator::ActionGroupCreator
                ((ActionGroupCreator *)&local_608,pDVar27,false,false);
      local_660 = (Group *)0x0;
      pCVar18 = DocumentEdit::InsertNewObjectOnTop((ContentObject *)pGVar21,(Group *)this,true);
      DynamicMark::ApplyPDFPlusColor((DynamicMark *)this,pCVar18);
      ArtDoc::ActionGroupCreator::~ActionGroupCreator((ActionGroupCreator *)&local_608);
      DocumentEdit::Expander::~Expander(local_348);
      pdVar34 = pdVar25 + 3;
      pdVar25 = pdVar25 + 4;
    } while (pdVar34 != pdStack_618);
    pdVar25 = local_6d0;
  }
  if (pdVar25 != (double *)0x0) {
    pdVar34 = pdVar25;
    if ((0xfff < ((longlong)local_6c8 - (longlong)pdVar25 & 0xffffffffffffffe0U)) &&
       (pdVar34 = (double *)pdVar25[-1],
       0x1f < (ulonglong)((longlong)pdVar25 + (-8 - (longlong)pdVar34)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pdVar34);
  }
LAB_1801406e3:
  FUN_1802a0fa0(local_570);
  return;
}


