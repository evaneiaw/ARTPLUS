---
modulo: ColorManipulationLayer.dll
versao: 24.03.10017
funcao: 0x180014980
nome: GCColorManipulation::SetLevelICCProfile
confianca: alta
xrefs: []
strings: []
---

# O que a função faz
`GCColorManipulation::SetLevelICCProfile(...)` define o perfil ICC ativo para um nível e categoria específicos, gerenciando a pilha de perfis da camada.

## Evidência
- Lógica: Seleciona nível de perfil via `CategoryType`, acessa array de `GCColorLibInfo` e atualiza a referência.

## Confiança
`alta` — lógica de manipulação de pilha de perfis ICC confirmada por demangling e símbolos.
