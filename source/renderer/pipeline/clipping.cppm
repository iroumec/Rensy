module;

export module renderer:pipeline.clipping;

// ============================================================================
// Imports
// ============================================================================

import vector;

// ============================================================================
// Declarations
// ============================================================================

export bool insideClipVolume(const Vector4D &vector)
{
    double w = vector.w();

    if (w <= 0.0)
        return false; // Point behind camera.

    return -w <= vector.x() && vector.x() <= w &&
           -w <= vector.y() && vector.y() <= w &&
           -w <= vector.z() && vector.z() <= w;
}

// ============================================================================