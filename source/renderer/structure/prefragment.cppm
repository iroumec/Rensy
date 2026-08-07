module;

export module renderer:structure.prefragment;

// ============================================================================
// Imports
// ============================================================================

import :interpolation.data;

// ============================================================================
// Declarations
// ============================================================================

// World position, normal, depth and UV must already be interpolated.
// Fragment should not know any details about the method of rasterization. So
// it should not contain barycentric coordinates.
export struct PreFragment
{
    // A pre-fragment represents a sample created by the rasterizer. It is not yet
    // a fragment. Its attributes are not complete.
    unsigned xScreen;
    unsigned yScreen;

    double lightIntensity = 1.0;

    // Información necesaria para interpolar
    InterpolationData interpolationData;
};

// ============================================================================
// EOF
// ============================================================================