# Document 18023b8e0
```yaml
modulo: Document.dll
versao: 24.03.10017.10017
funcao: 0x18023b8e0
nome: ?WriteImage@DocumentIO@@YA?AU?$pair@_NV?$optional@UMappingData@DocumentIO@@@std@@@std@@AEBVContentObject@ArtDoc@@AEBVpath@filesystem@boost@@AEBV?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@3@W4ImageFileFormats@1@AEBV?$optional@UResolution@ArtImg@@@3@@Z
mangled: WriteImage
confianca: alta
xrefs: []
strings: []
```

## Assinatura
```c
pair<bool,std::optional<DocumentIO::MappingData>_> WriteImage(ContentObject * param_1, path * param_2, vector<ArtDoc::Separation::Entry,std::allocator<ArtDoc::Separation::Entry>_> * param_3, ImageFileFormats param_4, optional<ArtImg::Resolution> * param_5)
```

## Pseudocódigo (decompilado)
```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* struct std::pair<bool,class std::optional<struct DocumentIO::MappingData> > __cdecl
   DocumentIO::WriteImage(class ArtDoc::ContentObject const & __ptr64,class boost::filesystem::path
   const & __ptr64,class std::vector<class ArtDoc::Separation::Entry,class std::allocator<class
   ArtDoc::Separation::Entry> > const & __ptr64,enum DocumentIO::ImageFileFormats,class
   std::optional<struct ArtImg::Resolution> const & __ptr64) */

ContentObject * __cdecl
DocumentIO::WriteImage
          (ContentObject *param_1,path *param_2,
          vector<ArtDoc::Separation::Entry,std::allocator<ArtDoc::Separation::Entry>_> *param_3,
          ImageFileFormats param_4,optional<ArtImg::Resolution> *param_5)

{
  int *piVar1;
  longlong *plVar2;
  longlong *plVar3;
  int iVar4;
  char cVar5;
  ImageFileFormats IVar6;
  ImageMask *this;
  shared_ptr<ArtImg::PictureData_const_> *psVar7;
  vector<std::shared_ptr<ArtSys::Core::Error>,std::allocator<std::shared_ptr<ArtSys::Core::Error>_>_>
  *pvVar8;
  longlong lVar9;
  undefined8 *puVar10;
  undefined8 uVar11;
  MappingData *pMVar12;
  undefined8 uVar13;
  undefined4 in_register_0000008c;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined8 *in_stack_00000030;
  undefined1 auStack_4d8 [32];
  uint local_4b8;
  uint local_4a8;
  undefined8 local_498;
  undefined8 uStack_490;
  longlong local_488;
  longlong *local_480;
  undefined4 local_478;
  undefined4 uStack_474;
  undefined4 uStack_470;
  undefined4 uStack_46c;
  MappingData *local_468;
  undefined1 local_460 [8];
  longlong *local_458;
  undefined1 local_450 [8];
  longlong *local_448;
  undefined8 local_440;
  undefined8 uStack_438;
  undefined8 local_430;
  undefined8 local_428;
  undefined8 uStack_420;
  undefined8 local_418;
  MappingData local_408 [288];
  char local_2e8;
  undefined1 local_2d8 [312];
  undefined1 local_1a0;
  undefined8 local_198;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  ulonglong local_50;
  
                    /* 0x23b8e0  2880
                       ?WriteImage@DocumentIO@@YA?AU?$pair@_NV?$optional@UMappingData@DocumentIO@@@std@@@std@@AEBVContentObject@ArtDoc@@AEBVpath@filesystem@boost@@AEBV?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@3@W4ImageFileFormats@1@AEBV?$optional@UResolution@ArtImg@@@3@@Z
                        */
  local_50 = DAT_1803e3780 ^ (ulonglong)auStack_4d8;
  local_4a8 = 0;
  local_468 = (MappingData *)param_1;
  local_198 = CONCAT44(in_register_0000008c,param_4);
  IVar6 = GetImageSavableFormat((ContentObject *)param_2);
  IVar6 = (ImageFileFormats)param_5 & IVar6;
  if (IVar6 == 0) {
    *param_1 = (ContentObject)0x0;
    param_1[0x128] = (ContentObject)0x0;
    return param_1;
  }
  local_498 = (longlong *)0x0;
  uStack_490 = (longlong *)0x0;
  local_2e8 = '\0';
  local_4b8 = 0;
  this = (ImageMask *)
         __RTDynamicCast(param_2,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                         &ArtDoc::ImageMask::RTTI_Type_Descriptor);
  if (this == (ImageMask *)0x0) {
    lVar9 = FUN_180239cf0(param_2);
    if (lVar9 != 0) {
      FUN_18023ac30(&local_488,lVar9);
      if (local_488 != 0) {
        FUN_180235150(&local_478,lVar9,&local_488);
        pMVar12 = (MappingData *)(CONCAT44(uStack_474,local_478) + 0xa8);
        if (*(char *)(CONCAT44(uStack_474,local_478) + 0x1c8) == '\0') {
          if (local_2e8 != '\0') {
            MappingData::~MappingData(local_408);
            local_2e8 = '\0';
          }
        }
        else if (local_2e8 == '\0') {
          MappingData::MappingData(local_408,pMVar12);
          local_2e8 = '\x01';
        }
        else {
          MappingData::operator=(local_408,pMVar12);
        }
        local_498 = (longlong *)CONCAT44(uStack_474,local_478);
        uStack_490 = (longlong *)CONCAT44(uStack_46c,uStack_470);
      }
LAB_18023bb0b:
      plVar3 = local_480;
      if (local_480 != (longlong *)0x0) {
        LOCK();
        plVar2 = local_480 + 1;
        lVar9 = *plVar2;
        *(int *)plVar2 = (int)*plVar2 + -1;
        UNLOCK();
        if ((int)lVar9 == 1) {
          (**(code **)*local_480)(local_480);
          LOCK();
          piVar1 = (int *)((longlong)plVar3 + 0xc);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 == 1) {
            (**(code **)(*local_480 + 8))();
          }
        }
      }
      uVar13 = local_198;
      goto LAB_18023bb4c;
    }
    local_4b8 = 0;
    lVar9 = __RTDynamicCast(param_2,0,&ArtDoc::ContentObject::RTTI_Type_Descriptor,
                            &ImageImpersonator::RTTI_Type_Descriptor);
    if (lVar9 != 0) {
      FUN_18023acd0(&local_488,lVar9);
      if (local_488 != 0) {
        FUN_180235270(&local_478,lVar9,&local_488);
        pMVar12 = (MappingData *)(CONCAT44(uStack_474,local_478) + 0xa8);
        if (*(char *)(CONCAT44(uStack_474,local_478) + 0x1c8) == '\0') {
          if (local_2e8 != '\0') {
            MappingData::~MappingData(local_408);
            local_2e8 = '\0';
          }
        }
        else if (local_2e8 == '\0') {
          MappingData::MappingData(local_408,pMVar12);
          local_2e8 = '\x01';
        }
        else {
          MappingData::operator=(local_408,pMVar12);
        }
        local_498 = (longlong *)CONCAT44(uStack_474,local_478);
        uStack_490 = (longlong *)CONCAT44(uStack_46c,uStack_470);
      }
      goto LAB_18023bb0b;
    }
  }
  else {
    psVar7 = ArtDoc::ImageMask::GetPictureData(this);
    pvVar8 = ArtDoc::Errors::GetAllErrors(*(Errors **)psVar7);
    if (*(longlong *)(pvVar8 + 8) != 0) {
      LOCK();
      piVar1 = (int *)(*(longlong *)(pvVar8 + 8) + 8);
      *piVar1 = *piVar1 + 1;
      UNLOCK();
    }
    local_498 = *(longlong **)pvVar8;
    uStack_490 = *(longlong **)(pvVar8 + 8);
    uVar13 = CONCAT44(in_register_0000008c,param_4);
LAB_18023bb4c:
    if (local_498 != (longlong *)0x0) {
      if (*(char *)(in_stack_00000030 + 2) == '\0') {
        puVar10 = (undefined8 *)(**(code **)(*local_498 + 0x50))(local_498,local_2d8);
      }
      else {
        local_440 = *in_stack_00000030;
        uStack_438 = in_stack_00000030[1];
        local_430 = in_stack_00000030[2];
        puVar10 = &local_440;
      }
      if (*(char *)(puVar10 + 2) == '\0') {
        uVar14 = _DAT_1802fe9a0;
        uVar15 = _UNK_1802fe9a4;
        uStack_190 = _UNK_1802fe9a8;
        uStack_18c = _UNK_1802fe9ac;
      }
      else {
        uVar14 = *(undefined4 *)puVar10;
        uVar15 = *(undefined4 *)((longlong)puVar10 + 4);
        uStack_190 = *(undefined4 *)(puVar10 + 1);
        uStack_18c = *(undefined4 *)((longlong)puVar10 + 0xc);
      }
      local_198 = CONCAT44(uVar15,uVar14);
      if ((IVar6 & 3) == 0) {
        if ((IVar6 & 4) == 0) {
          cVar5 = '\0';
        }
        else {
          uVar11 = FUN_18023b100(local_460,&local_498);
          local_4a8 = 4;
          cVar5 = FUN_18022d580(uVar11,param_3,uVar13,&local_198);
        }
      }
      else {
        uVar11 = FUN_18023b100(local_450,&local_498);
        local_4a8 = 2;
        local_4b8 = CONCAT31(local_4b8._1_3_,(char)(IVar6 >> 1)) & 0xffffff01;
        cVar5 = FUN_1802302e0(uVar11,param_3,uVar13,&local_198);
      }
      if (((local_4a8 & 4) != 0) &&
         (local_4a8 = local_4a8 & 0xfffffffb, local_458 != (longlong *)0x0)) {
        LOCK();
        plVar3 = local_458 + 1;
        lVar9 = *plVar3;
        *(int *)plVar3 = (int)*plVar3 + -1;
        UNLOCK();
        if ((int)lVar9 == 1) {
          (**(code **)*local_458)(local_458);
          LOCK();
          piVar1 = (int *)((longlong)local_458 + 0xc);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 == 1) {
            (**(code **)(*local_458 + 8))(local_458);
          }
        }
      }
      if (((local_4a8 & 2) != 0) && (local_448 != (longlong *)0x0)) {
        LOCK();
        plVar3 = local_448 + 1;
        lVar9 = *plVar3;
        *(int *)plVar3 = (int)*plVar3 + -1;
        UNLOCK();
        if ((int)lVar9 == 1) {
          (**(code **)*local_448)(local_448);
          LOCK();
          piVar1 = (int *)((longlong)local_448 + 0xc);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 == 1) {
            (**(code **)(*local_448 + 8))(local_448);
          }
        }
      }
      if (cVar5 == '\0') {
        local_428 = 0;
        uStack_420 = 0;
        local_418 = 0;
        boost::filesystem::detail::remove((path *)param_3,(error_code *)&local_428);
        *param_1 = (ContentObject)0x0;
        param_1[0x128] = (ContentObject)0x0;
        local_1a0 = 0;
        goto LAB_18023bd02;
      }
    }
  }
  *param_1 = (ContentObject)0x1;
  local_468 = (MappingData *)(param_1 + 8);
  param_1[0x128] = (ContentObject)0x0;
  if (local_2e8 != '\0') {
    MappingData::MappingData(local_468,local_408);
    param_1[0x128] = (ContentObject)0x1;
  }
LAB_18023bd02:
  if (local_2e8 != '\0') {
    MappingData::~MappingData(local_408);
  }
  plVar3 = uStack_490;
  if (uStack_490 != (longlong *)0x0) {
    LOCK();
    plVar2 = uStack_490 + 1;
    lVar9 = *plVar2;
    *(int *)plVar2 = (int)*plVar2 + -1;
    UNLOCK();
    if ((int)lVar9 == 1) {
      (**(code **)*uStack_490)(uStack_490);
      LOCK();
      piVar1 = (int *)((longlong)plVar3 + 0xc);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 == 1) {
        (**(code **)(*uStack_490 + 8))();
      }
    }
  }
  return param_1;
}


```

---
_Fonte: Ghidra 12.2 headless, Document.dll, 0x18023b8e0_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
