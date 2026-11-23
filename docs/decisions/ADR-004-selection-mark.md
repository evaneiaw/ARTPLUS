# ADR-004 — Selection Mark

## Contexto
Spec F-004; funções estáticas em `PDFObjectActions.dll` (`GOVSelectOverlappingObjects`, `GOVSelectOverlapping` — endereços Ghidra pendentes).
Evidência comportamental: `CAP-20261120-01` a `CAP-20261120-06` (criação, handles, arraste, status, delete, undo/redo).

## Decisão
Implementação de `SelectionMark` (value object) e `SelectionMarkManager` (instance, QObject) em `src/prepress/` para gerenciar o contexto de seleção dinâmico sobre objetos PDF existentes, sem diálogo modal, aderindo a R1, R2 e R3. Undo/redo via command pattern (`SelectionMoveCommand`, `SelectionResizeCommand`, `SelectionRotateCommand`, `SelectionActivateCommand`) integrados a `UndoStack`. Persistência em `metadata.DocumentMarks.selectionMark`.

## Mapeamento binário → ArtPlus
| Função (Ghidra/REA) | Classe/método ArtPlus | Observação |
|---|---|---|
| `GOVSelectOverlappingObjects` (pendente) | `SelectionMarkManager::activateSelection(ObjectId)` | Ativa o contexto de seleção sobre o objeto alvo. |
| `GOVSelectOverlapping` (pendente) | `SelectionMarkManager::rotateSelection(qreal)` / `resizeSelection(HandleId, QPointF)` | Atualiza handles e estado visual do objeto selecionado. |
| Funções de movimento/remoção (pendentes) | `SelectionMarkManager::moveSelection(QPointF)` / `deactivateSelection()` | Encapsulados no manager; commands gravam no `UndoStack`. |

## Contrato de interface

```cpp
namespace ArtPlus {

enum class HandleId {
    TopLeft = 0, Top = 1, TopRight = 2, Right = 3,
    BottomRight = 4, Bottom = 5, BottomLeft = 6, Left = 7,
    None = 255
};

// Value object que guarda o estado de uma seleção ativa
class SelectionMark {
public:
    explicit SelectionMark(ObjectId targetObjectId = 0);
    SelectionMark(const SelectionMark&) = default;
    SelectionMark& operator=(const SelectionMark&) = default;

    ObjectId targetObjectId() const;
    void setTargetObjectId(ObjectId);

    QRectF selectionBounds() const;
    void setSelectionBounds(const QRectF&);

    QVector<QPointF> handlePositions() const;
    void setHandlePositions(const QVector<QPointF>&);

    // Atualiza handles aplicando um transform (usado por move/rotate)
    void updateHandles(const QTransform& transform);

    // Recalcula bounds e handles a partir do objeto no documento
    void recomputeFromObject(const Document& doc);

    // Hit-test em handles (scene coords, tolerance em pontos)
    static HandleId hitTestHandle(const QVector<QPointF>& handles, const QPointF& scenePos, qreal tolerance = 6.0);

    // Persistence
    QJsonObject toMetadata() const;
    static std::optional<SelectionMark> fromMetadata(const QJsonObject& json, const Document& doc);

    QString displayName() const; // "Selection Mark"

private:
    ObjectId m_targetObjectId = 0;
    QRectF m_bounds;
    QVector<QPointF> m_handles; // 8 handles
};

// Manager singleton-style (owned by ArtPlusMainWindow), integra undo/redo e sinais
class SelectionMarkManager : public QObject {
    Q_OBJECT
public:
    explicit SelectionMarkManager(Document& document);

    static SelectionMarkManager* instance();

    void setUndoStack(UndoStack* stack);

    // Ativa seleção no objeto alvo (cria SelectionMark, mostra handles, push ActivateCommand)
    void activateSelection(ObjectId target);

    // Desativa seleção (remove handles, push ActivateCommand com captureSavedMark)
    void deactivateSelection();

    // Move o objeto selecionado por delta (document points), push MoveCommand
    void moveSelection(const QPointF& delta);

    // Resize via handle específico; pos é nova posição do handle (document points), push ResizeCommand
    void resizeSelection(HandleId handle, const QPointF& pos);

    // Rotaciona seleção ao redor do centro por ângulo (graus), push RotateCommand
    void rotateSelection(qreal angleDegrees);

    bool hasActiveSelection() const;
    const SelectionMark* activeSelection() const;
    SelectionMark* activeSelection();

    // Persistence: estado da SelectionMark em metadata.DocumentMarks
    bool loadFromMetadata();
    bool saveToMetadata() const;
    QJsonObject toMetadata() const;

signals:
    void selectionChanged();
    void selectionActivated();
    void selectionDeactivated();

private:
    friend class SelectionMoveCommand;
    friend class SelectionResizeCommand;
    friend class SelectionRotateCommand;
    friend class SelectionActivateCommand;

    // Called by undo commands after undo/redo para ressincronizar estado do manager
    void onSelectionRestored(ObjectId targetId, const QRectF& bounds, const QVector<QPointF>& handles, bool present);

    Document* m_document = nullptr;
    UndoStack* m_undoStack = nullptr;
    std::optional<SelectionMark> m_activeSelection;
    static SelectionMarkManager* s_instance;
};

// --- Undo Commands ---

// Base para commands que fazem snapshot do transform do objeto alvo
class SelectionCommandBase : public Command {
public:
    SelectionCommandBase(SelectionMarkManager* manager, ObjectId targetId);
    virtual ~SelectionCommandBase() = default;

    // Chamado pelo manager ANTES da operação
    void captureBefore(Document& doc);
    // Chamado pelo manager DEPOIS da operação
    void captureAfter(Document& doc);

protected:
    SelectionMarkManager* m_manager = nullptr;
    ObjectId m_targetId = 0;
    QTransform m_beforeTransform;
    QTransform m_afterTransform;
    bool m_hasBefore = false;
    bool m_hasAfter = false;

    void applyTransform(Document& doc, const QTransform& transform) const;
};

// Move selection (drag objeto)
class SelectionMoveCommand : public SelectionCommandBase {
public:
    SelectionMoveCommand(SelectionMarkManager* manager, ObjectId targetId, const QPointF& delta);
    QString description() const override { return QStringLiteral("Move Selection"); }
    void undo(Document& doc) const override;
    void redo(Document& doc) const override;
private:
    QPointF m_delta;
};

// Resize selection via handle (PLACEHOLDER: marca modified mas não aplica transform ainda)
class SelectionResizeCommand : public SelectionCommandBase {
public:
    SelectionResizeCommand(SelectionMarkManager* manager, ObjectId targetId, HandleId handle, const QPointF& newHandlePos);
    QString description() const override { return QStringLiteral("Resize Selection"); }
    void undo(Document& doc) const override;
    void redo(Document& doc) const override;
private:
    HandleId m_handle = HandleId::None;
    QPointF m_newHandlePos;
};

// Rotate selection
class SelectionRotateCommand : public SelectionCommandBase {
public:
    SelectionRotateCommand(SelectionMarkManager* manager, ObjectId targetId, qreal angleDegrees);
    QString description() const override { return QStringLiteral("Rotate Selection"); }
    void undo(Document& doc) const override;
    void redo(Document& doc) const override;
private:
    qreal m_angleDegrees = 0.0;
};

// Activate/deactivate selection (cria/remove SelectionMark do metadata do documento)
class SelectionActivateCommand : public Command {
public:
    SelectionActivateCommand(SelectionMarkManager* manager, ObjectId targetId, bool activate);
    QString description() const override;
    void undo(Document& doc) const override;
    void redo(Document& doc) const override;

    // Captura estado da SelectionMark antes da desativação para undo
    void captureSavedMark(const SelectionMark& mark);

private:
    SelectionMarkManager* m_manager = nullptr;
    ObjectId m_targetId = 0;
    bool m_activate = false;
    SelectionMark m_savedMark;
    bool m_hasSavedMark = false;
};

} // namespace ArtPlus
```

## Fluxo de operações

1. **Ativação**: `activateSelection(targetId)` → valida `isSelectable` (camada visível/desbloqueada, não mask) → cria `SelectionMark` com bounds/handles do objeto → `push SelectionActivateCommand(true)` → `m_activeSelection = mark` → emite `selectionActivated`/`selectionChanged`.
2. **Movimento**: `moveSelection(delta)` → `captureBefore` → aplica `translate` no transform do objeto → `captureAfter` → `push MoveCommand` → `recomputeFromObject` → `setModified` → emite `selectionChanged`.
3. **Rotação**: `rotateSelection(angle)` → `captureBefore` → rotaciona ao redor do centro da seleção → `captureAfter` → `push RotateCommand` → `recomputeFromObject` → `setModified` → emite `selectionChanged`.
4. **Resize**: `resizeSelection(handle, pos)` → `captureBefore` → **PLACEHOLDER** (marca `setModified` mas não aplica transform) → `captureAfter` → `push ResizeCommand` → emite `selectionChanged`.
5. **Desativação**: `deactivateSelection()` → `push SelectionActivateCommand(false)` com `captureSavedMark(*m_activeSelection)` → `m_activeSelection.reset()` → emite `selectionDeactivated`/`selectionChanged`.
6. **Undo/Redo**: commands restauram `m_beforeTransform`/`m_afterTransform` no objeto e chamam `manager->onSelectionRestored(...)` para ressincronizar `m_activeSelection` e emitir sinais.

## Persistência (metadata)

```
metadata.DocumentMarks
  .version: int (atual 1)
  .selectionMark:
      .targetObjectId: int
      .kind: "SelectionMark"
      .bounds: [left, top, right, bottom] (document points)
      .handles: [[x,y], ...] (8 posições, document points)
```

`loadFromMetadata()` lê `DocumentMarks.selectionMark`, valida `isSelectable` no documento atual, faz `recomputeFromObject` para sincronizar com transform atual do objeto, seta `m_activeSelection` e emite sinais.

## Alternativas descartadas

1. **Diálogo Modal**: Descartado por violar R1 (seleção direta, sem diálogo modal).
2. **Marca Persistente como objeto de conteúdo**: Descartado, pois a Selection Mark opera sobre o **contexto de seleção** do objeto existente, não como um objeto de conteúdo novo.
3. **Métodos static no Manager**: A versão inicial da ADR previa `static` methods; a implementação real usa instância singleton-style para ter acesso a `Document&`, `UndoStack*`, sinais Qt e estado `m_activeSelection`.
4. **State enum no SelectionMark**: A implementação real não usa `enum State { Inactive, Active }`; o estado "ativo/inativo" é representado pela presença/ausência de valor em `std::optional<SelectionMark> m_activeSelection` no manager.

## Consequências

* **Afetados:** `src/prepress/selection_mark.h`, `src/prepress/selection_mark.cpp`, `src/ui/main_window.cpp` (handler `addSelectionMark`, atalho `Ctrl+Shift+S`, toolbar), `src/document/undo.h` (Command/UndoStack).
* **Risco:** Baixo. A v1 já está implementada e compilando. Resize é placeholder (não aplica transform) — precisa completar em iteração futura.
* **Migração de dados:** Nenhuma. A marca opera sobre estado do objeto no `Document`; persiste via metadata `.artplus`.

## Estado
implementado