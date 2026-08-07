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

/**
 * A lighting model changes the light intensity of a vertex, primitive (and,
 * hence, its vertices) or fragment.
 */
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