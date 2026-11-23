# Conflitos de contrato

Registro de divergências entre especialistas. Formato: data, agentes, tema, decisão, quem cedeu.

## 2026-11-21 — ADR-004 (Selection Mark) vs implementação real

- **Divergiu**: `arquitetura` (ADR-004-selection-mark.md) vs `implementacao` (src/prepress/selection_mark.h/.cpp).
- **O quê**: ADR descrevia contrato com métodos `static` em `SelectionMarkManager` (`bool activateSelection(Object&)`, `void handleObjectInteraction(Object&, InteractionType)`, `void registerUndoAction(const SelectionMark&)`), classe `SelectionMark` com `enum State {Inactive, Active}` e métodos `activate()`, `updateHandles()`, `move()`, `remove()`, `getState()`. Implementação real usa **instância** `SelectionMarkManager` (singleton-style via `instance()`), métodos de instância `activateSelection(ObjectId)`, `moveSelection(QPointF)`, `resizeSelection(HandleId, QPointF)`, `rotateSelection(qreal)`, `deactivateSelection()`, sem `remove()`; `SelectionMark` é value object sem `State` enum; undo/redo via `SelectionMoveCommand`/`ResizeCommand`/`RotateCommand`/`ActivateCommand` (herdam de `SelectionCommandBase` com `captureBefore`/`captureAfter`). Persistência em `metadata.DocumentMarks.selectionMark` (mescla, writer único).
- **Decisão**: ADR atualizado para refletir a API real implementada. `resizeSelection` marcado como PLACEHOLDER (não computa transform) — a ser resolvido pelo `implementacao`.
- **Quem cedeu**: `arquitetura` (ADR reescrito para coincidir com implementação real). Divergência registrada aqui para rastreabilidade.

## 2026-11-21 — Versão de referência (v24 × v25)

- **Divergiu**: `AGENTS.md`, `docs/agents/AUTOPILOT.md`, `.opencode/agents/*`,
  `.opencode/skills/*`, `docs/features/*`, `scripts/*` usavam a v25
  (`bg_prog_artpro+_v250` = 25.03.116) como referência.
- **O quê**: a ordem executiva de reestruturação estabelece a v24.03.10017
  (`bg_prog_artpro+_v240`) como única referência válida.
- **Decisão**: v24.03.10017 é a referência canônica (`docs/agents/REFERENCE_VERSION.md`).
  Registros derivados da v25 ficam **históricos e fora do fluxo ativo**.
- **Quem cedeu**: as referências à v25 nos arquivos ativos (corrigidas/marcadas como históricas).
  Hashes e resultados históricos **não** foram alterados para simular v24.

## 2026-11-21 — F-004: a UI de "Selection Mark" não existe na v24

- **Divergiu**: `docs/features/F-004.md` e `docs/behavior/SelectionMark.md` (derivados da captura
  histórica da v25) **vs** o comportamento observado no ArtPro+ v24.03.10017
  (`CAP-20261121-02`) e a evidência estática do `PDFObjectActions.dll` v240.
- **O quê**: a spec descreve uma ferramenta "Selection Mark" com UI própria e atalho
  `Ctrl+Shift+S`. Na v24, `File`/`Object`/`Select`/`Prepress` e o ribbon **não têm** esse item;
  `Ctrl+Shift+S` é **`Save as...`**. O DLL só expõe operadores genéricos de seleção e
  transformação (`GOVSelect*`, `GOVChangeScaleSelection`, `GOVChangeRotateSelection`,
  `GOVChangeFlipSelection`, `GOVCloneSelection`).
- **Decisão (do orquestrador, sob autonomia)**: a spec passa a declarar a UI de §3 como
  **histórica e não reproduzível**; nenhuma ação fictícia será implementada. A evidência
  comportamental registra o resultado **negativo**, com os caminhos medidos e os não medidos
  (`View`/`Window`/`Edit`/`Help` e toolbar de contexto).
- **Pendente**: **reescopo da feature** (reduzir F-004 a "seleção e transformação", que é o que
  a v24 tem, ou encerrá-la como não-aplicável) — decisão de produto que o proprietário precisa
  confirmar. Até lá F-004 fica `testado` mas **não** é promovida a `auditado`.
- **Quem cedeu**: a descrição de UI derivada da v25 (marcada como histórica, não apagada).

## 2026-11-22 — Correção EXISTENCE-FIRST: F-004 reclassificado como fora-do-escopo-v24

- **Divergiu**: A classificação anterior de F-004 como `auditado` **vs** o princípio do
  contrato de existência primeiro.
- **O quê**: A auditoria original considerou F-004 como `auditado` com ressalvas HASP. Porém,
  a ressalva significava que **a paridade comportamental com a v24 é impossível de verificar**,
  pois a funcionalidade **não existe** na versão-alvo. Um laudo com ressalva desta natureza
  não pode ser classificado como "auditado" para um objetivo de clone da v24.
- **Decisão**: F-004 reclassificado de `auditado` para **`fora-do-escopo-v24`**:
  - A feature **não deve ser implementada** no ArtPlus v24 clone, pois a UI original não existe.
  - A implementação atual (`src/prepress/selection_mark.*`, `src/ui/main_window.cpp`) deve
    ser marcada como `TODO(remover)` ou reutilizada como base para uma feature genérica de
    seleção/transformação (não como Selection Mark específico).
  - F-004 **não entra** na contagem de features elegíveis para implementação.
- **Quem cedeu**: orquestrador, como aplicação do princípio de existência primeiro
  (AGENTS.md §11: "Estado real > estado desejado").

## 2026-11-21 — Permissão de edição de configuração (bootstrap)

- **Divergiu**: o frontmatter do `orquestrador` (`permission.edit/write: "*": deny`)
  impedia editar `AGENTS.md`, `opencode.jsonc` e `.opencode/**`.
- **O quê**: a reestruturação (FASE C/D/E) exige que o orquestrador edite esses arquivos.
- **Decisão**: o usuário autorizou a expansão da permissão (edição manual de
  `.opencode/agents/orquestrador.md` em 2026-11-21).
- **Quem cedeu**: o bloco de permissão restritivo (substituído por lista explícita de allow).
