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

export class BorderColourShadingFactory : public ColourShadingFactory
{
public:
    std::shared_ptr<ColourShading> instance(
        const Triangle &primitive) const override
    {
        static auto staticInstance =
            std::make_shared<BorderColourShading>();
        return staticInstance;
    }
};

// ============================================================================
// EOF
// ============================================================================