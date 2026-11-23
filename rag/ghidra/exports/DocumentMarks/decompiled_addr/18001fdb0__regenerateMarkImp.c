// DocumentMarks.dll 18001fdb0 DocumentMarks::BearerBar::regenerateMarkImp
// signature: void regenerateMarkImp(BearerBar * this)

/* protected: virtual void __cdecl DocumentMarks::BearerBar::regenerateMarkImp(void) __ptr64 */

void __thiscall DocumentMarks::BearerBar::regenerateMarkImp(BearerBar *this)

{
  int *piVar1;
  longlong *plVar2;
  longlong *plVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  longlong *plVar8;
  longlong *plVar9;
  double dVar10;
  bool bVar11;
  int iVar12;
  longlong lVar13;
  Fillable *this_00;
  Path *pPVar14;
  shared_ptr<ArtPaint::Paint_const_> *psVar15;
  Factory *this_01;
  undefined8 *puVar16;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar17;
  basic_ostream<char,std::char_traits<char>_> *pbVar18;
  undefined8 uVar19;
  char *pcVar20;
  longlong *plVar21;
  uint uVar22;
  longlong *plVar23;
  longlong *local_res10;
  ContentObject *local_res18;
  Path *local_res20;
  undefined8 in_stack_fffffffffffffd18;
  ulonglong uVar24;
  longlong *local_2d0;
  longlong *plStack_2c8;
  longlong *local_2c0;
  undefined8 local_2b8;
  undefined8 uStack_2b0;
  undefined8 local_2a8;
  undefined8 uStack_2a0;
  undefined1 local_298 [16];
  undefined8 local_288;
  longlong *plStack_280;
  undefined1 local_278 [8];
  undefined4 uStack_270;
  undefined4 uStack_26c;
  ContentObject local_268 [8];
  longlong *local_260;
  double local_258;
  double local_250;
  double local_248;
  double local_240;
  char local_238;
  double local_230;
  undefined8 local_208;
  undefined8 uStack_200;
  undefined8 local_1f8;
  undefined1 local_160;
  undefined2 local_158;
  Factory local_150 [272];
  
                    /* 0x1fdb0  2176  ?regenerateMarkImp@BearerBar@DocumentMarks@@MEAAXXZ */
  uVar22 = (uint)((ulonglong)in_stack_fffffffffffffd18 >> 0x20);
  iVar12 = GetMarksDebugLevel();
  local_res18 = *(ContentObject **)(this + 0x2c0);
  if (local_res18 != (ContentObject *)0x0) {
    local_2d0 = (longlong *)0x0;
    plStack_2c8 = (longlong *)0x0;
    plVar23 = (longlong *)0x0;
    local_res10 = (longlong *)0x0;
    local_2c0 = (longlong *)0x0;
    uVar24 = (ulonglong)uVar22 << 0x20;
    lVar13 = __RTDynamicCast(local_res18,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                             &ArtDoc::Group::RTTI_Type_Descriptor,uVar24);
    if (lVar13 != 0) {
      plVar21 = *(longlong **)(lVar13 + 0x2c0);
      for (plStack_2c8 = (longlong *)0x0;
          (plVar21 != (longlong *)0x0 && (plStack_2c8 != (longlong *)0x0));
          plStack_2c8 = plStack_2c8 + 1) {
        *plStack_2c8 = (longlong)plVar21;
        plVar21 = (longlong *)plVar21[1];
      }
      if (plVar21 != (longlong *)0x0) {
        do {
          if (plStack_2c8 == plVar23) {
            local_res10 = plVar21;
            FUN_18001de60(&local_2d0,plStack_2c8,&local_res10);
            plVar23 = local_2c0;
          }
          else {
            *plStack_2c8 = (longlong)plVar21;
            plStack_2c8 = plStack_2c8 + 1;
          }
          plVar21 = (longlong *)plVar21[1];
        } while (plVar21 != (longlong *)0x0);
        local_res10 = plVar23;
      }
    }
    plVar23 = plStack_2c8;
    this_00 = (Fillable *)
              __RTDynamicCast(plStack_2c8[-1],0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                              &ArtDoc::Path::RTTI_Type_Descriptor,uVar24 & 0xffffffff00000000);
    DynamicObject::getPositionRefBBox((DynamicObject *)this);
    uVar22 = 0;
    do {
      if ((*(uint *)(this + 0x6b0) >> (uVar22 & 0x1f) & 1) != 0) {
        FUN_18001edf0(local_278,&local_258,uVar22,this + 0x698,this + 0x6a0,this + 0x6a8);
        pPVar14 = (Path *)FUN_1802d6b50(0x398);
        local_res20 = pPVar14;
        if (pPVar14 == (Path *)0x0) {
          pPVar14 = (Path *)0x0;
        }
        else {
          if (CONCAT44(uStack_26c,uStack_270) != 0) {
            LOCK();
            piVar1 = (int *)(CONCAT44(uStack_26c,uStack_270) + 8);
            *piVar1 = *piVar1 + 1;
            UNLOCK();
          }
          ArtDoc::Path::Path(pPVar14,local_298);
          *(undefined ***)pPVar14 = ArtDoc::Path::vftable;
          *(undefined ***)(pPVar14 + 0x20) = ArtDoc::Path::vftable;
        }
        bVar11 = ArtDoc::Fillable::IsFilled(this_00);
        if (bVar11) {
          psVar15 = ArtDoc::Fillable::GetFillPaint(this_00);
          if (*(longlong *)(psVar15 + 8) != 0) {
            LOCK();
            piVar1 = (int *)(*(longlong *)(psVar15 + 8) + 8);
            *piVar1 = *piVar1 + 1;
            UNLOCK();
          }
          local_2b8 = *(undefined8 *)psVar15;
          uStack_2b0 = *(undefined8 *)(psVar15 + 8);
          ArtDoc::Fillable::SetFillPaint((Fillable *)pPVar14,&local_2b8);
        }
        else {
          local_288 = 0;
          plStack_280 = (longlong *)0x0;
          local_208 = 0;
          uStack_200 = 0;
          local_1f8 = 0;
          local_160 = 0;
          local_158 = 0x200;
          this_01 = (Factory *)
                    ArtPaint::FlatPaint::Factory::Factory(local_150,&local_208,0,&local_288);
          puVar16 = (undefined8 *)ArtPaint::FlatPaint::Factory::Get(this_01);
          local_2a8 = *puVar16;
          uStack_2a0 = puVar16[1];
          *puVar16 = 0;
          puVar16[1] = 0;
          ArtDoc::Fillable::SetFillPaint((Fillable *)pPVar14,&local_2a8);
          plVar21 = local_260;
          if (local_260 != (longlong *)0x0) {
            LOCK();
            plVar2 = local_260 + 1;
            lVar13 = *plVar2;
            *(int *)plVar2 = (int)*plVar2 + -1;
            UNLOCK();
            if ((int)lVar13 == 1) {
              (**(code **)*local_260)(local_260);
              LOCK();
              piVar1 = (int *)((longlong)plVar21 + 0xc);
              iVar4 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar4 == 1) {
                (**(code **)(*plVar21 + 8))(plVar21);
              }
            }
          }
          ArtPaint::FlatPaint::Factory::~Factory(local_150);
          plVar21 = plStack_280;
          if (plStack_280 != (longlong *)0x0) {
            LOCK();
            plVar2 = plStack_280 + 1;
            lVar13 = *plVar2;
            *(int *)plVar2 = (int)*plVar2 + -1;
            UNLOCK();
            if ((int)lVar13 == 1) {
              (**(code **)*plStack_280)(plStack_280);
              LOCK();
              piVar1 = (int *)((longlong)plVar21 + 0xc);
              iVar4 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar4 == 1) {
                (**(code **)(*plVar21 + 8))(plVar21);
              }
            }
          }
        }
        FUN_1800f79a0(this_00,pPVar14);
        FUN_1800f7d70(this_00,pPVar14);
        DocumentEdit::InsertNewObjectAfter((ContentObject *)pPVar14,(ContentObject *)this_00,true);
        plVar21 = (longlong *)CONCAT44(uStack_26c,uStack_270);
        if (plVar21 != (longlong *)0x0) {
          LOCK();
          plVar2 = plVar21 + 1;
          lVar13 = *plVar2;
          *(int *)plVar2 = (int)*plVar2 + -1;
          UNLOCK();
          if ((int)lVar13 == 1) {
            (**(code **)*plVar21)(plVar21);
            LOCK();
            piVar1 = (int *)((longlong)plVar21 + 0xc);
            iVar4 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar4 == 1) {
              (**(code **)(*plVar21 + 8))(plVar21);
            }
          }
        }
      }
      plVar8 = local_2d0;
      plVar2 = local_res10;
      uVar22 = uVar22 + 1;
      plVar21 = local_2d0;
    } while ((int)uVar22 < 4);
    for (; plVar21 != plVar23; plVar21 = plVar21 + 1) {
      DocumentEdit::ExtractObjectFromParent(local_268);
      plVar9 = local_260;
      if (local_260 != (longlong *)0x0) {
        LOCK();
        plVar3 = local_260 + 1;
        lVar13 = *plVar3;
        *(int *)plVar3 = (int)*plVar3 + -1;
        UNLOCK();
        if ((int)lVar13 == 1) {
          (**(code **)*local_260)(local_260);
          LOCK();
          piVar1 = (int *)((longlong)plVar9 + 0xc);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 == 1) {
            (**(code **)(*plVar9 + 8))(plVar9);
          }
        }
      }
    }
    DynamicObject::applyColor((DynamicObject *)this,local_res18);
    if (2 < iVar12) {
      local_230 = (local_258 * DAT_180305518) / DAT_180305520;
      dVar7 = (local_250 * DAT_180305518) / DAT_180305520;
      dVar5 = (local_248 * DAT_180305518) / DAT_180305520;
      dVar6 = (local_240 * DAT_180305518) / DAT_180305520;
      FUN_18001b3e0(cout_exref," Bearer Bar update\n");
      pbVar17 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                FUN_18001b3e0(cout_exref,"   Reference object Bbox mm:");
      if (local_238 == '\0') {
        pbVar18 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(pbVar17,"[ L: ");
        dVar10 = local_230;
        pbVar17 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar18,local_230);
        pbVar18 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(pbVar17,", T: ");
        pbVar17 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            (pbVar18,dVar7 + dVar6);
        pbVar18 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(pbVar17,", R: ");
        pbVar17 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            (pbVar18,dVar10 + dVar5);
        pbVar18 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(pbVar17,", B: ");
        pbVar17 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar18,dVar7);
        pbVar18 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(pbVar17," (W: ");
        pbVar17 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar18,dVar5);
        pbVar18 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(pbVar17,", H: ");
        pbVar17 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar18,dVar6);
        pcVar20 = ") ]";
      }
      else {
        pcVar20 = "[ <initial/default state> ]";
      }
      uVar19 = FUN_18001b3e0(pbVar17,pcVar20);
      FUN_18001b3e0(uVar19,&DAT_18030544c);
    }
    if (plVar8 != (longlong *)0x0) {
      plVar23 = plVar8;
      if ((0xfff < ((longlong)plVar2 - (longlong)plVar8 & 0xfffffffffffffff8U)) &&
         (plVar23 = (longlong *)plVar8[-1],
         0x1f < (ulonglong)((longlong)plVar8 + (-8 - (longlong)plVar23)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(plVar23);
    }
  }
  return;
}


