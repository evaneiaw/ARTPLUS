modulo: LayoutEngine.dll
versao: 24.03.10017.10017
funcao: 18002d570
nome: Nest
assinatura: nesterror_type Nest(NestingSheetGenerator * this, Nesting * param_1, long param_2)
parametros: 3
retorno: nesterror_type

## Callers (xrefs de entrada)
- 1800719e8 -> unknown (DATA)
- 18007f7b8 -> unknown (DATA)
- Entry Point -> unknown (EXTERNAL)
- 180025e84 -> ClassicFillSheet @ 180025820 (UNCONDITIONAL_CALL)
- 1800265ea -> ClassicMinimalLayouts @ 1800261f0 (UNCONDITIONAL_CALL)
- 18002766f -> ClassicMinimalLayouts @ 1800261f0 (UNCONDITIONAL_CALL)
- 180029e65 -> GenerateSheetFilling @ 1800298a0 (UNCONDITIONAL_CALL)
- 18002ab34 -> GenerateSheetLeftovers @ 18002a5d0 (UNCONDITIONAL_CALL)
- 18002b255 -> GenerateSheetWeighed @ 18002af10 (UNCONDITIONAL_CALL)

## Callees (xrefs de saida)
- 180040240 FUN_180040240

## Strings referenciadas
(nenhuma)

## Pseudocodigo (Ghidra Decompiler)
```c

/* private: enum Nesting::nesterror_type __cdecl LayoutEngine::NestingSheetGenerator::Nest(class
   Nesting::Nesting * __ptr64,long)const __ptr64 */

nesterror_type __thiscall
LayoutEngine::NestingSheetGenerator::Nest(NestingSheetGenerator *this,Nesting *param_1,long param_2)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
                    /* 0x2d570  237
                       ?Nest@NestingSheetGenerator@LayoutEngine@@AEBA?AW4nesterror_type@Nesting@@PEAV44@J@Z
                        */
  if ((*(int *)(this + 0x24) == 0) || (uVar3 = 2, *(int *)(this + 0x24) != 1)) {
    uVar3 = 0;
  }
  if (*(int *)(this + 0x20) == 0) {
    uVar2 = 0;
  }
  else if (*(int *)(this + 0x20) == 1) {
    uVar2 = 1;
  }
  else {
    uVar2 = 4;
  }
  uVar1 = FUN_180040240((ulonglong *****)param_1,1,uVar2,0,0,0,uVar3,param_2);
  return (nesterror_type)uVar1;
}


```
