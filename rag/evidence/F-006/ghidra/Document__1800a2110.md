---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x1800a2110
nome: ??0PieceInfoWriter@ArtDoc@@QEAA@AEBV01@@Z
mangled: PieceInfoWriter
confianca: alta
xrefs: []
strings: []
---

# Document 1800a2110

## Assinatura
```c
undefined PieceInfoWriter(PieceInfoWriter * this, PieceInfoWriter * param_1)
```

## Pseudocódigo (decompilado)
```c

/* public: __cdecl ArtDoc::PieceInfoWriter::PieceInfoWriter(class ArtDoc::PieceInfoWriter const &
   __ptr64) __ptr64 */

PieceInfoWriter * __thiscall
ArtDoc::PieceInfoWriter::PieceInfoWriter(PieceInfoWriter *this,PieceInfoWriter *param_1)

{
                    /* 0xa2110  329  ??0PieceInfoWriter@ArtDoc@@QEAA@AEBV01@@Z
                       0xa2110  330  ??0PieceInfoWriter@ArtDoc@@QEAA@XZ */
  *(undefined ***)this = _vftable_;
  return this;
}


```

---
_Fonte: Ghidra 12.2 headless, Document.dll, 0x1800a2110_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
