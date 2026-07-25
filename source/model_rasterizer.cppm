module;

#include <string>

export module model_rasterizer;

import model;
import colour;
import buffer;
import geometry;
import tgaimage;
import rasterizer;

vec3 projectVector(vec3 vector, unsigned width, unsigned height);

export template <class Rasterizer>
class ModelRasterizer
{
    const unsigned height;
    const unsigned width;
    FrameBuffer buffer;
    Rasterizer rasterizer;

public:
    ~ModelRasterizer() = default;

    ModelRasterizer(unsigned height, unsigned width)
        : height{height},
          width{width},
          buffer(height, width) {}

    void draw(const Model &model, const ColourGenerator &colourGenerator)
    {
        // Iterates through all triangles and draw them.
        for (unsigned i = 0; i < model.getNumberOfFaces(); i++)
        {
            vec3 a = projectVector(model.getVertex(i, 0), this->width, this->height);
            vec3 b = projectVector(model.getVertex(i, 1), this->width, this->height);
            vec3 c = projectVector(model.getVertex(i, 2), this->width, this->height);
            this->rasterizer.draw(a, b, c, this->buffer, colourGenerator());
        }

        // The vertices are highlighted.
        for (unsigned i = 0; i < model.getNumberOfVertices(); i++)
        {
            vec3 originalVertex = model.getVertex(i);
            vec3 projectedVertex = projectVector(originalVertex, this->width, this->height);
            this->buffer.setColour(projectedVertex.x, projectedVertex.y, colourGenerator());
        }
    }

    void renderFrameBufferToTGAImage(const std::string path) const
    {
        this->buffer.renderColourBuffer(path);
    }

    void renderZBufferToTGAImage(const std::string path) const
    {
        this->buffer.renderDepthBuffer(path);
    }
};

// Viewport transform.
vec3 projectVector(vec3 vector, unsigned width, unsigned height)
{
    // First, ortographics projection -> Z axis is discard.
    // Second, since the input models are scaled to have fir in the [-1.1]^3 world coordinates,
    // the vector is scaled to span the entire screen.
    vec3 out;
    out.x = (vector.x + 1.) * width / 2;
    out.y = (vector.y + 1.) * height / 2;
    out.z = (vector.z + 1.) * 255. / 2; // Here we save the colours.

    return out;
}