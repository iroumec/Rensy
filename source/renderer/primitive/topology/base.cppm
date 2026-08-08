module;

#include <vector>
#include <memory>

export module renderer:primitive.topology.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :math.vector.vector_3d;

// ============================================================================
// Declarations
// ============================================================================

export class PrimitiveTopology
{

public:
    virtual ~PrimitiveTopology() = default;

    virtual std::vector<VertexOut> vertices() const = 0;
    virtual unsigned getVertexCount() const = 0;
    virtual Vector3D getRepresentativeWorldNormal() const = 0;

    virtual Vector3D getAverageWorldNormal() const
    {
        Vector3D worldNormalSum;

        for (const VertexOut &vertex : this->vertices())
            worldNormalSum += vertex.worldNormal;

        return worldNormalSum /= this->getVertexCount();
    }

    Vector3D getCentroid() const
    {
        Vector3D centroid;

        for (const VertexOut &vertex : this->vertices())
            centroid += vertex.worldPosition;

        return centroid /= this->getVertexCount();
    }
};

export using Primitive = PrimitiveTopology;

// ============================================================================
// EOF
// ============================================================================
