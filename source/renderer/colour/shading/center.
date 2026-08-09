module;

#include <cmath>

export module renderer:colour.shading.instance.center;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :structure.fragment;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class CenterShading : public Shading
{
public:
    constexpr void adjustColour(Fragment &fragment) const override
    {
        /*
        double sum = 0.0;

        for (double weight : fragment.weights)
        {
            sum += weight * weight;
        }

        double intensity = fragment.weights.size() * sum;

        if (intensity > 0.0)
            fragment.colour.set(
                fragment.colour.get() * (1.0 / intensity));
                */
    }
};

// ============================================================================
// EOF
// ============================================================================