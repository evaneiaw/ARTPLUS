---
modulo: LayoutEngine.dll
versao: 24.03.10017
funcao: 180013d00
nome: GenerateLayout
assinatura: vector<LayoutEngine::OutputSheet,std::allocator<LayoutEngine::OutputSheet>_> GenerateLayout(GlobalEngine * this)
parametros: 1
retorno: vector<LayoutEngine::OutputSheet,std::allocator<LayoutEngine::OutputSheet>_>
confianca: media
---

## Callers (xrefs de entrada)
- 18007182c -> unknown (DATA)
- 18007eee8 -> unknown (DATA)
- Entry Point -> unknown (EXTERNAL)

## Callees (xrefs de saida)
- 180013d20 FUN_180013d20

## Strings referenciadas
(nenhuma)

## Pseudocodigo (Ghidra Decompiler)
```c

/* public: class std::vector<class LayoutEngine::OutputSheet,class std::allocator<class
   LayoutEngine::OutputSheet> > __cdecl LayoutEngine::GlobalEngine::GenerateLayout(void)const
   __ptr64 */

void __thiscall LayoutEngine::GlobalEngine::GenerateLayout(GlobalEngine *this)

{
  longlong *in_RDX;
  undefined8 in_R8;
  undefined8 in_R9;
  
                    /* 0x13d00  126
                       ?GenerateLayout@GlobalEngine@LayoutEngine@@QEBA?AV?$vector@VOutputSheet@LayoutEngine@@V?$allocator@VOutputSheet@LayoutEngine@@@std@@@std@@XZ
                        */
  FUN_180013d20(*(undefined8 **)this,in_RDX,in_R8,in_R9);
  return;
}


```