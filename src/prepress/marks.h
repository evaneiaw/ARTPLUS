#pragma once

#include "../document/document_model.h"
#include <QVector>
#include <QRectF>
#include <QColor>
#include <QFont>
#include <memory>

namespace ArtPlus {

// Mark settings structures (moved out of MarksEngine for visibility in MarksUtils)
struct MarkCropSettings {
    bool enabled = true;
    float weight = 0.3f;
    float offset = 3.0f;
    float length = 8.0f;
    bool doubleLines = false;
    float doubleGap = 1.0f;  // mm
    QColor color = Qt::black;
};

struct MarkRegistrationSettings {
    bool enabled = true;
    float weight = 0.25f;
    float size = 6.0f;       // mm diameter
    float offset = 5.0f;
    QColor color = Qt::black;
    bool circle = true;
    bool crosshair = true;
};

struct MarkColorBarSettings {
    bool enabled = false;
    float height = 10.0f;    // mm
    float offset = 5.0f;
    int patches = 12;         // Number of patches
    float patchWidth = 5.0f;  // mm
    float gap = 0.5f;         // mm between patches
    QVector<QColor> customColors;  // Custom patch colors
    bool showLabels = true;
    float fontSize = 4.0f;   // pt
    enum Position { BottomCenter, BottomLeft, BottomRight, TopCenter, TopLeft, TopRight };
    Position position = Position::BottomCenter;
};

struct MarkPageNumberSettings {
    bool enabled = false;
    float fontSize = 6.0f;   // pt
    QFont font;
    QColor color = Qt::black;
    QString format = "{page}";  // {page}, {total}, {section}
    float offset = 5.0f;
    enum Position { BottomCenter, BottomLeft, BottomRight, TopCenter, TopLeft, TopRight };
    Position position = Position::BottomCenter;
};

// TODO(F-001): superseded by CutMark / CutMarkParams (ADR-001, D1) for the
// dynamic `Add Cut Mark` object (DynamicObject_PDFPlusCutMark). This preset
// struct keeps its defaults (offset 2.0 mm) untouched for the static preset
// path only; do not extend it for the dynamic mark.
struct MarkCutMarkSettings {
    bool enabled = false;
    float weight = 0.25f;
    float length = 5.0f;
    float offset = 2.0f;
    QColor color = Qt::red;
    enum Style { Single, Double, Corner };
    Style style = Style::Single;
};

// TODO(F-002): superseded by MarkSetProcessor (ADR-012)
// MarksEngine is kept for static preset marks (crop, registration, color bar, etc.)
// Dynamic mark set workflow (Document > Marks panel, Load/Save Mark Set, ApplyRelevantMarkSets)
// is handled by MarkSetProcessor and DocumentMarksPanel.

struct MarkCreaseMarkSettings {
    bool enabled = false;
    float weight = 0.2f;
    float length = 10.0f;
    float offset = 0.0f;
    QColor color = Qt::blue;
    enum Style { Dash, Dot, DashDot, DoubleDash };
    Style style = Style::Dash;
};

struct MarkFoldMarkSettings {
    bool enabled = false;
    float weight = 0.2f;
    float length = 8.0f;
    float offset = 0.0f;
    QColor color = Qt::green;
    enum Style { Arrow, Tick, Line };
    Style style = Style::Arrow;
};

struct MarkBleedMarkSettings {
    bool enabled = false;
    float weight = 0.2f;
    float length = 4.0f;
    QColor color = Qt::magenta;
};

struct MarkColorBarPatchesSettings {
    bool enabled = false;
    int patches = 12;
    float width = 5.0f;       // mm
    float height = 10.0f;     // mm
    float gap = 0.5f;         // mm
    float offset = 5.0f;
    QVector<QColor> colors;   // Custom colors, empty = standard
};

struct MarkGrayBalanceSettings {
    bool enabled = false;
    float size = 3.0f;        // mm
    float offset = 3.0f;
};

struct MarkResolutionTargetSettings {
    bool enabled = false;
    float size = 10.0f;       // mm
    float offset = 5.0f;
};

struct MarkSlurGaugeSettings {
    bool enabled = false;
    float size = 10.0f;
    float offset = 5.0f;
};

struct MarkStarTargetSettings {
    bool enabled = false;
    float size = 15.0f;       // mm
    float offset = 5.0f;
    int rays = 12;
};

struct MarkCustomMark {
    QString name;
    QVector<QPointF> path;
    float weight = 0.3f;
    QColor color = Qt::black;
    bool filled = false;
    QColor fillColor = Qt::transparent;
};

class MarksEngine {
public:
    enum class MarkType {
        Crop = 0,
        Registration = 1,
        ColorBar = 2,
        PageNumber = 2,
        CutMark = 3,
        CreaseMark = 4,
        FoldMark = 5,
        BleedMark = 6,
        TrimMark = 7,
        CenterMark = 8,
        ColorBarPatches = 9,
        GrayBalance = 10,
        ResolutionTarget = 11,
        SlurGauge = 12,
        StarTarget = 13,
        Custom = 99
    };
    
    struct MarkSettings {
        // Common
        bool enabled = true;
        float weight = 0.3f;       // pt
        float offset = 3.0f;       // mm from page edge
        QColor color = Qt::black;
        float length = 8.0f;       // mm
        
        // Individual mark settings
        MarkCropSettings crop;
        MarkRegistrationSettings registration;
        MarkColorBarSettings colorBar;
        MarkPageNumberSettings pageNumber;
        MarkCutMarkSettings cutMark;
        MarkCreaseMarkSettings creaseMark;
        MarkFoldMarkSettings foldMark;
        MarkBleedMarkSettings bleedMark;
        MarkColorBarPatchesSettings colorBarPatches;
        MarkGrayBalanceSettings grayBalance;
        MarkResolutionTargetSettings resolutionTarget;
        MarkSlurGaugeSettings slurGauge;
        MarkStarTargetSettings starTarget;
    };
    
    struct Preset {
        QString name;
        MarkSettings settings;
    };
    
    MarksEngine();
    ~MarksEngine();
    
    void setSettings(const MarkSettings& settings);
    const MarkSettings& settings() const;
    
    // Apply marks to page
    struct Result {
        QVector<ObjectId> createdObjects;
        int marksCreated = 0;
        QString error;
        bool success = false;
    };
    
    Result applyMarks(Document& document, PageId pageId);
    Result applyMarksToAllPages(Document& document);
    Result applyMarksToRange(Document& document, int startPage, int endPage);
    
    // Specific mark types
    struct CropResult {
        QVector<ObjectId> marks;
        QRectF pageBounds;
    };
    
    CropResult addCropMarks(Document& document, PageId pageId, const MarkCropSettings& settings);
    
    struct RegistrationResult {
        QVector<ObjectId> marks;
        QVector<QPointF> positions;
    };
    
    RegistrationResult addRegistrationMarks(Document& document, PageId pageId, const MarkRegistrationSettings& settings);
    
    struct ColorBarResult {
        QVector<ObjectId> patches;
        QVector<ObjectId> labels;
        QRectF bounds;
    };
    
    ColorBarResult addColorBar(Document& document, PageId pageId, const MarkColorBarSettings& settings);
    
    struct PageNumberResult {
        ObjectId textObject;
        QRectF bounds;
    };
    
    PageNumberResult addPageNumber(Document& document, PageId pageId, int pageNumber, int totalPages, const MarkPageNumberSettings& settings);
    
    struct MarksResult {
        QVector<ObjectId> marks;
    };
    
    MarksResult addCutMarks(Document& document, PageId pageId, const MarkCutMarkSettings& settings);
    MarksResult addCreaseMarks(Document& document, PageId pageId, const MarkCreaseMarkSettings& settings);
    MarksResult addFoldMarks(Document& document, PageId pageId, const MarkFoldMarkSettings& settings);
    MarksResult addBleedMarks(Document& document, PageId pageId, const MarkBleedMarkSettings& settings);
    MarksResult addColorBarPatches(Document& document, PageId pageId, const MarkColorBarPatchesSettings& settings);
    MarksResult addGrayBalance(Document& document, PageId pageId, const MarkGrayBalanceSettings& settings);
    MarksResult addResolutionTarget(Document& document, PageId pageId, const MarkResolutionTargetSettings& settings);
    MarksResult addSlurGauge(Document& document, PageId pageId, const MarkSlurGaugeSettings& settings);
    MarksResult addStarTarget(Document& document, PageId pageId, const MarkStarTargetSettings& settings);
    
    // Apply all enabled marks
    Result applyAllMarks(Document& document, PageId pageId);
    Result applyAllMarksToDocument(Document& document);
    
    // Presets
    void savePreset(const QString& name);
    void loadPreset(const QString& name);
    void deletePreset(const QString& name);
    QStringList presetNames() const;
    MarkSettings preset(const QString& name) const;
    
    // Standard presets
    static MarkSettings standardOffsetPreset();
    static MarkSettings standardDigitalPreset();
    static MarkSettings standardFlexoPreset();
    static MarkSettings standardScreenPreset();
    static MarkSettings standardGravurePreset();
    
    // Color management
    void setColorManager(class ColorManager* manager);
    
    // Custom mark creation
    ObjectId addCustomMark(Document& document, PageId pageId, const QPointF& position, const MarkCustomMark& mark);
    
private:
    struct Private;
    std::unique_ptr<Private> d;
};

namespace MarksUtils {
    // Geometry
    QVector<QPointF> createCropMark(const QRectF& pageRect, float offset, float length, bool doubleLines, float doubleGap);
    QVector<QPointF> createRegistrationMark(const QPointF& center, float size, bool circle, bool crosshair);
    QVector<QVector<QPointF>> createColorBarPatches(int count, float width, float height, float gap, const QVector<QColor>& colors);
    QVector<QPointF> createCutMark(const QPointF& corner, const QPointF& direction, float length, float weight, MarkCutMarkSettings::Style style);
    QVector<QPointF> createCreaseMark(const QPointF& start, const QPointF& end, float weight, MarkCreaseMarkSettings::Style style);
    QVector<QPointF> createFoldMark(const QPointF& center, const QPointF& direction, float length, MarkFoldMarkSettings::Style style);
    QVector<QPointF> createBleedMark(const QRectF& pageRect, float bleed, float length);
    QVector<QVector<QPointF>> createColorBarPatches(int count, float width, float height, float gap, const QVector<QColor>& colors);
    QVector<QPointF> createGrayBalance(float size);
    QVector<QPointF> createResolutionTarget(float size);
    QVector<QPointF> createSlurGauge(float size);
    QVector<QPointF> createStarTarget(float size, int rays);
    
    // Positioning
    QVector<QPointF> cropMarkPositions(const QRectF& pageRect, float offset);
    QVector<QPointF> registrationMarkPositions(const QRectF& pageRect, float offset);
    QPointF colorBarPosition(const QRectF& pageRect, float offset, MarkColorBarSettings::Position position);
    QPointF pageNumberPosition(const QRectF& pageRect, float offset, MarkPageNumberSettings::Position position);
    QVector<QPointF> cutMarkPositions(const QRectF& pageRect, float offset);
    QVector<QPointF> creaseMarkPositions(const QVector<QLineF>& foldLines, float offset);
    QPointF colorBarPosition(const QRectF& pageRect, const MarkColorBarSettings& settings);
    
    // Drawing
    ObjectId createLineMark(Document& document, PageId pageId, const QVector<QPointF>& points, float weight, const QColor& color, MarkCreaseMarkSettings::Style style = MarkCreaseMarkSettings::Style::Dash);
    ObjectId createPathMark(Document& document, PageId pageId, const QVector<QPointF>& points, float weight, const QColor& color, bool closed = false);
    ObjectId createTextMark(Document& document, PageId pageId, const QString& text, const QPointF& position, const QFont& font, const QColor& color);
    
    // Color patches
    QColor standardPatchColor(int index, int total);
    QVector<QColor> standardColorBarColors(int count);
    QVector<QColor> grayBalanceColors();
    QVector<QColor> standardResolutionTarget();
    
    // Measurement
    float pointsToMm(float points);
    float mmToPoints(float mm);
}

} // namespace ArtPlus