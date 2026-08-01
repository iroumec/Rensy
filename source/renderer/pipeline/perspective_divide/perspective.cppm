module;

#include <stdexcept>

export module perspective;

// ============================================================================
// Imports
// ============================================================================

import vector;

// ============================================================================
// Declarations
// ============================================================================

export constexpr Vector4D getNDC(const Vector4D &vector)
{
    const double w = vector.w();

    if (w == 0.0)
        throw std::runtime_error("Perspective divide by zero");

    return Vector4D{
        vector.x() / w,
        vector.y() / w,
        vector.z() / w,
        1};
}

// Alternative names for the function.
constexpr auto &applyPerspectiveDivide = getNDC;

// ============================================================================