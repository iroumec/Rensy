module;

#include <memory>
#include <string>

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
export constexpr std::string outputZBufferFileName = "zbuffer.tga";
export constexpr std::string outputFrameFileName = "framebuffer.tga";
export const BorderDrawingPattern BORDER_DRAWING_PATTERN{};
export const CenterDrawingPattern CENTER_DRAWING_PATTERN{};
// export const Pattern *PATTERN = &BORDER_PATTERN;
export const DrawingPattern *DRAWING_PATTERN = nullptr;

export const BorderColourIntensifier BORDER_COLOUR_INTENSIFIER{};
export const CenterColourIntensifier CENTER_COLOUR_INTENSIFIER{};

// export const ColourIntensifier *COLOUR_INTENSIFIER = &BORDER_COLOUR_INTENSIFIER;
// export const ColourIntensifier *COLOUR_INTENSIFIER = &CENTER_COLOUR_INTENSIFIER;
export const ColourIntensifier *COLOUR_INTENSIFIER = nullptr;

// COLOUR CALCULATOR

export const GradientColourCalculator GRADIENT_COLOUR_CALCULATOR{};
export const ColourCalculator &COLOUR_CALCULATOR = GRADIENT_COLOUR_CALCULATOR;