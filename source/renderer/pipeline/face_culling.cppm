module;

#include <vector>
#include <stdexcept>

export module renderer:pipeline.face_culling;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
import :math.vector.vector_3d;
import :math.vector.vector_4d;

// ============================================================================
// Declarations and Implementations
// ============================================================================

bool isVisible(const Triangle &primitive)
{

    Vector3D a = primitive.v1.viewPosition - primitive.v0.viewPosition;
    Vector3D b = primitive.v2.viewPosition - primitive.v0.viewPosition;

    // Face normal calculation.
    Vector3D normal = a.cross(b);

    // View space, so the camera is always in (0, 0, 0).
    Vector3D viewDirection = -primitive.v0.viewPosition;

    double dot = normal.dot(viewDirection); // Normalization is not necessary. Only the sign matters.

    return dot > 0;
}

export std::vector<Triangle> applyFaceCulling(const std::vector<Triangle> &primitives)
{
    std::vector<Triangle> visible; // Visible primitives.
    visible.reserve(primitives.size());

    for (const Triangle &primitive : primitives)
    {
        if (isVisible(primitive))
            visible.push_back(primitive);
    }

    return visible;
}

// ============================================================================
// EOF
// ============================================================================
