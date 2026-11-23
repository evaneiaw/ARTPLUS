---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x1802988F0
endereco: 0x1802988F0
nome: "FUN_1802988F0"
confianca: media
xrefs: ["0x180490D1C", "0x180052BF1", "0x18013659E", "0x180330B58"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---

# FUN_1802988F0 — Geração de posições para referência por objeto/grid (v24.03.10017)

## Identificacao

- Endereco: `0x1802988F0`
- Nome: `FUN_1802988F0` (nome generico Ghidra; nao desmangulado)
- Assinatura decompilada: `void FUN_1802988F0(undefined8 param_1, undefined8 param_2, undefined8 param_3)`
- Convenção de chamada: `__cdecl` (Ghidra default)
- Tamanho do corpo: ~30 bytes (instrucoes)

## Xrefs

### Callers (xrefs de entrada)
- `0x180052BF1` -> `CutMark::regenerateMarkImp` @ `0x180052950` (chamada incondicional, caminho legado)
- `0x18013659E` -> `PDFPlusCutMark::regenerateMarkImp` @ `0x180136190` (chamada incondicional, caminho PDF+)
- `0x180490D1C` -> referencia de dados (tabela de modulo)
- `0x180330B58` -> referencia de dados (tabela de modulo)

### Callees (xrefs de saida)
- `0x18004A880` -> funcao utilitaria (inicializacao/limpeza do vetor?)
- `0x1802983F0` -> gerador de posicoes para um eixo/direcao (chamado duas vezes)

### Strings referenciadas
- (nenhuma)

## Analise do Pseudocodigo

```c
void FUN_1802988F0(undefined8 param_1, undefined8 param_2, undefined8 param_3)
{
  // param_1: objeto de referencia com GridInterface (ou dados do grid)
  // param_2: retangulo/dimensoes ou transformacao
  // param_3: ponteiro para dm::MarkPositionVector
  
  // Limpa/inicializa o vetor de posicoes
  FUN_18004a880(param_3);
  
  // Chama gerador com flag = 1 (eixo vertical? ou primeira direcao?)
  FUN_1802983f0(param_1, param_2, 1, param_3);
  
  // Chama gerador com flag = 0 (eixo horizontal? ou segunda direcao?)
  FUN_1802983f0(param_1, param_2, 0, param_3);
  return;
}
```

## Interpretacao para F-001 (Cut Mark)

Esta funcao e chamada em `regenerateMarkImp` (slot [29] de `PDFPlusCutMark`, `0x180136190`) **quando a referencia e por objeto** (`this+0x838 == 1`). O fluxo:

1. `regenerateMarkImp` obtem o objeto referenciado por `GetObjectWithID(*(uint64*)(this+0x7C0))`.
2. Valida que o objeto implementa `GridInterface` via `__RTDynamicCast`.
3. Chama `FUN_1802988F0(gridObj, bounds, &markPosVector)`.

**O que a funcao faz:**
- Chama `FUN_18004a880` para inicializar/limpar o `MarkPositionVector` (`param_3`).
- Chama `FUN_1802983f0` duas vezes:
  - Primeira com flag `1`
  - Segunda com flag `0`
- As duas chamadas sugerem **dois eixos** (horizontal e vertical) ou **duas direcoes** para posicionamento em relacao a um grid/repeticao de objetos.

**Contagem de posicoes:**
- A contagem de posicoes depende do numero de celulas no grid (`param_1`) multiplicado pelo numero de marcas geradas por `FUN_1802983f0`.
- Para um unico objeto simples (1x1), `FUN_1802983f0` provavelmente gera marcas para os limites desse objeto.
- Para um grid NxM, gera marcas para todas as celulas/estacoes.

**Limitacoes:**
- `FUN_1802983f0` nao foi decompilada nesta sessao; sua logica interna determina quantas posicoes sao adicionadas por chamada.
- Os tipos exatos de `param_1` e `param_2` dependem do contexto de chamada em `regenerateMarkImp`.

## Relacao com a Spec F-001

- **R4 (Referência por objeto)**: confirma que objetos de referencia precisam suportar `GridInterface` para ter marcas geradas por este caminho.
- **R7 (Geração da geometria)**: confirma que o caminho de objeto e o caminho de PageBox convergem no mesmo `dm::MarkPositionVector`, gerando um `Group` por posicao.

---

_Fonte: Ghidra 12.2 headless, DocumentMarks.dll, 0x1802988F0_