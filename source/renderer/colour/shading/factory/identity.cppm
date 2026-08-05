module;

#include <memory>

export module renderer:colour.shading.factory.identity;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;
import :colour.shading.factory.base;
import :colour.shading.instance.base;
import :colour.shading.instance.identity;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class IdentityShadingFactory : public ShadingFactory
{
public:
    std::shared_ptr<Shading> instance(
        const Primitive &primitive) const override
    {
        static auto staticInstance =
            std::make_shared<IdentityShading>();
        return staticInstance;
    }
};

// ============================================================================
// EOF
// ============================================================================