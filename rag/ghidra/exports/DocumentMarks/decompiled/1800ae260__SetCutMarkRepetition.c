// 1800ae260 SetCutMarkRepetition

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetCutMarkRepetition(class DocumentMarks::PDFPlusCutMark &
   __ptr64,enum DocumentMarks::PDFPlusCutMark::Repetition) */

void __cdecl DocumentMarks::SetCutMarkRepetition(PDFPlusCutMark *param_1,Repetition param_2)

{
  undefined1 auStack_d8 [32];
  Repetition local_b8 [2];
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
  
                    /* 0xae260  1516
                       ?SetCutMarkRepetition@DocumentMarks@@YAXAEAVPDFPlusCutMark@1@W4Repetition@21@@Z
                        */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_d8;
  local_58 = std::
             _Func_impl_no_alloc<enum_DocumentMarks::PDFPlusCutMark::Repetition_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(void)const___ptr64,DocumentMarks::PDFPlusCutMark::Repetition,DocumentMarks::PDFPlusCutMark_const&___ptr64>
             ::vftable;
  lStack_48 = (ulonglong)uStack_a4 << 0x20;
  local_50 = PDFPlusCutMark::GetRepetition;
  local_20 = &local_58;
  local_b0 = PDFPlusCutMark::SetRepetition;
  uStack_a8 = 0;
  local_98 = std::
             _Func_impl_no_alloc<void_(__cdecl_DocumentMarks::PDFPlusCutMark::*)(DocumentMarks::PDFPlusCutMark::Repetition)___ptr64,void,DocumentMarks::PDFPlusCutMark&___ptr64,DocumentMarks::PDFPlusCutMark::Repetition_const&___ptr64>
             ::vftable;
  local_90 = 0x8013d2b0;
  uStack_8c = 1;
  uStack_88 = 0;
  local_60 = &local_98;
  local_b8[0] = param_2;
  FUN_1800aaae0(0x8013d2b0,local_b8,&local_98,&local_58);
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


