---
modulo: LayoutEngine.dll
versao: 24.03.10017
funcao: 18001d5a0
nome: GenerateClassicSolution
assinatura: vector<LayoutEngine::IntermediateSheet,std::allocator<LayoutEngine::IntermediateSheet>_> GenerateClassicSolution(GuillotineSheetGenerator * this, vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> * param_1, bool param_2)
parametros: 3
retorno: vector<LayoutEngine::IntermediateSheet,std::allocator<LayoutEngine::IntermediateSheet>_>
confianca: alta
---

## Callers (xrefs de entrada)
- 180071824 -> unknown (DATA)
- 18007f2d8 -> unknown (DATA)
- Entry Point -> unknown (EXTERNAL)
- 180064648 -> unknown (DATA)

## Callees (xrefs de saida)
(nenhum)

## Strings referenciadas
(nenhuma)

## Pseudocodigo (Ghidra Decompiler)
```c

/* public: virtual class std::vector<class LayoutEngine::IntermediateSheet,class
   std::allocator<class LayoutEngine::IntermediateSheet> > __cdecl
   LayoutEngine::GuillotineSheetGenerator::GenerateClassicSolution(class std::vector<class
   LayoutEngine::OrderedStation,class std::allocator<class LayoutEngine::OrderedStation> > const &
   __ptr64,bool) __ptr64 */

vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_> * __thiscall
LayoutEngine::GuillotineSheetGenerator::GenerateClassicSolution
          (GuillotineSheetGenerator *this,
          vector<LayoutEngine::OrderedStation,std::allocator<LayoutEngine::OrderedStation>_>
          *param_1,bool param_2)

{
                    /* 0x1d5a0  124
                       ?GenerateClassicSolution@GuillotineSheetGenerator@LayoutEngine@@UEAA?AV?$vector@VIntermediateSheet@LayoutEngine@@V?$allocator@VIntermediateSheet@LayoutEngine@@@std@@@std@@AEBV?$vector@VOrderedStation@LayoutEngine@@V?$allocator@VOrderedStation@LayoutEngine@@@std@@@4@_N@Z
                        */
  *(undefined8 *)param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  return param_1;
}


```