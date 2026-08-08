module;

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
    VertexOut vertex;

public:
    Point(const VertexOut &vertex) : vertex{vertex} {}

    constexpr VertexOut getVertex() const { return this->vertex; }
    constexpr VertexOut &getVertex() { return this->vertex; }

    std::vector<VertexOut> vertices() const override;
    unsigned getVertexCount() const override { return 2; }

    Vector3D getRepresentativeWorldNormal() const override;

    std::vector<PreFragment> rasterizeWith(
        const RasterizationContext &context) const override;

    std::string toString() const override;
};

// ============================================================================
// EOF
// ============================================================================
