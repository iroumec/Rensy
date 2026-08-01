module;

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :transform.mvp;
import :transform.view;
import :transform.model;
import :transform.projection;

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// MVP Transform
// ----------------------------------------------------------------------------

MVPTransform::MVPTransform(
    const ModelTransform &modelTransform,
    const ViewTransform &viewTransform,
    const ProjectionTransform &projectionTransform)
    : Transform(
          projectionTransform.getMatrix() *
          viewTransform.getMatrix() *
          modelTransform.getMatrix())
{
}

// ============================================================================
// EOF
// ============================================================================
