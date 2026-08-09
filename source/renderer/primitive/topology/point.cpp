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

Vector3D Point::getRepresentativeWorldNormal() const
{
    return this->getAverageWorldNormal();
}

Vector3D Point::getRepresentativeViewNormal() const
{
    return this->getAverageViewNormal();
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
        this->getVertex().toString());
}

// ============================================================================
// EOF
// ============================================================================
