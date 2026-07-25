module;

#include <string>
#include <cmath>
#include <iostream>

module drawer;

import model;
import tgaimage;
import geometry;

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
