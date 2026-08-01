module;

#include <vector>
#include <stdexcept>

export module renderer:pipeline.perspective_divide;

// ============================================================================
// Imports
// ============================================================================

import vector;
import :structure.triangle;

// ============================================================================
// Declarations and Implementations
// ============================================================================

constexpr Vector3D getNDC(const Vector4D &vector)
{
    const double w = vector.w();

    if (w == 0.0)
        throw std::runtime_error("Perspective divide by zero");

    return Vector3D{
        vector.x() / w,
        vector.y() / w,
        vector.z() / w};
}

export constexpr void applyPerspectiveDivide(std::vector<Triangle> &primitives)
{
    // #pragma omp parallel for
    for (Triangle &primitive : primitives)
    {
        primitive.v0.ndcPosition = getNDC(primitive.v0.clipPosition);
        primitive.v1.ndcPosition = getNDC(primitive.v1.clipPosition);
        primitive.v2.ndcPosition = getNDC(primitive.v2.clipPosition);
    }
}

// ============================================================================
// EOF
// ============================================================================
