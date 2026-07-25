module;

#include <string>
#include <cmath>
#include <iostream>

module drawer;

import model;
import tgaimage;
import geometry;

constexpr bool DEBUG = false;

void Drawer::drawPoint(vec2 point, const TGAColour &colour)
{
    this->framebuffer.set(point.x, point.y, colour);
}

void Drawer::drawLine(vec2 a, vec2 b, const TGAColour &colour)
{
    /// Bresenham's line algorithm.
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

void Drawer::drawTriangle(vec2 a, vec2 b, vec2 c, const TGAColour &colour)
{
    this->drawLine(a, b, colour);
    this->drawLine(b, c, colour);
    this->drawLine(c, a, colour);
}

void Drawer::drawFilledTriangle(vec2 a, vec2 b, vec2 c, const TGAColour &colour)
{
    // Scanline rendering or scanline rasterization.

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
    for (unsigned y = top.y; y >= bottom.y; y--)
    {
        // Implementation logic in documentation/drawings/scanline.excalidraw.
        // For Y, which Xleft and Xright closures the segment of the triangle?
        unsigned rightX = interpolateX(top, bottom, y);
        unsigned leftX = (middle.y == top.y || middle.y > y) ? interpolateX(middle, bottom, y) : interpolateX(top, middle, y);
        if (middle.x > top.x)
            std::swap(leftX, rightX);

        if (DEBUG)
        {
            std::cout << "leftX: " << leftX << std::endl;
            std::cout << "rightX: " << rightX << std::endl;
        }

        // The segment is painted.
        for (unsigned x = leftX; x <= rightX; x++)
            this->framebuffer.set(x, y, colour);
    }
}

void Drawer::drawModel(const Model &model, const TGAColour &lineColour, const TGAColour &vertexColour)
{
    // Iterates through all triangles and draw them.
    for (unsigned i = 0; i < model.getNumberOfFaces(); i++)
    {
        vec2 a = projectVector(model.getVertex(i, 0));
        vec2 b = projectVector(model.getVertex(i, 1));
        vec2 c = projectVector(model.getVertex(i, 2));
        this->triangleRasterizer->draw(a, b, c, this->framebuffer, lineColour);
    }

    // The vertices are highlighted.
    for (unsigned i = 0; i < model.getNumberOfVertices(); i++)
    {
        vec3 originalVertex = model.getVertex(i);
        vec2 projectedVertex = projectVector(originalVertex);
        framebuffer.set(projectedVertex.x, projectedVertex.y, vertexColour);
    }
}

void Drawer::renderTGAImage(const std::string path) const
{

    this->framebuffer.write_tga_file(path);
}

// Viewport transform.
vec2 Drawer::projectVector(vec3 vector) const
{
    // First, ortographics projection -> Z axis is discard.
    // Second, since the input models are scaled to have fir in the [-1.1]^3 world coordinates,
    // the vector is scaled to span the entire screen.
    vec2 out;
    out.x = (vector.x + 1.) * this->width / 2;
    out.y = (vector.y + 1.) * this->height / 2;

    return out;
}
