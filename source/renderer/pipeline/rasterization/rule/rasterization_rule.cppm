module;

#include <cmath>

export module renderer:drawing_pattern;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// Drawing Pattern (Base Class)
// ----------------------------------------------------------------------------

export class DrawingPattern
{

public:
    virtual ~DrawingPattern() = default;

    virtual constexpr bool isValid(
        const BarycentricCoordinate &coordinates) const = 0;
};

// ----------------------------------------------------------------------------
// Border Drawing Pattern
// ----------------------------------------------------------------------------

export class BorderDrawingPattern : public DrawingPattern
{
    const double epsilon; // It's not recommended a value smaller than 0.04.

public:
    BorderDrawingPattern(double epsilon = 4e-2) : epsilon(epsilon) {}

    constexpr bool isValid(
        const BarycentricCoordinate &coordinates) const override
    {

        return std::abs(coordinates.alpha) < epsilon ||
               std::abs(coordinates.beta) < epsilon ||
               std::abs(coordinates.gamma) < epsilon;
    }
};

// ----------------------------------------------------------------------------
// Center Drawing Pattern
// ----------------------------------------------------------------------------

export class CenterDrawingPattern : public DrawingPattern
{

    const double epsilon; // It's not recommended a value smaller than 0.1.

public:
    CenterDrawingPattern(double epsilon = 1e-1) : epsilon(epsilon) {}

    constexpr bool isValid(
        const BarycentricCoordinate &coordinates) const override
    {

        return std::abs(coordinates.alpha) > epsilon &&
               std::abs(coordinates.beta) > epsilon &&
               std::abs(coordinates.gamma) > epsilon;
    }
};

// ============================================================================
// EOF
// ============================================================================