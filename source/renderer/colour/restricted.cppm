module;

export module renderer:colour.restricted;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;

// ============================================================================
// Declarations
// ============================================================================

export class RestrictedColour
{
    Colour colour;
    bool locked = false;

public:
    RestrictedColour() = default;
    ~RestrictedColour() = default;

    RestrictedColour(const Colour &colour, bool locked = false)
        : colour{colour}, locked{locked} {}

    RestrictedColour clone(const Colour &colour) const
    {
        if (locked)
            return RestrictedColour(this->colour, this->locked);
        else
            return RestrictedColour(colour);
    }

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
