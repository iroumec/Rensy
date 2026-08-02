module;

export module renderer:structure.fragment;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :math.barycentric;
import :math.vector.vector_3d;

// ============================================================================
// Declarations
// ============================================================================

export struct Fragment
{
    unsigned xScreen;
    unsigned yScreen;
    double depth;

    BarycentricCoordinate barycentricCoordinates;

    Vector3D worldPosition;
    // Vector3 normal;
    // Vector2 uv;
    Colour colour;
};

// ============================================================================
// EOF
// ============================================================================
