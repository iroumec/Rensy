module;

#include <memory>
#include <string>
#include <filesystem>

export module configuration;

import radian;
import colour;
import rotation;
import drawing_pattern;
import colour_generator;
import colour_calculator;
import colour_intensifier;

export constexpr unsigned WIDTH = 1080;
export constexpr unsigned HEIGHT = 1080;
export constexpr unsigned RANDOM_SEED = 42;
// export const RandomColourGenerator COLOUR_GENERATOR{RANDOM_SEED};
//  export const StaticColourGenerator COLOUR_GENERATOR{red};
export const CircularColourGenerator COLOUR_GENERATOR{
    std::make_shared<RandomColourGenerator>(RANDOM_SEED),
    std::make_shared<RandomColourGenerator>(RANDOM_SEED + 100),
    std::make_shared<RandomColourGenerator>(RANDOM_SEED + 200)};
export constexpr Rotation ROTATION = Rotation{Radian{}, Radian::fromDegrees(30.0), Radian{}};

// ============================================================================
// OUTPUT
// ============================================================================

export const std::filesystem::path outputDirectory = "output";
export void initializeConfiguration()
{
    std::filesystem::create_directories(outputDirectory);
}

export const std::filesystem::path outputZBufferFileName = outputDirectory / "zbuffer.tga";
export const std::filesystem::path outputFrameFileName = outputDirectory / "framebuffer.tga";

// ============================================================================
// COLOUR INTENSIFIER
// ============================================================================

// DO NOT CHANGE!
export const BorderColourIntensifier BORDER_COLOUR_INTENSIFIER{};
export const CenterColourIntensifier CENTER_COLOUR_INTENSIFIER{};

// SELECT ONE:
// export const ColourIntensifier *COLOUR_INTENSIFIER = &BORDER_COLOUR_INTENSIFIER;
// export const ColourIntensifier *COLOUR_INTENSIFIER = &CENTER_COLOUR_INTENSIFIER;
export const ColourIntensifier *COLOUR_INTENSIFIER = nullptr;

// ============================================================================
// COLOUR CALCULATOR
// ============================================================================

// DO NOT CHANGE!
export const GradientColourCalculator GRADIENT_COLOUR_CALCULATOR{};

// SELECT ONE:
export const ColourCalculator &COLOUR_CALCULATOR = GRADIENT_COLOUR_CALCULATOR;

// ============================================================================
// DRAWING PATTERN
// ============================================================================

export const BorderDrawingPattern BORDER_DRAWING_PATTERN{};
export const CenterDrawingPattern CENTER_DRAWING_PATTERN{};
// export const Pattern *PATTERN = &BORDER_PATTERN;
export const DrawingPattern *DRAWING_PATTERN = nullptr;