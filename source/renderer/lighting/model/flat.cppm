module;

export module renderer:lighting.model.flat;

// ============================================================================
// Imports
// ============================================================================

import :lighting.model.base;
import :math.vector.vector_3d;
import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

// Calculates the light intensity using the centroid of a primitive.
// All fragment inside the primitive are asigned that same light intensity.
export class FlatLightingModel : public LightingModel
{
    const Vector3D lightPoint;
    const double ambientLight;

public:
    FlatLightingModel(const Vector3D &lightPoint, double ambientLight = 0.0)
        : lightPoint{lightPoint}, ambientLight{ambientLight} {}

    void processPrimitive(Primitive &primitive) const override;
};

// ============================================================================
// EOF
// ============================================================================