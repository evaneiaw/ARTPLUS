---
modulo: ColorManipulationLayer.dll
versao: 25.0
funcao: 0x180012bf0
nome: GCColorManipulation::GetActiveICCProfile (?GetActiveICCProfile@GCColorManipulation@@QEBA?BV?$GSharedObject@VGCICCProfile@@@@W4ColorType@GCColorManipulationEnums@@_NW4CategoryType@4@@Z)
endereco: 0x180012bf0
confianca: alta
xrefs: [0x180040490, 0x18005132c]
strings: ["Enfocus XYZ Profile.icc", "AdobeRGB1998.icc", "WAN-IFRA/ISOcoated_v2_eci.icc", "No XYZ ICC profile has been defined", "An ICC profile could not be read", "Invalid ICC profile"]
---

# O que a função faz

**Observado (via REA/Ghidra decompiler):**
`GCColorManipulation::GetActiveICCProfile(ColorType, bool, CategoryType)` retorna um `GSharedObject<GCICCProfile>` (perfil ICC ativo) para um tipo de cor e categoria dados.

Lógica resumida:
1. Se `param_2` (bool) for um valor 0–1 ou 2–3 (`iVar1 - 6U < 2`), pega `*(GRefCount **)(this + 0x38)` — se for NULL, lança `GCSimpleException` com código `0x124f85` (erro interno); caso contrário, adquire referência e retorna.
2. Senão, itera sobre um array de `GCColorLibInfo` (`this + 8` ou `this + 0x20` dependendo de `in_stack_00000028`), chamando `GCColorLibInfo::GetGreen255` e `FUN_180015cc0` para encontrar um perfil que corresponda ao tipo/categoria; quando encontrado, chama `FUN_180015c00` para obter o `GSharedObject<GCICCProfile>` e adquire referência.

## Evidência

- Pseudocódigo bruto: `rag/evidence/F-004/ghidra/ColorManipulationLayer__0x180012bf0.json`
- Xrefs de entrada: `0x180040490` (DATA), `0x18005132c` (DATA)
- Chamadas de saída (call graph): `0x180024f30` (GCSomething), `0x18000b8e0` (GetSomething)
- Chamada de outra sobrecarga: `0x180012d20` (GetActiveICCProfile wrapper) chama esta função
- Strings vizinhas (do .rdata): `Enfocus XYZ Profile.icc` (0x180032258), `AdobeRGB1998.icc` (0x180036be8), `WAN-IFRA/ISOcoated_v2_eci.icc` (0x180036c00), `No XYZ ICC profile has been defined` (0x180036d98), `An ICC profile could not be read` (0x180036e30), `Invalid ICC profile` (0x180036e58)

## Inferência

> Inferência: Esta função resolve o perfil ICC ativo consultando um cache de perfis (`GCColorLibInfo`) por tipo de cor e categoria; se não houver match, lança exceção interna. Usada como ponto central para obtenção do perfil ativo em conversões. Fonte: pseudocódigo do decompiler Ghidra + strings.csv.

## Confiança

`alta` — endereço confirmado em `symbols.csv`; pseudocódigo completo e coerente com strings de perfil ICC encontradas no binário.

---