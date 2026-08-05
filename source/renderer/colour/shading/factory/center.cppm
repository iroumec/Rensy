module;

#include <memory>

export module renderer:colour.shading.factory.center;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.triangle;
import :colour.shading.factory.base;
import :colour.shading.instance.base;
import :colour.shading.instance.center;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class CenterShadingFactory : public ShadingFactory
{
public:
    std::shared_ptr<Shading> instance(
        const Triangle &primitive) const override
    {
        static auto staticInstance =
            std::make_shared<CenterShading>();
        return staticInstance;
    }
};

// ============================================================================
// EOF
// ============================================================================