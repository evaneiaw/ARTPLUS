#pragma once

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QMap>
#include <functional>
#include <memory>

namespace ArtPlus {

class Document;

class RecoveryManager : public QObject {
    Q_OBJECT
    
public:
    enum class RecoveryType {
        AutoSave = 0,
        CrashRecovery = 1,
        ManualBackup = 2,
        VersionHistory = 3,
        CloudSync = 4
    };
    
    enum class RecoveryStatus {
        Idle = 0,
        Saving = 1,
        Restoring = 2,
        Validating = 3,
        Error = 4
    };
    
    struct AutoSaveSettings {
        bool enabled = true;
        int intervalMinutes = 5;
        int maxBackups = 10;
        QString backupDirectory;
        bool compressBackups = true;
        bool incrementalBackups = false;
        int maxBackupSizeMB = 100;
        
        // Triggers
        bool saveOnIdle = true;
        int idleTimeoutSeconds = 30;
        bool saveBeforeRiskyOperations = true;
        bool saveOnDocumentSwitch = true;
    };
    
    struct BackupInfo {
        QString id;
        QString filePath;
        QString originalPath;
        QDateTime timestamp;
        qint64 size = 0;
        QString description;
        RecoveryType type;
        QString documentName;
        int pageCount = 0;
        int objectCount = 0;
        bool compressed = false;
        QString checksum;
        QStringList tags;
    };
    
    struct RecoveryResult {
        bool success = false;
        QString restoredPath;
        QString error;
        QDateTime recoveredFrom;
        int objectsRestored = 0;
        int pagesRestored = 0;
    };
    
    struct ValidationResult {
        bool valid = false;
        QStringList errors;
        QStringList warnings;
        QStringList missingResources;
        QStringList corruptObjects;
        bool canRecover = false;
    };
    
    struct HealthReport {
        QDateTime timestamp;
        QString documentPath;
        bool valid = false;
        int corruptionLevel = 0;  // 0=none, 1=minor, 2=moderate, 3=severe
        QStringList issues;
        QStringList recoverableIssues;
        QStringList fatalIssues;
        qint64 fileSize = 0;
        QString checksum;
        int pageCount = 0;
        int objectCount = 0;
        int layerCount = 0;
        int version = 0;
        QStringList missingResources;
        QStringList missingFonts;
        QStringList missingImages;
        QStringList corruptObjects;
        QStringList corruptLayers;
    };
    
    RecoveryManager();
    ~RecoveryManager();
    
    void setSettings(const AutoSaveSettings& settings);
    const AutoSaveSettings& settings() const;
    
    // Auto-save
    void startAutoSave();
    void stopAutoSave();
    bool isAutoSaveRunning() const;
    void triggerAutoSave(const QString& reason = "Auto-save");
    void forceSave();
    
    // Backup management
    QString createBackup(RecoveryType type = RecoveryType::ManualBackup, const QString& description = "");
    bool deleteBackup(const QString& backupId);
    void cleanupOldBackups();
    
    QVector<BackupInfo> listBackups() const;
    QVector<BackupInfo> listBackupsForDocument(const QString& documentPath) const;
    BackupInfo backupInfo(const QString& backupId) const;
    
    // Recovery
    RecoveryResult restoreBackup(const QString& backupId, const QString& targetPath = "");
    RecoveryResult restoreLatestBackup(const QString& documentPath);
    RecoveryResult recoverFromCrash();
    
    // Validation
    ValidationResult validateDocument(const QString& filePath);
    ValidationResult validateBackup(const QString& backupId);
    ValidationResult validateDocumentIntegrity(class Document* document);
    
    // Health monitoring
    HealthReport checkHealth(const QString& filePath);
    HealthReport checkDocumentHealth(class Document* document);
    
    QVector<HealthReport> healthHistory(const QString& documentPath) const;
    void clearHealthHistory(const QString& documentPath);
    
    // Version history
    struct VersionInfo {
        QString id;
        QDateTime timestamp;
        QString description;
        QString author;
        int objectCount = 0;
        int pageCount = 0;
        QString parentVersion;
    };
    
    QVector<VersionInfo> versionHistory(const QString& documentPath) const;
    QString createVersion(const QString& documentPath, const QString& description);
    bool restoreVersion(const QString& documentPath, const QString& versionId);
    bool deleteVersion(const QString& documentPath, const QString& versionId);
    
    // Corruption repair
    struct RepairResult {
        bool success = false;
        int objectsRepaired = 0;
        int objectsRemoved = 0;
        int pagesRepaired = 0;
        QStringList recoveredObjects;
        QStringList lostObjects;
        QString error;
    };
    
    RepairResult repairDocument(const QString& filePath, const QString& outputPath = "");
    RepairResult repairDocument(class Document* document);
    
    struct RepairOptions {
        bool removeCorruptObjects = true;
        bool repairCorruptPaths = true;
        bool fixInvalidTransforms = true;
        bool fixInvalidColors = true;
        bool fixInvalidText = true;
        bool removeEmptyObjects = true;
        bool fixLayerReferences = true;
        bool fixPageReferences = true;
        bool rebuildIndices = true;
        bool validateGeometry = true;
        float maxRepairDistance = 0.1f;  // mm
    };
    
    RepairResult repairWithOptions(class Document* document, const RepairOptions& options);
    
    // Cloud sync (placeholder for future)
    struct SyncResult {
        bool success = false;
        QString remotePath;
        QString error;
        QDateTime timestamp;
    };
    
    SyncResult syncToCloud(const QString& documentPath);
    SyncResult syncFromCloud(const QString& documentPath);
    bool isCloudSyncEnabled() const;
    void setCloudSyncEnabled(bool enabled);
    void setCloudCredentials(const QString& provider, const QString& credentials);
    
    // Settings persistence
    void saveSettings();
    void loadSettings();
    
    // Status
    RecoveryStatus status() const;
    QString statusMessage() const;
    QDateTime lastAutoSave() const;
    QDateTime lastBackup() const;
    int pendingOperations() const;
    
    // Callbacks
    using ProgressCallback = std::function<void(int progress, const QString& message)>;
    using StatusCallback = std::function<void(RecoveryStatus, const QString&)>;
    using AlertCallback = std::function<void(const QString&, int level)>;  // level: 0=info, 1=warning, 2=error
    
    void setProgressCallback(std::function<void(int, const QString&)> callback);
    void setStatusCallback(StatusCallback callback);
    void setAlertCallback(AlertCallback callback);
    
signals:
    void autoSaveStarted();
    void autoSaveCompleted(const QString& backupId);
    void autoSaveFailed(const QString& error);
    void backupCreated(const QString& backupId);
    void backupRestored(const QString& backupId);
    void recoveryStarted();
    void recoveryCompleted(const QString& path);
    void recoveryFailed(const QString& error);
    void healthCheckCompleted(const QString& path, bool healthy);
    void corruptionDetected(const QString& path, int level);
    void statusChanged(RecoveryStatus status, const QString& message);
    
private:
    struct Private;
    std::unique_ptr<Private> d;
    
    friend class RecoveryScope;
};

class RecoveryScope {
public:
    explicit RecoveryScope(const QString& operation);
    ~RecoveryScope();
    
    void setDescription(const QString& desc);
    void setProgress(int percent, const QString& message);
    
private:
    QString m_operation;
    QDateTime m_startTime;
};

class DocumentValidator {
public:
    struct ValidationContext {
        bool checkGeometry = true;
        bool checkColors = true;
        bool checkText = true;
        bool checkImages = true;
        bool checkFonts = true;
        bool checkLinks = true;
        bool checkLayers = true;
        bool checkPages = true;
        bool checkReferences = true;
        bool checkTransforms = true;
        bool checkBounds = true;
        bool checkDuplicates = true;
        bool checkOrphans = true;
    };
    
    struct ValidationResult {
        bool valid = false;
        QStringList errors;
        QStringList warnings;
        QStringList info;
        int checkedItems = 0;
        int errorCount = 0;
        int warningCount = 0;
        double score = 0.0;  // 0.0 - 1.0
    };
    
    static ValidationResult validate(class Document* document, const ValidationContext& context);
static ValidationResult validate(class Document* document);
    static ValidationResult validateFile(const QString& filePath);
    static ValidationResult validateBackup(const QString& backupPath);
    
    // Specific checks
    static QStringList checkGeometry(class Document* document);
    static QStringList checkColors(class Document* document);
    static QStringList checkText(class Document* document);
    static QStringList checkImages(class Document* document);
    static QStringList checkFonts(class Document* document);
    static QStringList checkLinks(class Document* document);
    static QStringList checkLayers(class Document* document);
    static QStringList checkPages(class Document* document);
    static QStringList checkReferences(class Document* document);
    static QStringList checkTransforms(class Document* document);
    static QStringList checkBounds(class Document* document);
    static QStringList checkDuplicates(class Document* document);
    static QStringList checkOrphans(class Document* document);
    
    // Repair suggestions
    static QStringList suggestRepairs(const QStringList& errors);
    
    // Integrity hash
    static QString calculateHash(class Document* document);
    static bool verifyHash(class Document* document, const QString& expectedHash);
    
    // Consistency
    static bool checkConsistency(class Document* document, QStringList& issues);
    static bool checkIntegrity(class Document* document, QStringList& issues);
    
    // Comparison
    static QStringList compare(class Document* doc1, class Document* doc2);
    static QStringList differences(class Document* doc1, class Document* doc2);
};

class CrashRecovery {
public:
    struct CrashInfo {
        QDateTime timestamp;
        QString documentPath;
        QString crashReason;
        QString stackTrace;
        QString systemInfo;
        QString userActions;
        QString recoveredFiles;
    };
    
    static CrashInfo lastCrashInfo();
    static void saveCrashInfo(const CrashInfo& info);
    static void clearCrashHistory();
    static QVector<CrashInfo> crashHistory();
    
    // Recovery
    static QStringList recoverableDocuments();
    static QString recoverDocument(const QString& tempPath, const QString& targetPath);
    static bool verifyRecovered(const QString& path);
    
    // Temp files
    static QString tempDirectory();
    static void cleanupTempFiles();
    static QStringList tempFiles();
    
    // Auto-recovery
    static bool shouldRecover(const QString& documentPath);
    static QString autoRecoverPath(const QString& documentPath);
    static bool attemptAutoRecovery(const QString& documentPath);
};

} // namespace ArtPlus