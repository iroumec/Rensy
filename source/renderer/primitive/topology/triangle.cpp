module;

#include <vector>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :math.vector.vector_3d;
import :primitive.topology.triangle;

// ============================================================================
// Implementations
// ============================================================================

std::vector<VertexOut> Triangle::vertices() const
{
    return {vertexOne, vertexTwo, vertexThree};
}

Vector3D Triangle::getRepresentativaWorldNormal() const
{
    Vector3D a = this->vertexOne.worldPosition;
    Vector3D b = this->vertexTwo.worldPosition;
    Vector3D c = this->vertexThree.worldPosition;

    // Normal vector calculation.
    Vector3D ab = b - a;
    Vector3D ac = c - a;

    return (ab.cross(ac)).normalize();
}

// ============================================================================
// EOF
// ============================================================================
