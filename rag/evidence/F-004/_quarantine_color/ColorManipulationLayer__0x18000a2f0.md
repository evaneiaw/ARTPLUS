---
modulo: ColorManipulationLayer.dll
versao: 25.0
funcao: 0x18000a2f0
nome: GCCallbackConverter::ConvertColor (?ConvertColor@GCCallbackConverter@@UEBAXAEBV?$GTable@N@@AEBV?$GTable@PEBVGFunction@@@@PEBVGFunction@@2AEAV2@@Z)
endereco: 0x18000a2f0
confianca: media
xrefs: [0x180040430, 0x18005093c]
strings: []
---

# O que a função faz

**Observado (via symbols.csv demangling):**
`GCCallbackConverter::ConvertColor(GTable<N> const&, GTable<GFunction*> const&, GFunction*, int, GTable<...>&)` é uma função membro virtual (`UEBA`) da classe `GCCallbackConverter`, responsável por conversão de cor via mecanismo de callback.

A assinatura demangled completa indica parâmetros:
- `AEBV?$GTable@N@@` — tabela de números (double) de entrada
- `AEBV?$GTable@PEBVGFunction@@@@` — tabela de ponteiros de função (callbacks)
- `PEBVGFunction` — função de callback
- `int` — parâmetro adicional
- `AEAV2@` — tabela de saída (referência ao mesmo tipo de tabela de saída)

**Não foi possível obter pseudocódigo via REA:** a chamada `rea decompile ... --procedure 0x18000a2f0` falhou com `target_unavailable` (o caminho do binário `C:\bg_prog_artpro+_v250\...` não existe neste ambiente). O import do Ghidra foi feito com sucesso e o endereço está confirmado em `symbols.csv`.

## Evidência

- Pseudocódigo bruto: NÃO DISPONÍVEL (falha do REA; veja `ColorManipulationLayer__0x18000a2f0.json` com registro de limitação)
- Xrefs de entrada: `0x180040430` (DATA), `0x18005093c` (DATA) — referências de dados que contêm o endereço da função
- Chamadas de saída: não registradas no callgraph exportado (não há entrada para este endereço como chamador em `callgraph_simplified.csv`)
- Strings vizinhas: nenhuma encontrada diretamente no `strings.csv` próximo ao endereço

## Inferência

> Inferência: `GCCallbackConverter::ConvertColor` é o caminho de conversão de cor que permite injetar callbacks de transformação (via `GTable<GFunction*>`), usado para conversões customizadas entre espaços de cor (ICC ↔ device ↔ calibrated). Fonte: demangling do símbolo exportado + triagem (seção 4 do TRIAGE.md).

## Confiança

`media` — endereço e assinatura confirmados em `symbols.csv`, mas pseudocódigo não disponível (falha do REA) e comportamento exato não verificado por decompiler.

---