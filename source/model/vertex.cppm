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
    const Vector3D worldPosition;  // For lighting / shdadows.
    const Vector4D screenPosition; // For viewport.
    // const Vector3D normal;         // For Phong, Goraud...
    const Colour colour;

public:
    Vertex(const Vector3D &worldPosition, const Vector4D &screenPosition, const Colour &colour)
        : worldPosition{worldPosition}, screenPosition{screenPosition}, colour{colour} {}

    constexpr double &xWorld() { return worldPosition.x(); }
    constexpr double &yWorld() { return worldPosition.y(); }
    constexpr double &zWorld() { return worldPosition.z(); }
    constexpr double xWorld() const { return worldPosition.x(); }
    constexpr double yWorld() const { return worldPosition.y(); }
    constexpr double zWorld() const { return worldPosition.z(); }

    constexpr double &xScreen() { return screenPosition.x(); }
    constexpr double &yScreen() { return screenPosition.y(); }
    constexpr double &zScreen() { return screenPosition.z(); }
    constexpr double &wScreen() { return screenPosition.w(); }
    constexpr double xScreen() const { return screenPosition.x(); }
    constexpr double yScreen() const { return screenPosition.y(); }
    constexpr double zScreen() const { return screenPosition.z(); }
    constexpr double wScreen() const { return screenPosition.w(); }

    constexpr const Vector3D &getWorldPosition() const { return this->wordPosition; }
    constexpr const Vector4D &getScreenPosition() const { return this->screenPosition; }
    constexpr const Colour &getColour() const { return this->colour; }

    friend std::ostream &operator<<(std::ostream &out, const Vertex &vertex)
    {
        return out << vertex.vector;
    }
};

export std::array<Vertex, 3>
orderByAscendingAxisY(Vertex a, Vertex b, Vertex c)
{
    if (a.yScreen() > b.yScreen())
        std::swap(a, b);
    if (a.yScreen() > c.yScreen())
        std::swap(a, c);
    if (b.yScreen() > c.yScreen())
        std::swap(b, c);

    return {a, b, c};
}