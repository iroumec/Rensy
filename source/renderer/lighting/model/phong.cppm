module;

export module renderer:lighting.model.phong;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :lighting.model.base;
import :math.vector.vector_3d;

// ============================================================================
// Declarations
// ============================================================================

export class PhongLightingModel : public LightingModel
{
    const Vector3D lightPoint;
    const double ambientLight;

public:
    PhongLightingModel(const Vector3D &lightPoint, double ambientLight = 0.0)
        : lightPoint{lightPoint}, ambientLight{ambientLight} {}

    void processFragment(Fragment &fragment) const override;
};

// ============================================================================
// EOF
// ============================================================================