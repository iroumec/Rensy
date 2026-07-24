module;

#include <vector>
#include <string>

export module model;

import geometry;

export class Model
{
    std::vector<vec3> vertices = {}; // Array of vertices
    std::vector<int> faces = {};     // Per-triangle index in the above array
public:
    Model(const std::string filename);                                       // Constructor.
    int getNumberOfVertices() const;                                         // Number of vertices.
    int getNumberOfFaces() const;                                            // Number of triangles.
    vec3 getVertex(const unsigned vertexNumber) const;                       // 0 <= i < nverts()
    vec3 getVertex(const unsigned faceNumber, const unsigned nthvert) const; // 0 <= iface <= nfaces(), 0 <= nthvert < 3
};