---
modulo: ColorManipulationLayer.dll
versao: 24.03.10017
funcao: 0x1800132f0
nome: GCColorManipulation::GetInstance
confianca: alta
xrefs: []
strings: []
---

# O que a função faz
`GCColorManipulation::GetInstance()` retorna o ponteiro estático `sInstance`, servindo como ponto de acesso global ao singleton da classe `GCColorManipulation`.

## Evidência
- Pseudocódigo: Implementação padrão de singleton (retorno de ponteiro estático).
- Xrefs: Acesso global à API de cor.

## Confiança
`alta` — padrão de projeto singleton inequívoco.
