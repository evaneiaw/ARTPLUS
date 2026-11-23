#pragma once

#include "../document/document_model.h"
#include <QVector>
#include <QRectF>
#include <QTransform>
#include <memory>

namespace ArtPlus {

class StepRepeatEngine {
public:
    struct Settings {
        // Grid
        int copiesX = 3;
        int copiesY = 3;
        float spacingX = 50.0f;  // mm
        float spacingY = 50.0f;  // mm
        float angle = 0.0f;      // degrees
        
        // Offsets
        float offsetX = 0.0f;
        float offsetY = 0.0f;
        bool alternateOffset = false;  // Staggered grid
        float alternateOffsetX = 0.0f;
        float alternateOffsetY = 0.0f;
        
        // Margins
        float marginLeft = 10.0f;
        float marginTop = 10.0f;
        float marginRight = 10.0f;
        float marginBottom = 10.0f;
        
        // Options
        bool cloneObjects = true;           // Create copies
        bool mergeIntoGroup = false;        // Group all copies
        bool preserveLayers = true;         // Keep original layers
        bool trapBetweenCopies = false;     // Trap between copies
        float trapWidth = 0.15f;            // mm
        
        // Preview
        bool showPreview = true;
        float previewOpacity = 0.5f;
        
        // Limits
        int maxCopies = 1000;
        float maxSpacing = 1000.0f;
    };
    
    struct Result {
        QVector<ObjectId> createdObjects;
        int copiesCreated = 0;
        QRectF boundingBox;
        QString error;
        bool success = false;
    };
    
    struct Preview {
        QVector<QRectF> copyBounds;
        QVector<QTransform> transforms;
        QRectF totalBounds;
    };
    
    StepRepeatEngine();
    ~StepRepeatEngine();
    
    void setSettings(const Settings& settings);
    const Settings& settings() const;
    
    // Main execution
    Result execute(Document& document, const QVector<ObjectId>& objectIds);
    
    // Preview without creating
    Preview preview(const Document& document, const QVector<ObjectId>& objectIds) const;
    
    // Single copy
    ObjectId createCopy(Document& document, ObjectId objectId, const QTransform& transform);
    
    // Circular step & repeat
    struct CircularSettings {
        int count = 8;
        float radius = 50.0f;
        float startAngle = 0.0f;
        float angleStep = 45.0f;
        bool rotateObjects = true;
        QPointF center;
    };
    
    Result executeCircular(Document& document, const QVector<ObjectId>& objectIds, const CircularSettings& settings);
    
    // Mirror step & repeat
    struct MirrorSettings {
        bool horizontal = true;
        bool vertical = false;
        float gap = 0.0f;
    };
    
    Result executeMirror(Document& document, const QVector<ObjectId>& objectIds, const MirrorSettings& settings);
    
    // Nested step & repeat (step & repeat of step & repeat)
    struct NestedSettings {
        Settings outer;
        Settings inner;
    };
    
    Result executeNested(Document& document, const QVector<ObjectId>& objectIds, const NestedSettings& settings);
    
    // Preview without execution
    struct PreviewInfo {
        int totalCopies = 0;
        QRectF totalBounds;
        float totalArea = 0.0f;
        QVector<QRectF> copyBounds;
    };
    
    PreviewInfo previewInfo(const Document& document, const QVector<ObjectId>& objectIds) const;
    
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
    
    // Undo integration
    void setUndoStack(class UndoStack* stack);
    
private:
    struct Private;
    std::unique_ptr<Private> d;
};

namespace StepRepeatUtils {
    // Grid calculations
    QVector<QTransform> generateGridTransforms(const StepRepeatEngine::Settings& settings, const QRectF& objectBounds);
    QVector<QTransform> generateCircularTransforms(const StepRepeatEngine::CircularSettings& settings, const QRectF& objectBounds);
    QVector<QTransform> generateMirrorTransforms(const StepRepeatEngine::MirrorSettings& settings, const QRectF& objectBounds);
    
    // Bounds calculation
    QRectF calculateTotalBounds(const QVector<QTransform>& transforms, const QRectF& objectBounds);
    QRectF calculateCopyBounds(const QTransform& transform, const QRectF& objectBounds);
    
    // Validation
    struct ValidationResult {
        bool valid = false;
        QString error;
        int estimatedCopies = 0;
        float estimatedArea = 0.0f;
    };
    
    ValidationResult validateSettings(const StepRepeatEngine::Settings& settings, const QRectF& objectBounds, const QRectF& pageBounds);
    
    // Transform composition
    QTransform composeTransforms(const QTransform& a, const QTransform& b);
    QTransform createGridTransform(int x, int y, float spacingX, float spacingY, float angle, float offsetX, float offsetY);
    QTransform createCircularTransform(int index, int count, float radius, float startAngle, float angleStep, const QPointF& center, bool rotate);
    QTransform createMirrorTransform(bool horizontal, bool vertical, float gap, const QRectF& bounds);
}

} // namespace ArtPlus