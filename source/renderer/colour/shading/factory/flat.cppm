module;

#include <cmath>
#include <memory>

export module renderer:colour.shading.factory.flat;

// ============================================================================
// Imports
// ============================================================================

import :math.vector;
import :primitive.topology.triangle;
import :colour.shading.factory.base;
import :colour.shading.instance.base;
import :colour.shading.instance.flat;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class FlatShadingFactory : public ShadingFactory
{
    const Vector3D lightPoint;

public:
    FlatShadingFactory(const Vector3D &lightPoint)
        : lightPoint(lightPoint) {}

    std::shared_ptr<Shading> instance(
        const Primitive &primitive) const override
    {
        Vector3D n = primitive.getRepresentativeWorldNormal();

        // Light direction calculation using the midpoint or centroid.
        Vector3D l = (this->lightPoint - primitive.getCentroid()).normalize();

        // Light intensity calculation.
        // double lightIntensity = std::max(0.0, n.dot(l));
        double lightIntensity = std::abs(n.dot(l)); // Two points of lights.

        return std::make_shared<FlatShading>(lightIntensity);
    }
};

// ============================================================================
// EOF
// ============================================================================