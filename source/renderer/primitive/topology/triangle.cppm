module;

#include <vector>

export module renderer:primitive.topology.triangle;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

export class Triangle : public PrimitiveTopology
{
    VertexOut vertexOne;
    VertexOut vertexTwo;
    VertexOut vertexThree;

public:
    Triangle(
        const VertexOut &vertexOne,
        const VertexOut &vertexTwo,
        const VertexOut &vertexThree)
        : vertexOne{vertexOne},
          vertexTwo{vertexTwo},
          vertexThree{vertexThree} {}

    constexpr VertexOut getVertexOne() const { return this->vertexOne; }
    constexpr VertexOut getVertexTwo() const { return this->vertexTwo; }
    constexpr VertexOut getVertexThree() const { return this->vertexThree; }
    constexpr VertexOut &getVertexOne() { return this->vertexOne; }
    constexpr VertexOut &getVertexTwo() { return this->vertexTwo; }
    constexpr VertexOut &getVertexThree() { return this->vertexThree; }

    std::vector<VertexOut> vertices() const override;
};

// ============================================================================
// EOF
// ============================================================================
