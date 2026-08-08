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

std::vector<PreFragment> Line::rasterizeWith(
    const RasterizationContext &context) const
{
    return context.rasterizeLine(*this);
}

std::string Line::toString() const
{
    return std::format(
        "Line:\n"
        "Vertex 1:\n{}\n"
        "Vertex 2:\n{}",
        vertexOne.toString(),
        vertexTwo.toString());
}

// ============================================================================
// EOF
// ============================================================================
