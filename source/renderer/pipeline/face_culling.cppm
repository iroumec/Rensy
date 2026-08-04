module;

#include <vector>
#include <stdexcept>

export module renderer:pipeline.face_culling;

// ============================================================================
// Imports
// ============================================================================

import :logging.logger;
import :structure.triangle;
import :math.vector.vector_3d;
import :math.vector.vector_4d;

// ============================================================================
// Declarations and Implementations
// ============================================================================

bool isVisible(const Triangle &primitive, const Logger &logger)
{
    Vector3D edge1 =
        primitive.v1.viewPosition -
        primitive.v0.viewPosition;

    Vector3D edge2 =
        primitive.v2.viewPosition -
        primitive.v0.viewPosition;

    // Face normal calculation.
    // Normalization is not necessary. Only the sign matters.
    // However, we normalize so we can interpret easily the result for
    // debugging:
    // 1.0 -> Direct to the camera.
    // 0.0 -> Perpendicular to the camera.
    // -1.0 -> Opposite to the camera.
    Vector3D normal1to2 =
        edge1.cross(edge2).normalize();

    // Winding order.
    // normal2to1 is equals to normal1to2 but negative.
    // Vector3D normal2to1 = edge2.cross(edge1).normalize();

    Vector3D center =
        (primitive.v0.viewPosition +
         primitive.v1.viewPosition +
         primitive.v2.viewPosition) /
        3.0;

    // View space, so the camera is always in (0, 0, 0).
    Vector3D viewDirection =
        (-center).normalize();

    double dot = normal1to2.dot(viewDirection);

    logger.trace("Dot test result: {}", dot);

    return dot > 0;
}

export std::vector<Triangle> applyFaceCulling(
    const std::vector<Triangle> &primitives,
    const Logger &logger)
{
    std::vector<Triangle> visible; // Visible primitives.
    visible.reserve(primitives.size());

    for (const Triangle &primitive : primitives)
    {
        if (isVisible(primitive, logger))
            visible.push_back(primitive);
    }

    return visible;
}

// ============================================================================
// EOF
// ============================================================================
