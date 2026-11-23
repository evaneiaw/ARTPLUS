// DocumentMarks.dll 180060920 FUN_180060920
// signature: undefined FUN_180060920(void)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_180060920(void)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  char *_Memory;
  void *pvVar4;
  undefined1 auStack_558 [32];
  undefined1 local_538;
  code *local_530;
  void *local_528;
  undefined8 uStack_520;
  undefined *local_518;
  ulonglong uStack_510;
  undefined8 local_508;
  undefined8 uStack_500;
  undefined *local_4f8;
  ulonglong uStack_4f0;
  undefined8 *local_4d0;
  undefined8 local_4c8;
  undefined8 uStack_4c0;
  undefined *local_4b8;
  ulonglong uStack_4b0;
  Field local_4a8 [128];
  undefined **local_428;
  code *local_420;
  undefined ***local_3f0;
  undefined **local_3e8;
  code *local_3e0;
  undefined ***local_3b0;
  undefined **local_3a8;
  code *local_3a0;
  undefined ***local_370;
  undefined **local_368;
  code *local_360;
  undefined ***local_330;
  undefined **local_328;
  code *local_320;
  undefined ***local_2f0;
  undefined **local_2e8;
  code *local_2e0;
  undefined ***local_2b0;
  undefined **local_2a8;
  code *local_2a0;
  undefined ***local_270;
  undefined **local_268 [7];
  undefined ***local_230;
  undefined **local_228 [7];
  undefined ***local_1f0;
  undefined **local_1e8 [7];
  undefined ***local_1b0;
  undefined **local_1a8 [7];
  undefined ***local_170;
  undefined **local_168 [7];
  undefined ***local_130;
  undefined **local_128 [7];
  undefined ***local_f0;
  undefined **local_e8 [7];
  undefined ***local_b0;
  undefined **local_a8 [7];
  undefined ***local_70;
  undefined **local_68 [7];
  undefined ***local_30;
  ulonglong local_28;
  
  local_28 = DAT_180418e00 ^ (ulonglong)auStack_558;
  if (*(int *)(*(longlong *)((longlong)ThreadLocalStoragePointer + (ulonglong)_tls_index * 8) + 4) <
      DAT_180488930) {
    FUN_1802d7114(&DAT_180488930);
    if (DAT_180488930 == -1) {
      FUN_18005fd70(&DAT_1804888b0);
      atexit(FUN_1802f7a60);
      _Init_thread_footer(&DAT_180488930);
    }
  }
  if (DAT_180488934 == '\0') {
    DAT_180488934 = '\x01';
    local_4b8 = (undefined *)_DAT_1803091b0;
    uStack_4b0 = _UNK_1803091b8;
    local_4c8 = (void *)s_File_Name_18030a450._0_8_;
    uStack_4c0 = (ulonglong)(byte)s_File_Name_18030a450[8];
    uStack_520 = 0;
    local_518 = (undefined *)_DAT_1803056e0;
    uStack_510 = _UNK_1803056e8;
    local_528 = (void *)0x4e46;
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_4c8);
    if (0xf < uStack_510) {
      pvVar4 = local_528;
      if ((0xfff < uStack_510 + 1) &&
         (pvVar4 = *(void **)((longlong)local_528 + -8),
         0x1f < (ulonglong)((longlong)local_528 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    uVar2 = _UNK_180304c28;
    puVar1 = PTR_180304c20;
    local_518 = PTR_180304c20;
    uStack_510 = _UNK_180304c28;
    local_528 = (void *)((ulonglong)local_528 & 0xffffffffffffff00);
    if (0xf < uStack_4b0) {
      pvVar4 = local_4c8;
      if ((0xfff < uStack_4b0 + 1) &&
         (pvVar4 = *(void **)((longlong)local_4c8 + -8),
         0x1f < (ulonglong)((longlong)local_4c8 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    local_4b8 = puVar1;
    uStack_4b0 = uVar2;
    local_4c8 = (void *)((ulonglong)local_4c8 & 0xffffffffffffff00);
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)_DAT_180308bb0;
    uStack_4f0 = _UNK_180308bb8;
    local_508 = (undefined **)(ulonglong)CONCAT24(DAT_18030a460,DAT_18030a45c);
    ArtDoc::Field::AddFormat
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508);
    if (0xf < uStack_4f0) {
      pvVar4 = local_508;
      if ((0xfff < uStack_4f0 + 1) &&
         (pvVar4 = *(void **)((longlong)local_508 + -8),
         0x1f < (ulonglong)((longlong)local_508 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    local_4f8 = (undefined *)_DAT_180308000;
    uStack_4f0 = _UNK_180308008;
    local_508 = (undefined **)s__name__ext__180309228._0_8_;
    uStack_500 = (code *)(ulonglong)
                         CONCAT12(s__name__ext__180309228[10],s__name__ext__180309228._8_2_);
    ArtDoc::Field::AddFormat
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508);
    if (0xf < uStack_4f0) {
      pvVar4 = local_508;
      if ((0xfff < uStack_4f0 + 1) &&
         (pvVar4 = *(void **)((longlong)local_508 + -8),
         0x1f < (ulonglong)((longlong)local_508 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    local_508 = (undefined **)0x0;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)0x0;
    uStack_4f0 = 0;
    local_508 = (undefined **)FUN_1802d6b50(0x20);
    uVar3 = s__path__name__ext__18030a468._8_8_;
    local_4f8 = (undefined *)_DAT_18030a950;
    uStack_4f0 = _UNK_18030a958;
    *local_508 = (undefined *)s__path__name__ext__18030a468._0_8_;
    *(undefined8 *)((longlong)local_508 + 8) = uVar3;
    *(char *)((longlong)local_508 + 0x10) = s__path__name__ext__18030a468[0x10];
    *(char *)((longlong)local_508 + 0x11) = '\0';
    ArtDoc::Field::AddFormat
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508);
    if (0xf < uStack_4f0) {
      _Memory = (char *)local_508;
      if ((0xfff < uStack_4f0 + 1) &&
         (_Memory = *(char **)((longlong)local_508 + -8),
         (char *)0x1f < (char *)((longlong)local_508 + (-8 - (longlong)_Memory)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(_Memory);
    }
    ArtDoc::Field::AddVariableInformation(local_4a8,"path","File path");
    ArtDoc::Field::AddVariableInformation(local_4a8,"name","File name");
    ArtDoc::Field::AddVariableInformation(local_4a8,"ext","File extension");
    ArtDoc::Field::SetSupportsCustomFormats(local_4a8,true);
    local_428 = std::
                _Func_impl_no_alloc<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_(__cdecl*)(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64),std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64>
                ::vftable;
    local_420 = FUN_1800621c0;
    local_3f0 = &local_428;
    ArtDoc::Category::AddFormattedField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64)>
                *)&local_428);
    if (local_3f0 != (undefined ***)0x0) {
      (*(code *)(*local_3f0)[4])
                (local_3f0,CONCAT71((int7)((ulonglong)&local_428 >> 8),local_3f0 != &local_428));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_518 = (undefined *)_DAT_180308bc0;
    uStack_510 = _UNK_180308bc8;
    local_528 = (void *)s_File_Location_18030a490._0_8_;
    uStack_520 = (ulonglong)CONCAT14(s_File_Location_18030a490[0xc],s_File_Location_18030a490._8_4_)
    ;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)_DAT_1803056e0;
    uStack_4f0 = _UNK_1803056e8;
    local_508 = (void *)0x4c46;
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4f0) {
      pvVar4 = local_508;
      if ((0xfff < uStack_4f0 + 1) &&
         (pvVar4 = *(void **)((longlong)local_508 + -8),
         0x1f < (ulonglong)((longlong)local_508 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    local_4f8 = puVar1;
    uStack_4f0 = uVar2;
    local_508 = (undefined **)((ulonglong)local_508 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      pvVar4 = local_528;
      if ((0xfff < uStack_510 + 1) &&
         (pvVar4 = *(void **)((longlong)local_528 + -8),
         0x1f < (ulonglong)((longlong)local_528 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    local_268[0] = std::
                   _Func_impl_no_alloc<`class_ArtDoc::Category&___ptr64___cdecl_DocumentMarks::GetDocumentCategory(void)'::`7'::<lambda_1>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,int>
                   ::vftable;
    local_230 = local_268;
    ArtDoc::Category::AddBasicField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int)>
                *)local_268);
    if (local_230 != (undefined ***)0x0) {
      (*(code *)(*local_230)[4])
                (local_230,CONCAT71((int7)((ulonglong)local_268 >> 8),local_230 != local_268));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_518 = (undefined *)_DAT_1803091b0;
    uStack_510 = _UNK_1803091b8;
    local_528 = (void *)s_Full_Path_18030a4a0._0_8_;
    uStack_520 = (ulonglong)(byte)s_Full_Path_18030a4a0[8];
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)_DAT_1803056e0;
    uStack_4f0 = _UNK_1803056e8;
    local_508 = (void *)0x5046;
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4f0) {
      pvVar4 = local_508;
      if ((0xfff < uStack_4f0 + 1) &&
         (pvVar4 = *(void **)((longlong)local_508 + -8),
         0x1f < (ulonglong)((longlong)local_508 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    local_4f8 = puVar1;
    uStack_4f0 = uVar2;
    local_508 = (undefined **)((ulonglong)local_508 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      pvVar4 = local_528;
      if ((0xfff < uStack_510 + 1) &&
         (pvVar4 = *(void **)((longlong)local_528 + -8),
         0x1f < (ulonglong)((longlong)local_528 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    local_228[0] = std::
                   _Func_impl_no_alloc<`class_ArtDoc::Category&___ptr64___cdecl_DocumentMarks::GetDocumentCategory(void)'::`8'::<lambda_2>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,int>
                   ::vftable;
    local_1f0 = local_228;
    ArtDoc::Category::AddBasicField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int)>
                *)local_228);
    if (local_1f0 != (undefined ***)0x0) {
      (*(code *)(*local_1f0)[4])
                (local_1f0,CONCAT71((int7)((ulonglong)local_228 >> 8),local_1f0 != local_228));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_518 = (undefined *)_DAT_1803096c0;
    uStack_510 = _UNK_1803096c8;
    local_528 = (void *)s_Font_Names_18030a4b0._0_8_;
    uStack_520 = (ulonglong)(ushort)s_Font_Names_18030a4b0._8_2_;
    uStack_4c0 = 0;
    local_4b8 = (undefined *)_DAT_18030a940;
    uStack_4b0 = _UNK_18030a948;
    local_4c8 = (void *)(ulonglong)CONCAT14(s_FONTS_18030a42c[4],s_FONTS_18030a42c._0_4_);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_4c8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4b0) {
      pvVar4 = local_4c8;
      if ((0xfff < uStack_4b0 + 1) &&
         (pvVar4 = *(void **)((longlong)local_4c8 + -8),
         0x1f < (ulonglong)((longlong)local_4c8 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    local_4b8 = puVar1;
    uStack_4b0 = uVar2;
    local_4c8 = (void *)((ulonglong)local_4c8 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      pvVar4 = local_528;
      if ((0xfff < uStack_510 + 1) &&
         (pvVar4 = *(void **)((longlong)local_528 + -8),
         0x1f < (ulonglong)((longlong)local_528 + (-8 - (longlong)pvVar4)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pvVar4);
    }
    local_518 = puVar1;
    uStack_510 = uVar2;
    local_528 = (void *)((ulonglong)local_528 & 0xffffffffffffff00);
    ArtDoc::AddIndexFormats(local_4a8,5);
    ArtDoc::Field::AddVariableInformation(local_4a8,"1","First font");
    ArtDoc::Field::AddVariableInformation(local_4a8,"2","Second font");
    ArtDoc::Field::AddVariableInformation(local_4a8,"3","Third font");
    ArtDoc::Field::AddVariableInformation(local_4a8,"4","Fourth font");
    ArtDoc::Field::AddVariableInformation(local_4a8,"5","Fifth font");
    local_3e8 = std::
                _Func_impl_no_alloc<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_(__cdecl*)(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64),std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64>
                ::vftable;
    local_3e0 = FUN_180062890;
    local_3b0 = &local_3e8;
    ArtDoc::Category::AddListField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64)>
                *)&local_3e8);
    if (local_3b0 != (undefined ***)0x0) {
      (*(code *)(*local_3b0)[4])
                (local_3b0,CONCAT71((int7)((ulonglong)&local_3e8 >> 8),local_3b0 != &local_3e8));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_4f8 = (undefined *)_DAT_1803091a0;
    uStack_4f0 = _UNK_1803091a8;
    local_508 = (undefined **)0x4449207472616d53;
    uStack_500 = (code *)0x0;
    uStack_4c0 = 0;
    local_4b8 = (undefined *)_DAT_1803096a0;
    uStack_4b0 = _UNK_1803096a8;
    local_4c8 = (void *)(ulonglong)(uint3)DAT_18030a444;
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_4c8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508);
    if (0xf < uStack_4b0) {
      FUN_1800187d0(&local_4c8);
    }
    local_4b8 = puVar1;
    uStack_4b0 = uVar2;
    local_4c8 = (void *)((ulonglong)local_4c8 & 0xffffffffffffff00);
    if (0xf < uStack_4f0) {
      FUN_1800187d0(&local_508);
    }
    local_3a8 = std::
                _Func_impl_no_alloc<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_(__cdecl*)(int),std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,int>
                ::vftable;
    local_3a0 = FUN_1800643a0;
    local_370 = &local_3a8;
    ArtDoc::Category::AddBasicField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int)>
                *)&local_3a8);
    if (local_370 != (undefined ***)0x0) {
      (*(code *)(*local_370)[4])
                (local_370,CONCAT71((int7)((ulonglong)&local_3a8 >> 8),local_370 != &local_3a8));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_4b8 = (undefined *)_DAT_180308000;
    uStack_4b0 = _UNK_180308008;
    local_4c8._0_1_ = s_Layer_Names_18030a510[0];
    local_4c8._1_1_ = s_Layer_Names_18030a510[1];
    local_4c8._2_1_ = s_Layer_Names_18030a510[2];
    local_4c8._3_1_ = s_Layer_Names_18030a510[3];
    local_4c8._4_1_ = s_Layer_Names_18030a510[4];
    local_4c8._5_1_ = s_Layer_Names_18030a510[5];
    local_4c8._6_1_ = s_Layer_Names_18030a510[6];
    local_4c8._7_1_ = s_Layer_Names_18030a510[7];
    uStack_4c0 = (ulonglong)CONCAT12(s_Layer_Names_18030a510[10],s_Layer_Names_18030a510._8_2_);
    uStack_520 = 0;
    local_518 = (undefined *)_DAT_1803096b0;
    uStack_510 = _UNK_1803096b8;
    local_528 = (void *)0x4e52594c;
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_4c8);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528,local_528);
    }
    local_518 = puVar1;
    uStack_510 = uVar2;
    local_528 = (void *)((ulonglong)local_528 & 0xffffffffffffff00);
    if (0xf < uStack_4b0) {
      FUN_1800187d0(&local_4c8,local_4c8);
    }
    local_4b8 = puVar1;
    uStack_4b0 = uVar2;
    local_4c8 = (void *)((ulonglong)local_4c8 & 0xffffffffffffff00);
    ArtDoc::AddIndexFormats(local_4a8,5);
    ArtDoc::Field::AddVariableInformation(local_4a8,"1","First layer");
    ArtDoc::Field::AddVariableInformation(local_4a8,"2","Second layer");
    ArtDoc::Field::AddVariableInformation(local_4a8,"3","Third layer");
    ArtDoc::Field::AddVariableInformation(local_4a8,"4","Fourth layer");
    ArtDoc::Field::AddVariableInformation(local_4a8,"5","Fifth layer");
    local_368 = std::
                _Func_impl_no_alloc<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_(__cdecl*)(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64),std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64>
                ::vftable;
    local_360 = FUN_180062bf0;
    local_330 = &local_368;
    ArtDoc::Category::AddListField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64)>
                *)&local_368);
    if (local_330 != (undefined ***)0x0) {
      (*(code *)(*local_330)[4])
                (local_330,CONCAT71((int7)((ulonglong)&local_368 >> 8),local_330 != &local_368));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_4f8 = (undefined *)_DAT_1803096d0;
    uStack_4f0 = _UNK_1803096d8;
    local_508._0_1_ = s_CMYK_Profile_18030a570[0];
    local_508._1_1_ = s_CMYK_Profile_18030a570[1];
    local_508._2_1_ = s_CMYK_Profile_18030a570[2];
    local_508._3_1_ = s_CMYK_Profile_18030a570[3];
    local_508._4_1_ = s_CMYK_Profile_18030a570[4];
    local_508._5_1_ = s_CMYK_Profile_18030a570[5];
    local_508._6_1_ = s_CMYK_Profile_18030a570[6];
    local_508._7_1_ = s_CMYK_Profile_18030a570[7];
    uStack_500 = (code *)(ulonglong)(uint)s_CMYK_Profile_18030a570._8_4_;
    uStack_520 = 0;
    local_518 = (undefined *)_DAT_1803096b0;
    uStack_510 = _UNK_1803096b8;
    local_528 = (void *)0x4b594d43;
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528);
    }
    local_518 = puVar1;
    uStack_510 = uVar2;
    local_528 = (void *)((ulonglong)local_528 & 0xffffffffffffff00);
    if (0xf < uStack_4f0) {
      FUN_1800187d0(&local_508);
    }
    local_1e8[0] = std::
                   _Func_impl_no_alloc<`class_ArtDoc::Category&___ptr64___cdecl_DocumentMarks::GetDocumentCategory(void)'::`12'::<lambda_3>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,int>
                   ::vftable;
    local_1b0 = local_1e8;
    ArtDoc::Category::AddBasicField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int)>
                *)local_1e8);
    if (local_1b0 != (undefined ***)0x0) {
      (*(code *)(*local_1b0)[4])
                (local_1b0,CONCAT71((int7)((ulonglong)local_1e8 >> 8),local_1b0 != local_1e8));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_518 = (undefined *)_DAT_180308000;
    uStack_510 = _UNK_180308008;
    local_528 = (void *)s_RGB_Profile_18030a580._0_8_;
    uStack_520 = (ulonglong)CONCAT12(s_RGB_Profile_18030a580[10],s_RGB_Profile_18030a580._8_2_);
    uStack_4c0 = 0;
    local_4b8 = (undefined *)_DAT_1803096a0;
    uStack_4b0 = _UNK_1803096a8;
    local_4c8 = (void *)(ulonglong)(uint3)DAT_18030a2b0;
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_4c8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4b0) {
      FUN_1800187d0(&local_4c8);
    }
    local_4b8 = puVar1;
    uStack_4b0 = uVar2;
    local_4c8 = (void *)((ulonglong)local_4c8 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528);
    }
    local_1a8[0] = std::
                   _Func_impl_no_alloc<`class_ArtDoc::Category&___ptr64___cdecl_DocumentMarks::GetDocumentCategory(void)'::`13'::<lambda_4>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,int>
                   ::vftable;
    local_170 = local_1a8;
    ArtDoc::Category::AddBasicField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int)>
                *)local_1a8);
    if (local_170 != (undefined ***)0x0) {
      (*(code *)(*local_170)[4])
                (local_170,CONCAT71((int7)((ulonglong)local_1a8 >> 8),local_170 != local_1a8));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_518 = (undefined *)_DAT_1803096c0;
    uStack_510 = _UNK_1803096c8;
    local_528 = (void *)s_Color_Mode_18030a590._0_8_;
    uStack_520 = (ulonglong)(ushort)s_Color_Mode_18030a590._8_2_;
    local_508 = (undefined **)0x0;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)0x0;
    uStack_4f0 = 0;
    FUN_180010070(&local_508,&DAT_18030a434,2);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4f0) {
      FUN_1800187d0(&local_508);
    }
    local_4f8 = puVar1;
    uStack_4f0 = uVar2;
    local_508 = (undefined **)((ulonglong)local_508 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528);
    }
    local_328 = std::
                _Func_impl_no_alloc<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_(__cdecl*)(int),std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,int>
                ::vftable;
    local_320 = FUN_180060710;
    local_2f0 = &local_328;
    ArtDoc::Category::AddBasicField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int)>
                *)&local_328);
    if (local_2f0 != (undefined ***)0x0) {
      (*(code *)(*local_2f0)[4])
                (local_2f0,CONCAT71((int7)((ulonglong)&local_328 >> 8),local_2f0 != &local_328));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_528 = (void *)0x0;
    uStack_520 = 0;
    local_518 = (undefined *)0x0;
    uStack_510 = 0;
    FUN_180010070(&local_528,"Page Label",10);
    local_508 = (undefined **)0x0;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)0x0;
    uStack_4f0 = 0;
    FUN_180010070(&local_508,&DAT_18030a440,2);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4f0) {
      FUN_1800187d0(&local_508);
    }
    local_4f8 = puVar1;
    uStack_4f0 = uVar2;
    local_508 = (undefined **)((ulonglong)local_508 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528);
    }
    local_2e8 = std::
                _Func_impl_no_alloc<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_(__cdecl*)(int),std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,int>
                ::vftable;
    local_2e0 = FUN_180063ac0;
    local_2b0 = &local_2e8;
    ArtDoc::Category::AddBasicField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int)>
                *)&local_2e8);
    if (local_2b0 != (undefined ***)0x0) {
      (*(code *)(*local_2b0)[4])
                (local_2b0,CONCAT71((int7)((ulonglong)&local_2e8 >> 8),local_2b0 != &local_2e8));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_528 = (void *)0x0;
    uStack_520 = 0;
    local_518 = (undefined *)0x0;
    uStack_510 = 0;
    FUN_180010070(&local_528,"Media Box",9);
    local_508 = (undefined **)0x0;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)0x0;
    uStack_4f0 = 0;
    FUN_180010070(&local_508,&DAT_18030a404,2);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4f0) {
      FUN_1800187d0(&local_508,local_508);
    }
    local_4f8 = puVar1;
    uStack_4f0 = uVar2;
    local_508 = (undefined **)((ulonglong)local_508 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528,local_528);
    }
    local_518 = puVar1;
    uStack_510 = uVar2;
    local_528 = (void *)((ulonglong)local_528 & 0xffffffffffffff00);
    FUN_180060370(local_4a8);
    ArtDoc::Field::SetSupportsRemovingZeros(local_4a8,true);
    local_168[0] = std::
                   _Func_impl_no_alloc<`class_ArtDoc::Category&___ptr64___cdecl_DocumentMarks::GetDocumentCategory(void)'::`16'::<lambda_5>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,VariableEngine::Units>
                   ::vftable;
    local_130 = local_168;
    ArtDoc::Category::AddUnitField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,VariableEngine::Units)>
                *)local_168);
    if (local_130 != (undefined ***)0x0) {
      (*(code *)(*local_130)[4])
                (local_130,CONCAT71((int7)((ulonglong)local_168 >> 8),local_130 != local_168));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_528 = (void *)0x0;
    uStack_520 = 0;
    local_518 = (undefined *)0x0;
    uStack_510 = 0;
    FUN_180010070(&local_528,"Crop Box",8);
    local_508 = (undefined **)0x0;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)0x0;
    uStack_4f0 = 0;
    FUN_180010070(&local_508,&DAT_18030a408,2);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4f0) {
      FUN_1800187d0(&local_508,local_508);
    }
    local_4f8 = puVar1;
    uStack_4f0 = uVar2;
    local_508 = (undefined **)((ulonglong)local_508 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528,local_528);
    }
    local_518 = puVar1;
    uStack_510 = uVar2;
    local_528 = (void *)((ulonglong)local_528 & 0xffffffffffffff00);
    FUN_180060370(local_4a8);
    ArtDoc::Field::SetSupportsRemovingZeros(local_4a8,true);
    local_128[0] = std::
                   _Func_impl_no_alloc<`class_ArtDoc::Category&___ptr64___cdecl_DocumentMarks::GetDocumentCategory(void)'::`17'::<lambda_6>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,VariableEngine::Units>
                   ::vftable;
    local_f0 = local_128;
    ArtDoc::Category::AddUnitField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,VariableEngine::Units)>
                *)local_128);
    if (local_f0 != (undefined ***)0x0) {
      (*(code *)(*local_f0)[4])
                (local_f0,CONCAT71((int7)((ulonglong)local_128 >> 8),local_f0 != local_128));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_528 = (void *)0x0;
    uStack_520 = 0;
    local_518 = (undefined *)0x0;
    uStack_510 = 0;
    FUN_180010070(&local_528,"Trim Box",8);
    local_508 = (undefined **)0x0;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)0x0;
    uStack_4f0 = 0;
    FUN_180010070(&local_508,&DAT_18030a40c,2);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4f0) {
      FUN_1800187d0(&local_508,local_508);
    }
    local_4f8 = puVar1;
    uStack_4f0 = uVar2;
    local_508 = (undefined **)((ulonglong)local_508 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528,local_528);
    }
    local_518 = puVar1;
    uStack_510 = uVar2;
    local_528 = (void *)((ulonglong)local_528 & 0xffffffffffffff00);
    FUN_180060370(local_4a8);
    ArtDoc::Field::SetSupportsRemovingZeros(local_4a8,true);
    local_e8[0] = std::
                  _Func_impl_no_alloc<`class_ArtDoc::Category&___ptr64___cdecl_DocumentMarks::GetDocumentCategory(void)'::`18'::<lambda_7>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,VariableEngine::Units>
                  ::vftable;
    local_b0 = local_e8;
    ArtDoc::Category::AddUnitField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,VariableEngine::Units)>
                *)local_e8);
    if (local_b0 != (undefined ***)0x0) {
      (*(code *)(*local_b0)[4])
                (local_b0,CONCAT71((int7)((ulonglong)local_e8 >> 8),local_b0 != local_e8));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_528 = (void *)0x0;
    uStack_520 = 0;
    local_518 = (undefined *)0x0;
    uStack_510 = 0;
    FUN_180010070(&local_528,"Bleed Box",9);
    local_508 = (undefined **)0x0;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)0x0;
    uStack_4f0 = 0;
    FUN_180010070(&local_508,&DAT_18030a410,2);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4f0) {
      FUN_1800187d0(&local_508,local_508);
    }
    local_4f8 = puVar1;
    uStack_4f0 = uVar2;
    local_508 = (undefined **)((ulonglong)local_508 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528,local_528);
    }
    local_518 = puVar1;
    uStack_510 = uVar2;
    local_528 = (void *)((ulonglong)local_528 & 0xffffffffffffff00);
    FUN_180060370(local_4a8);
    ArtDoc::Field::SetSupportsRemovingZeros(local_4a8,true);
    local_a8[0] = std::
                  _Func_impl_no_alloc<`class_ArtDoc::Category&___ptr64___cdecl_DocumentMarks::GetDocumentCategory(void)'::`19'::<lambda_8>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,VariableEngine::Units>
                  ::vftable;
    local_70 = local_a8;
    ArtDoc::Category::AddUnitField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,VariableEngine::Units)>
                *)local_a8);
    if (local_70 != (undefined ***)0x0) {
      (*(code *)(*local_70)[4])
                (local_70,CONCAT71((int7)((ulonglong)local_a8 >> 8),local_70 != local_a8));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_528 = (void *)0x0;
    uStack_520 = 0;
    local_518 = (undefined *)0x0;
    uStack_510 = 0;
    FUN_180010070(&local_528,"Art Box",7);
    local_508 = (undefined **)0x0;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)0x0;
    uStack_4f0 = 0;
    FUN_180010070(&local_508,&DAT_18030a414,2);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4f0) {
      FUN_1800187d0(&local_508,local_508);
    }
    local_4f8 = puVar1;
    uStack_4f0 = uVar2;
    local_508 = (undefined **)((ulonglong)local_508 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528,local_528);
    }
    local_518 = puVar1;
    uStack_510 = uVar2;
    local_528 = (void *)((ulonglong)local_528 & 0xffffffffffffff00);
    FUN_180060370(local_4a8);
    ArtDoc::Field::SetSupportsRemovingZeros(local_4a8,true);
    local_68[0] = std::
                  _Func_impl_no_alloc<`class_ArtDoc::Category&___ptr64___cdecl_DocumentMarks::GetDocumentCategory(void)'::`20'::<lambda_9>,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,VariableEngine::Units>
                  ::vftable;
    local_30 = local_68;
    ArtDoc::Category::AddUnitField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&___ptr64,VariableEngine::Units)>
                *)local_68);
    if (local_30 != (undefined ***)0x0) {
      (*(code *)(*local_30)[4])
                (local_30,CONCAT71((int7)((ulonglong)local_68 >> 8),local_30 != local_68));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_528 = (void *)0x0;
    uStack_520 = 0;
    local_518 = (undefined *)0x0;
    uStack_510 = 0;
    FUN_180010070(&local_528,"Author",6);
    local_508 = (undefined **)0x0;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)0x0;
    uStack_4f0 = 0;
    FUN_180010070(&local_508,&DAT_18030a5b4,4);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    if (0xf < uStack_4f0) {
      FUN_1800187d0(&local_508);
    }
    local_4f8 = puVar1;
    uStack_4f0 = uVar2;
    local_508 = (undefined **)((ulonglong)local_508 & 0xffffffffffffff00);
    if (0xf < uStack_510) {
      FUN_1800187d0(&local_528);
    }
    local_2a8 = std::
                _Func_impl_no_alloc<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_(__cdecl*)(int),std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,int>
                ::vftable;
    local_2a0 = FUN_1800608c0;
    local_270 = &local_2a8;
    ArtDoc::Category::AddBasicField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int)>
                *)&local_2a8);
    if (local_270 != (undefined ***)0x0) {
      (*(code *)(*local_270)[4])
                (local_270,CONCAT71((int7)((ulonglong)&local_2a8 >> 8),local_270 != &local_2a8));
    }
    ArtDoc::Field::~Field(local_4a8);
    local_508 = (undefined **)0x0;
    uStack_500 = (code *)0x0;
    local_4f8 = (undefined *)0x0;
    uStack_4f0 = 0;
    FUN_180010070(&local_508,"Title",5);
    FUN_18000f600(&local_528,local_538);
    FUN_180010070(&local_528,"TITLE",5);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508);
    FUN_1800118b0(&local_528);
    FUN_1800118b0(&local_508);
    local_530 = FUN_180062160;
    FUN_180053250(&local_508);
    ArtDoc::Category::AddBasicField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int)>
                *)&local_508);
    FUN_180013b30(&local_508);
    ArtDoc::Field::~Field(local_4a8);
    FUN_180011dc0(&local_528,"Color Profile");
    FUN_180011dc0(&local_508,&DAT_18030a438);
    ArtDoc::Field::Field
              (local_4a8,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_508,
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_528);
    FUN_1800118b0(&local_508);
    FUN_1800118b0(&local_528);
    local_530 = FUN_1800640c0;
    FUN_180053250(&local_508);
    ArtDoc::Category::AddBasicField
              ((Category *)&DAT_1804888b0,0,local_4a8,
               (function<class_std::basic_string<char,std::char_traits<char>,std::allocator<char>_>___cdecl(int)>
                *)&local_508);
    FUN_180013b30(&local_508);
    ArtDoc::Field::~Field(local_4a8);
    local_508 = std::
                _Func_impl_no_alloc<void_(__cdecl*)(ArtDoc::Document&___ptr64,ArtDoc::WriteOptions_const&___ptr64),void,ArtDoc::Document&___ptr64,ArtDoc::WriteOptions_const&___ptr64>
                ::vftable;
    uStack_500 = FUN_1800604a0;
    local_4d0 = &local_508;
    ArtDoc::RegisterDocumentPreWriter(&local_508);
  }
  return &DAT_1804888b0;
}


