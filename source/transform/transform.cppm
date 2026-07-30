module;

export module transform;

// ============================================================================
// Imports
// ============================================================================

import matrix;
import vector;
import rotation;

// ============================================================================
// Exports
// ============================================================================

export class RotationTransform;
export class ModelTransform;
// export class ViewTransform;
export class ProjectionTransform;
export class MVPTransform;
export class ViewportTransform;

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// Transform (Base Class)
// ----------------------------------------------------------------------------

class Transform
{
private:
    Matrix<double, 4, 4> matrix;

protected:
    Transform(const Matrix<double, 4, 4> &matrix);

public:
    const Matrix<double, 4, 4> &getMatrix() const;
    Vector4D apply(const Vector4D &vector) const;
};

// ----------------------------------------------------------------------------
// Viewport Transform
// ----------------------------------------------------------------------------

export class ViewportTransform : public Transform
{
public:
    // nX is the number of horizontal pixels.
    // ny is the number of vertical pixels.
    // Viewport Matrix.
    ViewportTransform(unsigned nX, unsigned nY);
};

using WindowingTransform = ViewportTransform;

// ----------------------------------------------------------------------------
// MVP Transform
// ----------------------------------------------------------------------------

export class MVPTransform : public Transform
{
    // Creates a Model-View-Projection Matrix.

public:
    MVPTransform(
        const ModelTransform &modelTransform,
        /*, const ViewTransform &viewTransform */
        const ProjectionTransform &projectionTransform);
};

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
    PerspectiveProjection(double focalLength = 3
                          /*double aspect,
                          double near,
                          double far*/
    );
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
// Model Transform
// ----------------------------------------------------------------------------

export class ModelTransform : public Transform
{
    // Creates a model transform matrix.

public:
    ModelTransform(const RotationTransform &rotationTransform);
};

// ----------------------------------------------------------------------------
// Rotation Transform
// ----------------------------------------------------------------------------

export class RotationTransform : public Transform
{
    // Creates a rotation matrix.

public:
    RotationTransform(const Rotation &rotation);
};