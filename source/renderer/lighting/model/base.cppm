module;

export module renderer:lighting.model.base;

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
    virtual void processVertex(VertexOut &) const {}
    virtual void processPrimitive(Primitive &) const {}
    virtual void processFragment(Fragment &) const {}
};

// ============================================================================
// EOF
// ============================================================================