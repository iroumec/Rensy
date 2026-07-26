module;

#include <string>

export module configuration;

export constexpr unsigned width = 800;
export constexpr unsigned height = 800;
export constexpr unsigned randomSeed = 42;
export constexpr std::string outputZBufferFileName = "zbuffer.tga";
export constexpr std::string outputFrameFileName = "framebuffer.tga";