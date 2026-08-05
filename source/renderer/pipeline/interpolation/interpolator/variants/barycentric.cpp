module;

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :math.vector.vector_3d;
import :pipeline.interpolation.interpolator.barycentric;

// ============================================================================
// Declarations
// ============================================================================

Vector3D BarycentricInterpolator::interpolate(
    const Vector3D &a,
    const Vector3D &b,
    const Vector3D &c,
    const BarycentricCoordinate &bc) const
{
    return bc.alpha * a + bc.beta * b + bc.gamma * c;
}

double BarycentricInterpolator::interpolate(
    const double &a,
    const double &b,
    const double &c,
    const BarycentricCoordinate &bc) const
{
    return bc.alpha * a + bc.beta * b + bc.gamma * c;
}

// ============================================================================
// EOF
// ============================================================================
