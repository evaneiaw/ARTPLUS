// DocumentMarks.dll 18001f160 DocumentMarks::BearerBar::DumpInfo
// signature: pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_> DumpInfo(BearerBar * this)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* public: virtual struct std::pair<class std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >,class std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> > > __cdecl DocumentMarks::BearerBar::DumpInfo(void)const __ptr64 */

void __thiscall DocumentMarks::BearerBar::DumpInfo(BearerBar *this)

{
  uint uVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  basic_ostream<char,std::char_traits<char>_> *pbVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar6;
  undefined8 uVar7;
  longlong in_RDX;
  undefined8 ****ppppuVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  undefined1 auStack_1f8 [32];
  undefined4 local_1d8;
  basic_ostream<char,std::char_traits<char>_> abStack_1cc [4];
  undefined *local_1c8;
  undefined **local_1c0;
  basic_ostream<char,std::char_traits<char>_> local_1b8 [96];
  undefined8 local_158;
  undefined4 local_150;
  basic_ios<char,std::char_traits<char>_> local_140 [104];
  undefined1 local_d8;
  undefined7 uStack_d7;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  undefined1 local_b8 [32];
  undefined8 ****local_98 [2];
  undefined8 local_88;
  ulonglong local_80;
  ulonglong local_78;
  
                    /* 0x1f160  988
                       ?DumpInfo@BearerBar@DocumentMarks@@UEBA?AU?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@XZ
                        */
  local_78 = DAT_180418e00 ^ (ulonglong)auStack_1f8;
  local_1d8 = 0;
  DynamicObject::DumpInfo((DynamicObject *)this);
  local_1c8 = &DAT_180305168;
  std::basic_ios<char,std::char_traits<char>_>::basic_ios<char,std::char_traits<char>_>(local_140);
  local_1d8 = 2;
  std::basic_ostream<char,std::char_traits<char>_>::basic_ostream<char,std::char_traits<char>_>
            ((basic_ostream<char,std::char_traits<char>_> *)&local_1c8,
             (basic_streambuf<char,std::char_traits<char>_> *)&local_1c0,false);
  *(undefined ***)(local_1b8 + (longlong)*(int *)(local_1c8 + 4) + -0x10) =
       std::basic_ostringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  *(int *)(local_1b8 + (longlong)*(int *)(local_1c8 + 4) + -0x14) = *(int *)(local_1c8 + 4) + -0x88;
  std::basic_streambuf<char,std::char_traits<char>_>::basic_streambuf<char,std::char_traits<char>_>
            ((basic_streambuf<char,std::char_traits<char>_> *)&local_1c0);
  local_1c0 = std::basic_stringbuf<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  local_158 = 0;
  local_150 = 4;
  dVar2 = (*(double *)(this + 0x698) * DAT_180305518) / DAT_180305520;
  dVar3 = (*(double *)(this + 0x6a0) * DAT_180305518) / DAT_180305520;
  dVar4 = (*(double *)(this + 0x6a8) * DAT_180305518) / DAT_180305520;
  uVar1 = *(uint *)(this + 0x6b0);
  FUN_18001b3e0(&local_1c8,"BearerBar(");
  pbVar5 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(&local_1c8,"width=");
  pbVar6 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar5,dVar2);
  FUN_18001b3e0(pbVar6,&DAT_18030547c);
  pbVar5 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(&local_1c8,", extend=");
  pbVar6 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar5,dVar3);
  FUN_18001b3e0(pbVar6,&DAT_18030547c);
  pbVar5 = (basic_ostream<char,std::char_traits<char>_> *)FUN_18001b3e0(&local_1c8,", offset=");
  pbVar6 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar5,dVar4);
  FUN_18001b3e0(pbVar6,&DAT_18030547c);
  puVar10 = &DAT_1803050d0;
  puVar12 = &DAT_1803050d0;
  if ((uVar1 & 8) != 0) {
    puVar12 = &DAT_1803054a4;
  }
  puVar11 = &DAT_1803050d0;
  if ((uVar1 & 4) != 0) {
    puVar11 = &DAT_1803054a8;
  }
  puVar9 = &DAT_1803050d0;
  if ((uVar1 & 2) != 0) {
    puVar9 = &DAT_1803054ac;
  }
  if ((uVar1 & 1) != 0) {
    puVar10 = &DAT_1803054b0;
  }
  uVar7 = FUN_18001b3e0(&local_1c8,", location=");
  uVar7 = FUN_18001b3e0(uVar7,puVar10);
  uVar7 = FUN_18001b3e0(uVar7,puVar9);
  uVar7 = FUN_18001b3e0(uVar7,puVar11);
  uVar7 = FUN_18001b3e0(uVar7,puVar12);
  FUN_18001b3e0(uVar7,&DAT_1803050d4);
  FUN_18001da70(&local_1c8,10);
  ppppuVar8 = local_98;
  if (0xf < local_80) {
    ppppuVar8 = local_98[0];
  }
  FUN_18001b810(&local_1c8,ppppuVar8,local_88);
  uVar7 = FUN_180020730(&local_1c0,&local_d8);
  FUN_180011ca0(uVar7,local_b8);
  *(ulonglong *)(in_RDX + 0x20) = CONCAT71(uStack_d7,local_d8);
  *(undefined8 *)(in_RDX + 0x28) = uStack_d0;
  *(undefined4 *)(in_RDX + 0x30) = (undefined4)local_c8;
  *(undefined4 *)(in_RDX + 0x34) = local_c8._4_4_;
  *(undefined4 *)(in_RDX + 0x38) = (undefined4)uStack_c0;
  *(undefined4 *)(in_RDX + 0x3c) = uStack_c0._4_4_;
  local_c8 = PTR_180304c20;
  uStack_c0 = _UNK_180304c28;
  local_d8 = 0;
  *(undefined ***)(local_1b8 + (longlong)*(int *)(local_1c8 + 4) + -0x10) =
       std::basic_ostringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  *(int *)(local_1b8 + (longlong)*(int *)(local_1c8 + 4) + -0x14) = *(int *)(local_1c8 + 4) + -0x88;
  local_1c0 = std::basic_stringbuf<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  FUN_18001f5a0(&local_1c0);
  std::basic_streambuf<char,std::char_traits<char>_>::~basic_streambuf<char,std::char_traits<char>_>
            ((basic_streambuf<char,std::char_traits<char>_> *)&local_1c0);
  std::basic_ostream<char,std::char_traits<char>_>::~basic_ostream<char,std::char_traits<char>_>
            (local_1b8);
  std::basic_ios<char,std::char_traits<char>_>::~basic_ios<char,std::char_traits<char>_>(local_140);
  FUN_18001e5b0(local_b8);
  return;
}


