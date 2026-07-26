module;

#include <vector>
#include <string>

export module model;

import vector;
import rotation;

export class Model
{
    std::vector<Vector3D> vertices = {}; // Array of vertices
    std::vector<int> faces = {};         // Per-triangle index in the above array
public:
    Model(const std::string &filename, const Rotation &rotation);
    unsigned getNumberOfVertices() const;
    unsigned getNumberOfFaces() const;
    Vector3D getVertex(const unsigned vertexNumber) const;
    Vector3D getVertex(const unsigned faceNumber, const unsigned nthvert) const;
};