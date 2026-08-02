module;

export module renderer:structure.fragment;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :math.barycentric;

// ============================================================================
// Declarations
// ============================================================================

export struct Fragment
{
    unsigned xScreen;
    unsigned yScreen;
    double depth;

    BarycentricCoordinate barycentricCoordinates;

    // Vector3 worldPosition;
    // Vector3 normal;
    // Vector2 uv;
    Colour colour;
};

// ============================================================================
// EOF
// ============================================================================
