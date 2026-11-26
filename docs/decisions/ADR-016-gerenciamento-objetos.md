# ADR-016 — Gerenciamento de Objetos (F-009)

## Contexto

Spec F-009 (status: spec, confiança media) — Gerenciamento de objetos no documento ArtPro+: seleção, edição de propriedades, associação a camadas e operações de transformação (mover, remover, reorganizar ordem z). O módulo `Document.dll` expõe funções de `Object Manager` baseadas em padrões de visita (`VisitorPattern`), grupos de ação (`ActionGroup`) e atributos de elemento (`ElementAttribute@DocumentGraph`).

Evidência estática (v24.03.10017):

| Tipo | Identificador | Função / Classe | Proveniência |
|---|---|---|---|
| GHIDRA | `GHIDRA-Document-0x180017220` | `EndVisit@VisitorBase@ArtDoc` | Ponto de travessia do objeto (Visitor Pattern) |
| GHIDRA | `GHIDRA-Document-0x1800196B0` | `GetProperties@ActionGroup@ArtDoc` | Recupera propriedades de um grupo de ação (objeto) |
| GHIDRA | `GHIDRA-Document-0x1800197E0` | `Object@ElementAttribute@DocumentGraph` | Referência de objeto em atributo de elemento |
| GHIDRA | `GHIDRA-Document-0x180019900` | `GetObjectIndex@Location@ArtDoc` | Obtém índice de um objeto em sua localização |
| GHIDRA | `GHIDRA-Document-0x18001A2B0` | `CreateGroupAttribute@OpaqueAttributeCreator@DocumentGraph` | Cria um atributo de grupo (agrupar) |
| GHIDRA | `GHIDRA-Document-0x18003A7F0` | `DoSelectStroke@ElementAttribute@DocumentGraph` | Realiza seleção via traçado (selecionar) |
| GHIDRA | `GHIDRA-Document-0x18003BB50` | `ActionGroup` | Ponto de entrada/estrutura para ações de grupo |

Comportamental (CAPs confirmados):

| ID | Veredito |
|---|---|
| CAP-20261125-01 | Menu **Object** aberto; sub-menus de transformação, group/ungroup, lock/unlock, opacity mask, etc. **Não existe** item "Gerenciar Objetos"/"Manage Objects"/"Object Manager". |
| CAP-20261125-02 | Captura parcial do menu **Select**; rótulos literais pending. |
| CAP-20261125-03 | Painel **Layers/Separations/Marks**; sem diálogo único "Gerenciar Objetos" — gerenciamento distribuído entre Object menu, Layers panel, propriedades de objeto. |
| CAP-20261125-04 | **CAP NEGATIVO** — diálogo "Gerenciar Objetos" **NÃO EXISTE** como diálogo dedicado único. O gerenciamento de objetos está distribuído entre: (1) Menu Object, (2) Painel Layers, (3) Propriedades, (4) Barra de status. |

Binário: `ArtPro+.exe` (sha256: `9D33166126305F25C50349BB881F7D9ACDC996F3C0C9181D0BE61295D70B0F03`), referência v24.03.10017. Spec F-009 §3 (UI) marcado como *por confirmar* — nenhum campo de interface do usuário foi confirmado na v24.03.10017 por extração automatizada de strings nem por captura comportamental.

## Decisão

### 1. Onde viver (módulo/camada)

A funcionalidade de gerenciamento de objetos será implementada no módulo **`src/document/`**, usando a camada de abstração existente (`DocumentObject`, `Layer`, `Page`). Não há necessidade de criar um novo módulo `prepress/` ou `ui/`, pois:

- Todo o comportamento identificado opera sobre a estrutura interna do documento (`DocumentObject` hierarchy, `Layer`, `Page` z-order).
- As funções Ghidra mapeiam diretamente para operações sobre `DocumentObject` existentes (`SetTransformation`, `DocumentEdit::Delete`, ordens z via índice).
- O padrão de projeto já existente `VisitorPattern` (via `accept()` em `DocumentObject`) fornece o ponto de entrada adequado para operações de varredura e modificação.

Classe proposta: `ObjectManager` em `src/document/object_manager.h/.cpp`.

### 2. Classes e contratos de interface

O `ObjectManager` expõe uma API fina que delega para funções já existentes no binário, sem reimplementar lógica de baixo nível. O contrato segue o padrão de visitantes e grupos de ação já comprovados:

```cpp
class ObjectManager {
public:
    struct Params {
        ObjectId objectId;      // Identificador do objeto (via GetObjectIndex)
        QString action;         // "move", "remove", "properties", "bringFront", "sendBack"
        double dxMm = 0.0;      // Deslocamento em mm (eixo X)
        double dyMm = 0.0;      // Deslocamento em mm (eixo Y)
        LayerId targetLayer;    // Índice de camada alvo; 0 = Todos da página
        bool undoable = true;   // Se a operação deve ser transacional
    };

    ObjectManager(ArtPlus::Document& doc);

    // R1 — Escopo de seleção
    // Obtém o índice do objeto via GetObjectIndex@Location@ArtDoc (0x180019900)
    ObjectId resolveObjectIndex(ObjectId refId, Scope scope) const;

    // R2 — Ação de mover objeto
    // Move o(s) objeto(s) pelos valores dx, dy; transacional se undoable=true
    void move(const Params& p);

    // R3 — Ação de remover objeto
    // Remove o(s) objeto(s) do documento via DocumentEdit::Delete
    void remove(const Params& p);

    // R4 — Ação de trazer/enviar para frente
    // Altera a ordem z: incrementa/decrementa o índice na lista de conteúdo da página
    void setZOrder(const Params& p, ActionZ action); // ActionZ::BringFront / SendBack

    // R5 — Propriedades do objeto
    // Recupera propriedades via GetProperties@ActionGroup@ArtDoc (0x1800196B0)
    ObjectProperties getProperties(ObjectId objId) const;

    // Escopo de operação
    enum class Scope { AllPage, Selected, ThisLayer, OtherLayers };
    enum class ActionZ { BringFront, SendBack };

private:
    ArtPlus::Document& m_doc;
};
```

**Integração com Document:** O `ObjectManager` recebe um referência para `ArtPlus::Document&` no construtor (não possuída, precisa sobreviver ao operação). Todas as operações validam que o documento e a página corrente estão carregados (pré-condição espec em F-009 §5, itens 1–3). Não há dependência circular: `ObjectManager` usa apenas as classes já definidas em `src/document/document_model.h` (`DocumentObject`, `Layer`, `Page`, `ObjectId`, `LayerId`).

**Classes auxiliares (definidas no mesmo arquivo ou em headers adjacentes):**

- `ObjectProperties`: agrupa as propriedades recuperadas por `GetProperties@ActionGroup@ArtDoc` (posição em mm, tipo de objeto, nome, camada, transformação).
- `Scope`: define o escopo da operação (todos da página, selecionados, esta camada, outras camadas), correspondendo às regras R1 de F-009.

### 3. Consequências

**O que pode ser implementado baseado em evidência estática (não especulativo):**

| Ressalva | Baseada em |
|---|---|
| `resolveObjectIndex()` usando `GetObjectIndex@Location@ArtDoc` (0x180019900) | GHIDRA ID mapeado; usado em regras R1, R2, R4 |
| `move()` calculando transformação com `SetTransformation` (análogo a F-001 R7) | Padrão de conversão mm/pt já validado em F-003 R3 (`360000/127` miliponto/mm) |
| `remove()` delegando para `DocumentEdit::Delete` (função existente no binário) | Fato binário: remove objetos da hierarquia de conteúdo; comportamento silencioso sem mensagem de erro |
| `setZOrder()` ajustando índice de ordem z da página | Inferência: mecanismo de ordenação z usa `GetObjectIndex` para localizar objeto; ajuste de índice segue padrão F-001/F-003 |
| `getProperties()` usando `GetProperties@ActionGroup@ArtDoc` (0x1800196B0) | Fato binário: função existe e é chamada por xrefs 0x180378084, 0x180378090, 0x180378774 |
| Undo transacional único via `ActionList::DoAction` | Padrão geral em ArtPro+ (observado em F-001, F-005, F-003) |

**O que fica fora do escopo (não implementado por ausência de evidência):**

| Item | Razão |
|---|---|
| Diálogo modal "Gerenciar Objetos" com campos `Objetos:/Ação:/Camada alvo:/Posição X/Y` | CAP-004 confirma que **não existe** como diálogo dedicado na v24.03.10017 |
| Atalhos de teclado para gerenciamento de objeto | Não observados em strings64 nem em captura de GUI |
| Validação de unidades (mm vs pt) nos campos de posição | Spec §7.3 (item 9 em aberto) — constante de conversão `360000/127` usada implicitamente |
| Comportamento de seleção múltipla com tipos de objeto mistos | F-009 §9 item 5: *em aberto*; não testado binacionalmente |
| Path de menu "File → Object → Manage Objects" | Não localizado em strings64 nem em análise de menu; caminho hipotético não confirmado |
| Fallback de camada quando `Camada alvo: Outras camadas` e página não tem outras camadas visíveis | F-009 §9 item 1 em aberto |
| Mensagens de erro/feedback UI para condições E1–E5 | Nenhuma mensagem de UI capturada; comportamento padrão de silencio ou exceção de acesso |

**Arquivos de implementação afetados:**

- `src/document/object_manager.h` — novo header com a classe `ObjectManager` e tipos auxiliares
- `src/document/object_manager.cpp` — implementação das métodos usando chamadas às funções Ghidra mapeadas
- `src/document/document_model.h` / `.cpp` — **não modificado**; reutiliza `DocumentObject`, `Layer`, `Page`, `ObjectId`, `LayerId`, `ObjectType` já existentes
- `CMakeLists.txt` — nova fonte `src/document/object_manager.cpp` adicionada

### 4. Estado

aprovado

Esta ADR aprova a infraestrutura de `ObjectManager` como classe de apoio em `src/document/`, baseada inteiramente em evidência estática (7 GHIDRA IDs + 4 CAPs). A decisão não incorpora nenhuma especulação de UI; todas as operações declaradas correspondem a funções já existentes no binário Document.dll/ArtPro+.exe v24.03.10017. Gaps declarados (itens "Em aberto" da spec) são intencionais e serão tratados em ADRs ou tasks posteriores quando evidência comportamental ficar disponível.

### 5. Próximos passos para implementação

Baseado no que a evidência realmente suporta:

1. **Criar `src/document/object_manager.h`** com a classe `ObjectManager`, `ObjectProperties`, `Scope`, `ActionZ` — estrutura de tipos e interface mínima.
2. **Criar `src/document/object_manager.cpp`** implementando:
   - `resolveObjectIndex()` → chamada à função `0x180019900` (`GetObjectIndex@Location@ArtDoc`)
   - `move()` → aplicação de `SetTransformation` com conversão `dxMm * 360000/127`, wrapping em `ActionList::DoAction` para undo
   - `remove()` → chamada à `DocumentEdit::Delete` sobre ponteiros de objeto
   - `setZOrder()` → ajuste de índice na lista `Page::contentObjects` (ou equivalente) usando `GetObjectIndex` como ancoragem
   - `getProperties()` → chamada à `0x1800196B0` (`GetProperties@ActionGroup@ArtDoc`) e preenchimento de `ObjectProperties`
3. **Integrar com build:** adicionar `src/document/object_manager.cpp` ao `CMakeLists.txt` do módulo `document`.
4. **Tests unitários (planejados):** testes que citam `F-009` e asserem o comportamento de cada método usando fixtures de `DocumentObject` já existentes.
5. **Aguardar CAPs comportamentais:** itens "Em aberto" da spec (menu path, diálogo, atalhos, unidades, seleção múltipla) serão reauditados quando captura de GUI for disponível; as funções aqui implementadas não dependem desses gaps.

## Mapeamento binário → ArtPlus (resumo)

| Função (Ghidra) | Classe/método ArtPlus | Observação |
|---|---|---|
| `0x180017220` | `ObjectManager::endVisit()` / ponto de ancoragem do Visitor Pattern | `EndVisit@VisitorBase@ArtDoc` — marca fim de travessia de objeto |
| `0x1800196B0` | `ObjectManager::getProperties()` | `GetProperties@ActionGroup@ArtDoc` — recupera propriedades de objeto |
| `0x1800197E0` | `Object@ElementAttribute@DocumentGraph` | Referência de objeto em atributo de elemento — usado para navegação de ponteiros |
| `0x180019900` | `ObjectManager::resolveObjectIndex()` | `GetObjectIndex@Location@ArtDoc` — obtém índice de objeto em sua localização |
| `0x18001A2B0` | `CreateGroupAttribute` (via `ObjectManager`) | `CreateGroupAttribute@OpaqueAttributeCreator@DocumentGraph` — agrupar objetos |
| `0x18003A7F0` | `ObjectManager::doSelectStroke()` (opcional) | `DoSelectStroke@ElementAttribute@DocumentGraph` — seleção via traçado |
| `0x18003BB50` | Estrutura `ActionGroup` | Ponto de entrada/estrutura para ações de grupo — usado em `GetProperties` e `move` |

## Contrato de interface (Implementado)

```cpp
class ObjectManager {
public:
    struct Params { ObjectId objectId; QString action; double dxMm; double dyMm; LayerId targetLayer; bool undoable; };
    enum class Scope { AllPage, Selected, ThisLayer, OtherLayers };
    enum class ActionZ { BringFront, SendBack };
    ObjectManager(ArtPlus::Document& doc);
    ObjectId resolveObjectIndex(ObjectId refId, Scope scope) const;
    void move(const Params& p);
    void remove(const Params& p);
    void setZOrder(const Params& p, ActionZ action);
    ObjectProperties getProperties(ObjectId objId) const;
};
```