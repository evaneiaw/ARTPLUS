#include "document_save_manager.h"
#include "document_serializer.h"
#include <QFileInfo>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

namespace ArtPlus {

// static
WriteOptions WriteOptions::fromSaveOptions(const QString& /*source*/) {
    // TODO(F-006): Refinar leitura do basic_string_view de origem
    // (GHIDRA-NDLModel-0x180042a40). Por enquanto, retorna default.
    qWarning() << "TODO(F-006): WriteOptions::fromSaveOptions not implemented. Returning default.";
    return {};
}

DocumentSaveManager::DocumentSaveManager(Document& doc, QObject* parent)
    : QObject(parent)
    , doc_(doc)
{}

SaveResult DocumentSaveManager::save(const QString& destinationPath, const WriteOptions& options) {
    SaveResult result;
    result.filePath = destinationPath;

    // E1: The original file could not be copied to the working file, so saving <path> is impossible
    // TODO(F-006): Implement SwitchToWorkingFile() and error check (binário: this+0x78 == 2)
    if (!switchToWorkingFile()) {
        result.errorMessage = "Erro (TODO F-006): O arquivo original não pôde ser copiado para o arquivo de trabalho.";
        result.errorCode = 8; // SaveException(8)
        emit finished(result);
        return result;
    }

    // R1: Detecção de caminho (Save vs Save As)
    const QFileInfo destinationInfo(destinationPath);
    bool isSaveAs = options.isSaveAs;
    // E5: destino inexistente (status < 2) força IsSaveAs == true.
    // Precisa vir antes da comparação por canonicalFilePath(): dois caminhos
    // inexistentes devolvem "" e comparariam iguais.
    if (!destinationInfo.exists()) {
        isSaveAs = true;
    }
    if (doc_.filePath().isEmpty() || QFileInfo(doc_.filePath()).canonicalFilePath() != destinationInfo.canonicalFilePath()) {
        isSaveAs = true;
    }

    // ADR-006 D5 / R4.1: Criptografia não implementada
    // R5.2/E8: retorna ANTES de qualquer escrita — nenhum backup/cópia/rename/
    // gravação do destino pode ocorrer neste caminho de erro.
    if (options.encryption.encryptionLevel != 0) {
        result.errorMessage = "Erro (TODO F-006): Criptografia não é suportada nesta versão.";
        emit finished(result);
        return result;
    }
    // TODO(F-006): applyEncryption(options.encryption) (binário: Security::GetEncryption/GetPassword + SetNew*)
    if (!applyEncryption(options.encryption)) {
        // Error from applyEncryption (e.g. invalid password, though not implemented yet)
        result.errorMessage = "Erro (TODO F-006): Falha ao aplicar parâmetros de criptografia.";
        emit finished(result);
        return result;
    }

    // R2.2: Flavour == 1 (preflight) ou Flavour == 2 (separações): ramos dedicados sem incremental.
    // ADR-006 Risco: Ramos retornam erro explícito SaveException(8) (paridade com E3)
    // E9: nenhuma gravação/backup — retorno anterior a qualquer escrita no destino.
    if (options.flavour != SaveFlavour::NormalPdf) {
        result.errorMessage = QString("Erro (TODO F-006): O tipo de salvamento '%1' não é suportado nesta versão.").arg(static_cast<int>(options.flavour));
        result.errorCode = 8; // SaveException(8)
        emit finished(result);
        return result;
    }

    // R3: Backup / renomeação
    // R3.1: Backup ativado quando IsSaveAs == false e NeedBackupOnSave == true
    // R3.5: Se IsSaveAs == true → nenhum backup
    // Rastreio do backup feito por rename(): guarda o caminho do backup só quando o
    // original foi MOVIDO (R3.4). Nesse caso o destino fica ausente até o serializer
    // gravar; se ele falhar (E10) o original precisa voltar para o destino.
    QString renamedBackupPath;
    if (!isSaveAs && !options.needBackupOnSave) {
        // No backup: neither SaveAs nor backup requested
    } else if (!isSaveAs && options.needBackupOnSave) {
        result.backupPath = deriveBackupPath(destinationPath);
        QFile currentFile(destinationPath);
        if (!currentFile.exists()) {
            qInfo() << "Document: Destination does not exist, no backup needed.";
        } else {
            if (options.isIncrementalSave) {
                // R3.3: copy_file(destino, backup, ...) (preserva o arquivo original em backup).
                if (!currentFile.copy(result.backupPath)) {
                    qWarning() << "Document: Could not copy the incremental base file to " << result.backupPath << " (error: " << currentFile.errorString() << ")";
                    // E2: Falha em copy_file da base incremental — fluxo continua sem throw
                    result.errorMessage = "Aviso (TODO F-006): Falha ao copiar base incremental para backup.";
                }
            } else {
                // R3.4: rename(destino, backup, ...) (move o original para backup).
                if (!currentFile.rename(result.backupPath)) {
                    qWarning() << "Document: Could not rename original file to backup " << result.backupPath << " (error: " << currentFile.errorString() << ")";
                    result.errorMessage = "Aviso (TODO F-006): Falha ao renomear arquivo original para backup.";
                } else {
                    // O destino não existe mais; o original está em result.backupPath.
                    renamedBackupPath = result.backupPath;
                }
            }
        }
    }

    // R2.3: Montagem de GADocSaveParams para a gravação - noOptimizedSave (1 = otimizar)
    // TODO(F-006): noOptimizedSave, semântica exata. Por enquanto, só registra a flag.
    if (options.noOptimizedSave) {
        qDebug() << "TODO(F-006): Saving without optimization is requested.";
    }

    emit progressStatus("STATUS_SAVE");
    // R4.2: GODocument::Save (gravação proprietária substituída pelo serializer JSON existente)
    // Salvamento incremental mínimo: se isIncrementalSave e NoOptimizedSave → salvar direto via DocumentSerializer existente.
    // isIncrementalSave=true e destino inexistente: forçado a false. O DocumentSerializer::save já é 'completo'.
    bool incrementalActuallyApplied = options.isIncrementalSave;
    if (options.isIncrementalSave && !QFile::exists(destinationPath)) {
        incrementalActuallyApplied = false; // Cannot be incremental if no base exists
        qDebug() << "Incremental save requested but destination does not exist. Proceeding with full save.";
    }

    // Save As: sempre salva completo (não incremental)
    if (isSaveAs) {
        incrementalActuallyApplied = false;
    }

    // NOTE: DocumentSerializer::save always performs a full save, not an incremental one.
    // The incremental flag in options is mostly for the *backup* logic in v1.
    if (!DocumentSerializer::save(doc_, destinationPath)) {
        result.errorCode = 8; // Genérico SaveException(8)
        // E4: Disco cheio / permissão negada / caminho inválido
        // TODO(F-006): Mensagens de exceção de UI não observadas.
        //
        // E10 + needBackupOnSave — decisão de ROBUSTEZ declarada, não paridade com o
        // original: no backup não-incremental o original foi movido para <dest>.bak
        // ANTES do serializer (R3.4), então uma falha daqui deixaria o destino AUSENTE
        // (o usuário veria o arquivo "sumir"). Aqui o original volta para o destino.
        if (!renamedBackupPath.isEmpty()) {
            const QString failedBackupPath = renamedBackupPath;
            bool restored = true;
            // O serializer pode ter deixado um arquivo parcial no destino; este nunca é
            // o original (que está em .bak), então pode ser descartado para o rename.
            const QFileInfo destinationAfterFailure(destinationPath);
            if (destinationAfterFailure.isFile()) {
                QFile partialFile(destinationPath);
                if (!partialFile.remove()) {
                    qWarning() << "Document: E10 rollback could not remove partial destination "
                               << destinationPath << "(error: " << partialFile.errorString() << ")";
                    restored = false;
                }
            }
            if (restored && !QFile::rename(failedBackupPath, destinationPath)) {
                qWarning() << "Document: E10 rollback failed. Original content kept at backup "
                           << failedBackupPath;
                restored = false;
            }
            if (restored) {
                qInfo() << "Document: E10 rollback restored the original file to " << destinationPath
                        << "from " << failedBackupPath;
                result.errorMessage = "Erro (TODO F-006): Falha na serialização do documento; "
                                      "o arquivo original foi restaurado a partir do backup.";
                // O backup foi consumido pelo rollback: não há mais arquivo de backup.
                result.backupPath.clear();
            } else {
                // Rollback impossível: dizer exatamente onde está o original.
                result.errorMessage = QString("Erro (TODO F-006): Falha na serialização do documento "
                                              "e o rollback do backup falhou. O conteúdo original está "
                                              "em '%1' e o destino '%2' não foi restaurado.")
                                          .arg(failedBackupPath, destinationPath);
                result.backupPath = failedBackupPath;
            }
        } else {
            result.errorMessage = "Erro (TODO F-006): Falha na serialização do documento.";
            // Backup incremental (R3.3, copy_file): o destino original NUNCA foi movido,
            // por isso não há rollback e o destino não é apagado. O .bak pode permanecer
            // (result.backupPath continua preenchido quando ele foi criado).
        }
        emit finished(result);
        return result;
    }

    emit progressStatus("STATUS_WRITING_TO_DISK");

    // Finalização
    finalizeState(destinationPath, options);

    result.ok = true;
    emit finished(result);
    return result;
}

SaveResult DocumentSaveManager::saveDocument(const QString& destinationPath, const WriteOptions& options) {
    // ADR-006 D3: NDLModel::SaveDocument (entrada de aplicação) mapeia para save()
    // TODO(F-006): Na v1 a execução é síncrona; a variante assíncrona (saveDocumentAsync → QFuture<SaveResult>)
    // fica como TODO(F-006) para documentos grandes.
    qWarning() << "TODO(F-006): saveDocument is synchronous. Consider implementing async version.";
    return save(destinationPath, options);
}

// static
QString DocumentSaveManager::deriveBackupPath(const QString& destinationPath) {
    // TODO(F-006): Conteúdo de FUN_180095230 (prefixo/sufixo, extensão).
    // Por enquanto, provisório: <dest>.bak
    qWarning() << "TODO(F-006): deriveBackupPath is provisional. Using .bak extension.";
    return destinationPath + ".bak";
}

bool DocumentSaveManager::revertToSaved() {
    qWarning() << "TODO(F-006): revertToSaved not implemented.";
    return false;
}

bool DocumentSaveManager::switchToWorkingFile() {
    // SwitchToWorkingFile: copia o documento original para um arquivo temporário de trabalho.
    // E1 (this+0x78 == 2) é falha REAL de cópia do original para o working file e só se
    // aplica quando existe arquivo de origem. Documento ainda não salvo (sem filePath,
    // ex.: File > New) não tem nada a copiar — não é E1: o save prossegue como Save As.
    if (doc_.filePath().isEmpty()) {
        qDebug() << "DocumentSaveManager: No source file (document never saved), nothing to copy to working file.";
        return true;
    }
    // Simula a cópia do arquivo original para um arquivo temporário de trabalho.
    qDebug() << "DocumentSaveManager: Switched to working file successfully (simulated).";
    return true;
}

bool DocumentSaveManager::applyEncryption(const SaveEncryptionParams& params) {
    // ADR-006 D5: Criptografia não é suportada em v1, retorna erro explícito.
    if (params.encryptionLevel != 0) {
        qWarning() << "Encryption is not supported. Returning false.";
        return false;
    }
    return true;
}

void DocumentSaveManager::finalizeState(const QString& path, const WriteOptions& opts) {
    // R4.4: Finalização: SetDirty(false), SetFilePath, SwitchToWorkingFile,
    // StatusReporting::ProgressFinalize, ChangeCollector::NotifyChangesCollected.
    // E6/E7: Em Save As Copy / Save Unmodified o dirty state e o caminho podem não ser atualizados.

    if (!opts.isSaveAsCopy && !opts.isSaveUnmodified) {
        doc_.setFilePath(path);
        doc_.setModified(false);
    }

    // TODO(F-006): Implementar SwitchToWorkingFile novamente se necessário.
    // Emitir sinal de finalização de progresso
    emit progressStatus("PROGRESS_FINALIZE");

    // TODO(F-006): Implementar ChangeCollector::NotifyChangesCollected.
}

} // namespace ArtPlus
