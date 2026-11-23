# NDLModel 18004b420
```yaml
modulo: NDLModel.dll
versao: 24.03.10017.10017
funcao: 0x18004b420
nome: ?SaveMarkSet@NDLModel@@YA?AV?$Future@X@Parallel@@USelection@1@AEBVpath@filesystem@boost@@@Z
mangled: SaveMarkSet
confianca: alta
xrefs: []
strings: []
```

## Assinatura
```c
Future<void> SaveMarkSet(Selection param_1, path * param_2)
```

## Pseudocódigo (decompilado)
```c

/* class Parallel::Future<void> __cdecl NDLModel::SaveMarkSet(struct NDLModel::Selection,class
   boost::filesystem::path const & __ptr64) */

undefined8 __cdecl NDLModel::SaveMarkSet(undefined8 param_1,undefined8 *param_2,undefined8 param_3)

{
  undefined8 local_res8 [4];
  
                    /* 0x4b420  1434
                       ?SaveMarkSet@NDLModel@@YA?AV?$Future@X@Parallel@@USelection@1@AEBVpath@filesystem@boost@@@Z
                        */
  local_res8[0] = *param_2;
  (**(code **)(*DAT_1800c3018 + 0x188))(DAT_1800c3018,param_1,local_res8,param_3);
  return param_1;
}


```

---
_Fonte: Ghidra 12.2 headless, NDLModel.dll, 0x18004b420_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
