module;

#include <memory>

export module renderer:colour.shading.factory.center;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
import :colour.shading.factory.base;
import :colour.shading.instance.base;
import :colour.shading.instance.center;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class CenterColourShadingFactory : public ColourShadingFactory
{
public:
    std::shared_ptr<ColourShading> instance(
        const Triangle &primitive) const override
    {
        static auto staticInstance =
            std::make_shared<CenterColourShading>();
        return staticInstance;
    }
};

// ============================================================================
// EOF
// ============================================================================