# F-002 — Mark Set na UI do ArtPro+ v24.03.10017

- Captura: **CAP-20261121-03**
- Versão: **24.03.10017**
- Data da sessão: 2026-11-21 (sessão 2, retomada)
- Binário executado: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe`
- Entrada: `tools/reference_capture/F-002/input/test_vector.pdf`
  - `sha256` antes: `ADFD91B4E95BCE3708DB37055885C355880068EE53A1472AB1DC82E0820640D7` (1868 bytes)
  - `sha256` depois: `ADFD91B4E95BCE3708DB37055885C355880068EE53A1472AB1DC82E0820640D7` (inalterado)
- Estado inicial: `ArtPro+ = 0`, `QtWebEngineProcess = 0` (PID 12452 da sessão anterior encerrado com `Stop-Process -Force`)
- Estado final: `ArtPro+ = 0`, `QtWebEngineProcess = 0`; `tools/reference_capture/F-002/output/` com **0** arquivos; input inalterado

## Resultado em uma linha

**Positivo.** Na v24.03.10017 **existe Mark Set**, mas **não** como menu `Marks` na barra de menus nem
como rótulo no ribbon: o acesso é pelo **painel `Document` → seção `Marks` → botão de engrenagem (menu
de opções)** — itens literais **`Load Mark Set...`** e **`Save/Delete Mark Set...`**. O diálogo
`Save/Delete Mark Set` foi aberto e capturado.

> Isto **refuta** o registro `CAP-BLOCKED-20261121-01` ("Mark Set não localizada"). A funcionalidade
> existe; o que faltava era procurar no painel, não nos menus.

## Caminho na UI (medido)

```
painel lateral direito > Document > Marks > [botão de engrenagem ▾, x≈1899 y≈303]
   ├─ Load Mark Set...
   ├─ Save/Delete Mark Set...
   ├─ Update Marks
   ├─ Create Mark from Selection ▸
   ├─ Add Mark ▸
   ├─ Load Custom Variables Database...
   ├─ Delete Mark
   └─ Delete All Marks
```

E, no mesmo painel, o botão **`+ ▾`** (x≈1842 y≈303) lista os tipos de marca:

```
Add Repeat for Grid Mark
Add Cut Mark
Add Bearer Bar Mark
Add Dimensions Mark
Add External File Mark
Add Position Mark
Add Input File Mark
```

## Passos executados (literal)

1. `Get-Process ArtPro+,QtWebEngineProcess | Stop-Process -Force` → `PROC_COUNT=0`.
2. `Start-Process` do `ArtPro+.exe` v240 → `START=21044`; janela `ArtPro+` (953,0) 974x1039.
   - Em T+18 s e T+30 s a janela ainda era um **shell vazio** com a barra de menus (sem ribbon/painéis);
     `shot-04-relaunch.png`, `shot-05-relaunch-wait.png`.
   - **O diálogo `ArtPro+ License Info` não reapareceu nesta execução** — a UI abriu direto. Nenhum
     `Continue` foi necessário. Portanto o texto `suboptimal combination…` **não foi lido nesta sessão**
     (ver "Não medido").
3. Menu `File` clicado em (975,39): popup abre normalmente, prova de UI responsiva. Itens literais:
   `New  Ctrl+N`, `New Report Template...`, `Open...  Ctrl+O`, `Open Recent`, `Close  Ctrl+W`,
   `Close All  Ctrl+Alt+W`, `Save  Ctrl+S`, `Save As...  Ctrl+Shift+S`, `Export To`, `Convert To PDF+`,
   `Convert To Report Template...`, `Convert To Variable Data Template...`, `Action Lists`, `Launch Workflow...  Ctrl+L`,
   `Insert Content From PDF...`, `Place File...  Ctrl+Shift+P`, `Place Image Inside...  Ctrl+Alt+Shift+P`,
   `Pages`, `Page Boxes Setup...  Ctrl+Alt+P`, `Document Setup...`, `Print...  Ctrl+P`, `Exit  Ctrl+Q`.
   - **Nenhum item `Mark Set`/`Marks`.** `shot-06-file-probe.png`.
4. `File > Open...` (1018,109) → documento aberto. Título: **`test_vector.pdf @ 96,45% - ArtPro+`**.
   - Estado: `Media Box 210,00 x 297,00 mm`; `Layers` → `Unlayered Art`;
     `Separations` → `Document Profile: ISO Coated v2 300% (ECI)`, `Cyan #1`, `Magenta #2`,
     `Yellow #3`, `Black #4`, `PANTONE 485 C #5`; `Quality Control` → `Total Area Coverage`, `Limit: 270%`.
   - `shot-07-document-open.png`.
5. Barra de menus lida: **`File  Edit  Object  Select  Prepress  View  Window  Help`** — não existe
   menu `Marks`. Ribbon lido (16 rótulos): `Object Browser  Colors  Images  Placed Art  Messages
   Action Lists  Share & Approve  Clean  Select  Recolor  Shaper  Barcode  Screening  Trapping  Warp  3D`
   — não existe rótulo `Marks`/`Mark Set`.
6. Painel `Document` → seção **`Marks`** (cabeçalho em y≈267; barra de ferramentas em y≈292–314).
   UIA da janela (262 elementos) mostra **apenas** `ControlType.Text||Marks|1694,267` como texto;
   os botões da barra existem em (1664, 1687, 1710, 1795, 1829, 1863, 1886) **sem nome acessível**.
   - Hover de 1,4 s sobre cada botão **não exibiu tooltip** em nenhuma captura (`tt-1664.png` …
     `tt-1886.png`); a barra lida visualmente é: [3 ícones sem rótulo: carregar / abrir pasta / atualizar]
     [ícone de marca com `▾`] [`+` `▾`] [`−` `▾`] [engrenagem `▾`].
7. Clique no `▾` do botão de marca (1808,303) → **nenhum menu** observado (`menu-1808.png`).
8. Clique no `▾` do `+` (1842,303) → menu literal com 7 tipos de marca (lista acima). `menu-1842.png`.
9. Clique no `▾` do `−` (1876,303) → **nenhum menu** (lista de marcas vazia). `menu-1876.png`.
10. Clique no `▾` da engrenagem (1899,303) → menu literal com 8 itens (lista do caminho acima).
    `menu-1899.png`.
11. `Save/Delete Mark Set...` (1813,364) → diálogo **`Save/Delete Mark Set`** (240,283 490x437):
    - Texto literal: `You are currently managing the local Mark Sets.`
    - Tabela com cabeçalho **`Mark Sets`**, estado vazio **`The list is empty.`**, campo de busca com ícone de lupa.
    - Campo **`Name:`** vazio; botões **`Save`** e **`Cancel`**; botão **`−`** em (687,623).
    - Ação: `Cancel` (1619,700) → diálogo fecha. Nada foi gravado. `shot-08-save-delete-markset.png`.
12. Tentativa de `Load Mark Set...` (1813,341) após o `Cancel`: **nenhum diálogo apareceu** na captura
    seguinte (`shot-09-load-markset.png` mostra a UI normal). Item lido no menu, **diálogo não medido**.
13. Encerramento: `Get-Process ArtPro+,QtWebEngineProcess | Stop-Process -Force` →
    **`ArtPro=0 QtWeb=0`**. Nenhum diálogo de gravação; `output/` vazio; hash do input inalterado.

## Campos do diálogo observados

`Save/Delete Mark Set`

| nome | tipo | default | unidade | faixa aceita |
|---|---|---|---|---|
| `Mark Sets` | tabela (lista) | vazia → texto `The list is empty.` | — | — |
| campo de busca | edit + ícone lupa | vazio | — | não testado |
| `Name:` | edit | vazio | — | não testado |
| `Save` | botão | — | — | não acionado |
| `Cancel` | botão | — | — | acionado (fecha) |
| `−` | botão | — | — | não acionado |

## Saída observada

| item | valor |
|---|---|
| Funcionalidade Mark Set na UI | **existe**: `Marks > (engrenagem) > Load Mark Set... / Save/Delete Mark Set...` |
| Diálogo de gestão | `Save/Delete Mark Set` (texto e campos acima) |
| Tipos de marca disponíveis no `+` | `Add Repeat for Grid Mark`, `Add Cut Mark`, `Add Bearer Bar Mark`, `Add Dimensions Mark`, `Add External File Mark`, `Add Position Mark`, `Add Input File Mark` |
| Arquivo gravado | **nenhum** (`output/` vazio) |
| Processos ao final | `ArtPro+ = 0`, `QtWebEngineProcess = 0` |

## Indício de dependência de edição/licença

- **Nenhuma indicação observada nesta sessão.** O menu da engrenagem e o diálogo `Save/Delete Mark Set`
  apareceram sem aviso, cadeado ou marca de edição; os itens estavam habilitados para clique.
- O diálogo `ArtPro+ License Info` **não apareceu** nesta execução, então não há texto de licença novo
  para citar. **Não se conclui nada sobre licença** a partir desta sessão.

## Não medido (declarado, não inferido)

- **Texto do diálogo de licença** (`suboptimal combination…`) nesta sessão: o diálogo não apareceu.
  O texto existente em `docs/behavior/V24_RUNNABILITY_20261121.md` e em F-004 é de sessão anterior.
- **`Load Mark Set...`**: item existe no menu; o diálogo/resultado do clique **não foi capturado**.
- **Menus `Edit`, `Object`, `Select`, `Prepress`, `View`, `Window`, `Help`**: não abertos nesta sessão.
  A ausência de `Mark Set` neles **não** foi comprovada (F-004 mediu `File`, `Object`, `Select`,
  `Prepress` sem encontrar Marks; `Edit`/`View`/`Window`/`Help` seguem não medidos).
- **Menu de contexto** (clique direito no canvas e sobre objeto): não testado.
- **`Ctrl+I` (Inspector)**: não testado.
- **Tooltips** dos botões da barra `Marks`: não renderizaram em hover de 1,4 s; os botões não têm nome
  acessível na UIA. Os rótulos acima vêm dos **menus**, não de tooltips.
- **`Create Mark from Selection ▸`** e **`Add Mark ▸`**: submenus não abertos.
- **Efeito de `Update Marks`, `Delete Mark`, `Delete All Marks`**: não acionados.
- **Ícone `▾` em 1808** e **`−` em 1876**: clique sem menu observado; a função dos botões não foi provada.

## Divergências com a spec / registros anteriores

| # | registro dizia | v24 medido |
|---|---|---|
| 1 | `CAP-BLOCKED-20261121-01`: "Mark Set não localizada no v24.03.10017" | **refutado** — existe no painel `Document > Marks > engrenagem` |
| 2 | caminho `Marks` como menu | não existe menu `Marks`; existe **seção** `Marks` no painel `Document` |
| 3 | — | o painel tem botão `+` com 7 tipos de marca, inclusive `Add Cut Mark` e `Add Bearer Bar Mark` |

## Capturas

Em `tools/reference_capture/F-002/shots/` (cópia em `rag/evidence/F-002/behavior/`):

| arquivo | o que mostra |
|---|---|
| `shot-04-relaunch.png`, `shot-05-relaunch-wait.png` | janela `ArtPro+` em shell vazio (sem ribbon/painéis) |
| `shot-06-file-probe.png` | menu `File` literal, sem `Mark Set` |
| `shot-07-document-open.png` | `test_vector.pdf @ 96,45%`, painel `Document` com seção `Marks` |
| `menu-1808.png` | clique no `▾` do ícone de marca — sem menu |
| `menu-1842.png` | menu `+` com os 7 `Add … Mark` |
| `menu-1876.png` | clique no `▾` do `−` — sem menu |
| `menu-1899.png` | menu da engrenagem: `Load Mark Set...`, `Save/Delete Mark Set...`, etc. |
| `shot-08-save-delete-markset.png` | diálogo `Save/Delete Mark Set` |
| `shot-09-load-markset.png` | após tentativa de `Load Mark Set...` — sem diálogo |
| `tt-1664.png` … `tt-1886.png` | hovers de 1,4 s — nenhum tooltip |
| `uia-main.txt` | árvore UIA da janela com documento (única ocorrência de "Mark": cabeçalho da seção) |

## Erros e limites

- Nenhuma mensagem de erro do aplicativo em todo o fluxo.
- **`tools/reference_capture/F-004/ui.ps1` captura a janela errada** (outra aplicação em primeiro plano):
  `SetForegroundWindow` simples falha por foreground lock. A sessão usou
  `tools/reference_capture/F-002/ui2.ps1` (`AttachThreadInput` + `BringWindowToTop`, alvo por PID/título).
- `crop.ps1` (recorte/zoom) falha por conversão de argumentos no PowerShell 5.1; os recortes de tooltip
  foram feitos por captura de região (`ui2.ps1 -Action region`), não por crop de PNG.
- O app pode **relançar a si mesmo**: o PID devolvido por `Start-Process` não é garantia de ser o dono da
  janela; o alvo foi sempre resolvido por HWND/título.
