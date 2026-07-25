module;

export module triangle_renderer;

import geometry;
import tgaimage;

export class TriangleRenderer
{
public:
    virtual ~TriangleRenderer() = default;

    virtual void draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour) = 0;
};

export class EmptyTriangleRenderer : public TriangleRenderer
{
public:
    void draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour) override;
};

export class FilledTriangleRenderer : public TriangleRenderer
{
public:
    void draw(vec2 a, vec2 b, vec2 c, TGAImage &framebuffer, const TGAColour &colour) override;
};