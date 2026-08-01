module;

module renderer;

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
