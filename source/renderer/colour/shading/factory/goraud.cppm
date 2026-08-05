module;

#include <cmath>
#include <memory>
#include <vector>

export module renderer:colour.shading.factory.gouraud;

// ============================================================================
// Imports
// ============================================================================

import :math.vector;
import :primitive.topology.base;
import :colour.shading.factory.base;
import :colour.shading.instance.base;
import :colour.shading.instance.gouraud;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class GouraudShadingFactory : public ShadingFactory
{
    const Vector3D lightPoint;

public:
    GouraudShadingFactory(const Vector3D &lightPoint)
        : lightPoint(lightPoint) {}

    std::shared_ptr<Shading> instance(
        const Primitive &primitive) const override
    {
        std::vector<double> lightIntensities;

        for (const VertexOut &vertex : primitive.vertices())
        {
            Vector3D worldPosition = vertex.worldPosition;
            Vector3D worldNormal = vertex.worldNormal;

            // Light direction calculation.
            Vector3D lightDirection =
                (this->lightPoint - worldPosition).normalize();

            // Light intensity calculation.
            // double lightIntensity = std::max(0.0, n.dot(l));
            double lightIntensity =
                std::abs(worldNormal.dot(lightDirection)); // Two points of lights.

            lightIntensities.push_back(lightIntensity);
        }

        return std::make_shared<GouraudShading>(lightIntensities);
    }
};

// ============================================================================
// EOF
// ============================================================================