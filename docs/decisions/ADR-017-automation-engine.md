---
id: ADR-017
feature: F-011
titulo: Integração com Automation Engine / DataCenter
Estado: aprovado
data: 2026-11-26
versao_ref: 24.03.10017
autor: arquitetura
---

# ADR-017 — Integração com Automation Engine / DataCenter (F-011)

## Contexto

Spec `F-011` (status `spec`, confiança `media`, versao_ref `24.03.10017`) descreve o módulo
`DocumentAutomationEngine.dll` como adaptador de integração entre o ArtPro+ e o servidor Esko
Automation Engine / DataCenter. Ele expõe funções de conexão, autenticação, sincronização de
recursos, mapeamento URI↔path, Smart Names (Job, Product, ProductPart, Workflow, Barcode), e
métodos de impressão/cor/DotGain.

A interface do usuário é exposta principalmente através da aba `Automation Engine` e da aba
`Printing Methods` no diálogo `Edit > Options...`, além de itens de menu `File > Launch Workflow...`
e `Window > My Workspace Activity`. **Não implementa Action Lists** (escopo de
`NDLModelActionList.dll`).

Evidência estática (v24.03.10017):
- 73 exports no `DocumentAutomationEngine.dll` focados em Connect/Disconnect/Auth, SyncResources,
  SyncURIFromServer, Smart Names, Printing Methods, DotGain, CMS flags, URI↔Path mapping.
- RTTI: `AutomationEngineModule`, `ServerCategory`, `JobCategory`, `ProductCategory`, `ProductPartCategory`,
  `WorkflowCategory`, `JobBarcodesCategory`, `ConnectionProxy`, `AESyncer`, `SmartNameUtils`,
  `AT_TTicket`, `BGM_TAuthenticator`, `BGM_TClient`.
- Strings de preferência: `documentautomationengine.barcodeproperties`,
  `documentautomationengine.connectionproxy`, `documentautomationengine.connection.alwayspublic`,
  `documentautomationengine.enableMyWorkspace`.
- Strings de serviços: `BG_SERVER`, `ServerTreeName`, `Containerserver`, `ElemServer`,
  `FileServer`, `TicketServer`, `TaskManager`, `LogonServer`, `ScreenServer`, `DGCServer`.
- Comportamental `CAP-20261126-01`: aba Automation Engine (Server field + dropdown "No Connection"/
  "Automation Engine Server"), aba Printing Methods (9 métodos padrão), menus
  `File > Launch Workflow...`, `Window > My Workspace Activity`, `Help > Not Signed In`.

Evidência comportamental `CAP-20261126-01` confirma a UI observada, mas o estado "Not connected to
any server" é o padrão ao iniciar o ArtPro+; o comportamento ao conectar-se a um servidor real não foi
capturado.

## Decisão

### 1. Onde viver (módulo/camada)

A funcionalidade de integração com Automation Engine / DataCenter será implementada no módulo
**`src/prepress/automation_engine.h/.cpp`**, integrado à camada `prepress` existente.

**Justificativa:**

- O módulo `DocumentAutomationEngine.dll` fornece funcionalidades de backend que são
  **relevantes para fluxos de trabalho de prepress**: sincronização de recursos do servidor,
  Smart Names (variáveis de Job/Product/Workflow) usadas em layouts de impressão, métodos de
  impressão e curvas de ganho de ponto para calibração. Isso é análogo ao porquê de `Trapping`
  ter sido colocado em `src/prepress/` (`ADR-015`): a camada `prepress` lida com a integração
  de servidores e variáveis de impressão.

- **Classes e responsabilidades propostas** (novos arquivos, não reescrita existente):

  - `src/prepress/automation_engine.h` — header com a classe `AutomationEngineAdapter` e tipos
    auxiliares.
  - `src/prepress/automation_engine.cpp` — implementação usando as funções Ghidra mapeadas.

- **Alternativa considerada:** `src/document/`. A integração com Automation Engine opera em nível
  de documento/metadados, mas o modelo `Document` já tem responsabilidades próprias (undo, seleção,
  camadas). Colocá-lo em `src/prepress/` evita acoplamento circular com a estrutura interna do
  documento e segue o padrão `TrappingManager` em `src/prepress/trapping_flag.h/.cpp`
  (`ADR-015`).

- **O que fica fora do escopo desta ADR:**
  - Action Lists (`NDLModelActionList.dll`) — escopo separado, fora do `F-011`.
  - Servidor Automation Engine real — o código implementa o modelo de conexão **desconectado**
    e o estado UI "Not connected", mas não implementa comunicação de rede com um servidor
    efetivo (esse dependeria de bibliotecas externas `aeserver_c.dll`, `BGMWare.dll`, etc., e
    de captura comportamental com conexão ativa).
  - Diálogos UI completos para campos de login, URL, porta, proxy quando conectado — esses
    dependem de nova captura GUI (items "Em aberto" da spec E2, E9).

### 2. Classes e contratos de interface

A classe central é `AutomationEngineAdapter`, que fornece uma API fina que delega para as
funções exportadas do `DocumentAutomationEngine.dll`, sem reimplementar lógica de baixo nível.

```cpp
class AutomationEngineAdapter {
public:
    struct ParamsConnect {
        QString serverUri;       // URI do servidor (ex.: "https://ae-server:8080")
        QString username;        // usuário opcional
        QString password;        // senha opcional
        bool useTunneling;       // usa AAProxy/tunneling
    };

    struct ConnectionProperties {
        bool connected = false;
        QString serverName;
        optional<ServerVersion> version;
        vector<AuthenticationMethodProperties> authMethods;
    };

    struct AuthenticationMethodProperties {
        QString name;          // ex.: "Default", "AAProxy", "Tunneling"
        bool available = false;
    };

    struct SyncResourcesParams {
        QString pathOrUri;     // path local ou URI do servidor
        SyncDirection direction; // SyncDirection::Upload ou SyncDirection::Download
    };

    struct PrintingMethod {
        QString name;          // ex.: "Offset", "Gravure", "Flexo", "InkJet", etc.
        bool custom = false;   // true se método customizado (adicionado via servidor)
    };

    struct SmartNameValue {
        QString name;          // ex.: "Job_Name", "Product_Part_Name", "Workflow_Name", "Barcode_Type"
        QString value;         // valor resolvido do Smart Name
    };

    // Construtor: recebe referência ao Document (não possuída, deve sobreviver à operação).
    explicit AutomationEngineAdapter(Document& doc);

    // Conexão e desconexão
    ConnectionProperties connect(const ParamsConnect& params);
    void disconnect();

    // Autenticação
    vector<AuthenticationMethodProperties> getAuthenticationMethods();

    // Sincronização de recursos
    optional<bool> syncResources(const SyncResourcesParams& params);

    // Mapeamento URI ↔ Path
    optional<QString> mapPathToDataCenterUri(const QString& localPath);
    optional<QString> mapDataCenterUriToPath(const QString& uri, bool = false); // fallback flag

    // Smart Names / Workflow
    vector<SmartNameValue> getSmartNames(const vector<QString>& categories); // Job, Product, ProductPart, Workflow, Barcode

    // Métodos de impressão
    vector<PrintingMethod> getPrintingMethods();
    bool addPrintingMethod(const QString& name);
    bool removePrintingMethod(const QString& name);
    void refreshPrintingMethods();

    // Curvas e formas de ponto
    vector<string> getDotGainCurves();
    vector<DotShape> getDotShapes(); // DotShape = {name, angle, shapeType}

    // Estado de recursos e links
    optional<bool> isResourceUpToDate(const QString& resourcePath);

    // My Workspace
    optional<pair<QString, QString>> getMyWorkspaceSettings(); // (uri, name)

    // Callback de perda de conexão
    using ConnectionLostCallback = function<void()>;
    void setCallbackOnConnectionLost(ConnectionLostCallback cb);

    // Override de informações de arquivo (Job/Product/Part)
    optional<JobInfo> getJobInfo(const QString& path);
    optional<ProductInfo> getProductInfo(const QString& path);
    optional<BarcodeProperties> getJobBarcodeProperties(const QString& path);

private:
    Document& m_doc;
};
```

**Tipos auxiliares definidos no mesmo header:**

- `enum class SyncDirection { Upload, Download }`
- `enum class ServerVersion { Major, Minor }` (ou `pair<int,int>`)
- `struct DotShape { QString name; double angle; int shapeType; }` (shapeType: round, square, etc.)

**Integração com Document:** `AutomationEngineAdapter` recebe um referência para
`ArtPlus::Document&` no construtor (não possuída, precisa sobreviver ao operação). Todas as
operações validam que o documento e a página corrente estão carregados (pré-condição espec em
F-011 §3, itens 1–3). Não há dependência circular: `AutomationEngineAdapter` usa apenas as
classes já definidas em `src/document/document_model.h` (`Document`, `Layer`, `Page`, `ObjectId`,
etc.) e tipos Qt (`QString`, `QVariant`, `QSizeF`).

### 3. Consequências

**O que pode ser implementado baseado em evidência estática (não especulativo):**

| Funcionalidade | Baseada em |
|---|---|
| `connect()` preenchendo `ConnectionProperties` com valores do proxy | `GHIDRA-DocumentAutomationEngine-0x180014310` (R1) |
| `disconnect()` reiniciando `BGM_TAuthenticator` e devolvendo estado "Not connected" | `GHIDRA-DocumentAutomationEngine-0x1800143f0` (R2) |
| `getAuthenticationMethods()` retornando métodos suportados (Default, AAProxy, etc.) | `GHIDRA-DocumentAutomationEngine-0x180014400` (R3) |
| `syncResources()` com direção Upload/Download | `GHIDRA-DocumentAutomationEngine-0x180065b30` (R6) |
| `mapPathToDataCenterURI()` / `mapDataCenterURIToPath()` conversão URI↔path | `GHIDRA-DocumentAutomationEngine-0x1800546f0`, `0x1800542b0` (R7) |
| `getPrintingMethods()` retornando os 9 métodos padrões: Offset, Gravure, Flexo, Letterpress, ScreenPrinting, InkJet, Toner, Thermal, ElectroInk | `GHIDRA-DocumentAutomationEngine-0x1800618d0` (R10) |
| `getDotGainCurves()` e `getDotShapes()` | `GHIDRA-DocumentAutomationEngine-0x180065b90`, `0x180065be0` (R11) |
| `isResourceUpToDate()` verificando se recurso foi alterado no servidor | `GHIDRA-DocumentAutomationEngine-0x180065a40` (R12) |
| `getMyWorkspaceSettings()` retornando URI e nome do workspace | `GHIDRA-DocumentAutomationEngine-0x180014420` (R4) |
| `getServerVersion()` retornando versão major/minor | `GHIDRA-DocumentAutomationEngine-0x180014460` (R5) |
| `setCallbackOnConnectionLost()` registrando callback | `GHIDRA-DocumentAutomationEngine-0x1800144a0` (R14) |
| `AESyncDirectory()` retornando caminho do diretório sincronizado | `GHIDRA-DocumentAutomationEngine-0x180053f00` (R15) |
| `getJobBarcodeProperties()` retornando propriedades de código de barras | `GHIDRA-DocumentAutomationEngine-0x180012c80` (R9) |
| `addPrintingMethod()` / `removePrintingMethod()` / `refreshPrintingMethods()` | `GHIDRA-DocumentAutomationEngine-0x1800618a0`, `0x180061940`, `0x180061920` (R10) |

**O que fica fora do escopo (não implementado por ausência de evidência):**

| Item | Razão |
|---|---|
| Comportamento da aba `Automation Engine` quando a opção `Automation Engine Server` é selecionada (campos de login, URL, porta, proxy) | *E1 item 1 em aberto*: não foi capturado com conexão ativa (necessário novo comportamento GUI). |
| Campos de autenticação (usuário, senha, porta, proxy) quando conectado | *E2 item 2 em aberto*: UI mostra apenas `Server:` e lista quando desconectado; campos aparecem apenas quando conectado (não observado). |
| `File > Launch Workflow...` — comportamento ao clicar | *E3 em aberto*: nenhum diálogo confirmado pela UIA; pode estar desabilitado ou silencioso. |
| `Window > My Workspace Activity` — efeito visual | *E4 em aberto*: toggle pode não abrir janela detectada pela UIA. |
| Inserção de Smart Names na UI/documento | *E5 em aberto*: funções retornam dados, mas não foi observado onde são inseridas na UI. |
| Botões de add/remove de métodos de impressão na aba Printing Methods | *E6 em aberto*: UI mostra 9 métodos padrão + texto informativo; controles de add/remover não observados sem conexão ativa. |
| Curvas e formas de ponto na UI | *E7 em aberto*: dados retornados, mas não observado campo/diálogo UI onde serem selecionados/ aplicados. |
| Flags CMS (CanUserChangeCMSDatabaseFlag, IsCMSDatabaseBeingEdited, Set/RemoveCMSDatabaseFlag) | *E8 em aberto*: funções existem no backend, mas não foi encontrada UI que as exponha. |
| OverrideInputFileInfo/PathInfo/ProductInfo | *E9 em aberto*: funções existem, mas não há UI associada. |
| CancelAllSyncing e TouchServer | *E10 em aberto*: funções sem observação de UI; operam em segundo plano. |
| Mensagens de erro de conexão ao usuário | *E11 em aberto*: erro reportado via `ErrorReporter` do documento; texto exibido não capturado. |

**Arquivos de implementação afetados:**

- `src/prepress/automation_engine.h` — novo header com a classe `AutomationEngineAdapter` e tipos auxiliares
- `src/prepress/automation_engine.cpp` — implementação dos métodos usando chamadas às funções Ghidra mapeadas
- `src/prepress/CMakeLists.txt` — nova fonte `src/prepress/automation_engine.cpp` adicionada
- `src/document/document_model.h` / `.cpp` — **não modificado**; reutiliza `Document`, `Layer`, `Page`, tipos já existentes
- `src/ui/` — **não modificado** por esta ADR; eventuais alterações UI (checkboxes, diálogos) dependem de novas capturas comportamentais e ADRs futuras

## Estado

aprovado

Esta ADR aprova a infraestrutura de `AutomationEngineAdapter` como classe de apoio em `src/prepress/`,
baseada inteiramente em evidência estática (73 exports + 24 GHIDRA IDs + 1 CAP comportamental). A decisão
não incorpora nenhuma especulação de UI; todas as operações declaradas correspondem a funções já existentes
no binário `DocumentAutomationEngine.dll` v24.03.10017. Gaps declarados (itens "Em aberto" da spec) são
intencionais e serão tratados em ADRs ou tasks posteriores quando evidência comportamental ficar disponível.

Além disso, esta ADR **não implementa comunicação de rede com um servidor Automation Engine real**; o
código implementa o modelo de conexão **desconectado** (estado "Not connected to any server") e as
funções que podem operar sem conexão ativa. A conectividade real dependeria de bibliotecas externas
(`aesynclib.dll`, `aaserver_c.dll`, `BGMWare.dll`) e de nova captura comportamental com conexão
bem-sucedida, o que seria decidido em ADR futura.

## Próximos passos para implementação

Baseado no que a evidência realmente suporta:

1. **Criar `src/prepress/automation_engine.h`** com a classe `AutomationEngineAdapter`, `ConnectionProperties`,
   `AuthenticationMethodProperties`, `SyncResourcesParams`, `PrintingMethod`, `SmartNameValue`, `DotShape`,
   `SyncDirection`, `ServerVersion` — estrutura de tipos e interface mínima.

2. **Criar `src/prepress/automation_engine.cpp`** implementando:
   - `connect()` → chamada à função `0x180014310` (`Connect(2-param)`) preenchendo `ConnectionProperties`
   - `disconnect()` → chamada à `0x1800143f0` (`Disconnect()`), reinício do `BGM_TAuthenticator`
   - `getAuthenticationMethods()` → chamada à `0x180014400` (`GetAuthenticationMethods`)
   - `syncResources()` → chamada à `0x180065b30` (`SyncResources`) com parâmetro `SyncDirection`
   - `mapPathToDataCenterURI()` → chamada à `0x1800546f0` (`MapPathToDataCenterURI`)
   - `mapDataCenterURIToPath()` → chamada à `0x1800542b0` (`MapDataCenterURIToPath`)
   - `getSmartNames()` → funções `0x180066700` (`GetWorkflows`), `0x1800666a0` (`GetWorkflowParameters`),
     `0x180065c50` (`LoadWorkflowVariables`), `0x18000bbb0` (`RegisterWorkflowCategory`)
   - `getPrintingMethods()` → chamada à `0x1800618d0` (`GetPrintingMethods`)
   - `addPrintingMethod()` / `removePrintingMethod()` / `refreshPrintingMethods()` → `0x1800618a0`,
     `0x180061940`, `0x180061920`
   - `getDotGainCurves()` → `0x180065b90`
   - `getDotShapes()` → `0x180065be0` (inferido)
   - `isResourceUpToDate()` → `0x180065a40`
   - `getMyWorkspaceSettings()` → `0x180014420`
   - `getServerVersion()` → `0x180014460`
   - `setCallbackOnConnectionLost()` → `0x1800144a0`
   - `AESyncDirectory()` → `0x180053f00`
   - `getJobBarcodeProperties()` → `0x180012c80`

3. **Integrar com build:** adicionar `src/prepress/automation_engine.cpp` ao `CMakeLists.txt` do módulo
   `prepress`.

4. **Tests unitários (planejados):** testes que citam `F-011` e asserem o comportamento de cada método
   usando fixtures de `Document` já existentes, operando no estado "desconectado".

5. **Aguardar CAPs comportamentais:** itens "Em aberto" da spec (campos de login, diálogo de workflow,
   botões de add/remove de métodos, mensagens de erro UI) serão reauditados quando captura de GUI com
   conexão ativa for disponível; as funções aqui implementadas não dependem desses gaps para operar no
   estado desconectado.

6. **Registrar laudo de auditoria** `docs/audit/F-011-audit.md` após primeira build bem-sucedida.

## Mapeamento binário → ArtPlus (resumo)

| Função (Ghidra) | Classe/método ArtPlus | Observação |
|---|---|---|
| `0x18000a8b0` | `AutomationEngineModule` (construtor/initialization) | Ponto de entrada do módulo; registration de callbacks e categorias Smart Name |
| `0x18000b880` | `AutomationEngineModule::Create()` | Fábrica do módulo; retorna `unique_ptr<ArtDoc::Module>` |
| `0x18000bbb0` | `AutomationEngineAdapter::registerWorkflowCategory()` | `RegisterWorkflowCategory()` registra categoria de variáveis de workflow |
| `0x180014310` | `AutomationEngineAdapter::connect()` | `Connect(2-param)` estabelece conexão com proxy provider; preenche `ConnectionProperties` |
| `0x1800143f0` | `AutomationEngineAdapter::disconnect()` | `Disconnect()` limpa estado de autenticação e memória alocada |
| `0x180014400` | `AutomationEngineAdapter::getAuthenticationMethods()` | `GetAuthenticationMethods()` retorna `vector<AuthenticationMethodProperties>` |
| `0x180014420` | `AutomationEngineAdapter::getMyWorkspaceSettings()` | `GetMyWorkspaceSettings()` retorna `optional<pair<uri, string>>` |
| `0x180014460` | `AutomationEngineAdapter::getServerVersion()` | `GetServerVersion()` retorna `optional<ServerVersion>` |
| `0x1800144a0` | `AutomationEngineAdapter::setCallbackOnConnectionLost()` | `SetCallbackOnConnectionLost()` registra callback para perda de conexão |
| `0x180053f00` | `AutomationEngineAdapter::AESyncDirectory()` | `AESyncDirectory()` retorna caminho do diretório sincronizado |
| `0x1800542b0` | `AutomationEngineAdapter::mapDataCenterURIToPath()` | `MapDataCenterURIToPath()` converte URI do DataCenter para caminho local |
| `0x1800546f0` | `AutomationEngineAdapter::mapPathToDataCenterURI()` | `MapPathToDataCenterURI()` converte caminho local para URI do DataCenter |
| `0x1800618a0` | `AutomationEngineAdapter::addPrintingMethod()` | `AddPrintingMethod()` adiciona método de impressão customizado |
| `0x1800618d0` | `AutomationEngineAdapter::getPrintingMethods()` | `GetPrintingMethods()` retorna os 9 métodos padrões listados na UI |
| `0x180061920` | `AutomationEngineAdapter::refreshPrintingMethods()` | `RefreshPrintingMethods()` atualiza lista de métodos de impressão |
| `0x180061940` | `AutomationEngineAdapter::removePrintingMethod()` | `RemovePrintingMethod()` remove método de impressão do catálogo |
| `0x180065a40` | `AutomationEngineAdapter::isResourceUpToDate()` | `IsResourceUpToDate()` verifica se recurso foi alterado no servidor |
| `0x180065b30` | `AutomationEngineAdapter::syncResources()` | `SyncResources()` sincroniza recursos servidor↔cache com direção SyncDirection |
| `0x180065b90` | `AutomationEngineAdapter::getDotGainCurves()` | `GetDotGainCurves()` retorna curvas de ganho de ponto para calibração |
| `0x180065be0` | `AutomationEngineAdapter::getDotShapes()` | `GetDotShapes()` retorna formas de ponto para calibração de impressão |
| `0x180065c50` | `AutomationEngineAdapter::loadWorkflowVariables()` | `LoadWorkflowVariables()` carrega variáveis de workflow do servidor |
| `0x180065ce0` | `AutomationEngineAdapter::refreshSmartNames()` | `RefreshSmartNames()` atualiza variáveis Smart Name no contexto |
| `0x1800666a0` | `AutomationEngineAdapter::getWorkflowParameters()` | `GetWorkflowParameters()` retorna parâmetros de workflow especificado por nome |
| `0x180066700` | `AutomationEngineAdapter::getWorkflows()` | `GetWorkflows()` retorna lista de workflows disponíveis no servidor |
| `0x180012c80` | `AutomationEngineAdapter::getJobBarcodeProperties()` | `GetJobBarcodeProperties()` retorna propriedades de código de barras do job |
| `CAP-20261126-01` | aba Automation Engine + aba Printing Methods + menus UI | evidência comportamental; confirma estado "Not connected" e 9 métodos padrões |

## Referências cruzadas

- Spec: `docs/features/F-011.md` (status: spec, confiança: media)
- Evidência: `rag/evidence/F-011/` (24 IDs GHIDRA + CAP-20261126-01)
- ADRs anteriores: `ADR-015-trapping.md`, `ADR-016-gerenciamento-objetos.md`
- Módulo: `src/prepress/automation_engine.h/.cpp` (nova)
- Pipeline: ghidra → documentação → F-011 → arquitetura → ADR → implementacao → testes → auditor