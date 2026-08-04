module;

#include <memory>
#include <string>
#include <filesystem>

export module configuration;

// ============================================================================
// IMPORTS
// ============================================================================

import renderer;

// ============================================================================
// SCREEN
// ============================================================================

export constexpr unsigned WIDTH = 1080;
export constexpr unsigned HEIGHT = 1080;

// ============================================================================
// SEED
// ============================================================================

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
// MODEL LOADER
// ============================================================================

// DO NOT CHANGE!
const ObjModelLoader OBJ_MODEL_LOADER{};

// SELECT ONE:
export const ModelLoader &MODEL_LOADER = OBJ_MODEL_LOADER;

// ============================================================================
// NORMAL CALCULATOR
// ============================================================================

// DO NOT CHANGE!
const AdjacentFacesNormalCalculator ADJACENT_FACES_NORMAL_CALCULATOR{};
const FileExtractedNormalCalculator FILE_EXTRACTED_NORMAL_CALCULATOR{};

// SELECT ONE:
export const NormalCalculator &NORMAL_CALCULATOR = ADJACENT_FACES_NORMAL_CALCULATOR;

// ============================================================================
// PROJECTION TRANSFORM
// ============================================================================

// DO NOT CHANGE!
const NoProjection NO_PROJECTION{};
const PerspectiveProjection PERSPECTIVE_PROJECTION{};

// SELECT ONE:
// export const ProjectionTransform &PROJECTION_TRANSFORM = NO_PROJECTION;
export const ProjectionTransform &PROJECTION_TRANSFORM = PERSPECTIVE_PROJECTION;

// ============================================================================
// MVP Transform
// ============================================================================

constexpr Rotation ROTATION =
    Rotation{Radian{}, Radian::fromDegrees(30.0), Radian{}};

const Vector3D EYE(0, 0, 1);  // Camera position.
const Vector3D GAZE(0, 0, 0); // Camera direction.
const Vector3D UP(0, 1, 0);   // Camera up vector.

export const ModelTransform MODEL_TRANSFORM{RotationTransform{ROTATION}};
export const ViewTransform VIEW_TRANSFORM{EYE, GAZE, UP};

// ============================================================================
// COLOURS
// ============================================================================

export const Colour BACKGROUND_COLOUR = black;
const Colour FOG_COLOUR = BACKGROUND_COLOUR;
const Colour STATIC_COLOUR = darkGray;

// ============================================================================
// PHONG MODEL
// ============================================================================

const Vector3D LIGHT_POSITION(-5, 2, -1); // World coordinates.
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
// export const ColourGenerator &COLOUR_GENERATOR = RANDOM_COLOUR_GENERATOR;
// export const ColourGenerator &COLOUR_GENERATOR = CIRCULAR_RANDOM_COLOUR_GENERATOR;

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
// SHADING
// ============================================================================

// DO NOT CHANGE!
const DepthShadingFactory DEPTH_SHADING{};
const BorderShadingFactory BORDER_SHADING{};
const CenterShadingFactory CENTER_SHADING{};
const FlatShadingFactory FLAT_SHADING{LIGHT_POSITION};
const GouraudShadingFactory GOURAUD_SHADING{LIGHT_POSITION};
const PhongShadingFactory PHONG_SHADING{LIGHT_POSITION};

// SELECT ONE:
// export const ShadingFactory *SHADING = nullptr;
// export const ShadingFactory *SHADING = &DEPTH_SHADING;
// export const ShadingFactory *SHADING = &BORDER_SHADING;
//  export const ShadingFactory *SHADING = &CENTER_SHADING;
export const ShadingFactory *SHADING = &FLAT_SHADING;
// export const ShadingFactory *SHADING = &GOURAUD_SHADING;
// export const ShadingFactory *SHADING = &PHONG_SHADING;

// ============================================================================
// DRAWING PATTERN
// ============================================================================

// DO NOT CHANGE!
// const BorderDrawingPattern BORDER_DRAWING_PATTERN{};
// const CenterDrawingPattern CENTER_DRAWING_PATTERN{};

// SELECT ONE:
// export const DrawingPattern *DRAWING_PATTERN = &BORDER_DRAWING_PATTERN;
// export const DrawingPattern *DRAWING_PATTERN = &CENTER_DRAWING_PATTERN;
export const DrawingPattern *DRAWING_PATTERN = nullptr;

// ============================================================================
// NORMAL RASTERIZER
// ============================================================================

// DO NOT CHANGE!
const LineNormalRasterizer LINE_NORMAL_RASTERIZER(8, red);

// SELECT ONE:
export const NormalRasterizer *NORMAL_RASTERIZER = nullptr;
// export const NormalRasterizer *NORMAL_RASTERIZER = &LINE_NORMAL_RASTERIZER;

// ============================================================================
// RASTERIZER
// ============================================================================

// DO NOT CHANGE!
const VertexRasterizer VERTEX_RASTERIZER{};
const WireframeRasterizer WIREFRAME_RASTERIZER{};
// const ScanlineRasterizer SCANLINE_RASTERIZER{};
const BoundingBoxRasterizer BOUNDING_BOX_RASTERIZER(
    DRAWING_PATTERN, NORMAL_RASTERIZER);

// SELECT ONE:
// export const Rasterizer &RASTERIZER = VERTEX_RASTERIZER;
// export const Rasterizer &RASTERIZER = WIREFRAME_RASTERIZER;
//  export const Rasterizer &RASTERIZER = SCANLINE_RASTERIZER;
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
//    export const Filter *FILTER = &BRIGHT_FILTER;