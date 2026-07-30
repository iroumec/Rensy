module;

#include <cmath>
#include <iostream>
#include <algorithm>

module rasterizer;

// ============================================================================
// Imports
// ============================================================================

import bbox;
import model;
import buffer;
import colour;
import vector;
import vertex;
import matrix;
import geometry;
import clipping;
import transform;
import perspective;
import barycentric;

// ============================================================================
// Constants
// ============================================================================

constexpr bool DEBUG = false;

// ============================================================================
// Implementations
// ============================================================================

// ----------------------------------------------------------------------------
// Rasterizer (Base Class)
// ----------------------------------------------------------------------------

void Rasterizer::draw(
    const Model &model,
    FrameBuffer &buffer,
    const ColourGenerator &colourGenerator,
    const MVPTransform &mvpTransform) const
{

    ViewportTransform viewportTransform(buffer.getWidth(), buffer.getHeight());

    // Iterates through all triangles and draw them.
    for (unsigned i = 0; i < model.getNumberOfFaces(); i++)
    {
        // Model coordinates.
        Vector4D v0Local(model.getVertex(i, 0));
        Vector4D v1Local(model.getVertex(i, 1));
        Vector4D v2Local(model.getVertex(i, 2));

        // Transformation to homogeneous clip space.
        Vector4D v0Clip = mvpTransform.apply(v0Local);
        Vector4D v1Clip = mvpTransform.apply(v1Local);
        Vector4D v2Clip = mvpTransform.apply(v2Local);

        std::cout << "v0Clip: " << v0Clip << std::endl;
        std::cout << "v1Clip: " << v1Clip << std::endl;
        std::cout << "v2Clip: " << v2Clip << std::endl;

        // Clipping space validation.
        if (/*insideClipVolume(v0Clip) &&
            insideClipVolume(v1Clip) &&
            insideClipVolume(v2Clip)*/
            v0Clip.w() > 0.001 &&
            v1Clip.w() > 0.001 && v2Clip.w() > 0.001)
        {
            // Screen space transformation (NDC -> Viewport).
            Vector4D a = viewportTransform.apply(getNDC(v0Clip));
            Vector4D b = viewportTransform.apply(getNDC(v1Clip));
            Vector4D c = viewportTransform.apply(getNDC(v2Clip));

            this->draw(
                {a, colourGenerator()},
                {b, colourGenerator()},
                {c, colourGenerator()},
                buffer);
        }
    }
}

// ----------------------------------------------------------------------------
// Vertex Rasterizer
// ----------------------------------------------------------------------------

void VertexRasterizer::
    draw(Vertex a, Vertex b, Vertex c, FrameBuffer &buffer) const
{
    buffer.setColour(a.x(), a.y(), a.getColour());
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

void WireframeRasterizer::
    draw(Vertex a, Vertex b, Vertex c, FrameBuffer &buffer) const
{
    // This order is important for circular colour generators.
    this->drawLine(a, b, buffer);
    this->drawLine(c, a, buffer);
    this->drawLine(b, c, buffer);
}

// ----------------------------------------------------------------------------
// Scanline Rasterizer
// ----------------------------------------------------------------------------

void ScanlineRasterizer::
    draw(Vertex a, Vertex b, Vertex c, FrameBuffer &buffer) const
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

// ----------------------------------------------------------------------------
// Bounding Box Rasterizer
// ----------------------------------------------------------------------------

void BoundingBoxRasterizer::
    draw(Vertex a, Vertex b, Vertex c, FrameBuffer &buffer) const
{
    BoundingBox bbox = BoundingBox(a.getVector(), b.getVector(), c.getVector());

    int minX = std::max(0, static_cast<int>(bbox.minX));
    int maxX = std::min(static_cast<int>(buffer.getWidth() - 1), static_cast<int>(bbox.maxX));
    int minY = std::max(0, static_cast<int>(bbox.minY));
    int maxY = std::min(static_cast<int>(buffer.getHeight() - 1), static_cast<int>(bbox.maxY));

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            // Barycentric coordinates obtention.
            BarycentricCoordinate coordinates = getBarycentricCoordinates(
                a.getVector(), b.getVector(), c.getVector(),
                Vector2D{(double)x, (double)y});

            // If the point is not inside the triangle, it is discarded.
            if (!coordinates.isInsideTriangle())
                continue;

            // If the point isn't valid in the drawing pattern, it's discarded.
            if (drawingPattern != nullptr && !drawingPattern->isValid(coordinates))
                continue;

            // Depth calculation.
            double z =
                coordinates.alpha * a.z() +
                coordinates.beta * b.z() +
                coordinates.gamma * c.z();

            // If the new depth is higher than the stored one, continue.
            if (buffer.isStoredDepthLower(x, y, z))
                continue;

            // Colour calculation and adjusting.
            Colour colour = this->colourCalculator.calculateColour(a, b, c, coordinates);
            if (colourIntensifier != nullptr)
                colour = colourIntensifier->adjustColour(colour, a, b, c, coordinates);

            buffer.setColour(x, y, colour);
            buffer.setDepth(x, y, z);
        }
    }
}

// ============================================================================
// EOF
// ============================================================================