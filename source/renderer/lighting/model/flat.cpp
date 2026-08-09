module;

#include <cmath>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :lighting.model.flat;
import :structure.vertex_out;
import :math.vector.vector_3d;
import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

void FlatLightingModel::processPrimitive(Primitive &primitive) const
{
    Vector3D n = primitive.getRepresentativeWorldNormal();

    // Light direction calculation using the midpoint or centroid.
    Vector3D l = (this->lightPoint - primitive.getCentroid()).normalize();

    // Light intensity calculation.
    double lightIntensity = std::abs(n.dot(l));
    // double lightIntensity = std::max(0.0, n.dot(l));

    // The same light intensity is saved in each vertex of the primitive.
    // Another option considered was saving the light intensity in the
    // primitive. However, it added unnecesary complexity.
    for (VertexOut &vertex : primitive.getVertices())
        vertex.lightIntensity = lightIntensity;
}

// ============================================================================
// EOF
// ============================================================================