module;

#include <vector>
#include <string>

export module model;

import geometry;

export class Model
{
    std::vector<vec3> verts = {};    // Array of vertices
    std::vector<int> facet_vrt = {}; // Per-triangle index in the above array
public:
    Model(const std::string filename);                   // Constructor.
    int nverts() const;                                  // Number of vertices.
    int nfaces() const;                                  // Number of triangles.
    vec3 vert(const int i) const;                        // 0 <= i < nverts()
    vec3 vert(const int iface, const int nthvert) const; // 0 <= iface <= nfaces(), 0 <= nthvert < 3
};