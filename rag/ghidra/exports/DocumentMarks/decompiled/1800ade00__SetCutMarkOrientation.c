// 1800ade00 SetCutMarkOrientation

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkOrientation(class DocumentMarks::PDFPlusCutMark &
   __ptr64,enum DocumentMarks::PDFPlusCutMark::Orientation) */

void __cdecl DocumentMarks::SetCutMarkOrientation(PDFPlusCutMark *param_1,Orientation param_2)

{
  undefined1 auStack_d8 [32];
  Orientation local_b8 [2];
  code *local_b0;
  undefined4 uStack_a8;
  uint uStack_a4;
  undefined **local_98;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined ***local_60;
  undefined **local_58;
  code *local_50;
  longlong lStack_48;
  undefined ***local_20;
  ulonglong local_18;
  
                    /* 0xade00  1513
                       ?SetCutMarkOrientation@DocumentMarks@@YAXAEAVPDFPlusCutMark@1@W4Orientation@21@@Z
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_d8;
  local_58 = std::
             _Func_impl_no_alloc<enum_DocumentMarks::PDFPlusCutMark::Orientation_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,DocumentMarks::PDFPlusCutMark::Orientation,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_48 = (ulonglong)uStack_a4 << 0x20;
  local_50 = PDFPlusCutMark::GetOrientation;
  local_20 = &local_58;
  local_b0 = PDFPlusCutMark::SetOrientation;
  uStack_a8 = 0;
  local_98 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(DocumentMarks::PDFPlusCutMark::Orientation)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,DocumentMarks::PDFPlusCutMark::Orientation_const&___ptr64>
             ::vftable;
  local_90 = 0x8013d230;
  uStack_8c = 1;
  uStack_88 = 0;
  local_60 = &local_98;
  local_b8[0] = param_2;
  FUN_1800aa980(0x8013d230,local_b8,&local_98,&local_58);
  if (local_60 != (undefined ***)0x0) {
    (*(code *)(*local_60)[4])
              (local_60,CONCAT71((int7)((ulonglong)&local_98 >> 8),local_60 != &local_98));
    local_60 = (undefined ***)0x0;
  }
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])
              (local_20,CONCAT71((int7)((ulonglong)&local_58 >> 8),local_20 != &local_58));
  }
  return;
}


