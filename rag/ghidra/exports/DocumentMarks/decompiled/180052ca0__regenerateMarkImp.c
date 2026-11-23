// 180052ca0 regenerateMarkImp

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: virtual void __cdecl DocumentMarks::CutMark::regenerateMarkImp(void) __ptr64 */

void __thiscall DocumentMarks::CutMark::regenerateMarkImp(CutMark *this)

{
  longlong *plVar1;
  int *piVar2;
  ContentObject *this_00;
  CPoint *pCVar3;
  void *pvVar4;
  int iVar5;
  ContentObject *pCVar6;
  longlong lVar7;
  longlong *plVar8;
  Content *this_01;
  Document *pDVar9;
  basic_ostream<char,std::char_traits<char>_> *pbVar10;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar11;
  double *pdVar12;
  undefined8 uVar13;
  int iVar14;
  ulonglong uVar15;
  longlong *plVar16;
  ulonglong uVar17;
  void *_Memory;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  longlong local_res8;
  double local_res10;
  undefined1 local_1d8 [16];
  undefined1 local_1c8 [16];
  undefined8 local_1b8;
  void *local_1b0;
  longlong *plStack_1a8;
  longlong *local_1a0;
  undefined **local_198;
  longlong local_190;
  longlong lStack_188;
  undefined8 local_180;
  undefined1 local_178 [8];
  double local_170;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 uStack_158;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined8 local_140;
  char local_138;
  undefined1 local_130 [16];
  undefined1 local_110;
  undefined7 uStack_10f;
  CloneStrategy local_d8 [160];
  
                    /* 0x52ca0  2179  ?regenerateMarkImp@CutMark@DocumentMarks@@MEAAXXZ */
  pCVar6 = DynamicObject::getPositionRefObject((DynamicObject *)this);
  if (*(longlong *)(this + 0x2c0) != 0) {
    local_1b0 = (void *)0x0;
    plStack_1a8 = (longlong *)0x0;
    iVar14 = 0;
    plVar16 = (longlong *)0x0;
    local_1a0 = (longlong *)0x0;
    lVar7 = __RTDynamicCast(*(longlong *)(this + 0x2c0),0,
                            &ArtDoc::ContentObject::RTTI_Type_Descriptor,
                            &ArtDoc::Group::RTTI_Type_Descriptor,0);
    if (lVar7 != 0) {
      lVar7 = *(longlong *)(lVar7 + 0x2c0);
                    /* WARNING: Read-only address (ram,0x0001803082f0) is written */
      for (plStack_1a8 = (longlong *)0x0; (lVar7 != 0 && (plStack_1a8 != (longlong *)0x0));
          plStack_1a8 = plStack_1a8 + 1) {
        *plStack_1a8 = lVar7;
        lVar7 = *(longlong *)(lVar7 + 8);
      }
      for (; lVar7 != 0; lVar7 = *(longlong *)(lVar7 + 8)) {
        local_res8 = lVar7;
        if (plStack_1a8 == plVar16) {
          FUN_18001de60(&local_1b0,plStack_1a8,&local_res8);
          plVar16 = local_1a0;
        }
        else {
          *plStack_1a8 = lVar7;
          plStack_1a8 = plStack_1a8 + 1;
        }
      }
    }
    plVar1 = plStack_1a8;
    this_00 = (ContentObject *)plStack_1a8[-1];
    GetBoundingBoxForPositioning((ContentObject *)&local_160);
    if (local_138 == '\0') {
      uStack_148 = 0;
      uStack_144 = 0;
      local_110 = 1;
      local_1d8 = ZEXT816(0);
      uVar18 = (undefined4)CONCAT71(uStack_10f,1);
      uVar19 = (undefined4)((uint7)uStack_10f >> 0x18);
    }
    else {
      local_1d8._8_8_ = uStack_158;
      local_1d8._0_8_ = local_160;
      uVar18 = (undefined4)local_140;
      uVar19 = (undefined4)((ulonglong)local_140 >> 0x20);
    }
    local_1b8 = CONCAT44(uVar19,uVar18);
    iVar5 = GetMarksDebugLevel();
    local_res8 = CONCAT44(local_res8._4_4_,iVar5);
    FUN_1802a1ce0(local_178);
    local_168 = *(undefined8 *)(this + 0x698);
    local_198 = dm::MarkPositionVector::vftable;
    local_190 = 0;
    lStack_188 = 0;
    local_180 = 0;
    local_170 = ((double)CONCAT44(uStack_144,uStack_148) * 127.0) / 360000.0;
    plVar8 = (longlong *)
             __RTDynamicCast(pCVar6,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                             &GridInterface::RTTI_Type_Descriptor,0);
    if (plVar8 == (longlong *)0x0) {
      pdVar12 = (double *)DynamicObject::getPositionRefBBox((DynamicObject *)this);
      auVar21._0_8_ = *pdVar12 * 127.0;
      auVar21._8_8_ = pdVar12[1] * 127.0;
      local_130 = divpd(auVar21,_DAT_1803082f0);
      local_1d8._8_8_ = local_130._8_8_ + (pdVar12[3] * 127.0) / 360000.0;
      local_1d8._0_8_ = local_130._0_8_;
      local_res10 = (double)local_130._0_8_;
      local_1c8._8_8_ = local_130._8_8_;
      local_1c8._0_8_ = (double)local_130._0_8_ + (pdVar12[2] * 127.0) / 360000.0;
      FUN_1802a26c0(local_178,local_1d8,&local_198);
    }
    else {
      (**(code **)(*plVar8 + 8))(plVar8,local_d8);
      if (2 < iVar5) {
        FUN_18001b3e0(cout_exref,"gridParams:\n");
        FUN_18029f2e0(cout_exref,local_d8);
      }
      FUN_1802a2780(local_178,local_d8,&local_198);
    }
    uVar17 = 0;
    uVar15 = lStack_188 - local_190 >> 3;
    if (uVar15 != 0) {
      do {
        this_01 = ArtDoc::ContentObject::GetContent(this_00);
        pDVar9 = ArtDoc::Content::GetDocument(this_01);
        ArtDoc::CloneStrategy::CloneStrategy(local_d8,pDVar9,1);
        pCVar6 = (ContentObject *)(**(code **)(*(longlong *)this_00 + 8))(this_00,local_d8);
        pCVar6 = DocumentEdit::InsertNewObjectAfter(pCVar6,this_00,true);
        pCVar3 = *(CPoint **)(local_190 + uVar17 * 8);
        PlaceCutMarkSymbol(this,pCVar6,pCVar3,pCVar3 + 0x10);
        ArtDoc::CloneStrategy::~CloneStrategy(local_d8);
        uVar17 = uVar17 + 1;
      } while (uVar17 < uVar15);
    }
    if (2 < (int)local_res8) {
      FUN_18001b3e0(cout_exref," Cut Mark update at \n");
      uVar17 = lStack_188 - local_190 >> 3;
      uVar15 = 0;
      if (uVar17 != 0) {
        do {
          pdVar12 = *(double **)(local_190 + uVar15 * 8);
          pbVar10 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(cout_exref,&DAT_180308290);
          iVar14 = iVar14 + 1;
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar10,iVar14);
          pbVar10 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(pbVar11,&DAT_180306bac);
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar10,*pdVar12);
          pbVar10 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(pbVar11,&DAT_180307580);
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar10,pdVar12[1])
          ;
          pbVar10 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(pbVar11,"] -> [");
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar10,pdVar12[2])
          ;
          pbVar10 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_18001b3e0(pbVar11,&DAT_180307580);
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar10,pdVar12[3])
          ;
          FUN_18001b3e0(pbVar11,&DAT_18030828c);
          uVar15 = uVar15 + 1;
        } while (uVar15 < uVar17);
      }
      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_18003dae0);
      pdVar12 = (double *)DynamicObject::getPositionRefBBox((DynamicObject *)this);
      auVar20._0_8_ = *pdVar12 * 127.0;
      auVar20._8_8_ = pdVar12[1] * 127.0;
      local_1d8 = divpd(auVar20,_DAT_1803082f0);
      auVar22._0_8_ = pdVar12[2] * 127.0;
      auVar22._8_8_ = pdVar12[3] * 127.0;
      local_1c8 = divpd(auVar22,_DAT_1803082f0);
      local_1b8 = CONCAT71(local_1b8._1_7_,*(undefined1 *)(pdVar12 + 4));
      uVar13 = FUN_18001b3e0(cout_exref,"GridBbox mm:");
      uVar13 = FUN_18001dcb0(uVar13,local_1d8);
      FUN_18001b3e0(uVar13,&DAT_18030544c);
    }
    pvVar4 = local_1b0;
    uVar15 = 0;
    uVar17 = (longlong)plVar1 - (longlong)local_1b0 >> 3;
    if (uVar17 != 0) {
      do {
        DocumentEdit::ExtractObjectFromParent((ContentObject *)local_1d8);
        uVar13 = local_1d8._8_8_;
        if ((longlong *)local_1d8._8_8_ != (longlong *)0x0) {
          LOCK();
          plVar1 = (longlong *)(local_1d8._8_8_ + 8);
          lVar7 = *plVar1;
          *(int *)plVar1 = (int)*plVar1 + -1;
          UNLOCK();
          if ((int)lVar7 == 1) {
            (*(code *)**(undefined8 **)local_1d8._8_8_)(local_1d8._8_8_);
            LOCK();
            piVar2 = (int *)(uVar13 + 0xc);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 == 1) {
              (**(code **)(*(longlong *)uVar13 + 8))(uVar13);
            }
          }
        }
        uVar15 = uVar15 + 1;
      } while (uVar15 < uVar17);
    }
    DynamicObject::applyColor((DynamicObject *)this,(ContentObject *)this);
    FUN_18004a7b0(&local_198);
    FUN_1802a0fa0(local_178);
    if (pvVar4 != (void *)0x0) {
      _Memory = pvVar4;
      if ((0xfff < ((longlong)plVar16 - (longlong)pvVar4 & 0xfffffffffffffff8U)) &&
         (_Memory = *(void **)((longlong)pvVar4 + -8),
         0x1f < (ulonglong)((longlong)pvVar4 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
  }
  return;
}


