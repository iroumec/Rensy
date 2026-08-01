module;

#include <cmath>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import bbox;
import vector;
import matrix;
import geometry;
import barycentric;
import :structure.triangle;
import :structure.fragment;

// ============================================================================
// Constants
// ============================================================================

constexpr bool DEBUG = false;

// ============================================================================
// Implementations
// ============================================================================

// ----------------------------------------------------------------------------
// Vertex Rasterizer
// ----------------------------------------------------------------------------

/*
std::vector<Fragment> VertexRasterizer::
    rasterize(const Triangle &primitive) const override
{

    buffer.setColour(a.xScreen(), a.yScreen(), a.getColour());
    buffer.setColour(b.x(), b.y(), b.getColour());
    buffer.setColour(c.x(), c.y(), c.getColour());
}

// ----------------------------------------------------------------------------
// Wireframe Rasterizer
// ----------------------------------------------------------------------------

void WireframeRasterizer::
    drawLine(Vertex a, Vertex b, FrameBuffer &buffer) const
{
    /// Bresenham's line algorithm (variant with barycentric coordinates).
    // Is the line more vertical than horizontal?
    bool steep = std::abs(a.x() - b.x()) < std::abs(a.y() - b.y());
    if (steep)
    { // If that's the case, the image is transposed.
        std::swap(a.x(), a.y());
        std::swap(b.x(), b.y());
    }

    // Due to x increasing in the below loop, and it starting
    // at ax, it cannot draw right-to-left lines.
    if (a.x() > b.x())
    { // Make it left-to-right.
        std::swap(a.x(), b.x());
        std::swap(a.y(), b.y());
    }

    for (int x = a.x(); x <= b.x(); ++x)
    {
        int y = round(interpolateY(a.getVector(), b.getVector(), x));

        // If the image was transposed (steep), it's de-transposed.
        if (steep)
            buffer.setColour(y, x, a.getColour()); // TODO: Change the colour generation.
        else
            buffer.setColour(x, y, a.getColour()); // TODO: Change the oclpur generation.
    }
}

std::vector<Fragment> WireframeRasterizer::
    rasterize(const Triangle &primitive) const override
{
    // This order is important for circular colour generators.
    this->drawLine(a, b, buffer);
    this->drawLine(c, a, buffer);
    this->drawLine(b, c, buffer);
}

*/

// ----------------------------------------------------------------------------
// Scanline Rasterizer
// ----------------------------------------------------------------------------

/*
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

std::vector<Fragment> ScanlineRasterizer::
    rasterize(const Triangle &primitive) const override
{
    // Vertices ordering.
    auto orderedVertices = orderByAscendingAxisY(a, b, c);

    Vertex top = orderedVertices[2];
    Vertex middle = orderedVertices[1];
    Vertex bottom = orderedVertices[0];

    if (DEBUG)
    {
        std::cout << "Top: " << top << std::endl;
        std::cout << "Middle: " << middle << std::endl;
        std::cout << "Bottom: " << bottom << std::endl;
    }

    // The triangle is scanned row by row (scanline).
    // Each value of y is a scanline.
    // The scanning can be top to bottom or bottom to top.
    for (unsigned y = bottom.y(); y <= top.y(); y++)
    {

        // Implementation logic in documentation/drawings/scanline.excalidraw.
        // For Y, which Xleft and Xright closures the segment of the triangle?
        unsigned rightX = interpolateX(bottom.getVector(), top.getVector(), y);
        unsigned leftX = (middle.y() == top.y() || middle.y() > y)
                             ? interpolateX(bottom.getVector(), middle.getVector(), y)
                             : interpolateX(middle.getVector(), top.getVector(), y);
        if (middle.x() > top.x())
            std::swap(leftX, rightX);

        if (DEBUG)
        {
            std::cout << "leftX: " << leftX << std::endl;
            std::cout << "rightX: " << rightX << std::endl;
        }

        // The segment is painted.
        for (unsigned x = leftX; x <= rightX; x++)
            buffer.setColour(x, y, top.getColour()); // TODO: Fix this.
    }
}
*/

// ----------------------------------------------------------------------------
// Bounding Box Rasterizer
// ----------------------------------------------------------------------------

std::vector<Fragment> BoundingBoxRasterizer::
    rasterize(const Triangle &primitive) const override
{
    std::vector<Fragment> fragments;

    BoundingBox bbox = BoundingBox(a.getVector(), b.getVector(), c.getVector());

    int minX = std::max(0, static_cast<int>(bbox.minX));
    int maxX = std::min(static_cast<int>(buffer.getWidth() - 1), static_cast<int>(bbox.maxX));
    int minY = std::max(0, static_cast<int>(bbox.minY));
    int maxY = std::min(static_cast<int>(buffer.getHeight() - 1), static_cast<int>(bbox.maxY));

    Vector3D a = primitive.v0.screenPosition;
    Vector3D b = primitive.v1.screenPosition;
    Vector3D c = primitive.v2.screenPosition;

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            // Barycentric coordinates obtention.
            BarycentricCoordinate barycentricCoordinates =
                getBarycentricCoordinates(
                    a, b, c,
                    Vector2D{static_cast<double> x, static_cast<double> y});

            // If the point is not inside the triangle, it is discarded.
            if (barycentricCoordinates.isInsideTriangle())
            {
                // If the point isn't valid in the drawing pattern, it's discarded.
                if (drawingPattern != nullptr && !drawingPattern->isValid(coordinates))
                    continue;

                Fragment fragment;

                fragment.xScreen = x;
                fragment.yScreen = y;
                fragment.depth = barycentricCoordinates.alpha * a.z() +
                                 barycentricCoordinates.beta * b.z() +
                                 barycentricCoordinates.gamma * c.z();

                fragment.barycentricCoordinates = barycentricCoordinates;

                /*
                fragment.worldPosition =
                    barycentricCoordinates.alpha * primitive.v0.worldPosition +
                    barycentricCoordinates.beta * primitive.v1.worldPosition +
                    barycentricCoordinates.gamma * primitive.v2.worldPosition;

                fragment.normal =
                    alpha * primitive.v0.normal +
                    beta * primitive.v1.normal +
                    gamma * primitive.v2.normal;

                fragment.uv =
                    alpha * primitive.v0.uv +
                    beta * primitive.v1.uv +
                    gamma * primitive.v2.uv;

                fragment.colour =
                    alpha * primitive.v0.colour +
                    beta * primitive.v1.colour +
                    gamma * primitive.v2.colour;
                */
                fragments.push_back(fragment);
            }
        }
    }
}

// ============================================================================
// EOF
// ============================================================================