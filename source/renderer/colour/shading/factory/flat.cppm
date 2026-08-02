module;

#include <cmath>
#include <memory>

export module renderer:colour.shading.factory.flat;

// ============================================================================
// Imports
// ============================================================================

import :math.vector;
import :structure.triangle;
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
        const Triangle &primitive) const override
    {
        Vector3D a = primitive.v0.worldPosition;
        Vector3D b = primitive.v1.worldPosition;
        Vector3D c = primitive.v2.worldPosition;

        // Normal vector calculation.
        Vector3D ab = b - a;
        Vector3D ac = c - a;
        Vector3D n = (ab.cross(ac)).normalize();

        // Midpoint calculation.
        Vector3D midpoint = Vector3D(
            (a.x() + b.x() + c.x()) / 3,
            (a.y() + b.y() + c.y()) / 3,
            (a.z() + b.z() + c.z()) / 3);

        // Light direction calculation.
        Vector3D l = (this->lightPoint - midpoint).normalize();

        // Light intensity calculation.
        // double lightIntensity = std::max(0.0, n.dot(l));
        double lightIntensity = std::abs(n.dot(l)); // Two points of lights.

        return std::make_shared<FlatShading>(lightIntensity);
    }
};

// ============================================================================
// EOF
// ============================================================================