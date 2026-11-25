---
modulo: NDLModel.dll
versao: 24.03.10017
funcao: 0x1800508d0
nome: ?SavePreflightReport@NDLModel@@YA?AV?$Future@X@Parallel@@USelection@1@UAction@1@AEBVpath@filesystem@boost@@W4PreflightReportType@1@AEBULocale@1@AEBUApplicationInfo@1@2@Z
mangled: SavePreflightReport
confianca: alta
xrefs: []
strings: []
---

# NDLModel 1800508d0

## Assinatura
```c
Future<void> SavePreflightReport(Selection param_1, Action param_2, path * param_3, PreflightReportType param_4, Locale * param_5, ApplicationInfo * param_6, path * param_7)
```

## Pseudocódigo (decompilado)
```c

/* class Parallel::Future<void> __cdecl NDLModel::SavePreflightReport(struct
   NDLModel::Selection,struct NDLModel::Action,class boost::filesystem::path const & __ptr64,enum
   NDLModel::PreflightReportType,struct NDLModel::Locale const & __ptr64,struct
   NDLModel::ApplicationInfo const & __ptr64,class boost::filesystem::path const & __ptr64) */

undefined8 __cdecl
NDLModel::SavePreflightReport
          (undefined8 param_1,undefined8 *param_2,undefined8 *param_3,undefined8 param_4,
          undefined4 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined8 local_res8;
  undefined8 local_res10 [3];
  
                    /* 0x508d0  1435
                       ?SavePreflightReport@NDLModel@@YA?AV?$Future@X@Parallel@@USelection@1@UAction@1@AEBVpath@filesystem@boost@@W4PreflightReportType@1@AEBULocale@1@AEBUApplicationInfo@1@2@Z
                        */
  local_res8 = *param_3;
  local_res10[0] = *param_2;
  (**(code **)(*DAT_1800c3228 + 0x70))
            (DAT_1800c3228,param_1,local_res10,&local_res8,param_4,param_5,param_6,param_7,param_8);
  return param_1;
}


```

---
_Fonte: Ghidra 12.2 headless, NDLModel.dll, 0x1800508d0_


## Xrefs de entrada (callers)

_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._

## Xrefs de saida (callees)

_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._
