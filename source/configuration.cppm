module;

#include <memory>
#include <string>
#include <filesystem>

export module configuration;

// ============================================================================
// IMPORTS
// ============================================================================

import radian;
import colour;
import filter;
import vector;
import rotation;
import transform;
import rasterizer;
import intensifier;
import drawing_pattern;
import colour_generator;
import colour_calculator;

export constexpr unsigned WIDTH = 1080;
export constexpr unsigned HEIGHT = 1080;
export constexpr unsigned RANDOM_SEED = 42;

// ============================================================================
// OUTPUT
// ============================================================================

export const std::filesystem::path outputDirectory = "output";
export void initializeConfiguration()
{
    std::filesystem::create_directories(outputDirectory);
}
export const std::filesystem::path outputZBufferFileName =
    outputDirectory / "zbuffer.tga";
export const std::filesystem::path outputFrameFileName =
    outputDirectory / "framebuffer.tga";

// ============================================================================
// MVP Transform
// ============================================================================

constexpr Rotation ROTATION =
    Rotation{Radian{}, Radian::fromDegrees(30.0), Radian{}};

const Vector3D EYE(0, 0, 1);  // Camera position.
const Vector3D GAZE(0, 0, 0); // Camera direction.
const Vector3D UP(0, 1, 0);   // Camera up vector.

export const MVPTransform &getMVPTransform()
{
    static const MVPTransform instance{
        ModelTransform{
            RotationTransform{ROTATION},
        },
        ViewTransform{EYE, GAZE, UP},
        PerspectiveProjection{}};
    return instance;
}

// ============================================================================
// COLOURS
// ============================================================================

export const Colour BACKGROUND_COLOUR = black;
const Colour FOG_COLOUR = BACKGROUND_COLOUR;
const Colour STATIC_COLOUR = darkGray;

// ============================================================================
// PHONG MODEL
// ============================================================================

const Vector3D LIGHT_POSITION(2, 2, 4);
const Colour AMBIENT_COLOUR = darkGray;

// ============================================================================
// COLOUR GENERATOR
// ============================================================================

// DO NOT CHANGE!
const RandomColourGenerator RANDOM_COLOUR_GENERATOR{RANDOM_SEED};
const StaticColourGenerator STATIC_COLOUR_GENERATOR{STATIC_COLOUR};
const CircularColourGenerator CIRCULAR_RANDOM_COLOUR_GENERATOR{
    std::make_shared<RandomColourGenerator>(RANDOM_SEED),
    std::make_shared<RandomColourGenerator>(RANDOM_SEED + 100),
    std::make_shared<RandomColourGenerator>(RANDOM_SEED + 200)};

// SELECT ONE:
export const ColourGenerator &COLOUR_GENERATOR = STATIC_COLOUR_GENERATOR;

// ============================================================================
// COLOUR CALCULATOR
// ============================================================================

// DO NOT CHANGE!
export const GradientColourCalculator GRADIENT_COLOUR_CALCULATOR{};
export const DominantColourCalculator DOMINANT_COLOUR_CALCULATOR{};
export const SubordinateColourCalculator SUBORDINATE_COLOUR_CALCULATOR{};

// SELECT ONE:
export const ColourCalculator &COLOUR_CALCULATOR = GRADIENT_COLOUR_CALCULATOR;
// export const ColourCalculator &COLOUR_CALCULATOR = DOMINANT_COLOUR_CALCULATOR;
// export const ColourCalculator &COLOUR_CALCULATOR = SUBORDINATE_COLOUR_CALCULATOR;

// ============================================================================
// COLOUR INTENSIFIER
// ============================================================================

// DO NOT CHANGE!
const DepthColourIntensifierFactory DEPTH_COLOUR_INTENSIFIER{};
const BorderColourIntensifierFactory BORDER_COLOUR_INTENSIFIER{};
const CenterColourIntensifierFactory CENTER_COLOUR_INTENSIFIER{};
const UniformPhongColourIntensifierFactory UNIFORM_PHONG_COLOUR_INTENSIFIER{LIGHT_POSITION};

// SELECT ONE:
// export const ColourIntensifierFactory *COLOUR_INTENSIFIER = nullptr;
// export const ColourIntensifierFactory *COLOUR_INTENSIFIER = &DEPTH_COLOUR_INTENSIFIER;
// export const ColourIntensifierFactory *COLOUR_INTENSIFIER = &BORDER_COLOUR_INTENSIFIER;
//  export const ColourIntensifierFactory *COLOUR_INTENSIFIER = &CENTER_COLOUR_INTENSIFIER;
export const ColourIntensifierFactory *COLOUR_INTENSIFIER = &UNIFORM_PHONG_COLOUR_INTENSIFIER;

// ============================================================================
// DRAWING PATTERN
// ============================================================================

// DO NOT CHANGE!
export const BorderDrawingPattern BORDER_DRAWING_PATTERN{};
export const CenterDrawingPattern CENTER_DRAWING_PATTERN{};

// SELECT ONE:
// export const DrawingPattern *DRAWING_PATTERN = &BORDER_DRAWING_PATTERN;
// export const DrawingPattern *DRAWING_PATTERN = &CENTER_DRAWING_PATTERN;
export const DrawingPattern *DRAWING_PATTERN = nullptr;

// ============================================================================
// RASTERIZER
// ============================================================================

// DO NOT CHANGE!
const VertexRasterizer VERTEX_RASTERIZER{};
const WireframeRasterizer WIREFRAME_RASTERIZER{};
const ScanlineRasterizer SCANLINE_RASTERIZER{};
const BoundingBoxRasterizer BOUNDING_BOX_RASTERIZER{
    COLOUR_CALCULATOR, COLOUR_INTENSIFIER, DRAWING_PATTERN};

// SELECT ONE:
// export const Rasterizer &RASTERIZER = VERTEX_RASTERIZER;
// export const Rasterizer &RASTERIZER = WIREFRAME_RASTERIZER;
// export const Rasterizer &RASTERIZER = SCANLINE_RASTERIZER;
export const Rasterizer &RASTERIZER = BOUNDING_BOX_RASTERIZER;

// ============================================================================
// FILTERS
// ============================================================================

// DO NOT CHANGE!
export const FogFilter FOG_FILTER{FOG_COLOUR};
export const BrightFilter BRIGHT_FILTER{Colour{237, 234, 222, 255}};

// SELECT ONE:
export const Filter *FILTER = nullptr;
// export const Filter *FILTER = &FOG_FILTER;
// export const Filter *FILTER = &BRIGHT_FILTER;