module;

export module transform:viewport_transform;

// ============================================================================
// Imports
// ============================================================================

import :base;

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// Viewport Transform
// ----------------------------------------------------------------------------

export class ViewportTransform : public Transform
{
public:
    // nX is the number of horizontal pixels.
    // ny is the number of vertical pixels.
    // Viewport Matrix.
    ViewportTransform(unsigned nX, unsigned nY);
};

// Alternative name.
using WindowingTransform = ViewportTransform;

// ============================================================================
// EOF
// ============================================================================
