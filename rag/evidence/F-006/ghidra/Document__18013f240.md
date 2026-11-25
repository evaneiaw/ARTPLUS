---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x18013f240
nome: ??0WriteContext@ArtDoc@@QEAA@AEBV01@@Z
mangled: WriteContext
confianca: alta
xrefs: []
strings: []
---

# Document 18013f240

## Assinatura
```c
undefined WriteContext(WriteContext * this, WriteContext * param_1)
```

## Pseudocódigo (decompilado)
```c

/* public: __cdecl ArtDoc::WriteContext::WriteContext(class ArtDoc::WriteContext const & __ptr64)
   __ptr64 */

WriteContext * __thiscall
ArtDoc::WriteContext::WriteContext(WriteContext *this,WriteContext *param_1)

{
                    /* 0x13f240  392  ??0WriteContext@ArtDoc@@QEAA@AEBV01@@Z
                       0x13f240  393  ??0WriteContext@ArtDoc@@QEAA@XZ */
  *(undefined ***)this = _vftable_;
  return this;
}


```

---
_Fonte: Ghidra 12.2 headless, Document.dll, 0x18013f240_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
