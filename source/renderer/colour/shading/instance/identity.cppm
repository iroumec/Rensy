module;

#include <cmath>

export module renderer:colour.shading.instance.identity;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class IdentityShading : public Shading
{
public:
    constexpr void adjustColour(Fragment &fragment) const override
    {
        // Intentionally does nothing.
    }
};

// ============================================================================
// EOF
// ============================================================================