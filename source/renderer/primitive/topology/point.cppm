module;

#include <vector>
#include <memory>

export module renderer:primitive.topology.point;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :math.vector.vector_3d;
import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

export class Point : public PrimitiveTopology
{
    VertexOut vertex;

public:
    Point(const VertexOut &vertex) : vertex{vertex} {}

    constexpr VertexOut getVertex() const { return this->vertex; }
    constexpr VertexOut &getVertex() { return this->vertex; }

    std::vector<VertexOut> vertices() const override;
    unsigned getVertexCount() const override { return 2; }

    Vector3D getRepresentativeWorldNormal() const override;

    std::unique_ptr<PrimitiveTopology> clone() const override
    {
        return std::make_unique<Point>(*this);
    }
};

// ============================================================================
// EOF
// ============================================================================
