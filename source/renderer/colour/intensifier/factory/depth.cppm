module;

#include <cmath>
#include <memory>

export module renderer:colour.intensifier.factory.depth;

// ============================================================================
// Imports
// ============================================================================

import vertex;
import :colour.intensifier.factory.base;
import :colour.intensifier.instance.base;
import :colour.intensifier.instance.depth;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class DepthColourIntensifierFactory : public ColourIntensifierFactory
{
public:
    std::shared_ptr<ColourIntensifier> instance(
        const Vertex &a, const Vertex &b, const Vertex &c) const override
    {
        return std::make_shared<DepthColourIntensifier>(
            a.z(),
            b.z(),
            c.z(),
            std::min(a.z(), std::min(b.z(), c.z())),
            std::max(a.z(), std::max(b.z(), c.z())));
    }
};

// ============================================================================
// EOF
// ============================================================================