---
modulo: NDLModel.dll
versao: 24.03.10017
funcao: 0x180042b80
nome: ?IsIncrementalSave@SaveOptions@NDLModel@@QEBA_NXZ
mangled: IsIncrementalSave
confianca: alta
xrefs: []
strings: []
---

# NDLModel 180042b80

## Assinatura
```c
bool IsIncrementalSave(SaveOptions * this)
```

## Pseudocódigo (decompilado)
```c

/* public: bool __cdecl NDLModel::SaveOptions::IsIncrementalSave(void)const __ptr64 */

bool __thiscall NDLModel::SaveOptions::IsIncrementalSave(SaveOptions *this)

{
                    /* 0x42b80  1298  ?IsIncrementalSave@SaveOptions@NDLModel@@QEBA_NXZ */
  return (bool)this[0x20];
}


```

---
_Fonte: Ghidra 12.2 headless, NDLModel.dll, 0x180042b80_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
