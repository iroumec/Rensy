module;

#include <string>

export module drawer;

import model;
import tgaimage;
import geometry;

export class Drawer
{
    const unsigned height;
    const unsigned width;
    TGAImage framebuffer;

public:
    Drawer(unsigned height, unsigned width) : height{height}, width{width}, framebuffer(width, height, TGAImage::RGB) {};
    void drawPoint(vec2 point, const TGAColour &colour);
    void drawLine(vec2 a, vec2 b, const TGAColour &colour);
    void drawModel(const Model &model, const TGAColour &lineColour, const TGAColour &vertexColour);
    void renderTGAImage(const std::string path) const;
    vec2 projectVector(vec3 vector) const;
};