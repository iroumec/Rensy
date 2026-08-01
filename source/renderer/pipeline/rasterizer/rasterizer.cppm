module;

#include <vector>

export module renderer:pipeline.rasterizer;

// ============================================================================
// Imports
// ============================================================================

import drawing_pattern;
import :structure.triangle;
import :structure.fragment;
import :structure.vertex_out;

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// Rasterizer (Base Class)
// ----------------------------------------------------------------------------

export class Rasterizer
{
public:
    virtual ~Rasterizer() = default;

    virtual std::vector<Fragment> rasterize(
        const Triangle &primitive) const = 0;
};

// ----------------------------------------------------------------------------
// Vertex Rasterizer
// ----------------------------------------------------------------------------

/*
export class VertexRasterizer : public Rasterizer
{
public:
    std::vector<Fragment> rasterize(const Triangle &primitive) const override;
};

// ----------------------------------------------------------------------------
// Wireframe Rasterizer
// ----------------------------------------------------------------------------

export class WireframeRasterizer : public Rasterizer
{
    void drawLine(VertexOut a, VertexOut b) const;

public:
    std::vector<Fragment> rasterize(const Triangle &primitive) const override;
};

// ----------------------------------------------------------------------------
// Scanline Rasterizer
// ----------------------------------------------------------------------------

export class ScanlineRasterizer : public Rasterizer
{
public:
    std::vector<Fragment> rasterize(const Triangle &primitive) const override;
};

*/

// ----------------------------------------------------------------------------
// Bounding Box Rasterizer
// ----------------------------------------------------------------------------

export class BoundingBoxRasterizer : public Rasterizer
{
    const DrawingPattern *drawingPattern = nullptr;

public:
    BoundingBoxRasterizer(const DrawingPattern *drawingPattern = nullptr)
        : drawingPattern(drawingPattern) {}

    std::vector<Fragment> rasterize(const Triangle &primitive) const override;
};

// ============================================================================
// EOF
// ============================================================================