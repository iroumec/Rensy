module;

#include <cmath>
#include <vector>

export module renderer:colour.shading.instance.phong;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :math.vector.vector_3d;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class PhongShading : public Shading
{
    const Vector3D lightPoint;
    const std::vector<Vector3D> normals;
    const double ambientLight;

public:
    PhongShading(
        const Vector3D &lightPoint,
        const std::vector<Vector3D> &normals,
        double ambientLight = 0.2)
        : lightPoint(lightPoint), normals(normals), ambientLight(ambientLight) {}

    constexpr void adjustColour(Fragment &fragment) const override
    {
        // Light direction calculation.
        Vector3D l = (this->lightPoint - fragment.worldPosition).normalize();

        // Light intensity calculation.
        // double lightIntensity = std::max(0.0, n.dot(l));
        // The fragment normal is already interpolated.
        double lightIntensity = std::abs(fragment.normal.dot(l));

        fragment.colour.set(
            fragment.colour.get() * (ambientLight + lightIntensity));
    }
};

// ============================================================================
// EOF
// ============================================================================
