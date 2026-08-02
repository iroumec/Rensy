module;

#include <vector>

export module renderer:normal.calculator.adjacent_faces;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_in;
import :math.vector.vector_3d;
import :normal.calculator.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

// WARNING: It overwrites the normals already extracted by the model loader!
export class AdjacentFacesNormalCalculator : public NormalCalculator
{
public:
    constexpr void calculateNormals(
        std::vector<VertexIn> &vertices,
        const std::vector<int> &faces) const override
    {
        std::vector<std::vector<Vector3D>> adjacentNormals(vertices.size());

        int numberOfFaces = faces.size() / 3;

        // The normal of each face is calculated and associated to each vertex.
        for (int i = 0; i < numberOfFaces; ++i)
        {
            int ia = faces[i * 3 + 0];
            int ib = faces[i * 3 + 1];
            int ic = faces[i * 3 + 2];

            Vector3D a = vertices[ia].localPosition;
            Vector3D b = vertices[ib].localPosition;
            Vector3D c = vertices[ic].localPosition;

            Vector3D ab = b - a;
            Vector3D ac = c - a;

            Vector3D faceNormal = ab.cross(ac).normalize();

            adjacentNormals[ia].push_back(faceNormal);
            adjacentNormals[ib].push_back(faceNormal);
            adjacentNormals[ic].push_back(faceNormal);
        }

        // The average normal of each vertex, based on its adjacents faces,
        // is calculated and saved on the VertexIn.
        for (size_t i = 0; i < adjacentNormals.size(); ++i)
        {
            Vector3D normal{0, 0, 0};

            for (const Vector3D &n : adjacentNormals[i])
                normal += n;

            vertices[i].normal = normal.normalize();
        }
    }
};

// ============================================================================
// EOF
// ============================================================================