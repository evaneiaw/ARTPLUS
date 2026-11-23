#pragma once

#include "../document/document_model.h"
#include <QVector>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <functional>
#include <memory>

namespace ArtPlus {

class ActionListEngine {
public:
    struct Result {
        bool success = false;
        QString error;
        int actionsExecuted = 0;
        int actionsFailed = 0;
    };
    
    enum class ActionType {
        // Document operations
        NewDocument = 0,
        OpenDocument = 1,
        SaveDocument = 2,
        ExportPDF = 3,
        
        // Selection
        SelectAll = 10,
        DeselectAll = 11,
        SelectObjects = 12,
        SelectByColor = 13,
        SelectByLayer = 14,
        SelectByType = 15,
        InvertSelection = 16,
        
        // Transform
        Move = 20,
        Scale = 21,
        Rotate = 22,
        Skew = 23,
        FlipHorizontal = 24,
        FlipVertical = 25,
        
        // Editing
        Delete = 30,
        Duplicate = 31,
        Copy = 32,
        Paste = 33,
        Cut = 34,
        Group = 35,
        Ungroup = 35,
        
        // Production
        StepRepeat = 40,
        Imposition = 41,
        Marks = 42,
        CutCreaseLines = 43,
        Trapping = 44,
        Separations = 45,
        
        // Color
        ConvertColor = 50,
        ApplyProfile = 51,
        Simulate = 52,
        
        // View
        Zoom = 60,
        Pan = 61,
        FitPage = 62,
        NextPage = 63,
        PrevPage = 64,
        
        // Automation
        Wait = 70,
        Message = 71,
        Condition = 72,
        Loop = 73,
        CallActionList = 74,
        
        // File
        Import = 80,
        Export = 81,
        Print = 82,
        
        Custom = 999
    };
    
    struct Action {
        ActionType type = ActionType::Custom;
        QString name;
        QString description;
        QJsonObject parameters;
        bool enabled = true;
        bool continueOnError = false;
        int repeatCount = 1;
        int delayMs = 0;
        
        QJsonObject toJson() const;
        static Action fromJson(const QJsonObject& obj);
    };
    
    struct ActionList {
        QString name;
        QString description;
        QString author;
        QDateTime created;
        QDateTime modified;
        QString version;
        QVector<Action> actions;
        QStringList tags;
        
        QJsonDocument toJson() const;
        static ActionList fromJson(const QJsonDocument& doc);
        
        bool isValid() const;
        QString validationError() const;
    };
    
    struct ExecutionResult {
        bool success = false;
        QString error;
        int actionsExecuted = 0;
        int actionsFailed = 0;
        QDateTime startTime;
        QDateTime endTime;
        QVector<QString> log;
        
        QString summary() const;
    };
    
    struct ExecutionContext {
        Document* document = nullptr;
        QVector<ObjectId> selection;
        QMap<QString, QVariant> variables;
        bool stopRequested = false;
        std::function<void(int progress, const QString& message)> progressCallback;
        std::function<bool()> shouldStop;
    };
    
    ActionListEngine();
    ~ActionListEngine();
    
    // Recording
    void startRecording(const QString& name = "Untitled");
    void stopRecording();
    bool isRecording() const;
    QString recordingName() const;
    ActionList recordedList() const;
    
    // Playback
    Result play(const ActionList& list, ExecutionContext& context);
    Result playAction(const Action& action, ExecutionContext& context);
    
    // Management
    void saveList(const ActionList& list, const QString& path);
    ActionList loadList(const QString& path);
    bool deleteList(const QString& path);
    QStringList listFiles() const;
    
    // Variables
    void setVariable(const QString& name, const QVariant& value);
    QVariant getVariable(const QString& name) const;
    void clearVariables();
    
    // Built-in actions
    static QStringList availableActions();
    static Action createAction(ActionType type, const QJsonObject& params = {});
    
    // Validation
    struct ValidationResult {
        bool valid = false;
        QStringList errors;
        QStringList warnings;
    };
    
    ValidationResult validate(const ActionList& list) const;
    
    // Batch processing
    struct BatchResult {
        int total = 0;
        int succeeded = 0;
        int failed = 0;
        QVector<QString> errors;
        QDateTime startTime;
        QDateTime endTime;
    };
    
    BatchResult batchProcess(const ActionList& list, const QStringList& files, ExecutionContext& context);
    
    // Undo integration
    void setUndoStack(class UndoStack* stack);
    
    // Progress
    using ProgressCallback = std::function<void(int progress, const QString& message)>;
    void setProgressCallback(std::function<void(int, const QString&)> callback);
    
private:
    struct Private;
    std::unique_ptr<Private> d;
};

} // namespace ArtPlus