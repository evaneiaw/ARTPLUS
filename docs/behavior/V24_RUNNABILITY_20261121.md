# V24 — Viabilidade de execução e captura comportamental (2026-11-21)

- Versão de referência: **24.03.10017**
- Máquina: sessão de console `Evanei` (Session 4, Console, Ativa), 1920x1080, 1 monitor
- Binário: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe`
- `FileVersion` lido do binário: `24.03.10017`
- `sha256` do `.exe`: `9d33166126305f25c50349bb881f7d9acdc996f3c0c9181d0be61295d70b0f03`
- `Size`: 31.276.976 bytes
- Veredito: **(a) ABRE — interface utilizável**. Nenhum bloqueio de licença/HASP.
- Capturas: `tools/reference_capture/v24_probe/` e `rag/evidence/v24_probe/behavior/`
  - `shot-01-license-dialog.png` — tela inteira no T+6 s (janela do app atrás do editor)
  - `shot-02-license-dialog.png` — tela inteira com o ArtPro+ em primeiro plano, documento aberto
  - `shot-03-file-menu.png` — tela inteira após clique no menu `File`
  - `license-dialog-uia.txt` — strings literais do diálogo de licença lidas por UIA

## A1 — Execução

```
Start-Process -FilePath 'C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe' `
              -WorkingDirectory 'C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows' -PassThru
```

PID retornado pelo `Start-Process`: **2820** (2026-11-21T18:31:05).

Existem 3 `.exe` no diretório: `ArtPro+.exe` (31 MB, principal), `PreflightProfileEditor.exe`
(116 KB), `QtWebEngineProcess.exe` (644 KB, auxiliar do Qt). Só o principal foi iniciado.

## A2 — Estado observado (até 20 s)

| Item | Valor observado |
|---|---|
| Agendamento | janela presente em **T+6 s** |
| `HasExited` | **False** (permaneceu em execução) |
| `ExitCode` | não aplicável — processo não saiu |
| `Responding` | **True** |
| `MainWindowHandle` (PID 2820) | `4850812` (0x4A0A3C) no primeiro instante → `8324976` (0x7F0770) depois |
| `MainWindowTitle` | `ArtPro+` → depois **`ArtPro+ License Info`** → depois **`Untitled @ 96,45% - ArtPro+`** |

Tela exibida ao usuário (o que a janela **mostra**):

1. **Splash / janela principal** com título `ArtPro+` (sem documento).
2. **Diálogo modal `ArtPro+ License Info`** (754x548 px, em 573,216) — aviso de licença,
   não erro. Conteúdo literal (lido por UIA, arquivo `license-dialog-uia.txt`):

   > “A suboptimal combination of ArtPro+ Edition licenses has been selected.
   >
   > An ArtPro+ Essentials license offers all of the features of an ArtPro+ Digital license and
   > more. This means you can deselect ArtPro+ Digital from the list below to release the license
   > and make it available for use on another computer, without losing any features here.”

   Campos/colunas do diálogo: `License Server: localhost` · link `(Change)` ·
   cabeçalhos `Edition License | Status | Type | Remaining Days`.

   Edições listadas (todas com Status `network` e Remaining Days `Unlimited`):
   `ArtPro+ Essentials 24`, `ArtPro+ Layout 24`, `ArtPro+ Digital 24`;
   em *Additional Licenses*: `ArtPro+ Advanced 24`, `ArtPro+ Plate Cut` (sem status),
   `ArtPro+ GMG OpenColor Connector`, `ArtPro+ Equinox`, `ArtPro+ Variable Data Expansion`,
   `Studio Designer 20`, `Studio Toolkit for Labels 20`, `Studio Toolkit for Shrink Sleeves 20`.

   Botões: **`Continue`** e **`Quit ArtPro+`**.

3. Após a fase de licença, a **UI principal** ficou utilizável (shot-02), com:
   - barra de título `Untitled @ 96,45% - ArtPro+`
   - menus: `File  Edit  Object  Select  Prepress  View  Window  Help`
   - ribbon: `Object Browser  Colors  Images  Placed Art  Messages  Action Lists  Share & Approve
     Clean  Select  Recolor  Sharper  Barcode  Screening  Trapping  Warp  3D`
   - painéis à direita: `Document` (Page Boxes, Layers, Marks, Separations, Quality Control),
     `Document Profile: ISO Coated v2 300% (ECI)`
   - página branca vazia, zoom `96,45%`

**Não** houve diálogo de HASP, nem mensagem de DLL ausente, nem crash, nem saída com erro.
Nenhum serviço HASP está instalado nesta máquina (`Get-Service HASP*` → vazio); a licença é
**flutuante por rede** em `localhost`.

## A3 — Veredito

**(a) ABRE interface utilizável.** O diálogo `ArtPro+ License Info` é apenas um **aviso**
(combinação subótima de edições) com botão `Continue`; não exige credencial, dongle,
ativação nem inserção de chave. Licenças reportadas como `network` / `Unlimited`.

## A4 — Operação mínima não destrutiva

- Clique em `File` (menu bar, coordenadas de tela 974,37) executado com `pc-control.mouse_click`.
- Resultado imediato: surgiu uma **segunda janela pertencente ao `ArtPro+.exe`**
  (710x354 px em 605,363) — o popup do menu — enquanto a janela principal manteve
  geometria (953,0 974x1039) e título `Untitled @ 96,45% - ArtPro+`. Captura: `shot-03-file-menu.png`.
- Nenhum arquivo foi aberto, salvo ou alterado; `ESC` enviado em seguida para fechar o popup.
- **Limite desta evidência**: a lista de itens do menu `File` não foi transcrita (sem OCR
  dentro do orçamento de passos desta sessão). Para `CAP-*` de menu é preciso uma captura
  dedicada com leitura da árvore UIA do popup.

## A5 — Encerramento

- `CloseMainWindow()` no PID 2820 → o processo 2820 saiu de forma graciosa.
- **Atenção operacional**: o ArtPro+ **relança a si mesmo** — a UI real (título
  `Untitled @ 96,45% - ArtPro+`) pertencia a outro PID (**14148**), não ao PID devolvido por
  `Start-Process`. Isso explica `EnumWindows`/`FindWindow` por PID 2820 não encontrarem janela.
- O PID 14148 foi encerrado com `Stop-Process -Force`; verificação final:
  `final ArtPro count = 0`; nenhum `QtWebEngineProcess` remanescente.

## Consequência para o pipeline

1. **F-002 / F-004 / F-005 NÃO estão bloqueadas por licença/HASP.** O caminho é **capturar
   comportamento no v24.03.10017**, não declarar bloqueio. O registro anterior
   (“HASP v240 impede execução comportamental no ArtPro+ v24.03.10017”, em
   `rag/evidence/F-004/manifest.json`) está **refutado por observação direta** nesta sessão.
2. **As capturas existentes de F-001/F-003 são da v25 histórica e não servem** como evidência
   da versão-alvo. Precisam ser refeitas no v24 com identificador próprio.
3. **Ordem recomendada**: capturar cedo as features que dependem de licença flutuante —
   a licença é *network/Unlimited* em `localhost`, mas janela de lease pode expirar e a
   combinação de edições pode mudar sem aviso.
4. **Receita operacional para o agente `comportamento`** (obtida nesta sessão):
   - iniciar com `Start-Process` e **não** confiar no PID devolvido: localizar a janela por
     título (`MainWindowTitle` contendo `ArtPro+`) e usar `Get-Process | ? ProcessName -like '*ArtPro*'`;
   - na primeira execução aparece o diálogo `ArtPro+ License Info`; clicar `Continue`;
   - se a UI ficar atrás de outra janela, `SetForegroundWindow` direto **falha** (foreground lock);
     funciona com `AttachThreadInput` ao thread da janela em foreground **e** ao do alvo
     (`GetCurrentThreadId` vem de `kernel32.dll`, não de `user32.dll`);
   - `pc-control.get_elements`/`click_element` com `window_title: "ArtPro+"` falha depois que o
     título vira `Untitled @ ... - ArtPro+`; usar coordenadas da captura ou o título completo;
   - ao encerrar, matar **todos** os PIDs `ArtPro+`, incluindo o relançado.

## Proposição para `docs/agents/BLOQUEIOS.md` (não editado — dono é o orquestrador)

**Não propor bloqueio de F-002/F-004/F-005.** Texto sugerido para registrar a correção:

```
| F-002 / F-004 / F-005 | NÃO BLOQUEADO (correção) | Evidência anterior "HASP v240 impede execução
comportamental" refutada em 2026-11-21: o ArtPro+.exe 24.03.10017 (sha256 9d33166126305f25c50349bb881f7d9acdc996f3c0c9181d0be61295d70b0f03)
abre UI utilizável; apenas diálogo informativo "ArtPro+ License Info" (Continue). Evidência:
docs/behavior/V24_RUNNABILITY_20261121.md, rag/evidence/v24_probe/behavior/shot-0{1,2,3}*.png.
Condição: recalcular CAP-* das três features contra a v24; CAPs da v25 não valem. |
```

Se ainda assim o orquestrador optar por bloquear por outro motivo, o motivo **não** pode ser
licença/HASP — precisa ser um bloqueio novo e observado.

## Situação do gate (informativa)

`python scripts/gate.py --all` → **exit code 1**, saída final:

```
[GATE 3 evidência] REPROVADO  - manifest.json ausente
[GATE 2 spec] ok
[GATE 2 arquitetura] ok
[GATE 4 código] REPROVADO - spec não declara arquivos de implementação em src/
[GATE 5 testes] REPROVADO - nenhum teste cita F-008
[GATE 6 auditoria] REPROVADO - laudo de auditoria ausente (F-008-audit*.md)

HALT ATIVO: avanço de funcionalidade bloqueado.
```

Essas reprovações são de **F-008** e não deste probe (que não é feature). O texto
`HALT ATIVO` aparece na saída do gate e deve ser lido pelo orquestrador contra
`docs/agents/HALT.md` antes de avançar qualquer feature.
