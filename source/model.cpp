module;

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>

module model;

import geometry;

Model::Model(const std::string filename)
{
    std::ifstream ist{filename};
    if (!ist)
        throw std::runtime_error("Cannot open input file: " + filename);

    std::string line;
    while (std::getline(ist, line)) // All the line is consumed.
    {
        std::istringstream lineStream(line);
        std::string dataType;
        lineStream >> dataType;

        if (dataType == "v")
        {
            vec3 v;
            lineStream >> v.x >> v.y >> v.z;
            this->vertices.push_back(v);
        }
        else if (dataType == "f")
        {
            int idx;
            while (lineStream >> idx)
                this->faces.push_back(idx);
        }
    }

    std::cout << "Loaded " << this->vertices.size() << " vertices\n";
}

int Model::getNumberOfVertices() const
{
    return this->vertices.size();
}

int Model::getNumberOfFaces() const
{
    return this->faces.size() / 3;
}

vec3 Model::getVertex(const unsigned vertexNumber) const
{
    return this->vertices[vertexNumber];
}

vec3 Model::getVertex(const unsigned faceNumber, const unsigned vertexNumber) const
{
    return this->vertices[this->faces[faceNumber * 3 + vertexNumber]];
}