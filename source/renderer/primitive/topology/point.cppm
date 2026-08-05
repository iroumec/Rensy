module;

#include <vector>

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

    Vector3D getAverageWorldNormal() const override;
    Vector3D getRepresentativaWorldNormal() const override;
};

// ============================================================================
// EOF
// ============================================================================
