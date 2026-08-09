module;

#include <span>
#include <vector>
#include <string>

export module renderer:primitive.topology.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :math.vector.vector_3d;

// ============================================================================
// Forward Declarations
// ============================================================================

struct PreFragment;
class RasterizationContext;

// ============================================================================
// Declarations
// ============================================================================

export class PrimitiveTopology
{

public:
    virtual ~PrimitiveTopology() = default;

    virtual unsigned getVertexCount() const = 0;
    virtual std::span<VertexOut> getVertices() = 0;
    virtual std::span<const VertexOut> getVertices() const = 0;
    virtual Vector3D getRepresentativeWorldNormal() const = 0;

    virtual Vector3D getAverageWorldNormal() const
    {
        Vector3D worldNormalSum;

        for (const VertexOut &vertex : this->getVertices())
            worldNormalSum += vertex.worldNormal;

        return worldNormalSum /= this->getVertexCount();
    }

    Vector3D getCentroid() const
    {
        Vector3D centroid;

        for (const VertexOut &vertex : this->getVertices())
            centroid += vertex.worldPosition;

        return centroid /= this->getVertexCount();
    }

    virtual std::vector<PreFragment> rasterizeWith(
        const RasterizationContext &context) const = 0;

    virtual std::string toString() const = 0;
};

export using Primitive = PrimitiveTopology;

// ============================================================================
// EOF
// ============================================================================
