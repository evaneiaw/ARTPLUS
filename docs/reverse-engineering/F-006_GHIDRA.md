# F-006 — Save Document — Ghidra Static Analysis Report

## Contexto da Missão

Módulos alvo: `Document.dll` (módulo de I/O principal) e `NDLModel.dll` (lógica de fluxo de trabalho de salvamento).
Versão referenciada: v240.
Objetivo: mapear as funções de "Save", "Serialize", "Write" e "Archive" em ambos os módulos com evidência estática via Ghidra 12.2 (JDK 25).

## Evidências Criadas

### Arquivos MD por módulo e função

| Endereço | Módulo | Nome Ghidra / Mangling | ID Evidência |
|---|---|---|---|
| 0x180099710 | Document.dll | `?Save@Document@ArtDoc@@QEAAXAEBVpath@filesystem@boost@@AEBVWriteOptions@2@@Z` (ArtDoc::Document::Save) | GHIDRA-Document-0x180099710 |
| 0x180099690 | Document.dll | `?RevertToSaved@Document@ArtDoc@@QEAAXXZ` (ArtDoc::Document::RevertToSaved) | GHIDRA-Document-0x180099690 |
| 0x180016730 | Document.dll | `??0WriteOptions@ArtDoc@@QEAA@$$QEAV01@@Z` (WriteOptions copy ctor) | GHIDRA-Document-0x180016730 |
| 0x1800a2110 | Document.dll | `??0PieceInfoWriter@ArtDoc@@QEAA@AEBV01@@Z` (PieceInfoWriter) | GHIDRA-Document-0x1800a2110 |
| 0x1800a20e0 | Document.dll | `??0EskoPieceInfoWriter@ArtDoc@@QEAA@XZ` (EskoPieceInfoWriter) | GHIDRA-Document-0x1800a20e0 |
| 0x18013f240 | Document.dll | `??0WriteContext@ArtDoc@@QEAA@AEBV01@@Z` (WriteContext) | GHIDRA-Document-0x18013f240 |
| 0x180195c10 | Document.dll | `?RegisterPieceInfoWriter@ArtDoc@@YA_K...` (RegisterPieceInfoWriter) | GHIDRA-Document-0x180195c10 |
| 0x18023b8e0 | Document.dll | `?WriteImage@DocumentIO@@YA?AU?$pair@_NV?$optional...` (DocumentIO::WriteImage) | GHIDRA-Document-0x18023b8e0 |
| 0x1802ad561 | Document.dll | `Save(GODocument *, GADocSaveParams *)` | GHIDRA-Document-0x1802ad561 |
| 0x1802ad5eb | Document.dll | `SignOnSave(GODocument *, GODocSignParams *)` | GHIDRA-Document-0x1802ad5eb |
| 0x180021990 | NDLModel.dll | `?SaveDocument@NDLModel@@YA?AV?$Future@V?$vector@UActionMessage@NDLModel@@V?$allocator@UActionMessage@NDLModel@@@std@@@std@@@Parallel@@USelection@1@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVSaveOptions@1@@Z` | GHIDRA-NDLModel-0x180021990 |
| 0x180042a40 | NDLModel.dll | `??0SaveOptions@NDLModel@@QEAA@AEBV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z` (SaveOptions ctor from string_view) | GHIDRA-NDLModel-0x180042a40 |
| 0x1800428b0 | NDLModel.dll | `SaveOptions` (default ctor) | GHIDRA-NDLModel-0x1800428b0 |
| 0x180042b80 | NDLModel.dll | `?IsIncrementalSave@SaveOptions@NDLModel@@QEBA_NXZ` | GHIDRA-NDLModel-0x180042b80 |
| 0x18004b420 | NDLModel.dll | `?SaveMarkSet@NDLModel@@YA?AV?$Future@X@Parallel@@USelection@1@AEBVpath@filesystem@boost@@@Z` | GHIDRA-NDLModel-0x18004b420 |
| 0x1800508d0 | NDLModel.dll | `?SavePreflightReport@NDLModel@@YA?AV?$Future@X@Parallel@@USelection@1@UAction@1@AEBVpath@filesystem@boost@@W4PreflightReportType@1@AEBUApplicationInfo@1@2@Z` | GHIDRA-NDLModel-0x1800508d0 |

### Resumo dos Arquivos MD
11 arquivos para `Document.dll` e 10 para `NDLModel.dll` em `rag/evidence/F-006/ghidra/`. Cada arquivo contém: yaml metadata, assinatura C, pseudocódigo decompilado completo, xrefs (callers/callees), strings referenciadas, e símbolos externos.

## Principais Achados de Serialização

### 1. Document.dll — ArtDoc::Document::Save (0x180099710)

**Assinatura:** `void Save(Document * this, boost::filesystem::path const& param_1, WriteOptions const& param_2)`

**Fluxo resumido do pseudocódigo (extracto):**

1. **Setup inicial:** obtém reporter de status, inicializa progresso `STATUS_SAVE`
2. **Checagem de save-conditions:** 
   - Se `(*(longlong *)(this + 0x70) != 0)`, troca para o working file
   - Se `(*(int *)(this + 0x78) == 2)`, lança `SaveException` ("original file could not be copied to working file")
3. **Condicionais de salvamento:**
   - Se `Flavour == 0`: **PDF normal** — processa incremental save (copia arquivo base), gera GADocSaveParams, chama `GODocument::Save(params)`.
   - Se `Flavour == 1`: abre cache, define `this->[0x78] = 3`, copia working file preflightado.
   - Se `Flavour == 2`: define estado, copia o working file.
4. **Incremental save (`NoOptimizedSave`):** compara string_view atual (`kNoOptimizedSave`) com o novo e decide se faz copy completo ou incremental.
5. **Escrita real (Flavour 0):** usa `GODocument::Save(local_638)` — o parâmetro contém caminho, flags de otimização, ranges, encryption params.
6. **Flags de backup:** se `NeedBackupOnSave` e não for save-as, faz rename/copy com backup.
7. **Criptografia:** coleta password owner/user, aplica encryption nos GADocSaveParams.
8. **Finalização:** `SetDirty(false)`, `SetFilePath`, `StatusReporting::ProgressFinalize`, `ChangeCollector::NotifyChangesCollected`.

**Strings críticas:** `STATUS_SAVE`, `STATUS_OPTIMIZING`, `STATUS_WRITING_TO_DISK`, `NoOptimizedSave`, `document.document` (log channel), mensagens de erro "Could not copy the incremental base file to ...", "Could not copy the preflighted working file to ...".

### 2. NDLModel.dll — NDLModel::SaveDocument (0x180021990)

**Assinatura:** `Future<std::vector<NDLModel::ActionMessage,std::allocator<NDLModel::ActionMessage>>> SaveDocument(Selection, std::string const&, SaveOptions const&)`

**Implementação:** É um wrapper (trampoline) que dispatches para o handler real via ponteiro de função em `DAT_1800c1768+0x68` (provavelmente um serviço/instância global). O wrapper apenas empacota os argumentos `Selection`, `basic_string` (caminho), e `SaveOptions`, e retorna um `Future<vector<ActionMessage>>`.

**Outras funções chave:**
- `SaveMarkSet(Selection, path)` — wrapper similar para salvar marcações.
- `SavePreflightReport(Action, path, PreflightReportType, Locale, ApplicationInfo)` — wrapper para relatório de preflight.
- `SaveOptions(ctor from string_view)` — inicializa flags `IsIncrementalSave`, `IsSaveAsCopy`, `IsSaveUnmodified` a partir de um `basic_string_view` (ex: caminho ou configuração nomeada).

### 3. WriteOptions (0x180016730)

**Flags observáveis (offsets):**
- `+0x60 .. +0x71`: campos bool (probavelmente `IsSaveAs`, `IsSaveAsCopy`, `IsSaveUnmodified`, `NeedBackupOnSave`, `IsIncrementalSave` e similares — 12 bools).
- `+0x78`: path ao arquivo.
- Enum `Flavour` (offset variável): `0 = PDF normal`, `1 = preflight`, `2 = separações/outros`.

### 4. Cadeia de "Archive" / Persistência

O salvamento segue esta ordem hierárquica:

1. `NDLModel::SaveDocument` (entrada da aplicação)
2. → chama handler real (vtable em Document.dll)
3. → `ArtDoc::Document::Save(path, WriteOptions)` — controle principal
4. → decide Flavour (0/1/2) → ramo de código específico
5. → `GODocument::Save(GADocSaveParams *)` — salva a estrutura GADoc via PDF/serialização própria
6. → `GODocument::SaveMetadataStream`, `GODocument::Receive(WillSaveMessage/DidSaveMessage)` — callbacks de metadados
7. → encryption (owner/user password), backup rename
8. → state update (`SetDirty(false)`, `SetFilePath`)

## Dependências de Módulos

- **Document.dll** depende fortemente de: `ArtSys.dll`, `LayoutEngine.dll`, `BasicFrameworkCoreLayer.dll`, boost (filesystem, detail), icudtl.dat, libxml.
- **NDLModel.dll** depende de: `boost`, `NDLTypes.dll`, `JEFModel.dll`, `JEFUtils.dll`, YAGL.dll, `Document.dll` (via imports simbólicos).

## Confiança e Limitações

| Aspecto | Confiança | Observação |
|---|---|---|
| Assinatura de funções (`Save`, `WriteOptions`, `SaveOptions`) | **Alta** | Nomes demangled completos, RTTI visível. |
| Estrutura de parâmetros e fluxo básico | **Alta** | Pseudocódigo decompilado estruturado e coerente. |
| Detalhes de template C++ (`std::allocator`, `basic_string_view`, `Future`) | **Média/Alta** | Requer familiaridade com convenções de nome da Esko. Alguns namespaces `std::` estão expostos, mas tipagem completa depende de headers. |
| Formato de arquivo `.artplus` | **Baixa/Média** | Evidência estática não inclui formatação de conteúdo (imagens, vetores, layout) — apenas o mecanismo de I/O. |
| Confirmação do comportamento de `NoOptimizedSave` / incremental | **Alta** | Flags e código condicional identificados; `kNoOptimizedSave` string confirmada. |

## Próximos Passos / Follow-up

1. **Comportamental (CAP-):** Captura de salvamento real no ArtPro+ real (v240/v250) para validar o caminho do arquivo gerado, flags de incremental, e saída do PDF/art+. Necessário para validar `Flavour` e `Encryption` fluxo.
2. **RTTI/Vtable diff v240→v250:** Comparar os mesmos módulos em v240 vs v250 para detectar adições/remoções de funções virtuais.
3. **Manifest.json:** O manifest atual em `rag/evidence/F-006/manifest.json` referencia `DocumentMarks.dll` (v250). Necessita correção para apontar `Document.dll` (v240) ou ser atualizado com o hash correto. **Não editado por determinação do contrato** (não editar evidência bruta).
4. **Decompilação de SaveOptions flags:** Investigar o `basic_string_view` source no `FUN_180016ab0` para entender exatamente quais flags são lidas do parâmetro de configuração.
5. **Exportação de xrefs cruzados:** Exportar xrefs Document.dll → NDLModel.dll e inverso para entender orquestração completa.

## Comando de Execução (reprodutível)

As importações e análises foram realizadas via:

```powershell
# Import Document.dll
$env:JAVA_HOME = 'C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot'
& 'H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat' `
  'H:\Desktop\ArtPlus\tools\ghidra_projects' 'ArtProPlus_Document' -import 'C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\Document.dll' -overwrite

# Import NDLModel.dll
& 'H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat' `
  'H:\Desktop\ArtPlus\tools\ghidra_projects' 'ArtProPlus_NDLModel' -import 'C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\NDLModel.dll' -overwrite

# Script deexport detalhado (funções alvo)
& 'H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat' `
  'H:\Desktop\ArtPlus\tools\ghidra_projects' 'ArtProPlus_Document' -process 'Document.dll' -scriptPath 'H:\Desktop\ArtPlus\tools\ghidra_analysis' -postScript 'DecompileTargets.java' `
  'H:\Desktop\ArtPlus\rag\evidence\F-006\ghidra' '180099710' '180021990' '180042a40' '18004b420' '1800508d0'

# Idem para NDLModel.dll (listada acima)
```