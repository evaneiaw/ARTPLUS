// DocumentMarks.dll 180130a20 FUN_180130a20
// signature: undefined FUN_180130a20(void)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_180130a20(undefined8 *param_1,longlong *param_2)

{
  int *piVar1;
  longlong *plVar2;
  int iVar3;
  longlong *plVar4;
  ErrorType EVar5;
  Severity SVar6;
  longlong lVar7;
  vector<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
  *pvVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  void *_Memory;
  undefined8 *puVar11;
  undefined8 *puVar12;
  ulonglong uVar13;
  ulonglong uVar14;
  undefined1 auStackY_a8 [32];
  void *local_60;
  undefined8 uStack_58;
  undefined8 local_50;
  ulonglong local_48;
  ulonglong local_40;
  
  local_40 = DAT_180418e00 ^ (ulonglong)auStackY_a8;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  uVar13 = param_2[1] - *param_2 >> 4;
  puVar11 = (undefined8 *)0x0;
  puVar12 = (undefined8 *)0x0;
  if (uVar13 != 0) {
    if (0xfffffffffffffff < uVar13) {
                    /* WARNING: Subroutine does not return */
      FUN_1800193a0();
    }
    uVar14 = uVar13 * 0x10;
    if (uVar14 != 0) {
      if (uVar14 < 0x1000) {
        puVar11 = (undefined8 *)FUN_1802d6b50(uVar14);
      }
      else {
        if (uVar14 + 0x27 <= uVar14) {
                    /* WARNING: Subroutine does not return */
          FUN_180019130();
        }
        lVar7 = FUN_1802d6b50();
        if (lVar7 == 0) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        puVar11 = (undefined8 *)(lVar7 + 0x27U & 0xffffffffffffffe0);
        puVar11[-1] = lVar7;
      }
    }
    *param_1 = puVar11;
    param_1[1] = puVar11;
    param_1[2] = puVar11 + uVar13 * 2;
    puVar9 = (undefined8 *)param_2[1];
    puVar10 = (undefined8 *)*param_2;
    puVar12 = puVar11;
    if (puVar10 != puVar9) {
      do {
        *puVar11 = 0;
        puVar11[1] = 0;
        if (puVar10[1] != 0) {
          LOCK();
          piVar1 = (int *)(puVar10[1] + 8);
          *piVar1 = *piVar1 + 1;
          UNLOCK();
        }
        *puVar11 = *puVar10;
        puVar11[1] = puVar10[1];
        puVar12 = puVar11 + 2;
        puVar10 = puVar10 + 2;
        puVar11 = puVar12;
      } while (puVar10 != puVar9);
      puVar11 = (undefined8 *)*param_1;
    }
    param_1[1] = puVar12;
  }
  do {
    if (puVar11 == puVar12) {
      return param_1;
    }
    EVar5 = DocumentMarks::MarkActionError::GetErrorType((MarkActionError *)*puVar11);
    if (EVar5 == 0x33) {
      SVar6 = ArtSys::Core::Error::GetSeverity((Error *)*puVar11);
      pvVar8 = DocumentMarks::MarkError::GetParameters((MarkError *)*puVar11);
      puVar9 = (undefined8 *)FUN_1802d6b50(0x90);
      if (puVar9 == (undefined8 *)0x0) {
        puVar9 = (undefined8 *)0x0;
      }
      else {
        *puVar9 = 0;
        puVar9[1] = 0;
        *(undefined4 *)(puVar9 + 1) = 1;
        *(undefined4 *)((longlong)puVar9 + 0xc) = 1;
        *puVar9 = std::_Ref_count_obj2<DocumentMarks::MarkError>::vftable;
        uStack_58 = 0;
        local_50 = 0;
        local_48 = 0xf;
        local_60 = (void *)0x0;
        DocumentMarks::MarkError::MarkError
                  ((MarkError *)(puVar9 + 2),0x34,pvVar8,SVar6,0,
                   (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_60);
        if (0xf < local_48) {
          _Memory = local_60;
          if ((0xfff < local_48 + 1) &&
             (_Memory = *(void **)((longlong)local_60 + -8),
             0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          free(_Memory);
        }
      }
      *puVar11 = puVar9 + 2;
      plVar4 = (longlong *)puVar11[1];
      puVar11[1] = puVar9;
      if (plVar4 != (longlong *)0x0) {
        LOCK();
        plVar2 = plVar4 + 1;
        lVar7 = *plVar2;
        *(int *)plVar2 = (int)*plVar2 + -1;
        UNLOCK();
        if ((int)lVar7 == 1) {
          (**(code **)*plVar4)(plVar4);
          LOCK();
          piVar1 = (int *)((longlong)plVar4 + 0xc);
          iVar3 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar3 == 1) {
            (**(code **)(*plVar4 + 8))(plVar4);
          }
        }
      }
    }
    puVar11 = puVar11 + 2;
  } while( true );
}


