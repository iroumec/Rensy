module;

#include <vector>
#include <string>

export module model;

import vector;

export class Model
{
    std::vector<Vector3D> vertices = {}; // Array of vertices
    std::vector<int> faces = {};         // Per-triangle index in the above array
public:
    Model(const std::string &filename);                                          // Constructor.
    unsigned getNumberOfVertices() const;                                        // Number of vertices.
    unsigned getNumberOfFaces() const;                                           // Number of triangles.
    Vector3D getVertex(const unsigned vertexNumber) const;                       // 0 <= i < nverts()
    Vector3D getVertex(const unsigned faceNumber, const unsigned nthvert) const; // 0 <= iface <= nfaces(), 0 <= nthvert < 3
};