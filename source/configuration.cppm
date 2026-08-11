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
// LOGGING
// ============================================================================

// SELECT ONE:
export const LogLevel LOG_LEVEL = LogLevel::Trace;

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
// PRIMITIVE GENERATOR
// ============================================================================

// DO NOT CHANGE!
const FaceNormalPrimitiveGenerator FACE_NORMAL_PRIMITIVE_GENERATOR(0., red);
const VertexNormalPrimitiveGenerator VERTEX_NORMAL_PRIMITIVE_GENERATOR(0., red);

// SELECT ONE:
// export const PrimitiveGenerator *PRIMITIVE_GENERATOR = nullptr;
export const PrimitiveGenerator *PRIMITIVE_GENERATOR = &VERTEX_NORMAL_PRIMITIVE_GENERATOR;
//  export const PrimitiveGenerator *PRIMITIVE_GENERATOR = &FACE_NORMAL_PRIMITIVE_GENERATOR;

// ============================================================================
// LIGHTING
// ============================================================================

// DO NOT CHANGE!
// const DepthShadingFactory DEPTH_SHADING{};
// const BorderShadingFactory BORDER_SHADING{};
// const CenterShadingFactory CENTER_SHADING{};
const FlatLightingModel FLAT_LIGHTING(LIGHT_POSITION);
const GouraudLightingModel GOURAUD_LIGHTING(LIGHT_POSITION);
const PhongLightingModel PHONG_LIGHTING(LIGHT_POSITION);

// SELECT ONE:
// export const LightingModel *LIGHTING_MODEL = nullptr;
// export const LightingModel *LIGHTING_MODEL = &DEPTH_SHADING;
// export const LightingModel *LIGHTING_MODEL = &BORDER_SHADING;
//  export const LightingModel *SHADLIGHTING_MODELING = &CENTER_SHADING;
export const LightingModel *LIGHTING_MODEL = &FLAT_LIGHTING;
// export const LightingModel *SHADILIGHTING_MODELNG = &GOURAUD_SHADING;
// export const LightingModel *LIGHTING_MODEL = &PHONG_LIGHTING;

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
// RASTERIZERS
// ============================================================================

// DO NOT CHANGE!
const VertexAlgorithm VERTEX_ALGORITHM{};
const WireframeAlgorithm WIREFRAME_ALGORITHM{};
const BoundingBoxAlgorithm BOUNDING_BOX_ALGORITHM{DRAWING_PATTERN};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// POINT RASTERIZER
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// SELECTE ONE:
export const PointRasterizer &POINT_RASTERIZER = VERTEX_ALGORITHM;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// LINE RASTERIZER
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// SELECTE ONE:
// export const LineRasterizer &LINE_RASTERIZER = VERTEX_ALGORITHM;
export const LineRasterizer &LINE_RASTERIZER = WIREFRAME_ALGORITHM;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TRIANGLE RASTERIZER
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// SELECTE ONE:
// export const TriangleRasterizer &TRIANGLE_RASTERIZER = VERTEX_ALGORITHM;
export const TriangleRasterizer &TRIANGLE_RASTERIZER = WIREFRAME_ALGORITHM;
// export const TriangleRasterizer &TRIANGLE_RASTERIZER = BOUNDING_BOX_ALGORITHM;

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