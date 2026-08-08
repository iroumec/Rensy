module;

export module renderer:lighting.model.gouraud;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :lighting.model.base;
import :structure.vertex_out;
import :math.vector.vector_3d;
import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

// Calculates the light intensity per vertex. Then, the light intensity
// of a fragment it's the interpolation of all the light intensities of all
// the vertices of it primitive.
export class GouraudLightingModel : public LightingModel
{
    const Vector3D lightPoint;
    const double ambientLight;

public:
    GouraudLightingModel(const Vector3D &lightPoint, double ambientLight = 0.0)
        : lightPoint{lightPoint}, ambientLight{ambientLight} {}

    void processVertex(VertexOut &vertex) const override;
};

// ============================================================================
// EOF
// ============================================================================