module;

#include <vector>
#include <format>
#include <string>

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

Vector3D Triangle::getRepresentativeWorldNormal() const
{
    Vector3D a = this->getVertexOne().worldPosition;
    Vector3D b = this->getVertexTwo().worldPosition;
    Vector3D c = this->getVertexThree().worldPosition;

    // Normal vector calculation.
    Vector3D ab = b - a;
    Vector3D ac = c - a;

    return (ab.cross(ac)).normalize();
}

Vector3D Triangle::getRepresentativeViewNormal() const
{
    Vector3D a = this->getVertexOne().viewPosition;
    Vector3D b = this->getVertexTwo().viewPosition;
    Vector3D c = this->getVertexThree().viewPosition;

    // Normal vector calculation.
    Vector3D ab = b - a;
    Vector3D ac = c - a;

    return (ab.cross(ac)).normalize();
}

std::vector<PreFragment> Triangle::rasterizeWith(
    const RasterizationContext &context) const
{
    return context.rasterizeTriangle(*this);
}

std::string Triangle::toString() const
{
    return std::format(
        "Triangle:\n"
        "Vertex 1:\n{}\n"
        "Vertex 2:\n{}\n"
        "Vertex 3:\n{}",
        getVertexOne().toString(),
        getVertexTwo().toString(),
        getVertexThree().toString());
}

// ============================================================================
// EOF
// ============================================================================
