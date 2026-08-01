module;

export module renderer:fragment;

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
    Colour colour;
    BarycentricCoordinates barycentricCoordinates;
};

// ============================================================================
// EOF
// ============================================================================
