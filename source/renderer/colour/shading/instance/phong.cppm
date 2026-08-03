module;

#include <cmath>

export module renderer:colour.shading.instance.phong;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :structure.fragment;
import :math.vector.vector_3d;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class PhongShading : public Shading
{
    const Vector3D lightPoint;
    const Vector3D alphaNormal;
    const Vector3D betaNormal;
    const Vector3D gammaNormal;
    const double ambientLight;

public:
    PhongShading(
        const Vector3D &lightPoint, const Vector3D &alphaNormal,
        const Vector3D &betaNormal, const Vector3D &gammaNormal,
        double ambientLight = 0.2)
        : lightPoint(lightPoint), alphaNormal(alphaNormal),
          betaNormal(betaNormal), gammaNormal(gammaNormal),
          ambientLight(ambientLight) {}

    constexpr void adjustColour(Fragment &fragment) const override
    {
        BarycentricCoordinate coordinates = fragment.barycentricCoordinates;

        Vector3D interpolatedNormal =
            coordinates.alpha * alphaNormal +
            coordinates.beta * betaNormal +
            coordinates.gamma * gammaNormal;

        // Light direction calculation.
        Vector3D l = (this->lightPoint - fragment.worldPosition).normalize();

        // Light intensity calculation.
        // double lightIntensity = std::max(0.0, n.dot(l));
        double lightIntensity = std::abs(interpolatedNormal.dot(l));

        fragment.colour.set(
            fragment.colour.get() * (ambientLight + lightIntensity));
    }
};

// ============================================================================
// EOF
// ============================================================================
