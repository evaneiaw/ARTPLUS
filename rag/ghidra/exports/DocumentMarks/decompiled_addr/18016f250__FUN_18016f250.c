// DocumentMarks.dll 18016f250 FUN_18016f250
// signature: undefined FUN_18016f250(void)

undefined8 * FUN_18016f250(undefined8 *param_1,undefined8 *param_2)

{
  PDFPlusBearerBar *pPVar1;
  undefined8 uVar2;
  undefined8 local_20;
  undefined8 local_18;
  
  uVar2 = 0;
  pPVar1 = (PDFPlusBearerBar *)FUN_1802d6b50(0x790);
  if (pPVar1 != (PDFPlusBearerBar *)0x0) {
    local_20 = *param_2;
    local_18 = param_2[1];
    *param_2 = 0;
    param_2[1] = 0;
    uVar2 = DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar(pPVar1,&local_20);
  }
  *param_1 = uVar2;
  return param_1;
}


