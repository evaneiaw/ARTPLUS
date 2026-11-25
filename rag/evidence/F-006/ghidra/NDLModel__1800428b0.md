---
modulo: NDLModel.dll
versao: 24.03.10017
funcao: 0x1800428b0
nome: ??0SaveOptions@NDLModel@@QEAA@$$QEAV01@@Z
mangled: SaveOptions
confianca: alta
xrefs: []
strings: []
---

# NDLModel 1800428b0

## Assinatura
```c
undefined SaveOptions(SaveOptions * this, SaveOptions * param_1)
```

## Pseudocódigo (decompilado)
```c

/* public: __cdecl NDLModel::SaveOptions::SaveOptions(class NDLModel::SaveOptions && __ptr64)
   __ptr64 */

SaveOptions * __thiscall NDLModel::SaveOptions::SaveOptions(SaveOptions *this,SaveOptions *param_1)

{
  undefined8 uVar1;
  
                    /* 0x428b0  283  ??0SaveOptions@NDLModel@@QEAA@$$QEAV01@@Z */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  uVar1 = *(undefined8 *)(param_1 + 8);
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = uVar1;
  uVar1 = *(undefined8 *)(param_1 + 0x18);
  *(undefined8 *)(this + 0x10) = *(undefined8 *)(param_1 + 0x10);
  *(undefined8 *)(this + 0x18) = uVar1;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0xf;
  *param_1 = (SaveOptions)0x0;
  this[0x20] = param_1[0x20];
  this[0x21] = param_1[0x21];
  this[0x22] = param_1[0x22];
  return this;
}


```

---
_Fonte: Ghidra 12.2 headless, NDLModel.dll, 0x1800428b0_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
