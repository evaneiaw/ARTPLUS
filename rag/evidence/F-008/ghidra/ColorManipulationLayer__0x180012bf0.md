---
modulo: ColorManipulationLayer.dll
versao: 24.03.10017
funcao: 0x180012bf0
nome: GCColorManipulation::GetActiveICCProfile
confianca: alta
xrefs: []
strings: ["Enfocus XYZ Profile.icc", "AdobeRGB1998.icc", "WAN-IFRA/ISOcoated_v2_eci.icc", "No XYZ ICC profile has been defined"]
---

# O que a função faz
`GCColorManipulation::GetActiveICCProfile(...)` resolve o perfil ICC ativo consultando o cache interno por tipo de cor e categoria.

## Evidência
- Pseudocódigo: Consulta `GCColorLibInfo` e retorna `GSharedObject<GCICCProfile>`.
- Strings vizinhas: Perfis ICC comuns referenciados no `.rdata`.

## Confiança
`alta` — coerente com strings de perfil ICC e cache interno da DLL.
