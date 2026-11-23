#pragma once

#include "../document/document_model.h"
#include <QVector>
#include <QRectF>
#include <QTransform>
#include <memory>

namespace ArtPlus {

class PackagingEngine {
public:
    enum class Type {
        Carton = 0,
        Corrugated = 1,
        Flexible = 2,
        Label = 3,
        Sleeve = 4,
        Tray = 5,
        Box = 6,
        Custom = 99
    };
    
    enum class LineType {
        Cut = 0,           // Cut line
        Crease = 1,        // Crease/fold line
        Perf = 2,          // Perforation
        Score = 3,         // Score line
        CutCrease = 4,     // Combination
        HalfCut = 5,       // Half cut (kiss cut)
        ThroughCut = 6,    // Through cut
        KissCut = 7,       // Kiss cut (through face, not liner)
        DieCut = 8,        // Die cut shape
        Emboss = 9,        // Emboss area
        Deboss = 10,       // Deboss area
        Foil = 11,         // Foil stamp area
        SpotUV = 12,       // Spot UV area
        Braille = 13,      // Braille area
        Custom = 99
    };
    
    struct LineProperties {
        LineType type = LineType::Cut;
        float weight = 0.3f;           // pt
        QColor color = Qt::red;        // Cut = red, Crease = blue, etc.
        Qt::PenStyle style = Qt::SolidLine;
        QVector<float> dashPattern;    // For dashed lines
        float miterLimit = 4.0f;
        
        // Identification
        QString name;
        QString layer;                  // Layer name
        int order = 0;                  // Processing order
        
        // Technical
        float knifeAngle = 45.0f;       // degrees
        float bevelAngle = 0.0f;
        float gap = 0.0f;               // For perf/score
        float depth = 0.0f;             // For emboss/deboss
        float pressure = 0.0f;          // For foil/emboss
        
        // Tolerances
        float tolerance = 0.1f;         // mm
        float angleTolerance = 0.5f;    // degrees
        
        // Production
        int station = 1;                // Die station
        int pass = 1;                   // Pass number
        bool required = true;           // Mandatory
        QString notes;
    };
    
    struct Dieline {
        QString name;
        QVector<ObjectId> lines;
        QRectF bounds;
        QTransform transform;
        int station = 1;
        int passes = 1;
        
        // Structural
        QString boardGrade;
        float boardThickness = 0.0f;    // mm
        float boardWeight = 0.0f;       // gsm
        float fluteHeight = 0.0f;       // mm (for corrugated)
        
        // Production
        int stations = 1;
        int tools = 1;
        float maxSpeed = 0.0f;          // m/min
        float tolerance = 0.1f;         // mm
    };
    
    struct Settings {
        // Document
        float bleed = 3.0f;             // mm
        float boardThickness = 0.5f;    // mm
        float boardWeight = 300.0f;     // gsm
        
        // Identification
        float lineWeight = 0.3f;        // pt
        float identificationGap = 2.0f;  // mm
        bool labelLines = true;
        
        // Colors (standard Esko)
        QColor cutColor = QColor(255, 0, 0);       // Red
        QColor creaseColor = QColor(0, 0, 255);    // Blue
        QColor perfColor = QColor(0, 255, 0);      // Green
        QColor scoreColor = QColor(255, 165, 0);   // Orange
        QColor halfCutColor = QColor(128, 0, 128); // Purple
        QColor kissCutColor = QColor(0, 255, 255); // Cyan
        QColor embossColor = QColor(255, 20, 147); // Deep pink
        QColor debossColor = QColor(139, 69, 19);  // Saddle brown
        
        // Tolerances
        float positionTolerance = 0.1f;  // mm
        float angleTolerance = 0.5f;     // degrees
        float lengthTolerance = 0.1f;    // mm
        
        // Production
        float knifeAngle = 45.0f;        // degrees
        float knifeHeight = 23.8f;       // mm
        float knifeBevel = 0.0f;         // mm
        int stations = 1;
        
        // Validation
        float minLineLength = 0.5f;      // mm
        float minAngle = 5.0f;           // degrees
        float maxLineLength = 1000.0f;   // mm
        float minRadius = 0.5f;          // mm
        
        // Output
        bool exportDXF = true;
        bool exportCF2 = true;
        bool separateFiles = false;
    };
    
    struct DielineResult {
        QVector<ObjectId> lines;
        QVector<ObjectId> annotations;
        QRectF bounds;
        QString name;
        QString error;
        bool success = false;
    };
    
    struct ValidationResult {
        bool valid = false;
        QStringList errors;
        QStringList warnings;
        int totalLines = 0;
        float totalLength = 0.0f;
        int cutLines = 0;
        int creaseLines = 0;
        int perfLines = 0;
        float totalCutLength = 0.0f;
        float totalCreaseLength = 0.0f;
        float totalPerfLength = 0.0f;
    };
    
    struct ExportResult {
        QString dxfPath;
        QString cf2Path;
        QString error;
        bool success = false;
    };
    
    PackagingEngine();
    ~PackagingEngine();
    
    void setSettings(const Settings& settings);
    const Settings& settings() const;
    
    // Identification
    struct IdentificationResult {
        QVector<ObjectId> cutLines;
        QVector<ObjectId> creaseLines;
        QVector<ObjectId> perfLines;
        QVector<ObjectId> otherLines;
        int totalIdentified = 0;
        QString error;
        bool success = false;
    };
    
    IdentificationResult identifyLines(const Document& document, PageId pageId);
    IdentificationResult identifyLinesInSelection(const Document& document, const QVector<ObjectId>& objectIds);
    
    // Conversion
    struct ConversionResult {
        QVector<ObjectId> converted;
        int convertedCount = 0;
        QString error;
        bool success = false;
    };
    
    ConversionResult convertToCut(Document& document, const QVector<ObjectId>& lineIds);
    ConversionResult convertToCrease(Document& document, const QVector<ObjectId>& lineIds);
    ConversionResult convertToPerf(Document& document, const QVector<ObjectId>& lineIds);
    ConversionResult convertToLineType(Document& document, const QVector<ObjectId>& lineIds, LineType type);
    
    // Creation
    struct CreationResult {
        ObjectId objectId;
        bool success = false;
        QString error;
    };
    
    CreationResult createCutLine(Document& document, PageId pageId, const QVector<QPointF>& points);
    CreationResult createCreaseLine(Document& document, PageId pageId, const QVector<QPointF>& points);
    CreationResult createPerfLine(Document& document, PageId pageId, const QVector<QPointF>& points, float gap = 1.0f);
    CreationResult createDieline(Document& document, PageId pageId, const QVector<QVector<QPointF>>& contours, const QString& name = "Dieline");
    
    // Dieline operations
    DielineResult createDielineFromShape(Document& document, PageId pageId, ObjectId shapeId, const QString& name = "");
    DielineResult offsetDieline(Document& document, const QVector<ObjectId>& dielineIds, float offset);
    DielineResult mergeDielines(Document& document, const QVector<ObjectId>& dielineIds, const QString& name = "");
    DielineResult splitDieline(Document& document, ObjectId dielineId, float position);
    
    // Validation
    ValidationResult validateDieline(const Document& document, const QVector<ObjectId>& dielineIds);
    ValidationResult validateDielineForProduction(const Document& document, const QVector<ObjectId>& dielineIds);
    
    // Separation
    struct SeparationResult {
        QVector<ObjectId> artObjects;
        QVector<ObjectId> cutLines;
        QVector<ObjectId> creaseLines;
        QVector<ObjectId> otherLines;
        QString error;
        bool success = false;
    };
    
    SeparationResult separateArtAndKnife(const Document& document, PageId pageId);
    SeparationResult separateByColor(const Document& document, PageId pageId, const QColor& cutColor, const QColor& creaseColor);
    SeparationResult separateByLayer(const Document& document, PageId pageId, const QString& cutLayer, const QString& creaseLayer);
    
    // Export
    ExportResult exportDXF(const Document& document, const QVector<ObjectId>& dielineIds, const QString& path);
    ExportResult exportCF2(const Document& document, const QVector<ObjectId>& dielineIds, const QString& path);
    ExportResult exportAll(const Document& document, const QVector<ObjectId>& dielineIds, const QString& basePath);
    
    // Board/Structural
    struct BoardSpec {
        QString grade;           // e.g., "FBB", "SBS", "F-Flute"
        float thickness = 0.0f;  // mm
        float weight = 0.0f;     // gsm
        float stiffness = 0.0f;  // mN.m
        QString flute;           // A, B, C, E, F, N, etc.
        float fluteHeight = 0.0f;
        int flutesPerMeter = 0;
    };
    
    struct StructuralAnalysis {
        float blankSize[2];       // Width, Height
        float blankArea = 0.0f;
        float materialUsage = 0.0f;
        float wastePercentage = 0.0f;
        int panels = 0;
        float totalCreaseLength = 0.0f;
        float totalCutLength = 0.0f;
        float estimatedWeight = 0.0f;
        QString errors;
        QString warnings;
    };
    
    StructuralAnalysis analyzeStructure(const Document& document, PageId pageId, const BoardSpec& board);
    
    // Nesting
    struct NestingResult {
        QVector<QTransform> transforms;
        QRectF sheetBounds;
        int partsPerSheet = 0;
        int sheetsRequired = 0;
        float utilization = 0.0f;
    };
    
    struct NestingSettings {
        QSizeF sheetSize;
        float spacing = 5.0f;
        float margin = 10.0f;
        bool allowRotation = true;
        int maxRotations = 4;
        bool allowMirroring = false;
        int maxParts = 100;
    };
    
    NestingResult nestDielines(const QVector<QRectF>& dielineBounds, const NestingSettings& settings);
    
    // Presets
    struct Preset {
        QString name;
        Settings settings;
    };
    
    void savePreset(const QString& name);
    void loadPreset(const QString& name);
    void deletePreset(const QString& name);
    QStringList presetNames() const;
    Settings preset(const QString& name) const;
    
    // Standard presets
    static Settings standardCartonPreset();
    static Settings standardCorrugatedPreset();
    static Settings standardLabelPreset();
    static Settings standardFlexiblePreset();
    
    // Board database
    struct BoardDatabase {
        struct Board {
            QString name;
            QString grade;
            float thickness;
            float weight;
            QString flute;
            float fluteHeight;
        };
        
        QVector<Board> boards;
        void addBoard(const Board& board);
        void removeBoard(const QString& name);
        Board board(const QString& name) const;
        QStringList boardNames() const;
    };
    
    BoardDatabase boardDatabase() const;
    void setBoardDatabase(const BoardDatabase& db);
    
private:
    struct Private;
    std::unique_ptr<Private> d;
};

namespace PackagingUtils {
    // Line identification
    PackagingEngine::LineType identifyLineType(const QColor& color, float weight, const QVector<float>& dashPattern);
    PackagingEngine::LineType identifyByLayer(const QString& layerName);
    PackagingEngine::LineType identifyByName(const QString& name);
    
    // Geometry
    QVector<QPointF> simplifyPath(const QVector<QPointF>& points, float tolerance);
    QVector<QPointF> smoothPath(const QVector<QPointF>& points, float factor);
    QVector<QPointF> offsetPath(const QVector<QPointF>& points, float offset);
    QVector<QVector<QPointF>> offsetPaths(const QVector<QVector<QPointF>>& paths, float offset);
    
    // Validation
    bool isClosedPath(const QVector<QPointF>& points, float tolerance = 0.01f);
    float pathLength(const QVector<QPointF>& points);
    float pathArea(const QVector<QPointF>& points);
    bool isClockwise(const QVector<QPointF>& points);
    QVector<QPointF> ensureClockwise(QVector<QPointF> points);
    QVector<QPointF> ensureCounterClockwise(QVector<QPointF> points);
    
    // Path operations
    QVector<QVector<QPointF>> pathUnion(const QVector<QVector<QPointF>>& paths);
    QVector<QVector<QPointF>> pathDifference(const QVector<QVector<QPointF>>& subject, const QVector<QVector<QPointF>>& clip);
    QVector<QVector<QPointF>> pathIntersection(const QVector<QVector<QPointF>>& a, const QVector<QVector<QPointF>>& b);
    
    // Corner/Vertex analysis
    struct Corner {
        QPointF point;
        float angle;
        bool isConvex;
        int index;
    };
    
    QVector<Corner> findCorners(const QVector<QPointF>& points, float angleTolerance = 5.0f);
    bool isSharpCorner(const Corner& corner, float minAngle = 5.0f);
    float cornerRadius(const QVector<QPointF>& points, int index, int neighbors = 2);
    
    // Measurement
    float totalLength(const QVector<QVector<QPointF>>& paths);
    float totalCutLength(const QVector<QVector<QPointF>>& paths, const QVector<PackagingEngine::LineType>& types);
    float totalCreaseLength(const QVector<QVector<QPointF>>& paths, const QVector<PackagingEngine::LineType>& types);
    QRectF boundingBox(const QVector<QVector<QPointF>>& paths);
    
    // Export formats
    QString toDXF(const QVector<QVector<QPointF>>& paths, const QVector<PackagingEngine::LineType>& types, const QColor& paperColor = Qt::white);
    QString toCF2(const QVector<QVector<QPointF>>& paths, const QVector<PackagingEngine::LineType>& types);
    
    // Board calculations
    float calculateBlankSize(float width, float height, float thickness, int panels);
    float calculateMaterialUsage(const QVector<QVector<QPointF>>& dielines, float boardThickness, float sheetWidth, float sheetHeight);
    float calculateWaste(float sheetArea, float usedArea);
    int calculatePanelsPerSheet(const QRectF& dielineBounds, const QSizeF& sheetSize, float spacing, float margin);
}

} // namespace ArtPlus