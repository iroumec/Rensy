module;

#include <cmath>

export module renderer:colour.shading.instance.flat;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :structure.fragment;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class FlatShading : public Shading
{
    const double lightIntensity;
    const double ambientLight;

public:
    FlatShading(double lightIntensity, double ambientLight = 0.2)
        : lightIntensity(lightIntensity), ambientLight{ambientLight} {}

    constexpr void adjustColour(Fragment &fragment) const override
    {
        fragment.colour =
            fragment.colour * (ambientLight + this->lightIntensity);
    }
};

// ============================================================================
// EOF
// ============================================================================
