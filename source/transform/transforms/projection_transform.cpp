module;

#include <cmath>
#include <cassert>
#include <numbers>

module transform;

// ============================================================================
// Imports
// ============================================================================

import vector;
import matrix;

// ============================================================================
// Implementations
// ============================================================================

// ----------------------------------------------------------------------------
// Projection Transform
// ----------------------------------------------------------------------------

ProjectionTransform::ProjectionTransform(const Matrix<double, 4, 4> &matrix)
    : Transform(matrix) {}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Ortographic Projection
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Perspective Projection
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PerspectiveProjection::PerspectiveProjection(
    double fieldOfView, double aspect, double near, double far)
    : ProjectionTransform(
          makePerspectiveMatrix(fieldOfView, aspect, near, far)) {}

// ----------------------------------------------------------------------------
// Perspective Matrix
// ----------------------------------------------------------------------------

Matrix<double, 4, 4> makePerspectiveMatrix(
    double fieldOfView, double aspect, double near, double far)
{
    double scale = 1 / std::tan(fieldOfView * 0.5 * std::numbers::pi / 180);

    return Matrix<double, 4, 4>{
        {scale / aspect, 0, 0, 0},
        {0, scale, 0, 0},
        {0, 0, -(far + near) / (far - near),
         -(2 * far * near) / (far - near)},
        {0, 0, -1, 0}};
}

// ============================================================================
// EOF
// ============================================================================
