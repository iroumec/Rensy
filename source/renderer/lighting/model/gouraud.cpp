module;

#include <cmath>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :structure.vertex_out;
import :math.vector.vector_3d;
import :lighting.model.gouraud;

// ============================================================================
// Declarations
// ============================================================================

void GouraudLightingModel::processVertex(VertexOut &vertex) const
{
    Vector3D worldPosition = vertex.worldPosition;
    Vector3D worldNormal = vertex.worldNormal;

    // Light direction calculation.
    Vector3D lightDirection =
        (this->lightPoint - worldPosition).normalize();

    // Light intensity calculation.
    // double lightIntensity = std::max(0.0, n.dot(l));
    vertex.lightIntensity =
        this->ambientLight +
        std::abs(worldNormal.dot(lightDirection)); // Two points of lights.
}

// ============================================================================
// EOF
// ============================================================================