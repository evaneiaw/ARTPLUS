modulo: LayoutEngine.dll
versao: 24.03.10017.10017
funcao: 18002d610
nome: SetUpNest
assinatura: Nesting * SetUpNest(NestingSheetGenerator * this)
parametros: 1
retorno: Nesting *

## Callers (xrefs de entrada)
- 180071a9c -> unknown (DATA)
- 18007f7d0 -> unknown (DATA)
- Entry Point -> unknown (EXTERNAL)
- 18002754a -> ClassicMinimalLayouts @ 1800261f0 (UNCONDITIONAL_CALL)
- 180029c34 -> GenerateSheetFilling @ 1800298a0 (UNCONDITIONAL_CALL)

## Callees (xrefs de saida)
- 180040920 FUN_180040920

## Strings referenciadas
- 180063de0 : -0x8000000000000000
- 180063df0 : 0x3fe0000000000000

## Pseudocodigo (Ghidra Decompiler)
```c

/* private: class Nesting::Nesting * __ptr64 __cdecl
   LayoutEngine::NestingSheetGenerator::SetUpNest(void)const __ptr64 */

Nesting * __thiscall LayoutEngine::NestingSheetGenerator::SetUpNest(NestingSheetGenerator *this)

{
  double dVar1;
  Nesting *pNVar2;
  
                    /* 0x2d610  282
                       ?SetUpNest@NestingSheetGenerator@LayoutEngine@@AEBAPEAVNesting@3@XZ */
  dVar1 = *(double *)(this + 0x18);
  pNVar2 = (Nesting *)
           FUN_180040920(-dVar1 * 0.5,-dVar1 * 0.5,dVar1 + *(double *)(this + 0x10),
                         dVar1 + *(double *)(this + 8),0);
  return pNVar2;
}


```
