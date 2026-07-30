module;

export module transform:mvp_transform;

// ============================================================================
// Imports
// ============================================================================

import :base;
import :view_transform;
import :model_transform;
import :projection_transform;

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// MVP Transform
// ----------------------------------------------------------------------------

export class MVPTransform : public Transform
{
    // Creates a Model-View-Projection Matrix.

public:
    MVPTransform(
        const ModelTransform &modelTransform,
        const ViewTransform &viewTransform,
        const ProjectionTransform &projectionTransform);
};

// ============================================================================
// EOF
// ============================================================================