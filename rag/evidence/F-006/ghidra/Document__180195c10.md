# Document 180195c10
```yaml
modulo: Document.dll
versao: 24.03.10017.10017
funcao: 0x180195c10
nome: ?RegisterPieceInfoWriter@ArtDoc@@YA_KV?$function@$$A6A_NAEBVContentObject@ArtDoc@@@Z@std@@V?$function@$$A6A?AV?$unique_ptr@$$CBVPieceInfoWriter@ArtDoc@@U?$default_delete@$$CBVPieceInfoWriter@ArtDoc@@@std@@@std@@AEBVContentObject@ArtDoc@@AEAVWriteContext@4@@Z@3@@Z
mangled: RegisterPieceInfoWriter
confianca: alta
xrefs: []
strings: []
```

## Assinatura
```c
__uint64 RegisterPieceInfoWriter(function<bool___cdecl(ArtDoc::ContentObject_const&___ptr64)> param_1, function<class_std::unique_ptr<ArtDoc::PieceInfoWriter_const_,std::default_delete<ArtDoc::PieceInfoWriter_const_>_>___cdecl(ArtDoc::ContentObject_const&___ptr64,ArtDoc::WriteContext&___ptr64)> param_2)
```

## Pseudocódigo (decompilado)
```c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* unsigned __int64 __cdecl ArtDoc::RegisterPieceInfoWriter(class std::function<bool __cdecl(class
   ArtDoc::ContentObject const & __ptr64)>,class std::function<class std::unique_ptr<class
   ArtDoc::PieceInfoWriter const ,struct std::default_delete<class ArtDoc::PieceInfoWriter const > >
   __cdecl(class ArtDoc::ContentObject const & __ptr64,class ArtDoc::WriteContext & __ptr64)>) */

__uint64 __cdecl ArtDoc::RegisterPieceInfoWriter(longlong *param_1,longlong *param_2)

{
  __uint64 _Var1;
  longlong *plVar2;
  longlong *plVar3;
  undefined1 auStack_d8 [32];
  longlong *local_b8;
  longlong *local_b0;
  longlong local_a8 [7];
  longlong *local_70;
  longlong local_68 [7];
  longlong *local_30;
  ulonglong local_28;
  
                    /* 0x195c10  2455
                       ?RegisterPieceInfoWriter@ArtDoc@@YA_KV?$function@$$A6A_NAEBVContentObject@ArtDoc@@@Z@std@@V?$function@$$A6A?AV?$unique_ptr@$$CBVPieceInfoWriter@ArtDoc@@U?$default_delete@$$CBVPieceInfoWriter@ArtDoc@@@std@@@std@@AEBVContentObject@ArtDoc@@AEAVWriteContext@4@@Z@3@@Z
                        */
  local_28 = DAT_1803e3780 ^ (ulonglong)auStack_d8;
  local_70 = (longlong *)0x0;
  local_b8 = param_1;
  local_b0 = param_2;
  FUN_18006f450(local_a8,param_1);
  local_30 = (longlong *)0x0;
  FUN_18006f450(local_68,param_2);
  plVar2 = DAT_1804110b8;
  DAT_180411060 = DAT_180411060 + 1;
  if (DAT_1804110b8 == DAT_1804110c0) {
    plVar3 = DAT_1804110b8;
    FUN_18018fff0(&DAT_1804110b0,DAT_1804110b8,&DAT_180411060,local_a8);
  }
  else {
    DAT_1804110b8[7] = 0;
    FUN_18006f450(plVar2,local_a8);
    plVar2[0xf] = 0;
    plVar3 = local_68;
    FUN_18006f450(plVar2 + 8,plVar3);
    plVar2[0x10] = DAT_180411060;
    DAT_1804110b8 = DAT_1804110b8 + 0x11;
  }
  if (local_30 != (longlong *)0x0) {
    plVar3 = (longlong *)CONCAT71((int7)((ulonglong)local_68 >> 8),local_30 != local_68);
    (**(code **)(*local_30 + 0x20))(local_30,plVar3);
    local_30 = (longlong *)0x0;
  }
  if (local_70 != (longlong *)0x0) {
    plVar3 = (longlong *)CONCAT71((int7)((ulonglong)local_a8 >> 8),local_70 != local_a8);
    (**(code **)(*local_70 + 0x20))(local_70,plVar3);
  }
  _Var1 = DAT_1804110b8[-1];
  plVar2 = (longlong *)param_1[7];
  if (plVar2 != (longlong *)0x0) {
    (**(code **)(*plVar2 + 0x20))
              (plVar2,CONCAT71((int7)((ulonglong)plVar3 >> 8),plVar2 == param_1) ^ 1);
    param_1[7] = 0;
  }
  plVar2 = (longlong *)param_2[7];
  if (plVar2 != (longlong *)0x0) {
    (**(code **)(*plVar2 + 0x20))(plVar2,plVar2 != param_2);
    param_2[7] = 0;
  }
  return _Var1;
}


```

---
_Fonte: Ghidra 12.2 headless, Document.dll, 0x180195c10_


## Xrefs de entrada (callers)

- caller 1800a1230 (FUN_1800a1230)

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
