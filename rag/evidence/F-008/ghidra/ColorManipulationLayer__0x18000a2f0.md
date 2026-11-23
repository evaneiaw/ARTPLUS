---
modulo: ColorManipulationLayer.dll
versao: 24.03.10017
funcao: 0x18000a2f0
nome: GCCallbackConverter::ConvertColor
confianca: media
xrefs: []
strings: []
---

# O que a função faz
`GCCallbackConverter::ConvertColor(...)` é o ponto de conversão via callback da classe `GCCallbackConverter`, usada para transformações de espaço de cor customizadas.

## Evidência
- Assinatura: `GCCallbackConverter::ConvertColor(GTable<N> const&, GTable<GFunction*> const&, ...)`

## Confiança
`media` — assinatura confirmada por demangling, mas lógica de callback complexa e não totalmente descompilada.
