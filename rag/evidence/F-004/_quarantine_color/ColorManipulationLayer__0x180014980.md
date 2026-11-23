---
modulo: ColorManipulationLayer.dll
versao: 25.0
funcao: 0x180014980
nome: GCColorManipulation::SetLevelICCProfile (?SetLevelICCProfile@GCColorManipulation@@QEAAXW4ColorType@GCColorManipulationEnums@@AEBV?$GSharedObject@VGCICCProfile@@@@_NW4CategoryType@3@@Z)
endereco: 0x180014980
confianca: alta
xrefs: [0x180040860]
strings: []
---

# O que a função faz

**Observado (via REA/Ghidra decompiler):**
`GCColorManipulation::SetLevelICCProfile(ColorType, GSharedObject<GCICCProfile>, bool, CategoryType)` define o perfil ICC ativo por nível (stack de perfis).

Lógica resumida:
1. Se `param_4` (CategoryType) == 0, usa o ponteiro `this + 0x20`; senão usa `this + 8`. (Seleção de nível/stack de perfis.)
2. Calcula índice no array de perfis: `*(longlong *)(*(longlong *)pGVar1 + -8 + (longlong)*(int *)(pGVar1 + 0xc) * 8)` — acessa elemento do array de `GCColorLibInfo`/`GCICCProfile` pelo índice atual.
3. Chama `FUN_1800161c0(perfil_ptr, param_1, param_2, param_3)` para efetivamente definir o perfil no nível selecionado.

## Evidência

- Pseudocódigo bruto: `rag/evidence/F-004/ghidra/ColorManipulationLayer__0x180014980.json`
- Xrefs de entrada: `0x180040860` (DATA)
- Chamada de saída: `0x1800161c0` (FUN_1800161c0 — definição interna de perfil por nível)
- Strings vizinhas: nenhuma encontrada diretamente no `strings.csv` próximo ao endereço

## Inferência

> Inferência: `SetLevelICCProfile` empilha/substitui um perfil ICC em um nível específico (override vs device-link) dentro do `GCColorManipulation`. É a função de manipulação de perfil principal da camada de cor, complementar a `GetActiveICCProfile`. Fonte: pseudocódigo do decompiler Ghidra + symbols.csv.

## Confiança

`alta` — endereço confirmado em `symbols.csv`; pseudocódigo direto e coerente com o descritor de "pilha de perfis por nível" da triagem (seção 7 do TRIAGE.md).

---