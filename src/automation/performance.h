#pragma once

#include <QObject>
#include <QString>
#include <QMap>
#include <QVector>
#include <QDateTime>
#include <chrono>
#include <memory>

namespace ArtPlus {

class PerformanceMonitor : public QObject {
    Q_OBJECT
    
public:
    struct Metrics {
        // Time
        double totalTime = 0.0;
        double renderTime = 0.0;
        double layoutTime = 0.0;
        double scriptTime = 0.0;
        double ioTime = 0.0;
        
        // Memory
        size_t currentMemory = 0;
        size_t peakMemory = 0;
        size_t allocatedObjects = 0;
        size_t freedObjects = 0;
        
        // Counts
        int framesRendered = 0;
        int objectsCreated = 0;
        int objectsDestroyed = 0;
        int commandsExecuted = 0;
        int undoRedoOperations = 0;
        
        // Document
        int documentSize = 0;
        int pageCount = 0;
        int layerCount = 0;
        int objectCount = 0;
        
        QString toString() const;
        QVariantMap toMap() const;
    };
    
    struct Timer {
        QString name;
        std::chrono::high_resolution_clock::time_point start;
        double elapsed = 0.0;
        int count = 0;
    };
    
    static PerformanceMonitor& instance();
    
    // Timing
    void startTimer(const QString& name);
    double stopTimer(const QString& name);
    double timerValue(const QString& name) const;
    void resetTimer(const QString& name);
    void resetAllTimers();
    
    // Counters
    void incrementCounter(const QString& name, int value = 1);
    int counterValue(const QString& name) const;
    void resetCounter(const QString& name);
    void resetAllCounters();
    
    // Memory
    void recordAllocation(size_t size);
    void recordDeallocation(size_t size);
    void recordObjectCreation();
    void recordObjectDestruction();
    
    // Document metrics
    void updateDocumentMetrics(int pageCount, int layerCount, int objectCount, int documentSize);
    
    // Metrics access
    Metrics currentMetrics() const;
    void resetMetrics();
    
    // Profiling
    struct ProfileSession {
        QString name;
        QDateTime startTime;
        QDateTime endTime;
        Metrics startMetrics;
        Metrics endMetrics;
        QMap<QString, Timer> timers;
        QMap<QString, int> counters;
    };
    
    void startProfile(const QString& name);
    void endProfile(const QString& name);
    QVector<ProfileSession> profiles() const;
    void clearProfiles();
    
    // Reporting
    QString generateReport() const;
    QString generateJSONReport() const;
    void saveReport(const QString& path) const;
    
    // Alerts
    struct Alert {
        QString name;
        QString message;
        QDateTime time;
        Metrics metrics;
        enum Level { Info, Warning, Critical } level;
    };
    
    using AlertCallback = std::function<void(const Alert&)>;
    void setAlertCallback(AlertCallback callback);
    void setMemoryLimit(size_t bytes);
    void setTimeLimit(const QString& timer, double seconds);
    
    // Automatic monitoring
    void startMonitoring(int intervalMs = 1000);
    void stopMonitoring();
    bool isMonitoring() const;
    
    // Comparison
    struct Comparison {
        Metrics baseline;
        Metrics current;
        QMap<QString, double> differences;
        QMap<QString, double> percentChanges;
        QString summary;
    };
    
    Comparison compare(const Metrics& baseline, const Metrics& current) const;
    
    // Export/Import
    bool saveMetrics(const QString& path) const;
    bool loadMetrics(const QString& path);
    
signals:
    void metricsUpdated(const Metrics& metrics);
    void alertTriggered(const QString& name, const QString& message, int level);
    void profileCompleted(const QString& name);
    void thresholdExceeded(const QString& name, double value, double limit);
    
private:
    PerformanceMonitor();
    ~PerformanceMonitor();
    
    struct Private;
    std::unique_ptr<Private> d;
    
    friend class PerformanceScope;
};

class PerformanceScope {
public:
    explicit PerformanceScope(const QString& name);
    ~PerformanceScope();
    
private:
    QString m_name;
};

class MemoryTracker {
public:
    static void* allocate(size_t size);
    static void deallocate(void* ptr, size_t size);
    static void* reallocate(void* ptr, size_t oldSize, size_t newSize);
    
    static size_t totalAllocated();
    static size_t peakAllocated();
    static int allocationCount();
    
    static void reset();
    
    // Custom allocator for STL containers
    template<typename T>
    class Allocator {
    public:
        using value_type = T;
        
        Allocator() noexcept = default;
        template<typename U>
        Allocator(const Allocator<U>&) noexcept {}
        
        T* allocate(size_t n) {
            return static_cast<T*>(allocate(n * sizeof(T)));
        }
        
        void deallocate(T* p, size_t n) {
            deallocate(p, n * sizeof(T));
        }
        
        template<typename U>
        bool operator==(const Allocator<U>&) const noexcept { return true; }
        
        template<typename U>
        bool operator!=(const Allocator<U>&) const noexcept { return false; }
    };
};

class Profiler {
public:
    static void beginFrame();
    static void endFrame();
    
    static void beginSection(const QString& name);
    static void endSection(const QString& name);
    
    struct FrameData {
        double totalTime = 0.0;
        QMap<QString, double> sections;
        int drawCalls = 0;
        int triangles = 0;
        int textureBinds = 0;
        size_t memoryUsed = 0;
    };
    
    static FrameData lastFrame();
    static QVector<FrameData> frameHistory(int count = 60);
    static void clearHistory();
    static void setHistorySize(int frames);
    
    static QString report();
    static QString jsonReport();
};

class DocumentProfiler {
public:
    struct DocumentStats {
        int pages = 0;
        int layers = 0;
        int objects = 0;
        int paths = 0;
        int texts = 0;
        int images = 0;
        int groups = 0;
        int masks = 0;
        
        size_t estimatedMemory = 0;
        double complexity = 0.0;
        
        QMap<QString, int> objectsByLayer;
        QMap<QString, int> objectsByType;
        QMap<QString, int> colorsUsed;
    };
    
    static DocumentStats analyze(class Document* document);
    static QString report(const DocumentStats& stats);
    static bool validate(class Document* document, QStringList& errors);
    
    static bool checkConsistency(class Document* document, QStringList& issues);
    static bool checkIntegrity(class Document* document, QStringList& issues);
    
    // Performance recommendations
    struct Recommendation {
        QString category;
        QString description;
        QString action;
        int priority;  // 1=low, 2=medium, 3=high
    };
    
    static QVector<Recommendation> recommend(const DocumentStats& stats);
};

} // namespace ArtPlus