module;

export module renderer:colour.lighting.flat;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :structure.vertex_out;
import :colour.lighting.base;
import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

export class FlatLightingModel : public LightingModel
{
public:
    virtual void processVertex(VertexOut &) {}
    virtual void processPrimitive(Primitive &) {}
    virtual void processFragment(Fragment &) {}
};

// ============================================================================
// EOF
// ============================================================================