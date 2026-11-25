---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x1801954e0
nome: ?RegisterDocumentPieceInfoWriter@ArtDoc@@YA_KV?$function@$$A6A_NAEBVDocument@ArtDoc@@@Z@std@@AEBV?$basic_string_view@DU?$char_traits@D@std@@@3@V?$function@$$A6AXAEAVGADict@@AEBVDocument@ArtDoc@@@Z@3@@Z
mangled: RegisterDocumentPieceInfoWriter
confianca: alta
xrefs: []
strings: []
---

# Document 1801954e0

## Assinatura
```c
__uint64 RegisterDocumentPieceInfoWriter(function<bool___cdecl(ArtDoc::Document_const&___ptr64)> param_1, basic_string_view<char,std::char_traits<char>_> * param_2, function<void___cdecl(GADict&___ptr64,ArtDoc::Document_const&___ptr64)> param_3)
```

## Pseudocódigo (decompilado)
```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* unsigned __int64 __cdecl ArtDoc::RegisterDocumentPieceInfoWriter(class std::function<bool
   __cdecl(class ArtDoc::Document const & __ptr64)>,class std::basic_string_view<char,struct
   std::char_traits<char> > const & __ptr64,class std::function<void __cdecl(class GADict &
   __ptr64,class ArtDoc::Document const & __ptr64)>) */

__uint64 __cdecl
ArtDoc::RegisterDocumentPieceInfoWriter(longlong *param_1,undefined4 *param_2,longlong *param_3)

{
  __uint64 _Var1;
  longlong *plVar2;
  longlong *plVar3;
  undefined1 auStack_e8 [32];
  longlong *local_c8;
  longlong *local_c0;
  longlong local_b8 [7];
  longlong *local_80;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  longlong local_68 [7];
  longlong *local_30;
  ulonglong local_28;
  
                    /* 0x1954e0  2431
                       ?RegisterDocumentPieceInfoWriter@ArtDoc@@YA_KV?$function@$$A6A_NAEBVDocument@ArtDoc@@@Z@std@@AEBV?$basic_string_view@DU?$char_traits@D@std@@@3@V?$function@$$A6AXAEAVGADict@@AEBVDocument@ArtDoc@@@Z@3@@Z
                        */
  local_28 = DAT_1803e3780 ^ (ulonglong)auStack_e8;
  local_80 = (longlong *)0x0;
  local_c8 = param_1;
  local_c0 = param_3;
  FUN_18006f450(local_b8,param_3);
  local_78 = *param_2;
  uStack_74 = param_2[1];
  uStack_70 = param_2[2];
  uStack_6c = param_2[3];
  local_30 = (longlong *)0x0;
  FUN_18006f450(local_68,param_1);
  plVar2 = DAT_180411118;
  DAT_180411060 = DAT_180411060 + 1;
  if (DAT_180411118 == DAT_180411120) {
    plVar3 = DAT_180411118;
    FUN_180190510(&DAT_180411110,DAT_180411118,&DAT_180411060,local_b8);
  }
  else {
    DAT_180411118[7] = 0;
    FUN_18006f450(plVar2,local_b8);
    *(undefined4 *)(plVar2 + 8) = local_78;
    *(undefined4 *)((longlong)plVar2 + 0x44) = uStack_74;
    *(undefined4 *)(plVar2 + 9) = uStack_70;
    *(undefined4 *)((longlong)plVar2 + 0x4c) = uStack_6c;
    plVar2[0x11] = 0;
    plVar3 = local_68;
    FUN_18006f450(plVar2 + 10,plVar3);
    plVar2[0x12] = DAT_180411060;
    DAT_180411118 = DAT_180411118 + 0x13;
  }
  if (local_30 != (longlong *)0x0) {
    plVar3 = (longlong *)CONCAT71((int7)((ulonglong)local_68 >> 8),local_30 != local_68);
    (**(code **)(*local_30 + 0x20))(local_30,plVar3);
    local_30 = (longlong *)0x0;
  }
  if (local_80 != (longlong *)0x0) {
    plVar3 = (longlong *)CONCAT71((int7)((ulonglong)local_b8 >> 8),local_80 != local_b8);
    (**(code **)(*local_80 + 0x20))(local_80,plVar3);
  }
  _Var1 = DAT_180411118[-1];
  plVar2 = (longlong *)param_1[7];
  if (plVar2 != (longlong *)0x0) {
    (**(code **)(*plVar2 + 0x20))
              (plVar2,CONCAT71((int7)((ulonglong)plVar3 >> 8),plVar2 == param_1) ^ 1);
    param_1[7] = 0;
  }
  plVar2 = (longlong *)param_3[7];
  if (plVar2 != (longlong *)0x0) {
    (**(code **)(*plVar2 + 0x20))(plVar2,plVar2 != param_3);
    param_3[7] = 0;
  }
  return _Var1;
}


```

---
_Fonte: Ghidra 12.2 headless, Document.dll, 0x1801954e0_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
