## Bearer Bar Mark

- **Captura:** `CAP-20261119-02` — **histórico (v25.03.116)**, fora do fluxo ativo (registro mantido por rastreabilidade, não é especificação da v24).
- **Versão:** 24.03.10017 (App v240 — `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe`, sha256 do executável `ArtPro+.exe`: `9D33166126305F25C50349BB881F7D9ACDC996F3C0C9181D0BE61295D70B0F03`)
- **Caminho na UI:** painel `Marks` → botão `+` → item **`Add Bearer Bar Mark`** (observado na captura histórica v25 `CAP-20261119-02`; não re-executado em v24 nesta sessão).
  - Rótulo literal do item de menu: `Add Bearer Bar Mark` (ver `crop-marks-menu.png`).
  - Itens irmãos no mesmo menu (observados na captura da F-001): `Add Cut Mark`, `Add Repeat for Grid Mark`, `Add Dimensions Mark`, `Add External File Mark`, `Add Position Mark`, `Add Input File Mark`.
- **Entrada:** `tools/reference_capture/F-003/input/test_vector.pdf`
  - Documento: `test_vector.pdf @ 97,52%` (após criação, título ganha `*`)
  - SHA-256 do input: `ADFD91B4E95BCE3708DB37055885C355880068EE53A1472AB1DC82E0820640D7`
  - É o mesmo arquivo usado na `CAP-20261119-01` (F-001, hash idêntico): Media Box **210,00 x 297,00 mm**, perfil **ISO Coated v2 300% (ECI)**, separações Cyan/Magenta/Yellow/Black + `PANTONE 485 C`.
  - `input/test_vector.pdf` não foi alterado; `output/` ficou vazio.

### Captura v24 (2026-11-23)

- versao_ref: 24.03.10017
- sha256 executável v240 (`ArtPro+.exe`): `9D33166126305F25C50349BB881F7D9ACDC996F3C0C9181D0BE61295D70B0F03`
- fluxo capturado nesta sessão: abertura do aplicativo (diálogo de licença apresentado, fechado com **Continue**) e abertura do PDF `test_vector.pdf` na ArtPro+ v24.03.10017.
- **Não houve criação da Bearer Bar Mark nesta sessão v24:** o fluxo de criação (Marks → + → Add Bearer Bar Mark) não foi executado. **`CAP-20261123-04` (criação da Bearer Bar) não existe**; registrar como lacuna/bloqueio comportamental.
- CAP-20261123-* existentes (cópia em `tools/reference_capture/F-003/shots/` e `rag/evidence/F-003/behavior/`):
  - `CAP-20261123-01-initial-with-license.png` — tela inicial com diálogo de licença aberto
  - `CAP-20261123-02-after-continue.png` — após clique em Continue (diálogo de licença fechado)
  - `CAP-20261123-03-open-pdf.png` — `test_vector.pdf` aberto na ArtPro+ v24.03.10017

### Criação (sem diálogo modal)
1. `Marks` → `+` → `Add Bearer Bar Mark`.
2. **Não abre diálogo modal.** A marca é criada direto no documento.
3. Resultado imediato:
   - o título da janela ganha `*`;
   - a barra de contexto no topo vira **`Dynamic Marks | Bearer Bar Mark 1`**;
   - o painel `Marks` passa a listar a linha **`Bearer Bar Mark 1`, acima de `Cut Mark 1`** (a marca nova é inserida no topo da lista, não no fim).

### Campos do diálogo
Não há diálogo de criação **e nesta sessão nenhum campo numérico próprio foi localizado** (espessura, offset, comprimento, lados).

Barra de contexto observada com `Bearer Bar Mark 1` ativa (`crop-contextbar-bearerbar.png`):

| Controle | Tipo | Valor observado | Significado |
|---|---|---|---|
| `Normal` | dropdown | `Normal` | não confirmado (modo de render/overprint?) |
| `100%` | campo/dropdown | `100%` | não confirmado (opacidade/força?) |
| `Registration` | dropdown | `Registration` | não confirmado (tinta/cor da marca?) |
| `Trim Box` | dropdown de ancoragem | `Trim Box` | ancoragem da marca (mesmo padrão do `Attach to:` do Cut Mark) |

Nenhum dos quatro controles acima expõe valor numérico em mm — portanto **os parâmetros geométricos da barra não são editáveis por este caminho** na UI observada.

### Saída observada (visual)
Medições de pixel na tela (zoom 97,52%), obtidas pelos scripts `scan_red.ps1` / `scan_red_lines.ps1` / `scan_row.ps1` e pelos recortes `probe-*`:

- **Media Box:** cor laranja `247,143,73`, desenhada como traços verticais em **x=541–542** e **x=1121–1122**, com topo em **y≈183**.
- **Bearer Bar:** **faixa preenchida em cinza `168,164,164`**, encostada **por fora** do Media Box; a aresta **externa** é um **filete vermelho `255,79,79` de 1 px**, medido em **x=527** e **x=1716** (topo/arestas verticais).
- **Bounding box observado da barra:** `527,186 → 1726,1006`.
- ⚠️ **Correção de descrição:** a marca **não** é "linha fina"; é **faixa/barra preenchida cinza com filete vermelho na aresta externa**.
- A assimetria entre a aresta esquerda da barra (x=527) e o eixo esquerdo medido do Media Box (x=541–542), versus a aresta direita (x=1716) e o eixo direito (x=1121–1122), **não foi explicada nesta captura** — registrar como lacuna, não como regra de offset.
- Objetos de arte do documento permanecem intactos; a barra é um item separado listado em `Marks`.

### Tentativas de inspeção (sem resultado)
- **Duplo clique** na marca: não abriu inspetor com campos.
- **Botão direito** na marca: abriu **menu radial/pie** (não um menu de propriedades) — `attempt-rightclick-pie.png`.
- **Menu `View`:** inspecionado, sem item de propriedades da marca utilizável — `attempt-view-menu-inspector.png`.
- **`Open Next Inspector`:** foi clicado, mas **o resultado não foi capturado** — registrar como **não confirmado** (`shot-05-ctrl-i.png` só mostra o estado da tela após o atalho).

### Erros e limites (lacunas registradas)
- **Nenhum campo numérico próprio localizado** para Bearer Bar (espessura, offset, comprimento, lados). Só existem `Normal` / `100%` / `Registration` / `Trim Box` na barra de contexto. Não inferir nomes/defaults de campo.
- **Inspetor não confirmado:** `Open Next Inspector` foi acionado mas a tela resultante não foi capturada; não se sabe se existe inspetor com campos.
- **PDF de saída não gerado:** nenhum Save As/export foi tentado nesta sessão (por instrução); `tools/reference_capture/F-003/output/` está **vazio**. O PDF resultante com a barra permanece lacuna.
- **Referência estática já existente** (não verificada nesta sessão): `rag/evidence/F-003/ghidra/DocumentMarks__0x18001E3C0.md` (ctor) e `rag/evidence/F-003/ghidra/DocumentMarks__0x18001E350.md` (clone).

### Capturas
`tools/reference_capture/F-003/shots/` (copiadas também para `rag/evidence/F-003/behavior/`):

- `shot-01-initial.png` — estado inicial (documento aberto, `test_vector.pdf @ 97,52%`)
- `shot-02-maximized.png` — janela maximizada
- `shot-03-marks-dropdown.png` — dropdown de criação do painel `Marks` (com `Add Bearer Bar Mark`)
- `shot-04-after-add-bearerbar.png` — após `Add Bearer Bar Mark`: título com `*`, `Dynamic Marks | Bearer Bar Mark 1`
- `shot-05-ctrl-i.png` — estado após `Open Next Inspector` (resultado **não confirmado**, sem inspetor capturado)
- `crop-marks-menu.png` — recorte do menu de criação
- `crop-marks-panel-bearerbar.png` — recorte do painel: `Bearer Bar Mark 1` acima de `Cut Mark 1`
- `crop-contextbar-bearerbar.png` — recorte da barra de contexto (`Normal`, `100%`, `Registration`, `Trim Box`)
- `crop-edge-top-left.png` — canto superior-esquerdo (barra cinza + filete vermelho externo)
- `crop-edge-left-mid.png` — meio da aresta esquerda
- `crop-edge-bottom-right.png` — canto inferior-direito
- `probe-live.png` — tela completa durante as medições de pixel
- `probe-top-edge.png` — sondagem da aresta superior
- `probe-corner-tl.png` — sondagem do canto superior-esquerdo
- `probe-corner-tr.png` — sondagem do canto superior-direito
- `attempt-rightclick-pie.png` — menu radial/pie do botão direito (sem propriedades)
- `attempt-view-menu-inspector.png` — menu `View` inspecionado (sem item útil de inspetor)

### Capturas v24 (2026-11-23)
`tools/reference_capture/F-003/shots/CAP-20261123-*.png` (copiadas também para `rag/evidence/F-003/behavior/`):

- `CAP-20261123-01-initial-with-license.png` — tela inicial com diálogo de licença aberto
- `CAP-20261123-02-after-continue.png` — após clique em Continue (diálogo de licença fechado)
- `CAP-20261123-03-open-pdf.png` — `test_vector.pdf` aberto na ArtPro+ v24.03.10017
