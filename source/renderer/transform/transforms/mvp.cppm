module;

export module transform:mvp;

// ============================================================================
// Imports
// ============================================================================

import :base;
import :view;
import :model;
import :projection;

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