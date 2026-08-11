module;

export module renderer:clipping.plane;

// ============================================================================
// Imports
// ============================================================================

import :math.vector.vector_4d;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export struct ClipPlane
{
    Vector4D equation;

    double evaluate(const Vector4D &position) const
    {
        return equation.dot(position);
    }

    bool inside(const Vector4D &position) const
    {
        return evaluate(position) >= 0.0;
    }
};

// ============================================================================
// EOF
// ============================================================================