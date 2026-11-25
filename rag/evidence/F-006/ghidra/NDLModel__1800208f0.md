---
modulo: NDLModel.dll
versao: 24.03.10017
funcao: 0x1800208f0
nome: ??0SaveDocumentException@NDLModel@@QEAA@AEBV01@@Z
mangled: SaveDocumentException
confianca: alta
xrefs: []
strings: []
---

# NDLModel 1800208f0

## Assinatura
```c
undefined SaveDocumentException(SaveDocumentException * this, SaveDocumentException * param_1)
```

## Pseudocódigo (decompilado)
```c

/* public: __cdecl NDLModel::SaveDocumentException::SaveDocumentException(class
   NDLModel::SaveDocumentException const & __ptr64) __ptr64 */

SaveDocumentException * __thiscall
NDLModel::SaveDocumentException::SaveDocumentException
          (SaveDocumentException *this,SaveDocumentException *param_1)

{
                    /* 0x208f0  281  ??0SaveDocumentException@NDLModel@@QEAA@AEBV01@@Z */
  *(undefined ***)this = _vftable_;
  FUN_18001ff90((undefined8 *)(this + 8),(undefined8 *)(param_1 + 8));
  return this;
}


```

---
_Fonte: Ghidra 12.2 headless, NDLModel.dll, 0x1800208f0_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
