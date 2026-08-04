module;

export module renderer:colour.restricted;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;

// ============================================================================
// Declarations
// ============================================================================

class RestrictedColour
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

// ============================================================================
// EOF
// ============================================================================
