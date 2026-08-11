module;

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

std::vector<std::unique_ptr<Primitive>>
Line::clip(const ClipVolume &volume) const
{
    const VertexOut &a = this->vertices[0];
    const VertexOut &b = this->vertices[1];

    double tMin = 0.0;
    double tMax = 1.0;

    const Vector4D &aClip = a.clipPosition;
    const Vector4D &bClip = b.clipPosition;

    for (const ClipPlane &plane : volume.getPlanes())
    {
        const double da = plane.evaluate(aClip);
        const double db = plane.evaluate(bClip);

        // Both endpoints are outside this plane.
        if (da < 0.0 && db < 0.0)
            return {};

        // The segment is parallel to this plane.
        if (std::abs(da - db) < 1e-12)
            continue;

        const double t = da / (da - db);

        if (da < 0.0)
            tMin = std::max(tMin, t);
        else
            tMax = std::min(tMax, t);

        if (tMin > tMax)
            return {};
    }

    const VertexOut start =
        a * (1.0 - tMin) + b * tMin;

    const VertexOut end =
        a * (1.0 - tMax) + b * tMax;

    std::vector<std::unique_ptr<Primitive>> result;

    result.push_back(
        std::make_unique<Line>(start, end));

    return result;
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
