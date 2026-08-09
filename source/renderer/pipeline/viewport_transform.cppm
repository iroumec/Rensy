module;

export module renderer:pipeline.viewport_transform;

// ============================================================================
// Imports
// ============================================================================

import :transform.viewport;
import :primitive.topology.base;

// ============================================================================
// Forward Declarations
// ============================================================================

class Logger;

// ============================================================================
// Declarations
// ============================================================================

export class ViewportTransformPhase
{
    const ViewportTransform viewportTransform;
    const Logger &logger;

public:
    ViewportTransformPhase(
        unsigned screenWidth,
        unsigned screenHeight,
        const Logger &logger)
        : viewportTransform(screenWidth, screenHeight), logger{logger} {}

    void processPrimitive(Primitive &primitive) const;
};

// ============================================================================
// EOF
// ============================================================================