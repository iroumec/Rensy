module;

export module rasterizer;

import model;
import buffer;
import vertex;
import rotation;
import drawing_pattern;
import colour_generator;
import colour_calculator;
import colour_intensifier;

export class Rasterizer
{
public:
    virtual ~Rasterizer() = default;

    virtual void draw(Vertex a, Vertex b, Vertex c, FrameBuffer &framebuffer) = 0;

    void draw(const Model &model, FrameBuffer &framebuffer, const ColourGenerator &colourGenerator, const Rotation &rotation);
};

export class VertexRasterizer : public Rasterizer
{
public:
    using Rasterizer::draw;
    void draw(Vertex a, Vertex b, Vertex c, FrameBuffer &framebuffer) override;
};

export class WireframeRasterizer : public Rasterizer
{
    void drawLine(Vertex a, Vertex b, FrameBuffer &framebuffer);

public:
    using Rasterizer::draw;
    void draw(Vertex a, Vertex b, Vertex c, FrameBuffer &framebuffer) override;
};

export class ScanlineRasterizer : public Rasterizer
{
public:
    using Rasterizer::draw;
    void draw(Vertex a, Vertex b, Vertex c, FrameBuffer &framebuffer) override;
};

export class BoundingBoxRasterizer : public Rasterizer
{
    const ColourCalculator &colourCalculator;
    const DrawingPattern *drawingPattern = nullptr;
    const ColourIntensifier *colourIntensifier = nullptr;

public:
    BoundingBoxRasterizer(
        const ColourCalculator &colourCalculator,
        const DrawingPattern *drawingPattern = nullptr,
        const ColourIntensifier *colourIntensifier = nullptr)
        : colourCalculator(colourCalculator),
          drawingPattern(drawingPattern),
          colourIntensifier(colourIntensifier) {}

    BoundingBoxRasterizer(
        const ColourCalculator &colourCalculator,
        const ColourIntensifier *colourIntensifier = nullptr,
        const DrawingPattern *drawingPattern = nullptr)
        : colourCalculator(colourCalculator),
          drawingPattern(drawingPattern),
          colourIntensifier(colourIntensifier) {}

    using Rasterizer::draw;
    void draw(Vertex a, Vertex b, Vertex c, FrameBuffer &framebuffer) override;
};