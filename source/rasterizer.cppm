module;

export module rasterizer;

import buffer;
import colour;
import geometry;

export class Rasterizer
{
public:
    virtual ~Rasterizer() = default;

    virtual void draw(vec3 a, vec3 b, vec3 c, FrameBuffer &framebuffer, const Colour &colour) = 0;
};

export class VertexRasterizer : public Rasterizer
{
public:
    void draw(vec3 a, vec3 b, vec3 c, FrameBuffer &framebuffer, const Colour &colour) override;
};

export class WireframeRasterizer : public Rasterizer
{
    void drawLine(vec3 a, vec3 b, FrameBuffer &framebuffer, const Colour &colour);

public:
    void draw(vec3 a, vec3 b, vec3 c, FrameBuffer &framebuffer, const Colour &colour) override;
};

export class ScanlineRasterizer : public Rasterizer
{
public:
    void draw(vec3 a, vec3 b, vec3 c, FrameBuffer &framebuffer, const Colour &colour) override;
};

export class BoundingBoxRasterizer : public Rasterizer
{
public:
    void draw(vec3 a, vec3 b, vec3 c, FrameBuffer &framebuffer, const Colour &colour) override;
};