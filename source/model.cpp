module;

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cassert>

module model;

import geometry;

constexpr bool debug = false;

Model::Model(const std::string &filename)
{
    std::ifstream ist{filename};
    if (!ist)
        throw std::runtime_error("Cannot open input file: " + filename);

    std::string line;
    while (std::getline(ist, line)) // All the line is consumed.
    {
        if (debug)
            std::cout << "Line: " << line << '\n';

        std::istringstream lineStream(line);
        std::string dataType;
        lineStream >> dataType;

        if (dataType == "v") // Vertices.
        {
            vec3 v;
            lineStream >> v.x >> v.y >> v.z;
            this->vertices.push_back(v);
        }
        else if (dataType == "f") // Faces / Triangles.
        {
            std::string token;

            while (lineStream >> token) // Each token can have a form n, n/n, n//n, n/n/n. Where n is a number.
            {
                if (debug)
                    std::cout << "Token: " << token << '\n';

                std::istringstream tokenStream(token); // So we are able to read from it.

                // Only the first number in each token is of interest.
                int idx;
                tokenStream >> idx; // It stops when finding a "/" or the end.

                if (debug)
                    std::cout << idx << std::endl;

                this->faces.push_back(idx - 1); // The vertices in .obj starts at 1, but the array starts at 0. So we have to decrease one.
            }
        }
    }

    if (debug)
        std::cout << "Loaded " << this->vertices.size() << " vertices\n";
}

unsigned Model::getNumberOfVertices() const
{
    return this->vertices.size();
}

unsigned Model::getNumberOfFaces() const
{
    return this->faces.size() / 3;
}

vec3 Model::getVertex(const unsigned vertexNumber) const
{
    return this->vertices[vertexNumber];
}

vec3 Model::getVertex(const unsigned faceNumber, const unsigned vertexNumber) const
{
    assert(faceNumber < this->getNumberOfFaces() && vertexNumber <= 2);

    // Each face is stored as three consecutive indices into the vertices array.
    // faceNumber * 3 gives the first index of the face, and vertexNumber (0-2)
    // selects one of its three vertices.

    // If faceNumber = 0, we are placed in the first face. Increasing vertexNumber
    // in [0, 2] gives us the vertex.
    return this->vertices[this->faces[faceNumber * 3 + vertexNumber]];
}