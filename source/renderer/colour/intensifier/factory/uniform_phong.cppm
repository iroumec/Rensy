module;

#include <cmath>
#include <memory>

export module renderer:colour.intensifier.factory.uniform_phong;

// ============================================================================
// Imports
// ============================================================================

import vertex;
import vector;
import :colour.intensifier.factory.base;
import :colour.intensifier.instance.base;
import :colour.intensifier.instance.uniform_phong;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class UniformPhongColourIntensifierFactory
    : public ColourIntensifierFactory
{
    const Vector3D lightPoint;

public:
    UniformPhongColourIntensifierFactory(const Vector3D &lightPoint)
        : lightPoint(lightPoint) {}

    std::shared_ptr<ColourIntensifier> instance(
        const Vertex &a, const Vertex &b, const Vertex &c) const override
    {
        // Normal vector calculation.
        Vector3D ab = b.getVector() - a.getVector();
        Vector3D ac = c.getVector() - a.getVector();
        Vector3D n = (ab.cross(ac)).normalize();

        // Midpoint calculation.
        Vector3D midpoint = Vector3D(
            (a.x() + b.x() + c.x()) / 3,
            (a.y() + b.y() + c.y()) / 3,
            (a.z() + b.z() + c.z()) / 3);

        // Light direction calculation.
        Vector3D l = (this->lightPoint - midpoint).normalize();

        // Light intensity calculation.
        // double lightIntensity = std::max(0.0, n.dot(l));
        double lightIntensity = std::abs(n.dot(l)); // Two points of lights.

        return std::make_shared<UniformPhongColourIntensifier>(lightIntensity);
    }
};

// ============================================================================
// EOF
// ============================================================================