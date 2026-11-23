// DocumentMarks.dll 1800453f0 FUN_1800453f0
// signature: undefined FUN_1800453f0(void)

undefined8 * FUN_1800453f0(int param_1)

{
  char cVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 *local_48;
  undefined8 uStack_40;
  undefined8 *local_38;
  uint uStack_30;
  undefined4 uStack_2c;
  
  if ((*(int *)(*(longlong *)((longlong)ThreadLocalStoragePointer + (ulonglong)_tls_index * 8) + 4)
       < DAT_180488460) && (FUN_1802d7114(&DAT_180488460), DAT_180488460 == -1)) {
    DAT_180488450 = (undefined8 *)FUN_1802d6b50(0x48);
    *DAT_180488450 = DAT_180488450;
    DAT_180488450[1] = DAT_180488450;
    DAT_180488450[2] = DAT_180488450;
    *(undefined2 *)(DAT_180488450 + 3) = 0x101;
    atexit(FUN_1802f7010);
    _Init_thread_footer(&DAT_180488460);
  }
  puVar5 = DAT_180488450;
  if (DAT_180488458 == 0) {
    puVar3 = (undefined8 *)DAT_180488450[1];
    uStack_30 = 0;
    cVar1 = *(char *)((longlong)puVar3 + 0x19);
    local_38 = puVar3;
    puVar4 = DAT_180488450;
    while (puVar2 = puVar3, cVar1 == '\0') {
      if (-1 < *(int *)(puVar2 + 4)) {
        puVar3 = (undefined8 *)*puVar2;
        puVar4 = puVar2;
      }
      else {
        puVar3 = (undefined8 *)puVar2[2];
      }
      uStack_30 = (uint)(-1 < *(int *)(puVar2 + 4));
      cVar1 = *(char *)((longlong)puVar3 + 0x19);
      local_38 = puVar2;
    }
    if ((*(char *)((longlong)puVar4 + 0x19) != '\0') || (0 < *(int *)(puVar4 + 4))) {
      local_48 = &DAT_180488450;
      uStack_40 = 0;
      puVar3 = (undefined8 *)FUN_1802d6b50(0x48);
      *(undefined4 *)(puVar3 + 4) = 0;
      puVar3[5] = 0;
      puVar3[6] = 0;
      puVar3[7] = 0;
      puVar3[8] = 0xf;
      *(undefined1 *)(puVar3 + 5) = 0;
      *puVar3 = puVar5;
      puVar3[1] = puVar5;
      puVar3[2] = puVar5;
      *(undefined2 *)(puVar3 + 3) = 0;
      local_48 = local_38;
      uStack_40 = CONCAT44(uStack_2c,uStack_30);
      puVar4 = (undefined8 *)FUN_180018dc0(&DAT_180488450,&local_48,puVar3);
    }
    FUN_180019430(puVar4 + 5,"Media Box",9);
    puVar4 = DAT_180488450;
    puVar5 = (undefined8 *)DAT_180488450[1];
    uStack_30 = 0;
    cVar1 = *(char *)((longlong)puVar5 + 0x19);
    local_38 = puVar5;
    puVar3 = DAT_180488450;
    while (puVar2 = puVar5, cVar1 == '\0') {
      if (0 < *(int *)(puVar2 + 4)) {
        puVar5 = (undefined8 *)*puVar2;
        puVar3 = puVar2;
      }
      else {
        puVar5 = (undefined8 *)puVar2[2];
      }
      uStack_30 = (uint)(0 < *(int *)(puVar2 + 4));
      cVar1 = *(char *)((longlong)puVar5 + 0x19);
      local_38 = puVar2;
    }
    if ((*(char *)((longlong)puVar3 + 0x19) != '\0') || (1 < *(int *)(puVar3 + 4))) {
      if (DAT_180488458 == 0x38e38e38e38e38e) {
                    /* WARNING: Subroutine does not return */
        FUN_180019150();
      }
      local_48 = &DAT_180488450;
      uStack_40 = 0;
      puVar5 = (undefined8 *)FUN_1802d6b50(0x48);
      *(undefined4 *)(puVar5 + 4) = 1;
      puVar5[5] = 0;
      puVar5[6] = 0;
      puVar5[7] = 0;
      puVar5[8] = 0xf;
      *(undefined1 *)(puVar5 + 5) = 0;
      *puVar5 = puVar4;
      puVar5[1] = puVar4;
      puVar5[2] = puVar4;
      *(undefined2 *)(puVar5 + 3) = 0;
      local_48 = local_38;
      uStack_40 = CONCAT44(uStack_2c,uStack_30);
      puVar3 = (undefined8 *)FUN_180018dc0(&DAT_180488450,&local_48,puVar5);
    }
    FUN_180019430(puVar3 + 5,"Crop Box",8);
    puVar4 = DAT_180488450;
    puVar5 = (undefined8 *)DAT_180488450[1];
    uStack_30 = 0;
    cVar1 = *(char *)((longlong)puVar5 + 0x19);
    local_38 = puVar5;
    puVar3 = DAT_180488450;
    while (puVar2 = puVar5, cVar1 == '\0') {
      if (1 < *(int *)(puVar2 + 4)) {
        puVar5 = (undefined8 *)*puVar2;
        puVar3 = puVar2;
      }
      else {
        puVar5 = (undefined8 *)puVar2[2];
      }
      uStack_30 = (uint)(1 < *(int *)(puVar2 + 4));
      cVar1 = *(char *)((longlong)puVar5 + 0x19);
      local_38 = puVar2;
    }
    if ((*(char *)((longlong)puVar3 + 0x19) != '\0') || (2 < *(int *)(puVar3 + 4))) {
      if (DAT_180488458 == 0x38e38e38e38e38e) {
                    /* WARNING: Subroutine does not return */
        FUN_180019150();
      }
      local_48 = &DAT_180488450;
      uStack_40 = 0;
      puVar5 = (undefined8 *)FUN_1802d6b50(0x48);
      *(undefined4 *)(puVar5 + 4) = 2;
      puVar5[5] = 0;
      puVar5[6] = 0;
      puVar5[7] = 0;
      puVar5[8] = 0xf;
      *(undefined1 *)(puVar5 + 5) = 0;
      *puVar5 = puVar4;
      puVar5[1] = puVar4;
      puVar5[2] = puVar4;
      *(undefined2 *)(puVar5 + 3) = 0;
      local_48 = local_38;
      uStack_40 = CONCAT44(uStack_2c,uStack_30);
      puVar3 = (undefined8 *)FUN_180018dc0(&DAT_180488450,&local_48,puVar5);
    }
    FUN_180019430(puVar3 + 5,"Bleed Box",9);
    puVar4 = DAT_180488450;
    puVar5 = (undefined8 *)DAT_180488450[1];
    uStack_30 = 0;
    cVar1 = *(char *)((longlong)puVar5 + 0x19);
    local_38 = puVar5;
    puVar3 = DAT_180488450;
    while (puVar2 = puVar5, cVar1 == '\0') {
      if (2 < *(int *)(puVar2 + 4)) {
        puVar5 = (undefined8 *)*puVar2;
        puVar3 = puVar2;
      }
      else {
        puVar5 = (undefined8 *)puVar2[2];
      }
      uStack_30 = (uint)(2 < *(int *)(puVar2 + 4));
      cVar1 = *(char *)((longlong)puVar5 + 0x19);
      local_38 = puVar2;
    }
    if ((*(char *)((longlong)puVar3 + 0x19) != '\0') || (3 < *(int *)(puVar3 + 4))) {
      if (DAT_180488458 == 0x38e38e38e38e38e) {
                    /* WARNING: Subroutine does not return */
        FUN_180019150();
      }
      local_48 = &DAT_180488450;
      uStack_40 = 0;
      puVar5 = (undefined8 *)FUN_1802d6b50(0x48);
      *(undefined4 *)(puVar5 + 4) = 3;
      puVar5[5] = 0;
      puVar5[6] = 0;
      puVar5[7] = 0;
      puVar5[8] = 0xf;
      *(undefined1 *)(puVar5 + 5) = 0;
      *puVar5 = puVar4;
      puVar5[1] = puVar4;
      puVar5[2] = puVar4;
      *(undefined2 *)(puVar5 + 3) = 0;
      local_48 = local_38;
      uStack_40 = CONCAT44(uStack_2c,uStack_30);
      puVar3 = (undefined8 *)FUN_180018dc0(&DAT_180488450,&local_48,puVar5);
    }
    FUN_180019430(puVar3 + 5,"Trim Box",8);
    puVar4 = DAT_180488450;
    puVar5 = (undefined8 *)DAT_180488450[1];
    uStack_30 = 0;
    cVar1 = *(char *)((longlong)puVar5 + 0x19);
    local_38 = puVar5;
    puVar3 = DAT_180488450;
    while (puVar2 = puVar5, cVar1 == '\0') {
      if (3 < *(int *)(puVar2 + 4)) {
        puVar5 = (undefined8 *)*puVar2;
        puVar3 = puVar2;
      }
      else {
        puVar5 = (undefined8 *)puVar2[2];
      }
      uStack_30 = (uint)(3 < *(int *)(puVar2 + 4));
      cVar1 = *(char *)((longlong)puVar5 + 0x19);
      local_38 = puVar2;
    }
    if ((*(char *)((longlong)puVar3 + 0x19) != '\0') || (4 < *(int *)(puVar3 + 4))) {
      if (DAT_180488458 == 0x38e38e38e38e38e) {
                    /* WARNING: Subroutine does not return */
        FUN_180019150();
      }
      local_48 = &DAT_180488450;
      uStack_40 = 0;
      puVar5 = (undefined8 *)FUN_1802d6b50(0x48);
      *(undefined4 *)(puVar5 + 4) = 4;
      puVar5[5] = 0;
      puVar5[6] = 0;
      puVar5[7] = 0;
      puVar5[8] = 0xf;
      *(undefined1 *)(puVar5 + 5) = 0;
      *puVar5 = puVar4;
      puVar5[1] = puVar4;
      puVar5[2] = puVar4;
      *(undefined2 *)(puVar5 + 3) = 0;
      local_48 = local_38;
      uStack_40 = CONCAT44(uStack_2c,uStack_30);
      puVar3 = (undefined8 *)FUN_180018dc0(&DAT_180488450,&local_48,puVar5);
    }
    FUN_180019430(puVar3 + 5,"Art Box",7);
  }
  puVar4 = DAT_180488450;
  puVar5 = (undefined8 *)DAT_180488450[1];
  uStack_30 = 0;
  cVar1 = *(char *)((longlong)puVar5 + 0x19);
  local_38 = puVar5;
  puVar3 = DAT_180488450;
  while (puVar2 = puVar5, cVar1 == '\0') {
    if (param_1 <= *(int *)(puVar2 + 4)) {
      puVar5 = (undefined8 *)*puVar2;
      puVar3 = puVar2;
    }
    else {
      puVar5 = (undefined8 *)puVar2[2];
    }
    uStack_30 = (uint)(param_1 <= *(int *)(puVar2 + 4));
    cVar1 = *(char *)((longlong)puVar5 + 0x19);
    local_38 = puVar2;
  }
  if ((*(char *)((longlong)puVar3 + 0x19) != '\0') || (param_1 < *(int *)(puVar3 + 4))) {
    if (DAT_180488458 == 0x38e38e38e38e38e) {
                    /* WARNING: Subroutine does not return */
      FUN_180019150();
    }
    local_48 = &DAT_180488450;
    uStack_40 = 0;
    puVar5 = (undefined8 *)FUN_180049340(&DAT_180488450,1);
    *(int *)(puVar5 + 4) = param_1;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0;
    puVar5[8] = 0xf;
    *(undefined1 *)(puVar5 + 5) = 0;
    *puVar5 = puVar4;
    puVar5[1] = puVar4;
    puVar5[2] = puVar4;
    *(undefined2 *)(puVar5 + 3) = 0;
    local_48 = local_38;
    uStack_40 = CONCAT44(uStack_2c,uStack_30);
    puVar3 = (undefined8 *)FUN_180018dc0(&DAT_180488450,&local_48,puVar5);
  }
  return puVar3 + 5;
}


