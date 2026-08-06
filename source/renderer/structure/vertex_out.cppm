module;

export module renderer:structure.vertex_out;

// ============================================================================
// Imports
// ============================================================================

import :colour.restricted;
import :math.vector.vector_2d;
import :math.vector.vector_3d;
import :math.vector.vector_4d;

// ============================================================================
// Declarations
// ============================================================================

export struct VertexOut
{
    Vector3D worldPosition; // For lighting / shdadows.
    Vector3D viewPosition;
    Vector4D clipPosition; // After MVP.
    Vector3D ndcPosition;
    Vector3D screenPosition; // For viewport. // TODO: cambiar a 2D.
                             // const Vector3D normal;         // For Phong, Goraud...
    Vector3D worldNormal;
    Vector3D viewNormal;
    double lightIntensity;
    RestrictedColour colour;

    VertexOut() = default;

    VertexOut(
        Vector3D worldPosition,
        Vector3D viewPosition,
        Vector4D clipPosition,
        Vector3D ndcPosition,
        Vector3D screenPosition,
        Vector3D worldNormal,
        Vector3D viewNormal,
        double lightIntensity,
        RestrictedColour colour)
        : worldPosition{worldPosition},
          viewPosition{viewPosition},
          clipPosition{clipPosition},
          ndcPosition{ndcPosition},
          screenPosition{screenPosition},
          worldNormal{worldNormal},
          viewNormal{viewNormal},
          lightIntensity{lightIntensity},
          colour{colour}
    {
    }

    VertexOut operator*(double value) const
    {
        return VertexOut(
            this->worldPosition * value,
            this->viewPosition * value,
            this->clipPosition * value,
            this->ndcPosition * value,
            this->screenPosition * value,
            this->worldNormal * value,
            this->viewNormal * value,
            this->lightIntensity * value,
            this->colour.clone(this->colour.get() * value));
    }

    VertexOut operator+(const VertexOut &other) const
    {
        return VertexOut(
            this->worldPosition + other.worldPosition,
            this->viewPosition + other.viewPosition,
            this->clipPosition + other.clipPosition,
            this->ndcPosition + other.ndcPosition,
            this->screenPosition + other.screenPosition,
            this->worldNormal + other.worldNormal,
            this->viewNormal + other.viewNormal,
            this->lightIntensity + other.lightIntensity,
            this->colour.clone(this->colour.get() + other.colour.get()));
    }

    VertexOut &operator+=(const VertexOut &other)
    {
        this->worldPosition += other.worldPosition;
        this->viewPosition += other.viewPosition;
        this->clipPosition += other.clipPosition;
        this->ndcPosition += other.ndcPosition;
        this->screenPosition += other.screenPosition;
        this->worldNormal += other.worldNormal;
        this->viewNormal += other.viewNormal;
        this->lightIntensity += other.lightIntensity;
        this->colour.set(this->colour.get() + other.colour.get());

        return *this;
    }
};

// ============================================================================
// EOF
// ============================================================================
