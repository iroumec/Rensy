module;

#include <cmath>
#include <memory>

export module renderer:colour.shading.factory.gouraud;

// ============================================================================
// Imports
// ============================================================================

import vector;
import :structure.triangle;
import :colour.shading.factory.base;
import :colour.shading.instance.base;
import :colour.shading.instance.gouraud;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class GouraudColourShadingFactory
    : public ColourShadingFactory
{
    const Vector3D lightPoint;

public:
    GouraudColourShadingFactory(const Vector3D &lightPoint)
        : lightPoint(lightPoint) {}

    std::shared_ptr<ColourShading> instance(
        const Triangle &primitive) const override
    {
        Vector3D a = primitive.v0.worldPosition;
        Vector3D b = primitive.v1.worldPosition;
        Vector3D c = primitive.v2.worldPosition;
        Vector3D an = primitive.v0.worldNormal;
        Vector3D bn = primitive.v1.worldNormal;
        Vector3D cn = primitive.v2.worldNormal;

        // Light direction calculation.
        Vector3D al = (this->lightPoint - a).normalize();
        Vector3D bl = (this->lightPoint - b).normalize();
        Vector3D cl = (this->lightPoint - c).normalize();

        // Light intensity calculation.
        // double lightIntensity = std::max(0.0, n.dot(l));
        double aLightIntensity = std::abs(an.dot(al)); // Two points of lights.
        double bLightIntensity = std::abs(bn.dot(bl)); // Two points of lights.
        double cLightIntensity = std::abs(cn.dot(cl)); // Two points of lights.

        return std::make_shared<GouraudColourShading>(
            aLightIntensity, bLightIntensity, cLightIntensity);
    }
};

// ============================================================================
// EOF
// ============================================================================