module;

#include <vector>
#include <string>
#include <format>
#include <memory>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :clipping.volume;
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

std::vector<std::unique_ptr<Primitive>>
Point::clip(const ClipVolume &volume) const
{
    std::vector<std::unique_ptr<Primitive>> result;

    if (volume.inside(this->vertices[0]))
        result.push_back(std::make_unique<Point>(*this));

    return result;
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
