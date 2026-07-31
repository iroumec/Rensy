module;

#include <memory>

export module intensifier:factory.border;

// ============================================================================
// Imports
// ============================================================================

import vertex;
import :factory.base;
import :instance.base;
import :instance.border;

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