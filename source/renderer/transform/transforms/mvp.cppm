module;

export module renderer:transform.mvp;

// ============================================================================
// Imports
// ============================================================================

import :transform.base;
import :transform.view;
import :transform.model;
import :transform.projection;

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