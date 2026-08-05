module;

#include <cmath>
#include <memory>

export module renderer:colour.shading.factory.phong;

// ============================================================================
// Imports
// ============================================================================

import :math.vector;
import :primitive.topology.triangle;
import :colour.shading.factory.base;
import :colour.shading.instance.base;
import :colour.shading.instance.phong;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class PhongShadingFactory : public ShadingFactory
{
    const Vector3D lightPoint;

public:
    PhongShadingFactory(const Vector3D &lightPoint) : lightPoint(lightPoint) {}

    std::shared_ptr<Shading> instance(const Triangle &primitive) const override
    {
        Vector3D aNormal = primitive.v0.worldNormal;
        Vector3D bNormal = primitive.v1.worldNormal;
        Vector3D cNormal = primitive.v2.worldNormal;

        return std::make_shared<PhongShading>(
            lightPoint, aNormal, bNormal, cNormal);
    }
};

// ============================================================================
// EOF
// ============================================================================