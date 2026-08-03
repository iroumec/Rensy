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

// ----------------------------------------------------------------------------
// Fragment Colour
// ----------------------------------------------------------------------------

class FragmentColour
{
    Colour colour;
    bool locked = false;

public:
    void lock()
    {
        locked = true;
    }

    void unlock()
    {
        locked = false;
    }

    void set(const Colour &c)
    {
        if (!locked)
            colour = c;
    }

    const Colour &get() const
    {
        return colour;
    }
};

// ----------------------------------------------------------------------------
// Fragment
// ----------------------------------------------------------------------------

export struct Fragment
{

    unsigned xScreen;
    unsigned yScreen;
    double depth = 0.0;

    BarycentricCoordinate barycentricCoordinates;

    Vector3D worldPosition;
    Vector3D normal;
    // Vector2D uv;

    FragmentColour colour;
};

// ============================================================================
// EOF
// ============================================================================
