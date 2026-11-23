// DocumentMarks.dll 18012f730 FUN_18012f730
// signature: undefined FUN_18012f730(void)

undefined4 * FUN_18012f730(longlong *param_1,void *param_2,undefined4 *param_3)

{
  ulonglong uVar1;
  undefined4 *puVar2;
  longlong lVar3;
  void *pvVar4;
  longlong lVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  undefined4 *_Dst;
  void *_Memory;
  undefined4 *_Dst_00;
  size_t _Size;
  
  lVar3 = *param_1;
  lVar5 = param_1[1] - lVar3 >> 2;
  if (lVar5 == 0x3fffffffffffffff) {
                    /* WARNING: Subroutine does not return */
    FUN_1800193a0();
  }
  uVar1 = lVar5 + 1;
  uVar6 = param_1[2] - lVar3 >> 2;
  if (0x3fffffffffffffff - (uVar6 >> 1) < uVar6) {
LAB_18012f8b4:
                    /* WARNING: Subroutine does not return */
    FUN_180019130();
  }
  uVar6 = (uVar6 >> 1) + uVar6;
  uVar7 = uVar1;
  if (uVar1 <= uVar6) {
    uVar7 = uVar6;
  }
  if (0x3fffffffffffffff < uVar7) goto LAB_18012f8b4;
  uVar6 = uVar7 * 4;
  if (uVar6 == 0) {
    _Dst_00 = (undefined4 *)0x0;
  }
  else if (uVar6 < 0x1000) {
    _Dst_00 = (undefined4 *)FUN_1802d6b50(uVar6);
  }
  else {
    if (uVar6 + 0x27 <= uVar6) goto LAB_18012f8b4;
    lVar5 = FUN_1802d6b50();
    if (lVar5 == 0) goto LAB_18012f8ad;
    _Dst_00 = (undefined4 *)(lVar5 + 0x27U & 0xffffffffffffffe0);
    *(longlong *)(_Dst_00 + -2) = lVar5;
  }
  puVar2 = _Dst_00 + ((longlong)param_2 - lVar3 >> 2);
  *puVar2 = *param_3;
  pvVar4 = (void *)*param_1;
  if (param_2 == (void *)param_1[1]) {
    _Size = param_1[1] - (longlong)pvVar4;
    _Dst = _Dst_00;
    param_2 = pvVar4;
  }
  else {
    memmove(_Dst_00,pvVar4,(longlong)param_2 - (longlong)pvVar4);
    _Dst = puVar2 + 1;
    _Size = param_1[1] - (longlong)param_2;
  }
  memmove(_Dst,param_2,_Size);
  pvVar4 = (void *)*param_1;
  if (pvVar4 != (void *)0x0) {
    _Memory = pvVar4;
    if ((0xfff < (param_1[2] - (longlong)pvVar4 & 0xfffffffffffffffcU)) &&
       (_Memory = *(void **)((longlong)pvVar4 + -8),
       0x1f < (ulonglong)((longlong)pvVar4 + (-8 - (longlong)_Memory)))) {
LAB_18012f8ad:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(_Memory);
  }
  *param_1 = (longlong)_Dst_00;
  param_1[1] = (longlong)(_Dst_00 + uVar1);
  param_1[2] = (longlong)(_Dst_00 + uVar7);
  return puVar2;
}


