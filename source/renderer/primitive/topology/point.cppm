module;

#include <vector>

export module renderer:primitive.topology.point;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
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
};

// ============================================================================
// EOF
// ============================================================================
