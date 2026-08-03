module;

export module renderer:structure.vertex_out;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :math.vector.vector_2d;
import :math.vector.vector_3d;
import :math.vector.vector_4d;

// ============================================================================
// Declarations
// ============================================================================

export struct VertexOut
{
    Vector3D worldPosition; // For lighting / shdadows.
    Vector4D clipPosition;  // After MVP.
    Vector3D ndcPosition;
    Vector3D screenPosition; // For viewport. // TODO: cambiar a 2D.
                             // const Vector3D normal;         // For Phong, Goraud...
    Vector3D worldNormal;
    Vector3D viewNormal;
    Colour colour;
};

// ============================================================================
// EOF
// ============================================================================
