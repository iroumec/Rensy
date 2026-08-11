module;

#include <array>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :clipping.volume;
import :structure.vertex_out;

// ============================================================================
// Declarations
// ============================================================================

const std::array<ClipPlane, 6> &ClipVolume::getPlanes() const
{
    return this->planes;
}

bool ClipVolume::inside(const VertexOut &vertex) const
{
    for (const ClipPlane &plane : this->planes)
    {
        if (!plane.inside(vertex.clipPosition))
            return false;
    }

    return true;
}

// ============================================================================
// EOF
// ============================================================================
