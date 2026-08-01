module;

export module renderer:structure.fragment;

// ============================================================================
// Imports
// ============================================================================

import vector;
import colour;
import barycentric;

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
