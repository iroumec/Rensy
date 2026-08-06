module;

export module renderer:colour.lighting.phong;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :colour.lighting.base;

// ============================================================================
// Declarations
// ============================================================================

export class PhongLightingModel : public LightingModel
{
    const Vector3D lightPoint;
    const double ambientLight;

public:
    PhongLightingModel(const Vector3D &lightPoint, double ambientLight)
        : lightPoint{lightPoint}, ambientLight{ambientLight} {}

    void processFragment(Fragment &fragment) override;
};

// ============================================================================
// EOF
// ============================================================================