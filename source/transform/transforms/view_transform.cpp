module;

module transform;

// ============================================================================
// Imports
// ============================================================================

import vector;
import matrix;

// ============================================================================
// Implementation
// ============================================================================

// ----------------------------------------------------------------------------
// View Transform
// ----------------------------------------------------------------------------

ViewTransform::ViewTransform(
    const Vector3D &eye, const Vector3D &center, const Vector3D &up)
    : Transform(makeViewMatrix(eye, center, up)) {}

// ----------------------------------------------------------------------------
// View Matrix
// ----------------------------------------------------------------------------

Matrix<double, 4, 4> makeViewMatrix(
    const Vector3D &eye, const Vector3D &center, const Vector3D &up)
{
    Vector3D n = (eye - center).normalize();
    Vector3D l = (up.cross(n)).normalize();
    Vector3D m = (n.cross(l)).normalize();

    // Rotation matrix.
    Matrix<double, 4, 4> R = {{{l.x(), l.y(), l.z(), 0},
                               {m.x(), m.y(), m.z(), 0},
                               {n.x(), n.y(), n.z(), 0},
                               {0, 0, 0, 1}}};

    // Traslation matrix.
    Matrix<double, 4, 4> T = {{{1, 0, 0, -center.x()},
                               {0, 1, 0, -center.y()},
                               {0, 0, 1, -center.z()},
                               {0, 0, 0, 1}}};

    return Matrix<double, 4, 4>::getIdentity();

    return R * T;
}

// ============================================================================
// EOF
// ============================================================================