# F-004 — Selection Mark — comportamento observado na v24.03.10017

- Captura: **CAP-20261121-02**
- Versão: **24.03.10017**
- Data da sessão: 2026-11-21
- Binário executado (UI): `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe`
- DLL da evidência estática desta feature: `...\Contents\Windows\PDFObjectActions.dll`
  (SHA-256 `8F6A23C1533E45AF657D91E62C18379AF3FE5B59C947C04A068A42E43573184D`, 8.004.528 bytes)
- Caminho na UI procurado: **`Marks > Selection Mark`** (caminho declarado na spec F-004 §3)
- Entrada: `tools/reference_capture/F-004/input/test_vector.pdf`
  - `sha256` pré-abertura e pós-encerramento: `ADFD91B4E95BCE3708DB37055885C355880068EE53A1472AB1DC82E0820640D7`
  - Tamanho: `1868` bytes
  - Origem: cópia de `tools/reference_capture/F-005/input/test_vector.pdf` (nunca o original)
- Estado inicial: nenhum processo `ArtPro+` nem `QtWebEngineProcess` em execução
- Estado final: `ArtPro+ = 0`, `QtWebEngineProcess = 0`; `tools/reference_capture/F-004/output/` vazio; hash do input inalterado

## Resultado em uma linha

**Negativo.** Na v24.03.10017 não existe a ação `Selection Mark` — nem o menu `Marks` — nos
menus `File`, `Object`, `Select` e `Prepress`, nem entre os rótulos do ribbon. O atalho
`Ctrl+Shift+S` que a descrição histórica atribui a *Selection Mark* está atribuído, no menu
`File`, a **`Save As...`**.

## Passos executados (literal)

1. `Start-Process 'C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe' -WorkingDirectory '<pasta do exe>'`
   - Resultado: PID `15444`; em T+14 s a janela principal é o diálogo **`ArtPro+ License Info`** (770x587 em 565,185; área cliente 754x548).
2. Diálogo modal `ArtPro+ License Info`, lido por UIA.
   - Texto literal: `A suboptimal combination of ArtPro+ Edition licenses has been selected.  An ArtPro+ Essentials license offers all of the features of an ArtPro+ Digital license and more. [...]`
   - `License Server: localhost`, link `(Change)`.
   - Colunas: `Edition License | Status | Type | Remaining Days`.
   - Edições principais: `ArtPro+ Essentials 24`, `ArtPro+ Layout 24`, `ArtPro+ Digital 24` (todas `network` / `Unlimited`).
   - Bloco `Additional Licenses`: `ArtPro+ Advanced 24`, `ArtPro+ Plate Cut`, `ArtPro+ GMG OpenColor Connector`, `ArtPro+ Equinox`, `ArtPro+ Variable Data Expansion`, `Studio Designer 20`, `Studio Toolkit for Labels 20`, `Studio Toolkit for Shrink Sleeves 20`.
   - Botões: **`Continue`** (1232,720 75x24), `Quit ArtPro+` (1146,720 76x24).
   - Ação: clique em `Continue` → diálogo fecha. Janela principal `ArtPro+` (974x1039 em 953,0), sem HASP e sem erro. Captura `shot-01-license-dialog.png`, `shot-02-app-open.png`.
3. Estado vazio: barra de menus literal **`File  Edit  Object  Select  Prepress  View  Window  Help`**.
   - Observação: **não existe menu `Marks`** na barra de menus.
4. Clique em `File` (978,39) → popup 337x571 em (961,52). Itens literais, na ordem, com o atalho exibido à direita:
   `New  Ctrl+N`, `New Report Template...`, `Open...  Ctrl+O`, `Open Recent  ▸`, `Close  Ctrl+W`,
   `Close All  Ctrl+Alt+W`, `Save  Ctrl+S`, **`Save As...  Ctrl+Shift+S`**, `Export To  ▸`,
   `Convert To PDF+`, `Convert To Report Template...`, `Convert To Variable Data Template...`,
   `Action Lists  ▸`, `Launch Workflow...  Ctrl+L`, `Insert Content From PDF...`,
   `Place File...  Ctrl+Shift+P`, `Place Image Inside...  Ctrl+Alt+Shift+P`, `Pages  ▸`,
   `Page Boxes Setup...  Ctrl+Alt+P`, `Document Setup...`, `Print...  Ctrl+P`, `Exit  Ctrl+Q`.
   - **Nenhum item `Selection Mark`.** Captura `shot-03-file-menu.png`.
5. `File > Open...` (981,114) → diálogo **nativo do Windows** `Open File`, 641x468 em (974,36).
   - Rótulos: `Examinar:`, `Name:`, `Tipo:`, botões **`Abrir`** e `Cancelar`.
   - Filtro literal: `All supported documents (*.pdf; *.pdpdla; *.ap; *.art)`.
   - Colunas da lista: `Nome`, `Data de modificação`, `Tipo`; shell em pt-BR (`Início`, `Área de Trabalho`, `Bibliotecas`, `Este Computador`, `Rede`); cabeçalho em inglês.
   - Estado inicial do diálogo: pasta `input` (memória da última abertura) listando `test_vector`. Captura `shot-04-document-open.png`.
6. Clique na linha `test_vector` → o campo `Name:` passa a exibir `test_vector`.
   - `Enter` no campo `Name:` **não** abre o documento (comportamento já registrado em CAP-20261121-01).
7. Clique em **`Abrir`** (1565,427) → diálogo fecha e o documento abre em T+10 s.
   - Título da janela: **`test_vector.pdf @ 96,45% - ArtPro+`**.
   - Estado da janela: `Media Box 210,00 x 297,00 mm`; `Document` → `Crosshair`, `Page Boxes`;
     `Layers` → 1 camada `Unlayered Art`; `Marks` → **vazio**; `Separations` →
     `Document Profile: ISO Coated v2 300% (ECI)`, `Cyan #1`, `Magenta #2`, `Yellow #3`, `Black #4`, `PANTONE 485 C #5`;
     `Quality Control` → `Total Area Coverage`, `Limit: 270%`.
   - Captura `shot-05-document-open.png`.
8. Leitura do ribbon (rótulos de aba/toolbar, da esquerda para a direita):
   `Object Browser`, `Colors`, `Images`, `Placed Art`, `Messages`, `Action Lists`, `Share & Approve`,
   `Clean`, `Select`, `Recolor`, `Sharper`, `Barcode`, `Screening`, `Trapping`, `Warp`, `3D`.
   - **Nenhum rótulo `Selection Mark` nem `Marks` no ribbon.** Captura `shot-09-select-ribbon.png`.
9. Menu `Select` (1105,39) → popup. Itens literais:
   `Select All  Ctrl+A`, `Deselect All  Ctrl+Shift+A`, `Select Inverse  Ctrl+Alt+A`,
   `Select Next Object  Ctrl+Tab`, `Select Previous Object  Ctrl+Shift+Tab`,
   `Select...  Ctrl+U`, `Select Same Fill Color  Ctrl+Alt+I`,
   `Select Same Stroke Color  Ctrl+Alt+Shift+I`, `✓ Select by Paths (Outline Mode)`.
   - **Nenhum item `Selection Mark`.** Captura `shot-06-select-menu.png`.
10. Menu `Prepress` (1158,39) → popup. Itens literais:
    `Add Barcode  Ctrl+Shift+B`, `Convert to Barcode  Ctrl+Alt+Shift+B`, `Add Dimensions  Ctrl+Shift+L`,
    `Add Bleed...`, `White Underprint...  Ctrl+Shift+W`, `Rich Black...`, `Ink Eater Areas  ▸`,
    `Screening...  Ctrl+Alt+S`, `Ink Coverage...`, `Convert Separations With  ▸`, `Thin Parts`,
    `Update Trap Layer  Ctrl+T`, `Trapping...  Ctrl+Alt+T`, `Warp  ▸`, `Preflight...`,
    `Manage Preflight Profiles...`, `Variable Data  ▸`, `Step & Repeat  ▸`,
    `Create Seamless Repetition...`, `Flexo Tools  ▸`.
    - **Nenhum item `Selection Mark`.** Captura `shot-07-prepress-menu.png`.
11. Menu `Object` (1046,39) → popup. Itens literais:
    `Arrange`, `Transform...  Ctrl+Shift+M`, `Transform Again  Ctrl+D`, `Group  Ctrl+G`,
    `Ungroup  Ctrl+Shift+G`, `Lock  Ctrl+2`, `Unlock All  Ctrl+Alt+2`, `Hide  Ctrl+3`,
    `Show All  Ctrl+Alt+3`, `Path  ▸`, `Compound  ▸`, `Clipping Mask  ▸`, `Opacity Mask  ▸`,
    `Image  ▸`, `Text  ▸`, `Placed Art  ▸`, `Remove Color Profile  ▸`, `Recolor...`,
    `Shaper...  Ctrl+E`, `Spread/Choke...  Ctrl+Shift+T`, `Expand`, `Rasterize...`,
    `Clean  ▸`, `Clip  ▸`, `Fit  ▸` (lista continua abaixo da área capturada).
    - **Nenhum item `Selection Mark`.** Captura `shot-08-object-menu.png`.
12. Encerramento: `Stop-Process -Id 15444 -Force` → `ArtPro+ = 0`, `QtWebEngineProcess = 0`.
    - Nenhum diálogo de gravação apareceu; `tools/reference_capture/F-004/output/` vazio; hash do input igual ao pré-abertura.

### Passos deliberadamente **não** executados

- **`Ctrl+Shift+S` não foi pressionado.** O menu `File` já exibe o atalho ao lado de
  `Save As...`, e acioná-lo abriria o diálogo de gravação — risco desnecessário para a
  captura. Registrado como **atribuição lida na UI**, não como efeito testado.
- `View`, `Window`, `Edit` e `Help` **não foram abertos** (ver "Não medido").
- Nenhum objeto foi selecionado no canvas; a toolbar de contexto do objeto ativo
  (aba `Object Browser`) e seus ícones **não foram inspecionados**.

## Campos dos diálogos observados

`ArtPro+ License Info`

| nome | tipo | default | unidade | faixa aceita |
|---|---|---|---|---|
| `License Server:` | texto + link `(Change)` | `localhost` | — | não editado |
| tabela de edições | tabela somente leitura | — | — | — |
| `Continue` | botão (default) | — | — | — |
| `Quit ArtPro+` | botão | — | — | — |

`Open File` (diálogo nativo, pt-BR parcial)

| nome | tipo | default | unidade | faixa aceita |
|---|---|---|---|---|
| `Examinar:` | combo + árvore de pastas | `input` (última pasta usada) | — | qualquer pasta acessível |
| `Name:` | edit | vazio / `test_vector` após seleção | — | nome ou caminho absoluto |
| `Tipo:` | combo de filtro | `All supported documents (*.pdf; *.pdpdla; *.ap; *.art)` | — | filtro único observado |
| `Abrir` | botão (default) | — | — | — |
| `Cancelar` | botão | — | — | — |

## Saída observada

| item | valor observado |
|---|---|
| Diálogo de Selection Mark | **não existe / não abriu** — nenhum item ou ícone com esse nome foi encontrado |
| Mensagem de status `Selection Mark ativo` | **não observada** — a ação não foi localizável para acionar |
| Handles de seleção | **não observados** |
| Arquivo gravado | **nenhum** (`output/` vazio) |
| Título da janela | `test_vector.pdf @ 96,45% - ArtPro+` |
| Overlay de caixa | `Media Box 210,00 x 297,00 mm` |
| Hash do input após a sessão | `ADFD91B4E95BCE3708DB37055885C355880068EE53A1472AB1DC82E0820640D7` (inalterado) |

## Conclusão negativa — o que NÃO existe na v24.03.10017

1. **Não existe menu `Marks`.** A barra de menus é `File  Edit  Object  Select  Prepress  View  Window  Help`.
   O caminho `Marks > Selection Mark` da spec F-004 §3 é **irreproduzível** na versão-alvo.
2. **Não existe item `Selection Mark`** em `File` (22 itens lidos), `Object` (25 itens lidos
   acima da área visível do popup), `Select` (9 itens lidos) nem `Prepress` (20 itens lidos).
3. **Não existe rótulo `Selection Mark` no ribbon** (16 rótulos lidos).
4. **`Ctrl+Shift+S` não é Selection Mark**: o menu `File` atribui `Ctrl+Shift+S` a `Save As...`.
5. Coerente com a estática: `PDFObjectActions.dll` **não contém** as strings `SelectionMark`,
   `Selection Mark` nem `Selection mark` (37.006 strings, `ghidra/PDFObjectActions__identity.md` §5).
   O que o DLL implementa são operadores genéricos de **seleção e transformação**
   (`GOVSelectHitElement`, `GOVSelectOverlapping*`, `GOVChangeScaleSelection`,
   `GOVChangeRotateSelection`, `GOVChangeFlipSelection`, `GOVCloneSelection`) — sem nome de
   produto "Selection Mark" e sem string de UI.

> **Natureza da fonte histórica.** `docs/behavior/SelectionMark.md` declara
> `Versao: 25.0` — versão **histórica, fora do fluxo ativo** (AGENTS.md §0), sem nenhum ID
> `CAP-*` e sem artefato em `rag/evidence/F-004/behavior/`. A UI que ela descreve
> (ícone `Selection Mark` na toolbar, atalho `Ctrl+Shift+S`, status `Selection Mark ativo`)
> **não se reproduz** na v24.03.10017 pelos caminhos medidos nesta captura.

## Não medido (declarado, não inferido)

- **`View`, `Window`, `Edit`, `Help`**: menus não abertos nesta sessão. A ausência nesses
  menus **não** foi comprovada.
- **Toolbar de contexto do objeto ativo**: nenhum objeto foi selecionado; a aba
  `Object Browser` e a barra de ferramentas contextual (onde a descrição histórica situa o
  ícone "próximo ao botão Select") **não foram inspecionadas**.
- **Atalhos em geral**: não foi feita varredura sistemática de combinações; só se sabe que
  `Ctrl+Shift+S` pertence a `Save As...` por leitura do menu.
- **Efeito de `Ctrl+Shift+S`**: não acionado (evitou-se abrir o diálogo de gravação).
- **Títulos literais dos operadores do DLL** (`GStringPool::GetString(0x73FAA)` / `(0x63254)`):
  continuam não resolvidos — a captura não expõe esses textos.
- **Rubber-band / hit-test (`0x180276230`) e `SetHitType`/`SetRect`**: o comportamento de
  seleção por caixa no canvas **não foi exercitado** (nenhum arrasto foi feito). A evidência
  dessas regras continua sendo apenas estática.
- **Escala / rotação / flip / clone da seleção** (`GOVChange*Selection`): não exercitados.

## Erros e limites

- Nenhuma mensagem de erro do aplicativo em todo o fluxo (licença, abertura, menus).
- Nenhum diálogo de importação de PDF; abertura direta no viewport.
- **Limite de ferramenta**: o MCP `pc-control` respondeu `Request timed out` em
  `get_screen_info`, `screenshot` e `list_open_windows`. A sessão foi conduzida com
  `tools/reference_capture/F-004/ui.ps1` (Win32 `SetCursorPos`/`mouse_event`/`keybd_event`,
  UIA por `System.Windows.Automation`, captura por `CopyFromScreen`) e com
  `tools/reference_capture/F-001/capture.ps1`. Isso **não** afeta o conteúdo observado, mas
  fica registrado porque o caminho de captura não foi o previsto.
- `capture.ps1 -TitleMatch "ArtPro+"` falha com `NO_WINDOW` quando o `MainWindowTitle` fica
  vazio (logo após fechar o diálogo `Open File`); a captura foi feita por região de tela
  inteira (1920x1080).
- `shot-05-document-open.png` é captura de **desktop inteiro**: a metade esquerda mostra uma
  janela de editor alheia ao experimento (não é artefato do ArtPro+). A região do ArtPro+ é
  `x ≥ 960`. Mantida inteira conforme o aceite; para diff visual convém recortar.

## Divergências spec × v24

| # | spec F-004 diz | v24.03.10017 mostra |
|---|---|---|
| 1 | caminho `Marks > Selection Mark` | **não existe menu `Marks`**; barra é `File Edit Object Select Prepress View Window Help` |
| 2 | atalho `Ctrl+Shift+S` | atribuído a `Save As...` no menu `File` |
| 3 | ícone na toolbar próximo ao botão Select | nenhum rótulo `Selection Mark` entre os 16 do ribbon; toolbar de contexto não inspecionada |
| 4 | status `Selection Mark ativo` | não observado — ação não localizável |
| 5 | "não abre diálogo modal" | não aplicável: a ação não existe nos caminhos medidos |

## Capturas

Todas em `tools/reference_capture/F-004/shots/` (cópia em `rag/evidence/F-004/behavior/`):

| arquivo | o que mostra |
|---|---|
| `shot-01-license-dialog.png` | diálogo `ArtPro+ License Info` com `Continue` / `Quit ArtPro+` |
| `shot-02-app-open.png` | app aberto e vazio, menus `File Edit Object Select Prepress View Window Help` |
| `shot-03-file-menu.png` | popup `File` com os 22 itens e `Save As... Ctrl+Shift+S` |
| `shot-04-document-open.png` | diálogo nativo `Open File` com `test_vector` e o filtro literal |
| `shot-05-document-open.png` | documento aberto (`Media Box 210,00 x 297,00 mm`), painéis Document/Layers/Marks/Separations/Quality Control; captura de desktop inteiro |
| `shot-06-select-menu.png` | menu `Select` literal — sem `Selection Mark` |
| `shot-07-prepress-menu.png` | menu `Prepress` literal — sem `Selection Mark` |
| `shot-08-object-menu.png` | menu `Object` literal — sem `Selection Mark` |
| `shot-09-select-ribbon.png` | ribbon `Object Browser … Share & Approve  Clean  Select  Recolor  Sharper …` — sem `Selection Mark` |

## Notas operacionais para a próxima captura

- `pc-control` inoperante nesta sessão (timeout): use `tools/reference_capture/F-004/ui.ps1`
  (`-Action shot|click|keys|uia`).
- Após `Abrir`, o `MainWindowTitle` do processo fica vazio por alguns segundos; aguarde 8–12 s
  e capture por região/desktop em vez de por título.
- O diálogo `Open File` **não** é visível para `Get-Process MainWindowTitle`; clique por
  coordenada (linha do arquivo e botão `Abrir`).
- Para fechar a questão da UI, faltam: `View`, `Window`, `Edit`, `Help`, e a **toolbar de
  contexto com um objeto selecionado** — é o único lugar restante onde a descrição histórica
  poderia se materializar.
