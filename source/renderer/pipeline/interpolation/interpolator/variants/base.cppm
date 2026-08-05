module;

export module renderer:pipeline.interpolation.interpolator.base;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :math.vector.vector_3d;

// ============================================================================
// Declarations
// ============================================================================

export class Interpolator
{
public:
    virtual Vector3D interpolate(
        const Vector3D &a,
        const Vector3D &b,
        const Vector3D &c,
        const BarycentricCoordinate &bc) const = 0;

    virtual double interpolate(
        const double &a,
        const double &b,
        const double &c,
        const BarycentricCoordinate &bc) const = 0;
};

// ============================================================================
// EOF
// ============================================================================