module;

#include <cmath>
#include <memory>

export module renderer:colour.intensifier.factory.depth;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
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
        const Triangle &primitive) const override
    {
        return std::make_shared<DepthColourIntensifier>(
            primitive.v0.screenPosition.z(),
            primitive.v1.screenPosition.z(),
            primitive.v2.screenPosition.z(),
            std::min(
                primitive.v0.screenPosition.z(),
                std::min(
                    primitive.v1.screenPosition.z(),
                    primitive.v2.screenPosition.z())),
            std::max(
                primitive.v0.screenPosition.z(),
                std::max(
                    primitive.v1.screenPosition.z(),
                    primitive.v2.screenPosition.z())));
    }
};

// ============================================================================
// EOF
// ============================================================================