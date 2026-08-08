module;

#include <vector>

export module renderer:primitive.topology.line;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :math.vector.vector_3d;
import :rasterization.context;
import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

export class Line : public PrimitiveTopology
{
    VertexOut vertexOne;
    VertexOut vertexTwo;

public:
    Line(const VertexOut &vertexOne, const VertexOut &vertexTwo)
        : vertexOne{vertexOne}, vertexTwo{vertexTwo} {}

    constexpr VertexOut getVertexOne() const { return this->vertexOne; }
    constexpr VertexOut getVertexTwo() const { return this->vertexTwo; }
    constexpr VertexOut &getVertexOne() { return this->vertexOne; }
    constexpr VertexOut &getVertexTwo() { return this->vertexTwo; }

    std::vector<VertexOut> vertices() const override;
    unsigned getVertexCount() const override { return 1; }

    Vector3D getRepresentativeWorldNormal() const override;

    std::vector<PreFragment> Line::rasterizeWith(
        const RasterizationContext &context) const override
    {
        return context.rasterizeLine(*this);
    }
};

// ============================================================================
// EOF
// ============================================================================
