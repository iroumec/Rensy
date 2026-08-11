module;

#include <vector>
#include <memory>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :clipping.volume;
import :pipeline.clipping;

// ============================================================================
// Implementations
// ============================================================================

void Clipper::applyClipping(
    std::vector<std::unique_ptr<Primitive>> &primitives) const
{
    ClipVolume clipVolume;

    std::vector<std::unique_ptr<Primitive>> clipped;

    for (const auto &primitive : primitives)
    {
        auto result = primitive->clip(clipVolume);

        this->logger.traceEvery<1000>(
            "CLIPPING: Primitives after applying clipping: {}",
            result.size());

        std::move(
            result.begin(),
            result.end(),
            std::back_inserter(clipped));
    }

    primitives = std::move(clipped);
}

// ============================================================================
// EOF
// ============================================================================
