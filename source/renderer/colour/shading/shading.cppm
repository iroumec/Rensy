module;

export module renderer:colour.shading;

// ============================================================================
// Principles
// ============================================================================

// A shader shouldn't interpolate attributes.
// It should work with the attributes already presented in the fragment.

// Rasterizer/interpolator: "What attributes does this fragment have?".
// Shader: "With those attributes, what colour is the fragment?".

// ============================================================================
// Imports and Exports
// ============================================================================

export import :colour.shading.factory;
export import :colour.shading.instance;

// ============================================================================
// EOF
// ============================================================================