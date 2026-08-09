module;

#include <memory>

export module renderer:colour.shading.factory.border;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;
import :colour.shading.factory.base;
import :colour.shading.instance.base;
import :colour.shading.instance.border;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class BorderShadingFactory : public ShadingFactory
{
public:
    std::shared_ptr<Shading> instance(
        const Primitive &primitive) const override
    {
        static auto staticInstance =
            std::make_shared<BorderShading>();
        return staticInstance;
    }
};

// ============================================================================
// EOF
// ============================================================================