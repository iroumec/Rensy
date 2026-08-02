module;

#include <cassert>
#include <iostream>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :math.matrix;
import :math.vector.vector_3d;

// ============================================================================
// Constants
// ============================================================================

constexpr bool DEBUG = false;

// ============================================================================
// Implementation
// ============================================================================

// ----------------------------------------------------------------------------
// View Transform
// ----------------------------------------------------------------------------

ViewTransform::ViewTransform(
    const Vector3D &eye, const Vector3D &gaze, const Vector3D &up)
    : Transform(makeViewMatrix(eye, gaze, up)) {}

// ----------------------------------------------------------------------------
// View Matrix
// ----------------------------------------------------------------------------

Matrix<double, 4, 4> makeViewMatrix(
    const Vector3D &eye, const Vector3D &gaze, const Vector3D &up)
{
    assert((eye - gaze).length() != 0);
    assert(up.length() != 0);

    Vector3D w = (eye - gaze).normalize();
    // Vector3D w = -(gaze).normalize();
    Vector3D u = (up.cross(w)).normalize();
    Vector3D v = w.cross(u);

    if (DEBUG)
    {
        std::cout << "Eye: " << eye << '\n';
        std::cout << "Gaze: " << gaze << '\n';
        std::cout << "Up: " << up << '\n';

        std::cout << w << " length=" << w.length() << '\n';
        std::cout << u << " length=" << u.length() << '\n';
        std::cout << v << " length=" << v.length() << '\n';
    }

    // Rotation matrix.
    Matrix<double, 4, 4> R = {{{u.x(), u.y(), u.z(), 0},
                               {v.x(), v.y(), v.z(), 0},
                               {w.x(), w.y(), w.z(), 0},
                               {0, 0, 0, 1}}};

    // Traslation matrix.
    Matrix<double, 4, 4> T = {{{1, 0, 0, -eye.x()},
                               {0, 1, 0, -eye.y()},
                               {0, 0, 1, -eye.z()},
                               {0, 0, 0, 1}}};

    if (DEBUG)
    {
        std::cout << R << '\n';
        std::cout << T << '\n';
    }

    return R * T;
}

// ============================================================================
// EOF
// ============================================================================
