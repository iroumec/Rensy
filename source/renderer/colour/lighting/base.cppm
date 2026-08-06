module;

export module renderer:colour.lighting.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :structure.vertex_out;
import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

export class LightingModel
{
public:
    virtual ~LightingModel() = default;
    virtual void processVertex(VertexOut &) {}
    virtual void processPrimitive(Primitive &) {}
    virtual void processFragment(Fragment &) {}
};

// ============================================================================
// EOF
// ============================================================================