# F-005 — Open Document (abrir PDF) — comportamento observado na v24.03.10017

- Captura: **CAP-20261121-01**
- Versão: **24.03.10017**
- Data da sessão: 2026-11-21
- Binário: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe`
- Caminho na UI observado: **`File > Open...`** (não existe menu `Documents` na v24)
- Entrada: `tools/reference_capture/F-005/input/test_vector.pdf`
  - `sha256` pré-abertura e pós-encerramento: `ADFD91B4E95BCE3708DB37055885C355880068EE53A1472AB1DC82E0820640D7`
  - Tamanho: `1868` bytes
  - Origem: cópia de `tools/reference_capture/F-001/input/test_vector.pdf` (original não aberto)
- Estado inicial do ambiente: nenhum processo `ArtPro+` em execução; janela do app ainda não aberta

## Passos executados (literal)

1. `Start-Process 'C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe' -WorkingDirectory '<pasta do exe>'`
   - Resultado: PID `9360` retornado; em T+20 s a janela principal tem título **`ArtPro+ License Info`**.
2. Diálogo modal **`ArtPro+ License Info`** (754x548 px, posição 573,216).
   - Conteúdo literal: `A suboptimal combination of ArtPro+ Edition licenses has been selected.` / `An ArtPro+ Essentials license offers all of the features of an ArtPro+ Digital license and more. [...]`
   - Campos: `License Server: localhost`, link `(Change)`; colunas `Edition License | Status | Type | Remaining Days`.
   - Edições listadas: `ArtPro+ Essentials 24`, `ArtPro+ Layout 24`, `ArtPro+ Digital 24` (todas `network` / `Unlimited`); bloco `Additional Licenses` com `ArtPro+ Advanced 24`, `ArtPro+ Plate Cut`, `ArtPro+ GMG OpenColor Connector` (lista continua abaixo da área visível — não transcrita integralmente nesta captura).
   - Botões: **`Continue`**, `Quit ArtPro+`.
   - Ação: clique em `Continue` (bounds 1232,720 75x24).
   - Resultado: diálogo fecha; janela principal `ArtPro+` (974x1039 em 953,0), **sem diálogo de HASP, sem erro, sem crash**. Captura `shot-01-license-dialog.png`.
3. Estado do app vazio: título `ArtPro+`; barra de menus literal **`File  Edit  Object  Select  Prepress  View  Window  Help`**. Captura `shot-02-app-open.png`.
4. Clique em `File` (961,31 34x21).
   - Resultado: popup 337x571 em (961,52) com os itens literais, na ordem:
     `New`, `New Report Template...`, `Open...`, `Open Recent`, `Close`, `Close All`, `Save`, `Save As...`, `Export To`, `Convert To PDF+`, `Convert To Report Template...`, `Convert To Variable Data Template...`, `Action Lists`, `Launch Workflow...`, `Insert Content From PDF...`, `Place File...`, `Place Image Inside...`, `Pages`, `Page Boxes Setup...`, `Document Setup...`, `Print...`, `Exit`.
   - Captura `shot-03-file-menu.png`.
5. Clique em `Open...` (964,99 330x22).
   - Resultado: abre diálogo **`Open File`** — **diálogo nativo do Windows** (661x481 em 961,31), com moldura de shell e árvore de pastas. Captura `shot-04-open-file-dialog.png`.
6. Preenchimento do campo `Name:` por teclado com caminho absoluto do PDF.
   - Resultado: caminho aceito e exibido truncado à esquerda: `...Desktop\ArtPlus\tools\reference_capture\F-005\input\test_vector.pdf`. Captura `shot-05-path-typed.png`.
7. `Enter` no campo `Name:` → **não abriu o documento**; o diálogo permaneceu aberto (neste diálogo nativo o Enter no campo de nome não aciona `Abrir`).
8. Clique em **`Abrir`** (1558,427) → documento aberto.
   - Resultado: diálogo fecha, **nenhum diálogo de importação/opções de PDF aparece**; o documento vai direto ao viewport.
   - Título da janela: **`test_vector.pdf @ 96,45% – ArtPro+`** (travessão U+2013 conforme a UI).
   - Captura `shot-06-document-open.png`.
9. Inspeção dos painéis (leitura por UIA + captura): ver seção "Saída observada".
10. `File > Pages` → submenu literal `Insert Blank Page...`, `Delete Pages...` — **não expõe contagem de páginas**.
11. `Window` → itens literais `Synchronize Views`, `My Workspace Activity`, `Arrange`, `test_vector.pdf` — nenhum painel de páginas.
12. Toggle do ribbon **`Object Browser`** (CheckBox, 963,55 93x50) → painel esquerdo abre com `4× <Path>` e `1× <Text Box>`; **zoom cai de 96,45% para 64,00%** (relayout). Captura `shot-07-after-object-browser.png`.
13. Encerramento: `Stop-Process -Name ArtPro+ -Force` → contagem final `ArtPro+ = 0`, `QtWebEngineProcess = 0`. Nenhum diálogo de gravação apareceu; **nada foi salvo**.

## Campos do diálogo `Open File`

| nome | tipo | default | unidade | faixa aceita |
|---|---|---|---|---|
| `Examinar:` | pasta de navegação (combo + árvore) | pasta da última abertura — nesta sessão `...\F-001\input` | — | qualquer pasta acessível |
| `Name:` | campo de texto editável | vazio (lista de arquivos abaixo) | — | nome de arquivo ou caminho absoluto |
| `Tipo:` | combo de filtro | `All supported documents (*.pdf; *.pdpdla; *.ap; *.art)` | — | filtro literal único observado (não enumerado: lista completa de filtros não aberta) |
| `Abrir` | botão (default) | — | — | — |
| `Cancelar` | botão | — | — | — |

Colunas da lista de arquivos: `Nome`, `Data de modificação`, `Tipo`. Para o PDF o valor de `Tipo` aparece truncado como `Documento do A...`.
Rótulos de shell em **pt-BR**: `Início`, `Área de Trabalho`, `Bibliotecas`, `Este Computador`, `Rede`; o título do diálogo permanece em inglês (`Open File`) e o filtro em inglês (`All supported documents`).

## Saída observada

| item | valor observado |
|---|---|
| Título da janela após abrir | `test_vector.pdf @ 96,45% – ArtPro+` |
| Overlay de caixa no canvas | `Media Box  210,00 x 297,00 mm` (vírgula decimal) |
| Painel `Document` | `Crosshair`, `Page Boxes` |
| Painel `Layers` | 1 camada: `Unlayered Art` (colunas `Name`, `Type`) |
| Painel `Marks` | vazio |
| Painel `Separations` | `ISO Coated v2 300% (ECI)`; `Cyan #1`, `Magenta #2`, `Yellow #3`, `Black #4`, `PANTONE 485 C #5` |
| Painel `Quality Control` | `Total Area Coverage`, `Limit: 270%` |
| Ribbon visível | `Object Browser  Colors  Images  Placed Art  Messages  Action Lists  Share & Approve  Clean  Select  Recolor  Sharper  Barcode  Screening  Trapping  Warp  3D` |
| Arquivo gravado | **nenhum** — nenhum `Save`/`Save As` foi acionado |
| Hash do input após a sessão | idêntico ao pré-abertura (`ADFD91B4…40D7`, 1868 bytes) |

## Contagem de páginas

**NÃO MEDIDA.** Nenhum dos caminhos testados expõe contagem de páginas:
- `File > Pages` só oferece `Insert Blank Page...` / `Delete Pages...`;
- `Window` só lista `Synchronize Views`, `My Workspace Activity`, `Arrange`, `test_vector.pdf`;
- `Object Browser` mostra objetos (`<Path>`, `<Text Box>`), não páginas.

O canvas mostra **uma** página com o overlay `Media Box 210,00 x 297,00 mm`, mas isso não é uma contagem medida por painel — registrado como não medido, sem inferência.

## Erros e limites

- **Nenhuma mensagem de erro** apareceu em todo o fluxo (licença, abertura, carregamento).
- **Nenhum diálogo de importação de PDF** foi exibido — a abertura é atômica do ponto de vista do usuário.
- `Enter` no campo `Name:` do diálogo nativo **não** confirma a abertura; é preciso clicar `Abrir`.
- Exceções da spec (arquivo inexistente, PDF corrompido, offset de falha, documento sem camadas) **não foram exercitadas** nesta captura — não medidas.

## Divergências spec × v24

1. **Caminho de UI (R1/UI):** a spec registra `Documents > Open Document`. Na v24 **não existe menu `Documents`**; o caminho real é **`File > Open...`**.
2. **Detecção de tipo (R1):** não há comandos separados para "proprietário" × "padrão aberto". Existe **um único `Open...`** cujo filtro nativo já enumera as extensões: `All supported documents (*.pdf; *.pdpdla; *.ap; *.art)`. A distinção observável é filtro/extensão no diálogo, não a ação de menu.
3. **Diálogo de importação (R3):** a spec sugere etapa de parsing perceptível ao usuário; na v24 **não há diálogo intermediário algum** — PDF abre direto no viewport.
4. **Localização do diálogo:** o `Open File` é **nativo e em pt-BR** (`Examinar:`, `Name:`, `Tipo:`, `Abrir`, `Cancelar`), com cabeçalho e filtro em inglês. A spec apenas diz "Standard Open File Dialog", sem rótulos literais.
5. **Relayout/zoom (não coberto por R1–R4):** abrir o ribbon `Object Browser` reduz o zoom de `96,45%` para `64,00%` sem ação de zoom do usuário — efeito relevante para regressão visual e para o clone (o viewport precisa reajustar ao abrir/fechar painéis).

## Capturas

Todas em `tools/reference_capture/F-005/shots/` (cópia em `rag/evidence/F-005/behavior/`):

| arquivo | o que mostra |
|---|---|
| `shot-01-license-dialog.png` | diálogo `ArtPro+ License Info` com `Continue` / `Quit ArtPro+` |
| `shot-02-app-open.png` | app aberto e vazio, menus `File Edit Object Select Prepress View Window Help` |
| `shot-03-file-menu.png` | popup do menu `File` com a lista literal de 22 itens |
| `shot-04-open-file-dialog.png` | diálogo nativo `Open File` com `Examinar:`, `Name:`, `Tipo:` e filtro literal |
| `shot-05-path-typed.png` | caminho absoluto digitado no campo `Name:` |
| `shot-06-document-open.png` | documento aberto, `Media Box 210,00 x 297,00 mm`, painéis Document/Layers/Marks/Separations/Quality Control |
| `shot-07-after-object-browser.png` | `Object Browser` aberto e zoom em `64,00%` (relayout) |

## Notas operacionais para a próxima captura

- `capture.ps1 -TitleMatch "Open File"` **falha** (`NO_WINDOW`): o diálogo nativo não é `MainWindowTitle` de processo próprio. Use captura por região: `-Region -X 950 -Y 20 -W 680 -H 500`.
- `pc-control.get_elements("Open File")` retorna `No elements found` — o diálogo comum do Windows não é exposto por esse caminho; use captura de tela + coordenadas para interagir.
- Após abrir o documento, o título muda para `<arquivo> @ <zoom> – ArtPro+`; `get_elements`/`click_element` devem usar o título completo (inclusive o travessão U+2013).
