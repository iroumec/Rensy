module;

#include <memory>

export module renderer:colour.shading.factory.border;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
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
        const Triangle &primitive) const override
    {
        static auto staticInstance =
            std::make_shared<BorderShading>();
        return staticInstance;
    }
};

// ============================================================================
// EOF
// ============================================================================