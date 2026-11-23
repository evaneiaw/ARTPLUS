# NDLModel 180042a40
```yaml
modulo: NDLModel.dll
versao: 24.03.10017.10017
funcao: 0x180042a40
nome: ??0SaveOptions@NDLModel@@QEAA@AEBV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z
mangled: SaveOptions
confianca: alta
xrefs: []
strings: []
```

## Assinatura
```c
undefined SaveOptions(SaveOptions * this, basic_string_view<char,std::char_traits<char>_> * param_1)
```

## Pseudocódigo (decompilado)
```c

/* public: __cdecl NDLModel::SaveOptions::SaveOptions(class std::basic_string_view<char,struct
   std::char_traits<char> > const & __ptr64) __ptr64 */

SaveOptions * __thiscall
NDLModel::SaveOptions::SaveOptions
          (SaveOptions *this,basic_string_view<char,std::char_traits<char>_> *param_1)

{
                    /* 0x42a40  285
                       ??0SaveOptions@NDLModel@@QEAA@AEBV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  FUN_180016ab0((undefined8 *)this,*(void **)param_1,*(size_t *)(param_1 + 8));
  *(undefined2 *)(this + 0x20) = 0;
  this[0x22] = (SaveOptions)0x0;
  return this;
}


```

---
_Fonte: Ghidra 12.2 headless, NDLModel.dll, 0x180042a40_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
