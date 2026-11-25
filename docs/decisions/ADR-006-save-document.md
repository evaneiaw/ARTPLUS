# ADR-006 — Save Document (F-006)

> **ADR canônica de F-006.** Única decisão vigente de arquitetura para *Save Document*.
> `docs/architecture/F-006-ADR.md` foi **consolidado** neste documento (ver §Consolidação).
> Visão de módulo complementar (não normativa): `docs/architecture/F-006-SaveDocument.md`.

## Contexto

Spec: `docs/features/F-006.md` (v24.03.10017, `status: spec`, `confianca: media`). O estado da
funcionalidade **não** é declarado por esta ADR: `BLO-005` consta como **SUPERADO em
2026-11-24** em `docs/agents/BLOQUEIOS.md`, e o estado vigente é o que `INVENTORY.md` deriva
dos gates. Este ADR decide a **arquitetura** de F-006; **não** eleva o estado da
funcionalidade: `Estado: aprovado` na ADR significa "decisão de desenho aprovada",
não "feature implementada" nem "feature auditada". O gate `--stage code`/`--stage audit`
continua sendo o juiz do estado da feature.

Escopo v1 já declarado na spec (§ cabeçalho, §4 R5, §6, §9): o container proprietário
`.artplus` **não** foi derivado; a **criptografia do container está fora do escopo da v1**,
os flavours `Preflight (1)` e `Separations (2)` estão fora do escopo, e a gravação da v1 é
feita pelo `DocumentSerializer` do ArtPlus (JSON), não pelo container proprietário.

Evidência estática (v24.03.10017, `Document.dll` + `NDLModel.dll`), em
`rag/evidence/F-006/ghidra/`:

| ID | Função | Arquivo |
|---|---|---|
| `GHIDRA-Document-0x180099710` | `ArtDoc::Document::Save(boost::filesystem::path const&, ArtDoc::WriteOptions const&)` | `Document__180099710.md` |
| `GHIDRA-Document-0x180016730` | `ArtDoc::WriteOptions` (move ctor `??0WriteOptions@ArtDoc@@QEAA@$$QEAV01@@Z`) | `Document__180016730.md` |
| `GHIDRA-Document-0x1802ad561` | `GODocument::Save(GODocument*, GADocSaveParams*)` — trampolim por jumptable | `Document__1802ad561.md` |
| `GHIDRA-Document-0x1802ad5eb` | `GODocument::SignOnSave(GODocument*, GODocSignParams*)` — trampolim por jumptable | `Document__1802ad5eb.md` |
| `GHIDRA-NDLModel-0x180021990` | `NDLModel::SaveDocument(Selection, string const&, SaveOptions const&)` → `Future<vector<ActionMessage>>` | `NDLModel__180021990.md` |
| `GHIDRA-NDLModel-0x180042a40` | `NDLModel::SaveOptions` ctor a partir de `basic_string_view` | `NDLModel__180042a40.md` |

Evidência comportamental: `CAP-20261124-01` (v24.03.10017, 2026-11-24; `docs/behavior/F-006.md`
e `rag/evidence/F-006/behavior/CAP-20261124-01.md`) — menu `File` lido item a item
(`Save`/`Ctrl+S`, `Save As...`/`Ctrl+Shift+S`), diálogo **nativo** do Windows com filtro
`ArtPlus Files (*.artplus)`, gravação de `saveas-test.artplus` (15739 bytes) e **nenhuma
mensagem ao usuário**; o `Ctrl+S` subsequente regrava em silêncio. O registro anterior
`CAP-BLOCKED-006` (2026-11-21, "GUI inativa") está **SUPERADO** por essa captura
(`rag/evidence/F-006/manifest.json` → `historico_bloqueios`) e é mantido apenas como
histórico: não sustenta nem contesta decisão alguma deste ADR.

A captura cobre o **caminho de sucesso** e a apresentação de UI. Ela **não** cobre backup
(`NeedBackupOnSave` não foi exercido), confirmação de sobrescrita, caminho inválido /
permissão negada, extensão automática nem mensagens de erro de I/O; esses pontos continuam
vindo de pseudocódigo estático ou permanecem não observados, e estão declarados como tal em
§Limitações e §Não decidido por este ADR.

## Decisão

1. **`DocumentSaveManager`** (`src/document/document_save_manager.h/.cpp`, já existente) é o
   único orquestrador do fluxo de salvamento. Ele **reusa** `DocumentSerializer` — não
   reimplementa serialização — e concentra as decisões de Save vs Save As, backup,
   flavours, criptografia (recusada) e finalização de estado.
2. Os tipos de domínio `SaveFlavour`, `SaveEncryptionParams`, `SavePageRange`,
   `WriteOptions`, `SaveResult` e `SaveException` vivem no mesmo módulo `src/document/`.
   `WriteOptions` espelha as flags observadas em `ArtDoc::WriteOptions` (`+0x60..+0x71`,
   path em `+0x78`, `Flavour`) com nomes explícitos.
3. `NDLModel::SaveDocument` (`0x180021990`) mapeia para `DocumentSaveManager::saveDocument()`.
   Na v1 a execução é **síncrona no thread chamador**; a variante assíncrona é
   `TODO(F-006)` porque `Document`/undo não são thread-safe.
4. A UI (`ArtPlusMainWindow`) instancia o manager e delega; trata o `SaveResult` retornado —
   sucesso exibe status, falha exibe aviso explícito e **não** é mascarada por mensagem de
   sucesso (correção D3, §Correções pós-laudo). O `QFileDialog` de *Save As* permanece em
   `src/ui/` (diálogo é UI, regra de negócio não). `src/document` não depende de `QtWidgets`.
5. **Nada de stub silencioso.** Pedido fora do escopo da v1 (criptografia, `Flavour != 0`)
   retorna `SaveResult{ok = false}` com `errorCode` e mensagem explícitos, **antes** de
   qualquer escrita. É proibido gravar em claro quando uma senha foi pedida.
6. **Gravação da v1** = `DocumentSerializer::save` (JSON com `"format": "artplus"`). O
   container proprietário `.artplus` é `TODO(F-006)` até existir evidência do layout;
   enquanto isso não houver, `GODocument::Save` **não** é reproduzido byte a byte.
7. Backup preserva a regra binária confirmada (`IsSaveAs == false && NeedBackupOnSave ==
   true`; incremental → `copy_file`, senão → `rename`), mas o **nome** do backup é
   provisório (`<destino>.bak`) porque `FUN_180095230` não foi decompilado (spec §8.1 item 2).
8. **Ordem do fluxo na v1** (ratificada após o laudo de 2026-11-24):
   working file (E1) → detecção de caminho e **E5** (Save vs Save As) → guard **E8**
   (criptografia) → guard **E9** (flavour) → backup (R3) → `DocumentSerializer::save` →
   finalização. Os guards de escopo vêm **antes** de qualquer escrita — exigência da spec
   §4 R5.2/§6 e das exceções E8/E9. Detalhe em §Correções pós-laudo.
9. **Falha do serializer depois do backup por `rename` (E10) restaura o original** (D4,
   §Correções pós-laudo): o backup não-incremental **move** o destino para `<destino>.bak`
   antes da gravação, então, se `DocumentSerializer::save` falha, a v1 faz o *rollback* do
   `.bak` de volta ao destino antes de devolver `ok = false`. É **robustez declarada** do
   clone, não paridade: o comportamento do ArtPro+ v24 nesse caminho não foi medido.

## Mapeamento binário → ArtPlus (confirmado)

| Função (Ghidra) | Classe/método ArtPlus | Observação |
|---|---|---|
| `0x180099710` — `ArtDoc::Document::Save` | `DocumentSaveManager::save()` | ponto único de escrita do fluxo: `WriteOptions`, Save vs Save As, incremental, backup, `GODocument::Save`, finalização |
| `0x180016730` — `ArtDoc::WriteOptions` | `ArtPlus::WriteOptions` (struct) | move ctor do tipo de opções; 12 bools em `+0x60..+0x71`, path em `+0x78`, enum `Flavour`; mapeado para campos nomeados |
| `0x1802ad561` — `GODocument::Save` | `DocumentSerializer::save()` (reuse) | **trampolim por jumptable**; o corpo real e o layout do container **não** foram recuperados — a v1 usa o serializer JSON existente e marca paridade binária como `TODO(F-006)` |
| `0x1802ad5eb` — `GODocument::SignOnSave` | nenhum (fora da v1) | é **assinatura digital**, não criptografia; também trampolim por jumptable; nenhuma classe ArtPlus o implementa |
| `0x180042a40` — `NDLModel::SaveOptions` ctor | `WriteOptions::fromSaveOptions()` (adapter) | a v1 é stub declarado (`TODO(F-006)`): devolve `WriteOptions{}` + `qWarning`, não lê o `string_view` |
| `0x180021990` — `NDLModel::SaveDocument` | `DocumentSaveManager::saveDocument()` | wrapper de aplicação (assíncrono no original via `Future<...>`, síncrono na v1) |

### Correção de mapeamento anterior

O ADR consolidado `docs/architecture/F-006-ADR.md` §6 mapeava `0x1802ad5eb` para
`DocumentSaveManager::applyEncryption()`. **Está errado.** A evidência
`Document__1802ad5eb.md` identifica `GODocument::SignOnSave(GODocument*, GODocSignParams*)`
— assinatura digital. `applyEncryption()` existe no ArtPlus como ponto de extensão interno
(`document_save_manager.h`, privado) e **não** corresponde a essa função binária. Não há
endereço confirmado para `applyEncryption()`; ela permanece sem contraparte mapeada e fora
do caminho alcançável da v1 (o guard de criptografia retorna antes).

### Funções com evidência estática, sem mapeamento decidido na v1

Existem `.md` de evidência para as funções abaixo; **este ADR não decide** a classe ArtPlus
delas. Ficam para ADR futura, quando a spec as cobrir com regra e teste:

| Função (Ghidra) | Nome confirmado na evidência | Situação |
|---|---|---|
| `0x180099690` | `ArtDoc::Document::RevertToSaved` | `DocumentSaveManager::revertToSaved()` existe como `TODO(F-006)` (retorna `false` + `qWarning`); semântica não especificada |
| `FUN_180095230` | helper de caminho de backup (sem `.md` no manifest) | `deriveBackupPath()` provisório `.bak` |
| `0x180042b80` / `0x180042bb0` | `SaveOptions::IsIncrementalSave` / `SetIncrementalSave` | flag lida/escrita; semântica de gravação incremental não reproduzida |
| `0x1800a2110` / `0x1800a20e0` | `PieceInfoWriter` / `EskoPieceInfoWriter` (ctors) | metadados de peça; `TODO(F-006)` |
| `0x18013f240` / `0x180195c10` / `0x1801954e0` | `WriteContext` ctor / `RegisterPieceInfoWriter` / `RegisterDocumentPieceInfoWriter` | pipeline de escrita por peça; `TODO(F-006)` |
| `0x18023b8e0` | `DocumentIO::WriteImage` | imagens separadas; `TODO(F-006)` |
| `0x18004b420` / `0x1800508d0` | `NDLModel::SaveMarkSet` / `SavePreflightReport` | salvamentos especializados; fora da v1 |
| `0x1800208f0` / `0x180020920` | `SaveDocumentException` ctors | mapeia conceitualmente para `SaveException`, sem decisão de forma |

## Contrato de interface

```cpp
// src/document/document_save_manager.h  (estado atual do código; este ADR o ratifica)
namespace ArtPlus {

enum class SaveFlavour { NormalPdf = 0, Preflight = 1, Separations = 2 };

struct SaveEncryptionParams {
    int encryptionLevel = 0;      // 0 = sem criptografia; != 0 => erro explícito na v1
    QString ownerPassword;        // nunca persistida, nunca logada
    QString userPassword;
};

struct SavePageRange { int firstPage = 0; int lastPage = 0; bool allPages = true; };

struct WriteOptions {
    bool isSaveAs = false;
    bool isSaveAsCopy = false;
    bool isSaveUnmodified = false;
    bool needBackupOnSave = false;
    bool isIncrementalSave = false;
    bool noOptimizedSave = false;      // v1: apenas registrado (qDebug)
    SaveFlavour flavour = SaveFlavour::NormalPdf;
    std::vector<SavePageRange> pageRanges;   // vazio => todas as páginas
    SaveEncryptionParams encryption;
    static WriteOptions fromSaveOptions(const QString&);  // TODO(F-006): stub declarado
};

struct SaveResult { bool ok = false; QString filePath; QString backupPath;
                    int errorCode = 0; QString errorMessage; };

class SaveException : public std::runtime_error { public: int code() const noexcept; };

class DocumentSaveManager : public QObject {
    Q_OBJECT
public:
    explicit DocumentSaveManager(Document& doc, QObject* parent = nullptr);
    SaveResult save(const QString& destinationPath, const WriteOptions& options);
    SaveResult saveDocument(const QString& destinationPath, const WriteOptions& options);
    static QString deriveBackupPath(const QString& destinationPath);   // provisório: <dest>.bak
    bool revertToSaved();                                             // TODO(F-006)
signals:
    void progressStatus(const QString& status);   // STATUS_SAVE / STATUS_OPTIMIZING / STATUS_WRITING_TO_DISK
    void finished(const SaveResult& result);
private:
    Document& doc_;
    bool switchToWorkingFile();
    bool applyEncryption(const SaveEncryptionParams&);
    void finalizeState(const QString& path, const WriteOptions& opts);
};

} // namespace ArtPlus
```

Observações de contrato:

- `save()` **não** lança para a UI: `SaveException` é capturada na borda e convertida em
  `SaveResult`.
- `encryptionLevel != 0` → `ok = false`, `errorCode = 0`, mensagem
  `Erro (TODO F-006): Criptografia não é suportada nesta versão.`, zero bytes escritos.
- `flavour != NormalPdf` → `ok = false`, `errorCode = 8` (análogo de `SaveException(8)`),
  zero bytes escritos.
- Falha de serialização → `ok = false`, `errorCode = 8`, mensagem genérica de falha.

## Limitações declaradas da v1 (sem inventar comportamento)

Estas limitações são **decisão de escopo**, com referência ao parágrafo da spec. Nenhuma
delas afirma que o original se comporta assim; todas afirmam o que a v1 **não** faz.

1. **Criptografia do container: fora da v1** (§4 R5, E8). `GADocSaveParams::SetNewEncryptionParams`,
   `SetNewOwnerPassword`, `SetNewUserPassword` são observáveis em R4.1, mas o container que
   receberia esses parâmetros não foi derivado. Fica fora até o container ser derivado.
   `GODocument::SignOnSave` (`0x1802ad5eb`) é assinatura digital e também está fora.
2. **`Flavour == 1` (preflight) e `Flavour == 2` (separações): fora da v1** (§4 R2.2, E9).
   Retornam erro explícito; nenhum ramo de processamento é implementado.
3. **`switchToWorkingFile()`** — a v1 não copia arquivo nem reproduz o estado `this+0x78 == 2`
   (E1); devolve `true` sempre. Documento nunca salvo (`filePath()` vazio) **não** é E1: sem
   arquivo de origem não há cópia a falhar, e o save prossegue como Save As. **A confirmar em
   evidência** (a captura não exercitou o estado `this+0x78 == 2`).
4. **Backup** — regra binária preservada; **nome** provisório `<destino>.bak` até
   `FUN_180095230` ser lido (spec §8.1 item 2). **A confirmar em evidência.**
5. **`noOptimizedSave`** — comprovado como chave de 15 bytes comparada por `memcmp` no
   binário; o efeito em `GADocSaveParams` (valor `lVar43`) é **inferência** da spec §4 R2.3.
   Na v1 é apenas registrado; não altera a gravação. **A confirmar em evidência.**
6. **`isIncrementalSave`** — na v1 afeta só a escolha `copy_file`/`rename` do backup; a
   semântica de R2 (base incremental, `GADocSaveParams` com clone strategy) não é
   reproduzida.
7. **`revertToSaved()`** — `TODO(F-006)`, devolve `false` + `qWarning`. **A confirmar em
   evidência.**
8. **`WriteOptions::fromSaveOptions()`** — stub declarado; não lê `NDLModel::SaveOptions`.
9. **Assincronia** — `saveDocument()` é síncrono; `QFuture<SaveResult>` é `TODO(F-006)`.
10. **Comportamento de UI no caminho de sucesso** — `CAP-20261124-01` observou menu, atalhos e
    diálogo nativo, e que **nenhuma** mensagem aparece ao gravar. O caminho de **erro**
    (texto por `error_code`, disco cheio, permissão, caminho inválido) permanece **não
    observado** (E4). A v1 exibe aviso explícito e nunca "Saved" com `SaveResult::ok == false`
    — escolha deliberada (D3), não paridade comprovada.
11. **`ChangeCollector::NotifyChangesCollected` / `SetTitle`** — presentes no original
    (R4.4) e ausentes em `finalizeState()`; não implementados na v1.
12. **E10 com backup por `rename`** — a v1 restaura o original ao destino (D4,
    §Correções pós-laudo). É **robustez declarada**, não paridade: o caminho não foi
    observado no ArtPro+ v24 e não há teste dedicado que combine `needBackupOnSave` com E10.

## Correções pós-laudo (2026-11-24) — ordem de efeitos, E5 e UI

O laudo `docs/audit/F-006-audit-20261124.md` (REPROVADO) apontou três divergências de
**código** (D1/D2/D3), não de evidência. Foram corrigidas em
`src/document/document_save_manager.cpp` e `src/ui/main_window.cpp` (verificado por leitura em
2026-11-24; cobertura em `tests/unit/test_save_document.cpp`). Este ADR ratifica o desenho
resultante e **não** altera o estado da feature: quem o define é `INVENTORY.md` a partir dos
gates (`--stage code`/`--stage test`/`--stage audit`), não este documento.

| Item | Desenho ratificado |
|---|---|
| **D1** — guards antes da escrita | E8 (`encryptionLevel != 0`) e E9 (`flavour != NormalPdf`) retornam **antes** do bloco de backup: nenhum `rename`/`copy`/gravação toca o destino em caminho de erro. Era o efeito destrutivo provado pelo laudo (destino movido para `.bak` mesmo com o save rejeitado). |
| **D2** — E5 | destino inexistente (`!QFileInfo(dest).exists()`) força `isSaveAs = true` **antes** da comparação por `canonicalFilePath()` — que devolve vazio para caminho inexistente e faria dois inexistentes compararem iguais. |
| **D3** — UI não mascara falha | `saveArtPlus`/`saveArtPlusAs` checam `SaveResult::ok`; em falha exibem aviso + status bar e **não** atualizam o indicador de modificado. "Saved" só no sucesso. |
| documento nunca salvo | documento sem `filePath()` é salvável (primeiro save = Save As); **não** é E1. |

Ordem v1 de `DocumentSaveManager::save()`: working file (E1) → R1 + **E5** → **E8** → **E9** →
R3 backup → `DocumentSerializer::save` → finalização. Guards de escopo antes de qualquer
escrita é requisito da spec §4 R5.2 e §6; a implementação anterior violava isso.

**Risco residual de E10 com backup — RESOLVIDO por rollback (D4).** O laudo
`F-006-audit-20261124d.md` §5 registrava: o backup (R3) executa **antes** do
`DocumentSerializer::save`; com `isIncrementalSave == false` e `needBackupOnSave == true` o
backup é `rename` (spec §R3.4), o destino fica ausente até a gravação, e uma falha E10
deixava o original apenas em `<destino>.bak` — o usuário veria o arquivo "sumir". O código
atual **restaura** o original. Situações cobertas por `src/document/document_save_manager.cpp`
(bloco de falha do serializer; verificado por leitura em 2026-11-24):

| Situação | Resultado observável |
|---|---|
| backup incremental (`copy_file`, R3.3) + falha do serializer | o destino **nunca** foi movido → **sem rollback**, destino não é apagado; `ok = false`, `errorCode = 8`; `backupPath` permanece preenchido se o `.bak` foi criado |
| backup por `rename` (R3.4) + falha do serializer, rollback **ok** | o original volta do `.bak` para o destino (arquivo parcial do serializer, se existir, é removido antes do `rename` de volta); `ok = false`, `errorCode = 8`, **`backupPath` vazio** (consumido pelo rollback), mensagem declara a restauração |
| backup por `rename` + rollback **falhou** | `backupPath` aponta o `.bak` e a mensagem nomeia explicitamente onde o conteúdo original está e que o destino **não** foi restaurado |

### D4 — rollback do backup no E10 (robustez declarada, não paridade)

Decisão registrada em 2026-11-24 sobre o desenho já implementado:

1. Quando o backup **moveu** o original (`rename`, R3.4), a falha do serializer **restaura**
   o original ao destino pedido, em vez de deixá-lo somente em `.bak`. Motivo: o estado
   anterior deixava o caminho pedido **sem arquivo** sem que a spec §6 (linha E10) previsse
   essa consequência — mesma classe de efeito destrutivo apontada na D1, agora no caminho de
   falha de gravação.
2. Quando o backup foi `copy_file` (incremental), **não** há rollback: o original nunca foi
   movido e o destino **não** é apagado — apagar seria perda de dados, e a spec §R3.3 define a
   cópia como *preservação* do original.
3. Um arquivo **parcial** deixado pelo serializer no destino **não** é o original (este está
   em `.bak`); por isso pode ser descartado para viabilizar o `rename` de volta. Se não puder
   ser descartado, o rollback é declarado **falho** e o `backupPath` é reportado.
4. O rollback **não** mascara a falha: `ok = false` e `errorCode = 8` permanecem em todos os
   ramos; mudam apenas a mensagem e o `backupPath`.

**Base da decisão.** É decisão de **robustez / política de restauração** do clone, não
reprodução de comportamento medido: `CAP-20261124-01` não exerceu `NeedBackupOnSave` nem
provocou falha de serializer no ArtPro+ v24, e a evidência estática de `0x180099710` não
revela tratamento de rollback (`FUN_180095230` e o corpo de `GODocument::Save` seguem não
derivados). Nada aqui afirma o que o original faz nesse caminho — nem que restaura, nem que
deixa o `.bak`; registra-se apenas o que o clone passou a fazer.

**Desvio declarado da tabela E10 da spec.** A linha E10 de `docs/features/F-006.md` §6
prescreve a mensagem base `"Erro (TODO F-006): Falha na serialização do documento."`. No
clone ela permanece **exata** apenas no caminho sem rollback (incremental ou sem backup); no
rollback bem-sucedido há um acréscimo declarando a restauração, e no rollback falho a
mensagem nomeia o `.bak`. Alinhar a tabela é do dono da spec (`documentacao`) — este ADR não
edita a spec.

**Lacuna que permanece (não é decisão de arquitetura).** Não existe teste que combine
`needBackupOnSave = true` com E10 e verifique a restauração: os testes de E10
(`testT9SaveInvalidPathReturnsGenericError`, `testT10WriteFailureReturnsGenericError`) usam
`baseOpts()` sem backup. O item "adicionar teste `needBackupOnSave=true` + E10" do laudo
`F-006-audit-20261124d.md` §8 continua **aberto** e é do dono de `tests/`. Este ADR registra a
decisão e o estado do código; **não** declara cobertura de teste.

## Não decidido por este ADR (devolve à spec)

Itens da spec que permanecem abertos e que **este ADR não resolve por inferência**. A
pergunta objetiva e o dono estão na spec; aqui só se registra que a decisão de arquitetura
fica pendente até a resposta:

| Item | Parágrafo exato | Por que não decidido aqui |
|---|---|---|
| Layout/chunking/compressão/assinatura do container `.artplus` | `docs/features/F-006.md` §8.1 item 1 | exige disassembly do alvo do jumptable de `0x1802ad561`; a captura `CAP-20261124-01` produziu um `.artplus` real, mas gravar um arquivo não revela o layout, e este ADR não trata leitura de container |
| Nome real do backup (`FUN_180095230`) | §8.1 item 2 | corpo da função não lido; `.bak` é provisório declarado |
| Mensagens de I/O por `error_code` | §8.1 item 3 | a captura cobre só o caminho de sucesso; nenhuma mensagem de erro observada |

O item "existência/comportamento de UI do save" (§8.1 item 4 + §3) **deixou de ser
pendência** em 2026-11-24: `CAP-20261124-01` observou menu, atalhos, diálogo nativo e ausência
de mensagem no sucesso. O que resta não observado é a UI de **erro** (linha acima).

## Alternativas descartadas

1. **Manter gravação direta em `DocumentSerializer::save` na UI** — descartada: não cobre
   Save/Save As, backup, flavours, criptografia nem finalização; espalha regra de negócio em
   `src/ui/`.
2. **Implementar escritor do container `.artplus` agora** — descartada: o formato não foi
   derivado; `CAP-20261124-01` prova que a v24 grava um `.artplus` (15739 bytes) e nada mais —
   não revela layout, chunking, compressão ou assinatura. Produziria bytes inventados
   apresentados como compatíveis.
3. **Mapear `0x1802ad5eb` para `applyEncryption()`** (como fazia o ADR consolidado) —
   descartada por **falso**: a evidência diz `GODocument::SignOnSave`, assinatura digital.
4. **Criptografia "melhor esforço"** (gravar em claro quando há senha, ou gerar container
   criptografado sem evidência) — descartada: viola "nada de stub silencioso" e produziria
   arquivo com garantia de segurança falsa.
5. **Assíncrono obrigatório já na v1** — descartada: `Document` não é thread-safe; marshal
   não compensa no v1 síncrono.

## Consequências

- **Arquivos afetados** (já implementados; este ADR apenas ratifica a fronteira):
  `src/document/document_save_manager.h/.cpp`, `src/document/document_serializer.h/.cpp`
  (reuse), `src/document/document_model.h/.cpp` (`filePath`/`setModified`),
  `src/ui/main_window.cpp` (chamador; trata `SaveResult::ok` — D3), `CMakeLists.txt`
  (`DOCUMENT_SOURCES`).
- **Dependências:** nenhuma nova. `QtCore`/`QtGui` (`QObject`, `QFile`, `QFileInfo`,
  `QJsonDocument`); `boost::filesystem` do original **não** é reproduzido — a v1 usa `QFile`.
  Sem ADR de licença adicional.
- **Risco:** a spec é `confianca: media` — há captura do **caminho de sucesso**, mas o formato
  binário, o nome do backup e a UI de erro seguem não derivados. O risco de o destino ficar
  ausente em E10 com backup por `rename` está **resolvido** por rollback declarado (D4); essa
  restauração é robustez do clone, **não** paridade medida, e ainda não tem teste dedicado.
  Mitigação estrutural: todo caminho não comprovado retorna erro explícito ou registra
  `TODO(F-006)`; nunca finge sucesso.
- **Migração de dados:** nenhuma. O formato JSON do `DocumentSerializer` permanece; o
  container proprietário nunca foi produzido pela v1, então não há artefato a migrar.
- **Contrato entre módulos:** `src/ui` → `src/document` apenas. `src/document` não importa
  `QtWidgets`, `src/ui`, `src/prepress` nem `src/automation`. `src/pdf` não escreve
  `.artplus`.

## Consolidação

- `docs/decisions/ADR-006-save-document.md` (este arquivo) passa a ser a **única ADR de
  F-006**.
- `docs/architecture/F-006-ADR.md` foi reduzido a uma nota de consolidação apontando para
  cá; o mapeamento errado de `0x1802ad5eb` foi removido de lá para não contradizer este ADR.
- `docs/architecture/F-006-SaveDocument.md` permanece como **visão de módulo** (diagramas,
  fluxo de dados, dependências), subordinada a este ADR.
- A spec `docs/features/F-006.md` §8.3 registrava a divergência de mapeamento e a existência
  de dois ADRs; ambos tratados aqui.

## Estado

aprovado

Aprovado em 2026-11-24 como decisão de arquitetura de F-006. **Não** altera o estado da
feature: `BLO-005` está **SUPERADO** em `docs/agents/BLOQUEIOS.md` e o estado vigente de F-006
é o que `INVENTORY.md` deriva de `--stage code`/`--stage test`/`--stage audit` — esta ADR não
o declara nem o eleva.

Revalidado em 2026-11-24 (mesma data): o ADR foi alinhado à evidência vigente —
`CAP-20261124-01` no lugar de `CAP-BLOCKED-006` (SUPERADO), `confianca: media` da spec, e o
desenho de ordem de efeitos/E5/UI das correções D1/D2/D3. A decisão de arquitetura não mudou
de substância; o que mudou foi a base factual e o registro do risco residual. Isso **não**
eleva F-006: o veredito continua sendo do laudo (`docs/audit/`).

Registrado em 2026-11-24: **D4** — rollback do backup quando o serializer falha (E10) — como
*robustez declarada* do clone, não paridade com o ArtPro+ v24 (caminho não medido). O risco
residual de E10 com backup deixa de existir; a lacuna de teste combinado permanece com o dono
de `tests/`. O estado desta ADR continua `aprovado` e o estado da **feature** não é elevado
aqui.
