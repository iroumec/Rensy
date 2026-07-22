#include <cmath>
#include "tgaimage.h"

constexpr TGAColor white = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

/// Bresenham's line algorithm.
void draw_line(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor colour)
{
    for (float t = 0.; t < 1.; t += 0.02) // 0.02 already gives a continue line. Using a greater value could produce a discontinue line.
    {
        int x = t * (bx - ax) + ax;
        int y = t * (by - ay) + ay;
        framebuffer.set(x, y, colour);
    }
}

int main(int argc, char **argv)
{
    // Image dimensions.
    constexpr int width = 64;
    constexpr int height = 64;

    // Framebuffer creation.
    TGAImage framebuffer(width, height, TGAImage::RGB);

    // The x and y coordinates of three points are stablished.
    // Of course, the coordinates must be in the range defined.
    // X in [0, 63] and Y in [0, 63], where X and Y are integer values.
    int ax = 7, ay = 3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    // We connect the previous points using lines.
    draw_line(ax, ay, bx, by, framebuffer, red);
    draw_line(ax, ay, cx, cy, framebuffer, green);
    draw_line(cx, cy, bx, by, framebuffer, blue);

    // We set a colour to the points previously defined.
    // It's important that this is made after the lines.
    // In other case, the points colour will be overlaped by the line colour.
    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);

    // A TGA image is rendered using the buffer information.
    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}
