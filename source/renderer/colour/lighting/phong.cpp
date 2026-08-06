module;

#include <cmath>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :colour.lighting.phong;

// ============================================================================
// Declarations
// ============================================================================

void PhongLightingModel::processFragment(Fragment &fragment)
{
    // Light direction calculation.
    Vector3D l = (this->lightPoint - fragment.worldPosition).normalize();

    // Light intensity calculation.
    // double lightIntensity = std::max(0.0, n.dot(l));
    // The fragment normal is already interpolated.
    double lightIntensity = std::abs(fragment.normal.dot(l));

    fragment.colour.set(
        fragment.colour.get() * (this->ambientLight + lightIntensity));
}

// ============================================================================
// EOF
// ============================================================================