module;

#include <cmath>

export module renderer:colour.calculator.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :math.barycentric;
import :structure.fragment;
import :primitive.topology;

// ============================================================================
// Declarations
// ============================================================================

/**
 * Given a list of vertex, these classes calculate the final colour.
 *
 */
export class ColourCalculator
{

public:
    virtual ~ColourCalculator() = default;

    virtual constexpr Colour calculateColour(
        const Fragment &fragment, const Point &primitive) const = 0;

    virtual constexpr Colour calculateColour(
        const Fragment &fragment, const Line &primitive) const = 0;

    virtual constexpr Colour calculateColour(
        const Fragment &fragment, const Triangle &primitive) const = 0;
};

// ============================================================================
// EOF
// ============================================================================