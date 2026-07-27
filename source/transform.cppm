module;

export module transform;

import matrix;
import vector;
import rotation;

export class RotationTransform;
export class ModelTransform;
// export class ViewTransform;
export class ProjectionTransform;
export class MVPTransform;
export class ViewportTransform;

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

export class ViewportTransform : public Transform
{
public:
    // nX is the number of horizontal pixels.
    // ny is the number of vertical pixels.
    // Viewport Matrix.
    ViewportTransform(unsigned nX, unsigned nY);
};

using WindowingTransform = ViewportTransform;

export class MVPTransform : public Transform
{
    // Creates a Model-View-Projection Matrix.

public:
    MVPTransform(
        const ModelTransform &modelTransform
        /*, const ViewTransform &viewTransform */
        /*,const ProjectionTransform &projectionTransform*/);
};

using ClipTransform = MVPTransform;

export class ModelTransform : public Transform
{
    // Creates a model transform matrix.

public:
    ModelTransform(const RotationTransform &rotationTransform);
};

export class ProjectionTransform : public Transform
{
public:
    // Distance to near plane.
    // Distance to far plane.
    ProjectionTransform(double near, double far);
};

export class RotationTransform : public Transform
{
    // Creates a rotation matrix.

public:
    RotationTransform(const Rotation &rotation);
};