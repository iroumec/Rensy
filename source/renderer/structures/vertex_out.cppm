module;

export module vertex_out;

// ============================================================================
// Imports
// ============================================================================

import vector;
import colour;

// ============================================================================
// Declarations
// ============================================================================

export struct VertexOut
{
    const Vector3D worldPosition; // For lighting / shdadows.
    const Vector4D clipPosition;  // After MVP.
    const Vector3D ndcPosition;
    const Vector3D screenPosition; // For viewport.
    // const Vector3D normal;         // For Phong, Goraud...
    const Colour colour;
};

// ============================================================================
// EOF
// ============================================================================
