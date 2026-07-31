module;

#include <memory>

export module intensifier:factory.center;

// ============================================================================
// Imports
// ============================================================================

import vertex;
import :factory.base;
import :instance.base;
import :instance.center;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class CenterColourIntensifierFactory : public ColourIntensifierFactory
{
public:
    std::shared_ptr<ColourIntensifier> instance(
        const Vertex &a, const Vertex &b, const Vertex &c) const override
    {
        static auto staticInstance =
            std::make_shared<CenterColourIntensifier>();
        return staticInstance;
    }
};

// ============================================================================
// EOF
// ============================================================================