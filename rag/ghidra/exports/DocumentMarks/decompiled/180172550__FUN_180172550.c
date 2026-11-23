// 180172550 FUN_180172550

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Removing unreachable block (ram,0x000180172ff8) */
/* WARNING: Removing unreachable block (ram,0x000180174e6e) */
/* WARNING: Removing unreachable block (ram,0x000180174b07) */
/* WARNING: Removing unreachable block (ram,0x00018017796d) */
/* WARNING: Removing unreachable block (ram,0x000180175af2) */
/* WARNING: Removing unreachable block (ram,0x00018017481d) */
/* WARNING: Type propagation algorithm not settling */

longlong * FUN_180172550(MarkReader *param_1,longlong *param_2)

{
  int *piVar1;
  size_t _Size;
  Document *pDVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  code *pcVar5;
  void *pvVar6;
  longlong lVar7;
  DynamicObject *pDVar8;
  TextAreaMark *pTVar9;
  TextOnPathMark *pTVar10;
  DynamicMark *pDVar11;
  PDFPlusRepeatForGridMark *pPVar12;
  bool bVar13;
  bool bVar14;
  char cVar15;
  byte bVar16;
  Type TVar17;
  int iVar18;
  uint uVar19;
  TextFittingStyle TVar20;
  ColorType CVar21;
  Type TVar22;
  Dictionary *pDVar23;
  Content *pCVar24;
  PropertiesWithNotification *pPVar25;
  undefined8 *_Buf2;
  undefined8 uVar26;
  GADict *pGVar27;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar28;
  longlong *plVar29;
  Module *pMVar30;
  MarksModule *this;
  int *******pppppppiVar31;
  ulonglong *puVar32;
  DynamicTextObject *pDVar33;
  GANumber *pGVar34;
  GAName *this_00;
  ContentObject *this_01;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar35;
  List<ArtDoc::ContentObject> *pLVar36;
  ContentObject *pCVar37;
  Factory *this_02;
  Properties *pPVar38;
  GAObject *pGVar39;
  ColorList<ArtColor::ColorSpacePolicy> *pCVar40;
  variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
  *pvVar41;
  longlong lVar42;
  Parameters *this_03;
  Errors *this_04;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar43;
  int *******pppppppiVar44;
  void *pvVar45;
  undefined8 *******pppppppuVar46;
  undefined8 *puVar47;
  undefined8 *puVar48;
  longlong lVar49;
  longlong *plVar50;
  uint uVar51;
  ulonglong _Size_00;
  undefined4 uVar52;
  double dVar53;
  undefined4 uVar54;
  undefined4 uVar55;
  undefined1 auStack_1d78 [32];
  undefined8 local_1d58;
  GAObject local_1d48 [8];
  char local_1d40;
  byte local_1d3f;
  uint local_1d3c;
  uint local_1d38;
  GADict *local_1d28;
  GADict *pGStack_1d20;
  undefined8 local_1d18;
  Error *local_1d08;
  longlong *plStack_1d00;
  DynamicObject *local_1cf8;
  TextAreaMark *local_1cf0;
  TextOnPathMark *local_1ce8;
  DynamicTextObject *local_1ce0;
  DynamicMark *local_1cd8;
  DynamicMark *local_1cd0;
  DynamicObject *local_1cc8;
  Dictionary *local_1cc0;
  PDFPlusRepeatForGridMark *local_1cb8;
  DynamicObject *local_1cb0;
  undefined1 local_1ca8;
  undefined1 local_1ca7;
  undefined1 local_1ca6;
  undefined1 local_1ca5;
  undefined1 local_1ca4;
  undefined1 local_1ca3;
  undefined1 local_1ca2;
  undefined1 local_1ca1;
  longlong local_1ca0;
  longlong local_1c98;
  DynamicObject *local_1c90;
  DynamicObject *local_1c88;
  PDFPlusRepeatForGridMark *local_1c80;
  longlong local_1c78;
  longlong local_1c70;
  DynamicObject *local_1c68;
  longlong local_1c60;
  GName local_1c58 [8];
  GName local_1c50 [8];
  longlong local_1c48;
  DynamicObject *local_1c40;
  GName local_1c38 [5];
  undefined2 local_1c33;
  undefined1 local_1c31;
  longlong local_1c30;
  GName local_1c28 [8];
  GName local_1c20 [8];
  longlong local_1c18;
  Group *local_1c10;
  GName local_1c08 [8];
  GName local_1c00 [8];
  FormPaint *local_1bf8;
  longlong lStack_1bf0;
  undefined8 local_1be8;
  longlong lStack_1be0;
  undefined8 local_1bd8;
  undefined1 uStack_1bd0;
  undefined7 uStack_1bcf;
  FormPaint *local_1bc8 [2];
  GName local_1bb8 [8];
  GName local_1bb0 [8];
  GName local_1ba8 [8];
  GName local_1ba0 [8];
  GName local_1b98 [8];
  GName local_1b90 [8];
  GName local_1b88 [8];
  GName local_1b80 [8];
  GName local_1b78 [8];
  GName local_1b70 [8];
  GName local_1b68 [8];
  GName local_1b60 [8];
  undefined1 local_1b58 [16];
  FormPaint *local_1b48;
  longlong lStack_1b40;
  undefined1 local_1b38 [16];
  undefined1 local_1b28 [16];
  GName local_1b18 [8];
  GName local_1b10 [8];
  GName local_1b08 [8];
  GName local_1b00 [8];
  GName local_1af8 [8];
  GName local_1af0 [8];
  GName local_1ae8 [8];
  GName local_1ae0 [8];
  GADict local_1ad8 [8];
  GName local_1ad0 [8];
  GName local_1ac8 [8];
  GName local_1ac0 [8];
  GName local_1ab8 [8];
  GName local_1ab0 [8];
  GName local_1aa8 [8];
  GName local_1aa0 [8];
  GName local_1a98 [8];
  GADict local_1a90 [8];
  GName local_1a88 [8];
  GName local_1a80 [8];
  GName local_1a78 [8];
  GName local_1a70 [8];
  GName local_1a68 [8];
  GName local_1a60 [8];
  GName local_1a58 [8];
  GADict local_1a50 [8];
  char *local_1a48;
  char *local_1a40;
  GName local_1a38 [8];
  GName local_1a30 [8];
  GName local_1a28 [8];
  GName local_1a20 [8];
  GName local_1a18 [8];
  GName local_1a10 [8];
  char *local_1a08;
  char *local_1a00;
  GName local_19f8 [8];
  GName local_19f0 [8];
  char *local_19e8;
  GName local_19e0 [8];
  GName local_19d8 [8];
  GName local_19d0 [8];
  GName local_19c8 [8];
  GName local_19c0 [8];
  GName local_19b8 [8];
  GName local_19b0 [8];
  GName local_19a8 [8];
  char *local_19a0;
  GName local_1998 [8];
  GName local_1990 [8];
  GName local_1988 [8];
  char *local_1980;
  GName local_1978 [8];
  GName local_1970 [8];
  GName local_1968 [8];
  DynamicObject **local_1960;
  GName local_1958 [8];
  GName local_1950 [8];
  GName local_1948 [8];
  char *local_1940;
  GName local_1938 [8];
  DynamicObject **local_1930;
  char *local_1928;
  GName local_1920 [8];
  GName local_1918 [8];
  char *local_1910;
  GName local_1908 [8];
  GName local_1900 [8];
  GName local_18f8 [8];
  MarkReader *local_18f0;
  longlong *local_18e8;
  GName local_18e0 [8];
  GName local_18d8 [8];
  GAObject local_18d0 [8];
  char *local_18c8;
  GADict local_18c0 [8];
  GName local_18b8 [8];
  char *local_18b0;
  GName local_18a8 [8];
  GName local_18a0 [8];
  char *local_1898 [2];
  undefined8 local_1888;
  longlong lStack_1880;
  undefined8 local_1878;
  longlong lStack_1870;
  FormPaint *local_1868;
  longlong lStack_1860;
  FormPaint *local_1858;
  longlong lStack_1850;
  FormPaint *local_1848;
  longlong lStack_1840;
  undefined8 local_1838;
  longlong lStack_1830;
  undefined8 local_1828;
  longlong lStack_1820;
  undefined8 local_1818;
  longlong lStack_1810;
  undefined8 local_1808;
  longlong lStack_1800;
  Error *local_17f8;
  longlong *plStack_17f0;
  longlong local_17e8;
  longlong lStack_17e0;
  undefined8 local_17d8;
  BarCode *local_17d0;
  longlong local_17c8 [2];
  undefined8 local_17b8;
  longlong local_17b0 [2];
  undefined1 local_17a0 [16];
  FormPaint *local_1790 [3];
  GADict *local_1778;
  GADict *pGStack_1770;
  undefined1 local_1768 [16];
  FormPaint *local_1758 [2];
  GADict *local_1748;
  GADict *pGStack_1740;
  GADict *local_1738;
  GADict *pGStack_1730;
  GADict *local_1728;
  ulonglong *puStack_1720;
  GADict *local_1718;
  GADict *pGStack_1710;
  GADict *local_1708;
  undefined1 *puStack_1700;
  GADict *local_16f8;
  GADict *pGStack_16f0;
  undefined1 local_16e8 [16];
  GADict *local_16d8;
  undefined1 *puStack_16d0;
  VisitorBase local_16c8 [8];
  undefined **local_16c0;
  DynamicMark *local_16b8;
  VisitorBase local_16a8 [8];
  undefined **local_16a0;
  DynamicMark *local_1698;
  undefined **local_1688;
  longlong *local_1680;
  undefined ***local_1650;
  undefined1 local_1648 [16];
  undefined1 local_1638 [16];
  undefined1 local_1628 [16];
  undefined1 local_1618 [16];
  undefined1 local_1608 [16];
  undefined1 local_15f8 [16];
  undefined1 local_15e8 [16];
  undefined1 local_15d8 [16];
  undefined1 local_15c8 [16];
  undefined1 local_15b8 [16];
  undefined1 local_15a8 [16];
  undefined1 local_1598 [16];
  undefined1 local_1588 [16];
  undefined1 local_1578 [16];
  undefined1 local_1568 [16];
  undefined1 local_1558 [16];
  undefined1 local_1548 [16];
  undefined1 local_1538 [16];
  undefined1 local_1528 [16];
  undefined1 local_1518 [16];
  undefined1 local_1508 [16];
  undefined1 local_14f8 [16];
  undefined8 local_14e8;
  undefined8 uStack_14e0;
  undefined1 local_14d8 [16];
  undefined1 local_14c8 [16];
  undefined1 local_14b8 [16];
  undefined1 local_14a8 [16];
  undefined1 local_1498 [16];
  undefined1 local_1488 [24];
  undefined1 local_1470 [24];
  undefined1 local_1458 [24];
  undefined1 local_1440 [24];
  undefined1 local_1428 [24];
  undefined1 local_1410 [24];
  undefined1 local_13f8 [24];
  undefined1 local_13e0 [40];
  undefined4 local_13b8 [2];
  longlong local_13b0;
  undefined8 uStack_13a8;
  uint local_13a0;
  undefined1 local_1398;
  undefined1 local_1390 [8];
  longlong local_1388;
  undefined1 local_1378 [8];
  undefined1 local_1370 [40];
  undefined1 local_1348 [40];
  undefined1 local_1320 [40];
  undefined4 local_12f8;
  char local_12f4;
  undefined2 local_12f3;
  undefined1 local_12f1;
  undefined4 local_12f0;
  char local_12ec;
  undefined2 local_12eb;
  undefined1 local_12e9;
  uint local_12e8 [12];
  undefined4 local_12b8 [14];
  undefined1 local_1280;
  undefined8 local_1278;
  longlong lStack_1270;
  void *local_1268;
  undefined8 uStack_1260;
  longlong local_1258;
  undefined1 local_1240;
  undefined8 local_1238;
  undefined8 uStack_1230;
  undefined8 local_1228;
  undefined8 uStack_1220;
  undefined8 local_1218;
  undefined8 uStack_1210;
  undefined4 local_1208 [14];
  undefined1 local_11d0;
  undefined8 local_11c8;
  longlong lStack_11c0;
  undefined8 local_11b8;
  undefined8 uStack_11b0;
  undefined8 local_11a8;
  undefined1 local_1190;
  undefined4 local_1188 [14];
  undefined1 local_1150;
  undefined8 local_1148;
  undefined8 uStack_1140;
  undefined8 local_1138;
  undefined8 uStack_1130;
  undefined8 local_1128;
  undefined1 local_1110;
  undefined1 local_1108 [8];
  undefined1 local_1100 [40];
  undefined1 local_10d8 [40];
  undefined1 local_10b0 [56];
  CloneStrategy local_1078 [144];
  undefined1 local_fe8 [112];
  undefined1 local_f78 [112];
  undefined1 local_f08 [112];
  undefined1 local_e98 [184];
  undefined1 local_de0 [184];
  Factory local_d28 [312];
  int *******local_bf0;
  undefined8 uStack_be8;
  longlong local_be0;
  ulonglong local_bd8;
  void *local_bd0;
  ulonglong uStack_bc8;
  undefined *local_bc0;
  ulonglong uStack_bb8;
  undefined1 local_bb0;
  undefined7 uStack_baf;
  undefined *local_ba0;
  ulonglong uStack_b98;
  undefined8 *******local_b90 [2];
  longlong local_b80;
  ulonglong local_b78;
  ulonglong local_b70;
  undefined4 uStack_b68;
  undefined2 uStack_b64;
  undefined2 uStack_b62;
  undefined *local_b60;
  ulonglong uStack_b58;
  void *local_b50;
  undefined8 uStack_b48;
  undefined *local_b40;
  ulonglong uStack_b38;
  void *local_b30;
  undefined8 uStack_b28;
  undefined *local_b20;
  ulonglong uStack_b18;
  ulonglong local_b10 [2];
  undefined *local_b00;
  ulonglong uStack_af8;
  undefined8 *******local_af0 [2];
  longlong local_ae0;
  ulonglong local_ad8;
  void *local_ad0;
  undefined8 uStack_ac8;
  undefined *local_ac0;
  ulonglong uStack_ab8;
  ulonglong local_ab0 [2];
  undefined *local_aa0;
  ulonglong uStack_a98;
  void *local_a90;
  undefined8 uStack_a88;
  undefined *local_a80;
  ulonglong uStack_a78;
  undefined8 local_a70;
  undefined8 uStack_a68;
  undefined8 local_a60;
  undefined8 uStack_a58;
  undefined8 local_a50;
  undefined8 uStack_a48;
  undefined8 local_a40;
  undefined8 uStack_a38;
  undefined4 local_a30 [2];
  undefined8 local_a28;
  undefined8 uStack_a20;
  undefined *local_a18;
  undefined8 uStack_a10;
  undefined **local_a08;
  TextAreaMark **local_a00;
  undefined ***local_9d0;
  undefined **local_9c8;
  TextOnPathMark **local_9c0;
  undefined ***local_990;
  undefined **local_988;
  DynamicTextObject **local_980;
  undefined ***local_950;
  undefined **local_948;
  undefined **local_940;
  undefined1 local_938 [56];
  undefined ***local_900;
  undefined8 local_8f8;
  undefined8 uStack_8f0;
  undefined8 local_8e8;
  undefined8 uStack_8e0;
  undefined8 local_8d8;
  undefined8 uStack_8d0;
  undefined8 local_8c8;
  undefined8 uStack_8c0;
  undefined8 local_8b8;
  undefined8 uStack_8b0;
  undefined8 local_8a8;
  undefined8 uStack_8a0;
  undefined8 local_898;
  undefined8 uStack_890;
  undefined8 local_888;
  undefined8 uStack_880;
  undefined8 local_878;
  undefined8 uStack_870;
  undefined8 local_868;
  undefined8 uStack_860;
  undefined1 local_858 [32];
  char local_838;
  GAString local_830 [32];
  Content local_810 [32];
  undefined1 local_7f0 [32];
  undefined1 local_7d0 [32];
  undefined1 local_7b0 [32];
  GAName local_790 [40];
  GADict local_768 [32];
  undefined1 local_748 [32];
  undefined1 local_728 [32];
  undefined1 local_708 [32];
  undefined1 local_6e8 [8];
  int local_6e0;
  char local_660;
  int local_648;
  char local_640;
  char local_638;
  undefined1 local_628 [64];
  undefined1 local_5e8 [64];
  GADict local_5a8 [32];
  undefined1 local_588 [32];
  undefined1 local_568 [32];
  undefined1 local_548 [32];
  undefined1 local_528 [32];
  undefined1 local_508 [32];
  GADict local_4e8 [32];
  undefined1 local_4c8 [32];
  undefined1 local_4a8 [32];
  undefined1 local_488 [32];
  undefined1 local_468 [32];
  undefined1 local_448 [32];
  GADict local_428 [32];
  undefined1 local_408 [32];
  undefined1 local_3e8 [32];
  undefined1 local_3c8 [32];
  undefined1 local_3a8 [32];
  undefined1 local_388 [32];
  GADict local_368 [32];
  undefined1 local_348 [32];
  undefined1 local_328 [32];
  undefined1 local_308 [32];
  undefined1 local_2e8 [32];
  undefined1 local_2c8 [32];
  GADict local_2a8 [32];
  undefined1 local_288 [32];
  undefined1 local_268 [32];
  undefined1 local_248 [32];
  undefined1 local_228 [32];
  undefined1 local_208 [32];
  undefined1 local_1e8 [32];
  GADict local_1c8 [32];
  undefined1 local_1a8 [32];
  undefined1 local_188 [32];
  undefined1 local_168 [32];
  undefined1 local_148 [32];
  undefined1 local_128 [32];
  undefined1 local_108 [32];
  undefined1 local_e8 [32];
  undefined1 local_c8 [32];
  undefined1 local_a8 [32];
  undefined1 local_88 [32];
  ulonglong local_68 [8];
  
  local_68[0] = DAT_180418e00 ^ (ulonglong)auStack_1d78;
  bVar14 = false;
  local_1d3c = 0;
  local_18f0 = param_1;
  local_18e8 = param_2;
  pDVar23 = ArtDoc::MarkReader::GetPropertiesAsDictionary(param_1);
  local_1d08 = (Error *)0x0;
  plStack_1d00 = (longlong *)0x0;
  uStack_be8 = 0;
  local_be0 = 0;
  local_bd8 = 0xf;
  local_bf0 = (int *******)0x0;
  local_1d18 = pDVar23;
  pCVar24 = (Content *)(**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
  TVar17 = ArtDoc::Content::GetType(pCVar24);
  local_1d40 = (char)TVar17;
  pCVar24 = (Content *)(**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
  pPVar25 = ArtDoc::Content::GetProperties(pCVar24);
  pcVar5 = kUserScaling_exref;
  puVar47 = *(undefined8 **)pPVar25;
  puVar48 = puVar47 + *(longlong *)(pPVar25 + 8) * 0xc;
  if (puVar47 == puVar48) {
LAB_1801726d1:
    uVar55 = 0;
    uVar52 = 0x3ff00000;
  }
  else {
    do {
      _Buf2 = puVar47;
      if (0xf < (ulonglong)puVar47[3]) {
        _Buf2 = (undefined8 *)*puVar47;
      }
      _Size = *(size_t *)(pcVar5 + 8);
    } while (((_Size != puVar47[2]) ||
             ((_Size != 0 && (iVar18 = memcmp(*(void **)pcVar5,_Buf2,_Size), iVar18 != 0)))) &&
            (puVar47 = puVar47 + 0xc, puVar47 != puVar48));
    pDVar23 = local_1d18;
    if (puVar47 == puVar48) goto LAB_1801726d1;
    puVar48 = puVar47 + 4;
    if (((puVar48 == (undefined8 *)0x0) || ((puVar47[0xb] & 0xfffffffffffffffc) == 0)) ||
       (iVar18 = __std_type_info_compare((puVar47[0xb] & 0xfffffffffffffffc) + 8,0x18041c6e8),
       iVar18 != 0)) {
      puVar48 = (undefined8 *)0x0;
    }
    if (puVar48 == (undefined8 *)0x0) goto LAB_1801726d1;
    uVar55 = (undefined4)*puVar48;
    uVar52 = (undefined4)((ulonglong)*puVar48 >> 0x20);
  }
  uVar26 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
  local_1d38 = FUN_180177fe0(uVar26);
  local_1d3f = (byte)local_1d38 & 1;
  local_1d18 = (Dictionary *)
               (CONCAT44(local_1d18._4_4_,CONCAT31((uint3)(local_1d38 >> 9),(char)(local_1d38 >> 1))
                        ) & 0xffffffffffffff01);
  if ((local_1d40 == '\0') || ((local_1d38 & 1) != 0)) {
    uStack_b48 = 0;
    local_b40 = &DAT_00000007;
    uStack_b38 = 0xf;
    local_b50 = (void *)0x65746176697250;
    bVar14 = true;
    local_1d3c = 1;
    bVar13 = ArtDoc::Dictionary::HasDictionaryValue
                       (pDVar23,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                                &local_b50);
    if (!bVar13) goto LAB_18017277f;
    bVar13 = true;
  }
  else {
LAB_18017277f:
    bVar13 = false;
  }
  if (bVar14) {
    if (0xf < uStack_b38) {
      pvVar45 = local_b50;
      if (0xfff < uStack_b38 + 1) {
        pvVar45 = *(void **)((longlong)local_b50 + -8);
        if (0x1f < (ulonglong)((longlong)local_b50 + (-8 - (longlong)pvVar45))) goto LAB_1801728a0;
      }
      free(pvVar45);
    }
    local_b40 = (undefined *)0x0;
    uStack_b38 = 0xf;
    local_b50 = (void *)((ulonglong)local_b50 & 0xffffffffffffff00);
  }
  if (!bVar13) goto LAB_180177860;
  uStack_b28 = 0;
  local_b20 = &DAT_00000007;
  uStack_b18 = 0xf;
  local_b30 = (void *)0x65746176697250;
  pDVar23 = ArtDoc::Dictionary::GetDictionaryValue
                      (pDVar23,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                               &local_b30);
  local_1cc0 = pDVar23;
  if (0xf < uStack_b18) {
    pvVar45 = local_b30;
    if ((0xfff < uStack_b18 + 1) &&
       (pvVar45 = *(void **)((longlong)local_b30 + -8),
       0x1f < (ulonglong)((longlong)local_b30 + (-8 - (longlong)pvVar45)))) {
LAB_1801728a0:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar45);
  }
  local_b20 = (undefined *)0x0;
  uStack_b18 = 0xf;
  local_b30 = (void *)((ulonglong)local_b30 & 0xffffffffffffff00);
  pGVar27 = (GADict *)GADict::Cast(local_18d0);
  GName::GName(local_18e0,"Private");
  GADict::Get(pGVar27,local_18d8);
  GADict::Cast(local_1d48);
  GAObject::~GAObject((GAObject *)local_18d8);
  GADict::~GADict((GADict *)local_18d0);
  local_ac0 = (undefined *)0xa;
  uStack_ab8 = 0xf;
  local_ad0 = (void *)0x79547463656a624f;
  uStack_ac8 = 0x6570;
  bVar14 = ArtDoc::Dictionary::HasStringValue
                     (pDVar23,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                              &local_ad0);
  if (0xf < uStack_ab8) {
    pvVar45 = local_ad0;
    if ((0xfff < uStack_ab8 + 1) &&
       (pvVar45 = *(void **)((longlong)local_ad0 + -8),
       0x1f < (ulonglong)((longlong)local_ad0 + (-8 - (longlong)pvVar45)))) goto LAB_1801730ba;
    free(pvVar45);
  }
  local_ac0 = (undefined *)0x0;
  uStack_ab8 = 0xf;
  local_ad0 = (void *)((ulonglong)local_ad0 & 0xffffffffffffff00);
  if (!bVar14) {
LAB_180177854:
    GADict::~GADict((GADict *)local_1d48);
LAB_180177860:
    local_1c10 = (Group *)FUN_1802d6b50(0x2d0);
    local_1d28 = (GADict *)local_1c10;
    if (local_1c10 == (Group *)0x0) {
      local_1c10 = (Group *)0x0;
    }
    else {
      ArtDoc::Group::Group(local_1c10,4);
      *(undefined ***)local_1c10 = ArtDoc::Group::vftable;
      *(undefined ***)(local_1c10 + 0x20) = ArtDoc::Group::vftable;
    }
    if (local_1d08 != (Error *)0x0) {
      pCVar24 = (Content *)(**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
      this_04 = ArtDoc::Content::GetActiveErrors(pCVar24);
      if (plStack_1d00 != (longlong *)0x0) {
        LOCK();
        *(int *)(plStack_1d00 + 1) = (int)plStack_1d00[1] + 1;
        UNLOCK();
      }
      local_17f8 = local_1d08;
      plStack_17f0 = plStack_1d00;
      ArtDoc::Errors::AddError(this_04,(shared_ptr<ArtSys::Core::Error> *)&local_17f8);
      if (plStack_17f0 != (longlong *)0x0) {
        FUN_180018860();
      }
      pCVar24 = (Content *)(**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
      ArtDoc::AssociateObjectWithError(local_1d08,(ContentObject *)local_1c10,pCVar24);
    }
    *param_2 = (longlong)local_1c10;
    local_1c10 = (Group *)0x0;
    if (0xf < local_bd8) {
      pppppppiVar31 = local_bf0;
      if ((0xfff < local_bd8 + 1) &&
         (pppppppiVar31 = (int *******)local_bf0[-1],
         0x1f < (ulonglong)((longlong)local_bf0 + (-8 - (longlong)pppppppiVar31)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      free(pppppppiVar31);
    }
    plVar50 = plStack_1d00;
    local_be0 = 0;
    local_bd8 = 0xf;
    local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
    if (plStack_1d00 != (longlong *)0x0) {
      LOCK();
      plVar29 = plStack_1d00 + 1;
      lVar42 = *plVar29;
      *(int *)plVar29 = (int)*plVar29 + -1;
      UNLOCK();
      if ((int)lVar42 == 1) {
        (**(code **)*plStack_1d00)(plStack_1d00);
        LOCK();
        piVar1 = (int *)((longlong)plVar50 + 0xc);
        iVar18 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar18 == 1) {
          (**(code **)(*plVar50 + 8))(plVar50);
        }
      }
    }
    return param_2;
  }
  local_a80 = (undefined *)0xa;
  uStack_a78 = 0xf;
  local_a90 = (void *)0x79547463656a624f;
  uStack_a88 = 0x6570;
  pbVar28 = ArtDoc::Dictionary::GetStringValue
                      (pDVar23,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)&local_a90);
  if ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_bf0 != pbVar28) {
    pbVar43 = pbVar28 + 0x10;
    if (0xf < *(ulonglong *)(pbVar28 + 0x18)) {
      pbVar28 = *(basic_string<char,std::char_traits<char>,std::allocator<char>_> **)pbVar28;
    }
    FUN_180019430(&local_bf0,pbVar28,*(undefined8 *)pbVar43);
  }
  if (0xf < uStack_a78) {
    pvVar45 = local_a90;
    if ((0xfff < uStack_a78 + 1) &&
       (pvVar45 = *(void **)((longlong)local_a90 + -8),
       0x1f < (ulonglong)((longlong)local_a90 + (-8 - (longlong)pvVar45)))) goto LAB_1801730ba;
    free(pvVar45);
  }
  local_a80 = (undefined *)0x0;
  uStack_a78 = 0xf;
  local_a90 = (void *)((ulonglong)local_a90 & 0xffffffffffffff00);
  FUN_180184a80(&local_bb0,local_1d48);
  plVar29 = (longlong *)FUN_180178260(local_1390,&local_bf0,&local_bb0);
  local_1d08 = (Error *)*plVar29;
  plVar50 = (longlong *)plVar29[1];
  *plVar29 = 0;
  plVar29[1] = 0;
  bVar14 = plStack_1d00 != (longlong *)0x0;
  plStack_1d00 = plVar50;
  if (bVar14) {
    FUN_180018860();
  }
  if (local_1388 != 0) {
    FUN_180018860();
  }
  if (local_1d08 != (Error *)0x0) {
    local_18c8 = "Unsupported type or version";
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(&local_18c8,(ThrowInfo *)&DAT_1803b78c8);
  }
  pDVar2 = *(Document **)(param_1 + 0x28);
  pGVar27 = (GADict *)GADict::GADict(local_18c0,(GADict *)local_1d48);
  local_1d28 = pGVar27;
  pMVar30 = ArtDoc::FindModule(0x4d61726b);
  local_1d58 = (ulonglong)local_1d58._4_4_ << 0x20;
  this = (MarksModule *)
         __RTDynamicCast(pMVar30,0,&ArtDoc::Module::RTTI_Type_Descriptor,
                         &DocumentMarks::MarksModule::RTTI_Type_Descriptor);
  if ((this != (MarksModule *)0x0) &&
     (uVar19 = DocumentMarks::MarksModule::GetFeatures(this), (uVar19 >> 9 & 1) != 0)) {
    GName::GName(local_18b8,"Context");
    bVar14 = GADict::Has(pGVar27,local_18b8);
    bVar13 = DocumentMarks::IsReportTemplate(pDVar2);
    if (bVar13) {
      if (!bVar14) {
        local_18b0 = "Context mismatch";
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(&local_18b0,(ThrowInfo *)&DAT_1803b78c8);
      }
    }
    else if (!bVar14) goto LAB_180172c69;
    pppppppiVar31 = (int *******)&local_bf0;
    if (0xf < local_bd8) {
      pppppppiVar31 = local_bf0;
    }
    if (local_be0 == 4) {
      bVar14 = *(int *)pppppppiVar31 == 0x74786554;
    }
    else {
      bVar14 = false;
    }
    GName::GName(local_18a8,"Context");
    uVar26 = GADict::GetDict(pGVar27,local_18a0);
    cVar15 = FUN_180178a00(uVar26,bVar13,bVar14);
    GADict::~GADict((GADict *)local_18a0);
    if (cVar15 == '\0') {
      local_1898[0] = "Mark contains invalid Context.";
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(local_1898,(ThrowInfo *)&DAT_1803b78c8);
    }
  }
LAB_180172c69:
  GADict::~GADict(pGVar27);
  GName::GName(local_1b18,"Context");
  bVar14 = GADict::Has((GADict *)local_1d48,local_1b18);
  if (bVar14) {
    GName::GName(local_1b10,"Context");
    pGVar27 = (GADict *)GADict::GetDict((GADict *)local_1d48,local_1af8);
    local_1d3c = 2;
    GName::GName(local_1b08,"Type");
    GADict::GetName(pGVar27,local_1b00);
    local_1d3c = 6;
    puVar32 = (ulonglong *)ArtDocGlue::PDFConverters::UTF8String(local_790);
    uVar19 = 0xe;
  }
  else {
    uStack_b62 = 0;
    local_b60 = (undefined *)0xe;
    uStack_b58 = 0xf;
    local_b70 = 0x696e6961746e6f43;
    uStack_b68 = 0x6150676e;
    uStack_b64 = 0x6567;
    puVar32 = &local_b70;
    uVar19 = 0x10;
  }
  local_bd0 = (void *)0x0;
  uStack_bc8 = 0;
  local_bc0 = (undefined *)0x0;
  uStack_bb8 = 0;
  local_bd0 = (void *)*puVar32;
  uStack_bc8 = puVar32[1];
  local_bc0 = (undefined *)puVar32[2];
  uStack_bb8 = puVar32[3];
  puVar32[2] = 0;
  puVar32[3] = 0xf;
  *(undefined1 *)puVar32 = 0;
  if ((uVar19 & 0x10) != 0) {
    uVar19 = uVar19 & 0xffffffef;
    if (0xf < uStack_b58) {
      FUN_1800187d0(&local_b70,local_b70);
    }
    local_b60 = (undefined *)0x0;
    uStack_b58 = 0xf;
    local_b70 = local_b70 & 0xffffffffffffff00;
  }
  if ((uVar19 & 8) != 0) {
    uVar19 = uVar19 & 0xfffffff7;
    FUN_1800118b0(local_790);
  }
  if ((uVar19 & 4) != 0) {
    uVar19 = uVar19 & 0xfffffffb;
    GAName::~GAName((GAName *)local_1b00);
  }
  if ((uVar19 & 2) != 0) {
    uVar19 = uVar19 & 0xfffffffd;
    GADict::~GADict((GADict *)local_1af8);
  }
  uVar3 = local_bd8;
  lVar42 = local_be0;
  pppppppiVar31 = local_bf0;
  pppppppiVar44 = (int *******)&local_bf0;
  if (0xf < local_bd8) {
    pppppppiVar44 = local_bf0;
  }
  iVar18 = FUN_180021700(pppppppiVar44,local_be0,"Generic",7);
  if (iVar18 != 0) {
    pppppppiVar44 = (int *******)&local_bf0;
    if (0xf < uVar3) {
      pppppppiVar44 = pppppppiVar31;
    }
    iVar18 = FUN_180021700(pppppppiVar44,lVar42,&DAT_180312a38,4);
    if (iVar18 == 0) {
      local_aa0 = (undefined *)0x8;
      uStack_a98 = 0xf;
      local_ab0[0] = 0x6570795474786554;
      local_ab0[1] = 0;
      pbVar28 = ArtDoc::Dictionary::GetStringValue
                          (local_1cc0,
                           (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            *)local_ab0);
      if (0xf < uStack_a98) {
        FUN_1800187d0(local_ab0,local_ab0[0]);
      }
      local_aa0 = (undefined *)0x0;
      uStack_a98 = 0xf;
      local_ab0[0] = local_ab0[0] & 0xffffffffffffff00;
      uVar3 = *(ulonglong *)(pbVar28 + 0x10);
      uVar4 = *(ulonglong *)(pbVar28 + 0x18);
      pbVar43 = pbVar28;
      if (0xf < uVar4) {
        pbVar43 = *(basic_string<char,std::char_traits<char>,std::allocator<char>_> **)pbVar28;
      }
      _Size_00 = uVar3;
      if (9 < uVar3) {
        _Size_00 = 9;
      }
      iVar18 = memcmp(pbVar43,"PointText",_Size_00);
      if ((iVar18 != 0) || (uVar3 != 9)) {
        if (0xf < uVar4) {
          pbVar28 = *(basic_string<char,std::char_traits<char>,std::allocator<char>_> **)pbVar28;
        }
        iVar18 = FUN_180021700(pbVar28,uVar3,"ContainedText",0xd);
        if (iVar18 != 0) {
LAB_180177ada:
          local_1a40 = "Unsupported type or Text Mark";
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(&local_1a40,(ThrowInfo *)&DAT_1803b78c8);
        }
        local_a50 = 0;
        uStack_a48 = 0;
        local_a40 = 0;
        uStack_a38 = 0;
        FUN_180010070(&local_a50,"Source",6);
        pbVar28 = ArtDoc::Dictionary::GetStringValue
                            (local_1cc0,
                             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              *)&local_a50);
        FUN_1800118b0(&local_a50);
        GName::GName(local_1ad0,"Container");
        GADict::GetDict((GADict *)local_1d48,local_1c50);
        GName::GName(local_1ac8,"Type");
        GADict::GetName((GADict *)local_1c50,local_1c58);
        bVar14 = GAName::operator==((GAName *)local_1c58,"InsideBox");
        if ((!bVar14) && (bVar14 = GAName::operator==((GAName *)local_1c58,"InPath"), !bVar14)) {
          bVar14 = GAName::operator==((GAName *)local_1c58,"OnPath");
          if (!bVar14) {
            GAName::~GAName((GAName *)local_1c58);
            GADict::~GADict((GADict *)local_1c50);
            goto LAB_180177ada;
          }
          local_1d28 = (GADict *)FUN_1802d6b50(0x770);
          if (local_1d28 == (GADict *)0x0) {
            pDVar33 = (DynamicTextObject *)0x0;
          }
          else {
            pDVar33 = (DynamicTextObject *)
                      DocumentMarks::TextOnPathMark::TextOnPathMark
                                ((TextOnPathMark *)local_1d28,false);
          }
          uVar51 = 0;
          local_1ce8 = (TextOnPathMark *)pDVar33;
          pbVar28 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                    FUN_1801cd320(local_7d0,pbVar28);
          DocumentMarks::DynamicTextObject::setUniversalText(pDVar33,pbVar28);
          FUN_1800118b0(local_7d0);
          pTVar10 = local_1ce8;
          uVar26 = FUN_180184510(local_1638,local_1c50,*(undefined8 *)(param_1 + 0x30));
          DocumentMarks::TextOnPathMark::SetTextPath(pTVar10,uVar26);
          pTVar10 = local_1ce8;
          GName::GName(local_1ac0,"Reflow");
          bVar14 = GADict::Has((GADict *)local_1d48,local_1ac0);
          if (bVar14) {
            GName::GName(local_1ab8,"Reflow");
            GADict::GetDict((GADict *)local_1d48,local_1c00);
            GName::GName(local_1ab0,"MinimumFontSize");
            bVar14 = GADict::Has((GADict *)local_1c00,local_1ab0);
            if (bVar14) {
              GName::GName(local_1aa8,"MinimumFontSize");
              pGVar34 = (GANumber *)GADict::GetNumber((GADict *)local_1c00,local_1aa0);
              uVar51 = uVar19 | 0x1800000;
              local_1d3c = uVar51;
              dVar53 = GANumber::Get(pGVar34);
              uVar52 = SUB84(dVar53,0);
              uVar54 = (undefined4)((ulonglong)dVar53 >> 0x20);
            }
            else {
              uVar52 = 0;
              uVar54 = 0x401c0000;
            }
            if ((uVar51 >> 0x17 & 1) != 0) {
              GANumber::~GANumber((GANumber *)local_1aa0);
            }
            DocumentMarks::TextOnPathMark::SetMinimumFontSize
                      (pTVar10,(double)CONCAT44(uVar54,uVar52));
            GADict::~GADict((GADict *)local_1c00);
          }
          if (local_1d40 != '\0') {
            GName::GName(local_1a98,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1a98);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1ce8 + 0x2f0),0);
              }
              goto LAB_18017398c;
            }
          }
          FUN_180180330(local_1d48,local_1ce8,&local_bd0,uVar55);
LAB_18017398c:
          FUN_18017b590(local_1d48,local_1ce8,(ulonglong)local_1d18 & 0xff);
          local_9c8 = std::
                      _Func_impl_no_alloc<`public:_virtual_class_std::unique_ptr<ArtDoc::Group,std::default_delete<ArtDoc::Group>_>___cdecl_DocumentMarks::PDFPlusMarkReader::CreateGroup(void)___ptr64'::`54'::<lambda_3>,void,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
                      ::vftable;
          local_9c0 = &local_1ce8;
          local_990 = &local_9c8;
          FUN_1801837d0(local_1d48,&local_9c8);
          if (local_990 != (undefined ***)0x0) {
            (*(code *)(*local_990)[4])(local_990,local_990 != &local_9c8);
            local_990 = (undefined ***)0x0;
          }
          local_1188[0] = 2;
          local_1150 = 0;
          local_1148 = 0;
          uStack_1140 = 0;
          local_1138 = 0;
          uStack_1130 = 0;
          local_1128 = 0;
          local_1110 = 0;
          DocumentTypesetting::SetRecognitionContext
                    ((ContentObject *)local_1ce8,(RecognitionContext *)local_1188);
          pTVar10 = local_1ce8;
          uVar26 = GADict::GADict(local_1a90,(GADict *)local_1d48);
          bVar16 = FUN_180178cd0(uVar26);
          DocumentMarks::DynamicTextObject::SetUseStationInformation
                    ((DynamicTextObject *)pTVar10,(bool)(bVar16 ^ 1));
          pTVar10 = local_1ce8;
          local_1ce8 = (TextOnPathMark *)0x0;
          *param_2 = (longlong)pTVar10;
          FUN_1800653d0(local_1188);
          pTVar10 = local_1ce8;
          if (local_1ce8 != (TextOnPathMark *)0x0) {
            DocumentMarks::TextOnPathMark::~TextOnPathMark(local_1ce8);
            free(pTVar10);
          }
          GAName::~GAName((GAName *)local_1c58);
          GADict::~GADict((GADict *)local_1c50);
          if (0xf < uStack_bb8) {
            FUN_1800187d0(&local_bd0,local_bd0);
          }
          local_bc0 = (undefined *)0x0;
          uStack_bb8 = 0xf;
          local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
          if (0xf < uStack_b98) {
            FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
          }
          local_ba0 = (undefined *)0x0;
          uStack_b98 = 0xf;
          local_bb0 = 0;
          GADict::~GADict((GADict *)local_1d48);
          if (0xf < local_bd8) {
            FUN_1800187d0(&local_bf0,local_bf0);
          }
          local_be0 = 0;
          local_bd8 = 0xf;
          local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
          if (plStack_1d00 == (longlong *)0x0) {
            return param_2;
          }
          FUN_180018860();
          return param_2;
        }
        local_1d28 = (GADict *)FUN_1802d6b50(0x858);
        if (local_1d28 == (GADict *)0x0) {
          pDVar33 = (DynamicTextObject *)0x0;
        }
        else {
          pDVar33 = (DynamicTextObject *)
                    DocumentMarks::TextAreaMark::TextAreaMark((TextAreaMark *)local_1d28,false);
        }
        uVar51 = 0;
        local_1cf0 = (TextAreaMark *)pDVar33;
        pbVar28 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                  FUN_1801cd320(local_7f0,pbVar28);
        DocumentMarks::DynamicTextObject::setUniversalText(pDVar33,pbVar28);
        FUN_1800118b0(local_7f0);
        FUN_180184000(local_1c50,*(undefined8 *)(param_1 + 0x30),local_1cf0,uVar55);
        pTVar9 = local_1cf0;
        GName::GName(local_1a88,"Reflow");
        GADict::GetDict((GADict *)local_1d48,local_1c08);
        GName::GName(local_1a80,"ReflowStyle");
        this_00 = (GAName *)GADict::GetName((GADict *)local_1c08,local_1a78);
        bVar14 = GAName::operator==(this_00,"WrapThenShrink");
        if (bVar14) {
          TVar20 = 2;
        }
        else {
          bVar14 = GAName::operator==(this_00,"ShrinkWithoutWrapping");
          if (!bVar14) {
            local_1a48 = "Unknown text fitting style.";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_1a48,(ThrowInfo *)&DAT_1803b78c8);
          }
          TVar20 = 1;
        }
        DocumentMarks::TextAreaMark::SetTextFittingStyle(pTVar9,TVar20);
        GAName::~GAName((GAName *)local_1a78);
        GName::GName(local_1a70,"MinimumFontSize");
        bVar14 = GADict::Has((GADict *)local_1c08,local_1a70);
        if (bVar14) {
          GName::GName(local_1a68,"MinimumFontSize");
          pGVar34 = (GANumber *)GADict::GetNumber((GADict *)local_1c08,local_1a60);
          uVar51 = uVar19 | 0x600000;
          local_1d3c = uVar51;
          dVar53 = GANumber::Get(pGVar34);
          uVar52 = SUB84(dVar53,0);
          uVar54 = (undefined4)((ulonglong)dVar53 >> 0x20);
        }
        else {
          uVar52 = 0;
          uVar54 = 0x401c0000;
        }
        if ((uVar51 >> 0x15 & 1) != 0) {
          GANumber::~GANumber((GANumber *)local_1a60);
        }
        DocumentMarks::TextAreaMark::SetMinimumFontSize(pTVar9,(double)CONCAT44(uVar54,uVar52));
        GADict::~GADict((GADict *)local_1c08);
        if (local_1d40 != '\0') {
          GName::GName(local_1a58,"Position");
          bVar14 = GADict::Has((GADict *)local_1d48,local_1a58);
          if (!bVar14) {
            if (local_1d3f != 0) {
              DocumentMarks::MarkPosition::setReferenceObject
                        ((MarkPosition *)(local_1cf0 + 0x2f0),0);
            }
            goto LAB_180173e23;
          }
        }
        FUN_180180330(local_1d48,local_1cf0,&local_bd0,uVar55);
LAB_180173e23:
        FUN_18017b590(local_1d48,local_1cf0,(ulonglong)local_1d18 & 0xff);
        local_a08 = std::
                    _Func_impl_no_alloc<`public:_virtual_class_std::unique_ptr<ArtDoc::Group,std::default_delete<ArtDoc::Group>_>___cdecl_DocumentMarks::PDFPlusMarkReader::CreateGroup(void)___ptr64'::`43'::<lambda_2>,void,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
                    ::vftable;
        local_a00 = &local_1cf0;
        local_9d0 = &local_a08;
        FUN_1801837d0(local_1d48,&local_a08);
        if (local_9d0 != (undefined ***)0x0) {
          (*(code *)(*local_9d0)[4])(local_9d0,local_9d0 != &local_a08);
          local_9d0 = (undefined ***)0x0;
        }
        local_1208[0] = 1;
        local_11d0 = 0;
        local_11c8 = 0;
        lStack_11c0 = 0;
        local_11b8 = 0;
        uStack_11b0 = 0;
        local_11a8 = 0;
        local_1190 = 0;
        DocumentTypesetting::SetRecognitionContext
                  ((ContentObject *)local_1cf0,(RecognitionContext *)local_1208);
        pTVar9 = local_1cf0;
        uVar26 = GADict::GADict(local_1a50,(GADict *)local_1d48);
        bVar16 = FUN_180178cd0(uVar26);
        DocumentMarks::DynamicTextObject::SetUseStationInformation
                  ((DynamicTextObject *)pTVar9,(bool)(bVar16 ^ 1));
        pTVar9 = local_1cf0;
        local_1cf0 = (TextAreaMark *)0x0;
        *param_2 = (longlong)pTVar9;
        thunk_FUN_180066380(&local_11b8);
        if (lStack_11c0 != 0) {
          FUN_180018860();
        }
        pTVar9 = local_1cf0;
        if (local_1cf0 != (TextAreaMark *)0x0) {
          DocumentMarks::TextAreaMark::~TextAreaMark(local_1cf0);
          free(pTVar9);
        }
        GAName::~GAName((GAName *)local_1c58);
        GADict::~GADict((GADict *)local_1c50);
        if (0xf < uStack_bb8) {
          FUN_1800187d0(&local_bd0,local_bd0);
        }
        local_bc0 = (undefined *)0x0;
        uStack_bb8 = 0xf;
        local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
        if (0xf < uStack_b98) {
          FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
        }
        local_ba0 = (undefined *)0x0;
        uStack_b98 = 0xf;
        local_bb0 = 0;
        GADict::~GADict((GADict *)local_1d48);
        if (0xf < local_bd8) {
          FUN_1800187d0(&local_bf0,local_bf0);
        }
        local_be0 = 0;
        local_bd8 = 0xf;
        local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
        if (plStack_1d00 == (longlong *)0x0) {
          return param_2;
        }
        FUN_180018860();
        return param_2;
      }
      local_1d28 = (GADict *)FUN_1802d6b50(0x750);
      if (local_1d28 == (GADict *)0x0) {
        local_1ce0 = (DynamicTextObject *)0x0;
      }
      else {
        local_1ce0 = (DynamicTextObject *)
                     DocumentMarks::TextMark::TextMark((TextMark *)local_1d28,false);
      }
      local_b10[1] = 0;
      local_b00 = (undefined *)0x6;
      uStack_af8 = 0xf;
      local_b10[0] = 0x656372756f53;
      pbVar28 = ArtDoc::Dictionary::GetStringValue
                          (local_1cc0,
                           (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            *)local_b10);
      if (0xf < uStack_af8) {
        FUN_1800187d0(local_b10,local_b10[0]);
      }
      pDVar33 = local_1ce0;
      local_b00 = (undefined *)0x0;
      uStack_af8 = 0xf;
      local_b10[0] = local_b10[0] & 0xffffffffffffff00;
      pbVar28 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
                FUN_1801cd320(local_7b0,pbVar28);
      DocumentMarks::DynamicTextObject::setUniversalText(pDVar33,pbVar28);
      FUN_1800118b0(local_7b0);
      if (local_1d40 != '\0') {
        GName::GName(local_1ae0,"Position");
        bVar14 = GADict::Has((GADict *)local_1d48,local_1ae0);
        if (!bVar14) {
          if (local_1d3f != 0) {
            DocumentMarks::MarkPosition::setReferenceObject((MarkPosition *)(local_1ce0 + 0x2f0),0);
          }
          goto LAB_1801733a5;
        }
      }
      FUN_180180330(local_1d48,local_1ce0,&local_bd0,uVar55);
LAB_1801733a5:
      FUN_18017b590(local_1d48,local_1ce0,(ulonglong)local_1d18 & 0xff);
      local_988 = std::
                  _Func_impl_no_alloc<`public:_virtual_class_std::unique_ptr<ArtDoc::Group,std::default_delete<ArtDoc::Group>_>___cdecl_DocumentMarks::PDFPlusMarkReader::CreateGroup(void)___ptr64'::`29'::<lambda_1>,void,std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
                  ::vftable;
      local_980 = &local_1ce0;
      local_950 = &local_988;
      FUN_1801837d0(local_1d48,&local_988);
      if (local_950 != (undefined ***)0x0) {
        (*(code *)(*local_950)[4])(local_950,local_950 != &local_988);
        local_950 = (undefined ***)0x0;
      }
      local_12b8[0] = 3;
      local_1280 = 0;
      local_1278 = 0;
      lStack_1270 = 0;
      local_1268 = (void *)0x0;
      uStack_1260 = 0;
      local_1258 = 0;
      local_1240 = 0;
      DocumentTypesetting::SetRecognitionContext
                ((ContentObject *)local_1ce0,(RecognitionContext *)local_12b8);
      pDVar33 = local_1ce0;
      uVar26 = GADict::GADict(local_1ad8,(GADict *)local_1d48);
      bVar16 = FUN_180178cd0(uVar26);
      DocumentMarks::DynamicTextObject::SetUseStationInformation(pDVar33,(bool)(bVar16 ^ 1));
      pDVar33 = local_1ce0;
      local_1ce0 = (DynamicTextObject *)0x0;
      *param_2 = (longlong)pDVar33;
      if (local_1268 != (void *)0x0) {
        pvVar45 = local_1268;
        if ((0xfff < (ulonglong)(((local_1258 - (longlong)local_1268) / 0xb0) * 0xb0)) &&
           (pvVar45 = *(void **)((longlong)local_1268 + -8),
           0x1f < (ulonglong)((longlong)local_1268 + (-8 - (longlong)pvVar45)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        free(pvVar45);
        local_1268 = (void *)0x0;
        uStack_1260 = 0;
        local_1258 = 0;
      }
      if (lStack_1270 != 0) {
        FUN_180018860();
      }
      pDVar33 = local_1ce0;
      if (local_1ce0 != (DynamicTextObject *)0x0) {
        DocumentMarks::DynamicTextObject::~DynamicTextObject(local_1ce0);
        free(pDVar33);
      }
      if (0xf < uStack_bb8) {
        FUN_1800187d0(&local_bd0,local_bd0);
      }
      local_bc0 = (undefined *)0x0;
      uStack_bb8 = 0xf;
      local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
      if (0xf < uStack_b98) {
        FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
      }
      local_ba0 = (undefined *)0x0;
      uStack_b98 = 0xf;
      local_bb0 = 0;
      GADict::~GADict((GADict *)local_1d48);
      if (0xf < local_bd8) {
        FUN_1800187d0(&local_bf0,local_bf0);
      }
      local_be0 = 0;
      local_bd8 = 0xf;
      local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
      if (plStack_1d00 == (longlong *)0x0) {
        return param_2;
      }
      FUN_180018860();
      return param_2;
    }
    pppppppiVar44 = (int *******)&local_bf0;
    if (0xf < uVar3) {
      pppppppiVar44 = pppppppiVar31;
    }
    iVar18 = FUN_180021700(pppppppiVar44,lVar42,"GridMark",8);
    if (iVar18 != 0) {
      iVar18 = FUN_18016ef10(&local_bf0,&PTR_DAT_180326b90);
      if (iVar18 == 0) {
        GName::GName(local_1a30,"Source");
        GADict::GetStream((GADict *)local_1d48,local_1ba8);
        local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
        uVar26 = FUN_1801788e0(local_1608,*(undefined8 *)(param_1 + 0x30),local_1ba8,
                               *(undefined8 *)(param_1 + 0x28));
        FUN_1801716a0(&local_1828,uVar26);
        local_1d28 = (GADict *)FUN_1802d6b50(0x7c0);
        if (local_1d28 == (GADict *)0x0) {
          local_1c30 = 0;
        }
        else {
          if (lStack_1820 != 0) {
            LOCK();
            *(int *)(lStack_1820 + 8) = *(int *)(lStack_1820 + 8) + 1;
            UNLOCK();
          }
          local_1838 = local_1828;
          lStack_1830 = lStack_1820;
          local_1c30 = DocumentMarks::PDFPlusCutMark::PDFPlusCutMark
                                 ((PDFPlusCutMark *)local_1d28,&local_1838);
        }
        FUN_18017c5d0(local_1d48,local_1c30,&local_bd0,uVar55);
        FUN_18017c2b0(local_1d48,local_1c30,(ulonglong)local_1d18 & 0xff);
        *param_2 = local_1c30;
        local_1c30 = 0;
        FUN_180013ed0(&local_1828);
        GAStream::~GAStream((GAStream *)local_1ba8);
        if (0xf < uStack_bb8) {
          FUN_1800187d0(&local_bd0,local_bd0);
        }
        local_bc0 = (undefined *)0x0;
        uStack_bb8 = 0xf;
        local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
        if (0xf < uStack_b98) {
          FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
        }
        local_ba0 = (undefined *)0x0;
        uStack_b98 = 0xf;
        local_bb0 = 0;
        GADict::~GADict((GADict *)local_1d48);
        if (0xf < local_bd8) {
          FUN_1800187d0(&local_bf0,local_bf0);
        }
        local_be0 = 0;
        local_bd8 = 0xf;
        local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
        if (plStack_1d00 == (longlong *)0x0) {
          return param_2;
        }
        FUN_180018860();
        return param_2;
      }
      iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_RepeatForSeparations_180326bb0);
      if (iVar18 == 0) {
        FUN_180184a80(local_b90,local_1d48);
        pppppppuVar46 = local_b90;
        if (0xf < local_b78) {
          pppppppuVar46 = local_b90[0];
        }
        if ((local_b80 == 3) && (iVar18 = memcmp(pppppppuVar46,&DAT_180326c58,3), iVar18 == 0)) {
          GName::GName(local_1a28,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1ba0);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
          uVar26 = FUN_1801788e0(local_15f8,*(undefined8 *)(param_1 + 0x30),local_1ba0,
                                 *(undefined8 *)(param_1 + 0x28));
          FUN_1801716a0(local_1b38,uVar26);
          uVar26 = FUN_180172110(local_15e8,local_1b38,*(undefined8 *)(param_1 + 0x28));
          FUN_1800233b0(local_1b38,uVar26);
          FUN_180013ed0(local_15e8);
          FUN_18016f770(&local_1ca0,local_1b38);
          if (local_1d40 != '\0') {
            GName::GName(local_1a20,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1a20);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1ca0 + 0x2f0),0);
              }
              goto LAB_180174abf;
            }
          }
          FUN_180180330(local_1d48,local_1ca0,&local_bd0,uVar55);
LAB_180174abf:
          FUN_180182ce0(local_1d48,local_1ca0,uVar55);
          FUN_1801819b0(local_1d48,local_1ca0);
          *param_2 = local_1ca0;
          local_1ca0 = 0;
          FUN_180013ed0(local_1b38);
          GAStream::~GAStream((GAStream *)local_1ba0);
          FUN_1800118b0(local_b90);
          if (0xf < uStack_bb8) {
            FUN_1800187d0(&local_bd0,local_bd0);
          }
          local_bc0 = (undefined *)0x0;
          uStack_bb8 = 0xf;
          local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
          if (0xf < uStack_b98) {
            FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
          }
          local_ba0 = (undefined *)0x0;
          uStack_b98 = 0xf;
          local_bb0 = 0;
          GADict::~GADict((GADict *)local_1d48);
          if (0xf < local_bd8) {
            FUN_1800187d0(&local_bf0,local_bf0);
          }
          local_be0 = 0;
          local_bd8 = 0xf;
          local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
          if (plStack_1d00 == (longlong *)0x0) {
            return param_2;
          }
          FUN_180018860();
          return param_2;
        }
        pppppppuVar46 = local_b90;
        if (0xf < local_b78) {
          pppppppuVar46 = local_b90[0];
        }
        if ((local_b80 != 3) || (iVar18 = memcmp(pppppppuVar46,&DAT_180326c5c,3), iVar18 != 0)) {
          pppppppuVar46 = local_b90;
          if (0xf < local_b78) {
            pppppppuVar46 = local_b90[0];
          }
          if ((local_b80 != 3) || (iVar18 = memcmp(pppppppuVar46,&DAT_180326c60,3), iVar18 != 0)) {
            pppppppuVar46 = local_b90;
            if (0xf < local_b78) {
              pppppppuVar46 = local_b90[0];
            }
            if (((((local_b80 != 3) ||
                  (iVar18 = memcmp(pppppppuVar46,&DAT_180326c64,3), iVar18 != 0)) &&
                 (cVar15 = FUN_180021010(local_b90,&DAT_180326c68), cVar15 == '\0')) &&
                ((cVar15 = FUN_180021010(local_b90,&DAT_180326c6c), cVar15 == '\0' &&
                 (cVar15 = FUN_180021010(local_b90,&DAT_180326c70), cVar15 == '\0')))) &&
               (cVar15 = FUN_180021010(local_b90,&DAT_180326c74), cVar15 == '\0')) {
              FUN_1800118b0(local_b90);
              goto LAB_180177838;
            }
          }
        }
        GName::GName(local_1a18,"Source");
        GADict::GetStream((GADict *)local_1d48,local_1b98);
        local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
        uVar26 = FUN_1801788e0(local_15d8,*(undefined8 *)(param_1 + 0x30),local_1b98,
                               *(undefined8 *)(param_1 + 0x28));
        FUN_1801716a0(local_16e8,uVar26);
        FUN_18016f770(&local_1c98,local_16e8);
        if (local_1d40 != '\0') {
          GName::GName(local_1a10,"Position");
          bVar14 = GADict::Has((GADict *)local_1d48,local_1a10);
          if (!bVar14) {
            if (local_1d3f != 0) {
              DocumentMarks::MarkPosition::setReferenceObject
                        ((MarkPosition *)(local_1c98 + 0x2f0),0);
            }
            goto LAB_180174e1e;
          }
        }
        FUN_180180330(local_1d48,local_1c98,&local_bd0,uVar55);
LAB_180174e1e:
        FUN_18016e200(local_1d48,local_1c98,&local_bd0,uVar55);
        FUN_1801819b0(local_1d48,local_1c98);
        *param_2 = local_1c98;
        local_1c98 = 0;
        FUN_180013ed0(local_16e8);
        GAStream::~GAStream((GAStream *)local_1b98);
        FUN_1800118b0(local_b90);
        if (0xf < uStack_bb8) {
          FUN_1800187d0(&local_bd0,local_bd0);
        }
        local_bc0 = (undefined *)0x0;
        uStack_bb8 = 0xf;
        local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
        if (0xf < uStack_b98) {
          FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
        }
        local_ba0 = (undefined *)0x0;
        uStack_b98 = 0xf;
        local_bb0 = 0;
        GADict::~GADict((GADict *)local_1d48);
        if (0xf < local_bd8) {
          FUN_1800187d0(&local_bf0,local_bf0);
        }
        local_be0 = 0;
        local_bd8 = 0xf;
        local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
        if (plStack_1d00 == (longlong *)0x0) {
          return param_2;
        }
        FUN_180018860();
        return param_2;
      }
      iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_RepeatForGrid_180326ba0);
      if (iVar18 == 0) {
        GName::GName(local_1c38,"Source");
        GADict::GetStream((GADict *)local_1d48,local_1b90);
        local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
        uVar26 = FUN_1801788e0(local_15c8,*(undefined8 *)(param_1 + 0x30),local_1b90,
                               *(undefined8 *)(param_1 + 0x28));
        FUN_1801716a0(local_17a0,uVar26);
        local_1cc0 = (Dictionary *)0x0;
        FUN_18016f5b0(&local_1cb8,&local_1cc0,local_17a0);
        local_8f8 = 0;
        uStack_8f0 = 0;
        local_8e8 = 0;
        uStack_8e0 = 0;
        FUN_180010070(&local_8f8,"ObjectType",10);
        local_8d8 = 0;
        uStack_8d0 = 0;
        local_8c8 = 0;
        uStack_8c0 = 0;
        FUN_180010070(&local_8d8,"Context",7);
        local_8b8 = 0;
        uStack_8b0 = 0;
        local_8a8 = 0;
        uStack_8a0 = 0;
        FUN_180010070(&local_8b8,"Source",6);
        local_898 = 0;
        uStack_890 = 0;
        local_888 = 0;
        uStack_880 = 0;
        FUN_180010070(&local_898,"Position",8);
        local_878 = 0;
        uStack_870 = 0;
        local_868 = 0;
        uStack_860 = 0;
        FUN_180010070(&local_878,"Repetition",10);
        local_1d28 = (GADict *)&local_8f8;
        pGStack_1d20 = (GADict *)local_858;
        local_16d8 = local_1d28;
        puStack_16d0 = pGStack_1d20;
        FUN_180012730(local_1488,&local_1d28,&local_1ca8);
        cVar15 = FUN_180169530(local_1d48,local_1488);
        FUN_180019170(local_1488);
        _eh_vector_destructor_iterator_(&local_8f8,0x20,5,FUN_1800118b0);
        if (cVar15 != '\0') {
          DocumentMarks::DynamicObject::SetHasNewFeatures((DynamicObject *)local_1cb8,true);
        }
        local_1d58 = CONCAT44(uVar52,uVar55);
        FUN_180180480(local_1378,local_1d48,local_1cb8,&local_bd0);
        pPVar38 = ArtDoc::ContentObject::GetProperties((ContentObject *)local_1cb8);
        FUN_18016e9f0(pPVar38,&PTR_s_DocumentMarks_RepeatForGridMark__1803263a8,local_1378);
        FUN_180180ff0(local_12e8,local_1d48,local_1cb8);
        pPVar38 = ArtDoc::ContentObject::GetProperties((ContentObject *)local_1cb8);
        FUN_18016ebb0(pPVar38,&PTR_s_DocumentMarks_RepeatForGridMark__1803263b8,local_12e8);
        pPVar12 = local_1cb8;
        if (local_12ec == '\0') {
          local_12f0 = 1;
          local_12ec = '\x01';
          local_12eb = local_1c33;
          local_12e9 = local_1c31;
        }
        else if ((local_12e8[0] & 0xfffffffd) != 0) {
          local_1a08 = "HorizontalReference";
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(&local_1a08,(ThrowInfo *)&DAT_1803b78c8);
        }
        if (local_12f4 == '\0') {
          local_12f8 = 1;
          local_12f4 = '\x01';
          local_12f3 = local_1c33;
          local_12f1 = local_1c31;
        }
        else if (1 < local_12e8[0]) {
          local_1a00 = "VerticalReference";
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(&local_1a00,(ThrowInfo *)&DAT_1803b78c8);
        }
        local_1cb8 = (PDFPlusRepeatForGridMark *)0x0;
        *param_2 = (longlong)pPVar12;
        FUN_18006da40(local_1320);
        FUN_18006da40(local_1348);
        FUN_180022d90(local_1370);
        pPVar12 = local_1cb8;
        if (local_1cb8 != (PDFPlusRepeatForGridMark *)0x0) {
          DocumentMarks::PDFPlusRepeatForGridMark::~PDFPlusRepeatForGridMark(local_1cb8);
          free(pPVar12);
        }
        FUN_180013ed0(local_17a0);
        GAStream::~GAStream((GAStream *)local_1b90);
        if (0xf < uStack_bb8) {
          FUN_1800187d0(&local_bd0,local_bd0);
        }
        local_bc0 = (undefined *)0x0;
        uStack_bb8 = 0xf;
        local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
        if (0xf < uStack_b98) {
          FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
        }
        local_ba0 = (undefined *)0x0;
        uStack_b98 = 0xf;
        local_bb0 = 0;
        GADict::~GADict((GADict *)local_1d48);
        if (0xf < local_bd8) {
          FUN_1800187d0(&local_bf0,local_bf0);
        }
        local_be0 = 0;
        local_bd8 = 0xf;
        local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
        if (plStack_1d00 == (longlong *)0x0) {
          return param_2;
        }
        FUN_180018860();
        return param_2;
      }
      iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_RepeatForCount_180326bc0);
      if (iVar18 == 0) {
        GName::GName(local_19f8,"Source");
        GADict::GetStream((GADict *)local_1d48,local_1c28);
        local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
        uVar26 = FUN_1801788e0(local_15b8,*(undefined8 *)(param_1 + 0x30),local_1c28,
                               *(undefined8 *)(param_1 + 0x28));
        FUN_1801716a0(local_1bc8,uVar26);
        FUN_180184a80(local_af0,local_1d48);
        pppppppuVar46 = local_af0;
        if (0xf < local_ad8) {
          pppppppuVar46 = local_af0[0];
        }
        if ((local_ae0 == 3) && (iVar18 = memcmp(pppppppuVar46,&DAT_180326c58,3), iVar18 == 0)) {
          local_17e8 = 0;
          lStack_17e0 = 0;
          local_17d8 = 0;
          local_1688 = std::
                       _Func_impl_no_alloc<`public:_virtual_class_std::unique_ptr<ArtDoc::Group,std::default_delete<ArtDoc::Group>_>___cdecl_DocumentMarks::PDFPlusMarkReader::CreateGroup(void)___ptr64'::`115'::<lambda_4>,bool,DocumentMarks::PDFPlusRepeatForSeparationsMark&___ptr64>
                       ::vftable;
          local_1680 = &local_17e8;
          local_1650 = &local_1688;
          ArtDoc::VisitorBase::VisitorBase((VisitorBase *)&local_948);
          local_948 = ArtDoc::SimpleVisitor<DocumentMarks::PDFPlusRepeatForSeparationsMark>::vftable
          ;
          local_940 = ArtDoc::SimpleVisitor<DocumentMarks::PDFPlusRepeatForSeparationsMark>::vftable
          ;
          local_900 = (undefined ***)0x0;
          if (local_1650 != (undefined ***)0x0) {
            if (local_1650 == &local_1688) {
              local_900 = (undefined ***)(*(code *)(*local_1650)[1])(local_1650,local_938);
              FUN_180013b30(&local_1688);
            }
            else {
              local_900 = local_1650;
              local_1650 = (undefined ***)0x0;
            }
          }
          FUN_180013b30(&local_1688);
          pCVar24 = ArtPaint::FormPaint::GetContent(local_1bc8[0]);
          (**(code **)(*(longlong *)pCVar24 + 0x10))(pCVar24,&local_948);
          if ((lStack_17e0 - local_17e8 & 0xfffffffffffffff8U) != 8) {
            local_19e8 = "Wrong number of inner marks.";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_19e8,(ThrowInfo *)&DAT_1803b78c8);
          }
          FUN_18016f530(&local_1c48,local_1bc8);
          if (local_1d40 != '\0') {
            GName::GName(local_19f0,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_19f0);
            if (!bVar14) goto LAB_18017569f;
          }
          FUN_180180330(local_1d48,local_1c48,&local_bd0,uVar55);
LAB_18017569f:
          FUN_180182740(local_1d48,local_1c48,uVar55);
          lVar42 = local_1c48;
          local_1c48 = 0;
          *param_2 = lVar42;
          FUN_1801702d0(&local_1c48);
          FUN_1800bc8d0(&local_948);
          FID_conflict__vector<CHN*___ptr64,std::allocator<CHN*___ptr64>_>(&local_17e8);
          FUN_1800118b0(local_af0);
          FUN_180013ed0(local_1bc8);
          GAStream::~GAStream((GAStream *)local_1c28);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        pppppppuVar46 = local_af0;
        if (0xf < local_ad8) {
          pppppppuVar46 = local_af0[0];
        }
        if ((((local_ae0 == 3) && (iVar18 = memcmp(pppppppuVar46,&DAT_180326c5c,3), iVar18 == 0)) ||
            (cVar15 = FUN_180021010(local_af0,&DAT_180326c64), cVar15 != '\0')) ||
           (cVar15 = FUN_180021010(local_af0,&DAT_180326c68), cVar15 != '\0')) {
          FUN_18016f530(&local_1c78,local_1bc8);
          if (local_1d40 != '\0') {
            GName::GName(local_19e0,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_19e0);
            if (!bVar14) goto LAB_18017585d;
          }
          FUN_180180330(local_1d48,local_1c78,&local_bd0,uVar55);
LAB_18017585d:
          FUN_18016dc70(local_1d48,local_1c78,&local_bd0,uVar55);
          FUN_180183340(local_1d48,local_1c78,&local_bd0);
          lVar42 = local_1c78;
          local_1c78 = 0;
          *param_2 = lVar42;
          FUN_1801702d0(&local_1c78);
          FUN_1800118b0(local_af0);
          FUN_180013ed0(local_1bc8);
          GAStream::~GAStream((GAStream *)local_1c28);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        FUN_1800118b0(local_af0);
        FUN_180013ed0(local_1bc8);
        GAStream::~GAStream((GAStream *)local_1c28);
      }
      else {
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_RepeatForStations_180326bd0);
        if (iVar18 == 0) {
          GName::GName(local_19d8,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1b60);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38) | 2;
          FUN_1801788e0(&local_1be8,*(undefined8 *)(param_1 + 0x30),local_1b60,
                        *(undefined8 *)(param_1 + 0x28));
          if (lStack_1be0 != 0) {
            LOCK();
            *(int *)(lStack_1be0 + 8) = *(int *)(lStack_1be0 + 8) + 1;
            UNLOCK();
          }
          local_1818 = local_1be8;
          lStack_1810 = lStack_1be0;
          FUN_180177c50(&local_1818);
          if (lStack_1be0 != 0) {
            LOCK();
            *(int *)(lStack_1be0 + 8) = *(int *)(lStack_1be0 + 8) + 1;
            UNLOCK();
          }
          local_1808 = local_1be8;
          lStack_1800 = lStack_1be0;
          uVar26 = FUN_1801716a0(local_15a8,&local_1808);
          FUN_1800233b0(&local_1be8,uVar26);
          FUN_180013ed0(local_15a8);
          local_a30[0] = 0;
          uStack_a20 = 0;
          local_a18 = (undefined *)0x0;
          uStack_a10 = 0xf;
          local_a28 = 0;
          FUN_18016f7f0(&local_1c70,&local_1be8,local_a30);
          DocumentMarks::VDPSimpleRule::~VDPSimpleRule((VDPSimpleRule *)local_a30);
          FUN_180181cc0(local_1d48,local_1c70,&local_bd0,uVar55);
          FUN_180182410(local_1d48,local_1c70);
          FUN_18017b590(local_1d48,local_1c70,(ulonglong)local_1d18 & 0xff);
          *param_2 = local_1c70;
          local_1c70 = 0;
          FUN_180013ed0(&local_1be8);
          GAStream::~GAStream((GAStream *)local_1b60);
          if (0xf < uStack_bb8) {
            FUN_1800187d0(&local_bd0,local_bd0);
          }
          local_bc0 = (undefined *)0x0;
          uStack_bb8 = 0xf;
          local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
          if (0xf < uStack_b98) {
            FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
          }
          local_ba0 = (undefined *)0x0;
          uStack_b98 = 0xf;
          local_bb0 = 0;
          GADict::~GADict((GADict *)local_1d48);
          if (0xf < local_bd8) {
            FUN_1800187d0(&local_bf0,local_bf0);
          }
          local_be0 = 0;
          local_bd8 = 0xf;
          local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
          if (plStack_1d00 == (longlong *)0x0) {
            return param_2;
          }
          FUN_180018860();
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_Resize_180326be0);
        if (iVar18 == 0) {
          GName::GName(local_19d0,"Size");
          GADict::GetDict((GADict *)local_1d48,local_1c20);
          GName::GName(local_19c8,"Width");
          pGVar39 = (GAObject *)GADict::Get((GADict *)local_1c20,local_19b0);
          uVar51 = uVar19 | 0x40;
          local_1d3c = uVar51;
          bVar14 = GAObject::IsDict(pGVar39);
          if (bVar14) {
LAB_180175cd3:
            bVar14 = true;
          }
          else {
            GName::GName(local_19c0,"Height");
            pGVar39 = (GAObject *)GADict::Get((GADict *)local_1c20,local_19b8);
            uVar51 = uVar19 | 0xc0;
            local_1d3c = uVar51;
            bVar14 = GAObject::IsDict(pGVar39);
            if (bVar14) goto LAB_180175cd3;
            bVar14 = false;
          }
          if ((char)uVar51 < '\0') {
            uVar51 = uVar51 & 0xffffff7f;
            GAObject::~GAObject((GAObject *)local_19b8);
          }
          if ((uVar51 & 0x40) != 0) {
            GAObject::~GAObject((GAObject *)local_19b0);
          }
          if (bVar14) {
            GName::GName(local_19a8,"Source");
            GADict::GetStream((GADict *)local_1d48,local_1b88);
            local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
            uVar26 = FUN_1801788e0(local_1598,*(undefined8 *)(param_1 + 0x30),local_1b88,
                                   *(undefined8 *)(param_1 + 0x28));
            FUN_1801716a0(local_1790,uVar26);
            FUN_18016fed0(local_16a8);
            pCVar24 = ArtPaint::FormPaint::GetContent(local_1790[0]);
            (**(code **)(*(longlong *)pCVar24 + 0x10))(pCVar24,local_16a8);
            if (local_1698 == (DynamicMark *)0x0) {
              local_19a0 = "Mark contains unexpected objects.";
                    /* WARNING: Subroutine does not return */
              _CxxThrowException(&local_19a0,(ThrowInfo *)&DAT_1803b78c8);
            }
            uVar26 = DocumentMarks::DynamicMark::GetSourceContent(local_1698);
            uVar26 = FUN_180172110(local_1588,uVar26);
            FUN_18016f250(&local_1cd0,uVar26);
            FUN_180013ed0(local_1588);
            FUN_180013ed0(local_1578);
            pDVar11 = local_1cd0;
            pCVar40 = (ColorList<ArtColor::ColorSpacePolicy> *)
                      DocumentMarks::DynamicMark::GetOrderedSourceColorSpace(local_1698);
            DocumentMarks::DynamicMark::setSourceColorants(pDVar11,pCVar40);
            FUN_180022cb0(local_de0);
            pDVar11 = local_1cd0;
            CVar21 = DocumentMarks::DynamicObject::getColorType((DynamicObject *)local_1698,0);
            DocumentMarks::DynamicObject::setColorType((DynamicObject *)pDVar11,CVar21,0);
            pDVar11 = local_1cd0;
            pvVar41 = (variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
                       *)DocumentMarks::DynamicObject::GetTargetSeparations
                                   ((DynamicObject *)local_1698,(PaintAttribute)local_f08);
            DocumentMarks::DynamicObject::SetTargetSeparations((DynamicObject *)pDVar11,pvVar41,0);
            FUN_18006d990(local_f08);
            pDVar11 = local_1cd0;
            CVar21 = DocumentMarks::DynamicObject::getColorType((DynamicObject *)local_1698,1);
            DocumentMarks::DynamicObject::setColorType((DynamicObject *)pDVar11,CVar21,1);
            FUN_180185ff0(local_1d48);
            FUN_180179da0(local_1d48,local_1cd0,&local_bd0,uVar55);
            FUN_18017a330(local_1d48,local_1cd0,&local_bd0,uVar55);
            pDVar11 = local_1cd0;
            local_1cd0 = (DynamicMark *)0x0;
            *param_2 = (longlong)pDVar11;
            FUN_180170150(&local_1cd0);
            local_16a0 = ArtDoc::Visitor<DocumentMarks::CustomMark>::_vftable_;
            ArtDoc::VisitorBase::~VisitorBase(local_16a8);
            FUN_180013ed0(local_1790);
            GAStream::~GAStream((GAStream *)local_1b88);
            GADict::~GADict((GADict *)local_1c20);
            FUN_1800118b0(&local_bd0);
            FUN_1800118b0(&local_bb0);
            GADict::~GADict((GADict *)local_1d48);
            FUN_1800118b0(&local_bf0);
            FUN_180013ed0(&local_1d08);
            return param_2;
          }
          GName::GName(local_1998,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1b80);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
          uVar26 = FUN_1801788e0(local_1568,*(undefined8 *)(param_1 + 0x30),local_1b80,
                                 *(undefined8 *)(param_1 + 0x28));
          FUN_1801716a0(local_1768,uVar26);
          local_1d18 = (Dictionary *)CONCAT44(local_1d18._4_4_,1);
          FUN_18016f870(&local_1c90,local_1768,&local_1d18);
          FUN_180011dc0(local_5a8,"Version");
          FUN_180011dc0(local_588,"ObjectType");
          FUN_180011dc0(local_568,"Context");
          FUN_180011dc0(local_548,"Source");
          FUN_180011dc0(local_528,"Position");
          FUN_180011dc0(local_508,&DAT_180327254);
          local_1d28 = local_5a8;
          pGStack_1d20 = local_4e8;
          local_1778 = local_1d28;
          pGStack_1770 = pGStack_1d20;
          FUN_180012730(local_1470,&local_1d28,&local_1ca7);
          cVar15 = FUN_180169530(local_1d48,local_1470);
          FUN_180019170(local_1470);
          _eh_vector_destructor_iterator_(local_5a8,0x20,6,FUN_1800118b0);
          if (cVar15 != '\0') {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1c90,true);
          }
          FUN_18017eff0(local_1d48,local_1c90,&local_bd0,uVar55);
          if (local_1d40 != '\0') {
            GName::GName(local_1990,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1990);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1c90 + 0x2f0),0);
              }
              goto LAB_1801761dd;
            }
          }
          FUN_180180330(local_1d48,local_1c90,&local_bd0,uVar55);
LAB_1801761dd:
          pDVar8 = local_1c90;
          local_1c90 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_1801703c0(&local_1c90);
          FUN_180013ed0(local_1768);
          GAStream::~GAStream((GAStream *)local_1b80);
          GADict::~GADict((GADict *)local_1c20);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_DAT_180326bf0);
        if (iVar18 == 0) {
          GName::GName(local_1988,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1b78);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
          uVar26 = FUN_1801788e0(local_1558,*(undefined8 *)(param_1 + 0x30),local_1b78,
                                 *(undefined8 *)(param_1 + 0x28));
          FUN_1801716a0(local_1758,uVar26);
          FUN_18016fed0(local_16c8);
          pCVar24 = ArtPaint::FormPaint::GetContent(local_1758[0]);
          (**(code **)(*(longlong *)pCVar24 + 0x10))(pCVar24,local_16c8);
          if (local_16b8 == (DynamicMark *)0x0) {
            local_1980 = "Mark contains unexpected objects.";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_1980,(ThrowInfo *)&DAT_1803b78c8);
          }
          uVar26 = DocumentMarks::DynamicMark::GetSourceContent(local_16b8);
          uVar26 = FUN_180172110(local_1548,uVar26);
          FUN_18016f2c0(&local_1cd8,uVar26);
          FUN_180013ed0(local_1548);
          FUN_180013ed0(local_1538);
          pDVar11 = local_1cd8;
          pCVar40 = (ColorList<ArtColor::ColorSpacePolicy> *)
                    DocumentMarks::DynamicMark::GetOrderedSourceColorSpace(local_16b8);
          DocumentMarks::DynamicMark::setSourceColorants(pDVar11,pCVar40);
          FUN_180022cb0(local_e98);
          pDVar11 = local_1cd8;
          CVar21 = DocumentMarks::DynamicObject::getColorType((DynamicObject *)local_16b8,0);
          DocumentMarks::DynamicObject::setColorType((DynamicObject *)pDVar11,CVar21,0);
          pDVar11 = local_1cd8;
          pvVar41 = (variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
                     *)DocumentMarks::DynamicObject::GetTargetSeparations
                                 ((DynamicObject *)local_16b8,(PaintAttribute)local_f78);
          DocumentMarks::DynamicObject::SetTargetSeparations((DynamicObject *)pDVar11,pvVar41,0);
          FUN_18006d990(local_f78);
          pDVar11 = local_1cd8;
          CVar21 = DocumentMarks::DynamicObject::getColorType((DynamicObject *)local_16b8,1);
          DocumentMarks::DynamicObject::setColorType((DynamicObject *)pDVar11,CVar21,1);
          pDVar11 = local_1cd8;
          pvVar41 = (variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
                     *)DocumentMarks::DynamicObject::GetTargetSeparations
                                 ((DynamicObject *)local_16b8,(PaintAttribute)local_fe8);
          DocumentMarks::DynamicObject::SetTargetSeparations((DynamicObject *)pDVar11,pvVar41,1);
          FUN_18006d990(local_fe8);
          FUN_180180330(local_1d48,local_1cd8,&local_bd0,uVar55);
          FUN_18017a450(local_1d48,local_1cd8,uVar55);
          pDVar11 = local_1cd8;
          local_1cd8 = (DynamicMark *)0x0;
          *param_2 = (longlong)pDVar11;
          FUN_180170180(&local_1cd8);
          local_16c0 = ArtDoc::Visitor<DocumentMarks::CustomMark>::_vftable_;
          ArtDoc::VisitorBase::~VisitorBase(local_16c8);
          FUN_180013ed0(local_1758);
          GAStream::~GAStream((GAStream *)local_1b78);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_ExternalFile_180326c00);
        if (iVar18 == 0) {
          GName::GName(local_1978,"URI");
          bVar14 = (bool)GADict::GetString((GADict *)local_1d48,local_1970);
          ArtDocGlue::PDFConverters::UTF8String(local_830,bVar14);
          GAString::~GAString((GAString *)local_1970);
          FUN_18016f3a0(&local_1cb0,local_830);
          FUN_180011dc0(local_2a8,"ObjectType");
          FUN_180011dc0(local_288,"Context");
          FUN_180011dc0(local_268,&DAT_180326ccc);
          FUN_180011dc0(local_248,"ResolvedURI");
          FUN_180011dc0(local_228,"Position");
          FUN_180011dc0(local_208,"Rotation");
          FUN_180011dc0(local_1e8,"Color");
          local_1d28 = local_2a8;
          pGStack_1d20 = local_1c8;
          local_1748 = local_1d28;
          pGStack_1740 = pGStack_1d20;
          FUN_180012730(local_1458,&local_1d28,&local_1ca6);
          cVar15 = FUN_180169530(local_1d48,local_1458);
          FUN_180019170(local_1458);
          _eh_vector_destructor_iterator_(local_2a8,0x20,7,FUN_1800118b0);
          if (cVar15 != '\0') {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1cb0,true);
          }
          if (local_1d40 != '\0') {
            GName::GName(local_1968,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1968);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1cb0 + 0x2f0),0);
              }
              goto LAB_18017676e;
            }
          }
          FUN_180180330(local_1d48,local_1cb0,&local_bd0,uVar55);
LAB_18017676e:
          local_1960 = &local_1cb0;
          FUN_18016db00(local_628,&local_1960);
          FUN_1801837d0(local_1d48,local_628);
          FUN_180013b30(local_628);
          FUN_18017b590(local_1d48,local_1cb0,(ulonglong)local_1d18 & 0xff);
          pDVar8 = local_1cb0;
          local_1cb0 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_180170210(&local_1cb0);
          FUN_1800118b0(local_830);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_InputFile_180326c10);
        if (iVar18 == 0) {
          FUN_18016f400(&local_1cc8);
          FUN_180011dc0(local_4e8,"ObjectType");
          FUN_180011dc0(local_4c8,"Context");
          FUN_180011dc0(local_4a8,"Position");
          FUN_180011dc0(local_488,"Rotation");
          FUN_180011dc0(local_468,&DAT_1803272f0);
          FUN_180011dc0(local_448,"Color");
          local_1d28 = local_4e8;
          pGStack_1d20 = local_428;
          local_1738 = local_1d28;
          pGStack_1730 = pGStack_1d20;
          FUN_180012730(local_1440,&local_1d28,&local_1ca5);
          cVar15 = FUN_180169530(local_1d48,local_1440);
          FUN_180019170(local_1440);
          _eh_vector_destructor_iterator_(local_4e8,0x20,6,FUN_1800118b0);
          if (cVar15 != '\0') {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1cc8,true);
          }
          if (local_1d40 != '\0') {
            GName::GName(local_1958,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1958);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1cc8 + 0x2f0),0);
              }
              goto LAB_1801769f8;
            }
          }
          FUN_180180330(local_1d48,local_1cc8,&local_bd0,uVar55);
LAB_1801769f8:
          FUN_18017ec00(local_1d48,local_1cc8);
          FUN_18017e400(local_1d48,local_1cc8);
          FUN_18017e820(local_1d48,local_1cc8);
          pDVar8 = local_1cc8;
          local_1cc8 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_180170240(&local_1cc8);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_Barcode_180326b70);
        if (iVar18 == 0) {
          plVar50 = *(longlong **)(param_1 + 0x30);
          pcVar5 = *(code **)(*plVar50 + 0x10);
          GName::GName(local_1950,"Source");
          uVar26 = GADict::GetStream((GADict *)local_1d48,local_1948);
          (*pcVar5)(plVar50,&local_17d0,uVar26);
          GAStream::~GAStream((GAStream *)local_1948);
          if (local_17c8[0] == 0) {
LAB_180177bf8:
            local_1928 = "Invalid source content for barcode mark";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_1928,(ThrowInfo *)&DAT_1803b78c8);
          }
          local_1d58 = local_1d58 & 0xffffffff00000000;
          lVar42 = __RTDynamicCast(local_17d0,0,&ArtDoc::Group::RTTI_Type_Descriptor,
                                   &DocumentBarCode::BarCode::RTTI_Type_Descriptor);
          if (lVar42 == 0) goto LAB_180177bf8;
          this_03 = DocumentBarCode::BarCode::GetParameters(local_17d0);
          TVar22 = BarCodeWrapper::Parameters::GetType(this_03);
          bVar14 = DocumentMarks::IsAllowedInPDFPlusBarcodeMark(TVar22);
          if (!bVar14) {
            local_1940 = "Barcode type unsupported for barcode mark";
                    /* WARNING: Subroutine does not return */
            _CxxThrowException(&local_1940,(ThrowInfo *)&DAT_1803b78c8);
          }
          uVar26 = FUN_18001e320(local_1528,local_17c8);
          uVar26 = FUN_1801716a0(local_1518,uVar26);
          FUN_18016f1e0(&local_1cf8,uVar26);
          FUN_180013ed0(local_1518);
          FUN_180011dc0(local_1c8,"ObjectType");
          FUN_180011dc0(local_1a8,"Context");
          FUN_180011dc0(local_188,"Source");
          FUN_180011dc0(local_168,"Value");
          FUN_180011dc0(local_148,"DecimalValue");
          FUN_180011dc0(local_128,"SupplementalValue");
          FUN_180011dc0(local_108,"CompositeValue");
          FUN_180011dc0(local_e8,"AutoVersion");
          FUN_180011dc0(local_c8,"Position");
          FUN_180011dc0(local_a8,"Rotation");
          FUN_180011dc0(local_88,"Color");
          local_1d28 = local_1c8;
          pGStack_1d20 = (GADict *)local_68;
          local_1728 = local_1d28;
          puStack_1720 = (ulonglong *)pGStack_1d20;
          FUN_180012730(local_1428,&local_1d28,&local_1ca4);
          cVar15 = FUN_180169530(local_1d48,local_1428);
          FUN_180019170(local_1428);
          _eh_vector_destructor_iterator_(local_1c8,0x20,0xb,FUN_1800118b0);
          if (cVar15 != '\0') {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1cf8,true);
          }
          FUN_180184710(local_1d48,local_1cf8);
          FUN_180183e70(local_1d48,local_1cf8);
          FUN_18017c0d0(local_1d48,local_1cf8);
          FUN_180179b90(local_1d48,local_1cf8);
          if (local_1d40 != '\0') {
            GName::GName(local_1938,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1938);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1cf8 + 0x2f0),0);
              }
              goto LAB_180176dee;
            }
          }
          FUN_180180330(local_1d48,local_1cf8,&local_bd0,uVar55);
LAB_180176dee:
          local_1930 = &local_1cf8;
          FUN_18016db30(local_5e8,&local_1930);
          FUN_1801837d0(local_1d48,local_5e8);
          FUN_180013b30(local_5e8);
          FUN_180179c30(local_1d48,local_1cf8,(ulonglong)local_1d18 & 0xff);
          pDVar8 = local_1cf8;
          local_1cf8 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_180170120(&local_1cf8);
          FUN_1800d5170(&local_17d0);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_Dimension_180326b80);
        if (iVar18 == 0) {
          plVar50 = *(longlong **)(param_1 + 0x30);
          pcVar5 = *(code **)(*plVar50 + 0x10);
          GName::GName(local_1920,"Source");
          uVar26 = GADict::GetStream((GADict *)local_1d48,local_1918);
          (*pcVar5)(plVar50,&local_17b8,uVar26);
          GAStream::~GAStream((GAStream *)local_1918);
          if (local_17b0[0] != 0) {
            local_1d58 = local_1d58 & 0xffffffff00000000;
            lVar42 = __RTDynamicCast(local_17b8,0,&ArtDoc::Group::RTTI_Type_Descriptor,
                                     &DocumentDimensions::Box::RTTI_Type_Descriptor);
            if (lVar42 != 0) {
              uVar26 = FUN_18001e320(local_1508,local_17b0);
              uVar26 = FUN_1801716a0(local_14f8,uVar26);
              FUN_18016f330(&local_1c40,uVar26);
              FUN_180013ed0(local_14f8);
              FUN_180011dc0(local_428,"ObjectType");
              FUN_180011dc0(local_408,"Context");
              FUN_180011dc0(local_3e8,"Source");
              FUN_180011dc0(local_3c8,"Reference");
              FUN_180011dc0(local_3a8,"ReferenceID");
              FUN_180011dc0(local_388,"ReferenceBounds");
              local_1d28 = local_428;
              pGStack_1d20 = local_368;
              local_1718 = local_1d28;
              pGStack_1710 = pGStack_1d20;
              FUN_180012730(local_1410,&local_1d28,&local_1ca3);
              cVar15 = FUN_180169530(local_1d48,local_1410);
              FUN_180019170(local_1410);
              _eh_vector_destructor_iterator_(local_428,0x20,6,FUN_1800118b0);
              if (cVar15 != '\0') {
                DocumentMarks::DynamicObject::SetHasNewFeatures(local_1c40,true);
              }
              FUN_18017ced0(local_1d48,local_1c40);
              pDVar8 = local_1c40;
              local_1c40 = (DynamicObject *)0x0;
              *param_2 = (longlong)pDVar8;
              FUN_1801701e0(&local_1c40);
              FUN_1800d5170(&local_17b8);
              FUN_1800118b0(&local_bd0);
              FUN_1800118b0(&local_bb0);
              GADict::~GADict((GADict *)local_1d48);
              FUN_1800118b0(&local_bf0);
              FUN_180013ed0(&local_1d08);
              return param_2;
            }
          }
          local_1910 = "Invalid source content for dimensions mark";
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(&local_1910,(ThrowInfo *)&DAT_1803b78c8);
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_Position_180326c20);
        if (iVar18 == 0) {
          local_14e8 = 0;
          uStack_14e0 = 0;
          FUN_18016f4d0(&local_1c88,&local_14e8);
          FUN_180011dc0(local_768,"ObjectType");
          FUN_180011dc0(local_748,"Context");
          FUN_180011dc0(local_728,"Position");
          FUN_180011dc0(local_708,&DAT_180327254);
          local_1d28 = local_768;
          pGStack_1d20 = (GADict *)local_6e8;
          local_1708 = local_1d28;
          puStack_1700 = pGStack_1d20;
          FUN_180012730(local_13f8,&local_1d28,&local_1ca1);
          cVar15 = FUN_180169530(local_1d48,local_13f8);
          FUN_180019170(local_13f8);
          _eh_vector_destructor_iterator_(local_768,0x20,4,FUN_1800118b0);
          if (cVar15 != '\0') {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1c88,true);
          }
          FUN_18017ee50(local_1d48,local_1c88,&local_bd0,uVar55);
          if (local_1d40 != '\0') {
            GName::GName(local_1908,"Position");
            bVar14 = GADict::Has((GADict *)local_1d48,local_1908);
            if (!bVar14) {
              if (local_1d3f != 0) {
                DocumentMarks::MarkPosition::setReferenceObject
                          ((MarkPosition *)(local_1c88 + 0x2f0),0);
              }
              goto LAB_180177319;
            }
          }
          FUN_180180330(local_1d48,local_1c88,&local_bd0,uVar55);
LAB_180177319:
          pDVar8 = local_1c88;
          local_1c88 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_1801702a0(&local_1c88);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_RepeatForObjects_180326c30);
        if (iVar18 == 0) {
          GName::GName(local_1900,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1b70);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
          FUN_1801788e0(local_1b58,*(undefined8 *)(param_1 + 0x30),local_1b70,
                        *(undefined8 *)(param_1 + 0x28));
          uVar26 = FUN_18001e320(local_14d8,local_1b58);
          FUN_180177c50(uVar26);
          uVar26 = FUN_18001e320(local_14c8,local_1b58);
          uVar26 = FUN_1801716a0(local_14b8,uVar26);
          FUN_1800233b0(local_1b58,uVar26);
          FUN_180013ed0(local_14b8);
          FUN_18016f640(&local_1c18,local_1b58,&DAT_1803050d0);
          FUN_180181440(local_1d48,local_1c18,uVar55);
          lVar42 = local_1c18;
          local_1c18 = 0;
          *param_2 = lVar42;
          FUN_180170330(&local_1c18);
          FUN_180013ed0(local_1b58);
          GAStream::~GAStream((GAStream *)local_1b70);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
        iVar18 = FUN_18016ef10(&local_bf0,&PTR_s_PlateID_180326c40);
        if (iVar18 == 0) {
          GName::GName(local_18f8,"Source");
          GADict::GetStream((GADict *)local_1d48,local_1b68);
          local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
          FUN_1801788e0(local_1b28,*(undefined8 *)(param_1 + 0x30),local_1b68,
                        *(undefined8 *)(param_1 + 0x28));
          uVar26 = FUN_18001e320(local_14a8,local_1b28);
          uVar26 = FUN_1801716a0(local_1498,uVar26);
          FUN_1800233b0(local_1b28,uVar26);
          FUN_180013ed0(local_1498);
          FUN_18017f870(local_858,local_1d48,*(undefined8 *)(param_1 + 0x28));
          FUN_18016f450(&local_1c68,local_1b28,local_858);
          FUN_180180030(local_1d48,local_1c68);
          FUN_18017fda0(local_1d48,local_1c68,&local_bd0,uVar55);
          if (local_838 == '\0') {
            FUN_180011dc0(local_368,"ObjectType");
            local_1d3c = uVar19 | 0x100;
            FUN_180011dc0(local_348,"Context");
            local_1d3c = uVar19 | 0x300;
            FUN_180011dc0(local_328,"Source");
            local_1d3c = uVar19 | 0x700;
            FUN_180011dc0(local_308,"Repetition");
            local_1d3c = uVar19 | 0xf00;
            FUN_180011dc0(local_2e8,"Color");
            local_1d3c = uVar19 | 0x1f00;
            FUN_180011dc0(local_2c8,"Position");
            local_1d3c = uVar19 | 0x7f00;
            local_1d28 = local_368;
            pGStack_1d20 = local_2a8;
            local_16f8 = local_1d28;
            pGStack_16f0 = pGStack_1d20;
            FUN_180012730(local_13e0,&local_1d28,&local_1ca2);
            uVar19 = uVar19 | 0xff00;
            local_1d3c = uVar19;
            cVar15 = FUN_180169530(local_1d48,local_13e0);
            if (cVar15 == '\0') {
              bVar14 = false;
              goto LAB_180177753;
            }
          }
          bVar14 = true;
LAB_180177753:
          if (uVar19 >> 0xf != 0) {
            uVar19 = uVar19 & 0xffff7fff;
            FUN_180019170(local_13e0);
          }
          if ((uVar19 >> 0xe & 1) != 0) {
            _eh_vector_destructor_iterator_(local_368,0x20,6,FUN_1800118b0);
          }
          if (bVar14) {
            DocumentMarks::DynamicObject::SetHasNewFeatures(local_1c68,true);
          }
          pDVar8 = local_1c68;
          local_1c68 = (DynamicObject *)0x0;
          *param_2 = (longlong)pDVar8;
          FUN_180170270(&local_1c68);
          FUN_1800118b0(local_858);
          FUN_180013ed0(local_1b28);
          GAStream::~GAStream((GAStream *)local_1b68);
          FUN_1800118b0(&local_bd0);
          FUN_1800118b0(&local_bb0);
          GADict::~GADict((GADict *)local_1d48);
          FUN_1800118b0(&local_bf0);
          FUN_180013ed0(&local_1d08);
          return param_2;
        }
      }
LAB_180177838:
      FUN_1800118b0(&local_bd0);
      FUN_1800118b0(&local_bb0);
      goto LAB_180177854;
    }
    GName::GName(local_1a38,"Source");
    GADict::GetStream((GADict *)local_1d48,local_1bb0);
    local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
    uVar26 = FUN_1801788e0(local_1628,*(undefined8 *)(param_1 + 0x30),local_1bb0,
                           *(undefined8 *)(param_1 + 0x28));
    FUN_1801716a0(&local_1b48,uVar26);
    FUN_18017d6a0(local_6e8,local_1d48,&local_bd0,uVar55);
    local_1d28 = (GADict *)FUN_1802d6b50(0x698);
    if (local_1d28 == (GADict *)0x0) {
      this_01 = (ContentObject *)0x0;
    }
    else {
      if (lStack_1b40 != 0) {
        LOCK();
        *(int *)(lStack_1b40 + 8) = *(int *)(lStack_1b40 + 8) + 1;
        UNLOCK();
      }
      local_1868 = local_1b48;
      lStack_1860 = lStack_1b40;
      this_01 = (ContentObject *)
                DocumentMarks::CustomMark::CustomMark((CustomMark *)local_1d28,&local_1868,0x1cf);
    }
    local_a70 = 0;
    uStack_a68 = 0;
    local_a60 = 0;
    uStack_a58 = 0;
    lVar42 = -1;
    do {
      lVar49 = lVar42 + 1;
      lVar7 = lVar42 + 1;
      lVar42 = lVar49;
    } while ("Custom Mark"[lVar7] != '\0');
    FUN_180010070(&local_a70,"Custom Mark",lVar49);
    pbVar35 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              (**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))();
    pbVar28 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
              DocumentMarks::CreateMarkName(local_810,pbVar35);
    ArtDoc::ContentObject::SetName(this_01,pbVar28);
    FUN_1800118b0(local_810);
    FUN_1800118b0(&local_a70);
    DocumentMarks::MarkPosition::setReferenceObject((MarkPosition *)(this_01 + 0x2f0),0);
    ArtDoc::CloneStrategy::CloneStrategy(local_1078,*(Document **)(param_1 + 0x28),1);
    pCVar24 = ArtPaint::FormPaint::GetContent(local_1b48);
    pLVar36 = ArtDoc::Content::GetChildren(pCVar24);
    plVar50 = *(longlong **)pLVar36;
    while( true ) {
      if (plVar50 == (longlong *)0x0) break;
      pCVar37 = (ContentObject *)(**(code **)(*plVar50 + 8))(plVar50,local_1078);
      ArtDoc::Group::AddOnTop((Group *)this_01,pCVar37);
      plVar50 = (longlong *)plVar50[1];
    }
    if (local_6e0 == 1) {
      local_1238 = 0xbff0000000000000;
      uStack_1230 = 0;
      local_1228 = 0;
      uStack_1220 = 0xbff0000000000000;
      local_1218 = 0;
      uStack_1210 = 0;
      ArtDoc::Transformable::SetTransformation
                ((Transformable *)this_01,
                 (TransformationBase<YAGL::MilliPointCoordinateSystem> *)&local_1238,7);
    }
    FUN_18017d2b0(local_1d48,this_01,(ulonglong)local_1d18 & 0xff);
    this_02 = (Factory *)
              ArtPaint::FormPaint::Factory::Factory(local_d28,*(Document **)(param_1 + 0x28));
    ArtPaint::FormPaint::Factory::Get(this_02);
    ArtPaint::FormPaint::Factory::~Factory(local_d28);
    pCVar24 = ArtPaint::FormPaint::GetContent(local_1bf8);
    ArtDoc::Content::AddOnTop(pCVar24,this_01);
    if (lStack_1bf0 != 0) {
      LOCK();
      *(int *)(lStack_1bf0 + 8) = *(int *)(lStack_1bf0 + 8) + 1;
      UNLOCK();
    }
    local_1858 = local_1bf8;
    lStack_1850 = lStack_1bf0;
    uVar26 = FUN_1801716a0(local_1618,&local_1858);
    FUN_1800233b0(&local_1bf8,uVar26);
    FUN_180013ed0(local_1618);
    local_1d28 = (GADict *)FUN_1802d6b50(0x860);
    if (local_1d28 == (GADict *)0x0) {
      local_1c80 = (PDFPlusRepeatForGridMark *)0x0;
    }
    else {
      if (lStack_1bf0 != 0) {
        LOCK();
        *(int *)(lStack_1bf0 + 8) = *(int *)(lStack_1bf0 + 8) + 1;
        UNLOCK();
      }
      local_1848 = local_1bf8;
      lStack_1840 = lStack_1bf0;
      local_1c80 = (PDFPlusRepeatForGridMark *)
                   DocumentMarks::PDFPlusRepeatForGridMark::PDFPlusRepeatForGridMark
                             ((PDFPlusRepeatForGridMark *)local_1d28,0,&local_1848);
    }
    DocumentMarks::DynamicObject::linkMarkProperties((DynamicObject *)this_01);
    DocumentMarks::DynamicObject::setMarkDirty((DynamicObject *)this_01);
    FUN_1801853c0(local_1108,local_6e8);
    pPVar38 = ArtDoc::ContentObject::GetProperties((ContentObject *)local_1c80);
    FUN_18016e9f0(pPVar38,&PTR_s_DocumentMarks_RepeatForGridMark__1803263a8,local_1108);
    local_1398 = 0;
    if (local_638 == '\0') {
      cVar15 = (local_660 != '\0') + '\x02';
    }
    else {
      cVar15 = local_660 != '\0';
    }
    if (((cVar15 == '\0') || (cVar15 == '\x01')) || ((cVar15 != '\x02' && (cVar15 != '\x03')))) {
      local_13b8[0] = 0;
    }
    else {
      local_13b8[0] = 1;
    }
    if ((local_638 == '\0') || (local_640 != '\x01')) {
      local_1bd8 = (ulonglong)local_1bd8._4_4_ << 0x20;
LAB_1801744d0:
      uStack_1bd0 = 0;
    }
    else {
      if (local_648 == 1) {
        local_1bd8 = CONCAT44(local_1bd8._4_4_,2);
        goto LAB_1801744d0;
      }
      local_1bd8 = (longlong)local_648;
      uStack_1bd0 = 1;
    }
    uStack_13a8 = CONCAT71(uStack_1bcf,uStack_1bd0);
    local_13b0 = local_1bd8;
    local_13a0 = (uint)(local_6e0 != 0);
    pPVar38 = ArtDoc::ContentObject::GetProperties((ContentObject *)local_1c80);
    FUN_18016ebb0(pPVar38,&PTR_s_DocumentMarks_RepeatForGridMark__1803263b8,local_13b8);
    DocumentMarks::PDFPlusRepeatForGridMark::SetIsConvertedGridMark(local_1c80,true);
    pPVar12 = local_1c80;
    local_1c80 = (PDFPlusRepeatForGridMark *)0x0;
    *param_2 = (longlong)pPVar12;
    FUN_18006da40(local_10b0);
    FUN_18006da40(local_10d8);
    FUN_180022d90(local_1100);
    pPVar12 = local_1c80;
    if (local_1c80 != (PDFPlusRepeatForGridMark *)0x0) {
      DocumentMarks::PDFPlusRepeatForGridMark::~PDFPlusRepeatForGridMark(local_1c80);
      free(pPVar12);
    }
    FUN_180013ed0(&local_1bf8);
    ArtDoc::CloneStrategy::~CloneStrategy(local_1078);
    FUN_1801706d0(local_6e8);
    FUN_180013ed0(&local_1b48);
    GAStream::~GAStream((GAStream *)local_1bb0);
    if (0xf < uStack_bb8) {
      pvVar45 = local_bd0;
      if ((0xfff < uStack_bb8 + 1) &&
         (pvVar45 = *(void **)((longlong)local_bd0 + -8),
         0x1f < (ulonglong)((longlong)local_bd0 + (-8 - (longlong)pvVar45)))) goto LAB_180174612;
      free(pvVar45);
    }
    local_bc0 = (undefined *)0x0;
    uStack_bb8 = 0xf;
    local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
    if (0xf < uStack_b98) {
      FUN_1800187d0(&local_bb0,CONCAT71(uStack_baf,local_bb0));
    }
    local_ba0 = (undefined *)0x0;
    uStack_b98 = 0xf;
    local_bb0 = 0;
    GADict::~GADict((GADict *)local_1d48);
    if (local_bd8 < 0x10) {
LAB_1801746b7:
      local_be0 = 0;
      local_bd8 = 0xf;
      local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
      if (plStack_1d00 == (longlong *)0x0) {
        return param_2;
      }
      FUN_180018860();
      return param_2;
    }
    pppppppiVar31 = local_bf0;
    if ((local_bd8 + 1 < 0x1000) ||
       (pppppppiVar31 = (int *******)local_bf0[-1],
       (ulonglong)((longlong)local_bf0 + (-8 - (longlong)pppppppiVar31)) < 0x20)) {
      free(pppppppiVar31);
      goto LAB_1801746b7;
    }
    goto LAB_1801746ab;
  }
  GName::GName(local_1af0,"Source");
  GADict::GetStream((GADict *)local_1d48,local_1bb8);
  local_1d58 = CONCAT44(local_1d58._4_4_,local_1d38);
  uVar26 = FUN_1801788e0(local_1648,*(undefined8 *)(param_1 + 0x30),local_1bb8,
                         *(undefined8 *)(param_1 + 0x28));
  FUN_1801716a0(&local_1878,uVar26);
  local_1d28 = (GADict *)FUN_1802d6b50(0x698);
  if (local_1d28 == (GADict *)0x0) {
    local_1c60 = 0;
  }
  else {
    if (lStack_1870 != 0) {
      LOCK();
      *(int *)(lStack_1870 + 8) = *(int *)(lStack_1870 + 8) + 1;
      UNLOCK();
    }
    local_1888 = local_1878;
    lStack_1880 = lStack_1870;
    local_1c60 = DocumentMarks::CustomMark::CustomMark((CustomMark *)local_1d28,&local_1888,0x1cf);
  }
  if (local_1d40 == '\0') {
LAB_180172fa7:
    FUN_180180330(local_1d48,local_1c60,&local_bd0,uVar55);
  }
  else {
    GName::GName(local_1ae8,"Position");
    bVar14 = GADict::Has((GADict *)local_1d48,local_1ae8);
    if (bVar14) goto LAB_180172fa7;
    if (local_1d3f != 0) {
      DocumentMarks::MarkPosition::setReferenceObject((MarkPosition *)(local_1c60 + 0x2f0),0);
    }
  }
  FUN_18017b590(local_1d48,local_1c60,(ulonglong)local_1d18 & 0xff);
  *param_2 = local_1c60;
  local_1c60 = 0;
  FUN_180013ed0(&local_1878);
  GAStream::~GAStream((GAStream *)local_1bb8);
  if (0xf < uStack_bb8) {
    pvVar45 = local_bd0;
    if ((0xfff < uStack_bb8 + 1) &&
       (pvVar45 = *(void **)((longlong)local_bd0 + -8),
       0x1f < (ulonglong)((longlong)local_bd0 + (-8 - (longlong)pvVar45)))) {
LAB_180174612:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar45);
  }
  local_bc0 = (undefined *)0x0;
  uStack_bb8 = 0xf;
  local_bd0 = (void *)((ulonglong)local_bd0 & 0xffffffffffffff00);
  if (0xf < uStack_b98) {
    pvVar6 = (void *)CONCAT71(uStack_baf,local_bb0);
    pvVar45 = pvVar6;
    if ((0xfff < uStack_b98 + 1) &&
       (pvVar45 = *(void **)((longlong)pvVar6 + -8),
       0x1f < (ulonglong)((longlong)pvVar6 + (-8 - (longlong)pvVar45)))) {
LAB_1801730ba:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pvVar45);
  }
  local_ba0 = (undefined *)0x0;
  uStack_b98 = 0xf;
  local_bb0 = 0;
  GADict::~GADict((GADict *)local_1d48);
  if (0xf < local_bd8) {
    pppppppiVar31 = local_bf0;
    if ((0xfff < local_bd8 + 1) &&
       (pppppppiVar31 = (int *******)local_bf0[-1],
       0x1f < (ulonglong)((longlong)local_bf0 + (-8 - (longlong)pppppppiVar31)))) {
LAB_1801746ab:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    free(pppppppiVar31);
  }
  local_be0 = 0;
  local_bd8 = 0xf;
  local_bf0 = (int *******)((ulonglong)local_bf0 & 0xffffffffffffff00);
  if (plStack_1d00 == (longlong *)0x0) {
    return param_2;
  }
  FUN_180018860();
  return param_2;
}


