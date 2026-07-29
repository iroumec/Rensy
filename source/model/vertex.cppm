module;

#include <cmath>
#include <array>
#include <utility>
#include <ostream>

export module vertex;

import vector;
import colour;

export class Vertex
{
    Vector3D vector;
    Colour colour;

public:
    Vertex(const Vector3D &vector, const Colour &colour)
        : vector{vector}, colour{colour} {}

    constexpr double &x() { return vector.x(); }
    constexpr double &y() { return vector.y(); }
    constexpr double &z() { return vector.z(); }
    constexpr double x() const { return vector.x(); }
    constexpr double y() const { return vector.y(); }
    constexpr double z() const { return vector.z(); }

    constexpr const Vector3D &getVector() const { return this->vector; }
    constexpr const Colour &getColour() const { return this->colour; }

    constexpr operator Vector3D() const
    {
        return this->vector;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vertex &vertex)
    {
        return out << vertex.vector;
    }
};

export std::array<Vertex, 3>
orderByAscendingAxisY(Vertex a, Vertex b, Vertex c)
{
    if (a.y() > b.y())
        std::swap(a, b);
    if (a.y() > c.y())
        std::swap(a, c);
    if (b.y() > c.y())
        std::swap(b, c);

    return {a, b, c};
}