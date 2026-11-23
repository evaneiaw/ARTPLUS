# NDLModel 180042bb0
```yaml
modulo: NDLModel.dll
versao: 24.03.10017.10017
funcao: 0x180042bb0
nome: ?SetIncrementalSave@SaveOptions@NDLModel@@QEAAX_N@Z
mangled: SetIncrementalSave
confianca: alta
xrefs: []
strings: []
```

## Assinatura
```c
void SetIncrementalSave(SaveOptions * this, bool param_1)
```

## Pseudocódigo (decompilado)
```c

/* public: void __cdecl NDLModel::SaveOptions::SetIncrementalSave(bool) __ptr64 */

void __thiscall NDLModel::SaveOptions::SetIncrementalSave(SaveOptions *this,bool param_1)

{
                    /* 0x42bb0  1682  ?SetIncrementalSave@SaveOptions@NDLModel@@QEAAX_N@Z */
  this[0x20] = (SaveOptions)param_1;
  return;
}


```

---
_Fonte: Ghidra 12.2 headless, NDLModel.dll, 0x180042bb0_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
