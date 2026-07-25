module;

export module triangle_rasterizer;

import geometry;
import tgaimage;

export class TriangleRasterizer
{
public:
    virtual ~TriangleRasterizer() = default;

    virtual void draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour) = 0;
};

export class VertexTriangleRasterizer : public TriangleRasterizer
{
public:
    void draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour) override;
};

export class WireframeTriangleRasterizer : public TriangleRasterizer
{
    void drawLine(vec2 a, vec2 b, TGAImage &framebuffer, const TGAColour &colour);

public:
    void draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour) override;
};

export class ScanlineTriangleRasterizer : public TriangleRasterizer
{
public:
    void draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour) override;
};

export class BoundingBoxTriangleRasterizer : public TriangleRasterizer
{
public:
    void draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour) override;
};