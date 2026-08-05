module;

export module renderer:pipeline.interpolation.interpolator.barycentric;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :math.vector.vector_3d;
import :pipeline.interpolation.interpolator.base;

// ============================================================================
// Declarations
// ============================================================================

export class BarycentricInterpolator : public Interpolator
{
public:
    Vector3D interpolate(
        const Vector3D &a,
        const Vector3D &b,
        const Vector3D &c,
        const BarycentricCoordinate &bc) const override;

    double interpolate(
        const double &a,
        const double &b,
        const double &c,
        const BarycentricCoordinate &bc) const override;
};

// ============================================================================
// EOF
// ============================================================================
