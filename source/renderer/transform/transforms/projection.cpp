module;

#include <cmath>
#include <cassert>
#include <numbers>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :math.matrix;

// ============================================================================
// Implementations
// ============================================================================

// ----------------------------------------------------------------------------
// Projection Transform
// ----------------------------------------------------------------------------

ProjectionTransform::ProjectionTransform(const Matrix<double, 4, 4> &matrix)
    : Transform(matrix) {}

NoProjection::NoProjection()
    : ProjectionTransform(Matrix<double, 4, 4>::getIdentity()) {}

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

PerspectiveProjection::PerspectiveProjection(double focalLength)
    : ProjectionTransform(
          makePerspectiveMatrix(focalLength)) {}

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

Matrix<double, 4, 4> makePerspectiveMatrix(
    double focalLength)
{
    assert(focalLength > 0);

    return {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, -1. / focalLength, 1}};
}

// ============================================================================
// EOF
// ============================================================================
