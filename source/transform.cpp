module;

#include <cmath>

module transform;

namespace
{
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
}

Transform::Transform(const Matrix<double, 4, 4> &matrix)
    : matrix(matrix) {}

const Matrix<double, 4, 4> &Transform::getMatrix() const
{
    return matrix;
}

Vector4D Transform::apply(const Vector4D &vector) const
{
    return Vector4D(this->matrix * static_cast<Matrix<double, 4, 1>>(vector));
}

RotationTransform::RotationTransform(const Rotation &rotation)
    : Transform(makeRotationMatrix(rotation))
{
}

ModelTransform::ModelTransform(const RotationTransform &rotationTransform)
    : Transform(rotationTransform.getMatrix())
{
}

ProjectionTransform::ProjectionTransform(double near, double far)
    : Transform(Matrix<double, 4, 4>{
          {near, 0, 0, 0},
          {0, near, 0, 0},
          {0, 0, near + far, -far * near},
          {0, 0, 0, 1}}) {}

MVPTransform::MVPTransform(
    const ModelTransform &modelTransform
    /*const ViewTransform &viewTransform */
    /*, const ProjectionTransform &projectionTransform */)
    : Transform(
          // projectionTransform.getMatrix() *
          //  viewTransform.getMatrix() *
          modelTransform.getMatrix())
{
}

// First, ortographics projection -> Z axis is discard.
// Second, since the input models are scaled to have fir in the [-1.1]^3 world coordinates,
// the vector is scaled to span the entire screen.
ViewportTransform::ViewportTransform(unsigned nx, unsigned ny)
    : Transform(
          Matrix<double, 4, 4>{
              {nx / 2.0, 0, 0, (nx - 1) / 2.0},
              {0, ny / 2.0, 0, (ny - 1) / 2.0},
              {0, 0, 1, 0},
              {0, 0, 0, 1}})
{
}