module;

#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

module model;

// ============================================================================
// Imports
// ============================================================================

import vector;

// ============================================================================
// Constants
// ============================================================================

constexpr bool DEBUG = false;

// ============================================================================
// Implementations
// ============================================================================

Model::Model(const std::string &filename)
{
    std::ifstream ist{filename};
    if (!ist)
        throw std::runtime_error("Cannot open input file: " + filename);

    std::string line;
    while (std::getline(ist, line)) // All the line is consumed.
    {
        if (DEBUG)
            std::cout << "Line: " << line << '\n';

        std::istringstream lineStream(line);
        std::string dataType;
        lineStream >> dataType;

        if (dataType == "v") // Vertices.
        {
            Vector3D v;
            lineStream >> v;
            this->vertices.push_back(v);
        }
        else if (dataType == "f") // Faces / Triangles.
        {
            std::string token;

            // Each token can have a form n, n/n, n//n, n/n/n.
            // Where n is a number.
            // At the moemnt, just the first n is of interest.
            while (lineStream >> token)
            {
                if (DEBUG)
                    std::cout << "Token: " << token << '\n';

                // Token stream creation so we are able to read from it.
                std::istringstream tokenStream(token);

                // Only the first number in each token is of interest.
                int idx;
                tokenStream >> idx; // It stops when finding a "/" or the end.

                if (DEBUG)
                    std::cout << idx << std::endl;

                // The vertices in .obj starts at 1, but the array starts at 0.
                // So we have to decrease one.
                this->faces.push_back(idx - 1);
            }
        }
    }

    if (DEBUG)
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

Vector3D Model::getVertex(const unsigned vertexNumber) const
{
    return this->vertices[vertexNumber];
}

Vector3D Model::getVertex(const unsigned faceNumber, const unsigned vertexNumber) const
{
    assert(faceNumber < this->getNumberOfFaces() && vertexNumber <= 2);

    // Each face is stored as three consecutive indices into the vertices array.
    // faceNumber * 3 gives the first index of the face, and vertexNumber (0-2)
    // selects one of its three vertices.

    // If faceNumber = 0, we are placed in the first face. Increasing vertexNumber
    // in [0, 2] gives us the vertex.
    return this->vertices[this->faces[faceNumber * 3 + vertexNumber]];
}

// ============================================================================
// EOF
// ============================================================================