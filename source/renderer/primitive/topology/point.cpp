module;

#include <vector>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :math.vector.vector_3d;
import :primitive.topology.point;

// ============================================================================
// Implementations
// ============================================================================

std::vector<VertexOut> Point::vertices() const
{
    return {vertex};
}

Vector3D Point::getRepresentativeWorldNormal() const
{
    return this->getAverageWorldNormal();
}

// ============================================================================
// EOF
// ============================================================================
