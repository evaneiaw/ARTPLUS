#pragma once

#include "../document/document_model.h"
#include <QVector>
#include <QColor>
#include <QRectF>
#include <memory>

namespace ArtPlus {

class TrappingEngine {
public:
    struct Settings {
        // General
        float defaultWidth = 0.3f;      // mm
        float maxWidth = 2.0f;          // mm
        float minWidth = 0.05f;         // mm
        
        // Color thresholds
        float colorDifferenceThreshold = 10.0f;  // DeltaE
        float neutralDensityThreshold = 0.1f;
        
        // Step & Repeat
        bool trapStepRepeat = true;
        float stepRepeatTrapWidth = 0.15f;  // mm
        
        // Images
        bool trapImages = false;
        float imageTrapWidth = 0.2f;        // mm
        
        // Text
        bool trapText = true;
        float textTrapWidth = 0.1f;         // mm
        float minFontSizeForTrap = 6.0f;    // pt
        
        // Lines
        bool trapLines = true;
        float lineTrapWidth = 0.1f;         // mm
        float minLineWidthForTrap = 0.2f;   // mm
        
        // Overprint
        bool respectOverprint = true;
        bool trapOverprintObjects = false;
        
        // Performance
        int maxTrapObjects = 10000;
        float gridSize = 5.0f;  // mm
        
        // Advanced
        bool useColorManagement = true;
        float blackThreshold = 0.9f;  // K > 0.9 is "black"
        float whiteThreshold = 0.1f;  // All < 0.1 is "white"
        
        // Trapping methods
        enum class Method {
            Spread = 0,      // Lighter spreads into darker
            Choke = 1,       // Darker chokes into lighter
            Centerline = 2,  // Centered on edge
            Auto = 3         // Automatic based on colors
        };
        Method defaultMethod = Method::Auto;
    };
    
    struct TrapZone {
        QRectF bounds;
        QVector<QVector<QPointF>> contours;  // Trap polygons
        QColor color;
        float width;
        bool isSpread;
        uint32_t objectId;
    };
    
    struct Result {
        QVector<TrapZone> traps;
        int objectsProcessed = 0;
        int trapsCreated = 0;
        QString error;
        bool success = false;
    };
    
    TrappingEngine();
    ~TrappingEngine();
    
    void setSettings(const Settings& settings);
    const Settings& settings() const;
    
    // Main trapping function
    Result calculateTraps(Document& document, PageId pageId);
    
    // Analyze without creating traps
    struct Analysis {
        int edgesAnalyzed = 0;
        int trapCandidates = 0;
        int colorTransitions = 0;
        float maxColorDifference = 0.0f;
        QString report;
    };
    
    Analysis analyzeTrapping(const Document& document, PageId pageId) const;
    
    // Manual trap creation
    bool addManualTrap(const QVector<QPointF>& polygon, const QColor& color, float width, bool isSpread);
    bool removeManualTrap(uint32_t trapId);
    QVector<TrapZone> manualTraps() const;
    
    // Black/White trapping
    struct BlackWhiteRules {
        float blackLimit = 0.9f;
        float blackWidth = 0.3f;
        float whiteLimit = 0.1f;
        float whiteWidth = 0.1f;
        bool chokeBlack = true;
        bool spreadWhite = true;
    };
    
    void setBlackWhiteRules(const BlackWhiteRules& rules);
    const BlackWhiteRules& blackWhiteRules() const;
    
    // Step & Repeat specific
    Result trapStepRepeat(const QVector<ObjectId>& baseObjects, int copiesX, int copiesY, float spacingX, float spacingY);
    
    // Color management integration
    void setColorManager(class ColorManager* manager);
    
    // Progress callback
    using ProgressCallback = std::function<void(int progress, const QString& message)>;
    void setProgressCallback(ProgressCallback callback);
    
private:
    struct Private;
    std::unique_ptr<Private> d;
};

namespace TrapUtils {
    // Color analysis
    float colorDifference(const QColor& c1, const QColor& c2);
    bool isBlack(const QColor& color, float threshold = 0.9f);
    bool isWhite(const QColor& color, float threshold = 0.1f);
    bool isNeutral(const QColor& color, float threshold = 0.1f);
    
    // Edge detection
    struct Edge {
        QPointF p1, p2;
        QColor color1, color2;
        float angle;
        float length;
        bool isHorizontal() const;
        bool isVertical() const;
    };
    
    QVector<Edge> findEdges(const QVector<QPointF>& polygon1, const QVector<QPointF>& polygon2);
    
    // Trap generation
    QVector<QPointF> createSpread(const QVector<QPointF>& edge, float width, const QColor& lighterColor);
    QVector<QPointF> createChoke(const QVector<QPointF>& edge, float width, const QColor& darkerColor);
    QVector<QPointF> createCenterline(const QVector<QPointF>& edge, float width, const QColor& color);
    
    // Trap width calculation
    float calculateTrapWidth(const QColor& c1, const QColor& c2, float defaultWidth, float maxWidth, float minWidth);
    
    // Overprint handling
    bool shouldOverprint(const QColor& top, const QColor& bottom, float blackThreshold = 0.9f);
    
    // Shape operations
    QVector<QPointF> offsetPolygon(const QVector<QPointF>& poly, float distance);
    QVector<QPointF> polygonDifference(const QVector<QPointF>& subject, const QVector<QPointF>& clip);
    QVector<QPointF> polygonUnion(const QVector<QPointF>& a, const QVector<QPointF>& b);
}

} // namespace ArtPlus