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
    double depth = 0.0;

    BarycentricCoordinate barycentricCoordinates;

    Vector3D worldPosition;
    Vector3D normal;
    // Vector2D uv;
    Colour colour;
};

// ============================================================================
// EOF
// ============================================================================
