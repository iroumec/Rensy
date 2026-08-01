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

export constexpr void getNDC(VertexOut &vertex)
{
    vertex.ndcPosition = getNDC(vertex.clipPosition);
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

// Alternative names for the function.
constexpr auto &applyPerspectiveDivide = getNDC;

// ============================================================================