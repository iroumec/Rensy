module;

#include <vector>
#include <string>

export module renderer:primitive.topology.triangle;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;

// ============================================================================
// Forward Declarations
// ============================================================================

class Vector3D;
struct VertexOut;
struct PreFragment;
class RasterizationContext;

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
    unsigned getVertexCount() const override { return 3; }

    Vector3D getRepresentativeWorldNormal() const override;

    std::vector<PreFragment> rasterizeWith(
        const RasterizationContext &context) const override;

    std::string toString() const override;
};

// ============================================================================
// EOF
// ============================================================================
