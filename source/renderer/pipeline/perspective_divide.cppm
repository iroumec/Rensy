module;

#include <vector>
#include <stdexcept>

export module renderer:pipeline.perspective_divide;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :math.vector.vector_3d;
import :math.vector.vector_4d;
import :primitive.topology.base;

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

export constexpr void applyPerspectiveDivide(std::vector<Primitive> &primitives)
{
    // #pragma omp parallel for
    for (Primitive &primitive : primitives)
        for (VertexOut &vertex : primitive.vertices())
            vertex.ndcPosition = getNDC(vertex.clipPosition);
}

// ============================================================================
// EOF
// ============================================================================
