module;

export module rasterizer;

import model;
import buffer;
import colour;
import vector;
import rotation;

export class Rasterizer
{
public:
    virtual ~Rasterizer() = default;

    virtual void draw(Vector3D a, Vector3D b, Vector3D c, FrameBuffer &framebuffer, const Colour &colour) = 0;

    void draw(const Model &model, FrameBuffer &framebuffer, const ColourGenerator &colourGenerator, const Rotation &rotation);
};

export class VertexRasterizer : public Rasterizer
{
public:
    using Rasterizer::draw;
    void draw(Vector3D a, Vector3D b, Vector3D c, FrameBuffer &framebuffer, const Colour &colour) override;
};

export class WireframeRasterizer : public Rasterizer
{
    void drawLine(Vector3D a, Vector3D b, FrameBuffer &framebuffer, const Colour &colour);

public:
    using Rasterizer::draw;
    void draw(Vector3D a, Vector3D b, Vector3D c, FrameBuffer &framebuffer, const Colour &colour) override;
};

export class ScanlineRasterizer : public Rasterizer
{
public:
    using Rasterizer::draw;
    void draw(Vector3D a, Vector3D b, Vector3D c, FrameBuffer &framebuffer, const Colour &colour) override;
};

export class BoundingBoxRasterizer : public Rasterizer
{
public:
    using Rasterizer::draw;
    void draw(Vector3D a, Vector3D b, Vector3D c, FrameBuffer &framebuffer, const Colour &colour) override;
};