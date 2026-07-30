module;

export module transform:projection_transform;

// ============================================================================
// Imports
// ============================================================================

import :base;
import matrix;

// ============================================================================
// Declaration
// ============================================================================

// ----------------------------------------------------------------------------
// Projection Transform
// ----------------------------------------------------------------------------

class ProjectionTransform : public Transform
{
protected:
    ProjectionTransform(const Matrix<double, 4, 4> &matrix);
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Perspective Projection
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Creates a perspective matrix.
export class PerspectiveProjection : public ProjectionTransform
{
public:
    PerspectiveProjection(double fieldOfView = 90.,
                          double aspect = 1.0,
                          double near = 0.1,
                          double far = 100.0);
};

using PerspectiveTransform = PerspectiveProjection;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Ortographic Projection
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

export class OrthographicProjection : public ProjectionTransform
{
public:
    OrthographicProjection(double left,
                           double right,
                           double bottom,
                           double top,
                           double near,
                           double far);
};

using OrthographicTransform = OrthographicProjection;

// ----------------------------------------------------------------------------
// Perspective Matrix
// ----------------------------------------------------------------------------

Matrix<double, 4, 4> makePerspectiveMatrix(
    double fieldOfView, double aspect, double near, double far);

// ============================================================================
// EOF
// ============================================================================
