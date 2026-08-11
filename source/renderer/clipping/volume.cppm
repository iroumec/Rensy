module;

#include <array>

export module renderer:clipping.volume;

// ============================================================================
// Imports
// ============================================================================

import :clipping.plane;

// ============================================================================
// Forward Declarations
// ============================================================================

struct VertexOut;

// ============================================================================
// Declarations
// ============================================================================

// ClipPlane left{{1.0, 0.0, 0.0, 1.0}};   // x + w >= 0
// ClipPlane right{{-1.0, 0.0, 0.0, 1.0}}; // w - x >= 0

// ClipPlane bottom{{0.0, 1.0, 0.0, 1.0}}; // y + w >= 0
// ClipPlane top{{0.0, -1.0, 0.0, 1.0}};   // w - y >= 0

// ClipPlane near{{0.0, 0.0, 1.0, 1.0}}; // z + w >= 0
// ClipPlane far{{0.0, 0.0, -1.0, 1.0}}; // w - z >= 0

export class ClipVolume
{
    std::array<ClipPlane, 6> planes;

public:
    ClipVolume()
        : planes{
              ClipPlane{{1.0, 0.0, 0.0, 1.0}},  // Left
              ClipPlane{{-1.0, 0.0, 0.0, 1.0}}, // Right
              ClipPlane{{0.0, 1.0, 0.0, 1.0}},  // Bottom
              ClipPlane{{0.0, -1.0, 0.0, 1.0}}, // Top
              // ClipPlane{{0.0, 0.0, 1.0, 1.0}},  // Near
              // ClipPlane{{0.0, 0.0, -1.0, 1.0}}  // Far
              // TODO: near nad far planes must be activated later, when the frustrum plane works well.
          }
    {
    }

    const std::array<ClipPlane, 6> &getPlanes() const;

    bool inside(const VertexOut &vertex) const;
};

// ============================================================================
// EOF
// ============================================================================
