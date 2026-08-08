module;

#include <vector>

export module renderer:colour.shading.instance.border;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class BorderShading : public Shading
{
public:
    constexpr void adjustColour(Fragment &fragment) const override
    {
        /*
        double intensity = 0.0;

        for (double weight : fragment.weights)
        {
            intensity += weight * weight;
        }

        fragment.colour.set(
            fragment.colour.get() * intensity);
            */
    }
};

// ============================================================================
// EOF
// ============================================================================