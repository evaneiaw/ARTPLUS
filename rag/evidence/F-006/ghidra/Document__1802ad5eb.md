---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x1802ad5eb
nome: SignOnSave
mangled: SignOnSave
confianca: alta
xrefs: []
strings: []
---

# Document 1802ad5eb

## Assinatura
```c
void SignOnSave(GODocument * this, GODocSignParams * param_1)
```

## Pseudocódigo (decompilado)
```c

void __thiscall GODocument::SignOnSave(GODocument *this,GODocSignParams *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0001802ad5eb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SignOnSave(this,param_1);
  return;
}


```

---
_Fonte: Ghidra 12.2 headless, Document.dll, 0x1802ad5eb_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
