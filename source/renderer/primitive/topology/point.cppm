module;

#include <span>
#include <array>
#include <vector>
#include <string>

export module renderer:primitive.topology.point;

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

export class Point : public PrimitiveTopology
{
    std::array<VertexOut, 1> vertices;

public:
    Point(const VertexOut &vertex) : vertices{vertex} {}

    constexpr VertexOut getVertex() const { return this->vertices[0]; }
    constexpr VertexOut &getVertex() { return this->vertices[0]; }

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
    Vector3D getRepresentativeViewNormal() const override;

    std::vector<PreFragment> rasterizeWith(
        const RasterizationContext &context) const override;

    std::string toString() const override;
};

// ============================================================================
// EOF
// ============================================================================
