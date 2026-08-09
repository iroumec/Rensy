module;

export module renderer:pipeline.perspective_divide;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;

// ============================================================================
// Forward Declarations
// ============================================================================

class Logger;
class Vector3D;
class Vector4D;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class PerspectiveDivider
{
    const Logger &logger;

    Vector3D getNDC(const Vector4D &vector) const;

public:
    PerspectiveDivider(const Logger &logger)
        : logger{logger} {}

    void applyPerspectiveDivision(Primitive &primitive) const;
};

// ============================================================================
// EOF
// ============================================================================
