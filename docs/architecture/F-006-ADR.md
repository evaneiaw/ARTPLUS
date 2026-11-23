# ADR-006 — Save Document (F-006)

## 1. Entrada (Contexto/Spec)
Spec: `docs/features/F-006.md`. Funcionalidade: Salvar documento ativo (`ArtDoc::Document::Save`). Confiança: Baixa, devido à ausência de evidência comportamental (`CAP-BLOCKED-006`) na GUI v24.03.10017.
Evidências estáticas primárias: `GHIDRA-Document-0x180099710` (ponto de escrita) e `GHIDRA-NDLModel-0x180021990` (wrapper de aplicação).

## 2. Saída (Resultado)
Documento gravado no disco no caminho destino (proprietário `.artplus` ou JSON via `DocumentSerializer`); estado do documento em memória atualizado (`SetDirty(false)`, `SetFilePath`, `SwitchToWorkingFile`); mensagens de status emitidas via `ArtSys::StatusReporting` (`STATUS_SAVE`, etc.). A saída é I/O, sem dependência de UI para a lógica de domínio.

## 3. Regras (Decisões de Domínio)
- **R1 (Save vs Save As):** Determinado por comparação do status do arquivo de destino com o caminho atual (`0x180099710`).
- **R2 (Incremental):** Se `Flavour == NormalPdf (0)` e `IsIncrementalSave == true`, verifica existência da base; copia (`copy_file`) ou renomeia (`rename`) para criar backup.
- **R3 (Backup):** Backup é criado se `IsSaveAs == false` **e** `NeedBackupOnSave == true`. Backup é `copy_file` se incremental, ou `rename` caso contrário.
- **R4 (Finalização):** Se `Flavour == NormalPdf`, executa `GADoc::Close` e finaliza o estado (`SetDirty(false)`, `ChangeCollector::NotifyChangesCollected`).

## 4. Exceções
- **E1:** Falha ao copiar arquivo original para working file (`this+0x78 == 2`) $\implies$ `SaveException(8)`.
- **E2:** Falha na cópia da base incremental $\implies$ Log de erro; fluxo continua.
- **E3:** Falha ao copiar working file (Flavour=1) $\implies$ Log + `SaveException(8)`.
- **E4:** I/O (Disco cheio/Permissão) $\implies$ Log via `boost::filesystem::error_code`; trata erro sem `throw` se possível.
- **E5:** Destino inexistente + `IsSaveAsCopy=true` $\implies$ Gravação prossegue como Save As.
- **E6:** Documento não modificado (`IsSaveUnmodified == true`) $\implies$ Pula atualização de título/caminho e finalização de dirty state.
- **E7:** `SaveAsCopy == true` $\implies$ Não atualiza caminho/título nem `SetDirty(false)`; grava em caminho diferente do original.

## 5. Evidência
- **Estática:** `GHIDRA-Document-0x180099710` (Orquestração Save), `GHIDRA-Document-0x180016730` (WriteOptions), `GHIDRA-Document-0x1802ad561` (Gravação Proprietária), `GHIDRA-NDLModel-0x180021990` (Wrapper de Aplicação).
- **Comportamental:** `CAP-BLOCKED-006` (GUI inativa; sem observação de fluxo de salvamento via atalhos/menu).

## 6. Mapa Função $\to$ Classe
| Função (Ghidra) | Classe/método ArtPlus | Observação |
| :--- | :--- | :--- |
| `0x180099710` | `DocumentSaveManager::save()` | Orquestra todo o fluxo de Save/Save As. |
| `0x180016730` | `WriteOptions` (struct) | Mapeamento dos 12 bools + caminho + `Flavour`. |
| `0x1802ad561` | `DocumentSerializer::save()` (reuse) | Substitui a gravação proprietária por Serializer JSON existente. |
| `0x1802ad5eb` | `DocumentSaveManager::applyEncryption()` | Implementação de `SignOnSave` (TODO F-006). |
| `0x180099690` | `DocumentSaveManager::revertToSaved()` | Funcionalidade não implementada na v1 (TODO F-006). |
| `0x1800a2110` | `DocumentSaveManager` (PieceInfoWriter) | Responsável por metadados de peça (TODO F-006). |
| `0x180099710` (NDL) | `DocumentSaveManager::saveDocument()` | Interface de entrada da aplicação (wrapper). |
| `0x180042a40` | `WriteOptions::fromSaveOptions()` | Adapter para `NDLModel::SaveOptions` $\to$ `WriteOptions`. |

## 7. Contrato de Interface
```cpp
// src/document/document_save_manager.h
class DocumentSaveManager : public QObject {
public:
    // ... structs SaveEncryptionParams, SavePageRange, WriteOptions, SaveResult ...

    // Binário: ArtDoc::Document::Save(path, WriteOptions)
    SaveResult save(const QString& destinationPath, const WriteOptions& options);

    // Binário: NDLModel::SaveDocument (entrada de aplicação)
    SaveResult saveDocument(const QString& destinationPath, const WriteOptions& options);

    // Derivação de caminho de backup (binário: FUN_180095230)
    static QString deriveBackupPath(const QString& destinationPath);

    // RevertToSaved (binário: 0x180099690) — TODO(F-006)
    bool revertToSaved();

signals:
    void progressStatus(const QString& status);
    void finished(const SaveResult& result);
};
```

## 8. Limitações
- **Formato Binário `.artplus`:** Não derivado; o sistema reusa o Serializer JSON e marca a paridade binária como `TODO(F-006)`.
- **Criptografia:** Suporte em v1 é apenas em retorno de erro explícito; não escreve *plaintext* se senha for fornecida (Regra: Nada de stub silencioso).
- **Flavors 1 & 2:** Implementações para Preflight (1) e Separações (2) retornam `SaveException(8)` se solicitadas, sem lógica de processamento de domínio.
- **Assincronia:** Chamada assíncrona (`QFuture<SaveResult>`) permanece como `TODO(F-006)` devido à não thread-safety do `Document`.
- **Ambiguidades da Spec:** Semântica de `NoOptimizedSave` e nome exato de backup (`FUN_180095230`) permanecem abertos (ver §8.1 a 8.5 da Spec F-006).

## Estado
proposto