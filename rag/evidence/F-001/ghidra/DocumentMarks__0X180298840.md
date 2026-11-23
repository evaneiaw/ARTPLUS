---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180298840
endereco: 0x180298840
nome: "FUN_180298840"
confianca: media
xrefs: ["0x180490D10", "0x180052CAC", "0x18013668B", "0x180330B50"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---

# FUN_180298840 — Geração de posições para PageBox (v24.03.10017)

## Identificacao

- Endereco: `0x180298840`
- Nome: `FUN_180298840` (nome generico Ghidra; nao desmangulado)
- Assinatura decompilada: `void FUN_180298840(longlong *param_1, double *param_2)`
- Convenção de chamada: `__cdecl` (Ghidra default)
- Tamanho do corpo: ~110 bytes (instrucoes)

## Xrefs

### Callers (xrefs de entrada)
- `0x180052CAC` -> `CutMark::regenerateMarkImp` @ `0x180052950` (chamada incondicional, caminho legado)
- `0x18013668B` -> `PDFPlusCutMark::regenerateMarkImp` @ `0x180136190` (chamada incondicional, caminho PDF+)
- `0x180490D10` -> referencia de dados (tabela de modulo)
- `0x180330B50` -> referencia de dados (tabela de modulo)

### Callees (xrefs de saida)
- Chamada virtual via vtable: `(*param_1 + 0x10)` — metodo `push_back` ou similar de `dm::MarkPositionVector` (nao resolvido estaticamente)

### Strings referenciadas
- (nenhuma)

## Analise do Pseudocodigo

```c
void FUN_180298840(longlong *param_1, double *param_2)
{
  // param_1: ponteiro para dm::MarkPositionVector (objeto com vtable)
  // param_2: ponteiro para 4 doubles = retangulo [x0, y1, x2, y3]
  //          nota: y1 = top, y3 = bottom (coordenadas com origem no topo?)
  
  // Copia os 4 cantos do retangulo
  local_a0 = *param_2;        // x0 (left)
  dStack_98 = param_2[1];     // y1 (top)
  local_90 = param_2[2];      // x2 (right)
  dStack_88 = param_2[3];     // y3 (bottom)
  
  // Calcula largura e altura
  local_70 = param_2[2] - *param_2;      // width  = x2 - x0
  local_68 = param_2[1] - param_2[3];    // height = y1 - y3
  
  // Inicializa estrutura local (aparentemente 4 posicoes base?)
  local_58 = 0;
  local_a8 = 1;   // flag 1
  local_a4 = 1;   // flag 2
  local_80 = 0;
  uStack_78 = 0;
  local_60 = 0;
  local_50 = 1;   // flag 3
  local_4c = 0;
  local_48 = 0;
  local_38 = 0;
  
  // Chama metodo virtual no offset 0x10 do objeto param_1 (MarkPositionVector)
  // Passa largura (truncada a int?) e ponteiro para estrutura local
  (**(code **)(*param_1 + 0x10))(SUB84(local_70,0), &local_a8);
  return;
}
```

## Interpretacao para F-001 (Cut Mark)

Esta funcao e chamada em `regenerateMarkImp` (slot [29] de `PDFPlusCutMark`, `0x180136190`) **quando a referencia e PageBox** (`this+0x838 == 0`). O fluxo:

1. `regenerateMarkImp` obtem a caixa de referencia via `GetReferenceBox` (retorna `RectangleBase` com 4 doubles).
2. Cria um `dm::MarkPositionVector` (vftable em `local_9D8`).
3. Chama `FUN_180298840(rect, vector)` para popular o vetor com as posicoes de marca.

**O que a funcao faz:**
- Recebe o retangulo da caixa de pagina (4 doubles: left, top, right, bottom).
- Calcula `width` e `height`.
- Prepara uma estrutura local com flags (provavelmente definindo 4 posicoes base: 4 cantos?).
- Invoca o metodo virtual no offset `0x10` do `MarkPositionVector` — este e provavelmente `push_back` ou `addPosition`, chamado **uma vez** com a estrutura preparada.

**Contagem de posicoes:**
- A funcao so faz **uma chamada** ao metodo virtual do vetor.
- A estrutura `local_a8`..`local_38` parece codificar **4 posicoes** (cantos do retangulo) em uma unica chamada, ou o metodo chamado itera internamente.
- **Nao e possivel determinar a contagem exata** sem descompilar o metodo virtual do `MarkPositionVector` (vtable offset 0x10) ou analisar `FUN_1802983F0` (usado pelo caminho objeto).

**Limitacoes:**
- A chamada virtual `(*param_1 + 0x10)` nao e resolvida estaticamente; o alvo real esta na vtable de `dm::MarkPositionVector`.
- A estrutura passada (`&local_a8`) tem 10 campos (40+ bytes) — sua interpretacao exata requer a definicao de `dm::MarkPosition`/`MarkPositionVector`.
- Nenhuma string ou literal de debug no corpo.

## Relacao com a Spec F-001

- **R7 (Geração da geometria)**: confirma que `FUN_180298840` e o gerador de posicoes para o caso PageBox.
- **Lacuna declarada (Item 1, §8)**: a contagem de posicoes em `dm::MarkPositionVector` ainda nao foi medida; esta funcao faz uma unica chamada virtual que pode inserir multiplas posicoes.

---

_Fonte: Ghidra 12.2 headless, DocumentMarks.dll, 0x180298840_