module;

#include <memory>

export module renderer:colour.intensifier.factory.center;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
import :colour.intensifier.factory.base;
import :colour.intensifier.instance.base;
import :colour.intensifier.instance.center;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class CenterColourIntensifierFactory : public ColourIntensifierFactory
{
public:
    std::shared_ptr<ColourIntensifier> instance(
        const Triangle &primitive) const override
    {
        static auto staticInstance =
            std::make_shared<CenterColourIntensifier>();
        return staticInstance;
    }
};

// ============================================================================
// EOF
// ============================================================================