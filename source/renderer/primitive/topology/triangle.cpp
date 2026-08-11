module;

#include <vector>
#include <format>
#include <string>
#include <memory>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :clipping.volume;
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

VertexOut Triangle::intersection(
    const VertexOut &a,
    const VertexOut &b,
    double da,
    double db) const
{
    const double t = da / (da - db);

    return a * (1.0 - t) + b * t;
}

std::vector<std::unique_ptr<Primitive>>
Triangle::clip(const ClipVolume &volume) const
{
    std::vector<VertexOut> polygon{
        this->vertices[0],
        this->vertices[1],
        this->vertices[2]};

    for (const ClipPlane &plane : volume.getPlanes())
    {
        std::vector<VertexOut> clipped;

        if (polygon.empty())
            break;

        for (std::size_t i = 0; i < polygon.size(); ++i)
        {
            const VertexOut &current =
                polygon[i];

            const VertexOut &previous =
                polygon[(i + polygon.size() - 1) % polygon.size()];

            const double currentDistance =
                plane.evaluate(current.clipPosition);

            const double previousDistance =
                plane.evaluate(previous.clipPosition);

            const bool currentInside =
                currentDistance >= 0.0;

            const bool previousInside =
                previousDistance >= 0.0;

            if (currentInside && previousInside)
            {
                // Inside -> inside
                clipped.push_back(current);
            }
            else if (previousInside && !currentInside)
            {
                // Inside -> outside
                clipped.push_back(
                    intersection(
                        previous,
                        current,
                        previousDistance,
                        currentDistance));
            }
            else if (!previousInside && currentInside)
            {
                // Outside -> inside
                clipped.push_back(
                    intersection(
                        previous,
                        current,
                        previousDistance,
                        currentDistance));

                clipped.push_back(current);
            }

            // Outside -> outside
            // Nothing is emitted.
        }

        polygon = std::move(clipped);
    }

    std::vector<std::unique_ptr<Primitive>> result;

    if (polygon.size() < 3)
        return result;

    // Fan triangulation.
    for (std::size_t i = 1; i + 1 < polygon.size(); ++i)
    {
        result.push_back(
            std::make_unique<Triangle>(
                polygon[0],
                polygon[i],
                polygon[i + 1]));
    }

    return result;
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
