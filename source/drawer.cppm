module;

#include <memory>
#include <string>

export module drawer;

import model;
import tgaimage;
import geometry;
import triangle_rasterizer;

export class Drawer
{
    const unsigned height;
    const unsigned width;
    TGAImage framebuffer;
    std::unique_ptr<TriangleRasterizer> triangleRasterizer;

public:
    Drawer(unsigned height, unsigned width)
        : Drawer(height, width, std::make_unique<BoundingBoxTriangleRasterizer>()) {}
    Drawer(unsigned height, unsigned width, std::unique_ptr<TriangleRasterizer> rasterizer)
        : height{height},
          width{width},
          framebuffer(width, height, TGAImage::RGB),
          triangleRasterizer{std::move(rasterizer)} {}
    void drawPoint(vec2 point, const TGAColour &colour);
    void drawLine(vec2 a, vec2 b, const TGAColour &colour);
    void drawTriangle(vec2 a, vec2 b, vec2 c, const TGAColour &colour);
    void drawFilledTriangle(vec2 a, vec2 b, vec2 c, const TGAColour &colour);
    void drawModel(const Model &model, const TGAColour &lineColour, const TGAColour &vertexColour);
    void renderTGAImage(const std::string path) const;
    vec2 projectVector(vec3 vector) const;
};