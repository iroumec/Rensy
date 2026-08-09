module;

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

Vector3D Line::getRepresentativeWorldNormal() const
{
    return this->getAverageWorldNormal();
}

Vector3D Line::getRepresentativeViewNormal() const
{
    return this->getAverageViewNormal();
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
        getVertexOne().toString(),
        getVertexTwo().toString());
}

// ============================================================================
// EOF
// ============================================================================
