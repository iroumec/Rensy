module;

export module renderer:pipeline;

// ============================================================================
// Exports
// ============================================================================

// TODO: extract image generation to another process.
// The pipeline should not be accesible by the user.
export import :pipeline.depth_test;
export import :pipeline.framebuffer;
export import :pipeline.rasterization;

// ============================================================================
// EOF
// ============================================================================
