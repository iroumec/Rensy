module;

export module renderer:structure.vertex_out;

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
    Vector3D worldPosition; // For lighting / shdadows.
    Vector4D clipPosition;  // After MVP.
    Vector3D ndcPosition;
    Vector3D screenPosition; // For viewport.
                             // const Vector3D normal;         // For Phong, Goraud...
    Colour colour;
};

// ============================================================================
// EOF
// ============================================================================
