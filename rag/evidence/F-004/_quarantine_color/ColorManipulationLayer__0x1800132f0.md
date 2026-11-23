---
modulo: ColorManipulationLayer.dll
versao: 25.0
funcao: 0x1800132f0
nome: GCColorManipulation::GetInstance (?GetInstance@GCColorManipulation@@SAAEAV1@XZ)
endereco: 0x1800132f0
confianca: alta
xrefs: [0x1800405c8]
strings: []
---

# O que a função faz

**Observado (via REA/Ghidra decompiler):**
`GCColorManipulation::GetInstance()` implementa o padrão singleton: retorna o ponteiro estático `sInstance` da classe `GCColorManipulation`. É o ponto de acesso global à API de manipulação de cores da DLL.

## Evidência

- Pseudocódigo bruto: `rag/evidence/F-004/ghidra/ColorManipulationLayer__0x1800132f0.json`
- Xrefs de entrada: `0x1800405c8` (DATA)
- Chamadas de entrada (call graph): `0x1800042d0` (FUN_1800042d0), `0x180004fd0` (FUN_180004fd0), `0x180014cc0` (InitializeXYZProfile)
- Strings vizinhas: nenhuma encontrada diretamente no `strings.csv` próximo ao endereço

## Inferência

> Inferência: `GetInstance` é o único ponto de entrada público para acessar o singleton `GCColorManipulation`; todo fluxo de conversão de cor passa por ele indiretamente. Fonte: pseudocódigo do decompiler Ghidra + symbols.csv.

## Confiança

`alta` — endereço confirmado em `symbols.csv` como `?GetInstance@GCColorManipulation@@SAAEAV1@XZ`; pseudocódigo direto e simples do decompiler.

---