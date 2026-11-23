#pragma once

#include "../document/document_model.h"
#include <QVector>
#include <QRectF>
#include <QTransform>
#include <memory>

namespace ArtPlus {

class ImpositionEngine {
public:
    enum class Type {
        None = 0,
        Sheetwise = 1,      // 2-up sheetwise
        WorkAndTurn = 2,    // 2-up work and turn
        WorkAndTumble = 3,  // 2-up work and tumble
        HalfFold = 4,       // 2-up half fold (booklet)
        QuarterFold = 5,    // 4-up quarter fold
        EightFold = 6,      // 8-up
        SixteenFold = 7,    // 16-up
        CutStack = 8,       // Cut stack imposition
        Custom = 99
    };
    
    enum class Binding {
        None = 0,
        SaddleStitch = 1,
        PerfectBind = 2,
        Spiral = 3,
        WireO = 4
    };
    
    struct Settings {
        Type type = Type::Sheetwise;
        Binding binding = Binding::None;
        
        // Sheet
        QSizeF sheetSize;           // mm
        QSizeF pageSize;            // mm
        QMarginsF margins;          // mm
        float bleed = 3.0f;         // mm
        
        // Pages
        int pagesPerSheet = 2;      // 2, 4, 8, 16, etc.
        int totalPages = 0;         // 0 = auto from document
        int signatureSize = 0;      // 0 = auto (4, 8, 16, 32)
        
        // Gaps
        float horizontalGap = 5.0f;  // mm
        float verticalGap = 5.0f;    // mm
        
        // Marks
        bool addCropMarks = true;
        bool addRegistrationMarks = true;
        bool addColorBars = false;
        bool addPageNumbers = false;
        bool addCutMarks = false;
        float markWeight = 0.3f;    // pt
        float markOffset = 3.0f;    // mm
        
        // Creasing
        bool addCreaseMarks = false;
        float creaseOffset = 0.0f;  // from fold line
        
        // Binding
        float bindingMargin = 0.0f;  // mm (gutter)
        bool compensateCreep = true;  // for saddle stitch
        
        // Shingling/Creep
        float creepPerPage = 0.0f;   // mm per page
        float maxCreep = 0.0f;
        
        // Bottling (for work and tumble)
        bool bottlePages = false;
        
        // Output
        bool createCutFile = false;  // Separate cut file
        bool separateSignatures = false;
    };
    
    struct Signature {
        int number = 0;
        int pages = 0;
        QVector<int> pageOrder;      // Page indices in imposition order
        QRectF sheetRect;
        QVector<QTransform> pageTransforms;
        QVector<QRectF> pageRects;
    };
    
    struct Result {
        QVector<Signature> signatures;
        int totalSheets = 0;
        QSizeF sheetSize;
        QString error;
        bool success = false;
        
        // For preview
        QVector<QRectF> pageRects;
        QVector<QTransform> pageTransforms;
    };
    
    struct Preview {
        QVector<QRectF> sheetRects;
        QVector<QVector<QRectF>> signaturePageRects;
        int totalSheets = 0;
        int totalSignatures = 0;
    };
    
    ImpositionEngine();
    ~ImpositionEngine();
    
    void setSettings(const Settings& settings);
    const Settings& settings() const;
    
    // Main imposition
    Result impose(Document& document);
    
    // Preview without modifying document
    Preview preview(const Document& document) const;
    
    // Calculate imposition plan without applying
    struct Plan {
        int signatures = 0;
        int sheetsPerSignature = 0;
        int totalSheets = 0;
        int pagesPerSignature = 0;
        int blankPages = 0;
        QVector<int> pageOrder;  // Page indices in final order
    };
    
    Plan calculatePlan(const Document& document) const;
    
    // Apply imposition to document (modifies page order, adds marks)
    bool applyToDocument(Document& document);
    
    // Generate imposed pages as new document
    std::unique_ptr<Document> createImposedDocument(const Document& source) const;
    
    // Specific imposition types
    Result imposeSheetwise(const Document& document) const;
    Result imposeWorkAndTurn(const Document& document) const;
    Result imposeWorkAndTumble(const Document& document) const;
    Result imposeHalfFold(const Document& document) const;
    Result imposeQuarterFold(const Document& document) const;
    Result imposeCutStack(const Document& document) const;
    
    // Marks generation
    struct MarksSettings {
        bool crop = true;
        bool registration = true;
        bool colorBars = false;
        bool pageNumbers = false;
        bool cutMarks = false;
        float weight = 0.3f;    // pt
        float offset = 3.0f;    // mm
        QColor color = Qt::black;
    };
    
    void addMarks(Document& document, const MarksSettings& settings) const;
    
    // Creep compensation
    void applyCreepCompensation(Document& document) const;
    
    // Shingling for saddle stitch
    void applyShingling(Document& document) const;
    
    // Custom imposition from template
    struct Template {
        QString name;
        QString description;
        Settings settings;
        QVector<QTransform> pageTransforms;  // For custom layouts
    };
    
    void saveTemplate(const QString& name, const Template& tmpl);
    void loadTemplate(const QString& name);
    void deleteTemplate(const QString& name);
    QStringList templateNames() const;
    Template templateData(const QString& name) const;
    
    // PDF export with imposition
    bool exportImposedPDF(const Document& document, const QString& path, bool includeMarks = true) const;
    
private:
    struct Private;
    std::unique_ptr<Private> d;
};

namespace ImpositionUtils {
    // Page ordering for different imposition types
    QVector<int> calculatePageOrder(int totalPages, int pagesPerSheet, ImpositionEngine::Type type);
    
    // Sheetwise (2-up)
    QVector<int> sheetwiseOrder(int pages);
    
    // Work and Turn (2-up, front/back same plate)
    QVector<int> workAndTurnOrder(int pages);
    
    // Work and Tumble (2-up, head-to-head)
    QVector<int> workAndTumbleOrder(int pages);
    
    // Half fold (booklet, saddle stitch)
    QVector<int> halfFoldOrder(int pages);
    
    // Quarter fold (4-up booklet)
    QVector<int> quarterFoldOrder(int pages);
    
    // Cut stack
    QVector<int> cutStackOrder(int pages, int sheets);
    
    // Signature calculation
    int calculateSignatures(int pages, int signatureSize);
    int calculateSheets(int pages, int pagesPerSheet);
    
    // Creep calculation
    float calculateCreep(int pageIndex, int totalPages, float paperThickness, float creepPerPage);
    
    // Shingling calculation
    float calculateShingling(int pageIndex, int signaturePages, float paperThickness);
    
    // Transform generation
    QTransform pageTransform(int pageIndex, int pagesPerSheet, const QSizeF& pageSize, const QSizeF& sheetSize, 
                            const QMarginsF& margins, float hGap, float vGap);
    
    // Marks generation
    struct MarksData {
        QVector<QLineF> cropMarks;
        QVector<QPointF> registrationMarks;
        QVector<QRectF> colorBars;
        QVector<QPointF> pageNumberPositions;
    };
    
    MarksData generateMarks(const QRectF& pageRect, const QSizeF& sheetSize, 
                           const ImpositionEngine::MarksSettings& settings);
    
    // Creep/shingling application
    void applyCreep(QVector<QTransform>& transforms, float paperThickness, float creepPerPage);
    void applyShingling(QVector<QTransform>& transforms, float paperThickness);
}

} // namespace ArtPlus