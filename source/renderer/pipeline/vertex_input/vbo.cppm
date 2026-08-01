module;

#include <cmath>
#include <array>
#include <utility>
#include <ostream>

export module vertex_shader:vertex_in;

// ============================================================================
// Imports
// ============================================================================

import vector;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export struct VBO
{
    std::vector<VertexIn> vertices;

public:
    Vertex(const Vector3D &localPosition)
        : localPosition{localPosition} {}

    constexpr double &xLocal() { return localPosition.x(); }
    constexpr double &yLocal() { return localPosition.y(); }
    constexpr double &zLocal() { return localPosition.z(); }
    constexpr double xLocal() const { return localPosition.x(); }
    constexpr double yLocal() const { return localPosition.y(); }
    constexpr double zLocal() const { return localPosition.z(); }

    constexpr const Vector3D &getLocalPosition() const { return this->localPosition; }

    friend std::ostream &operator<<(std::ostream &out, const Vertex &vertex)
    {
        return out << vertex.localPosition;
    }
};

// ============================================================================
// EOF
// ============================================================================
