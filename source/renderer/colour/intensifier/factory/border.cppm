module;

#include <memory>

export module renderer:colour.intensifier.factory.border;

// ============================================================================
// Imports
// ============================================================================

import vertex;
import :colour.intensifier.factory.base;
import :colour.intensifier.instance.base;
import :colour.intensifier.instance.border;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class BorderColourIntensifierFactory : public ColourIntensifierFactory
{
public:
    std::shared_ptr<ColourIntensifier> instance(
        const Vertex &a, const Vertex &b, const Vertex &c) const override
    {
        static auto staticInstance =
            std::make_shared<BorderColourIntensifier>();
        return staticInstance;
    }
};

// ============================================================================
// EOF
// ============================================================================