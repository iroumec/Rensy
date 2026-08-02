module;

export module renderer:colour.filter.base;

// ============================================================================
// Imports
// ============================================================================

import colour;
import :pipeline.depth_test;
import :pipeline.framebuffer;

// ============================================================================
// Declarations
// ============================================================================

export class Filter
{

public:
    virtual constexpr void apply(
        FrameBuffer &colourBuffer, const DepthBuffer &depthBuffer) const = 0;
};

// ============================================================================
// EOF
// ============================================================================