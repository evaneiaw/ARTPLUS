#pragma once

#include "document_model.h"
#include <QObject>
#include <QString>
#include <QJsonObject>
#include <vector>
#include <stdexcept>
#include <memory> // Para std::shared_ptr

namespace ArtPlus {

enum class SaveFlavour {
    NormalPdf = 0,   // PDF normal
    Preflight = 1,   // preflight (Flavour == 1)
    Separations = 2  // separações (Flavour == 2)
};

struct SaveEncryptionParams {
    int encryptionLevel = 0;          // 0 = sem criptografia
    QString ownerPassword;            // senha owner (texto plano em memória; convertida na borda)
    QString userPassword;             // senha user
};

struct SavePageRange {
    int firstPage = 0;   // 0-based, inclusivo
    int lastPage = 0;    // 0-based, inclusivo
    bool allPages = true;
};

struct WriteOptions {
    // Flags espelhando ArtDoc::WriteOptions (+0x60..+0x71)
    bool isSaveAs = false;
    bool isSaveAsCopy = false;
    bool isSaveUnmodified = false;
    bool needBackupOnSave = false;
    bool isIncrementalSave = false;
    bool noOptimizedSave = false;     // true => desabilita otimização

    SaveFlavour flavour = SaveFlavour::NormalPdf;

    std::vector<SavePageRange> pageRanges; // vazio => todas as páginas

    SaveEncryptionParams encryption;

    // Adapter a partir de SaveOptions (NDLModel) — TODO(F-006): refinar leitura
    // do basic_string_view de origem (GHIDRA-NDLModel-0x180042a40).
    static WriteOptions fromSaveOptions(const QString& /*source*/);
};

class SaveException : public std::runtime_error {
public:
    explicit SaveException(int code, const std::string& what)
        : std::runtime_error(what), code_(code) {}
    int code() const noexcept { return code_; }
private:
    int code_;
};

struct SaveResult {
    bool ok = false;
    QString filePath;          // caminho efetivamente gravado
    QString backupPath;        // caminho do backup (vazio se não houve)
    int errorCode = 0;         // código SaveException, se aplicável
    QString errorMessage;      // mensagem para UI (português técnico)
};

class DocumentSaveManager : public QObject {
    Q_OBJECT
public:
    explicit DocumentSaveManager(Document& doc, QObject* parent = nullptr);

    // Binário: ArtDoc::Document::Save(path, WriteOptions)
    SaveResult save(const QString& destinationPath, const WriteOptions& options);

    // Binário: NDLModel::SaveDocument (entrada de aplicação)
    SaveResult saveDocument(const QString& destinationPath, const WriteOptions& options);

    // Derivação de caminho de backup (binário: FUN_180095230) — provisória
    static QString deriveBackupPath(const QString& destinationPath);

    // RevertToSaved (binário: 0x180099690) — TODO(F-006)
    bool revertToSaved();

signals:
    void progressStatus(const QString& status);   // STATUS_SAVE / STATUS_OPTIMIZING / STATUS_WRITING_TO_DISK
    void finished(const SaveResult& result);

private:
    Document& doc_;
    bool switchToWorkingFile();                  // binário: SwitchToWorkingFile
    bool applyEncryption(const SaveEncryptionParams&);  // binário: Security::GetEncryption/GetPassword + SetNew* (TODO)
    void finalizeState(const QString& path, const WriteOptions& opts); // SetDirty/SetFilePath/...
};

} // namespace ArtPlus
