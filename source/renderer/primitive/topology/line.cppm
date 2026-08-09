module;

#include <span>
#include <array>
#include <vector>
#include <string>

export module renderer:primitive.topology.line;

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

export class Line : public PrimitiveTopology
{
    std::array<VertexOut, 2> vertices;

public:
    Line(const VertexOut &vertexOne, const VertexOut &vertexTwo)
        : vertices{vertexOne, vertexTwo} {}

    constexpr VertexOut getVertexOne() const { return this->vertices[0]; }
    constexpr VertexOut getVertexTwo() const { return this->vertices[1]; }
    constexpr VertexOut &getVertexOne() { return this->vertices[0]; }
    constexpr VertexOut &getVertexTwo() { return this->vertices[1]; }

    std::span<VertexOut> getVertices() override
    {
        return this->vertices;
    }
    std::span<const VertexOut> getVertices() const override
    {
        return this->vertices;
    }

    unsigned getVertexCount() const override { return this->vertices.size(); }

    Vector3D getRepresentativeWorldNormal() const override;

    std::vector<PreFragment> rasterizeWith(
        const RasterizationContext &context) const override;

    std::string toString() const override;
};

// ============================================================================
// EOF
// ============================================================================
