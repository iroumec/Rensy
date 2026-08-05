module;

#include <vector>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :math.vector.vector_3d;
import :primitive.topology.line;

// ============================================================================
// Implementations
// ============================================================================

std::vector<VertexOut> Line::vertices() const
{
    return {vertexOne, vertexTwo};
}

Vector3D Line::getRepresentativeWorldNormal() const
{
    return this->getAverageWorldNormal();
}

// ============================================================================
// EOF
// ============================================================================
