---
modulo: ColorManipulationLayer.dll
versao: 24.03.10017
funcao: 0x180014b80
nome: GCColorManipulationLayer::Initialize
confianca: alta
xrefs: [0x1800119c0, 0x180011aa0]
strings: []
---

# O que a função faz
`GCColorManipulationLayer::Initialize()` é o ponto de entrada de inicialização da camada de manipulação de cores. Implementa padrão singleton, verifica estado de inicialização e invoca subsistemas de cache de perfis e strings.

## Evidência
- Pseudocódigo (Ghidra 12.2): `GCColorManipulationLayer::Initialize()` inicializa cache de perfis se `sInitialized == 0`.
- Xrefs de entrada: `0x1800119c0`, `0x180011aa0`
- Chamadas (saída): `0x180014ab0`, `0x180014a10`, `Release` (externa)

## Confiança
`alta` — endereço confirmado e coerente com a estrutura singleton de inicialização da camada.
