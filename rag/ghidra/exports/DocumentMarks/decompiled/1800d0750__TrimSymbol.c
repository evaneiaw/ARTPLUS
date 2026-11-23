// 1800d0750 TrimSymbol

/* private: static void __cdecl DocumentMarks::GradationMark::TrimSymbol(class ArtDoc::ContentObject
   & __ptr64,bool,double) */

void __cdecl
DocumentMarks::GradationMark::TrimSymbol(ContentObject *param_1,bool param_2,double param_3)

{
  int *piVar1;
  longlong *plVar2;
  int iVar3;
  void *pvVar4;
  double dVar5;
  double dVar6;
  longlong lVar7;
  ulonglong uVar8;
  longlong *plVar9;
  ulonglong uVar10;
  void *_Memory;
  ulonglong uVar11;
  longlong *plVar12;
  bool bVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  longlong local_138;
  longlong *local_130;
  void *local_128;
  longlong *plStack_120;
  longlong *local_118;
  undefined1 local_108;
  double local_100;
  double dStack_f8;
  undefined8 local_f0;
  double dStack_e8;
  double local_d8;
  double dStack_d0;
  undefined8 local_c8;
  double dStack_c0;
  char local_b0;
  double local_a8;
  double dStack_a0;
  double local_98;
  undefined8 local_88;
  char local_80;
  undefined8 local_58;
  
                    /* 0xd0750  1717
                       ?TrimSymbol@GradationMark@DocumentMarks@@CAXAEAVContentObject@ArtDoc@@_NN@Z
                        */
  GetBoundingBoxForPositioning((ContentObject *)&local_d8);
  if (local_b0 == '\0') {
    local_d8 = 0.0;
    dStack_d0 = 0.0;
    local_c8 = 0;
    dStack_c0 = 0.0;
    local_108 = 1;
  }
  local_128 = (void *)0x0;
  plStack_120 = (longlong *)0x0;
  plVar12 = (longlong *)0x0;
  local_118 = (longlong *)0x0;
  uVar11 = 0;
  local_100 = local_d8;
  dStack_f8 = dStack_d0;
  local_f0 = local_c8;
  dStack_e8 = dStack_c0;
  lVar7 = __RTDynamicCast(param_1,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                          &ArtDoc::Group::RTTI_Type_Descriptor,0);
  dVar6 = dStack_e8;
  dVar5 = dStack_f8;
  plVar9 = plStack_120;
  if ((lVar7 != 0) && (lVar7 = *(longlong *)(lVar7 + 0x2c0), lVar7 != 0)) {
    do {
      uVar11 = uVar11 + 1;
      local_138 = lVar7;
      GetBoundingBoxForPositioning((ContentObject *)&local_a8);
      if (local_80 == '\0') {
        dVar14 = 0.0;
        dVar15 = 0.0;
        dVar16 = 0.0;
        local_58 = CONCAT71(local_58._1_7_,1);
      }
      else {
        dVar16 = local_98;
        local_58 = local_88;
        dVar14 = local_a8;
        dVar15 = dStack_a0;
      }
      if (param_2) {
        bVar13 = local_100 + param_3 < dVar16 + dVar14;
      }
      else {
        bVar13 = dVar15 < (dVar6 + dVar5) - param_3;
      }
      if (bVar13) {
        if (plVar9 == plVar12) {
          FUN_18001de60(&local_128,plVar9,&local_138);
          plVar9 = plStack_120;
          plVar12 = local_118;
        }
        else {
          *plVar9 = lVar7;
          plStack_120 = plVar9 + 1;
          plVar9 = plStack_120;
        }
      }
      lVar7 = *(longlong *)(lVar7 + 8);
    } while (lVar7 != 0);
  }
  pvVar4 = local_128;
  uVar8 = 0;
  uVar10 = (longlong)plVar9 - (longlong)local_128 >> 3;
  if (((uVar10 == 0) || (uVar11 != uVar10)) && (uVar11 != 0)) {
    if (uVar10 != 0) {
      do {
        DocumentEdit::ExtractObjectFromParent((ContentObject *)&local_138);
        plVar9 = local_130;
        if (local_130 != (longlong *)0x0) {
          LOCK();
          plVar2 = local_130 + 1;
          lVar7 = *plVar2;
          *(int *)plVar2 = (int)*plVar2 + -1;
          UNLOCK();
          if ((int)lVar7 == 1) {
            (**(code **)*local_130)(local_130);
            LOCK();
            piVar1 = (int *)((longlong)plVar9 + 0xc);
            iVar3 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar3 == 1) {
              (**(code **)(*plVar9 + 8))(plVar9);
            }
          }
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar10);
    }
  }
  else {
    DocumentEdit::ExtractObjectFromParent((ContentObject *)&local_138);
    if (local_130 != (longlong *)0x0) {
      LOCK();
      plVar9 = local_130 + 1;
      lVar7 = *plVar9;
      *(int *)plVar9 = (int)*plVar9 + -1;
      UNLOCK();
      if ((int)lVar7 == 1) {
        (**(code **)*local_130)(local_130);
        LOCK();
        piVar1 = (int *)((longlong)local_130 + 0xc);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 == 1) {
          (**(code **)(*local_130 + 8))(local_130);
        }
      }
    }
  }
  if (pvVar4 != (void *)0x0) {
    _Memory = pvVar4;
    if ((0xfff < ((longlong)plVar12 - (longlong)pvVar4 & 0xfffffffffffffff8U)) &&
       (_Memory = *(void **)((longlong)pvVar4 + -8),
       0x1f < (ulonglong)((longlong)pvVar4 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
  }
  return;
}


