module;

#include <span>
#include <vector>
#include <string>
#include <memory>

export module renderer:primitive.topology.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :math.vector.vector_3d;

// ============================================================================
// Forward Declarations
// ============================================================================

class ClipVolume;
struct PreFragment;
class RasterizationContext;

// ============================================================================
// Declarations
// ============================================================================

export class Primitive
{

public:
    virtual ~Primitive() = default;

    virtual unsigned getVertexCount() const = 0;
    virtual std::span<VertexOut> getVertices() = 0;
    virtual std::span<const VertexOut> getVertices() const = 0;
    virtual Vector3D getRepresentativeWorldNormal() const = 0;
    virtual Vector3D getRepresentativeViewNormal() const = 0;

    Vector3D getAverageWorldNormal() const
    {
        const auto vertices = this->getVertices();

        Vector3D worldNormal{};

        for (const auto &vertex : vertices)
            worldNormal += vertex.worldNormal;

        return worldNormal / static_cast<double>(vertices.size());
    }

    Vector3D getAverageViewNormal() const
    {
        const auto vertices = this->getVertices();

        Vector3D viewNormal{};

        for (const auto &vertex : vertices)
            viewNormal += vertex.viewNormal;

        return viewNormal / static_cast<double>(vertices.size());
    }

    Vector3D getCentroid() const
    {
        const auto vertices = this->getVertices();

        Vector3D centroid{};

        for (const auto &vertex : vertices)
            centroid += vertex.worldPosition;

        return centroid / static_cast<double>(vertices.size());
    }

    Vector3D getViewCentroid() const
    {
        const auto vertices = this->getVertices();

        Vector3D centroid{};

        for (const auto &vertex : vertices)
            centroid += vertex.viewPosition;

        return centroid / static_cast<double>(vertices.size());
    }

    virtual std::vector<PreFragment> rasterizeWith(
        const RasterizationContext &context) const = 0;

    virtual std::vector<std::unique_ptr<Primitive>>
    clip(const ClipVolume &volume) const = 0;

    virtual std::string toString() const = 0;
};

// ============================================================================
// EOF
// ============================================================================
