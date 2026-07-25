module;

#include <string>

export module model_rasterizer;

import model;
import geometry;
import tgaimage;
import triangle_rasterizer;

vec2 projectVector(vec3 vector, unsigned width, unsigned height);

export template <class Rasterizer>
class ModelRasterizer
{
    const unsigned height;
    const unsigned width;
    TGAImage framebuffer;
    Rasterizer triangleRasterizer;

public:
    ~ModelRasterizer() = default;

    ModelRasterizer(unsigned height, unsigned width)
        : height{height}, width{width}, framebuffer(width, height, TGAImage::RGB) {}

    void draw(const Model &model, const TGAColour &lineColour, const TGAColour &vertexColour)
    {
        // Iterates through all triangles and draw them.
        for (unsigned i = 0; i < model.getNumberOfFaces(); i++)
        {
            vec2 a = projectVector(model.getVertex(i, 0), this->width, this->height);
            vec2 b = projectVector(model.getVertex(i, 1), this->width, this->height);
            vec2 c = projectVector(model.getVertex(i, 2), this->width, this->height);
            this->triangleRasterizer.draw(a, b, c, this->framebuffer, lineColour);
        }

        // The vertices are highlighted.
        for (unsigned i = 0; i < model.getNumberOfVertices(); i++)
        {
            vec3 originalVertex = model.getVertex(i);
            vec2 projectedVertex = projectVector(originalVertex, this->width, this->height);
            this->framebuffer.set(projectedVertex.x, projectedVertex.y, vertexColour);
        }
    }

    void renderTGAImage(const std::string path) const
    {

        this->framebuffer.write_tga_file(path);
    }
};

// Viewport transform.
vec2 projectVector(vec3 vector, unsigned width, unsigned height)
{
    // First, ortographics projection -> Z axis is discard.
    // Second, since the input models are scaled to have fir in the [-1.1]^3 world coordinates,
    // the vector is scaled to span the entire screen.
    vec2 out;
    out.x = (vector.x + 1.) * width / 2;
    out.y = (vector.y + 1.) * height / 2;

    return out;
}