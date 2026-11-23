# DocumentMarks.dll — RE Report

## Visão Geral
Mapeamento de funções críticas de marcação (F-006).

| Função | Endereço | Nota |
|---|---|---|
| `updatePdfPropertiesDictImp@BarcodeMark` | `0x18001D6C0` | Atualiza o dicionário PDF do BarcodeMark. |
| `updatePdfPropertiesDictImp@BearerBar` | `0x180020950` | Atualiza o dicionário PDF do BearerBar. |
| `wrapMarkSelection` | `0x180076C90` | Gerencia seleção e agrupamento de marcas. |
| `CutMark::CutMark` | `0x180052340` | Construtor principal da marca de corte. |
| `GradationMark` (ColorBar) | `0x1800CF820` | Construtor da GradationMark (barra de cor). |

## Evidência (Pseudocódigo e Detalhes)

### 1. `updatePdfPropertiesDictImp@BarcodeMark` (0x18001D6C0)
*   **Xrefs:** Chamada por `DocumentMarks::PDFPlusBarcodeMark::updatePdfPropertiesDictImp`.
*   **Comportamento:** Serializa parâmetros de BarcodeMark (código, formato, cor) para dicionário PDF.

### 2. `wrapMarkSelection` (0x180076C90)
*   **Xrefs:** Referenciado em operações de UI de seleção de marcas.
*   **Comportamento:** Envolve uma lista de marcas (`vector<ContentObject*>`) em um container de seleção, garantindo consistência com o modelo do Documento.

### 3. `CutMark::CutMark` (0x180052340)
*   **Xrefs:** Construtor chamado durante instanciação de CutMark via `DocumentMarks::Factory`.
*   **Comportamento:** Inicializa flags de marca de corte (ex: corte de vinco, marcação padrão).

### 4. `BearerBar::BearerBar` (0x18001E350)
*   **Xrefs:** Chamado pela `BearerBarFactory`.
*   **Comportamento:** Inicializa parâmetros da barra de registro (offset, largura).

### 5. `GradationMark` (0x1800CF820)
*   **Xrefs:** Chamado durante criação de Color Bar.
*   **Comportamento:** Cria o objeto de marca de gradação (Color Bar).

## Confiança
- **Alta**: Funções exportadas e claramente identificadas via RTTI/Visitor pattern mapeado no Ghidra.
- **Limitação**: O decompilador Ghidra exige mais contexto de símbolos para resolver templates C++ de `ConstVisitor`.
