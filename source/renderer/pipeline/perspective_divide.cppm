module;

#include <stdexcept>

export module perspective_divide;

// ============================================================================
// Imports
// ============================================================================

import vector;
import triangle;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export constexpr void applyPerspectiveDivide(std::vector<Triangles> &primitives)
{
    // #pragma omp parallel for
    for (primitive : primitives)
    {
        primitive.v0.ndcPositionn = getNDC(primitive.v0);
        primitive.v1.ndcPositionn = getNDC(primitive.v1);
        primitive.v2.ndcPositionn = getNDC(primitive.v2);
    }
}

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

// ============================================================================