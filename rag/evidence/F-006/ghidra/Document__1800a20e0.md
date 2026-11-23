# Document 1800a20e0
```yaml
modulo: Document.dll
versao: 24.03.10017.10017
funcao: 0x1800a20e0
nome: ??0EskoPieceInfoWriter@ArtDoc@@QEAA@$$QEAV01@@Z
mangled: EskoPieceInfoWriter
confianca: alta
xrefs: []
strings: []
```

## Assinatura
```c
undefined EskoPieceInfoWriter(EskoPieceInfoWriter * this, EskoPieceInfoWriter * param_1)
```

## Pseudocódigo (decompilado)
```c

/* public: __cdecl ArtDoc::EskoPieceInfoWriter::EskoPieceInfoWriter(class
   ArtDoc::EskoPieceInfoWriter && __ptr64) __ptr64 */

EskoPieceInfoWriter * __thiscall
ArtDoc::EskoPieceInfoWriter::EskoPieceInfoWriter
          (EskoPieceInfoWriter *this,EskoPieceInfoWriter *param_1)

{
                    /* 0xa20e0  156  ??0EskoPieceInfoWriter@ArtDoc@@QEAA@$$QEAV01@@Z
                       0xa20e0  157  ??0EskoPieceInfoWriter@ArtDoc@@QEAA@AEBV01@@Z
                       0xa20e0  158  ??0EskoPieceInfoWriter@ArtDoc@@QEAA@XZ */
  *(undefined ***)this = _vftable_;
  return this;
}


```

---
_Fonte: Ghidra 12.2 headless, Document.dll, 0x1800a20e0_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
