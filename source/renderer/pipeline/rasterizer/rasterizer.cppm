module;

#include <vector>

export module rasterizer;

// ============================================================================
// Imports
// ============================================================================

import model;
import buffer;
import vertex;
import transform;
import drawing_pattern;
import colour_generator;
import colour_calculator;
import intensifier;

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
    void drawLine(Vertex a, Vertex b, FrameBuffer &buffer) const;

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

// ----------------------------------------------------------------------------
// Bounding Box Rasterizer
// ----------------------------------------------------------------------------

export class BoundingBoxRasterizer : public Rasterizer
{
    const ColourCalculator &colourCalculator;
    const DrawingPattern *drawingPattern = nullptr;
    const ColourIntensifierFactory *colourIntensifierFactory = nullptr;

public:
    BoundingBoxRasterizer(
        const ColourCalculator &colourCalculator,
        const DrawingPattern *drawingPattern = nullptr,
        const ColourIntensifierFactory *colourIntensifierFactory = nullptr)
        : colourCalculator(colourCalculator),
          drawingPattern(drawingPattern),
          colourIntensifierFactory(colourIntensifierFactory) {}

    BoundingBoxRasterizer(
        const ColourCalculator &colourCalculator,
        const ColourIntensifierFactory *colourIntensifierFactory = nullptr,
        const DrawingPattern *drawingPattern = nullptr)
        : colourCalculator(colourCalculator),
          drawingPattern(drawingPattern),
          colourIntensifierFactory(colourIntensifierFactory) {}

    std::vector<Fragment> rasterize(const Triangle &primitive) const override;
};

// ============================================================================
// EOF
// ============================================================================