module;

#include <vector>

export module renderer:structure.fragment;

// ============================================================================
// Imports
// ============================================================================

import :colour.restricted;
import :math.vector.vector_3d;

// ============================================================================
// Declarations
// ============================================================================

// World position, normal, depth and UV must already be interpolated.
// Fragment should not know any details about the method of rasterization. So
// it should not contain barycentric coordinates.
export struct Fragment
{
    unsigned xScreen;
    unsigned yScreen;
    double depth = 0.0;

    Vector3D worldPosition;
    Vector3D normal;
    // Vector2D uv;

    double lightIntensity = 1.0;

    // Where to calculate the colour?
    // If the fragment colour depends on the fragment itself -> Fragment shader.
    // If the fragment colour depends on the relationship with
    // its primitive -> Before fragment shader.
    RestrictedColour colour;
};

// ============================================================================
// EOF
// ============================================================================
