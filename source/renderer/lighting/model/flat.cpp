module;

#include <cmath>
#include <limits>
#include <cassert>

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

    assert(std::isfinite(direction.x()));
    assert(std::isfinite(direction.y()));
    assert(std::isfinite(direction.z()));

    // Light direction calculation using the midpoint or centroid.
    Vector3D l = (this->lightPoint - primitive.getCentroid()).normalize();

    assert(std::isfinite(l.x()));
    assert(std::isfinite(l.y()));
    assert(std::isfinite(l.z()));

    // Light intensity calculation.
    double lightIntensity = std::abs(n.dot(l));
    // double lightIntensity = std::max(0.0, n.dot(l));

    assert(std::isfinite(lightIntensity));

    // The same light intensity is saved in each vertex of the primitive.
    // Another option considered was saving the light intensity in the
    // primitive. However, it added unnecesary complexity.
    for (VertexOut &vertex : primitive.getVertices())
    {
        vertex.lightIntensity = lightIntensity;

        assert(std::isfinite(vertex.lightIntensity));
    }
}

// ============================================================================
// EOF
// ============================================================================