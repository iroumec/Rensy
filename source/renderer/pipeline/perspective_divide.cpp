module;

#include <stdexcept>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :logging.logger;
import :structure.vertex_out;
import :math.vector.vector_3d;
import :math.vector.vector_4d;
import :primitive.topology.base;
import :pipeline.perspective_divide;

// ============================================================================
// Declarations and Implementations
// ============================================================================

void PerspectiveDivider::applyPerspectiveDivision(
    Primitive &primitive) const
{

    for (VertexOut &vertex : primitive.getVertices())
    {
        vertex.ndcPosition = getNDC(vertex.clipPosition);

        this->logger.traceEvery<1000>(
            "Vertex's NDC position obtained: {},\nfrom clip position {}.",
            vertex.ndcPosition.toString(), vertex.clipPosition.toString());
    }
}

Vector3D PerspectiveDivider::getNDC(const Vector4D &vector) const
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
// EOF
// ============================================================================
