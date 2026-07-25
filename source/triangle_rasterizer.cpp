module;

#include <cmath>
#include <iostream>

module triangle_rasterizer;

import bbox;
import geometry;

constexpr bool DEBUG = false;

void VertexTriangleRasterizer::draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour)
{
    framebuffer.set(a.x, a.y, colour);
    framebuffer.set(b.x, b.y, colour);
    framebuffer.set(c.x, c.y, colour);
}

void WireframeTriangleRasterizer::drawLine(vec2 a, vec2 b, TGAImage &framebuffer, const TGAColour &colour)
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
            framebuffer.set(y, x, colour);
        else
            framebuffer.set(x, y, colour);
    }
}

void WireframeTriangleRasterizer::draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour)
{
    this->drawLine(a, b, framebuffer, colour);
    this->drawLine(a, c, framebuffer, colour);
    this->drawLine(b, c, framebuffer, colour);
}

void ScanlineTriangleRasterizer::draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour)
{
    // Vertices ordering.
    auto orderedVertices = orderByAscendingAxisY(a, b, c);

    vec2 top = orderedVertices[2];
    vec2 middle = orderedVertices[1];
    vec2 bottom = orderedVertices[0];

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
            framebuffer.set(x, y, colour);
    }
}

void BoundingBoxTriangleRasterizer::draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour)
{
    BoundingBox bbox = BoundingBox(a, b, c);

    for (double y = bbox.minY; y <= bbox.maxY; y++)
    {
        for (double x = bbox.minX; x <= bbox.maxX; x++)
        {
            vec3 barycentricCoordinates = getBarycentricCoordinates(a, b, c, vec2{x, y});
            if (barycentricCoordinates.x < 0 || barycentricCoordinates.y < 0 || barycentricCoordinates.z < 0)
                continue; // Outside the triangle.
            framebuffer.set(x, y, colour);
        }
    }
}