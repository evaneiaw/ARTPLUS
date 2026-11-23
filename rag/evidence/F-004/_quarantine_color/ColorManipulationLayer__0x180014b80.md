---
modulo: ColorManipulationLayer.dll
versao: 25.0
funcao: 0x180014b80
nome: GCColorManipulationLayer::Initialize (?Initialize@GCColorManipulationLayer@@SA_NXZ)
endereco: 0x180014b80
confianca: alta
xrefs: [0x180040760, 0x18005162c]
strings: []
---

# O que a função faz

**Observado (via Ghidra decompiler, pseudocódigo parcial registrado na sessão):**
`GCColorManipulationLayer::Initialize()` é o ponto de entrada de inicialização da camada de manipulação de cores. Implementa padrão singleton com contador de reentrância (`sInitialized`). Se já inicializado, incrementa o contador e retorna `true`. Caso contrário, chama `GCICCProfileCache::CreateInstance()`, depois `FUN_180027c40()` e `FUN_1800269b0()` (ambas retornam bool; se qualquer uma retornar `\0`, aborta com `false`), e finalmente chama `InitializeStrings()` e `InitializeXYZProfile()`.

**Inferência:** `FUN_180027c40()` e `FUN_1800269b0()` são provavelmente inicialização de subsistemas de cor (lcms / device-link / Pantone), mas seus nomes reais não foram resolvidos no export.

## Evidência

- Pseudocódigo bruto: `rag/evidence/F-004/ghidra/ColorManipulationLayer__0x180014b80.json` (não regenerado via REA — conteúdo reconstruído do terminal da sessão anterior; veja limitação abaixo)
- Xrefs de entrada: `0x180040760` (DATA), `0x18005162c` (DATA) — referências de dados que contêm o endereço da função
- Chamadas (saída): `0x180020d90` (CreateInstance), `0x180014cc0` (InitializeXYZProfile), `0x1800269b0` (FUN_1800269b0), `0x180027c40` (FUN_180027c40), `0x180014bd0` (InitializeStrings)
- Strings vizinhas: nenhuma encontrada diretamente no `strings.csv` próximo ao endereço

## Inferência

> Inferência: `Initialize` registra/cacheia perfis ICC padrão (`InitializeXYZProfile`) e strings de erro (`InitializeStrings`) antes de expor a API de cor. Fonte: pseudocódigo do decompiler Ghidra + export de funções (symbols.csv, callgraph_simplified.csv).

## Confiança

`alta` — endereço confirmado em `symbols.csv` como `?Initialize@GCColorManipulationLayer@@SA_NXZ`; pseudocódigo coerente com o comportamento de singleton descrito na triagem (seção 4 do TRIAGE.md).

---