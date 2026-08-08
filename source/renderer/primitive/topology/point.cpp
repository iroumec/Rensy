module;

#include <vector>
#include <string>
#include <format>

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

std::vector<PreFragment> Point::rasterizeWith(
    const RasterizationContext &context) const
{
    return context.rasterizePoint(*this);
}

std::string Point::toString() const
{
    return std::format(
        "Point:\n"
        "Vertex:\n{}",
        vertex.toString());
}

// ============================================================================
// EOF
// ============================================================================
