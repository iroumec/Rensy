module;

#include <cmath>
#include <iostream>

module rasterizer;

import bbox;
import buffer;
import colour;
import geometry;

constexpr bool DEBUG = false;

void VertexRasterizer::draw(vec3 a, vec3 b, vec3 c, FrameBuffer &framebuffer, const Colour &colour)
{
    framebuffer.setColour(a.x, a.y, colour);
    framebuffer.setColour(b.x, b.y, colour);
    framebuffer.setColour(c.x, c.y, colour);
}

void WireframeRasterizer::drawLine(vec3 a, vec3 b, FrameBuffer &framebuffer, const Colour &colour)
{
    /// Bresenham's line algorithm (variant with barycentric coordinates).
    // Is the line more vertical than horizontal?
    bool steep = std::abs(a.x - b.x) < std::abs(a.y - b.y);
    if (steep)
    { // If that's the case, the image is transposed.
        std::swap(a.x, a.y);
        std::swap(b.x, b.y);
    }

    // Due to x increasing in the below loop, and it starting
    // at ax, it cannot draw right-to-left lines.
    if (a.x > b.x)
    { // Make it left-to-right.
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);
    }

    for (int x = a.x; x <= b.x; x++)
    {
        int y = interpolateY(a, b, x);
        if (steep) // If the image was transposed, it's de-transposed.
            framebuffer.setColour(y, x, colour);
        else
            framebuffer.setColour(x, y, colour);
    }
}

void WireframeRasterizer::draw(vec3 a, vec3 b, vec3 c, FrameBuffer &framebuffer, const Colour &colour)
{
    this->drawLine(a, b, framebuffer, colour);
    this->drawLine(a, c, framebuffer, colour);
    this->drawLine(b, c, framebuffer, colour);
}

void ScanlineRasterizer::draw(vec3 a, vec3 b, vec3 c, FrameBuffer &framebuffer, const Colour &colour)
{
    // Vertices ordering.
    auto orderedVertices = orderByAscendingAxisY(a, b, c);

    vec3 top = orderedVertices[2];
    vec3 middle = orderedVertices[1];
    vec3 bottom = orderedVertices[0];

    if (DEBUG)
    {
        std::cout << "Top: " << top << std::endl;
        std::cout << "Middle: " << middle << std::endl;
        std::cout << "Bottom: " << bottom << std::endl;
    }

    // The triangle is scanned row by row (scanline).
    // Each value of y is a scanline.
    // The scanning can be top to bottom or bottom to top.
    for (unsigned y = bottom.y; y <= top.y; y++)
    {

        // Implementation logic in documentation/drawings/scanline.excalidraw.
        // For Y, which Xleft and Xright closures the segment of the triangle?
        unsigned rightX = interpolateX(bottom, top, y);
        unsigned leftX = (middle.y == top.y || middle.y > y) ? interpolateX(bottom, middle, y) : interpolateX(middle, top, y);
        if (middle.x > top.x)
            std::swap(leftX, rightX);

        if (DEBUG)
        {
            std::cout << "leftX: " << leftX << std::endl;
            std::cout << "rightX: " << rightX << std::endl;
        }

        // The segment is painted.
        for (unsigned x = leftX; x <= rightX; x++)
            framebuffer.setColour(x, y, colour);
    }
}

void BoundingBoxRasterizer::draw(vec3 a, vec3 b, vec3 c, FrameBuffer &framebuffer, const Colour &colour)
{
    BoundingBox bbox = BoundingBox(a, b, c);

    for (double y = bbox.minY; y <= bbox.maxY; y++)
    {
        for (double x = bbox.minX; x <= bbox.maxX; x++)
        {
            BarycentricCoordinate coordinates = getBarycentricCoordinates(a, b, c, vec2{x, y});
            if (coordinates.alpha < 0 || coordinates.beta < 0 || coordinates.gamma < 0)
                continue; // Outside the triangle.
            double z = coordinates.alpha * a.z + coordinates.beta * b.z + coordinates.gamma * c.z;
            if (framebuffer.isCurrentDepthLower(x, y, z))
                continue;
            framebuffer.setColour(x, y, colour);
            framebuffer.setDepth(x, y, z);
        }
    }
}