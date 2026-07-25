module;

#include <string>

export module configuration;

export constexpr unsigned width = 800;
export constexpr unsigned height = 800;
export constexpr std::string outputFrameFileName = "framebuffer.tga";
export constexpr std::string outputZBufferFileName = "zbuffer.tga";