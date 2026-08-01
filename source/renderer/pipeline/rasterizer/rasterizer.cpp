module;

#include <cmath>
#include <memory>
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

// Delete then.
import rotation;
import radian;

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

// ----------------------------------------------------------------------------
// Scanline Rasterizer
// ----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
// Bounding Box Rasterizer
// ----------------------------------------------------------------------------

std::vector<Fragment> BoundingBoxRasterizer::
    rasterize(const Triangle &primitive) const override
{
    BoundingBox bbox = BoundingBox(a.getVector(), b.getVector(), c.getVector());

    int minX = std::max(0, static_cast<int>(bbox.minX));
    int maxX = std::min(static_cast<int>(buffer.getWidth() - 1), static_cast<int>(bbox.maxX));
    int minY = std::max(0, static_cast<int>(bbox.minY));
    int maxY = std::min(static_cast<int>(buffer.getHeight() - 1), static_cast<int>(bbox.maxY));

    if (DEBUG)
    {
        std::cout << "Bunding Box: " << std::endl;
        std::cout << "minX: " << minX << std::endl;
        std::cout << "maxX: " << maxX << std::endl;
        std::cout << "minY: " << minY << std::endl;
        std::cout << "maxY: " << maxY << std::endl;
    }

    std::shared_ptr<ColourIntensifier> colourIntensifier = nullptr;

    if (colourIntensifierFactory)
        colourIntensifier = colourIntensifierFactory->instance(a, b, c);

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
            if (colourIntensifier)
                colour = colourIntensifier->adjustColour(colour, coordinates);

            buffer.setColour(x, y, colour);
            buffer.setDepth(x, y, z);
        }
    }
}

/*
std::vector<Fragment> BoundingBoxRasterizer::
    rasterize(const Triangle &primitive) const override
{
    BoundingBox bbox = BoundingBox(a.getVector(), b.getVector(), c.getVector());

    int minX = std::max(0, static_cast<int>(bbox.minX));
    int maxX = std::min(static_cast<int>(buffer.getWidth() - 1), static_cast<int>(bbox.maxX));
    int minY = std::max(0, static_cast<int>(bbox.minY));
    int maxY = std::min(static_cast<int>(buffer.getHeight() - 1), static_cast<int>(bbox.maxY));

    if (DEBUG)
    {
        std::cout << "Bunding Box: " << std::endl;
        std::cout << "minX: " << minX << std::endl;
        std::cout << "maxX: " << maxX << std::endl;
        std::cout << "minY: " << minY << std::endl;
        std::cout << "maxY: " << maxY << std::endl;
    }

    std::shared_ptr<ColourIntensifier> colourIntensifier = nullptr;

    if (colourIntensifierFactory)
        colourIntensifier = colourIntensifierFactory->instance(a, b, c);

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
            if (colourIntensifier)
                colour = colourIntensifier->adjustColour(colour, coordinates);

            buffer.setColour(x, y, colour);
            buffer.setDepth(x, y, z);
        }
    }
}
*/

// ============================================================================
// EOF
// ============================================================================