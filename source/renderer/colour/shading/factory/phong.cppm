module;

#include <cmath>
#include <memory>
#include <vector>

export module renderer:colour.shading.factory.phong;

// ============================================================================
// Imports
// ============================================================================

import :math.vector.vector_3d;
import :primitive.topology.base;
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

    std::shared_ptr<Shading> instance(
        const Primitive &primitive) const override
    {
        std::vector<Vector3D> normals;

        for (const VertexOut &vertex : primitive.vertices())
        {
            normals.push_back(vertex.worldNormal);
        }

        return std::make_shared<PhongShading>(lightPoint, normals);
    }
};

// ============================================================================
// EOF
// ============================================================================