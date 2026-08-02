module;

#include <cmath>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :math.matrix;
import :transform.rotation;

// ============================================================================
// Implementations
// ============================================================================

// ----------------------------------------------------------------------------
// Rotation Transform
// ----------------------------------------------------------------------------

RotationTransform::RotationTransform(const Rotation &rotation)
    : Transform(makeRotationMatrix(rotation)) {}

// ----------------------------------------------------------------------------
// Rotation Matrix
// ----------------------------------------------------------------------------

Matrix<double, 4, 4> makeRotationMatrix(const Rotation &rotation)
{
    Matrix<double, 4, 4> result = Matrix<double, 4, 4>::getIdentity();

    double radians = rotation.x();

    if (radians != 0.0)
    {
        Matrix<double, 4, 4> Rx =
            {
                {1, 0, 0, 0},
                {0, std::cos(radians), -std::sin(radians), 0},
                {0, std::sin(radians), std::cos(radians), 0},
                {0, 0, 0, 1}};

        result = Rx;
    }

    radians = rotation.y();

    if (radians != 0.0)
    {
        Matrix<double, 4, 4> Ry =
            {
                {std::cos(radians), 0, std::sin(radians), 0},
                {0, 1, 0, 0},
                {-std::sin(radians), 0, std::cos(radians), 0},
                {0, 0, 0, 1}};

        result = Ry * result;
    }

    radians = rotation.z();

    if (radians != 0.0)
    {
        Matrix<double, 4, 4> Rz =
            {
                {std::cos(radians), -std::sin(radians), 0, 0},
                {std::sin(radians), std::cos(radians), 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}};

        result = Rz * result;
    }

    return result;
}

// ============================================================================
// EOF
// ============================================================================
