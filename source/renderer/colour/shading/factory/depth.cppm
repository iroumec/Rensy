module;

#include <cmath>
#include <memory>

export module renderer:colour.shading.factory.depth;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.triangle;
import :colour.shading.factory.base;
import :colour.shading.instance.base;
import :colour.shading.instance.depth;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class DepthShadingFactory : public ShadingFactory
{
public:
    std::shared_ptr<Shading> instance(
        const Triangle &primitive) const override
    {
        return std::make_shared<DepthShading>(
            primitive.v0.screenPosition.z(),
            primitive.v1.screenPosition.z(),
            primitive.v2.screenPosition.z(),
            std::min(
                primitive.v0.screenPosition.z(),
                std::min(
                    primitive.v1.screenPosition.z(),
                    primitive.v2.screenPosition.z())),
            std::max(
                primitive.v0.screenPosition.z(),
                std::max(
                    primitive.v1.screenPosition.z(),
                    primitive.v2.screenPosition.z())));
    }
};

// ============================================================================
// EOF
// ============================================================================