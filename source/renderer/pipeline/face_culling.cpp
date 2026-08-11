module;

#include <vector>
#include <stdexcept>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :logging.logger;
import :structure.vertex_out;
import :math.vector.vector_3d;
import :pipeline.face_culling;
import :primitive.topology.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

bool FaceCuller::isVisible(const Primitive &primitive)
{
    // Face normal calculation.
    // Normalization is not necessary. Only the sign matters.
    // However, we normalize so we can interpret easily the result for
    // debugging:
    // 1.0 -> Direct to the camera.
    // 0.0 -> Perpendicular to the camera.
    // -1.0 -> Opposite to the camera.
    Vector3D normal1to2 = primitive.getRepresentativeViewNormal();

    // Winding order.
    // normal2to1 is equals to normal1to2 but negative.
    // Vector3D normal2to1 = edge2.cross(edge1).normalize();

    Vector3D centroid = primitive.getViewCentroid();

    // View space, so the camera is always in (0, 0, 0).
    Vector3D viewDirection =
        (-centroid).normalize();

    double dot = normal1to2.dot(viewDirection);

    logger.trace("Dot test result: {}", dot);

    return dot > 0;
}

/*

// In this algorithm, the face is discarded if all vertices have
// a normal whose dot product with the camera is <= 0.
bool FaceCuller::isVisible(const Primitive &primitive)
{
    bool isVisible = false;

    auto vertices = primitive.getVertices();
    auto it = vertices.begin();

    while (it != vertices.end() && !isVisible)
    {
        const VertexOut &vertex = *it;

        // View space, so the camera is always in (0, 0, 0).
        Vector3D viewDirection =
            (-vertex.viewPosition).normalize();

        double dot = vertex.viewNormal.dot(viewDirection);

        logger.trace("Dot test result: {}", dot);

        isVisible = dot > 0;

        ++it;
    }

    return isVisible;
}
*/

// ============================================================================
// EOF
// ============================================================================
